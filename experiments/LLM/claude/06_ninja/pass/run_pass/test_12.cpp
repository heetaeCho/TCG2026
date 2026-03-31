#include "gtest/gtest.h"
#include "explanations.h"
#include <vector>
#include <string>
#include <cstdarg>

class ExplanationsTest_12 : public ::testing::Test {
 protected:
  Explanations explanations_;
};

TEST_F(ExplanationsTest_12, LookupNonExistentItemReturnsEmpty_12) {
  int dummy = 42;
  std::vector<std::string> out;
  explanations_.LookupAndAppend(&dummy, &out);
  EXPECT_TRUE(out.empty());
}

TEST_F(ExplanationsTest_12, RecordAndLookupSingleItem_12) {
  int item = 1;
  explanations_.Record(&item, "test message %d", 42);
  std::vector<std::string> out;
  explanations_.LookupAndAppend(&item, &out);
  ASSERT_EQ(out.size(), 1u);
  EXPECT_EQ(out[0], "test message 42");
}

TEST_F(ExplanationsTest_12, RecordMultipleMessagesForSameItem_12) {
  int item = 1;
  explanations_.Record(&item, "first message");
  explanations_.Record(&item, "second message %s", "hello");
  explanations_.Record(&item, "third %d %d", 1, 2);
  std::vector<std::string> out;
  explanations_.LookupAndAppend(&item, &out);
  ASSERT_EQ(out.size(), 3u);
  EXPECT_EQ(out[0], "first message");
  EXPECT_EQ(out[1], "second message hello");
  EXPECT_EQ(out[2], "third 1 2");
}

TEST_F(ExplanationsTest_12, RecordDifferentItemsAreSeparate_12) {
  int item1 = 1;
  int item2 = 2;
  explanations_.Record(&item1, "message for item1");
  explanations_.Record(&item2, "message for item2");

  std::vector<std::string> out1;
  explanations_.LookupAndAppend(&item1, &out1);
  ASSERT_EQ(out1.size(), 1u);
  EXPECT_EQ(out1[0], "message for item1");

  std::vector<std::string> out2;
  explanations_.LookupAndAppend(&item2, &out2);
  ASSERT_EQ(out2.size(), 1u);
  EXPECT_EQ(out2[0], "message for item2");
}

TEST_F(ExplanationsTest_12, LookupAndAppendAppendsToExistingVector_12) {
  int item = 1;
  explanations_.Record(&item, "recorded message");

  std::vector<std::string> out;
  out.push_back("pre-existing");
  explanations_.LookupAndAppend(&item, &out);
  ASSERT_EQ(out.size(), 2u);
  EXPECT_EQ(out[0], "pre-existing");
  EXPECT_EQ(out[1], "recorded message");
}

TEST_F(ExplanationsTest_12, RecordWithNullItem_12) {
  explanations_.Record(nullptr, "null item message");
  std::vector<std::string> out;
  explanations_.LookupAndAppend(nullptr, &out);
  ASSERT_EQ(out.size(), 1u);
  EXPECT_EQ(out[0], "null item message");
}

TEST_F(ExplanationsTest_12, RecordEmptyFormatString_12) {
  int item = 1;
  explanations_.Record(&item, "");
  std::vector<std::string> out;
  explanations_.LookupAndAppend(&item, &out);
  ASSERT_EQ(out.size(), 1u);
  EXPECT_EQ(out[0], "");
}

TEST_F(ExplanationsTest_12, RecordWithVariousFormatSpecifiers_12) {
  int item = 1;
  explanations_.Record(&item, "%s %d %f", "hello", 42, 3.14);
  std::vector<std::string> out;
  explanations_.LookupAndAppend(&item, &out);
  ASSERT_EQ(out.size(), 1u);
  // Just check it starts with the expected prefix
  EXPECT_NE(out[0].find("hello 42"), std::string::npos);
}

TEST_F(ExplanationsTest_12, LookupNonExistentDoesNotModifyVector_12) {
  int item = 1;
  std::vector<std::string> out;
  out.push_back("existing");
  explanations_.LookupAndAppend(&item, &out);
  ASSERT_EQ(out.size(), 1u);
  EXPECT_EQ(out[0], "existing");
}

TEST_F(ExplanationsTest_12, RecordMultipleItemsThenLookupAll_12) {
  const int NUM_ITEMS = 10;
  int items[NUM_ITEMS];
  for (int i = 0; i < NUM_ITEMS; i++) {
    items[i] = i;
    explanations_.Record(&items[i], "item %d", i);
  }
  for (int i = 0; i < NUM_ITEMS; i++) {
    std::vector<std::string> out;
    explanations_.LookupAndAppend(&items[i], &out);
    ASSERT_EQ(out.size(), 1u);
    char expected[64];
    snprintf(expected, sizeof(expected), "item %d", i);
    EXPECT_EQ(out[0], expected);
  }
}

TEST_F(ExplanationsTest_12, RecordLongMessage_12) {
  int item = 1;
  std::string long_str(1000, 'x');
  explanations_.Record(&item, "%s", long_str.c_str());
  std::vector<std::string> out;
  explanations_.LookupAndAppend(&item, &out);
  ASSERT_EQ(out.size(), 1u);
  EXPECT_EQ(out[0], long_str);
}
