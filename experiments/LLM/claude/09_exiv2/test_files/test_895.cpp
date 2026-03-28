#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

// We need to include or replicate the class under test
// Since it's in an internal namespace, we include what's needed
namespace Exiv2 {
namespace Internal {
class OlympusMakerNote {
 public:
  std::ostream& print0x050f(std::ostream& os, const Value& value, const ExifData*);
};
}  // namespace Internal
}  // namespace Exiv2

// Re-include the implementation inline since we need the actual function
// In practice, this would be linked from the library
#include "olympusmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class OlympusMakerNoteTest_895 : public ::testing::Test {
 protected:
  OlympusMakerNote maker_;
  std::ostringstream os_;
};

// Test: Normal case - Low Key (count=3, values: -1, -1, 1)
TEST_F(OlympusMakerNoteTest_895, Print050f_LowKey_Count3_895) {
  Exiv2::ValueType<int16_t> value(Exiv2::signedShort);
  value.value_.push_back(-1);
  value.value_.push_back(-1);
  value.value_.push_back(1);

  maker_.print0x050f(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_NE(result.find("Low Key"), std::string::npos) << "Expected 'Low Key' but got: " << result;
}

// Test: Normal case - Normal (count=3, values: 0, -1, 1)
TEST_F(OlympusMakerNoteTest_895, Print050f_Normal_Count3_895) {
  Exiv2::ValueType<int16_t> value(Exiv2::signedShort);
  value.value_.push_back(0);
  value.value_.push_back(-1);
  value.value_.push_back(1);

  maker_.print0x050f(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_NE(result.find("Normal"), std::string::npos) << "Expected 'Normal' but got: " << result;
}

// Test: Normal case - High Key (count=3, values: 1, -1, 1)
TEST_F(OlympusMakerNoteTest_895, Print050f_HighKey_Count3_895) {
  Exiv2::ValueType<int16_t> value(Exiv2::signedShort);
  value.value_.push_back(1);
  value.value_.push_back(-1);
  value.value_.push_back(1);

  maker_.print0x050f(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_NE(result.find("High Key"), std::string::npos) << "Expected 'High Key' but got: " << result;
}

// Test: Normal case - unrecognized combination prints raw values (count=3)
TEST_F(OlympusMakerNoteTest_895, Print050f_UnknownCombination_Count3_895) {
  Exiv2::ValueType<int16_t> value(Exiv2::signedShort);
  value.value_.push_back(2);
  value.value_.push_back(3);
  value.value_.push_back(4);

  maker_.print0x050f(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_EQ(result, "2 3 4");
}

// Test: Count=4 with User-Selected (4th value = 0)
TEST_F(OlympusMakerNoteTest_895, Print050f_Normal_UserSelected_Count4_895) {
  Exiv2::ValueType<int16_t> value(Exiv2::signedShort);
  value.value_.push_back(0);
  value.value_.push_back(-1);
  value.value_.push_back(1);
  value.value_.push_back(0);

  maker_.print0x050f(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_NE(result.find("Normal"), std::string::npos);
  EXPECT_NE(result.find("User-Selected"), std::string::npos);
}

// Test: Count=4 with Auto-Override (4th value = 1)
TEST_F(OlympusMakerNoteTest_895, Print050f_LowKey_AutoOverride_Count4_895) {
  Exiv2::ValueType<int16_t> value(Exiv2::signedShort);
  value.value_.push_back(-1);
  value.value_.push_back(-1);
  value.value_.push_back(1);
  value.value_.push_back(1);

  maker_.print0x050f(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_NE(result.find("Low Key"), std::string::npos);
  EXPECT_NE(result.find("Auto-Override"), std::string::npos);
}

// Test: Count=4 with unknown 4th value (not 0 or 1)
TEST_F(OlympusMakerNoteTest_895, Print050f_HighKey_UnknownFourth_Count4_895) {
  Exiv2::ValueType<int16_t> value(Exiv2::signedShort);
  value.value_.push_back(1);
  value.value_.push_back(-1);
  value.value_.push_back(1);
  value.value_.push_back(5);

  maker_.print0x050f(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_NE(result.find("High Key"), std::string::npos);
  EXPECT_NE(result.find("5"), std::string::npos);
}

// Test: Boundary - wrong count (count=2) should just print value
TEST_F(OlympusMakerNoteTest_895, Print050f_WrongCount2_895) {
  Exiv2::ValueType<int16_t> value(Exiv2::signedShort);
  value.value_.push_back(0);
  value.value_.push_back(-1);

  maker_.print0x050f(os_, value, nullptr);
  std::string result = os_.str();
  // Should print raw value since count != 3 and count != 4
  EXPECT_FALSE(result.empty());
}

// Test: Boundary - wrong count (count=5) should just print value
TEST_F(OlympusMakerNoteTest_895, Print050f_WrongCount5_895) {
  Exiv2::ValueType<int16_t> value(Exiv2::signedShort);
  value.value_.push_back(0);
  value.value_.push_back(-1);
  value.value_.push_back(1);
  value.value_.push_back(0);
  value.value_.push_back(0);

  maker_.print0x050f(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

// Test: Boundary - wrong type (unsignedShort instead of signedShort)
TEST_F(OlympusMakerNoteTest_895, Print050f_WrongType_895) {
  Exiv2::ValueType<uint16_t> value(Exiv2::unsignedShort);
  value.value_.push_back(0);
  value.value_.push_back(static_cast<uint16_t>(-1));
  value.value_.push_back(1);

  maker_.print0x050f(os_, value, nullptr);
  std::string result = os_.str();
  // Wrong type should trigger the early return with raw value
  EXPECT_FALSE(result.empty());
}

// Test: Boundary - count=1 should just print value
TEST_F(OlympusMakerNoteTest_895, Print050f_Count1_895) {
  Exiv2::ValueType<int16_t> value(Exiv2::signedShort);
  value.value_.push_back(42);

  maker_.print0x050f(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

// Test: Count=4, unknown combination with User-Selected
TEST_F(OlympusMakerNoteTest_895, Print050f_UnknownCombination_UserSelected_Count4_895) {
  Exiv2::ValueType<int16_t> value(Exiv2::signedShort);
  value.value_.push_back(5);
  value.value_.push_back(6);
  value.value_.push_back(7);
  value.value_.push_back(0);

  maker_.print0x050f(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_NE(result.find("5 6 7"), std::string::npos);
  EXPECT_NE(result.find("User-Selected"), std::string::npos);
}

// Test: Count=4, unknown combination with Auto-Override
TEST_F(OlympusMakerNoteTest_895, Print050f_UnknownCombination_AutoOverride_Count4_895) {
  Exiv2::ValueType<int16_t> value(Exiv2::signedShort);
  value.value_.push_back(10);
  value.value_.push_back(20);
  value.value_.push_back(30);
  value.value_.push_back(1);

  maker_.print0x050f(os_, value, nullptr);
  std::string result = os_.str();
  EXPECT_NE(result.find("10 20 30"), std::string::npos);
  EXPECT_NE(result.find("Auto-Override"), std::string::npos);
}

// Test: nullptr ExifData pointer is acceptable
TEST_F(OlympusMakerNoteTest_895, Print050f_NullExifData_895) {
  Exiv2::ValueType<int16_t> value(Exiv2::signedShort);
  value.value_.push_back(0);
  value.value_.push_back(-1);
  value.value_.push_back(1);

  // Should not crash with nullptr
  EXPECT_NO_THROW(maker_.print0x050f(os_, value, nullptr));
}

// Test: Empty value (count=0)
TEST_F(OlympusMakerNoteTest_895, Print050f_EmptyValue_895) {
  Exiv2::ValueType<int16_t> value(Exiv2::signedShort);

  maker_.print0x050f(os_, value, nullptr);
  // Count is 0, which is neither 3 nor 4, so raw print
  // Just ensure it doesn't crash
  EXPECT_TRUE(true);
}

// Test: Return value is the same ostream reference
TEST_F(OlympusMakerNoteTest_895, Print050f_ReturnsOstream_895) {
  Exiv2::ValueType<int16_t> value(Exiv2::signedShort);
  value.value_.push_back(0);
  value.value_.push_back(-1);
  value.value_.push_back(1);

  std::ostream& result = maker_.print0x050f(os_, value, nullptr);
  EXPECT_EQ(&result, &os_);
}
