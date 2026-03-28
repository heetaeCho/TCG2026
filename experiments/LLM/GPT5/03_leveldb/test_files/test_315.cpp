// File: db_impl_get_approx_sizes_test.cc
#include <gtest/gtest.h>
#include <leveldb/db.h>
#include <leveldb/options.h>
#include <leveldb/slice.h>

#include <cstdint>
#include <filesystem>
#include <memory>
#include <string>
#include <vector>

using leveldb::DB;
using leveldb::Options;
using leveldb::Range;
using leveldb::Slice;
using leveldb::Status;
using leveldb::WriteOptions;

namespace {

std::string MakeTempDir(const std::string& suffix) {
  auto base = std::filesystem::temp_directory_path();
  auto path = base / ("ldb_sizes_" + suffix + "_" + std::to_string(::getpid()));
  std::filesystem::create_directories(path);
  return path.string();
}

class DBApproxSizesTest_315 : public ::testing::Test {
protected:
  void SetUp() override {
    dbpath_ = MakeTempDir("315");
    Options options;
    options.create_if_missing = true;
    Status s = DB::Open(options, dbpath_, &db_);
    ASSERT_TRUE(s.ok()) << s.ToString();
  }

  void TearDown() override {
    delete db_;
    Options options;
    leveldb::DestroyDB(dbpath_, options);
    std::error_code ec;
    std::filesystem::remove_all(dbpath_, ec);
  }

  void FillKeys(size_t n, size_t value_bytes) {
    std::string value(value_bytes, 'x');
    WriteOptions wopt;
    for (size_t i = 0; i < n; ++i) {
      char keybuf[16];
      std::snprintf(keybuf, sizeof(keybuf), "a%03zu", i);
      ASSERT_TRUE(db_->Put(wopt, keybuf, value).ok());
    }
    // Force data to be flushed/organized to files so approximate sizes are meaningful.
    db_->CompactRange(/*begin=*/nullptr, /*end=*/nullptr);
  }

  DB* db_ = nullptr;
  std::string dbpath_;
};

} // namespace

// Empty DB → reported size is 0 for any range
TEST_F(DBApproxSizesTest_315, EmptyDatabaseReturnsZero_315) {
  Range r(Slice("a000"), Slice("a999"));
  uint64_t sz = 1;  // sentinel
  db_->GetApproximateSizes(&r, 1, &sz);
  EXPECT_EQ(sz, 0u);
}

// start == limit → size is 0 (empty range)
TEST_F(DBApproxSizesTest_315, EmptyRangeIsZero_315) {
  FillKeys(/*n=*/300, /*value_bytes=*/100);
  Range r(Slice("a150"), Slice("a150"));
  uint64_t sz = 12345;
  db_->GetApproximateSizes(&r, 1, &sz);
  EXPECT_EQ(sz, 0u);
}

// limit offset < start offset (reversed logical order) → size clamped to 0
TEST_F(DBApproxSizesTest_315, ReversedRangeClampedToZero_315) {
  FillKeys(/*n=*/400, /*value_bytes=*/120);
  Range r(Slice("a300"), Slice("a100"));
  uint64_t sz = 777;
  db_->GetApproximateSizes(&r, 1, &sz);
  EXPECT_EQ(sz, 0u);
}

// Wider range should report size >= inner subrange
TEST_F(DBApproxSizesTest_315, WiderRangeReportsAtLeastAsLarge_315) {
  FillKeys(/*n=*/600, /*value_bytes=*/128);

  Range inner(Slice("a200"), Slice("a300"));     // ~100 keys
  Range outer(Slice("a150"), Slice("a350"));     // strictly wider

  uint64_t sizes[2] = {0, 0};
  Range rs[2] = {inner, outer};
  db_->GetApproximateSizes(rs, 2, sizes);

  // Non-negative
  EXPECT_GE(sizes[0], 0u);
  EXPECT_GE(sizes[1], 0u);
  // Monotonic w.r.t. containment
  EXPECT_LE(sizes[0], sizes[1]);
}

// Multiple ranges are computed independently and populate all outputs
TEST_F(DBApproxSizesTest_315, PopulatesAllRangesIndependently_315) {
  FillKeys(/*n=*/800, /*value_bytes=*/90);

  Range ranges[3] = {
      Range(Slice("a000"), Slice("a100")),
      Range(Slice("a300"), Slice("a500")),
      Range(Slice("a700"), Slice("a799")),
  };
  uint64_t sizes[3] = {0, 0, 0};
  db_->GetApproximateSizes(ranges, 3, sizes);

  // All filled with some value (possibly 0 if extremely tiny, but should be >= 0)
  for (int i = 0; i < 3; ++i) {
    EXPECT_GE(sizes[i], 0u) << "range index " << i << " not populated";
  }

  // Disjoint ranges typically yield different (non-equal) sizes; allow equality but check not all identical.
  bool all_equal = (sizes[0] == sizes[1]) && (sizes[1] == sizes[2]);
  EXPECT_FALSE(all_equal) << "All sizes identical; expected per‑range independence.";
}

// n == 0 must be a no-op and safe even if sizes == nullptr
TEST_F(DBApproxSizesTest_315, ZeroCountIsNoOpAndSafe_315) {
  FillKeys(/*n=*/50, /*value_bytes=*/64);
  db_->GetApproximateSizes(/*range=*/nullptr, /*n=*/0, /*sizes=*/nullptr);
  SUCCEED();  // Reaching here without crash is the observable guarantee
}
