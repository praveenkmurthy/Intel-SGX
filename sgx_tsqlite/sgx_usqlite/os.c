/*
** 2005 November 29
**
** The author disclaims copyright to this source code.  In place of
** a legal notice, here is a blessing:
**
**    May you do good and not evil.
**    May you find forgiveness for yourself and forgive others.
**    May you share freely, never taking more than you give.
**
******************************************************************************
**
** This file contains OS interface code that is common to all
** architectures.
*/
#define _SQLITE_OS_C_ 1
#include "sqliteInt.h"
#include "sqlite3ext.h"
#undef _SQLITE_OS_C_

/*
** If we compile with the SQLITE_TEST macro set, then the following block
** of code will give us the ability to simulate a disk I/O error.  This
** is used for testing the I/O recovery logic.
*/
#if defined(SQLITE_TEST)
int sqlite3_io_error_hit = 0;            /* Total number of I/O Errors */
int sqlite3_io_error_hardhit = 0;        /* Number of non-benign errors */
int sqlite3_io_error_pending = 0;        /* Count down to first I/O error */
int sqlite3_io_error_persist = 0;        /* True if I/O errors persist */
int sqlite3_io_error_benign = 0;         /* True if errors are benign */
int sqlite3_diskfull_pending = 0;
int sqlite3_diskfull = 0;
#endif /* defined(SQLITE_TEST) */

/*
** When testing, also keep a count of the number of open files.
*/
#if defined(SQLITE_TEST)
int sqlite3_open_file_count = 0;
#endif /* defined(SQLITE_TEST) */

/*
** The default SQLite sqlite3_vfs implementations do not allocate
** memory (actually, os_unix.c allocates a small amount of memory
** from within OsOpen()), but some third-party implementations may.
** So we test the effects of a malloc() failing and the sqlite3OsXXX()
** function returning SQLITE_IOERR_NOMEM using the DO_OS_MALLOC_TEST macro.
**
** The following functions are instrumented for malloc() failure
** testing:
**
**     sqlite3OsRead()
**     sqlite3OsWrite()
**     sqlite3OsSync()
**     sqlite3OsFileSize()
**     sqlite3OsLock()
**     sqlite3OsCheckReservedLock()
**     sqlite3OsFileControl()
**     sqlite3OsShmMap()
**     sqlite3OsOpen()
**     sqlite3OsDelete()
**     sqlite3OsAccess()
**     sqlite3OsFullPathname()
**
*/
#if defined(SQLITE_TEST)
int sqlite3_memdebug_vfs_oom_test = 1;
  #define DO_OS_MALLOC_TEST(x)                                       \
  if (sqlite3_memdebug_vfs_oom_test && (!x || !sqlite3IsMemJournal(x))) {  \
    void *pTstAlloc = sqlite3Malloc(10);                             \
    if (!pTstAlloc) return SQLITE_IOERR_NOMEM;                       \
    sqlite3_free(pTstAlloc);                                         \
  }
#else
  #define DO_OS_MALLOC_TEST(x)
#endif

