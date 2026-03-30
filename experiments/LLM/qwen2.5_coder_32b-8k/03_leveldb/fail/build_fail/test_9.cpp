#include <gtest/gtest.h>

#include "leveldb/slice.h"



using namespace leveldb;



class SliceTest_9 : public ::testing::Test {

protected:

    Slice emptySlice;

    Slice charArraySlice;

    Slice stringSlice;

    Slice cStringSlice;



    SliceTest_9()

        : emptySlice(),

          charArraySlice("test", 4),

          stringSlice("example"),

          cStringSlice("cstring") {}

};



TEST_F(SliceTest_9, ToString_ReturnsCorrectString_9) {

    EXPECT_EQ(emptySlice.ToString(), "");

    EXPECT_EQ(charArraySlice.ToString(), "test");

    EXPECT_EQ(stringSlice.ToString(), "example");

    EXPECT_EQ(cStringSlice.ToString(), "cstring");

}



TEST_F(SliceTest_9, Data_ReturnsPointerToData_9) {

    EXPECT_EQ(memcmp(emptySlice.data(), "", 0), 0);

    EXPECT_EQ(memcmp(charArraySlice.data(), "test", 4), 0);

    EXPECT_EQ(memcmp(stringSlice.data(), "example", 7), 0);

    EXPECT_EQ(memcmp(cStringSlice.data(), "cstring", 7), 0);

}



TEST_F(SliceTest_9, Size_ReturnsCorrectSize_9) {

    EXPECT_EQ(emptySlice.size(), 0);

    EXPECT_EQ(charArraySlice.size(), 4);

    EXPECT_EQ(stringSlice.size(), 7);

    EXPECT_EQ(cStringSlice.size(), 7);

}



TEST_F(SliceTest_9, Empty_ReturnsTrueForEmptySlice_9) {

    EXPECT_TRUE(emptySlice.empty());

    EXPECT_FALSE(charArraySlice.empty());

    EXPECT_FALSE(stringSlice.empty());

    EXPECT_FALSE(cStringSlice.empty());

}



TEST_F(SliceTest_9, Begin_End_ReturnCorrectPointers_9) {

    EXPECT_EQ(emptySlice.begin(), emptySlice.end());

    EXPECT_EQ(charArraySlice.begin(), charArraySlice.data());

    EXPECT_EQ(charArraySlice.end(), charArraySlice.data() + 4);

    EXPECT_EQ(stringSlice.begin(), stringSlice.data());

    EXPECT_EQ(stringSlice.end(), stringSlice.data() + 7);

    EXPECT_EQ(cStringSlice.begin(), cStringSlice.data());

    EXPECT_EQ(cStringSlice.end(), cStringSlice.data() + 7);

}



TEST_F(SliceTest_9, OperatorIndex_ReturnsCorrectCharacter_9) {

    EXPECT_THROW(emptySlice[0], std::out_of_range); // Assuming out_of_range is thrown for empty slice

    EXPECT_EQ(charArraySlice[0], 't');

    EXPECT_EQ(stringSlice[1], 'x');

    EXPECT_EQ(cStringSlice[2], 'r');

}



TEST_F(SliceTest_9, Clear_ResetsSliceToEmpty_9) {

    charArraySlice.clear();

    stringSlice.clear();

    cStringSlice.clear();



    EXPECT_TRUE(charArraySlice.empty());

    EXPECT_TRUE(stringSlice.empty());

    EXPECT_TRUE(cStringSlice.empty());

}



TEST_F(SliceTest_9, RemovePrefix_ReducesSizeCorrectly_9) {

    Slice testSlice("remove", 6);

    testSlice.remove_prefix(2);

    EXPECT_EQ(testSlice.ToString(), "move");



    testSlice.remove_prefix(4);

    EXPECT_TRUE(testSlice.empty());



    // Boundary condition: removing more than size

    testSlice = Slice("boundary", 8);

    testSlice.remove_prefix(10);

    EXPECT_TRUE(testSlice.empty());

}



TEST_F(SliceTest_9, Compare_ReturnsCorrectResult_9) {

    Slice sliceA("abc");

    Slice sliceB("def");

    Slice sliceC("abc");



    EXPECT_LT(sliceA.compare(sliceB), 0); // "abc" < "def"

    EXPECT_GT(sliceB.compare(sliceA), 0); // "def" > "abc"

    EXPECT_EQ(sliceA.compare(sliceC), 0); // "abc" == "abc"

}



TEST_F(SliceTest_9, StartsWith_ReturnsCorrectBoolean_9) {

    Slice slice("prefixtest");

    Slice prefix("prefix");

    Slice nonPrefix("non");



    EXPECT_TRUE(slice.starts_with(prefix));

    EXPECT_FALSE(slice.starts_with(nonPrefix));

    EXPECT_TRUE(emptySlice.starts_with(emptySlice));

}
