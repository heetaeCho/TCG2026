#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

// We need access to the internal function. Since it's defined in a namespace
// but is static, we need to include the source or find another way.
// Since the function is static in the .cpp file, we need to test it indirectly
// or re-declare access. However, given the constraints, we'll test through
// the Samsung MakerNote tags if they're registered, or we need to find
// a way to access the function.

// Since the function is static (file-local linkage), we cannot directly call it
// from a test file. However, we can test it through the tag print functions
// that are registered for Samsung MakerNote tags, which use this function
// as a print function.

// Alternative approach: include the .cpp file to get access to the static function
// This is a common testing technique for static functions.
#include "samsungmn_int.cpp"

namespace {

using namespace Exiv2;
using namespace Exiv2::Internal;

class SamsungMnTest_1721 : public ::testing::Test {
protected:
    std::ostringstream os;
};

// Test normal operation with a valid signedRational value with count 1
TEST_F(SamsungMnTest_1721, PrintCameraTemperature_ValidSignedRational_1721) {
    RationalValue val; // This is for unsignedRational
    // We need signedRational - use SRationalValue
    // Exiv2 uses ValueType<Rational> for unsignedRational and ValueType<SRational> for signedRational
    
    // signedRational value
    ValueType<SRational> sval;
    sval.value_.push_back(SRational(25, 1));
    
    printCameraTemperature(os, sval, nullptr);
    
    std::string result = os.str();
    EXPECT_TRUE(result.find("25") != std::string::npos);
    EXPECT_TRUE(result.find("C") != std::string::npos);
}

// Test with signedRational representing a fractional temperature
TEST_F(SamsungMnTest_1721, PrintCameraTemperature_FractionalTemperature_1721) {
    ValueType<SRational> sval;
    sval.value_.push_back(SRational(50, 2)); // 25.0
    
    printCameraTemperature(os, sval, nullptr);
    
    std::string result = os.str();
    EXPECT_TRUE(result.find("25") != std::string::npos);
    EXPECT_TRUE(result.find("C") != std::string::npos);
}

// Test with negative temperature
TEST_F(SamsungMnTest_1721, PrintCameraTemperature_NegativeTemperature_1721) {
    ValueType<SRational> sval;
    sval.value_.push_back(SRational(-10, 1));
    
    printCameraTemperature(os, sval, nullptr);
    
    std::string result = os.str();
    EXPECT_TRUE(result.find("-10") != std::string::npos);
    EXPECT_TRUE(result.find("C") != std::string::npos);
}

// Test with zero temperature
TEST_F(SamsungMnTest_1721, PrintCameraTemperature_ZeroTemperature_1721) {
    ValueType<SRational> sval;
    sval.value_.push_back(SRational(0, 1));
    
    printCameraTemperature(os, sval, nullptr);
    
    std::string result = os.str();
    EXPECT_TRUE(result.find("0") != std::string::npos);
    EXPECT_TRUE(result.find("C") != std::string::npos);
}

// Test boundary: count != 1 (count == 0) should just print value directly
TEST_F(SamsungMnTest_1721, PrintCameraTemperature_EmptyValue_1721) {
    ValueType<SRational> sval;
    // No values pushed, count == 0
    
    printCameraTemperature(os, sval, nullptr);
    
    std::string result = os.str();
    // Should not contain " C" since count != 1
    EXPECT_TRUE(result.find(" C") == std::string::npos);
}

// Test boundary: count > 1 should just print value directly
TEST_F(SamsungMnTest_1721, PrintCameraTemperature_MultipleValues_1721) {
    ValueType<SRational> sval;
    sval.value_.push_back(SRational(25, 1));
    sval.value_.push_back(SRational(30, 1));
    
    printCameraTemperature(os, sval, nullptr);
    
    std::string result = os.str();
    // count is 2, not 1, so it should fall through to raw print
    EXPECT_TRUE(result.find(" C") == std::string::npos);
}

// Test with wrong type (unsignedRational instead of signedRational)
TEST_F(SamsungMnTest_1721, PrintCameraTemperature_WrongType_UnsignedRational_1721) {
    ValueType<URational> uval;
    uval.value_.push_back(URational(25, 1));
    
    printCameraTemperature(os, uval, nullptr);
    
    std::string result = os.str();
    // typeId is unsignedRational, not signedRational, so should just print value
    EXPECT_TRUE(result.find(" C") == std::string::npos);
}

// Test with wrong type (integer type)
TEST_F(SamsungMnTest_1721, PrintCameraTemperature_WrongType_Integer_1721) {
    ValueType<int32_t> ival;
    ival.value_.push_back(25);
    
    printCameraTemperature(os, ival, nullptr);
    
    std::string result = os.str();
    // typeId is signedLong, not signedRational
    EXPECT_TRUE(result.find(" C") == std::string::npos);
}

// Test with large positive temperature
TEST_F(SamsungMnTest_1721, PrintCameraTemperature_LargePositiveTemp_1721) {
    ValueType<SRational> sval;
    sval.value_.push_back(SRational(1000, 1));
    
    printCameraTemperature(os, sval, nullptr);
    
    std::string result = os.str();
    EXPECT_TRUE(result.find("1000") != std::string::npos);
    EXPECT_TRUE(result.find("C") != std::string::npos);
}

// Test with large negative temperature
TEST_F(SamsungMnTest_1721, PrintCameraTemperature_LargeNegativeTemp_1721) {
    ValueType<SRational> sval;
    sval.value_.push_back(SRational(-273, 1));
    
    printCameraTemperature(os, sval, nullptr);
    
    std::string result = os.str();
    EXPECT_TRUE(result.find("-273") != std::string::npos);
    EXPECT_TRUE(result.find("C") != std::string::npos);
}

// Test that the output ends with " C" for valid input
TEST_F(SamsungMnTest_1721, PrintCameraTemperature_OutputFormat_1721) {
    ValueType<SRational> sval;
    sval.value_.push_back(SRational(42, 1));
    
    printCameraTemperature(os, sval, nullptr);
    
    std::string result = os.str();
    // Should end with " C"
    ASSERT_GE(result.size(), 2u);
    EXPECT_EQ(result.substr(result.size() - 2), " C");
}

// Test with ExifData being nullptr (should not crash)
TEST_F(SamsungMnTest_1721, PrintCameraTemperature_NullExifData_1721) {
    ValueType<SRational> sval;
    sval.value_.push_back(SRational(20, 1));
    
    EXPECT_NO_THROW(printCameraTemperature(os, sval, nullptr));
    
    std::string result = os.str();
    EXPECT_TRUE(result.find("C") != std::string::npos);
}

// Test return value is the same stream
TEST_F(SamsungMnTest_1721, PrintCameraTemperature_ReturnsSameStream_1721) {
    ValueType<SRational> sval;
    sval.value_.push_back(SRational(15, 1));
    
    std::ostream& returned = printCameraTemperature(os, sval, nullptr);
    
    EXPECT_EQ(&returned, &os);
}

// Test return value is the same stream for error case too
TEST_F(SamsungMnTest_1721, PrintCameraTemperature_ReturnsSameStreamOnError_1721) {
    ValueType<SRational> sval;
    // empty - count != 1
    
    std::ostream& returned = printCameraTemperature(os, sval, nullptr);
    
    EXPECT_EQ(&returned, &os);
}

} // namespace
