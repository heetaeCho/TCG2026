// File: filtered_re2_move_assignment_test.cc
#include <gtest/gtest.h>
#include "re2/filtered_re2.h"
#include "re2/re2.h"

using re2::FilteredRE2;

class FilteredRE2MoveAssignTest_471 : public ::testing::Test {
protected:
  RE2::Options opts_;  // Default options; we don't assume anything about internals.
};

// Verifies that move-assigning transfers the observable state (e.g., number of
// added regexps) from source to destination and that the destination can be used
// normally after the move.
TEST_F(FilteredRE2MoveAssignTest_471, TransfersStateAndAllowsFurtherUse_471) {
  FilteredRE2 src;
  int id0 = -1, id1 = -1;

  // Populate source with two simple patterns and capture assigned ids.
  EXPECT_EQ(RE2::NoError, src.Add("foo", opts_, &id0));
  EXPECT_EQ(0, id0);
  EXPECT_EQ(RE2::NoError, src.Add("bar", opts_, &id1));
  EXPECT_EQ(1, id1);

  const int src_count = src.NumRegexps();
  ASSERT_EQ(2, src_count);

  // Destination starts with its own content so we can verify it's replaced.
  FilteredRE2 dst;
  int dst_id0 = -1;
  EXPECT_EQ(RE2::NoError, dst.Add("zzz", opts_, &dst_id0));
  EXPECT_EQ(0, dst_id0);
  ASSERT_EQ(1, dst.NumRegexps());

  // Move-assign: destination should now reflect the (former) source state.
  dst = std::move(src);

  EXPECT_EQ(src_count, dst.NumRegexps()) << "Destination should take over source state after move-assign.";

  // Destination remains usable: adding another regexp should append after current count.
  int appended_id = -1;
  EXPECT_EQ(RE2::NoError, dst.Add("qux", opts_, &appended_id));
  EXPECT_EQ(src_count, appended_id);
  EXPECT_EQ(src_count + 1, dst.NumRegexps());
}

// Verifies move-assigning from an empty (default-constructed) source results in
// an "empty" destination (observable via NumRegexps), and subsequent use behaves normally.
TEST_F(FilteredRE2MoveAssignTest_471, MoveFromEmptySourceProducesEmptyDest_471) {
  FilteredRE2 empty_src;

  FilteredRE2 dst;
  int dst_id0 = -1;
  EXPECT_EQ(RE2::NoError, dst.Add("alpha", opts_, &dst_id0));
  EXPECT_EQ(0, dst_id0);
  ASSERT_EQ(1, dst.NumRegexps());

  // Move-assign from empty.
  dst = std::move(empty_src);

  // Now destination should be "empty" by observable behavior.
  EXPECT_EQ(0, dst.NumRegexps());

  // And it should still be usable afterwards.
  int new_id = -1;
  EXPECT_EQ(RE2::NoError, dst.Add("beta", opts_, &new_id));
  EXPECT_EQ(0, new_id);
  EXPECT_EQ(1, dst.NumRegexps());
}

// Verifies that repeated move-assignments behave consistently and the destination
// reflects the latest source's observable state (not a combination).
TEST_F(FilteredRE2MoveAssignTest_471, MultipleMoveAssignmentsTakeLatestState_471) {
  // Source A with one pattern.
  FilteredRE2 src_a;
  int a0 = -1;
  EXPECT_EQ(RE2::NoError, src_a.Add("one", opts_, &a0));
  EXPECT_EQ(0, a0);
  ASSERT_EQ(1, src_a.NumRegexps());

  // Source B with two patterns.
  FilteredRE2 src_b;
  int b0 = -1, b1 = -1;
  EXPECT_EQ(RE2::NoError, src_b.Add("two", opts_, &b0));
  EXPECT_EQ(RE2::NoError, src_b.Add("three", opts_, &b1));
  ASSERT_EQ(2, src_b.NumRegexps());

  // Destination with some initial content.
  FilteredRE2 dst;
  int d0 = -1;
  EXPECT_EQ(RE2::NoError, dst.Add("initial", opts_, &d0));
  ASSERT_EQ(1, dst.NumRegexps());

  // First move-assign from A -> dst.
  dst = std::move(src_a);
  EXPECT_EQ(1, dst.NumRegexps());

  // Then move-assign from B -> dst; dst should now reflect B's state (not additive).
  dst = std::move(src_b);
  EXPECT_EQ(2, dst.NumRegexps());

  // Destination still usable after multiple move-assignments.
  int appended = -1;
  EXPECT_EQ(RE2::NoError, dst.Add("four", opts_, &appended));
  EXPECT_EQ(2, appended);
  EXPECT_EQ(3, dst.NumRegexps());
}
