#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>
#include "olympusmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Test fixture for OlympusMakerNote tests
class OlympusMakerNoteTest_890 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// ============================================================
// Tests for tagList functions (returning tag info arrays)
// ============================================================

TEST_F(OlympusMakerNoteTest_890, TagListRd2ReturnsNonNull_890) {
  auto tagList = OlympusMakerNote::tagListRd2();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(OlympusMakerNoteTest_890, TagListReturnsNonNull_890) {
  auto tagList = OlympusMakerNote::tagList();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(OlympusMakerNoteTest_890, TagListCsReturnsNonNull_890) {
  auto tagList = OlympusMakerNote::tagListCs();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(OlympusMakerNoteTest_890, TagListEqReturnsNonNull_890) {
  auto tagList = OlympusMakerNote::tagListEq();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(OlympusMakerNoteTest_890, TagListRdReturnsNonNull_890) {
  auto tagList = OlympusMakerNote::tagListRd();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(OlympusMakerNoteTest_890, TagListIpReturnsNonNull_890) {
  auto tagList = OlympusMakerNote::tagListIp();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(OlympusMakerNoteTest_890, TagListFiReturnsNonNull_890) {
  auto tagList = OlympusMakerNote::tagListFi();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(OlympusMakerNoteTest_890, TagListFeReturnsNonNull_890) {
  auto tagList = OlympusMakerNote::tagListFe();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(OlympusMakerNoteTest_890, TagListRiReturnsNonNull_890) {
  auto tagList = OlympusMakerNote::tagListRi();
  ASSERT_NE(tagList, nullptr);
}

// ============================================================
// Tests for print0x0200 (Special Mode)
// ============================================================

TEST_F(OlympusMakerNoteTest_890, Print0x0200WithThreeValues_890) {
  ULongValue value;
  value.read("0 0 0");
  OlympusMakerNote::print0x0200(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(OlympusMakerNoteTest_890, Print0x0200WithSingleValue_890) {
  ULongValue value;
  value.read("1");
  OlympusMakerNote::print0x0200(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(OlympusMakerNoteTest_890, Print0x0200WithEmptyValue_890) {
  ULongValue value;
  OlympusMakerNote::print0x0200(os, value, nullptr);
  std::string result = os.str();
  // Should produce some output even with empty value
}

// ============================================================
// Tests for print0x0204 (Digital Zoom)
// ============================================================

TEST_F(OlympusMakerNoteTest_890, Print0x0204WithZeroValue_890) {
  URationalValue value;
  value.read("0/10");
  OlympusMakerNote::print0x0204(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(OlympusMakerNoteTest_890, Print0x0204WithNonZeroValue_890) {
  URationalValue value;
  value.read("20/10");
  OlympusMakerNote::print0x0204(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for print0x1015 (White Balance)
// ============================================================

TEST_F(OlympusMakerNoteTest_890, Print0x1015WithTwoValues_890) {
  UShortValue value;
  value.read("0 0");
  OlympusMakerNote::print0x1015(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(OlympusMakerNoteTest_890, Print0x1015WithSingleValue_890) {
  UShortValue value;
  value.read("1");
  OlympusMakerNote::print0x1015(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for print0x0201 (Quality)
// ============================================================

TEST_F(OlympusMakerNoteTest_890, Print0x0201WithKnownQuality_890) {
  UShortValue value;
  value.read("1 0");
  OlympusMakerNote::print0x0201(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(OlympusMakerNoteTest_890, Print0x0201WithSingleValue_890) {
  UShortValue value;
  value.read("3");
  OlympusMakerNote::print0x0201(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for print0x0209 (Camera ID)
// ============================================================

TEST_F(OlympusMakerNoteTest_890, Print0x0209WithEmptyValue_890) {
  UndefinedValue value;
  OlympusMakerNote::print0x0209(os, value, nullptr);
  std::string result = os.str();
  // Should handle empty gracefully
}

// ============================================================
// Tests for printEq0x0301 (Equipment Lens Type)
// ============================================================

TEST_F(OlympusMakerNoteTest_890, PrintEq0x0301WithSixValues_890) {
  UShortValue value;
  value.read("0 0 0 0 0 0");
  OlympusMakerNote::printEq0x0301(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(OlympusMakerNoteTest_890, PrintEq0x0301WithFewerValues_890) {
  UShortValue value;
  value.read("1");
  OlympusMakerNote::printEq0x0301(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for printCs0x0301 (Camera Settings Scene Mode)
// ============================================================

TEST_F(OlympusMakerNoteTest_890, PrintCs0x0301KnownValue_890) {
  UShortValue value;
  value.read("0");
  OlympusMakerNote::printCs0x0301(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(OlympusMakerNoteTest_890, PrintCs0x0301UnknownValue_890) {
  UShortValue value;
  value.read("65535");
  OlympusMakerNote::printCs0x0301(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for print0x050f (Sensor Temperature)
// ============================================================

TEST_F(OlympusMakerNoteTest_890, Print0x050fNormalValue_890) {
  ShortValue value;
  value.read("25");
  OlympusMakerNote::print0x050f(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for print0x0527 (Olympus Raw Development - Color Space)
// ============================================================

TEST_F(OlympusMakerNoteTest_890, Print0x0527NormalValue_890) {
  UShortValue value;
  value.read("0");
  OlympusMakerNote::print0x0527(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for print0x0529
// ============================================================

TEST_F(OlympusMakerNoteTest_890, Print0x0529WithNullMetadata_890) {
  UShortValue value;
  value.read("0");
  OlympusMakerNote::print0x0529(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(OlympusMakerNoteTest_890, Print0x0529WithMetadata_890) {
  ExifData exifData;
  UShortValue value;
  value.read("1");
  OlympusMakerNote::print0x0529(os, value, &exifData);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for print0x1209
// ============================================================

TEST_F(OlympusMakerNoteTest_890, Print0x1209NormalValue_890) {
  UShortValue value;
  value.read("0");
  OlympusMakerNote::print0x1209(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for print0x0305 (Equipment Teleconverter)
// ============================================================

TEST_F(OlympusMakerNoteTest_890, Print0x0305NormalValue_890) {
  UShortValue value;
  value.read("0");
  OlympusMakerNote::print0x0305(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for print0x0308 (Equipment Flash Model)
// ============================================================

TEST_F(OlympusMakerNoteTest_890, Print0x0308WithNullMetadata_890) {
  UShortValue value;
  value.read("0");
  OlympusMakerNote::print0x0308(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(OlympusMakerNoteTest_890, Print0x0308WithMetadata_890) {
  ExifData exifData;
  UShortValue value;
  value.read("0");
  OlympusMakerNote::print0x0308(os, value, &exifData);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for printGeneric
// ============================================================

TEST_F(OlympusMakerNoteTest_890, PrintGenericSingleValue_890) {
  UShortValue value;
  value.read("42");
  OlympusMakerNote::printGeneric(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(OlympusMakerNoteTest_890, PrintGenericMultipleValues_890) {
  UShortValue value;
  value.read("1 2 3 4 5");
  OlympusMakerNote::printGeneric(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(OlympusMakerNoteTest_890, PrintGenericEmptyValue_890) {
  UShortValue value;
  OlympusMakerNote::printGeneric(os, value, nullptr);
  // Should handle empty value
}

// ============================================================
// Verify stream returns reference correctly
// ============================================================

TEST_F(OlympusMakerNoteTest_890, Print0x0200ReturnsOstream_890) {
  ULongValue value;
  value.read("0 0 0");
  std::ostream& ret = OlympusMakerNote::print0x0200(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(OlympusMakerNoteTest_890, Print0x0204ReturnsOstream_890) {
  URationalValue value;
  value.read("10/10");
  std::ostream& ret = OlympusMakerNote::print0x0204(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(OlympusMakerNoteTest_890, PrintGenericReturnsOstream_890) {
  UShortValue value;
  value.read("1");
  std::ostream& ret = OlympusMakerNote::printGeneric(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(OlympusMakerNoteTest_890, PrintCs0x0301ReturnsOstream_890) {
  UShortValue value;
  value.read("0");
  std::ostream& ret = OlympusMakerNote::printCs0x0301(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(OlympusMakerNoteTest_890, PrintEq0x0301ReturnsOstream_890) {
  UShortValue value;
  value.read("0 0 0 0 0 0");
  std::ostream& ret = OlympusMakerNote::printEq0x0301(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(OlympusMakerNoteTest_890, Print0x050fReturnsOstream_890) {
  ShortValue value;
  value.read("30");
  std::ostream& ret = OlympusMakerNote::print0x050f(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(OlympusMakerNoteTest_890, Print0x0527ReturnsOstream_890) {
  UShortValue value;
  value.read("1");
  std::ostream& ret = OlympusMakerNote::print0x0527(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(OlympusMakerNoteTest_890, Print0x0529ReturnsOstream_890) {
  UShortValue value;
  value.read("0");
  std::ostream& ret = OlympusMakerNote::print0x0529(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(OlympusMakerNoteTest_890, Print0x1209ReturnsOstream_890) {
  UShortValue value;
  value.read("0");
  std::ostream& ret = OlympusMakerNote::print0x1209(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(OlympusMakerNoteTest_890, Print0x0305ReturnsOstream_890) {
  UShortValue value;
  value.read("0");
  std::ostream& ret = OlympusMakerNote::print0x0305(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(OlympusMakerNoteTest_890, Print0x0308ReturnsOstream_890) {
  UShortValue value;
  value.read("0");
  std::ostream& ret = OlympusMakerNote::print0x0308(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(OlympusMakerNoteTest_890, Print0x1015ReturnsOstream_890) {
  UShortValue value;
  value.read("0 0");
  std::ostream& ret = OlympusMakerNote::print0x1015(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(OlympusMakerNoteTest_890, Print0x0201ReturnsOstream_890) {
  UShortValue value;
  value.read("1");
  std::ostream& ret = OlympusMakerNote::print0x0201(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

TEST_F(OlympusMakerNoteTest_890, Print0x0209ReturnsOstream_890) {
  UndefinedValue value;
  std::ostream& ret = OlympusMakerNote::print0x0209(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
}

// ============================================================
// Consistency tests: calling tagList functions multiple times
// ============================================================

TEST_F(OlympusMakerNoteTest_890, TagListRd2ConsistentAcrossCalls_890) {
  auto first = OlympusMakerNote::tagListRd2();
  auto second = OlympusMakerNote::tagListRd2();
  EXPECT_EQ(first, second);
}

TEST_F(OlympusMakerNoteTest_890, TagListConsistentAcrossCalls_890) {
  auto first = OlympusMakerNote::tagList();
  auto second = OlympusMakerNote::tagList();
  EXPECT_EQ(first, second);
}

TEST_F(OlympusMakerNoteTest_890, TagListCsConsistentAcrossCalls_890) {
  auto first = OlympusMakerNote::tagListCs();
  auto second = OlympusMakerNote::tagListCs();
  EXPECT_EQ(first, second);
}

// ============================================================
// Boundary tests for print functions with edge case values
// ============================================================

TEST_F(OlympusMakerNoteTest_890, Print0x0200WithLargeValues_890) {
  ULongValue value;
  value.read("4294967295 4294967295 4294967295");
  OlympusMakerNote::print0x0200(os, value, nullptr);
  std::string result = os.str();
  // Should not crash, may produce unknown or numeric output
  EXPECT_FALSE(result.empty());
}

TEST_F(OlympusMakerNoteTest_890, PrintCs0x0301WithVariousKnownValues_890) {
  // Test a few known scene mode values
  std::vector<std::string> testValues = {"0", "6", "7", "8", "9", "10"};
  for (const auto& tv : testValues) {
    std::ostringstream localOs;
    UShortValue value;
    value.read(tv);
    OlympusMakerNote::printCs0x0301(localOs, value, nullptr);
    EXPECT_FALSE(localOs.str().empty()) << "Failed for value: " << tv;
  }
}

TEST_F(OlympusMakerNoteTest_890, Print0x0204WithOneToOneRatio_890) {
  URationalValue value;
  value.read("10/10");
  OlympusMakerNote::print0x0204(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(OlympusMakerNoteTest_890, Print0x050fNegativeTemperature_890) {
  ShortValue value;
  value.read("-10");
  OlympusMakerNote::print0x050f(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

TEST_F(OlympusMakerNoteTest_890, Print0x050fZeroTemperature_890) {
  ShortValue value;
  value.read("0");
  OlympusMakerNote::print0x050f(os, value, nullptr);
  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}
