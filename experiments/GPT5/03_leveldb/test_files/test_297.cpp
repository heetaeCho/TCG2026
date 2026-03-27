// File: db_impl_compaction_state_current_output_test.cc

#include <gtest/gtest.h>

// Prefer the public header if available; fall back to the .cc only if that's
// how this project exposes CompactionState in tests.
#include "db/db_impl.h"   // If your project exposes CompactionState here
// #include "db/db_impl.cc" // (last resort) uncomment only if needed in your build

namespace leveldb {

using ::testing::Test;

class CompactionStateCurrentOutputTest_297 : public Test {
protected:
  // Helper to make a CompactionState in a valid, observable state.
  static DBImpl::CompactionState MakeCS() {
    // Constructor takes Compaction*; the method under test doesn't use it,
    // so nullptr is acceptable for black-box testing of current_output().
    return DBImpl::CompactionState(/*Compaction*=*/nullptr);
  }
};

// [Normal] Single element: returns a pointer to the (only) last element.
TEST_F(CompactionStateCurrentOutputTest_297, ReturnsBackPointerWithSingleElement_297) {
  auto cs = MakeCS();
  ASSERT_TRUE(cs.outputs.empty());  // pre-condition for clarity

  // Put the object into a valid state for current_output().
  cs.outputs.emplace_back();

  // Act
  DBImpl::Output* ptr = cs.current_output();

  // Assert: pointer equals address of the last element and size unchanged
  EXPECT_EQ(ptr, &cs.outputs.back());
  EXPECT_EQ(cs.outputs.size(), 1u);
}

// [Normal] Multiple elements: always returns the last element.
TEST_F(CompactionStateCurrentOutputTest_297, ReturnsLastElementWhenMultipleExist_297) {
  auto cs = MakeCS();

  // Make sure there are several elements.
  cs.outputs.emplace_back();  // index 0
  cs.outputs.emplace_back();  // index 1
  cs.outputs.emplace_back();  // index 2

  DBImpl::Output* ptr = cs.current_output();

  EXPECT_EQ(ptr, &cs.outputs.back());
  EXPECT_EQ(cs.outputs.size(), 3u);
}

// [Boundary] After adding more outputs, the "current" output updates to the new back.
TEST_F(CompactionStateCurrentOutputTest_297, TracksNewBackAfterAdditionalPush_297) {
  auto cs = MakeCS();

  cs.outputs.emplace_back();  // back #1
  DBImpl::Output* first_back = cs.current_output();
  ASSERT_EQ(first_back, &cs.outputs.back());  // sanity

  cs.outputs.emplace_back();  // back #2
  DBImpl::Output* second_back = cs.current_output();

  // Should now point to the *new* last element; and it must differ from the prior back.
  EXPECT_EQ(second_back, &cs.outputs.back());
  EXPECT_NE(second_back, first_back);
}

}  // namespace leveldb
