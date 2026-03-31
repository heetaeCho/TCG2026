#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>
#include "canonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class CanonMakerNoteTest_936 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// =============================================================================
// Tag list accessor tests
// =============================================================================

TEST_F(CanonMakerNoteTest_936, TagListReturnsNonNull_936) {
  auto tagList = CanonMakerNote::tagList();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_936, TagListCsReturnsNonNull_936) {
  auto tagList = CanonMakerNote::tagListCs();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_936, TagListSiReturnsNonNull_936) {
  auto tagList = CanonMakerNote::tagListSi();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_936, TagListPaReturnsNonNull_936) {
  auto tagList = CanonMakerNote::tagListPa();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_936, TagListCfReturnsNonNull_936) {
  auto tagList = CanonMakerNote::tagListCf();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_936, TagListPiReturnsNonNull_936) {
  auto tagList = CanonMakerNote::tagListPi();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_936, TagListTiReturnsNonNull_936) {
  auto tagList = CanonMakerNote::tagListTi();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_936, TagListFiReturnsNonNull_936) {
  auto tagList = CanonMakerNote::tagListFi();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_936, TagListPrReturnsNonNull_936) {
  auto tagList = CanonMakerNote::tagListPr();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_936, TagListMvReturnsNonNull_936) {
  auto tagList = CanonMakerNote::tagListMv();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_936, TagListMcReturnsNonNull_936) {
  auto tagList = CanonMakerNote::tagListMc();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_936, TagListMeReturnsNonNull_936) {
  auto tagList = CanonMakerNote::tagListMe();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_936, TagListLeReturnsNonNull_936) {
  auto tagList = CanonMakerNote::tagListLe();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_936, TagListFlReturnsNonNull_936) {
  auto tagList = CanonMakerNote::tagListFl();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_936, TagListCoReturnsNonNull_936) {
  auto tagList = CanonMakerNote::tagListCo();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_936, TagListWbiReturnsNonNull_936) {
  auto tagList = CanonMakerNote::tagListWbi();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_936, TagListMoReturnsNonNull_936) {
  auto tagList = CanonMakerNote::tagListMo();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_936, TagListPreIReturnsNonNull_936) {
  auto tagList = CanonMakerNote::tagListPreI();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_936, TagListCiReturnsNonNull_936) {
  auto tagList = CanonMakerNote::tagListCi();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_936, TagListAfMiAdjReturnsNonNull_936) {
  auto tagList = CanonMakerNote::tagListAfMiAdj();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_936, TagListVigCorReturnsNonNull_936) {
  auto tagList = CanonMakerNote::tagListVigCor();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_936, TagListVigCor2ReturnsNonNull_936) {
  auto tagList = CanonMakerNote::tagListVigCor2();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_936, TagListLiOpReturnsNonNull_936) {
  auto tagList = CanonMakerNote::tagListLiOp();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_936, TagListAmReturnsNonNull_936) {
  auto tagList = CanonMakerNote::tagListAm();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_936, TagListFilReturnsNonNull_936) {
  auto tagList = CanonMakerNote::tagListFil();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_936, TagListHdrReturnsNonNull_936) {
  auto tagList = CanonMakerNote::tagListHdr();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_936, TagListAfCReturnsNonNull_936) {
  auto tagList = CanonMakerNote::tagListAfC();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_936, TagListRawBReturnsNonNull_936) {
  auto tagList = CanonMakerNote::tagListRawB();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_936, TagListFcd1ReturnsNonNull_936) {
  auto tagList = CanonMakerNote::tagListFcd1();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_936, TagListFcd2ReturnsNonNull_936) {
  auto tagList = CanonMakerNote::tagListFcd2();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_936, TagListFcd3ReturnsNonNull_936) {
  auto tagList = CanonMakerNote::tagListFcd3();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_936, TagListAsReturnsNonNull_936) {
  auto tagList = CanonMakerNote::tagListAs();
  EXPECT_NE(tagList, nullptr);
}

