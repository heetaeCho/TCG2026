#include <gtest/gtest.h>
#include "exiv2/tags.hpp"
#include "tags_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class IfdNameTest_1370 : public ::testing::Test {
protected:
};

// Test normal operation: known IFD IDs return the expected names
TEST_F(IfdNameTest_1370, ReturnsCorrectNameForIfdIdNotSet_1370) {
    const char* result = ifdName(IfdId::ifdIdNotSet);
    EXPECT_STREQ(result, "Unknown IFD");
}

TEST_F(IfdNameTest_1370, ReturnsCorrectNameForIfd0Id_1370) {
    const char* result = ifdName(IfdId::ifd0Id);
    EXPECT_STREQ(result, "IFD0");
}

TEST_F(IfdNameTest_1370, ReturnsCorrectNameForIfd1Id_1370) {
    const char* result = ifdName(IfdId::ifd1Id);
    EXPECT_STREQ(result, "IFD1");
}

TEST_F(IfdNameTest_1370, ReturnsCorrectNameForIfd2Id_1370) {
    const char* result = ifdName(IfdId::ifd2Id);
    EXPECT_STREQ(result, "IFD2");
}

TEST_F(IfdNameTest_1370, ReturnsCorrectNameForIfd3Id_1370) {
    const char* result = ifdName(IfdId::ifd3Id);
    EXPECT_STREQ(result, "IFD3");
}

TEST_F(IfdNameTest_1370, ReturnsCorrectNameForExifId_1370) {
    const char* result = ifdName(IfdId::exifId);
    EXPECT_STREQ(result, "Exif");
}

TEST_F(IfdNameTest_1370, ReturnsCorrectNameForGpsId_1370) {
    const char* result = ifdName(IfdId::gpsId);
    EXPECT_STREQ(result, "GPSInfo");
}

TEST_F(IfdNameTest_1370, ReturnsCorrectNameForIopId_1370) {
    const char* result = ifdName(IfdId::iopId);
    EXPECT_STREQ(result, "Iop");
}

TEST_F(IfdNameTest_1370, ReturnsCorrectNameForMpfId_1370) {
    const char* result = ifdName(IfdId::mpfId);
    EXPECT_STREQ(result, "MPF");
}

TEST_F(IfdNameTest_1370, ReturnsCorrectNameForSubImage1Id_1370) {
    const char* result = ifdName(IfdId::subImage1Id);
    EXPECT_STREQ(result, "SubImage1");
}

TEST_F(IfdNameTest_1370, ReturnsCorrectNameForMnId_1370) {
    const char* result = ifdName(IfdId::mnId);
    EXPECT_STREQ(result, "Makernote");
}

TEST_F(IfdNameTest_1370, ReturnsCorrectNameForCanonId_1370) {
    const char* result = ifdName(IfdId::canonId);
    EXPECT_STREQ(result, "Makernote");
}

TEST_F(IfdNameTest_1370, ReturnsCorrectNameForNikon3Id_1370) {
    const char* result = ifdName(IfdId::nikon3Id);
    EXPECT_STREQ(result, "Makernote");
}

TEST_F(IfdNameTest_1370, ReturnsCorrectNameForOlympusId_1370) {
    const char* result = ifdName(IfdId::olympusId);
    EXPECT_STREQ(result, "Makernote");
}

TEST_F(IfdNameTest_1370, ReturnsCorrectNameForPanasonicId_1370) {
    const char* result = ifdName(IfdId::panasonicId);
    EXPECT_STREQ(result, "Makernote");
}

TEST_F(IfdNameTest_1370, ReturnsCorrectNameForSony1Id_1370) {
    const char* result = ifdName(IfdId::sony1Id);
    EXPECT_STREQ(result, "Makernote");
}

TEST_F(IfdNameTest_1370, ReturnsCorrectNameForPanaRawId_1370) {
    const char* result = ifdName(IfdId::panaRawId);
    EXPECT_STREQ(result, "PanaRaw");
}

TEST_F(IfdNameTest_1370, ReturnsCorrectNameForSubThumb1Id_1370) {
    const char* result = ifdName(IfdId::subThumb1Id);
    EXPECT_STREQ(result, "SubThumb1");
}

