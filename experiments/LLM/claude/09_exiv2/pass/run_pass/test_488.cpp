#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>

// Include the internal header for Nikon3MakerNote
// We need access to the class under test
namespace Exiv2 {
namespace Internal {
class Nikon3MakerNote;
}
}

// We need to include the actual implementation headers
#include "nikonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class Nikon3MakerNoteTest_488 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test printExternalFlashData2 with a valid unsignedByte value of count 1, value 0 -> "Off"
TEST_F(Nikon3MakerNoteTest_488, PrintExternalFlashData2_Value0_Off_488) {
  std::ostringstream os;
  auto value = Value::create(unsignedByte);
  value->read("0");
  Nikon3MakerNote::printExternalFlashData2(os, *value, nullptr);
  EXPECT_EQ(os.str(), "Off");
}

// Test printExternalFlashData2 with value 1 -> "TTL"
TEST_F(Nikon3MakerNoteTest_488, PrintExternalFlashData2_Value1_TTL_488) {
  std::ostringstream os;
  auto value = Value::create(unsignedByte);
  value->read("1");
  Nikon3MakerNote::printExternalFlashData2(os, *value, nullptr);
  EXPECT_EQ(os.str(), "TTL");
}

// Test printExternalFlashData2 with value 2 -> "iTTL"
TEST_F(Nikon3MakerNoteTest_488, PrintExternalFlashData2_Value2_iTTL_488) {
  std::ostringstream os;
  auto value = Value::create(unsignedByte);
  value->read("2");
  Nikon3MakerNote::printExternalFlashData2(os, *value, nullptr);
  EXPECT_EQ(os.str(), "iTTL");
}

// Test printExternalFlashData2 with value 3 -> "Auto Aperture"
TEST_F(Nikon3MakerNoteTest_488, PrintExternalFlashData2_Value3_AutoAperture_488) {
  std::ostringstream os;
  auto value = Value::create(unsignedByte);
  value->read("3");
  Nikon3MakerNote::printExternalFlashData2(os, *value, nullptr);
  EXPECT_EQ(os.str(), "Auto Aperture");
}

// Test printExternalFlashData2 with value 4 -> "Automatic"
TEST_F(Nikon3MakerNoteTest_488, PrintExternalFlashData2_Value4_Automatic_488) {
  std::ostringstream os;
  auto value = Value::create(unsignedByte);
  value->read("4");
  Nikon3MakerNote::printExternalFlashData2(os, *value, nullptr);
  EXPECT_EQ(os.str(), "Automatic");
}

// Test printExternalFlashData2 with value 5 -> "GN (distance priority)"
TEST_F(Nikon3MakerNoteTest_488, PrintExternalFlashData2_Value5_GN_488) {
  std::ostringstream os;
  auto value = Value::create(unsignedByte);
  value->read("5");
  Nikon3MakerNote::printExternalFlashData2(os, *value, nullptr);
  EXPECT_EQ(os.str(), "GN (distance priority)");
}

// Test printExternalFlashData2 with value 6 -> "Manual"
TEST_F(Nikon3MakerNoteTest_488, PrintExternalFlashData2_Value6_Manual_488) {
  std::ostringstream os;
  auto value = Value::create(unsignedByte);
  value->read("6");
  Nikon3MakerNote::printExternalFlashData2(os, *value, nullptr);
  EXPECT_EQ(os.str(), "Manual");
}

// Test printExternalFlashData2 with value 7 -> "Repeating Flash"
TEST_F(Nikon3MakerNoteTest_488, PrintExternalFlashData2_Value7_RepeatingFlash_488) {
  std::ostringstream os;
  auto value = Value::create(unsignedByte);
  value->read("7");
  Nikon3MakerNote::printExternalFlashData2(os, *value, nullptr);
  EXPECT_EQ(os.str(), "Repeating Flash");
}

// Test printExternalFlashData2 with masking: value 0x10 should mask to 0 -> "Off"
// Because 0x10 & 0x0F = 0
TEST_F(Nikon3MakerNoteTest_488, PrintExternalFlashData2_Value16_MaskedToOff_488) {
  std::ostringstream os;
  auto value = Value::create(unsignedByte);
  value->read("16");
  Nikon3MakerNote::printExternalFlashData2(os, *value, nullptr);
  EXPECT_EQ(os.str(), "Off");
}

// Test printExternalFlashData2 with masking: value 0x21 (33) & 0x0F = 1 -> "TTL"
TEST_F(Nikon3MakerNoteTest_488, PrintExternalFlashData2_Value33_MaskedToTTL_488) {
  std::ostringstream os;
  auto value = Value::create(unsignedByte);
  value->read("33");
  Nikon3MakerNote::printExternalFlashData2(os, *value, nullptr);
  EXPECT_EQ(os.str(), "TTL");
}