/*
** The following routines are convenience wrappers around methods
** of the sqlite3_file object.  This is mostly just syntactic sugar. All
** of this would be completely automatic if SQLite were coded using
** C++ instead of plain old C.
*/
int sqlite3OsClose(sqlite3_file *pId){
  int rc = SQLITE_OK;
  sqlite3_vfs *pVfs = sqlite3_vfs_find(0);
  if( pVfs->pMethods ){
    rc = pVfs->pMethods->xClose(pId);
    pVfs->pMethods = 0;
  }
  return rc;
}
int sqlite3OsRead(sqlite3_file *id, void *pBuf, int amt, i64 offset){
  //DO_OS_MALLOC_TEST(id);
  sqlite3_vfs *pVfs = sqlite3_vfs_find(0);
  return pVfs->pMethods->xRead(id, pBuf, amt, offset);
}
int sqlite3OsWrite(sqlite3_file *id, const void *pBuf, int amt, i64 offset){
  //DO_OS_MALLOC_TEST(id);
  sqlite3_vfs *pVfs = sqlite3_vfs_find(0);
  return pVfs->pMethods->xWrite(id, pBuf, amt, offset);
}
int sqlite3OsTruncate(sqlite3_file *id, i64 size){
	sqlite3_vfs *pVfs = sqlite3_vfs_find(0);
	return pVfs->pMethods->xTruncate(id, size);
}
int sqlite3OsSync(sqlite3_file *id, int flags){
  //DO_OS_MALLOC_TEST(id);
  sqlite3_vfs *pVfs = sqlite3_vfs_find(0);
  return pVfs->pMethods->xSync(id, flags);
}
int sqlite3OsFileSize(sqlite3_file *id, i64 *pSize){
  //DO_OS_MALLOC_TEST(id);
  sqlite3_vfs *pVfs = sqlite3_vfs_find(0);
  return pVfs->pMethods->xFileSize(id, pSize);
}
int sqlite3OsLock(sqlite3_file *id, int lockType){
  //DO_OS_MALLOC_TEST(id);
  sqlite3_vfs *pVfs = sqlite3_vfs_find(0);
  return pVfs->pMethods->xLock(id, lockType);
}
int sqlite3OsUnlock(sqlite3_file *id, int lockType){
	sqlite3_vfs *pVfs = sqlite3_vfs_find(0);
  return pVfs->pMethods->xUnlock(id, lockType);
}
int sqlite3OsCheckReservedLock(sqlite3_file *id, int *pResOut){
  //DO_OS_MALLOC_TEST(id);
  sqlite3_vfs *pVfs = sqlite3_vfs_find(0);
  return pVfs->pMethods->xCheckReservedLock(id, pResOut);
}

/*
** Use sqlite3OsFileControl() when we are doing something that might fail
** and we need to know about the failures.  Use sqlite3OsFileControlHint()
** when simply tossing information over the wall to the VFS and we do not
** really care if the VFS receives and understands the information since it
** is only a hint and can be safely ignored.  The sqlite3OsFileControlHint()
** routine has no return value since the return value would be meaningless.
*/
int sqlite3OsFileControl(sqlite3_file *id, int op, void *pArg){
#ifdef SQLITE_TEST
  if( op!=SQLITE_FCNTL_COMMIT_PHASETWO ){
    /* Faults are not injected into COMMIT_PHASETWO because, assuming SQLite
    ** is using a regular VFS, it is called after the corresponding
    ** transaction has been committed. Injecting a fault at this point
    ** confuses the test scripts - the COMMIT comand returns SQLITE_NOMEM
    ** but the transaction is committed anyway.
    **
    ** The core must call OsFileControl() though, not OsFileControlHint(),
    ** as if a custom VFS (e.g. zipvfs) returns an error here, it probably
    ** means the commit really has failed and an error should be returned
    ** to the user.  */
    DO_OS_MALLOC_TEST(id);
  }
#endif
  return id->pMethods->xFileControl(id, op, pArg);
}

int sqlite3OsSectorSize(sqlite3_file *id){
	sqlite3_vfs *pVfs = sqlite3_vfs_find(0);
  int (*xSectorSize)(sqlite3_file*) = pVfs->pMethods->xSectorSize;
  return (xSectorSize ? xSectorSize(id) : SQLITE_DEFAULT_SECTOR_SIZE);
}
int sqlite3OsDeviceCharacteristics(sqlite3_file *id){
	sqlite3_vfs *pVfs = sqlite3_vfs_find(0);
  return pVfs->pMethods->xDeviceCharacteristics(id);
}
int sqlite3OsShmLock(sqlite3_file *id, int offset, int n, int flags){
	sqlite3_vfs *pVfs = sqlite3_vfs_find(0);
  return pVfs->pMethods->xShmLock(id, offset, n, flags);
}
void sqlite3OsShmBarrier(sqlite3_file *id){
	sqlite3_vfs *pVfs = sqlite3_vfs_find(0);
  pVfs->pMethods->xShmBarrier(id);
}
int sqlite3OsShmUnmap(sqlite3_file *id, int deleteFlag){
	sqlite3_vfs *pVfs = sqlite3_vfs_find(0);
  return pVfs->pMethods->xShmUnmap(id, deleteFlag);
}
int sqlite3OsShmMap(
  sqlite3_file *id,               /* Database file handle */
  int iPage,
  int pgsz,
  int bExtend,                    /* True to extend file if necessary */
  void volatile **pp              /* OUT: Pointer to mapping */
){
  //DO_OS_MALLOC_TEST(id);
  sqlite3_vfs *pVfs = sqlite3_vfs_find(0);
  return pVfs->pMethods->xShmMap(id, iPage, pgsz, bExtend, pp);
}

