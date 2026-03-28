#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>
#include "canonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class CanonMakerNoteTest_929 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// ============================================================
// Tests for tagList functions (constexpr tag list accessors)
// ============================================================

TEST_F(CanonMakerNoteTest_929, TagListCiIsNotNull_929) {
  auto result = CanonMakerNote::tagListCi();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_929, TagListIsNotNull_929) {
  auto result = CanonMakerNote::tagList();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_929, TagListCsIsNotNull_929) {
  auto result = CanonMakerNote::tagListCs();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_929, TagListSiIsNotNull_929) {
  auto result = CanonMakerNote::tagListSi();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_929, TagListPaIsNotNull_929) {
  auto result = CanonMakerNote::tagListPa();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_929, TagListCfIsNotNull_929) {
  auto result = CanonMakerNote::tagListCf();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_929, TagListPiIsNotNull_929) {
  auto result = CanonMakerNote::tagListPi();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_929, TagListTiIsNotNull_929) {
  auto result = CanonMakerNote::tagListTi();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_929, TagListFiIsNotNull_929) {
  auto result = CanonMakerNote::tagListFi();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_929, TagListPrIsNotNull_929) {
  auto result = CanonMakerNote::tagListPr();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_929, TagListMvIsNotNull_929) {
  auto result = CanonMakerNote::tagListMv();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_929, TagListMcIsNotNull_929) {
  auto result = CanonMakerNote::tagListMc();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_929, TagListFcd3IsNotNull_929) {
  auto result = CanonMakerNote::tagListFcd3();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_929, TagListWbiIsNotNull_929) {
  auto result = CanonMakerNote::tagListWbi();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_929, TagListCoIsNotNull_929) {
  auto result = CanonMakerNote::tagListCo();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_929, TagListFcd2IsNotNull_929) {
  auto result = CanonMakerNote::tagListFcd2();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_929, TagListFcd1IsNotNull_929) {
  auto result = CanonMakerNote::tagListFcd1();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_929, TagListAsIsNotNull_929) {
  auto result = CanonMakerNote::tagListAs();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_929, TagListCbiIsNotNull_929) {
  auto result = CanonMakerNote::tagListCbi();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_929, TagListFlIsNotNull_929) {
  auto result = CanonMakerNote::tagListFl();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_929, TagListMoIsNotNull_929) {
  auto result = CanonMakerNote::tagListMo();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_929, TagListPreIIsNotNull_929) {
  auto result = CanonMakerNote::tagListPreI();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_929, TagListAfMiAdjIsNotNull_929) {
  auto result = CanonMakerNote::tagListAfMiAdj();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_929, TagListVigCorIsNotNull_929) {
  auto result = CanonMakerNote::tagListVigCor();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_929, TagListVigCor2IsNotNull_929) {
  auto result = CanonMakerNote::tagListVigCor2();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_929, TagListLiOpIsNotNull_929) {
  auto result = CanonMakerNote::tagListLiOp();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_929, TagListLeIsNotNull_929) {
  auto result = CanonMakerNote::tagListLe();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_929, TagListAmIsNotNull_929) {
  auto result = CanonMakerNote::tagListAm();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_929, TagListMeIsNotNull_929) {
  auto result = CanonMakerNote::tagListMe();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_929, TagListFilIsNotNull_929) {
  auto result = CanonMakerNote::tagListFil();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_929, TagListHdrIsNotNull_929) {
  auto result = CanonMakerNote::tagListHdr();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_929, TagListAfCIsNotNull_929) {
  auto result = CanonMakerNote::tagListAfC();
  EXPECT_NE(result, nullptr);
}

TEST_F(CanonMakerNoteTest_929, TagListRawBIsNotNull_929) {
  auto result = CanonMakerNote::tagListRawB();
  EXPECT_NE(result, nullptr);
}

// ============================================================
// Tests for print functions with various Value types
// ============================================================

