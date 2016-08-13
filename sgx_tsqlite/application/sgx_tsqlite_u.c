#include "sgx_tsqlite_u.h"

typedef struct ms_sqlite3_prepare_v2_t {
	int ms_retval;
	sqlite3* ms_db;
	char* ms_zSql;
	int ms_nByte;
	sqlite3** ms_ppStmt;
	char** ms_pzTail;
} ms_sqlite3_prepare_v2_t;

typedef struct ms_sqlite3_open_t {
	int ms_retval;
	char* ms_filename;
	sqlite3** ms_ppDb;
} ms_sqlite3_open_t;

typedef struct ms_sqlite3_open_v2_t {
	int ms_retval;
	char* ms_filename;
	sqlite3** ms_ppDb;
	int ms_flags;
	char* ms_zVfs;
} ms_sqlite3_open_v2_t;

typedef struct ms_vdbeIncrPopulateThread_t {
	void* ms_retval;
	void* ms_pCtx;
} ms_vdbeIncrPopulateThread_t;

typedef struct ms_vdbeSorterFlushThread_t {
	void* ms_retval;
	void* ms_pCtx;
} ms_vdbeSorterFlushThread_t;

typedef struct ms_vdbePmaReaderBgIncrInit_t {
	void* ms_retval;
	void* ms_pCtx;
} ms_vdbePmaReaderBgIncrInit_t;

typedef struct ms_sqlite3_libversion_t {
	char* ms_retval;
} ms_sqlite3_libversion_t;

typedef struct ms_sqlite3_sourceid_t {
	char* ms_retval;
} ms_sqlite3_sourceid_t;

typedef struct ms_sqlite3_libversion_number_t {
	int ms_retval;
} ms_sqlite3_libversion_number_t;

typedef struct ms_sqlite3_threadsafe_t {
	int ms_retval;
} ms_sqlite3_threadsafe_t;

typedef struct ms_sqlite3_close_t {
	int ms_retval;
	sqlite3* ms_db;
} ms_sqlite3_close_t;

typedef struct ms_sqlite3_close_v2_t {
	int ms_retval;
	sqlite3* ms_db;
} ms_sqlite3_close_v2_t;

typedef struct ms_sqlite3_initialize_t {
	int ms_retval;
} ms_sqlite3_initialize_t;

typedef struct ms_sqlite3_shutdown_t {
	int ms_retval;
} ms_sqlite3_shutdown_t;

typedef struct ms_sqlite3_extended_result_codes_t {
	int ms_retval;
	sqlite3* ms_db;
	int ms_onoff;
} ms_sqlite3_extended_result_codes_t;

typedef struct ms_sqlite3_last_insert_rowid_t {
	long long ms_retval;
	sqlite3* ms_db;
} ms_sqlite3_last_insert_rowid_t;

typedef struct ms_sqlite3_changes_t {
	int ms_retval;
	sqlite3* ms_db;
} ms_sqlite3_changes_t;

typedef struct ms_sqlite3_total_changes_t {
	int ms_retval;
	sqlite3* ms_db;
} ms_sqlite3_total_changes_t;

typedef struct ms_sqlite3_interrupt_t {
	sqlite3* ms_db;
} ms_sqlite3_interrupt_t;

typedef struct ms_sqlite3_complete_t {
	int ms_retval;
	char* ms_sql;
} ms_sqlite3_complete_t;

typedef struct ms_sqlite3_complete16_t {
	int ms_retval;
	char* ms_sql;
} ms_sqlite3_complete16_t;

typedef struct ms_sqlite3_busy_timeout_t {
	int ms_retval;
	sqlite3* ms_db;
	int ms_msec;
} ms_sqlite3_busy_timeout_t;

typedef struct ms_sqlite3_memory_used_t {
	long long ms_retval;
} ms_sqlite3_memory_used_t;

typedef struct ms_sqlite3_memory_highwater_t {
	long long ms_retval;
	int ms_resetFlag;
} ms_sqlite3_memory_highwater_t;

typedef struct ms_sqlite3_randomness_t {
	int ms_N;
	void* ms_P;
} ms_sqlite3_randomness_t;

typedef struct ms_sqlite3_uri_int64_t {
	long long ms_retval;
	char* ms_zFilename;
	char* ms_zParam;
	long long ms_bDflt;
} ms_sqlite3_uri_int64_t;

typedef struct ms_sqlite3_errcode_t {
	int ms_retval;
	sqlite3* ms_db;
} ms_sqlite3_errcode_t;

typedef struct ms_sqlite3_extended_errcode_t {
	int ms_retval;
	sqlite3* ms_db;
} ms_sqlite3_extended_errcode_t;

typedef struct ms_sqlite3_errmsg_t {
	char* ms_retval;
	sqlite3* ms_db;
} ms_sqlite3_errmsg_t;

typedef struct ms_sqlite3_errmsg16_t {
	void* ms_retval;
	sqlite3* ms_db;
} ms_sqlite3_errmsg16_t;

typedef struct ms_sqlite3_errstr_t {
	char* ms_retval;
	int ms_rc;
} ms_sqlite3_errstr_t;

typedef struct ms_sqlite3_limit_t {
	int ms_retval;
	sqlite3* ms_db;
	int ms_id;
	int ms_newVal;
} ms_sqlite3_limit_t;

typedef struct ms_sqlite3_prepare_t {
	int ms_retval;
	sqlite3* ms_db;
	char* ms_zSql;
	int ms_nByte;
	sqlite3_stmt** ms_ppStmt;
	char** ms_pzTail;
} ms_sqlite3_prepare_t;

typedef struct ms_sqlite3_sql_t {
	char* ms_retval;
	sqlite3_stmt* ms_pStmt;
} ms_sqlite3_sql_t;

typedef struct ms_sqlite3_stmt_readonly_t {
	int ms_retval;
	sqlite3_stmt* ms_pStmt;
} ms_sqlite3_stmt_readonly_t;

typedef struct ms_sqlite3_stmt_busy_t {
	int ms_retval;
	sqlite3_stmt* ms_pStmt;
} ms_sqlite3_stmt_busy_t;

typedef struct ms_sqlite3_bind_double_t {
	int ms_retval;
	sqlite3_stmt* ms_pStmt;
	int ms_i;
	double ms_rValue;
} ms_sqlite3_bind_double_t;

typedef struct ms_sqlite3_bind_int_t {
	int ms_retval;
	sqlite3_stmt* ms_p;
	int ms_i;
	int ms_iValue;
} ms_sqlite3_bind_int_t;

typedef struct ms_sqlite3_bind_int64_t {
	int ms_retval;
	sqlite3_stmt* ms_pStmt;
	int ms_i;
	sqlite_int64 ms_iValue;
} ms_sqlite3_bind_int64_t;

typedef struct ms_sqlite3_bind_null_t {
	int ms_retval;
	sqlite3_stmt* ms_pStmt;
	int ms_i;
} ms_sqlite3_bind_null_t;

typedef struct ms_sqlite3_bind_value_t {
	int ms_retval;
	sqlite3_stmt* ms_pStmt;
	int ms_i;
	sqlite3_value* ms_pValue;
} ms_sqlite3_bind_value_t;

typedef struct ms_sqlite3_bind_zeroblob_t {
	int ms_retval;
	sqlite3_stmt* ms_pStmt;
	int ms_i;
	int ms_n;
} ms_sqlite3_bind_zeroblob_t;

typedef struct ms_sqlite3_bind_zeroblob64_t {
	int ms_retval;
	sqlite3_stmt* ms_pStmt;
	int ms_i;
	sqlite3_uint64 ms_n;
} ms_sqlite3_bind_zeroblob64_t;

typedef struct ms_sqlite3_bind_parameter_count_t {
	int ms_retval;
	sqlite3_stmt* ms_pStmt;
} ms_sqlite3_bind_parameter_count_t;

typedef struct ms_sqlite3_bind_parameter_name_t {
	char* ms_retval;
	sqlite3_stmt* ms_pStmt;
	int ms_i;
} ms_sqlite3_bind_parameter_name_t;

typedef struct ms_sqlite3_bind_parameter_index_t {
	int ms_retval;
	sqlite3_stmt* ms_pStmt;
	char* ms_zName;
} ms_sqlite3_bind_parameter_index_t;

