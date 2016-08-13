#ifndef SGX_TSQLITE_T_H__
#define SGX_TSQLITE_T_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include "sgx_edger8r.h" /* for sgx_ocall etc. */

#include "sqliteInt.h"
#include "time.h"

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SQLiteThread {
	void* tid;
	unsigned int id;
	void* pIn;
	void* pResult;
} SQLiteThread;

size_t getIncrMergerSize(const void* val);
size_t getSortSubtaskSize(const void* val);
size_t getPmaReaderSize(const void* val);
size_t getSQLiteThreadSize(const SQLiteThread** val);

int sqlite3_prepare_v2(sqlite3* db, const char* zSql, int nByte, sqlite3** ppStmt, char** pzTail);
int sqlite3_open(const char* filename, sqlite3** ppDb);
int sqlite3_open_v2(const char* filename, sqlite3** ppDb, int flags, const char* zVfs);
void* vdbeIncrPopulateThread(void* pCtx);
void* vdbeSorterFlushThread(void* pCtx);
void* vdbePmaReaderBgIncrInit(void* pCtx);
char* sqlite3_libversion();
char* sqlite3_sourceid();
int sqlite3_libversion_number();
int sqlite3_threadsafe();
int sqlite3_close(sqlite3* db);
int sqlite3_close_v2(sqlite3* db);
int sqlite3_initialize();
int sqlite3_shutdown();
int sqlite3_extended_result_codes(sqlite3* db, int onoff);
long long sqlite3_last_insert_rowid(sqlite3* db);
int sqlite3_changes(sqlite3* db);
int sqlite3_total_changes(sqlite3* db);
void sqlite3_interrupt(sqlite3* db);
int sqlite3_complete(const char* sql);
int sqlite3_complete16(const char* sql);
int sqlite3_busy_timeout(sqlite3* db, int msec);
long long sqlite3_memory_used();
long long sqlite3_memory_highwater(int resetFlag);
void sqlite3_randomness(int N, void* P);
long long sqlite3_uri_int64(const char* zFilename, const char* zParam, long long bDflt);
int sqlite3_errcode(sqlite3* db);
int sqlite3_extended_errcode(sqlite3* db);
char* sqlite3_errmsg(sqlite3* db);
void* sqlite3_errmsg16(sqlite3* db);
char* sqlite3_errstr(int rc);
int sqlite3_limit(sqlite3* db, int id, int newVal);
int sqlite3_prepare(sqlite3* db, const char* zSql, int nByte, sqlite3_stmt** ppStmt, char** pzTail);
char* sqlite3_sql(sqlite3_stmt* pStmt);
int sqlite3_stmt_readonly(sqlite3_stmt* pStmt);
int sqlite3_stmt_busy(sqlite3_stmt* pStmt);
int sqlite3_bind_double(sqlite3_stmt* pStmt, int i, double rValue);
int sqlite3_bind_int(sqlite3_stmt* p, int i, int iValue);
int sqlite3_bind_int64(sqlite3_stmt* pStmt, int i, sqlite_int64 iValue);
int sqlite3_bind_null(sqlite3_stmt* pStmt, int i);
int sqlite3_bind_value(sqlite3_stmt* pStmt, int i, const sqlite3_value* pValue);
int sqlite3_bind_zeroblob(sqlite3_stmt* pStmt, int i, int n);
int sqlite3_bind_zeroblob64(sqlite3_stmt* pStmt, int i, sqlite3_uint64 n);
int sqlite3_bind_parameter_count(sqlite3_stmt* pStmt);
char* sqlite3_bind_parameter_name(sqlite3_stmt* pStmt, int i);
int sqlite3_bind_parameter_index(sqlite3_stmt* pStmt, const char* zName);
int sqlite3_clear_bindings(sqlite3_stmt* pStmt);
int sqlite3_column_count(sqlite3_stmt* pStmt);
char* sqlite3_column_name(sqlite3_stmt* pStmt, int N);
void* sqlite3_column_name16(sqlite3_stmt* pStmt, int N);
char* sqlite3_column_database_name(sqlite3_stmt* pStmt, int N);
void* sqlite3_column_database_name16(sqlite3_stmt* pStmt, int N);
char* sqlite3_column_table_name(sqlite3_stmt* pStmt, int N);
void* sqlite3_column_table_name16(sqlite3_stmt* pStmt, int N);
char* sqlite3_column_origin_name(sqlite3_stmt* pStmt, int N);
void* sqlite3_column_origin_name16(sqlite3_stmt* pStmt, int N);
void* sqlite3_aggregate_context(sqlite3_context* p, int nBytes);
int sqlite3_step(sqlite3_stmt* pStmt);
void* sqlite3_column_blob(sqlite3_stmt* pStmt, int iCol);
int sqlite3_column_bytes(sqlite3_stmt* pStmt, int iCol);
int sqlite3_column_bytes16(sqlite3_stmt* pStmt, int iCol);
double sqlite3_column_double(sqlite3_stmt* pStmt, int iCol);
int sqlite3_column_int(sqlite3_stmt* pStmt, int iCol);
sqlite3_int64 sqlite3_column_int64(sqlite3_stmt* pStmt, int iCol);
unsigned char* sqlite3_column_text(sqlite3_stmt* pStmt, int iCol);
void* sqlite3_column_text16(sqlite3_stmt* pStmt, int iCol);
int sqlite3_column_type(sqlite3_stmt* pStmt, int iCol);
sqlite3_value* sqlite3_column_value(sqlite3_stmt* pStmt, int iCol);
int sqlite3_finalize(sqlite3_stmt* pStmt);

