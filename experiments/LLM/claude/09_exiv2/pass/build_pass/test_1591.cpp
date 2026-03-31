#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>

// Include internal header for SonyMakerNote
#include "sonymn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class SonyMakerNotePrintAutoHDRStdTest_1591 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// Test: Normal operation with valid unsignedLong value, count==1, low byte=0 (Off), high word=0 (Uncorrected image)
TEST_F(SonyMakerNotePrintAutoHDRStdTest_1591, ValidValue_Off_Uncorrected_1591) {
  auto value = Value::create(unsignedLong);
  // v0 = 0x00000000: low byte = 0 ("Off"), high word (>>16) = 0 ("Uncorrected image")
  value->read("0");
  std::ostringstream os;
  SonyMakerNote::printAutoHDRStd(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_NE(result.find("Off"), std::string::npos);
  EXPECT_NE(result.find("Uncorrected image"), std::string::npos);
}

// Test: Normal operation with Auto HDR and HDR image (good)
TEST_F(SonyMakerNotePrintAutoHDRStdTest_1591, ValidValue_Auto_HDRGood_1591) {
  auto value = Value::create(unsignedLong);
  // low byte = 1 ("Auto"), high word = 1 ("HDR image (good)")
  // v0 = (1 << 16) | 1 = 65537
  value->read("65537");
  std::ostringstream os;
  SonyMakerNote::printAutoHDRStd(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_NE(result.find("Auto"), std::string::npos);
  EXPECT_NE(result.find("HDR image (good)"), std::string::npos);
}

// Test: Normal operation with 1.0 EV and HDR (fail 1)
TEST_F(SonyMakerNotePrintAutoHDRStdTest_1591, ValidValue_1EV_HDRFail1_1591) {
  auto value = Value::create(unsignedLong);
  // low byte = 16 ("1.0 EV"), high word = 2 ("HDR (fail 1)")
  // v0 = (2 << 16) | 16 = 131088
  value->read("131088");
  std::ostringstream os;
  SonyMakerNote::printAutoHDRStd(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_NE(result.find("1.0 EV"), std::string::npos);
  EXPECT_NE(result.find("HDR (fail 1)"), std::string::npos);
}

// Test: Normal operation with 6.0 EV and HDR (fail 2)
TEST_F(SonyMakerNotePrintAutoHDRStdTest_1591, ValidValue_6EV_HDRFail2_1591) {
  auto value = Value::create(unsignedLong);
  // low byte = 26 ("6.0 EV"), high word = 3 ("HDR (fail 2)")
  // v0 = (3 << 16) | 26 = 196634
  value->read("196634");
  std::ostringstream os;
  SonyMakerNote::printAutoHDRStd(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_NE(result.find("6.0 EV"), std::string::npos);
  EXPECT_NE(result.find("HDR (fail 2)"), std::string::npos);
}

// Test: Contains comma separator between the two parts
TEST_F(SonyMakerNotePrintAutoHDRStdTest_1591, OutputContainsCommaSeparator_1591) {
  auto value = Value::create(unsignedLong);
  value->read("65537");
  std::ostringstream os;
  SonyMakerNote::printAutoHDRStd(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_NE(result.find(", "), std::string::npos);
}

// Test: Wrong type (unsignedShort instead of unsignedLong) should produce parenthesized output
TEST_F(SonyMakerNotePrintAutoHDRStdTest_1591, WrongType_UnsignedShort_1591) {
  auto value = Value::create(unsignedShort);
  value->read("0");
  std::ostringstream os;
  SonyMakerNote::printAutoHDRStd(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_NE(result.find("("), std::string::npos);
  EXPECT_NE(result.find(")"), std::string::npos);
}

// Test: Wrong count (multiple values) - should produce parenthesized output
TEST_F(SonyMakerNotePrintAutoHDRStdTest_1591, WrongCount_MultipleValues_1591) {
  auto value = Value::create(unsignedLong);
  value->read("0 1");
  std::ostringstream os;
  SonyMakerNote::printAutoHDRStd(os, *value, nullptr);
  std::string result = os.str();
  // With count != 1, expect parenthesized output
  EXPECT_NE(result.find("("), std::string::npos);
  EXPECT_NE(result.find(")"), std::string::npos);
}

// Test: Wrong type (signedLong) should produce parenthesized output
TEST_F(SonyMakerNotePrintAutoHDRStdTest_1591, WrongType_SignedLong_1591) {
  auto value = Value::create(signedLong);
  value->read("0");
  std::ostringstream os;
  SonyMakerNote::printAutoHDRStd(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_NE(result.find("("), std::string::npos);
  EXPECT_NE(result.find(")"), std::string::npos);
}

// Test: Return value is the same ostream reference
TEST_F(SonyMakerNotePrintAutoHDRStdTest_1591, ReturnsSameOstream_1591) {
  auto value = Value::create(unsignedLong);
  value->read("0");
  std::ostringstream os;
  std::ostream& ret = SonyMakerNote::printAutoHDRStd(os, *value, nullptr);
  EXPECT_EQ(&ret, &os);
}

// Test: Return value is same ostream on error path too
TEST_F(SonyMakerNotePrintAutoHDRStdTest_1591, ReturnsSameOstreamOnError_1591) {
  auto value = Value::create(unsignedShort);
  value->read("0");
  std::ostringstream os;
  std::ostream& ret = SonyMakerNote::printAutoHDRStd(os, *value, nullptr);
  EXPECT_EQ(&ret, &os);
}

// Test: 2.5 EV with Uncorrected image
TEST_F(SonyMakerNotePrintAutoHDRStdTest_1591, ValidValue_2_5EV_Uncorrected_1591) {
  auto value = Value::create(unsignedLong);
  // low byte = 19 ("2.5 EV"), high word = 0 ("Uncorrected image")
  // v0 = 19
  value->read("19");
  std::ostringstream os;
  SonyMakerNote::printAutoHDRStd(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_NE(result.find("2.5 EV"), std::string::npos);
  EXPECT_NE(result.find("Uncorrected image"), std::string::npos);
}

// Test: Unknown low byte value (e.g., 5 not in the table)
TEST_F(SonyMakerNotePrintAutoHDRStdTest_1591, UnknownLowByteValue_1591) {
  auto value = Value::create(unsignedLong);
  // low byte = 5 (not in sonyHDRStdPart1), high word = 0
  value->read("5");
  std::ostringstream os;
  SonyMakerNote::printAutoHDRStd(os, *value, nullptr);
  std::string result = os.str();
  // Should still produce some output (likely "(5)" or similar for unknown tag)
  EXPECT_FALSE(result.empty());
}

// Test: Unknown high word value (e.g., 10 not in sonyHDRStdPart2)
TEST_F(SonyMakerNotePrintAutoHDRStdTest_1591, UnknownHighWordValue_1591) {
  auto value = Value::create(unsignedLong);
  // low byte = 0 ("Off"), high word = 10 (not in sonyHDRStdPart2)
  // v0 = (10 << 16) | 0 = 655360
  value->read("655360");
  std::ostringstream os;
  SonyMakerNote::printAutoHDRStd(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_NE(result.find("Off"), std::string::npos);
  EXPECT_NE(result.find(", "), std::string::npos);
}

// Test: unsignedByte type should produce parenthesized output
TEST_F(SonyMakerNotePrintAutoHDRStdTest_1591, WrongType_UnsignedByte_1591) {
  auto value = Value::create(unsignedByte);
  value->read("0");
  std::ostringstream os;
  SonyMakerNote::printAutoHDRStd(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_NE(result.find("("), std::string::npos);
  EXPECT_NE(result.find(")"), std::string::npos);
}

// Test: 3.0 EV HDR image (good)
TEST_F(SonyMakerNotePrintAutoHDRStdTest_1591, ValidValue_3EV_HDRGood_1591) {
  auto value = Value::create(unsignedLong);
  // low byte = 20 ("3.0 EV"), high word = 1 ("HDR image (good)")
  // v0 = (1 << 16) | 20 = 65556
  value->read("65556");
  std::ostringstream os;
  SonyMakerNote::printAutoHDRStd(os, *value, nullptr);
  std::string result = os.str();
  EXPECT_NE(result.find("3.0 EV"), std::string::npos);
  EXPECT_NE(result.find("HDR image (good)"), std::string::npos);
}

// Test: With non-null ExifData (nullptr is fine but test with actual ExifData too)
TEST_F(SonyMakerNotePrintAutoHDRStdTest_1591, ValidWithExifData_1591) {
  auto value = Value::create(unsignedLong);
  value->read("0");
  ExifData exifData;
  std::ostringstream os;
  SonyMakerNote::printAutoHDRStd(os, *value, &exifData);
  std::string result = os.str();
  EXPECT_NE(result.find("Off"), std::string::npos);
  EXPECT_NE(result.find("Uncorrected image"), std::string::npos);
}
