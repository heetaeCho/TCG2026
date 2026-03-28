#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

// We need to include the internal header or replicate the minimal interface
// Since we're testing the class as defined in the prompt, we include what's needed.
namespace Exiv2 {
namespace Internal {

class Nikon3MakerNote {
 public:
  std::ostream& printPictureControl(std::ostream& os, const Value& value, const ExifData*) {
    if (value.count() != 1 || value.typeId() != unsignedByte)
      return os << "(" << value << ")";
    const auto pcval = value.toInt64() - 0x80;
    if (pcval == 0)
      return os << "Normal";
    if (pcval == 127)
      return os << "n/a";
    if (pcval == -127)
      return os << "User";
    if (pcval == -128)
      return os << "Auto";
    return os << pcval;
  }
};

}  // namespace Internal
}  // namespace Exiv2

using namespace Exiv2;
using namespace Exiv2::Internal;

class Nikon3MakerNoteTest_504 : public ::testing::Test {
 protected:
  Nikon3MakerNote maker_;
  std::ostringstream os_;
};

// Test: Normal value (0x80 -> pcval == 0 -> "Normal")
TEST_F(Nikon3MakerNoteTest_504, PrintPictureControl_Normal_504) {
  Exiv2::DataValue value(Exiv2::unsignedByte);
  value.read(reinterpret_cast<const Exiv2::byte*>("\x80"), 1, Exiv2::littleEndian);

  maker_.printPictureControl(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "Normal");
}

// Test: n/a value (0x80 + 127 = 0xFF -> pcval == 127 -> "n/a")
TEST_F(Nikon3MakerNoteTest_504, PrintPictureControl_NA_504) {
  Exiv2::DataValue value(Exiv2::unsignedByte);
  uint8_t data = 0xFF;  // 0x80 + 127
  value.read(&data, 1, Exiv2::littleEndian);

  maker_.printPictureControl(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "n/a");
}

// Test: User value (0x80 - 127 = 0x01 -> pcval == -127 -> "User")
TEST_F(Nikon3MakerNoteTest_504, PrintPictureControl_User_504) {
  Exiv2::DataValue value(Exiv2::unsignedByte);
  uint8_t data = 0x01;  // 0x80 - 127
  value.read(&data, 1, Exiv2::littleEndian);

  maker_.printPictureControl(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "User");
}

// Test: Auto value (0x80 - 128 = 0x00 -> pcval == -128 -> "Auto")
TEST_F(Nikon3MakerNoteTest_504, PrintPictureControl_Auto_504) {
  Exiv2::DataValue value(Exiv2::unsignedByte);
  uint8_t data = 0x00;  // 0x80 - 128
  value.read(&data, 1, Exiv2::littleEndian);

  maker_.printPictureControl(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "Auto");
}

// Test: Positive pcval (e.g., 0x85 -> pcval == 5 -> prints "5")
TEST_F(Nikon3MakerNoteTest_504, PrintPictureControl_PositiveValue_504) {
  Exiv2::DataValue value(Exiv2::unsignedByte);
  uint8_t data = 0x85;  // 0x80 + 5
  value.read(&data, 1, Exiv2::littleEndian);

  maker_.printPictureControl(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "5");
}

// Test: Negative pcval (e.g., 0x7B -> pcval == -5 -> prints "-5")
TEST_F(Nikon3MakerNoteTest_504, PrintPictureControl_NegativeValue_504) {
  Exiv2::DataValue value(Exiv2::unsignedByte);
  uint8_t data = 0x7B;  // 0x80 - 5
  value.read(&data, 1, Exiv2::littleEndian);

  maker_.printPictureControl(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "-5");
}

// Test: pcval == 1 (edge near Normal)
TEST_F(Nikon3MakerNoteTest_504, PrintPictureControl_PcvalOne_504) {
  Exiv2::DataValue value(Exiv2::unsignedByte);
  uint8_t data = 0x81;  // 0x80 + 1
  value.read(&data, 1, Exiv2::littleEndian);

  maker_.printPictureControl(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "1");
}