sgx_status_t SGX_CDECL sqlite3_printf(char* log);
sgx_status_t SGX_CDECL sqlite3OsInit(int* retval);
sgx_status_t SGX_CDECL sqlite3OsSleep(int* retval, sqlite3_vfs* pVfs, int nMicro);
sgx_status_t SGX_CDECL sqlite3_os_end(int* retval);
sgx_status_t SGX_CDECL sqlite3_win32_sleep(unsigned long int milliseconds);
sgx_status_t SGX_CDECL ocall_vdbeSorterCreateThread(int* retval, SQLiteThread** pThread, void* pIn);
sgx_status_t SGX_CDECL ocall_vdbeSorterCreateThread_flushThr(int* retval, SQLiteThread** pThread, void* pIn);
sgx_status_t SGX_CDECL ocall_vdbeSorterCreateThread_PmaReader(int* retval, SQLiteThread** pThread, void* pIn);
sgx_status_t SGX_CDECL sqlite3OsWrite(int* retval, sqlite3_file* id, const void* pBuf, int buf_size, long long offset);
sgx_status_t SGX_CDECL sqlite3OsRead(int* retval, sqlite3_file* id, void* pBuf, int buf_size, long long offset);
sgx_status_t SGX_CDECL sqlite3OsTruncate(int* retval, sqlite3_file* id, long long size);
sgx_status_t SGX_CDECL sqlite3OsFileSize(int* retval, sqlite3_file* id, long long* pSize);
sgx_status_t SGX_CDECL sqlite3OsFileControl(int* retval, sqlite3_file* id, int op, void* pArg, int arg_size);
sgx_status_t SGX_CDECL sqlite3OsFullPathname(int* retval, sqlite3_vfs* pVfs, const char* zPath, int nPathOut, char* zPathOut, int buf_size);
sgx_status_t SGX_CDECL sqlite3_vfs_register(int* retval, sqlite3_vfs* pVfs, int makeDflt);
sgx_status_t SGX_CDECL sqlite3_vfs_unregister(int* retval, sqlite3_vfs* pVfs);
sgx_status_t SGX_CDECL sqlite3OsSync(int* retval, sqlite3_file* id, int flags);
sgx_status_t SGX_CDECL sqlite3OsLock(int* retval, sqlite3_file* id, int lockType);
sgx_status_t SGX_CDECL sqlite3OsUnlock(int* retval, sqlite3_file* id, int lockType);
sgx_status_t SGX_CDECL sqlite3OsCheckReservedLock(int* retval, sqlite3_file* id, int* pResOut);
sgx_status_t SGX_CDECL sqlite3OsSectorSize(int* retval, sqlite3_file* id);
sgx_status_t SGX_CDECL sqlite3OsDeviceCharacteristics(int* retval, sqlite3_file* id);
sgx_status_t SGX_CDECL sqlite3OsFetch(int* retval, sqlite3_file* id, long long iOff, int iAmt, void** pp);
sgx_status_t SGX_CDECL sqlite3OsUnfetch(int* retval, sqlite3_file* id, long long iOff, void* p, int arg_size);
sgx_status_t SGX_CDECL sqlite3OsOpen(int* retval, sqlite3_vfs* pVfs, const char* zPath, sqlite3_file* pFile, int flags, int* pFlagsOut);
sgx_status_t SGX_CDECL sqlite3OsDelete(int* retval, sqlite3_vfs* pVfs, const char* zPath, int dirSync);
sgx_status_t SGX_CDECL sqlite3OsAccess(int* retval, sqlite3_vfs* pVfs, const char* zPath, int flags, int* pResOut);
sgx_status_t SGX_CDECL sqlite3OsRandomness(int* retval, sqlite3_vfs* pVfs, int nByte, char* zBufOut);
sgx_status_t SGX_CDECL sqlite3OsCurrentTimeInt64(int* retval, sqlite3_vfs* pVfs, sqlite3_int64* pTimeOut);
sgx_status_t SGX_CDECL sqlite3OsOpenMalloc(int* retval, sqlite3_vfs* pVfs, const char* zFile, sqlite3_file** ppFile, int flags, int* pOutFlags);
sgx_status_t SGX_CDECL sqlite3OsCloseFree(int* retval, sqlite3_file* pFile);
sgx_status_t SGX_CDECL sqlite3OsShmMap(int* retval, sqlite3_file* id, int iPage, int pgsz, int bExtend, void** pp);
sgx_status_t SGX_CDECL sqlite3OsShmLock(int* retval, sqlite3_file* id, int offset, int n, int flags);
sgx_status_t SGX_CDECL sqlite3OsShmBarrier(sqlite3_file* id);
sgx_status_t SGX_CDECL sqlite3OsShmUnmap(int* retval, sqlite3_file* id, int deleteFlag);
sgx_status_t SGX_CDECL sqlite3LoadExtension(int* retval, sqlite3* db, const char* zFile, const char* zProc, char** pzErrMsg, int buf_size);
sgx_status_t SGX_CDECL sqlite3CloseExtensions(sqlite3* db);
sgx_status_t SGX_CDECL sqlite3OsClose(int* retval, sqlite3_file* pId);
sgx_status_t SGX_CDECL get_sqlite3JournalSize(int* retval);
sgx_status_t SGX_CDECL getMxPathName(int* retval);
sgx_status_t SGX_CDECL sgx_thread_wait_untrusted_event_ocall(int* retval, const void* self);
sgx_status_t SGX_CDECL sgx_thread_set_untrusted_event_ocall(int* retval, const void* waiter);
sgx_status_t SGX_CDECL sgx_thread_setwait_untrusted_events_ocall(int* retval, const void* waiter, const void* self);
sgx_status_t SGX_CDECL sgx_thread_set_multiple_untrusted_events_ocall(int* retval, const void** waiters, size_t total);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
