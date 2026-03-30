#include <gtest/gtest.h>

#include "util/coding.cc"



namespace {



class VarintLengthTest_445 : public ::testing::Test {

protected:

    // You can set up any common state here if needed.

};



TEST_F(VarintLengthTest_445, ZeroValue_ReturnsOne_445) {

    EXPECT_EQ(leveldb::VarintLength(0), 1);

}



TEST_F(VarintLengthTest_445, SingleByteMax_ReturnsOne_445) {

    EXPECT_EQ(leveldb::VarintLength(127), 1);

}



TEST_F(VarintLengthTest_445, TwoBytesMin_ReturnsTwo_445) {

    EXPECT_EQ(leveldb::VarintLength(128), 2);

}



TEST_F(VarintLengthTest_445, TwoBytesMax_ReturnsTwo_445) {

    EXPECT_EQ(leveldb::VarintLength(16383), 2);

}



TEST_F(VarintLengthTest_445, ThreeBytesMin_ReturnsThree_445) {

    EXPECT_EQ(leveldb::VarintLength(16384), 3);

}



TEST_F(VarintLengthTest_445, ThreeBytesMax_ReturnsThree_445) {

    EXPECT_EQ(leveldb::VarintLength(2097151), 3);

}



TEST_F(VarintLengthTest_445, FourBytesMin_ReturnsFour_445) {

    EXPECT_EQ(leveldb::VarintLength(2097152), 4);

}



TEST_F(VarintLengthTest_445, FourBytesMax_ReturnsFour_445) {

    EXPECT_EQ(leveldb::VarintLength(268435455), 4);

}



TEST_F(VarintLengthTest_445, FiveBytesMin_ReturnsFive_445) {

    EXPECT_EQ(leveldb::VarintLength(268435456), 5);

}



TEST_F(VarintLengthTest_445, FiveBytesMax_ReturnsFive_445) {

    EXPECT_EQ(leveldb::VarintLength(34359738367), 5);

}



TEST_F(VarintLengthTest_445, SixBytesMin_ReturnsSix_445) {

    EXPECT_EQ(leveldb::VarintLength(34359738368), 6);

}



TEST_F(VarintLengthTest_445, SixBytesMax_ReturnsSix_445) {

    EXPECT_EQ(leveldb::VarintLength(4398046511103), 6);

}



TEST_F(VarintLengthTest_445, SevenBytesMin_ReturnsSeven_445) {

    EXPECT_EQ(leveldb::VarintLength(4398046511104), 7);

}



TEST_F(VarintLengthTest_445, SevenBytesMax_ReturnsSeven_445) {

    EXPECT_EQ(leveldb::VarintLength(562949953421311), 7);

}



TEST_F(VarintLengthTest_445, EightBytesMin_ReturnsEight_445) {

    EXPECT_EQ(leveldb::VarintLength(562949953421312), 8);

}



TEST_F(VarintLengthTest_445, EightBytesMax_ReturnsEight_445) {

    EXPECT_EQ(leveldb::VarintLength(72057594037927935), 8);

}



TEST_F(VarintLengthTest_445, NineBytesMin_ReturnsNine_445) {

    EXPECT_EQ(leveldb::VarintLength(72057594037927936), 9);

}



TEST_F(VarintLengthTest_445, NineBytesMax_ReturnsNine_445) {

    EXPECT_EQ(leveldb::VarintLength(9223372036854775807), 9);

}



} // namespace
