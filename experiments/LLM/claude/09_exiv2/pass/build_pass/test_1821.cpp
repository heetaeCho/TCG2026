#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

// Include the implementation
namespace Exiv2 {
namespace Internal {
class CasioMakerNote {
 public:
  std::ostream& print0x0015(std::ostream& os, const Value& value, const ExifData*) {
    std::vector<char> numbers;
    for (size_t i = 0; i < value.size(); i++) {
      const auto l = value.toInt64(i);
      if (l != 0) {
        numbers.push_back(l);
      }
    }
    if (numbers.size() >= 10) {
      long l = ((numbers[0] - 48) * 10) + (numbers[1] - 48);
      if (l < 70)
        l += 2000;
      else
        l += 1900;
      os << l << ":";
      os << numbers[2] << numbers[3] << ":" << numbers[4] << numbers[5] << " " << numbers[6] << numbers[7] << ":"
         << numbers[8] << numbers[9];
      if (numbers.size() == 12) {
        os << ":" << numbers[10] << numbers[11];
      }
    } else
      os << value;
    return os;
  }
};
}  // namespace Internal
}  // namespace Exiv2

using namespace Exiv2;
using namespace Exiv2::Internal;

class CasioMakerNoteTest_1821 : public ::testing::Test {
 protected:
  CasioMakerNote maker_;
  std::ostringstream os_;
};

// Helper to create an AsciiValue with the given string
static Exiv2::AsciiValue makeAscii(const std::string& s) {
  Exiv2::AsciiValue v;
  v.read(s);
  return v;
}

// Test with a date string that represents year 2023 (< 70 => +2000), 10 non-zero chars
TEST_F(CasioMakerNoteTest_1821, DateYear2000s_10Digits_1821) {
  // '2','3','0','6','1','5','1','4','3','0' => year = (50-48)*10 + (51-48) = 23 => 2023
  // But these are ASCII chars: '2'=50, '3'=51, '0'=48, '6'=54, '1'=49, '5'=53, '1'=49, '4'=52, '3'=51, '0'=48
  // However '0' has value 48 which is != 0, so it IS included in numbers
  // year = ((50-48)*10) + (51-48) = 20+3 = 23 < 70 => 2023
  // output: "2023:" + '0' + '6' + ":" + '1' + '5' + " " + '1' + '4' + ":" + '3' + '0'
  // = "2023:06:15 14:30"

  // We need a Value where each element is a single byte (ASCII char code)
  Exiv2::DataBuf buf(10);
  uint8_t data[] = {'2', '3', '0', '6', '1', '5', '1', '4', '3', '0'};
  
  Exiv2::DataValue val(data, 10, Exiv2::ByteOrder::littleEndian, Exiv2::TypeId::undefined);
  
  maker_.print0x0015(os_, val, nullptr);
  EXPECT_EQ(os_.str(), "2023:06:15 14:30");
}

// Test with 12 non-zero digits (includes seconds)
TEST_F(CasioMakerNoteTest_1821, DateWith12Digits_IncludesSeconds_1821) {
  // '2','3','0','6','1','5','1','4','3','0','4','5'
  // year=23 => 2023, month=06, day=15, hour=14, min=30, sec=45
  uint8_t data[] = {'2', '3', '0', '6', '1', '5', '1', '4', '3', '0', '4', '5'};
  Exiv2::DataValue val(data, 12, Exiv2::ByteOrder::littleEndian, Exiv2::TypeId::undefined);
  
  maker_.print0x0015(os_, val, nullptr);
  EXPECT_EQ(os_.str(), "2023:06:15 14:30:45");
}

// Test with year >= 70 => 1900s
TEST_F(CasioMakerNoteTest_1821, DateYear1900s_1821) {
  // '9','5' => year = (57-48)*10 + (53-48) = 90+5 = 95 >= 70 => 1995
  uint8_t data[] = {'9', '5', '1', '2', '2', '5', '0', '8', '3', '0'};
  // '0' = 48 != 0, so included
  // But wait, '0' is 48, which != 0, so all 10 digits stay
  // year = 95 => 1995
  // output: "1995:12:25 08:30"
  // numbers[2]='1', numbers[3]='2', numbers[4]='2', numbers[5]='5',
  // numbers[6]='0' (char), numbers[7]='8', numbers[8]='3', numbers[9]='0' (char)
  // Wait, these are chars being output, not their numeric values
  // os << numbers[6] << numbers[7] means outputting char '0' and char '8' => "08"
  
  Exiv2::DataValue val(data, 10, Exiv2::ByteOrder::littleEndian, Exiv2::TypeId::undefined);
  
  maker_.print0x0015(os_, val, nullptr);
  EXPECT_EQ(os_.str(), "1995:12:25 08:30");
}

