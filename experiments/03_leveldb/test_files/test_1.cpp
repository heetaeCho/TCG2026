#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "leveldb/slice.h"



using namespace leveldb;



class SliceTest_1 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



TEST_F(SliceTest_1, DefaultConstructorCreatesEmptySlice_1) {

    Slice s;

    EXPECT_EQ(s.data(), "");

    EXPECT_EQ(s.size(), 0);

    EXPECT_TRUE(s.empty());

}



TEST_F(SliceTest_1, ConstructorWithCharArrayAndSizeSetsDataAndSize_1) {

    const char* data = "hello";

    size_t size = 5;

    Slice s(data, size);

    EXPECT_EQ(s.data(), data);

    EXPECT_EQ(s.size(), size);

    EXPECT_FALSE(s.empty());

}



TEST_F(SliceTest_1, ConstructorWithStringLiteralSetsDataAndSize_1) {

    const char* data = "world";

    Slice s(data);

    EXPECT_EQ(s.data(), data);

    EXPECT_EQ(s.size(), strlen(data));

    EXPECT_FALSE(s.empty());

}



TEST_F(SliceTest_1, ConstructorWithStdStringSetsDataAndSize_1) {

    std::string str = "example";

    Slice s(str);

    EXPECT_EQ(s.data(), str.data());

    EXPECT_EQ(s.size(), str.size());

    EXPECT_FALSE(s.empty());

}



TEST_F(SliceTest_1, CopyConstructorCreatesIdenticalSlice_1) {

    const char* data = "test";

    size_t size = 4;

    Slice s1(data, size);

    Slice s2(s1);

    EXPECT_EQ(s2.data(), s1.data());

    EXPECT_EQ(s2.size(), s1.size());

}



TEST_F(SliceTest_1, AssignmentOperatorCreatesIdenticalSlice_1) {

    const char* data = "assign";

    size_t size = 6;

    Slice s1(data, size);

    Slice s2;

    s2 = s1;

    EXPECT_EQ(s2.data(), s1.data());

    EXPECT_EQ(s2.size(), s1.size());

}



TEST_F(SliceTest_1, CompareMethodReturnsZeroForEqualSlices_1) {

    const char* data = "equal";

    size_t size = 5;

    Slice s1(data, size);

    Slice s2(data, size);

    EXPECT_EQ(s1.compare(s2), 0);

}



TEST_F(SliceTest_1, CompareMethodReturnsNegativeForSmallerSlice_1) {

    const char* data1 = "abc";

    const char* data2 = "abcd";

    Slice s1(data1);

    Slice s2(data2);

    EXPECT_LT(s1.compare(s2), 0);

}



TEST_F(SliceTest_1, CompareMethodReturnsPositiveForLargerSlice_1) {

    const char* data1 = "abcd";

    const char* data2 = "abc";

    Slice s1(data1);

    Slice s2(data2);

    EXPECT_GT(s1.compare(s2), 0);

}



TEST_F(SliceTest_1, ToStringMethodReturnsEquivalentString_1) {

    const char* data = "string";

    Slice s(data);

    std::string str = s.ToString();

    EXPECT_EQ(str, data);

}



TEST_F(SliceTest_1, StartsWithMethodReturnsTrueForPrefix_1) {

    const char* data = "prefixtest";

    Slice s(data);

    Slice prefix("prefix");

    EXPECT_TRUE(s.starts_with(prefix));

}



TEST_F(SliceTest_1, StartsWithMethodReturnsFalseForNonPrefix_1) {

    const char* data = "prefixtest";

    Slice s(data);

    Slice non_prefix("nonprefix");

    EXPECT_FALSE(s.starts_with(non_prefix));

}



TEST_F(SliceTest_1, BeginAndEndMethodsReturnCorrectPointers_1) {

    const char* data = "beginend";

    Slice s(data);

    EXPECT_EQ(s.begin(), data);

    EXPECT_EQ(s.end(), data + strlen(data));

}



TEST_F(SliceTest_1, OperatorBracketReturnsCorrectCharacters_1) {

    const char* data = "bracket";

    Slice s(data);

    for (size_t i = 0; i < strlen(data); ++i) {

        EXPECT_EQ(s[i], data[i]);

    }

}



TEST_F(SliceTest_1, ClearMethodResetsSliceToEmpty_1) {

    const char* data = "clear";

    Slice s(data);

    s.clear();

    EXPECT_TRUE(s.empty());

    EXPECT_EQ(s.size(), 0);

}



TEST_F(SliceTest_1, RemovePrefixReducesSizeAndAdjustsDataPointer_1) {

    const char* data = "removeprefix";

    size_t prefix_size = 6;

    Slice s(data);

    s.remove_prefix(prefix_size);

    EXPECT_EQ(s.data(), data + prefix_size);

    EXPECT_EQ(s.size(), strlen(data) - prefix_size);

}



TEST_F(SliceTest_1, RemovePrefixWithFullSizeResultsInEmptySlice_1) {

    const char* data = "fullremove";

    Slice s(data);

    s.remove_prefix(strlen(data));

    EXPECT_TRUE(s.empty());

    EXPECT_EQ(s.size(), 0);

}
