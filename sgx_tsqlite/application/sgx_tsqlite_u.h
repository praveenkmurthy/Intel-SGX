#ifndef SGX_TSQLITE_U_H__
#define SGX_TSQLITE_U_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include <string.h>
#include "sgx_edger8r.h" /* for sgx_status_t etc. */

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

void SGX_UBRIDGE(SGX_NOCONVENTION, sqlite3_printf, (char* log));
int SGX_UBRIDGE(SGX_NOCONVENTION, sqlite3OsInit, ());
int SGX_UBRIDGE(SGX_NOCONVENTION, sqlite3OsSleep, (sqlite3_vfs* pVfs, int nMicro));
int SGX_UBRIDGE(SGX_NOCONVENTION, sqlite3_os_end, ());
void SGX_UBRIDGE(SGX_NOCONVENTION, sqlite3_win32_sleep, (unsigned long int milliseconds));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_vdbeSorterCreateThread, (SQLiteThread** pThread, void* pIn));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_vdbeSorterCreateThread_flushThr, (SQLiteThread** pThread, void* pIn));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_vdbeSorterCreateThread_PmaReader, (SQLiteThread** pThread, void* pIn));
int SGX_UBRIDGE(SGX_NOCONVENTION, sqlite3OsWrite, (sqlite3_file* id, const void* pBuf, int buf_size, long long offset));
int SGX_UBRIDGE(SGX_NOCONVENTION, sqlite3OsRead, (sqlite3_file* id, void* pBuf, int buf_size, long long offset));
int SGX_UBRIDGE(SGX_NOCONVENTION, sqlite3OsTruncate, (sqlite3_file* id, long long size));
int SGX_UBRIDGE(SGX_NOCONVENTION, sqlite3OsFileSize, (sqlite3_file* id, long long* pSize));
int SGX_UBRIDGE(SGX_NOCONVENTION, sqlite3OsFileControl, (sqlite3_file* id, int op, void* pArg, int arg_size));
int SGX_UBRIDGE(SGX_NOCONVENTION, sqlite3OsFullPathname, (sqlite3_vfs* pVfs, const char* zPath, int nPathOut, char* zPathOut, int buf_size));
int SGX_UBRIDGE(SGX_NOCONVENTION, sqlite3_vfs_register, (sqlite3_vfs* pVfs, int makeDflt));
int SGX_UBRIDGE(SGX_NOCONVENTION, sqlite3_vfs_unregister, (sqlite3_vfs* pVfs));
int SGX_UBRIDGE(SGX_NOCONVENTION, sqlite3OsSync, (sqlite3_file* id, int flags));
int SGX_UBRIDGE(SGX_NOCONVENTION, sqlite3OsLock, (sqlite3_file* id, int lockType));
int SGX_UBRIDGE(SGX_NOCONVENTION, sqlite3OsUnlock, (sqlite3_file* id, int lockType));
int SGX_UBRIDGE(SGX_NOCONVENTION, sqlite3OsCheckReservedLock, (sqlite3_file* id, int* pResOut));
int SGX_UBRIDGE(SGX_NOCONVENTION, sqlite3OsSectorSize, (sqlite3_file* id));
int SGX_UBRIDGE(SGX_NOCONVENTION, sqlite3OsDeviceCharacteristics, (sqlite3_file* id));
int SGX_UBRIDGE(SGX_NOCONVENTION, sqlite3OsFetch, (sqlite3_file* id, long long iOff, int iAmt, void** pp));
int SGX_UBRIDGE(SGX_NOCONVENTION, sqlite3OsUnfetch, (sqlite3_file* id, long long iOff, void* p, int arg_size));
int SGX_UBRIDGE(SGX_NOCONVENTION, sqlite3OsOpen, (sqlite3_vfs* pVfs, const char* zPath, sqlite3_file* pFile, int flags, int* pFlagsOut));
int SGX_UBRIDGE(SGX_NOCONVENTION, sqlite3OsDelete, (sqlite3_vfs* pVfs, const char* zPath, int dirSync));
int SGX_UBRIDGE(SGX_NOCONVENTION, sqlite3OsAccess, (sqlite3_vfs* pVfs, const char* zPath, int flags, int* pResOut));
int SGX_UBRIDGE(SGX_NOCONVENTION, sqlite3OsRandomness, (sqlite3_vfs* pVfs, int nByte, char* zBufOut));
int SGX_UBRIDGE(SGX_NOCONVENTION, sqlite3OsCurrentTimeInt64, (sqlite3_vfs* pVfs, sqlite3_int64* pTimeOut));
int SGX_UBRIDGE(SGX_NOCONVENTION, sqlite3OsOpenMalloc, (sqlite3_vfs* pVfs, const char* zFile, sqlite3_file** ppFile, int flags, int* pOutFlags));
int SGX_UBRIDGE(SGX_NOCONVENTION, sqlite3OsCloseFree, (sqlite3_file* pFile));
int SGX_UBRIDGE(SGX_NOCONVENTION, sqlite3OsShmMap, (sqlite3_file* id, int iPage, int pgsz, int bExtend, void** pp));
int SGX_UBRIDGE(SGX_NOCONVENTION, sqlite3OsShmLock, (sqlite3_file* id, int offset, int n, int flags));
void SGX_UBRIDGE(SGX_NOCONVENTION, sqlite3OsShmBarrier, (sqlite3_file* id));
int SGX_UBRIDGE(SGX_NOCONVENTION, sqlite3OsShmUnmap, (sqlite3_file* id, int deleteFlag));
int SGX_UBRIDGE(SGX_NOCONVENTION, sqlite3LoadExtension, (sqlite3* db, const char* zFile, const char* zProc, char** pzErrMsg, int buf_size));
void SGX_UBRIDGE(SGX_NOCONVENTION, sqlite3CloseExtensions, (sqlite3* db));
int SGX_UBRIDGE(SGX_NOCONVENTION, sqlite3OsClose, (sqlite3_file* pId));
int SGX_UBRIDGE(SGX_NOCONVENTION, get_sqlite3JournalSize, ());
int SGX_UBRIDGE(SGX_NOCONVENTION, getMxPathName, ());
int SGX_UBRIDGE(SGX_CDECL, sgx_thread_wait_untrusted_event_ocall, (const void* self));
int SGX_UBRIDGE(SGX_CDECL, sgx_thread_set_untrusted_event_ocall, (const void* waiter));
int SGX_UBRIDGE(SGX_CDECL, sgx_thread_setwait_untrusted_events_ocall, (const void* waiter, const void* self));
int SGX_UBRIDGE(SGX_CDECL, sgx_thread_set_multiple_untrusted_events_ocall, (const void** waiters, size_t total));

