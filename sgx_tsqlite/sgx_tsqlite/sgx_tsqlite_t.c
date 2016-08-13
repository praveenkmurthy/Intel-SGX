#include "sgx_tsqlite_t.h"

#include "sgx_trts.h" /* for sgx_ocalloc, sgx_is_outside_enclave */

#include <string.h> /* for memcpy etc */
#include <stdlib.h> /* for malloc/free etc */

#define CHECK_REF_POINTER(ptr, siz) do {	\
	if (!(ptr) || ! sgx_is_outside_enclave((ptr), (siz)))	\
		return SGX_ERROR_INVALID_PARAMETER;\
} while (0)

#define CHECK_UNIQUE_POINTER(ptr, siz) do {	\
	if ((ptr) && ! sgx_is_outside_enclave((ptr), (siz)))	\
		return SGX_ERROR_INVALID_PARAMETER;\
} while (0)

/* sgx_ocfree() just restores the original outside stack pointer. */
#define OCALLOC(val, type, len) do {	\
	void* __tmp = sgx_ocalloc(len);	\
	if (__tmp == NULL) {	\
		sgx_ocfree();	\
		return SGX_ERROR_UNEXPECTED;\
	}			\
	(val) = (type)__tmp;	\
} while (0)


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

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4127)
#pragma warning(disable: 4200)
#endif