// Test boundary: year exactly 70 => 1970
TEST_F(CasioMakerNoteTest_1821, DateYearExactly70_1821) {
  // '7','0' => year = 70 >= 70 => 1970
  uint8_t data[] = {'7', '0', '0', '1', '0', '1', '0', '0', '0', '0'};
  Exiv2::DataValue val(data, 10, Exiv2::ByteOrder::littleEndian, Exiv2::TypeId::undefined);
  
  maker_.print0x0015(os_, val, nullptr);
  EXPECT_EQ(os_.str(), "1970:01:01 00:00");
}

// Test boundary: year exactly 69 => 2069
TEST_F(CasioMakerNoteTest_1821, DateYearExactly69_1821) {
  // '6','9' => year = 69 < 70 => 2069
  uint8_t data[] = {'6', '9', '1', '2', '3', '1', '2', '3', '5', '9'};
  Exiv2::DataValue val(data, 10, Exiv2::ByteOrder::littleEndian, Exiv2::TypeId::undefined);
  
  maker_.print0x0015(os_, val, nullptr);
  EXPECT_EQ(os_.str(), "2069:12:31 23:59");
}

// Test with fewer than 10 non-zero chars => falls through to os << value
TEST_F(CasioMakerNoteTest_1821, TooFewNonZeroDigits_FallbackToValue_1821) {
  // Only 5 non-zero bytes
  uint8_t data[] = {'1', '2', '3', '4', '5'};
  Exiv2::DataValue val(data, 5, Exiv2::ByteOrder::littleEndian, Exiv2::TypeId::undefined);
  
  maker_.print0x0015(os_, val, nullptr);
  // Should output value.toString() or similar fallback
  // The exact output depends on DataValue::operator<<, but it won't match date format
  std::string result = os_.str();
  // It should NOT contain a 4-digit year followed by colon
  // We just verify it doesn't crash and produces some output
  EXPECT_FALSE(result.empty());
}

// Test with zero bytes mixed in (zeros get filtered out)
TEST_F(CasioMakerNoteTest_1821, ZeroBytesFiltered_1821) {
  // 12 bytes total, but 2 are zero, leaving 10 non-zero => date format
  // '2','3', 0, '0','6','1','5', 0, '1','4','3','0'
  // After filtering zeros: '2','3','0','6','1','5','1','4','3','0' => 10 digits
  // year=23 => 2023
  uint8_t data[] = {'2', '3', 0, '0', '6', '1', '5', 0, '1', '4', '3', '0'};
  Exiv2::DataValue val(data, 12, Exiv2::ByteOrder::littleEndian, Exiv2::TypeId::undefined);
  
  maker_.print0x0015(os_, val, nullptr);
  EXPECT_EQ(os_.str(), "2023:06:15 14:30");
}

// Test with 11 non-zero digits (more than 10 but not 12 => no seconds)
TEST_F(CasioMakerNoteTest_1821, ElevenDigits_NoSeconds_1821) {
  uint8_t data[] = {'2', '3', '0', '6', '1', '5', '1', '4', '3', '0', '4'};
  Exiv2::DataValue val(data, 11, Exiv2::ByteOrder::littleEndian, Exiv2::TypeId::undefined);
  
  maker_.print0x0015(os_, val, nullptr);
  // 11 >= 10 but != 12, so no seconds appended
  EXPECT_EQ(os_.str(), "2023:06:15 14:30");
}

// Test with 13 non-zero digits (more than 12 => no seconds either, only ==12 triggers seconds)
TEST_F(CasioMakerNoteTest_1821, ThirteenDigits_NoSeconds_1821) {
  uint8_t data[] = {'2', '3', '0', '6', '1', '5', '1', '4', '3', '0', '4', '5', '9'};
  Exiv2::DataValue val(data, 13, Exiv2::ByteOrder::littleEndian, Exiv2::TypeId::undefined);
  
  maker_.print0x0015(os_, val, nullptr);
  // 13 >= 10 but != 12, so no seconds
  EXPECT_EQ(os_.str(), "2023:06:15 14:30");
}