sgx_status_t sqlite3_prepare_v2(sgx_enclave_id_t eid, int* retval, sqlite3* db, const char* zSql, int nByte, sqlite3** ppStmt, char** pzTail);
sgx_status_t sqlite3_open(sgx_enclave_id_t eid, int* retval, const char* filename, sqlite3** ppDb);
sgx_status_t sqlite3_open_v2(sgx_enclave_id_t eid, int* retval, const char* filename, sqlite3** ppDb, int flags, const char* zVfs);
sgx_status_t vdbeIncrPopulateThread(sgx_enclave_id_t eid, void** retval, void* pCtx);
sgx_status_t vdbeSorterFlushThread(sgx_enclave_id_t eid, void** retval, void* pCtx);
sgx_status_t vdbePmaReaderBgIncrInit(sgx_enclave_id_t eid, void** retval, void* pCtx);
sgx_status_t sqlite3_libversion(sgx_enclave_id_t eid, char** retval);
sgx_status_t sqlite3_sourceid(sgx_enclave_id_t eid, char** retval);
sgx_status_t sqlite3_libversion_number(sgx_enclave_id_t eid, int* retval);
sgx_status_t sqlite3_threadsafe(sgx_enclave_id_t eid, int* retval);
sgx_status_t sqlite3_close(sgx_enclave_id_t eid, int* retval, sqlite3* db);
sgx_status_t sqlite3_close_v2(sgx_enclave_id_t eid, int* retval, sqlite3* db);
sgx_status_t sqlite3_initialize(sgx_enclave_id_t eid, int* retval);
sgx_status_t sqlite3_shutdown(sgx_enclave_id_t eid, int* retval);
sgx_status_t sqlite3_extended_result_codes(sgx_enclave_id_t eid, int* retval, sqlite3* db, int onoff);
sgx_status_t sqlite3_last_insert_rowid(sgx_enclave_id_t eid, long long* retval, sqlite3* db);
sgx_status_t sqlite3_changes(sgx_enclave_id_t eid, int* retval, sqlite3* db);
sgx_status_t sqlite3_total_changes(sgx_enclave_id_t eid, int* retval, sqlite3* db);
sgx_status_t sqlite3_interrupt(sgx_enclave_id_t eid, sqlite3* db);
sgx_status_t sqlite3_complete(sgx_enclave_id_t eid, int* retval, const char* sql);
sgx_status_t sqlite3_complete16(sgx_enclave_id_t eid, int* retval, const char* sql);
sgx_status_t sqlite3_busy_timeout(sgx_enclave_id_t eid, int* retval, sqlite3* db, int msec);
sgx_status_t sqlite3_memory_used(sgx_enclave_id_t eid, long long* retval);
sgx_status_t sqlite3_memory_highwater(sgx_enclave_id_t eid, long long* retval, int resetFlag);
sgx_status_t sqlite3_randomness(sgx_enclave_id_t eid, int N, void* P);
sgx_status_t sqlite3_uri_int64(sgx_enclave_id_t eid, long long* retval, const char* zFilename, const char* zParam, long long bDflt);
sgx_status_t sqlite3_errcode(sgx_enclave_id_t eid, int* retval, sqlite3* db);
sgx_status_t sqlite3_extended_errcode(sgx_enclave_id_t eid, int* retval, sqlite3* db);
sgx_status_t sqlite3_errmsg(sgx_enclave_id_t eid, char** retval, sqlite3* db);
sgx_status_t sqlite3_errmsg16(sgx_enclave_id_t eid, void** retval, sqlite3* db);
sgx_status_t sqlite3_errstr(sgx_enclave_id_t eid, char** retval, int rc);
sgx_status_t sqlite3_limit(sgx_enclave_id_t eid, int* retval, sqlite3* db, int id, int newVal);
sgx_status_t sqlite3_prepare(sgx_enclave_id_t eid, int* retval, sqlite3* db, const char* zSql, int nByte, sqlite3_stmt** ppStmt, char** pzTail);
sgx_status_t sqlite3_sql(sgx_enclave_id_t eid, char** retval, sqlite3_stmt* pStmt);
sgx_status_t sqlite3_stmt_readonly(sgx_enclave_id_t eid, int* retval, sqlite3_stmt* pStmt);
sgx_status_t sqlite3_stmt_busy(sgx_enclave_id_t eid, int* retval, sqlite3_stmt* pStmt);
sgx_status_t sqlite3_bind_double(sgx_enclave_id_t eid, int* retval, sqlite3_stmt* pStmt, int i, double rValue);
sgx_status_t sqlite3_bind_int(sgx_enclave_id_t eid, int* retval, sqlite3_stmt* p, int i, int iValue);
sgx_status_t sqlite3_bind_int64(sgx_enclave_id_t eid, int* retval, sqlite3_stmt* pStmt, int i, sqlite_int64 iValue);
sgx_status_t sqlite3_bind_null(sgx_enclave_id_t eid, int* retval, sqlite3_stmt* pStmt, int i);
sgx_status_t sqlite3_bind_value(sgx_enclave_id_t eid, int* retval, sqlite3_stmt* pStmt, int i, const sqlite3_value* pValue);
sgx_status_t sqlite3_bind_zeroblob(sgx_enclave_id_t eid, int* retval, sqlite3_stmt* pStmt, int i, int n);
sgx_status_t sqlite3_bind_zeroblob64(sgx_enclave_id_t eid, int* retval, sqlite3_stmt* pStmt, int i, sqlite3_uint64 n);
sgx_status_t sqlite3_bind_parameter_count(sgx_enclave_id_t eid, int* retval, sqlite3_stmt* pStmt);
sgx_status_t sqlite3_bind_parameter_name(sgx_enclave_id_t eid, char** retval, sqlite3_stmt* pStmt, int i);
sgx_status_t sqlite3_bind_parameter_index(sgx_enclave_id_t eid, int* retval, sqlite3_stmt* pStmt, const char* zName);
sgx_status_t sqlite3_clear_bindings(sgx_enclave_id_t eid, int* retval, sqlite3_stmt* pStmt);
sgx_status_t sqlite3_column_count(sgx_enclave_id_t eid, int* retval, sqlite3_stmt* pStmt);
sgx_status_t sqlite3_column_name(sgx_enclave_id_t eid, char** retval, sqlite3_stmt* pStmt, int N);
sgx_status_t sqlite3_column_name16(sgx_enclave_id_t eid, void** retval, sqlite3_stmt* pStmt, int N);
sgx_status_t sqlite3_column_database_name(sgx_enclave_id_t eid, char** retval, sqlite3_stmt* pStmt, int N);
sgx_status_t sqlite3_column_database_name16(sgx_enclave_id_t eid, void** retval, sqlite3_stmt* pStmt, int N);
sgx_status_t sqlite3_column_table_name(sgx_enclave_id_t eid, char** retval, sqlite3_stmt* pStmt, int N);
sgx_status_t sqlite3_column_table_name16(sgx_enclave_id_t eid, void** retval, sqlite3_stmt* pStmt, int N);
sgx_status_t sqlite3_column_origin_name(sgx_enclave_id_t eid, char** retval, sqlite3_stmt* pStmt, int N);
sgx_status_t sqlite3_column_origin_name16(sgx_enclave_id_t eid, void** retval, sqlite3_stmt* pStmt, int N);
sgx_status_t sqlite3_aggregate_context(sgx_enclave_id_t eid, void** retval, sqlite3_context* p, int nBytes);
sgx_status_t sqlite3_step(sgx_enclave_id_t eid, int* retval, sqlite3_stmt* pStmt);
sgx_status_t sqlite3_column_blob(sgx_enclave_id_t eid, void** retval, sqlite3_stmt* pStmt, int iCol);
sgx_status_t sqlite3_column_bytes(sgx_enclave_id_t eid, int* retval, sqlite3_stmt* pStmt, int iCol);
sgx_status_t sqlite3_column_bytes16(sgx_enclave_id_t eid, int* retval, sqlite3_stmt* pStmt, int iCol);
sgx_status_t sqlite3_column_double(sgx_enclave_id_t eid, double* retval, sqlite3_stmt* pStmt, int iCol);
sgx_status_t sqlite3_column_int(sgx_enclave_id_t eid, int* retval, sqlite3_stmt* pStmt, int iCol);
sgx_status_t sqlite3_column_int64(sgx_enclave_id_t eid, sqlite3_int64* retval, sqlite3_stmt* pStmt, int iCol);
sgx_status_t sqlite3_column_text(sgx_enclave_id_t eid, unsigned char** retval, sqlite3_stmt* pStmt, int iCol);
sgx_status_t sqlite3_column_text16(sgx_enclave_id_t eid, void** retval, sqlite3_stmt* pStmt, int iCol);
sgx_status_t sqlite3_column_type(sgx_enclave_id_t eid, int* retval, sqlite3_stmt* pStmt, int iCol);
sgx_status_t sqlite3_column_value(sgx_enclave_id_t eid, sqlite3_value** retval, sqlite3_stmt* pStmt, int iCol);
sgx_status_t sqlite3_finalize(sgx_enclave_id_t eid, int* retval, sqlite3_stmt* pStmt);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
