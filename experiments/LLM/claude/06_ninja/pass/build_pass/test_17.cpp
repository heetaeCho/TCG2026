#include "gtest/gtest.h"
#include "explanations.h"
#include <vector>
#include <string>

// Tests for Explanations struct
class ExplanationsTest_17 : public ::testing::Test {
protected:
    Explanations explanations_;
};

TEST_F(ExplanationsTest_17, LookupAndAppendWithNoRecords_17) {
    int item = 42;
    std::vector<std::string> out;
    explanations_.LookupAndAppend(&item, &out);
    EXPECT_TRUE(out.empty());
}

TEST_F(ExplanationsTest_17, RecordAndLookup_17) {
    int item = 1;
    explanations_.Record(&item, "test explanation");
    std::vector<std::string> out;
    explanations_.LookupAndAppend(&item, &out);
    ASSERT_EQ(out.size(), 1u);
    EXPECT_EQ(out[0], "test explanation");
}

TEST_F(ExplanationsTest_17, RecordMultipleForSameItem_17) {
    int item = 1;
    explanations_.Record(&item, "first");
    explanations_.Record(&item, "second");
    std::vector<std::string> out;
    explanations_.LookupAndAppend(&item, &out);
    ASSERT_EQ(out.size(), 2u);
    EXPECT_EQ(out[0], "first");
    EXPECT_EQ(out[1], "second");
}

TEST_F(ExplanationsTest_17, RecordWithFormatString_17) {
    int item = 1;
    explanations_.Record(&item, "value is %d", 42);
    std::vector<std::string> out;
    explanations_.LookupAndAppend(&item, &out);
    ASSERT_EQ(out.size(), 1u);
    EXPECT_EQ(out[0], "value is 42");
}

TEST_F(ExplanationsTest_17, RecordWithStringFormat_17) {
    int item = 1;
    explanations_.Record(&item, "name is %s", "ninja");
    std::vector<std::string> out;
    explanations_.LookupAndAppend(&item, &out);
    ASSERT_EQ(out.size(), 1u);
    EXPECT_EQ(out[0], "name is ninja");
}

TEST_F(ExplanationsTest_17, LookupDifferentItems_17) {
    int item1 = 1;
    int item2 = 2;
    explanations_.Record(&item1, "for item1");
    explanations_.Record(&item2, "for item2");

    std::vector<std::string> out1;
    explanations_.LookupAndAppend(&item1, &out1);
    ASSERT_EQ(out1.size(), 1u);
    EXPECT_EQ(out1[0], "for item1");

    std::vector<std::string> out2;
    explanations_.LookupAndAppend(&item2, &out2);
    ASSERT_EQ(out2.size(), 1u);
    EXPECT_EQ(out2[0], "for item2");
}

TEST_F(ExplanationsTest_17, LookupUnknownItem_17) {
    int item1 = 1;
    int item2 = 2;
    explanations_.Record(&item1, "only for item1");

    std::vector<std::string> out;
    explanations_.LookupAndAppend(&item2, &out);
    EXPECT_TRUE(out.empty());
}

TEST_F(ExplanationsTest_17, LookupAndAppendAppendsToExistingVector_17) {
    int item = 1;
    explanations_.Record(&item, "recorded");

    std::vector<std::string> out;
    out.push_back("existing");
    explanations_.LookupAndAppend(&item, &out);
    ASSERT_EQ(out.size(), 2u);
    EXPECT_EQ(out[0], "existing");
    EXPECT_EQ(out[1], "recorded");
}

TEST_F(ExplanationsTest_17, RecordWithNullItem_17) {
    explanations_.Record(nullptr, "null item explanation");
    std::vector<std::string> out;
    explanations_.LookupAndAppend(nullptr, &out);
    ASSERT_EQ(out.size(), 1u);
    EXPECT_EQ(out[0], "null item explanation");
}

// Tests for OptionalExplanations struct
class OptionalExplanationsTest_17 : public ::testing::Test {
protected:
};

