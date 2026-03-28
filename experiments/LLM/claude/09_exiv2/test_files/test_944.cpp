#include <gtest/gtest.h>
#include <sstream>
#include <cstdint>

// Include necessary Exiv2 headers
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

// We need access to the Internal namespace
// Since the class is defined in canonmn_int.cpp, we need to include appropriate headers
// or redeclare the class interface for testing purposes.
// Based on the provided code, we'll include the internal header if available.
#include "canonmn_int.hpp"

namespace {

using namespace Exiv2;
using namespace Exiv2::Internal;

class CanonMakerNoteTest_944 : public ::testing::Test {
 protected:
  CanonMakerNote maker_note_;
  std::ostringstream os_;
};

// Test normal operation with a typical value
TEST_F(CanonMakerNoteTest_944, Print0x000a_NormalValue_944) {
  // Value where upper 16 bits and lower 16 bits are both non-zero
  // Let's use value = (0x0001 << 16) | 0x00001 = 65537
  ULongValue value;
  value.read("65537");  // 0x00010001
  
  maker_note_.print0x000a(os_, value, nullptr);
  
  // upper 16 bits: 0x0001, lower 16 bits: 0x0001 = 1
  // Expected: "000100001"
  EXPECT_EQ(os_.str(), "000100001");
}

// Test with zero value
TEST_F(CanonMakerNoteTest_944, Print0x000a_ZeroValue_944) {
  ULongValue value;
  value.read("0");
  
  maker_note_.print0x000a(os_, value, nullptr);
  
  // upper 16 bits: 0x0000, lower 16 bits: 0x0000 = 0
  // Expected: "000000000"
  EXPECT_EQ(os_.str(), "000000000");
}

// Test with maximum 32-bit value
TEST_F(CanonMakerNoteTest_944, Print0x000a_MaxUint32_944) {
  ULongValue value;
  value.read("4294967295");  // 0xFFFFFFFF
  
  maker_note_.print0x000a(os_, value, nullptr);
  
  // upper 16 bits: 0xFFFF, lower 16 bits: 0xFFFF = 65535
  // Expected: "ffff65535"
  EXPECT_EQ(os_.str(), "ffff65535");
}

// Test with value where only upper 16 bits are set
TEST_F(CanonMakerNoteTest_944, Print0x000a_OnlyUpperBitsSet_944) {
  ULongValue value;
  // 0xABCD0000 = 2882338816
  value.read("2882338816");
  
  maker_note_.print0x000a(os_, value, nullptr);
  
  // upper 16 bits: 0xABCD, lower 16 bits: 0x0000 = 0
  // Expected: "abcd00000"
  EXPECT_EQ(os_.str(), "abcd00000");
}

// Test with value where only lower 16 bits are set
TEST_F(CanonMakerNoteTest_944, Print0x000a_OnlyLowerBitsSet_944) {
  ULongValue value;
  // 0x0000FFFF = 65535
  value.read("65535");
  
  maker_note_.print0x000a(os_, value, nullptr);
  
  // upper 16 bits: 0x0000, lower 16 bits: 0xFFFF = 65535
  // Expected: "000065535"
  EXPECT_EQ(os_.str(), "000065535");
}

// Test with value = 1 (minimal non-zero)
TEST_F(CanonMakerNoteTest_944, Print0x000a_MinimalNonZero_944) {
  ULongValue value;
  value.read("1");
  
  maker_note_.print0x000a(os_, value, nullptr);
  
  // upper 16 bits: 0x0000, lower 16 bits: 0x0001 = 1
  // Expected: "000000001"
  EXPECT_EQ(os_.str(), "000000001");
}

// Test with value = 0x00010000 (65536) - boundary between upper and lower
TEST_F(CanonMakerNoteTest_944, Print0x000a_BoundaryUpperLower_944) {
  ULongValue value;
  value.read("65536");  // 0x00010000
  
  maker_note_.print0x000a(os_, value, nullptr);
  
  // upper 16 bits: 0x0001, lower 16 bits: 0x0000 = 0
  // Expected: "000100000"
  EXPECT_EQ(os_.str(), "000100000");
}

// Test that the function returns the ostream reference
TEST_F(CanonMakerNoteTest_944, Print0x000a_ReturnsOstream_944) {
  ULongValue value;
  value.read("0");
  
  std::ostream& result = maker_note_.print0x000a(os_, value, nullptr);
  
  EXPECT_EQ(&result, &os_);
}

// Test with a specific known firmware-like value
TEST_F(CanonMakerNoteTest_944, Print0x000a_FirmwareLikeValue_944) {
  ULongValue value;
  // 0x01020304 = 16909060
  value.read("16909060");
  
  maker_note_.print0x000a(os_, value, nullptr);
  
  // upper 16 bits: 0x0102, lower 16 bits: 0x0304 = 772
  // Expected: "010200772"
  EXPECT_EQ(os_.str(), "010200772");
}

// Test with value where lower 16 bits produce exactly 5 digits
TEST_F(CanonMakerNoteTest_944, Print0x000a_LowerBits5Digits_944) {
  ULongValue value;
  // lower 16 bits = 10000, upper 16 bits = 0x0000
  // value = 10000
  value.read("10000");
  
  maker_note_.print0x000a(os_, value, nullptr);
  
  // upper 16 bits: 0x0000, lower 16 bits: 10000
  // Expected: "000010000"
  EXPECT_EQ(os_.str(), "000010000");
}

// Test with nullptr ExifData (should work fine)
TEST_F(CanonMakerNoteTest_944, Print0x000a_NullExifData_944) {
  ULongValue value;
  value.read("123456789");
  
  // Should not crash with nullptr ExifData
  EXPECT_NO_THROW(maker_note_.print0x000a(os_, value, nullptr));
}

}  // namespace
