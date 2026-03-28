#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <cmath>
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>
#include "canonmn_int.hpp"

// We need to access the CanonMakerNote class from the Internal namespace
// Since the class is in Internal namespace, we include relevant headers

using namespace Exiv2;
using namespace Exiv2::Internal;

class CanonMakerNoteTest_953 : public ::testing::Test {
protected:
    CanonMakerNote maker_;
    std::ostringstream os_;
};

// Test: printSi0x0001 with a valid unsignedShort value with count > 0
TEST_F(CanonMakerNoteTest_953, PrintSi0x0001_ValidUnsignedShort_953) {
    ValueType<uint16_t> value;
    value.value_.push_back(0);  // value of 0

    std::ostringstream os;
    maker_.printSi0x0001(os, value, nullptr);

    // With value 0, canonEv(0)/32 = 0, std::exp2(0) * 100 = 100
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test: printSi0x0001 with non-unsignedShort type should produce no output
TEST_F(CanonMakerNoteTest_953, PrintSi0x0001_WrongType_NoOutput_953) {
    ValueType<int32_t> value;  // signedLong type, not unsignedShort
    value.value_.push_back(100);

    std::ostringstream os;
    auto& ret = maker_.printSi0x0001(os, value, nullptr);

    EXPECT_TRUE(os.str().empty());
    EXPECT_EQ(&ret, &os);
}

// Test: printSi0x0001 returns the ostream reference
TEST_F(CanonMakerNoteTest_953, PrintSi0x0001_ReturnsOstream_953) {
    ValueType<uint16_t> value;
    value.value_.push_back(32);

    std::ostringstream os;
    std::ostream& result = maker_.printSi0x0001(os, value, nullptr);

    EXPECT_EQ(&result, &os);
}

// Test: printSi0x0001 with unsignedShort but count == 0 should produce no output
TEST_F(CanonMakerNoteTest_953, PrintSi0x0001_EmptyValue_NoOutput_953) {
    ValueType<uint16_t> value;  // count is 0

    std::ostringstream os;
    maker_.printSi0x0001(os, value, nullptr);

    EXPECT_TRUE(os.str().empty());
}

// Test: printSi0x0001 with a specific known value
TEST_F(CanonMakerNoteTest_953, PrintSi0x0001_SpecificValue_953) {
    ValueType<uint16_t> value;
    // value = 32 means canonEv(32)/32 should give some known result
    value.value_.push_back(32);

    std::ostringstream os;
    maker_.printSi0x0001(os, value, nullptr);

    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test: printSi0x0001 with multiple values (count > 1), should use first value
TEST_F(CanonMakerNoteTest_953, PrintSi0x0001_MultipleValues_953) {
    ValueType<uint16_t> value;
    value.value_.push_back(0);
    value.value_.push_back(64);
    value.value_.push_back(128);

    std::ostringstream os;
    maker_.printSi0x0001(os, value, nullptr);

    // Should produce output since count > 0 and type is unsignedShort
    EXPECT_FALSE(os.str().empty());
}

// Test: printSi0x0001 with nullptr ExifData (should work fine)
TEST_F(CanonMakerNoteTest_953, PrintSi0x0001_NullExifData_953) {
    ValueType<uint16_t> value;
    value.value_.push_back(96);

    std::ostringstream os;
    // Should not crash with nullptr ExifData
    EXPECT_NO_THROW(maker_.printSi0x0001(os, value, nullptr));
    EXPECT_FALSE(os.str().empty());
}

// Test: printSi0x0001 with value of 0 produces expected result (exp2(0)*100 = 100)
TEST_F(CanonMakerNoteTest_953, PrintSi0x0001_ZeroValue_ProducesHundred_953) {
    ValueType<uint16_t> value;
    value.value_.push_back(0);

    std::ostringstream os;
    maker_.printSi0x0001(os, value, nullptr);

    std::string result = os.str();
    // canonEv(0) should return 0, exp2(0/32)*100 = 100
    // The exact format depends on the float formatting
    EXPECT_FALSE(result.empty());
    // Check that the output contains "100" 
    float parsed = std::stof(result);
    EXPECT_FLOAT_EQ(parsed, 100.0f);
}

// Test: printSi0x0001 with a large unsignedShort value
TEST_F(CanonMakerNoteTest_953, PrintSi0x0001_LargeValue_953) {
    ValueType<uint16_t> value;
    value.value_.push_back(65535);  // max uint16_t

    std::ostringstream os;
    EXPECT_NO_THROW(maker_.printSi0x0001(os, value, nullptr));
}

// Test: printSi0x0001 with signedShort type (not unsignedShort) should produce no output
TEST_F(CanonMakerNoteTest_953, PrintSi0x0001_SignedShort_NoOutput_953) {
    ValueType<int16_t> value;  // signedShort type
    value.value_.push_back(100);

    std::ostringstream os;
    maker_.printSi0x0001(os, value, nullptr);

    // signedShort != unsignedShort, so no output expected
    EXPECT_TRUE(os.str().empty());
}

// Test: printSi0x0001 with string type should produce no output
TEST_F(CanonMakerNoteTest_953, PrintSi0x0001_StringType_NoOutput_953) {
    StringValue value;
    value.read("test");

    std::ostringstream os;
    maker_.printSi0x0001(os, value, nullptr);

    EXPECT_TRUE(os.str().empty());
}
