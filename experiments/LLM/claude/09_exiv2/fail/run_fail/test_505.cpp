#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <exiv2/value.hpp>
#include <exiv2/types.hpp>
#include <exiv2/exif.hpp>

// We need to include or replicate the class definition for testing
namespace Exiv2 {
namespace Internal {
class Nikon3MakerNote {
 public:
  std::ostream& print0x009a(std::ostream& os, const Value& value, const ExifData*) {
    if (value.count() != 2 || value.typeId() != unsignedRational)
      return os << value;
    float f1 = value.toFloat(0);
    float f2 = value.toFloat(1);
    return os << f1 << " x " << f2 << " um";
  }
};
}  // namespace Internal
}  // namespace Exiv2

using namespace Exiv2;
using namespace Exiv2::Internal;

class Nikon3MakerNoteTest_505 : public ::testing::Test {
 protected:
  Nikon3MakerNote maker_;
  std::ostringstream os_;
};

// Test normal operation with two unsigned rational values
TEST_F(Nikon3MakerNoteTest_505, Print0x009a_NormalTwoRationals_505) {
  URationalValue value;
  value.value_.push_back({600, 100});  // 6.0
  value.value_.push_back({600, 100});  // 6.0

  maker_.print0x009a(os_, value, nullptr);
  std::string result = os_.str();

  EXPECT_NE(result.find("x"), std::string::npos);
  EXPECT_NE(result.find("um"), std::string::npos);
}

// Test with count != 2 (only one rational value) - should fall through to default output
TEST_F(Nikon3MakerNoteTest_505, Print0x009a_SingleRational_505) {
  URationalValue value;
  value.value_.push_back({600, 100});

  maker_.print0x009a(os_, value, nullptr);
  std::string result = os_.str();

  // Should not contain "um" since count != 2
  EXPECT_EQ(result.find("um"), std::string::npos);
}

// Test with count != 2 (three rational values) - should fall through to default output
TEST_F(Nikon3MakerNoteTest_505, Print0x009a_ThreeRationals_505) {
  URationalValue value;
  value.value_.push_back({600, 100});
  value.value_.push_back({600, 100});
  value.value_.push_back({600, 100});

  maker_.print0x009a(os_, value, nullptr);
  std::string result = os_.str();

  EXPECT_EQ(result.find("um"), std::string::npos);
}

// Test with wrong type (not unsignedRational) - should fall through to default output
TEST_F(Nikon3MakerNoteTest_505, Print0x009a_WrongType_505) {
  UShortValue value;
  value.value_.push_back(600);
  value.value_.push_back(600);

  maker_.print0x009a(os_, value, nullptr);
  std::string result = os_.str();

  // Should not contain "um" since type is not unsignedRational
  EXPECT_EQ(result.find("um"), std::string::npos);
}

// Test with zero values in rationals
TEST_F(Nikon3MakerNoteTest_505, Print0x009a_ZeroValues_505) {
  URationalValue value;
  value.value_.push_back({0, 1});
  value.value_.push_back({0, 1});

  maker_.print0x009a(os_, value, nullptr);
  std::string result = os_.str();

  EXPECT_NE(result.find("0"), std::string::npos);
  EXPECT_NE(result.find("x"), std::string::npos);
  EXPECT_NE(result.find("um"), std::string::npos);
}

// Test with specific known values to verify formatting
TEST_F(Nikon3MakerNoteTest_505, Print0x009a_SpecificValues_505) {
  URationalValue value;
  value.value_.push_back({1200, 100});  // 12.0
  value.value_.push_back({800, 100});   // 8.0

  maker_.print0x009a(os_, value, nullptr);
  std::string result = os_.str();

  EXPECT_NE(result.find("12"), std::string::npos);
  EXPECT_NE(result.find("8"), std::string::npos);
  EXPECT_NE(result.find(" x "), std::string::npos);
  EXPECT_NE(result.find(" um"), std::string::npos);
}

// Test with nullptr ExifData - should work fine
TEST_F(Nikon3MakerNoteTest_505, Print0x009a_NullExifData_505) {
  URationalValue value;
  value.value_.push_back({500, 100});
  value.value_.push_back({500, 100});

  EXPECT_NO_THROW(maker_.print0x009a(os_, value, nullptr));
  std::string result = os_.str();
  EXPECT_NE(result.find("um"), std::string::npos);
}

// Test with empty value (count == 0)
TEST_F(Nikon3MakerNoteTest_505, Print0x009a_EmptyValue_505) {
  URationalValue value;

  maker_.print0x009a(os_, value, nullptr);
  std::string result = os_.str();

  // count is 0, not 2, so should not contain "um"
  EXPECT_EQ(result.find("um"), std::string::npos);
}

// Test that the return value is the same ostream
TEST_F(Nikon3MakerNoteTest_505, Print0x009a_ReturnsSameStream_505) {
  URationalValue value;
  value.value_.push_back({100, 10});
  value.value_.push_back({200, 10});

  std::ostream& returned = maker_.print0x009a(os_, value, nullptr);
  EXPECT_EQ(&returned, &os_);
}

// Test return value for fallback path
TEST_F(Nikon3MakerNoteTest_505, Print0x009a_ReturnsSameStreamFallback_505) {
  URationalValue value;
  value.value_.push_back({100, 10});  // only one element

  std::ostream& returned = maker_.print0x009a(os_, value, nullptr);
  EXPECT_EQ(&returned, &os_);
}

// Test with large rational values
TEST_F(Nikon3MakerNoteTest_505, Print0x009a_LargeValues_505) {
  URationalValue value;
  value.value_.push_back({4294967295u, 1});
  value.value_.push_back({4294967295u, 1});

  maker_.print0x009a(os_, value, nullptr);
  std::string result = os_.str();

  EXPECT_NE(result.find("x"), std::string::npos);
  EXPECT_NE(result.find("um"), std::string::npos);
}

// Test with fractional rational values
TEST_F(Nikon3MakerNoteTest_505, Print0x009a_FractionalValues_505) {
  URationalValue value;
  value.value_.push_back({1, 3});   // ~0.333
  value.value_.push_back({2, 7});   // ~0.286

  maker_.print0x009a(os_, value, nullptr);
  std::string result = os_.str();

  EXPECT_NE(result.find(" x "), std::string::npos);
  EXPECT_NE(result.find("um"), std::string::npos);
}
