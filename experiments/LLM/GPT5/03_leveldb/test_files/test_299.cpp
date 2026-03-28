// File: db/table_cache_size_test_299.cc

#include "gtest/gtest.h"
#include "leveldb/options.h"

// Include the .cc so the internal-static symbol is available in this TU.
#include "db/db_impl.cc"

namespace {

using leveldb::Options;
using leveldb::kNumNonTableCacheFiles;

class TableCacheSizeTest_299 : public ::testing::Test {};

TEST_F(TableCacheSizeTest_299, DefaultOptions_299) {
  Options opt;  // uses library defaults
  // Observable behavior: returns max_open_files - kNumNonTableCacheFiles
  const int expected = opt.max_open_files - kNumNonTableCacheFiles;
  EXPECT_EQ(expected, leveldb::TableCacheSize(opt));
}

TEST_F(TableCacheSizeTest_299, ZeroWhenEqualThreshold_299) {
  Options opt;
  opt.max_open_files = kNumNonTableCacheFiles;  // boundary
  EXPECT_EQ(0, leveldb::TableCacheSize(opt));
}

TEST_F(TableCacheSizeTest_299, NegativeWhenBelowThreshold_299) {
  Options opt;
  opt.max_open_files = kNumNonTableCacheFiles - 5;  // below boundary
  EXPECT_EQ(-5, leveldb::TableCacheSize(opt));
}

TEST_F(TableCacheSizeTest_299, LargeValueDoesNotOverflow_299) {
  Options opt;
  opt.max_open_files = std::numeric_limits<int>::max();
  const int expected = std::numeric_limits<int>::max() - kNumNonTableCacheFiles;
  EXPECT_EQ(expected, leveldb::TableCacheSize(opt));
}

}  // namespace
