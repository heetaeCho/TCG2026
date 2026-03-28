#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "goo/gbase64.h"



class GBase64Test_35 : public ::testing::Test {

protected:

    // No additional setup or teardown required for this interface.

};



TEST_F(GBase64Test_35, EncodeEmptyInput_35) {

    std::vector<unsigned char> input = {};

    std::string result = gbase64Encode(input);

    EXPECT_EQ(result, "");

}



TEST_F(GBase64Test_35, EncodeSingleByte_35) {

    std::vector<unsigned char> input = {'A'};

    std::string result = gbase64Encode(input);

    EXPECT_EQ(result, "QQ==");

}



TEST_F(GBase64Test_35, EncodeThreeBytes_35) {

    std::vector<unsigned char> input = {'M', 'a', 'n'};

    std::string result = gbase64Encode(input);

    EXPECT_EQ(result, "TWFu");

}



TEST_F(GBase64Test_35, EncodeFourBytes_35) {

    std::vector<unsigned char> input = {'t', 'e', 's', 't'};

    std::string result = gbase64Encode(input);

    EXPECT_EQ(result, "dGVzdA==");

}



TEST_F(GBase64Test_35, EncodeFiveBytes_35) {

    std::vector<unsigned char> input = {'h', 'e', 'l', 'l', 'o'};

    std::string result = gbase64Encode(input);

    EXPECT_EQ(result, "aGVsbG8=");

}



TEST_F(GBase64Test_35, EncodeBinaryData_35) {

    std::vector<unsigned char> input = {0xde, 0xad, 0xbe, 0xef};

    std::string result = gbase64Encode(input);

    EXPECT_EQ(result, "3q2+7w==");

}



TEST_F(GBase64Test_35, EncodeLongString_35) {

    std::vector<unsigned char> input(1024, 'A'); // 1KB of 'A's

    std::string result = gbase64Encode(input);

    EXPECT_EQ(result.size(), 1448); // Base64 encoding increases size by ~1.33x

}



TEST_F(GBase64Test_35, EncodeNonPrintableCharacters_35) {

    std::vector<unsigned char> input = {0x00, 0x01, 0x7f, 0x80, 0xff};

    std::string result = gbase64Encode(input);

    EXPECT_EQ(result, "AAH/A+D/");

}
