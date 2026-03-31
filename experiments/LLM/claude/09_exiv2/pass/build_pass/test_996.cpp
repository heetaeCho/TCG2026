#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>
#include "minoltamn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class MinoltaMakerNoteTest_996 : public ::testing::Test {
 protected:
  std::ostringstream os;
};

// ============================================================
// Tests for tagListCsStd()
// ============================================================

TEST_F(MinoltaMakerNoteTest_996, TagListCsStdReturnsNonNull_996) {
  auto tagList = MinoltaMakerNote::tagListCsStd();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(MinoltaMakerNoteTest_996, TagListCsStdFirstEntryValid_996) {
  auto tagList = MinoltaMakerNote::tagListCsStd();
  // The first entry should have a valid tag (non-negative typically) and a non-null name
  EXPECT_NE(tagList[0].name_, nullptr);
}

// ============================================================
// Tests for tagList()
// ============================================================

TEST_F(MinoltaMakerNoteTest_996, TagListReturnsNonNull_996) {
  auto tagList = MinoltaMakerNote::tagList();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(MinoltaMakerNoteTest_996, TagListFirstEntryValid_996) {
  auto tagList = MinoltaMakerNote::tagList();
  EXPECT_NE(tagList[0].name_, nullptr);
}

// ============================================================
// Tests for tagListCs7D()
// ============================================================

TEST_F(MinoltaMakerNoteTest_996, TagListCs7DReturnsNonNull_996) {
  auto tagList = MinoltaMakerNote::tagListCs7D();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(MinoltaMakerNoteTest_996, TagListCs7DFirstEntryValid_996) {
  auto tagList = MinoltaMakerNote::tagListCs7D();
  EXPECT_NE(tagList[0].name_, nullptr);
}

// ============================================================
// Tests for tagListCs5D()
// ============================================================

TEST_F(MinoltaMakerNoteTest_996, TagListCs5DReturnsNonNull_996) {
  auto tagList = MinoltaMakerNote::tagListCs5D();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(MinoltaMakerNoteTest_996, TagListCs5DFirstEntryValid_996) {
  auto tagList = MinoltaMakerNote::tagListCs5D();
  EXPECT_NE(tagList[0].name_, nullptr);
}

// ============================================================
// Tests for tagListCsA100()
// ============================================================

TEST_F(MinoltaMakerNoteTest_996, TagListCsA100ReturnsNonNull_996) {
  auto tagList = MinoltaMakerNote::tagListCsA100();
  ASSERT_NE(tagList, nullptr);
}

TEST_F(MinoltaMakerNoteTest_996, TagListCsA100FirstEntryValid_996) {
  auto tagList = MinoltaMakerNote::tagListCsA100();
  EXPECT_NE(tagList[0].name_, nullptr);
}

// ============================================================
// Tests for printMinoltaExposureSpeedStd
// ============================================================

TEST_F(MinoltaMakerNoteTest_996, PrintExposureSpeedStdNormalValue_996) {
  ULongValue value;
  value.read("104");
  auto& result = MinoltaMakerNote::printMinoltaExposureSpeedStd(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(MinoltaMakerNoteTest_996, PrintExposureSpeedStdZeroValue_996) {
  ULongValue value;
  value.read("0");
  MinoltaMakerNote::printMinoltaExposureSpeedStd(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

// ============================================================
// Tests for printMinoltaExposureTimeStd
// ============================================================

TEST_F(MinoltaMakerNoteTest_996, PrintExposureTimeStdNormalValue_996) {
  ULongValue value;
  value.read("128");
  auto& result = MinoltaMakerNote::printMinoltaExposureTimeStd(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(MinoltaMakerNoteTest_996, PrintExposureTimeStdZeroValue_996) {
  ULongValue value;
  value.read("0");
  MinoltaMakerNote::printMinoltaExposureTimeStd(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

// ============================================================
// Tests for printMinoltaFNumberStd
// ============================================================

TEST_F(MinoltaMakerNoteTest_996, PrintFNumberStdNormalValue_996) {
  ULongValue value;
  value.read("16");
  auto& result = MinoltaMakerNote::printMinoltaFNumberStd(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(MinoltaMakerNoteTest_996, PrintFNumberStdZeroValue_996) {
  ULongValue value;
  value.read("0");
  MinoltaMakerNote::printMinoltaFNumberStd(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

// ============================================================
// Tests for printMinoltaExposureCompensationStd
// ============================================================

TEST_F(MinoltaMakerNoteTest_996, PrintExposureCompensationStdNormalValue_996) {
  ULongValue value;
  value.read("6");
  auto& result = MinoltaMakerNote::printMinoltaExposureCompensationStd(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(MinoltaMakerNoteTest_996, PrintExposureCompensationStdZeroValue_996) {
  ULongValue value;
  value.read("0");
  MinoltaMakerNote::printMinoltaExposureCompensationStd(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

// ============================================================
// Tests for printMinoltaFocalLengthStd
// ============================================================

TEST_F(MinoltaMakerNoteTest_996, PrintFocalLengthStdNormalValue_996) {
  ULongValue value;
  value.read("50");
  auto& result = MinoltaMakerNote::printMinoltaFocalLengthStd(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(MinoltaMakerNoteTest_996, PrintFocalLengthStdZeroValue_996) {
  ULongValue value;
  value.read("0");
  MinoltaMakerNote::printMinoltaFocalLengthStd(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

// ============================================================
// Tests for printMinoltaDateStd
// ============================================================

TEST_F(MinoltaMakerNoteTest_996, PrintDateStdNormalValue_996) {
  ULongValue value;
  value.read("20230115");
  auto& result = MinoltaMakerNote::printMinoltaDateStd(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(MinoltaMakerNoteTest_996, PrintDateStdZeroValue_996) {
  ULongValue value;
  value.read("0");
  MinoltaMakerNote::printMinoltaDateStd(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

// ============================================================
// Tests for printMinoltaTimeStd
// ============================================================

TEST_F(MinoltaMakerNoteTest_996, PrintTimeStdNormalValue_996) {
  ULongValue value;
  value.read("123456");
  auto& result = MinoltaMakerNote::printMinoltaTimeStd(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(MinoltaMakerNoteTest_996, PrintTimeStdZeroValue_996) {
  ULongValue value;
  value.read("0");
  MinoltaMakerNote::printMinoltaTimeStd(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

// ============================================================
// Tests for printMinoltaFlashExposureCompStd
// ============================================================

TEST_F(MinoltaMakerNoteTest_996, PrintFlashExposureCompStdNormalValue_996) {
  ULongValue value;
  value.read("6");
  auto& result = MinoltaMakerNote::printMinoltaFlashExposureCompStd(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(MinoltaMakerNoteTest_996, PrintFlashExposureCompStdZeroValue_996) {
  ULongValue value;
  value.read("0");
  MinoltaMakerNote::printMinoltaFlashExposureCompStd(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

// ============================================================
// Tests for printMinoltaWhiteBalanceStd
// ============================================================

TEST_F(MinoltaMakerNoteTest_996, PrintWhiteBalanceStdNormalValue_996) {
  ULongValue value;
  value.read("32");
  auto& result = MinoltaMakerNote::printMinoltaWhiteBalanceStd(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(MinoltaMakerNoteTest_996, PrintWhiteBalanceStdZeroValue_996) {
  ULongValue value;
  value.read("0");
  MinoltaMakerNote::printMinoltaWhiteBalanceStd(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

// ============================================================
// Tests for printMinoltaBrightnessStd
// ============================================================

TEST_F(MinoltaMakerNoteTest_996, PrintBrightnessStdNormalValue_996) {
  ULongValue value;
  value.read("50");
  auto& result = MinoltaMakerNote::printMinoltaBrightnessStd(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(MinoltaMakerNoteTest_996, PrintBrightnessStdZeroValue_996) {
  ULongValue value;
  value.read("0");
  MinoltaMakerNote::printMinoltaBrightnessStd(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

// ============================================================
// Tests for printMinoltaExposureManualBias5D
// ============================================================

TEST_F(MinoltaMakerNoteTest_996, PrintExposureManualBias5DNormalValue_996) {
  ULongValue value;
  value.read("10");
  auto& result = MinoltaMakerNote::printMinoltaExposureManualBias5D(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(MinoltaMakerNoteTest_996, PrintExposureManualBias5DZeroValue_996) {
  ULongValue value;
  value.read("0");
  MinoltaMakerNote::printMinoltaExposureManualBias5D(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

// ============================================================
// Tests for printMinoltaExposureCompensation5D
// ============================================================

TEST_F(MinoltaMakerNoteTest_996, PrintExposureCompensation5DNormalValue_996) {
  ULongValue value;
  value.read("6");
  auto& result = MinoltaMakerNote::printMinoltaExposureCompensation5D(os, value, nullptr);
  EXPECT_EQ(&result, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(MinoltaMakerNoteTest_996, PrintExposureCompensation5DZeroValue_996) {
  ULongValue value;
  value.read("0");
  MinoltaMakerNote::printMinoltaExposureCompensation5D(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

// ============================================================
// Boundary / Edge case tests
// ============================================================

TEST_F(MinoltaMakerNoteTest_996, PrintExposureSpeedStdLargeValue_996) {
  ULongValue value;
  value.read("4294967295");  // max uint32
  MinoltaMakerNote::printMinoltaExposureSpeedStd(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(MinoltaMakerNoteTest_996, PrintExposureTimeStdLargeValue_996) {
  ULongValue value;
  value.read("4294967295");
  MinoltaMakerNote::printMinoltaExposureTimeStd(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(MinoltaMakerNoteTest_996, PrintFNumberStdLargeValue_996) {
  ULongValue value;
  value.read("4294967295");
  MinoltaMakerNote::printMinoltaFNumberStd(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(MinoltaMakerNoteTest_996, PrintFocalLengthStdLargeValue_996) {
  ULongValue value;
  value.read("4294967295");
  MinoltaMakerNote::printMinoltaFocalLengthStd(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(MinoltaMakerNoteTest_996, PrintWhiteBalanceStdLargeValue_996) {
  ULongValue value;
  value.read("4294967295");
  MinoltaMakerNote::printMinoltaWhiteBalanceStd(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(MinoltaMakerNoteTest_996, PrintBrightnessStdLargeValue_996) {
  ULongValue value;
  value.read("4294967295");
  MinoltaMakerNote::printMinoltaBrightnessStd(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(MinoltaMakerNoteTest_996, PrintExposureManualBias5DLargeValue_996) {
  ULongValue value;
  value.read("4294967295");
  MinoltaMakerNote::printMinoltaExposureManualBias5D(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(MinoltaMakerNoteTest_996, PrintExposureCompensation5DLargeValue_996) {
  ULongValue value;
  value.read("4294967295");
  MinoltaMakerNote::printMinoltaExposureCompensation5D(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

// ============================================================
// Tests with multiple values (count > 1)
// ============================================================

TEST_F(MinoltaMakerNoteTest_996, PrintDateStdMultipleValues_996) {
  ULongValue value;
  value.read("2023 1 15");
  MinoltaMakerNote::printMinoltaDateStd(os, value, nullptr);
  // Should produce some output regardless of count
  EXPECT_FALSE(os.str().empty());
}

TEST_F(MinoltaMakerNoteTest_996, PrintTimeStdMultipleValues_996) {
  ULongValue value;
  value.read("12 30 45");
  MinoltaMakerNote::printMinoltaTimeStd(os, value, nullptr);
  EXPECT_FALSE(os.str().empty());
}

// ============================================================
// Consistency tests - calling same function twice yields same output
// ============================================================

TEST_F(MinoltaMakerNoteTest_996, PrintExposureSpeedStdConsistency_996) {
  ULongValue value;
  value.read("104");

  std::ostringstream os1, os2;
  MinoltaMakerNote::printMinoltaExposureSpeedStd(os1, value, nullptr);
  MinoltaMakerNote::printMinoltaExposureSpeedStd(os2, value, nullptr);
  EXPECT_EQ(os1.str(), os2.str());
}

TEST_F(MinoltaMakerNoteTest_996, PrintFNumberStdConsistency_996) {
  ULongValue value;
  value.read("16");

  std::ostringstream os1, os2;
  MinoltaMakerNote::printMinoltaFNumberStd(os1, value, nullptr);
  MinoltaMakerNote::printMinoltaFNumberStd(os2, value, nullptr);
  EXPECT_EQ(os1.str(), os2.str());
}

// ============================================================
// Tag list consistency - calling multiple times returns same pointer
// ============================================================

TEST_F(MinoltaMakerNoteTest_996, TagListCsStdConsistentAcrossCalls_996) {
  auto list1 = MinoltaMakerNote::tagListCsStd();
  auto list2 = MinoltaMakerNote::tagListCsStd();
  EXPECT_EQ(list1, list2);
}

TEST_F(MinoltaMakerNoteTest_996, TagListConsistentAcrossCalls_996) {
  auto list1 = MinoltaMakerNote::tagList();
  auto list2 = MinoltaMakerNote::tagList();
  EXPECT_EQ(list1, list2);
}

TEST_F(MinoltaMakerNoteTest_996, TagListCs7DConsistentAcrossCalls_996) {
  auto list1 = MinoltaMakerNote::tagListCs7D();
  auto list2 = MinoltaMakerNote::tagListCs7D();
  EXPECT_EQ(list1, list2);
}

TEST_F(MinoltaMakerNoteTest_996, TagListCs5DConsistentAcrossCalls_996) {
  auto list1 = MinoltaMakerNote::tagListCs5D();
  auto list2 = MinoltaMakerNote::tagListCs5D();
  EXPECT_EQ(list1, list2);
}

TEST_F(MinoltaMakerNoteTest_996, TagListCsA100ConsistentAcrossCalls_996) {
  auto list1 = MinoltaMakerNote::tagListCsA100();
  auto list2 = MinoltaMakerNote::tagListCsA100();
  EXPECT_EQ(list1, list2);
}

// ============================================================
// All tag lists are different from each other
// ============================================================

TEST_F(MinoltaMakerNoteTest_996, AllTagListsAreDifferent_996) {
  auto listStd = MinoltaMakerNote::tagListCsStd();
  auto list7D = MinoltaMakerNote::tagListCs7D();
  auto list5D = MinoltaMakerNote::tagListCs5D();
  auto listA100 = MinoltaMakerNote::tagListCsA100();
  auto listMain = MinoltaMakerNote::tagList();

  EXPECT_NE(listStd, list7D);
  EXPECT_NE(listStd, list5D);
  EXPECT_NE(listStd, listA100);
  EXPECT_NE(listStd, listMain);
  EXPECT_NE(list7D, list5D);
  EXPECT_NE(list7D, listA100);
  EXPECT_NE(list5D, listA100);
}
