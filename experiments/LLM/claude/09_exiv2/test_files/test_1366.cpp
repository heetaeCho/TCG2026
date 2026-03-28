#include <gtest/gtest.h>
#include "exiv2/tags.hpp"
#include "tags_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class TagListTest_1366 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that a known valid IfdId returns a non-null TagInfo pointer
TEST_F(TagListTest_1366, ReturnsNonNullForIfd0Id_1366) {
    const TagInfo* result = tagList(IfdId::ifd0Id);
    EXPECT_NE(result, nullptr);
}

// Test that a known valid IfdId (exifId) returns a non-null TagInfo pointer
TEST_F(TagListTest_1366, ReturnsNonNullForExifId_1366) {
    const TagInfo* result = tagList(IfdId::exifId);
    EXPECT_NE(result, nullptr);
}

// Test that a known valid IfdId (gpsId) returns a non-null TagInfo pointer
TEST_F(TagListTest_1366, ReturnsNonNullForGpsId_1366) {
    const TagInfo* result = tagList(IfdId::gpsId);
    EXPECT_NE(result, nullptr);
}

// Test that a known valid IfdId (iopId) returns a non-null TagInfo pointer
TEST_F(TagListTest_1366, ReturnsNonNullForIopId_1366) {
    const TagInfo* result = tagList(IfdId::iopId);
    EXPECT_NE(result, nullptr);
}

// Test that ifdIdNotSet has nullptr tagList_ and returns nullptr
TEST_F(TagListTest_1366, ReturnsNullForIfdIdNotSet_1366) {
    const TagInfo* result = tagList(IfdId::ifdIdNotSet);
    EXPECT_EQ(result, nullptr);
}

// Test that lastId has nullptr tagList_ and returns nullptr
TEST_F(TagListTest_1366, ReturnsNullForLastId_1366) {
    const TagInfo* result = tagList(IfdId::lastId);
    EXPECT_EQ(result, nullptr);
}

// Test that ifd1Id returns a non-null TagInfo pointer (Thumbnail)
TEST_F(TagListTest_1366, ReturnsNonNullForIfd1Id_1366) {
    const TagInfo* result = tagList(IfdId::ifd1Id);
    EXPECT_NE(result, nullptr);
}

// Test that ifd2Id returns a non-null TagInfo pointer
TEST_F(TagListTest_1366, ReturnsNonNullForIfd2Id_1366) {
    const TagInfo* result = tagList(IfdId::ifd2Id);
    EXPECT_NE(result, nullptr);
}

// Test that ifd3Id returns a non-null TagInfo pointer
TEST_F(TagListTest_1366, ReturnsNonNullForIfd3Id_1366) {
    const TagInfo* result = tagList(IfdId::ifd3Id);
    EXPECT_NE(result, nullptr);
}

// Test that mpfId returns a non-null TagInfo pointer
TEST_F(TagListTest_1366, ReturnsNonNullForMpfId_1366) {
    const TagInfo* result = tagList(IfdId::mpfId);
    EXPECT_NE(result, nullptr);
}

// Test that canonId returns a non-null TagInfo pointer
TEST_F(TagListTest_1366, ReturnsNonNullForCanonId_1366) {
    const TagInfo* result = tagList(IfdId::canonId);
    EXPECT_NE(result, nullptr);
}

// Test that nikonId returns a non-null TagInfo pointer
TEST_F(TagListTest_1366, ReturnsNonNullForNikon3Id_1366) {
    const TagInfo* result = tagList(IfdId::nikon3Id);
    EXPECT_NE(result, nullptr);
}

// Test that sony1Id returns a non-null TagInfo pointer
TEST_F(TagListTest_1366, ReturnsNonNullForSony1Id_1366) {
    const TagInfo* result = tagList(IfdId::sony1Id);
    EXPECT_NE(result, nullptr);
}

// Test that olympusId returns a non-null TagInfo pointer
TEST_F(TagListTest_1366, ReturnsNonNullForOlympusId_1366) {
    const TagInfo* result = tagList(IfdId::olympusId);
    EXPECT_NE(result, nullptr);
}