// Test boundary: last valid entry in groupInfo
TEST_F(IfdNameTest_1370, ReturnsCorrectNameForLastId_1370) {
    const char* result = ifdName(IfdId::lastId);
    EXPECT_STREQ(result, "(Last IFD info)");
}

// Test that the result is not null for any known IFD
TEST_F(IfdNameTest_1370, ResultIsNotNullForKnownIds_1370) {
    EXPECT_NE(ifdName(IfdId::ifd0Id), nullptr);
    EXPECT_NE(ifdName(IfdId::exifId), nullptr);
    EXPECT_NE(ifdName(IfdId::gpsId), nullptr);
    EXPECT_NE(ifdName(IfdId::canonId), nullptr);
}

// Test error/fallback: an unknown IFD ID should return the default (first entry's name)
TEST_F(IfdNameTest_1370, ReturnsDefaultNameForUnknownIfdId_1370) {
    // Cast an invalid value to IfdId to simulate an unknown ID
    const char* result = ifdName(static_cast<IfdId>(99999));
    EXPECT_STREQ(result, "Unknown IFD");
}

TEST_F(IfdNameTest_1370, ReturnsDefaultNameForNegativeIfdId_1370) {
    const char* result = ifdName(static_cast<IfdId>(-1));
    EXPECT_STREQ(result, "Unknown IFD");
}

// Test various sub-image IDs
TEST_F(IfdNameTest_1370, ReturnsCorrectNameForSubImage9Id_1370) {
    const char* result = ifdName(IfdId::subImage9Id);
    EXPECT_STREQ(result, "SubImage9");
}

TEST_F(IfdNameTest_1370, ReturnsCorrectNameForSubImage5Id_1370) {
    const char* result = ifdName(IfdId::subImage5Id);
    EXPECT_STREQ(result, "SubImage5");
}

// Test some specific maker note sub-groups
TEST_F(IfdNameTest_1370, ReturnsCorrectNameForFujiId_1370) {
    const char* result = ifdName(IfdId::fujiId);
    EXPECT_STREQ(result, "Makernote");
}

TEST_F(IfdNameTest_1370, ReturnsCorrectNameForSigmaId_1370) {
    const char* result = ifdName(IfdId::sigmaId);
    EXPECT_STREQ(result, "Makernote");
}

TEST_F(IfdNameTest_1370, ReturnsCorrectNameForPentaxId_1370) {
    const char* result = ifdName(IfdId::pentaxId);
    EXPECT_STREQ(result, "Makernote");
}

TEST_F(IfdNameTest_1370, ReturnsCorrectNameForSamsung2Id_1370) {
    const char* result = ifdName(IfdId::samsung2Id);
    EXPECT_STREQ(result, "Makernote");
}

TEST_F(IfdNameTest_1370, ReturnsCorrectNameForMinoltaId_1370) {
    const char* result = ifdName(IfdId::minoltaId);
    EXPECT_STREQ(result, "Makernote");
}

TEST_F(IfdNameTest_1370, ReturnsCorrectNameForCasioId_1370) {
    const char* result = ifdName(IfdId::casioId);
    EXPECT_STREQ(result, "Makernote");
}

// Test that the return value is a valid C string (not empty for known IDs)
TEST_F(IfdNameTest_1370, ReturnedStringIsNonEmptyForKnownIds_1370) {
    const char* result = ifdName(IfdId::ifd0Id);
    EXPECT_GT(strlen(result), 0u);
}

TEST_F(IfdNameTest_1370, ReturnedStringIsNonEmptyForDefaultFallback_1370) {
    const char* result = ifdName(static_cast<IfdId>(99999));
    EXPECT_GT(strlen(result), 0u);
}

// Verify Nikon preview IFD
TEST_F(IfdNameTest_1370, ReturnsCorrectNameForNikonPvId_1370) {
    const char* result = ifdName(IfdId::nikonPvId);
    EXPECT_STREQ(result, "Makernote");
}

// Verify Sony2010e
TEST_F(IfdNameTest_1370, ReturnsCorrectNameForSony2010eId_1370) {
    const char* result = ifdName(IfdId::sony2010eId);
    EXPECT_STREQ(result, "Makernote");
}
