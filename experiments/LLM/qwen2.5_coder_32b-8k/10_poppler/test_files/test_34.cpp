#include <gtest/gtest.h>

#include "./TestProjects/poppler/goo/gbase64.h"



class GBase64EncodeTest_34 : public ::testing::Test {

protected:

    // Setup and teardown can be added here if needed.

};



TEST_F(GBase64EncodeTest_34, EmptyInput_ReturnsEmptyString_34) {

    std::vector<char> input;

    std::string result = gbase64Encode(input);

    EXPECT_EQ(result, "");

}



TEST_F(GBase64EncodeTest_34, SingleCharacterInput_ReturnsEncodedString_34) {

    std::vector<char> input = {'A'};

    std::string result = gbase64Encode(input);

    EXPECT_EQ(result, "QQ==");

}



TEST_F(GBase64EncodeTest_34, ThreeCharactersInput_ReturnsEncodedString_34) {

    std::vector<char> input = {'M', 'a', 'n'};

    std::string result = gbase64Encode(input);

    EXPECT_EQ(result, "TWFu");

}



TEST_F(GBase64EncodeTest_34, FourCharactersInput_ReturnsEncodedString_34) {

    std::vector<char> input = {'M', 'a', 'n', 'g'};

    std::string result = gbase64Encode(input);

    EXPECT_EQ(result, "TWFuZw==");

}



TEST_F(GBase64EncodeTest_34, NonPrintableCharactersInput_ReturnsEncodedString_34) {

    std::vector<char> input = {'\x01', '\x02', '\x03'};

    std::string result = gbase64Encode(input);

    EXPECT_EQ(result, "AQID");

}



TEST_F(GBase64EncodeTest_34, LargeInput_ReturnsEncodedString_34) {

    std::vector<char> input(100, 'a'); // 100 'a's

    std::string result = gbase64Encode(input);

    EXPECT_EQ(result.size(), 136); // Expected size for base64 encoding of 100 bytes

}



TEST_F(GBase64EncodeTest_34, InputWithPadding_ReturnsEncodedStringWithPadding_34) {

    std::vector<char> input = {'f', 'o', 'o'};

    std::string result = gbase64Encode(input);

    EXPECT_EQ(result, "Zm9v");

}



TEST_F(GBase64EncodeTest_34, InputWithoutPadding_ReturnsEncodedStringWithoutPadding_34) {

    std::vector<char> input = {'f', 'o', 'o', 'b'};

    std::string result = gbase64Encode(input);

    EXPECT_EQ(result, "Zm9vYg==");

}
