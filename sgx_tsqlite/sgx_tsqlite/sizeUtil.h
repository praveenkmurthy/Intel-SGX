

#ifndef SIZE_UTIL_H
#define SIZE_UTIL_H

#include "sqlite3.h"
#include "sqliteInt.h"

size_t getIncrMergerSize(const void* val);
size_t getSortSubtaskSize(const void* val);
size_t getPmaReaderSize(const void* val);
size_t getSqlite3Size(const void* val);
size_t getSqlite3fileSize(const sqlite3_file ** val);
size_t getSQLiteThreadSize(const SQLiteThread ** val);

#endif