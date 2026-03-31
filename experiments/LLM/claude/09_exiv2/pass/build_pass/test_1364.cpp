#include <gtest/gtest.h>
#include "exiv2/tags.hpp"

// Forward declare the internal function we're testing
namespace Exiv2 {
namespace Internal {
bool isExifIfd(IfdId ifdId);
}
}

using Exiv2::IfdId;
using Exiv2::Internal::isExifIfd;

class IsExifIfdTest_1364 : public ::testing::Test {};

// Tests for IFD IDs that should return true

TEST_F(IsExifIfdTest_1364, Ifd0Id_ReturnsTrue_1364) {
    EXPECT_TRUE(isExifIfd(IfdId::ifd0Id));
}

TEST_F(IsExifIfdTest_1364, ExifId_ReturnsTrue_1364) {
    EXPECT_TRUE(isExifIfd(IfdId::exifId));
}

TEST_F(IsExifIfdTest_1364, GpsId_ReturnsTrue_1364) {
    EXPECT_TRUE(isExifIfd(IfdId::gpsId));
}

TEST_F(IsExifIfdTest_1364, IopId_ReturnsTrue_1364) {
    EXPECT_TRUE(isExifIfd(IfdId::iopId));
}

TEST_F(IsExifIfdTest_1364, Ifd1Id_ReturnsTrue_1364) {
    EXPECT_TRUE(isExifIfd(IfdId::ifd1Id));
}

TEST_F(IsExifIfdTest_1364, Ifd2Id_ReturnsTrue_1364) {
    EXPECT_TRUE(isExifIfd(IfdId::ifd2Id));
}

TEST_F(IsExifIfdTest_1364, Ifd3Id_ReturnsTrue_1364) {
    EXPECT_TRUE(isExifIfd(IfdId::ifd3Id));
}

TEST_F(IsExifIfdTest_1364, MpfId_ReturnsTrue_1364) {
    EXPECT_TRUE(isExifIfd(IfdId::mpfId));
}

TEST_F(IsExifIfdTest_1364, SubImage1Id_ReturnsTrue_1364) {
    EXPECT_TRUE(isExifIfd(IfdId::subImage1Id));
}

TEST_F(IsExifIfdTest_1364, SubImage2Id_ReturnsTrue_1364) {
    EXPECT_TRUE(isExifIfd(IfdId::subImage2Id));
}

TEST_F(IsExifIfdTest_1364, SubImage3Id_ReturnsTrue_1364) {
    EXPECT_TRUE(isExifIfd(IfdId::subImage3Id));
}

TEST_F(IsExifIfdTest_1364, SubImage4Id_ReturnsTrue_1364) {
    EXPECT_TRUE(isExifIfd(IfdId::subImage4Id));
}

TEST_F(IsExifIfdTest_1364, SubImage5Id_ReturnsTrue_1364) {
    EXPECT_TRUE(isExifIfd(IfdId::subImage5Id));
}

TEST_F(IsExifIfdTest_1364, SubImage6Id_ReturnsTrue_1364) {
    EXPECT_TRUE(isExifIfd(IfdId::subImage6Id));
}

TEST_F(IsExifIfdTest_1364, SubImage7Id_ReturnsTrue_1364) {
    EXPECT_TRUE(isExifIfd(IfdId::subImage7Id));
}

TEST_F(IsExifIfdTest_1364, SubImage8Id_ReturnsTrue_1364) {
    EXPECT_TRUE(isExifIfd(IfdId::subImage8Id));
}

TEST_F(IsExifIfdTest_1364, SubImage9Id_ReturnsTrue_1364) {
    EXPECT_TRUE(isExifIfd(IfdId::subImage9Id));
}

TEST_F(IsExifIfdTest_1364, SubThumb1Id_ReturnsTrue_1364) {
    EXPECT_TRUE(isExifIfd(IfdId::subThumb1Id));
}

TEST_F(IsExifIfdTest_1364, PanaRawId_ReturnsTrue_1364) {
    EXPECT_TRUE(isExifIfd(IfdId::panaRawId));
}

// Tests for IFD IDs that should return false

TEST_F(IsExifIfdTest_1364, IfdIdNotSet_ReturnsFalse_1364) {
    EXPECT_FALSE(isExifIfd(IfdId::ifdIdNotSet));
}

TEST_F(IsExifIfdTest_1364, MnId_ReturnsFalse_1364) {
    EXPECT_FALSE(isExifIfd(IfdId::mnId));
}

TEST_F(IsExifIfdTest_1364, CanonId_ReturnsFalse_1364) {
    EXPECT_FALSE(isExifIfd(IfdId::canonId));
}

