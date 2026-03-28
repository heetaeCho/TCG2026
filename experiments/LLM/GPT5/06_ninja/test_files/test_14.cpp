// File: explanations_lookup_and_append_test.cc

#include "explanations.h"

#include <gtest/gtest.h>

#include <string>
#include <vector>

namespace {

class ExplanationsTest_14 : public ::testing::Test {
 protected:
  Explanations explanations_;
};

// Verifies that when no explanation is recorded for the given item,
// LookupAndAppend does not modify the output vector.
TEST_F(ExplanationsTest_14, LookupAndAppend_NoEntry_DoesNotModifyOutput_14) {
  int unused_item = 0;
  const void* key = &unused_item;

  std::vector<std::string> out;
  out.push_back("existing");

  explanations_.LookupAndAppend(key, &out);

  ASSERT_EQ(out.size(), 1u);
  EXPECT_EQ(out[0], "existing");
}

// Verifies that a single recorded explanation is appended to an empty vector.
TEST_F(ExplanationsTest_14, LookupAndAppend_SingleExplanation_AppendsToEmptyVector_14) {
  int item = 0;
  const void* key = &item;

  const char* kMessage = "single explanation message";

  explanations_.Record(key, kMessage);

  std::vector<std::string> out;
  explanations_.LookupAndAppend(key, &out);

  ASSERT_EQ(out.size(), 1u);
  // We don't assume the exact formatting beyond containing the message text.
  EXPECT_NE(out[0].find(kMessage), std::string::npos);
}

// Verifies that multiple recorded explanations for the same item are all appended.
TEST_F(ExplanationsTest_14, LookupAndAppend_MultipleExplanationsForSameItem_14) {
  int item = 0;
  const void* key = &item;

  const char* kMessage1 = "first explanation";
  const char* kMessage2 = "second explanation";

  explanations_.Record(key, kMessage1);
  explanations_.Record(key, kMessage2);

  std::vector<std::string> out;
  explanations_.LookupAndAppend(key, &out);

  ASSERT_EQ(out.size(), 2u);

  bool found1 = false;
  bool found2 = false;
  for (const std::string& s : out) {
    if (s.find(kMessage1) != std::string::npos) found1 = true;
    if (s.find(kMessage2) != std::string::npos) found2 = true;
  }

  EXPECT_TRUE(found1);
  EXPECT_TRUE(found2);
}

// Verifies that LookupAndAppend appends to an existing vector instead of clearing it.
TEST_F(ExplanationsTest_14, LookupAndAppend_AppendsToNonEmptyVector_14) {
  int item = 0;
  const void* key = &item;

  const char* kMessage = "new explanation";

  explanations_.Record(key, kMessage);

  std::vector<std::string> out;
  out.push_back("existing");

  explanations_.LookupAndAppend(key, &out);

  ASSERT_EQ(out.size(), 2u);
  EXPECT_EQ(out[0], "existing");

  bool found_new = false;
  for (size_t i = 1; i < out.size(); ++i) {
    if (out[i].find(kMessage) != std::string::npos) {
      found_new = true;
      break;
    }
  }
  EXPECT_TRUE(found_new);
}

// Verifies that explanations are separated per item pointer (no cross-contamination).
TEST_F(ExplanationsTest_14, LookupAndAppend_DifferentItems_HaveSeparateExplanations_14) {
  int item1 = 0;
  int item2 = 0;
  const void* key1 = &item1;
  const void* key2 = &item2;

  const char* kMessage1 = "item1 explanation";
  const char* kMessage2 = "item2 explanation";

  explanations_.Record(key1, kMessage1);
  explanations_.Record(key2, kMessage2);

  std::vector<std::string> out1;
  std::vector<std::string> out2;

  explanations_.LookupAndAppend(key1, &out1);
  explanations_.LookupAndAppend(key2, &out2);

  ASSERT_EQ(out1.size(), 1u);
  ASSERT_EQ(out2.size(), 1u);

  EXPECT_NE(out1[0].find(kMessage1), std::string::npos);
  EXPECT_EQ(out1[0].find(kMessage2), std::string::npos);

  EXPECT_NE(out2[0].find(kMessage2), std::string::npos);
  EXPECT_EQ(out2[0].find(kMessage1), std::string::npos);
}

// Boundary case: using nullptr as the item key should behave consistently
// across Record and LookupAndAppend.
TEST_F(ExplanationsTest_14, LookupAndAppend_NullItemKey_14) {
  const void* key = nullptr;
  const char* kMessage = "null item explanation";

  explanations_.Record(key, kMessage);

  std::vector<std::string> out;
  explanations_.LookupAndAppend(key, &out);

  ASSERT_EQ(out.size(), 1u);
  EXPECT_NE(out[0].find(kMessage), std::string::npos);
}

// Verifies that multiple calls to LookupAndAppend append explanations again
// (no internal clearing or deduplication assumed).
TEST_F(ExplanationsTest_14, LookupAndAppend_CalledMultipleTimes_AppendsAgain_14) {
  int item = 0;
  const void* key = &item;
  const char* kMessage = "repeated explanation";

  explanations_.Record(key, kMessage);

  std::vector<std::string> out;
  explanations_.LookupAndAppend(key, &out);
  explanations_.LookupAndAppend(key, &out);

  ASSERT_EQ(out.size(), 2u);

  // Both entries should contain the message.
  EXPECT_NE(out[0].find(kMessage), std::string::npos);
  EXPECT_NE(out[1].find(kMessage), std::string::npos);
}

}  // namespace
