//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/assert.hpp
//
//
//===----------------------------------------------------------------------===//

#include "duckdb/common/winapi.hpp"

#pragma once

namespace duckdb {
DUCKDB_API void DuckDBAssertInternal(bool condition, const char *condition_name, const char *file, int linenr);
DUCKDB_API void DuckDBAssertLogInternal(bool condition, const char *condition_name, const char *file, int linenr);
}

#if defined(DUCKDB_LOG_ASSERT)

//! Evaluate assertions and log failures without changing release-mode control flow.
//! D_ASSERT_IS_ENABLED is intentionally not defined, keeping additional debug-only verification disabled.
#define D_ASSERT(condition) duckdb::DuckDBAssertLogInternal(bool(condition), #condition, __FILE__, __LINE__)

#else

// clang-format off
#if ( \
    /* Not a debug build */ \
    !defined(DEBUG) && \
    /* FORCE_ASSERT is not set (enables assertions even on release mode when set to true) */ \
    !defined(DUCKDB_FORCE_ASSERT) && \
    /* The project is not compiled for Microsoft Visual Studio */ \
    !defined(__MVS__) \
)
// clang-format on

//! On most builds, NDEBUG is defined, turning the assert call into a NO-OP
//! Only the 'else' condition is supposed to check the assertions
#include <assert.h>
#define D_ASSERT assert

#else

#define D_ASSERT(condition) duckdb::DuckDBAssertInternal(bool(condition), #condition, __FILE__, __LINE__)
#define D_ASSERT_IS_ENABLED

#endif
#endif

//! Force assertion implementation, which always asserts whatever build type is used.
#define ALWAYS_ASSERT(condition) duckdb::DuckDBAssertInternal(bool(condition), #condition, __FILE__, __LINE__)
