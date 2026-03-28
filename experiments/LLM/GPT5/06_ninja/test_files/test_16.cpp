// File: optional_explanations_recordargs_test_16.cc

#include <gtest/gtest.h>

#include <cstdarg>
#include <string>
#include <vector>

#include "explanations.h"

// Helper that builds a va_list and calls OptionalExplanations::RecordArgs.
// This treats OptionalExplanations as a black box and only uses its public API.
static void CallRecordArgsHelper(OptionalExplanations& opt,
                                 const void* item,
                                 const char* fmt,
                                 ...) {
  va_list args;
  va_start(args, fmt);
  opt.RecordArgs(item, fmt, args);
  va_end(args);
}

class OptionalExplanationsTest_16 : public ::testing::Test {
 protected:
  Explanations explanations_;
  OptionalExplanations with_explanations_{&explanations_};
  OptionalExplanations without_explanations_{nullptr};
};

// Normal operation: when an underlying Explanations* exists,
// RecordArgs should record a formatted explanation that can be
// retrieved via Explanations::LookupAndAppend.
TEST_F(OptionalExplanationsTest_16, RecordArgs_ForwardsAndRecords_16) {
  int item;
  std::vector<std::string> out;

  CallRecordArgsHelper(with_explanations_, &item, "%s %d", "value", 42);

  explanations_.LookupAndAppend(&item, &out);
  ASSERT_EQ(out.size(), 1u);
  EXPECT_EQ(out[0], "value 42");
}

// Boundary / accumulation behavior: multiple RecordArgs calls for the
// same item should append multiple explanations in order.
TEST_F(OptionalExplanationsTest_16, RecordArgs_AppendsMultipleEntries_16) {
  int item;
  std::vector<std::string> out;

  CallRecordArgsHelper(with_explanations_, &item, "%s", "first");
  CallRecordArgsHelper(with_explanations_, &item, "%s", "second");
  CallRecordArgsHelper(with_explanations_, &item, "%s", "third");

  explanations_.LookupAndAppend(&item, &out);
  ASSERT_EQ(out.size(), 3u);
  EXPECT_EQ(out[0], "first");
  EXPECT_EQ(out[1], "second");
  EXPECT_EQ(out[2], "third");
}

// Boundary behavior: explanations for different items should be
// stored and retrieved independently.
TEST_F(OptionalExplanationsTest_16, RecordArgs_SeparatesItems_16) {
  int item1;
  int item2;
  std::vector<std::string> out1;
  std::vector<std::string> out2;

  CallRecordArgsHelper(with_explanations_, &item1, "%s", "item1");
  CallRecordArgsHelper(with_explanations_, &item2, "%s", "item2");

  explanations_.LookupAndAppend(&item1, &out1);
  explanations_.LookupAndAppend(&item2, &out2);

  ASSERT_EQ(out1.size(), 1u);
  ASSERT_EQ(out2.size(), 1u);
  EXPECT_EQ(out1[0], "item1");
  EXPECT_EQ(out2[0], "item2");
}

// Exceptional / edge behavior: when OptionalExplanations is constructed
// with a null Explanations*, RecordArgs should be a no-op and must be safe
// to call (no crash / UB). We can only verify via lack of side effects
// on an unrelated Explanations instance.
TEST_F(OptionalExplanationsTest_16, RecordArgs_NullUnderlyingIsNoOp_16) {
  int item;
  std::vector<std::string> out;

  // Call RecordArgs on the OptionalExplanations that has no underlying
  // Explanations pointer. This should not crash or affect the separate
  // 'explanations_' instance.
  CallRecordArgsHelper(without_explanations_, &item, "%s", "ignored");

  // Verify that our independent Explanations instance remains unaffected.
  explanations_.LookupAndAppend(&item, &out);
  EXPECT_TRUE(out.empty());
}
