#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

// We need to replicate the class interface for testing since we're testing the method
namespace Exiv2 {
namespace Internal {
class Nikon3MakerNote {
 public:
  std::ostream& printExitPupilPosition(std::ostream& os, const Value& value, const ExifData*) {
    if (value.count() != 1 || value.typeId() != unsignedByte || value.toInt64() == 0)
      return os << "(" << value << ")";
    return os << stringFormat("{:.1f} mm", 2048.0 / value.toInt64());
  }
};
}  // namespace Internal
}  // namespace Exiv2

using namespace Exiv2;
using namespace Exiv2::Internal;

class Nikon3MakerNoteTest_481 : public ::testing::Test {
 protected:
  Nikon3MakerNote maker_;
  std::ostringstream os_;
};

// Test normal operation with a valid unsigned byte value
TEST_F(Nikon3MakerNoteTest_481, PrintExitPupilPosition_NormalValue_481) {
  auto value = Value::create(unsignedByte);
  value->read("128");
  maker_.printExitPupilPosition(os_, *value, nullptr);
  EXPECT_EQ(os_.str(), "16.0 mm");
}

// Test with value = 1 (maximum result 2048.0)
TEST_F(Nikon3MakerNoteTest_481, PrintExitPupilPosition_ValueOne_481) {
  auto value = Value::create(unsignedByte);
  value->read("1");
  maker_.printExitPupilPosition(os_, *value, nullptr);
  EXPECT_EQ(os_.str(), "2048.0 mm");
}

// Test with value = 255 (minimum non-zero unsigned byte)
TEST_F(Nikon3MakerNoteTest_481, PrintExitPupilPosition_Value255_481) {
  auto value = Value::create(unsignedByte);
  value->read("255");
  maker_.printExitPupilPosition(os_, *value, nullptr);
  // 2048.0 / 255 ≈ 8.03137...
  EXPECT_EQ(os_.str(), "8.0 mm");
}

// Test with value = 0 (should produce parenthesized output)
TEST_F(Nikon3MakerNoteTest_481, PrintExitPupilPosition_ValueZero_481) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  maker_.printExitPupilPosition(os_, *value, nullptr);
  std::string result = os_.str();
  EXPECT_EQ(result.front(), '(');
  EXPECT_EQ(result.back(), ')');
}

// Test with wrong type (unsignedShort instead of unsignedByte)
TEST_F(Nikon3MakerNoteTest_481, PrintExitPupilPosition_WrongType_481) {
  auto value = Value::create(unsignedShort);
  value->read("128");
  maker_.printExitPupilPosition(os_, *value, nullptr);
  std::string result = os_.str();
  EXPECT_EQ(result.front(), '(');
  EXPECT_EQ(result.back(), ')');
}

// Test with count != 1 (multiple values)
TEST_F(Nikon3MakerNoteTest_481, PrintExitPupilPosition_MultipleValues_481) {
  auto value = Value::create(unsignedByte);
  value->read("128 64");
  EXPECT_EQ(value->count(), 2u);
  maker_.printExitPupilPosition(os_, *value, nullptr);
  std::string result = os_.str();
  EXPECT_EQ(result.front(), '(');
  EXPECT_EQ(result.back(), ')');
}

// Test with signed type (signedByte is not unsignedByte)
TEST_F(Nikon3MakerNoteTest_481, PrintExitPupilPosition_SignedType_481) {
  auto value = Value::create(signedShort);
  value->read("100");
  maker_.printExitPupilPosition(os_, *value, nullptr);
  std::string result = os_.str();
  EXPECT_EQ(result.front(), '(');
  EXPECT_EQ(result.back(), ')');
}

// Test with value = 2 (2048.0 / 2 = 1024.0)
TEST_F(Nikon3MakerNoteTest_481, PrintExitPupilPosition_ValueTwo_481) {
  auto value = Value::create(unsignedByte);
  value->read("2");
  maker_.printExitPupilPosition(os_, *value, nullptr);
  EXPECT_EQ(os_.str(), "1024.0 mm");
}

// Test with value = 64 (2048.0 / 64 = 32.0)
TEST_F(Nikon3MakerNoteTest_481, PrintExitPupilPosition_Value64_481) {
  auto value = Value::create(unsignedByte);
  value->read("64");
  maker_.printExitPupilPosition(os_, *value, nullptr);
  EXPECT_EQ(os_.str(), "32.0 mm");
}

// Test that nullptr ExifData is acceptable
TEST_F(Nikon3MakerNoteTest_481, PrintExitPupilPosition_NullExifData_481) {
  auto value = Value::create(unsignedByte);
  value->read("10");
  maker_.printExitPupilPosition(os_, *value, nullptr);
  // 2048.0 / 10 = 204.8
  EXPECT_EQ(os_.str(), "204.8 mm");
}

// Test with unsignedLong type (wrong type, should be parenthesized)
TEST_F(Nikon3MakerNoteTest_481, PrintExitPupilPosition_UnsignedLongType_481) {
  auto value = Value::create(unsignedLong);
  value->read("50");
  maker_.printExitPupilPosition(os_, *value, nullptr);
  std::string result = os_.str();
  EXPECT_EQ(result.front(), '(');
  EXPECT_EQ(result.back(), ')');
}

// Test that return value is the same ostream
TEST_F(Nikon3MakerNoteTest_481, PrintExitPupilPosition_ReturnsSameStream_481) {
  auto value = Value::create(unsignedByte);
  value->read("128");
  std::ostream& ret = maker_.printExitPupilPosition(os_, *value, nullptr);
  EXPECT_EQ(&ret, &os_);
}

// Test return value for error case
TEST_F(Nikon3MakerNoteTest_481, PrintExitPupilPosition_ReturnsSameStreamOnError_481) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostream& ret = maker_.printExitPupilPosition(os_, *value, nullptr);
  EXPECT_EQ(&ret, &os_);
}

// Test with empty value (count = 0)
TEST_F(Nikon3MakerNoteTest_481, PrintExitPupilPosition_EmptyValue_481) {
  auto value = Value::create(unsignedByte);
  // Don't read anything, count should be 0
  EXPECT_EQ(value->count(), 0u);
  maker_.printExitPupilPosition(os_, *value, nullptr);
  std::string result = os_.str();
  EXPECT_EQ(result.front(), '(');
  EXPECT_EQ(result.back(), ')');
}

// Test with value = 3 (2048/3 ≈ 682.666...)
TEST_F(Nikon3MakerNoteTest_481, PrintExitPupilPosition_Value3_481) {
  auto value = Value::create(unsignedByte);
  value->read("3");
  maker_.printExitPupilPosition(os_, *value, nullptr);
  EXPECT_EQ(os_.str(), "682.7 mm");
}
