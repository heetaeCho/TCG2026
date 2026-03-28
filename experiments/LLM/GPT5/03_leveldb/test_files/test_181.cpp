#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "db/version_set.h"
#include "db/dbformat.h"
#include "leveldb/comparator.h"
#include "leveldb/slice.h"

using ::testing::Return;
using ::testing::InSequence;
using ::testing::_;
using leveldb::Compaction;
using leveldb::FileMetaData;
using leveldb::InternalKey;
using leveldb::InternalKeyComparator;
using leveldb::Slice;

// -----------------------------
// Test-only utilities (assumed)
// -----------------------------
// The following declarations represent *test-only* helpers typically provided
// by the codebase's test harness. They should construct a Compaction instance
// and allow adding files to a Version at specific levels without exposing or
// touching private implementation details in production code.
//
// If your repository already has equivalents (e.g., in testutil), include and use them.
// Otherwise, implement them in a test-only translation unit and friend them from
// the relevant classes.
//
// 1) Create a Compaction bound to `input_version` at `level` with level_ptrs reset.
Compaction* Test_CreateCompactionForLevel(leveldb::Version* input_version, int level);

// 2) Add a file [smallest_user_key, largest_user_key] to `version` at `level`.
FileMetaData* Test_AddFile(leveldb::Version* version,
                           int level,
                           const std::string& smallest_user_key,
                           const std::string& largest_user_key);

// 3) Build a minimal VersionSet/Version pair ready for use in compaction tests.
struct TestVersionEnv {
  std::unique_ptr<leveldb::VersionSet> vset;
  leveldb::Version* version;  // owned by vset
};
TestVersionEnv Test_MakeVersionEnv(const leveldb::Comparator* user_cmp);

// -----------------------------
// Mock user comparator
// -----------------------------
class MockUserComparator : public leveldb::Comparator {
public:
  std::string name_ = "mock";

  MOCK_METHOD(int, Compare, (const Slice& a, const Slice& b), (const, override));
  const char* Name() const override { return name_.c_str(); }
  void FindShortestSeparator(std::string*, const Slice&) const override {}
  void FindShortSuccessor(std::string*) const override {}
};

// -----------------------------
// Test fixture
// -----------------------------
class CompactionIsBaseLevelForKeyTest_181 : public ::testing::Test {
protected:
  std::unique_ptr<MockUserComparator> user_cmp_;
  std::unique_ptr<InternalKeyComparator> ikc_;
  std::unique_ptr<TestVersionEnv> env_; // holds VersionSet + Version

  void SetUp() override {
    user_cmp_ = std::make_unique<MockUserComparator>();
    // InternalKeyComparator consumes a user comparator; Compare() calls on it are what we verify.
    ikc_ = std::make_unique<InternalKeyComparator>(user_cmp_.get());
    env_.reset(new TestVersionEnv(Test_MakeVersionEnv(user_cmp_.get())));
  }

  // Helper to create a test compaction at given base level.
  Compaction* MakeCompactionAtLevel(int level) {
    return Test_CreateCompactionForLevel(env_->version, level);
  }

  // Helper to add a file to some level [smallest, largest] (user keys).
  FileMetaData* AddFile(int level, const std::string& s, const std::string& l) {
    return Test_AddFile(env_->version, level, s, l);
  }
};

// ------------------------------------------------------
// TESTS
// ------------------------------------------------------

// 1) No files in higher levels: should return true and never call Compare.
//    This verifies the early-success path when there is nothing to check.
TEST_F(CompactionIsBaseLevelForKeyTest_181, ReturnsTrueWhenNoHigherLevelFiles_181) {
  // Arrange
  // Compaction at L0 => IsBaseLevelForKey inspects levels 2..6, which are empty.
  Compaction* c = MakeCompactionAtLevel(/*level=*/0);
  Slice user_key("k");

  // Expect: Compare is never needed because there are no files to scan.
  EXPECT_CALL(*user_cmp_, Compare(_, _)).Times(0);

  // Act
  const bool is_base = c->IsBaseLevelForKey(user_key);

  // Assert
  EXPECT_TRUE(is_base);
}