#if SQLITE_MAX_MMAP_SIZE>0
/* The real implementation of xFetch and xUnfetch */
int sqlite3OsFetch(sqlite3_file *id, i64 iOff, int iAmt, void **pp){
  //DO_OS_MALLOC_TEST(id);
  sqlite3_vfs *pVfs = sqlite3_vfs_find(0);
  return pVfs->pMethods->xFetch(id, iOff, iAmt, pp);
}
int sqlite3OsUnfetch(sqlite3_file *id, i64 iOff, void *p){
	sqlite3_vfs *pVfs = sqlite3_vfs_find(0);
  return pVfs->pMethods->xUnfetch(id, iOff, p);
}
#else
/* No-op stubs to use when memory-mapped I/O is disabled */
int sqlite3OsFetch(sqlite3_file *id, i64 iOff, int iAmt, void **pp){
  *pp = 0;
  return SQLITE_OK;
}
int sqlite3OsUnfetch(sqlite3_file *id, i64 iOff, void *p){
  return SQLITE_OK;
}
#endif

/*
** The next group of routines are convenience wrappers around the
** VFS methods.
*/
int sqlite3OsOpen(
  sqlite3_vfs *pVfs,
  const char *zPath,
  sqlite3_file *pFile,
  int flags,
  int *pFlagsOut
){
  int rc;
  DO_OS_MALLOC_TEST(0);
  /* 0x87f7f is a mask of SQLITE_OPEN_ flags that are valid to be passed
  ** down into the VFS layer.  Some SQLITE_OPEN_ flags (for example,
  ** SQLITE_OPEN_FULLMUTEX or SQLITE_OPEN_SHAREDCACHE) are blocked before
  ** reaching the VFS. */
  pVfs = sqlite3_vfs_find(0);
  printf("xOpen: %s %d \n", zPath, flags);
  rc = pVfs->xOpen(pVfs, zPath, pFile, flags & 0x87f7f, pFlagsOut);
  printf("xOpen: %d %s %d \n", rc, zPath, flags);
  assert( rc==SQLITE_OK || pFile->pMethods==0 );
  return rc;
}
int sqlite3OsDelete(sqlite3_vfs *pVfs, const char *zPath, int dirSync){
  DO_OS_MALLOC_TEST(0);
  assert( dirSync==0 || dirSync==1 );
  pVfs = sqlite3_vfs_find(0);
  return pVfs->xDelete(pVfs, zPath, dirSync);
}
int sqlite3OsAccess(
  sqlite3_vfs *pVfs,
  const char *zPath,
  int flags,
  int *pResOut
){
  DO_OS_MALLOC_TEST(0);
  pVfs = sqlite3_vfs_find(0);
  return pVfs->xAccess(pVfs, zPath, flags, pResOut);
}
int sqlite3OsFullPathname(
  sqlite3_vfs *pVfs,
  const char *zPath,
  int nPathOut,
  char *zPathOut
){
  DO_OS_MALLOC_TEST(0);
  zPathOut[0] = 0;
  pVfs = sqlite3_vfs_find(0);
  return pVfs->xFullPathname(pVfs, zPath, nPathOut, zPathOut);
}
#ifndef SQLITE_OMIT_LOAD_EXTENSION
void *sqlite3OsDlOpen(sqlite3_vfs *pVfs, const char *zPath){
  return pVfs->xDlOpen(pVfs, zPath);
}
void sqlite3OsDlError(sqlite3_vfs *pVfs, int nByte, char *zBufOut){
  pVfs->xDlError(pVfs, nByte, zBufOut);
}
void (*sqlite3OsDlSym(sqlite3_vfs *pVfs, void *pHdle, const char *zSym))(void){
  return pVfs->xDlSym(pVfs, pHdle, zSym);
}
void sqlite3OsDlClose(sqlite3_vfs *pVfs, void *pHandle){
  pVfs->xDlClose(pVfs, pHandle);
}
#endif /* SQLITE_OMIT_LOAD_EXTENSION */
int sqlite3OsRandomness(sqlite3_vfs *pVfs, int nByte, char *zBufOut){
  	pVfs = sqlite3_vfs_find(0);

	return pVfs->xRandomness(pVfs, nByte, zBufOut);
}
int sqlite3OsSleep(sqlite3_vfs *pVfs, int nMicro){
	pVfs = sqlite3_vfs_find(0);

  return pVfs->xSleep(pVfs, nMicro);
}
int sqlite3OsCurrentTimeInt64(sqlite3_vfs *pVfs, sqlite3_int64 *pTimeOut){
  int rc;
  /* IMPLEMENTATION-OF: R-49045-42493 SQLite will use the xCurrentTimeInt64()
  ** method to get the current date and time if that method is available
  ** (if iVersion is 2 or greater and the function pointer is not NULL) and
  ** will fall back to xCurrentTime() if xCurrentTimeInt64() is
  ** unavailable.
  */
  pVfs = sqlite3_vfs_find(0);
  if( pVfs->iVersion>=2 && pVfs->xCurrentTimeInt64 ){
    rc = pVfs->xCurrentTimeInt64(pVfs, pTimeOut);
  }else{
    double r;
    rc = pVfs->xCurrentTime(pVfs, &r);
    *pTimeOut = (sqlite3_int64)(r*86400000.0);
  }
  return rc;
}

