#include <gtest/gtest.h>
#include <exiv2/tags.hpp>

// Declaration of the function under test
namespace Exiv2 {
namespace Internal {
IfdId groupId(const std::string& groupName);
}
}

using Exiv2::IfdId;
using Exiv2::Internal::groupId;

class GroupIdTest_1369 : public ::testing::Test {
protected:
};

// Normal operation tests - known group names from the groupInfo table

TEST_F(GroupIdTest_1369, ReturnsIfdIdNotSetForUnknownGroup_1369) {
    EXPECT_EQ(IfdId::ifdIdNotSet, groupId("Unknown"));
}

TEST_F(GroupIdTest_1369, ReturnsIfd0IdForImage_1369) {
    EXPECT_EQ(IfdId::ifd0Id, groupId("Image"));
}

TEST_F(GroupIdTest_1369, ReturnsIfd1IdForThumbnail_1369) {
    EXPECT_EQ(IfdId::ifd1Id, groupId("Thumbnail"));
}

TEST_F(GroupIdTest_1369, ReturnsIfd2IdForImage2_1369) {
    EXPECT_EQ(IfdId::ifd2Id, groupId("Image2"));
}

TEST_F(GroupIdTest_1369, ReturnsIfd3IdForImage3_1369) {
    EXPECT_EQ(IfdId::ifd3Id, groupId("Image3"));
}

TEST_F(GroupIdTest_1369, ReturnsExifIdForPhoto_1369) {
    EXPECT_EQ(IfdId::exifId, groupId("Photo"));
}

TEST_F(GroupIdTest_1369, ReturnsGpsIdForGPSInfo_1369) {
    EXPECT_EQ(IfdId::gpsId, groupId("GPSInfo"));
}

TEST_F(GroupIdTest_1369, ReturnsIopIdForIop_1369) {
    EXPECT_EQ(IfdId::iopId, groupId("Iop"));
}

TEST_F(GroupIdTest_1369, ReturnsMpfIdForMpfInfo_1369) {
    EXPECT_EQ(IfdId::mpfId, groupId("MpfInfo"));
}

TEST_F(GroupIdTest_1369, ReturnsSubImage1Id_1369) {
    EXPECT_EQ(IfdId::subImage1Id, groupId("SubImage1"));
}

TEST_F(GroupIdTest_1369, ReturnsSubImage9Id_1369) {
    EXPECT_EQ(IfdId::subImage9Id, groupId("SubImage9"));
}

TEST_F(GroupIdTest_1369, ReturnsSubThumb1Id_1369) {
    EXPECT_EQ(IfdId::subThumb1Id, groupId("SubThumb1"));
}

TEST_F(GroupIdTest_1369, ReturnsPanaRawIdForPanasonicRaw_1369) {
    EXPECT_EQ(IfdId::panaRawId, groupId("PanasonicRaw"));
}

TEST_F(GroupIdTest_1369, ReturnsMnIdForMakerNote_1369) {
    EXPECT_EQ(IfdId::mnId, groupId("MakerNote"));
}

TEST_F(GroupIdTest_1369, ReturnsCanonIdForCanon_1369) {
    EXPECT_EQ(IfdId::canonId, groupId("Canon"));
}

TEST_F(GroupIdTest_1369, ReturnsCanonCsIdForCanonCs_1369) {
    EXPECT_EQ(IfdId::canonCsId, groupId("CanonCs"));
}

TEST_F(GroupIdTest_1369, ReturnsFujiIdForFujifilm_1369) {
    EXPECT_EQ(IfdId::fujiId, groupId("Fujifilm"));
}

TEST_F(GroupIdTest_1369, ReturnsMinoltaIdForMinolta_1369) {
    EXPECT_EQ(IfdId::minoltaId, groupId("Minolta"));
}

TEST_F(GroupIdTest_1369, ReturnsNikon1IdForNikon1_1369) {
    EXPECT_EQ(IfdId::nikon1Id, groupId("Nikon1"));
}

TEST_F(GroupIdTest_1369, ReturnsNikon3IdForNikon3_1369) {
    EXPECT_EQ(IfdId::nikon3Id, groupId("Nikon3"));
}

TEST_F(GroupIdTest_1369, ReturnsOlympusIdForOlympus_1369) {
    EXPECT_EQ(IfdId::olympusId, groupId("Olympus"));
}

TEST_F(GroupIdTest_1369, ReturnsPanasonicIdForPanasonic_1369) {
    EXPECT_EQ(IfdId::panasonicId, groupId("Panasonic"));
}

TEST_F(GroupIdTest_1369, ReturnsPentaxIdForPentax_1369) {
    EXPECT_EQ(IfdId::pentaxId, groupId("Pentax"));
}

TEST_F(GroupIdTest_1369, ReturnsSigmaIdForSigma_1369) {
    EXPECT_EQ(IfdId::sigmaId, groupId("Sigma"));
}

TEST_F(GroupIdTest_1369, ReturnsSony1IdForSony1_1369) {
    EXPECT_EQ(IfdId::sony1Id, groupId("Sony1"));
}

TEST_F(GroupIdTest_1369, ReturnsSony2IdForSony2_1369) {
    EXPECT_EQ(IfdId::sony2Id, groupId("Sony2"));
}

TEST_F(GroupIdTest_1369, ReturnsSony2FpIdForSony2Fp_1369) {
    EXPECT_EQ(IfdId::sony2FpId, groupId("Sony2Fp"));
}

// Boundary condition tests

TEST_F(GroupIdTest_1369, ReturnsIfdIdNotSetForEmptyString_1369) {
    EXPECT_EQ(IfdId::ifdIdNotSet, groupId(""));
}

