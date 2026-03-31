#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>

// We need to include or replicate the minimal interface for Value and ExifData
// Since we're treating implementation as black box, we need the actual headers
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

// Include the internal header for Nikon1MakerNote
// Based on the file path, we need the internal namespace
namespace Exiv2 {
namespace Internal {

class Nikon1MakerNote {
 public:
  std::ostream& print0x0002(std::ostream& os, const Value& value, const ExifData*);
};

}  // namespace Internal
}  // namespace Exiv2

class Nikon1MakerNoteTest_450 : public ::testing::Test {
 protected:
  Exiv2::Internal::Nikon1MakerNote maker_;
  std::ostringstream os_;
};

// Test: When value has more than 1 element, prints the second element (index 1)
TEST_F(Nikon1MakerNoteTest_450, Print0x0002_MultipleValues_PrintsSecondElement_450) {
  // Create a value with multiple entries
  Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
  value.value_.push_back(100);
  value.value_.push_back(200);

  maker_.print0x0002(os_, value, nullptr);

  EXPECT_EQ(os_.str(), "200");
}

// Test: When value has exactly 1 element, prints in parenthesized format
TEST_F(Nikon1MakerNoteTest_450, Print0x0002_SingleValue_PrintsParenthesized_450) {
  Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
  value.value_.push_back(42);

  maker_.print0x0002(os_, value, nullptr);

  std::string result = os_.str();
  EXPECT_EQ(result.front(), '(');
  EXPECT_EQ(result.back(), ')');
  // Should contain the value representation
  EXPECT_NE(result.find("42"), std::string::npos);
}

// Test: When value has exactly 2 elements, prints the second element
TEST_F(Nikon1MakerNoteTest_450, Print0x0002_TwoValues_PrintsSecondElement_450) {
  Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
  value.value_.push_back(10);
  value.value_.push_back(20);

  maker_.print0x0002(os_, value, nullptr);

  EXPECT_EQ(os_.str(), "20");
}

// Test: When value has 3 elements, still prints only the second element
TEST_F(Nikon1MakerNoteTest_450, Print0x0002_ThreeValues_PrintsSecondElement_450) {
  Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
  value.value_.push_back(5);
  value.value_.push_back(15);
  value.value_.push_back(25);

  maker_.print0x0002(os_, value, nullptr);

  EXPECT_EQ(os_.str(), "15");
}

// Test: ExifData pointer is null - should work fine for both cases
TEST_F(Nikon1MakerNoteTest_450, Print0x0002_NullExifData_SingleValue_450) {
  Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
  value.value_.push_back(99);

  maker_.print0x0002(os_, value, nullptr);

  std::string result = os_.str();
  EXPECT_EQ(result, "(99)");
}

// Test: Returns reference to the same ostream
TEST_F(Nikon1MakerNoteTest_450, Print0x0002_ReturnsOstreamReference_MultipleValues_450) {
  Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
  value.value_.push_back(1);
  value.value_.push_back(2);

  std::ostream& result = maker_.print0x0002(os_, value, nullptr);

  EXPECT_EQ(&result, &os_);
}

// Test: Returns reference to the same ostream for single value
TEST_F(Nikon1MakerNoteTest_450, Print0x0002_ReturnsOstreamReference_SingleValue_450) {
  Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
  value.value_.push_back(1);

  std::ostream& result = maker_.print0x0002(os_, value, nullptr);

  EXPECT_EQ(&result, &os_);
}

// Test: Value with zero as second element
TEST_F(Nikon1MakerNoteTest_450, Print0x0002_ZeroSecondValue_450) {
  Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
  value.value_.push_back(1);
  value.value_.push_back(0);

  maker_.print0x0002(os_, value, nullptr);

  EXPECT_EQ(os_.str(), "0");
}

// Test: Single value with zero
TEST_F(Nikon1MakerNoteTest_450, Print0x0002_SingleZeroValue_Parenthesized_450) {
  Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
  value.value_.push_back(0);

  maker_.print0x0002(os_, value, nullptr);

  EXPECT_EQ(os_.str(), "(0)");
}

// Test: Large number of values - should still print second element
TEST_F(Nikon1MakerNoteTest_450, Print0x0002_ManyValues_PrintsSecondElement_450) {
  Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
  for (uint16_t i = 0; i < 100; ++i) {
    value.value_.push_back(i * 10);
  }

  maker_.print0x0002(os_, value, nullptr);

  // Second element (index 1) should be 10
  EXPECT_EQ(os_.str(), "10");
}

// Test: Using signed values
TEST_F(Nikon1MakerNoteTest_450, Print0x0002_SignedValues_PrintsSecondElement_450) {
  Exiv2::ValueType<int16_t> value(Exiv2::signedShort);
  value.value_.push_back(-10);
  value.value_.push_back(-20);

  maker_.print0x0002(os_, value, nullptr);

  EXPECT_EQ(os_.str(), "-20");
}

// Test: Non-null ExifData pointer with multiple values
TEST_F(Nikon1MakerNoteTest_450, Print0x0002_NonNullExifData_MultipleValues_450) {
  Exiv2::ExifData exifData;
  Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
  value.value_.push_back(50);
  value.value_.push_back(75);

  maker_.print0x0002(os_, value, &exifData);

  EXPECT_EQ(os_.str(), "75");
}

// Test: Non-null ExifData pointer with single value
TEST_F(Nikon1MakerNoteTest_450, Print0x0002_NonNullExifData_SingleValue_450) {
  Exiv2::ExifData exifData;
  Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
  value.value_.push_back(50);

  maker_.print0x0002(os_, value, &exifData);

  EXPECT_EQ(os_.str(), "(50)");
}