int sqlite3OsOpenMalloc(
  sqlite3_vfs *pVfs,
  const char *zFile,
  sqlite3_file **ppFile,
  int flags,
  int *pOutFlags
){
  int rc = SQLITE_NOMEM;
  sqlite3_file *pFile;
  pVfs = sqlite3_vfs_find(0);
  pFile = (sqlite3_file *)sqlite3MallocZero(pVfs->szOsFile);
  if( pFile ){
    rc = sqlite3OsOpen(pVfs, zFile, pFile, flags, pOutFlags);
    if( rc!=SQLITE_OK ){
      sqlite3_free(pFile);
    }else{
      *ppFile = pFile;
    }
  }
  return rc;
}
int sqlite3OsCloseFree(sqlite3_file *pFile){
  int rc = SQLITE_OK;
  assert( pFile );
  rc = sqlite3OsClose(pFile);
  sqlite3_free(pFile);
  return rc;
}

/*
** Initialize SQLite.
**
** This routine must be called to initialize the memory allocation,
** VFS, and mutex subsystems prior to doing any serious work with
** SQLite.  But as long as you do not compile with SQLITE_OMIT_AUTOINIT
** this routine will be called automatically by key routines such as
** sqlite3_open().
**
** This routine is a no-op except on its very first call for the process,
** or for the first call after a call to sqlite3_shutdown.
**
** The first thread to call this routine runs the initialization to
** completion.  If subsequent threads call this routine before the first
** thread has finished the initialization process, then the subsequent
** threads must block until the first thread finishes with the initialization.
**
** The first thread might call this routine recursively.  Recursive
** calls to this routine should not block, of course.  Otherwise the
** initialization process would never complete.
**
** Let X be the first thread to enter this routine.  Let Y be some other
** thread.  Then while the initial invocation of this routine by X is
** incomplete, it is required that:
**
**    *  Calls to this routine from Y must block until the outer-most
**       call by X completes.
**
**    *  Recursive calls to this routine from thread X return immediately
**       without blocking.
*/
int sqlite3_int_initialize(void){
  MUTEX_LOGIC( sqlite3_mutex *pMaster; )       /* The main static mutex */
  int rc;                                      /* Result code */
#ifdef SQLITE_EXTRA_INIT
  int bRunExtraInit = 0;                       /* Extra initialization needed */
#endif

#ifdef SQLITE_OMIT_WSD
  rc = sqlite3_wsd_init(4096, 24);
  if( rc!=SQLITE_OK ){
    return rc;
  }
#endif

  /* If the following assert() fails on some obscure processor/compiler
  ** combination, the work-around is to set the correct pointer
  ** size at compile-time using -DSQLITE_PTRSIZE=n compile-time option */
  assert( SQLITE_PTRSIZE==sizeof(char*) );

  /* If SQLite is already completely initialized, then this call
  ** to sqlite3_initialize() should be a no-op.  But the initialization
  ** must be complete.  So isInit must not be set until the very end
  ** of this routine.
  */
  if( sqlite3GlobalConfig.isInit ) return SQLITE_OK;

  /* Make sure the mutex subsystem is initialized.  If unable to
  ** initialize the mutex subsystem, return early with the error.
  ** If the system is so sick that we are unable to allocate a mutex,
  ** there is not much SQLite is going to be able to do.
  **
  ** The mutex subsystem must take care of serializing its own
  ** initialization.
  */
  rc = sqlite3MutexInit();
  if( rc ) return rc;
  
  /* Initialize the malloc() system and the recursive pInitMutex mutex.
  ** This operation is protected by the STATIC_MASTER mutex.  Note that
  ** MutexAlloc() is called for a static mutex prior to initializing the
  ** malloc subsystem - this implies that the allocation of a static
  ** mutex must not require support from the malloc subsystem.
  */
  MUTEX_LOGIC( pMaster = sqlite3MutexAlloc(SQLITE_MUTEX_STATIC_MASTER); )
  sqlite3_mutex_enter(pMaster);
  sqlite3GlobalConfig.isMutexInit = 1;
  if( !sqlite3GlobalConfig.isMallocInit ){
    rc = sqlite3MallocInit();
  }
  printf("Initializing untrusted library %d\n", rc);
  
  if( rc==SQLITE_OK ){
    sqlite3GlobalConfig.isMallocInit = 1;
    if( !sqlite3GlobalConfig.pInitMutex ){
      sqlite3GlobalConfig.pInitMutex =
           sqlite3MutexAlloc(SQLITE_MUTEX_RECURSIVE);
      if( sqlite3GlobalConfig.bCoreMutex && !sqlite3GlobalConfig.pInitMutex ){
        rc = SQLITE_NOMEM;
      }
    }
  }
  if( rc==SQLITE_OK ){
    sqlite3GlobalConfig.nRefInitMutex++;
  }
  sqlite3_mutex_leave(pMaster);
  
  /* If rc is not SQLITE_OK at this point, then either the malloc
  ** subsystem could not be initialized or the system failed to allocate
  ** the pInitMutex mutex. Return an error in either case.  */
  if( rc!=SQLITE_OK ){
    return rc;
  }

  /* Do the rest of the initialization under the recursive mutex so
  ** that we will be able to handle recursive calls into
  ** sqlite3_initialize().  The recursive calls normally come through
  ** sqlite3_os_init() when it invokes sqlite3_vfs_register(), but other
  ** recursive calls might also be possible.
  **
  ** IMPLEMENTATION-OF: R-00140-37445 SQLite automatically serializes calls
  ** to the xInit method, so the xInit method need not be threadsafe.
  **
  ** The following mutex is what serializes access to the appdef pcache xInit
  ** methods.  The sqlite3_pcache_methods.xInit() all is embedded in the
  ** call to sqlite3PcacheInitialize().
  */
  sqlite3_mutex_enter(sqlite3GlobalConfig.pInitMutex);
  if( sqlite3GlobalConfig.isInit==0 && sqlite3GlobalConfig.inProgress==0 ){
    FuncDefHash *pHash = &GLOBAL(FuncDefHash, sqlite3GlobalFunctions);
    sqlite3GlobalConfig.inProgress = 1;
#ifdef SQLITE_ENABLE_SQLLOG
    {
      extern void sqlite3_init_sqllog(void);
      sqlite3_init_sqllog();
    }
#endif
    //memset(pHash, 0, sizeof(sqlite3GlobalFunctions));
    //sqlite3RegisterGlobalFunctions();
    if( sqlite3GlobalConfig.isPCacheInit==0 ){
    //  rc = sqlite3PcacheInitialize();
    }

	if( rc==SQLITE_OK ){
      sqlite3GlobalConfig.isPCacheInit = 1;
    //  sqlite3OsInit(&rc);
    }

	if( rc==SQLITE_OK ){
      //sqlite3PCacheBufferSetup( sqlite3GlobalConfig.pPage,
      //    sqlite3GlobalConfig.szPage, sqlite3GlobalConfig.nPage);
      sqlite3GlobalConfig.isInit = 1;
#ifdef SQLITE_EXTRA_INIT
      bRunExtraInit = 1;
#endif
    }
    sqlite3GlobalConfig.inProgress = 0;
  }
  sqlite3_mutex_leave(sqlite3GlobalConfig.pInitMutex);

  /* Go back under the static mutex and clean up the recursive
  ** mutex to prevent a resource leak.
  */
  sqlite3_mutex_enter(pMaster);
  sqlite3GlobalConfig.nRefInitMutex--;
  if( sqlite3GlobalConfig.nRefInitMutex<=0 ){
    assert( sqlite3GlobalConfig.nRefInitMutex==0 );
    sqlite3_mutex_free(sqlite3GlobalConfig.pInitMutex);
    sqlite3GlobalConfig.pInitMutex = 0;
  }
  sqlite3_mutex_leave(pMaster);

  /* The following is just a sanity check to make sure SQLite has
  ** been compiled correctly.  It is important to run this code, but
  ** we don't want to run it too often and soak up CPU cycles for no
  ** reason.  So we run it once during initialization.
  */
#ifndef NDEBUG
#ifndef SQLITE_OMIT_FLOATING_POINT
  /* This section of code's only "output" is via assert() statements. */
  if ( rc==SQLITE_OK ){
    u64 x = (((u64)1)<<63)-1;
    double y;
    assert(sizeof(x)==8);
    assert(sizeof(x)==sizeof(y));
    memcpy(&y, &x, 8);
    assert( sqlite3IsNaN(y) );
  }
#endif
#endif

  /* Do extra initialization steps requested by the SQLITE_EXTRA_INIT
  ** compile-time option.
  */
#ifdef SQLITE_EXTRA_INIT
  if( bRunExtraInit ){
    int SQLITE_EXTRA_INIT(const char*);
    rc = SQLITE_EXTRA_INIT(0);
  }
#endif
  
  return rc;
}

