#include "gtest/gtest.h"
#include "explanations.h"
#include <vector>
#include <string>
#include <cstdarg>

class ExplanationsTest_13 : public ::testing::Test {
protected:
    Explanations explanations_;
};

// Helper function to call Record with variadic args
static void CallRecord(Explanations* e, const void* item, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    e->RecordArgs(item, fmt, args);
    va_end(args);
}

TEST_F(ExplanationsTest_13, LookupOnEmptyReturnsNothing_13) {
    int dummy = 42;
    std::vector<std::string> out;
    explanations_.LookupAndAppend(&dummy, &out);
    EXPECT_TRUE(out.empty());
}

TEST_F(ExplanationsTest_13, RecordAndLookupSingleEntry_13) {
    int dummy = 1;
    explanations_.Record(&dummy, "hello %s", "world");
    std::vector<std::string> out;
    explanations_.LookupAndAppend(&dummy, &out);
    ASSERT_EQ(out.size(), 1u);
    EXPECT_EQ(out[0], "hello world");
}

TEST_F(ExplanationsTest_13, RecordArgsAndLookup_13) {
    int dummy = 2;
    CallRecord(&explanations_, &dummy, "value is %d", 123);
    std::vector<std::string> out;
    explanations_.LookupAndAppend(&dummy, &out);
    ASSERT_EQ(out.size(), 1u);
    EXPECT_EQ(out[0], "value is 123");
}

TEST_F(ExplanationsTest_13, RecordMultipleEntriesForSameItem_13) {
    int dummy = 3;
    explanations_.Record(&dummy, "first: %d", 1);
    explanations_.Record(&dummy, "second: %d", 2);
    explanations_.Record(&dummy, "third: %d", 3);
    std::vector<std::string> out;
    explanations_.LookupAndAppend(&dummy, &out);
    ASSERT_EQ(out.size(), 3u);
    EXPECT_EQ(out[0], "first: 1");
    EXPECT_EQ(out[1], "second: 2");
    EXPECT_EQ(out[2], "third: 3");
}

TEST_F(ExplanationsTest_13, DifferentItemsAreIndependent_13) {
    int item1 = 10;
    int item2 = 20;
    explanations_.Record(&item1, "item1: %s", "alpha");
    explanations_.Record(&item2, "item2: %s", "beta");

    std::vector<std::string> out1;
    explanations_.LookupAndAppend(&item1, &out1);
    ASSERT_EQ(out1.size(), 1u);
    EXPECT_EQ(out1[0], "item1: alpha");

    std::vector<std::string> out2;
    explanations_.LookupAndAppend(&item2, &out2);
    ASSERT_EQ(out2.size(), 1u);
    EXPECT_EQ(out2[0], "item2: beta");
}

TEST_F(ExplanationsTest_13, LookupNonExistentItemDoesNotModifyOutput_13) {
    int item1 = 100;
    int item2 = 200;
    explanations_.Record(&item1, "exists");

    std::vector<std::string> out;
    out.push_back("pre-existing");
    explanations_.LookupAndAppend(&item2, &out);
    ASSERT_EQ(out.size(), 1u);
    EXPECT_EQ(out[0], "pre-existing");
}

TEST_F(ExplanationsTest_13, LookupAndAppendAppendsToExistingVector_13) {
    int dummy = 5;
    explanations_.Record(&dummy, "new entry");

    std::vector<std::string> out;
    out.push_back("already here");
    explanations_.LookupAndAppend(&dummy, &out);
    ASSERT_EQ(out.size(), 2u);
    EXPECT_EQ(out[0], "already here");
    EXPECT_EQ(out[1], "new entry");
}

TEST_F(ExplanationsTest_13, RecordWithNoFormatArgs_13) {
    int dummy = 6;
    explanations_.Record(&dummy, "plain message");
    std::vector<std::string> out;
    explanations_.LookupAndAppend(&dummy, &out);
    ASSERT_EQ(out.size(), 1u);
    EXPECT_EQ(out[0], "plain message");
}

TEST_F(ExplanationsTest_13, RecordWithMultipleFormatSpecifiers_13) {
    int dummy = 7;
    explanations_.Record(&dummy, "%s=%d (%.2f)", "count", 42, 3.14);
    std::vector<std::string> out;
    explanations_.LookupAndAppend(&dummy, &out);
    ASSERT_EQ(out.size(), 1u);
    EXPECT_EQ(out[0], "count=42 (3.14)");
}

TEST_F(ExplanationsTest_13, RecordEmptyString_13) {
    int dummy = 8;
    explanations_.Record(&dummy, "");
    std::vector<std::string> out;
    explanations_.LookupAndAppend(&dummy, &out);
    ASSERT_EQ(out.size(), 1u);
    EXPECT_EQ(out[0], "");
}

TEST_F(ExplanationsTest_13, NullptrAsItem_13) {
    explanations_.Record(nullptr, "null item %d", 99);
    std::vector<std::string> out;
    explanations_.LookupAndAppend(nullptr, &out);
    ASSERT_EQ(out.size(), 1u);
    EXPECT_EQ(out[0], "null item 99");
}

TEST_F(ExplanationsTest_13, RecordArgsWithMultipleFormats_13) {
    int dummy = 9;
    CallRecord(&explanations_, &dummy, "a=%d b=%s c=%x", 10, "hello", 255);
    std::vector<std::string> out;
    explanations_.LookupAndAppend(&dummy, &out);
    ASSERT_EQ(out.size(), 1u);
    EXPECT_EQ(out[0], "a=10 b=hello c=ff");
}

TEST_F(ExplanationsTest_13, LookupSameItemMultipleTimes_13) {
    int dummy = 11;
    explanations_.Record(&dummy, "entry");

    std::vector<std::string> out1;
    explanations_.LookupAndAppend(&dummy, &out1);
    ASSERT_EQ(out1.size(), 1u);
    EXPECT_EQ(out1[0], "entry");

    // Lookup again - the data should still be there
    std::vector<std::string> out2;
    explanations_.LookupAndAppend(&dummy, &out2);
    ASSERT_EQ(out2.size(), 1u);
    EXPECT_EQ(out2[0], "entry");
}

TEST_F(ExplanationsTest_13, LongFormattedString_13) {
    int dummy = 12;
    // Create a string that's long but within 1024 buffer limit
    std::string longStr(500, 'A');
    explanations_.Record(&dummy, "prefix_%s_suffix", longStr.c_str());
    std::vector<std::string> out;
    explanations_.LookupAndAppend(&dummy, &out);
    ASSERT_EQ(out.size(), 1u);
    std::string expected = "prefix_" + longStr + "_suffix";
    EXPECT_EQ(out[0], expected);
}

TEST_F(ExplanationsTest_13, RecordArgsThenRecordMixed_13) {
    int dummy = 14;
    CallRecord(&explanations_, &dummy, "via args: %d", 1);
    explanations_.Record(&dummy, "via record: %d", 2);
    std::vector<std::string> out;
    explanations_.LookupAndAppend(&dummy, &out);
    ASSERT_EQ(out.size(), 2u);
    EXPECT_EQ(out[0], "via args: 1");
    EXPECT_EQ(out[1], "via record: 2");
}
