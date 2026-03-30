#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/xmpsdk/src/UnicodeInlines.incl_cpp"

#include "XMP_Const.h"



// Mocking XMP_Throw for verification of error conditions

void MockXMP_Throw(const char* message, int errorCode) {

    throw std::runtime_error(std::string(message) + ":" + std::to_string(errorCode));

}



#define XMP_Throw(msg, err) MockXMP_Throw(msg, err)



TEST(VerifySimpleXMLNameTest_1880, ValidASCIIName_1880) {

    const char* nameStart = "ValidName";

    const char* nameEnd = nameStart + strlen(nameStart);

    EXPECT_NO_THROW(VerifySimpleXMLName(nameStart, nameEnd));

}



TEST(VerifySimpleXMLNameTest_1880, ValidNonASCIIName_1880) {

    const char* nameStart = "\xC3\xA9l\u00E8ve"; // élève in UTF-8

    const char* nameEnd = nameStart + strlen(nameStart);

    EXPECT_NO_THROW(VerifySimpleXMLName(nameStart, nameEnd));

}



TEST(VerifySimpleXMLNameTest_1880, EmptyName_1880) {

    const char* nameStart = "";

    const char* nameEnd = nameStart;

    EXPECT_THROW({

        try {

            VerifySimpleXMLName(nameStart, nameEnd);

        } catch (const std::runtime_error& e) {

            EXPECT_EQ(std::string(e.what()), "Empty XML name:102");

            throw;

        }

    }, std::runtime_error);

}



TEST(VerifySimpleXMLNameTest_1880, InvalidStartCharASCII_1880) {

    const char* nameStart = "3Invalid";

    const char* nameEnd = nameStart + strlen(nameStart);

    EXPECT_THROW({

        try {

            VerifySimpleXMLName(nameStart, nameEnd);

        } catch (const std::runtime_error& e) {

            EXPECT_EQ(std::string(e.what()), "Bad XML name:102");

            throw;

        }

    }, std::runtime_error);

}



TEST(VerifySimpleXMLNameTest_1880, InvalidCharInASCII_1880) {

    const char* nameStart = "Valid-Name";

    const char* nameEnd = nameStart + strlen(nameStart);

    EXPECT_THROW({

        try {

            VerifySimpleXMLName(nameStart, nameEnd);

        } catch (const std::runtime_error& e) {

            EXPECT_EQ(std::string(e.what()), "Bad XML name:102");

            throw;

        }

    }, std::runtime_error);

}



TEST(VerifySimpleXMLNameTest_1880, InvalidNonASCIIStartChar_1880) {

    const char* nameStart = "\xC3\xA9l\u00E8v\u00AE"; // élève with invalid character at end

    const char* nameEnd = nameStart + strlen(nameStart);

    EXPECT_THROW({

        try {

            VerifySimpleXMLName(nameStart, nameEnd);

        } catch (const std::runtime_error& e) {

            EXPECT_EQ(std::string(e.what()), "Bad XML name:102");

            throw;

        }

    }, std::runtime_error);

}
