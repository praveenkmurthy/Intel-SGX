#include <stdio.h>
#include <tchar.h>
#include "sgx_urts.h"
#include "sgx_tsqlite_u.h"
#define ENCLAVE_FILE _T("sgx_tsqlite.signed.dll")
#define MAX_BUF_LEN 100

int runsql(sgx_enclave_id_t* eid, sqlite3 * db, const char* zSql)
{
	sqlite3_stmt *stmt = (sqlite3_stmt*) malloc(100);
	char* tmp = "test";
	sgx_status_t ret   = SGX_SUCCESS;
    int rc = -1; 
	ret = sqlite3_prepare_v2(*eid, &rc, db, zSql, strlen(zSql), (sqlite3**)&stmt, &tmp );
	//ret = sqlite3_prepare_v2(*eid, &rc, zSql, strlen(zSql), (sqlite3**)&stmt, &tmp );
    printf("Prepare done: %X %d %s %d", rc, ret, zSql, strlen(zSql));

	if (rc != SQLITE_OK)
        return rc;
	
    int rowCount = 0;
    ret = sqlite3_step(*eid, &rc, stmt);
    while (rc != SQLITE_DONE && rc != SQLITE_OK)
    {
        rowCount++;
        int colCount;
		ret = sqlite3_column_count(*eid, &colCount, stmt);
        for (int colIndex = 0; colIndex < colCount; colIndex++)
        {
            int type;
			ret = sqlite3_column_type(*eid, &type, stmt, colIndex);
            //const char * columnName = sqlite3_column_name(stmt, colIndex); ***
			char * columnName;
			ret = sqlite3_column_name(*eid, &columnName, stmt, colIndex);
            if (type == SQLITE_INTEGER)
            {
                int valInt;
				ret = sqlite3_column_int(*eid, &valInt, stmt, colIndex);
                printf("columnName = %s, Integer val = %d", columnName, valInt);
            }
            else if (type == SQLITE_FLOAT)
            {
                double valDouble;
				ret = sqlite3_column_double(*eid, &valDouble, stmt, colIndex);
                printf("columnName = %s,Double val = %f", columnName, valDouble);
            }
            else if (type == SQLITE_TEXT)
            {
                unsigned char * valChar;
				ret = sqlite3_column_text(*eid, &valChar, stmt, colIndex);
                printf("columnName = %s,Text val = %s", columnName, valChar);
            }
            else if (type == SQLITE_BLOB)
            {
                printf("columnName = %s,BLOB", columnName);
            }
            else if (type == SQLITE_NULL)
            {
                printf("columnName = %s,NULL", columnName);
            }
        }
        printf("\nLine %d, rowCount = %d", rowCount, colCount);

        ret = sqlite3_step(*eid, &rc, stmt);
    }

    ret = sqlite3_finalize(*eid, &rc, stmt);

    return rc;
}

int main()
{
sgx_enclave_id_t   eid;
sgx_status_t       ret   = SGX_SUCCESS;
sgx_launch_token_t token = {0};
int updated = 0;

// Create the Enclave with above launch token.
ret = sgx_create_enclave(ENCLAVE_FILE, SGX_DEBUG_FLAG, &token, &updated,&eid, NULL);
if (ret != SGX_SUCCESS) {
	printf("App: error %#x, failed to create enclave.\n", ret);
	return -1;
}
printf("Enclave created successfully %#x \n", ret);
// A bunch of Enclave calls (ECALL) will happen here.
sqlite3 *db;
char *zErrMsg = 0;
int rc;
char *sql;
ret = sqlite3_open(eid,&rc,"example.db",&db);

printf("Sqlite3 Open %#x %d \n", ret, rc);
if (ret != SGX_SUCCESS || rc != SGX_SUCCESS) {
	printf("App: error %#x, failed to create enclave.\n", rc);
	return -1;
}
if( rc ){
	char* ret_val=NULL;
	sqlite3_errmsg(eid, &ret_val, db);
	fprintf(stderr, "Can't open database: %s\n", ret_val);
	fprintf(stderr, "Can't open database\n");
	//exit(0);
	return -1;
} else{
	fprintf(stderr, "Opened database successfully\n");
	}

/* Create SQL statement */
sql = "SELECT * from Employee;";

//sql = "CREATE TABLE COMPANY("  \
         "ID INT PRIMARY KEY     NOT NULL," \
         "NAME           TEXT    NOT NULL," \
         "AGE            INT     NOT NULL," \
         "ADDRESS        CHAR(50)," \
         "SALARY         REAL );";

runsql(&eid, db, sql);
sqlite3_close(eid,&rc,db);

//Destroy the enclave when all Enclave calls finished.
if(SGX_SUCCESS != sgx_destroy_enclave(eid))
	return -1;
return 0;
}

void sqlite3_printf(char* log){

	printf("Sqlite3_Log: %s \n", log);

}