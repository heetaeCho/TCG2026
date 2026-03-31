#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>
#include "olympusmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class OlympusMakerNoteTest_893 : public ::testing::Test {
protected:
    std::ostringstream os;
};

// ============================================================
// Tests for tagList functions (constexpr tag list accessors)
// ============================================================

TEST_F(OlympusMakerNoteTest_893, TagListFeReturnsNonNull_893) {
    auto tagList = OlympusMakerNote::tagListFe();
    ASSERT_NE(tagList, nullptr);
}

TEST_F(OlympusMakerNoteTest_893, TagListReturnsNonNull_893) {
    auto tagList = OlympusMakerNote::tagList();
    ASSERT_NE(tagList, nullptr);
}

TEST_F(OlympusMakerNoteTest_893, TagListCsReturnsNonNull_893) {
    auto tagList = OlympusMakerNote::tagListCs();
    ASSERT_NE(tagList, nullptr);
}

TEST_F(OlympusMakerNoteTest_893, TagListEqReturnsNonNull_893) {
    auto tagList = OlympusMakerNote::tagListEq();
    ASSERT_NE(tagList, nullptr);
}

TEST_F(OlympusMakerNoteTest_893, TagListRdReturnsNonNull_893) {
    auto tagList = OlympusMakerNote::tagListRd();
    ASSERT_NE(tagList, nullptr);
}

TEST_F(OlympusMakerNoteTest_893, TagListRd2ReturnsNonNull_893) {
    auto tagList = OlympusMakerNote::tagListRd2();
    ASSERT_NE(tagList, nullptr);
}

TEST_F(OlympusMakerNoteTest_893, TagListIpReturnsNonNull_893) {
    auto tagList = OlympusMakerNote::tagListIp();
    ASSERT_NE(tagList, nullptr);
}

TEST_F(OlympusMakerNoteTest_893, TagListFiReturnsNonNull_893) {
    auto tagList = OlympusMakerNote::tagListFi();
    ASSERT_NE(tagList, nullptr);
}

TEST_F(OlympusMakerNoteTest_893, TagListRiReturnsNonNull_893) {
    auto tagList = OlympusMakerNote::tagListRi();
    ASSERT_NE(tagList, nullptr);
}

// ============================================================
// Tests for print0x0200 (Quality)
// ============================================================

TEST_F(OlympusMakerNoteTest_893, Print0x0200WithSingleValue_893) {
    UShortValue value;
    value.read("0");
    auto& result = OlympusMakerNote::print0x0200(os, value, nullptr);
    EXPECT_EQ(&result, &os);
    EXPECT_FALSE(os.str().empty());
}

