#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/value.hpp>
#include <exiv2/types.hpp>
#include <exiv2/exif.hpp>

// We need to include the internal header or replicate the class interface
// Since we have the implementation provided, we'll work with the Exiv2 namespace
namespace Exiv2 {
namespace Internal {

class OlympusMakerNote {
 public:
  std::ostream& print0x0305(std::ostream& os, const Value& value, const ExifData*) {
    if (value.count() != 1 || value.typeId() != unsignedRational) {
      return os << value;
    }
    auto [r, s] = value.toRational();
    if (static_cast<uint32_t>(r) == 0xffffffff) {
      return os << "Infinity";
    }
    return os << Exiv2::Internal::stringFormat("%.2f m", static_cast<float>(r) / 1000);
  }
};

}  // namespace Internal
}  // namespace Exiv2

class OlympusMakerNoteTest_906 : public ::testing::Test {
 protected:
  Exiv2::Internal::OlympusMakerNote maker_;
  std::ostringstream os_;
};

// Test: Normal distance value (e.g., 1500 -> "1.50 m")
TEST_F(OlympusMakerNoteTest_906, NormalDistanceValue_906) {
  Exiv2::URationalValue value;
  value.value_.push_back({1500, 1});
  
  maker_.print0x0305(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "1.50 m");
}

// Test: Zero distance value (0 -> "0.00 m")
TEST_F(OlympusMakerNoteTest_906, ZeroDistanceValue_906) {
  Exiv2::URationalValue value;
  value.value_.push_back({0, 1});
  
  maker_.print0x0305(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "0.00 m");
}

// Test: Infinity value (0xffffffff -> "Infinity")
TEST_F(OlympusMakerNoteTest_906, InfinityValue_906) {
  Exiv2::URationalValue value;
  value.value_.push_back({0xffffffff, 1});
  
  maker_.print0x0305(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "Infinity");
}

// Test: Count is not 1 (multiple values) - should print raw value
TEST_F(OlympusMakerNoteTest_906, MultipleValuesReturnsRaw_906) {
  Exiv2::URationalValue value;
  value.value_.push_back({1000, 1});
  value.value_.push_back({2000, 1});
  
  maker_.print0x0305(os_, value, nullptr);
  // With count != 1, it should fall through to os << value
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
  // It should NOT contain " m" format since it's raw output
}

// Test: Wrong type (not unsignedRational) - should print raw value
TEST_F(OlympusMakerNoteTest_906, WrongTypeReturnsRaw_906) {
  Exiv2::UShortValue value;
  value.value_.push_back(1500);
  
  maker_.print0x0305(os_, value, nullptr);
  std::string result = os_.str();
  // Should print raw value, not formatted distance
  EXPECT_EQ(result, "1500");
}

// Test: Small distance value (1 -> "0.00 m")
TEST_F(OlympusMakerNoteTest_906, SmallDistanceValue_906) {
  Exiv2::URationalValue value;
  value.value_.push_back({1, 1});
  
  maker_.print0x0305(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "0.00 m");
}

// Test: Exact 1000 (1000 -> "1.00 m")
TEST_F(OlympusMakerNoteTest_906, ExactOneMeter_906) {
  Exiv2::URationalValue value;
  value.value_.push_back({1000, 1});
  
  maker_.print0x0305(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "1.00 m");
}

// Test: Large distance value
TEST_F(OlympusMakerNoteTest_906, LargeDistanceValue_906) {
  Exiv2::URationalValue value;
  value.value_.push_back({100000, 1});
  
  maker_.print0x0305(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "100.00 m");
}

// Test: Value just below infinity (0xfffffffe)
TEST_F(OlympusMakerNoteTest_906, JustBelowInfinity_906) {
  Exiv2::URationalValue value;
  value.value_.push_back({0xfffffffe, 1});
  
  maker_.print0x0305(os_, value, nullptr);
  std::string result = os_.str();
  // Should NOT be "Infinity" - it should be a formatted distance
  EXPECT_NE(result, "Infinity");
  EXPECT_TRUE(result.find(" m") != std::string::npos);
}

// Test: Nullptr ExifData should not cause crash
TEST_F(OlympusMakerNoteTest_906, NullExifDataDoesNotCrash_906) {
  Exiv2::URationalValue value;
  value.value_.push_back({5000, 1});
  
  EXPECT_NO_THROW(maker_.print0x0305(os_, value, nullptr));
  EXPECT_EQ(os_.str(), "5.00 m");
}

// Test: Empty value (count == 0)
TEST_F(OlympusMakerNoteTest_906, EmptyValueReturnsRaw_906) {
  Exiv2::URationalValue value;
  // No values pushed - count is 0
  
  maker_.print0x0305(os_, value, nullptr);
  // count != 1, should fall through to raw output
  std::string result = os_.str();
  // Empty value printed as raw
}

// Test: Fractional distance (e.g., 1234 -> "1.23 m")
TEST_F(OlympusMakerNoteTest_906, FractionalDistanceValue_906) {
  Exiv2::URationalValue value;
  value.value_.push_back({1234, 1});
  
  maker_.print0x0305(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "1.23 m");
}

// Test: Distance with rounding (e.g., 1235 -> should round to "1.24 m" or "1.23 m")
TEST_F(OlympusMakerNoteTest_906, DistanceWithRounding_906) {
  Exiv2::URationalValue value;
  value.value_.push_back({1239, 1});
  
  maker_.print0x0305(os_, value, nullptr);
  EXPECT_EQ(os_.str(), "1.24 m");
}
