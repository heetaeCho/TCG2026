#include <gtest/gtest.h>
#include "exiv2/tags.hpp"
#include "tags_int.hpp"

namespace Exiv2 {
namespace Internal {

// Test fixture for isMakerIfd tests
class IsMakerIfdTest_1363 : public ::testing::Test {
protected:
    // No setup needed - we're testing a free function
};

// Test that known Makernote IFD IDs return true
TEST_F(IsMakerIfdTest_1363, MnIdReturnsTrueForMakernote_1363) {
    EXPECT_TRUE(isMakerIfd(IfdId::mnId));
}

TEST_F(IsMakerIfdTest_1363, CanonIdReturnsTrueForMakernote_1363) {
    EXPECT_TRUE(isMakerIfd(IfdId::canonId));
}

TEST_F(IsMakerIfdTest_1363, CanonCsIdReturnsTrueForMakernote_1363) {
    EXPECT_TRUE(isMakerIfd(IfdId::canonCsId));
}

TEST_F(IsMakerIfdTest_1363, CanonSiIdReturnsTrueForMakernote_1363) {
    EXPECT_TRUE(isMakerIfd(IfdId::canonSiId));
}

TEST_F(IsMakerIfdTest_1363, NikonIds_ReturnTrueForMakernote_1363) {
    EXPECT_TRUE(isMakerIfd(IfdId::nikon1Id));
    EXPECT_TRUE(isMakerIfd(IfdId::nikon2Id));
    EXPECT_TRUE(isMakerIfd(IfdId::nikon3Id));
    EXPECT_TRUE(isMakerIfd(IfdId::nikonPvId));
    EXPECT_TRUE(isMakerIfd(IfdId::nikonVrId));
    EXPECT_TRUE(isMakerIfd(IfdId::nikonPcId));
    EXPECT_TRUE(isMakerIfd(IfdId::nikonWtId));
    EXPECT_TRUE(isMakerIfd(IfdId::nikonIiId));
    EXPECT_TRUE(isMakerIfd(IfdId::nikonAfId));
    EXPECT_TRUE(isMakerIfd(IfdId::nikonAf21Id));
    EXPECT_TRUE(isMakerIfd(IfdId::nikonAf22Id));
    EXPECT_TRUE(isMakerIfd(IfdId::nikonAFTId));
    EXPECT_TRUE(isMakerIfd(IfdId::nikonFiId));
    EXPECT_TRUE(isMakerIfd(IfdId::nikonMeId));
    EXPECT_TRUE(isMakerIfd(IfdId::nikonFl1Id));
    EXPECT_TRUE(isMakerIfd(IfdId::nikonFl2Id));
    EXPECT_TRUE(isMakerIfd(IfdId::nikonFl3Id));
    EXPECT_TRUE(isMakerIfd(IfdId::nikonFl6Id));
    EXPECT_TRUE(isMakerIfd(IfdId::nikonFl7Id));
    EXPECT_TRUE(isMakerIfd(IfdId::nikonSi1Id));
    EXPECT_TRUE(isMakerIfd(IfdId::nikonSi2Id));
    EXPECT_TRUE(isMakerIfd(IfdId::nikonSi3Id));
    EXPECT_TRUE(isMakerIfd(IfdId::nikonSi4Id));
    EXPECT_TRUE(isMakerIfd(IfdId::nikonSi5Id));
    EXPECT_TRUE(isMakerIfd(IfdId::nikonSi6Id));
    EXPECT_TRUE(isMakerIfd(IfdId::nikonCb1Id));
    EXPECT_TRUE(isMakerIfd(IfdId::nikonCb2Id));
    EXPECT_TRUE(isMakerIfd(IfdId::nikonCb2aId));
    EXPECT_TRUE(isMakerIfd(IfdId::nikonCb2bId));
    EXPECT_TRUE(isMakerIfd(IfdId::nikonCb3Id));
    EXPECT_TRUE(isMakerIfd(IfdId::nikonCb4Id));
    EXPECT_TRUE(isMakerIfd(IfdId::nikonLd1Id));
    EXPECT_TRUE(isMakerIfd(IfdId::nikonLd2Id));
    EXPECT_TRUE(isMakerIfd(IfdId::nikonLd3Id));
    EXPECT_TRUE(isMakerIfd(IfdId::nikonLd4Id));
}

TEST_F(IsMakerIfdTest_1363, OlympusIds_ReturnTrueForMakernote_1363) {
    EXPECT_TRUE(isMakerIfd(IfdId::olympusId));
    EXPECT_TRUE(isMakerIfd(IfdId::olympus2Id));
    EXPECT_TRUE(isMakerIfd(IfdId::olympusCsId));
    EXPECT_TRUE(isMakerIfd(IfdId::olympusEqId));
    EXPECT_TRUE(isMakerIfd(IfdId::olympusRdId));
    EXPECT_TRUE(isMakerIfd(IfdId::olympusRd2Id));
    EXPECT_TRUE(isMakerIfd(IfdId::olympusIpId));
    EXPECT_TRUE(isMakerIfd(IfdId::olympusFiId));
    EXPECT_TRUE(isMakerIfd(IfdId::olympusFe1Id));
    EXPECT_TRUE(isMakerIfd(IfdId::olympusRiId));
}

TEST_F(IsMakerIfdTest_1363, SonyIds_ReturnTrueForMakernote_1363) {
    EXPECT_TRUE(isMakerIfd(IfdId::sony1Id));
    EXPECT_TRUE(isMakerIfd(IfdId::sony2Id));
    EXPECT_TRUE(isMakerIfd(IfdId::sonyMltId));
    EXPECT_TRUE(isMakerIfd(IfdId::sony1CsId));
    EXPECT_TRUE(isMakerIfd(IfdId::sony1Cs2Id));
    EXPECT_TRUE(isMakerIfd(IfdId::sony2CsId));
    EXPECT_TRUE(isMakerIfd(IfdId::sony2Cs2Id));
    EXPECT_TRUE(isMakerIfd(IfdId::sony2FpId));
    EXPECT_TRUE(isMakerIfd(IfdId::sonyMisc1Id));
    EXPECT_TRUE(isMakerIfd(IfdId::sonyMisc2bId));
    EXPECT_TRUE(isMakerIfd(IfdId::sonyMisc3cId));
    EXPECT_TRUE(isMakerIfd(IfdId::sonySInfo1Id));
    EXPECT_TRUE(isMakerIfd(IfdId::sony2010eId));
}

TEST_F(IsMakerIfdTest_1363, PanasonicIdReturnsTrueForMakernote_1363) {
    EXPECT_TRUE(isMakerIfd(IfdId::panasonicId));
}

TEST_F(IsMakerIfdTest_1363, PentaxIds_ReturnTrueForMakernote_1363) {
    EXPECT_TRUE(isMakerIfd(IfdId::pentaxId));
    EXPECT_TRUE(isMakerIfd(IfdId::pentaxDngId));
}

TEST_F(IsMakerIfdTest_1363, SamsungIds_ReturnTrueForMakernote_1363) {
    EXPECT_TRUE(isMakerIfd(IfdId::samsung2Id));
    EXPECT_TRUE(isMakerIfd(IfdId::samsungPvId));
    EXPECT_TRUE(isMakerIfd(IfdId::samsungPwId));
}

TEST_F(IsMakerIfdTest_1363, SigmaIdReturnsTrueForMakernote_1363) {
    EXPECT_TRUE(isMakerIfd(IfdId::sigmaId));
}

TEST_F(IsMakerIfdTest_1363, FujiIdReturnsTrueForMakernote_1363) {
    EXPECT_TRUE(isMakerIfd(IfdId::fujiId));
}

TEST_F(IsMakerIfdTest_1363, MinoltaIds_ReturnTrueForMakernote_1363) {
    EXPECT_TRUE(isMakerIfd(IfdId::minoltaId));
    EXPECT_TRUE(isMakerIfd(IfdId::minoltaCs5DId));
    EXPECT_TRUE(isMakerIfd(IfdId::minoltaCs7DId));
    EXPECT_TRUE(isMakerIfd(IfdId::minoltaCsOldId));
    EXPECT_TRUE(isMakerIfd(IfdId::minoltaCsNewId));
}

TEST_F(IsMakerIfdTest_1363, CasioIds_ReturnTrueForMakernote_1363) {
    EXPECT_TRUE(isMakerIfd(IfdId::casioId));
    EXPECT_TRUE(isMakerIfd(IfdId::casio2Id));
}

// Test that non-Makernote IFD IDs return false
TEST_F(IsMakerIfdTest_1363, Ifd0IdReturnsFalse_1363) {
    EXPECT_FALSE(isMakerIfd(IfdId::ifd0Id));
}

TEST_F(IsMakerIfdTest_1363, Ifd1IdReturnsFalse_1363) {
    EXPECT_FALSE(isMakerIfd(IfdId::ifd1Id));
}

TEST_F(IsMakerIfdTest_1363, Ifd2IdReturnsFalse_1363) {
    EXPECT_FALSE(isMakerIfd(IfdId::ifd2Id));
}

TEST_F(IsMakerIfdTest_1363, Ifd3IdReturnsFalse_1363) {
    EXPECT_FALSE(isMakerIfd(IfdId::ifd3Id));
}

TEST_F(IsMakerIfdTest_1363, ExifIdReturnsFalse_1363) {
    EXPECT_FALSE(isMakerIfd(IfdId::exifId));
}

TEST_F(IsMakerIfdTest_1363, GpsIdReturnsFalse_1363) {
    EXPECT_FALSE(isMakerIfd(IfdId::gpsId));
}

TEST_F(IsMakerIfdTest_1363, IopIdReturnsFalse_1363) {
    EXPECT_FALSE(isMakerIfd(IfdId::iopId));
}

TEST_F(IsMakerIfdTest_1363, MpfIdReturnsFalse_1363) {
    EXPECT_FALSE(isMakerIfd(IfdId::mpfId));
}

TEST_F(IsMakerIfdTest_1363, SubImageIdsReturnFalse_1363) {
    EXPECT_FALSE(isMakerIfd(IfdId::subImage1Id));
    EXPECT_FALSE(isMakerIfd(IfdId::subImage2Id));
    EXPECT_FALSE(isMakerIfd(IfdId::subImage3Id));
    EXPECT_FALSE(isMakerIfd(IfdId::subImage4Id));
    EXPECT_FALSE(isMakerIfd(IfdId::subImage5Id));
    EXPECT_FALSE(isMakerIfd(IfdId::subImage6Id));
    EXPECT_FALSE(isMakerIfd(IfdId::subImage7Id));
    EXPECT_FALSE(isMakerIfd(IfdId::subImage8Id));
    EXPECT_FALSE(isMakerIfd(IfdId::subImage9Id));
}

TEST_F(IsMakerIfdTest_1363, SubThumb1IdReturnsFalse_1363) {
    EXPECT_FALSE(isMakerIfd(IfdId::subThumb1Id));
}

TEST_F(IsMakerIfdTest_1363, PanaRawIdReturnsFalse_1363) {
    // PanaRaw has ifdName_ "PanaRaw", not "Makernote"
    EXPECT_FALSE(isMakerIfd(IfdId::panaRawId));
}

// Boundary: ifdIdNotSet - "Unknown IFD" is not "Makernote"
TEST_F(IsMakerIfdTest_1363, IfdIdNotSetReturnsFalse_1363) {
    EXPECT_FALSE(isMakerIfd(IfdId::ifdIdNotSet));
}

// Boundary: lastId - "(Last IFD info)" is not "Makernote"
TEST_F(IsMakerIfdTest_1363, LastIdReturnsFalse_1363) {
    EXPECT_FALSE(isMakerIfd(IfdId::lastId));
}

}  // namespace Internal
}  // namespace Exiv2
