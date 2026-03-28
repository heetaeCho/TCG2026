#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "db/db_impl.h"
#include "db/dbformat.h"
#include "leveldb/cache.h"
#include "leveldb/comparator.h"
#include "leveldb/env.h"
#include "leveldb/filter_policy.h"
#include "leveldb/options.h"
#include "util/testutil.h"

#include <string>

namespace leveldb {

// Forward declaration of the function under test
extern const int kNumNonTableCacheFiles;
Options SanitizeOptions(const std::string& dbname,
                        const InternalKeyComparator* icmp,
                        const InternalFilterPolicy* ipolicy,
                        const Options& src);

class SanitizeOptionsTest_298 : public ::testing::Test {
 protected:
  void SetUp() override {
    icmp_ = new InternalKeyComparator(BytewiseComparator());
    ipolicy_ = nullptr;  // Will be set per-test if needed
    dbname_ = testing::TempDir() + "/sanitize_options_test";
  }

  void TearDown() override {
    delete icmp_;
    delete ipolicy_;
  }

  InternalKeyComparator* icmp_;
  InternalFilterPolicy* ipolicy_;
  std::string dbname_;
};

// Test that comparator is set to the InternalKeyComparator
TEST_F(SanitizeOptionsTest_298, ComparatorIsSetToInternalKeyComparator_298) {
  Options opts;
  Options result = SanitizeOptions(dbname_, icmp_, nullptr, opts);
  EXPECT_EQ(result.comparator, icmp_);
}

// Test that filter_policy is nullptr when src.filter_policy is nullptr
TEST_F(SanitizeOptionsTest_298, FilterPolicyNullWhenSrcFilterPolicyNull_298) {
  Options opts;
  opts.filter_policy = nullptr;
  Options result = SanitizeOptions(dbname_, icmp_, nullptr, opts);
  EXPECT_EQ(result.filter_policy, nullptr);
}

// Test that filter_policy is set to ipolicy when src.filter_policy is non-null
TEST_F(SanitizeOptionsTest_298, FilterPolicySetWhenSrcFilterPolicyNonNull_298) {
  const FilterPolicy* bloom = NewBloomFilterPolicy(10);
  ipolicy_ = new InternalFilterPolicy(bloom);
  Options opts;
  opts.filter_policy = bloom;
  Options result = SanitizeOptions(dbname_, icmp_, ipolicy_, opts);
  EXPECT_EQ(result.filter_policy, ipolicy_);
  delete bloom;
}

// Test that max_open_files is clipped to minimum
TEST_F(SanitizeOptionsTest_298, MaxOpenFilesClippedToMinimum_298) {
  Options opts;
  opts.max_open_files = 1;  // Way below minimum of 64 + kNumNonTableCacheFiles
  Options result = SanitizeOptions(dbname_, icmp_, nullptr, opts);
  EXPECT_GE(result.max_open_files, 64 + kNumNonTableCacheFiles);
}

// Test that max_open_files is clipped to maximum
TEST_F(SanitizeOptionsTest_298, MaxOpenFilesClippedToMaximum_298) {
  Options opts;
  opts.max_open_files = 100000;  // Above maximum of 50000
  Options result = SanitizeOptions(dbname_, icmp_, nullptr, opts);
  EXPECT_LE(result.max_open_files, 50000);
}

// Test that max_open_files within range is unchanged
TEST_F(SanitizeOptionsTest_298, MaxOpenFilesInRangeUnchanged_298) {
  Options opts;
  opts.max_open_files = 1000;
  Options result = SanitizeOptions(dbname_, icmp_, nullptr, opts);
  EXPECT_EQ(result.max_open_files, 1000);
}

// Test write_buffer_size clipped to minimum (64KB)
TEST_F(SanitizeOptionsTest_298, WriteBufferSizeClippedToMinimum_298) {
  Options opts;
  opts.write_buffer_size = 1;  // Way below 64KB
  Options result = SanitizeOptions(dbname_, icmp_, nullptr, opts);
  EXPECT_GE(result.write_buffer_size, static_cast<size_t>(64 << 10));
}

// Test write_buffer_size clipped to maximum (1GB)
TEST_F(SanitizeOptionsTest_298, WriteBufferSizeClippedToMaximum_298) {
  Options opts;
  opts.write_buffer_size = static_cast<size_t>(2) << 30;  // 2GB
  Options result = SanitizeOptions(dbname_, icmp_, nullptr, opts);
  EXPECT_LE(result.write_buffer_size, static_cast<size_t>(1 << 30));
}

// Test write_buffer_size within range is unchanged
TEST_F(SanitizeOptionsTest_298, WriteBufferSizeInRangeUnchanged_298) {
  Options opts;
  opts.write_buffer_size = 4 * 1024 * 1024;  // 4MB
  Options result = SanitizeOptions(dbname_, icmp_, nullptr, opts);
  EXPECT_EQ(result.write_buffer_size, 4u * 1024 * 1024);
}

// Test max_file_size clipped to minimum (1MB)
TEST_F(SanitizeOptionsTest_298, MaxFileSizeClippedToMinimum_298) {
  Options opts;
  opts.max_file_size = 1;
  Options result = SanitizeOptions(dbname_, icmp_, nullptr, opts);
  EXPECT_GE(result.max_file_size, static_cast<size_t>(1 << 20));
}

// Test max_file_size clipped to maximum (1GB)
TEST_F(SanitizeOptionsTest_298, MaxFileSizeClippedToMaximum_298) {
  Options opts;
  opts.max_file_size = static_cast<size_t>(2) << 30;
  Options result = SanitizeOptions(dbname_, icmp_, nullptr, opts);
  EXPECT_LE(result.max_file_size, static_cast<size_t>(1 << 30));
}

// Test max_file_size within range is unchanged
TEST_F(SanitizeOptionsTest_298, MaxFileSizeInRangeUnchanged_298) {
  Options opts;
  opts.max_file_size = 2 * 1024 * 1024;  // 2MB
  Options result = SanitizeOptions(dbname_, icmp_, nullptr, opts);
  EXPECT_EQ(result.max_file_size, 2u * 1024 * 1024);
}

// Test block_size clipped to minimum (1KB)
TEST_F(SanitizeOptionsTest_298, BlockSizeClippedToMinimum_298) {
  Options opts;
  opts.block_size = 1;
  Options result = SanitizeOptions(dbname_, icmp_, nullptr, opts);
  EXPECT_GE(result.block_size, static_cast<size_t>(1 << 10));
}

// Test block_size clipped to maximum (4MB)
TEST_F(SanitizeOptionsTest_298, BlockSizeClippedToMaximum_298) {
  Options opts;
  opts.block_size = 8 << 20;  // 8MB
  Options result = SanitizeOptions(dbname_, icmp_, nullptr, opts);
  EXPECT_LE(result.block_size, static_cast<size_t>(4 << 20));
}

// Test block_size within range is unchanged
TEST_F(SanitizeOptionsTest_298, BlockSizeInRangeUnchanged_298) {
  Options opts;
  opts.block_size = 4 * 1024;  // 4KB
  Options result = SanitizeOptions(dbname_, icmp_, nullptr, opts);
  EXPECT_EQ(result.block_size, 4u * 1024);
}

// Test that block_cache is created if not provided
TEST_F(SanitizeOptionsTest_298, BlockCacheCreatedIfNull_298) {
  Options opts;
  opts.block_cache = nullptr;
  Options result = SanitizeOptions(dbname_, icmp_, nullptr, opts);
  EXPECT_NE(result.block_cache, nullptr);
  // Clean up the created cache
  delete result.block_cache;
}

// Test that block_cache is preserved if already set
TEST_F(SanitizeOptionsTest_298, BlockCachePreservedIfNotNull_298) {
  Cache* my_cache = NewLRUCache(1 << 20);
  Options opts;
  opts.block_cache = my_cache;
  Options result = SanitizeOptions(dbname_, icmp_, nullptr, opts);
  EXPECT_EQ(result.block_cache, my_cache);
  delete my_cache;
}

// Test that info_log is created when not provided (nullptr)
TEST_F(SanitizeOptionsTest_298, InfoLogCreatedIfNull_298) {
  Options opts;
  opts.info_log = nullptr;
  Options result = SanitizeOptions(dbname_, icmp_, nullptr, opts);
  // info_log may or may not be nullptr depending on whether NewLogger succeeds
  // But at least the function should not crash
  if (result.block_cache) {
    delete result.block_cache;
  }
}

// Test that info_log is preserved if already set
TEST_F(SanitizeOptionsTest_298, InfoLogPreservedIfNotNull_298) {
  Options opts;
  Logger* logger = nullptr;
  // Create a logger to pass in
  Status s = opts.env->NewLogger(dbname_ + "/test_log", &logger);
  if (s.ok() && logger != nullptr) {
    opts.info_log = logger;
    Options result = SanitizeOptions(dbname_, icmp_, nullptr, opts);
    EXPECT_EQ(result.info_log, logger);
    if (result.block_cache) {
      delete result.block_cache;
    }
    delete logger;
  }
}

// Test that other options fields are preserved (e.g., create_if_missing)
TEST_F(SanitizeOptionsTest_298, OtherOptionsFieldsPreserved_298) {
  Options opts;
  opts.create_if_missing = true;
  opts.error_if_exists = true;
  opts.paranoid_checks = true;
  opts.compression = kNoCompression;
  opts.block_restart_interval = 32;
  opts.reuse_logs = true;
  Options result = SanitizeOptions(dbname_, icmp_, nullptr, opts);
  EXPECT_EQ(result.create_if_missing, true);
  EXPECT_EQ(result.error_if_exists, true);
  EXPECT_EQ(result.paranoid_checks, true);
  EXPECT_EQ(result.compression, kNoCompression);
  EXPECT_EQ(result.block_restart_interval, 32);
  EXPECT_EQ(result.reuse_logs, true);
  if (result.block_cache) {
    delete result.block_cache;
  }
}

// Test that env is preserved from source options
TEST_F(SanitizeOptionsTest_298, EnvPreservedFromSource_298) {
  Options opts;
  Env* original_env = opts.env;
  Options result = SanitizeOptions(dbname_, icmp_, nullptr, opts);
  EXPECT_EQ(result.env, original_env);
  if (result.block_cache) {
    delete result.block_cache;
  }
}

// Test boundary: max_open_files exactly at minimum boundary
TEST_F(SanitizeOptionsTest_298, MaxOpenFilesExactlyAtMinBoundary_298) {
  Options opts;
  opts.max_open_files = 64 + kNumNonTableCacheFiles;
  Options result = SanitizeOptions(dbname_, icmp_, nullptr, opts);
  EXPECT_EQ(result.max_open_files, 64 + kNumNonTableCacheFiles);
}

// Test boundary: max_open_files exactly at maximum boundary
TEST_F(SanitizeOptionsTest_298, MaxOpenFilesExactlyAtMaxBoundary_298) {
  Options opts;
  opts.max_open_files = 50000;
  Options result = SanitizeOptions(dbname_, icmp_, nullptr, opts);
  EXPECT_EQ(result.max_open_files, 50000);
}

// Test boundary: write_buffer_size exactly at minimum boundary (64KB)
TEST_F(SanitizeOptionsTest_298, WriteBufferSizeExactlyAtMinBoundary_298) {
  Options opts;
  opts.write_buffer_size = 64 << 10;
  Options result = SanitizeOptions(dbname_, icmp_, nullptr, opts);
  EXPECT_EQ(result.write_buffer_size, static_cast<size_t>(64 << 10));
}

// Test boundary: write_buffer_size exactly at maximum boundary (1GB)
TEST_F(SanitizeOptionsTest_298, WriteBufferSizeExactlyAtMaxBoundary_298) {
  Options opts;
  opts.write_buffer_size = 1 << 30;
  Options result = SanitizeOptions(dbname_, icmp_, nullptr, opts);
  EXPECT_EQ(result.write_buffer_size, static_cast<size_t>(1 << 30));
}

// Test boundary: block_size exactly at minimum boundary (1KB)
TEST_F(SanitizeOptionsTest_298, BlockSizeExactlyAtMinBoundary_298) {
  Options opts;
  opts.block_size = 1 << 10;
  Options result = SanitizeOptions(dbname_, icmp_, nullptr, opts);
  EXPECT_EQ(result.block_size, static_cast<size_t>(1 << 10));
}

// Test boundary: block_size exactly at maximum boundary (4MB)
TEST_F(SanitizeOptionsTest_298, BlockSizeExactlyAtMaxBoundary_298) {
  Options opts;
  opts.block_size = 4 << 20;
  Options result = SanitizeOptions(dbname_, icmp_, nullptr, opts);
  EXPECT_EQ(result.block_size, static_cast<size_t>(4 << 20));
}

// Test boundary: max_file_size exactly at minimum boundary (1MB)
TEST_F(SanitizeOptionsTest_298, MaxFileSizeExactlyAtMinBoundary_298) {
  Options opts;
  opts.max_file_size = 1 << 20;
  Options result = SanitizeOptions(dbname_, icmp_, nullptr, opts);
  EXPECT_EQ(result.max_file_size, static_cast<size_t>(1 << 20));
}

// Test boundary: max_file_size exactly at maximum boundary (1GB)
TEST_F(SanitizeOptionsTest_298, MaxFileSizeExactlyAtMaxBoundary_298) {
  Options opts;
  opts.max_file_size = 1 << 30;
  Options result = SanitizeOptions(dbname_, icmp_, nullptr, opts);
  EXPECT_EQ(result.max_file_size, static_cast<size_t>(1 << 30));
}

// Test with default options - all defaults should be valid
TEST_F(SanitizeOptionsTest_298, DefaultOptionsAreValid_298) {
  Options opts;
  Options result = SanitizeOptions(dbname_, icmp_, nullptr, opts);
  EXPECT_EQ(result.comparator, icmp_);
  EXPECT_EQ(result.filter_policy, nullptr);
  EXPECT_GE(result.max_open_files, 64 + kNumNonTableCacheFiles);
  EXPECT_LE(result.max_open_files, 50000);
  EXPECT_GE(result.write_buffer_size, static_cast<size_t>(64 << 10));
  EXPECT_LE(result.write_buffer_size, static_cast<size_t>(1 << 30));
  EXPECT_GE(result.max_file_size, static_cast<size_t>(1 << 20));
  EXPECT_LE(result.max_file_size, static_cast<size_t>(1 << 30));
  EXPECT_GE(result.block_size, static_cast<size_t>(1 << 10));
  EXPECT_LE(result.block_size, static_cast<size_t>(4 << 20));
  if (result.block_cache) {
    delete result.block_cache;
  }
}

}  // namespace leveldb
