#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include <exiv2/exiv2.hpp>
#include "canonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class CanonMakerNoteTest_950 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// Test that a non-unsignedShort type value produces parenthesized output
TEST_F(CanonMakerNoteTest_950, PrintCsLensType_NonUnsignedShortType_950) {
  // Create a value with a type that is NOT unsignedShort (e.g., asciiString)
  Value::UniquePtr val = Value::create(asciiString);
  val->read("test");

  std::ostringstream result;
  CanonMakerNote::printCsLensType(result, *val, nullptr);

  std::string output = result.str();
  // Should be surrounded by parentheses since typeId != unsignedShort
  EXPECT_TRUE(output.find("(") != std::string::npos);
  EXPECT_TRUE(output.find(")") != std::string::npos);
}

// Test that an empty unsignedShort value produces parenthesized output
TEST_F(CanonMakerNoteTest_950, PrintCsLensType_EmptyUnsignedShort_950) {
  Value::UniquePtr val = Value::create(unsignedShort);
  // Don't read any data, so count() == 0

  std::ostringstream result;
  CanonMakerNote::printCsLensType(result, *val, nullptr);

  std::string output = result.str();
  EXPECT_TRUE(output.find("(") != std::string::npos);
  EXPECT_TRUE(output.find(")") != std::string::npos);
}

// Test with a valid unsignedShort value and nullptr metadata
TEST_F(CanonMakerNoteTest_950, PrintCsLensType_ValidUnsignedShort_NullMetadata_950) {
  Value::UniquePtr val = Value::create(unsignedShort);
  val->read("1");

  std::ostringstream result;
  CanonMakerNote::printCsLensType(result, *val, nullptr);

  std::string output = result.str();
  // Should produce some output (either from config or from metadata fallback)
  EXPECT_FALSE(output.empty());
}

// Test with a valid unsignedShort value and empty ExifData
TEST_F(CanonMakerNoteTest_950, PrintCsLensType_ValidUnsignedShort_EmptyExifData_950) {
  Value::UniquePtr val = Value::create(unsignedShort);
  val->read("0");

  ExifData exifData;
  std::ostringstream result;
  CanonMakerNote::printCsLensType(result, *val, &exifData);

  std::string output = result.str();
  EXPECT_FALSE(output.empty());
}

// Test with signedShort type (not unsignedShort) should produce parenthesized output
TEST_F(CanonMakerNoteTest_950, PrintCsLensType_SignedShortType_950) {
  Value::UniquePtr val = Value::create(signedShort);
  val->read("42");

  std::ostringstream result;
  CanonMakerNote::printCsLensType(result, *val, nullptr);

  std::string output = result.str();
  EXPECT_TRUE(output.find("(") != std::string::npos);
  EXPECT_TRUE(output.find(")") != std::string::npos);
}

// Test with unsignedLong type should produce parenthesized output
TEST_F(CanonMakerNoteTest_950, PrintCsLensType_UnsignedLongType_950) {
  Value::UniquePtr val = Value::create(unsignedLong);
  val->read("100");

  std::ostringstream result;
  CanonMakerNote::printCsLensType(result, *val, nullptr);

  std::string output = result.str();
  EXPECT_TRUE(output.find("(") != std::string::npos);
  EXPECT_TRUE(output.find(")") != std::string::npos);
}

// Test that the return value is the same ostream reference
TEST_F(CanonMakerNoteTest_950, PrintCsLensType_ReturnsOstreamReference_950) {
  Value::UniquePtr val = Value::create(unsignedShort);
  val->read("1");

  std::ostringstream result;
  std::ostream& returned = CanonMakerNote::printCsLensType(result, *val, nullptr);

  EXPECT_EQ(&returned, &result);
}

// Test with non-unsignedShort that return is still the same ostream
TEST_F(CanonMakerNoteTest_950, PrintCsLensType_NonUnsignedShort_ReturnsOstreamReference_950) {
  Value::UniquePtr val = Value::create(asciiString);
  val->read("hello");

  std::ostringstream result;
  std::ostream& returned = CanonMakerNote::printCsLensType(result, *val, nullptr);

  EXPECT_EQ(&returned, &result);
}

// Test with a large unsignedShort value
TEST_F(CanonMakerNoteTest_950, PrintCsLensType_LargeUnsignedShortValue_950) {
  Value::UniquePtr val = Value::create(unsignedShort);
  val->read("65535");

  std::ostringstream result;
  CanonMakerNote::printCsLensType(result, *val, nullptr);

  std::string output = result.str();
  EXPECT_FALSE(output.empty());
}