/*
** This function is a wrapper around the OS specific implementation of
** sqlite3_os_init(). The purpose of the wrapper is to provide the
** ability to simulate a malloc failure, so that the handling of an
** error in sqlite3_os_init() by the upper layers can be tested.
*/
int sqlite3OsInit(void){
  void *p = NULL;
	int rc=sqlite3_int_initialize();
  printf("sgx_usqlite: %d\n", rc);
  if(rc != SQLITE_OK)
	  return rc;

  return sqlite3_os_init();
}

/*
** The list of all registered VFS implementations.
*/
static sqlite3_vfs * SQLITE_WSD vfsList = 0;
#define vfsList GLOBAL(sqlite3_vfs *, vfsList)

/*
** Locate a VFS by name.  If no name is given, simply return the
** first VFS on the list.
*/
sqlite3_vfs *sqlite3_vfs_find(const char *zVfs){
  sqlite3_vfs *pVfs = 0;
#if SQLITE_THREADSAFE
  sqlite3_mutex *mutex;
#endif
#ifndef SQLITE_OMIT_AUTOINIT
  int rc = sqlite3_initialize();
  if( rc ) return 0;
#endif
#if SQLITE_THREADSAFE
  mutex = sqlite3MutexAlloc(SQLITE_MUTEX_STATIC_MASTER);
#endif
  sqlite3_mutex_enter(mutex);
  for(pVfs = vfsList; pVfs; pVfs=pVfs->pNext){
    if( zVfs==0 ) break;
    if( strcmp(zVfs, pVfs->zName)==0 ) break;
  }
  sqlite3_mutex_leave(mutex);
  return pVfs;
}