// Test that panasonicId returns a non-null TagInfo pointer
TEST_F(TagListTest_1366, ReturnsNonNullForPanasonicId_1366) {
    const TagInfo* result = tagList(IfdId::panasonicId);
    EXPECT_NE(result, nullptr);
}

// Test that pentaxId returns a non-null TagInfo pointer
TEST_F(TagListTest_1366, ReturnsNonNullForPentaxId_1366) {
    const TagInfo* result = tagList(IfdId::pentaxId);
    EXPECT_NE(result, nullptr);
}

// Test that sigmaId returns a non-null TagInfo pointer
TEST_F(TagListTest_1366, ReturnsNonNullForSigmaId_1366) {
    const TagInfo* result = tagList(IfdId::sigmaId);
    EXPECT_NE(result, nullptr);
}

// Test that fujiId returns a non-null TagInfo pointer
TEST_F(TagListTest_1366, ReturnsNonNullForFujiId_1366) {
    const TagInfo* result = tagList(IfdId::fujiId);
    EXPECT_NE(result, nullptr);
}

// Test that minoltaId returns a non-null TagInfo pointer
TEST_F(TagListTest_1366, ReturnsNonNullForMinoltaId_1366) {
    const TagInfo* result = tagList(IfdId::minoltaId);
    EXPECT_NE(result, nullptr);
}

// Test that casioId returns a non-null TagInfo pointer
TEST_F(TagListTest_1366, ReturnsNonNullForCasioId_1366) {
    const TagInfo* result = tagList(IfdId::casioId);
    EXPECT_NE(result, nullptr);
}

// Test that samsung2Id returns a non-null TagInfo pointer
TEST_F(TagListTest_1366, ReturnsNonNullForSamsung2Id_1366) {
    const TagInfo* result = tagList(IfdId::samsung2Id);
    EXPECT_NE(result, nullptr);
}

// Test that subImage1Id returns a non-null TagInfo pointer
TEST_F(TagListTest_1366, ReturnsNonNullForSubImage1Id_1366) {
    const TagInfo* result = tagList(IfdId::subImage1Id);
    EXPECT_NE(result, nullptr);
}

// Test that mnId (MakerNote) returns a non-null TagInfo pointer
TEST_F(TagListTest_1366, ReturnsNonNullForMnId_1366) {
    const TagInfo* result = tagList(IfdId::mnId);
    EXPECT_NE(result, nullptr);
}

// Test that panaRawId returns a non-null TagInfo pointer
TEST_F(TagListTest_1366, ReturnsNonNullForPanaRawId_1366) {
    const TagInfo* result = tagList(IfdId::panaRawId);
    EXPECT_NE(result, nullptr);
}

// Test that calling tagList with the same IfdId multiple times returns the same pointer
TEST_F(TagListTest_1366, ConsistentResultForSameId_1366) {
    const TagInfo* result1 = tagList(IfdId::exifId);
    const TagInfo* result2 = tagList(IfdId::exifId);
    EXPECT_EQ(result1, result2);
}

// Test that different known IfdIds with different tag lists return different pointers
TEST_F(TagListTest_1366, DifferentIdsReturnDifferentPointers_1366) {
    const TagInfo* exifResult = tagList(IfdId::exifId);
    const TagInfo* gpsResult = tagList(IfdId::gpsId);
    EXPECT_NE(exifResult, nullptr);
    EXPECT_NE(gpsResult, nullptr);
    EXPECT_NE(exifResult, gpsResult);
}

// Test that IfdIds sharing the same tag list function return the same pointer
TEST_F(TagListTest_1366, SameTagListFunctionReturnsSamePointer_1366) {
    // ifd0Id and ifd1Id both use &ifdTagList
    const TagInfo* ifd0Result = tagList(IfdId::ifd0Id);
    const TagInfo* ifd1Result = tagList(IfdId::ifd1Id);
    EXPECT_NE(ifd0Result, nullptr);
    EXPECT_NE(ifd1Result, nullptr);
    EXPECT_EQ(ifd0Result, ifd1Result);
}

