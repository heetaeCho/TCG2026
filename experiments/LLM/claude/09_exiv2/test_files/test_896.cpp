#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

// We need access to the internal class
// Recreate the class interface as provided
namespace Exiv2 {
namespace Internal {
class OlympusMakerNote {
 public:
  std::ostream& print0x0527(std::ostream& os, const Value& value, const ExifData*);
};
}  // namespace Internal
}  // namespace Exiv2

// Include the actual implementation
// Since we have the implementation in the prompt, we include the necessary headers
// and rely on the linker to find the implementation
#include "olympusmn_int.hpp"

// For the translation macro
#ifndef _
#define _(x) x
#endif

using namespace Exiv2;
using namespace Exiv2::Internal;

class OlympusMakerNoteTest_896 : public ::testing::Test {
 protected:
  OlympusMakerNote maker_note_;
  std::ostringstream os_;

  // Helper to create a ShortValue (signed short) with specific values
  Exiv2::Value::UniquePtr createSignedShortValue(std::vector<int16_t> values) {
    auto val = Exiv2::Value::create(Exiv2::signedShort);
    for (auto v : values) {
      std::ostringstream s;
      s << v;
      val->read(s.str());
    }
    return val;
  }

  // Helper to create an unsigned short value
  Exiv2::Value::UniquePtr createUnsignedShortValue(std::vector<uint16_t> values) {
    auto val = Exiv2::Value::create(Exiv2::unsignedShort);
    for (auto v : values) {
      std::ostringstream s;
      s << v;
      val->read(s.str());
    }
    return val;
  }

  // Helper to create a signed long value
  Exiv2::Value::UniquePtr createSignedLongValue(std::vector<int32_t> values) {
    auto val = Exiv2::Value::create(Exiv2::signedLong);
    for (auto v : values) {
      std::ostringstream s;
      s << v;
      val->read(s.str());
    }
    return val;
  }
};

// Test: Standard noise filter value (0, -2, 1) -> "Standard"
TEST_F(OlympusMakerNoteTest_896, StandardNoiseFilter_896) {
  auto val = createSignedShortValue({0, -2, 1});
  maker_note_.print0x0527(os_, *val, nullptr);
  EXPECT_EQ(os_.str(), "Standard");
}

// Test: Off noise filter value (-2, -2, 1) -> "Off"
TEST_F(OlympusMakerNoteTest_896, OffNoiseFilter_896) {
  auto val = createSignedShortValue({-2, -2, 1});
  maker_note_.print0x0527(os_, *val, nullptr);
  EXPECT_EQ(os_.str(), "Off");
}

// Test: Low noise filter value (-1, -2, 1) -> "Low"
TEST_F(OlympusMakerNoteTest_896, LowNoiseFilter_896) {
  auto val = createSignedShortValue({-1, -2, 1});
  maker_note_.print0x0527(os_, *val, nullptr);
  EXPECT_EQ(os_.str(), "Low");
}

// Test: High noise filter value (1, -2, 1) -> "High"
TEST_F(OlympusMakerNoteTest_896, HighNoiseFilter_896) {
  auto val = createSignedShortValue({1, -2, 1});
  maker_note_.print0x0527(os_, *val, nullptr);
  EXPECT_EQ(os_.str(), "High");
}

// Test: Unknown first value with valid structure -> prints the numeric value
TEST_F(OlympusMakerNoteTest_896, UnknownFirstValuePrintsNumeric_896) {
  auto val = createSignedShortValue({5, -2, 1});
  maker_note_.print0x0527(os_, *val, nullptr);
  EXPECT_EQ(os_.str(), "5");
}

// Test: Unknown negative first value with valid structure -> prints the numeric value
TEST_F(OlympusMakerNoteTest_896, UnknownNegativeFirstValuePrintsNumeric_896) {
  auto val = createSignedShortValue({-5, -2, 1});
  maker_note_.print0x0527(os_, *val, nullptr);
  EXPECT_EQ(os_.str(), "-5");
}

// Test: Wrong count (2 elements instead of 3) -> prints raw value
TEST_F(OlympusMakerNoteTest_896, WrongCountTwoElements_896) {
  auto val = createSignedShortValue({0, -2});
  maker_note_.print0x0527(os_, *val, nullptr);
  // Should print the raw value representation, not "Standard"
  std::string result = os_.str();
  EXPECT_NE(result, "Standard");
  EXPECT_NE(result, "Off");
  EXPECT_NE(result, "Low");
  EXPECT_NE(result, "High");
}

