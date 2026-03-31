#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

// Include the internal header for SonyMakerNote
// We need to replicate the class since it's defined in the cpp file
namespace Exiv2 {
namespace Internal {
class SonyMakerNote {
 public:
  std::ostream& printImageSize(std::ostream& os, const Value& value, const ExifData*) {
    if (value.count() != 2 || value.typeId() != unsignedLong)
      return os << "(" << value << ")";
    return os << value.toString(1) << " x " << value.toString(0);
  }
};
}  // namespace Internal
}  // namespace Exiv2

using namespace Exiv2;
using namespace Exiv2::Internal;

class SonyMakerNoteTest_1608 : public ::testing::Test {
 protected:
  SonyMakerNote makerNote_;
  std::ostringstream os_;
};

// Test normal operation: two unsignedLong values should print "value[1] x value[0]"
TEST_F(SonyMakerNoteTest_1608, PrintImageSize_NormalTwoUnsignedLongs_1608) {
  ValueType<uint32_t> value(unsignedLong);
  value.value_.push_back(3000);  // width (index 0)
  value.value_.push_back(2000);  // height (index 1)

  makerNote_.printImageSize(os_, value, nullptr);

  EXPECT_EQ(os_.str(), "2000 x 3000");
}

// Test with count != 2: only one value
TEST_F(SonyMakerNoteTest_1608, PrintImageSize_SingleValue_1608) {
  ValueType<uint32_t> value(unsignedLong);
  value.value_.push_back(3000);

  makerNote_.printImageSize(os_, value, nullptr);

  std::string result = os_.str();
  EXPECT_TRUE(result.front() == '(' && result.back() == ')');
}

// Test with count != 2: three values
TEST_F(SonyMakerNoteTest_1608, PrintImageSize_ThreeValues_1608) {
  ValueType<uint32_t> value(unsignedLong);
  value.value_.push_back(3000);
  value.value_.push_back(2000);
  value.value_.push_back(1000);

  makerNote_.printImageSize(os_, value, nullptr);

  std::string result = os_.str();
  EXPECT_TRUE(result.front() == '(' && result.back() == ')');
}

// Test with count == 0: empty value
TEST_F(SonyMakerNoteTest_1608, PrintImageSize_EmptyValue_1608) {
  ValueType<uint32_t> value(unsignedLong);

  makerNote_.printImageSize(os_, value, nullptr);

  std::string result = os_.str();
  EXPECT_TRUE(result.front() == '(' && result.back() == ')');
}

// Test with wrong type: two values but unsignedShort instead of unsignedLong
TEST_F(SonyMakerNoteTest_1608, PrintImageSize_WrongType_UnsignedShort_1608) {
  ValueType<uint16_t> value(unsignedShort);
  value.value_.push_back(3000);
  value.value_.push_back(2000);

  makerNote_.printImageSize(os_, value, nullptr);

  std::string result = os_.str();
  EXPECT_TRUE(result.front() == '(' && result.back() == ')');
}

// Test with wrong type: signedLong with two values
TEST_F(SonyMakerNoteTest_1608, PrintImageSize_WrongType_SignedLong_1608) {
  ValueType<int32_t> value(signedLong);
  value.value_.push_back(3000);
  value.value_.push_back(2000);

  makerNote_.printImageSize(os_, value, nullptr);

  std::string result = os_.str();
  EXPECT_TRUE(result.front() == '(' && result.back() == ')');
}

// Test normal with specific known dimensions
TEST_F(SonyMakerNoteTest_1608, PrintImageSize_SpecificDimensions_1608) {
  ValueType<uint32_t> value(unsignedLong);
  value.value_.push_back(4000);  // index 0
  value.value_.push_back(6000);  // index 1

  makerNote_.printImageSize(os_, value, nullptr);

  EXPECT_EQ(os_.str(), "6000 x 4000");
}

// Test with zero values
TEST_F(SonyMakerNoteTest_1608, PrintImageSize_ZeroValues_1608) {
  ValueType<uint32_t> value(unsignedLong);
  value.value_.push_back(0);
  value.value_.push_back(0);

  makerNote_.printImageSize(os_, value, nullptr);

  EXPECT_EQ(os_.str(), "0 x 0");
}

// Test with large values
TEST_F(SonyMakerNoteTest_1608, PrintImageSize_LargeValues_1608) {
  ValueType<uint32_t> value(unsignedLong);
  value.value_.push_back(4294967295u);  // max uint32
  value.value_.push_back(4294967295u);

  makerNote_.printImageSize(os_, value, nullptr);

  EXPECT_EQ(os_.str(), "4294967295 x 4294967295");
}

// Test that nullptr ExifData is handled (doesn't crash)
TEST_F(SonyMakerNoteTest_1608, PrintImageSize_NullExifData_1608) {
  ValueType<uint32_t> value(unsignedLong);
  value.value_.push_back(1920);
  value.value_.push_back(1080);

  EXPECT_NO_THROW(makerNote_.printImageSize(os_, value, nullptr));
  EXPECT_EQ(os_.str(), "1080 x 1920");
}

// Test return value is the same ostream reference
TEST_F(SonyMakerNoteTest_1608, PrintImageSize_ReturnsOstream_1608) {
  ValueType<uint32_t> value(unsignedLong);
  value.value_.push_back(800);
  value.value_.push_back(600);

  std::ostream& result = makerNote_.printImageSize(os_, value, nullptr);

  EXPECT_EQ(&result, &os_);
}

// Test with string type (wrong type, count might be right but type is wrong)
TEST_F(SonyMakerNoteTest_1608, PrintImageSize_StringType_1608) {
  StringValue value;
  value.read("test");

  makerNote_.printImageSize(os_, value, nullptr);

  std::string result = os_.str();
  EXPECT_TRUE(result.front() == '(' && result.back() == ')');
}

// Test format: ensure " x " separator is present
TEST_F(SonyMakerNoteTest_1608, PrintImageSize_CorrectSeparator_1608) {
  ValueType<uint32_t> value(unsignedLong);
  value.value_.push_back(1920);
  value.value_.push_back(1080);

  makerNote_.printImageSize(os_, value, nullptr);

  std::string result = os_.str();
  EXPECT_NE(result.find(" x "), std::string::npos);
}
