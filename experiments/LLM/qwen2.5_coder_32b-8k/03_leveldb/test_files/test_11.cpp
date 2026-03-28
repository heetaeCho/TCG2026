#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "leveldb/slice.h"

#include <string>



using namespace leveldb;

using ::testing::Eq;



class SliceTest_11 : public ::testing::Test {

protected:

    void SetUp() override {}

};



TEST_F(SliceTest_11, DefaultConstructorCreatesEmptySlice_11) {

    Slice s;

    EXPECT_EQ(s.size(), 0);

    EXPECT_STREQ(s.data(), "");

}



TEST_F(SliceTest_11, CharPtrAndSizeConstructorWorks_11) {

    const char* data = "hello";

    size_t size = 5;

    Slice s(data, size);

    EXPECT_EQ(s.size(), size);

    EXPECT_STREQ(s.data(), data);

}



TEST_F(SliceTest_11, StdStringConstructorWorks_11) {

    std::string str = "world";

    Slice s(str);

    EXPECT_EQ(s.size(), str.size());

    EXPECT_STREQ(s.data(), str.c_str());

}



TEST_F(SliceTest_11, CharPtrConstructorWorks_11) {

    const char* data = "example";

    Slice s(data);

    EXPECT_EQ(s.size(), strlen(data));

    EXPECT_STREQ(s.data(), data);

}



TEST_F(SliceTest_11, CopyConstructorWorks_11) {

    const char* data = "copytest";

    Slice original(data);

    Slice copy(original);

    EXPECT_EQ(copy.size(), original.size());

    EXPECT_STREQ(copy.data(), original.data());

}



TEST_F(SliceTest_11, AssignmentOperatorWorks_11) {

    const char* data = "assignment";

    Slice original(data);

    Slice assigned;

    assigned = original;

    EXPECT_EQ(assigned.size(), original.size());

    EXPECT_STREQ(assigned.data(), original.data());

}



TEST_F(SliceTest_11, CompareMethodReturnsZeroForEqualSlices_11) {

    const char* data = "equal";

    Slice s1(data);

    Slice s2(data);

    EXPECT_EQ(s1.compare(s2), 0);

}



TEST_F(SliceTest_11, CompareMethodReturnsNonZeroForDifferentSlices_11) {

    Slice s1("first");

    Slice s2("second");

    EXPECT_NE(s1.compare(s2), 0);

}



TEST_F(SliceTest_11, EmptyMethodReturnsTrueForEmptySlice_11) {

    Slice s;

    EXPECT_TRUE(s.empty());

}



TEST_F(SliceTest_11, EmptyMethodReturnsFalseForNonEmptySlice_11) {

    Slice s("nonempty");

    EXPECT_FALSE(s.empty());

}



TEST_F(SliceTest_11, BeginAndEndMethodsReturnCorrectPointers_11) {

    const char* data = "beginend";

    Slice s(data);

    EXPECT_EQ(s.begin(), data);

    EXPECT_EQ(s.end(), data + strlen(data));

}



TEST_F(SliceTest_11, OperatorBracketAccessWorks_11) {

    Slice s("index");

    EXPECT_EQ(s[0], 'i');

    EXPECT_EQ(s[1], 'n');

    EXPECT_EQ(s[2], 'd');

    EXPECT_EQ(s[3], 'e');

    EXPECT_EQ(s[4], 'x');

}



TEST_F(SliceTest_11, ClearMethodResetsSlice_11) {

    Slice s("clearme");

    s.clear();

    EXPECT_TRUE(s.empty());

}



TEST_F(SliceTest_11, RemovePrefixReducesSizeAndDataPointer_11) {

    const char* data = "removeprefix";

    size_t prefixSize = 6;

    Slice s(data);

    s.remove_prefix(prefixSize);

    EXPECT_EQ(s.size(), strlen(data) - prefixSize);

    EXPECT_STREQ(s.data(), data + prefixSize);

}



TEST_F(SliceTest_11, ToStringMethodReturnsCorrectString_11) {

    const char* data = "tostring";

    Slice s(data);

    std::string str = s.ToString();

    EXPECT_EQ(str, data);

}



TEST_F(SliceTest_11, StartsWithReturnsTrueForMatchingPrefix_11) {

    Slice s("startswithprefix");

    Slice prefix("start");

    EXPECT_TRUE(s.starts_with(prefix));

}



TEST_F(SliceTest_11, StartsWithReturnsFalseForNonMatchingPrefix_11) {

    Slice s("startswithprefix");

    Slice prefix("notmatch");

    EXPECT_FALSE(s.starts_with(prefix));

}
