#include <gtest/gtest.h>

#include "_re2.cc"



namespace {



class OneCharLenTest_50 : public ::testing::Test {

protected:

    // No additional setup required for this simple function.

};



TEST_F(OneCharLenTest_50, NormalOperation_Latin1_50) {

    EXPECT_EQ(re2_python::OneCharLen("A"), 1);

    EXPECT_EQ(re2_python::OneCharLen("z"), 1);

}



TEST_F(OneCharLenTest_50, NormalOperation_TwoByte_50) {

    char two_byte_char[] = {static_cast<char>(0xC3), 'a'}; // á in UTF-8

    EXPECT_EQ(re2_python::OneCharLen(two_byte_char), 2);

}



TEST_F(OneCharLenTest_50, NormalOperation_ThreeByte_50) {

    char three_byte_char[] = {static_cast<char>(0xE9), static_cast<char>(0x9F), 'B'}; // 九大 in UTF-8

    EXPECT_EQ(re2_python::OneCharLen(three_byte_char), 3);

}



TEST_F(OneCharLenTest_50, NormalOperation_FourByte_50) {

    char four_byte_char[] = {static_cast<char>(0xF0), static_cast<char>(0x9F), 'A', 'C'}; // 🌀 in UTF-8

    EXPECT_EQ(re2_python::OneCharLen(four_byte_char), 4);

}



TEST_F(OneCharLenTest_50, BoundaryCondition_ZeroByte_50) {

    char zero_byte_char = '\0';

    EXPECT_EQ(re2_python::OneCharLen(&zero_byte_char), 1);

}



TEST_F(OneCharLenTest_50, BoundaryCondition_MaxValue_50) {

    char max_value_char = static_cast<char>(0xFF);

    EXPECT_EQ(re2_python::OneCharLen(&max_value_char), 4);

}



} // namespace
