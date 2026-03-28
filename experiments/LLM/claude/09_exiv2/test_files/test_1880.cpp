#include <gtest/gtest.h>
#include <string>

// Include necessary XMP SDK headers
#include "XMP_Const.h"
#include "XMP_Environment.h"

// We need the XMP exception mechanism
#include "source/XMP_LibUtils.hpp"

// Include the file that contains VerifySimpleXMLName and its dependencies
// We need the Unicode utility functions and the inline implementation
#include "XMPCore/source/XMPCore_Impl.hpp"

// If direct inclusion doesn't work, we may need to declare the function externally
// For the purpose of these tests, we assume VerifySimpleXMLName is available

class VerifySimpleXMLNameTest_1880 : public ::testing::Test {
protected:
    void expectValid(const std::string& name) {
        EXPECT_NO_THROW(
            VerifySimpleXMLName(name.c_str(), name.c_str() + name.size())
        ) << "Expected valid XML name: \"" << name << "\"";
    }

    void expectInvalid(const std::string& name) {
        EXPECT_THROW(
            VerifySimpleXMLName(name.c_str(), name.c_str() + name.size()),
            XMP_Error
        ) << "Expected invalid XML name: \"" << name << "\"";
    }

    void expectInvalidRange(const char* start, const char* end) {
        EXPECT_THROW(
            VerifySimpleXMLName(start, end),
            XMP_Error
        );
    }
};

// Test: Empty name should throw
TEST_F(VerifySimpleXMLNameTest_1880, EmptyNameThrows_1880) {
    const char* empty = "";
    EXPECT_THROW(
        VerifySimpleXMLName(empty, empty),
        XMP_Error
    );
}

// Test: Single ASCII letter is a valid XML name
TEST_F(VerifySimpleXMLNameTest_1880, SingleLetterValid_1880) {
    expectValid("a");
}

// Test: Single uppercase letter is valid
TEST_F(VerifySimpleXMLNameTest_1880, SingleUppercaseLetterValid_1880) {
    expectValid("Z");
}

// Test: Underscore as start character is valid
TEST_F(VerifySimpleXMLNameTest_1880, UnderscoreStartValid_1880) {
    expectValid("_");
}

// Test: Colon as start character is valid (XML names allow colon)
TEST_F(VerifySimpleXMLNameTest_1880, ColonStartValid_1880) {
    expectValid(":");
}

// Test: Name starting with a digit is invalid
TEST_F(VerifySimpleXMLNameTest_1880, DigitStartInvalid_1880) {
    expectInvalid("1abc");
}

// Test: Name starting with a hyphen is invalid
TEST_F(VerifySimpleXMLNameTest_1880, HyphenStartInvalid_1880) {
    expectInvalid("-abc");
}

// Test: Name starting with a dot is invalid
TEST_F(VerifySimpleXMLNameTest_1880, DotStartInvalid_1880) {
    expectInvalid(".abc");
}

// Test: Simple valid multi-character name
TEST_F(VerifySimpleXMLNameTest_1880, SimpleMultiCharValid_1880) {
    expectValid("abc");
}

// Test: Valid name with digits after first character
TEST_F(VerifySimpleXMLNameTest_1880, LettersAndDigitsValid_1880) {
    expectValid("a123");
}

// Test: Valid name with hyphens
TEST_F(VerifySimpleXMLNameTest_1880, NameWithHyphensValid_1880) {
    expectValid("my-name");
}

// Test: Valid name with dots
TEST_F(VerifySimpleXMLNameTest_1880, NameWithDotsValid_1880) {
    expectValid("my.name");
}

// Test: Valid name with underscores
TEST_F(VerifySimpleXMLNameTest_1880, NameWithUnderscoresValid_1880) {
    expectValid("my_name");
}

// Test: Valid name with colons (namespace-style)
TEST_F(VerifySimpleXMLNameTest_1880, NameWithColonsValid_1880) {
    expectValid("ns:local");
}

// Test: Valid name with mixed allowed characters
TEST_F(VerifySimpleXMLNameTest_1880, MixedValidCharsValid_1880) {
    expectValid("a1-b2.c3_d4:e5");
}

// Test: Single digit is invalid (can't start with digit)
TEST_F(VerifySimpleXMLNameTest_1880, SingleDigitInvalid_1880) {
    expectInvalid("0");
}

// Test: Name with space is invalid
TEST_F(VerifySimpleXMLNameTest_1880, NameWithSpaceInvalid_1880) {
    expectInvalid("a b");
}

