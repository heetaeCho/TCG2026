#include <gtest/gtest.h>
#include "exiv2/tags.hpp"

// Forward declaration of the function under test (it's in an internal namespace)
namespace Exiv2 {
namespace Internal {
bool isTiffImageTagLookup(uint16_t tag, IfdId group);
}
}

using Exiv2::IfdId;
using Exiv2::Internal::isTiffImageTagLookup;

class IsTiffImageTagLookupTest_1179 : public ::testing::Test {};

// =============================================================================
// Tests for non-ifd0Id groups (should always return false)
// =============================================================================

TEST_F(IsTiffImageTagLookupTest_1179, NonIfd0Group_ReturnsF_ifdIdNotSet_1179) {
    EXPECT_FALSE(isTiffImageTagLookup(0x0100, IfdId::ifdIdNotSet));
}

TEST_F(IsTiffImageTagLookupTest_1179, NonIfd0Group_ReturnsFalse_ifd1Id_1179) {
    EXPECT_FALSE(isTiffImageTagLookup(0x0100, IfdId::ifd1Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, NonIfd0Group_ReturnsFalse_exifId_1179) {
    EXPECT_FALSE(isTiffImageTagLookup(0x0100, IfdId::exifId));
}

TEST_F(IsTiffImageTagLookupTest_1179, NonIfd0Group_ReturnsFalse_gpsId_1179) {
    EXPECT_FALSE(isTiffImageTagLookup(0x0100, IfdId::gpsId));
}

TEST_F(IsTiffImageTagLookupTest_1179, NonIfd0Group_ReturnsFalse_iopId_1179) {
    EXPECT_FALSE(isTiffImageTagLookup(0x0100, IfdId::iopId));
}

TEST_F(IsTiffImageTagLookupTest_1179, NonIfd0Group_ReturnsFalse_mnId_1179) {
    EXPECT_FALSE(isTiffImageTagLookup(0x0100, IfdId::mnId));
}

TEST_F(IsTiffImageTagLookupTest_1179, NonIfd0Group_ReturnsFalse_lastId_1179) {
    EXPECT_FALSE(isTiffImageTagLookup(0x0100, IfdId::lastId));
}

TEST_F(IsTiffImageTagLookupTest_1179, NonIfd0Group_KnownTag_subImage1Id_1179) {
    EXPECT_FALSE(isTiffImageTagLookup(0x0111, IfdId::subImage1Id));
}

// =============================================================================
// Tests for valid tags in ifd0Id group (should return true)
// =============================================================================

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_NewSubfileType_ReturnsTrue_1179) {
    EXPECT_TRUE(isTiffImageTagLookup(0x00fe, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_SubfileType_ReturnsTrue_1179) {
    EXPECT_TRUE(isTiffImageTagLookup(0x00ff, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_ImageWidth_ReturnsTrue_1179) {
    EXPECT_TRUE(isTiffImageTagLookup(0x0100, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_ImageLength_ReturnsTrue_1179) {
    EXPECT_TRUE(isTiffImageTagLookup(0x0101, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_BitsPerSample_ReturnsTrue_1179) {
    EXPECT_TRUE(isTiffImageTagLookup(0x0102, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_Compression_ReturnsTrue_1179) {
    EXPECT_TRUE(isTiffImageTagLookup(0x0103, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_PhotometricInterpretation_ReturnsTrue_1179) {
    EXPECT_TRUE(isTiffImageTagLookup(0x0106, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_FillOrder_ReturnsTrue_1179) {
    EXPECT_TRUE(isTiffImageTagLookup(0x010a, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_StripOffsets_ReturnsTrue_1179) {
    EXPECT_TRUE(isTiffImageTagLookup(0x0111, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_SamplesPerPixel_ReturnsTrue_1179) {
    EXPECT_TRUE(isTiffImageTagLookup(0x0115, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_RowsPerStrip_ReturnsTrue_1179) {
    EXPECT_TRUE(isTiffImageTagLookup(0x0116, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_StripByteCounts_ReturnsTrue_1179) {
    EXPECT_TRUE(isTiffImageTagLookup(0x0117, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_XResolution_ReturnsTrue_1179) {
    EXPECT_TRUE(isTiffImageTagLookup(0x011a, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_YResolution_ReturnsTrue_1179) {
    EXPECT_TRUE(isTiffImageTagLookup(0x011b, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_PlanarConfiguration_ReturnsTrue_1179) {
    EXPECT_TRUE(isTiffImageTagLookup(0x011c, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_GrayResponseUnit_ReturnsTrue_1179) {
    EXPECT_TRUE(isTiffImageTagLookup(0x0122, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_GrayResponseCurve_ReturnsTrue_1179) {
    EXPECT_TRUE(isTiffImageTagLookup(0x0123, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_T4Options_ReturnsTrue_1179) {
    EXPECT_TRUE(isTiffImageTagLookup(0x0124, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_T6Options_ReturnsTrue_1179) {
    EXPECT_TRUE(isTiffImageTagLookup(0x0125, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_ResolutionUnit_ReturnsTrue_1179) {
    EXPECT_TRUE(isTiffImageTagLookup(0x0128, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_PageNumber_ReturnsTrue_1179) {
    EXPECT_TRUE(isTiffImageTagLookup(0x0129, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_TransferFunction_ReturnsTrue_1179) {
    EXPECT_TRUE(isTiffImageTagLookup(0x012d, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_Predictor_ReturnsTrue_1179) {
    EXPECT_TRUE(isTiffImageTagLookup(0x013d, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_WhitePoint_ReturnsTrue_1179) {
    EXPECT_TRUE(isTiffImageTagLookup(0x013e, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_PrimaryChromaticities_ReturnsTrue_1179) {
    EXPECT_TRUE(isTiffImageTagLookup(0x013f, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_ColorMap_ReturnsTrue_1179) {
    EXPECT_TRUE(isTiffImageTagLookup(0x0140, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_HalftoneHints_ReturnsTrue_1179) {
    EXPECT_TRUE(isTiffImageTagLookup(0x0141, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_TileWidth_ReturnsTrue_1179) {
    EXPECT_TRUE(isTiffImageTagLookup(0x0142, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_TileLength_ReturnsTrue_1179) {
    EXPECT_TRUE(isTiffImageTagLookup(0x0143, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_TileOffsets_ReturnsTrue_1179) {
    EXPECT_TRUE(isTiffImageTagLookup(0x0144, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_TileByteCounts_ReturnsTrue_1179) {
    EXPECT_TRUE(isTiffImageTagLookup(0x0145, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_InkSet_ReturnsTrue_1179) {
    EXPECT_TRUE(isTiffImageTagLookup(0x014c, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_InkNames_ReturnsTrue_1179) {
    EXPECT_TRUE(isTiffImageTagLookup(0x014d, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_NumberOfInks_ReturnsTrue_1179) {
    EXPECT_TRUE(isTiffImageTagLookup(0x014e, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_DotRange_ReturnsTrue_1179) {
    EXPECT_TRUE(isTiffImageTagLookup(0x0150, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_TargetPrinter_ReturnsTrue_1179) {
    EXPECT_TRUE(isTiffImageTagLookup(0x0151, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_ExtraSamples_ReturnsTrue_1179) {
    EXPECT_TRUE(isTiffImageTagLookup(0x0152, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_SampleFormat_ReturnsTrue_1179) {
    EXPECT_TRUE(isTiffImageTagLookup(0x0153, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_SMinSampleValue_ReturnsTrue_1179) {
    EXPECT_TRUE(isTiffImageTagLookup(0x0154, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_SMaxSampleValue_ReturnsTrue_1179) {
    EXPECT_TRUE(isTiffImageTagLookup(0x0155, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_TransferRange_ReturnsTrue_1179) {
    EXPECT_TRUE(isTiffImageTagLookup(0x0156, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_ClipPath_ReturnsTrue_1179) {
    EXPECT_TRUE(isTiffImageTagLookup(0x0157, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_XClipPathUnits_ReturnsTrue_1179) {
    EXPECT_TRUE(isTiffImageTagLookup(0x0158, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_YClipPathUnits_ReturnsTrue_1179) {
    EXPECT_TRUE(isTiffImageTagLookup(0x0159, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_Indexed_ReturnsTrue_1179) {
    EXPECT_TRUE(isTiffImageTagLookup(0x015a, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_JPEGTables_ReturnsTrue_1179) {
    EXPECT_TRUE(isTiffImageTagLookup(0x015b, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_JPEGProc_ReturnsTrue_1179) {
    EXPECT_TRUE(isTiffImageTagLookup(0x0200, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_JPEGInterchangeFormat_ReturnsTrue_1179) {
    EXPECT_TRUE(isTiffImageTagLookup(0x0201, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_JPEGInterchangeFormatLength_ReturnsTrue_1179) {
    EXPECT_TRUE(isTiffImageTagLookup(0x0202, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_JPEGRestartInterval_ReturnsTrue_1179) {
    EXPECT_TRUE(isTiffImageTagLookup(0x0203, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_JPEGLosslessPredictors_ReturnsTrue_1179) {
    EXPECT_TRUE(isTiffImageTagLookup(0x0205, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_JPEGPointTransforms_ReturnsTrue_1179) {
    EXPECT_TRUE(isTiffImageTagLookup(0x0206, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_JPEGQTables_ReturnsTrue_1179) {
    EXPECT_TRUE(isTiffImageTagLookup(0x0207, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_JPEGDCTables_ReturnsTrue_1179) {
    EXPECT_TRUE(isTiffImageTagLookup(0x0208, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_JPEGACTables_ReturnsTrue_1179) {
    EXPECT_TRUE(isTiffImageTagLookup(0x0209, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_YCbCrCoefficients_ReturnsTrue_1179) {
    EXPECT_TRUE(isTiffImageTagLookup(0x0211, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_YCbCrSubSampling_ReturnsTrue_1179) {
    EXPECT_TRUE(isTiffImageTagLookup(0x0212, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_YCbCrPositioning_ReturnsTrue_1179) {
    EXPECT_TRUE(isTiffImageTagLookup(0x0213, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_ReferenceBlackWhite_ReturnsTrue_1179) {
    EXPECT_TRUE(isTiffImageTagLookup(0x0214, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_CFARepeatPatternDim_ReturnsTrue_1179) {
    EXPECT_TRUE(isTiffImageTagLookup(0x828d, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_CFAPattern_ReturnsTrue_1179) {
    EXPECT_TRUE(isTiffImageTagLookup(0x828e, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_SpectralSensitivity_ReturnsTrue_1179) {
    EXPECT_TRUE(isTiffImageTagLookup(0x8824, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_OECF_ReturnsTrue_1179) {
    EXPECT_TRUE(isTiffImageTagLookup(0x8828, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_CompressedBitsPerPixel_ReturnsTrue_1179) {
    EXPECT_TRUE(isTiffImageTagLookup(0x9102, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_SensingMethod_ReturnsTrue_1179) {
    EXPECT_TRUE(isTiffImageTagLookup(0x9217, IfdId::ifd0Id));
}

// =============================================================================
// Tests for tags NOT in the list with ifd0Id (should return false)
// =============================================================================

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_UnknownTag_0x0000_ReturnsFalse_1179) {
    EXPECT_FALSE(isTiffImageTagLookup(0x0000, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_UnknownTag_0x0001_ReturnsFalse_1179) {
    EXPECT_FALSE(isTiffImageTagLookup(0x0001, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_UnknownTag_0x00fd_ReturnsFalse_1179) {
    EXPECT_FALSE(isTiffImageTagLookup(0x00fd, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_UnknownTag_0x0104_ReturnsFalse_1179) {
    EXPECT_FALSE(isTiffImageTagLookup(0x0104, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_UnknownTag_0x0105_ReturnsFalse_1179) {
    EXPECT_FALSE(isTiffImageTagLookup(0x0105, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_UnknownTag_0x0107_ReturnsFalse_1179) {
    EXPECT_FALSE(isTiffImageTagLookup(0x0107, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_UnknownTag_0x0112_ReturnsFalse_1179) {
    EXPECT_FALSE(isTiffImageTagLookup(0x0112, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_UnknownTag_0x0204_ReturnsFalse_1179) {
    EXPECT_FALSE(isTiffImageTagLookup(0x0204, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_UnknownTag_0x020a_ReturnsFalse_1179) {
    EXPECT_FALSE(isTiffImageTagLookup(0x020a, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_UnknownTag_0x0210_ReturnsFalse_1179) {
    EXPECT_FALSE(isTiffImageTagLookup(0x0210, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_UnknownTag_0x0215_ReturnsFalse_1179) {
    EXPECT_FALSE(isTiffImageTagLookup(0x0215, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_UnknownTag_0xFFFF_ReturnsFalse_1179) {
    EXPECT_FALSE(isTiffImageTagLookup(0xFFFF, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_UnknownTag_0x828c_ReturnsFalse_1179) {
    EXPECT_FALSE(isTiffImageTagLookup(0x828c, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_UnknownTag_0x828f_ReturnsFalse_1179) {
    EXPECT_FALSE(isTiffImageTagLookup(0x828f, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_UnknownTag_0x8825_ReturnsFalse_1179) {
    EXPECT_FALSE(isTiffImageTagLookup(0x8825, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_UnknownTag_0x9101_ReturnsFalse_1179) {
    EXPECT_FALSE(isTiffImageTagLookup(0x9101, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_UnknownTag_0x9103_ReturnsFalse_1179) {
    EXPECT_FALSE(isTiffImageTagLookup(0x9103, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_UnknownTag_0x9218_ReturnsFalse_1179) {
    EXPECT_FALSE(isTiffImageTagLookup(0x9218, IfdId::ifd0Id));
}

// =============================================================================
// Boundary: tag 0 and max uint16_t with various groups
// =============================================================================

TEST_F(IsTiffImageTagLookupTest_1179, ZeroTag_NonIfd0_ReturnsFalse_1179) {
    EXPECT_FALSE(isTiffImageTagLookup(0x0000, IfdId::exifId));
}

TEST_F(IsTiffImageTagLookupTest_1179, MaxTag_Ifd0_ReturnsFalse_1179) {
    EXPECT_FALSE(isTiffImageTagLookup(0xFFFF, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, MaxTag_NonIfd0_ReturnsFalse_1179) {
    EXPECT_FALSE(isTiffImageTagLookup(0xFFFF, IfdId::ifd2Id));
}

// =============================================================================
// Tags that are gaps between recognized tags in ifd0Id
// =============================================================================

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_GapTag_0x0108_ReturnsFalse_1179) {
    EXPECT_FALSE(isTiffImageTagLookup(0x0108, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_GapTag_0x0109_ReturnsFalse_1179) {
    EXPECT_FALSE(isTiffImageTagLookup(0x0109, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_GapTag_0x010b_ReturnsFalse_1179) {
    EXPECT_FALSE(isTiffImageTagLookup(0x010b, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_GapTag_0x0113_ReturnsFalse_1179) {
    EXPECT_FALSE(isTiffImageTagLookup(0x0113, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_GapTag_0x0118_ReturnsFalse_1179) {
    EXPECT_FALSE(isTiffImageTagLookup(0x0118, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_GapTag_0x0119_ReturnsFalse_1179) {
    EXPECT_FALSE(isTiffImageTagLookup(0x0119, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_GapTag_0x011d_ReturnsFalse_1179) {
    EXPECT_FALSE(isTiffImageTagLookup(0x011d, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_GapTag_0x0126_ReturnsFalse_1179) {
    EXPECT_FALSE(isTiffImageTagLookup(0x0126, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_GapTag_0x0127_ReturnsFalse_1179) {
    EXPECT_FALSE(isTiffImageTagLookup(0x0127, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_GapTag_0x012a_ReturnsFalse_1179) {
    EXPECT_FALSE(isTiffImageTagLookup(0x012a, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_GapTag_0x014f_ReturnsFalse_1179) {
    EXPECT_FALSE(isTiffImageTagLookup(0x014f, IfdId::ifd0Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, Ifd0_GapTag_0x015c_ReturnsFalse_1179) {
    EXPECT_FALSE(isTiffImageTagLookup(0x015c, IfdId::ifd0Id));
}

// =============================================================================
// Valid known tag with multiple non-ifd0 groups to ensure group check
// =============================================================================

TEST_F(IsTiffImageTagLookupTest_1179, ValidTagWithIfd2Id_ReturnsFalse_1179) {
    EXPECT_TRUE(isTiffImageTagLookup(0x0102, IfdId::ifd0Id));
    EXPECT_FALSE(isTiffImageTagLookup(0x0102, IfdId::ifd2Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, ValidTagWithIfd3Id_ReturnsFalse_1179) {
    EXPECT_FALSE(isTiffImageTagLookup(0x0211, IfdId::ifd3Id));
}

TEST_F(IsTiffImageTagLookupTest_1179, ValidTagWithCanonId_ReturnsFalse_1179) {
    EXPECT_FALSE(isTiffImageTagLookup(0x9217, IfdId::canonId));
}