TEST_F(CanonMakerNoteTest_936, TagListCbiReturnsNonNull_936) {
  auto tagList = CanonMakerNote::tagListCbi();
  EXPECT_NE(tagList, nullptr);
}

// =============================================================================
// Print function tests - testing with single-value inputs
// =============================================================================

TEST_F(CanonMakerNoteTest_936, PrintFocalLength_SingleValue_936) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printFocalLength(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  // The output should not be empty — even an error message is output
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

TEST_F(CanonMakerNoteTest_936, PrintFocalLength_MultipleValues_936) {
  UShortValue value;
  value.read("1 50 0 0");
  auto& result = CanonMakerNote::printFocalLength(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

TEST_F(CanonMakerNoteTest_936, Print0x0008_ReturnsStream_936) {
  UShortValue value;
  value.read("12345");
  auto& result = CanonMakerNote::print0x0008(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_936, Print0x000a_ReturnsStream_936) {
  ULongValue value;
  value.read("12345678");
  auto& result = CanonMakerNote::print0x000a(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_936, Print0x000c_ReturnsStreamNullExifData_936) {
  ULongValue value;
  value.read("12345678");
  auto& result = CanonMakerNote::print0x000c(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_936, PrintCs0x0002_SingleValue_936) {
  UShortValue value;
  value.read("50");
  auto& result = CanonMakerNote::printCs0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_936, PrintCsLensType_ReturnsStream_936) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printCsLensType(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_936, PrintCsLens_SingleValue_936) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printCsLens(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_936, PrintCsLens_ThreeValues_936) {
  UShortValue value;
  value.read("50 18 1");
  auto& result = CanonMakerNote::printCsLens(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

TEST_F(CanonMakerNoteTest_936, PrintLe0x0000_ReturnsStream_936) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printLe0x0000(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_936, PrintSi0x0001_ReturnsStream_936) {
  UShortValue value;
  value.read("100");
  auto& result = CanonMakerNote::printSi0x0001(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_936, PrintSi0x0002_ReturnsStream_936) {
  UShortValue value;
  value.read("100");
  auto& result = CanonMakerNote::printSi0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_936, PrintSi0x0003_ReturnsStream_936) {
  UShortValue value;
  value.read("100");
  auto& result = CanonMakerNote::printSi0x0003(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_936, PrintSi0x0009_ReturnsStream_936) {
  UShortValue value;
  value.read("10");
  auto& result = CanonMakerNote::printSi0x0009(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_936, PrintSi0x000c_ReturnsStream_936) {
  UShortValue value;
  value.read("500");
  auto& result = CanonMakerNote::printSi0x000c(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_936, PrintSi0x000d_ReturnsStream_936) {
  UShortValue value;
  value.read("5");
  auto& result = CanonMakerNote::printSi0x000d(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_936, PrintSi0x000e_ReturnsStreamNullExifData_936) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x000e(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_936, PrintSi0x0013_ReturnsStream_936) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x0013(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_936, PrintSi0x0015_ReturnsStream_936) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x0015(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_936, PrintSi0x0016_ReturnsStream_936) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x0016(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_936, PrintSi0x0017_ReturnsStream_936) {
  UShortValue value;
  value.read("100");
  auto& result = CanonMakerNote::printSi0x0017(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_936, PrintSi0x0018_ReturnsStream_936) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x0018(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_936, PrintFiFocusDistance_ReturnsStream_936) {
  UShortValue value;
  value.read("100");
  auto& result = CanonMakerNote::printFiFocusDistance(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_936, PrintFiFocusDistance_ZeroValue_936) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printFiFocusDistance(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_936, PrintFiFocusDistance_MaxValue_936) {
  UShortValue value;
  value.read("65535");
  auto& result = CanonMakerNote::printFiFocusDistance(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_936, PrintFiFileNumber_ReturnsStream_936) {
  ULongValue value;
  value.read("1234567");
  auto& result = CanonMakerNote::printFiFileNumber(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_936, PrintFiFileNumber_ZeroValue_936) {
  ULongValue value;
  value.read("0");
  auto& result = CanonMakerNote::printFiFileNumber(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

// =============================================================================
// Tests with ExifData parameter
// =============================================================================

TEST_F(CanonMakerNoteTest_936, PrintSi0x000e_WithExifData_936) {
  ExifData exifData;
  UShortValue value;
  value.read("10");
  auto& result = CanonMakerNote::printSi0x000e(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_936, Print0x000c_WithExifData_936) {
  ExifData exifData;
  ULongValue value;
  value.read("12345678");
  auto& result = CanonMakerNote::print0x000c(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_936, PrintCsLensType_WithMetadata_936) {
  ExifData exifData;
  UShortValue value;
  value.read("1");
  auto& result = CanonMakerNote::printCsLensType(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_936, PrintFiFileNumber_WithMetadata_936) {
  ExifData exifData;
  ULongValue value;
  value.read("1000100");
  auto& result = CanonMakerNote::printFiFileNumber(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_936, PrintFocalLength_WithMetadata_936) {
  ExifData exifData;
  UShortValue value;
  value.read("1 50 0 0");
  auto& result = CanonMakerNote::printFocalLength(os, value, &exifData);
  EXPECT_EQ(&result, &os);
}

// =============================================================================
// Boundary tests for print functions with edge values
// =============================================================================

TEST_F(CanonMakerNoteTest_936, PrintSi0x0001_ZeroValue_936) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x0001(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_936, PrintSi0x0002_ZeroValue_936) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_936, PrintSi0x0003_ZeroValue_936) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x0003(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_936, PrintSi0x0001_MaxUShort_936) {
  UShortValue value;
  value.read("65535");
  auto& result = CanonMakerNote::printSi0x0001(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_936, PrintCs0x0002_ZeroValue_936) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printCs0x0002(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_936, Print0x0008_ZeroValue_936) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::print0x0008(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_936, PrintSi0x0009_ZeroValue_936) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x0009(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_936, PrintSi0x000c_ZeroValue_936) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x000c(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

TEST_F(CanonMakerNoteTest_936, PrintSi0x000d_ZeroValue_936) {
  UShortValue value;
  value.read("0");
  auto& result = CanonMakerNote::printSi0x000d(os, value, nullptr);
  EXPECT_EQ(&result, &os);
}

// =============================================================================
// Test that tag list functions return consistent results on multiple calls
// =============================================================================

TEST_F(CanonMakerNoteTest_936, TagListConsistentAcrossCalls_936) {
  auto first = CanonMakerNote::tagList();
  auto second = CanonMakerNote::tagList();
  EXPECT_EQ(first, second);
}

TEST_F(CanonMakerNoteTest_936, TagListCsConsistentAcrossCalls_936) {
  auto first = CanonMakerNote::tagListCs();
  auto second = CanonMakerNote::tagListCs();
  EXPECT_EQ(first, second);
}

TEST_F(CanonMakerNoteTest_936, TagListMeConsistentAcrossCalls_936) {
  auto first = CanonMakerNote::tagListMe();
  auto second = CanonMakerNote::tagListMe();
  EXPECT_EQ(first, second);
}

// =============================================================================
// Test output is produced (not empty) for normal values
// =============================================================================

TEST_F(CanonMakerNoteTest_936, PrintSi0x0017_ProducesOutput_936) {
  UShortValue value;
  value.read("200");
  CanonMakerNote::printSi0x0017(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_936, PrintSi0x0015_ProducesOutput_936) {
  UShortValue value;
  value.read("10");
  CanonMakerNote::printSi0x0015(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_936, PrintSi0x0016_ProducesOutput_936) {
  UShortValue value;
  value.read("10");
  CanonMakerNote::printSi0x0016(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_936, PrintFiFocusDistance_ProducesOutput_936) {
  UShortValue value;
  value.read("500");
  CanonMakerNote::printFiFocusDistance(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(CanonMakerNoteTest_936, PrintLe0x0000_ProducesOutput_936) {
  UShortValue value;
  value.read("5");
  CanonMakerNote::printLe0x0000(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}