/*
** Unlink a VFS from the linked list
*/
static void vfsUnlink(sqlite3_vfs *pVfs){
  assert( sqlite3_mutex_held(sqlite3MutexAlloc(SQLITE_MUTEX_STATIC_MASTER)) );
  if( pVfs==0 ){
    /* No-op */
  }else if( vfsList==pVfs ){
    vfsList = pVfs->pNext;
  }else if( vfsList ){
    sqlite3_vfs *p = vfsList;
    while( p->pNext && p->pNext!=pVfs ){
      p = p->pNext;
    }
    if( p->pNext==pVfs ){
      p->pNext = pVfs->pNext;
    }
  }
}

/*
** Register a VFS with the system.  It is harmless to register the same
** VFS multiple times.  The new VFS becomes the default if makeDflt is
** true.
*/
int sqlite3_vfs_register(sqlite3_vfs *pVfs, int makeDflt){
  MUTEX_LOGIC(sqlite3_mutex *mutex;)
#ifndef SQLITE_OMIT_AUTOINIT
  int rc = sqlite3_initialize();
  printf("Vfs_register: %d", rc);
  if( rc ) return rc;
#endif
#ifdef SQLITE_ENABLE_API_ARMOR
  if( pVfs==0 ) return SQLITE_MISUSE_BKPT;
#endif
  if(pVfs == NULL)
	pVfs = sqlite3_vfs_find(0);
  MUTEX_LOGIC( mutex = sqlite3MutexAlloc(SQLITE_MUTEX_STATIC_MASTER); )
  sqlite3_mutex_enter(mutex);
  vfsUnlink(pVfs);
  if( makeDflt || vfsList==0 ){
    pVfs->pNext = vfsList;
    vfsList = pVfs;
  }else{
    pVfs->pNext = vfsList->pNext;
    vfsList->pNext = pVfs;
  }
  assert(vfsList);
  sqlite3_mutex_leave(mutex);

  printf("pVfs: %p %p\n", sqlite3_vfs_find(0), vfsList);
  return SQLITE_OK;
}

