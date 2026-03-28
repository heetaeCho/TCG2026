#include <gtest/gtest.h>
#include "db/version_set.h"
#include "db/dbformat.h"

using namespace leveldb;

// Test fixture creating a minimally-initialized VersionSet.
// We keep everything strictly through public interfaces and avoid
// touching private state or assuming any internal logic.
class VersionSet_CompactRangeTest_177 : public ::testing::Test {
protected:
  // Members that can be constructed with standard defaults in LevelDB-style code.
  // We avoid depending on any internal details and only pass them to the ctor.
  Options options_;
  // NOTE: In real LevelDB, you would initialize env/comparator/table cache.
  // Since we must remain black-box and the provided snippet only relies
  // on VersionSet::CompactRange calling GetOverlappingInputs on current_,
  // having an empty current version (default-constructed VersionSet)
  // is enough to test "no overlaps" behavior.
  const InternalKeyComparator* icmp_ = nullptr; // nullptr per provided constructor signature
  TableCache* table_cache_ = nullptr;

  // We keep dbname minimal — CompactRange doesn’t touch the filesystem path
  // in the provided snippet.
  std::string dbname_ = "testdb-compactrange-177";

  // Helper to construct VersionSet through its public constructor.
  std::unique_ptr<VersionSet> MakeVS() {
    return std::unique_ptr<VersionSet>(
        new VersionSet(dbname_, &options_, table_cache_, icmp_));
  }
};

// [Behavior] When there are no overlapping inputs in the current version,
// CompactRange must return nullptr.
// (Covers the early-return branch: inputs.empty() -> nullptr)
TEST_F(VersionSet_CompactRangeTest_177, ReturnsNullWhenNoOverlaps_Level0_177) {
  auto vset = MakeVS();

  // No files have been added via public APIs (e.g., no LogAndApply).
  // Therefore current_->GetOverlappingInputs(...) will see no overlaps.
  const int level = 0;
  // begin/end can be nullptr per the interface usage pattern in LevelDB.
  const InternalKey* begin = nullptr;
  const InternalKey* end   = nullptr;

  Compaction* c = vset->CompactRange(level, begin, end);
  EXPECT_EQ(c, nullptr) << "Expected nullptr compaction for empty overlaps on L0";
}

// [Behavior] Even for non-zero levels (where size-limiting might kick in),
// if there are no overlapping inputs, CompactRange must return nullptr.
TEST_F(VersionSet_CompactRangeTest_177, ReturnsNullWhenNoOverlaps_Level1_177) {
  auto vset = MakeVS();

  const int level = 1; // > 0 to exercise the same early-return path
  const InternalKey* begin = nullptr;
  const InternalKey* end   = nullptr;

  Compaction* c = vset->CompactRange(level, begin, end);
  EXPECT_EQ(c, nullptr) << "Expected nullptr compaction for empty overlaps on L1";
}

// [Behavior] With explicit (but empty) ranges, still no overlaps -> nullptr.
// This verifies the observable contract is independent of the (null vs. non-null)
// begin/end pointer usage, as long as the current version contains no files.
TEST_F(VersionSet_CompactRangeTest_177, ReturnsNullWhenNoOverlaps_WithExplicitEmptyRange_177) {
  auto vset = MakeVS();

  InternalKey begin_key;  // default-constructed (empty)
  InternalKey end_key;    // default-constructed (empty)
  const int level = 2;

  Compaction* c = vset->CompactRange(level, &begin_key, &end_key);
  EXPECT_EQ(c, nullptr) << "Expected nullptr compaction for empty overlaps with explicit keys";
}
