#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include <exiv2/exiv2.hpp>

using namespace Exiv2;

namespace {

// Helper function to call printXmpDate
std::string callPrintXmpDate(const Value& value) {
    std::ostringstream os;
    Exiv2::Internal::printXmpDate(os, value, nullptr);
    return os.str();
}

} // namespace

// Test normal XMP date with 19 characters (no Z suffix)
TEST(PrintXmpDateTest_1424, NormalDate19Chars_1424) {
    XmpTextValue value;
    value.read("2023-06-15T10:30:45");
    std::string result = callPrintXmpDate(value);
    // '-' replaced with ':', 'T' replaced with ' '
    EXPECT_EQ(result, "2023:06:15 10:30:45");
}

// Test normal XMP date with 20 characters (with Z suffix)
TEST(PrintXmpDateTest_1424, NormalDate20CharsWithZ_1424) {
    XmpTextValue value;
    value.read("2023-06-15T10:30:45Z");
    std::string result = callPrintXmpDate(value);
    // Z removed, '-' replaced with ':', 'T' replaced with ' '
    EXPECT_EQ(result, "2023:06:15 10:30:45");
}

// Test that a value with wrong size (too short) is printed as-is
TEST(PrintXmpDateTest_1424, WrongSizeTooShort_1424) {
    XmpTextValue value;
    value.read("2023-06-15");
    std::string result = callPrintXmpDate(value);
    EXPECT_EQ(result, "2023-06-15");
}

// Test that a value with wrong size (too long) is printed as-is
TEST(PrintXmpDateTest_1424, WrongSizeTooLong_1424) {
    XmpTextValue value;
    value.read("2023-06-15T10:30:45ZZ");
    std::string result = callPrintXmpDate(value);
    EXPECT_EQ(result, "2023-06-15T10:30:45ZZ");
}

// Test that a non-xmpText type value is printed as-is
TEST(PrintXmpDateTest_1424, NonXmpTextType_1424) {
    AsciiValue value;
    value.read("2023-06-15T10:30:45");
    std::string result = callPrintXmpDate(value);
    EXPECT_EQ(result, "2023-06-15T10:30:45");
}

// Test empty string
TEST(PrintXmpDateTest_1424, EmptyString_1424) {
    XmpTextValue value;
    value.read("");
    std::string result = callPrintXmpDate(value);
    EXPECT_EQ(result, "");
}

// Test 20 chars but last char is not Z - should be printed as-is (size 20 but no Z)
TEST(PrintXmpDateTest_1424, TwentyCharsNoZ_1424) {
    XmpTextValue value;
    value.read("2023-06-15T10:30:45X");
    std::string result = callPrintXmpDate(value);
    // Size is 20 and type is xmpText, so enters the processing branch
    // stringValue.back() is 'X', not 'Z', so pop_back is NOT called
    // Then replacements happen on the full 20-char string
    EXPECT_EQ(result, "2023:06:15 10:30:45X");
}

// Test date with no dashes or T (19 chars xmpText)
TEST(PrintXmpDateTest_1424, NoDashesOrT19Chars_1424) {
    XmpTextValue value;
    value.read("1234567890123456789");
    std::string result = callPrintXmpDate(value);
    // No '-' or 'T' to replace, should return same string
    EXPECT_EQ(result, "1234567890123456789");
}

// Test 18-character string (boundary: just under 19)
TEST(PrintXmpDateTest_1424, EighteenChars_1424) {
    XmpTextValue value;
    value.read("123456789012345678");
    std::string result = callPrintXmpDate(value);
    // size != 19 and size != 20, so printed as-is
    EXPECT_EQ(result, "123456789012345678");
}

// Test single character string
TEST(PrintXmpDateTest_1424, SingleChar_1424) {
    XmpTextValue value;
    value.read("A");
    std::string result = callPrintXmpDate(value);
    EXPECT_EQ(result, "A");
}

// Test multiple T and - replacements in 19-char string
TEST(PrintXmpDateTest_1424, MultipleTAndDash_1424) {
    XmpTextValue value;
    value.read("T-T-T-T-T-T-T-T-T-T");
    // This is 20 chars actually. Let's be precise.
    // "T-T-T-T-T-T-T-T-T-" is 19 chars
    // Wait, let me count: T - T - T - T - T - T - T - T - T - = that's 9 T's and 9 dashes and 1 more? 
    // Let me just create exactly 19 chars with T and -
    XmpTextValue value2;
    value2.read("T--T--T--T--T--T--T"); // 19 chars: T(1) -(2) -(3) T(4) -(5) -(6) T(7) -(8) -(9) T(10) -(11) -(12) T(13) -(14) -(15) T(16) -(17) -(18) T(19)
    std::string result = callPrintXmpDate(value2);
    EXPECT_EQ(result, " :: :: :: :: :: :: ");
}

// Test that nullptr ExifData is acceptable
TEST(PrintXmpDateTest_1424, NullExifDataPtr_1424) {
    XmpTextValue value;
    value.read("2023-06-15T10:30:45");
    std::ostringstream os;
    // Should not crash with nullptr
    Exiv2::Internal::printXmpDate(os, value, nullptr);
    EXPECT_EQ(os.str(), "2023:06:15 10:30:45");
}

// Test exactly 19 chars with all dashes
TEST(PrintXmpDateTest_1424, AllDashes19_1424) {
    XmpTextValue value;
    value.read("-------------------"); // 19 dashes
    std::string result = callPrintXmpDate(value);
    EXPECT_EQ(result, ":::::::::::::::::::"); // all replaced with ':'
}

// Test exactly 20 chars ending with Z, all dashes before Z
TEST(PrintXmpDateTest_1424, AllDashes19PlusZ_1424) {
    XmpTextValue value;
    value.read("-------------------Z"); // 19 dashes + Z = 20 chars
    std::string result = callPrintXmpDate(value);
    // Z is popped, then 19 dashes replaced with colons
    EXPECT_EQ(result, ":::::::::::::::::::"); 
}
