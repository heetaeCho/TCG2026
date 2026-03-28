#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <optional>

#include "poppler-document.cc"



using namespace testing;



// Test fixture for poppler_password_to_latin1 tests

class PopplerPasswordToLatin1Test_2138 : public ::testing::Test {

protected:

    // Setup code, if needed

};



TEST_F(PopplerPasswordToLatin1Test_2138, NullInput_ReturnsEmptyOptional_2138) {

    auto result = poppler_password_to_latin1(nullptr);

    EXPECT_FALSE(result.has_value());

}



TEST_F(PopplerPasswordToLatin1Test_2138, EmptyString_ReturnsEmptyGooString_2138) {

    auto result = poppler_password_to_latin1("");

    ASSERT_TRUE(result.has_value());

    EXPECT_EQ(result->getCString(), "");

}



TEST_F(PopplerPasswordToLatin1Test_2138, BasicConversion_ReturnsCorrectLatin1String_2138) {

    const gchar* utf8Password = "test";

    auto result = poppler_password_to_latin1(utf8Password);

    ASSERT_TRUE(result.has_value());

    EXPECT_EQ(result->getCString(), "test");

}



TEST_F(PopplerPasswordToLatin1Test_2138, NonAsciiConversion_ReturnsCorrectLatin1String_2138) {

    const gchar* utf8Password = "café"; // UTF-8 encoding for café

    auto result = poppler_password_to_latin1(utf8Password);

    ASSERT_TRUE(result.has_value());

    EXPECT_EQ(result->getCString(), "caf?"); // ISO-8859-1 cannot fully represent 'é', so it gets replaced with '?'

}



TEST_F(PopplerPasswordToLatin1Test_2138, FullRangeOfLatin1_ReturnsCorrectLatin1String_2138) {

    const gchar* utf8Password = "¡¢£¤¥¦§¨©ª«¬®¯°±²³´µ¶·¸¹º»¼½¾¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõö÷øùúûüýþÿ";

    auto result = poppler_password_to_latin1(utf8Password);

    ASSERT_TRUE(result.has_value());

    EXPECT_EQ(std::string(result->getCString()), utf8Password); // All characters in this string are representable in ISO-8859-1

}