TEST_F(OptionalExplanationsTest_17, NullExplanationsPtr_17) {
    OptionalExplanations opt(nullptr);
    EXPECT_EQ(opt.ptr(), nullptr);
}

TEST_F(OptionalExplanationsTest_17, NonNullExplanationsPtr_17) {
    Explanations explanations;
    OptionalExplanations opt(&explanations);
    EXPECT_EQ(opt.ptr(), &explanations);
}

TEST_F(OptionalExplanationsTest_17, LookupAndAppendWithNullExplanations_17) {
    OptionalExplanations opt(nullptr);
    int item = 1;
    std::vector<std::string> out;
    // Should not crash when explanations_ is null
    opt.LookupAndAppend(&item, &out);
    EXPECT_TRUE(out.empty());
}

TEST_F(OptionalExplanationsTest_17, LookupAndAppendWithValidExplanations_17) {
    Explanations explanations;
    OptionalExplanations opt(&explanations);
    int item = 1;
    explanations.Record(&item, "test");

    std::vector<std::string> out;
    opt.LookupAndAppend(&item, &out);
    ASSERT_EQ(out.size(), 1u);
    EXPECT_EQ(out[0], "test");
}

TEST_F(OptionalExplanationsTest_17, RecordWithNullExplanations_17) {
    OptionalExplanations opt(nullptr);
    int item = 1;
    // Should not crash when explanations_ is null
    opt.Record(&item, "should not crash %d", 42);
    std::vector<std::string> out;
    opt.LookupAndAppend(&item, &out);
    EXPECT_TRUE(out.empty());
}

TEST_F(OptionalExplanationsTest_17, RecordWithValidExplanations_17) {
    Explanations explanations;
    OptionalExplanations opt(&explanations);
    int item = 1;
    opt.Record(&item, "recorded via optional %d", 99);

    std::vector<std::string> out;
    opt.LookupAndAppend(&item, &out);
    ASSERT_EQ(out.size(), 1u);
    EXPECT_EQ(out[0], "recorded via optional 99");
}

TEST_F(OptionalExplanationsTest_17, RecordAndLookupThroughDifferentPaths_17) {
    Explanations explanations;
    OptionalExplanations opt(&explanations);
    int item = 1;

    // Record through OptionalExplanations, lookup through Explanations directly
    opt.Record(&item, "via optional");
    std::vector<std::string> out;
    explanations.LookupAndAppend(&item, &out);
    ASSERT_EQ(out.size(), 1u);
    EXPECT_EQ(out[0], "via optional");
}

TEST_F(OptionalExplanationsTest_17, RecordDirectlyLookupThroughOptional_17) {
    Explanations explanations;
    OptionalExplanations opt(&explanations);
    int item = 1;

    // Record through Explanations directly, lookup through OptionalExplanations
    explanations.Record(&item, "via direct");
    std::vector<std::string> out;
    opt.LookupAndAppend(&item, &out);
    ASSERT_EQ(out.size(), 1u);
    EXPECT_EQ(out[0], "via direct");
}

TEST_F(OptionalExplanationsTest_17, RecordArgsWithNullExplanations_17) {
    OptionalExplanations opt(nullptr);
    int item = 1;
    // RecordArgs with null explanations should not crash
    // We can't easily call RecordArgs directly without va_list, but Record
    // internally calls RecordArgs, so testing Record with null is sufficient.
    opt.Record(&item, "test %s", "value");
    // No crash expected
}

TEST_F(OptionalExplanationsTest_17, MultipleRecordsViaOptional_17) {
    Explanations explanations;
    OptionalExplanations opt(&explanations);
    int item = 1;

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

TEST_F(OptionalExplanationsTest_17, PtrReturnsCorrectPointer_17) {
    Explanations explanations;
    OptionalExplanations opt(&explanations);
    EXPECT_EQ(opt.ptr(), &explanations);
}

TEST_F(OptionalExplanationsTest_17, PtrReturnsNullForNullInit_17) {
    OptionalExplanations opt(nullptr);
    EXPECT_EQ(opt.ptr(), nullptr);
}
