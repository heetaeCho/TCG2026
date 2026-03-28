#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

// Include the implementation
#include "pentaxmn_int.cpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class PentaxMakerNoteTest_191 : public ::testing::Test {
 protected:
  PentaxMakerNote maker_;
  std::ostringstream os_;
};

// Test normal date output with typical values
TEST_F(PentaxMakerNoteTest_191, PrintDate_NormalDate_191) {
  // Year is computed as (value[0] << 8) + value[1]
  // For year 2023: high byte = 7 (0x07), low byte = 231 (0xE7) -> 0x07E7 = 2023
  // Month = 6, Day = 15
  DataBuf buf(4);
  buf.write_uint8(0, 7);    // high byte of year
  buf.write_uint8(1, 231);  // low byte of year (7*256 + 231 = 2023)
  buf.write_uint8(2, 6);    // month
  buf.write_uint8(3, 15);   // day

  Value::UniquePtr value = Value::create(unsignedByte);
  value->read(buf.c_data(), buf.size(), byteOrder_);

  // We need to use a simpler approach - use DataValue
  DataValue dv(unsignedByte);
  std::vector<byte> data = {7, 231, 6, 15};
  dv.read(data.data(), data.size(), invalidByteOrder);

  maker_.printDate(os_, dv, nullptr);
  EXPECT_EQ(os_.str(), "2023:06:15");
}

// Test date with year 2000: 0x07D0 = 2000, high=7, low=208
TEST_F(PentaxMakerNoteTest_191, PrintDate_Year2000_191) {
  DataValue dv(unsignedByte);
  std::vector<byte> data = {7, 208, 1, 1};  // 7*256+208=2000, Jan 1
  dv.read(data.data(), data.size(), invalidByteOrder);

  maker_.printDate(os_, dv, nullptr);
  EXPECT_EQ(os_.str(), "2000:01:01");
}

// Test date with single digit month and day (padding check)
TEST_F(PentaxMakerNoteTest_191, PrintDate_SingleDigitMonthDay_191) {
  DataValue dv(unsignedByte);
  std::vector<byte> data = {7, 228, 3, 5};  // 7*256+228=2020, March 5
  dv.read(data.data(), data.size(), invalidByteOrder);

  maker_.printDate(os_, dv, nullptr);
  EXPECT_EQ(os_.str(), "2020:03:05");
}

// Test date with month=12, day=31 (end of year)
TEST_F(PentaxMakerNoteTest_191, PrintDate_EndOfYear_191) {
  DataValue dv(unsignedByte);
  std::vector<byte> data = {7, 227, 12, 31};  // 7*256+227=2019, Dec 31
  dv.read(data.data(), data.size(), invalidByteOrder);

  maker_.printDate(os_, dv, nullptr);
  EXPECT_EQ(os_.str(), "2019:12:31");
}

// Test with zero values
TEST_F(PentaxMakerNoteTest_191, PrintDate_AllZeros_191) {
  DataValue dv(unsignedByte);
  std::vector<byte> data = {0, 0, 0, 0};
  dv.read(data.data(), data.size(), invalidByteOrder);

  maker_.printDate(os_, dv, nullptr);
  EXPECT_EQ(os_.str(), "0:00:00");
}

// Test with max byte values (255 for all)
TEST_F(PentaxMakerNoteTest_191, PrintDate_MaxByteValues_191) {
  DataValue dv(unsignedByte);
  std::vector<byte> data = {255, 255, 255, 255};  // year = 255*256+255 = 65535
  dv.read(data.data(), data.size(), invalidByteOrder);

  maker_.printDate(os_, dv, nullptr);
  // Year = 65535, month = 255, day = 255
  EXPECT_EQ(os_.str(), "65535:255:255");
}

// Test that the return value is the same ostream reference
TEST_F(PentaxMakerNoteTest_191, PrintDate_ReturnsOstream_191) {
  DataValue dv(unsignedByte);
  std::vector<byte> data = {7, 228, 6, 15};
  dv.read(data.data(), data.size(), invalidByteOrder);

  std::ostream& result = maker_.printDate(os_, dv, nullptr);
  EXPECT_EQ(&result, &os_);
}

// Test year 1999: 0x07CF = 1999, high=7, low=207
TEST_F(PentaxMakerNoteTest_191, PrintDate_Year1999_191) {
  DataValue dv(unsignedByte);
  std::vector<byte> data = {7, 207, 11, 28};  // 1999, Nov 28
  dv.read(data.data(), data.size(), invalidByteOrder);

  maker_.printDate(os_, dv, nullptr);
  EXPECT_EQ(os_.str(), "1999:11:28");
}

// Test low year value (e.g., year = 256, high=1, low=0)
TEST_F(PentaxMakerNoteTest_191, PrintDate_LowYear_191) {
  DataValue dv(unsignedByte);
  std::vector<byte> data = {1, 0, 1, 1};  // year = 256
  dv.read(data.data(), data.size(), invalidByteOrder);

  maker_.printDate(os_, dv, nullptr);
  EXPECT_EQ(os_.str(), "256:01:01");
}

// Test with month=10 to verify no extra padding for two-digit month
TEST_F(PentaxMakerNoteTest_191, PrintDate_TwoDigitMonth_191) {
  DataValue dv(unsignedByte);
  std::vector<byte> data = {7, 232, 10, 20};  // 7*256+232=2024, Oct 20
  dv.read(data.data(), data.size(), invalidByteOrder);

  maker_.printDate(os_, dv, nullptr);
  EXPECT_EQ(os_.str(), "2024:10:20");
}
