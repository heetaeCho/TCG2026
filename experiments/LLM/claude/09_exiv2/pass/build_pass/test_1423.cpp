#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

// We need access to the Internal namespace function
namespace Exiv2 {
namespace Internal {
std::ostream& printXmpVersion(std::ostream& os, const Value& value, const ExifData*);
}
}

using namespace Exiv2;
using namespace Exiv2::Internal;

class PrintXmpVersionTest_1423 : public ::testing::Test {
protected:
    std::ostringstream os;
};

// Test normal operation with a valid 4-character xmpText version string
TEST_F(PrintXmpVersionTest_1423, ValidFourCharXmpText_1423) {
    XmpTextValue value;
    value.read("2300");  // Represents version like 2.3.0.0
    printXmpVersion(os, value, nullptr);
    std::string result = os.str();
    // Should not be wrapped in parentheses since it's valid
    EXPECT_TRUE(result.find("(") == std::string::npos);
}

// Test with size != 4 - should output value in parentheses
TEST_F(PrintXmpVersionTest_1423, SizeLessThanFour_1423) {
    XmpTextValue value;
    value.read("230");  // Only 3 characters
    printXmpVersion(os, value, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find("("), std::string::npos);
    EXPECT_NE(result.find(")"), std::string::npos);
}

// Test with size > 4 - should output value in parentheses
TEST_F(PrintXmpVersionTest_1423, SizeGreaterThanFour_1423) {
    XmpTextValue value;
    value.read("23001");  // 5 characters
    printXmpVersion(os, value, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find("("), std::string::npos);
    EXPECT_NE(result.find(")"), std::string::npos);
}

// Test with empty string - should output value in parentheses
TEST_F(PrintXmpVersionTest_1423, EmptyValue_1423) {
    XmpTextValue value;
    value.read("");
    printXmpVersion(os, value, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find("("), std::string::npos);
    EXPECT_NE(result.find(")"), std::string::npos);
}

// Test with non-xmpText type (e.g., using an AsciiValue which has typeId asciiString)
TEST_F(PrintXmpVersionTest_1423, NonXmpTextType_1423) {
    AsciiValue value;
    value.read("2300");
    printXmpVersion(os, value, nullptr);
    std::string result = os.str();
    // typeId is not xmpText, so should be parenthesized
    EXPECT_NE(result.find("("), std::string::npos);
    EXPECT_NE(result.find(")"), std::string::npos);
}

// Test valid version "0100" (version 0.1.0.0)
TEST_F(PrintXmpVersionTest_1423, VersionZeroOneZeroZero_1423) {
    XmpTextValue value;
    value.read("0100");
    printXmpVersion(os, value, nullptr);
    std::string result = os.str();
    // Valid: size==4 and xmpText
    EXPECT_TRUE(result.find("(") == std::string::npos);
}

// Test with nullptr ExifData - should work fine
TEST_F(PrintXmpVersionTest_1423, NullExifData_1423) {
    XmpTextValue value;
    value.read("0210");
    printXmpVersion(os, value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
    EXPECT_TRUE(result.find("(") == std::string::npos);
}

// Test that the function returns the ostream reference
TEST_F(PrintXmpVersionTest_1423, ReturnsOstream_1423) {
    XmpTextValue value;
    value.read("2300");
    std::ostream& returned = printXmpVersion(os, value, nullptr);
    EXPECT_EQ(&returned, &os);
}

// Test with single character - size != 4
TEST_F(PrintXmpVersionTest_1423, SingleCharValue_1423) {
    XmpTextValue value;
    value.read("2");
    printXmpVersion(os, value, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find("("), std::string::npos);
    EXPECT_NE(result.find(")"), std::string::npos);
}

// Test version "1000" 
TEST_F(PrintXmpVersionTest_1423, VersionOneZeroZeroZero_1423) {
    XmpTextValue value;
    value.read("1000");
    printXmpVersion(os, value, nullptr);
    std::string result = os.str();
    EXPECT_TRUE(result.find("(") == std::string::npos);
}

// Test with two characters
TEST_F(PrintXmpVersionTest_1423, TwoCharValue_1423) {
    XmpTextValue value;
    value.read("23");
    printXmpVersion(os, value, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find("("), std::string::npos);
    EXPECT_NE(result.find(")"), std::string::npos);
}

// Test that parenthesized output contains the original value
TEST_F(PrintXmpVersionTest_1423, ParenthesizedContainsValue_1423) {
    XmpTextValue value;
    value.read("abc");
    printXmpVersion(os, value, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find("abc"), std::string::npos);
    EXPECT_NE(result.find("("), std::string::npos);
    EXPECT_NE(result.find(")"), std::string::npos);
}
