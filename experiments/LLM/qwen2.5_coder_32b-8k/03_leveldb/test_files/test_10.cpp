#include <gtest/gtest.h>

#include "leveldb/slice.h"



class SliceTest_10 : public ::testing::Test {

protected:

    leveldb::Slice emptySlice;

    leveldb::Slice sliceHello;

    leveldb::Slice sliceWorld;

    leveldb::Slice sliceHelloWorld;



    void SetUp() override {

        emptySlice = leveldb::Slice();

        sliceHello = leveldb::Slice("hello");

        sliceWorld = leveldb::Slice("world");

        sliceHelloWorld = leveldb::Slice("helloworld");

    }

};



TEST_F(SliceTest_10, EmptySliceProperties_10) {

    EXPECT_TRUE(emptySlice.empty());

    EXPECT_EQ(emptySlice.size(), 0);

    EXPECT_STREQ(emptySlice.data(), "");

}



TEST_F(SliceTest_10, NonEmptySliceProperties_10) {

    EXPECT_FALSE(sliceHello.empty());

    EXPECT_EQ(sliceHello.size(), 5);

    EXPECT_STREQ(sliceHello.data(), "hello");

}



TEST_F(SliceTest_10, Starts_with_EmptyPrefix_10) {

    EXPECT_TRUE(sliceHello.starts_with(emptySlice));

}



TEST_F(SliceTest_10, Starts_with_Self_10) {

    EXPECT_TRUE(sliceHello.starts_with(sliceHello));

}



TEST_F(SliceTest_10, Starts_with_Substring_10) {

    EXPECT_FALSE(sliceHello.starts_with(sliceWorld));

    EXPECT_FALSE(sliceHello.starts_with(sliceHelloWorld));

    EXPECT_TRUE(sliceHelloWorld.starts_with(sliceHello));

}



TEST_F(SliceTest_10, Compare_EmptySlice_10) {

    EXPECT_EQ(emptySlice.compare(emptySlice), 0);

    EXPECT_LT(emptySlice.compare(sliceHello), 0);

    EXPECT_GT(sliceHello.compare(emptySlice), 0);

}



TEST_F(SliceTest_10, Compare_EqualSlices_10) {

    EXPECT_EQ(sliceHello.compare(sliceHello), 0);

}



TEST_F(SliceTest_10, Compare_DifferentSlices_10) {

    EXPECT_LT(sliceHello.compare(sliceWorld), 0);

    EXPECT_GT(sliceWorld.compare(sliceHello), 0);

}



TEST_F(SliceTest_10, ToString_Method_10) {

    EXPECT_EQ(emptySlice.ToString(), "");

    EXPECT_EQ(sliceHello.ToString(), "hello");

    EXPECT_EQ(sliceWorld.ToString(), "world");

    EXPECT_EQ(sliceHelloWorld.ToString(), "helloworld");

}



TEST_F(SliceTest_10, RemovePrefix_ValidRange_10) {

    leveldb::Slice temp = sliceHello;

    temp.remove_prefix(2);

    EXPECT_EQ(temp.size(), 3);

    EXPECT_STREQ(temp.data(), "llo");



    temp = sliceHelloWorld;

    temp.remove_prefix(5);

    EXPECT_EQ(temp.size(), 6);

    EXPECT_STREQ(temp.data(), "world");

}



TEST_F(SliceTest_10, RemovePrefix_OutOfRange_10) {

    leveldb::Slice temp = sliceHello;

    temp.remove_prefix(sliceHello.size());

    EXPECT_EQ(temp.size(), 0);

    EXPECT_STREQ(temp.data(), "");



    temp = sliceWorld;

    temp.remove_prefix(10); // Beyond the length

    EXPECT_EQ(temp.size(), 0);

    EXPECT_STREQ(temp.data(), "");

}
