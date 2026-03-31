#include "gtest/gtest.h"
#include "explanations.h"
#include <vector>
#include <string>
#include <cstdarg>

// Test fixture for OptionalExplanations
class OptionalExplanationsTest_18 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that ptr() returns nullptr when constructed with nullptr
TEST_F(OptionalExplanationsTest_18, PtrReturnsNullWhenConstructedWithNull_18) {
    OptionalExplanations opt(nullptr);
    EXPECT_EQ(nullptr, opt.ptr());
}

// Test that ptr() returns the provided Explanations pointer
TEST_F(OptionalExplanationsTest_18, PtrReturnsProvidedExplanations_18) {
    Explanations explanations;
    OptionalExplanations opt(&explanations);
    EXPECT_EQ(&explanations, opt.ptr());
}

// Test Record and LookupAndAppend with a valid Explanations object
TEST_F(OptionalExplanationsTest_18, RecordAndLookupWithValidExplanations_18) {
    Explanations explanations;
    OptionalExplanations opt(&explanations);

    int item = 42;
    opt.Record(&item, "test explanation %d", 123);

    std::vector<std::string> out;
    opt.LookupAndAppend(&item, &out);

    ASSERT_FALSE(out.empty());
    EXPECT_NE(std::string::npos, out[0].find("test explanation 123"));
}

// Test that Record with nullptr Explanations does not crash
TEST_F(OptionalExplanationsTest_18, RecordWithNullExplanationsDoesNotCrash_18) {
    OptionalExplanations opt(nullptr);
    int item = 42;
    // Should be a no-op and not crash
    opt.Record(&item, "test explanation %d", 123);
}

// Test that LookupAndAppend with nullptr Explanations does not crash
TEST_F(OptionalExplanationsTest_18, LookupAndAppendWithNullExplanationsDoesNotCrash_18) {
    OptionalExplanations opt(nullptr);
    int item = 42;
    std::vector<std::string> out;
    // Should be a no-op and not crash
    opt.LookupAndAppend(&item, &out);
    EXPECT_TRUE(out.empty());
}

// Test LookupAndAppend for an item that was never recorded
TEST_F(OptionalExplanationsTest_18, LookupAndAppendForUnrecordedItem_18) {
    Explanations explanations;
    OptionalExplanations opt(&explanations);

    int item1 = 1;
    int item2 = 2;
    opt.Record(&item1, "explanation for item1");

    std::vector<std::string> out;
    opt.LookupAndAppend(&item2, &out);
    // item2 was never recorded, so nothing should be appended
    EXPECT_TRUE(out.empty());
}

// Test multiple Records for the same item
TEST_F(OptionalExplanationsTest_18, MultipleRecordsForSameItem_18) {
    Explanations explanations;
    OptionalExplanations opt(&explanations);

    int item = 10;
    opt.Record(&item, "first explanation");
    opt.Record(&item, "second explanation");

    std::vector<std::string> out;
    opt.LookupAndAppend(&item, &out);

    // At least one explanation should be present
    EXPECT_FALSE(out.empty());
}

// Test Record with format string containing multiple arguments
TEST_F(OptionalExplanationsTest_18, RecordWithMultipleFormatArgs_18) {
    Explanations explanations;
    OptionalExplanations opt(&explanations);

    int item = 99;
    opt.Record(&item, "value=%d name=%s", 42, "test");

    std::vector<std::string> out;
    opt.LookupAndAppend(&item, &out);

    ASSERT_FALSE(out.empty());
    EXPECT_NE(std::string::npos, out[0].find("value=42"));
    EXPECT_NE(std::string::npos, out[0].find("name=test"));
}

// Test that LookupAndAppend appends to existing vector content
TEST_F(OptionalExplanationsTest_18, LookupAndAppendAppendsToExistingVector_18) {
    Explanations explanations;
    OptionalExplanations opt(&explanations);

    int item = 5;
    opt.Record(&item, "new explanation");

    std::vector<std::string> out;
    out.push_back("existing entry");
    opt.LookupAndAppend(&item, &out);

    EXPECT_GE(out.size(), 2u);
    EXPECT_EQ("existing entry", out[0]);
}

// Test Record with simple string (no format arguments)
TEST_F(OptionalExplanationsTest_18, RecordWithSimpleString_18) {
    Explanations explanations;
    OptionalExplanations opt(&explanations);

    int item = 7;
    opt.Record(&item, "simple explanation");

    std::vector<std::string> out;
    opt.LookupAndAppend(&item, &out);

    ASSERT_FALSE(out.empty());
    EXPECT_NE(std::string::npos, out[0].find("simple explanation"));
}

// Test different items are stored independently
TEST_F(OptionalExplanationsTest_18, DifferentItemsAreIndependent_18) {
    Explanations explanations;
    OptionalExplanations opt(&explanations);

    int item1 = 1;
    int item2 = 2;
    opt.Record(&item1, "explanation for item1");
    opt.Record(&item2, "explanation for item2");

    std::vector<std::string> out1;
    opt.LookupAndAppend(&item1, &out1);
    ASSERT_FALSE(out1.empty());
    EXPECT_NE(std::string::npos, out1[0].find("item1"));

    std::vector<std::string> out2;
    opt.LookupAndAppend(&item2, &out2);
    ASSERT_FALSE(out2.empty());
    EXPECT_NE(std::string::npos, out2[0].find("item2"));
}
