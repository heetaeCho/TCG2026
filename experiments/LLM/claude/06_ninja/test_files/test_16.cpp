#include <gtest/gtest.h>
#include <cstdarg>
#include <vector>
#include <string>
#include "explanations.h"

// Helper function to call Record with variadic args
static void CallRecord(Explanations* e, const void* item, const char* fmt, ...) {
  va_list args;
  va_start(args, fmt);
  e->RecordArgs(item, fmt, args);
  va_end(args);
}

static void CallOptionalRecord(OptionalExplanations& opt, const void* item, const char* fmt, ...) {
  va_list args;
  va_start(args, fmt);
  opt.RecordArgs(item, fmt, args);
  va_end(args);
}

// ==================== Explanations Tests ====================

class ExplanationsTest_16 : public ::testing::Test {
 protected:
  Explanations explanations_;
};

TEST_F(ExplanationsTest_16, LookupEmptyReturnsNothing_16) {
  int item = 42;
  std::vector<std::string> out;
  explanations_.LookupAndAppend(&item, &out);
  EXPECT_TRUE(out.empty());
}

TEST_F(ExplanationsTest_16, RecordAndLookup_16) {
  int item = 1;
  explanations_.Record(&item, "hello %s", "world");
  std::vector<std::string> out;
  explanations_.LookupAndAppend(&item, &out);
  ASSERT_EQ(out.size(), 1u);
  EXPECT_EQ(out[0], "hello world");
}

TEST_F(ExplanationsTest_16, RecordMultipleForSameItem_16) {
  int item = 2;
  explanations_.Record(&item, "first %d", 1);
  explanations_.Record(&item, "second %d", 2);
  std::vector<std::string> out;
  explanations_.LookupAndAppend(&item, &out);
  ASSERT_EQ(out.size(), 2u);
  EXPECT_EQ(out[0], "first 1");
  EXPECT_EQ(out[1], "second 2");
}

TEST_F(ExplanationsTest_16, RecordDifferentItems_16) {
  int item1 = 10;
  int item2 = 20;
  explanations_.Record(&item1, "item1 info");
  explanations_.Record(&item2, "item2 info");

  std::vector<std::string> out1;
  explanations_.LookupAndAppend(&item1, &out1);
  ASSERT_EQ(out1.size(), 1u);
  EXPECT_EQ(out1[0], "item1 info");

  std::vector<std::string> out2;
  explanations_.LookupAndAppend(&item2, &out2);
  ASSERT_EQ(out2.size(), 1u);
  EXPECT_EQ(out2[0], "item2 info");
}

TEST_F(ExplanationsTest_16, LookupNonExistentItem_16) {
  int item1 = 1;
  int item2 = 2;
  explanations_.Record(&item1, "exists");

  std::vector<std::string> out;
  explanations_.LookupAndAppend(&item2, &out);
  EXPECT_TRUE(out.empty());
}

TEST_F(ExplanationsTest_16, RecordArgsDirectly_16) {
  int item = 5;
  CallRecord(&explanations_, &item, "value is %d", 99);

  std::vector<std::string> out;
  explanations_.LookupAndAppend(&item, &out);
  ASSERT_EQ(out.size(), 1u);
  EXPECT_EQ(out[0], "value is 99");
}

TEST_F(ExplanationsTest_16, LookupAppendToExistingVector_16) {
  int item = 3;
  explanations_.Record(&item, "new entry");

  std::vector<std::string> out;
  out.push_back("pre-existing");
  explanations_.LookupAndAppend(&item, &out);
  ASSERT_EQ(out.size(), 2u);
  EXPECT_EQ(out[0], "pre-existing");
  EXPECT_EQ(out[1], "new entry");
}

TEST_F(ExplanationsTest_16, RecordEmptyFormatString_16) {
  int item = 7;
  explanations_.Record(&item, "");
  std::vector<std::string> out;
  explanations_.LookupAndAppend(&item, &out);
  ASSERT_EQ(out.size(), 1u);
  EXPECT_EQ(out[0], "");
}