TEST_F(IsExifIfdTest_1364, CanonCsId_ReturnsFalse_1364) {
    EXPECT_FALSE(isExifIfd(IfdId::canonCsId));
}

TEST_F(IsExifIfdTest_1364, NikonId_ReturnsFalse_1364) {
    EXPECT_FALSE(isExifIfd(IfdId::nikon1Id));
}

TEST_F(IsExifIfdTest_1364, Nikon2Id_ReturnsFalse_1364) {
    EXPECT_FALSE(isExifIfd(IfdId::nikon2Id));
}

TEST_F(IsExifIfdTest_1364, Nikon3Id_ReturnsFalse_1364) {
    EXPECT_FALSE(isExifIfd(IfdId::nikon3Id));
}

TEST_F(IsExifIfdTest_1364, OlympusId_ReturnsFalse_1364) {
    EXPECT_FALSE(isExifIfd(IfdId::olympusId));
}

TEST_F(IsExifIfdTest_1364, Olympus2Id_ReturnsFalse_1364) {
    EXPECT_FALSE(isExifIfd(IfdId::olympus2Id));
}

TEST_F(IsExifIfdTest_1364, PanasonicId_ReturnsFalse_1364) {
    EXPECT_FALSE(isExifIfd(IfdId::panasonicId));
}

TEST_F(IsExifIfdTest_1364, PentaxId_ReturnsFalse_1364) {
    EXPECT_FALSE(isExifIfd(IfdId::pentaxId));
}

TEST_F(IsExifIfdTest_1364, SigmaId_ReturnsFalse_1364) {
    EXPECT_FALSE(isExifIfd(IfdId::sigmaId));
}

TEST_F(IsExifIfdTest_1364, Sony1Id_ReturnsFalse_1364) {
    EXPECT_FALSE(isExifIfd(IfdId::sony1Id));
}

TEST_F(IsExifIfdTest_1364, Sony2Id_ReturnsFalse_1364) {
    EXPECT_FALSE(isExifIfd(IfdId::sony2Id));
}

TEST_F(IsExifIfdTest_1364, FujiId_ReturnsFalse_1364) {
    EXPECT_FALSE(isExifIfd(IfdId::fujiId));
}

TEST_F(IsExifIfdTest_1364, MinoltaId_ReturnsFalse_1364) {
    EXPECT_FALSE(isExifIfd(IfdId::minoltaId));
}

TEST_F(IsExifIfdTest_1364, CasioId_ReturnsFalse_1364) {
    EXPECT_FALSE(isExifIfd(IfdId::casioId));
}

TEST_F(IsExifIfdTest_1364, Casio2Id_ReturnsFalse_1364) {
    EXPECT_FALSE(isExifIfd(IfdId::casio2Id));
}

TEST_F(IsExifIfdTest_1364, Samsung2Id_ReturnsFalse_1364) {
    EXPECT_FALSE(isExifIfd(IfdId::samsung2Id));
}

TEST_F(IsExifIfdTest_1364, LastId_ReturnsFalse_1364) {
    EXPECT_FALSE(isExifIfd(IfdId::lastId));
}

TEST_F(IsExifIfdTest_1364, IgnoreId_ReturnsFalse_1364) {
    EXPECT_FALSE(isExifIfd(IfdId::ignoreId));
}

// Boundary: the ID just after the last true ID (panaRawId = 19, mnId = 20)
TEST_F(IsExifIfdTest_1364, BoundaryAfterPanaRaw_MnId_ReturnsFalse_1364) {
    EXPECT_FALSE(isExifIfd(IfdId::mnId));
}

// Test with various maker note sub-IDs
TEST_F(IsExifIfdTest_1364, CanonAfCId_ReturnsFalse_1364) {
    EXPECT_FALSE(isExifIfd(IfdId::canonAfCId));
}

TEST_F(IsExifIfdTest_1364, NikonAfId_ReturnsFalse_1364) {
    EXPECT_FALSE(isExifIfd(IfdId::nikonAfId));
}

TEST_F(IsExifIfdTest_1364, SonyMltId_ReturnsFalse_1364) {
    EXPECT_FALSE(isExifIfd(IfdId::sonyMltId));
}

TEST_F(IsExifIfdTest_1364, TagInfoMvId_ReturnsFalse_1364) {
    EXPECT_FALSE(isExifIfd(IfdId::tagInfoMvId));
}

TEST_F(IsExifIfdTest_1364, PentaxDngId_ReturnsFalse_1364) {
    EXPECT_FALSE(isExifIfd(IfdId::pentaxDngId));
}
