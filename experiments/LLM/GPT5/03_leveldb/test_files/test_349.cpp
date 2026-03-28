// table_cache_test_349.cc
#include "db/table_cache.h"

#include <gtest/gtest.h>
#include <type_traits>

namespace leveldb {

class TableCacheTest_349 : public ::testing::Test {};

// [Smoke] Construct and destroy without throwing/crashing.
// This exercises the public ctor/dtor contract without assuming internals.
TEST_F(TableCacheTest_349, ConstructAndDestroy_Smoke_349) {
  Options options;
  // Use default env and a small cache size; values are arbitrary but valid.
  const std::string dbname = "test-db-for-construct-destroy";
  const int entries = 4;

  // Scope ensures destructor runs at the end of this block.
  {
    TableCache cache(dbname, options, entries);
    (void)cache;  // silence unused warning; presence is enough for this smoke test
  }
  SUCCEED();  // If we get here, construction/destruction completed normally.
}

// [API Contract] Class is explicitly non-copyable per interface (deleted copy ctor).
TEST_F(TableCacheTest_349, IsNotCopyConstructible_349) {
  static_assert(!std::is_copy_constructible<TableCache>::value,
                "TableCache must not be copy-constructible");
  SUCCEED();
}

// [API Contract] Class is explicitly non-assignable per interface (deleted operator=).
TEST_F(TableCacheTest_349, IsNotCopyAssignable_349) {
  static_assert(!std::is_copy_assignable<TableCache>::value,
                "TableCache must not be copy-assignable");
  SUCCEED();
}

}  // namespace leveldb
