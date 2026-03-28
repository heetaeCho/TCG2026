#include <gtest/gtest.h>
#include "exiv2/tags.hpp"
#include "tags_int.hpp"

namespace {

using Exiv2::Internal::groupName;
using Exiv2::IfdId;

class GroupNameTest_1371 : public ::testing::Test {
protected:
};

// Test that ifdIdNotSet returns "Unknown"
TEST_F(GroupNameTest_1371, IfdIdNotSetReturnsUnknown_1371) {
  const char* result = groupName(IfdId::ifdIdNotSet);
  ASSERT_NE(result, nullptr);
  EXPECT_STREQ(result, "Unknown");
}

// Test that ifd0Id returns "Image"
TEST_F(GroupNameTest_1371, Ifd0IdReturnsImage_1371) {
  const char* result = groupName(IfdId::ifd0Id);
  ASSERT_NE(result, nullptr);
  EXPECT_STREQ(result, "Image");
}

// Test that ifd1Id returns "Thumbnail"
TEST_F(GroupNameTest_1371, Ifd1IdReturnsThumbnail_1371) {
  const char* result = groupName(IfdId::ifd1Id);
  ASSERT_NE(result, nullptr);
  EXPECT_STREQ(result, "Thumbnail");
}

// Test that ifd2Id returns "Image2"
TEST_F(GroupNameTest_1371, Ifd2IdReturnsImage2_1371) {
  const char* result = groupName(IfdId::ifd2Id);
  ASSERT_NE(result, nullptr);
  EXPECT_STREQ(result, "Image2");
}

// Test that ifd3Id returns "Image3"
TEST_F(GroupNameTest_1371, Ifd3IdReturnsImage3_1371) {
  const char* result = groupName(IfdId::ifd3Id);
  ASSERT_NE(result, nullptr);
  EXPECT_STREQ(result, "Image3");
}

// Test that exifId returns "Photo"
TEST_F(GroupNameTest_1371, ExifIdReturnsPhoto_1371) {
  const char* result = groupName(IfdId::exifId);
  ASSERT_NE(result, nullptr);
  EXPECT_STREQ(result, "Photo");
}

// Test that gpsId returns "GPSInfo"
TEST_F(GroupNameTest_1371, GpsIdReturnsGPSInfo_1371) {
  const char* result = groupName(IfdId::gpsId);
  ASSERT_NE(result, nullptr);
  EXPECT_STREQ(result, "GPSInfo");
}

// Test that iopId returns "Iop"
TEST_F(GroupNameTest_1371, IopIdReturnsIop_1371) {
  const char* result = groupName(IfdId::iopId);
  ASSERT_NE(result, nullptr);
  EXPECT_STREQ(result, "Iop");
}

// Test that mpfId returns "MpfInfo"
TEST_F(GroupNameTest_1371, MpfIdReturnsMpfInfo_1371) {
  const char* result = groupName(IfdId::mpfId);
  ASSERT_NE(result, nullptr);
  EXPECT_STREQ(result, "MpfInfo");
}

// Test that canonId returns "Canon"
TEST_F(GroupNameTest_1371, CanonIdReturnsCanon_1371) {
  const char* result = groupName(IfdId::canonId);
  ASSERT_NE(result, nullptr);
  EXPECT_STREQ(result, "Canon");
}

// Test that canonCsId returns "CanonCs"
TEST_F(GroupNameTest_1371, CanonCsIdReturnsCanonCs_1371) {
  const char* result = groupName(IfdId::canonCsId);
  ASSERT_NE(result, nullptr);
  EXPECT_STREQ(result, "CanonCs");
}

// Test that fujiId returns "Fujifilm"
TEST_F(GroupNameTest_1371, FujiIdReturnsFujifilm_1371) {
  const char* result = groupName(IfdId::fujiId);
  ASSERT_NE(result, nullptr);
  EXPECT_STREQ(result, "Fujifilm");
}

// Test that nikon1Id returns "Nikon1"
TEST_F(GroupNameTest_1371, Nikon1IdReturnsNikon1_1371) {
  const char* result = groupName(IfdId::nikon1Id);
  ASSERT_NE(result, nullptr);
  EXPECT_STREQ(result, "Nikon1");
}

// Test that nikon3Id returns "Nikon3"
TEST_F(GroupNameTest_1371, Nikon3IdReturnsNikon3_1371) {
  const char* result = groupName(IfdId::nikon3Id);
  ASSERT_NE(result, nullptr);
  EXPECT_STREQ(result, "Nikon3");
}

// Test that olympusId returns "Olympus"
TEST_F(GroupNameTest_1371, OlympusIdReturnsOlympus_1371) {
  const char* result = groupName(IfdId::olympusId);
  ASSERT_NE(result, nullptr);
  EXPECT_STREQ(result, "Olympus");
}

// Test that panasonicId returns "Panasonic"
TEST_F(GroupNameTest_1371, PanasonicIdReturnsPanasonic_1371) {
  const char* result = groupName(IfdId::panasonicId);
  ASSERT_NE(result, nullptr);
  EXPECT_STREQ(result, "Panasonic");
}

// Test that pentaxId returns "Pentax"
TEST_F(GroupNameTest_1371, PentaxIdReturnsPentax_1371) {
  const char* result = groupName(IfdId::pentaxId);
  ASSERT_NE(result, nullptr);
  EXPECT_STREQ(result, "Pentax");
}

// Test that sigmaId returns "Sigma"
TEST_F(GroupNameTest_1371, SigmaIdReturnsSigma_1371) {
  const char* result = groupName(IfdId::sigmaId);
  ASSERT_NE(result, nullptr);
  EXPECT_STREQ(result, "Sigma");
}

// Test that sony1Id returns "Sony1"
TEST_F(GroupNameTest_1371, Sony1IdReturnsSony1_1371) {
  const char* result = groupName(IfdId::sony1Id);
  ASSERT_NE(result, nullptr);
  EXPECT_STREQ(result, "Sony1");
}

// Test that sony2Id returns "Sony2"
TEST_F(GroupNameTest_1371, Sony2IdReturnsSony2_1371) {
  const char* result = groupName(IfdId::sony2Id);
  ASSERT_NE(result, nullptr);
  EXPECT_STREQ(result, "Sony2");
}

// Test that mnId returns "MakerNote"
TEST_F(GroupNameTest_1371, MnIdReturnsMakerNote_1371) {
  const char* result = groupName(IfdId::mnId);
  ASSERT_NE(result, nullptr);
  EXPECT_STREQ(result, "MakerNote");
}

// Test that panaRawId returns "PanasonicRaw"
TEST_F(GroupNameTest_1371, PanaRawIdReturnsPanasonicRaw_1371) {
  const char* result = groupName(IfdId::panaRawId);
  ASSERT_NE(result, nullptr);
  EXPECT_STREQ(result, "PanasonicRaw");
}

// Test that subImage1Id returns "SubImage1"
TEST_F(GroupNameTest_1371, SubImage1IdReturnsSubImage1_1371) {
  const char* result = groupName(IfdId::subImage1Id);
  ASSERT_NE(result, nullptr);
  EXPECT_STREQ(result, "SubImage1");
}

// Test that lastId returns "(Last IFD item)"
TEST_F(GroupNameTest_1371, LastIdReturnsLastIfdItem_1371) {
  const char* result = groupName(IfdId::lastId);
  ASSERT_NE(result, nullptr);
  EXPECT_STREQ(result, "(Last IFD item)");
}

// Boundary: Test that an invalid/unknown IfdId falls back to "Unknown"
TEST_F(GroupNameTest_1371, InvalidIfdIdReturnsUnknown_1371) {
  // Cast an integer that is unlikely to match any valid IfdId
  const char* result = groupName(static_cast<IfdId>(9999));
  ASSERT_NE(result, nullptr);
  EXPECT_STREQ(result, "Unknown");
}

// Test that minoltaId returns "Minolta"
TEST_F(GroupNameTest_1371, MinoltaIdReturnsMinolta_1371) {
  const char* result = groupName(IfdId::minoltaId);
  ASSERT_NE(result, nullptr);
  EXPECT_STREQ(result, "Minolta");
}

// Test that casioId returns "Casio"
TEST_F(GroupNameTest_1371, CasioIdReturnsCasio_1371) {
  const char* result = groupName(IfdId::casioId);
  ASSERT_NE(result, nullptr);
  EXPECT_STREQ(result, "Casio");
}

// Test that casio2Id returns "Casio2"
TEST_F(GroupNameTest_1371, Casio2IdReturnsCasio2_1371) {
  const char* result = groupName(IfdId::casio2Id);
  ASSERT_NE(result, nullptr);
  EXPECT_STREQ(result, "Casio2");
}

// Test that samsung2Id returns "Samsung2"
TEST_F(GroupNameTest_1371, Samsung2IdReturnsSamsung2_1371) {
  const char* result = groupName(IfdId::samsung2Id);
  ASSERT_NE(result, nullptr);
  EXPECT_STREQ(result, "Samsung2");
}

// Test that pentaxDngId returns "PentaxDng"
TEST_F(GroupNameTest_1371, PentaxDngIdReturnsPentaxDng_1371) {
  const char* result = groupName(IfdId::pentaxDngId);
  ASSERT_NE(result, nullptr);
  EXPECT_STREQ(result, "PentaxDng");
}

// Test groupName returns non-null for all well-known SubImage IDs
TEST_F(GroupNameTest_1371, SubImage9IdReturnsSubImage9_1371) {
  const char* result = groupName(IfdId::subImage9Id);
  ASSERT_NE(result, nullptr);
  EXPECT_STREQ(result, "SubImage9");
}

// Test subThumb1Id returns "SubThumb1"
TEST_F(GroupNameTest_1371, SubThumb1IdReturnsSubThumb1_1371) {
  const char* result = groupName(IfdId::subThumb1Id);
  ASSERT_NE(result, nullptr);
  EXPECT_STREQ(result, "SubThumb1");
}

// Test nikonPvId returns "NikonPreview"
TEST_F(GroupNameTest_1371, NikonPvIdReturnsNikonPreview_1371) {
  const char* result = groupName(IfdId::nikonPvId);
  ASSERT_NE(result, nullptr);
  EXPECT_STREQ(result, "NikonPreview");
}

// Test sonyMltId returns "SonyMinolta"
TEST_F(GroupNameTest_1371, SonyMltIdReturnsSonyMinolta_1371) {
  const char* result = groupName(IfdId::sonyMltId);
  ASSERT_NE(result, nullptr);
  EXPECT_STREQ(result, "SonyMinolta");
}

// Test sony2FpId returns "Sony2Fp"
TEST_F(GroupNameTest_1371, Sony2FpIdReturnsSony2Fp_1371) {
  const char* result = groupName(IfdId::sony2FpId);
  ASSERT_NE(result, nullptr);
  EXPECT_STREQ(result, "Sony2Fp");
}

// Test that another invalid IfdId (negative cast) returns "Unknown"
TEST_F(GroupNameTest_1371, NegativeIfdIdReturnsUnknown_1371) {
  const char* result = groupName(static_cast<IfdId>(-1));
  ASSERT_NE(result, nullptr);
  EXPECT_STREQ(result, "Unknown");
}

// Test olympus2Id returns "Olympus2"
TEST_F(GroupNameTest_1371, Olympus2IdReturnsOlympus2_1371) {
  const char* result = groupName(IfdId::olympus2Id);
  ASSERT_NE(result, nullptr);
  EXPECT_STREQ(result, "Olympus2");
}

// Test canonSiId returns "CanonSi"
TEST_F(GroupNameTest_1371, CanonSiIdReturnsCanonSi_1371) {
  const char* result = groupName(IfdId::canonSiId);
  ASSERT_NE(result, nullptr);
  EXPECT_STREQ(result, "CanonSi");
}

// Test nikon2Id returns "Nikon2"
TEST_F(GroupNameTest_1371, Nikon2IdReturnsNikon2_1371) {
  const char* result = groupName(IfdId::nikon2Id);
  ASSERT_NE(result, nullptr);
  EXPECT_STREQ(result, "Nikon2");
}

}  // namespace
