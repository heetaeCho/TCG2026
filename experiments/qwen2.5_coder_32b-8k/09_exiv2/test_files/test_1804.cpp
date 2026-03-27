#include <gtest/gtest.h>

#include <cstring>



namespace Exiv2 {

    size_t base64decode(const char* in, char* out, size_t out_size);

}



TEST(base64decodeTest_1804, NormalOperation_1804) {

    const char* input = "SGVsbG8gV29ybGQh"; // Base64 for "Hello World!"

    char output[1024];

    size_t result = Exiv2::base64decode(input, output, sizeof(output));

    EXPECT_EQ(result, 13);

    EXPECT_STREQ(output, "Hello World!");

}



TEST(base64decodeTest_1804, EmptyInput_1804) {

    const char* input = "";

    char output[1024];

    size_t result = Exiv2::base64decode(input, output, sizeof(output));

    EXPECT_EQ(result, 0);

}



TEST(base64decodeTest_1804, InvalidLength_1804) {

    const char* input = "SGVsbG8g"; // Base64 for "Hello ", but length is not a multiple of 4

    char output[1024];

    size_t result = Exiv2::base64decode(input, output, sizeof(output));

    EXPECT_EQ(result, 0);

}



TEST(base64decodeTest_1804, PaddingOne_1804) {

    const char* input = "SGVsbG8="; // Base64 for "Hello"

    char output[1024];

    size_t result = Exiv2::base64decode(input, output, sizeof(output));

    EXPECT_EQ(result, 5);

    EXPECT_STREQ(output, "Hello");

}



TEST(base64decodeTest_1804, PaddingTwo_1804) {

    const char* input = "SGVsbA=="; // Base64 for "Hell"

    char output[1024];

    size_t result = Exiv2::base64decode(input, output, sizeof(output));

    EXPECT_EQ(result, 4);

    EXPECT_STREQ(output, "Hell");

}



TEST(base64decodeTest_1804, OutputBufferTooSmall_1804) {

    const char* input = "SGVsbG8="; // Base64 for "Hello"

    char output[2]; // Too small buffer

    size_t result = Exiv2::base64decode(input, output, sizeof(output));

    EXPECT_EQ(result, 0);

}



TEST(base64decodeTest_1804, InvalidCharacters_1804) {

    const char* input = "SGVsbG8gVG9t!!"; // Base64 for "Hello Tom!" with invalid characters

    char output[1024];

    size_t result = Exiv2::base64decode(input, output, sizeof(output));

    EXPECT_EQ(result, 0);

}



TEST(base64decodeTest_1804, LargeInput_1804) {

    const char* input = "UHJvZ3JhbW1pbmcgaXMgY29vbCBhbmQgZmFudGFzdGljIQ=="; // Base64 for "Programming is cool and fantastic!"

    char output[1024];

    size_t result = Exiv2::base64decode(input, output, sizeof(output));

    EXPECT_EQ(result, 38);

    EXPECT_STREQ(output, "Programming is cool and fantastic!");

}
