#include "explanations.h"

#include <gtest/gtest.h>
#include <cstdarg>
#include <string>
#include <vector>

// Helper to call RecordArgs with normal variadic syntax.
static void CallRecordArgs(Explanations* explanations,
                           const void* item,
                           const char* fmt,
                           ...) {
  va_list args;
  va_start(args, fmt);
  explanations->RecordArgs(item, fmt, args);
  va_end(args);
}

class ExplanationsTest_13 : public ::testing::Test {
 protected:
  Explanations explanations_;
};

// Normal operation: a single formatted string is stored and retrievable.
TEST_F(ExplanationsTest_13, RecordArgsStoresSingleExplanationForItem_13) {
  int item = 42;
  const void* key = &item;

  CallRecordArgs(&explanations_, key, "value=%d", 7);

  std::vector<std::string> out;
  explanations_.LookupAndAppend(key, &out);

  ASSERT_EQ(out.size(), 1u);
  EXPECT_EQ(out[0], "value=7");
}

// Normal operation: multiple calls for the same item append explanations in order.
TEST_F(ExplanationsTest_13, RecordArgsAppendsMultipleExplanationsInOrder_13) {
  int item = 100;
  const void* key = &item;

  CallRecordArgs(&explanations_, key, "first %d", 1);
  CallRecordArgs(&explanations_, key, "second %s", "entry");

  std::vector<std::string> out;
  explanations_.LookupAndAppend(key, &out);

  ASSERT_EQ(out.size(), 2u);
  EXPECT_EQ(out[0], "first 1");
  EXPECT_EQ(out[1], "second entry");
}

// Boundary / separation: different items keep their explanations separate.
TEST_F(ExplanationsTest_13, RecordArgsSeparatesExplanationsByItem_13) {
  int item1 = 1;
  int item2 = 2;
  const void* key1 = &item1;
  const void* key2 = &item2;

  CallRecordArgs(&explanations_, key1, "item1-%d", 10);
  CallRecordArgs(&explanations_, key2, "item2-%d", 20);

  std::vector<std::string> out1;
  explanations_.LookupAndAppend(key1, &out1);
  ASSERT_EQ(out1.size(), 1u);
  EXPECT_EQ(out1[0], "item1-10");

  std::vector<std::string> out2;
  explanations_.LookupAndAppend(key2, &out2);
  ASSERT_EQ(out2.size(), 1u);
  EXPECT_EQ(out2[0], "item2-20");
}

// Boundary condition: very long formatted string is handled and stored
// as a prefix of the original (due to vsnprintf buffer limits).
TEST_F(ExplanationsTest_13, RecordArgsHandlesLongFormattedString_13) {
  int item = 0;
  const void* key = &item;

  // Create a long input string.
  std::string long_input(2000, 'x');

  CallRecordArgs(&explanations_, key, "%s", long_input.c_str());

  std::vector<std::string> out;
  explanations_.LookupAndAppend(key, &out);

  ASSERT_EQ(out.size(), 1u);
  // The stored string should be non-empty and a prefix of the original.
  ASSERT_FALSE(out[0].empty());
  EXPECT_EQ(long_input.substr(0, out[0].size()), out[0]);
}

// Exceptional / edge behavior: LookupAndAppend on an item with no records
// should not modify the output vector.
TEST_F(ExplanationsTest_13, LookupAndAppendUnrecordedItemLeavesOutputUnchanged_13) {
  int item = 123;
  const void* key = &item;

  std::vector<std::string> out;
  out.push_back("existing");

  explanations_.LookupAndAppend(key, &out);

  ASSERT_EQ(out.size(), 1u);
  EXPECT_EQ(out[0], "existing");
}
