#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <vector>
#include <cstdint>

// Include necessary Exiv2 headers
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>
#include <exiv2/types.hpp>

// We need to access the class from the internal namespace
namespace Exiv2 {
namespace Internal {

class OlympusMakerNote {
 public:
  std::ostream& print0x0200(std::ostream& os, const Value& value, const ExifData*);
};

}  // namespace Internal
}  // namespace Exiv2

using namespace Exiv2;
using namespace Exiv2::Internal;

class OlympusMakerNoteTest_897 : public ::testing::Test {
 protected:
  OlympusMakerNote maker_;
  std::ostringstream os_;
};

// Helper to create an UnsignedLong value with given entries
static std::unique_ptr<Value> makeULongValue(const std::vector<uint32_t>& vals) {
  auto v = Value::create(unsignedLong);
  for (auto val : vals) {
    std::ostringstream s;
    s << val;
    v->read(s.str());
  }
  return v;
}

// Test: When count != 3, should just print the value as-is
TEST_F(OlympusMakerNoteTest_897, WrongCountPrintsRawValue_897) {
  auto v = makeULongValue({0, 2});
  maker_.print0x0200(os_, *v, nullptr);
  std::string result = os_.str();
  // Should just output the value's default string representation (not decoded)
  EXPECT_FALSE(result.empty());
}