// Test: Wrong count (4 elements) -> prints raw value
TEST_F(OlympusMakerNoteTest_896, WrongCountFourElements_896) {
  auto val = createSignedShortValue({0, -2, 1, 3});
  maker_note_.print0x0527(os_, *val, nullptr);
  std::string result = os_.str();
  EXPECT_NE(result, "Standard");
}

// Test: Wrong count (1 element) -> prints raw value
TEST_F(OlympusMakerNoteTest_896, WrongCountOneElement_896) {
  auto val = createSignedShortValue({0});
  maker_note_.print0x0527(os_, *val, nullptr);
  std::string result = os_.str();
  EXPECT_NE(result, "Standard");
}

// Test: Wrong type (unsigned short instead of signed short) -> prints raw value
TEST_F(OlympusMakerNoteTest_896, WrongTypeUnsignedShort_896) {
  auto val = createUnsignedShortValue({0, 0, 1});
  maker_note_.print0x0527(os_, *val, nullptr);
  std::string result = os_.str();
  // Since typeId is unsignedShort instead of signedShort, should fall through to raw printing
  // (Note: behavior depends on whether -2 can be represented; with unsigned, it can't match)
  EXPECT_FALSE(result.empty());
}

// Test: Second element is not -2 -> prints raw value
TEST_F(OlympusMakerNoteTest_896, SecondElementNotNegTwo_896) {
  auto val = createSignedShortValue({0, 0, 1});
  maker_note_.print0x0527(os_, *val, nullptr);
  std::string result = os_.str();
  EXPECT_NE(result, "Standard");
}

// Test: Third element is not 1 -> prints raw value
TEST_F(OlympusMakerNoteTest_896, ThirdElementNotOne_896) {
  auto val = createSignedShortValue({0, -2, 0});
  maker_note_.print0x0527(os_, *val, nullptr);
  std::string result = os_.str();
  EXPECT_NE(result, "Standard");
}

// Test: Both second and third elements wrong -> prints raw value
TEST_F(OlympusMakerNoteTest_896, BothSecondAndThirdWrong_896) {
  auto val = createSignedShortValue({0, 0, 0});
  maker_note_.print0x0527(os_, *val, nullptr);
  std::string result = os_.str();
  EXPECT_NE(result, "Standard");
}

// Test: Wrong type (signed long) with 3 elements -> prints raw value
TEST_F(OlympusMakerNoteTest_896, WrongTypeSignedLong_896) {
  auto val = createSignedLongValue({0, -2, 1});
  maker_note_.print0x0527(os_, *val, nullptr);
  std::string result = os_.str();
  // typeId is signedLong, not signedShort, so should print raw
  EXPECT_FALSE(result.empty());
}

// Test: Return value is the same ostream reference
TEST_F(OlympusMakerNoteTest_896, ReturnsSameOstream_896) {
  auto val = createSignedShortValue({0, -2, 1});
  std::ostream& ret = maker_note_.print0x0527(os_, *val, nullptr);
  EXPECT_EQ(&ret, &os_);
}

// Test: Return value is the same ostream reference for fallback case
TEST_F(OlympusMakerNoteTest_896, ReturnsSameOstreamFallback_896) {
  auto val = createSignedShortValue({0, 0, 0});
  std::ostream& ret = maker_note_.print0x0527(os_, *val, nullptr);
  EXPECT_EQ(&ret, &os_);
}

// Test: Large unknown value in first position
TEST_F(OlympusMakerNoteTest_896, LargeUnknownValue_896) {
  auto val = createSignedShortValue({100, -2, 1});
  maker_note_.print0x0527(os_, *val, nullptr);
  EXPECT_EQ(os_.str(), "100");
}

// Test: Value of 2 in first position (just above High)
TEST_F(OlympusMakerNoteTest_896, ValueTwoDefaultCase_896) {
  auto val = createSignedShortValue({2, -2, 1});
  maker_note_.print0x0527(os_, *val, nullptr);
  EXPECT_EQ(os_.str(), "2");
}

// Test: Value of -3 in first position (just below Off)
TEST_F(OlympusMakerNoteTest_896, ValueNegThreeDefaultCase_896) {
  auto val = createSignedShortValue({-3, -2, 1});
  maker_note_.print0x0527(os_, *val, nullptr);
  EXPECT_EQ(os_.str(), "-3");
}
