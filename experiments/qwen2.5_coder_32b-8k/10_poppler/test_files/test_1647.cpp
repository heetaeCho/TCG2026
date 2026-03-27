#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/UnicodeMapFuncs.cc"



TEST(mapUTF8Test_1647, NormalOperationBelow7F_1647) {

    char buf[1];

    int result = mapUTF8(0x0000007E, buf, 1);

    EXPECT_EQ(result, 1);

    EXPECT_EQ(buf[0], (char)0x7E);

}



TEST(mapUTF8Test_1647, NormalOperationBelow7FF_1647) {

    char buf[2];

    int result = mapUTF8(0x000007FE, buf, 2);

    EXPECT_EQ(result, 2);

    EXPECT_EQ(buf[0], (char)0xDF);

    EXPECT_EQ(buf[1], (char)0xBE);

}



TEST(mapUTF8Test_1647, NormalOperationBelowFFFF_1647) {

    char buf[3];

    int result = mapUTF8(0x0000FFFE, buf, 3);

    EXPECT_EQ(result, 3);

    EXPECT_EQ(buf[0], (char)0xEF);

    EXPECT_EQ(buf[1], (char)0xBF);

    EXPECT_EQ(buf[2], (char)0xBE);

}



TEST(mapUTF8Test_1647, NormalOperationBelow10FFFF_1647) {

    char buf[4];

    int result = mapUTF8(0x0010FFFE, buf, 4);

    EXPECT_EQ(result, 4);

    EXPECT_EQ(buf[0], (char)0xF4);

    EXPECT_EQ(buf[1], (char)0x8F);

    EXPECT_EQ(buf[2], (char)0xBF);

    EXPECT_EQ(buf[3], (char)0xBE);

}



TEST(mapUTF8Test_1647, BoundaryConditionExactly7F_1647) {

    char buf[1];

    int result = mapUTF8(0x0000007F, buf, 1);

    EXPECT_EQ(result, 1);

    EXPECT_EQ(buf[0], (char)0x7F);

}



TEST(mapUTF8Test_1647, BoundaryConditionExactly7FF_1647) {

    char buf[2];

    int result = mapUTF8(0x000007FF, buf, 2);

    EXPECT_EQ(result, 2);

    EXPECT_EQ(buf[0], (char)0xDF);

    EXPECT_EQ(buf[1], (char)0xBF);

}



TEST(mapUTF8Test_1647, BoundaryConditionExactlyFFFF_1647) {

    char buf[3];

    int result = mapUTF8(0x0000FFFF, buf, 3);

    EXPECT_EQ(result, 3);

    EXPECT_EQ(buf[0], (char)0xEF);

    EXPECT_EQ(buf[1], (char)0xBF);

    EXPECT_EQ(buf[2], (char)0xBF);

}



TEST(mapUTF8Test_1647, BoundaryConditionExactly10FFFF_1647) {

    char buf[4];

    int result = mapUTF8(0x0010FFFF, buf, 4);

    EXPECT_EQ(result, 4);

    EXPECT_EQ(buf[0], (char)0xF4);

    EXPECT_EQ(buf[1], (char)0x8F);

    EXPECT_EQ(buf[2], (char)0xBF);

    EXPECT_EQ(buf[3], (char)0xBF);

}



TEST(mapUTF8Test_1647, BufferSizeTooSmallFor7F_1647) {

    char buf[0];

    int result = mapUTF8(0x0000007E, buf, 0);

    EXPECT_EQ(result, 0);

}



TEST(mapUTF8Test_1647, BufferSizeTooSmallFor7FF_1647) {

    char buf[1];

    int result = mapUTF8(0x000007FE, buf, 1);

    EXPECT_EQ(result, 0);

}



TEST(mapUTF8Test_1647, BufferSizeTooSmallForFFFF_1647) {

    char buf[2];

    int result = mapUTF8(0x0000FFFE, buf, 2);

    EXPECT_EQ(result, 0);

}



TEST(mapUTF8Test_1647, BufferSizeTooSmallFor10FFFF_1647) {

    char buf[3];

    int result = mapUTF8(0x0010FFFE, buf, 3);

    EXPECT_EQ(result, 0);

}



TEST(mapUTF8Test_1647, InvalidUnicodeValueAbove10FFFF_1647) {

    char buf[5];

    int result = mapUTF8(0x00110000, buf, 5);

    EXPECT_EQ(result, 0);

}
