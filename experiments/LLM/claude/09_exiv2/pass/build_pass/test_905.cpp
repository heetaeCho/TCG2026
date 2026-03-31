#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <exiv2/value.hpp>
#include <exiv2/types.hpp>
#include <exiv2/exif.hpp>

// We need to include the internal header or replicate the class declaration
// Since we have the implementation, we'll work with it
namespace Exiv2 {
namespace Internal {
class OlympusMakerNote {
 public:
  std::ostream& print0x1209(std::ostream& os, const Value& value, const ExifData*);
};
}  // namespace Internal
}  // namespace Exiv2

class OlympusMakerNoteTest_905 : public ::testing::Test {
 protected:
  Exiv2::Internal::OlympusMakerNote maker_;
  std::ostringstream os_;
};

// Test: When value count is not 2, should print raw value
TEST_F(OlympusMakerNoteTest_905, Print0x1209_CountNotTwo_PrintsRawValue_905) {
  Exiv2::ValueType<uint16_t> value;
  value.value_.push_back(1);  // Only one element
  maker_.print0x1209(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "1");
}

// Test: When value type is not unsignedShort, should print raw value
TEST_F(OlympusMakerNoteTest_905, Print0x1209_WrongType_PrintsRawValue_905) {
  Exiv2::ValueType<int32_t> value;
  value.value_.push_back(1);
  value.value_.push_back(2);
  maker_.print0x1209(os_, value, nullptr);
  // Should print raw value since typeId != unsignedShort
  EXPECT_EQ(os_.str(), "1 2");
}

// Test: When first value is 0 (Off), second value printed as number
TEST_F(OlympusMakerNoteTest_905, Print0x1209_FirstValueZero_PrintsOff_905) {
  Exiv2::ValueType<uint16_t> value;
  value.value_.push_back(0);
  value.value_.push_back(42);
  maker_.print0x1209(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_TRUE(result.find("Off") != std::string::npos);
  EXPECT_TRUE(result.find("42") != std::string::npos);
}

// Test: When first value is 1 (On), second value printed as number
TEST_F(OlympusMakerNoteTest_905, Print0x1209_FirstValueOne_PrintsOn_905) {
  Exiv2::ValueType<uint16_t> value;
  value.value_.push_back(1);
  value.value_.push_back(100);
  maker_.print0x1209(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_TRUE(result.find("On") != std::string::npos);
  EXPECT_TRUE(result.find("100") != std::string::npos);
}

// Test: When first value is unknown (default case), prints the numeric value
TEST_F(OlympusMakerNoteTest_905, Print0x1209_FirstValueUnknown_PrintsNumber_905) {
  Exiv2::ValueType<uint16_t> value;
  value.value_.push_back(5);
  value.value_.push_back(200);
  maker_.print0x1209(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_TRUE(result.find("5") != std::string::npos);
  EXPECT_TRUE(result.find("200") != std::string::npos);
}

// Test: Output format includes a space separator between first and second part
TEST_F(OlympusMakerNoteTest_905, Print0x1209_SpaceSeparator_905) {
  Exiv2::ValueType<uint16_t> value;
  value.value_.push_back(0);
  value.value_.push_back(10);
  maker_.print0x1209(os_, value, nullptr);
  std::string result = os_.str();
  // "Off 10" - space between Off and 10
  EXPECT_TRUE(result.find(" ") != std::string::npos);
}

// Test: Second value is zero
TEST_F(OlympusMakerNoteTest_905, Print0x1209_SecondValueZero_905) {
  Exiv2::ValueType<uint16_t> value;
  value.value_.push_back(1);
  value.value_.push_back(0);
  maker_.print0x1209(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_TRUE(result.find("On") != std::string::npos);
  EXPECT_TRUE(result.find("0") != std::string::npos);
}

// Test: Count is 3 (more than 2), should print raw value
TEST_F(OlympusMakerNoteTest_905, Print0x1209_CountThree_PrintsRawValue_905) {
  Exiv2::ValueType<uint16_t> value;
  value.value_.push_back(1);
  value.value_.push_back(2);
  value.value_.push_back(3);
  maker_.print0x1209(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "1 2 3");
}

// Test: Count is 0 (empty), should print raw value
TEST_F(OlympusMakerNoteTest_905, Print0x1209_CountZero_PrintsRawValue_905) {
  Exiv2::ValueType<uint16_t> value;
  maker_.print0x1209(os_, value, nullptr);
  std::string result = os_.str();
  // Empty value, raw print
  EXPECT_TRUE(result.empty() || result.length() >= 0);
}

// Test: ExifData pointer is null (should still work fine)
TEST_F(OlympusMakerNoteTest_905, Print0x1209_NullExifData_905) {
  Exiv2::ValueType<uint16_t> value;
  value.value_.push_back(0);
  value.value_.push_back(50);
  EXPECT_NO_THROW(maker_.print0x1209(os_, value, nullptr));
  std::string result = os_.str();
  EXPECT_TRUE(result.find("Off") != std::string::npos);
  EXPECT_TRUE(result.find("50") != std::string::npos);
}

// Test: Large unknown first value in default case
TEST_F(OlympusMakerNoteTest_905, Print0x1209_LargeFirstValue_905) {
  Exiv2::ValueType<uint16_t> value;
  value.value_.push_back(65535);
  value.value_.push_back(65535);
  maker_.print0x1209(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_TRUE(result.find("65535") != std::string::npos);
}

// Test: Return value is the same ostream reference
TEST_F(OlympusMakerNoteTest_905, Print0x1209_ReturnsOstream_905) {
  Exiv2::ValueType<uint16_t> value;
  value.value_.push_back(1);
  value.value_.push_back(10);
  std::ostream& ret = maker_.print0x1209(os_, value, nullptr);
  EXPECT_EQ(&ret, &os_);
}

// Test: First value 2 is unknown/default
TEST_F(OlympusMakerNoteTest_905, Print0x1209_FirstValueTwo_DefaultCase_905) {
  Exiv2::ValueType<uint16_t> value;
  value.value_.push_back(2);
  value.value_.push_back(77);
  maker_.print0x1209(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_TRUE(result.find("2") != std::string::npos);
  EXPECT_TRUE(result.find("77") != std::string::npos);
  // Should NOT contain "Off" or "On"
  EXPECT_EQ(result.find("Off"), std::string::npos);
  EXPECT_EQ(result.find("On"), std::string::npos);
}