/*
** Unregister a VFS so that it is no longer accessible.
*/
int sqlite3_vfs_unregister(sqlite3_vfs *pVfs){
#if SQLITE_THREADSAFE
  sqlite3_mutex *mutex = sqlite3MutexAlloc(SQLITE_MUTEX_STATIC_MASTER);
#endif
  sqlite3_mutex_enter(mutex);
  pVfs = sqlite3_vfs_find(0);
  vfsUnlink(pVfs);
  sqlite3_mutex_leave(mutex);
  return SQLITE_OK;
}

/*
** The following structure contains pointers to all SQLite API routines.
** A pointer to this structure is passed into extensions when they are
** loaded so that the extension can make calls back into the SQLite
** library.
**
** When adding new APIs, add them to the bottom of this structure
** in order to preserve backwards compatibility.
**
** Extensions that use newer APIs should first call the
** sqlite3_libversion_number() to make sure that the API they
** intend to use is supported by the library.  Extensions should
** also check to make sure that the pointer to the function is
** not NULL before calling it.
*/
static const sqlite3_api_routines sqlite3Apis = {0
};

/*
** Attempt to load an SQLite extension library contained in the file
** zFile.  The entry point is zProc.  zProc may be 0 in which case a
** default entry point name (sqlite3_extension_init) is used.  Use
** of the default name is recommended.
**
** Return SQLITE_OK on success and SQLITE_ERROR if something goes wrong.
**
** If an error occurs and pzErrMsg is not 0, then fill *pzErrMsg with
** error message text.  The calling function should free this memory
** by calling sqlite3DbFree(db, ).
*/
int sqlite3LoadExtension(
  sqlite3 *db,          /* Load the extension into this database connection */
  const char *zFile,    /* Name of the shared library containing extension */
  const char *zProc,    /* Entry point.  Use "sqlite3_extension_init" if 0 */
  char **pzErrMsg       /* Put error message here if not 0 */
){
  sqlite3_vfs *pVfs = db->pVfs;
  void *handle;
  int (*xInit)(sqlite3*,char**,const sqlite3_api_routines*);
  char *zErrmsg = 0;
  const char *zEntry;
  char *zAltEntry = 0;
  void **aHandle;
  u64 nMsg = 300 + sqlite3Strlen30(zFile);
  int ii;

  /* Shared library endings to try if zFile cannot be loaded as written */
  static const char *azEndings[] = {
#if SQLITE_OS_WIN
     "dll"
#elif defined(__APPLE__)
     "dylib"
#else
     "so"
#endif
  };


  if( pzErrMsg ) *pzErrMsg = 0;

  /* Ticket #1863.  To avoid a creating security problems for older
  ** applications that relink against newer versions of SQLite, the
  ** ability to run load_extension is turned off by default.  One
  ** must call sqlite3_enable_load_extension() to turn on extension
  ** loading.  Otherwise you get the following error.
  */
  if( (db->flags & SQLITE_LoadExtension)==0 ){
    if( pzErrMsg ){
      *pzErrMsg = sqlite3_mprintf("not authorized");
    }
    return SQLITE_ERROR;
  }

  zEntry = zProc ? zProc : "sqlite3_extension_init";

  handle = sqlite3OsDlOpen(pVfs, zFile);
#if SQLITE_OS_UNIX || SQLITE_OS_WIN
  for(ii=0; ii<ArraySize(azEndings) && handle==0; ii++){
    char *zAltFile = sqlite3_mprintf("%s.%s", zFile, azEndings[ii]);
    if( zAltFile==0 ) return SQLITE_NOMEM;
    handle = sqlite3OsDlOpen(pVfs, zAltFile);
    sqlite3_free(zAltFile);
  }
#endif
  if( handle==0 ){
    if( pzErrMsg ){
      *pzErrMsg = zErrmsg = sqlite3_malloc64(nMsg);
      if( zErrmsg ){
        sqlite3_snprintf(nMsg, zErrmsg,
            "unable to open shared library [%s]", zFile);
        sqlite3OsDlError(pVfs, nMsg-1, zErrmsg);
      }
    }
    return SQLITE_ERROR;
  }
  xInit = (int(*)(sqlite3*,char**,const sqlite3_api_routines*))
                   sqlite3OsDlSym(pVfs, handle, zEntry);

  /* If no entry point was specified and the default legacy
  ** entry point name "sqlite3_extension_init" was not found, then
  ** construct an entry point name "sqlite3_X_init" where the X is
  ** replaced by the lowercase value of every ASCII alphabetic
  ** character in the filename after the last "/" upto the first ".",
  ** and eliding the first three characters if they are "lib".
  ** Examples:
  **
  **    /usr/local/lib/libExample5.4.3.so ==>  sqlite3_example_init
  **    C:/lib/mathfuncs.dll              ==>  sqlite3_mathfuncs_init
  */
  if( xInit==0 && zProc==0 ){
    int iFile, iEntry, c;
    int ncFile = sqlite3Strlen30(zFile);
    zAltEntry = sqlite3_malloc64(ncFile+30);
    if( zAltEntry==0 ){
      sqlite3OsDlClose(pVfs, handle);
      return SQLITE_NOMEM;
    }
    memcpy(zAltEntry, "sqlite3_", 8);
    for(iFile=ncFile-1; iFile>=0 && zFile[iFile]!='/'; iFile--){}
    iFile++;
    if( sqlite3_strnicmp(zFile+iFile, "lib", 3)==0 ) iFile += 3;
    for(iEntry=8; (c = zFile[iFile])!=0 && c!='.'; iFile++){
      if( sqlite3Isalpha(c) ){
        zAltEntry[iEntry++] = (char)sqlite3UpperToLower[(unsigned)c];
      }
    }
    memcpy(zAltEntry+iEntry, "_init", 6);
    zEntry = zAltEntry;
    xInit = (int(*)(sqlite3*,char**,const sqlite3_api_routines*))
                     sqlite3OsDlSym(pVfs, handle, zEntry);
  }
  if( xInit==0 ){
    if( pzErrMsg ){
      nMsg += sqlite3Strlen30(zEntry);
      *pzErrMsg = zErrmsg = sqlite3_malloc64(nMsg);
      if( zErrmsg ){
        sqlite3_snprintf(nMsg, zErrmsg,
            "no entry point [%s] in shared library [%s]", zEntry, zFile);
        sqlite3OsDlError(pVfs, nMsg-1, zErrmsg);
      }
    }
    sqlite3OsDlClose(pVfs, handle);
    sqlite3_free(zAltEntry);
    return SQLITE_ERROR;
  }
  sqlite3_free(zAltEntry);
  if( xInit(db, &zErrmsg, &sqlite3Apis) ){
    if( pzErrMsg ){
      *pzErrMsg = sqlite3_mprintf("error during initialization: %s", zErrmsg);
    }
    sqlite3_free(zErrmsg);
    sqlite3OsDlClose(pVfs, handle);
    return SQLITE_ERROR;
  }

  /* Append the new shared library handle to the db->aExtension array. */
  aHandle = sqlite3DbMallocZero(db, sizeof(handle)*(db->nExtension+1));
  if( aHandle==0 ){
    return SQLITE_NOMEM;
  }
  if( db->nExtension>0 ){
    memcpy(aHandle, db->aExtension, sizeof(handle)*db->nExtension);
  }
  sqlite3DbFree(db, db->aExtension);
  db->aExtension = aHandle;

  db->aExtension[db->nExtension++] = handle;
  return SQLITE_OK;
}

/*
** Call this routine when the database connection is closing in order
** to clean up loaded extensions
*/
void sqlite3CloseExtensions(sqlite3 *db){
  int i;
  assert( sqlite3_mutex_held(db->mutex) );
  for(i=0; i<db->nExtension; i++){
    sqlite3OsDlClose(db->pVfs, db->aExtension[i]);
  }
  sqlite3DbFree(db, db->aExtension);
}

int get_sqlite3JournalSize(){
	return sqlite3_vfs_find(0)->szOsFile;
}

int getMxPathName(){
	return sqlite3_vfs_find(0)->mxPathname;
}