// 2) Key falls within a file in level (level+2): should return false.
//    This is the primary negative path: overlap detected at first eligible level.
TEST_F(CompactionIsBaseLevelForKeyTest_181, ReturnsFalseOnFirstOverlappingHigherLevelFile_181) {
  // Arrange
  // Compaction at L0 inspects L2..6. Put an overlapping file at L2: ["b", "m"].
  AddFile(/*level=*/2, /*smallest=*/"b", /*largest=*/"m");
  Compaction* c = MakeCompactionAtLevel(/*level=*/0);

  // For overlap: user_key "g" is s<=key<=l -> Compare("g","m")<=0 and Compare("g","b")>=0
  // Set explicit expectations on the mock comparator to enforce the overlap logic.
  {
    InSequence seq; // enforce call order within the same file check
    EXPECT_CALL(*user_cmp_, Compare(Slice("g"), Slice("m"))).WillOnce(Return(-1)); // "g" < "m"
    EXPECT_CALL(*user_cmp_, Compare(Slice("g"), Slice("b"))).WillOnce(Return(1));  // "g" > "b"
  }

  // Act
  const bool is_base = c->IsBaseLevelForKey(Slice("g"));

  // Assert
  EXPECT_FALSE(is_base);
}

// 3) Key less than a file's smallest in L2: iterator stops advancing and returns true
//    (no overlap, and since key <= file.largest and key < file.smallest => break and move up).
TEST_F(CompactionIsBaseLevelForKeyTest_181, ReturnsTrueWhenKeyPrecedesFirstCandidate_181) {
  // Arrange
  // L2: one file ["d","k"], key="b" should cause: Compare("b","k")<=0 (true) then
  // Compare("b","d")>=0 (false), so it breaks without marking overlap; overall true.
  AddFile(/*level=*/2, "d", "k");
  Compaction* c = MakeCompactionAtLevel(/*level=*/0);

  {
    InSequence seq;
    EXPECT_CALL(*user_cmp_, Compare(Slice("b"), Slice("k"))).WillOnce(Return(-1)); // "b" < "k"
    EXPECT_CALL(*user_cmp_, Compare(Slice("b"), Slice("d"))).WillOnce(Return(-1)); // "b" < "d"  => no overlap
  }

  // Act
  const bool is_base = c->IsBaseLevelForKey(Slice("b"));

  // Assert
  EXPECT_TRUE(is_base);
}

// 4) Non-overlapping at L2 but overlapping at L3: must continue scanning and return false
//    This checks pointer advancement across levels and correct final decision.
TEST_F(CompactionIsBaseLevelForKeyTest_181, SkipsNonOverlappingLevelThenFindsOverlapNextLevel_181) {
  // Arrange
  // L2: ["p","z"] (key "g" < "p": no overlap, early break at L2)
  // L3: ["a","h"] (key "g" inside => overlap here)
  AddFile(/*level=*/2, "p", "z");
  AddFile(/*level=*/3, "a", "h");
  Compaction* c = MakeCompactionAtLevel(/*level=*/0);

  {
    InSequence seq;
    // L2 checks:
    EXPECT_CALL(*user_cmp_, Compare(Slice("g"), Slice("z"))).WillOnce(Return(-1));  // g < z
    EXPECT_CALL(*user_cmp_, Compare(Slice("g"), Slice("p"))).WillOnce(Return(-1));  // g < p  => break (no overlap)

    // L3 checks:
    EXPECT_CALL(*user_cmp_, Compare(Slice("g"), Slice("h"))).WillOnce(Return(-1));  // g < h
    EXPECT_CALL(*user_cmp_, Compare(Slice("g"), Slice("a"))).WillOnce(Return(1));   // g > a  => overlap
  }

  // Act
  const bool is_base = c->IsBaseLevelForKey(Slice("g"));

  // Assert
  EXPECT_FALSE(is_base);
}

// 5) Edge boundary: key equals smallest or largest should still count as overlapping (false)
TEST_F(CompactionIsBaseLevelForKeyTest_181, BoundaryInclusiveOverlap_181) {
  // Arrange
  // File at L2: ["d","k"]. Keys "d" and "k" should both be considered overlapping.
  AddFile(/*level=*/2, "d", "k");
  Compaction* c = MakeCompactionAtLevel(/*level=*/0);

  // Case A: key == "d" (>= smallest, <= largest)
  {
    InSequence seq;
    EXPECT_CALL(*user_cmp_, Compare(Slice("d"), Slice("k"))).WillOnce(Return(-1)); // d < k
    EXPECT_CALL(*user_cmp_, Compare(Slice("d"), Slice("d"))).WillOnce(Return(0));  // d == d
  }
  EXPECT_FALSE(c->IsBaseLevelForKey(Slice("d")));

  // Case B: key == "k"
  {
    InSequence seq;
    EXPECT_CALL(*user_cmp_, Compare(Slice("k"), Slice("k"))).WillOnce(Return(0));  // k == k (<= largest)
    EXPECT_CALL(*user_cmp_, Compare(Slice("k"), Slice("d"))).WillOnce(Return(1));  // k > d (>= smallest)
  }
  EXPECT_FALSE(c->IsBaseLevelForKey(Slice("k")));
}

