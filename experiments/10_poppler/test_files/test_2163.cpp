#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/goo/GooString.h"

#include "TestProjects/poppler/glib/poppler-document.cc"



TEST(_poppler_goo_string_to_utf8_Test_2163, NullInput_ReturnsNull_2163) {

    GooString* input = nullptr;

    char* result = _poppler_goo_string_to_utf8(input);

    EXPECT_EQ(result, nullptr);

}



TEST(_poppler_goo_string_to_utf8_Test_2163, EmptyString_ReturnsEmptyUTF8_2163) {

    GooString input("");

    char* result = _poppler_goo_string_to_utf8(&input);

    EXPECT_STREQ(result, "");

    g_free(result); // Free the allocated memory

}



TEST(_poppler_goo_string_to_utf8_Test_2163, ASCIIString_ReturnsSameUTF8_2163) {

    GooString input("HelloWorld");

    char* result = _poppler_goo_string_to_utf8(&input);

    EXPECT_STREQ(result, "HelloWorld");

    g_free(result); // Free the allocated memory

}



TEST(_poppler_goo_string_to_utf8_Test_2163, UTF16BEString_ReturnsCorrectUTF8_2163) {

    char utf16be[] = {0xFE, 0xFF, 'H', '\0', 'e', '\0', 'l', '\0', 'l', '\0', 'o', '\0'};

    GooString input(utf16be, sizeof(utf16be));

    char* result = _poppler_goo_string_to_utf8(&input);

    EXPECT_STREQ(result, "Hello");

    g_free(result); // Free the allocated memory

}



TEST(_poppler_goo_string_to_utf8_Test_2163, UTF16LEString_ReturnsCorrectUTF8_2163) {

    char utf16le[] = {0xFF, 0xFE, 'H', '\0', 'e', '\0', 'l', '\0', 'l', '\0', 'o', '\0'};

    GooString input(utf16le, sizeof(utf16le));

    char* result = _poppler_goo_string_to_utf8(&input);

    EXPECT_STREQ(result, "Hello");

    g_free(result); // Free the allocated memory

}



TEST(_poppler_goo_string_to_utf8_Test_2163, PDFDocEncodedString_ReturnsCorrectUTF8_2163) {

    char pdfdocenc[] = {'H', 'e', 'l', 'l', 'o'};

    GooString input(pdfdocenc, sizeof(pdfdocenc));

    char* result = _poppler_goo_string_to_utf8(&input);

    EXPECT_STREQ(result, "Hello");

    g_free(result); // Free the allocated memory

}



TEST(_poppler_goo_string_to_utf8_Test_2163, BoundaryCondition_SmallString_ReturnsCorrectUTF8_2163) {

    char small[] = {'A'};

    GooString input(small, sizeof(small));

    char* result = _poppler_goo_string_to_utf8(&input);

    EXPECT_STREQ(result, "A");

    g_free(result); // Free the allocated memory

}



TEST(_poppler_goo_string_to_utf8_Test_2163, BoundaryCondition_LargeString_ReturnsCorrectUTF8_2163) {

    std::string large(1024, 'x');

    GooString input(large.c_str(), large.size());

    char* result = _poppler_goo_string_to_utf8(&input);

    EXPECT_STREQ(result, large.c_str());

    g_free(result); // Free the allocated memory

}
