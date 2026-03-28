#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>

// Include the internal header for Nikon3MakerNote
#include "nikonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class Nikon3MakerNoteTest_499 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// Test printExternalFlashData3 with a single unsignedByte value where bit 2 is 0
// Expected: maps to "Exposure Comp.: Entire frame" (value & 0x04 == 0)
TEST_F(Nikon3MakerNoteTest_499, PrintExternalFlashData3_SingleByte_Bit2Clear_499) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  Nikon3MakerNote::printExternalFlashData3(os, *value, nullptr);
  std::string result = os.str();
  // value & 0x04 == 0, should map to "Exposure Comp.: Entire frame"
  EXPECT_NE(result.find("Entire frame"), std::string::npos) << "Got: " << result;
}

// Test printExternalFlashData3 with a single unsignedByte value where bit 2 is set
// Expected: maps to "Exposure Comp.: Background Only" (value & 0x04 == 4)
TEST_F(Nikon3MakerNoteTest_499, PrintExternalFlashData3_SingleByte_Bit2Set_499) {
  auto value = Value::create(unsignedByte);
  value->read("4");
  Nikon3MakerNote::printExternalFlashData3(os, *value, nullptr);
  std::string result = os.str();
  // value & 0x04 == 4, should map to "Exposure Comp.: Background Only"
  EXPECT_NE(result.find("Background Only"), std::string::npos) << "Got: " << result;
}

// Test printExternalFlashData3 with value 5 (bit 2 set, other bits set too)
// Expected: value & 0x04 == 4, maps to "Background Only"
TEST_F(Nikon3MakerNoteTest_499, PrintExternalFlashData3_Value5_Bit2Set_499) {
  auto value = Value::create(unsignedByte);
  value->read("5");
  Nikon3MakerNote::printExternalFlashData3(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_NE(result.find("Background Only"), std::string::npos) << "Got: " << result;
}

// Test printExternalFlashData3 with value 3 (bit 2 clear)
// Expected: value & 0x04 == 0, maps to "Entire frame"
TEST_F(Nikon3MakerNoteTest_499, PrintExternalFlashData3_Value3_Bit2Clear_499) {
  auto value = Value::create(unsignedByte);
  value->read("3");
  Nikon3MakerNote::printExternalFlashData3(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_NE(result.find("Entire frame"), std::string::npos) << "Got: " << result;
}

// Test printExternalFlashData3 with value 255 (all bits set, bit 2 set)
// Expected: value & 0x04 == 4, maps to "Background Only"
TEST_F(Nikon3MakerNoteTest_499, PrintExternalFlashData3_Value255_AllBitsSet_499) {
  auto value = Value::create(unsignedByte);
  value->read("255");
  Nikon3MakerNote::printExternalFlashData3(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_NE(result.find("Background Only"), std::string::npos) << "Got: " << result;
}

// Test printExternalFlashData3 with wrong type (unsignedShort instead of unsignedByte)
// Expected: outputs "(" value ")" format since typeId != unsignedByte
TEST_F(Nikon3MakerNoteTest_499, PrintExternalFlashData3_WrongType_UnsignedShort_499) {
  auto value = Value::create(unsignedShort);
  value->read("0");
  Nikon3MakerNote::printExternalFlashData3(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_EQ(result.front(), '(') << "Got: " << result;
  EXPECT_EQ(result.back(), ')') << "Got: " << result;
}

// Test printExternalFlashData3 with multiple values (count != 1)
// Expected: outputs "(" value ")" format since count != 1
TEST_F(Nikon3MakerNoteTest_499, PrintExternalFlashData3_MultipleValues_499) {
  auto value = Value::create(unsignedByte);
  value->read("0 1");
  Nikon3MakerNote::printExternalFlashData3(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_EQ(result.front(), '(') << "Got: " << result;
  EXPECT_EQ(result.back(), ')') << "Got: " << result;
}

// Test printExternalFlashData3 with wrong type (asciiString)
// Expected: outputs "(" value ")" format
TEST_F(Nikon3MakerNoteTest_499, PrintExternalFlashData3_WrongType_AsciiString_499) {
  auto value = Value::create(asciiString);
  value->read("test");
  Nikon3MakerNote::printExternalFlashData3(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_EQ(result.front(), '(') << "Got: " << result;
  EXPECT_EQ(result.back(), ')') << "Got: " << result;
}

// Test printExternalFlashData3 with value 0 and non-null ExifData pointer
TEST_F(Nikon3MakerNoteTest_499, PrintExternalFlashData3_WithExifData_499) {
  ExifData exifData;
  auto value = Value::create(unsignedByte);
  value->read("0");
  Nikon3MakerNote::printExternalFlashData3(os, *value, &exifData);
  std::string result = os.str();
  EXPECT_NE(result.find("Entire frame"), std::string::npos) << "Got: " << result;
}

// Test printExternalFlashData3 with value 4 and non-null ExifData pointer
TEST_F(Nikon3MakerNoteTest_499, PrintExternalFlashData3_WithExifData_BackgroundOnly_499) {
  ExifData exifData;
  auto value = Value::create(unsignedByte);
  value->read("4");
  Nikon3MakerNote::printExternalFlashData3(os, *value, &exifData);
  std::string result = os.str();
  EXPECT_NE(result.find("Background Only"), std::string::npos) << "Got: " << result;
}

// Test that the return value is the same ostream reference
TEST_F(Nikon3MakerNoteTest_499, PrintExternalFlashData3_ReturnsSameOstream_499) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostream& returnedOs = Nikon3MakerNote::printExternalFlashData3(os, *value, nullptr);
  EXPECT_EQ(&returnedOs, &os);
}

// Test that the return value is the same ostream reference for error case
TEST_F(Nikon3MakerNoteTest_499, PrintExternalFlashData3_ReturnsSameOstream_ErrorCase_499) {
  auto value = Value::create(unsignedShort);
  value->read("0");
  std::ostream& returnedOs = Nikon3MakerNote::printExternalFlashData3(os, *value, nullptr);
  EXPECT_EQ(&returnedOs, &os);
}

// Test printExternalFlashData3 with unsignedLong type (wrong type)
TEST_F(Nikon3MakerNoteTest_499, PrintExternalFlashData3_WrongType_UnsignedLong_499) {
  auto value = Value::create(unsignedLong);
  value->read("0");
  Nikon3MakerNote::printExternalFlashData3(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_EQ(result.front(), '(') << "Got: " << result;
  EXPECT_EQ(result.back(), ')') << "Got: " << result;
}

// Test with value 251 (0xFB) - bit 2 is clear
// 0xFB = 11111011, bit 2 (value 4) is 0
TEST_F(Nikon3MakerNoteTest_499, PrintExternalFlashData3_Value251_Bit2Clear_499) {
  auto value = Value::create(unsignedByte);
  value->read("251");
  Nikon3MakerNote::printExternalFlashData3(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_NE(result.find("Entire frame"), std::string::npos) << "Got: " << result;
}
