// File: explanations_optional_explanations_test_15.cc

#include "explanations.h"

#include <gtest/gtest.h>

#include <cstdarg>
#include <string>
#include <vector>

namespace {

// Helper to safely call OptionalExplanations::RecordArgs with a va_list.
void RecordArgsThroughOptional(OptionalExplanations* opt,
                               const void* item,
                               const char* fmt,
                               ...) {
  va_list args;
  va_start(args, fmt);
  opt->RecordArgs(item, fmt, args);
  va_end(args);
}

class OptionalExplanationsTest_15 : public ::testing::Test {
 protected:
  Explanations explanations_;
  OptionalExplanations opt_with_{&explanations_};
  OptionalExplanations opt_without_{nullptr};
};

}  // namespace

// TEST_ID: 15
TEST_F(OptionalExplanationsTest_15,
       Record_ForwardsToUnderlyingExplanationsWhenPresent_15) {
  int item = 0;
  std::vector<std::string> out;

  // Initially, nothing should be recorded for this item.
  opt_with_.LookupAndAppend(&item, &out);
  EXPECT_TRUE(out.empty());

  // Record a formatted explanation via OptionalExplanations.
  opt_with_.Record(&item, "First %s %d", "message", 42);

  // Now LookupAndAppend should retrieve at least one explanation.
  opt_with_.LookupAndAppend(&item, &out);
  ASSERT_EQ(1u, out.size());

  // We do not rely on exact formatting, only that the message contains
  // the key parts of the format arguments.
  EXPECT_NE(std::string::npos, out[0].find("First"));
  EXPECT_NE(std::string::npos, out[0].find("message"));
}

// TEST_ID: 15
TEST_F(OptionalExplanationsTest_15,
       Record_DoesNothingWhenUnderlyingIsNull_15) {
  int item = 0;
  std::vector<std::string> out_before(1, "keep_me");

  // Calling Record on an OptionalExplanations with nullptr should be a no-op
  // (no crash, no observable side effects through the interface).
  opt_without_.Record(&item, "Should %s be ignored?", "definitely");

  // LookupAndAppend should also be a no-op when underlying is null.
  opt_without_.LookupAndAppend(&item, &out_before);

  // The existing contents must remain unchanged.
  ASSERT_EQ(1u, out_before.size());
  EXPECT_EQ("keep_me", out_before[0]);
}

// TEST_ID: 15
TEST_F(OptionalExplanationsTest_15,
       RecordArgs_ForwardsToUnderlyingExplanationsWhenPresent_15) {
  int item = 0;
  std::vector<std::string> out;

  // Use helper to construct a va_list and forward to OptionalExplanations.
  RecordArgsThroughOptional(&opt_with_, &item, "Second %s %d", "message", 7);

  opt_with_.LookupAndAppend(&item, &out);
  ASSERT_EQ(1u, out.size());

  // Again, do not depend on exact formatting, just on key substrings.
  EXPECT_NE(std::string::npos, out[0].find("Second"));
  EXPECT_NE(std::string::npos, out[0].find("message"));
}

// TEST_ID: 15
TEST_F(OptionalExplanationsTest_15,
       LookupAndAppend_DoesNothingWhenUnderlyingIsNull_15) {
  int item = 0;
  std::vector<std::string> out(2);
  out[0] = "a";
  out[1] = "b";

  opt_without_.LookupAndAppend(&item, &out);

  // The vector should be unchanged.
  ASSERT_EQ(2u, out.size());
  EXPECT_EQ("a", out[0]);
  EXPECT_EQ("b", out[1]);
}

// TEST_ID: 15
TEST_F(OptionalExplanationsTest_15,
       Ptr_ReturnsConfiguredUnderlyingPointer_15) {
  // For the instance with underlying Explanations*, ptr() should return it.
  EXPECT_EQ(&explanations_, opt_with_.ptr());

  // For the instance constructed with nullptr, ptr() should return nullptr.
  EXPECT_EQ(nullptr, opt_without_.ptr());
}
