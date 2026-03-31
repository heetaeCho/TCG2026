#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

// We need access to the class under test
namespace Exiv2 {
namespace Internal {
class Nikon3MakerNote {
 public:
  std::ostream& printFlashZoomHeadPosition(std::ostream& os, const Value& value, const ExifData*);
};
}  // namespace Internal
}  // namespace Exiv2

// Include necessary headers for the implementation
// Since we're treating this as a black box, we rely on the interface

using namespace Exiv2;
using namespace Exiv2::Internal;

class Nikon3MakerNoteTest_502 : public ::testing::Test {
 protected:
  Nikon3MakerNote maker_note_;
  std::ostringstream os_;
};

// Test: Single unsignedByte value with non-zero value should print "{value} mm"
TEST_F(Nikon3MakerNoteTest_502, FlashZoomHeadPosition_NonZeroValue_502) {
  auto value = Value::create(unsignedByte);
  value->read("24");
  maker_note_.printFlashZoomHeadPosition(os_, *value, nullptr);
  EXPECT_EQ(os_.str(), "24 mm");
}

// Test: Single unsignedByte value with zero should print "n/a"
TEST_F(Nikon3MakerNoteTest_502, FlashZoomHeadPosition_ZeroValue_502) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  maker_note_.printFlashZoomHeadPosition(os_, *value, nullptr);
  // n/a might be localized, but in default locale it should be "n/a"
  EXPECT_NE(os_.str().find("n/a"), std::string::npos);
}

// Test: Value with count != 1 should print "(value)" format
TEST_F(Nikon3MakerNoteTest_502, FlashZoomHeadPosition_MultipleValues_502) {
  auto value = Value::create(unsignedByte);
  value->read("24 48");
  maker_note_.printFlashZoomHeadPosition(os_, *value, nullptr);
  std::string result = os_.str();
  EXPECT_EQ(result.front(), '(');
  EXPECT_EQ(result.back(), ')');
}

// Test: Value with wrong type (not unsignedByte) should print "(value)" format
TEST_F(Nikon3MakerNoteTest_502, FlashZoomHeadPosition_WrongType_502) {
  auto value = Value::create(unsignedShort);
  value->read("24");
  maker_note_.printFlashZoomHeadPosition(os_, *value, nullptr);
  std::string result = os_.str();
  EXPECT_EQ(result.front(), '(');
  EXPECT_EQ(result.back(), ')');
}

// Test: Single unsignedByte with value 1 (boundary non-zero)
TEST_F(Nikon3MakerNoteTest_502, FlashZoomHeadPosition_ValueOne_502) {
  auto value = Value::create(unsignedByte);
  value->read("1");
  maker_note_.printFlashZoomHeadPosition(os_, *value, nullptr);
  EXPECT_EQ(os_.str(), "1 mm");
}

// Test: Single unsignedByte with max value 255
TEST_F(Nikon3MakerNoteTest_502, FlashZoomHeadPosition_MaxByte_502) {
  auto value = Value::create(unsignedByte);
  value->read("255");
  maker_note_.printFlashZoomHeadPosition(os_, *value, nullptr);
  EXPECT_EQ(os_.str(), "255 mm");
}

// Test: Passing nullptr for ExifData should still work
TEST_F(Nikon3MakerNoteTest_502, FlashZoomHeadPosition_NullExifData_502) {
  auto value = Value::create(unsignedByte);
  value->read("50");
  maker_note_.printFlashZoomHeadPosition(os_, *value, nullptr);
  EXPECT_EQ(os_.str(), "50 mm");
}

// Test: Wrong type unsignedLong with single count
TEST_F(Nikon3MakerNoteTest_502, FlashZoomHeadPosition_UnsignedLongType_502) {
  auto value = Value::create(unsignedLong);
  value->read("100");
  maker_note_.printFlashZoomHeadPosition(os_, *value, nullptr);
  std::string result = os_.str();
  EXPECT_EQ(result.front(), '(');
  EXPECT_EQ(result.back(), ')');
}

// Test: Empty value (count == 0) should print "(value)" format
TEST_F(Nikon3MakerNoteTest_502, FlashZoomHeadPosition_EmptyValue_502) {
  auto value = Value::create(unsignedByte);
  // Don't read any data, count should be 0
  maker_note_.printFlashZoomHeadPosition(os_, *value, nullptr);
  std::string result = os_.str();
  EXPECT_EQ(result.front(), '(');
  EXPECT_EQ(result.back(), ')');
}

// Test: signedByte type should trigger the wrong type branch
TEST_F(Nikon3MakerNoteTest_502, FlashZoomHeadPosition_SignedByteType_502) {
  auto value = Value::create(signedByte);
  value->read("10");
  maker_note_.printFlashZoomHeadPosition(os_, *value, nullptr);
  std::string result = os_.str();
  EXPECT_EQ(result.front(), '(');
  EXPECT_EQ(result.back(), ')');
}

// Test: Return value is the same ostream reference
TEST_F(Nikon3MakerNoteTest_502, FlashZoomHeadPosition_ReturnsOstream_502) {
  auto value = Value::create(unsignedByte);
  value->read("10");
  std::ostream& ret = maker_note_.printFlashZoomHeadPosition(os_, *value, nullptr);
  EXPECT_EQ(&ret, &os_);
}

// Test: Return value is the same ostream reference for error case
TEST_F(Nikon3MakerNoteTest_502, FlashZoomHeadPosition_ReturnsOstreamOnError_502) {
  auto value = Value::create(unsignedShort);
  value->read("10 20");
  std::ostream& ret = maker_note_.printFlashZoomHeadPosition(os_, *value, nullptr);
  EXPECT_EQ(&ret, &os_);
}
