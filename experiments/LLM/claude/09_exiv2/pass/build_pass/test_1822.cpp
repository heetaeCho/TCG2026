#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <vector>
#include <cstdint>

// Minimal stubs for Exiv2 types needed by the interface

namespace Exiv2 {

class ExifData {};

class Value {
 public:
  virtual ~Value() = default;
  virtual size_t size() const = 0;
  virtual int64_t toInt64(size_t index) const = 0;

  // operator<< for fallback output
  friend std::ostream& operator<<(std::ostream& os, const Value& v) {
    os << "RawValue";
    return os;
  }
};

namespace Internal {

class Casio2MakerNote {
 public:
  std::ostream& print0x2001(std::ostream& os, const Value& value, const ExifData*) {
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
    } else
      os << value;
    return os;
  }
};

}  // namespace Internal
}  // namespace Exiv2

// Mock for Value
class MockValue : public Exiv2::Value {
 public:
  MOCK_METHOD(size_t, size, (), (const, override));
  MOCK_METHOD(int64_t, toInt64, (size_t index), (const, override));
};

class Casio2MakerNoteTest_1822 : public ::testing::Test {
 protected:
  Exiv2::Internal::Casio2MakerNote maker_;
  std::ostringstream os_;
};

// Test: When value has fewer than 10 non-zero elements, fallback to printing raw value
TEST_F(Casio2MakerNoteTest_1822, FallbackWhenFewerThan10NonZeroElements_1822) {
  MockValue value;
  // 5 elements, all non-zero => numbers.size() == 5 < 10
  EXPECT_CALL(value, size()).WillRepeatedly(::testing::Return(5));
  EXPECT_CALL(value, toInt64(::testing::_)).WillRepeatedly(::testing::Return(49)); // '1'

  maker_.print0x2001(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "RawValue");
}

// Test: Empty value triggers fallback
TEST_F(Casio2MakerNoteTest_1822, FallbackWhenEmpty_1822) {
  MockValue value;
  EXPECT_CALL(value, size()).WillRepeatedly(::testing::Return(0));

  maker_.print0x2001(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "RawValue");
}

// Test: Exactly 10 non-zero elements with year < 70 => year += 2000
// Date: 2023:12:25 14:30
// ASCII: '2'=50, '0'=48, '1'=49, '2'=50, '1'=49, '2'=50, '5'=53, '1'=49, '4'=52, '3'=51, '0'=48
// numbers[0]='2'(50), numbers[1]='3'(51) => l = (50-48)*10 + (51-48) = 23 < 70 => 2023
// numbers[2]='1'(49), numbers[3]='2'(50) => "12"
// numbers[4]='2'(50), numbers[5]='5'(53) => "25"
// numbers[6]='1'(49), numbers[7]='4'(52) => "14"
// numbers[8]='3'(51), numbers[9]='0'(48) => "30"
TEST_F(Casio2MakerNoteTest_1822, Year2000sFormatting_1822) {
  MockValue value;
  std::vector<int64_t> data = {50, 51, 49, 50, 50, 53, 49, 52, 51, 48};
  EXPECT_CALL(value, size()).WillRepeatedly(::testing::Return(data.size()));
  for (size_t i = 0; i < data.size(); i++) {
    EXPECT_CALL(value, toInt64(i)).WillRepeatedly(::testing::Return(data[i]));
  }

  maker_.print0x2001(os_, value, nullptr);
  // Expected: "2023:12:25 14:30"
  EXPECT_EQ(os_.str(), "2023:12:25 14:30");
}

// Test: Year >= 70 => year += 1900 (e.g., year = 99 => 1999)
// numbers[0]='9'(57), numbers[1]='9'(57) => l = (57-48)*10 + (57-48) = 99 >= 70 => 1999
TEST_F(Casio2MakerNoteTest_1822, Year1900sFormatting_1822) {
  MockValue value;
  // '9','9','0','6','1','5','0','8','4','5' => 1999:06:15 08:45
  std::vector<int64_t> data = {57, 57, 48, 54, 49, 53, 48, 56, 52, 53};
  // Note: '0' is 48 which is 0 in the toInt64 check... Wait, toInt64 returns 48, which is != 0, so it's kept.
  EXPECT_CALL(value, size()).WillRepeatedly(::testing::Return(data.size()));
  for (size_t i = 0; i < data.size(); i++) {
    EXPECT_CALL(value, toInt64(i)).WillRepeatedly(::testing::Return(data[i]));
  }

  maker_.print0x2001(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "1999:06:15 08:45");
}

// Test: Year exactly 70 => 70 >= 70 => 1970
TEST_F(Casio2MakerNoteTest_1822, YearBoundary70_1822) {
  MockValue value;
  // numbers[0]='7'(55), numbers[1]='0'(48) => l = (55-48)*10 + (48-48) = 70 => 1970
  // Rest: '0','1','0','1','0','0','0','0' => 01:01 00:00
  std::vector<int64_t> data = {55, 48, 48, 49, 48, 49, 48, 48, 48, 48};
  EXPECT_CALL(value, size()).WillRepeatedly(::testing::Return(data.size()));
  for (size_t i = 0; i < data.size(); i++) {
    EXPECT_CALL(value, toInt64(i)).WillRepeatedly(::testing::Return(data[i]));
  }

  maker_.print0x2001(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "1970:01:01 00:00");
}