static sgx_status_t SGX_CDECL sgx_sqlite3_prepare_v2(void* pms)
{
	ms_sqlite3_prepare_v2_t* ms = SGX_CAST(ms_sqlite3_prepare_v2_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	sqlite3* _tmp_db = ms->ms_db;
	char* _tmp_zSql = ms->ms_zSql;
	size_t _len_zSql = _tmp_zSql ? strlen(_tmp_zSql) + 1 : 0;
	char* _in_zSql = NULL;
	sqlite3** _tmp_ppStmt = ms->ms_ppStmt;
	size_t _len_ppStmt = 1 * sizeof(*_tmp_ppStmt);
	sqlite3** _in_ppStmt = NULL;
	char** _tmp_pzTail = ms->ms_pzTail;

	if (1 > (SIZE_MAX / sizeof(*_tmp_ppStmt))) {
		status = SGX_ERROR_INVALID_PARAMETER;
		goto err;
	}

	CHECK_REF_POINTER(pms, sizeof(ms_sqlite3_prepare_v2_t));
	CHECK_UNIQUE_POINTER(_tmp_zSql, _len_zSql);
	CHECK_UNIQUE_POINTER(_tmp_ppStmt, _len_ppStmt);

	if (_tmp_zSql != NULL) {
		_in_zSql = (char*)malloc(_len_zSql);
		if (_in_zSql == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		memcpy((void*)_in_zSql, _tmp_zSql, _len_zSql);
		_in_zSql[_len_zSql - 1] = '\0';
	}
	if (_tmp_ppStmt != NULL) {
		_in_ppStmt = (sqlite3**)malloc(_len_ppStmt);
		if (_in_ppStmt == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		memcpy(_in_ppStmt, _tmp_ppStmt, _len_ppStmt);
	}
	ms->ms_retval = sqlite3_prepare_v2(_tmp_db, (const char*)_in_zSql, ms->ms_nByte, _in_ppStmt, _tmp_pzTail);
err:
	if (_in_zSql) free((void*)_in_zSql);
	if (_in_ppStmt) free(_in_ppStmt);

	return status;
}

static sgx_status_t SGX_CDECL sgx_sqlite3_open(void* pms)
{
	ms_sqlite3_open_t* ms = SGX_CAST(ms_sqlite3_open_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	char* _tmp_filename = ms->ms_filename;
	size_t _len_filename = _tmp_filename ? strlen(_tmp_filename) + 1 : 0;
	char* _in_filename = NULL;
	sqlite3** _tmp_ppDb = ms->ms_ppDb;
	size_t _len_ppDb = 1 * sizeof(*_tmp_ppDb);
	sqlite3** _in_ppDb = NULL;

	if (1 > (SIZE_MAX / sizeof(*_tmp_ppDb))) {
		status = SGX_ERROR_INVALID_PARAMETER;
		goto err;
	}

	CHECK_REF_POINTER(pms, sizeof(ms_sqlite3_open_t));
	CHECK_UNIQUE_POINTER(_tmp_filename, _len_filename);
	CHECK_UNIQUE_POINTER(_tmp_ppDb, _len_ppDb);

	if (_tmp_filename != NULL) {
		_in_filename = (char*)malloc(_len_filename);
		if (_in_filename == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		memcpy((void*)_in_filename, _tmp_filename, _len_filename);
		_in_filename[_len_filename - 1] = '\0';
	}
	if (_tmp_ppDb != NULL) {
		if ((_in_ppDb = (sqlite3**)malloc(_len_ppDb)) == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		memset((void*)_in_ppDb, 0, _len_ppDb);
	}
	ms->ms_retval = sqlite3_open((const char*)_in_filename, _in_ppDb);
err:
	if (_in_filename) free((void*)_in_filename);
	if (_in_ppDb) {
		memcpy(_tmp_ppDb, _in_ppDb, _len_ppDb);
		free(_in_ppDb);
	}

	return status;
}

static sgx_status_t SGX_CDECL sgx_sqlite3_open_v2(void* pms)
{
	ms_sqlite3_open_v2_t* ms = SGX_CAST(ms_sqlite3_open_v2_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	char* _tmp_filename = ms->ms_filename;
	size_t _len_filename = _tmp_filename ? strlen(_tmp_filename) + 1 : 0;
	char* _in_filename = NULL;
	sqlite3** _tmp_ppDb = ms->ms_ppDb;
	size_t _len_ppDb = 1 * sizeof(*_tmp_ppDb);
	sqlite3** _in_ppDb = NULL;
	char* _tmp_zVfs = ms->ms_zVfs;
	size_t _len_zVfs = _tmp_zVfs ? strlen(_tmp_zVfs) + 1 : 0;
	char* _in_zVfs = NULL;

	if (1 > (SIZE_MAX / sizeof(*_tmp_ppDb))) {
		status = SGX_ERROR_INVALID_PARAMETER;
		goto err;
	}

	CHECK_REF_POINTER(pms, sizeof(ms_sqlite3_open_v2_t));
	CHECK_UNIQUE_POINTER(_tmp_filename, _len_filename);
	CHECK_UNIQUE_POINTER(_tmp_ppDb, _len_ppDb);
	CHECK_UNIQUE_POINTER(_tmp_zVfs, _len_zVfs);

	if (_tmp_filename != NULL) {
		_in_filename = (char*)malloc(_len_filename);
		if (_in_filename == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		memcpy((void*)_in_filename, _tmp_filename, _len_filename);
		_in_filename[_len_filename - 1] = '\0';
	}
	if (_tmp_ppDb != NULL) {
		if ((_in_ppDb = (sqlite3**)malloc(_len_ppDb)) == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		memset((void*)_in_ppDb, 0, _len_ppDb);
	}
	if (_tmp_zVfs != NULL) {
		_in_zVfs = (char*)malloc(_len_zVfs);
		if (_in_zVfs == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		memcpy((void*)_in_zVfs, _tmp_zVfs, _len_zVfs);
		_in_zVfs[_len_zVfs - 1] = '\0';
	}
	ms->ms_retval = sqlite3_open_v2((const char*)_in_filename, _in_ppDb, ms->ms_flags, (const char*)_in_zVfs);
err:
	if (_in_filename) free((void*)_in_filename);
	if (_in_ppDb) {
		memcpy(_tmp_ppDb, _in_ppDb, _len_ppDb);
		free(_in_ppDb);
	}
	if (_in_zVfs) free((void*)_in_zVfs);

	return status;
}

static sgx_status_t SGX_CDECL sgx_vdbeIncrPopulateThread(void* pms)
{
	ms_vdbeIncrPopulateThread_t* ms = SGX_CAST(ms_vdbeIncrPopulateThread_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	void* _tmp_pCtx = ms->ms_pCtx;
	size_t _len_pCtx = ((_tmp_pCtx) ? getIncrMergerSize(_tmp_pCtx) : 0);
	void* _in_pCtx = NULL;

	CHECK_REF_POINTER(pms, sizeof(ms_vdbeIncrPopulateThread_t));
	CHECK_UNIQUE_POINTER(_tmp_pCtx, _len_pCtx);

	if (_tmp_pCtx != NULL) {
		_in_pCtx = (void*)malloc(_len_pCtx);
		if (_in_pCtx == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		memcpy(_in_pCtx, _tmp_pCtx, _len_pCtx);

		/* check whether the pointer is modified. */
		if (getIncrMergerSize(_in_pCtx) != _len_pCtx) {
			status = SGX_ERROR_INVALID_PARAMETER;
			goto err;
		}
	}
	ms->ms_retval = vdbeIncrPopulateThread(_in_pCtx);
err:
	if (_in_pCtx) free(_in_pCtx);

	return status;
}

static sgx_status_t SGX_CDECL sgx_vdbeSorterFlushThread(void* pms)
{
	ms_vdbeSorterFlushThread_t* ms = SGX_CAST(ms_vdbeSorterFlushThread_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	void* _tmp_pCtx = ms->ms_pCtx;
	size_t _len_pCtx = ((_tmp_pCtx) ? getSortSubtaskSize(_tmp_pCtx) : 0);
	void* _in_pCtx = NULL;

	CHECK_REF_POINTER(pms, sizeof(ms_vdbeSorterFlushThread_t));
	CHECK_UNIQUE_POINTER(_tmp_pCtx, _len_pCtx);

	if (_tmp_pCtx != NULL) {
		_in_pCtx = (void*)malloc(_len_pCtx);
		if (_in_pCtx == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		memcpy(_in_pCtx, _tmp_pCtx, _len_pCtx);

		/* check whether the pointer is modified. */
		if (getSortSubtaskSize(_in_pCtx) != _len_pCtx) {
			status = SGX_ERROR_INVALID_PARAMETER;
			goto err;
		}
	}
	ms->ms_retval = vdbeSorterFlushThread(_in_pCtx);
err:
	if (_in_pCtx) free(_in_pCtx);

	return status;
}

static sgx_status_t SGX_CDECL sgx_vdbePmaReaderBgIncrInit(void* pms)
{
	ms_vdbePmaReaderBgIncrInit_t* ms = SGX_CAST(ms_vdbePmaReaderBgIncrInit_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	void* _tmp_pCtx = ms->ms_pCtx;
	size_t _len_pCtx = ((_tmp_pCtx) ? getPmaReaderSize(_tmp_pCtx) : 0);
	void* _in_pCtx = NULL;

	CHECK_REF_POINTER(pms, sizeof(ms_vdbePmaReaderBgIncrInit_t));
	CHECK_UNIQUE_POINTER(_tmp_pCtx, _len_pCtx);

	if (_tmp_pCtx != NULL) {
		_in_pCtx = (void*)malloc(_len_pCtx);
		if (_in_pCtx == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		memcpy(_in_pCtx, _tmp_pCtx, _len_pCtx);

		/* check whether the pointer is modified. */
		if (getPmaReaderSize(_in_pCtx) != _len_pCtx) {
			status = SGX_ERROR_INVALID_PARAMETER;
			goto err;
		}
	}
	ms->ms_retval = vdbePmaReaderBgIncrInit(_in_pCtx);
err:
	if (_in_pCtx) free(_in_pCtx);

	return status;
}

static sgx_status_t SGX_CDECL sgx_sqlite3_libversion(void* pms)
{
	ms_sqlite3_libversion_t* ms = SGX_CAST(ms_sqlite3_libversion_t*, pms);
	sgx_status_t status = SGX_SUCCESS;

	CHECK_REF_POINTER(pms, sizeof(ms_sqlite3_libversion_t));

	ms->ms_retval = sqlite3_libversion();


	return status;
}

static sgx_status_t SGX_CDECL sgx_sqlite3_sourceid(void* pms)
{
	ms_sqlite3_sourceid_t* ms = SGX_CAST(ms_sqlite3_sourceid_t*, pms);
	sgx_status_t status = SGX_SUCCESS;

	CHECK_REF_POINTER(pms, sizeof(ms_sqlite3_sourceid_t));

	ms->ms_retval = sqlite3_sourceid();


	return status;
}

static sgx_status_t SGX_CDECL sgx_sqlite3_libversion_number(void* pms)
{
	ms_sqlite3_libversion_number_t* ms = SGX_CAST(ms_sqlite3_libversion_number_t*, pms);
	sgx_status_t status = SGX_SUCCESS;

	CHECK_REF_POINTER(pms, sizeof(ms_sqlite3_libversion_number_t));

	ms->ms_retval = sqlite3_libversion_number();


	return status;
}

static sgx_status_t SGX_CDECL sgx_sqlite3_threadsafe(void* pms)
{
	ms_sqlite3_threadsafe_t* ms = SGX_CAST(ms_sqlite3_threadsafe_t*, pms);
	sgx_status_t status = SGX_SUCCESS;

	CHECK_REF_POINTER(pms, sizeof(ms_sqlite3_threadsafe_t));

	ms->ms_retval = sqlite3_threadsafe();


	return status;
}

static sgx_status_t SGX_CDECL sgx_sqlite3_close(void* pms)
{
	ms_sqlite3_close_t* ms = SGX_CAST(ms_sqlite3_close_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	sqlite3* _tmp_db = ms->ms_db;
	size_t _len_db = sizeof(*_tmp_db);
	sqlite3* _in_db = NULL;

	CHECK_REF_POINTER(pms, sizeof(ms_sqlite3_close_t));
	CHECK_UNIQUE_POINTER(_tmp_db, _len_db);

	if (_tmp_db != NULL) {
		_in_db = (sqlite3*)malloc(_len_db);
		if (_in_db == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		memcpy(_in_db, _tmp_db, _len_db);
	}
	ms->ms_retval = sqlite3_close(_in_db);
err:
	if (_in_db) free(_in_db);

	return status;
}

static sgx_status_t SGX_CDECL sgx_sqlite3_close_v2(void* pms)
{
	ms_sqlite3_close_v2_t* ms = SGX_CAST(ms_sqlite3_close_v2_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	sqlite3* _tmp_db = ms->ms_db;
	size_t _len_db = sizeof(*_tmp_db);
	sqlite3* _in_db = NULL;

	CHECK_REF_POINTER(pms, sizeof(ms_sqlite3_close_v2_t));
	CHECK_UNIQUE_POINTER(_tmp_db, _len_db);

	if (_tmp_db != NULL) {
		_in_db = (sqlite3*)malloc(_len_db);
		if (_in_db == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		memcpy(_in_db, _tmp_db, _len_db);
	}
	ms->ms_retval = sqlite3_close_v2(_in_db);
err:
	if (_in_db) free(_in_db);

	return status;
}

static sgx_status_t SGX_CDECL sgx_sqlite3_initialize(void* pms)
{
	ms_sqlite3_initialize_t* ms = SGX_CAST(ms_sqlite3_initialize_t*, pms);
	sgx_status_t status = SGX_SUCCESS;

	CHECK_REF_POINTER(pms, sizeof(ms_sqlite3_initialize_t));

	ms->ms_retval = sqlite3_initialize();


	return status;
}

static sgx_status_t SGX_CDECL sgx_sqlite3_shutdown(void* pms)
{
	ms_sqlite3_shutdown_t* ms = SGX_CAST(ms_sqlite3_shutdown_t*, pms);
	sgx_status_t status = SGX_SUCCESS;

	CHECK_REF_POINTER(pms, sizeof(ms_sqlite3_shutdown_t));

	ms->ms_retval = sqlite3_shutdown();


	return status;
}

static sgx_status_t SGX_CDECL sgx_sqlite3_extended_result_codes(void* pms)
{
	ms_sqlite3_extended_result_codes_t* ms = SGX_CAST(ms_sqlite3_extended_result_codes_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	sqlite3* _tmp_db = ms->ms_db;
	size_t _len_db = sizeof(*_tmp_db);
	sqlite3* _in_db = NULL;

	CHECK_REF_POINTER(pms, sizeof(ms_sqlite3_extended_result_codes_t));
	CHECK_UNIQUE_POINTER(_tmp_db, _len_db);

	if (_tmp_db != NULL) {
		_in_db = (sqlite3*)malloc(_len_db);
		if (_in_db == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		memcpy(_in_db, _tmp_db, _len_db);
	}
	ms->ms_retval = sqlite3_extended_result_codes(_in_db, ms->ms_onoff);
err:
	if (_in_db) free(_in_db);

	return status;
}

static sgx_status_t SGX_CDECL sgx_sqlite3_last_insert_rowid(void* pms)
{
	ms_sqlite3_last_insert_rowid_t* ms = SGX_CAST(ms_sqlite3_last_insert_rowid_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	sqlite3* _tmp_db = ms->ms_db;
	size_t _len_db = sizeof(*_tmp_db);
	sqlite3* _in_db = NULL;

	CHECK_REF_POINTER(pms, sizeof(ms_sqlite3_last_insert_rowid_t));
	CHECK_UNIQUE_POINTER(_tmp_db, _len_db);

	if (_tmp_db != NULL) {
		_in_db = (sqlite3*)malloc(_len_db);
		if (_in_db == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		memcpy(_in_db, _tmp_db, _len_db);
	}
	ms->ms_retval = sqlite3_last_insert_rowid(_in_db);
err:
	if (_in_db) free(_in_db);

	return status;
}

static sgx_status_t SGX_CDECL sgx_sqlite3_changes(void* pms)
{
	ms_sqlite3_changes_t* ms = SGX_CAST(ms_sqlite3_changes_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	sqlite3* _tmp_db = ms->ms_db;
	size_t _len_db = sizeof(*_tmp_db);
	sqlite3* _in_db = NULL;

	CHECK_REF_POINTER(pms, sizeof(ms_sqlite3_changes_t));
	CHECK_UNIQUE_POINTER(_tmp_db, _len_db);

	if (_tmp_db != NULL) {
		_in_db = (sqlite3*)malloc(_len_db);
		if (_in_db == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		memcpy(_in_db, _tmp_db, _len_db);
	}
	ms->ms_retval = sqlite3_changes(_in_db);
err:
	if (_in_db) free(_in_db);

	return status;
}

static sgx_status_t SGX_CDECL sgx_sqlite3_total_changes(void* pms)
{
	ms_sqlite3_total_changes_t* ms = SGX_CAST(ms_sqlite3_total_changes_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	sqlite3* _tmp_db = ms->ms_db;
	size_t _len_db = sizeof(*_tmp_db);
	sqlite3* _in_db = NULL;

	CHECK_REF_POINTER(pms, sizeof(ms_sqlite3_total_changes_t));
	CHECK_UNIQUE_POINTER(_tmp_db, _len_db);

	if (_tmp_db != NULL) {
		_in_db = (sqlite3*)malloc(_len_db);
		if (_in_db == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		memcpy(_in_db, _tmp_db, _len_db);
	}
	ms->ms_retval = sqlite3_total_changes(_in_db);
err:
	if (_in_db) free(_in_db);

	return status;
}

static sgx_status_t SGX_CDECL sgx_sqlite3_interrupt(void* pms)
{
	ms_sqlite3_interrupt_t* ms = SGX_CAST(ms_sqlite3_interrupt_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	sqlite3* _tmp_db = ms->ms_db;
	size_t _len_db = sizeof(*_tmp_db);
	sqlite3* _in_db = NULL;

	CHECK_REF_POINTER(pms, sizeof(ms_sqlite3_interrupt_t));
	CHECK_UNIQUE_POINTER(_tmp_db, _len_db);

	if (_tmp_db != NULL) {
		_in_db = (sqlite3*)malloc(_len_db);
		if (_in_db == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		memcpy(_in_db, _tmp_db, _len_db);
	}
	sqlite3_interrupt(_in_db);
err:
	if (_in_db) free(_in_db);

	return status;
}

static sgx_status_t SGX_CDECL sgx_sqlite3_complete(void* pms)
{
	ms_sqlite3_complete_t* ms = SGX_CAST(ms_sqlite3_complete_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	char* _tmp_sql = ms->ms_sql;
	size_t _len_sql = _tmp_sql ? strlen(_tmp_sql) + 1 : 0;
	char* _in_sql = NULL;

	CHECK_REF_POINTER(pms, sizeof(ms_sqlite3_complete_t));
	CHECK_UNIQUE_POINTER(_tmp_sql, _len_sql);

	if (_tmp_sql != NULL) {
		_in_sql = (char*)malloc(_len_sql);
		if (_in_sql == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		memcpy((void*)_in_sql, _tmp_sql, _len_sql);
		_in_sql[_len_sql - 1] = '\0';
	}
	ms->ms_retval = sqlite3_complete((const char*)_in_sql);
err:
	if (_in_sql) free((void*)_in_sql);

	return status;
}

static sgx_status_t SGX_CDECL sgx_sqlite3_complete16(void* pms)
{
	ms_sqlite3_complete16_t* ms = SGX_CAST(ms_sqlite3_complete16_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	char* _tmp_sql = ms->ms_sql;
	size_t _len_sql = _tmp_sql ? (wcslen(_tmp_sql) + 1) * sizeof(wchar_t) : 0;
	char* _in_sql = NULL;

	CHECK_REF_POINTER(pms, sizeof(ms_sqlite3_complete16_t));
	CHECK_UNIQUE_POINTER(_tmp_sql, _len_sql);

	if (_tmp_sql != NULL) {
		_in_sql = (char*)malloc(_len_sql);
		if (_in_sql == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		memcpy((void*)_in_sql, _tmp_sql, _len_sql);
		_in_sql[(_len_sql - sizeof(wchar_t))/sizeof(wchar_t)] = (wchar_t)0;
	}
	ms->ms_retval = sqlite3_complete16((const char*)_in_sql);
err:
	if (_in_sql) free((void*)_in_sql);

	return status;
}

static sgx_status_t SGX_CDECL sgx_sqlite3_busy_timeout(void* pms)
{
	ms_sqlite3_busy_timeout_t* ms = SGX_CAST(ms_sqlite3_busy_timeout_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	sqlite3* _tmp_db = ms->ms_db;
	size_t _len_db = sizeof(*_tmp_db);
	sqlite3* _in_db = NULL;

	CHECK_REF_POINTER(pms, sizeof(ms_sqlite3_busy_timeout_t));
	CHECK_UNIQUE_POINTER(_tmp_db, _len_db);

	if (_tmp_db != NULL) {
		_in_db = (sqlite3*)malloc(_len_db);
		if (_in_db == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		memcpy(_in_db, _tmp_db, _len_db);
	}
	ms->ms_retval = sqlite3_busy_timeout(_in_db, ms->ms_msec);
err:
	if (_in_db) free(_in_db);

	return status;
}

static sgx_status_t SGX_CDECL sgx_sqlite3_memory_used(void* pms)
{
	ms_sqlite3_memory_used_t* ms = SGX_CAST(ms_sqlite3_memory_used_t*, pms);
	sgx_status_t status = SGX_SUCCESS;

	CHECK_REF_POINTER(pms, sizeof(ms_sqlite3_memory_used_t));

	ms->ms_retval = sqlite3_memory_used();


	return status;
}

static sgx_status_t SGX_CDECL sgx_sqlite3_memory_highwater(void* pms)
{
	ms_sqlite3_memory_highwater_t* ms = SGX_CAST(ms_sqlite3_memory_highwater_t*, pms);
	sgx_status_t status = SGX_SUCCESS;

	CHECK_REF_POINTER(pms, sizeof(ms_sqlite3_memory_highwater_t));

	ms->ms_retval = sqlite3_memory_highwater(ms->ms_resetFlag);


	return status;
}

static sgx_status_t SGX_CDECL sgx_sqlite3_randomness(void* pms)
{
	ms_sqlite3_randomness_t* ms = SGX_CAST(ms_sqlite3_randomness_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	void* _tmp_P = ms->ms_P;
	int _tmp_N = ms->ms_N;
	size_t _len_P = _tmp_N;
	void* _in_P = NULL;

	CHECK_REF_POINTER(pms, sizeof(ms_sqlite3_randomness_t));
	CHECK_UNIQUE_POINTER(_tmp_P, _len_P);

	if (_tmp_P != NULL) {
		if ((_in_P = (void*)malloc(_len_P)) == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		memset((void*)_in_P, 0, _len_P);
	}
	sqlite3_randomness(_tmp_N, _in_P);
err:
	if (_in_P) {
		memcpy(_tmp_P, _in_P, _len_P);
		free(_in_P);
	}

	return status;
}

static sgx_status_t SGX_CDECL sgx_sqlite3_uri_int64(void* pms)
{
	ms_sqlite3_uri_int64_t* ms = SGX_CAST(ms_sqlite3_uri_int64_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	char* _tmp_zFilename = ms->ms_zFilename;
	size_t _len_zFilename = _tmp_zFilename ? strlen(_tmp_zFilename) + 1 : 0;
	char* _in_zFilename = NULL;
	char* _tmp_zParam = ms->ms_zParam;
	size_t _len_zParam = _tmp_zParam ? strlen(_tmp_zParam) + 1 : 0;
	char* _in_zParam = NULL;

	CHECK_REF_POINTER(pms, sizeof(ms_sqlite3_uri_int64_t));
	CHECK_UNIQUE_POINTER(_tmp_zFilename, _len_zFilename);
	CHECK_UNIQUE_POINTER(_tmp_zParam, _len_zParam);

	if (_tmp_zFilename != NULL) {
		_in_zFilename = (char*)malloc(_len_zFilename);
		if (_in_zFilename == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		memcpy((void*)_in_zFilename, _tmp_zFilename, _len_zFilename);
		_in_zFilename[_len_zFilename - 1] = '\0';
	}
	if (_tmp_zParam != NULL) {
		_in_zParam = (char*)malloc(_len_zParam);
		if (_in_zParam == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		memcpy((void*)_in_zParam, _tmp_zParam, _len_zParam);
		_in_zParam[_len_zParam - 1] = '\0';
	}
	ms->ms_retval = sqlite3_uri_int64((const char*)_in_zFilename, (const char*)_in_zParam, ms->ms_bDflt);
err:
	if (_in_zFilename) free((void*)_in_zFilename);
	if (_in_zParam) free((void*)_in_zParam);

	return status;
}

static sgx_status_t SGX_CDECL sgx_sqlite3_errcode(void* pms)
{
	ms_sqlite3_errcode_t* ms = SGX_CAST(ms_sqlite3_errcode_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	sqlite3* _tmp_db = ms->ms_db;
	size_t _len_db = sizeof(*_tmp_db);
	sqlite3* _in_db = NULL;

	CHECK_REF_POINTER(pms, sizeof(ms_sqlite3_errcode_t));
	CHECK_UNIQUE_POINTER(_tmp_db, _len_db);

	if (_tmp_db != NULL) {
		_in_db = (sqlite3*)malloc(_len_db);
		if (_in_db == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		memcpy(_in_db, _tmp_db, _len_db);
	}
	ms->ms_retval = sqlite3_errcode(_in_db);
err:
	if (_in_db) free(_in_db);

	return status;
}

static sgx_status_t SGX_CDECL sgx_sqlite3_extended_errcode(void* pms)
{
	ms_sqlite3_extended_errcode_t* ms = SGX_CAST(ms_sqlite3_extended_errcode_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	sqlite3* _tmp_db = ms->ms_db;
	size_t _len_db = sizeof(*_tmp_db);
	sqlite3* _in_db = NULL;

	CHECK_REF_POINTER(pms, sizeof(ms_sqlite3_extended_errcode_t));
	CHECK_UNIQUE_POINTER(_tmp_db, _len_db);

	if (_tmp_db != NULL) {
		_in_db = (sqlite3*)malloc(_len_db);
		if (_in_db == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		memcpy(_in_db, _tmp_db, _len_db);
	}
	ms->ms_retval = sqlite3_extended_errcode(_in_db);
err:
	if (_in_db) free(_in_db);

	return status;
}

static sgx_status_t SGX_CDECL sgx_sqlite3_errmsg(void* pms)
{
	ms_sqlite3_errmsg_t* ms = SGX_CAST(ms_sqlite3_errmsg_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	sqlite3* _tmp_db = ms->ms_db;
	size_t _len_db = sizeof(*_tmp_db);
	sqlite3* _in_db = NULL;

	CHECK_REF_POINTER(pms, sizeof(ms_sqlite3_errmsg_t));
	CHECK_UNIQUE_POINTER(_tmp_db, _len_db);

	if (_tmp_db != NULL) {
		_in_db = (sqlite3*)malloc(_len_db);
		if (_in_db == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		memcpy(_in_db, _tmp_db, _len_db);
	}
	ms->ms_retval = sqlite3_errmsg(_in_db);
err:
	if (_in_db) free(_in_db);

	return status;
}

static sgx_status_t SGX_CDECL sgx_sqlite3_errmsg16(void* pms)
{
	ms_sqlite3_errmsg16_t* ms = SGX_CAST(ms_sqlite3_errmsg16_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	sqlite3* _tmp_db = ms->ms_db;
	size_t _len_db = sizeof(*_tmp_db);
	sqlite3* _in_db = NULL;

	CHECK_REF_POINTER(pms, sizeof(ms_sqlite3_errmsg16_t));
	CHECK_UNIQUE_POINTER(_tmp_db, _len_db);

	if (_tmp_db != NULL) {
		_in_db = (sqlite3*)malloc(_len_db);
		if (_in_db == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		memcpy(_in_db, _tmp_db, _len_db);
	}
	ms->ms_retval = sqlite3_errmsg16(_in_db);
err:
	if (_in_db) free(_in_db);

	return status;
}

static sgx_status_t SGX_CDECL sgx_sqlite3_errstr(void* pms)
{
	ms_sqlite3_errstr_t* ms = SGX_CAST(ms_sqlite3_errstr_t*, pms);
	sgx_status_t status = SGX_SUCCESS;

	CHECK_REF_POINTER(pms, sizeof(ms_sqlite3_errstr_t));

	ms->ms_retval = sqlite3_errstr(ms->ms_rc);


	return status;
}

static sgx_status_t SGX_CDECL sgx_sqlite3_limit(void* pms)
{
	ms_sqlite3_limit_t* ms = SGX_CAST(ms_sqlite3_limit_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	sqlite3* _tmp_db = ms->ms_db;
	size_t _len_db = sizeof(*_tmp_db);
	sqlite3* _in_db = NULL;

	CHECK_REF_POINTER(pms, sizeof(ms_sqlite3_limit_t));
	CHECK_UNIQUE_POINTER(_tmp_db, _len_db);

	if (_tmp_db != NULL) {
		_in_db = (sqlite3*)malloc(_len_db);
		if (_in_db == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		memcpy(_in_db, _tmp_db, _len_db);
	}
	ms->ms_retval = sqlite3_limit(_in_db, ms->ms_id, ms->ms_newVal);
err:
	if (_in_db) free(_in_db);

	return status;
}

static sgx_status_t SGX_CDECL sgx_sqlite3_prepare(void* pms)
{
	ms_sqlite3_prepare_t* ms = SGX_CAST(ms_sqlite3_prepare_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	sqlite3* _tmp_db = ms->ms_db;
	size_t _len_db = sizeof(*_tmp_db);
	sqlite3* _in_db = NULL;
	char* _tmp_zSql = ms->ms_zSql;
	size_t _len_zSql = _tmp_zSql ? strlen(_tmp_zSql) + 1 : 0;
	char* _in_zSql = NULL;
	sqlite3_stmt** _tmp_ppStmt = ms->ms_ppStmt;
	char** _tmp_pzTail = ms->ms_pzTail;
	size_t _len_pzTail = 1 * sizeof(*_tmp_pzTail);
	char** _in_pzTail = NULL;

	if (1 > (SIZE_MAX / sizeof(*_tmp_pzTail))) {
		status = SGX_ERROR_INVALID_PARAMETER;
		goto err;
	}

	CHECK_REF_POINTER(pms, sizeof(ms_sqlite3_prepare_t));
	CHECK_UNIQUE_POINTER(_tmp_db, _len_db);
	CHECK_UNIQUE_POINTER(_tmp_zSql, _len_zSql);
	CHECK_UNIQUE_POINTER(_tmp_pzTail, _len_pzTail);

	if (_tmp_db != NULL) {
		_in_db = (sqlite3*)malloc(_len_db);
		if (_in_db == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		memcpy(_in_db, _tmp_db, _len_db);
	}
	if (_tmp_zSql != NULL) {
		_in_zSql = (char*)malloc(_len_zSql);
		if (_in_zSql == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		memcpy((void*)_in_zSql, _tmp_zSql, _len_zSql);
		_in_zSql[_len_zSql - 1] = '\0';
	}
	if (_tmp_pzTail != NULL) {
		if ((_in_pzTail = (char**)malloc(_len_pzTail)) == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		memset((void*)_in_pzTail, 0, _len_pzTail);
	}
	ms->ms_retval = sqlite3_prepare(_in_db, (const char*)_in_zSql, ms->ms_nByte, _tmp_ppStmt, _in_pzTail);
err:
	if (_in_db) free(_in_db);
	if (_in_zSql) free((void*)_in_zSql);
	if (_in_pzTail) {
		memcpy(_tmp_pzTail, _in_pzTail, _len_pzTail);
		free(_in_pzTail);
	}

	return status;
}

static sgx_status_t SGX_CDECL sgx_sqlite3_sql(void* pms)
{
	ms_sqlite3_sql_t* ms = SGX_CAST(ms_sqlite3_sql_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	sqlite3_stmt* _tmp_pStmt = ms->ms_pStmt;

	CHECK_REF_POINTER(pms, sizeof(ms_sqlite3_sql_t));

	ms->ms_retval = sqlite3_sql(_tmp_pStmt);


	return status;
}

static sgx_status_t SGX_CDECL sgx_sqlite3_stmt_readonly(void* pms)
{
	ms_sqlite3_stmt_readonly_t* ms = SGX_CAST(ms_sqlite3_stmt_readonly_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	sqlite3_stmt* _tmp_pStmt = ms->ms_pStmt;

	CHECK_REF_POINTER(pms, sizeof(ms_sqlite3_stmt_readonly_t));

	ms->ms_retval = sqlite3_stmt_readonly(_tmp_pStmt);


	return status;
}

static sgx_status_t SGX_CDECL sgx_sqlite3_stmt_busy(void* pms)
{
	ms_sqlite3_stmt_busy_t* ms = SGX_CAST(ms_sqlite3_stmt_busy_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	sqlite3_stmt* _tmp_pStmt = ms->ms_pStmt;

	CHECK_REF_POINTER(pms, sizeof(ms_sqlite3_stmt_busy_t));

	ms->ms_retval = sqlite3_stmt_busy(_tmp_pStmt);


	return status;
}

static sgx_status_t SGX_CDECL sgx_sqlite3_bind_double(void* pms)
{
	ms_sqlite3_bind_double_t* ms = SGX_CAST(ms_sqlite3_bind_double_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	sqlite3_stmt* _tmp_pStmt = ms->ms_pStmt;

	CHECK_REF_POINTER(pms, sizeof(ms_sqlite3_bind_double_t));

	ms->ms_retval = sqlite3_bind_double(_tmp_pStmt, ms->ms_i, ms->ms_rValue);


	return status;
}

static sgx_status_t SGX_CDECL sgx_sqlite3_bind_int(void* pms)
{
	ms_sqlite3_bind_int_t* ms = SGX_CAST(ms_sqlite3_bind_int_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	sqlite3_stmt* _tmp_p = ms->ms_p;

	CHECK_REF_POINTER(pms, sizeof(ms_sqlite3_bind_int_t));

	ms->ms_retval = sqlite3_bind_int(_tmp_p, ms->ms_i, ms->ms_iValue);


	return status;
}

static sgx_status_t SGX_CDECL sgx_sqlite3_bind_int64(void* pms)
{
	ms_sqlite3_bind_int64_t* ms = SGX_CAST(ms_sqlite3_bind_int64_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	sqlite3_stmt* _tmp_pStmt = ms->ms_pStmt;

	CHECK_REF_POINTER(pms, sizeof(ms_sqlite3_bind_int64_t));

	ms->ms_retval = sqlite3_bind_int64(_tmp_pStmt, ms->ms_i, ms->ms_iValue);


	return status;
}

static sgx_status_t SGX_CDECL sgx_sqlite3_bind_null(void* pms)
{
	ms_sqlite3_bind_null_t* ms = SGX_CAST(ms_sqlite3_bind_null_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	sqlite3_stmt* _tmp_pStmt = ms->ms_pStmt;

	CHECK_REF_POINTER(pms, sizeof(ms_sqlite3_bind_null_t));

	ms->ms_retval = sqlite3_bind_null(_tmp_pStmt, ms->ms_i);


	return status;
}

static sgx_status_t SGX_CDECL sgx_sqlite3_bind_value(void* pms)
{
	ms_sqlite3_bind_value_t* ms = SGX_CAST(ms_sqlite3_bind_value_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	sqlite3_stmt* _tmp_pStmt = ms->ms_pStmt;
	sqlite3_value* _tmp_pValue = ms->ms_pValue;
	size_t _len_pValue = sizeof(*_tmp_pValue);
	sqlite3_value* _in_pValue = NULL;

	CHECK_REF_POINTER(pms, sizeof(ms_sqlite3_bind_value_t));
	CHECK_UNIQUE_POINTER(_tmp_pValue, _len_pValue);

	if (_tmp_pValue != NULL) {
		_in_pValue = (sqlite3_value*)malloc(_len_pValue);
		if (_in_pValue == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		memcpy((void*)_in_pValue, _tmp_pValue, _len_pValue);
	}
	ms->ms_retval = sqlite3_bind_value(_tmp_pStmt, ms->ms_i, (const sqlite3_value*)_in_pValue);
err:
	if (_in_pValue) free((void*)_in_pValue);

	return status;
}

static sgx_status_t SGX_CDECL sgx_sqlite3_bind_zeroblob(void* pms)
{
	ms_sqlite3_bind_zeroblob_t* ms = SGX_CAST(ms_sqlite3_bind_zeroblob_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	sqlite3_stmt* _tmp_pStmt = ms->ms_pStmt;

	CHECK_REF_POINTER(pms, sizeof(ms_sqlite3_bind_zeroblob_t));

	ms->ms_retval = sqlite3_bind_zeroblob(_tmp_pStmt, ms->ms_i, ms->ms_n);


	return status;
}

static sgx_status_t SGX_CDECL sgx_sqlite3_bind_zeroblob64(void* pms)
{
	ms_sqlite3_bind_zeroblob64_t* ms = SGX_CAST(ms_sqlite3_bind_zeroblob64_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	sqlite3_stmt* _tmp_pStmt = ms->ms_pStmt;

	CHECK_REF_POINTER(pms, sizeof(ms_sqlite3_bind_zeroblob64_t));

	ms->ms_retval = sqlite3_bind_zeroblob64(_tmp_pStmt, ms->ms_i, ms->ms_n);


	return status;
}

static sgx_status_t SGX_CDECL sgx_sqlite3_bind_parameter_count(void* pms)
{
	ms_sqlite3_bind_parameter_count_t* ms = SGX_CAST(ms_sqlite3_bind_parameter_count_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	sqlite3_stmt* _tmp_pStmt = ms->ms_pStmt;

	CHECK_REF_POINTER(pms, sizeof(ms_sqlite3_bind_parameter_count_t));

	ms->ms_retval = sqlite3_bind_parameter_count(_tmp_pStmt);


	return status;
}

static sgx_status_t SGX_CDECL sgx_sqlite3_bind_parameter_name(void* pms)
{
	ms_sqlite3_bind_parameter_name_t* ms = SGX_CAST(ms_sqlite3_bind_parameter_name_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	sqlite3_stmt* _tmp_pStmt = ms->ms_pStmt;

	CHECK_REF_POINTER(pms, sizeof(ms_sqlite3_bind_parameter_name_t));

	ms->ms_retval = sqlite3_bind_parameter_name(_tmp_pStmt, ms->ms_i);


	return status;
}

static sgx_status_t SGX_CDECL sgx_sqlite3_bind_parameter_index(void* pms)
{
	ms_sqlite3_bind_parameter_index_t* ms = SGX_CAST(ms_sqlite3_bind_parameter_index_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	sqlite3_stmt* _tmp_pStmt = ms->ms_pStmt;
	char* _tmp_zName = ms->ms_zName;
	size_t _len_zName = _tmp_zName ? strlen(_tmp_zName) + 1 : 0;
	char* _in_zName = NULL;

	CHECK_REF_POINTER(pms, sizeof(ms_sqlite3_bind_parameter_index_t));
	CHECK_UNIQUE_POINTER(_tmp_zName, _len_zName);

	if (_tmp_zName != NULL) {
		_in_zName = (char*)malloc(_len_zName);
		if (_in_zName == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		memcpy((void*)_in_zName, _tmp_zName, _len_zName);
		_in_zName[_len_zName - 1] = '\0';
	}
	ms->ms_retval = sqlite3_bind_parameter_index(_tmp_pStmt, (const char*)_in_zName);
err:
	if (_in_zName) free((void*)_in_zName);

	return status;
}

static sgx_status_t SGX_CDECL sgx_sqlite3_clear_bindings(void* pms)
{
	ms_sqlite3_clear_bindings_t* ms = SGX_CAST(ms_sqlite3_clear_bindings_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	sqlite3_stmt* _tmp_pStmt = ms->ms_pStmt;

	CHECK_REF_POINTER(pms, sizeof(ms_sqlite3_clear_bindings_t));

	ms->ms_retval = sqlite3_clear_bindings(_tmp_pStmt);


	return status;
}

static sgx_status_t SGX_CDECL sgx_sqlite3_column_count(void* pms)
{
	ms_sqlite3_column_count_t* ms = SGX_CAST(ms_sqlite3_column_count_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	sqlite3_stmt* _tmp_pStmt = ms->ms_pStmt;

	CHECK_REF_POINTER(pms, sizeof(ms_sqlite3_column_count_t));

	ms->ms_retval = sqlite3_column_count(_tmp_pStmt);


	return status;
}

static sgx_status_t SGX_CDECL sgx_sqlite3_column_name(void* pms)
{
	ms_sqlite3_column_name_t* ms = SGX_CAST(ms_sqlite3_column_name_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	sqlite3_stmt* _tmp_pStmt = ms->ms_pStmt;

	CHECK_REF_POINTER(pms, sizeof(ms_sqlite3_column_name_t));

	ms->ms_retval = sqlite3_column_name(_tmp_pStmt, ms->ms_N);


	return status;
}

static sgx_status_t SGX_CDECL sgx_sqlite3_column_name16(void* pms)
{
	ms_sqlite3_column_name16_t* ms = SGX_CAST(ms_sqlite3_column_name16_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	sqlite3_stmt* _tmp_pStmt = ms->ms_pStmt;

	CHECK_REF_POINTER(pms, sizeof(ms_sqlite3_column_name16_t));

	ms->ms_retval = sqlite3_column_name16(_tmp_pStmt, ms->ms_N);


	return status;
}

static sgx_status_t SGX_CDECL sgx_sqlite3_column_database_name(void* pms)
{
	ms_sqlite3_column_database_name_t* ms = SGX_CAST(ms_sqlite3_column_database_name_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	sqlite3_stmt* _tmp_pStmt = ms->ms_pStmt;

	CHECK_REF_POINTER(pms, sizeof(ms_sqlite3_column_database_name_t));

	ms->ms_retval = sqlite3_column_database_name(_tmp_pStmt, ms->ms_N);


	return status;
}

static sgx_status_t SGX_CDECL sgx_sqlite3_column_database_name16(void* pms)
{
	ms_sqlite3_column_database_name16_t* ms = SGX_CAST(ms_sqlite3_column_database_name16_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	sqlite3_stmt* _tmp_pStmt = ms->ms_pStmt;

	CHECK_REF_POINTER(pms, sizeof(ms_sqlite3_column_database_name16_t));

	ms->ms_retval = sqlite3_column_database_name16(_tmp_pStmt, ms->ms_N);


	return status;
}

static sgx_status_t SGX_CDECL sgx_sqlite3_column_table_name(void* pms)
{
	ms_sqlite3_column_table_name_t* ms = SGX_CAST(ms_sqlite3_column_table_name_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	sqlite3_stmt* _tmp_pStmt = ms->ms_pStmt;

	CHECK_REF_POINTER(pms, sizeof(ms_sqlite3_column_table_name_t));

	ms->ms_retval = sqlite3_column_table_name(_tmp_pStmt, ms->ms_N);


	return status;
}

static sgx_status_t SGX_CDECL sgx_sqlite3_column_table_name16(void* pms)
{
	ms_sqlite3_column_table_name16_t* ms = SGX_CAST(ms_sqlite3_column_table_name16_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	sqlite3_stmt* _tmp_pStmt = ms->ms_pStmt;

	CHECK_REF_POINTER(pms, sizeof(ms_sqlite3_column_table_name16_t));

	ms->ms_retval = sqlite3_column_table_name16(_tmp_pStmt, ms->ms_N);


	return status;
}

static sgx_status_t SGX_CDECL sgx_sqlite3_column_origin_name(void* pms)
{
	ms_sqlite3_column_origin_name_t* ms = SGX_CAST(ms_sqlite3_column_origin_name_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	sqlite3_stmt* _tmp_pStmt = ms->ms_pStmt;

	CHECK_REF_POINTER(pms, sizeof(ms_sqlite3_column_origin_name_t));

	ms->ms_retval = sqlite3_column_origin_name(_tmp_pStmt, ms->ms_N);


	return status;
}

static sgx_status_t SGX_CDECL sgx_sqlite3_column_origin_name16(void* pms)
{
	ms_sqlite3_column_origin_name16_t* ms = SGX_CAST(ms_sqlite3_column_origin_name16_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	sqlite3_stmt* _tmp_pStmt = ms->ms_pStmt;

	CHECK_REF_POINTER(pms, sizeof(ms_sqlite3_column_origin_name16_t));

	ms->ms_retval = sqlite3_column_origin_name16(_tmp_pStmt, ms->ms_N);


	return status;
}

static sgx_status_t SGX_CDECL sgx_sqlite3_aggregate_context(void* pms)
{
	ms_sqlite3_aggregate_context_t* ms = SGX_CAST(ms_sqlite3_aggregate_context_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	sqlite3_context* _tmp_p = ms->ms_p;

	CHECK_REF_POINTER(pms, sizeof(ms_sqlite3_aggregate_context_t));

	ms->ms_retval = sqlite3_aggregate_context(_tmp_p, ms->ms_nBytes);


	return status;
}

static sgx_status_t SGX_CDECL sgx_sqlite3_step(void* pms)
{
	ms_sqlite3_step_t* ms = SGX_CAST(ms_sqlite3_step_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	sqlite3_stmt* _tmp_pStmt = ms->ms_pStmt;

	CHECK_REF_POINTER(pms, sizeof(ms_sqlite3_step_t));

	ms->ms_retval = sqlite3_step(_tmp_pStmt);


	return status;
}

static sgx_status_t SGX_CDECL sgx_sqlite3_column_blob(void* pms)
{
	ms_sqlite3_column_blob_t* ms = SGX_CAST(ms_sqlite3_column_blob_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	sqlite3_stmt* _tmp_pStmt = ms->ms_pStmt;

	CHECK_REF_POINTER(pms, sizeof(ms_sqlite3_column_blob_t));

	ms->ms_retval = sqlite3_column_blob(_tmp_pStmt, ms->ms_iCol);


	return status;
}

static sgx_status_t SGX_CDECL sgx_sqlite3_column_bytes(void* pms)
{
	ms_sqlite3_column_bytes_t* ms = SGX_CAST(ms_sqlite3_column_bytes_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	sqlite3_stmt* _tmp_pStmt = ms->ms_pStmt;

	CHECK_REF_POINTER(pms, sizeof(ms_sqlite3_column_bytes_t));

	ms->ms_retval = sqlite3_column_bytes(_tmp_pStmt, ms->ms_iCol);


	return status;
}

static sgx_status_t SGX_CDECL sgx_sqlite3_column_bytes16(void* pms)
{
	ms_sqlite3_column_bytes16_t* ms = SGX_CAST(ms_sqlite3_column_bytes16_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	sqlite3_stmt* _tmp_pStmt = ms->ms_pStmt;

	CHECK_REF_POINTER(pms, sizeof(ms_sqlite3_column_bytes16_t));

	ms->ms_retval = sqlite3_column_bytes16(_tmp_pStmt, ms->ms_iCol);


	return status;
}

static sgx_status_t SGX_CDECL sgx_sqlite3_column_double(void* pms)
{
	ms_sqlite3_column_double_t* ms = SGX_CAST(ms_sqlite3_column_double_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	sqlite3_stmt* _tmp_pStmt = ms->ms_pStmt;

	CHECK_REF_POINTER(pms, sizeof(ms_sqlite3_column_double_t));

	ms->ms_retval = sqlite3_column_double(_tmp_pStmt, ms->ms_iCol);


	return status;
}

static sgx_status_t SGX_CDECL sgx_sqlite3_column_int(void* pms)
{
	ms_sqlite3_column_int_t* ms = SGX_CAST(ms_sqlite3_column_int_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	sqlite3_stmt* _tmp_pStmt = ms->ms_pStmt;

	CHECK_REF_POINTER(pms, sizeof(ms_sqlite3_column_int_t));

	ms->ms_retval = sqlite3_column_int(_tmp_pStmt, ms->ms_iCol);


	return status;
}

static sgx_status_t SGX_CDECL sgx_sqlite3_column_int64(void* pms)
{
	ms_sqlite3_column_int64_t* ms = SGX_CAST(ms_sqlite3_column_int64_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	sqlite3_stmt* _tmp_pStmt = ms->ms_pStmt;

	CHECK_REF_POINTER(pms, sizeof(ms_sqlite3_column_int64_t));

	ms->ms_retval = sqlite3_column_int64(_tmp_pStmt, ms->ms_iCol);


	return status;
}

static sgx_status_t SGX_CDECL sgx_sqlite3_column_text(void* pms)
{
	ms_sqlite3_column_text_t* ms = SGX_CAST(ms_sqlite3_column_text_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	sqlite3_stmt* _tmp_pStmt = ms->ms_pStmt;

	CHECK_REF_POINTER(pms, sizeof(ms_sqlite3_column_text_t));

	ms->ms_retval = sqlite3_column_text(_tmp_pStmt, ms->ms_iCol);


	return status;
}

static sgx_status_t SGX_CDECL sgx_sqlite3_column_text16(void* pms)
{
	ms_sqlite3_column_text16_t* ms = SGX_CAST(ms_sqlite3_column_text16_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	sqlite3_stmt* _tmp_pStmt = ms->ms_pStmt;

	CHECK_REF_POINTER(pms, sizeof(ms_sqlite3_column_text16_t));

	ms->ms_retval = sqlite3_column_text16(_tmp_pStmt, ms->ms_iCol);


	return status;
}

static sgx_status_t SGX_CDECL sgx_sqlite3_column_type(void* pms)
{
	ms_sqlite3_column_type_t* ms = SGX_CAST(ms_sqlite3_column_type_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	sqlite3_stmt* _tmp_pStmt = ms->ms_pStmt;

	CHECK_REF_POINTER(pms, sizeof(ms_sqlite3_column_type_t));

	ms->ms_retval = sqlite3_column_type(_tmp_pStmt, ms->ms_iCol);


	return status;
}

static sgx_status_t SGX_CDECL sgx_sqlite3_column_value(void* pms)
{
	ms_sqlite3_column_value_t* ms = SGX_CAST(ms_sqlite3_column_value_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	sqlite3_stmt* _tmp_pStmt = ms->ms_pStmt;

	CHECK_REF_POINTER(pms, sizeof(ms_sqlite3_column_value_t));

	ms->ms_retval = sqlite3_column_value(_tmp_pStmt, ms->ms_iCol);


	return status;
}

static sgx_status_t SGX_CDECL sgx_sqlite3_finalize(void* pms)
{
	ms_sqlite3_finalize_t* ms = SGX_CAST(ms_sqlite3_finalize_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	sqlite3_stmt* _tmp_pStmt = ms->ms_pStmt;

	CHECK_REF_POINTER(pms, sizeof(ms_sqlite3_finalize_t));

	ms->ms_retval = sqlite3_finalize(_tmp_pStmt);


	return status;
}

SGX_EXTERNC const struct {
	size_t nr_ecall;
	struct {void* call_addr; uint8_t is_priv;} ecall_table[69];
} g_ecall_table = {
	69,
	{
		{(void*)(uintptr_t)sgx_sqlite3_prepare_v2, 0},
		{(void*)(uintptr_t)sgx_sqlite3_open, 0},
		{(void*)(uintptr_t)sgx_sqlite3_open_v2, 0},
		{(void*)(uintptr_t)sgx_vdbeIncrPopulateThread, 0},
		{(void*)(uintptr_t)sgx_vdbeSorterFlushThread, 0},
		{(void*)(uintptr_t)sgx_vdbePmaReaderBgIncrInit, 0},
		{(void*)(uintptr_t)sgx_sqlite3_libversion, 0},
		{(void*)(uintptr_t)sgx_sqlite3_sourceid, 0},
		{(void*)(uintptr_t)sgx_sqlite3_libversion_number, 0},
		{(void*)(uintptr_t)sgx_sqlite3_threadsafe, 0},
		{(void*)(uintptr_t)sgx_sqlite3_close, 0},
		{(void*)(uintptr_t)sgx_sqlite3_close_v2, 0},
		{(void*)(uintptr_t)sgx_sqlite3_initialize, 0},
		{(void*)(uintptr_t)sgx_sqlite3_shutdown, 0},
		{(void*)(uintptr_t)sgx_sqlite3_extended_result_codes, 0},
		{(void*)(uintptr_t)sgx_sqlite3_last_insert_rowid, 0},
		{(void*)(uintptr_t)sgx_sqlite3_changes, 0},
		{(void*)(uintptr_t)sgx_sqlite3_total_changes, 0},
		{(void*)(uintptr_t)sgx_sqlite3_interrupt, 0},
		{(void*)(uintptr_t)sgx_sqlite3_complete, 0},
		{(void*)(uintptr_t)sgx_sqlite3_complete16, 0},
		{(void*)(uintptr_t)sgx_sqlite3_busy_timeout, 0},
		{(void*)(uintptr_t)sgx_sqlite3_memory_used, 0},
		{(void*)(uintptr_t)sgx_sqlite3_memory_highwater, 0},
		{(void*)(uintptr_t)sgx_sqlite3_randomness, 0},
		{(void*)(uintptr_t)sgx_sqlite3_uri_int64, 0},
		{(void*)(uintptr_t)sgx_sqlite3_errcode, 0},
		{(void*)(uintptr_t)sgx_sqlite3_extended_errcode, 0},
		{(void*)(uintptr_t)sgx_sqlite3_errmsg, 0},
		{(void*)(uintptr_t)sgx_sqlite3_errmsg16, 0},
		{(void*)(uintptr_t)sgx_sqlite3_errstr, 0},
		{(void*)(uintptr_t)sgx_sqlite3_limit, 0},
		{(void*)(uintptr_t)sgx_sqlite3_prepare, 0},
		{(void*)(uintptr_t)sgx_sqlite3_sql, 0},
		{(void*)(uintptr_t)sgx_sqlite3_stmt_readonly, 0},
		{(void*)(uintptr_t)sgx_sqlite3_stmt_busy, 0},
		{(void*)(uintptr_t)sgx_sqlite3_bind_double, 0},
		{(void*)(uintptr_t)sgx_sqlite3_bind_int, 0},
		{(void*)(uintptr_t)sgx_sqlite3_bind_int64, 0},
		{(void*)(uintptr_t)sgx_sqlite3_bind_null, 0},
		{(void*)(uintptr_t)sgx_sqlite3_bind_value, 0},
		{(void*)(uintptr_t)sgx_sqlite3_bind_zeroblob, 0},
		{(void*)(uintptr_t)sgx_sqlite3_bind_zeroblob64, 0},
		{(void*)(uintptr_t)sgx_sqlite3_bind_parameter_count, 0},
		{(void*)(uintptr_t)sgx_sqlite3_bind_parameter_name, 0},
		{(void*)(uintptr_t)sgx_sqlite3_bind_parameter_index, 0},
		{(void*)(uintptr_t)sgx_sqlite3_clear_bindings, 0},
		{(void*)(uintptr_t)sgx_sqlite3_column_count, 0},
		{(void*)(uintptr_t)sgx_sqlite3_column_name, 0},
		{(void*)(uintptr_t)sgx_sqlite3_column_name16, 0},
		{(void*)(uintptr_t)sgx_sqlite3_column_database_name, 0},
		{(void*)(uintptr_t)sgx_sqlite3_column_database_name16, 0},
		{(void*)(uintptr_t)sgx_sqlite3_column_table_name, 0},
		{(void*)(uintptr_t)sgx_sqlite3_column_table_name16, 0},
		{(void*)(uintptr_t)sgx_sqlite3_column_origin_name, 0},
		{(void*)(uintptr_t)sgx_sqlite3_column_origin_name16, 0},
		{(void*)(uintptr_t)sgx_sqlite3_aggregate_context, 0},
		{(void*)(uintptr_t)sgx_sqlite3_step, 0},
		{(void*)(uintptr_t)sgx_sqlite3_column_blob, 0},
		{(void*)(uintptr_t)sgx_sqlite3_column_bytes, 0},
		{(void*)(uintptr_t)sgx_sqlite3_column_bytes16, 0},
		{(void*)(uintptr_t)sgx_sqlite3_column_double, 0},
		{(void*)(uintptr_t)sgx_sqlite3_column_int, 0},
		{(void*)(uintptr_t)sgx_sqlite3_column_int64, 0},
		{(void*)(uintptr_t)sgx_sqlite3_column_text, 0},
		{(void*)(uintptr_t)sgx_sqlite3_column_text16, 0},
		{(void*)(uintptr_t)sgx_sqlite3_column_type, 0},
		{(void*)(uintptr_t)sgx_sqlite3_column_value, 0},
		{(void*)(uintptr_t)sgx_sqlite3_finalize, 0},
	}
};

SGX_EXTERNC const struct {
	size_t nr_ocall;
	uint8_t entry_table[44][69];
} g_dyn_entry_table = {
	44,
	{
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	}
};


sgx_status_t SGX_CDECL sqlite3_printf(char* log)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_log = log ? strlen(log) + 1 : 0;

	ms_sqlite3_printf_t* ms;
	OCALLOC(ms, ms_sqlite3_printf_t*, sizeof(*ms));

	if (log != NULL && sgx_is_within_enclave(log, _len_log)) {
		OCALLOC(ms->ms_log, char*, _len_log);
		memcpy(ms->ms_log, log, _len_log);
	} else if (log == NULL) {
		ms->ms_log = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	status = sgx_ocall(0, ms);


	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL sqlite3OsInit(int* retval)
{
	sgx_status_t status = SGX_SUCCESS;

	ms_sqlite3OsInit_t* ms;
	OCALLOC(ms, ms_sqlite3OsInit_t*, sizeof(*ms));

	status = sgx_ocall(1, ms);

	if (retval) *retval = ms->ms_retval;

	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL sqlite3OsSleep(int* retval, sqlite3_vfs* pVfs, int nMicro)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_pVfs = sizeof(*pVfs);

	ms_sqlite3OsSleep_t* ms;
	OCALLOC(ms, ms_sqlite3OsSleep_t*, sizeof(*ms));

	if (pVfs != NULL && sgx_is_within_enclave(pVfs, _len_pVfs)) {
		OCALLOC(ms->ms_pVfs, sqlite3_vfs*, _len_pVfs);
		memcpy(ms->ms_pVfs, pVfs, _len_pVfs);
	} else if (pVfs == NULL) {
		ms->ms_pVfs = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	ms->ms_nMicro = nMicro;
	status = sgx_ocall(2, ms);

	if (retval) *retval = ms->ms_retval;

	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL sqlite3_os_end(int* retval)
{
	sgx_status_t status = SGX_SUCCESS;

	ms_sqlite3_os_end_t* ms;
	OCALLOC(ms, ms_sqlite3_os_end_t*, sizeof(*ms));

	status = sgx_ocall(3, ms);

	if (retval) *retval = ms->ms_retval;

	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL sqlite3_win32_sleep(unsigned long int milliseconds)
{
	sgx_status_t status = SGX_SUCCESS;

	ms_sqlite3_win32_sleep_t* ms;
	OCALLOC(ms, ms_sqlite3_win32_sleep_t*, sizeof(*ms));

	ms->ms_milliseconds = milliseconds;
	status = sgx_ocall(4, ms);


	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL ocall_vdbeSorterCreateThread(int* retval, SQLiteThread** pThread, void* pIn)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_pThread = 1 * ((pThread) ? getSQLiteThreadSize(pThread) : 0);
	size_t _len_pIn = ((pIn) ? getIncrMergerSize(pIn) : 0);

	ms_ocall_vdbeSorterCreateThread_t* ms;
	OCALLOC(ms, ms_ocall_vdbeSorterCreateThread_t*, sizeof(*ms));

	if (pThread != NULL && sgx_is_within_enclave(pThread, _len_pThread)) {
		OCALLOC(ms->ms_pThread, SQLiteThread**, _len_pThread);
		memcpy(ms->ms_pThread, pThread, _len_pThread);
	} else if (pThread == NULL) {
		ms->ms_pThread = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	if (pIn != NULL && sgx_is_within_enclave(pIn, _len_pIn)) {
		OCALLOC(ms->ms_pIn, void*, _len_pIn);
		memcpy(ms->ms_pIn, pIn, _len_pIn);
	} else if (pIn == NULL) {
		ms->ms_pIn = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	status = sgx_ocall(5, ms);

	if (retval) *retval = ms->ms_retval;

	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL ocall_vdbeSorterCreateThread_flushThr(int* retval, SQLiteThread** pThread, void* pIn)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_pThread = sizeof(*pThread);
	size_t _len_pIn = ((pIn) ? getSortSubtaskSize(pIn) : 0);

	ms_ocall_vdbeSorterCreateThread_flushThr_t* ms;
	OCALLOC(ms, ms_ocall_vdbeSorterCreateThread_flushThr_t*, sizeof(*ms));

	if (pThread != NULL && sgx_is_within_enclave(pThread, _len_pThread)) {
		OCALLOC(ms->ms_pThread, SQLiteThread**, _len_pThread);
		memcpy(ms->ms_pThread, pThread, _len_pThread);
	} else if (pThread == NULL) {
		ms->ms_pThread = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	if (pIn != NULL && sgx_is_within_enclave(pIn, _len_pIn)) {
		OCALLOC(ms->ms_pIn, void*, _len_pIn);
		memcpy(ms->ms_pIn, pIn, _len_pIn);
	} else if (pIn == NULL) {
		ms->ms_pIn = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	status = sgx_ocall(6, ms);

	if (retval) *retval = ms->ms_retval;

	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL ocall_vdbeSorterCreateThread_PmaReader(int* retval, SQLiteThread** pThread, void* pIn)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_pThread = sizeof(*pThread);
	size_t _len_pIn = ((pIn) ? getPmaReaderSize(pIn) : 0);

	ms_ocall_vdbeSorterCreateThread_PmaReader_t* ms;
	OCALLOC(ms, ms_ocall_vdbeSorterCreateThread_PmaReader_t*, sizeof(*ms));

	if (pThread != NULL && sgx_is_within_enclave(pThread, _len_pThread)) {
		OCALLOC(ms->ms_pThread, SQLiteThread**, _len_pThread);
		memcpy(ms->ms_pThread, pThread, _len_pThread);
	} else if (pThread == NULL) {
		ms->ms_pThread = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	if (pIn != NULL && sgx_is_within_enclave(pIn, _len_pIn)) {
		OCALLOC(ms->ms_pIn, void*, _len_pIn);
		memcpy(ms->ms_pIn, pIn, _len_pIn);
	} else if (pIn == NULL) {
		ms->ms_pIn = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	status = sgx_ocall(7, ms);

	if (retval) *retval = ms->ms_retval;

	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL sqlite3OsWrite(int* retval, sqlite3_file* id, const void* pBuf, int buf_size, long long offset)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_id = 72;
	size_t _len_pBuf = buf_size;

	ms_sqlite3OsWrite_t* ms;
	OCALLOC(ms, ms_sqlite3OsWrite_t*, sizeof(*ms));

	if (id != NULL && sgx_is_within_enclave(id, _len_id)) {
		OCALLOC(ms->ms_id, sqlite3_file*, _len_id);
		memcpy(ms->ms_id, id, _len_id);
	} else if (id == NULL) {
		ms->ms_id = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	if (pBuf != NULL && sgx_is_within_enclave(pBuf, _len_pBuf)) {
		OCALLOC(ms->ms_pBuf, void*, _len_pBuf);
		memcpy((void*)ms->ms_pBuf, pBuf, _len_pBuf);
	} else if (pBuf == NULL) {
		ms->ms_pBuf = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	ms->ms_buf_size = buf_size;
	ms->ms_offset = offset;
	status = sgx_ocall(8, ms);

	if (retval) *retval = ms->ms_retval;

	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL sqlite3OsRead(int* retval, sqlite3_file* id, void* pBuf, int buf_size, long long offset)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_id = 72;
	size_t _len_pBuf = buf_size;

	ms_sqlite3OsRead_t* ms;
	OCALLOC(ms, ms_sqlite3OsRead_t*, sizeof(*ms));

	if (id != NULL && sgx_is_within_enclave(id, _len_id)) {
		OCALLOC(ms->ms_id, sqlite3_file*, _len_id);
		memcpy(ms->ms_id, id, _len_id);
	} else if (id == NULL) {
		ms->ms_id = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	if (pBuf != NULL && sgx_is_within_enclave(pBuf, _len_pBuf)) {
		OCALLOC(ms->ms_pBuf, void*, _len_pBuf);
		memcpy(ms->ms_pBuf, pBuf, _len_pBuf);
	} else if (pBuf == NULL) {
		ms->ms_pBuf = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	ms->ms_buf_size = buf_size;
	ms->ms_offset = offset;
	status = sgx_ocall(9, ms);

	if (retval) *retval = ms->ms_retval;

	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL sqlite3OsTruncate(int* retval, sqlite3_file* id, long long size)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_id = 72;

	ms_sqlite3OsTruncate_t* ms;
	OCALLOC(ms, ms_sqlite3OsTruncate_t*, sizeof(*ms));

	if (id != NULL && sgx_is_within_enclave(id, _len_id)) {
		OCALLOC(ms->ms_id, sqlite3_file*, _len_id);
		memcpy(ms->ms_id, id, _len_id);
	} else if (id == NULL) {
		ms->ms_id = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	ms->ms_size = size;
	status = sgx_ocall(10, ms);

	if (retval) *retval = ms->ms_retval;

	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL sqlite3OsFileSize(int* retval, sqlite3_file* id, long long* pSize)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_id = 72;
	size_t _len_pSize = sizeof(*pSize);

	ms_sqlite3OsFileSize_t* ms;
	OCALLOC(ms, ms_sqlite3OsFileSize_t*, sizeof(*ms));

	if (id != NULL && sgx_is_within_enclave(id, _len_id)) {
		OCALLOC(ms->ms_id, sqlite3_file*, _len_id);
		memcpy(ms->ms_id, id, _len_id);
	} else if (id == NULL) {
		ms->ms_id = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	if (pSize != NULL && sgx_is_within_enclave(pSize, _len_pSize)) {
		OCALLOC(ms->ms_pSize, long long*, _len_pSize);
		memset(ms->ms_pSize, 0, _len_pSize);
	} else if (pSize == NULL) {
		ms->ms_pSize = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	status = sgx_ocall(11, ms);

	if (retval) *retval = ms->ms_retval;
	if (pSize) memcpy((void*)pSize, ms->ms_pSize, _len_pSize);

	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL sqlite3OsFileControl(int* retval, sqlite3_file* id, int op, void* pArg, int arg_size)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_id = 72;
	size_t _len_pArg = arg_size;

	ms_sqlite3OsFileControl_t* ms;
	OCALLOC(ms, ms_sqlite3OsFileControl_t*, sizeof(*ms));

	if (id != NULL && sgx_is_within_enclave(id, _len_id)) {
		OCALLOC(ms->ms_id, sqlite3_file*, _len_id);
		memcpy(ms->ms_id, id, _len_id);
	} else if (id == NULL) {
		ms->ms_id = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	ms->ms_op = op;
	if (pArg != NULL && sgx_is_within_enclave(pArg, _len_pArg)) {
		OCALLOC(ms->ms_pArg, void*, _len_pArg);
		memcpy(ms->ms_pArg, pArg, _len_pArg);
	} else if (pArg == NULL) {
		ms->ms_pArg = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	ms->ms_arg_size = arg_size;
	status = sgx_ocall(12, ms);

	if (retval) *retval = ms->ms_retval;

	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL sqlite3OsFullPathname(int* retval, sqlite3_vfs* pVfs, const char* zPath, int nPathOut, char* zPathOut, int buf_size)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_pVfs = sizeof(*pVfs);
	size_t _len_zPath = zPath ? strlen(zPath) + 1 : 0;
	size_t _len_zPathOut = buf_size;

	ms_sqlite3OsFullPathname_t* ms;
	OCALLOC(ms, ms_sqlite3OsFullPathname_t*, sizeof(*ms));

	if (pVfs != NULL && sgx_is_within_enclave(pVfs, _len_pVfs)) {
		OCALLOC(ms->ms_pVfs, sqlite3_vfs*, _len_pVfs);
		memcpy(ms->ms_pVfs, pVfs, _len_pVfs);
	} else if (pVfs == NULL) {
		ms->ms_pVfs = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	if (zPath != NULL && sgx_is_within_enclave(zPath, _len_zPath)) {
		OCALLOC(ms->ms_zPath, char*, _len_zPath);
		memcpy((void*)ms->ms_zPath, zPath, _len_zPath);
	} else if (zPath == NULL) {
		ms->ms_zPath = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	ms->ms_nPathOut = nPathOut;
	if (zPathOut != NULL && sgx_is_within_enclave(zPathOut, _len_zPathOut)) {
		OCALLOC(ms->ms_zPathOut, char*, _len_zPathOut);
		memset(ms->ms_zPathOut, 0, _len_zPathOut);
	} else if (zPathOut == NULL) {
		ms->ms_zPathOut = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	ms->ms_buf_size = buf_size;
	status = sgx_ocall(13, ms);

	if (retval) *retval = ms->ms_retval;
	if (zPathOut) memcpy((void*)zPathOut, ms->ms_zPathOut, _len_zPathOut);

	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL sqlite3_vfs_register(int* retval, sqlite3_vfs* pVfs, int makeDflt)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_pVfs = sizeof(*pVfs);

	ms_sqlite3_vfs_register_t* ms;
	OCALLOC(ms, ms_sqlite3_vfs_register_t*, sizeof(*ms));

	if (pVfs != NULL && sgx_is_within_enclave(pVfs, _len_pVfs)) {
		OCALLOC(ms->ms_pVfs, sqlite3_vfs*, _len_pVfs);
		memcpy(ms->ms_pVfs, pVfs, _len_pVfs);
	} else if (pVfs == NULL) {
		ms->ms_pVfs = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	ms->ms_makeDflt = makeDflt;
	status = sgx_ocall(14, ms);

	if (retval) *retval = ms->ms_retval;

	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL sqlite3_vfs_unregister(int* retval, sqlite3_vfs* pVfs)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_pVfs = sizeof(*pVfs);

	ms_sqlite3_vfs_unregister_t* ms;
	OCALLOC(ms, ms_sqlite3_vfs_unregister_t*, sizeof(*ms));

	if (pVfs != NULL && sgx_is_within_enclave(pVfs, _len_pVfs)) {
		OCALLOC(ms->ms_pVfs, sqlite3_vfs*, _len_pVfs);
		memcpy(ms->ms_pVfs, pVfs, _len_pVfs);
	} else if (pVfs == NULL) {
		ms->ms_pVfs = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	status = sgx_ocall(15, ms);

	if (retval) *retval = ms->ms_retval;

	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL sqlite3OsSync(int* retval, sqlite3_file* id, int flags)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_id = 72;

	ms_sqlite3OsSync_t* ms;
	OCALLOC(ms, ms_sqlite3OsSync_t*, sizeof(*ms));

	if (id != NULL && sgx_is_within_enclave(id, _len_id)) {
		OCALLOC(ms->ms_id, sqlite3_file*, _len_id);
		memcpy(ms->ms_id, id, _len_id);
	} else if (id == NULL) {
		ms->ms_id = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	ms->ms_flags = flags;
	status = sgx_ocall(16, ms);

	if (retval) *retval = ms->ms_retval;

	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL sqlite3OsLock(int* retval, sqlite3_file* id, int lockType)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_id = 72;

	ms_sqlite3OsLock_t* ms;
	OCALLOC(ms, ms_sqlite3OsLock_t*, sizeof(*ms));

	if (id != NULL && sgx_is_within_enclave(id, _len_id)) {
		OCALLOC(ms->ms_id, sqlite3_file*, _len_id);
		memcpy(ms->ms_id, id, _len_id);
	} else if (id == NULL) {
		ms->ms_id = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	ms->ms_lockType = lockType;
	status = sgx_ocall(17, ms);

	if (retval) *retval = ms->ms_retval;

	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL sqlite3OsUnlock(int* retval, sqlite3_file* id, int lockType)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_id = 72;

	ms_sqlite3OsUnlock_t* ms;
	OCALLOC(ms, ms_sqlite3OsUnlock_t*, sizeof(*ms));

	if (id != NULL && sgx_is_within_enclave(id, _len_id)) {
		OCALLOC(ms->ms_id, sqlite3_file*, _len_id);
		memcpy(ms->ms_id, id, _len_id);
	} else if (id == NULL) {
		ms->ms_id = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	ms->ms_lockType = lockType;
	status = sgx_ocall(18, ms);

	if (retval) *retval = ms->ms_retval;

	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL sqlite3OsCheckReservedLock(int* retval, sqlite3_file* id, int* pResOut)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_id = 72;
	size_t _len_pResOut = sizeof(*pResOut);

	ms_sqlite3OsCheckReservedLock_t* ms;
	OCALLOC(ms, ms_sqlite3OsCheckReservedLock_t*, sizeof(*ms));

	if (id != NULL && sgx_is_within_enclave(id, _len_id)) {
		OCALLOC(ms->ms_id, sqlite3_file*, _len_id);
		memcpy(ms->ms_id, id, _len_id);
	} else if (id == NULL) {
		ms->ms_id = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	if (pResOut != NULL && sgx_is_within_enclave(pResOut, _len_pResOut)) {
		OCALLOC(ms->ms_pResOut, int*, _len_pResOut);
		memcpy(ms->ms_pResOut, pResOut, _len_pResOut);
	} else if (pResOut == NULL) {
		ms->ms_pResOut = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	status = sgx_ocall(19, ms);

	if (retval) *retval = ms->ms_retval;

	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL sqlite3OsSectorSize(int* retval, sqlite3_file* id)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_id = 72;

	ms_sqlite3OsSectorSize_t* ms;
	OCALLOC(ms, ms_sqlite3OsSectorSize_t*, sizeof(*ms));

	if (id != NULL && sgx_is_within_enclave(id, _len_id)) {
		OCALLOC(ms->ms_id, sqlite3_file*, _len_id);
		memcpy(ms->ms_id, id, _len_id);
	} else if (id == NULL) {
		ms->ms_id = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	status = sgx_ocall(20, ms);

	if (retval) *retval = ms->ms_retval;

	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL sqlite3OsDeviceCharacteristics(int* retval, sqlite3_file* id)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_id = 72;

	ms_sqlite3OsDeviceCharacteristics_t* ms;
	OCALLOC(ms, ms_sqlite3OsDeviceCharacteristics_t*, sizeof(*ms));

	if (id != NULL && sgx_is_within_enclave(id, _len_id)) {
		OCALLOC(ms->ms_id, sqlite3_file*, _len_id);
		memcpy(ms->ms_id, id, _len_id);
	} else if (id == NULL) {
		ms->ms_id = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	status = sgx_ocall(21, ms);

	if (retval) *retval = ms->ms_retval;

	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL sqlite3OsFetch(int* retval, sqlite3_file* id, long long iOff, int iAmt, void** pp)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_id = 72;
	size_t _len_pp = 1 * iAmt;

	ms_sqlite3OsFetch_t* ms;
	OCALLOC(ms, ms_sqlite3OsFetch_t*, sizeof(*ms));

	if (id != NULL && sgx_is_within_enclave(id, _len_id)) {
		OCALLOC(ms->ms_id, sqlite3_file*, _len_id);
		memcpy(ms->ms_id, id, _len_id);
	} else if (id == NULL) {
		ms->ms_id = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	ms->ms_iOff = iOff;
	ms->ms_iAmt = iAmt;
	if (pp != NULL && sgx_is_within_enclave(pp, _len_pp)) {
		OCALLOC(ms->ms_pp, void**, _len_pp);
		memcpy(ms->ms_pp, pp, _len_pp);
	} else if (pp == NULL) {
		ms->ms_pp = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	status = sgx_ocall(22, ms);

	if (retval) *retval = ms->ms_retval;
	if (pp) memcpy((void*)pp, ms->ms_pp, _len_pp);

	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL sqlite3OsUnfetch(int* retval, sqlite3_file* id, long long iOff, void* p, int arg_size)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_id = 72;
	size_t _len_p = arg_size;

	ms_sqlite3OsUnfetch_t* ms;
	OCALLOC(ms, ms_sqlite3OsUnfetch_t*, sizeof(*ms));

	if (id != NULL && sgx_is_within_enclave(id, _len_id)) {
		OCALLOC(ms->ms_id, sqlite3_file*, _len_id);
		memcpy(ms->ms_id, id, _len_id);
	} else if (id == NULL) {
		ms->ms_id = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	ms->ms_iOff = iOff;
	if (p != NULL && sgx_is_within_enclave(p, _len_p)) {
		OCALLOC(ms->ms_p, void*, _len_p);
		memcpy(ms->ms_p, p, _len_p);
	} else if (p == NULL) {
		ms->ms_p = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	ms->ms_arg_size = arg_size;
	status = sgx_ocall(23, ms);

	if (retval) *retval = ms->ms_retval;

	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL sqlite3OsOpen(int* retval, sqlite3_vfs* pVfs, const char* zPath, sqlite3_file* pFile, int flags, int* pFlagsOut)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_pVfs = sizeof(*pVfs);
	size_t _len_zPath = zPath ? strlen(zPath) + 1 : 0;
	size_t _len_pFile = 72;
	size_t _len_pFlagsOut = sizeof(*pFlagsOut);

	ms_sqlite3OsOpen_t* ms;
	OCALLOC(ms, ms_sqlite3OsOpen_t*, sizeof(*ms));

	if (pVfs != NULL && sgx_is_within_enclave(pVfs, _len_pVfs)) {
		OCALLOC(ms->ms_pVfs, sqlite3_vfs*, _len_pVfs);
		memcpy(ms->ms_pVfs, pVfs, _len_pVfs);
	} else if (pVfs == NULL) {
		ms->ms_pVfs = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	if (zPath != NULL && sgx_is_within_enclave(zPath, _len_zPath)) {
		OCALLOC(ms->ms_zPath, char*, _len_zPath);
		memcpy((void*)ms->ms_zPath, zPath, _len_zPath);
	} else if (zPath == NULL) {
		ms->ms_zPath = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	if (pFile != NULL && sgx_is_within_enclave(pFile, _len_pFile)) {
		OCALLOC(ms->ms_pFile, sqlite3_file*, _len_pFile);
		memcpy(ms->ms_pFile, pFile, _len_pFile);
	} else if (pFile == NULL) {
		ms->ms_pFile = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	ms->ms_flags = flags;
	if (pFlagsOut != NULL && sgx_is_within_enclave(pFlagsOut, _len_pFlagsOut)) {
		OCALLOC(ms->ms_pFlagsOut, int*, _len_pFlagsOut);
		memset(ms->ms_pFlagsOut, 0, _len_pFlagsOut);
	} else if (pFlagsOut == NULL) {
		ms->ms_pFlagsOut = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	status = sgx_ocall(24, ms);

	if (retval) *retval = ms->ms_retval;
	if (pFlagsOut) memcpy((void*)pFlagsOut, ms->ms_pFlagsOut, _len_pFlagsOut);

	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL sqlite3OsDelete(int* retval, sqlite3_vfs* pVfs, const char* zPath, int dirSync)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_pVfs = sizeof(*pVfs);
	size_t _len_zPath = zPath ? strlen(zPath) + 1 : 0;

	ms_sqlite3OsDelete_t* ms;
	OCALLOC(ms, ms_sqlite3OsDelete_t*, sizeof(*ms));

	if (pVfs != NULL && sgx_is_within_enclave(pVfs, _len_pVfs)) {
		OCALLOC(ms->ms_pVfs, sqlite3_vfs*, _len_pVfs);
		memcpy(ms->ms_pVfs, pVfs, _len_pVfs);
	} else if (pVfs == NULL) {
		ms->ms_pVfs = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	if (zPath != NULL && sgx_is_within_enclave(zPath, _len_zPath)) {
		OCALLOC(ms->ms_zPath, char*, _len_zPath);
		memcpy((void*)ms->ms_zPath, zPath, _len_zPath);
	} else if (zPath == NULL) {
		ms->ms_zPath = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	ms->ms_dirSync = dirSync;
	status = sgx_ocall(25, ms);

	if (retval) *retval = ms->ms_retval;

	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL sqlite3OsAccess(int* retval, sqlite3_vfs* pVfs, const char* zPath, int flags, int* pResOut)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_pVfs = sizeof(*pVfs);
	size_t _len_zPath = zPath ? strlen(zPath) + 1 : 0;
	size_t _len_pResOut = sizeof(*pResOut);

	ms_sqlite3OsAccess_t* ms;
	OCALLOC(ms, ms_sqlite3OsAccess_t*, sizeof(*ms));

	if (pVfs != NULL && sgx_is_within_enclave(pVfs, _len_pVfs)) {
		OCALLOC(ms->ms_pVfs, sqlite3_vfs*, _len_pVfs);
		memcpy(ms->ms_pVfs, pVfs, _len_pVfs);
	} else if (pVfs == NULL) {
		ms->ms_pVfs = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	if (zPath != NULL && sgx_is_within_enclave(zPath, _len_zPath)) {
		OCALLOC(ms->ms_zPath, char*, _len_zPath);
		memcpy((void*)ms->ms_zPath, zPath, _len_zPath);
	} else if (zPath == NULL) {
		ms->ms_zPath = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	ms->ms_flags = flags;
	if (pResOut != NULL && sgx_is_within_enclave(pResOut, _len_pResOut)) {
		OCALLOC(ms->ms_pResOut, int*, _len_pResOut);
		memset(ms->ms_pResOut, 0, _len_pResOut);
	} else if (pResOut == NULL) {
		ms->ms_pResOut = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	status = sgx_ocall(26, ms);

	if (retval) *retval = ms->ms_retval;
	if (pResOut) memcpy((void*)pResOut, ms->ms_pResOut, _len_pResOut);

	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL sqlite3OsRandomness(int* retval, sqlite3_vfs* pVfs, int nByte, char* zBufOut)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_pVfs = sizeof(*pVfs);
	size_t _len_zBufOut = nByte;

	ms_sqlite3OsRandomness_t* ms;
	OCALLOC(ms, ms_sqlite3OsRandomness_t*, sizeof(*ms));

	if (pVfs != NULL && sgx_is_within_enclave(pVfs, _len_pVfs)) {
		OCALLOC(ms->ms_pVfs, sqlite3_vfs*, _len_pVfs);
		memcpy(ms->ms_pVfs, pVfs, _len_pVfs);
	} else if (pVfs == NULL) {
		ms->ms_pVfs = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	ms->ms_nByte = nByte;
	if (zBufOut != NULL && sgx_is_within_enclave(zBufOut, _len_zBufOut)) {
		OCALLOC(ms->ms_zBufOut, char*, _len_zBufOut);
		memset(ms->ms_zBufOut, 0, _len_zBufOut);
	} else if (zBufOut == NULL) {
		ms->ms_zBufOut = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	status = sgx_ocall(27, ms);

	if (retval) *retval = ms->ms_retval;
	if (zBufOut) memcpy((void*)zBufOut, ms->ms_zBufOut, _len_zBufOut);

	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL sqlite3OsCurrentTimeInt64(int* retval, sqlite3_vfs* pVfs, sqlite3_int64* pTimeOut)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_pVfs = sizeof(*pVfs);
	size_t _len_pTimeOut = sizeof(*pTimeOut);

	ms_sqlite3OsCurrentTimeInt64_t* ms;
	OCALLOC(ms, ms_sqlite3OsCurrentTimeInt64_t*, sizeof(*ms));

	if (pVfs != NULL && sgx_is_within_enclave(pVfs, _len_pVfs)) {
		OCALLOC(ms->ms_pVfs, sqlite3_vfs*, _len_pVfs);
		memcpy(ms->ms_pVfs, pVfs, _len_pVfs);
	} else if (pVfs == NULL) {
		ms->ms_pVfs = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	if (pTimeOut != NULL && sgx_is_within_enclave(pTimeOut, _len_pTimeOut)) {
		OCALLOC(ms->ms_pTimeOut, sqlite3_int64*, _len_pTimeOut);
		memset(ms->ms_pTimeOut, 0, _len_pTimeOut);
	} else if (pTimeOut == NULL) {
		ms->ms_pTimeOut = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	status = sgx_ocall(28, ms);

	if (retval) *retval = ms->ms_retval;
	if (pTimeOut) memcpy((void*)pTimeOut, ms->ms_pTimeOut, _len_pTimeOut);

	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL sqlite3OsOpenMalloc(int* retval, sqlite3_vfs* pVfs, const char* zFile, sqlite3_file** ppFile, int flags, int* pOutFlags)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_pVfs = sizeof(*pVfs);
	size_t _len_zFile = zFile ? strlen(zFile) + 1 : 0;
	size_t _len_ppFile = 1 * 72;
	size_t _len_pOutFlags = sizeof(*pOutFlags);

	ms_sqlite3OsOpenMalloc_t* ms;
	OCALLOC(ms, ms_sqlite3OsOpenMalloc_t*, sizeof(*ms));

	if (pVfs != NULL && sgx_is_within_enclave(pVfs, _len_pVfs)) {
		OCALLOC(ms->ms_pVfs, sqlite3_vfs*, _len_pVfs);
		memcpy(ms->ms_pVfs, pVfs, _len_pVfs);
	} else if (pVfs == NULL) {
		ms->ms_pVfs = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	if (zFile != NULL && sgx_is_within_enclave(zFile, _len_zFile)) {
		OCALLOC(ms->ms_zFile, char*, _len_zFile);
		memcpy((void*)ms->ms_zFile, zFile, _len_zFile);
	} else if (zFile == NULL) {
		ms->ms_zFile = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	if (ppFile != NULL && sgx_is_within_enclave(ppFile, _len_ppFile)) {
		OCALLOC(ms->ms_ppFile, sqlite3_file**, _len_ppFile);
		memcpy(ms->ms_ppFile, ppFile, _len_ppFile);
	} else if (ppFile == NULL) {
		ms->ms_ppFile = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	ms->ms_flags = flags;
	if (pOutFlags != NULL && sgx_is_within_enclave(pOutFlags, _len_pOutFlags)) {
		OCALLOC(ms->ms_pOutFlags, int*, _len_pOutFlags);
		memset(ms->ms_pOutFlags, 0, _len_pOutFlags);
	} else if (pOutFlags == NULL) {
		ms->ms_pOutFlags = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	status = sgx_ocall(29, ms);

	if (retval) *retval = ms->ms_retval;
	if (pOutFlags) memcpy((void*)pOutFlags, ms->ms_pOutFlags, _len_pOutFlags);

	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL sqlite3OsCloseFree(int* retval, sqlite3_file* pFile)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_pFile = 72;

	ms_sqlite3OsCloseFree_t* ms;
	OCALLOC(ms, ms_sqlite3OsCloseFree_t*, sizeof(*ms));

	if (pFile != NULL && sgx_is_within_enclave(pFile, _len_pFile)) {
		OCALLOC(ms->ms_pFile, sqlite3_file*, _len_pFile);
		memcpy(ms->ms_pFile, pFile, _len_pFile);
	} else if (pFile == NULL) {
		ms->ms_pFile = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	status = sgx_ocall(30, ms);

	if (retval) *retval = ms->ms_retval;

	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL sqlite3OsShmMap(int* retval, sqlite3_file* id, int iPage, int pgsz, int bExtend, void** pp)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_id = 72;
	size_t _len_pp = 1 * pgsz;

	ms_sqlite3OsShmMap_t* ms;
	OCALLOC(ms, ms_sqlite3OsShmMap_t*, sizeof(*ms));

	if (id != NULL && sgx_is_within_enclave(id, _len_id)) {
		OCALLOC(ms->ms_id, sqlite3_file*, _len_id);
		memcpy(ms->ms_id, id, _len_id);
	} else if (id == NULL) {
		ms->ms_id = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	ms->ms_iPage = iPage;
	ms->ms_pgsz = pgsz;
	ms->ms_bExtend = bExtend;
	if (pp != NULL && sgx_is_within_enclave(pp, _len_pp)) {
		OCALLOC(ms->ms_pp, void**, _len_pp);
		memset(ms->ms_pp, 0, _len_pp);
	} else if (pp == NULL) {
		ms->ms_pp = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	status = sgx_ocall(31, ms);

	if (retval) *retval = ms->ms_retval;
	if (pp) memcpy((void*)pp, ms->ms_pp, _len_pp);

	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL sqlite3OsShmLock(int* retval, sqlite3_file* id, int offset, int n, int flags)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_id = 72;

	ms_sqlite3OsShmLock_t* ms;
	OCALLOC(ms, ms_sqlite3OsShmLock_t*, sizeof(*ms));

	if (id != NULL && sgx_is_within_enclave(id, _len_id)) {
		OCALLOC(ms->ms_id, sqlite3_file*, _len_id);
		memcpy(ms->ms_id, id, _len_id);
	} else if (id == NULL) {
		ms->ms_id = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	ms->ms_offset = offset;
	ms->ms_n = n;
	ms->ms_flags = flags;
	status = sgx_ocall(32, ms);

	if (retval) *retval = ms->ms_retval;

	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL sqlite3OsShmBarrier(sqlite3_file* id)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_id = 72;

	ms_sqlite3OsShmBarrier_t* ms;
	OCALLOC(ms, ms_sqlite3OsShmBarrier_t*, sizeof(*ms));

	if (id != NULL && sgx_is_within_enclave(id, _len_id)) {
		OCALLOC(ms->ms_id, sqlite3_file*, _len_id);
		memcpy(ms->ms_id, id, _len_id);
	} else if (id == NULL) {
		ms->ms_id = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	status = sgx_ocall(33, ms);


	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL sqlite3OsShmUnmap(int* retval, sqlite3_file* id, int deleteFlag)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_id = 72;

	ms_sqlite3OsShmUnmap_t* ms;
	OCALLOC(ms, ms_sqlite3OsShmUnmap_t*, sizeof(*ms));

	if (id != NULL && sgx_is_within_enclave(id, _len_id)) {
		OCALLOC(ms->ms_id, sqlite3_file*, _len_id);
		memcpy(ms->ms_id, id, _len_id);
	} else if (id == NULL) {
		ms->ms_id = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	ms->ms_deleteFlag = deleteFlag;
	status = sgx_ocall(34, ms);

	if (retval) *retval = ms->ms_retval;

	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL sqlite3LoadExtension(int* retval, sqlite3* db, const char* zFile, const char* zProc, char** pzErrMsg, int buf_size)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_db = sizeof(*db);
	size_t _len_zFile = zFile ? strlen(zFile) + 1 : 0;
	size_t _len_zProc = zProc ? strlen(zProc) + 1 : 0;
	size_t _len_pzErrMsg = 1 * buf_size;

	ms_sqlite3LoadExtension_t* ms;
	OCALLOC(ms, ms_sqlite3LoadExtension_t*, sizeof(*ms));

	if (db != NULL && sgx_is_within_enclave(db, _len_db)) {
		OCALLOC(ms->ms_db, sqlite3*, _len_db);
		memcpy(ms->ms_db, db, _len_db);
	} else if (db == NULL) {
		ms->ms_db = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	if (zFile != NULL && sgx_is_within_enclave(zFile, _len_zFile)) {
		OCALLOC(ms->ms_zFile, char*, _len_zFile);
		memcpy((void*)ms->ms_zFile, zFile, _len_zFile);
	} else if (zFile == NULL) {
		ms->ms_zFile = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	if (zProc != NULL && sgx_is_within_enclave(zProc, _len_zProc)) {
		OCALLOC(ms->ms_zProc, char*, _len_zProc);
		memcpy((void*)ms->ms_zProc, zProc, _len_zProc);
	} else if (zProc == NULL) {
		ms->ms_zProc = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	if (pzErrMsg != NULL && sgx_is_within_enclave(pzErrMsg, _len_pzErrMsg)) {
		OCALLOC(ms->ms_pzErrMsg, char**, _len_pzErrMsg);
		memset(ms->ms_pzErrMsg, 0, _len_pzErrMsg);
	} else if (pzErrMsg == NULL) {
		ms->ms_pzErrMsg = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	ms->ms_buf_size = buf_size;
	status = sgx_ocall(35, ms);

	if (retval) *retval = ms->ms_retval;
	if (pzErrMsg) memcpy((void*)pzErrMsg, ms->ms_pzErrMsg, _len_pzErrMsg);

	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL sqlite3CloseExtensions(sqlite3* db)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_db = sizeof(*db);

	ms_sqlite3CloseExtensions_t* ms;
	OCALLOC(ms, ms_sqlite3CloseExtensions_t*, sizeof(*ms));

	if (db != NULL && sgx_is_within_enclave(db, _len_db)) {
		OCALLOC(ms->ms_db, sqlite3*, _len_db);
		memcpy(ms->ms_db, db, _len_db);
	} else if (db == NULL) {
		ms->ms_db = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	status = sgx_ocall(36, ms);


	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL sqlite3OsClose(int* retval, sqlite3_file* pId)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_pId = 72;

	ms_sqlite3OsClose_t* ms;
	OCALLOC(ms, ms_sqlite3OsClose_t*, sizeof(*ms));

	if (pId != NULL && sgx_is_within_enclave(pId, _len_pId)) {
		OCALLOC(ms->ms_pId, sqlite3_file*, _len_pId);
		memcpy(ms->ms_pId, pId, _len_pId);
	} else if (pId == NULL) {
		ms->ms_pId = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	status = sgx_ocall(37, ms);

	if (retval) *retval = ms->ms_retval;

	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL get_sqlite3JournalSize(int* retval)
{
	sgx_status_t status = SGX_SUCCESS;

	ms_get_sqlite3JournalSize_t* ms;
	OCALLOC(ms, ms_get_sqlite3JournalSize_t*, sizeof(*ms));

	status = sgx_ocall(38, ms);

	if (retval) *retval = ms->ms_retval;

	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL getMxPathName(int* retval)
{
	sgx_status_t status = SGX_SUCCESS;

	ms_getMxPathName_t* ms;
	OCALLOC(ms, ms_getMxPathName_t*, sizeof(*ms));

	status = sgx_ocall(39, ms);

	if (retval) *retval = ms->ms_retval;

	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL sgx_thread_wait_untrusted_event_ocall(int* retval, const void* self)
{
	sgx_status_t status = SGX_SUCCESS;

	ms_sgx_thread_wait_untrusted_event_ocall_t* ms;
	OCALLOC(ms, ms_sgx_thread_wait_untrusted_event_ocall_t*, sizeof(*ms));

	ms->ms_self = SGX_CAST(void*, self);
	status = sgx_ocall(40, ms);

	if (retval) *retval = ms->ms_retval;

	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL sgx_thread_set_untrusted_event_ocall(int* retval, const void* waiter)
{
	sgx_status_t status = SGX_SUCCESS;

	ms_sgx_thread_set_untrusted_event_ocall_t* ms;
	OCALLOC(ms, ms_sgx_thread_set_untrusted_event_ocall_t*, sizeof(*ms));

	ms->ms_waiter = SGX_CAST(void*, waiter);
	status = sgx_ocall(41, ms);

	if (retval) *retval = ms->ms_retval;

	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL sgx_thread_setwait_untrusted_events_ocall(int* retval, const void* waiter, const void* self)
{
	sgx_status_t status = SGX_SUCCESS;

	ms_sgx_thread_setwait_untrusted_events_ocall_t* ms;
	OCALLOC(ms, ms_sgx_thread_setwait_untrusted_events_ocall_t*, sizeof(*ms));

	ms->ms_waiter = SGX_CAST(void*, waiter);
	ms->ms_self = SGX_CAST(void*, self);
	status = sgx_ocall(42, ms);

	if (retval) *retval = ms->ms_retval;

	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL sgx_thread_set_multiple_untrusted_events_ocall(int* retval, const void** waiters, size_t total)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_waiters = total * sizeof(*waiters);

	ms_sgx_thread_set_multiple_untrusted_events_ocall_t* ms;
	OCALLOC(ms, ms_sgx_thread_set_multiple_untrusted_events_ocall_t*, sizeof(*ms));

	if (waiters != NULL && sgx_is_within_enclave(waiters, _len_waiters)) {
		OCALLOC(ms->ms_waiters, void**, _len_waiters);
		memcpy((void*)ms->ms_waiters, waiters, _len_waiters);
	} else if (waiters == NULL) {
		ms->ms_waiters = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	ms->ms_total = total;
	status = sgx_ocall(43, ms);

	if (retval) *retval = ms->ms_retval;

	sgx_ocfree();
	return status;
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