// Test Canon sub-groups return non-null
TEST_F(TagListTest_1366, ReturnsNonNullForCanonCsId_1366) {
    const TagInfo* result = tagList(IfdId::canonCsId);
    EXPECT_NE(result, nullptr);
}

TEST_F(TagListTest_1366, ReturnsNonNullForCanonSiId_1366) {
    const TagInfo* result = tagList(IfdId::canonSiId);
    EXPECT_NE(result, nullptr);
}

// Test Nikon sub-groups return non-null
TEST_F(TagListTest_1366, ReturnsNonNullForNikonVrId_1366) {
    const TagInfo* result = tagList(IfdId::nikonVrId);
    EXPECT_NE(result, nullptr);
}

TEST_F(TagListTest_1366, ReturnsNonNullForNikonAfId_1366) {
    const TagInfo* result = tagList(IfdId::nikonAfId);
    EXPECT_NE(result, nullptr);
}

// Test Sony sub-groups
TEST_F(TagListTest_1366, ReturnsNonNullForSony1CsId_1366) {
    const TagInfo* result = tagList(IfdId::sony1CsId);
    EXPECT_NE(result, nullptr);
}

TEST_F(TagListTest_1366, ReturnsNonNullForSony2FpId_1366) {
    const TagInfo* result = tagList(IfdId::sony2FpId);
    EXPECT_NE(result, nullptr);
}

// Test Olympus sub-groups
TEST_F(TagListTest_1366, ReturnsNonNullForOlympusCsId_1366) {
    const TagInfo* result = tagList(IfdId::olympusCsId);
    EXPECT_NE(result, nullptr);
}

TEST_F(TagListTest_1366, ReturnsNonNullForOlympusEqId_1366) {
    const TagInfo* result = tagList(IfdId::olympusEqId);
    EXPECT_NE(result, nullptr);
}

// Test that olympusFe1Id through olympusFe9Id all return the same pointer (same tagListFe)
TEST_F(TagListTest_1366, OlympusFeSameTagList_1366) {
    const TagInfo* fe1 = tagList(IfdId::olympusFe1Id);
    const TagInfo* fe2 = tagList(IfdId::olympusFe2Id);
    const TagInfo* fe3 = tagList(IfdId::olympusFe3Id);
    EXPECT_NE(fe1, nullptr);
    EXPECT_EQ(fe1, fe2);
    EXPECT_EQ(fe2, fe3);
}

// Test Sony2010e returns non-null
TEST_F(TagListTest_1366, ReturnsNonNullForSony2010eId_1366) {
    const TagInfo* result = tagList(IfdId::sony2010eId);
    EXPECT_NE(result, nullptr);
}

// Test pentaxDngId returns non-null
TEST_F(TagListTest_1366, ReturnsNonNullForPentaxDngId_1366) {
    const TagInfo* result = tagList(IfdId::pentaxDngId);
    EXPECT_NE(result, nullptr);
}

// Test that pentaxId and pentaxDngId return the same tag list (both use &PentaxMakerNote::tagList)
TEST_F(TagListTest_1366, PentaxAndPentaxDngSameTagList_1366) {
    const TagInfo* pentax = tagList(IfdId::pentaxId);
    const TagInfo* pentaxDng = tagList(IfdId::pentaxDngId);
    EXPECT_NE(pentax, nullptr);
    EXPECT_EQ(pentax, pentaxDng);
}

// Test that sony1Id and sony2Id return the same tag list
TEST_F(TagListTest_1366, Sony1AndSony2SameTagList_1366) {
    const TagInfo* sony1 = tagList(IfdId::sony1Id);
    const TagInfo* sony2 = tagList(IfdId::sony2Id);
    EXPECT_NE(sony1, nullptr);
    EXPECT_EQ(sony1, sony2);
}

// Test nikon1Id and nikon2Id return different tag lists
TEST_F(TagListTest_1366, Nikon1AndNikon2DifferentTagLists_1366) {
    const TagInfo* n1 = tagList(IfdId::nikon1Id);
    const TagInfo* n2 = tagList(IfdId::nikon2Id);
    EXPECT_NE(n1, nullptr);
    EXPECT_NE(n2, nullptr);
    EXPECT_NE(n1, n2);
}