// Test: When type is not unsignedLong, should print raw value
TEST_F(OlympusMakerNoteTest_897, WrongTypePrintsRawValue_897) {
  auto v = Value::create(unsignedShort);
  v->read("0");
  v->read("1");
  v->read("2");
  maker_.print0x0200(os_, *v, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

// Test: l0 == 0 => "Normal", no sequence number, no direction
TEST_F(OlympusMakerNoteTest_897, NormalMode_897) {
  auto v = makeULongValue({0, 5, 1});
  maker_.print0x0200(os_, *v, nullptr);
  std::string result = os_.str();
  EXPECT_NE(result.find("Normal"), std::string::npos);
  // Should NOT contain sequence number or direction
  EXPECT_EQ(result.find("Sequence"), std::string::npos);
}

// Test: l0 == 2 => "Fast", sequence number printed, but NO direction
TEST_F(OlympusMakerNoteTest_897, FastMode_897) {
  auto v = makeULongValue({2, 7, 3});
  maker_.print0x0200(os_, *v, nullptr);
  std::string result = os_.str();
  EXPECT_NE(result.find("Fast"), std::string::npos);
  // Sequence number should be present
  EXPECT_NE(result.find("7"), std::string::npos);
  // Direction should NOT be present because l0 == 2
  EXPECT_EQ(result.find("Left to right"), std::string::npos);
  EXPECT_EQ(result.find("Right to left"), std::string::npos);
  EXPECT_EQ(result.find("Bottom to top"), std::string::npos);
  EXPECT_EQ(result.find("Top to bottom"), std::string::npos);
}

// Test: l0 == 3 => "Panorama", sequence number, and direction printed
TEST_F(OlympusMakerNoteTest_897, PanoramaLeftToRight_897) {
  auto v = makeULongValue({3, 1, 1});
  maker_.print0x0200(os_, *v, nullptr);
  std::string result = os_.str();
  EXPECT_NE(result.find("Panorama"), std::string::npos);
  EXPECT_NE(result.find("1"), std::string::npos);
  EXPECT_NE(result.find("Left to right"), std::string::npos);
}

TEST_F(OlympusMakerNoteTest_897, PanoramaRightToLeft_897) {
  auto v = makeULongValue({3, 2, 2});
  maker_.print0x0200(os_, *v, nullptr);
  std::string result = os_.str();
  EXPECT_NE(result.find("Panorama"), std::string::npos);
  EXPECT_NE(result.find("Right to left"), std::string::npos);
}

TEST_F(OlympusMakerNoteTest_897, PanoramaBottomToTop_897) {
  auto v = makeULongValue({3, 3, 3});
  maker_.print0x0200(os_, *v, nullptr);
  std::string result = os_.str();
  EXPECT_NE(result.find("Panorama"), std::string::npos);
  EXPECT_NE(result.find("Bottom to top"), std::string::npos);
}

TEST_F(OlympusMakerNoteTest_897, PanoramaTopToBottom_897) {
  auto v = makeULongValue({3, 4, 4});
  maker_.print0x0200(os_, *v, nullptr);
  std::string result = os_.str();
  EXPECT_NE(result.find("Panorama"), std::string::npos);
  EXPECT_NE(result.find("Top to bottom"), std::string::npos);
}

// Test: l0 == 3 with unknown direction (l2 not in 1-4)
TEST_F(OlympusMakerNoteTest_897, PanoramaUnknownDirection_897) {
  auto v = makeULongValue({3, 1, 99});
  maker_.print0x0200(os_, *v, nullptr);
  std::string result = os_.str();
  EXPECT_NE(result.find("Panorama"), std::string::npos);
  EXPECT_NE(result.find("(99)"), std::string::npos);
}

// Test: Unknown l0 value (not 0, 2, or 3), should print "(l0)", with sequence and direction
TEST_F(OlympusMakerNoteTest_897, UnknownModeWithDirection_897) {
  auto v = makeULongValue({5, 10, 1});
  maker_.print0x0200(os_, *v, nullptr);
  std::string result = os_.str();
  EXPECT_NE(result.find("(5)"), std::string::npos);
  EXPECT_NE(result.find("10"), std::string::npos);
  EXPECT_NE(result.find("Left to right"), std::string::npos);
}

// Test: l0 == 1 (unknown mode), should print "(1)", sequence number, and direction
TEST_F(OlympusMakerNoteTest_897, UnknownMode1_897) {
  auto v = makeULongValue({1, 3, 2});
  maker_.print0x0200(os_, *v, nullptr);
  std::string result = os_.str();
  EXPECT_NE(result.find("(1)"), std::string::npos);
  EXPECT_NE(result.find("Right to left"), std::string::npos);
}

// Test: Count of 1 element (not 3), should print raw
TEST_F(OlympusMakerNoteTest_897, SingleElementPrintsRaw_897) {
  auto v = makeULongValue({42});
  maker_.print0x0200(os_, *v, nullptr);
  std::string result = os_.str();
  EXPECT_NE(result.find("42"), std::string::npos);
}

// Test: Count of 4 elements (not 3), should print raw
TEST_F(OlympusMakerNoteTest_897, FourElementsPrintsRaw_897) {
  auto v = makeULongValue({0, 1, 2, 3});
  maker_.print0x0200(os_, *v, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

// Test: l0 == 0 with direction value 0 - should still only print "Normal"
TEST_F(OlympusMakerNoteTest_897, NormalModeIgnoresOtherFields_897) {
  auto v = makeULongValue({0, 0, 0});
  maker_.print0x0200(os_, *v, nullptr);
  std::string result = os_.str();
  EXPECT_NE(result.find("Normal"), std::string::npos);
  // No comma, no sequence info
  EXPECT_EQ(result.find(","), std::string::npos);
}

// Test: l0 == 2 (Fast) with sequence number 0
TEST_F(OlympusMakerNoteTest_897, FastModeSequenceZero_897) {
  auto v = makeULongValue({2, 0, 1});
  maker_.print0x0200(os_, *v, nullptr);
  std::string result = os_.str();
  EXPECT_NE(result.find("Fast"), std::string::npos);
  EXPECT_NE(result.find("0"), std::string::npos);
}

// Test: Direction value 0 (unknown direction, should print "(0)")
TEST_F(OlympusMakerNoteTest_897, PanoramaDirectionZero_897) {
  auto v = makeULongValue({3, 1, 0});
  maker_.print0x0200(os_, *v, nullptr);
  std::string result = os_.str();
  EXPECT_NE(result.find("Panorama"), std::string::npos);
  EXPECT_NE(result.find("(0)"), std::string::npos);
}

// Test: ExifData pointer is nullptr - should still work
TEST_F(OlympusMakerNoteTest_897, NullExifDataPointer_897) {
  auto v = makeULongValue({0, 0, 0});
  EXPECT_NO_THROW(maker_.print0x0200(os_, *v, nullptr));
}

// Test: Return value is the same ostream reference
TEST_F(OlympusMakerNoteTest_897, ReturnsOstreamReference_897) {
  auto v = makeULongValue({0, 0, 0});
  std::ostream& result = maker_.print0x0200(os_, *v, nullptr);
  EXPECT_EQ(&result, &os_);
}
