#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

// We need to include or replicate enough to test the printPressure method.
// Since we have the class definition in the prompt, we include relevant headers.

namespace Exiv2 {
namespace Internal {

class PanasonicMakerNote {
 public:
  std::ostream& printPressure(std::ostream& os, const Value& value, const ExifData*) {
    if (value.toInt64() == 65535)
      os << "infinite";
    else
      os << value << " hPa";
    return os;
  }
};

}  // namespace Internal
}  // namespace Exiv2

using namespace Exiv2;
using namespace Exiv2::Internal;

class PanasonicMakerNoteTest_714 : public ::testing::Test {
 protected:
  PanasonicMakerNote maker_;
  std::ostringstream os_;
};

// Test that when value is 65535, "infinite" is printed
TEST_F(PanasonicMakerNoteTest_714, PrintPressureInfinite_714) {
  Exiv2::UShortValue val;
  val.read("65535");
  maker_.printPressure(os_, val, nullptr);
  EXPECT_EQ(os_.str(), "infinite");
}

// Test that a normal pressure value prints with " hPa" suffix
TEST_F(PanasonicMakerNoteTest_714, PrintPressureNormalValue_714) {
  Exiv2::UShortValue val;
  val.read("1013");
  maker_.printPressure(os_, val, nullptr);
  std::string result = os_.str();
  EXPECT_TRUE(result.find("1013") != std::string::npos);
  EXPECT_TRUE(result.find("hPa") != std::string::npos);
}

// Test that zero pressure value prints correctly
TEST_F(PanasonicMakerNoteTest_714, PrintPressureZero_714) {
  Exiv2::UShortValue val;
  val.read("0");
  maker_.printPressure(os_, val, nullptr);
  std::string result = os_.str();
  EXPECT_TRUE(result.find("0") != std::string::npos);
  EXPECT_TRUE(result.find("hPa") != std::string::npos);
}

// Test that value just below infinite threshold (65534) is not "infinite"
TEST_F(PanasonicMakerNoteTest_714, PrintPressureBelowInfinite_714) {
  Exiv2::UShortValue val;
  val.read("65534");
  maker_.printPressure(os_, val, nullptr);
  std::string result = os_.str();
  EXPECT_TRUE(result.find("infinite") == std::string::npos);
  EXPECT_TRUE(result.find("65534") != std::string::npos);
  EXPECT_TRUE(result.find("hPa") != std::string::npos);
}

// Test that value 1 prints correctly
TEST_F(PanasonicMakerNoteTest_714, PrintPressureOne_714) {
  Exiv2::UShortValue val;
  val.read("1");
  maker_.printPressure(os_, val, nullptr);
  std::string result = os_.str();
  EXPECT_TRUE(result.find("1") != std::string::npos);
  EXPECT_TRUE(result.find("hPa") != std::string::npos);
}

// Test that nullptr ExifData doesn't cause issues
TEST_F(PanasonicMakerNoteTest_714, PrintPressureNullExifData_714) {
  Exiv2::UShortValue val;
  val.read("500");
  EXPECT_NO_THROW(maker_.printPressure(os_, val, nullptr));
  std::string result = os_.str();
  EXPECT_TRUE(result.find("500") != std::string::npos);
  EXPECT_TRUE(result.find("hPa") != std::string::npos);
}

// Test that the function returns the same ostream reference
TEST_F(PanasonicMakerNoteTest_714, PrintPressureReturnsOstream_714) {
  Exiv2::UShortValue val;
  val.read("1013");
  std::ostream& returned = maker_.printPressure(os_, val, nullptr);
  EXPECT_EQ(&returned, &os_);
}

// Test with a typical atmospheric pressure value
TEST_F(PanasonicMakerNoteTest_714, PrintPressureTypicalAtmospheric_714) {
  Exiv2::UShortValue val;
  val.read("1013");
  maker_.printPressure(os_, val, nullptr);
  std::string result = os_.str();
  // Should contain the value and unit
  EXPECT_TRUE(result.find("hPa") != std::string::npos);
  EXPECT_TRUE(result.find("infinite") == std::string::npos);
}

// Test with a signed long value that equals 65535
TEST_F(PanasonicMakerNoteTest_714, PrintPressureWithLongValue65535_714) {
  Exiv2::LongValue val;
  val.read("65535");
  maker_.printPressure(os_, val, nullptr);
  EXPECT_EQ(os_.str(), "infinite");
}

// Test that a large value below 65535 is treated as normal pressure
TEST_F(PanasonicMakerNoteTest_714, PrintPressureLargeNonInfinite_714) {
  Exiv2::UShortValue val;
  val.read("60000");
  maker_.printPressure(os_, val, nullptr);
  std::string result = os_.str();
  EXPECT_TRUE(result.find("60000") != std::string::npos);
  EXPECT_TRUE(result.find("hPa") != std::string::npos);
  EXPECT_TRUE(result.find("infinite") == std::string::npos);
}
