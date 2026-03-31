#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <cstdint>
#include <vector>

// Include necessary Exiv2 headers
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>
#include <exiv2/types.hpp>

// We need to include or replicate the class under test
namespace Exiv2 {
namespace Internal {

class OlympusMakerNote {
 public:
  std::ostream& printCs0x0301(std::ostream& os, const Value& value, const ExifData*);
};

}  // namespace Internal
}  // namespace Exiv2

// Since the implementation is in the .cpp file, we include it to get the actual definition
// For testing purposes, we replicate the implementation from the provided code
#include "olympusmn_int.hpp"

class OlympusMakerNotePrintCs0x0301Test_903 : public ::testing::Test {
 protected:
  Exiv2::Internal::OlympusMakerNote maker_;

  std::string callPrint(const Exiv2::Value& value) {
    std::ostringstream os;
    maker_.printCs0x0301(os, value, nullptr);
    return os.str();
  }
};

// Test: When value type is not unsignedShort, should output value in parentheses
TEST_F(OlympusMakerNotePrintCs0x0301Test_903, NonUnsignedShortType_OutputsParenthesized_903) {
  // Use a string value (not unsignedShort)
  Exiv2::AsciiValue val;
  val.read("test");
  std::string result = callPrint(val);
  EXPECT_NE(result.find("("), std::string::npos);
  EXPECT_NE(result.find(")"), std::string::npos);
}

// Test: When value count is 0 (empty), should output value in parentheses
TEST_F(OlympusMakerNotePrintCs0x0301Test_903, EmptyValue_OutputsParenthesized_903) {
  Exiv2::ValueType<uint16_t> val(Exiv2::unsignedShort);
  // Don't add any values, count should be 0
  std::string result = callPrint(val);
  EXPECT_NE(result.find("("), std::string::npos);
}

// Test: Single value 0 -> "Single AF"
TEST_F(OlympusMakerNotePrintCs0x0301Test_903, SingleValue_FocusMode0_SingleAF_903) {
  Exiv2::ValueType<uint16_t> val(Exiv2::unsignedShort);
  val.value_.push_back(0);
  std::string result = callPrint(val);
  EXPECT_NE(result.find("Single AF"), std::string::npos);
}

// Test: Single value 1 -> "Sequential shooting AF"
TEST_F(OlympusMakerNotePrintCs0x0301Test_903, SingleValue_FocusMode1_SequentialShootingAF_903) {
  Exiv2::ValueType<uint16_t> val(Exiv2::unsignedShort);
  val.value_.push_back(1);
  std::string result = callPrint(val);
  EXPECT_NE(result.find("Sequential shooting AF"), std::string::npos);
}

// Test: Single value 2 -> "Continuous AF"
TEST_F(OlympusMakerNotePrintCs0x0301Test_903, SingleValue_FocusMode2_ContinuousAF_903) {
  Exiv2::ValueType<uint16_t> val(Exiv2::unsignedShort);
  val.value_.push_back(2);
  std::string result = callPrint(val);
  EXPECT_NE(result.find("Continuous AF"), std::string::npos);
}

// Test: Single value 3 -> "Multi AF"
TEST_F(OlympusMakerNotePrintCs0x0301Test_903, SingleValue_FocusMode3_MultiAF_903) {
  Exiv2::ValueType<uint16_t> val(Exiv2::unsignedShort);
  val.value_.push_back(3);
  std::string result = callPrint(val);
  EXPECT_NE(result.find("Multi AF"), std::string::npos);
}

// Test: Single value 4 -> "Face detect"
TEST_F(OlympusMakerNotePrintCs0x0301Test_903, SingleValue_FocusMode4_FaceDetect_903) {
  Exiv2::ValueType<uint16_t> val(Exiv2::unsignedShort);
  val.value_.push_back(4);
  std::string result = callPrint(val);
  EXPECT_NE(result.find("Face detect"), std::string::npos);
}

// Test: Single value 10 -> "MF"
TEST_F(OlympusMakerNotePrintCs0x0301Test_903, SingleValue_FocusMode10_MF_903) {
  Exiv2::ValueType<uint16_t> val(Exiv2::unsignedShort);
  val.value_.push_back(10);
  std::string result = callPrint(val);
  EXPECT_NE(result.find("MF"), std::string::npos);
}

