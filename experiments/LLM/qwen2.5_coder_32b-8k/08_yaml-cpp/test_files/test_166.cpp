#include <gtest/gtest.h>

#include "exp.cpp"  // Assuming exp.cpp contains the implementation



namespace YAML {

namespace Exp {



class StrFunctionTest : public ::testing::Test {

};



TEST_F(StrFunctionTest_166, NormalOperation_ReturnsCorrectString_166) {

    unsigned ch = 'A';

    std::string expected = "A";

    EXPECT_EQ(expected, Str(ch));

}



TEST_F(StrFunctionTest_166, BoundaryCondition_MinUnsignedChar_ReturnsCorrectString_166) {

    unsigned ch = 0;

    std::string expected = "\0";

    EXPECT_EQ(expected, Str(ch));

}



TEST_F(StrFunctionTest_166, BoundaryCondition_MaxUnsignedChar_ReturnsCorrectString_166) {

    unsigned ch = UINT8_MAX;

    std::string expected(1, static_cast<char>(UINT8_MAX));

    EXPECT_EQ(expected, Str(ch));

}



}  // namespace Exp

}  // namespace YAML
