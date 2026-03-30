#include <gtest/gtest.h>

#include "TestProjects/exiv2/src/image_int.cpp"



namespace Exiv2 {

namespace Internal {



class IndentFunctionTest : public ::testing::Test {};



TEST_F(IndentFunctionTest_114, ZeroIndentation_ReturnsEmptyString_114) {

    EXPECT_EQ(indent(0), "");

}



TEST_F(IndentFunctionTest_114, SingleIndentation_ReturnsTwoSpaces_114) {

    EXPECT_EQ(indent(1), "  ");

}



TEST_F(IndentFunctionTest_114, MultipleIndentations_ReturnsCorrectNumberOfSpaces_114) {

    EXPECT_EQ(indent(5), "          "); // 10 spaces

}



TEST_F(IndentFunctionTest_114, LargeIndentation_ReturnsLargeNumberOfSpaces_114) {

    EXPECT_EQ(indent(20), std::string(40, ' ')); // 40 spaces

}



}  // namespace Internal

}  // namespace Exiv2
