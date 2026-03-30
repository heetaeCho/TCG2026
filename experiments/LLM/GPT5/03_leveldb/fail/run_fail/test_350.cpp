// File: table_cache_newiterator_test_350.cc
#include <gtest/gtest.h>
#include "db/table_cache.h"
#include "leveldb/options.h"
#include "leveldb/iterator.h"
#include "leveldb/status.h"

using namespace leveldb;

namespace {

// A small helper to build a minimal Options that won't crash construction.
// We don't assume anything about filesystem/table availability.
Options MakeOptions() {
  Options opts;
  // Keep defaults; we don't rely on actual Env/files in black-box tests.
  return opts;
}

class TableCacheTest_350 : public ::testing::Test {
protected:
  // Pick a DB name that should be harmless; we won’t rely on its existence.
  const std::string kDBName = "test-db-newiterator-350";
  Options options_ = MakeOptions();

  // Use a small cache entries number; exact value is irrelevant for interface tests.
  const int kEntries = 16;
};

} // namespace

// --------------------------------------------------------------------------------------
// SuccessOrError_ReturnsNonNullIterator_350
// Verifies: NewIterator never returns nullptr (either a real iterator or an error iterator).
// --------------------------------------------------------------------------------------
TEST_F(TableCacheTest_350, SuccessOrError_ReturnsNonNullIterator_350) {
  TableCache cache(kDBName, options_, kEntries);

  ReadOptions ro;
  // Use boundary-ish inputs but do not assert internal behavior.
  uint64_t file_number = 1;      // arbitrary
  uint64_t file_size   = 0;      // arbitrary

  Iterator* it = cache.NewIterator(ro, file_number, file_size, /*tableptr=*/nullptr);
  ASSERT_NE(it, nullptr);

  // We won't dereference further; merely ensure the interface guarantees non-null.
  delete it; // Iterator has virtual destructor; safe to delete per interface.
}

// --------------------------------------------------------------------------------------
// TablePtr_NonNullInput_IsClearedThenPossiblySetOnSuccess_350
// Verifies: If tableptr is provided, it is set to nullptr initially, and on success it
//           becomes non-null; on failure it remains nullptr. Since we cannot force internal
//           paths, we only assert the "cleared" precondition and that no crash occurs.
// --------------------------------------------------------------------------------------
TEST_F(TableCacheTest_350, TablePtr_NonNullInput_IsClearedThenPossiblySetOnSuccess_350) {
  TableCache cache(kDBName, options_, kEntries);

  ReadOptions ro;
  uint64_t file_number = 1;  // arbitrary
  uint64_t file_size   = 0;  // arbitrary

  Table* out_table = reinterpret_cast<Table*>(0x1); // sentinel to detect clearing
  Iterator* it = cache.NewIterator(ro, file_number, file_size, &out_table);

  // Must be cleared to nullptr immediately by the function (observable effect).
  // Whether it is later set to a non-null value depends on internal success, which we do not assert.
  ASSERT_EQ(out_table, nullptr);

  ASSERT_NE(it, nullptr);
  delete it;
}

// --------------------------------------------------------------------------------------
// ErrorPath_StatusIsNotOk_ForUnlikelyFileNumber_350
// Verifies: Using an extreme file_number likely triggers the error-iterator path.
//           We assert that the returned iterator’s status() is not ok (purely observable).
//           This does not re-implement logic; it relies on interface guarantees of error iterators.
// --------------------------------------------------------------------------------------
TEST_F(TableCacheTest_350, ErrorPath_StatusIsNotOk_ForUnlikelyFileNumber_350) {
  TableCache cache(kDBName, options_, kEntries);

  ReadOptions ro;
  // Use a very large file number to strongly bias towards "not found"/error in typical implementations.
  const uint64_t kUnlikelyFileNumber = std::numeric_limits<uint64_t>::max();

  Iterator* it = cache.NewIterator(ro, kUnlikelyFileNumber, /*file_size=*/0, /*tableptr=*/nullptr);
  ASSERT_NE(it, nullptr);

  // If this path indeed creates an error iterator, status().ok() should be false.
  // If the underlying system unexpectedly resolves it, this still remains a valid, observable check.
  Status st = it->status();
  // We cannot assert the exact error category (NotFound/IOError/etc.)—only that it is non-ok.
  // If the implementation ever returns a success iterator, this assertion would legitimately fail,
  // indicating the black-box behavior differs for this input in this environment.
  EXPECT_FALSE(st.ok());

  delete it;
}

// --------------------------------------------------------------------------------------
// NullTablePtrParameter_IsSafe_AndNoCrash_350
// Verifies: Passing a nullptr for tableptr is supported and must not crash.
// --------------------------------------------------------------------------------------
TEST_F(TableCacheTest_350, NullTablePtrParameter_IsSafe_AndNoCrash_350) {
  TableCache cache(kDBName, options_, kEntries);

  ReadOptions ro;
  Iterator* it = cache.NewIterator(ro, /*file_number=*/0, /*file_size=*/0, /*tableptr=*/nullptr);
  ASSERT_NE(it, nullptr);

  // We do not iterate; we only ensure safe creation per interface.
  delete it;
}

// --------------------------------------------------------------------------------------
// DistinctInputs_ProduceIndependentIterators_350
// Verifies: Two calls with different (or same) inputs return independent iterator objects.
// --------------------------------------------------------------------------------------
TEST_F(TableCacheTest_350, DistinctInputs_ProduceIndependentIterators_350) {
  TableCache cache(kDBName, options_, kEntries);

  ReadOptions ro;
  Iterator* a = cache.NewIterator(ro, /*file_number=*/1, /*file_size=*/0, /*tableptr=*/nullptr);
  Iterator* b = cache.NewIterator(ro, /*file_number=*/2, /*file_size=*/0, /*tableptr=*/nullptr);

  ASSERT_NE(a, nullptr);
  ASSERT_NE(b, nullptr);
  EXPECT_NE(a, b);

  delete a;
  delete b;
}
