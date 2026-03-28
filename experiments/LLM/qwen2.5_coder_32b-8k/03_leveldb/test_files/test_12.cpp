#include <gtest/gtest.h>

#include "leveldb/slice.h"



using namespace leveldb;



class SliceTest_12 : public ::testing::Test {

protected:

    virtual void SetUp() {

        // Setup if needed

    }



    virtual void TearDown() {

        // Cleanup if needed

    }

};



TEST_F(SliceTest_12, DefaultConstructorCreatesEmptySlice_12) {

    Slice s;

    EXPECT_TRUE(s.empty());

    EXPECT_EQ(0U, s.size());

}



TEST_F(SliceTest_12, CharPointerAndSizeConstructorWorks_12) {

    const char* data = "hello";

    size_t size = 5;

    Slice s(data, size);

    EXPECT_FALSE(s.empty());

    EXPECT_EQ(size, s.size());

    EXPECT_STREQ(data, s.data());

}



TEST_F(SliceTest_12, StringConstructorWorks_12) {

    std::string data = "world";

    Slice s(data);

    EXPECT_FALSE(s.empty());

    EXPECT_EQ(data.size(), s.size());

    EXPECT_STREQ(data.c_str(), s.data());

}



TEST_F(SliceTest_12, CharPointerConstructorWithNullTerminationWorks_12) {

    const char* data = "test";

    Slice s(data);

    EXPECT_FALSE(s.empty());

    EXPECT_EQ(strlen(data), s.size());

    EXPECT_STREQ(data, s.data());

}



TEST_F(SliceTest_12, CopyConstructorCreatesIdenticalSlice_12) {

    Slice original("copy");

    Slice copy(original);

    EXPECT_EQ(original.size(), copy.size());

    EXPECT_STREQ(original.data(), copy.data());

}



TEST_F(SliceTest_12, AssignmentOperatorCreatesIdenticalSlice_12) {

    Slice original("assign");

    Slice assigned = original;

    EXPECT_EQ(original.size(), assigned.size());

    EXPECT_STREQ(original.data(), assigned.data());

}



TEST_F(SliceTest_12, CompareMethodReturnsZeroForEqualSlices_12) {

    Slice s1("equal");

    Slice s2("equal");

    EXPECT_EQ(0, s1.compare(s2));

}



TEST_F(SliceTest_12, CompareMethodReturnsNegativeForSmallerSlice_12) {

    Slice s1("abc");

    Slice s2("def");

    EXPECT_LT(s1.compare(s2), 0);

}



TEST_F(SliceTest_12, CompareMethodReturnsPositiveForLargerSlice_12) {

    Slice s1("xyz");

    Slice s2("uvw");

    EXPECT_GT(s1.compare(s2), 0);

}



TEST_F(SliceTest_12, EmptyMethodReturnsTrueForEmptySlice_12) {

    Slice s;

    EXPECT_TRUE(s.empty());

}



TEST_F(SliceTest_12, SizeMethodReturnsCorrectSize_12) {

    const char* data = "example";

    size_t size = 7;

    Slice s(data, size);

    EXPECT_EQ(size, s.size());

}



TEST_F(SliceTest_12, DataMethodReturnsCorrectDataPointer_12) {

    const char* data = "sample";

    Slice s(data);

    EXPECT_STREQ(data, s.data());

}



TEST_F(SliceTest_12, BeginAndEndMethodsReturnCorrectPointers_12) {

    const char* data = "range";

    size_t size = 5;

    Slice s(data, size);

    EXPECT_EQ(s.begin(), s.data());

    EXPECT_EQ(s.end(), s.data() + size);

}



TEST_F(SliceTest_12, OperatorBracketReturnsCorrectCharacter_12) {

    const char* data = "index";

    size_t size = 5;

    Slice s(data, size);

    for (size_t i = 0; i < size; ++i) {

        EXPECT_EQ(s[i], data[i]);

    }

}



TEST_F(SliceTest_12, ClearMethodResetsSliceToEmpty_12) {

    Slice s("clear");

    s.clear();

    EXPECT_TRUE(s.empty());

    EXPECT_EQ(0U, s.size());

}



TEST_F(SliceTest_12, RemovePrefixRemovesCorrectNumberOfCharacters_12) {

    Slice s("prefix");

    size_t toRemove = 3;

    s.remove_prefix(toRemove);

    EXPECT_EQ(strlen("prefix") - toRemove, s.size());

    EXPECT_STREQ(s.data(), "fix");

}



TEST_F(SliceTest_12, ToStringMethodReturnsCorrectString_12) {

    std::string data = "convert";

    Slice s(data);

    EXPECT_EQ(data, s.ToString());

}



TEST_F(SliceTest_12, StartsWidthReturnsTrueForPrefixMatch_12) {

    Slice s("prefix_match");

    Slice prefix("prefix");

    EXPECT_TRUE(s.starts_with(prefix));

}



TEST_F(SliceTest_12, StartsWidthReturnsFalseForNonPrefixMatch_12) {

    Slice s("prefix_match");

    Slice nonPrefix("suffix");

    EXPECT_FALSE(s.starts_with(nonPrefix));

}
