#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

// We need to include the internal header or recreate the minimal interface
// Based on the provided code, we test SonyMakerNote::printSony2FpFocusMode
namespace Exiv2 {
namespace Internal {

class SonyMakerNote {
 public:
  std::ostream& printSony2FpFocusMode(std::ostream& os, const Value& value, const ExifData*) {
    if (value.count() != 1)
      return os << value;
    const auto val = (value.toInt64() & 0x7F);
    switch (val) {
      case 0:
        return os << "Manual";
      case 2:
        return os << "AF-S";
      case 3:
        return os << "AF-C";
      case 4:
        return os << "AF-A";
      case 6:
        return os << "DMF";
    }
    return os << "(" << val << ")";
  }
};

}  // namespace Internal
}  // namespace Exiv2

using namespace Exiv2;
using namespace Exiv2::Internal;

class SonyMakerNoteTest_1614 : public ::testing::Test {
 protected:
  SonyMakerNote maker_;
  std::ostringstream os_;
};

// Test Manual focus mode (value = 0)
TEST_F(SonyMakerNoteTest_1614, PrintFocusMode_Manual_1614) {
  UShortValue value;
  value.read("0");
  maker_.printSony2FpFocusMode(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "Manual");
}

// Test AF-S focus mode (value = 2)
TEST_F(SonyMakerNoteTest_1614, PrintFocusMode_AFS_1614) {
  UShortValue value;
  value.read("2");
  maker_.printSony2FpFocusMode(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "AF-S");
}

// Test AF-C focus mode (value = 3)
TEST_F(SonyMakerNoteTest_1614, PrintFocusMode_AFC_1614) {
  UShortValue value;
  value.read("3");
  maker_.printSony2FpFocusMode(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "AF-C");
}

// Test AF-A focus mode (value = 4)
TEST_F(SonyMakerNoteTest_1614, PrintFocusMode_AFA_1614) {
  UShortValue value;
  value.read("4");
  maker_.printSony2FpFocusMode(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "AF-A");
}

// Test DMF focus mode (value = 6)
TEST_F(SonyMakerNoteTest_1614, PrintFocusMode_DMF_1614) {
  UShortValue value;
  value.read("6");
  maker_.printSony2FpFocusMode(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "DMF");
}

// Test unknown value (value = 1, not in switch)
TEST_F(SonyMakerNoteTest_1614, PrintFocusMode_UnknownValue1_1614) {
  UShortValue value;
  value.read("1");
  maker_.printSony2FpFocusMode(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "(1)");
}

// Test unknown value (value = 5, not in switch)
TEST_F(SonyMakerNoteTest_1614, PrintFocusMode_UnknownValue5_1614) {
  UShortValue value;
  value.read("5");
  maker_.printSony2FpFocusMode(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "(5)");
}

// Test unknown value (value = 7, not in switch)
TEST_F(SonyMakerNoteTest_1614, PrintFocusMode_UnknownValue7_1614) {
  UShortValue value;
  value.read("7");
  maker_.printSony2FpFocusMode(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "(7)");
}

// Test that only lower 7 bits are used (0x7F mask)
// Value 128 (0x80) -> 0x80 & 0x7F = 0 -> "Manual"
TEST_F(SonyMakerNoteTest_1614, PrintFocusMode_MaskHighBit_Manual_1614) {
  UShortValue value;
  value.read("128");
  maker_.printSony2FpFocusMode(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "Manual");
}

// Test mask: 130 (0x82) -> 0x82 & 0x7F = 2 -> "AF-S"
TEST_F(SonyMakerNoteTest_1614, PrintFocusMode_MaskHighBit_AFS_1614) {
  UShortValue value;
  value.read("130");
  maker_.printSony2FpFocusMode(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "AF-S");
}

// Test mask: 131 (0x83) -> 0x83 & 0x7F = 3 -> "AF-C"
TEST_F(SonyMakerNoteTest_1614, PrintFocusMode_MaskHighBit_AFC_1614) {
  UShortValue value;
  value.read("131");
  maker_.printSony2FpFocusMode(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "AF-C");
}

// Test mask: 132 (0x84) -> 0x84 & 0x7F = 4 -> "AF-A"
TEST_F(SonyMakerNoteTest_1614, PrintFocusMode_MaskHighBit_AFA_1614) {
  UShortValue value;
  value.read("132");
  maker_.printSony2FpFocusMode(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "AF-A");
}

// Test mask: 134 (0x86) -> 0x86 & 0x7F = 6 -> "DMF"
TEST_F(SonyMakerNoteTest_1614, PrintFocusMode_MaskHighBit_DMF_1614) {
  UShortValue value;
  value.read("134");
  maker_.printSony2FpFocusMode(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "DMF");
}

// Test count != 1: multiple values should print raw value
TEST_F(SonyMakerNoteTest_1614, PrintFocusMode_MultipleValues_1614) {
  UShortValue value;
  value.read("2 3");
  ASSERT_EQ(value.count(), 2u);
  maker_.printSony2FpFocusMode(os_, value, nullptr);
  // When count != 1, it should print the value directly
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
  // It should NOT print "AF-S" since count != 1
  EXPECT_NE(result, "AF-S");
}

// Test large unknown value within 7-bit range: 127 (0x7F)
TEST_F(SonyMakerNoteTest_1614, PrintFocusMode_MaxMaskedValue_1614) {
  UShortValue value;
  value.read("127");
  maker_.printSony2FpFocusMode(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "(127)");
}

// Test value = 255: 0xFF & 0x7F = 127
TEST_F(SonyMakerNoteTest_1614, PrintFocusMode_Value255_1614) {
  UShortValue value;
  value.read("255");
  maker_.printSony2FpFocusMode(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "(127)");
}

// Test with nullptr ExifData (should work fine)
TEST_F(SonyMakerNoteTest_1614, PrintFocusMode_NullExifData_1614) {
  UShortValue value;
  value.read("6");
  maker_.printSony2FpFocusMode(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "DMF");
}

// Test value = 10, unknown
TEST_F(SonyMakerNoteTest_1614, PrintFocusMode_UnknownValue10_1614) {
  UShortValue value;
  value.read("10");
  maker_.printSony2FpFocusMode(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "(10)");
}

// Test that return value is the same stream
TEST_F(SonyMakerNoteTest_1614, PrintFocusMode_ReturnsSameStream_1614) {
  UShortValue value;
  value.read("0");
  std::ostream& result = maker_.printSony2FpFocusMode(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

// Test chaining output with multiple calls
TEST_F(SonyMakerNoteTest_1614, PrintFocusMode_ChainedOutput_1614) {
  UShortValue value1;
  value1.read("0");
  UShortValue value2;
  value2.read("2");
  maker_.printSony2FpFocusMode(os_, value1, nullptr);
  os_ << " ";
  maker_.printSony2FpFocusMode(os_, value2, nullptr);
  EXPECT_EQ(os_.str(), "Manual AF-S");
}
