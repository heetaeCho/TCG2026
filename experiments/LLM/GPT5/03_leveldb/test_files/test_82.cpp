// File: compaction_input_test_82.cc
#include <gtest/gtest.h>
#include "db/version_set.h"  // contains leveldb::Compaction declaration

// ----- Test-only forward declaration -----
// This must be provided by your test support (or you can swap with a real factory
// that yields a Compaction with the given inputs populated).
// The helper must:
//  - Create a Compaction instance
//  - Populate inputs_[0] with pointers from 'level0_inputs' (in given order)
//  - Populate inputs_[1] with pointers from 'level1_inputs' (in given order)
//  - Return a valid Compaction* whose lifetime outlives the test (caller will delete)
namespace leveldb {
struct FileMetaData;  // forward; real type comes from your codebase

Compaction* MakeCompactionWithInputs_ForTest(
    const std::vector<FileMetaData*>& level0_inputs,
    const std::vector<FileMetaData*>& level1_inputs);

// Optional: a convenience to destroy Compaction if your factory requires custom cleanup.
void DestroyCompaction_ForTest(Compaction* c);
}  // namespace leveldb

namespace {

using leveldb::Compaction;
using leveldb::FileMetaData;

// A tiny holder so we can fabricate distinct, stable pointers to FileMetaData.
// We don't rely on any FileMetaData internals; we only need addresses.
struct DummyFile {
  // Match production layout loosely: we do not read any fields.
  FileMetaData* ptr;
  DummyFile() : ptr(reinterpret_cast<FileMetaData*>(this)) {}
};

// ---------- Fixture ----------
class CompactionInputTest_82 : public ::testing::Test {
 protected:
  // Utility to create N dummy FileMetaData pointers.
  static std::vector<FileMetaData*> MakeDummyPtrs(size_t n, std::vector<std::unique_ptr<DummyFile>>& storage) {
    storage.clear();
    storage.reserve(n);
    std::vector<FileMetaData*> out;
    out.reserve(n);
    for (size_t i = 0; i < n; ++i) {
      auto df = std::make_unique<DummyFile>();
      out.push_back(df->ptr);
      storage.push_back(std::move(df));
    }
    return out;
  }

  // Keeps ownership of dummy objects so pointers stay valid.
  std::vector<std::unique_ptr<DummyFile>> keep0_;
  std::vector<std::unique_ptr<DummyFile>> keep1_;
};

// ---------- Tests ----------

// Normal operation: returns the exact pointer stored at [which][i]
TEST_F(CompactionInputTest_82, ReturnsExactPointer_Level0_Ordering_82) {
  auto l0 = MakeDummyPtrs(3, keep0_);  // pointers A,B,C
  auto l1 = MakeDummyPtrs(0, keep1_);

  Compaction* c = leveldb::MakeCompactionWithInputs_ForTest(l0, l1);
  ASSERT_NE(c, nullptr);

  // Access within bounds should return identical pointers and preserve order.
  EXPECT_EQ(c->input(0, 0), l0[0]);
  EXPECT_EQ(c->input(0, 1), l0[1]);
  EXPECT_EQ(c->input(0, 2), l0[2]);

  leveldb::DestroyCompaction_ForTest(c);
}

// Normal operation: second which index works independently
TEST_F(CompactionInputTest_82, ReturnsExactPointer_Level1_Ordering_82) {
  auto l0 = MakeDummyPtrs(0, keep0_);
  auto l1 = MakeDummyPtrs(2, keep1_);  // pointers D,E

  Compaction* c = leveldb::MakeCompactionWithInputs_ForTest(l0, l1);
  ASSERT_NE(c, nullptr);

  EXPECT_EQ(c->input(1, 0), l1[0]);
  EXPECT_EQ(c->input(1, 1), l1[1]);

  leveldb::DestroyCompaction_ForTest(c);
}

// Boundary: last valid index returns the stored pointer
TEST_F(CompactionInputTest_82, ReturnsPointer_AtLastValidIndex_82) {
  auto l0 = MakeDummyPtrs(1, keep0_);
  auto l1 = MakeDummyPtrs(4, keep1_);

  Compaction* c = leveldb::MakeCompactionWithInputs_ForTest(l0, l1);
  ASSERT_NE(c, nullptr);

  // Last elements
  EXPECT_EQ(c->input(0, 0), l0[0]);
  EXPECT_EQ(c->input(1, 3), l1[3]);

  leveldb::DestroyCompaction_ForTest(c);
}

// Boundary/Exceptional (observable): when a level has zero inputs, we do not call input()
// This test documents the expectation that callers should not index empty levels.
TEST_F(CompactionInputTest_82, NoAccessWhenLevelHasZeroInputs_82) {
  auto l0 = MakeDummyPtrs(0, keep0_);
  auto l1 = MakeDummyPtrs(0, keep1_);
  Compaction* c = leveldb::MakeCompactionWithInputs_ForTest(l0, l1);
  ASSERT_NE(c, nullptr);

  // There is nothing to access; this test simply ensures construction succeeds.
  // If your codebase defines behavior for out-of-range (e.g., CHECK/ASSERT),
  // add a death test in DEBUG builds, e.g.:
  // EXPECT_DEATH({ (void)c->input(0, 0); }, ".*");
  // EXPECT_DEATH({ (void)c->input(1, 0); }, ".*");

  leveldb::DestroyCompaction_ForTest(c);
}

// Defensive boundary: verify independence between which=0 and which=1 (no cross-contamination)
TEST_F(CompactionInputTest_82, IndependentLevels_DoNotAlias_82) {
  auto l0 = MakeDummyPtrs(2, keep0_);  // A,B
  auto l1 = MakeDummyPtrs(2, keep1_);  // C,D

  Compaction* c = leveldb::MakeCompactionWithInputs_ForTest(l0, l1);
  ASSERT_NE(c, nullptr);

  EXPECT_EQ(c->input(0, 0), l0[0]);
  EXPECT_EQ(c->input(0, 1), l0[1]);
  EXPECT_EQ(c->input(1, 0), l1[0]);
  EXPECT_EQ(c->input(1, 1), l1[1]);

  // Sanity: ensure no accidental alias between levels for the same index
  EXPECT_NE(c->input(0, 0), c->input(1, 0));
  EXPECT_NE(c->input(0, 1), c->input(1, 1));

  leveldb::DestroyCompaction_ForTest(c);
}

}  // namespace
