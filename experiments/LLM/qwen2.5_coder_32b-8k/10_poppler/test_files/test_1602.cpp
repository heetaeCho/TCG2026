#include <gtest/gtest.h>



// Assuming rotWord is part of a class or namespace for testing purposes

namespace {



unsigned int rotWord(unsigned int x) { return ((x << 8) & 0xffffffff) | (x >> 24); }



} // namespace



TEST(rotWordTest_1602, NormalOperation_1602) {

    EXPECT_EQ(rotWord(0x12345678), 0x34567812);

}



TEST(rotWordTest_1602, BoundaryCondition_Zero_1602) {

    EXPECT_EQ(rotWord(0x00000000), 0x00000000);

}



TEST(rotWordTest_1602, BoundaryCondition_MaxUint_1602) {

    EXPECT_EQ(rotWord(0xFFFFFFFF), 0xFFFFFFFF);

}



TEST(rotWordTest_1602, SingleByteNonZero_1602) {

    EXPECT_EQ(rotWord(0x000000FF), 0xFF000000);

}



TEST(rotWordTest_1602, SingleByteInUpperBits_1602) {

    EXPECT_EQ(rotWord(0xFF000000), 0x00FF0000);

}
