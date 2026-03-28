#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <exiv2/exiv2.hpp>

// Include internal headers for SonyMakerNote
#include "sonymn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class SonyMakerNoteTest_1589 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// ===========================================================================
// printMultiBurstMode tests
// ===========================================================================

TEST_F(SonyMakerNoteTest_1589, PrintMultiBurstMode_CountNotOne_ReturnsParenthesized_1589) {
  // Create a value with count != 1 and type undefined
  // Using DataValue with undefined type and multiple bytes
  DataValue val(undefined);
  byte data[] = {0x01, 0x02};
  val.read(data, 2, littleEndian);

  // count() should be 2, so should print "(" << value << ")"
  SonyMakerNote::printMultiBurstMode(os, val, nullptr);
  std::string result = os.str();
  EXPECT_EQ(result.front(), '(');
  EXPECT_EQ(result.back(), ')');
}

TEST_F(SonyMakerNoteTest_1589, PrintMultiBurstMode_WrongType_ReturnsParenthesized_1589) {
  // Create a value with count == 1 but type != undefined (e.g., unsignedShort)
  UShortValue val;
  val.read("42");

  EXPECT_EQ(val.count(), 1u);
  EXPECT_NE(val.typeId(), undefined);

  SonyMakerNote::printMultiBurstMode(os, val, nullptr);
  std::string result = os.str();
  EXPECT_EQ(result.front(), '(');
  EXPECT_EQ(result.back(), ')');
}

TEST_F(SonyMakerNoteTest_1589, PrintMultiBurstMode_ValidZero_1589) {
  // Create a value with count == 1 and type undefined, value = 0
  DataValue val(undefined);
  byte data[] = {0x00};
  val.read(data, 1, littleEndian);

  EXPECT_EQ(val.count(), 1u);
  EXPECT_EQ(val.typeId(), undefined);

  SonyMakerNote::printMultiBurstMode(os, val, nullptr);
  std::string result = os.str();
  // For bool value 0, printMinoltaSonyBoolValue should print "Off" or similar
  EXPECT_FALSE(result.empty());
  // Should NOT be parenthesized
  EXPECT_NE(result.front(), '(');
}

TEST_F(SonyMakerNoteTest_1589, PrintMultiBurstMode_ValidOne_1589) {
  // Create a value with count == 1 and type undefined, value = 1
  DataValue val(undefined);
  byte data[] = {0x01};
  val.read(data, 1, littleEndian);

  EXPECT_EQ(val.count(), 1u);
  EXPECT_EQ(val.typeId(), undefined);

  SonyMakerNote::printMultiBurstMode(os, val, nullptr);
  std::string result = os.str();
  // For bool value 1, printMinoltaSonyBoolValue should print "On" or similar
  EXPECT_FALSE(result.empty());
  EXPECT_NE(result.front(), '(');
}

