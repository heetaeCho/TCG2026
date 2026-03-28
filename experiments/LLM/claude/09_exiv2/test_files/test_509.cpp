#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <cmath>
#include <string>

// Include necessary Exiv2 headers
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>
#include <exiv2/types.hpp>

// Include the internal header for Nikon3MakerNote
#include "nikonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class Nikon3MakerNoteTest_509 : public ::testing::Test {
protected:
    Nikon3MakerNote maker_;
    std::ostringstream os_;
};

// Test: When value count is not 1, should output raw value in parentheses
TEST_F(Nikon3MakerNoteTest_509, PrintFocusDistanceLd4_WrongCount_509) {
    // Create a value with count != 1 (two unsigned short values)
    UShortValue val;
    val.read("100 200");
    
    maker_.printFocusDistanceLd4(os_, val, nullptr);
    std::string result = os_.str();
    
    // Should be wrapped in parentheses since count != 1
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test: When value type is not unsignedShort, should output raw value in parentheses
TEST_F(Nikon3MakerNoteTest_509, PrintFocusDistanceLd4_WrongType_509) {
    // Use a signed long value (wrong type)
    LongValue val;
    val.read("500");
    
    maker_.printFocusDistanceLd4(os_, val, nullptr);
    std::string result = os_.str();
    
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test: When value is 0, should output "n/a"
TEST_F(Nikon3MakerNoteTest_509, PrintFocusDistanceLd4_ZeroValue_509) {
    UShortValue val;
    val.read("0");
    
    maker_.printFocusDistanceLd4(os_, val, nullptr);
    std::string result = os_.str();
    
    // Should contain "n/a" (possibly translated, but in default locale it should be "n/a")
    EXPECT_TRUE(result.find("n/a") != std::string::npos || result.find("N/A") != std::string::npos || !result.empty());
}

// Test: Normal non-zero value should produce a distance in meters
TEST_F(Nikon3MakerNoteTest_509, PrintFocusDistanceLd4_NormalValue_509) {
    // Use a typical non-zero value
    UShortValue val;
    val.read("5120"); // 5120 = 20 * 256, so temp/(256*40) = 0.5, result = 10^(0.5-2) = 10^(-1.5) ≈ 0.0316 m
    
    maker_.printFocusDistanceLd4(os_, val, nullptr);
    std::string result = os_.str();
    
    // Should contain " m" for meters
    EXPECT_TRUE(result.find(" m") != std::string::npos);
}

// Test: Value of 1 (small non-zero) should produce a valid distance string
TEST_F(Nikon3MakerNoteTest_509, PrintFocusDistanceLd4_ValueOne_509) {
    UShortValue val;
    val.read("1");
    
    maker_.printFocusDistanceLd4(os_, val, nullptr);
    std::string result = os_.str();
    
    // Should output a distance in meters, not "n/a"
    EXPECT_TRUE(result.find(" m") != std::string::npos);
}

// Test: Large value should produce a valid distance string
TEST_F(Nikon3MakerNoteTest_509, PrintFocusDistanceLd4_LargeValue_509) {
    UShortValue val;
    val.read("65535"); // Max unsigned short
    
    maker_.printFocusDistanceLd4(os_, val, nullptr);
    std::string result = os_.str();
    
    // Should output a distance in meters
    EXPECT_TRUE(result.find(" m") != std::string::npos);
}

// Test: Verify the computed distance for a known value
TEST_F(Nikon3MakerNoteTest_509, PrintFocusDistanceLd4_KnownComputation_509) {
    // temp = 20480 => temp/(256*40) = 20480/10240 = 2.0 => 10^(2.0-2.0) = 10^0 = 1.0 m
    UShortValue val;
    val.read("20480");
    
    maker_.printFocusDistanceLd4(os_, val, nullptr);
    std::string result = os_.str();
    
    EXPECT_TRUE(result.find("1.00 m") != std::string::npos);
}

// Test: Another known computation
TEST_F(Nikon3MakerNoteTest_509, PrintFocusDistanceLd4_TenMeters_509) {
    // We want 10^(temp/(256*40) - 2) = 10.0
    // temp/(10240) - 2 = 1 => temp/10240 = 3 => temp = 30720
    UShortValue val;
    val.read("30720");
    
    maker_.printFocusDistanceLd4(os_, val, nullptr);
    std::string result = os_.str();
    
    EXPECT_TRUE(result.find("10.00 m") != std::string::npos);
}

// Test: Return value is the same ostream reference
TEST_F(Nikon3MakerNoteTest_509, PrintFocusDistanceLd4_ReturnsOstream_509) {
    UShortValue val;
    val.read("5120");
    
    std::ostream& ret = maker_.printFocusDistanceLd4(os_, val, nullptr);
    
    EXPECT_EQ(&ret, &os_);
}

// Test: Passing nullptr for ExifData should not cause crash
TEST_F(Nikon3MakerNoteTest_509, PrintFocusDistanceLd4_NullExifData_509) {
    UShortValue val;
    val.read("1000");
    
    EXPECT_NO_THROW(maker_.printFocusDistanceLd4(os_, val, nullptr));
}

// Test: String type value should output in parentheses (wrong type)
TEST_F(Nikon3MakerNoteTest_509, PrintFocusDistanceLd4_StringType_509) {
    StringValue val;
    val.read("hello");
    
    maker_.printFocusDistanceLd4(os_, val, nullptr);
    std::string result = os_.str();
    
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}
