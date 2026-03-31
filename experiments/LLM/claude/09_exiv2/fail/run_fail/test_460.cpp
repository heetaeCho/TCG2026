#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>
#include <vector>
#include <cstdint>

// We need Exiv2 headers for Value and ExifData types
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

// Include the internal header if available, otherwise declare the class
namespace Exiv2 {
namespace Internal {

class Nikon3MakerNote {
 public:
  std::ostream& print0x0002(std::ostream& os, const Value& value, const ExifData*);
};

}  // namespace Internal
}  // namespace Exiv2

using namespace Exiv2;
using namespace Exiv2::Internal;

class Nikon3MakerNoteTest_460 : public ::testing::Test {
 protected:
  Nikon3MakerNote maker_note_;
  std::ostringstream os_;
};

// Test: When value has count > 1, print0x0002 should output value.toInt64(1)
TEST_F(Nikon3MakerNoteTest_460, Print0x0002_MultipleValues_PrintsSecondValue_460) {
  auto value = Value::create(unsignedShort);
  value->read("10 20 30");

  ASSERT_GT(value->count(), 1u);

  maker_note_.print0x0002(os_, *value, nullptr);

  // Should print the second element (index 1) as an integer
  EXPECT_EQ(os_.str(), "20");
}

// Test: When value has exactly 1 element, print0x0002 should output "(value)"
TEST_F(Nikon3MakerNoteTest_460, Print0x0002_SingleValue_PrintsInParentheses_460) {
  auto value = Value::create(unsignedShort);
  value->read("42");

  ASSERT_EQ(value->count(), 1u);

  maker_note_.print0x0002(os_, *value, nullptr);

  std::string result = os_.str();
  EXPECT_EQ(result.front(), '(');
  EXPECT_EQ(result.back(), ')');
  EXPECT_NE(result.find("42"), std::string::npos);
}

// Test: When value has count == 0, should print "(value)" format
TEST_F(Nikon3MakerNoteTest_460, Print0x0002_EmptyValue_PrintsInParentheses_460) {
  auto value = Value::create(unsignedShort);
  // Don't read anything, count should be 0

  ASSERT_LE(value->count(), 1u);

  maker_note_.print0x0002(os_, *value, nullptr);

  std::string result = os_.str();
  EXPECT_EQ(result.front(), '(');
  EXPECT_EQ(result.back(), ')');
}

// Test: When value has exactly 2 elements, it should print the second element
TEST_F(Nikon3MakerNoteTest_460, Print0x0002_TwoValues_PrintsSecondValue_460) {
  auto value = Value::create(unsignedShort);
  value->read("100 200");

  ASSERT_EQ(value->count(), 2u);

  maker_note_.print0x0002(os_, *value, nullptr);

  EXPECT_EQ(os_.str(), "200");
}

// Test: With ExifData pointer being nullptr, function should still work
TEST_F(Nikon3MakerNoteTest_460, Print0x0002_NullExifData_WorksCorrectly_460) {
  auto value = Value::create(unsignedShort);
  value->read("5 10");

  maker_note_.print0x0002(os_, *value, nullptr);

  EXPECT_EQ(os_.str(), "10");
}

// Test: With ExifData pointer being non-null (it's unused but should still work)
TEST_F(Nikon3MakerNoteTest_460, Print0x0002_NonNullExifData_WorksCorrectly_460) {
  auto value = Value::create(unsignedShort);
  value->read("7 14 21");

  ExifData exifData;
  maker_note_.print0x0002(os_, *value, &exifData);

  EXPECT_EQ(os_.str(), "14");
}

// Test: Return value is the same ostream reference
TEST_F(Nikon3MakerNoteTest_460, Print0x0002_ReturnsSameOstream_460) {
  auto value = Value::create(unsignedShort);
  value->read("1 2");

  std::ostream& result = maker_note_.print0x0002(os_, *value, nullptr);

  EXPECT_EQ(&result, &os_);
}

// Test: Return value is the same ostream reference for single value case
TEST_F(Nikon3MakerNoteTest_460, Print0x0002_SingleValue_ReturnsSameOstream_460) {
  auto value = Value::create(unsignedShort);
  value->read("99");

  std::ostream& result = maker_note_.print0x0002(os_, *value, nullptr);

  EXPECT_EQ(&result, &os_);
}

// Test: Large values should work correctly
TEST_F(Nikon3MakerNoteTest_460, Print0x0002_LargeValues_PrintsCorrectly_460) {
  auto value = Value::create(unsignedLong);
  value->read("65535 1000000");

  ASSERT_GT(value->count(), 1u);

  maker_note_.print0x0002(os_, *value, nullptr);

  EXPECT_EQ(os_.str(), "1000000");
}

// Test: Zero values in multi-element
TEST_F(Nikon3MakerNoteTest_460, Print0x0002_ZeroSecondValue_PrintsZero_460) {
  auto value = Value::create(unsignedShort);
  value->read("5 0");

  maker_note_.print0x0002(os_, *value, nullptr);

  EXPECT_EQ(os_.str(), "0");
}

// Test: Many elements - should still print second element
TEST_F(Nikon3MakerNoteTest_460, Print0x0002_ManyValues_PrintsSecondValue_460) {
  auto value = Value::create(unsignedShort);
  value->read("1 2 3 4 5 6 7 8 9 10");

  ASSERT_GT(value->count(), 1u);

  maker_note_.print0x0002(os_, *value, nullptr);

  EXPECT_EQ(os_.str(), "2");
}

// Test: Using signed values
TEST_F(Nikon3MakerNoteTest_460, Print0x0002_SignedValues_PrintsSecondValue_460) {
  auto value = Value::create(signedShort);
  value->read("10 -5");

  ASSERT_GT(value->count(), 1u);

  maker_note_.print0x0002(os_, *value, nullptr);

  EXPECT_EQ(os_.str(), "-5");
}