typedef struct ms_sqlite3_clear_bindings_t {
	int ms_retval;
	sqlite3_stmt* ms_pStmt;
} ms_sqlite3_clear_bindings_t;

typedef struct ms_sqlite3_column_count_t {
	int ms_retval;
	sqlite3_stmt* ms_pStmt;
} ms_sqlite3_column_count_t;

typedef struct ms_sqlite3_column_name_t {
	char* ms_retval;
	sqlite3_stmt* ms_pStmt;
	int ms_N;
} ms_sqlite3_column_name_t;

typedef struct ms_sqlite3_column_name16_t {
	void* ms_retval;
	sqlite3_stmt* ms_pStmt;
	int ms_N;
} ms_sqlite3_column_name16_t;

typedef struct ms_sqlite3_column_database_name_t {
	char* ms_retval;
	sqlite3_stmt* ms_pStmt;
	int ms_N;
} ms_sqlite3_column_database_name_t;

typedef struct ms_sqlite3_column_database_name16_t {
	void* ms_retval;
	sqlite3_stmt* ms_pStmt;
	int ms_N;
} ms_sqlite3_column_database_name16_t;

typedef struct ms_sqlite3_column_table_name_t {
	char* ms_retval;
	sqlite3_stmt* ms_pStmt;
	int ms_N;
} ms_sqlite3_column_table_name_t;

typedef struct ms_sqlite3_column_table_name16_t {
	void* ms_retval;
	sqlite3_stmt* ms_pStmt;
	int ms_N;
} ms_sqlite3_column_table_name16_t;

typedef struct ms_sqlite3_column_origin_name_t {
	char* ms_retval;
	sqlite3_stmt* ms_pStmt;
	int ms_N;
} ms_sqlite3_column_origin_name_t;

typedef struct ms_sqlite3_column_origin_name16_t {
	void* ms_retval;
	sqlite3_stmt* ms_pStmt;
	int ms_N;
} ms_sqlite3_column_origin_name16_t;

typedef struct ms_sqlite3_aggregate_context_t {
	void* ms_retval;
	sqlite3_context* ms_p;
	int ms_nBytes;
} ms_sqlite3_aggregate_context_t;

typedef struct ms_sqlite3_step_t {
	int ms_retval;
	sqlite3_stmt* ms_pStmt;
} ms_sqlite3_step_t;

typedef struct ms_sqlite3_column_blob_t {
	void* ms_retval;
	sqlite3_stmt* ms_pStmt;
	int ms_iCol;
} ms_sqlite3_column_blob_t;

typedef struct ms_sqlite3_column_bytes_t {
	int ms_retval;
	sqlite3_stmt* ms_pStmt;
	int ms_iCol;
} ms_sqlite3_column_bytes_t;

typedef struct ms_sqlite3_column_bytes16_t {
	int ms_retval;
	sqlite3_stmt* ms_pStmt;
	int ms_iCol;
} ms_sqlite3_column_bytes16_t;

typedef struct ms_sqlite3_column_double_t {
	double ms_retval;
	sqlite3_stmt* ms_pStmt;
	int ms_iCol;
} ms_sqlite3_column_double_t;

typedef struct ms_sqlite3_column_int_t {
	int ms_retval;
	sqlite3_stmt* ms_pStmt;
	int ms_iCol;
} ms_sqlite3_column_int_t;

typedef struct ms_sqlite3_column_int64_t {
	sqlite3_int64 ms_retval;
	sqlite3_stmt* ms_pStmt;
	int ms_iCol;
} ms_sqlite3_column_int64_t;

typedef struct ms_sqlite3_column_text_t {
	unsigned char* ms_retval;
	sqlite3_stmt* ms_pStmt;
	int ms_iCol;
} ms_sqlite3_column_text_t;

typedef struct ms_sqlite3_column_text16_t {
	void* ms_retval;
	sqlite3_stmt* ms_pStmt;
	int ms_iCol;
} ms_sqlite3_column_text16_t;

typedef struct ms_sqlite3_column_type_t {
	int ms_retval;
	sqlite3_stmt* ms_pStmt;
	int ms_iCol;
} ms_sqlite3_column_type_t;

typedef struct ms_sqlite3_column_value_t {
	sqlite3_value* ms_retval;
	sqlite3_stmt* ms_pStmt;
	int ms_iCol;
} ms_sqlite3_column_value_t;

typedef struct ms_sqlite3_finalize_t {
	int ms_retval;
	sqlite3_stmt* ms_pStmt;
} ms_sqlite3_finalize_t;

typedef struct ms_sqlite3_printf_t {
	char* ms_log;
} ms_sqlite3_printf_t;

typedef struct ms_sqlite3OsInit_t {
	int ms_retval;
} ms_sqlite3OsInit_t;

typedef struct ms_sqlite3OsSleep_t {
	int ms_retval;
	sqlite3_vfs* ms_pVfs;
	int ms_nMicro;
} ms_sqlite3OsSleep_t;

typedef struct ms_sqlite3_os_end_t {
	int ms_retval;
} ms_sqlite3_os_end_t;

typedef struct ms_sqlite3_win32_sleep_t {
	unsigned long int ms_milliseconds;
} ms_sqlite3_win32_sleep_t;

typedef struct ms_ocall_vdbeSorterCreateThread_t {
	int ms_retval;
	SQLiteThread** ms_pThread;
	void* ms_pIn;
} ms_ocall_vdbeSorterCreateThread_t;

typedef struct ms_ocall_vdbeSorterCreateThread_flushThr_t {
	int ms_retval;
	SQLiteThread** ms_pThread;
	void* ms_pIn;
} ms_ocall_vdbeSorterCreateThread_flushThr_t;

typedef struct ms_ocall_vdbeSorterCreateThread_PmaReader_t {
	int ms_retval;
	SQLiteThread** ms_pThread;
	void* ms_pIn;
} ms_ocall_vdbeSorterCreateThread_PmaReader_t;

typedef struct ms_sqlite3OsWrite_t {
	int ms_retval;
	sqlite3_file* ms_id;
	void* ms_pBuf;
	int ms_buf_size;
	long long ms_offset;
} ms_sqlite3OsWrite_t;

typedef struct ms_sqlite3OsRead_t {
	int ms_retval;
	sqlite3_file* ms_id;
	void* ms_pBuf;
	int ms_buf_size;
	long long ms_offset;
} ms_sqlite3OsRead_t;

typedef struct ms_sqlite3OsTruncate_t {
	int ms_retval;
	sqlite3_file* ms_id;
	long long ms_size;
} ms_sqlite3OsTruncate_t;

typedef struct ms_sqlite3OsFileSize_t {
	int ms_retval;
	sqlite3_file* ms_id;
	long long* ms_pSize;
} ms_sqlite3OsFileSize_t;

typedef struct ms_sqlite3OsFileControl_t {
	int ms_retval;
	sqlite3_file* ms_id;
	int ms_op;
	void* ms_pArg;
	int ms_arg_size;
} ms_sqlite3OsFileControl_t;

typedef struct ms_sqlite3OsFullPathname_t {
	int ms_retval;
	sqlite3_vfs* ms_pVfs;
	char* ms_zPath;
	int ms_nPathOut;
	char* ms_zPathOut;
	int ms_buf_size;
} ms_sqlite3OsFullPathname_t;

typedef struct ms_sqlite3_vfs_register_t {
	int ms_retval;
	sqlite3_vfs* ms_pVfs;
	int ms_makeDflt;
} ms_sqlite3_vfs_register_t;

typedef struct ms_sqlite3_vfs_unregister_t {
	int ms_retval;
	sqlite3_vfs* ms_pVfs;
} ms_sqlite3_vfs_unregister_t;

typedef struct ms_sqlite3OsSync_t {
	int ms_retval;
	sqlite3_file* ms_id;
	int ms_flags;
} ms_sqlite3OsSync_t;

typedef struct ms_sqlite3OsLock_t {
	int ms_retval;
	sqlite3_file* ms_id;
	int ms_lockType;
} ms_sqlite3OsLock_t;

typedef struct ms_sqlite3OsUnlock_t {
	int ms_retval;
	sqlite3_file* ms_id;
	int ms_lockType;
} ms_sqlite3OsUnlock_t;

