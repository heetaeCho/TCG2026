#include <gtest/gtest.h>

#include "leveldb/slice.h"



using namespace leveldb;



class SliceTest_8 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup if needed

    }



    void TearDown() override {

        // Teardown if needed

    }

};



TEST_F(SliceTest_8, ConstructorWithCharPtrAndSize_8) {

    const char* str = "Hello";

    Slice slice(str, 5);

    EXPECT_STREQ(slice.data(), "Hello");

    EXPECT_EQ(slice.size(), 5);

}



TEST_F(SliceTest_8, ConstructorWithString_8) {

    std::string str = "World";

    Slice slice(str);

    EXPECT_STREQ(slice.data(), "World");

    EXPECT_EQ(slice.size(), 5);

}



TEST_F(SliceTest_8, ConstructorWithCharPtr_8) {

    const char* str = "HelloWorld";

    Slice slice(str);

    EXPECT_STREQ(slice.data(), "HelloWorld");

    EXPECT_EQ(slice.size(), 10);

}



TEST_F(SliceTest_8, CopyConstructor_8) {

    const char* str = "Copy";

    Slice original(str, 4);

    Slice copy(original);

    EXPECT_STREQ(copy.data(), "Copy");

    EXPECT_EQ(copy.size(), 4);

}



TEST_F(SliceTest_8, AssignmentOperator_8) {

    const char* str1 = "First";

    const char* str2 = "Second";

    Slice first(str1, 5);

    Slice second(str2, 6);

    first = second;

    EXPECT_STREQ(first.data(), "Second");

    EXPECT_EQ(first.size(), 6);

}



TEST_F(SliceTest_8, CompareEqual_8) {

    Slice slice1("Hello", 5);

    Slice slice2("Hello", 5);

    EXPECT_EQ(slice1.compare(slice2), 0);

}



TEST_F(SliceTest_8, CompareLess_8) {

    Slice slice1("Apple", 5);

    Slice slice2("Banana", 6);

    EXPECT_LT(slice1.compare(slice2), 0);

}



TEST_F(SliceTest_8, CompareGreater_8) {

    Slice slice1("Cherry", 6);

    Slice slice2("Berry", 5);

    EXPECT_GT(slice1.compare(slice2), 0);

}



TEST_F(SliceTest_8, EmptySlice_8) {

    Slice empty;

    EXPECT_TRUE(empty.empty());

    EXPECT_EQ(empty.size(), 0);

    EXPECT_STREQ(empty.data(), "");

}



TEST_F(SliceTest_8, RemovePrefix_NormalOperation_8) {

    Slice slice("HelloWorld", 10);

    slice.remove_prefix(5);

    EXPECT_STREQ(slice.data(), "World");

    EXPECT_EQ(slice.size(), 5);

}



TEST_F(SliceTest_8, RemovePrefix_BoundaryCondition_8) {

    Slice slice("Test", 4);

    slice.remove_prefix(4);

    EXPECT_TRUE(slice.empty());

    EXPECT_EQ(slice.size(), 0);

}



TEST_F(SliceTest_8, RemovePrefix_ExceptionalCase_8) {

    Slice slice("Edge", 4);

    EXPECT_DEATH(slice.remove_prefix(5), ".*assert.*");

}



TEST_F(SliceTest_8, ToString_8) {

    Slice slice("ConvertMe", 9);

    std::string result = slice.ToString();

    EXPECT_EQ(result, "ConvertMe");

}



TEST_F(SliceTest_8, StartsWith_True_8) {

    Slice slice("StartWithPrefix", 17);

    Slice prefix("Start");

    EXPECT_TRUE(slice.starts_with(prefix));

}



TEST_F(SliceTest_8, StartsWith_False_8) {

    Slice slice("NoPrefixHere", 14);

    Slice prefix("Prefix");

    EXPECT_FALSE(slice.starts_with(prefix));

}