// Test printExternalFlashData2 with masking: value 0xF2 (242) & 0x0F = 2 -> "iTTL"
TEST_F(Nikon3MakerNoteTest_488, PrintExternalFlashData2_Value242_MaskedToiTTL_488) {
  std::ostringstream os;
  auto value = Value::create(unsignedByte);
  value->read("242");
  Nikon3MakerNote::printExternalFlashData2(os, *value, nullptr);
  EXPECT_EQ(os.str(), "iTTL");
}

// Test printExternalFlashData2 with value that masked result is out of range (e.g., 8)
// value 8 & 0x0F = 8, which is not in the nikonFlashControlMode table
TEST_F(Nikon3MakerNoteTest_488, PrintExternalFlashData2_Value8_OutOfRange_488) {
  std::ostringstream os;
  auto value = Value::create(unsignedByte);
  value->read("8");
  Nikon3MakerNote::printExternalFlashData2(os, *value, nullptr);
  // Out of range values typically print as "(8)"
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// Test printExternalFlashData2 with wrong type (unsignedShort instead of unsignedByte)
// Should print "(<value>)" format
TEST_F(Nikon3MakerNoteTest_488, PrintExternalFlashData2_WrongType_UnsignedShort_488) {
  std::ostringstream os;
  auto value = Value::create(unsignedShort);
  value->read("1");
  Nikon3MakerNote::printExternalFlashData2(os, *value, nullptr);
  std::string result = os.str();
  // Should output in parenthesized format since typeId != unsignedByte
  EXPECT_NE(result.find("("), std::string::npos);
  EXPECT_NE(result.find(")"), std::string::npos);
}

// Test printExternalFlashData2 with wrong count (multiple values)
// Should print "(<values>)" format
TEST_F(Nikon3MakerNoteTest_488, PrintExternalFlashData2_MultipleValues_488) {
  std::ostringstream os;
  auto value = Value::create(unsignedByte);
  value->read("1 2");
  Nikon3MakerNote::printExternalFlashData2(os, *value, nullptr);
  std::string result = os.str();
  // count != 1, so should output parenthesized
  EXPECT_NE(result.find("("), std::string::npos);
  EXPECT_NE(result.find(")"), std::string::npos);
}

// Test printExternalFlashData2 with ExifData pointer (non-null but empty)
TEST_F(Nikon3MakerNoteTest_488, PrintExternalFlashData2_WithEmptyExifData_488) {
  std::ostringstream os;
  ExifData exifData;
  auto value = Value::create(unsignedByte);
  value->read("2");
  Nikon3MakerNote::printExternalFlashData2(os, *value, &exifData);
  EXPECT_EQ(os.str(), "iTTL");
}

// Test printExternalFlashData2 with masking: value 0xFF & 0x0F = 15, out of table range
TEST_F(Nikon3MakerNoteTest_488, PrintExternalFlashData2_Value255_Masked15_488) {
  std::ostringstream os;
  auto value = Value::create(unsignedByte);
  value->read("255");
  Nikon3MakerNote::printExternalFlashData2(os, *value, nullptr);
  std::string result = os.str();
  // 255 & 0x0F = 15, not in table
  EXPECT_FALSE(result.empty());
}

// Test printExternalFlashData2 with value 0x37 (55) & 0x0F = 7 -> "Repeating Flash"
TEST_F(Nikon3MakerNoteTest_488, PrintExternalFlashData2_Value55_MaskedToRepeatingFlash_488) {
  std::ostringstream os;
  auto value = Value::create(unsignedByte);
  value->read("55");
  Nikon3MakerNote::printExternalFlashData2(os, *value, nullptr);
  EXPECT_EQ(os.str(), "Repeating Flash");
}

// Test printExternalFlashData2 with signedByte type (not unsignedByte)
TEST_F(Nikon3MakerNoteTest_488, PrintExternalFlashData2_SignedByte_488) {
  std::ostringstream os;
  auto value = Value::create(signedByte);
  value->read("1");
  Nikon3MakerNote::printExternalFlashData2(os, *value, nullptr);
  std::string result = os.str();
  // typeId is signedByte, not unsignedByte, so should output parenthesized
  EXPECT_NE(result.find("("), std::string::npos);
  EXPECT_NE(result.find(")"), std::string::npos);
}

// Test return value is the same ostream reference
TEST_F(Nikon3MakerNoteTest_488, PrintExternalFlashData2_ReturnsOsReference_488) {
  std::ostringstream os;
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostream& result = Nikon3MakerNote::printExternalFlashData2(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}

// Test return value for error case is the same ostream reference
TEST_F(Nikon3MakerNoteTest_488, PrintExternalFlashData2_ErrorReturnsOsReference_488) {
  std::ostringstream os;
  auto value = Value::create(unsignedShort);
  value->read("1");
  std::ostream& result = Nikon3MakerNote::printExternalFlashData2(os, *value, nullptr);
  EXPECT_EQ(&result, &os);
}