typedef struct ms_sqlite3OsCheckReservedLock_t {
	int ms_retval;
	sqlite3_file* ms_id;
	int* ms_pResOut;
} ms_sqlite3OsCheckReservedLock_t;

typedef struct ms_sqlite3OsSectorSize_t {
	int ms_retval;
	sqlite3_file* ms_id;
} ms_sqlite3OsSectorSize_t;

typedef struct ms_sqlite3OsDeviceCharacteristics_t {
	int ms_retval;
	sqlite3_file* ms_id;
} ms_sqlite3OsDeviceCharacteristics_t;

typedef struct ms_sqlite3OsFetch_t {
	int ms_retval;
	sqlite3_file* ms_id;
	long long ms_iOff;
	int ms_iAmt;
	void** ms_pp;
} ms_sqlite3OsFetch_t;

typedef struct ms_sqlite3OsUnfetch_t {
	int ms_retval;
	sqlite3_file* ms_id;
	long long ms_iOff;
	void* ms_p;
	int ms_arg_size;
} ms_sqlite3OsUnfetch_t;

typedef struct ms_sqlite3OsOpen_t {
	int ms_retval;
	sqlite3_vfs* ms_pVfs;
	char* ms_zPath;
	sqlite3_file* ms_pFile;
	int ms_flags;
	int* ms_pFlagsOut;
} ms_sqlite3OsOpen_t;

typedef struct ms_sqlite3OsDelete_t {
	int ms_retval;
	sqlite3_vfs* ms_pVfs;
	char* ms_zPath;
	int ms_dirSync;
} ms_sqlite3OsDelete_t;

typedef struct ms_sqlite3OsAccess_t {
	int ms_retval;
	sqlite3_vfs* ms_pVfs;
	char* ms_zPath;
	int ms_flags;
	int* ms_pResOut;
} ms_sqlite3OsAccess_t;

typedef struct ms_sqlite3OsRandomness_t {
	int ms_retval;
	sqlite3_vfs* ms_pVfs;
	int ms_nByte;
	char* ms_zBufOut;
} ms_sqlite3OsRandomness_t;

typedef struct ms_sqlite3OsCurrentTimeInt64_t {
	int ms_retval;
	sqlite3_vfs* ms_pVfs;
	sqlite3_int64* ms_pTimeOut;
} ms_sqlite3OsCurrentTimeInt64_t;

typedef struct ms_sqlite3OsOpenMalloc_t {
	int ms_retval;
	sqlite3_vfs* ms_pVfs;
	char* ms_zFile;
	sqlite3_file** ms_ppFile;
	int ms_flags;
	int* ms_pOutFlags;
} ms_sqlite3OsOpenMalloc_t;

typedef struct ms_sqlite3OsCloseFree_t {
	int ms_retval;
	sqlite3_file* ms_pFile;
} ms_sqlite3OsCloseFree_t;

typedef struct ms_sqlite3OsShmMap_t {
	int ms_retval;
	sqlite3_file* ms_id;
	int ms_iPage;
	int ms_pgsz;
	int ms_bExtend;
	void** ms_pp;
} ms_sqlite3OsShmMap_t;

typedef struct ms_sqlite3OsShmLock_t {
	int ms_retval;
	sqlite3_file* ms_id;
	int ms_offset;
	int ms_n;
	int ms_flags;
} ms_sqlite3OsShmLock_t;

typedef struct ms_sqlite3OsShmBarrier_t {
	sqlite3_file* ms_id;
} ms_sqlite3OsShmBarrier_t;

typedef struct ms_sqlite3OsShmUnmap_t {
	int ms_retval;
	sqlite3_file* ms_id;
	int ms_deleteFlag;
} ms_sqlite3OsShmUnmap_t;

typedef struct ms_sqlite3LoadExtension_t {
	int ms_retval;
	sqlite3* ms_db;
	char* ms_zFile;
	char* ms_zProc;
	char** ms_pzErrMsg;
	int ms_buf_size;
} ms_sqlite3LoadExtension_t;

typedef struct ms_sqlite3CloseExtensions_t {
	sqlite3* ms_db;
} ms_sqlite3CloseExtensions_t;

typedef struct ms_sqlite3OsClose_t {
	int ms_retval;
	sqlite3_file* ms_pId;
} ms_sqlite3OsClose_t;

typedef struct ms_get_sqlite3JournalSize_t {
	int ms_retval;
} ms_get_sqlite3JournalSize_t;

typedef struct ms_getMxPathName_t {
	int ms_retval;
} ms_getMxPathName_t;

typedef struct ms_sgx_thread_wait_untrusted_event_ocall_t {
	int ms_retval;
	void* ms_self;
} ms_sgx_thread_wait_untrusted_event_ocall_t;

typedef struct ms_sgx_thread_set_untrusted_event_ocall_t {
	int ms_retval;
	void* ms_waiter;
} ms_sgx_thread_set_untrusted_event_ocall_t;

typedef struct ms_sgx_thread_setwait_untrusted_events_ocall_t {
	int ms_retval;
	void* ms_waiter;
	void* ms_self;
} ms_sgx_thread_setwait_untrusted_events_ocall_t;

typedef struct ms_sgx_thread_set_multiple_untrusted_events_ocall_t {
	int ms_retval;
	void** ms_waiters;
	size_t ms_total;
} ms_sgx_thread_set_multiple_untrusted_events_ocall_t;

