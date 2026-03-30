// File: ./TestProjects/ninja/src/optional_explanations_lookupandappend_test.cc

#include "gtest/gtest.h"
#include "explanations.h"

#include <string>
#include <vector>

class OptionalExplanationsTest_17 : public ::testing::Test {
 protected:
  Explanations explanations_;
  int dummy_item_;  // Just something with a stable address.

  const void* item() const { return &dummy_item_; }
};

// Normal case: when an Explanations* is provided, OptionalExplanations::LookupAndAppend
// should delegate to Explanations::LookupAndAppend and produce the same output.
TEST_F(OptionalExplanationsTest_17, DelegatesToExplanations_17) {
  OptionalExplanations optional(&explanations_);

  // Record some explanations for the same item through the underlying Explanations.
  explanations_.Record(item(), "first %d", 1);
  explanations_.Record(item(), "second %s", "message");

  std::vector<std::string> expected;
  std::vector<std::string> via_optional;

  // Directly through Explanations.
  explanations_.LookupAndAppend(item(), &expected);
  // Through OptionalExplanations (should behave the same).
  optional.LookupAndAppend(item(), &via_optional);

  EXPECT_EQ(expected, via_optional);
}

// Boundary / null case: when constructed with a nullptr, LookupAndAppend
// should be a no-op and must not modify the output vector.
TEST_F(OptionalExplanationsTest_17, NoOpWhenExplanationsIsNull_17) {
  OptionalExplanations optional(nullptr);

  std::vector<std::string> out;
  out.push_back("pre-existing");

  optional.LookupAndAppend(item(), &out);

  ASSERT_EQ(out.size(), 1u);
  EXPECT_EQ(out[0], "pre-existing");
}

// Boundary case: no explanations recorded for the item.
// Behavior through OptionalExplanations should match direct Explanations behavior.
TEST_F(OptionalExplanationsTest_17, NoRecordedItemBehaviorMatchesExplanations_17) {
  OptionalExplanations optional(&explanations_);

  std::vector<std::string> expected(1, "keep");
  std::vector<std::string> via_optional(1, "keep");

  // No calls to Record/RecordArgs for this item.
  explanations_.LookupAndAppend(item(), &expected);
  optional.LookupAndAppend(item(), &via_optional);

  EXPECT_EQ(expected, via_optional);
}

// Repeated calls: multiple LookupAndAppend calls through OptionalExplanations
// should mirror multiple direct calls to Explanations (appending in the same way).
TEST_F(OptionalExplanationsTest_17, MultipleCallsAccumulateConsistently_17) {
  OptionalExplanations optional(&explanations_);

  explanations_.Record(item(), "repeat %d", 1);

  std::vector<std::string> expected;
  std::vector<std::string> via_optional;

  // First round.
  explanations_.LookupAndAppend(item(), &expected);
  optional.LookupAndAppend(item(), &via_optional);

  // Second round.
  explanations_.LookupAndAppend(item(), &expected);
  optional.LookupAndAppend(item(), &via_optional);

  EXPECT_EQ(expected, via_optional);
}
