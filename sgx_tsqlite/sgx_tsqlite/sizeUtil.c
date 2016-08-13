
#include "sqlite3.h"
#include "sqliteInt.h"
#include "sizeUtil.h"
#include "sgx_tsqlite_t.h"

size_t getSqlite3Size(const void* val){
	return sizeof(struct sqlite3);
}

size_t getSqlite3fileSize(const sqlite3_file ** val){
	return sizeof(struct sqlite3_file);
}

size_t getSQLiteThreadSize(const SQLiteThread ** val){
	return sizeof(struct SQLiteThread);
}