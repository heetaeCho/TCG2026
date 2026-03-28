#include <gtest/gtest.h>
#include <sstream>
#include <cmath>
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>
#include "canonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class CanonMakerNoteTest_955 : public ::testing::Test {
protected:
    CanonMakerNote maker_;
    std::ostringstream os_;
};

// Test that when value type is unsignedShort and count > 0, output is produced
TEST_F(CanonMakerNoteTest_955, PrintSi0x0003_NormalUnsignedShortValue_955) {
    ValueType<uint16_t> value;
    value.read("0");
    std::ostringstream os;
    maker_.printSi0x0003(os, value, nullptr);
    // For input 0: 100 * (0/32.0 + 5.0) = 500, output = 500/100.0 = 5.00
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("5.00"), std::string::npos);
}

// Test with a positive unsigned short value
TEST_F(CanonMakerNoteTest_955, PrintSi0x0003_PositiveValue_955) {
    ValueType<uint16_t> value;
    value.read("32");
    std::ostringstream os;
    maker_.printSi0x0003(os, value, nullptr);
    // For input 32: static_cast<short>(32) = 32, 100*(32/32.0 + 5.0) = 100*6.0 = 600, => 6.00
    std::string result = os.str();
    EXPECT_NE(result.find("6.00"), std::string::npos);
}

// Test with a value that would be interpreted as negative via static_cast<short>
TEST_F(CanonMakerNoteTest_955, PrintSi0x0003_LargeValueInterpretedAsNegative_955) {
    ValueType<uint16_t> value;
    // 65504 as uint16_t => static_cast<short> = -32
    value.read("65504");
    std::ostringstream os;
    maker_.printSi0x0003(os, value, nullptr);
    // -32/32.0 + 5.0 = -1.0 + 5.0 = 4.0, 100*4.0 = 400, => 4.00
    std::string result = os.str();
    EXPECT_NE(result.find("4.00"), std::string::npos);
}

// Test with value 160 (positive short)
TEST_F(CanonMakerNoteTest_955, PrintSi0x0003_Value160_955) {
    ValueType<uint16_t> value;
    value.read("160");
    std::ostringstream os;
    maker_.printSi0x0003(os, value, nullptr);
    // 160/32.0 = 5.0, 5.0 + 5.0 = 10.0, 100*10.0 = 1000, => 10.00
    std::string result = os.str();
    EXPECT_NE(result.find("10.00"), std::string::npos);
}

// Test that a non-unsignedShort type produces no output
TEST_F(CanonMakerNoteTest_955, PrintSi0x0003_NonUnsignedShortType_NoOutput_955) {
    ValueType<int32_t> value;
    value.read("100");
    std::ostringstream os;
    maker_.printSi0x0003(os, value, nullptr);
    EXPECT_TRUE(os.str().empty());
}

// Test that string value type produces no output
TEST_F(CanonMakerNoteTest_955, PrintSi0x0003_StringType_NoOutput_955) {
    StringValue value;
    value.read("hello");
    std::ostringstream os;
    maker_.printSi0x0003(os, value, nullptr);
    EXPECT_TRUE(os.str().empty());
}

// Test return value is the same ostream reference
TEST_F(CanonMakerNoteTest_955, PrintSi0x0003_ReturnsSameOstream_955) {
    ValueType<uint16_t> value;
    value.read("0");
    std::ostringstream os;
    std::ostream& result = maker_.printSi0x0003(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

// Test return value is the same ostream reference even when no output produced
TEST_F(CanonMakerNoteTest_955, PrintSi0x0003_ReturnsSameOstream_NonUnsignedShort_955) {
    ValueType<int32_t> value;
    value.read("0");
    std::ostringstream os;
    std::ostream& result = maker_.printSi0x0003(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

// Test with value that gives fractional result
TEST_F(CanonMakerNoteTest_955, PrintSi0x0003_FractionalResult_955) {
    ValueType<uint16_t> value;
    // 16 => 16/32.0 = 0.5, 0.5 + 5.0 = 5.5, 100*5.5 = 550, => 5.50
    value.read("16");
    std::ostringstream os;
    maker_.printSi0x0003(os, value, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find("5.50"), std::string::npos);
}

// Test with value 65535 (interpreted as -1 in short)
TEST_F(CanonMakerNoteTest_955, PrintSi0x0003_MaxUint16_955) {
    ValueType<uint16_t> value;
    // 65535 => static_cast<short> = -1, -1/32.0 = -0.03125, + 5.0 = 4.96875
    // 100 * 4.96875 = 496.875, lround => 497, => 4.97
    value.read("65535");
    std::ostringstream os;
    maker_.printSi0x0003(os, value, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find("4.97"), std::string::npos);
}

// Test with nullptr ExifData (should not crash)
TEST_F(CanonMakerNoteTest_955, PrintSi0x0003_NullExifData_955) {
    ValueType<uint16_t> value;
    value.read("64");
    std::ostringstream os;
    // Should not crash with nullptr
    EXPECT_NO_THROW(maker_.printSi0x0003(os, value, nullptr));
    // 64/32.0 = 2.0, + 5.0 = 7.0, => 7.00
    EXPECT_NE(os.str().find("7.00"), std::string::npos);
}

// Test boundary: value 0 interpreted as short 0
TEST_F(CanonMakerNoteTest_955, PrintSi0x0003_ZeroValue_955) {
    ValueType<uint16_t> value;
    value.read("0");
    std::ostringstream os;
    maker_.printSi0x0003(os, value, nullptr);
    // 0/32.0 + 5.0 = 5.0, 100*5.0 = 500, => 5.00
    EXPECT_NE(os.str().find("5.00"), std::string::npos);
}

// Test with 32768 which is -32768 as short
TEST_F(CanonMakerNoteTest_955, PrintSi0x0003_Value32768_NegativeShort_955) {
    ValueType<uint16_t> value;
    // 32768 => static_cast<short> = -32768
    // -32768/32.0 = -1024.0, + 5.0 = -1019.0, 100*(-1019.0) = -101900, => -1019.00
    value.read("32768");
    std::ostringstream os;
    maker_.printSi0x0003(os, value, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find("-1019.00"), std::string::npos);
}
