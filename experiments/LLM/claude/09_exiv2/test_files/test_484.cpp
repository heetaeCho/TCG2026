#include <gtest/gtest.h>
#include <sstream>
#include <cstdint>

// Include necessary Exiv2 headers
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>
#include <exiv2/types.hpp>

// We need access to the Internal namespace
// Since the class is defined in nikonmn_int.cpp, we need to either include the header
// or replicate the minimal interface. Let's include the internal header.
#include "nikonmn_int.hpp"

// If the header doesn't expose the class directly, we may need to define it here
// based on the provided code. Since we're told it exists in the codebase, let's
// try to use it. If not available via header, define a minimal version for testing.

namespace {

using namespace Exiv2;
using namespace Exiv2::Internal;

class Nikon3MakerNoteTest_484 : public ::testing::Test {
protected:
    Nikon3MakerNote makerNote_;
    std::ostringstream os_;
};

// Test: Single unsigned byte value of 0 should print "n/a"
TEST_F(Nikon3MakerNoteTest_484, RepeatingFlashCount_ZeroValue_PrintsNA_484) {
    auto value = Value::create(unsignedByte);
    value->read("0");
    
    makerNote_.printRepeatingFlashCount(os_, *value, nullptr);
    
    // 0 means n/a
    std::string result = os_.str();
    EXPECT_NE(result.find("n/a"), std::string::npos) 
        << "Expected 'n/a' for value 0, got: " << result;
}

// Test: Single unsigned byte value of 255 should print "n/a"
TEST_F(Nikon3MakerNoteTest_484, RepeatingFlashCount_Value255_PrintsNA_484) {
    auto value = Value::create(unsignedByte);
    value->read("255");
    
    makerNote_.printRepeatingFlashCount(os_, *value, nullptr);
    
    std::string result = os_.str();
    EXPECT_NE(result.find("n/a"), std::string::npos)
        << "Expected 'n/a' for value 255, got: " << result;
}

// Test: Single unsigned byte value of 1 should print the count
TEST_F(Nikon3MakerNoteTest_484, RepeatingFlashCount_Value1_PrintsCount_484) {
    auto value = Value::create(unsignedByte);
    value->read("1");
    
    makerNote_.printRepeatingFlashCount(os_, *value, nullptr);
    
    std::string result = os_.str();
    EXPECT_NE(result.find("1"), std::string::npos)
        << "Expected '1' in output, got: " << result;
}

// Test: Single unsigned byte value of 128 should print the count
TEST_F(Nikon3MakerNoteTest_484, RepeatingFlashCount_Value128_PrintsCount_484) {
    auto value = Value::create(unsignedByte);
    value->read("128");
    
    makerNote_.printRepeatingFlashCount(os_, *value, nullptr);
    
    std::string result = os_.str();
    EXPECT_NE(result.find("128"), std::string::npos)
        << "Expected '128' in output, got: " << result;
}

// Test: Single unsigned byte value of 254 should print the count (not n/a)
TEST_F(Nikon3MakerNoteTest_484, RepeatingFlashCount_Value254_PrintsCount_484) {
    auto value = Value::create(unsignedByte);
    value->read("254");
    
    makerNote_.printRepeatingFlashCount(os_, *value, nullptr);
    
    std::string result = os_.str();
    EXPECT_NE(result.find("254"), std::string::npos)
        << "Expected '254' in output, got: " << result;
    EXPECT_EQ(result.find("n/a"), std::string::npos)
        << "Should not contain 'n/a' for value 254";
}

// Test: Wrong type (not unsignedByte) should print parenthesized value
TEST_F(Nikon3MakerNoteTest_484, RepeatingFlashCount_WrongType_PrintsParenthesized_484) {
    auto value = Value::create(unsignedShort);
    value->read("42");
    
    makerNote_.printRepeatingFlashCount(os_, *value, nullptr);
    
    std::string result = os_.str();
    EXPECT_NE(result.find("("), std::string::npos)
        << "Expected parenthesized output for wrong type, got: " << result;
    EXPECT_NE(result.find(")"), std::string::npos)
        << "Expected parenthesized output for wrong type, got: " << result;
}

// Test: Multiple values (count != 1) should print parenthesized value
TEST_F(Nikon3MakerNoteTest_484, RepeatingFlashCount_MultipleValues_PrintsParenthesized_484) {
    auto value = Value::create(unsignedByte);
    value->read("10 20");
    
    makerNote_.printRepeatingFlashCount(os_, *value, nullptr);
    
    std::string result = os_.str();
    EXPECT_NE(result.find("("), std::string::npos)
        << "Expected parenthesized output for multiple values, got: " << result;
    EXPECT_NE(result.find(")"), std::string::npos)
        << "Expected parenthesized output for multiple values, got: " << result;
}

// Test: Value of 2 should print the count
TEST_F(Nikon3MakerNoteTest_484, RepeatingFlashCount_Value2_PrintsCount_484) {
    auto value = Value::create(unsignedByte);
    value->read("2");
    
    makerNote_.printRepeatingFlashCount(os_, *value, nullptr);
    
    std::string result = os_.str();
    EXPECT_NE(result.find("2"), std::string::npos)
        << "Expected '2' in output, got: " << result;
}

// Test: Returns reference to the same ostream
TEST_F(Nikon3MakerNoteTest_484, RepeatingFlashCount_ReturnsOstream_484) {
    auto value = Value::create(unsignedByte);
    value->read("5");
    
    std::ostream& returned = makerNote_.printRepeatingFlashCount(os_, *value, nullptr);
    
    EXPECT_EQ(&returned, &os_);
}

// Test: ExifData pointer is nullptr - should still work
TEST_F(Nikon3MakerNoteTest_484, RepeatingFlashCount_NullExifData_Works_484) {
    auto value = Value::create(unsignedByte);
    value->read("10");
    
    EXPECT_NO_THROW(makerNote_.printRepeatingFlashCount(os_, *value, nullptr));
    
    std::string result = os_.str();
    EXPECT_NE(result.find("10"), std::string::npos)
        << "Expected '10' in output, got: " << result;
}

// Test: Value of 1 boundary - just above 0
TEST_F(Nikon3MakerNoteTest_484, RepeatingFlashCount_BoundaryValue1_NotNA_484) {
    auto value = Value::create(unsignedByte);
    value->read("1");
    
    makerNote_.printRepeatingFlashCount(os_, *value, nullptr);
    
    std::string result = os_.str();
    EXPECT_EQ(result.find("n/a"), std::string::npos)
        << "Value 1 should not be n/a, got: " << result;
}

// Test: Wrong type unsignedLong should print parenthesized
TEST_F(Nikon3MakerNoteTest_484, RepeatingFlashCount_UnsignedLongType_PrintsParenthesized_484) {
    auto value = Value::create(unsignedLong);
    value->read("100");
    
    makerNote_.printRepeatingFlashCount(os_, *value, nullptr);
    
    std::string result = os_.str();
    EXPECT_NE(result.find("("), std::string::npos)
        << "Expected parenthesized output for unsignedLong type, got: " << result;
}

} // namespace
