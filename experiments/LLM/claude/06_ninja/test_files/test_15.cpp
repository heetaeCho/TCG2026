#include "gtest/gtest.h"
#include "explanations.h"
#include <vector>
#include <string>

// Tests for Explanations struct
class ExplanationsTest_15 : public ::testing::Test {
protected:
  Explanations explanations_;
};

TEST_F(ExplanationsTest_15, RecordAndLookup_15) {
  int item = 42;
  explanations_.Record(&item, "test message %d", 123);
  
  std::vector<std::string> out;
  explanations_.LookupAndAppend(&item, &out);
  
  ASSERT_EQ(out.size(), 1u);
  EXPECT_EQ(out[0], "test message 123");
}

TEST_F(ExplanationsTest_15, LookupNonExistentItem_15) {
  int item = 42;
  std::vector<std::string> out;
  explanations_.LookupAndAppend(&item, &out);
  
  EXPECT_TRUE(out.empty());
}

TEST_F(ExplanationsTest_15, RecordMultipleMessagesForSameItem_15) {
  int item = 10;
  explanations_.Record(&item, "first message");
  explanations_.Record(&item, "second message");
  explanations_.Record(&item, "third message");
  
  std::vector<std::string> out;
  explanations_.LookupAndAppend(&item, &out);
  
  ASSERT_EQ(out.size(), 3u);
  EXPECT_EQ(out[0], "first message");
  EXPECT_EQ(out[1], "second message");
  EXPECT_EQ(out[2], "third message");
}

TEST_F(ExplanationsTest_15, RecordDifferentItems_15) {
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

TEST_F(ExplanationsTest_15, RecordWithFormatString_15) {
  int item = 0;
  explanations_.Record(&item, "value=%d, str=%s", 42, "hello");
  
  std::vector<std::string> out;
  explanations_.LookupAndAppend(&item, &out);
  
  ASSERT_EQ(out.size(), 1u);
  EXPECT_EQ(out[0], "value=42, str=hello");
}

TEST_F(ExplanationsTest_15, LookupAppendsToExistingVector_15) {
  int item = 5;
  explanations_.Record(&item, "new message");
  
  std::vector<std::string> out;
  out.push_back("existing message");
  
  explanations_.LookupAndAppend(&item, &out);
  
  ASSERT_EQ(out.size(), 2u);
  EXPECT_EQ(out[0], "existing message");
  EXPECT_EQ(out[1], "new message");
}

TEST_F(ExplanationsTest_15, RecordArgsDirectly_15) {
  // Test RecordArgs indirectly via Record (since Record calls RecordArgs)
  int item = 99;
  explanations_.Record(&item, "test %d %s", 7, "world");
  
  std::vector<std::string> out;
  explanations_.LookupAndAppend(&item, &out);
  
  ASSERT_EQ(out.size(), 1u);
  EXPECT_EQ(out[0], "test 7 world");
}

// Tests for OptionalExplanations struct
class OptionalExplanationsTest_15 : public ::testing::Test {
protected:
  Explanations explanations_;
};

TEST_F(OptionalExplanationsTest_15, ConstructedWithExplanations_15) {
  OptionalExplanations opt(&explanations_);
  EXPECT_EQ(opt.ptr(), &explanations_);
}

TEST_F(OptionalExplanationsTest_15, ConstructedWithNull_15) {
  OptionalExplanations opt(nullptr);
  EXPECT_EQ(opt.ptr(), nullptr);
}

TEST_F(OptionalExplanationsTest_15, RecordWithValidExplanations_15) {
  OptionalExplanations opt(&explanations_);
  
  int item = 1;
  opt.Record(&item, "optional message %d", 42);
  
  std::vector<std::string> out;
  explanations_.LookupAndAppend(&item, &out);
  
  ASSERT_EQ(out.size(), 1u);
  EXPECT_EQ(out[0], "optional message 42");
}

TEST_F(OptionalExplanationsTest_15, RecordWithNullExplanationsDoesNotCrash_15) {
  OptionalExplanations opt(nullptr);
  
  int item = 1;
  // Should not crash even though explanations_ is null
  opt.Record(&item, "this should be ignored %d", 42);
  // No way to verify the message was discarded other than no crash
}

TEST_F(OptionalExplanationsTest_15, LookupAndAppendWithValidExplanations_15) {
  OptionalExplanations opt(&explanations_);
  
  int item = 3;
  explanations_.Record(&item, "direct record");
  
  std::vector<std::string> out;
  opt.LookupAndAppend(&item, &out);
  
  ASSERT_EQ(out.size(), 1u);
  EXPECT_EQ(out[0], "direct record");
}

TEST_F(OptionalExplanationsTest_15, RecordMultipleViaOptional_15) {
  OptionalExplanations opt(&explanations_);
  
  int item = 7;
  opt.Record(&item, "msg1");
  opt.Record(&item, "msg2");
  
  std::vector<std::string> out;
  opt.LookupAndAppend(&item, &out);
  
  ASSERT_EQ(out.size(), 2u);
  EXPECT_EQ(out[0], "msg1");
  EXPECT_EQ(out[1], "msg2");
}

TEST_F(OptionalExplanationsTest_15, PtrReturnsCorrectPointer_15) {
  OptionalExplanations opt1(&explanations_);
  EXPECT_EQ(opt1.ptr(), &explanations_);
  
  OptionalExplanations opt2(nullptr);
  EXPECT_EQ(opt2.ptr(), nullptr);
}

TEST_F(OptionalExplanationsTest_15, RecordWithEmptyFormatString_15) {
  OptionalExplanations opt(&explanations_);
  
  int item = 0;
  opt.Record(&item, "");
  
  std::vector<std::string> out;
  explanations_.LookupAndAppend(&item, &out);
  
  ASSERT_EQ(out.size(), 1u);
  EXPECT_EQ(out[0], "");
}

TEST_F(OptionalExplanationsTest_15, RecordDifferentItemsViaOptional_15) {
  OptionalExplanations opt(&explanations_);
  
  int a = 1, b = 2;
  opt.Record(&a, "alpha");
  opt.Record(&b, "beta");
  
  std::vector<std::string> out_a, out_b;
  opt.LookupAndAppend(&a, &out_a);
  opt.LookupAndAppend(&b, &out_b);
  
  ASSERT_EQ(out_a.size(), 1u);
  EXPECT_EQ(out_a[0], "alpha");
  
  ASSERT_EQ(out_b.size(), 1u);
  EXPECT_EQ(out_b[0], "beta");
}

// Test that LookupAndAppend on non-existent item via OptionalExplanations
TEST_F(OptionalExplanationsTest_15, LookupNonExistentViaOptional_15) {
  OptionalExplanations opt(&explanations_);
  
  int item = 99;
  std::vector<std::string> out;
  opt.LookupAndAppend(&item, &out);
  
  EXPECT_TRUE(out.empty());
}