// Test: Single value with unknown mode (e.g., 5) should just output the numeric value
TEST_F(OlympusMakerNotePrintCs0x0301Test_903, SingleValue_UnknownFocusMode_JustOutputsValue_903) {
  Exiv2::ValueType<uint16_t> val(Exiv2::unsignedShort);
  val.value_.push_back(5);
  std::string result = callPrint(val);
  EXPECT_NE(result.find("5"), std::string::npos);
  // Should not contain any known label
  EXPECT_EQ(result.find("Single AF"), std::string::npos);
  EXPECT_EQ(result.find("Sequential"), std::string::npos);
  EXPECT_EQ(result.find("Continuous"), std::string::npos);
  EXPECT_EQ(result.find("Multi AF"), std::string::npos);
  EXPECT_EQ(result.find("Face detect"), std::string::npos);
  EXPECT_EQ(result.find("MF"), std::string::npos);
}

// Test: Two values, second value 0x0001 -> "S-AF"
TEST_F(OlympusMakerNotePrintCs0x0301Test_903, TwoValues_SAF_903) {
  Exiv2::ValueType<uint16_t> val(Exiv2::unsignedShort);
  val.value_.push_back(0);      // first value (ignored in multi-value path for label)
  val.value_.push_back(0x0001); // S-AF
  std::string result = callPrint(val);
  EXPECT_NE(result.find("S-AF"), std::string::npos);
}

// Test: Two values, second value 0x0004 -> "C-AF"
TEST_F(OlympusMakerNotePrintCs0x0301Test_903, TwoValues_CAF_903) {
  Exiv2::ValueType<uint16_t> val(Exiv2::unsignedShort);
  val.value_.push_back(0);
  val.value_.push_back(0x0004);
  std::string result = callPrint(val);
  EXPECT_NE(result.find("C-AF"), std::string::npos);
}

// Test: Two values, second value 0x0010 -> "MF"
TEST_F(OlympusMakerNotePrintCs0x0301Test_903, TwoValues_MF_903) {
  Exiv2::ValueType<uint16_t> val(Exiv2::unsignedShort);
  val.value_.push_back(0);
  val.value_.push_back(0x0010);
  std::string result = callPrint(val);
  EXPECT_NE(result.find("MF"), std::string::npos);
}

// Test: Two values, second value 0x0020 -> "Face detect"
TEST_F(OlympusMakerNotePrintCs0x0301Test_903, TwoValues_FaceDetect_903) {
  Exiv2::ValueType<uint16_t> val(Exiv2::unsignedShort);
  val.value_.push_back(0);
  val.value_.push_back(0x0020);
  std::string result = callPrint(val);
  EXPECT_NE(result.find("Face detect"), std::string::npos);
}

// Test: Two values, second value 0x0040 -> "Imager AF"
TEST_F(OlympusMakerNotePrintCs0x0301Test_903, TwoValues_ImagerAF_903) {
  Exiv2::ValueType<uint16_t> val(Exiv2::unsignedShort);
  val.value_.push_back(0);
  val.value_.push_back(0x0040);
  std::string result = callPrint(val);
  EXPECT_NE(result.find("Imager AF"), std::string::npos);
}

// Test: Two values, second value 0x0100 -> "AF sensor"
TEST_F(OlympusMakerNotePrintCs0x0301Test_903, TwoValues_AFSensor_903) {
  Exiv2::ValueType<uint16_t> val(Exiv2::unsignedShort);
  val.value_.push_back(0);
  val.value_.push_back(0x0100);
  std::string result = callPrint(val);
  EXPECT_NE(result.find("AF sensor"), std::string::npos);
}

// Test: Two values with multiple bits set -> comma-separated labels
TEST_F(OlympusMakerNotePrintCs0x0301Test_903, TwoValues_MultipleBitsSet_CommaSeparated_903) {
  Exiv2::ValueType<uint16_t> val(Exiv2::unsignedShort);
  val.value_.push_back(0);
  val.value_.push_back(0x0005); // S-AF (0x0001) | C-AF (0x0004)
  std::string result = callPrint(val);
  EXPECT_NE(result.find("S-AF"), std::string::npos);
  EXPECT_NE(result.find("C-AF"), std::string::npos);
  EXPECT_NE(result.find(", "), std::string::npos);
}

