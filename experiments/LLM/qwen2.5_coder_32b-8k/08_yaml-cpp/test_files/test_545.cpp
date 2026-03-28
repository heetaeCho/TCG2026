#include <gtest/gtest.h>

#include "binary.cpp"



namespace YAML {

    TEST(DecodeBase64Test_545, EmptyInput_ReturnsEmptyVector_545) {

        std::string input = "";

        std::vector<unsigned char> result = DecodeBase64(input);

        EXPECT_TRUE(result.empty());

    }



    TEST(DecodeBase64Test_545, ValidSingleBlock_ReturnsCorrectVector_545) {

        std::string input = "SGk=";

        std::vector<unsigned char> expected = {72, 105};

        std::vector<unsigned char> result = DecodeBase64(input);

        EXPECT_EQ(result, expected);

    }



    TEST(DecodeBase64Test_545, ValidTwoBlocks_ReturnsCorrectVector_545) {

        std::string input = "SGVsbG8=";

        std::vector<unsigned char> expected = {72, 101, 108, 108, 111};

        std::vector<unsigned char> result = DecodeBase64(input);

        EXPECT_EQ(result, expected);

    }



    TEST(DecodeBase64Test_545, ValidThreeBlocks_ReturnsCorrectVector_545) {

        std::string input = "SGVsbG8gV29ybGQ=";

        std::vector<unsigned char> expected = {72, 101, 108, 108, 111, 32, 87, 111, 114, 108, 100};

        std::vector<unsigned char> result = DecodeBase64(input);

        EXPECT_EQ(result, expected);

    }



    TEST(DecodeBase64Test_545, ValidFourBlocks_ReturnsCorrectVector_545) {

        std::string input = "SGVsbG8gV29ybGQh";

        std::vector<unsigned char> expected = {72, 101, 108, 108, 111, 32, 87, 111, 114, 108, 100, 33};

        std::vector<unsigned char> result = DecodeBase64(input);

        EXPECT_EQ(result, expected);

    }



    TEST(DecodeBase64Test_545, InvalidCharacter_ReturnsEmptyVector_545) {

        std::string input = "SGVsbG8gV29ybGQ!"; // '!' is not a valid base64 character

        std::vector<unsigned char> result = DecodeBase64(input);

        EXPECT_TRUE(result.empty());

    }



    TEST(DecodeBase64Test_545, TrailingSpaces_ReturnsCorrectVector_545) {

        std::string input = "SGVsbG8gV29ybGQ=   ";

        std::vector<unsigned char> expected = {72, 101, 108, 108, 111, 32, 87, 111, 114, 108, 100};

        std::vector<unsigned char> result = DecodeBase64(input);

        EXPECT_EQ(result, expected);

    }



    TEST(DecodeBase64Test_545, LeadingSpaces_ReturnsCorrectVector_545) {

        std::string input = "   SGVsbG8gV29ybGQ=";

        std::vector<unsigned char> expected = {72, 101, 108, 108, 111, 32, 87, 111, 114, 108, 100};

        std::vector<unsigned char> result = DecodeBase64(input);

        EXPECT_EQ(result, expected);

    }



    TEST(DecodeBase64Test_545, EmbeddedSpaces_ReturnsCorrectVector_545) {

        std::string input = "SG VsbG8 gV29ybGQ=";

        std::vector<unsigned char> expected = {72, 101, 108, 108, 111, 32, 87, 111, 114, 108, 100};

        std::vector<unsigned char> result = DecodeBase64(input);

        EXPECT_EQ(result, expected);

    }



    TEST(DecodeBase64Test_545, PaddingSingle_ReturnsCorrectVector_545) {

        std::string input = "SGVsbG8g";

        std::vector<unsigned char> expected = {72, 101, 108, 108, 111};

        std::vector<unsigned char> result = DecodeBase64(input);

        EXPECT_EQ(result, expected);

    }



    TEST(DecodeBase64Test_545, PaddingDouble_ReturnsCorrectVector_545) {

        std::string input = "SGVsbG8=";

        std::vector<unsigned char> expected = {72, 101, 108, 108, 111};

        std::vector<unsigned char> result = DecodeBase64(input);

        EXPECT_EQ(result, expected);

    }



    TEST(DecodeBase64Test_545, PaddingTriple_ReturnsCorrectVector_545) {

        std::string input = "SGVsbA==";

        std::vector<unsigned char> expected = {72, 101, 108, 108};

        std::vector<unsigned char> result = DecodeBase64(input);

        EXPECT_EQ(result, expected);

    }

}
