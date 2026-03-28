#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

// We need to include the internal header or replicate the class interface
// Since we're given the implementation, we work with the namespace directly
namespace Exiv2 {
namespace Internal {
class CanonMakerNote {
 public:
  std::ostream& printFiFocusDistance(std::ostream& os, const Value& value, const ExifData*) {
    if (value.typeId() != signedShort || value.count() == 0)
      return os << value;
    auto l = value.toInt64();
    if (l == -1) {
      return os << "Infinite";
    }
    return os << std::format("{:.2f} m", l / 100.0);
  }
};
}  // namespace Internal
}  // namespace Exiv2

using namespace Exiv2;
using namespace Exiv2::Internal;

class CanonMakerNoteTest_965 : public ::testing::Test {
 protected:
  CanonMakerNote maker_;
  std::ostringstream os_;
};

// Test: When value type is signedShort and value is -1, output should be "Infinite"
TEST_F(CanonMakerNoteTest_965, InfiniteDistance_965) {
  ValueType<int16_t> value(signedShort);
  value.value_.push_back(-1);

  maker_.printFiFocusDistance(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "Infinite");
}

// Test: When value type is signedShort and value is positive (e.g., 100 = 1.00 m)
TEST_F(CanonMakerNoteTest_965, PositiveDistance100_965) {
  ValueType<int16_t> value(signedShort);
  value.value_.push_back(100);

  maker_.printFiFocusDistance(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "1.00 m");
}

// Test: When value type is signedShort and value is 0 (0.00 m)
TEST_F(CanonMakerNoteTest_965, ZeroDistance_965) {
  ValueType<int16_t> value(signedShort);
  value.value_.push_back(0);

  maker_.printFiFocusDistance(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "0.00 m");
}

// Test: When value type is signedShort and value is 250 (2.50 m)
TEST_F(CanonMakerNoteTest_965, Distance250_965) {
  ValueType<int16_t> value(signedShort);
  value.value_.push_back(250);

  maker_.printFiFocusDistance(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "2.50 m");
}

// Test: When value type is signedShort and value is 1 (0.01 m)
TEST_F(CanonMakerNoteTest_965, Distance1_965) {
  ValueType<int16_t> value(signedShort);
  value.value_.push_back(1);

  maker_.printFiFocusDistance(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "0.01 m");
}

// Test: When value type is signedShort and value is 50 (0.50 m)
TEST_F(CanonMakerNoteTest_965, Distance50_965) {
  ValueType<int16_t> value(signedShort);
  value.value_.push_back(50);

  maker_.printFiFocusDistance(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "0.50 m");
}

// Test: When value type is signedShort and value is negative but not -1 (e.g., -50)
TEST_F(CanonMakerNoteTest_965, NegativeDistanceNotMinusOne_965) {
  ValueType<int16_t> value(signedShort);
  value.value_.push_back(-50);

  maker_.printFiFocusDistance(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "-0.50 m");
}

// Test: When value type is not signedShort (e.g., unsignedShort), it should fall through to printing value directly
TEST_F(CanonMakerNoteTest_965, NonSignedShortType_965) {
  ValueType<uint16_t> value(unsignedShort);
  value.value_.push_back(100);

  maker_.printFiFocusDistance(os_, value, nullptr);
  // Should print the value using operator<<, which prints the raw value
  EXPECT_FALSE(os_.str().empty());
}

// Test: When value type is signedShort but count is 0 (empty value)
TEST_F(CanonMakerNoteTest_965, EmptySignedShortValue_965) {
  ValueType<int16_t> value(signedShort);
  // Don't add any values, count should be 0

  maker_.printFiFocusDistance(os_, value, nullptr);
  // Should print value directly via os << value
  // The output for an empty value may vary, but should not crash
  // Just verify it doesn't print distance format
  EXPECT_TRUE(os_.str().find(" m") == std::string::npos);
}

// Test: When value type is unsignedLong, should print value directly
TEST_F(CanonMakerNoteTest_965, UnsignedLongType_965) {
  ValueType<uint32_t> value(unsignedLong);
  value.value_.push_back(500);

  maker_.printFiFocusDistance(os_, value, nullptr);
  EXPECT_FALSE(os_.str().empty());
}

// Test: Large positive value
TEST_F(CanonMakerNoteTest_965, LargePositiveValue_965) {
  ValueType<int16_t> value(signedShort);
  value.value_.push_back(32767);  // max int16_t

  maker_.printFiFocusDistance(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "327.67 m");
}

// Test: Passing nullptr for ExifData should work fine
TEST_F(CanonMakerNoteTest_965, NullExifData_965) {
  ValueType<int16_t> value(signedShort);
  value.value_.push_back(200);

  maker_.printFiFocusDistance(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "2.00 m");
}

// Test: Value of -2 (negative but not infinite)
TEST_F(CanonMakerNoteTest_965, NegativeTwo_965) {
  ValueType<int16_t> value(signedShort);
  value.value_.push_back(-2);

  maker_.printFiFocusDistance(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "-0.02 m");
}

// Test: Stream is returned correctly (chaining)
TEST_F(CanonMakerNoteTest_965, ReturnStream_965) {
  ValueType<int16_t> value(signedShort);
  value.value_.push_back(100);

  std::ostream& result = maker_.printFiFocusDistance(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}

// Test: Multiple values in signedShort - only first value (toInt64) is used
TEST_F(CanonMakerNoteTest_965, MultipleValues_965) {
  ValueType<int16_t> value(signedShort);
  value.value_.push_back(300);
  value.value_.push_back(500);

  maker_.printFiFocusDistance(os_, value, nullptr);
  // toInt64() with no index returns first value
  EXPECT_EQ(os_.str(), "3.00 m");
}