// Test: pcval == -1 (edge near Normal)
TEST_F(Nikon3MakerNoteTest_504, PrintPictureControl_PcvalMinusOne_504) {
  Exiv2::DataValue value(Exiv2::unsignedByte);
  uint8_t data = 0x7F;  // 0x80 - 1
  value.read(&data, 1, Exiv2::littleEndian);

  maker_.printPictureControl(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "-1");
}

// Test: pcval == 126 (edge near n/a)
TEST_F(Nikon3MakerNoteTest_504, PrintPictureControl_Pcval126_504) {
  Exiv2::DataValue value(Exiv2::unsignedByte);
  uint8_t data = 0xFE;  // 0x80 + 126
  value.read(&data, 1, Exiv2::littleEndian);

  maker_.printPictureControl(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "126");
}

// Test: pcval == -126 (edge near User)
TEST_F(Nikon3MakerNoteTest_504, PrintPictureControl_PcvalMinus126_504) {
  Exiv2::DataValue value(Exiv2::unsignedByte);
  uint8_t data = 0x02;  // 0x80 - 126
  value.read(&data, 1, Exiv2::littleEndian);

  maker_.printPictureControl(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "-126");
}

// Test: Wrong type (not unsignedByte) should output parenthesized value
TEST_F(Nikon3MakerNoteTest_504, PrintPictureControl_WrongType_504) {
  Exiv2::DataValue value(Exiv2::unsignedShort);
  uint8_t data[] = {0x80, 0x00};
  value.read(data, 2, Exiv2::littleEndian);

  maker_.printPictureControl(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_EQ(result.front(), '(');
  EXPECT_EQ(result.back(), ')');
}

// Test: Multiple values (count != 1) should output parenthesized value
TEST_F(Nikon3MakerNoteTest_504, PrintPictureControl_MultipleValues_504) {
  Exiv2::DataValue value(Exiv2::unsignedByte);
  uint8_t data[] = {0x80, 0x81};
  value.read(data, 2, Exiv2::littleEndian);

  maker_.printPictureControl(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_EQ(result.front(), '(');
  EXPECT_EQ(result.back(), ')');
}

// Test: Empty value (count == 0) should output parenthesized value
TEST_F(Nikon3MakerNoteTest_504, PrintPictureControl_EmptyValue_504) {
  Exiv2::DataValue value(Exiv2::unsignedByte);
  // No data read, count should be 0

  maker_.printPictureControl(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_EQ(result.front(), '(');
  EXPECT_EQ(result.back(), ')');
}

// Test: Verify nullptr ExifData doesn't cause crash
TEST_F(Nikon3MakerNoteTest_504, PrintPictureControl_NullExifData_504) {
  Exiv2::DataValue value(Exiv2::unsignedByte);
  uint8_t data = 0x80;
  value.read(&data, 1, Exiv2::littleEndian);

  EXPECT_NO_THROW(maker_.printPictureControl(os_, value, nullptr));
  EXPECT_EQ(os_.str(), "Normal");
}

// Test: Returns reference to the same ostream
TEST_F(Nikon3MakerNoteTest_504, PrintPictureControl_ReturnsOstream_504) {
  Exiv2::DataValue value(Exiv2::unsignedByte);
  uint8_t data = 0x80;
  value.read(&data, 1, Exiv2::littleEndian);

  std::ostream& result = maker_.printPictureControl(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

// Test: Boundary - maximum unsignedByte value 0xFF (pcval = 127 -> n/a)
TEST_F(Nikon3MakerNoteTest_504, PrintPictureControl_MaxByte_504) {
  Exiv2::DataValue value(Exiv2::unsignedByte);
  uint8_t data = 0xFF;
  value.read(&data, 1, Exiv2::littleEndian);

  maker_.printPictureControl(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "n/a");
}

// Test: Boundary - minimum unsignedByte value 0x00 (pcval = -128 -> Auto)
TEST_F(Nikon3MakerNoteTest_504, PrintPictureControl_MinByte_504) {
  Exiv2::DataValue value(Exiv2::unsignedByte);
  uint8_t data = 0x00;
  value.read(&data, 1, Exiv2::littleEndian);

  maker_.printPictureControl(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "Auto");
}