// Test: Name starting with space is invalid
TEST_F(VerifySimpleXMLNameTest_1880, SpaceStartInvalid_1880) {
    expectInvalid(" abc");
}

// Test: Name with exclamation mark is invalid
TEST_F(VerifySimpleXMLNameTest_1880, ExclamationMarkInvalid_1880) {
    expectInvalid("a!b");
}

// Test: Name with @ symbol is invalid
TEST_F(VerifySimpleXMLNameTest_1880, AtSymbolInvalid_1880) {
    expectInvalid("a@b");
}

// Test: Name with # symbol is invalid
TEST_F(VerifySimpleXMLNameTest_1880, HashSymbolInvalid_1880) {
    expectInvalid("a#b");
}

// Test: Name with $ symbol is invalid
TEST_F(VerifySimpleXMLNameTest_1880, DollarSignInvalid_1880) {
    expectInvalid("a$b");
}

// Test: Longer valid name
TEST_F(VerifySimpleXMLNameTest_1880, LongValidName_1880) {
    expectValid("ThisIsAValidXMLNameWithManyCharacters123");
}

// Test: Name that is just an underscore followed by digits
TEST_F(VerifySimpleXMLNameTest_1880, UnderscoreDigitsValid_1880) {
    expectValid("_123");
}

// Test: Two-byte UTF-8 character as start (valid non-ASCII start char, e.g., U+00C0 = À)
TEST_F(VerifySimpleXMLNameTest_1880, NonASCIIStartCharValid_1880) {
    // U+00C0 (À) encoded in UTF-8: 0xC3 0x80
    std::string name;
    name += (char)0xC3;
    name += (char)0x80;
    expectValid(name);
}

// Test: Non-ASCII character that is valid as a continuation
TEST_F(VerifySimpleXMLNameTest_1880, NonASCIIContinuationValid_1880) {
    // Start with ASCII 'a', then U+00C0
    std::string name = "a";
    name += (char)0xC3;
    name += (char)0x80;
    expectValid(name);
}

// Test: Pointer where start > end should throw (empty)
TEST_F(VerifySimpleXMLNameTest_1880, StartGreaterThanEndThrows_1880) {
    const char* str = "abc";
    EXPECT_THROW(
        VerifySimpleXMLName(str + 2, str),
        XMP_Error
    );
}

// Test: Single hyphen is invalid (hyphen can't start a name)
TEST_F(VerifySimpleXMLNameTest_1880, SingleHyphenInvalid_1880) {
    expectInvalid("-");
}

// Test: Single dot is invalid (dot can't start a name)
TEST_F(VerifySimpleXMLNameTest_1880, SingleDotInvalid_1880) {
    expectInvalid(".");
}

// Test: Valid XMP-style property name
TEST_F(VerifySimpleXMLNameTest_1880, XMPPropertyNameValid_1880) {
    expectValid("xmp:CreateDate");
}

// Test: Valid name starting with uppercase
TEST_F(VerifySimpleXMLNameTest_1880, UppercaseStartValid_1880) {
    expectValid("MyElement");
}

// Test: Name with only underscores
TEST_F(VerifySimpleXMLNameTest_1880, OnlyUnderscoresValid_1880) {
    expectValid("___");
}

// Test: Null character in middle should cause error (not a valid XML name char)
TEST_F(VerifySimpleXMLNameTest_1880, NullCharInMiddleInvalid_1880) {
    std::string name = "a";
    name += '\0';
    name += 'b';
    // The name has a null byte embedded; since we pass explicit end pointer,
    // the null byte should be treated as an invalid character
    EXPECT_THROW(
        VerifySimpleXMLName(name.c_str(), name.c_str() + name.size()),
        XMP_Error
    );
}

// Test: Tab character is invalid
TEST_F(VerifySimpleXMLNameTest_1880, TabCharInvalid_1880) {
    expectInvalid("a\tb");
}

// Test: Newline character is invalid
TEST_F(VerifySimpleXMLNameTest_1880, NewlineCharInvalid_1880) {
    expectInvalid("a\nb");
}

// Test: Single 'x' character is valid
TEST_F(VerifySimpleXMLNameTest_1880, SingleXValid_1880) {
    expectValid("x");
}

// Test: Typical namespace prefix format
TEST_F(VerifySimpleXMLNameTest_1880, NamespacePrefixFormatValid_1880) {
    expectValid("dc:title");
}