TEST_F(OlympusMakerNoteTest_893, Print0x0200WithMultipleValues_893) {
    UShortValue value;
    value.read("0 0 0");
    auto& result = OlympusMakerNote::print0x0200(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

// ============================================================
// Tests for print0x0204 (DigitalZoom)
// ============================================================

TEST_F(OlympusMakerNoteTest_893, Print0x0204WithZeroValue_893) {
    URationalValue value;
    value.read("0/1");
    auto& result = OlympusMakerNote::print0x0204(os, value, nullptr);
    EXPECT_EQ(&result, &os);
    EXPECT_FALSE(os.str().empty());
}

TEST_F(OlympusMakerNoteTest_893, Print0x0204WithNonZeroValue_893) {
    URationalValue value;
    value.read("200/100");
    auto& result = OlympusMakerNote::print0x0204(os, value, nullptr);
    EXPECT_EQ(&result, &os);
    EXPECT_FALSE(os.str().empty());
}

// ============================================================
// Tests for print0x1015 (WhiteBalance)
// ============================================================

TEST_F(OlympusMakerNoteTest_893, Print0x1015WithSingleValue_893) {
    UShortValue value;
    value.read("0");
    auto& result = OlympusMakerNote::print0x1015(os, value, nullptr);
    EXPECT_EQ(&result, &os);
    EXPECT_FALSE(os.str().empty());
}

TEST_F(OlympusMakerNoteTest_893, Print0x1015WithMultipleValues_893) {
    UShortValue value;
    value.read("0 0");
    auto& result = OlympusMakerNote::print0x1015(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

// ============================================================
// Tests for print0x0201 (Lens info)
// ============================================================

TEST_F(OlympusMakerNoteTest_893, Print0x0201WithValues_893) {
    UShortValue value;
    value.read("0 0 0");
    auto& result = OlympusMakerNote::print0x0201(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(OlympusMakerNoteTest_893, Print0x0201EmptyValue_893) {
    UShortValue value;
    // Empty value - boundary condition
    auto& result = OlympusMakerNote::print0x0201(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

// ============================================================
// Tests for print0x0209 (CameraID)
// ============================================================

TEST_F(OlympusMakerNoteTest_893, Print0x0209WithValues_893) {
    UndefinedValue value;
    value.read("48 49 50 51 52 53");
    auto& result = OlympusMakerNote::print0x0209(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

// ============================================================
// Tests for printEq0x0301 (Equipment lens type)
// ============================================================

TEST_F(OlympusMakerNoteTest_893, PrintEq0x0301WithSingleByte_893) {
    UByteValue value;
    value.read("0");
    auto& result = OlympusMakerNote::printEq0x0301(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(OlympusMakerNoteTest_893, PrintEq0x0301WithMultipleBytes_893) {
    UByteValue value;
    value.read("0 0 0 0 0 0");
    auto& result = OlympusMakerNote::printEq0x0301(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

// ============================================================
// Tests for printCs0x0301 (Camera settings drive mode)
// ============================================================

TEST_F(OlympusMakerNoteTest_893, PrintCs0x0301WithSingleValue_893) {
    UShortValue value;
    value.read("0");
    auto& result = OlympusMakerNote::printCs0x0301(os, value, nullptr);
    EXPECT_EQ(&result, &os);
    EXPECT_FALSE(os.str().empty());
}

TEST_F(OlympusMakerNoteTest_893, PrintCs0x0301WithMultipleValues_893) {
    UShortValue value;
    value.read("0 0 0");
    auto& result = OlympusMakerNote::printCs0x0301(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

// ============================================================
// Tests for print0x050f (Focus info - ManualFlash)
// ============================================================

TEST_F(OlympusMakerNoteTest_893, Print0x050fWithValues_893) {
    UShortValue value;
    value.read("0 0");
    auto& result = OlympusMakerNote::print0x050f(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(OlympusMakerNoteTest_893, Print0x050fWithSingleValue_893) {
    UShortValue value;
    value.read("0");
    auto& result = OlympusMakerNote::print0x050f(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

// ============================================================
// Tests for print0x0527 (Focus info)
// ============================================================

TEST_F(OlympusMakerNoteTest_893, Print0x0527WithValues_893) {
    UShortValue value;
    value.read("0 0 0 0");
    auto& result = OlympusMakerNote::print0x0527(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(OlympusMakerNoteTest_893, Print0x0527WithSingleValue_893) {
    UShortValue value;
    value.read("0");
    auto& result = OlympusMakerNote::print0x0527(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

// ============================================================
// Tests for print0x0529
// ============================================================

TEST_F(OlympusMakerNoteTest_893, Print0x0529WithValues_893) {
    UShortValue value;
    value.read("0");
    auto& result = OlympusMakerNote::print0x0529(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(OlympusMakerNoteTest_893, Print0x0529WithNullMetadata_893) {
    UShortValue value;
    value.read("1");
    auto& result = OlympusMakerNote::print0x0529(os, value, nullptr);
    EXPECT_EQ(&result, &os);
    EXPECT_FALSE(os.str().empty());
}

// ============================================================
// Tests for print0x1209
// ============================================================

TEST_F(OlympusMakerNoteTest_893, Print0x1209WithValues_893) {
    UShortValue value;
    value.read("0");
    auto& result = OlympusMakerNote::print0x1209(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

// ============================================================
// Tests for print0x0305
// ============================================================

TEST_F(OlympusMakerNoteTest_893, Print0x0305WithValues_893) {
    ShortValue value;
    value.read("0");
    auto& result = OlympusMakerNote::print0x0305(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(OlympusMakerNoteTest_893, Print0x0305WithNonZeroValue_893) {
    ShortValue value;
    value.read("1");
    auto& result = OlympusMakerNote::print0x0305(os, value, nullptr);
    EXPECT_EQ(&result, &os);
    EXPECT_FALSE(os.str().empty());
}

// ============================================================
// Tests for print0x0308
// ============================================================

TEST_F(OlympusMakerNoteTest_893, Print0x0308WithValues_893) {
    UShortValue value;
    value.read("0");
    auto& result = OlympusMakerNote::print0x0308(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(OlympusMakerNoteTest_893, Print0x0308WithNullMetadata_893) {
    UShortValue value;
    value.read("1");
    auto& result = OlympusMakerNote::print0x0308(os, value, nullptr);
    EXPECT_EQ(&result, &os);
    EXPECT_FALSE(os.str().empty());
}

// ============================================================
// Tests for printGeneric
// ============================================================

TEST_F(OlympusMakerNoteTest_893, PrintGenericWithSingleValue_893) {
    UShortValue value;
    value.read("42");
    auto& result = OlympusMakerNote::printGeneric(os, value, nullptr);
    EXPECT_EQ(&result, &os);
    EXPECT_FALSE(os.str().empty());
}

TEST_F(OlympusMakerNoteTest_893, PrintGenericWithMultipleValues_893) {
    UShortValue value;
    value.read("1 2 3 4 5");
    auto& result = OlympusMakerNote::printGeneric(os, value, nullptr);
    EXPECT_EQ(&result, &os);
    EXPECT_FALSE(os.str().empty());
}

TEST_F(OlympusMakerNoteTest_893, PrintGenericWithEmptyValue_893) {
    UShortValue value;
    auto& result = OlympusMakerNote::printGeneric(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

// ============================================================
// Tests for tag list content verification (first element check)
// ============================================================

TEST_F(OlympusMakerNoteTest_893, TagListFirstElementHasValidTag_893) {
    auto tagList = OlympusMakerNote::tagList();
    ASSERT_NE(tagList, nullptr);
    // The first element should have a valid tag (tag_ member of TagInfo)
    // We just verify the list is accessible and first element exists
    EXPECT_GE(tagList[0].tag_, 0);
}

TEST_F(OlympusMakerNoteTest_893, TagListFeFirstElementHasValidTag_893) {
    auto tagList = OlympusMakerNote::tagListFe();
    ASSERT_NE(tagList, nullptr);
    EXPECT_GE(tagList[0].tag_, 0);
}

TEST_F(OlympusMakerNoteTest_893, TagListCsFirstElementHasValidTag_893) {
    auto tagList = OlympusMakerNote::tagListCs();
    ASSERT_NE(tagList, nullptr);
    EXPECT_GE(tagList[0].tag_, 0);
}

TEST_F(OlympusMakerNoteTest_893, TagListEqFirstElementHasValidTag_893) {
    auto tagList = OlympusMakerNote::tagListEq();
    ASSERT_NE(tagList, nullptr);
    EXPECT_GE(tagList[0].tag_, 0);
}

// ============================================================
// Boundary tests for print functions with unusual values
// ============================================================

TEST_F(OlympusMakerNoteTest_893, Print0x0200WithLargeValue_893) {
    UShortValue value;
    value.read("65535");
    auto& result = OlympusMakerNote::print0x0200(os, value, nullptr);
    EXPECT_EQ(&result, &os);
    EXPECT_FALSE(os.str().empty());
}

TEST_F(OlympusMakerNoteTest_893, Print0x1015KnownWhiteBalanceValue_893) {
    UShortValue value;
    value.read("1");
    auto& result = OlympusMakerNote::print0x1015(os, value, nullptr);
    EXPECT_EQ(&result, &os);
    EXPECT_FALSE(os.str().empty());
}

TEST_F(OlympusMakerNoteTest_893, PrintCs0x0301WithLargeValue_893) {
    UShortValue value;
    value.read("65535");
    auto& result = OlympusMakerNote::printCs0x0301(os, value, nullptr);
    EXPECT_EQ(&result, &os);
    EXPECT_FALSE(os.str().empty());
}

TEST_F(OlympusMakerNoteTest_893, Print0x0204WithLargeRational_893) {
    URationalValue value;
    value.read("65535/1");
    auto& result = OlympusMakerNote::print0x0204(os, value, nullptr);
    EXPECT_EQ(&result, &os);
    EXPECT_FALSE(os.str().empty());
}

// ============================================================
// Tests with ExifData (non-null metadata)
// ============================================================

TEST_F(OlympusMakerNoteTest_893, Print0x0529WithExifData_893) {
    ExifData exifData;
    UShortValue value;
    value.read("0");
    auto& result = OlympusMakerNote::print0x0529(os, value, &exifData);
    EXPECT_EQ(&result, &os);
}

TEST_F(OlympusMakerNoteTest_893, Print0x0308WithExifData_893) {
    ExifData exifData;
    UShortValue value;
    value.read("0");
    auto& result = OlympusMakerNote::print0x0308(os, value, &exifData);
    EXPECT_EQ(&result, &os);
}

TEST_F(OlympusMakerNoteTest_893, PrintGenericWithNullptrExifData_893) {
    ULongValue value;
    value.read("12345678");
    auto& result = OlympusMakerNote::printGeneric(os, value, nullptr);
    EXPECT_EQ(&result, &os);
    EXPECT_FALSE(os.str().empty());
}