// Test: Two values with all bits set
TEST_F(OlympusMakerNotePrintCs0x0301Test_903, TwoValues_AllBitsSet_903) {
  Exiv2::ValueType<uint16_t> val(Exiv2::unsignedShort);
  val.value_.push_back(0);
  val.value_.push_back(0x0175); // 0x0001|0x0004|0x0010|0x0020|0x0040|0x0100
  std::string result = callPrint(val);
  EXPECT_NE(result.find("S-AF"), std::string::npos);
  EXPECT_NE(result.find("C-AF"), std::string::npos);
  EXPECT_NE(result.find("MF"), std::string::npos);
  EXPECT_NE(result.find("Face detect"), std::string::npos);
  EXPECT_NE(result.find("Imager AF"), std::string::npos);
  EXPECT_NE(result.find("AF sensor"), std::string::npos);
}

// Test: Two values, second value 0 -> no labels, just outputs the numeric value 0
TEST_F(OlympusMakerNotePrintCs0x0301Test_903, TwoValues_NoBitsSet_903) {
  Exiv2::ValueType<uint16_t> val(Exiv2::unsignedShort);
  val.value_.push_back(0);
  val.value_.push_back(0);
  std::string result = callPrint(val);
  EXPECT_NE(result.find("0"), std::string::npos);
  // Should not contain any mode label
  EXPECT_EQ(result.find("S-AF"), std::string::npos);
  EXPECT_EQ(result.find("C-AF"), std::string::npos);
}

// Test: Two values, second value with unrecognized bits only
TEST_F(OlympusMakerNotePrintCs0x0301Test_903, TwoValues_UnrecognizedBitsOnly_903) {
  Exiv2::ValueType<uint16_t> val(Exiv2::unsignedShort);
  val.value_.push_back(0);
  val.value_.push_back(0x0200); // Not in focusModes1
  std::string result = callPrint(val);
  EXPECT_NE(result.find("512"), std::string::npos); // 0x0200 = 512
}

// Test: The output always ends with the numeric value of v
TEST_F(OlympusMakerNotePrintCs0x0301Test_903, SingleValue_OutputEndsWithNumericValue_903) {
  Exiv2::ValueType<uint16_t> val(Exiv2::unsignedShort);
  val.value_.push_back(3);
  std::string result = callPrint(val);
  // The function always appends 'v' at the end: os << v
  // For single value path, v = value.toInt64(0) = 3
  EXPECT_NE(result.find("3"), std::string::npos);
}

// Test: Two values, numeric value of second element is always appended
TEST_F(OlympusMakerNotePrintCs0x0301Test_903, TwoValues_NumericValueAppended_903) {
  Exiv2::ValueType<uint16_t> val(Exiv2::unsignedShort);
  val.value_.push_back(0);
  val.value_.push_back(0x0001);
  std::string result = callPrint(val);
  // v = 0x0001 = 1, should appear
  EXPECT_NE(result.find("1"), std::string::npos);
}

// Test: Passing signed short type should output parenthesized
TEST_F(OlympusMakerNotePrintCs0x0301Test_903, SignedShortType_OutputsParenthesized_903) {
  Exiv2::ValueType<int16_t> val(Exiv2::signedShort);
  val.value_.push_back(1);
  std::string result = callPrint(val);
  EXPECT_NE(result.find("("), std::string::npos);
  EXPECT_NE(result.find(")"), std::string::npos);
}

// Test: Three values - still uses multi-value path (count > 1)
TEST_F(OlympusMakerNotePrintCs0x0301Test_903, ThreeValues_UsesMultiValuePath_903) {
  Exiv2::ValueType<uint16_t> val(Exiv2::unsignedShort);
  val.value_.push_back(0);
  val.value_.push_back(0x0004); // C-AF
  val.value_.push_back(0xFFFF); // extra value, should be ignored
  std::string result = callPrint(val);
  EXPECT_NE(result.find("C-AF"), std::string::npos);
}
