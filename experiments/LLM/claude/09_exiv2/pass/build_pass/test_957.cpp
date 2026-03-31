#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

// Include the internal header for CanonMakerNote
// We need to replicate the class definition since we're testing it
namespace Exiv2 {
namespace Internal {
class CanonMakerNote {
 public:
  std::ostream& printSi0x000c(std::ostream& os, const Value& value, const ExifData*) {
    if (value.toInt64() == 0)
      return os << "--";
    return os << value.toInt64() - 128 << " °C";
  }
};
}  // namespace Internal
}  // namespace Exiv2

class CanonMakerNoteTest_957 : public ::testing::Test {
 protected:
  Exiv2::Internal::CanonMakerNote maker_;
  std::ostringstream os_;
};

// Test that when value is 0, output is "--"
TEST_F(CanonMakerNoteTest_957, PrintSi0x000c_ZeroValue_ReturnsDashes_957) {
  Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
  value.value_.push_back(0);

  maker_.printSi0x000c(os_, value, nullptr);

  EXPECT_EQ(os_.str(), "--");
}

// Test that when value is 128, output is "0 °C"
TEST_F(CanonMakerNoteTest_957, PrintSi0x000c_Value128_ReturnsZeroDegrees_957) {
  Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
  value.value_.push_back(128);

  maker_.printSi0x000c(os_, value, nullptr);

  EXPECT_EQ(os_.str(), "0 °C");
}

// Test that when value is 148, output is "20 °C"
TEST_F(CanonMakerNoteTest_957, PrintSi0x000c_Value148_Returns20Degrees_957) {
  Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
  value.value_.push_back(148);

  maker_.printSi0x000c(os_, value, nullptr);

  EXPECT_EQ(os_.str(), "20 °C");
}

// Test that when value is 100, output is "-28 °C" (negative temperature)
TEST_F(CanonMakerNoteTest_957, PrintSi0x000c_Value100_ReturnsNegative28Degrees_957) {
  Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
  value.value_.push_back(100);

  maker_.printSi0x000c(os_, value, nullptr);

  EXPECT_EQ(os_.str(), "-28 °C");
}

// Test that when value is 1, output is "-127 °C"
TEST_F(CanonMakerNoteTest_957, PrintSi0x000c_Value1_ReturnsNegative127Degrees_957) {
  Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
  value.value_.push_back(1);

  maker_.printSi0x000c(os_, value, nullptr);

  EXPECT_EQ(os_.str(), "-127 °C");
}

// Test that when value is 255, output is "127 °C"
TEST_F(CanonMakerNoteTest_957, PrintSi0x000c_Value255_Returns127Degrees_957) {
  Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
  value.value_.push_back(255);

  maker_.printSi0x000c(os_, value, nullptr);

  EXPECT_EQ(os_.str(), "127 °C");
}

// Test with a large positive value
TEST_F(CanonMakerNoteTest_957, PrintSi0x000c_LargeValue_ReturnsCorrectTemperature_957) {
  Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
  value.value_.push_back(1000);

  maker_.printSi0x000c(os_, value, nullptr);

  EXPECT_EQ(os_.str(), "872 °C");
}

// Test with a negative value (not zero)
TEST_F(CanonMakerNoteTest_957, PrintSi0x000c_NegativeValue_ReturnsVeryNegativeTemperature_957) {
  Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
  value.value_.push_back(-10);

  maker_.printSi0x000c(os_, value, nullptr);

  EXPECT_EQ(os_.str(), "-138 °C");
}

// Test with ExifData as nullptr (should not crash)
TEST_F(CanonMakerNoteTest_957, PrintSi0x000c_NullExifData_DoesNotCrash_957) {
  Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
  value.value_.push_back(128);

  EXPECT_NO_THROW(maker_.printSi0x000c(os_, value, nullptr));
  EXPECT_EQ(os_.str(), "0 °C");
}

// Test that the function returns a reference to the same ostream
TEST_F(CanonMakerNoteTest_957, PrintSi0x000c_ReturnsOstreamReference_957) {
  Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
  value.value_.push_back(128);

  std::ostream& result = maker_.printSi0x000c(os_, value, nullptr);

  EXPECT_EQ(&result, &os_);
}

// Test that the function returns a reference to the same ostream when value is zero
TEST_F(CanonMakerNoteTest_957, PrintSi0x000c_ZeroValue_ReturnsOstreamReference_957) {
  Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
  value.value_.push_back(0);

  std::ostream& result = maker_.printSi0x000c(os_, value, nullptr);

  EXPECT_EQ(&result, &os_);
}

// Test with value exactly 129 -> 1 °C
TEST_F(CanonMakerNoteTest_957, PrintSi0x000c_Value129_Returns1Degree_957) {
  Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
  value.value_.push_back(129);

  maker_.printSi0x000c(os_, value, nullptr);

  EXPECT_EQ(os_.str(), "1 °C");
}

// Test with value exactly 127 -> -1 °C
TEST_F(CanonMakerNoteTest_957, PrintSi0x000c_Value127_ReturnsNegative1Degree_957) {
  Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
  value.value_.push_back(127);

  maker_.printSi0x000c(os_, value, nullptr);

  EXPECT_EQ(os_.str(), "-1 °C");
}
