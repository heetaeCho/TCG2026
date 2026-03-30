// FilterBlockBuilder_StartBlock_test.cc
#include "table/filter_block.h"
#include "leveldb/filter_policy.h"
#include "leveldb/slice.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::_;
using ::testing::DoAll;
using ::testing::InSequence;
using ::testing::Return;
using ::testing::SetArgPointee;
using ::testing::StrictMock;

namespace {

class MockFilterPolicy : public leveldb::FilterPolicy {
 public:
  MOCK_METHOD(const char*, Name, (), (const, override));
  MOCK_METHOD(void,
              CreateFilter,
              (const leveldb::Slice* keys, int n, std::string* dst),
              (const, override));
  MOCK_METHOD(bool,
              KeyMayMatch,
              (const leveldb::Slice& key, const leveldb::Slice& filter),
              (const, override));
};

class FilterBlockBuilderTest_371 : public ::testing::Test {
 protected:
  StrictMock<MockFilterPolicy> policy_;
};

TEST_F(FilterBlockBuilderTest_371, StartBlock_NoKeys_NoPolicyCall_371) {
  // When no keys have been added, advancing to the next filter region
  // should not invoke FilterPolicy::CreateFilter (observable interaction).
  leveldb::FilterBlockBuilder builder(&policy_);
  EXPECT_CALL(policy_, CreateFilter(_, _, _)).Times(0);

  builder.StartBlock(leveldb::kFilterBase);  // moves to index 1
}

TEST_F(FilterBlockBuilderTest_371, StartBlock_WithKey_AdvancingOneBase_InvokesCreateFilterOnce_371) {
  leveldb::FilterBlockBuilder builder(&policy_);

  // Collect one key for the current (index 0) region.
  builder.AddKey(leveldb::Slice("k1"));

  // Moving to the next region (index 1) must finalize the previous region
  // and call CreateFilter exactly once with n == 1.
  EXPECT_CALL(policy_, CreateFilter(_, 1, _))
      .Times(1);

  builder.StartBlock(leveldb::kFilterBase);
}

TEST_F(FilterBlockBuilderTest_371, StartBlock_JumpMultipleBases_OnlyOneCreateForCollectedKeys_371) {
  leveldb::FilterBlockBuilder builder(&policy_);

  // Add multiple keys to index 0.
  builder.AddKey(leveldb::Slice("a"));
  builder.AddKey(leveldb::Slice("b"));
  builder.AddKey(leveldb::Slice("c"));

  // Jump ahead several filter regions at once. Only the region that has
  // collected keys (index 0) should trigger a CreateFilter call; subsequent
  // empty regions should not.
  EXPECT_CALL(policy_, CreateFilter(_, 3, _))
      .Times(1);

  builder.StartBlock(5 * leveldb::kFilterBase);  // moves to index 5
}

TEST_F(FilterBlockBuilderTest_371, StartBlock_AddMoreKeys_AfterJump_NextBase_SecondCreate_371) {
  leveldb::FilterBlockBuilder builder(&policy_);

  {
    InSequence seq;  // enforce call order for clarity

    // First, gather two keys for index 0 and jump to index 5 -> one CreateFilter(n=2).
    builder.AddKey(leveldb::Slice("x"));
    builder.AddKey(leveldb::Slice("y"));
    EXPECT_CALL(policy_, CreateFilter(_, 2, _)).Times(1);
    builder.StartBlock(5 * leveldb::kFilterBase);

    // Now add one key for index 5 and advance to index 6 -> another CreateFilter(n=1).
    builder.AddKey(leveldb::Slice("z"));
    EXPECT_CALL(policy_, CreateFilter(_, 1, _)).Times(1);
    builder.StartBlock(6 * leveldb::kFilterBase);
  }
}

#if GTEST_HAS_DEATH_TEST
TEST_F(FilterBlockBuilderTest_371, StartBlock_BackwardOffset_TriggersAssert_DeathTest_371) {
  leveldb::FilterBlockBuilder builder(&policy_);

  // Establish forward progress first; no keys so policy is not called.
  EXPECT_CALL(policy_, CreateFilter(_, _, _)).Times(0);
  builder.StartBlock(2 * leveldb::kFilterBase);  // filter_offsets_.size() >= 2

  // Going backward should violate the assertion:
  // assert(filter_index >= filter_offsets_.size());
  EXPECT_DEATH(
      {
        // Use a compound statement to ensure the call happens within the death scope.
        builder.StartBlock(0);  // backward to index 0
      },
      ".*");
}
#endif  // GTEST_HAS_DEATH_TEST

}  // namespace
