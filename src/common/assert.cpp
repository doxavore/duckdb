#include "duckdb/common/assert.hpp"
#include "duckdb/common/exception.hpp"

#include <cstdio>

namespace duckdb {

void DuckDBAssertInternal(bool condition, const char *condition_name, const char *file, int linenr) {
#ifdef DISABLE_ASSERTIONS
	return;
#endif
	if (condition) {
		return;
	}
	throw InternalException("Assertion triggered in file \"%s\" on line %d: %s", file, linenr, condition_name);
}

void DuckDBAssertLogInternal(bool condition, const char *condition_name, const char *file, int linenr) {
#ifdef DISABLE_ASSERTIONS
	return;
#endif
	if (condition) {
		return;
	}
	fprintf(stderr, "DUCKDB_LOG_ASSERT: file \"%s\" line %d: %s\n", file, linenr, condition_name);
	fflush(stderr);
}

} // namespace duckdb