TEST_F(SonyMakerNoteTest_1589, PrintMultiBurstMode_NullMetadata_1589) {
  // Null metadata should still work for valid input
  DataValue val(undefined);
  byte data[] = {0x00};
  val.read(data, 1, littleEndian);

  SonyMakerNote::printMultiBurstMode(os, val, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(SonyMakerNoteTest_1589, PrintMultiBurstMode_ReturnsOstream_1589) {
  // Verify it returns the same ostream reference
  DataValue val(undefined);
  byte data[] = {0x00};
  val.read(data, 1, littleEndian);

  std::ostream& ret = SonyMakerNote::printMultiBurstMode(os, val, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(SonyMakerNoteTest_1589, PrintMultiBurstMode_WrongTypeReturnsOstream_1589) {
  // Verify it returns the same ostream reference even for error path
  UShortValue val;
  val.read("42");

  std::ostream& ret = SonyMakerNote::printMultiBurstMode(os, val, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(SonyMakerNoteTest_1589, PrintMultiBurstMode_EmptyUndefinedValue_1589) {
  // Create undefined value with no data - count should be 0
  DataValue val(undefined);
  // Don't read any data - count should be 0

  SonyMakerNote::printMultiBurstMode(os, val, nullptr);
  std::string result = os.str();
  // count != 1, so should get parenthesized form
  EXPECT_EQ(result.front(), '(');
  EXPECT_EQ(result.back(), ')');
}

TEST_F(SonyMakerNoteTest_1589, PrintMultiBurstMode_WithExifData_1589) {
  // Test with actual ExifData object (not null)
  ExifData exifData;
  DataValue val(undefined);
  byte data[] = {0x01};
  val.read(data, 1, littleEndian);

  SonyMakerNote::printMultiBurstMode(os, val, &exifData);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
  EXPECT_NE(result.front(), '(');
}

TEST_F(SonyMakerNoteTest_1589, PrintMultiBurstMode_LongTypeWrongType_1589) {
  // Test with signedLong type - should fail type check
  LongValue val;
  val.read("1");

  EXPECT_EQ(val.count(), 1u);
  EXPECT_NE(val.typeId(), undefined);

  SonyMakerNote::printMultiBurstMode(os, val, nullptr);
  std::string result = os.str();
  EXPECT_EQ(result.front(), '(');
  EXPECT_EQ(result.back(), ')');
}

// ===========================================================================
// printMultiBurstSize tests
// ===========================================================================

TEST_F(SonyMakerNoteTest_1589, PrintMultiBurstSize_NullMetadata_1589) {
  DataValue val(undefined);
  byte data[] = {0x00};
  val.read(data, 1, littleEndian);

  std::ostream& ret = SonyMakerNote::printMultiBurstSize(os, val, nullptr);
  EXPECT_EQ(&ret, &os);
  EXPECT_FALSE(os.str().empty());
}

// ===========================================================================
// printWhiteBalanceFineTune tests
// ===========================================================================

TEST_F(SonyMakerNoteTest_1589, PrintWhiteBalanceFineTune_ReturnsOstream_1589) {
  DataValue val(undefined);
  byte data[] = {0x00};
  val.read(data, 1, littleEndian);

  std::ostream& ret = SonyMakerNote::printWhiteBalanceFineTune(os, val, nullptr);
  EXPECT_EQ(&ret, &os);
}

// ===========================================================================
// printAutoHDRStd tests
// ===========================================================================

TEST_F(SonyMakerNoteTest_1589, PrintAutoHDRStd_ReturnsOstream_1589) {
  DataValue val(undefined);
  byte data[] = {0x00};
  val.read(data, 1, littleEndian);

  std::ostream& ret = SonyMakerNote::printAutoHDRStd(os, val, nullptr);
  EXPECT_EQ(&ret, &os);
}

// ===========================================================================
// printColorTemperature tests
// ===========================================================================

TEST_F(SonyMakerNoteTest_1589, PrintColorTemperature_ReturnsOstream_1589) {
  DataValue val(undefined);
  byte data[] = {0x00};
  val.read(data, 1, littleEndian);

  std::ostream& ret = SonyMakerNote::printColorTemperature(os, val, nullptr);
  EXPECT_EQ(&ret, &os);
}

// ===========================================================================
// printSonyMisc3cSequenceNumber tests
// ===========================================================================

TEST_F(SonyMakerNoteTest_1589, PrintSonyMisc3cSequenceNumber_ReturnsOstream_1589) {
  DataValue val(undefined);
  byte data[] = {0x00};
  val.read(data, 1, littleEndian);

  std::ostream& ret = SonyMakerNote::printSonyMisc3cSequenceNumber(os, val, nullptr);
  EXPECT_EQ(&ret, &os);
}

// ===========================================================================
// printMultiBurstMode additional boundary tests
// ===========================================================================

TEST_F(SonyMakerNoteTest_1589, PrintMultiBurstMode_HighByteValue_1589) {
  // Test with byte value 0xFF
  DataValue val(undefined);
  byte data[] = {0xFF};
  val.read(data, 1, littleEndian);

  SonyMakerNote::printMultiBurstMode(os, val, nullptr);
  std::string result = os.str();
  // count==1 and type==undefined, so should go through printMinoltaSonyBoolValue
  EXPECT_FALSE(result.empty());
}

TEST_F(SonyMakerNoteTest_1589, PrintMultiBurstMode_ThreeBytes_1589) {
  // Multiple bytes - count != 1
  DataValue val(undefined);
  byte data[] = {0x01, 0x02, 0x03};
  val.read(data, 3, littleEndian);

  SonyMakerNote::printMultiBurstMode(os, val, nullptr);
  std::string result = os.str();
  EXPECT_EQ(result.front(), '(');
  EXPECT_EQ(result.back(), ')');
}
