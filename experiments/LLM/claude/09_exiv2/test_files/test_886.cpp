#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>
#include "olympusmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class OlympusMakerNoteTest_886 : public ::testing::Test {
protected:
    std::ostringstream oss;
};

// ============================================================
// tagList() tests
// ============================================================

TEST_F(OlympusMakerNoteTest_886, TagListIsNotNull_886) {
    auto tagList = OlympusMakerNote::tagList();
    ASSERT_NE(tagList, nullptr);
}

TEST_F(OlympusMakerNoteTest_886, TagListFirstEntryHasValidTag_886) {
    auto tagList = OlympusMakerNote::tagList();
    // The first entry should have a valid tag number (non-negative in typical implementations)
    EXPECT_GE(tagList[0].tag_, 0);
}

// ============================================================
// print0x0200 tests - Quality
// ============================================================

TEST_F(OlympusMakerNoteTest_886, Print0x0200_SingleValue_886) {
    UShortValue value;
    value.read("1");
    OlympusMakerNote::print0x0200(oss, value, nullptr);
    std::string result = oss.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(OlympusMakerNoteTest_886, Print0x0200_MultipleValues_886) {
    UShortValue value;
    value.read("1 2 3");
    OlympusMakerNote::print0x0200(oss, value, nullptr);
    std::string result = oss.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(OlympusMakerNoteTest_886, Print0x0200_ZeroValue_886) {
    UShortValue value;
    value.read("0");
    OlympusMakerNote::print0x0200(oss, value, nullptr);
    std::string result = oss.str();
    EXPECT_FALSE(result.empty());
}

// ============================================================
// print0x0204 tests - Flash
// ============================================================

TEST_F(OlympusMakerNoteTest_886, Print0x0204_NormalValue_886) {
    URationalValue value;
    value.read("0/3");
    OlympusMakerNote::print0x0204(oss, value, nullptr);
    std::string result = oss.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(OlympusMakerNoteTest_886, Print0x0204_PositiveValue_886) {
    URationalValue value;
    value.read("1/3");
    OlympusMakerNote::print0x0204(oss, value, nullptr);
    std::string result = oss.str();
    EXPECT_FALSE(result.empty());
}

// ============================================================
// print0x1015 tests - White Balance
// ============================================================

TEST_F(OlympusMakerNoteTest_886, Print0x1015_TwoValues_886) {
    UShortValue value;
    value.read("0 0");
    OlympusMakerNote::print0x1015(oss, value, nullptr);
    std::string result = oss.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(OlympusMakerNoteTest_886, Print0x1015_SingleValue_886) {
    UShortValue value;
    value.read("1");
    OlympusMakerNote::print0x1015(oss, value, nullptr);
    std::string result = oss.str();
    EXPECT_FALSE(result.empty());
}

// ============================================================
// print0x0201 tests - Quality/Compression
// ============================================================

TEST_F(OlympusMakerNoteTest_886, Print0x0201_MultipleValues_886) {
    UShortValue value;
    value.read("1 2");
    OlympusMakerNote::print0x0201(oss, value, nullptr);
    std::string result = oss.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(OlympusMakerNoteTest_886, Print0x0201_SingleValue_886) {
    UShortValue value;
    value.read("0");
    OlympusMakerNote::print0x0201(oss, value, nullptr);
    std::string result = oss.str();
    EXPECT_FALSE(result.empty());
}

// ============================================================
// print0x0209 tests - Camera ID
// ============================================================

TEST_F(OlympusMakerNoteTest_886, Print0x0209_NormalValue_886) {
    ULongValue value;
    value.read("0");
    OlympusMakerNote::print0x0209(oss, value, nullptr);
    std::string result = oss.str();
    EXPECT_FALSE(result.empty());
}

// ============================================================
// printEq0x0301 tests
// ============================================================

TEST_F(OlympusMakerNoteTest_886, PrintEq0x0301_SingleValue_886) {
    UShortValue value;
    value.read("0");
    OlympusMakerNote::printEq0x0301(oss, value, nullptr);
    std::string result = oss.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(OlympusMakerNoteTest_886, PrintEq0x0301_KnownValue_886) {
    UShortValue value;
    value.read("1");
    OlympusMakerNote::printEq0x0301(oss, value, nullptr);
    std::string result = oss.str();
    EXPECT_FALSE(result.empty());
}

// ============================================================
// printCs0x0301 tests - Camera Settings
// ============================================================

TEST_F(OlympusMakerNoteTest_886, PrintCs0x0301_NormalValue_886) {
    UShortValue value;
    value.read("0");
    OlympusMakerNote::printCs0x0301(oss, value, nullptr);
    std::string result = oss.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(OlympusMakerNoteTest_886, PrintCs0x0301_KnownValue_886) {
    UShortValue value;
    value.read("1");
    OlympusMakerNote::printCs0x0301(oss, value, nullptr);
    std::string result = oss.str();
    EXPECT_FALSE(result.empty());
}

// ============================================================
// print0x050f tests - Focus/Area Mode
// ============================================================

TEST_F(OlympusMakerNoteTest_886, Print0x050f_SingleValue_886) {
    UShortValue value;
    value.read("0");
    OlympusMakerNote::print0x050f(oss, value, nullptr);
    std::string result = oss.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(OlympusMakerNoteTest_886, Print0x050f_MultipleValues_886) {
    UShortValue value;
    value.read("0 1");
    OlympusMakerNote::print0x050f(oss, value, nullptr);
    std::string result = oss.str();
    EXPECT_FALSE(result.empty());
}

// ============================================================
// print0x0527 tests
// ============================================================

TEST_F(OlympusMakerNoteTest_886, Print0x0527_NormalValue_886) {
    UShortValue value;
    value.read("0");
    OlympusMakerNote::print0x0527(oss, value, nullptr);
    std::string result = oss.str();
    EXPECT_FALSE(result.empty());
}

// ============================================================
// print0x0529 tests
// ============================================================

TEST_F(OlympusMakerNoteTest_886, Print0x0529_NormalValue_886) {
    UShortValue value;
    value.read("0");
    OlympusMakerNote::print0x0529(oss, value, nullptr);
    std::string result = oss.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(OlympusMakerNoteTest_886, Print0x0529_WithMetadata_886) {
    ExifData exifData;
    UShortValue value;
    value.read("1");
    OlympusMakerNote::print0x0529(oss, value, &exifData);
    std::string result = oss.str();
    EXPECT_FALSE(result.empty());
}

// ============================================================
// print0x1209 tests
// ============================================================

TEST_F(OlympusMakerNoteTest_886, Print0x1209_NormalValue_886) {
    UShortValue value;
    value.read("0");
    OlympusMakerNote::print0x1209(oss, value, nullptr);
    std::string result = oss.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(OlympusMakerNoteTest_886, Print0x1209_KnownValue_886) {
    UShortValue value;
    value.read("1");
    OlympusMakerNote::print0x1209(oss, value, nullptr);
    std::string result = oss.str();
    EXPECT_FALSE(result.empty());
}

// ============================================================
// print0x0305 tests
// ============================================================

TEST_F(OlympusMakerNoteTest_886, Print0x0305_NormalValue_886) {
    UShortValue value;
    value.read("0");
    OlympusMakerNote::print0x0305(oss, value, nullptr);
    std::string result = oss.str();
    EXPECT_FALSE(result.empty());
}

// ============================================================
// print0x0308 tests
// ============================================================

TEST_F(OlympusMakerNoteTest_886, Print0x0308_NormalValue_886) {
    UShortValue value;
    value.read("0");
    OlympusMakerNote::print0x0308(oss, value, nullptr);
    std::string result = oss.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(OlympusMakerNoteTest_886, Print0x0308_WithMetadata_886) {
    ExifData exifData;
    UShortValue value;
    value.read("1");
    OlympusMakerNote::print0x0308(oss, value, &exifData);
    std::string result = oss.str();
    EXPECT_FALSE(result.empty());
}

// ============================================================
// Other tagList tests
// ============================================================

TEST_F(OlympusMakerNoteTest_886, TagListCsIsNotNull_886) {
    auto tagList = OlympusMakerNote::tagListCs();
    ASSERT_NE(tagList, nullptr);
}

TEST_F(OlympusMakerNoteTest_886, TagListEqIsNotNull_886) {
    auto tagList = OlympusMakerNote::tagListEq();
    ASSERT_NE(tagList, nullptr);
}

TEST_F(OlympusMakerNoteTest_886, TagListRdIsNotNull_886) {
    auto tagList = OlympusMakerNote::tagListRd();
    ASSERT_NE(tagList, nullptr);
}

TEST_F(OlympusMakerNoteTest_886, TagListRd2IsNotNull_886) {
    auto tagList = OlympusMakerNote::tagListRd2();
    ASSERT_NE(tagList, nullptr);
}

TEST_F(OlympusMakerNoteTest_886, TagListIpIsNotNull_886) {
    auto tagList = OlympusMakerNote::tagListIp();
    ASSERT_NE(tagList, nullptr);
}

TEST_F(OlympusMakerNoteTest_886, TagListFiIsNotNull_886) {
    auto tagList = OlympusMakerNote::tagListFi();
    ASSERT_NE(tagList, nullptr);
}

TEST_F(OlympusMakerNoteTest_886, TagListFeIsNotNull_886) {
    auto tagList = OlympusMakerNote::tagListFe();
    ASSERT_NE(tagList, nullptr);
}

TEST_F(OlympusMakerNoteTest_886, TagListRiIsNotNull_886) {
    auto tagList = OlympusMakerNote::tagListRi();
    ASSERT_NE(tagList, nullptr);
}

// ============================================================
// Return value verification tests - ensure stream reference is returned
// ============================================================

TEST_F(OlympusMakerNoteTest_886, Print0x0200_ReturnsStreamReference_886) {
    UShortValue value;
    value.read("0");
    std::ostream& ret = OlympusMakerNote::print0x0200(oss, value, nullptr);
    EXPECT_EQ(&ret, &oss);
}

TEST_F(OlympusMakerNoteTest_886, Print0x0204_ReturnsStreamReference_886) {
    URationalValue value;
    value.read("0/1");
    std::ostream& ret = OlympusMakerNote::print0x0204(oss, value, nullptr);
    EXPECT_EQ(&ret, &oss);
}

TEST_F(OlympusMakerNoteTest_886, Print0x1015_ReturnsStreamReference_886) {
    UShortValue value;
    value.read("0");
    std::ostream& ret = OlympusMakerNote::print0x1015(oss, value, nullptr);
    EXPECT_EQ(&ret, &oss);
}

TEST_F(OlympusMakerNoteTest_886, Print0x0201_ReturnsStreamReference_886) {
    UShortValue value;
    value.read("0");
    std::ostream& ret = OlympusMakerNote::print0x0201(oss, value, nullptr);
    EXPECT_EQ(&ret, &oss);
}

TEST_F(OlympusMakerNoteTest_886, PrintEq0x0301_ReturnsStreamReference_886) {
    UShortValue value;
    value.read("0");
    std::ostream& ret = OlympusMakerNote::printEq0x0301(oss, value, nullptr);
    EXPECT_EQ(&ret, &oss);
}

TEST_F(OlympusMakerNoteTest_886, PrintCs0x0301_ReturnsStreamReference_886) {
    UShortValue value;
    value.read("0");
    std::ostream& ret = OlympusMakerNote::printCs0x0301(oss, value, nullptr);
    EXPECT_EQ(&ret, &oss);
}

TEST_F(OlympusMakerNoteTest_886, Print0x050f_ReturnsStreamReference_886) {
    UShortValue value;
    value.read("0");
    std::ostream& ret = OlympusMakerNote::print0x050f(oss, value, nullptr);
    EXPECT_EQ(&ret, &oss);
}

TEST_F(OlympusMakerNoteTest_886, Print0x0527_ReturnsStreamReference_886) {
    UShortValue value;
    value.read("0");
    std::ostream& ret = OlympusMakerNote::print0x0527(oss, value, nullptr);
    EXPECT_EQ(&ret, &oss);
}

TEST_F(OlympusMakerNoteTest_886, Print0x0529_ReturnsStreamReference_886) {
    UShortValue value;
    value.read("0");
    std::ostream& ret = OlympusMakerNote::print0x0529(oss, value, nullptr);
    EXPECT_EQ(&ret, &oss);
}

TEST_F(OlympusMakerNoteTest_886, Print0x1209_ReturnsStreamReference_886) {
    UShortValue value;
    value.read("0");
    std::ostream& ret = OlympusMakerNote::print0x1209(oss, value, nullptr);
    EXPECT_EQ(&ret, &oss);
}

TEST_F(OlympusMakerNoteTest_886, Print0x0305_ReturnsStreamReference_886) {
    UShortValue value;
    value.read("0");
    std::ostream& ret = OlympusMakerNote::print0x0305(oss, value, nullptr);
    EXPECT_EQ(&ret, &oss);
}

TEST_F(OlympusMakerNoteTest_886, Print0x0308_ReturnsStreamReference_886) {
    UShortValue value;
    value.read("0");
    std::ostream& ret = OlympusMakerNote::print0x0308(oss, value, nullptr);
    EXPECT_EQ(&ret, &oss);
}

TEST_F(OlympusMakerNoteTest_886, Print0x0209_ReturnsStreamReference_886) {
    ULongValue value;
    value.read("0");
    std::ostream& ret = OlympusMakerNote::print0x0209(oss, value, nullptr);
    EXPECT_EQ(&ret, &oss);
}

// ============================================================
// Boundary / edge case tests
// ============================================================

TEST_F(OlympusMakerNoteTest_886, Print0x0200_LargeValue_886) {
    UShortValue value;
    value.read("65535");
    OlympusMakerNote::print0x0200(oss, value, nullptr);
    std::string result = oss.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(OlympusMakerNoteTest_886, Print0x0209_LargeValue_886) {
    ULongValue value;
    value.read("4294967295");
    OlympusMakerNote::print0x0209(oss, value, nullptr);
    std::string result = oss.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(OlympusMakerNoteTest_886, TagListFirstEntrySane_886) {
    auto tagList = OlympusMakerNote::tagList();
    // Tag info should have a non-null title
    EXPECT_NE(tagList[0].title_, nullptr);
}

TEST_F(OlympusMakerNoteTest_886, TagListCsFirstEntrySane_886) {
    auto tagList = OlympusMakerNote::tagListCs();
    EXPECT_NE(tagList[0].title_, nullptr);
}

TEST_F(OlympusMakerNoteTest_886, TagListEqFirstEntrySane_886) {
    auto tagList = OlympusMakerNote::tagListEq();
    EXPECT_NE(tagList[0].title_, nullptr);
}
