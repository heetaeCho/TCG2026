#include "gtest/gtest.h"
#include "explanations.h"
#include <vector>
#include <string>

class ExplanationsTest_14 : public ::testing::Test {
protected:
    Explanations explanations_;
};

// Test that LookupAndAppend does nothing when no records exist for the item
TEST_F(ExplanationsTest_14, LookupAndAppendNoRecords_14) {
    int item = 42;
    std::vector<std::string> out;
    explanations_.LookupAndAppend(&item, &out);
    EXPECT_TRUE(out.empty());
}

// Test that Record stores an explanation and LookupAndAppend retrieves it
TEST_F(ExplanationsTest_14, RecordAndLookupSingleExplanation_14) {
    int item = 1;
    explanations_.Record(&item, "test explanation");
    std::vector<std::string> out;
    explanations_.LookupAndAppend(&item, &out);
    ASSERT_EQ(out.size(), 1u);
    EXPECT_EQ(out[0], "test explanation");
}

// Test that multiple explanations for the same item are all appended
TEST_F(ExplanationsTest_14, RecordMultipleExplanationsForSameItem_14) {
    int item = 2;
    explanations_.Record(&item, "first");
    explanations_.Record(&item, "second");
    explanations_.Record(&item, "third");
    std::vector<std::string> out;
    explanations_.LookupAndAppend(&item, &out);
    ASSERT_EQ(out.size(), 3u);
    EXPECT_EQ(out[0], "first");
    EXPECT_EQ(out[1], "second");
    EXPECT_EQ(out[2], "third");
}

// Test that LookupAndAppend with a different item returns nothing
TEST_F(ExplanationsTest_14, LookupDifferentItemReturnsNothing_14) {
    int item1 = 10;
    int item2 = 20;
    explanations_.Record(&item1, "only for item1");
    std::vector<std::string> out;
    explanations_.LookupAndAppend(&item2, &out);
    EXPECT_TRUE(out.empty());
}

// Test that LookupAndAppend appends to an existing vector rather than replacing
TEST_F(ExplanationsTest_14, LookupAndAppendAppendsToExistingVector_14) {
    int item = 3;
    explanations_.Record(&item, "new entry");
    std::vector<std::string> out;
    out.push_back("existing entry");
    explanations_.LookupAndAppend(&item, &out);
    ASSERT_EQ(out.size(), 2u);
    EXPECT_EQ(out[0], "existing entry");
    EXPECT_EQ(out[1], "new entry");
}

// Test Record with format string containing arguments
TEST_F(ExplanationsTest_14, RecordWithFormatString_14) {
    int item = 4;
    explanations_.Record(&item, "value is %d", 42);
    std::vector<std::string> out;
    explanations_.LookupAndAppend(&item, &out);
    ASSERT_EQ(out.size(), 1u);
    EXPECT_EQ(out[0], "value is 42");
}

// Test Record with string format argument
TEST_F(ExplanationsTest_14, RecordWithStringFormatArgument_14) {
    int item = 5;
    explanations_.Record(&item, "name is %s", "ninja");
    std::vector<std::string> out;
    explanations_.LookupAndAppend(&item, &out);
    ASSERT_EQ(out.size(), 1u);
    EXPECT_EQ(out[0], "name is ninja");
}

// Test that different items maintain separate explanation lists
TEST_F(ExplanationsTest_14, DifferentItemsSeparateExplanations_14) {
    int item1 = 100;
    int item2 = 200;
    explanations_.Record(&item1, "explanation for item1");
    explanations_.Record(&item2, "explanation for item2");

    std::vector<std::string> out1;
    explanations_.LookupAndAppend(&item1, &out1);
    ASSERT_EQ(out1.size(), 1u);
    EXPECT_EQ(out1[0], "explanation for item1");

    std::vector<std::string> out2;
    explanations_.LookupAndAppend(&item2, &out2);
    ASSERT_EQ(out2.size(), 1u);
    EXPECT_EQ(out2[0], "explanation for item2");
}

// Test LookupAndAppend with nullptr as item when nothing is recorded for nullptr
TEST_F(ExplanationsTest_14, LookupNullptrNoRecords_14) {
    std::vector<std::string> out;
    explanations_.LookupAndAppend(nullptr, &out);
    EXPECT_TRUE(out.empty());
}

// Test Record and Lookup with nullptr as item
TEST_F(ExplanationsTest_14, RecordAndLookupNullptrItem_14) {
    explanations_.Record(nullptr, "null item explanation");
    std::vector<std::string> out;
    explanations_.LookupAndAppend(nullptr, &out);
    ASSERT_EQ(out.size(), 1u);
    EXPECT_EQ(out[0], "null item explanation");
}

// Test calling LookupAndAppend multiple times accumulates results
TEST_F(ExplanationsTest_14, MultipleLookupAndAppendCalls_14) {
    int item = 6;
    explanations_.Record(&item, "entry");
    std::vector<std::string> out;
    explanations_.LookupAndAppend(&item, &out);
    explanations_.LookupAndAppend(&item, &out);
    ASSERT_EQ(out.size(), 2u);
    EXPECT_EQ(out[0], "entry");
    EXPECT_EQ(out[1], "entry");
}

// Test Record with multiple format arguments
TEST_F(ExplanationsTest_14, RecordWithMultipleFormatArgs_14) {
    int item = 7;
    explanations_.Record(&item, "%s has %d items at %p", "list", 5, (void*)0x1234);
    std::vector<std::string> out;
    explanations_.LookupAndAppend(&item, &out);
    ASSERT_EQ(out.size(), 1u);
    // We can at least verify it starts with "list has 5 items at"
    EXPECT_NE(out[0].find("list has 5 items at"), std::string::npos);
}

// Test Record with empty format string
TEST_F(ExplanationsTest_14, RecordWithEmptyFormatString_14) {
    int item = 8;
    explanations_.Record(&item, "");
    std::vector<std::string> out;
    explanations_.LookupAndAppend(&item, &out);
    ASSERT_EQ(out.size(), 1u);
    EXPECT_EQ(out[0], "");
}