// Test: Year exactly 69 => 69 < 70 => 2069
TEST_F(Casio2MakerNoteTest_1822, YearBoundary69_1822) {
  MockValue value;
  // numbers[0]='6'(54), numbers[1]='9'(57) => l = (54-48)*10 + (57-48) = 69 < 70 => 2069
  std::vector<int64_t> data = {54, 57, 48, 49, 48, 49, 48, 48, 48, 48};
  EXPECT_CALL(value, size()).WillRepeatedly(::testing::Return(data.size()));
  for (size_t i = 0; i < data.size(); i++) {
    EXPECT_CALL(value, toInt64(i)).WillRepeatedly(::testing::Return(data[i]));
  }

  maker_.print0x2001(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "2069:01:01 00:00");
}

// Test: Zero elements are skipped, so with zeros interspersed we might not reach 10
TEST_F(Casio2MakerNoteTest_1822, ZerosAreFiltered_1822) {
  MockValue value;
  // 15 elements but many are 0; only 8 non-zero => fallback
  std::vector<int64_t> data = {50, 0, 51, 0, 49, 0, 50, 0, 50, 0, 53, 0, 49, 0, 52};
  // Non-zero: 50,51,49,50,50,53,49,52 => 8 < 10 => fallback
  EXPECT_CALL(value, size()).WillRepeatedly(::testing::Return(data.size()));
  for (size_t i = 0; i < data.size(); i++) {
    EXPECT_CALL(value, toInt64(i)).WillRepeatedly(::testing::Return(data[i]));
  }

  maker_.print0x2001(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "RawValue");
}

// Test: Exactly 10 non-zero with some zeros in between => date is formatted
TEST_F(Casio2MakerNoteTest_1822, ZerosFilteredButStillReach10_1822) {
  MockValue value;
  // 12 elements, 2 zeros, 10 non-zero
  std::vector<int64_t> data = {50, 51, 0, 49, 50, 50, 53, 0, 49, 52, 51, 48};
  // Non-zero: 50,51,49,50,50,53,49,52,51,48 => size 10
  // l = (50-48)*10 + (51-48) = 23 < 70 => 2023
  EXPECT_CALL(value, size()).WillRepeatedly(::testing::Return(data.size()));
  for (size_t i = 0; i < data.size(); i++) {
    EXPECT_CALL(value, toInt64(i)).WillRepeatedly(::testing::Return(data[i]));
  }

  maker_.print0x2001(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "2023:12:25 14:30");
}

// Test: More than 10 non-zero elements, only first 10 are used in formatting
TEST_F(Casio2MakerNoteTest_1822, MoreThan10NonZeroElements_1822) {
  MockValue value;
  // 12 non-zero elements
  std::vector<int64_t> data = {50, 51, 49, 50, 50, 53, 49, 52, 51, 48, 65, 66};
  EXPECT_CALL(value, size()).WillRepeatedly(::testing::Return(data.size()));
  for (size_t i = 0; i < data.size(); i++) {
    EXPECT_CALL(value, toInt64(i)).WillRepeatedly(::testing::Return(data[i]));
  }

  maker_.print0x2001(os_, value, nullptr);
  // Still uses first 10: same as 2023:12:25 14:30
  EXPECT_EQ(os_.str(), "2023:12:25 14:30");
}

// Test: Exactly 9 non-zero elements => fallback
TEST_F(Casio2MakerNoteTest_1822, Exactly9NonZeroFallback_1822) {
  MockValue value;
  std::vector<int64_t> data = {50, 51, 49, 50, 50, 53, 49, 52, 51};
  EXPECT_CALL(value, size()).WillRepeatedly(::testing::Return(data.size()));
  for (size_t i = 0; i < data.size(); i++) {
    EXPECT_CALL(value, toInt64(i)).WillRepeatedly(::testing::Return(data[i]));
  }

  maker_.print0x2001(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "RawValue");
}

// Test: Null ExifData pointer is acceptable
TEST_F(Casio2MakerNoteTest_1822, NullExifDataPointer_1822) {
  MockValue value;
  std::vector<int64_t> data = {50, 48, 49, 50, 48, 49, 49, 50, 48, 48};
  EXPECT_CALL(value, size()).WillRepeatedly(::testing::Return(data.size()));
  for (size_t i = 0; i < data.size(); i++) {
    EXPECT_CALL(value, toInt64(i)).WillRepeatedly(::testing::Return(data[i]));
  }

  // Should not crash with nullptr
  maker_.print0x2001(os_, value, nullptr);
  // l = (50-48)*10 + (48-48) = 20 < 70 => 2020
  EXPECT_EQ(os_.str(), "2020:12:01 12:00");
}

// Test: Year 00 => 0 < 70 => 2000
TEST_F(Casio2MakerNoteTest_1822, Year2000_1822) {
  MockValue value;
  // numbers[0]='0'(48), numbers[1]='0'(48) => l = 0 < 70 => 2000
  std::vector<int64_t> data = {48, 48, 48, 49, 48, 49, 48, 48, 48, 48};
  EXPECT_CALL(value, size()).WillRepeatedly(::testing::Return(data.size()));
  for (size_t i = 0; i < data.size(); i++) {
    EXPECT_CALL(value, toInt64(i)).WillRepeatedly(::testing::Return(data[i]));
  }

  maker_.print0x2001(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "2000:01:01 00:00");
}

// Test: All elements are zero => numbers is empty => fallback
TEST_F(Casio2MakerNoteTest_1822, AllZerosAreFallback_1822) {
  MockValue value;
  EXPECT_CALL(value, size()).WillRepeatedly(::testing::Return(10));
  EXPECT_CALL(value, toInt64(::testing::_)).WillRepeatedly(::testing::Return(0));

  maker_.print0x2001(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "RawValue");
}

// Test: Return value is the same ostream reference
TEST_F(Casio2MakerNoteTest_1822, ReturnsOstreamReference_1822) {
  MockValue value;
  EXPECT_CALL(value, size()).WillRepeatedly(::testing::Return(0));

  std::ostream& result = maker_.print0x2001(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}