TEST_F(ExplanationsTest_16, RecordWithNullItemPointer_16) {
  explanations_.Record(nullptr, "null item");
  std::vector<std::string> out;
  explanations_.LookupAndAppend(nullptr, &out);
  ASSERT_EQ(out.size(), 1u);
  EXPECT_EQ(out[0], "null item");
}

// ==================== OptionalExplanations Tests ====================

class OptionalExplanationsTest_16 : public ::testing::Test {
 protected:
  Explanations explanations_;
};

TEST_F(OptionalExplanationsTest_16, ConstructWithNullptr_16) {
  OptionalExplanations opt(nullptr);
  EXPECT_EQ(opt.ptr(), nullptr);
}

TEST_F(OptionalExplanationsTest_16, ConstructWithValidPointer_16) {
  OptionalExplanations opt(&explanations_);
  EXPECT_EQ(opt.ptr(), &explanations_);
}

TEST_F(OptionalExplanationsTest_16, RecordWithNullExplanationsDoesNotCrash_16) {
  OptionalExplanations opt(nullptr);
  int item = 1;
  // Should be a no-op and not crash
  opt.Record(&item, "test %d", 42);
}

TEST_F(OptionalExplanationsTest_16, RecordArgsWithNullExplanationsDoesNotCrash_16) {
  OptionalExplanations opt(nullptr);
  int item = 1;
  CallOptionalRecord(opt, &item, "test %d", 42);
}

TEST_F(OptionalExplanationsTest_16, LookupAndAppendWithNullExplanations_16) {
  OptionalExplanations opt(nullptr);
  int item = 1;
  std::vector<std::string> out;
  opt.LookupAndAppend(&item, &out);
  EXPECT_TRUE(out.empty());
}

TEST_F(OptionalExplanationsTest_16, RecordDelegatesToExplanations_16) {
  OptionalExplanations opt(&explanations_);
  int item = 10;
  opt.Record(&item, "delegated %s", "message");

  std::vector<std::string> out;
  explanations_.LookupAndAppend(&item, &out);
  ASSERT_EQ(out.size(), 1u);
  EXPECT_EQ(out[0], "delegated message");
}

TEST_F(OptionalExplanationsTest_16, RecordArgsDelegatesToExplanations_16) {
  OptionalExplanations opt(&explanations_);
  int item = 20;
  CallOptionalRecord(opt, &item, "args %d", 123);

  std::vector<std::string> out;
  explanations_.LookupAndAppend(&item, &out);
  ASSERT_EQ(out.size(), 1u);
  EXPECT_EQ(out[0], "args 123");
}

TEST_F(OptionalExplanationsTest_16, LookupAndAppendDelegatesToExplanations_16) {
  OptionalExplanations opt(&explanations_);
  int item = 30;
  explanations_.Record(&item, "from explanations");

  std::vector<std::string> out;
  opt.LookupAndAppend(&item, &out);
  ASSERT_EQ(out.size(), 1u);
  EXPECT_EQ(out[0], "from explanations");
}

TEST_F(OptionalExplanationsTest_16, PtrReturnsCorrectPointer_16) {
  OptionalExplanations opt1(nullptr);
  EXPECT_EQ(opt1.ptr(), nullptr);

  OptionalExplanations opt2(&explanations_);
  EXPECT_EQ(opt2.ptr(), &explanations_);
}

TEST_F(OptionalExplanationsTest_16, MultipleRecordsViaOptional_16) {
  OptionalExplanations opt(&explanations_);
  int item = 40;
  opt.Record(&item, "first");
  opt.Record(&item, "second");
  opt.Record(&item, "third");

  std::vector<std::string> out;
  opt.LookupAndAppend(&item, &out);
  ASSERT_EQ(out.size(), 3u);
  EXPECT_EQ(out[0], "first");
  EXPECT_EQ(out[1], "second");
  EXPECT_EQ(out[2], "third");
}

TEST_F(OptionalExplanationsTest_16, LookupNonExistentItemViaOptional_16) {
  OptionalExplanations opt(&explanations_);
  int item1 = 50;
  int item2 = 60;
  opt.Record(&item1, "exists");

  std::vector<std::string> out;
  opt.LookupAndAppend(&item2, &out);
  EXPECT_TRUE(out.empty());
}
