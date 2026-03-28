// File: version_get_overlapping_inputs_test_155.cc
#include <gtest/gtest.h>
#include <vector>
#include <string>

// Make private members visible ONLY for setting up the fixture.
// We do not assert on private state; we only prepare inputs to call a public method.
#define private public
#include "db/version_set.h"
#include "db/version_edit.h"
#include "db/dbformat.h"
#include "leveldb/comparator.h"
#include "leveldb/slice.h"
#undef private

using namespace leveldb;

namespace {

// Simple user comparator: lexicographic on Slice
class LexicographicComparator : public Comparator {
 public:
  ~LexicographicComparator() override = default;
  int Compare(const Slice& a, const Slice& b) const override {
    return a.compare(b);
  }
  const char* Name() const override { return "test.LexicographicComparator"; }
  void FindShortestSeparator(std::string*, const Slice&) const override {}
  void FindShortSuccessor(std::string*) const override {}
};

// Minimal stand-in for VersionSet storage needed by Version::GetOverlappingInputs
// Only contains an InternalKeyComparator so vset_->icmp_.user_comparator() works.
struct FakeVS {
  explicit FakeVS(const Comparator* c) : icmp_(c) {}
  InternalKeyComparator icmp_;
};

// Helper to create a FileMetaData with default smallest/largest keys.
// We avoid depending on InternalKey encoding details; default-constructed
// InternalKey yields empty user_key(), which is fine for open-range tests.
static FileMetaData* MakeFile(uint64_t number, uint64_t size = 0) {
  auto* f = new FileMetaData();
  f->number = number;
  f->file_size = size;
  // f->smallest and f->largest remain default; user_key() will be empty
  return f;
}

// Fixture that owns Version and the fake VersionSet backing comparator.
class GetOverlappingInputsTest_155 : public ::testing::Test {
 protected:
  GetOverlappingInputsTest_155()
      : user_cmp_(),
        fake_vs_(&user_cmp_),
        version_(/*vset*/ reinterpret_cast<VersionSet*>(&fake_vs_)) {
    // Wire Version to our FakeVS. (Constructor took the pointer already.)
    version_.vset_ = reinterpret_cast<VersionSet*>(&fake_vs_);
  }

  ~GetOverlappingInputsTest_155() override {
    // Clean up allocated FileMetaData pointers we added to levels
    for (int lvl = 0; lvl < config::kNumLevels; ++lvl) {
      for (auto* f : version_.files_[lvl]) delete f;
      version_.files_[lvl].clear();
    }
  }

  // Convenience: add a file to a level
  void AddFile(int level, uint64_t number, uint64_t size = 0) {
    version_.files_[level].push_back(MakeFile(number, size));
  }

  LexicographicComparator user_cmp_;
  FakeVS fake_vs_;
  Version version_;
};

}  // namespace

// ---------------------- Tests ----------------------

// Ensures the method clears 'inputs' (observable) even when there are no files.
TEST_F(GetOverlappingInputsTest_155, ClearsOutputVectorWhenNoFiles_155) {
  std::vector<FileMetaData*> inputs;
  // Pre-fill to verify it gets cleared
  inputs.push_back(reinterpret_cast<FileMetaData*>(0x1));
  version_.GetOverlappingInputs(/*level=*/1, /*begin=*/nullptr, /*end=*/nullptr, &inputs);
  EXPECT_TRUE(inputs.empty());
}

// With an open range (begin==nullptr, end==nullptr) and some files at a level
// the method should return all files at that level (observable behavior).
TEST_F(GetOverlappingInputsTest_155, OpenRangeReturnsAllFiles_Level0_155) {
  // Level-0, multiple files
  AddFile(/*level=*/0, /*number=*/101);
  AddFile(/*level=*/0, /*number=*/102);
  AddFile(/*level=*/0, /*number=*/103);

  std::vector<FileMetaData*> inputs;
  version_.GetOverlappingInputs(/*level=*/0, /*begin=*/nullptr, /*end=*/nullptr, &inputs);

  ASSERT_EQ(inputs.size(), 3u);
  // Order is the same as stored for this observable case
  EXPECT_EQ(inputs[0]->number, 101u);
  EXPECT_EQ(inputs[1]->number, 102u);
  EXPECT_EQ(inputs[2]->number, 103u);
}

// Same as above but for a non-zero level (e.g., level 3) to show it is not limited to L0.
TEST_F(GetOverlappingInputsTest_155, OpenRangeReturnsAllFiles_Level3_155) {
  AddFile(/*level=*/3, /*number=*/201);
  AddFile(/*level=*/3, /*number=*/202);

  std::vector<FileMetaData*> inputs;
  version_.GetOverlappingInputs(/*level=*/3, /*begin=*/nullptr, /*end=*/nullptr, &inputs);

  ASSERT_EQ(inputs.size(), 2u);
  EXPECT_EQ(inputs[0]->number, 201u);
  EXPECT_EQ(inputs[1]->number, 202u);
}

// If the caller passes a pre-populated vector, it must be cleared before use.
TEST_F(GetOverlappingInputsTest_155, ClearsPrePopulatedInputsBeforeFilling_155) {
  AddFile(/*level=*/2, /*number=*/301);
  AddFile(/*level=*/2, /*number=*/302);

  std::vector<FileMetaData*> inputs;
  inputs.push_back(reinterpret_cast<FileMetaData*>(0xDEADBEEF));  // garbage to ensure clear()
  version_.GetOverlappingInputs(/*level=*/2, /*begin=*/nullptr, /*end=*/nullptr, &inputs);

  ASSERT_EQ(inputs.size(), 2u);
  EXPECT_EQ(inputs[0]->number, 301u);
  EXPECT_EQ(inputs[1]->number, 302u);
}

// -------- Death tests for level bound assertions (observable via assert) --------
#if GTEST_HAS_DEATH_TEST
TEST_F(GetOverlappingInputsTest_155, DeathOnNegativeLevel_155) {
  std::vector<FileMetaData*> inputs;
  EXPECT_DEATH(
      version_.GetOverlappingInputs(/*level=*/-1, /*begin=*/nullptr, /*end=*/nullptr, &inputs),
      ".*");
}

TEST_F(GetOverlappingInputsTest_155, DeathOnLevelGEKNumLevels_155) {
  std::vector<FileMetaData*> inputs;
  EXPECT_DEATH(
      version_.GetOverlappingInputs(/*level=*/config::kNumLevels, /*begin=*/nullptr, /*end=*/nullptr, &inputs),
      ".*");
}
#endif  // GTEST_HAS_DEATH_TEST

/*
 * Notes:
 * - We intentionally avoid constructing begin/end InternalKeys because that would
 *   require depending on encoding details of InternalKey. The open-range cases
 *   here exercise the function’s guaranteed observable behavior without peeking
 *   into internals.
 * - If you want to extend coverage to explicit ranges and L0 widening behavior,
 *   the codebase’s standard helpers (e.g., building InternalKeys and adding
 *   files through VersionEdits) can be used, still treating Version as a black box.
 */
