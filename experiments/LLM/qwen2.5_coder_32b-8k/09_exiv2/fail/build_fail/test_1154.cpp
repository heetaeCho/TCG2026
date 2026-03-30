#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/types.cpp"



namespace Exiv2Tests {



class IsHexTest_1154 : public ::testing::Test {

protected:

    // No setup or teardown needed for this simple function

};



TEST_F(IsHexTest_1154, ValidHexString_1154) {

    EXPECT_TRUE(Exiv2::isHex("0x1A3F", 4, "0x"));

}



TEST_F(IsHexTest_1154, InvalidPrefix_1154) {

    EXPECT_FALSE(Exiv2::isHex("hx1A3F", 4, "0x"));

}



TEST_F(IsHexTest_1154, IncorrectSize_1154) {

    EXPECT_FALSE(Exiv2::isHex("0x1A3", 4, "0x"));

}



TEST_F(IsHexTest_1154, EmptyString_1154) {

    EXPECT_FALSE(Exiv2::isHex("", 0, "0x"));

}



TEST_F(IsHexTest_1154, NonHexCharacters_1154) {

    EXPECT_FALSE(Exiv2::isHex("0x1A3G", 4, "0x"));

}



TEST_F(IsHexTest_1154, NoPrefixCheck_1154) {

    EXPECT_TRUE(Exiv2::isHex("1A3F", 4, ""));

}



TEST_F(IsHexTest_1154, ZeroSizeValid_1154) {

    EXPECT_TRUE(Exiv2::isHex("0x", 0, "0x"));

}



TEST_F(IsHexTest_1154, PrefixOnlyInvalid_1154) {

    EXPECT_FALSE(Exiv2::isHex("0x", 1, "0x"));

}



}  // namespace Exiv2Tests
