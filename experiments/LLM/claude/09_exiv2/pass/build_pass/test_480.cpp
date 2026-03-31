#include <gtest/gtest.h>
#include <sstream>
#include <string>

// Include necessary Exiv2 headers
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

// We need to access the Internal namespace
// Since the class is in Internal namespace, we recreate the declaration based on the provided code
namespace Exiv2 {
namespace Internal {

class Nikon3MakerNote {
 public:
  std::ostream& printFStops(std::ostream& os, const Value& value, const ExifData*);
};

}  // namespace Internal
}  // namespace Exiv2

// Re-include the implementation or link against it
// For the test, we assume the implementation from nikonmn_int.cpp is linked

class Nikon3MakerNoteTest_480 : public ::testing::Test {
 protected:
  Exiv2::Internal::Nikon3MakerNote makerNote_;
  std::ostringstream os_;
};

// Test: Normal operation with a single unsignedByte value
TEST_F(Nikon3MakerNoteTest_480, PrintFStops_NormalValue_480) {
  Exiv2::DataValue value(Exiv2::unsignedByte);
  // 48 / 12.0 = 4.0, so expect "F4.0"
  value.read(reinterpret_cast<const Exiv2::byte*>("\x30"), 1, Exiv2::littleEndian);
  makerNote_.printFStops(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "F4.0");
}

// Test: Value of 0 -> 0/12.0 = 0.0 -> "F0.0"
TEST_F(Nikon3MakerNoteTest_480, PrintFStops_ZeroValue_480) {
  Exiv2::DataValue value(Exiv2::unsignedByte);
  value.read(reinterpret_cast<const Exiv2::byte*>("\x00"), 1, Exiv2::littleEndian);
  makerNote_.printFStops(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "F0.0");
}

// Test: Value of 1 -> 1/12.0 ≈ 0.1
TEST_F(Nikon3MakerNoteTest_480, PrintFStops_ValueOne_480) {
  Exiv2::DataValue value(Exiv2::unsignedByte);
  value.read(reinterpret_cast<const Exiv2::byte*>("\x01"), 1, Exiv2::littleEndian);
  makerNote_.printFStops(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "F0.1");
}

// Test: Value of 255 (max unsigned byte) -> 255/12.0 = 21.25 -> "F21.2"
TEST_F(Nikon3MakerNoteTest_480, PrintFStops_MaxByteValue_480) {
  Exiv2::DataValue value(Exiv2::unsignedByte);
  value.read(reinterpret_cast<const Exiv2::byte*>("\xFF"), 1, Exiv2::littleEndian);
  makerNote_.printFStops(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "F21.2");
}

// Test: Value of 12 -> 12/12.0 = 1.0 -> "F1.0"
TEST_F(Nikon3MakerNoteTest_480, PrintFStops_ValueTwelve_480) {
  Exiv2::DataValue value(Exiv2::unsignedByte);
  value.read(reinterpret_cast<const Exiv2::byte*>("\x0C"), 1, Exiv2::littleEndian);
  makerNote_.printFStops(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "F1.0");
}

// Test: Wrong type (not unsignedByte) should produce fallback format "(value)"
TEST_F(Nikon3MakerNoteTest_480, PrintFStops_WrongType_ReturnsParenthesized_480) {
  Exiv2::DataValue value(Exiv2::unsignedShort);
  uint16_t val = 48;
  value.read(reinterpret_cast<const Exiv2::byte*>(&val), 2, Exiv2::littleEndian);
  makerNote_.printFStops(os_, value, nullptr);
  std::string result = os_.str();
  // Should be in parenthesized format since type is not unsignedByte
  EXPECT_TRUE(result.front() == '(');
  EXPECT_TRUE(result.back() == ')');
}

// Test: Count != 1 (multiple bytes) should produce fallback format
TEST_F(Nikon3MakerNoteTest_480, PrintFStops_MultipleValues_ReturnsParenthesized_480) {
  Exiv2::DataValue value(Exiv2::unsignedByte);
  const Exiv2::byte data[] = {48, 24};
  value.read(data, 2, Exiv2::littleEndian);
  makerNote_.printFStops(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_TRUE(result.front() == '(');
  EXPECT_TRUE(result.back() == ')');
}

// Test: Empty value (count == 0) should produce fallback format
TEST_F(Nikon3MakerNoteTest_480, PrintFStops_EmptyValue_ReturnsParenthesized_480) {
  Exiv2::DataValue value(Exiv2::unsignedByte);
  // Don't read any data, count should be 0
  makerNote_.printFStops(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_TRUE(result.front() == '(');
  EXPECT_TRUE(result.back() == ')');
}

// Test: Passing nullptr for ExifData should still work normally
TEST_F(Nikon3MakerNoteTest_480, PrintFStops_NullExifData_480) {
  Exiv2::DataValue value(Exiv2::unsignedByte);
  value.read(reinterpret_cast<const Exiv2::byte*>("\x18"), 1, Exiv2::littleEndian);
  // 24 / 12.0 = 2.0
  makerNote_.printFStops(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "F2.0");
}

// Test: Value 6 -> 6/12.0 = 0.5 -> "F0.5"
TEST_F(Nikon3MakerNoteTest_480, PrintFStops_HalfStop_480) {
  Exiv2::DataValue value(Exiv2::unsignedByte);
  value.read(reinterpret_cast<const Exiv2::byte*>("\x06"), 1, Exiv2::littleEndian);
  makerNote_.printFStops(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "F0.5");
}

// Test: Return value is the same ostream reference
TEST_F(Nikon3MakerNoteTest_480, PrintFStops_ReturnsOstream_480) {
  Exiv2::DataValue value(Exiv2::unsignedByte);
  value.read(reinterpret_cast<const Exiv2::byte*>("\x0C"), 1, Exiv2::littleEndian);
  std::ostream& result = makerNote_.printFStops(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

// Test: Wrong type also returns the ostream reference
TEST_F(Nikon3MakerNoteTest_480, PrintFStops_WrongType_ReturnsOstream_480) {
  Exiv2::DataValue value(Exiv2::unsignedShort);
  uint16_t val = 48;
  value.read(reinterpret_cast<const Exiv2::byte*>(&val), 2, Exiv2::littleEndian);
  std::ostream& result = makerNote_.printFStops(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

// Test: Value 96 -> 96/12.0 = 8.0 -> "F8.0"
TEST_F(Nikon3MakerNoteTest_480, PrintFStops_CommonFStop_F8_480) {
  Exiv2::DataValue value(Exiv2::unsignedByte);
  value.read(reinterpret_cast<const Exiv2::byte*>("\x60"), 1, Exiv2::littleEndian);
  makerNote_.printFStops(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "F8.0");
}

// Test: signedByte type should fail the type check
TEST_F(Nikon3MakerNoteTest_480, PrintFStops_SignedByte_ReturnsParenthesized_480) {
  Exiv2::DataValue value(Exiv2::signedByte);
  value.read(reinterpret_cast<const Exiv2::byte*>("\x30"), 1, Exiv2::littleEndian);
  makerNote_.printFStops(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_TRUE(result.front() == '(');
  EXPECT_TRUE(result.back() == ')');
}
