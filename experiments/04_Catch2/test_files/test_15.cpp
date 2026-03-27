#include <gtest/gtest.h>

#include "catch2/internal/catch_xmlwriter.hpp"



using namespace Catch;



class XmlFormattingTest_15 : public ::testing::Test {

protected:

    void SetUp() override {}

    void TearDown() override {}

};



TEST_F(XmlFormattingTest_15, BitwiseOrOperator_SameFlags_15) {

    XmlFormatting lhs = XmlFormatting::None;

    XmlFormatting rhs = XmlFormatting::None;

    EXPECT_EQ((lhs | rhs), XmlFormatting::None);

}



TEST_F(XmlFormattingTest_15, BitwiseOrOperator_DifferentFlags_15) {

    XmlFormatting lhs = XmlFormatting::Indent;

    XmlFormatting rhs = XmlFormatting::NoDeclaration;

    EXPECT_EQ((lhs | rhs), static_cast<XmlFormatting>(static_cast<std::uint8_t>(XmlFormatting::Indent) | static_cast<std::uint8_t>(XmlFormatting::NoDeclaration)));

}



TEST_F(XmlFormattingTest_15, BitwiseOrOperator_MultipleFlags_15) {

    XmlFormatting lhs = XmlFormatting::Indent;

    XmlFormatting rhs = XmlFormatting::Indent | XmlFormatting::NoDeclaration;

    EXPECT_EQ((lhs | rhs), static_cast<XmlFormatting>(static_cast<std::uint8_t>(XmlFormatting::Indent) | static_cast<std::uint8_t>(XmlFormatting::NoDeclaration)));

}



TEST_F(XmlFormattingTest_15, BitwiseOrOperator_AllFlags_15) {

    XmlFormatting lhs = XmlFormatting::Indent;

    XmlFormatting rhs = XmlFormatting::Indent | XmlFormatting::NoDeclaration | XmlFormatting::OmitRootElement;

    EXPECT_EQ((lhs | rhs), static_cast<XmlFormatting>(static_cast<std::uint8_t>(XmlFormatting::Indent) | static_cast<std::uint8_t>(XmlFormatting::NoDeclaration) | static_cast<std::uint8_t>(XmlFormatting::OmitRootElement)));

}
