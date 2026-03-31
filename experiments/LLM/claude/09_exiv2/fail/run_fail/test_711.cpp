#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

// Include the header that declares PanasonicMakerNote
// Since we're given the implementation directly, we need to access it
namespace Exiv2 {
namespace Internal {
class PanasonicMakerNote {
 public:
  std::ostream& print0x0036(std::ostream& os, const Value& value, const ExifData*);
};
}  // namespace Internal
}  // namespace Exiv2

// We need the actual implementation linked in, but declare it here for compilation
// The actual implementation is in panasonicmn_int.cpp

using namespace Exiv2;
using namespace Exiv2::Internal;

class PanasonicMakerNoteTest_711 : public ::testing::Test {
 protected:
  PanasonicMakerNote maker_note_;
  std::ostringstream os_;
};

// Test that value 65535 outputs "not set" (the N_ macro typically returns the string as-is)
TEST_F(PanasonicMakerNoteTest_711, Print0x0036_Value65535_PrintsNotSet_711) {
  Exiv2::ValueType<uint16_t> value;
  value.read("65535");
  maker_note_.print0x0036(os_, value, nullptr);
  // N_("not set") should resolve to "not set" in a non-localized context
  EXPECT_EQ(os_.str(), "not set");
}

// Test that a normal value (not 65535) is printed as the value itself
TEST_F(PanasonicMakerNoteTest_711, Print0x0036_NormalValue_PrintsValue_711) {
  Exiv2::ValueType<uint16_t> value;
  value.read("100");
  maker_note_.print0x0036(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "100");
}

// Test with value 0
TEST_F(PanasonicMakerNoteTest_711, Print0x0036_ZeroValue_PrintsZero_711) {
  Exiv2::ValueType<uint16_t> value;
  value.read("0");
  maker_note_.print0x0036(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "0");
}

// Test with value 1
TEST_F(PanasonicMakerNoteTest_711, Print0x0036_ValueOne_PrintsOne_711) {
  Exiv2::ValueType<uint16_t> value;
  value.read("1");
  maker_note_.print0x0036(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "1");
}

// Test with value 65534 (boundary, one less than 65535)
TEST_F(PanasonicMakerNoteTest_711, Print0x0036_Value65534_PrintsValue_711) {
  Exiv2::ValueType<uint16_t> value;
  value.read("65534");
  maker_note_.print0x0036(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "65534");
}

// Test that the function returns a reference to the same ostream
TEST_F(PanasonicMakerNoteTest_711, Print0x0036_ReturnsOstream_711) {
  Exiv2::ValueType<uint16_t> value;
  value.read("42");
  std::ostream& result = maker_note_.print0x0036(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

// Test that the function returns a reference to the same ostream for the 65535 case
TEST_F(PanasonicMakerNoteTest_711, Print0x0036_ReturnsOstream_NotSet_711) {
  Exiv2::ValueType<uint16_t> value;
  value.read("65535");
  std::ostream& result = maker_note_.print0x0036(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

// Test with nullptr ExifData (should not crash)
TEST_F(PanasonicMakerNoteTest_711, Print0x0036_NullExifData_DoesNotCrash_711) {
  Exiv2::ValueType<uint16_t> value;
  value.read("500");
  EXPECT_NO_THROW(maker_note_.print0x0036(os_, value, nullptr));
  EXPECT_EQ(os_.str(), "500");
}

// Test with a signed long value type where value is 65535
TEST_F(PanasonicMakerNoteTest_711, Print0x0036_SignedLongValue65535_PrintsNotSet_711) {
  Exiv2::ValueType<int32_t> value;
  value.read("65535");
  maker_note_.print0x0036(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "not set");
}

// Test with a larger value using int32
TEST_F(PanasonicMakerNoteTest_711, Print0x0036_LargeValueNotSpecial_PrintsValue_711) {
  Exiv2::ValueType<int32_t> value;
  value.read("70000");
  maker_note_.print0x0036(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "70000");
}

// Test with value 255
TEST_F(PanasonicMakerNoteTest_711, Print0x0036_Value255_PrintsValue_711) {
  Exiv2::ValueType<uint16_t> value;
  value.read("255");
  maker_note_.print0x0036(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "255");
}

// Test chaining: print twice to same stream
TEST_F(PanasonicMakerNoteTest_711, Print0x0036_MultiplePrints_ConcatenatesOutput_711) {
  Exiv2::ValueType<uint16_t> value1;
  value1.read("10");
  Exiv2::ValueType<uint16_t> value2;
  value2.read("65535");

  maker_note_.print0x0036(os_, value1, nullptr);
  maker_note_.print0x0036(os_, value2, nullptr);
  EXPECT_EQ(os_.str(), "10not set");
}
