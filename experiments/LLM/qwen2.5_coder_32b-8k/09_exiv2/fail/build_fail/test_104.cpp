#include <gtest/gtest.h>

#include "exiv2/matroskavideo.hpp"



using namespace Exiv2;



class MatroskaVideoTest_104 : public ::testing::Test {

protected:

    BasicIo::UniquePtr io = std::make_unique<BasicIo>();

    MatroskaVideo matroskaVideo{std::move(io)};

};



TEST_F(MatroskaVideoTest_104, FindBlockSize_MostSignificantBitSet_104) {

    byte b = 0x80; // 10000000 in binary

    EXPECT_EQ(matroskaVideo.findBlockSize(b), 1);

}



TEST_F(MatroskaVideoTest_104, FindBlockSize_SecondMostSignificantBitSet_104) {

    byte b = 0x40; // 01000000 in binary

    EXPECT_EQ(matroskaVideo.findBlockSize(b), 2);

}



TEST_F(MatroskaVideoTest_104, FindBlockSize_ThirdMostSignificantBitSet_104) {

    byte b = 0x20; // 00100000 in binary

    EXPECT_EQ(matroskaVideo.findBlockSize(b), 3);

}



TEST_F(MatroskaVideoTest_104, FindBlockSize_FourthMostSignificantBitSet_104) {

    byte b = 0x10; // 00010000 in binary

    EXPECT_EQ(matroskaVideo.findBlockSize(b), 4);

}



TEST_F(MatroskaVideoTest_104, FindBlockSize_FifthMostSignificantBitSet_104) {

    byte b = 0x8; // 00001000 in binary

    EXPECT_EQ(matroskaVideo.findBlockSize(b), 5);

}



TEST_F(MatroskaVideoTest_104, FindBlockSize_SixthMostSignificantBitSet_104) {

    byte b = 0x4; // 00000100 in binary

    EXPECT_EQ(matroskaVideo.findBlockSize(b), 6);

}



TEST_F(MatroskaVideoTest_104, FindBlockSize_SeventhMostSignificantBitSet_104) {

    byte b = 0x2; // 00000010 in binary

    EXPECT_EQ(matroskaVideo.findBlockSize(b), 7);

}



TEST_F(MatroskaVideoTest_104, FindBlockSize_EighthMostSignificantBitSet_104) {

    byte b = 0x1; // 00000001 in binary

    EXPECT_EQ(matroskaVideo.findBlockSize(b), 8);

}



TEST_F(MatroskaVideoTest_104, FindBlockSize_NoBitsSet_104) {

    byte b = 0x0; // 00000000 in binary

    EXPECT_EQ(matroskaVideo.findBlockSize(b), 0);

}
