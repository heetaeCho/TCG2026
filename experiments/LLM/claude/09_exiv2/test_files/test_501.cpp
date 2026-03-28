#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>

// Include the internal header for Nikon3MakerNote
#include "nikonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class Nikon3MakerNoteTest_501 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// =============================================================================
// Tests for printExternalFlashData4
// =============================================================================

TEST_F(Nikon3MakerNoteTest_501, PrintExternalFlashData4_SingleUnsignedByte_Value0_501) {
  // Normal case: single unsignedByte with value 0 -> "Illumination Pat.: Standard"
  auto value = Value::create(unsignedByte);
  value->read("0");
  Nikon3MakerNote::printExternalFlashData4(os, *value, nullptr);
  EXPECT_EQ(os.str(), "Illumination Pat.: Standard");
}

TEST_F(Nikon3MakerNoteTest_501, PrintExternalFlashData4_SingleUnsignedByte_Value1_501) {
  // Normal case: single unsignedByte with value 1 -> "Illumination Pat.: Center-weighted"
  auto value = Value::create(unsignedByte);
  value->read("1");
  Nikon3MakerNote::printExternalFlashData4(os, *value, nullptr);
  EXPECT_EQ(os.str(), "Illumination Pat.: Center-weighted");
}

TEST_F(Nikon3MakerNoteTest_501, PrintExternalFlashData4_SingleUnsignedByte_Value2_501) {
  // Normal case: single unsignedByte with value 2 -> "Illumination Pat.: Even"
  auto value = Value::create(unsignedByte);
  value->read("2");
  Nikon3MakerNote::printExternalFlashData4(os, *value, nullptr);
  EXPECT_EQ(os.str(), "Illumination Pat.: Even");
}

TEST_F(Nikon3MakerNoteTest_501, PrintExternalFlashData4_SingleUnsignedByte_UnknownValue_501) {
  // Boundary/error case: single unsignedByte with value outside known tags (e.g., 3)
  auto value = Value::create(unsignedByte);
  value->read("3");
  Nikon3MakerNote::printExternalFlashData4(os, *value, nullptr);
  // Should output something for unknown value - likely "(3)" or a default string
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest_501, PrintExternalFlashData4_WrongType_UnsignedShort_501) {
  // Error case: wrong type (unsignedShort instead of unsignedByte)
  // Should output "(value)" format
  auto value = Value::create(unsignedShort);
  value->read("1");
  Nikon3MakerNote::printExternalFlashData4(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_TRUE(result.find("(") != std::string::npos);
  EXPECT_TRUE(result.find(")") != std::string::npos);
}

TEST_F(Nikon3MakerNoteTest_501, PrintExternalFlashData4_WrongType_AsciiString_501) {
  // Error case: wrong type (asciiString)
  auto value = Value::create(asciiString);
  value->read("test");
  Nikon3MakerNote::printExternalFlashData4(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_TRUE(result.find("(") != std::string::npos);
}

TEST_F(Nikon3MakerNoteTest_501, PrintExternalFlashData4_MultipleValues_501) {
  // Error case: count != 1 (multiple unsignedByte values)
  auto value = Value::create(unsignedByte);
  value->read("0 1");
  Nikon3MakerNote::printExternalFlashData4(os, *value, nullptr);
  std::string result = os.str();
  // count != 1 should trigger the fallback "(value)" output
  EXPECT_TRUE(result.find("(") != std::string::npos);
  EXPECT_TRUE(result.find(")") != std::string::npos);
}

TEST_F(Nikon3MakerNoteTest_501, PrintExternalFlashData4_ReturnsOstream_501) {
  // Verify that the function returns a reference to the same ostream
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostream& returned = Nikon3MakerNote::printExternalFlashData4(os, *value, nullptr);
  EXPECT_EQ(&returned, &os);
}

TEST_F(Nikon3MakerNoteTest_501, PrintExternalFlashData4_WrongTypeReturnsOstream_501) {
  // Verify that the error path also returns a reference to the same ostream
  auto value = Value::create(unsignedShort);
  value->read("1");
  std::ostream& returned = Nikon3MakerNote::printExternalFlashData4(os, *value, nullptr);
  EXPECT_EQ(&returned, &os);
}

TEST_F(Nikon3MakerNoteTest_501, PrintExternalFlashData4_WithExifData_501) {
  // Normal case with non-null ExifData pointer
  ExifData exifData;
  auto value = Value::create(unsignedByte);
  value->read("0");
  Nikon3MakerNote::printExternalFlashData4(os, *value, &exifData);
  EXPECT_EQ(os.str(), "Illumination Pat.: Standard");
}

TEST_F(Nikon3MakerNoteTest_501, PrintExternalFlashData4_UnsignedLongType_501) {
  // Error case: unsignedLong type
  auto value = Value::create(unsignedLong);
  value->read("1");
  Nikon3MakerNote::printExternalFlashData4(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_TRUE(result.find("(") != std::string::npos);
  EXPECT_TRUE(result.find(")") != std::string::npos);
}

TEST_F(Nikon3MakerNoteTest_501, PrintExternalFlashData4_SignedByteType_501) {
  // Error case: signedByte type (not unsignedByte)
  auto value = Value::create(signedByte);
  value->read("1");
  Nikon3MakerNote::printExternalFlashData4(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_TRUE(result.find("(") != std::string::npos);
  EXPECT_TRUE(result.find(")") != std::string::npos);
}

TEST_F(Nikon3MakerNoteTest_501, PrintExternalFlashData4_LargeUnknownValue_501) {
  // Boundary case: large value (255, max for unsignedByte)
  auto value = Value::create(unsignedByte);
  value->read("255");
  Nikon3MakerNote::printExternalFlashData4(os, *value, nullptr);
  std::string result = os.str();
  // Value 255 is not in the known tag details, so it should produce some output
  EXPECT_FALSE(result.empty());
}