// Test with multiple unsignedShort values (count > 1)
TEST_F(CanonMakerNoteTest_950, PrintCsLensType_MultipleUnsignedShortValues_950) {
  Value::UniquePtr val = Value::create(unsignedShort);
  val->read("1 2 3");

  std::ostringstream result;
  CanonMakerNote::printCsLensType(result, *val, nullptr);

  std::string output = result.str();
  // count > 0 and type is unsignedShort, so it should not produce parenthesized format
  // (unless the value happens to match the parenthesized branch, which it shouldn't since count > 0)
  EXPECT_FALSE(output.empty());
}

// Test printCsLens with valid value
TEST_F(CanonMakerNoteTest_950, PrintCsLens_ValidInput_950) {
  Value::UniquePtr val = Value::create(unsignedShort);
  val->read("100 200 1 0");

  std::ostringstream result;
  CanonMakerNote::printCsLens(result, *val, nullptr);

  std::string output = result.str();
  // Should produce some output
  EXPECT_FALSE(output.empty());
}

// Test printFocalLength with unsignedShort value
TEST_F(CanonMakerNoteTest_950, PrintFocalLength_ValidInput_950) {
  Value::UniquePtr val = Value::create(unsignedShort);
  val->read("1 2 50 0");

  ExifData exifData;
  std::ostringstream result;
  CanonMakerNote::printFocalLength(result, *val, &exifData);

  std::string output = result.str();
  EXPECT_FALSE(output.empty());
}

// Test printSi0x0001 (ISO speed)
TEST_F(CanonMakerNoteTest_950, PrintSi0x0001_ValidInput_950) {
  Value::UniquePtr val = Value::create(unsignedShort);
  val->read("100");

  std::ostringstream result;
  CanonMakerNote::printSi0x0001(result, *val, nullptr);

  EXPECT_FALSE(result.str().empty());
}

// Test printSi0x0002 with valid value
TEST_F(CanonMakerNoteTest_950, PrintSi0x0002_ValidInput_950) {
  Value::UniquePtr val = Value::create(unsignedShort);
  val->read("160");

  std::ostringstream result;
  CanonMakerNote::printSi0x0002(result, *val, nullptr);

  EXPECT_FALSE(result.str().empty());
}

// Test printFiFocusDistance
TEST_F(CanonMakerNoteTest_950, PrintFiFocusDistance_ValidInput_950) {
  Value::UniquePtr val = Value::create(unsignedShort);
  val->read("500");

  std::ostringstream result;
  CanonMakerNote::printFiFocusDistance(result, *val, nullptr);

  EXPECT_FALSE(result.str().empty());
}

// Test printFiFocusDistance with zero (infinity or unknown)
TEST_F(CanonMakerNoteTest_950, PrintFiFocusDistance_Zero_950) {
  Value::UniquePtr val = Value::create(unsignedShort);
  val->read("0");

  std::ostringstream result;
  CanonMakerNote::printFiFocusDistance(result, *val, nullptr);

  EXPECT_FALSE(result.str().empty());
}

// Test printCs0x0002 with valid value
TEST_F(CanonMakerNoteTest_950, PrintCs0x0002_ValidInput_950) {
  Value::UniquePtr val = Value::create(unsignedShort);
  val->read("50");

  std::ostringstream result;
  CanonMakerNote::printCs0x0002(result, *val, nullptr);

  EXPECT_FALSE(result.str().empty());
}

// Test print0x0008 
TEST_F(CanonMakerNoteTest_950, Print0x0008_ValidInput_950) {
  Value::UniquePtr val = Value::create(unsignedShort);
  val->read("1234");

  std::ostringstream result;
  CanonMakerNote::print0x0008(result, *val, nullptr);

  EXPECT_FALSE(result.str().empty());
}

// Test print0x000c
TEST_F(CanonMakerNoteTest_950, Print0x000c_ValidInput_950) {
  Value::UniquePtr val = Value::create(unsignedLong);
  val->read("123456789");

  ExifData exifData;
  std::ostringstream result;
  CanonMakerNote::print0x000c(result, *val, &exifData);

  EXPECT_FALSE(result.str().empty());
}

// Test that undefined type triggers the parenthesized branch
TEST_F(CanonMakerNoteTest_950, PrintCsLensType_UndefinedType_950) {
  Value::UniquePtr val = Value::create(undefined);
  val->read("01");

  std::ostringstream result;
  CanonMakerNote::printCsLensType(result, *val, nullptr);

  std::string output = result.str();
  EXPECT_TRUE(output.find("(") != std::string::npos);
  EXPECT_TRUE(output.find(")") != std::string::npos);
}