TEST_F(CanonMakerNoteTest_929, PrintFocalLengthWithSingleValue_929) {
  UShortValue value;
  value.read("100");
  auto& result = CanonMakerNote::printFocalLength(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  // The output should be non-empty or at least the stream should be valid
  // We don't check the exact content as we treat implementation as black box
}

TEST_F(CanonMakerNoteTest_929, PrintFocalLengthWithMultipleValues_929) {
  UShortValue value;
  value.read("0 1 100 0");
  auto& result = CanonMakerNote::printFocalLength(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_929, Print0x0008ReturnsOstream_929) {
  UShortValue value;
  value.read("12345");
  auto& result = CanonMakerNote::print0x0008(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_929, Print0x000aReturnsOstream_929) {
  ULongValue value;
  value.read("12345");
  auto& result = CanonMakerNote::print0x000a(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_929, Print0x000cReturnsOstream_929) {
  ULongValue value;
  value.read("1234567890");
  ExifData exifData;
  auto& result = CanonMakerNote::print0x000c(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_929, Print0x000cWithNullExifData_929) {
  ULongValue value;
  value.read("1234567890");
  auto& result = CanonMakerNote::print0x000c(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_929, PrintCs0x0002ReturnsOstream_929) {
  UShortValue value;
  value.read("100");
  auto& result = CanonMakerNote::printCs0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_929, PrintCsLensTypeReturnsOstream_929) {
  UShortValue value;
  value.read("1");
  auto& result = CanonMakerNote::printCsLensType(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_929, PrintCsLensReturnsOstream_929) {
  UShortValue value;
  value.read("100 24 70");
  auto& result = CanonMakerNote::printCsLens(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_929, PrintCsLensWithSingleValue_929) {
  UShortValue value;
  value.read("100");
  auto& result = CanonMakerNote::printCsLens(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_929, PrintLe0x0000ReturnsOstream_929) {
  UShortValue value;
  value.read("1");
  auto& result = CanonMakerNote::printLe0x0000(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_929, PrintSi0x0001ReturnsOstream_929) {
  UShortValue value;
  value.read("96");
  auto& result = CanonMakerNote::printSi0x0001(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_929, PrintSi0x0002ReturnsOstream_929) {
  UShortValue value;
  value.read("160");
  auto& result = CanonMakerNote::printSi0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_929, PrintSi0x0003ReturnsOstream_929) {
  UShortValue value;
  value.read("100");
  auto& result = CanonMakerNote::printSi0x0003(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_929, PrintSi0x0009ReturnsOstream_929) {
  UShortValue value;
  value.read("5");
  auto& result = CanonMakerNote::printSi0x0009(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_929, PrintSi0x000cReturnsOstream_929) {
  UShortValue value;
  value.read("100");
  auto& result = CanonMakerNote::printSi0x000c(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_929, PrintSi0x000dReturnsOstream_929) {
  UShortValue value;
  value.read("5");
  auto& result = CanonMakerNote::printSi0x000d(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_929, PrintSi0x000eReturnsOstream_929) {
  UShortValue value;
  value.read("100");
  ExifData exifData;
  auto& result = CanonMakerNote::printSi0x000e(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_929, PrintSi0x000eWithNullExifData_929) {
  UShortValue value;
  value.read("100");
  auto& result = CanonMakerNote::printSi0x000e(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_929, PrintSi0x0013ReturnsOstream_929) {
  UShortValue value;
  value.read("3");
  auto& result = CanonMakerNote::printSi0x0013(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_929, PrintSi0x0015ReturnsOstream_929) {
  UShortValue value;
  value.read("2");
  auto& result = CanonMakerNote::printSi0x0015(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_929, PrintSi0x0016ReturnsOstream_929) {
  UShortValue value;
  value.read("1");
  auto& result = CanonMakerNote::printSi0x0016(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_929, PrintSi0x0017ReturnsOstream_929) {
  UShortValue value;
  value.read("128");
  auto& result = CanonMakerNote::printSi0x0017(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_929, PrintSi0x0018ReturnsOstream_929) {
  UShortValue value;
  value.read("128");
  auto& result = CanonMakerNote::printSi0x0018(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_929, PrintFiFocusDistanceReturnsOstream_929) {
  UShortValue value;
  value.read("100");
  auto& result = CanonMakerNote::printFiFocusDistance(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_929, PrintFiFocusDistanceZero_929) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printFiFocusDistance(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  // Zero distance may produce "inf" or special output
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

TEST_F(CanonMakerNoteTest_929, PrintFiFocusDistanceMaxValue_929) {
  UShortValue value;
  value.read("65535");
  auto& result = CanonMakerNote::printFiFocusDistance(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_929, PrintFiFileNumberReturnsOstream_929) {
  ULongValue value;
  value.read("1234567");
  auto& result = CanonMakerNote::printFiFileNumber(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_929, PrintFiFileNumberWithMetadata_929) {
  ULongValue value;
  value.read("1234567");
  ExifData exifData;
  auto& result = CanonMakerNote::printFiFileNumber(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Boundary / edge case tests
// ============================================================

TEST_F(CanonMakerNoteTest_929, PrintSi0x0001WithZeroValue_929) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x0001(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_929, PrintSi0x0002WithZeroValue_929) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_929, PrintSi0x0003WithZeroValue_929) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x0003(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_929, PrintCsLensTypeWithZeroValue_929) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printCsLensType(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_929, PrintCsLensTypeWithLargeValue_929) {
  UShortValue value;
  value.read("65535");
  auto& result = CanonMakerNote::printCsLensType(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_929, Print0x0008WithZeroValue_929) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::print0x0008(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_929, PrintLe0x0000WithZeroValue_929) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printLe0x0000(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_929, PrintSi0x0009WithZeroValue_929) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x0009(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_929, PrintSi0x000dWithZeroValue_929) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x000d(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

// ============================================================
// Verify stream output is non-empty for typical values
// ============================================================

TEST_F(CanonMakerNoteTest_929, PrintSi0x0001ProducesOutput_929) {
  UShortValue value;
  value.read("96");
  CanonMakerNote::printSi0x0001(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_929, PrintSi0x0002ProducesOutput_929) {
  UShortValue value;
  value.read("160");
  CanonMakerNote::printSi0x0002(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_929, PrintFiFocusDistanceProducesOutput_929) {
  UShortValue value;
  value.read("500");
  CanonMakerNote::printFiFocusDistance(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_929, PrintCs0x0002ProducesOutput_929) {
  UShortValue value;
  value.read("50");
  CanonMakerNote::printCs0x0002(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

// ============================================================
// Test that multiple tagList calls return consistent results
// ============================================================

TEST_F(CanonMakerNoteTest_929, TagListCiConsistentAcrossCalls_929) {
  auto result1 = CanonMakerNote::tagListCi();
  auto result2 = CanonMakerNote::tagListCi();
  EXPECT_EQ(result1, result2);
}

TEST_F(CanonMakerNoteTest_929, TagListConsistentAcrossCalls_929) {
  auto result1 = CanonMakerNote::tagList();
  auto result2 = CanonMakerNote::tagList();
  EXPECT_EQ(result1, result2);
}

TEST_F(CanonMakerNoteTest_929, TagListCsConsistentAcrossCalls_929) {
  auto result1 = CanonMakerNote::tagListCs();
  auto result2 = CanonMakerNote::tagListCs();
  EXPECT_EQ(result1, result2);
}

TEST_F(CanonMakerNoteTest_929, TagListSiConsistentAcrossCalls_929) {
  auto result1 = CanonMakerNote::tagListSi();
  auto result2 = CanonMakerNote::tagListSi();
  EXPECT_EQ(result1, result2);
}

// ============================================================
// Test print functions with ExifData containing relevant keys
// ============================================================

TEST_F(CanonMakerNoteTest_929, PrintCsLensTypeWithExifData_929) {
  UShortValue value;
  value.read("1");
  ExifData exifData;
  auto& result = CanonMakerNote::printCsLensType(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_929, PrintSi0x000eWithExifDataContainingModel_929) {
  UShortValue value;
  value.read("168");
  ExifData exifData;
  // Add a model tag to exif data
  exifData["Exif.Image.Model"] = "Canon EOS 5D Mark III";
  auto& result = CanonMakerNote::printSi0x000e(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_929, Print0x000cWithExifDataContainingModel_929) {
  ULongValue value;
  value.read("1234567890");
  ExifData exifData;
  exifData["Exif.Image.Model"] = "Canon EOS 5D Mark III";
  auto& result = CanonMakerNote::print0x000c(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}
