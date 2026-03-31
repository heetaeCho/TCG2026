#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

// We need to include or replicate the interface under test
namespace Exiv2 {
namespace Internal {

class SonyMakerNote {
 public:
  std::ostream& printColorCompensationFilter(std::ostream& os, const Value& value, const ExifData*) {
    if (value.count() != 1 || value.typeId() != unsignedLong)
      return os << "(" << value << ")";
    int64_t temp = static_cast<int32_t>(value.toUint32(0));
    os << "G/M: ";
    if (temp == 0)
      return os << "0";
    if (temp < 0)
      return os << "G" << -temp;
    return os << "M" << temp;
  }
};

}  // namespace Internal
}  // namespace Exiv2

using namespace Exiv2;
using namespace Exiv2::Internal;

class SonyMakerNoteTest_1605 : public ::testing::Test {
 protected:
  SonyMakerNote maker_;
  std::ostringstream os_;
};

// Test: When value is zero, output should be "G/M: 0"
TEST_F(SonyMakerNoteTest_1605, ZeroValue_1605) {
  ULongValue val;
  val.read("0");
  maker_.printColorCompensationFilter(os_, val, nullptr);
  EXPECT_EQ(os_.str(), "G/M: 0");
}

// Test: When value is positive, output should be "G/M: M<value>"
TEST_F(SonyMakerNoteTest_1605, PositiveValue_1605) {
  ULongValue val;
  val.read("5");
  maker_.printColorCompensationFilter(os_, val, nullptr);
  EXPECT_EQ(os_.str(), "G/M: M5");
}

// Test: When value is a large positive number that fits in int32, should show M<value>
TEST_F(SonyMakerNoteTest_1605, LargePositiveValue_1605) {
  ULongValue val;
  val.read("100");
  maker_.printColorCompensationFilter(os_, val, nullptr);
  EXPECT_EQ(os_.str(), "G/M: M100");
}

// Test: When value represents a negative number (high uint32 value wrapping to negative int32),
// output should be "G/M: G<abs_value>"
TEST_F(SonyMakerNoteTest_1605, NegativeValueViaOverflow_1605) {
  // 0xFFFFFFFF = 4294967295 as uint32, which is -1 as int32
  ULongValue val;
  val.read("4294967295");
  maker_.printColorCompensationFilter(os_, val, nullptr);
  EXPECT_EQ(os_.str(), "G/M: G1");
}

// Test: Another negative value: 0xFFFFFFFB = 4294967291 as uint32, which is -5 as int32
TEST_F(SonyMakerNoteTest_1605, NegativeValueMinusFive_1605) {
  ULongValue val;
  val.read("4294967291");  // -5 as int32
  maker_.printColorCompensationFilter(os_, val, nullptr);
  EXPECT_EQ(os_.str(), "G/M: G5");
}

// Test: When count != 1, should output raw value in parentheses
TEST_F(SonyMakerNoteTest_1605, MultipleValuesReturnsRaw_1605) {
  ULongValue val;
  val.read("3 7");  // Two values
  maker_.printColorCompensationFilter(os_, val, nullptr);
  std::string result = os_.str();
  EXPECT_EQ(result.front(), '(');
  EXPECT_EQ(result.back(), ')');
}

// Test: When type is not unsignedLong, should output raw value in parentheses
TEST_F(SonyMakerNoteTest_1605, WrongTypeReturnsRaw_1605) {
  UShortValue val;
  val.read("10");
  maker_.printColorCompensationFilter(os_, val, nullptr);
  std::string result = os_.str();
  EXPECT_EQ(result.front(), '(');
  EXPECT_EQ(result.back(), ')');
}

// Test: When count is 0 (empty value), should output parenthesized
TEST_F(SonyMakerNoteTest_1605, EmptyValueReturnsRaw_1605) {
  ULongValue val;
  // Don't read any value, count should be 0
  maker_.printColorCompensationFilter(os_, val, nullptr);
  std::string result = os_.str();
  EXPECT_EQ(result.front(), '(');
  EXPECT_EQ(result.back(), ')');
}

// Test: Value of 1 should produce "G/M: M1"
TEST_F(SonyMakerNoteTest_1605, ValueOne_1605) {
  ULongValue val;
  val.read("1");
  maker_.printColorCompensationFilter(os_, val, nullptr);
  EXPECT_EQ(os_.str(), "G/M: M1");
}

// Test: Passing nullptr as ExifData* should still work (no crash)
TEST_F(SonyMakerNoteTest_1605, NullExifDataDoesNotCrash_1605) {
  ULongValue val;
  val.read("10");
  EXPECT_NO_THROW(maker_.printColorCompensationFilter(os_, val, nullptr));
  EXPECT_EQ(os_.str(), "G/M: M10");
}

// Test: 0x80000000 as uint32 = 2147483648, which is INT32_MIN = -2147483648
TEST_F(SonyMakerNoteTest_1605, Int32MinBoundary_1605) {
  ULongValue val;
  val.read("2147483648");  // INT32_MIN as uint32
  maker_.printColorCompensationFilter(os_, val, nullptr);
  // INT32_MIN as int32 is negative, so should print G<abs>
  // Note: -INT32_MIN is undefined behavior for int32, but int64_t handles it
  std::string result = os_.str();
  EXPECT_TRUE(result.find("G/M: G") != std::string::npos);
}

// Test: INT32_MAX = 2147483647 should be positive
TEST_F(SonyMakerNoteTest_1605, Int32MaxBoundary_1605) {
  ULongValue val;
  val.read("2147483647");  // INT32_MAX
  maker_.printColorCompensationFilter(os_, val, nullptr);
  EXPECT_EQ(os_.str(), "G/M: M2147483647");
}

// Test: 0xFFFFFFFE = 4294967294 as uint32, which is -2 as int32
TEST_F(SonyMakerNoteTest_1605, NegativeValueMinusTwo_1605) {
  ULongValue val;
  val.read("4294967294");  // -2 as int32
  maker_.printColorCompensationFilter(os_, val, nullptr);
  EXPECT_EQ(os_.str(), "G/M: G2");
}

// Test: String type value should trigger the fallback parenthesized output
TEST_F(SonyMakerNoteTest_1605, StringTypeReturnsRaw_1605) {
  StringValue val;
  val.read("hello");
  maker_.printColorCompensationFilter(os_, val, nullptr);
  std::string result = os_.str();
  EXPECT_EQ(result.front(), '(');
  EXPECT_EQ(result.back(), ')');
}