static sgx_status_t SGX_CDECL sgx_tsqlite_sqlite3_printf(void* pms)
{
	ms_sqlite3_printf_t* ms = SGX_CAST(ms_sqlite3_printf_t*, pms);
	sqlite3_printf(ms->ms_log);
	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL sgx_tsqlite_sqlite3OsInit(void* pms)
{
	ms_sqlite3OsInit_t* ms = SGX_CAST(ms_sqlite3OsInit_t*, pms);
	ms->ms_retval = sqlite3OsInit();
	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL sgx_tsqlite_sqlite3OsSleep(void* pms)
{
	ms_sqlite3OsSleep_t* ms = SGX_CAST(ms_sqlite3OsSleep_t*, pms);
	ms->ms_retval = sqlite3OsSleep(ms->ms_pVfs, ms->ms_nMicro);
	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL sgx_tsqlite_sqlite3_os_end(void* pms)
{
	ms_sqlite3_os_end_t* ms = SGX_CAST(ms_sqlite3_os_end_t*, pms);
	ms->ms_retval = sqlite3_os_end();
	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL sgx_tsqlite_sqlite3_win32_sleep(void* pms)
{
	ms_sqlite3_win32_sleep_t* ms = SGX_CAST(ms_sqlite3_win32_sleep_t*, pms);
	sqlite3_win32_sleep(ms->ms_milliseconds);
	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL sgx_tsqlite_ocall_vdbeSorterCreateThread(void* pms)
{
	ms_ocall_vdbeSorterCreateThread_t* ms = SGX_CAST(ms_ocall_vdbeSorterCreateThread_t*, pms);
	ms->ms_retval = ocall_vdbeSorterCreateThread(ms->ms_pThread, ms->ms_pIn);
	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL sgx_tsqlite_ocall_vdbeSorterCreateThread_flushThr(void* pms)
{
	ms_ocall_vdbeSorterCreateThread_flushThr_t* ms = SGX_CAST(ms_ocall_vdbeSorterCreateThread_flushThr_t*, pms);
	ms->ms_retval = ocall_vdbeSorterCreateThread_flushThr(ms->ms_pThread, ms->ms_pIn);
	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL sgx_tsqlite_ocall_vdbeSorterCreateThread_PmaReader(void* pms)
{
	ms_ocall_vdbeSorterCreateThread_PmaReader_t* ms = SGX_CAST(ms_ocall_vdbeSorterCreateThread_PmaReader_t*, pms);
	ms->ms_retval = ocall_vdbeSorterCreateThread_PmaReader(ms->ms_pThread, ms->ms_pIn);
	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL sgx_tsqlite_sqlite3OsWrite(void* pms)
{
	ms_sqlite3OsWrite_t* ms = SGX_CAST(ms_sqlite3OsWrite_t*, pms);
	ms->ms_retval = sqlite3OsWrite(ms->ms_id, (const void*)ms->ms_pBuf, ms->ms_buf_size, ms->ms_offset);
	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL sgx_tsqlite_sqlite3OsRead(void* pms)
{
	ms_sqlite3OsRead_t* ms = SGX_CAST(ms_sqlite3OsRead_t*, pms);
	ms->ms_retval = sqlite3OsRead(ms->ms_id, ms->ms_pBuf, ms->ms_buf_size, ms->ms_offset);
	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL sgx_tsqlite_sqlite3OsTruncate(void* pms)
{
	ms_sqlite3OsTruncate_t* ms = SGX_CAST(ms_sqlite3OsTruncate_t*, pms);
	ms->ms_retval = sqlite3OsTruncate(ms->ms_id, ms->ms_size);
	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL sgx_tsqlite_sqlite3OsFileSize(void* pms)
{
	ms_sqlite3OsFileSize_t* ms = SGX_CAST(ms_sqlite3OsFileSize_t*, pms);
	ms->ms_retval = sqlite3OsFileSize(ms->ms_id, ms->ms_pSize);
	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL sgx_tsqlite_sqlite3OsFileControl(void* pms)
{
	ms_sqlite3OsFileControl_t* ms = SGX_CAST(ms_sqlite3OsFileControl_t*, pms);
	ms->ms_retval = sqlite3OsFileControl(ms->ms_id, ms->ms_op, ms->ms_pArg, ms->ms_arg_size);
	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL sgx_tsqlite_sqlite3OsFullPathname(void* pms)
{
	ms_sqlite3OsFullPathname_t* ms = SGX_CAST(ms_sqlite3OsFullPathname_t*, pms);
	ms->ms_retval = sqlite3OsFullPathname(ms->ms_pVfs, (const char*)ms->ms_zPath, ms->ms_nPathOut, ms->ms_zPathOut, ms->ms_buf_size);
	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL sgx_tsqlite_sqlite3_vfs_register(void* pms)
{
	ms_sqlite3_vfs_register_t* ms = SGX_CAST(ms_sqlite3_vfs_register_t*, pms);
	ms->ms_retval = sqlite3_vfs_register(ms->ms_pVfs, ms->ms_makeDflt);
	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL sgx_tsqlite_sqlite3_vfs_unregister(void* pms)
{
	ms_sqlite3_vfs_unregister_t* ms = SGX_CAST(ms_sqlite3_vfs_unregister_t*, pms);
	ms->ms_retval = sqlite3_vfs_unregister(ms->ms_pVfs);
	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL sgx_tsqlite_sqlite3OsSync(void* pms)
{
	ms_sqlite3OsSync_t* ms = SGX_CAST(ms_sqlite3OsSync_t*, pms);
	ms->ms_retval = sqlite3OsSync(ms->ms_id, ms->ms_flags);
	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL sgx_tsqlite_sqlite3OsLock(void* pms)
{
	ms_sqlite3OsLock_t* ms = SGX_CAST(ms_sqlite3OsLock_t*, pms);
	ms->ms_retval = sqlite3OsLock(ms->ms_id, ms->ms_lockType);
	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL sgx_tsqlite_sqlite3OsUnlock(void* pms)
{
	ms_sqlite3OsUnlock_t* ms = SGX_CAST(ms_sqlite3OsUnlock_t*, pms);
	ms->ms_retval = sqlite3OsUnlock(ms->ms_id, ms->ms_lockType);
	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL sgx_tsqlite_sqlite3OsCheckReservedLock(void* pms)
{
	ms_sqlite3OsCheckReservedLock_t* ms = SGX_CAST(ms_sqlite3OsCheckReservedLock_t*, pms);
	ms->ms_retval = sqlite3OsCheckReservedLock(ms->ms_id, ms->ms_pResOut);
	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL sgx_tsqlite_sqlite3OsSectorSize(void* pms)
{
	ms_sqlite3OsSectorSize_t* ms = SGX_CAST(ms_sqlite3OsSectorSize_t*, pms);
	ms->ms_retval = sqlite3OsSectorSize(ms->ms_id);
	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL sgx_tsqlite_sqlite3OsDeviceCharacteristics(void* pms)
{
	ms_sqlite3OsDeviceCharacteristics_t* ms = SGX_CAST(ms_sqlite3OsDeviceCharacteristics_t*, pms);
	ms->ms_retval = sqlite3OsDeviceCharacteristics(ms->ms_id);
	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL sgx_tsqlite_sqlite3OsFetch(void* pms)
{
	ms_sqlite3OsFetch_t* ms = SGX_CAST(ms_sqlite3OsFetch_t*, pms);
	ms->ms_retval = sqlite3OsFetch(ms->ms_id, ms->ms_iOff, ms->ms_iAmt, ms->ms_pp);
	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL sgx_tsqlite_sqlite3OsUnfetch(void* pms)
{
	ms_sqlite3OsUnfetch_t* ms = SGX_CAST(ms_sqlite3OsUnfetch_t*, pms);
	ms->ms_retval = sqlite3OsUnfetch(ms->ms_id, ms->ms_iOff, ms->ms_p, ms->ms_arg_size);
	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL sgx_tsqlite_sqlite3OsOpen(void* pms)
{
	ms_sqlite3OsOpen_t* ms = SGX_CAST(ms_sqlite3OsOpen_t*, pms);
	ms->ms_retval = sqlite3OsOpen(ms->ms_pVfs, (const char*)ms->ms_zPath, ms->ms_pFile, ms->ms_flags, ms->ms_pFlagsOut);
	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL sgx_tsqlite_sqlite3OsDelete(void* pms)
{
	ms_sqlite3OsDelete_t* ms = SGX_CAST(ms_sqlite3OsDelete_t*, pms);
	ms->ms_retval = sqlite3OsDelete(ms->ms_pVfs, (const char*)ms->ms_zPath, ms->ms_dirSync);
	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL sgx_tsqlite_sqlite3OsAccess(void* pms)
{
	ms_sqlite3OsAccess_t* ms = SGX_CAST(ms_sqlite3OsAccess_t*, pms);
	ms->ms_retval = sqlite3OsAccess(ms->ms_pVfs, (const char*)ms->ms_zPath, ms->ms_flags, ms->ms_pResOut);
	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL sgx_tsqlite_sqlite3OsRandomness(void* pms)
{
	ms_sqlite3OsRandomness_t* ms = SGX_CAST(ms_sqlite3OsRandomness_t*, pms);
	ms->ms_retval = sqlite3OsRandomness(ms->ms_pVfs, ms->ms_nByte, ms->ms_zBufOut);
	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL sgx_tsqlite_sqlite3OsCurrentTimeInt64(void* pms)
{
	ms_sqlite3OsCurrentTimeInt64_t* ms = SGX_CAST(ms_sqlite3OsCurrentTimeInt64_t*, pms);
	ms->ms_retval = sqlite3OsCurrentTimeInt64(ms->ms_pVfs, ms->ms_pTimeOut);
	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL sgx_tsqlite_sqlite3OsOpenMalloc(void* pms)
{
	ms_sqlite3OsOpenMalloc_t* ms = SGX_CAST(ms_sqlite3OsOpenMalloc_t*, pms);
	ms->ms_retval = sqlite3OsOpenMalloc(ms->ms_pVfs, (const char*)ms->ms_zFile, ms->ms_ppFile, ms->ms_flags, ms->ms_pOutFlags);
	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL sgx_tsqlite_sqlite3OsCloseFree(void* pms)
{
	ms_sqlite3OsCloseFree_t* ms = SGX_CAST(ms_sqlite3OsCloseFree_t*, pms);
	ms->ms_retval = sqlite3OsCloseFree(ms->ms_pFile);
	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL sgx_tsqlite_sqlite3OsShmMap(void* pms)
{
	ms_sqlite3OsShmMap_t* ms = SGX_CAST(ms_sqlite3OsShmMap_t*, pms);
	ms->ms_retval = sqlite3OsShmMap(ms->ms_id, ms->ms_iPage, ms->ms_pgsz, ms->ms_bExtend, ms->ms_pp);
	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL sgx_tsqlite_sqlite3OsShmLock(void* pms)
{
	ms_sqlite3OsShmLock_t* ms = SGX_CAST(ms_sqlite3OsShmLock_t*, pms);
	ms->ms_retval = sqlite3OsShmLock(ms->ms_id, ms->ms_offset, ms->ms_n, ms->ms_flags);
	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL sgx_tsqlite_sqlite3OsShmBarrier(void* pms)
{
	ms_sqlite3OsShmBarrier_t* ms = SGX_CAST(ms_sqlite3OsShmBarrier_t*, pms);
	sqlite3OsShmBarrier(ms->ms_id);
	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL sgx_tsqlite_sqlite3OsShmUnmap(void* pms)
{
	ms_sqlite3OsShmUnmap_t* ms = SGX_CAST(ms_sqlite3OsShmUnmap_t*, pms);
	ms->ms_retval = sqlite3OsShmUnmap(ms->ms_id, ms->ms_deleteFlag);
	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL sgx_tsqlite_sqlite3LoadExtension(void* pms)
{
	ms_sqlite3LoadExtension_t* ms = SGX_CAST(ms_sqlite3LoadExtension_t*, pms);
	ms->ms_retval = sqlite3LoadExtension(ms->ms_db, (const char*)ms->ms_zFile, (const char*)ms->ms_zProc, ms->ms_pzErrMsg, ms->ms_buf_size);
	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL sgx_tsqlite_sqlite3CloseExtensions(void* pms)
{
	ms_sqlite3CloseExtensions_t* ms = SGX_CAST(ms_sqlite3CloseExtensions_t*, pms);
	sqlite3CloseExtensions(ms->ms_db);
	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL sgx_tsqlite_sqlite3OsClose(void* pms)
{
	ms_sqlite3OsClose_t* ms = SGX_CAST(ms_sqlite3OsClose_t*, pms);
	ms->ms_retval = sqlite3OsClose(ms->ms_pId);
	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL sgx_tsqlite_get_sqlite3JournalSize(void* pms)
{
	ms_get_sqlite3JournalSize_t* ms = SGX_CAST(ms_get_sqlite3JournalSize_t*, pms);
	ms->ms_retval = get_sqlite3JournalSize();
	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL sgx_tsqlite_getMxPathName(void* pms)
{
	ms_getMxPathName_t* ms = SGX_CAST(ms_getMxPathName_t*, pms);
	ms->ms_retval = getMxPathName();
	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL sgx_tsqlite_sgx_thread_wait_untrusted_event_ocall(void* pms)
{
	ms_sgx_thread_wait_untrusted_event_ocall_t* ms = SGX_CAST(ms_sgx_thread_wait_untrusted_event_ocall_t*, pms);
	ms->ms_retval = sgx_thread_wait_untrusted_event_ocall((const void*)ms->ms_self);
	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL sgx_tsqlite_sgx_thread_set_untrusted_event_ocall(void* pms)
{
	ms_sgx_thread_set_untrusted_event_ocall_t* ms = SGX_CAST(ms_sgx_thread_set_untrusted_event_ocall_t*, pms);
	ms->ms_retval = sgx_thread_set_untrusted_event_ocall((const void*)ms->ms_waiter);
	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL sgx_tsqlite_sgx_thread_setwait_untrusted_events_ocall(void* pms)
{
	ms_sgx_thread_setwait_untrusted_events_ocall_t* ms = SGX_CAST(ms_sgx_thread_setwait_untrusted_events_ocall_t*, pms);
	ms->ms_retval = sgx_thread_setwait_untrusted_events_ocall((const void*)ms->ms_waiter, (const void*)ms->ms_self);
	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL sgx_tsqlite_sgx_thread_set_multiple_untrusted_events_ocall(void* pms)
{
	ms_sgx_thread_set_multiple_untrusted_events_ocall_t* ms = SGX_CAST(ms_sgx_thread_set_multiple_untrusted_events_ocall_t*, pms);
	ms->ms_retval = sgx_thread_set_multiple_untrusted_events_ocall((const void**)ms->ms_waiters, ms->ms_total);
	return SGX_SUCCESS;
}

static const struct {
	size_t nr_ocall;
	void * func_addr[44];
} ocall_table_sgx_tsqlite = {
	44,
	{
		(void*)(uintptr_t)sgx_tsqlite_sqlite3_printf,
		(void*)(uintptr_t)sgx_tsqlite_sqlite3OsInit,
		(void*)(uintptr_t)sgx_tsqlite_sqlite3OsSleep,
		(void*)(uintptr_t)sgx_tsqlite_sqlite3_os_end,
		(void*)(uintptr_t)sgx_tsqlite_sqlite3_win32_sleep,
		(void*)(uintptr_t)sgx_tsqlite_ocall_vdbeSorterCreateThread,
		(void*)(uintptr_t)sgx_tsqlite_ocall_vdbeSorterCreateThread_flushThr,
		(void*)(uintptr_t)sgx_tsqlite_ocall_vdbeSorterCreateThread_PmaReader,
		(void*)(uintptr_t)sgx_tsqlite_sqlite3OsWrite,
		(void*)(uintptr_t)sgx_tsqlite_sqlite3OsRead,
		(void*)(uintptr_t)sgx_tsqlite_sqlite3OsTruncate,
		(void*)(uintptr_t)sgx_tsqlite_sqlite3OsFileSize,
		(void*)(uintptr_t)sgx_tsqlite_sqlite3OsFileControl,
		(void*)(uintptr_t)sgx_tsqlite_sqlite3OsFullPathname,
		(void*)(uintptr_t)sgx_tsqlite_sqlite3_vfs_register,
		(void*)(uintptr_t)sgx_tsqlite_sqlite3_vfs_unregister,
		(void*)(uintptr_t)sgx_tsqlite_sqlite3OsSync,
		(void*)(uintptr_t)sgx_tsqlite_sqlite3OsLock,
		(void*)(uintptr_t)sgx_tsqlite_sqlite3OsUnlock,
		(void*)(uintptr_t)sgx_tsqlite_sqlite3OsCheckReservedLock,
		(void*)(uintptr_t)sgx_tsqlite_sqlite3OsSectorSize,
		(void*)(uintptr_t)sgx_tsqlite_sqlite3OsDeviceCharacteristics,
		(void*)(uintptr_t)sgx_tsqlite_sqlite3OsFetch,
		(void*)(uintptr_t)sgx_tsqlite_sqlite3OsUnfetch,
		(void*)(uintptr_t)sgx_tsqlite_sqlite3OsOpen,
		(void*)(uintptr_t)sgx_tsqlite_sqlite3OsDelete,
		(void*)(uintptr_t)sgx_tsqlite_sqlite3OsAccess,
		(void*)(uintptr_t)sgx_tsqlite_sqlite3OsRandomness,
		(void*)(uintptr_t)sgx_tsqlite_sqlite3OsCurrentTimeInt64,
		(void*)(uintptr_t)sgx_tsqlite_sqlite3OsOpenMalloc,
		(void*)(uintptr_t)sgx_tsqlite_sqlite3OsCloseFree,
		(void*)(uintptr_t)sgx_tsqlite_sqlite3OsShmMap,
		(void*)(uintptr_t)sgx_tsqlite_sqlite3OsShmLock,
		(void*)(uintptr_t)sgx_tsqlite_sqlite3OsShmBarrier,
		(void*)(uintptr_t)sgx_tsqlite_sqlite3OsShmUnmap,
		(void*)(uintptr_t)sgx_tsqlite_sqlite3LoadExtension,
		(void*)(uintptr_t)sgx_tsqlite_sqlite3CloseExtensions,
		(void*)(uintptr_t)sgx_tsqlite_sqlite3OsClose,
		(void*)(uintptr_t)sgx_tsqlite_get_sqlite3JournalSize,
		(void*)(uintptr_t)sgx_tsqlite_getMxPathName,
		(void*)(uintptr_t)sgx_tsqlite_sgx_thread_wait_untrusted_event_ocall,
		(void*)(uintptr_t)sgx_tsqlite_sgx_thread_set_untrusted_event_ocall,
		(void*)(uintptr_t)sgx_tsqlite_sgx_thread_setwait_untrusted_events_ocall,
		(void*)(uintptr_t)sgx_tsqlite_sgx_thread_set_multiple_untrusted_events_ocall,
	}
};

sgx_status_t sqlite3_prepare_v2(sgx_enclave_id_t eid, int* retval, sqlite3* db, const char* zSql, int nByte, sqlite3** ppStmt, char** pzTail)
{
	sgx_status_t status;
	ms_sqlite3_prepare_v2_t ms;
	ms.ms_db = db;
	ms.ms_zSql = (char*)zSql;
	ms.ms_nByte = nByte;
	ms.ms_ppStmt = ppStmt;
	ms.ms_pzTail = pzTail;
	status = sgx_ecall(eid, 0, &ocall_table_sgx_tsqlite, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t sqlite3_open(sgx_enclave_id_t eid, int* retval, const char* filename, sqlite3** ppDb)
{
	sgx_status_t status;
	ms_sqlite3_open_t ms;
	ms.ms_filename = (char*)filename;
	ms.ms_ppDb = ppDb;
	status = sgx_ecall(eid, 1, &ocall_table_sgx_tsqlite, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t sqlite3_open_v2(sgx_enclave_id_t eid, int* retval, const char* filename, sqlite3** ppDb, int flags, const char* zVfs)
{
	sgx_status_t status;
	ms_sqlite3_open_v2_t ms;
	ms.ms_filename = (char*)filename;
	ms.ms_ppDb = ppDb;
	ms.ms_flags = flags;
	ms.ms_zVfs = (char*)zVfs;
	status = sgx_ecall(eid, 2, &ocall_table_sgx_tsqlite, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t vdbeIncrPopulateThread(sgx_enclave_id_t eid, void** retval, void* pCtx)
{
	sgx_status_t status;
	ms_vdbeIncrPopulateThread_t ms;
	ms.ms_pCtx = pCtx;
	status = sgx_ecall(eid, 3, &ocall_table_sgx_tsqlite, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t vdbeSorterFlushThread(sgx_enclave_id_t eid, void** retval, void* pCtx)
{
	sgx_status_t status;
	ms_vdbeSorterFlushThread_t ms;
	ms.ms_pCtx = pCtx;
	status = sgx_ecall(eid, 4, &ocall_table_sgx_tsqlite, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t vdbePmaReaderBgIncrInit(sgx_enclave_id_t eid, void** retval, void* pCtx)
{
	sgx_status_t status;
	ms_vdbePmaReaderBgIncrInit_t ms;
	ms.ms_pCtx = pCtx;
	status = sgx_ecall(eid, 5, &ocall_table_sgx_tsqlite, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t sqlite3_libversion(sgx_enclave_id_t eid, char** retval)
{
	sgx_status_t status;
	ms_sqlite3_libversion_t ms;
	status = sgx_ecall(eid, 6, &ocall_table_sgx_tsqlite, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t sqlite3_sourceid(sgx_enclave_id_t eid, char** retval)
{
	sgx_status_t status;
	ms_sqlite3_sourceid_t ms;
	status = sgx_ecall(eid, 7, &ocall_table_sgx_tsqlite, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t sqlite3_libversion_number(sgx_enclave_id_t eid, int* retval)
{
	sgx_status_t status;
	ms_sqlite3_libversion_number_t ms;
	status = sgx_ecall(eid, 8, &ocall_table_sgx_tsqlite, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t sqlite3_threadsafe(sgx_enclave_id_t eid, int* retval)
{
	sgx_status_t status;
	ms_sqlite3_threadsafe_t ms;
	status = sgx_ecall(eid, 9, &ocall_table_sgx_tsqlite, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t sqlite3_close(sgx_enclave_id_t eid, int* retval, sqlite3* db)
{
	sgx_status_t status;
	ms_sqlite3_close_t ms;
	ms.ms_db = db;
	status = sgx_ecall(eid, 10, &ocall_table_sgx_tsqlite, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t sqlite3_close_v2(sgx_enclave_id_t eid, int* retval, sqlite3* db)
{
	sgx_status_t status;
	ms_sqlite3_close_v2_t ms;
	ms.ms_db = db;
	status = sgx_ecall(eid, 11, &ocall_table_sgx_tsqlite, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t sqlite3_initialize(sgx_enclave_id_t eid, int* retval)
{
	sgx_status_t status;
	ms_sqlite3_initialize_t ms;
	status = sgx_ecall(eid, 12, &ocall_table_sgx_tsqlite, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t sqlite3_shutdown(sgx_enclave_id_t eid, int* retval)
{
	sgx_status_t status;
	ms_sqlite3_shutdown_t ms;
	status = sgx_ecall(eid, 13, &ocall_table_sgx_tsqlite, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t sqlite3_extended_result_codes(sgx_enclave_id_t eid, int* retval, sqlite3* db, int onoff)
{
	sgx_status_t status;
	ms_sqlite3_extended_result_codes_t ms;
	ms.ms_db = db;
	ms.ms_onoff = onoff;
	status = sgx_ecall(eid, 14, &ocall_table_sgx_tsqlite, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t sqlite3_last_insert_rowid(sgx_enclave_id_t eid, long long* retval, sqlite3* db)
{
	sgx_status_t status;
	ms_sqlite3_last_insert_rowid_t ms;
	ms.ms_db = db;
	status = sgx_ecall(eid, 15, &ocall_table_sgx_tsqlite, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t sqlite3_changes(sgx_enclave_id_t eid, int* retval, sqlite3* db)
{
	sgx_status_t status;
	ms_sqlite3_changes_t ms;
	ms.ms_db = db;
	status = sgx_ecall(eid, 16, &ocall_table_sgx_tsqlite, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t sqlite3_total_changes(sgx_enclave_id_t eid, int* retval, sqlite3* db)
{
	sgx_status_t status;
	ms_sqlite3_total_changes_t ms;
	ms.ms_db = db;
	status = sgx_ecall(eid, 17, &ocall_table_sgx_tsqlite, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t sqlite3_interrupt(sgx_enclave_id_t eid, sqlite3* db)
{
	sgx_status_t status;
	ms_sqlite3_interrupt_t ms;
	ms.ms_db = db;
	status = sgx_ecall(eid, 18, &ocall_table_sgx_tsqlite, &ms);
	return status;
}

sgx_status_t sqlite3_complete(sgx_enclave_id_t eid, int* retval, const char* sql)
{
	sgx_status_t status;
	ms_sqlite3_complete_t ms;
	ms.ms_sql = (char*)sql;
	status = sgx_ecall(eid, 19, &ocall_table_sgx_tsqlite, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t sqlite3_complete16(sgx_enclave_id_t eid, int* retval, const char* sql)
{
	sgx_status_t status;
	ms_sqlite3_complete16_t ms;
	ms.ms_sql = (char*)sql;
	status = sgx_ecall(eid, 20, &ocall_table_sgx_tsqlite, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t sqlite3_busy_timeout(sgx_enclave_id_t eid, int* retval, sqlite3* db, int msec)
{
	sgx_status_t status;
	ms_sqlite3_busy_timeout_t ms;
	ms.ms_db = db;
	ms.ms_msec = msec;
	status = sgx_ecall(eid, 21, &ocall_table_sgx_tsqlite, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t sqlite3_memory_used(sgx_enclave_id_t eid, long long* retval)
{
	sgx_status_t status;
	ms_sqlite3_memory_used_t ms;
	status = sgx_ecall(eid, 22, &ocall_table_sgx_tsqlite, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t sqlite3_memory_highwater(sgx_enclave_id_t eid, long long* retval, int resetFlag)
{
	sgx_status_t status;
	ms_sqlite3_memory_highwater_t ms;
	ms.ms_resetFlag = resetFlag;
	status = sgx_ecall(eid, 23, &ocall_table_sgx_tsqlite, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t sqlite3_randomness(sgx_enclave_id_t eid, int N, void* P)
{
	sgx_status_t status;
	ms_sqlite3_randomness_t ms;
	ms.ms_N = N;
	ms.ms_P = P;
	status = sgx_ecall(eid, 24, &ocall_table_sgx_tsqlite, &ms);
	return status;
}

sgx_status_t sqlite3_uri_int64(sgx_enclave_id_t eid, long long* retval, const char* zFilename, const char* zParam, long long bDflt)
{
	sgx_status_t status;
	ms_sqlite3_uri_int64_t ms;
	ms.ms_zFilename = (char*)zFilename;
	ms.ms_zParam = (char*)zParam;
	ms.ms_bDflt = bDflt;
	status = sgx_ecall(eid, 25, &ocall_table_sgx_tsqlite, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t sqlite3_errcode(sgx_enclave_id_t eid, int* retval, sqlite3* db)
{
	sgx_status_t status;
	ms_sqlite3_errcode_t ms;
	ms.ms_db = db;
	status = sgx_ecall(eid, 26, &ocall_table_sgx_tsqlite, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t sqlite3_extended_errcode(sgx_enclave_id_t eid, int* retval, sqlite3* db)
{
	sgx_status_t status;
	ms_sqlite3_extended_errcode_t ms;
	ms.ms_db = db;
	status = sgx_ecall(eid, 27, &ocall_table_sgx_tsqlite, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t sqlite3_errmsg(sgx_enclave_id_t eid, char** retval, sqlite3* db)
{
	sgx_status_t status;
	ms_sqlite3_errmsg_t ms;
	ms.ms_db = db;
	status = sgx_ecall(eid, 28, &ocall_table_sgx_tsqlite, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t sqlite3_errmsg16(sgx_enclave_id_t eid, void** retval, sqlite3* db)
{
	sgx_status_t status;
	ms_sqlite3_errmsg16_t ms;
	ms.ms_db = db;
	status = sgx_ecall(eid, 29, &ocall_table_sgx_tsqlite, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t sqlite3_errstr(sgx_enclave_id_t eid, char** retval, int rc)
{
	sgx_status_t status;
	ms_sqlite3_errstr_t ms;
	ms.ms_rc = rc;
	status = sgx_ecall(eid, 30, &ocall_table_sgx_tsqlite, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t sqlite3_limit(sgx_enclave_id_t eid, int* retval, sqlite3* db, int id, int newVal)
{
	sgx_status_t status;
	ms_sqlite3_limit_t ms;
	ms.ms_db = db;
	ms.ms_id = id;
	ms.ms_newVal = newVal;
	status = sgx_ecall(eid, 31, &ocall_table_sgx_tsqlite, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t sqlite3_prepare(sgx_enclave_id_t eid, int* retval, sqlite3* db, const char* zSql, int nByte, sqlite3_stmt** ppStmt, char** pzTail)
{
	sgx_status_t status;
	ms_sqlite3_prepare_t ms;
	ms.ms_db = db;
	ms.ms_zSql = (char*)zSql;
	ms.ms_nByte = nByte;
	ms.ms_ppStmt = ppStmt;
	ms.ms_pzTail = pzTail;
	status = sgx_ecall(eid, 32, &ocall_table_sgx_tsqlite, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t sqlite3_sql(sgx_enclave_id_t eid, char** retval, sqlite3_stmt* pStmt)
{
	sgx_status_t status;
	ms_sqlite3_sql_t ms;
	ms.ms_pStmt = pStmt;
	status = sgx_ecall(eid, 33, &ocall_table_sgx_tsqlite, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t sqlite3_stmt_readonly(sgx_enclave_id_t eid, int* retval, sqlite3_stmt* pStmt)
{
	sgx_status_t status;
	ms_sqlite3_stmt_readonly_t ms;
	ms.ms_pStmt = pStmt;
	status = sgx_ecall(eid, 34, &ocall_table_sgx_tsqlite, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t sqlite3_stmt_busy(sgx_enclave_id_t eid, int* retval, sqlite3_stmt* pStmt)
{
	sgx_status_t status;
	ms_sqlite3_stmt_busy_t ms;
	ms.ms_pStmt = pStmt;
	status = sgx_ecall(eid, 35, &ocall_table_sgx_tsqlite, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t sqlite3_bind_double(sgx_enclave_id_t eid, int* retval, sqlite3_stmt* pStmt, int i, double rValue)
{
	sgx_status_t status;
	ms_sqlite3_bind_double_t ms;
	ms.ms_pStmt = pStmt;
	ms.ms_i = i;
	ms.ms_rValue = rValue;
	status = sgx_ecall(eid, 36, &ocall_table_sgx_tsqlite, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t sqlite3_bind_int(sgx_enclave_id_t eid, int* retval, sqlite3_stmt* p, int i, int iValue)
{
	sgx_status_t status;
	ms_sqlite3_bind_int_t ms;
	ms.ms_p = p;
	ms.ms_i = i;
	ms.ms_iValue = iValue;
	status = sgx_ecall(eid, 37, &ocall_table_sgx_tsqlite, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t sqlite3_bind_int64(sgx_enclave_id_t eid, int* retval, sqlite3_stmt* pStmt, int i, sqlite_int64 iValue)
{
	sgx_status_t status;
	ms_sqlite3_bind_int64_t ms;
	ms.ms_pStmt = pStmt;
	ms.ms_i = i;
	ms.ms_iValue = iValue;
	status = sgx_ecall(eid, 38, &ocall_table_sgx_tsqlite, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t sqlite3_bind_null(sgx_enclave_id_t eid, int* retval, sqlite3_stmt* pStmt, int i)
{
	sgx_status_t status;
	ms_sqlite3_bind_null_t ms;
	ms.ms_pStmt = pStmt;
	ms.ms_i = i;
	status = sgx_ecall(eid, 39, &ocall_table_sgx_tsqlite, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t sqlite3_bind_value(sgx_enclave_id_t eid, int* retval, sqlite3_stmt* pStmt, int i, const sqlite3_value* pValue)
{
	sgx_status_t status;
	ms_sqlite3_bind_value_t ms;
	ms.ms_pStmt = pStmt;
	ms.ms_i = i;
	ms.ms_pValue = (sqlite3_value*)pValue;
	status = sgx_ecall(eid, 40, &ocall_table_sgx_tsqlite, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t sqlite3_bind_zeroblob(sgx_enclave_id_t eid, int* retval, sqlite3_stmt* pStmt, int i, int n)
{
	sgx_status_t status;
	ms_sqlite3_bind_zeroblob_t ms;
	ms.ms_pStmt = pStmt;
	ms.ms_i = i;
	ms.ms_n = n;
	status = sgx_ecall(eid, 41, &ocall_table_sgx_tsqlite, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t sqlite3_bind_zeroblob64(sgx_enclave_id_t eid, int* retval, sqlite3_stmt* pStmt, int i, sqlite3_uint64 n)
{
	sgx_status_t status;
	ms_sqlite3_bind_zeroblob64_t ms;
	ms.ms_pStmt = pStmt;
	ms.ms_i = i;
	ms.ms_n = n;
	status = sgx_ecall(eid, 42, &ocall_table_sgx_tsqlite, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t sqlite3_bind_parameter_count(sgx_enclave_id_t eid, int* retval, sqlite3_stmt* pStmt)
{
	sgx_status_t status;
	ms_sqlite3_bind_parameter_count_t ms;
	ms.ms_pStmt = pStmt;
	status = sgx_ecall(eid, 43, &ocall_table_sgx_tsqlite, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t sqlite3_bind_parameter_name(sgx_enclave_id_t eid, char** retval, sqlite3_stmt* pStmt, int i)
{
	sgx_status_t status;
	ms_sqlite3_bind_parameter_name_t ms;
	ms.ms_pStmt = pStmt;
	ms.ms_i = i;
	status = sgx_ecall(eid, 44, &ocall_table_sgx_tsqlite, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t sqlite3_bind_parameter_index(sgx_enclave_id_t eid, int* retval, sqlite3_stmt* pStmt, const char* zName)
{
	sgx_status_t status;
	ms_sqlite3_bind_parameter_index_t ms;
	ms.ms_pStmt = pStmt;
	ms.ms_zName = (char*)zName;
	status = sgx_ecall(eid, 45, &ocall_table_sgx_tsqlite, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t sqlite3_clear_bindings(sgx_enclave_id_t eid, int* retval, sqlite3_stmt* pStmt)
{
	sgx_status_t status;
	ms_sqlite3_clear_bindings_t ms;
	ms.ms_pStmt = pStmt;
	status = sgx_ecall(eid, 46, &ocall_table_sgx_tsqlite, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t sqlite3_column_count(sgx_enclave_id_t eid, int* retval, sqlite3_stmt* pStmt)
{
	sgx_status_t status;
	ms_sqlite3_column_count_t ms;
	ms.ms_pStmt = pStmt;
	status = sgx_ecall(eid, 47, &ocall_table_sgx_tsqlite, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t sqlite3_column_name(sgx_enclave_id_t eid, char** retval, sqlite3_stmt* pStmt, int N)
{
	sgx_status_t status;
	ms_sqlite3_column_name_t ms;
	ms.ms_pStmt = pStmt;
	ms.ms_N = N;
	status = sgx_ecall(eid, 48, &ocall_table_sgx_tsqlite, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t sqlite3_column_name16(sgx_enclave_id_t eid, void** retval, sqlite3_stmt* pStmt, int N)
{
	sgx_status_t status;
	ms_sqlite3_column_name16_t ms;
	ms.ms_pStmt = pStmt;
	ms.ms_N = N;
	status = sgx_ecall(eid, 49, &ocall_table_sgx_tsqlite, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t sqlite3_column_database_name(sgx_enclave_id_t eid, char** retval, sqlite3_stmt* pStmt, int N)
{
	sgx_status_t status;
	ms_sqlite3_column_database_name_t ms;
	ms.ms_pStmt = pStmt;
	ms.ms_N = N;
	status = sgx_ecall(eid, 50, &ocall_table_sgx_tsqlite, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t sqlite3_column_database_name16(sgx_enclave_id_t eid, void** retval, sqlite3_stmt* pStmt, int N)
{
	sgx_status_t status;
	ms_sqlite3_column_database_name16_t ms;
	ms.ms_pStmt = pStmt;
	ms.ms_N = N;
	status = sgx_ecall(eid, 51, &ocall_table_sgx_tsqlite, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t sqlite3_column_table_name(sgx_enclave_id_t eid, char** retval, sqlite3_stmt* pStmt, int N)
{
	sgx_status_t status;
	ms_sqlite3_column_table_name_t ms;
	ms.ms_pStmt = pStmt;
	ms.ms_N = N;
	status = sgx_ecall(eid, 52, &ocall_table_sgx_tsqlite, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t sqlite3_column_table_name16(sgx_enclave_id_t eid, void** retval, sqlite3_stmt* pStmt, int N)
{
	sgx_status_t status;
	ms_sqlite3_column_table_name16_t ms;
	ms.ms_pStmt = pStmt;
	ms.ms_N = N;
	status = sgx_ecall(eid, 53, &ocall_table_sgx_tsqlite, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t sqlite3_column_origin_name(sgx_enclave_id_t eid, char** retval, sqlite3_stmt* pStmt, int N)
{
	sgx_status_t status;
	ms_sqlite3_column_origin_name_t ms;
	ms.ms_pStmt = pStmt;
	ms.ms_N = N;
	status = sgx_ecall(eid, 54, &ocall_table_sgx_tsqlite, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t sqlite3_column_origin_name16(sgx_enclave_id_t eid, void** retval, sqlite3_stmt* pStmt, int N)
{
	sgx_status_t status;
	ms_sqlite3_column_origin_name16_t ms;
	ms.ms_pStmt = pStmt;
	ms.ms_N = N;
	status = sgx_ecall(eid, 55, &ocall_table_sgx_tsqlite, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t sqlite3_aggregate_context(sgx_enclave_id_t eid, void** retval, sqlite3_context* p, int nBytes)
{
	sgx_status_t status;
	ms_sqlite3_aggregate_context_t ms;
	ms.ms_p = p;
	ms.ms_nBytes = nBytes;
	status = sgx_ecall(eid, 56, &ocall_table_sgx_tsqlite, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t sqlite3_step(sgx_enclave_id_t eid, int* retval, sqlite3_stmt* pStmt)
{
	sgx_status_t status;
	ms_sqlite3_step_t ms;
	ms.ms_pStmt = pStmt;
	status = sgx_ecall(eid, 57, &ocall_table_sgx_tsqlite, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t sqlite3_column_blob(sgx_enclave_id_t eid, void** retval, sqlite3_stmt* pStmt, int iCol)
{
	sgx_status_t status;
	ms_sqlite3_column_blob_t ms;
	ms.ms_pStmt = pStmt;
	ms.ms_iCol = iCol;
	status = sgx_ecall(eid, 58, &ocall_table_sgx_tsqlite, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t sqlite3_column_bytes(sgx_enclave_id_t eid, int* retval, sqlite3_stmt* pStmt, int iCol)
{
	sgx_status_t status;
	ms_sqlite3_column_bytes_t ms;
	ms.ms_pStmt = pStmt;
	ms.ms_iCol = iCol;
	status = sgx_ecall(eid, 59, &ocall_table_sgx_tsqlite, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t sqlite3_column_bytes16(sgx_enclave_id_t eid, int* retval, sqlite3_stmt* pStmt, int iCol)
{
	sgx_status_t status;
	ms_sqlite3_column_bytes16_t ms;
	ms.ms_pStmt = pStmt;
	ms.ms_iCol = iCol;
	status = sgx_ecall(eid, 60, &ocall_table_sgx_tsqlite, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t sqlite3_column_double(sgx_enclave_id_t eid, double* retval, sqlite3_stmt* pStmt, int iCol)
{
	sgx_status_t status;
	ms_sqlite3_column_double_t ms;
	ms.ms_pStmt = pStmt;
	ms.ms_iCol = iCol;
	status = sgx_ecall(eid, 61, &ocall_table_sgx_tsqlite, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t sqlite3_column_int(sgx_enclave_id_t eid, int* retval, sqlite3_stmt* pStmt, int iCol)
{
	sgx_status_t status;
	ms_sqlite3_column_int_t ms;
	ms.ms_pStmt = pStmt;
	ms.ms_iCol = iCol;
	status = sgx_ecall(eid, 62, &ocall_table_sgx_tsqlite, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t sqlite3_column_int64(sgx_enclave_id_t eid, sqlite3_int64* retval, sqlite3_stmt* pStmt, int iCol)
{
	sgx_status_t status;
	ms_sqlite3_column_int64_t ms;
	ms.ms_pStmt = pStmt;
	ms.ms_iCol = iCol;
	status = sgx_ecall(eid, 63, &ocall_table_sgx_tsqlite, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t sqlite3_column_text(sgx_enclave_id_t eid, unsigned char** retval, sqlite3_stmt* pStmt, int iCol)
{
	sgx_status_t status;
	ms_sqlite3_column_text_t ms;
	ms.ms_pStmt = pStmt;
	ms.ms_iCol = iCol;
	status = sgx_ecall(eid, 64, &ocall_table_sgx_tsqlite, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t sqlite3_column_text16(sgx_enclave_id_t eid, void** retval, sqlite3_stmt* pStmt, int iCol)
{
	sgx_status_t status;
	ms_sqlite3_column_text16_t ms;
	ms.ms_pStmt = pStmt;
	ms.ms_iCol = iCol;
	status = sgx_ecall(eid, 65, &ocall_table_sgx_tsqlite, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t sqlite3_column_type(sgx_enclave_id_t eid, int* retval, sqlite3_stmt* pStmt, int iCol)
{
	sgx_status_t status;
	ms_sqlite3_column_type_t ms;
	ms.ms_pStmt = pStmt;
	ms.ms_iCol = iCol;
	status = sgx_ecall(eid, 66, &ocall_table_sgx_tsqlite, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t sqlite3_column_value(sgx_enclave_id_t eid, sqlite3_value** retval, sqlite3_stmt* pStmt, int iCol)
{
	sgx_status_t status;
	ms_sqlite3_column_value_t ms;
	ms.ms_pStmt = pStmt;
	ms.ms_iCol = iCol;
	status = sgx_ecall(eid, 67, &ocall_table_sgx_tsqlite, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t sqlite3_finalize(sgx_enclave_id_t eid, int* retval, sqlite3_stmt* pStmt)
{
	sgx_status_t status;
	ms_sqlite3_finalize_t ms;
	ms.ms_pStmt = pStmt;
	status = sgx_ecall(eid, 68, &ocall_table_sgx_tsqlite, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

