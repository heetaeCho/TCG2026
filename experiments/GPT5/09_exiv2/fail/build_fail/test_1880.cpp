#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "XMP_Const.h"

extern "C" {
    #include "UnicodeInlines.incl_cpp"
}

// Mocking the required dependencies if necessary
class MockXMP {
public:
    MOCK_METHOD(void, XMP_Throw, (const char*, int), ());
};

// Test fixture class for organizing the tests
class VerifySimpleXMLNameTest : public ::testing::Test {
protected:
    MockXMP mockXMP;

    // Helper function to simulate the VerifySimpleXMLName logic
    void VerifySimpleXMLNameWrapper(XMP_StringPtr _nameStart, XMP_StringPtr _nameEnd) {
        VerifySimpleXMLName(_nameStart, _nameEnd);
    }
};

// Test case 1: Normal operation with a valid ASCII XML name
TEST_F(VerifySimpleXMLNameTest, ValidASCIIName_1880) {
    const char *validNameStart = "validName";
    const char *validNameEnd = validNameStart + strlen(validNameStart);

    // Expect that XMP_Throw is not called for a valid name
    EXPECT_CALL(mockXMP, XMP_Throw(::testing::_, ::testing::_)).Times(0);

    // Call the function
    VerifySimpleXMLNameWrapper(validNameStart, validNameEnd);
}

// Test case 2: Boundary case with an empty XML name
TEST_F(VerifySimpleXMLNameTest, EmptyName_1881) {
    const char *emptyNameStart = "";
    const char *emptyNameEnd = emptyNameStart;

    // Expect XMP_Throw to be called due to an empty XML name
    EXPECT_CALL(mockXMP, XMP_Throw("Empty XML name", kXMPErr_BadXPath)).Times(1);

    // Call the function
    VerifySimpleXMLNameWrapper(emptyNameStart, emptyNameEnd);
}

// Test case 3: Invalid XML name with an invalid start character (ASCII)
TEST_F(VerifySimpleXMLNameTest, InvalidStartChar_ASCII_1882) {
    const char *invalidNameStart = "!invalid";
    const char *invalidNameEnd = invalidNameStart + strlen(invalidNameStart);

    // Expect XMP_Throw to be called due to invalid start character
    EXPECT_CALL(mockXMP, XMP_Throw("Bad XML name", kXMPErr_BadXPath)).Times(1);

    // Call the function
    VerifySimpleXMLNameWrapper(invalidNameStart, invalidNameEnd);
}

// Test case 4: Invalid XML name with an invalid start character (non-ASCII)
TEST_F(VerifySimpleXMLNameTest, InvalidStartChar_NonASCII_1883) {
    const char *invalidNameStart = "𝑛𝑎𝑚𝑒";
    const char *invalidNameEnd = invalidNameStart + strlen(invalidNameStart);

    // Expect XMP_Throw to be called due to invalid start character (non-ASCII)
    EXPECT_CALL(mockXMP, XMP_Throw("Bad XML name", kXMPErr_BadXPath)).Times(1);

    // Call the function
    VerifySimpleXMLNameWrapper(invalidNameStart, invalidNameEnd);
}

// Test case 5: Valid XML name with valid non-ASCII characters
TEST_F(VerifySimpleXMLNameTest, ValidNonASCIIName_1884) {
    const char *validNameStart = "valid𝑛𝑎𝑚𝑒";
    const char *validNameEnd = validNameStart + strlen(validNameStart);

    // Expect that XMP_Throw is not called for a valid name
    EXPECT_CALL(mockXMP, XMP_Throw(::testing::_, ::testing::_)).Times(0);

    // Call the function
    VerifySimpleXMLNameWrapper(validNameStart, validNameEnd);
}

// Test case 6: Invalid XML name with an invalid character in the middle
TEST_F(VerifySimpleXMLNameTest, InvalidCharacterInMiddle_1885) {
    const char *invalidNameStart = "valid!name";
    const char *invalidNameEnd = invalidNameStart + strlen(invalidNameStart);

    // Expect XMP_Throw to be called due to invalid character in the middle
    EXPECT_CALL(mockXMP, XMP_Throw("Bad XML name", kXMPErr_BadXPath)).Times(1);

    // Call the function
    VerifySimpleXMLNameWrapper(invalidNameStart, invalidNameEnd);
}