TEST_F(GroupIdTest_1369, ReturnsIfdIdNotSetForNonExistentGroupName_1369) {
    EXPECT_EQ(IfdId::ifdIdNotSet, groupId("NonExistentGroup"));
}

TEST_F(GroupIdTest_1369, ReturnsIfdIdNotSetForRandomString_1369) {
    EXPECT_EQ(IfdId::ifdIdNotSet, groupId("abcdefghijklmnop"));
}

// Case sensitivity tests

TEST_F(GroupIdTest_1369, IsCaseSensitiveLowercaseImage_1369) {
    EXPECT_EQ(IfdId::ifdIdNotSet, groupId("image"));
}

TEST_F(GroupIdTest_1369, IsCaseSensitiveUppercaseIMAGE_1369) {
    EXPECT_EQ(IfdId::ifdIdNotSet, groupId("IMAGE"));
}

TEST_F(GroupIdTest_1369, IsCaseSensitiveLowercasePhoto_1369) {
    EXPECT_EQ(IfdId::ifdIdNotSet, groupId("photo"));
}

TEST_F(GroupIdTest_1369, IsCaseSensitiveLowercaseCanon_1369) {
    EXPECT_EQ(IfdId::ifdIdNotSet, groupId("canon"));
}

// Near-match tests

TEST_F(GroupIdTest_1369, ReturnsIfdIdNotSetForPartialMatch_1369) {
    EXPECT_EQ(IfdId::ifdIdNotSet, groupId("Imag"));
}

TEST_F(GroupIdTest_1369, ReturnsIfdIdNotSetForExtraCharacters_1369) {
    EXPECT_EQ(IfdId::ifdIdNotSet, groupId("Image "));
}

TEST_F(GroupIdTest_1369, ReturnsIfdIdNotSetForLeadingSpace_1369) {
    EXPECT_EQ(IfdId::ifdIdNotSet, groupId(" Image"));
}

// Additional maker note group names

TEST_F(GroupIdTest_1369, ReturnsCasioIdForCasio_1369) {
    EXPECT_EQ(IfdId::casioId, groupId("Casio"));
}

TEST_F(GroupIdTest_1369, ReturnsCasio2IdForCasio2_1369) {
    EXPECT_EQ(IfdId::casio2Id, groupId("Casio2"));
}

TEST_F(GroupIdTest_1369, ReturnsSamsung2IdForSamsung2_1369) {
    EXPECT_EQ(IfdId::samsung2Id, groupId("Samsung2"));
}

TEST_F(GroupIdTest_1369, ReturnsPentaxDngIdForPentaxDng_1369) {
    EXPECT_EQ(IfdId::pentaxDngId, groupId("PentaxDng"));
}

TEST_F(GroupIdTest_1369, ReturnsNikonPreviewForNikonPreview_1369) {
    EXPECT_EQ(IfdId::nikonPvId, groupId("NikonPreview"));
}

TEST_F(GroupIdTest_1369, ReturnsLastIdForLastIFDItem_1369) {
    EXPECT_EQ(IfdId::lastId, groupId("(Last IFD item)"));
}

TEST_F(GroupIdTest_1369, ReturnsSonyMisc1IdForSonyMisc1_1369) {
    EXPECT_EQ(IfdId::sonyMisc1Id, groupId("SonyMisc1"));
}

TEST_F(GroupIdTest_1369, ReturnsSony2010eIdForSony2010e_1369) {
    EXPECT_EQ(IfdId::sony2010eId, groupId("Sony2010e"));
}

TEST_F(GroupIdTest_1369, ReturnsCanonSiIdForCanonSi_1369) {
    EXPECT_EQ(IfdId::canonSiId, groupId("CanonSi"));
}

TEST_F(GroupIdTest_1369, ReturnsCanonCfIdForCanonCf_1369) {
    EXPECT_EQ(IfdId::canonCfId, groupId("CanonCf"));
}

TEST_F(GroupIdTest_1369, ReturnsOlympus2IdForOlympus2_1369) {
    EXPECT_EQ(IfdId::olympus2Id, groupId("Olympus2"));
}

TEST_F(GroupIdTest_1369, ReturnsSonyMinoltaForSonyMinolta_1369) {
    EXPECT_EQ(IfdId::sonyMltId, groupId("SonyMinolta"));
}

TEST_F(GroupIdTest_1369, ReturnsMinoltaCs5DForMinoltaCs5D_1369) {
    EXPECT_EQ(IfdId::minoltaCs5DId, groupId("MinoltaCs5D"));
}

TEST_F(GroupIdTest_1369, ReturnsMinoltaCs7DForMinoltaCs7D_1369) {
    EXPECT_EQ(IfdId::minoltaCs7DId, groupId("MinoltaCs7D"));
}

// Test with very long string
TEST_F(GroupIdTest_1369, ReturnsIfdIdNotSetForVeryLongString_1369) {
    std::string longStr(1000, 'X');
    EXPECT_EQ(IfdId::ifdIdNotSet, groupId(longStr));
}

// Test with special characters
TEST_F(GroupIdTest_1369, ReturnsIfdIdNotSetForSpecialCharacters_1369) {
    EXPECT_EQ(IfdId::ifdIdNotSet, groupId("!@#$%^&*()"));
}

TEST_F(GroupIdTest_1369, ReturnsIfdIdNotSetForNullCharInString_1369) {
    std::string withNull("Image\0Extra", 11);
    EXPECT_EQ(IfdId::ifdIdNotSet, groupId(withNull));
}