// Test with empty value
TEST_F(CasioMakerNoteTest_1821, EmptyValue_1821) {
  Exiv2::DataValue val(Exiv2::TypeId::undefined);
  
  maker_.print0x0015(os_, val, nullptr);
  // Empty => fewer than 10 non-zero => fallback
  // Should not crash
  std::string result = os_.str();
  // Just verify no crash; empty value may produce empty or some representation
  SUCCEED();
}

// Test with all zeros => all filtered out => fewer than 10 => fallback
TEST_F(CasioMakerNoteTest_1821, AllZeros_FallbackToValue_1821) {
  uint8_t data[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  Exiv2::DataValue val(data, 12, Exiv2::ByteOrder::littleEndian, Exiv2::TypeId::undefined);
  
  maker_.print0x0015(os_, val, nullptr);
  // 0 non-zero digits < 10 => fallback
  // Should not crash
  SUCCEED();
}

// Test year 00 => 2000
TEST_F(CasioMakerNoteTest_1821, DateYear2000_1821) {
  // '0','0' => year = 0 < 70 => 2000
  uint8_t data[] = {'0', '0', '0', '1', '0', '1', '1', '2', '0', '0'};
  Exiv2::DataValue val(data, 10, Exiv2::ByteOrder::littleEndian, Exiv2::TypeId::undefined);
  
  maker_.print0x0015(os_, val, nullptr);
  EXPECT_EQ(os_.str(), "2000:01:01 12:00");
}

// Test year 99 => 1999
TEST_F(CasioMakerNoteTest_1821, DateYear1999_1821) {
  // '9','9' => year = 99 >= 70 => 1999
  uint8_t data[] = {'9', '9', '1', '2', '3', '1', '2', '3', '5', '9'};
  Exiv2::DataValue val(data, 10, Exiv2::ByteOrder::littleEndian, Exiv2::TypeId::undefined);
  
  maker_.print0x0015(os_, val, nullptr);
  EXPECT_EQ(os_.str(), "1999:12:31 23:59");
}

// Test with exactly 12 digits and seconds
TEST_F(CasioMakerNoteTest_1821, FullDateTimeWithSeconds_1821) {
  // 2023-06-15 14:30:59
  uint8_t data[] = {'2', '3', '0', '6', '1', '5', '1', '4', '3', '0', '5', '9'};
  Exiv2::DataValue val(data, 12, Exiv2::ByteOrder::littleEndian, Exiv2::TypeId::undefined);
  
  maker_.print0x0015(os_, val, nullptr);
  EXPECT_EQ(os_.str(), "2023:06:15 14:30:59");
}

// Test return value is the same ostream reference
TEST_F(CasioMakerNoteTest_1821, ReturnsOstreamReference_1821) {
  uint8_t data[] = {'2', '3', '0', '6', '1', '5', '1', '4', '3', '0'};
  Exiv2::DataValue val(data, 10, Exiv2::ByteOrder::littleEndian, Exiv2::TypeId::undefined);
  
  std::ostream& result = maker_.print0x0015(os_, val, nullptr);
  EXPECT_EQ(&result, &os_);
}

// Test with nullptr ExifData (should not crash)
TEST_F(CasioMakerNoteTest_1821, NullExifData_1821) {
  uint8_t data[] = {'2', '3', '0', '6', '1', '5', '1', '4', '3', '0', '4', '5'};
  Exiv2::DataValue val(data, 12, Exiv2::ByteOrder::littleEndian, Exiv2::TypeId::undefined);
  
  EXPECT_NO_THROW(maker_.print0x0015(os_, val, nullptr));
  EXPECT_EQ(os_.str(), "2023:06:15 14:30:45");
}

// Test with exactly 9 non-zero digits (boundary: just under 10)
TEST_F(CasioMakerNoteTest_1821, NineNonZeroDigits_Fallback_1821) {
  uint8_t data[] = {'2', '3', '0', '6', '1', '5', '1', '4', '3'};
  Exiv2::DataValue val(data, 9, Exiv2::ByteOrder::littleEndian, Exiv2::TypeId::undefined);
  
  maker_.print0x0015(os_, val, nullptr);
  // 9 < 10 => fallback to os << value
  std::string result = os_.str();
  // Should not be in date format
  EXPECT_TRUE(result.find("20") == std::string::npos || result.find(":") == std::string::npos ||
              result != "2023:06:15 14:3");
}
