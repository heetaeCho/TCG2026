// We need the XMP SDK headers and definitions
#include <string>

// Include necessary XMP SDK headers
#include "public/include/XMP_Const.h"
#include "public/include/XMP_Environment.h"
#include "source/XMPCore/XMPMeta.hpp"

// To access the static function, we include the source file
// This is necessary because IsInternalProperty has internal linkage
#include "xmpsdk/src/XMPUtils-FileInfo.cpp"

#include <gtest/gtest.h>

class IsInternalPropertyTest_1920 : public ::testing::Test {
protected:
    // Helper to call the static function
    bool CallIsInternal(const std::string& schema, const std::string& prop) {
        return IsInternalProperty(schema, prop);
    }
};

// ============================================================
// DC namespace tests
// ============================================================

TEST_F(IsInternalPropertyTest_1920, DC_Format_IsInternal_1920) {
    EXPECT_TRUE(CallIsInternal(kXMP_NS_DC, "dc:format"));
}

TEST_F(IsInternalPropertyTest_1920, DC_Language_IsInternal_1920) {
    EXPECT_TRUE(CallIsInternal(kXMP_NS_DC, "dc:language"));
}

TEST_F(IsInternalPropertyTest_1920, DC_Title_IsNotInternal_1920) {
    EXPECT_FALSE(CallIsInternal(kXMP_NS_DC, "dc:title"));
}

TEST_F(IsInternalPropertyTest_1920, DC_Creator_IsNotInternal_1920) {
    EXPECT_FALSE(CallIsInternal(kXMP_NS_DC, "dc:creator"));
}

TEST_F(IsInternalPropertyTest_1920, DC_Description_IsNotInternal_1920) {
    EXPECT_FALSE(CallIsInternal(kXMP_NS_DC, "dc:description"));
}

// ============================================================
// XMP namespace tests
// ============================================================

TEST_F(IsInternalPropertyTest_1920, XMP_BaseURL_IsInternal_1920) {
    EXPECT_TRUE(CallIsInternal(kXMP_NS_XMP, "xmp:BaseURL"));
}

TEST_F(IsInternalPropertyTest_1920, XMP_CreatorTool_IsInternal_1920) {
    EXPECT_TRUE(CallIsInternal(kXMP_NS_XMP, "xmp:CreatorTool"));
}

TEST_F(IsInternalPropertyTest_1920, XMP_Format_IsInternal_1920) {
    EXPECT_TRUE(CallIsInternal(kXMP_NS_XMP, "xmp:Format"));
}

TEST_F(IsInternalPropertyTest_1920, XMP_Locale_IsInternal_1920) {
    EXPECT_TRUE(CallIsInternal(kXMP_NS_XMP, "xmp:Locale"));
}

TEST_F(IsInternalPropertyTest_1920, XMP_MetadataDate_IsInternal_1920) {
    EXPECT_TRUE(CallIsInternal(kXMP_NS_XMP, "xmp:MetadataDate"));
}

TEST_F(IsInternalPropertyTest_1920, XMP_ModifyDate_IsInternal_1920) {
    EXPECT_TRUE(CallIsInternal(kXMP_NS_XMP, "xmp:ModifyDate"));
}

TEST_F(IsInternalPropertyTest_1920, XMP_CreateDate_IsNotInternal_1920) {
    EXPECT_FALSE(CallIsInternal(kXMP_NS_XMP, "xmp:CreateDate"));
}

TEST_F(IsInternalPropertyTest_1920, XMP_Rating_IsNotInternal_1920) {
    EXPECT_FALSE(CallIsInternal(kXMP_NS_XMP, "xmp:Rating"));
}

// ============================================================
// PDF namespace tests
// ============================================================

TEST_F(IsInternalPropertyTest_1920, PDF_BaseURL_IsInternal_1920) {
    EXPECT_TRUE(CallIsInternal(kXMP_NS_PDF, "pdf:BaseURL"));
}

TEST_F(IsInternalPropertyTest_1920, PDF_Creator_IsInternal_1920) {
    EXPECT_TRUE(CallIsInternal(kXMP_NS_PDF, "pdf:Creator"));
}

TEST_F(IsInternalPropertyTest_1920, PDF_ModDate_IsInternal_1920) {
    EXPECT_TRUE(CallIsInternal(kXMP_NS_PDF, "pdf:ModDate"));
}

TEST_F(IsInternalPropertyTest_1920, PDF_PDFVersion_IsInternal_1920) {
    EXPECT_TRUE(CallIsInternal(kXMP_NS_PDF, "pdf:PDFVersion"));
}

TEST_F(IsInternalPropertyTest_1920, PDF_Producer_IsInternal_1920) {
    EXPECT_TRUE(CallIsInternal(kXMP_NS_PDF, "pdf:Producer"));
}

TEST_F(IsInternalPropertyTest_1920, PDF_Keywords_IsNotInternal_1920) {
    EXPECT_FALSE(CallIsInternal(kXMP_NS_PDF, "pdf:Keywords"));
}

TEST_F(IsInternalPropertyTest_1920, PDF_Title_IsNotInternal_1920) {
    EXPECT_FALSE(CallIsInternal(kXMP_NS_PDF, "pdf:Title"));
}

// ============================================================
// TIFF namespace tests - internal by default, some exceptions
// ============================================================

TEST_F(IsInternalPropertyTest_1920, TIFF_DefaultProp_IsInternal_1920) {
    EXPECT_TRUE(CallIsInternal(kXMP_NS_TIFF, "tiff:Make"));
}

TEST_F(IsInternalPropertyTest_1920, TIFF_Model_IsInternal_1920) {
    EXPECT_TRUE(CallIsInternal(kXMP_NS_TIFF, "tiff:Model"));
}

TEST_F(IsInternalPropertyTest_1920, TIFF_Orientation_IsInternal_1920) {
    EXPECT_TRUE(CallIsInternal(kXMP_NS_TIFF, "tiff:Orientation"));
}

TEST_F(IsInternalPropertyTest_1920, TIFF_ImageDescription_IsNotInternal_1920) {
    EXPECT_FALSE(CallIsInternal(kXMP_NS_TIFF, "tiff:ImageDescription"));
}

TEST_F(IsInternalPropertyTest_1920, TIFF_Artist_IsNotInternal_1920) {
    EXPECT_FALSE(CallIsInternal(kXMP_NS_TIFF, "tiff:Artist"));
}

TEST_F(IsInternalPropertyTest_1920, TIFF_Copyright_IsNotInternal_1920) {
    EXPECT_FALSE(CallIsInternal(kXMP_NS_TIFF, "tiff:Copyright"));
}

// ============================================================
// EXIF namespace tests - internal by default, UserComment exception
// ============================================================

TEST_F(IsInternalPropertyTest_1920, EXIF_DefaultProp_IsInternal_1920) {
    EXPECT_TRUE(CallIsInternal(kXMP_NS_EXIF, "exif:ExposureTime"));
}

TEST_F(IsInternalPropertyTest_1920, EXIF_FNumber_IsInternal_1920) {
    EXPECT_TRUE(CallIsInternal(kXMP_NS_EXIF, "exif:FNumber"));
}

TEST_F(IsInternalPropertyTest_1920, EXIF_UserComment_IsNotInternal_1920) {
    EXPECT_FALSE(CallIsInternal(kXMP_NS_EXIF, "exif:UserComment"));
}

// ============================================================
// EXIF Aux namespace tests - all internal
// ============================================================

TEST_F(IsInternalPropertyTest_1920, EXIFAux_AnyProp_IsInternal_1920) {
    EXPECT_TRUE(CallIsInternal(kXMP_NS_EXIF_Aux, "aux:Lens"));
}

TEST_F(IsInternalPropertyTest_1920, EXIFAux_SerialNumber_IsInternal_1920) {
    EXPECT_TRUE(CallIsInternal(kXMP_NS_EXIF_Aux, "aux:SerialNumber"));
}

// ============================================================
// Photoshop namespace tests
// ============================================================

TEST_F(IsInternalPropertyTest_1920, Photoshop_ICCProfile_IsInternal_1920) {
    EXPECT_TRUE(CallIsInternal(kXMP_NS_Photoshop, "photoshop:ICCProfile"));
}

TEST_F(IsInternalPropertyTest_1920, Photoshop_City_IsNotInternal_1920) {
    EXPECT_FALSE(CallIsInternal(kXMP_NS_Photoshop, "photoshop:City"));
}

TEST_F(IsInternalPropertyTest_1920, Photoshop_Country_IsNotInternal_1920) {
    EXPECT_FALSE(CallIsInternal(kXMP_NS_Photoshop, "photoshop:Country"));
}

// ============================================================
// CameraRaw namespace tests
// ============================================================

TEST_F(IsInternalPropertyTest_1920, CameraRaw_Version_IsInternal_1920) {
    EXPECT_TRUE(CallIsInternal(kXMP_NS_CameraRaw, "crs:Version"));
}

TEST_F(IsInternalPropertyTest_1920, CameraRaw_RawFileName_IsInternal_1920) {
    EXPECT_TRUE(CallIsInternal(kXMP_NS_CameraRaw, "crs:RawFileName"));
}

TEST_F(IsInternalPropertyTest_1920, CameraRaw_ToneCurveName_IsInternal_1920) {
    EXPECT_TRUE(CallIsInternal(kXMP_NS_CameraRaw, "crs:ToneCurveName"));
}

TEST_F(IsInternalPropertyTest_1920, CameraRaw_WhiteBalance_IsNotInternal_1920) {
    EXPECT_FALSE(CallIsInternal(kXMP_NS_CameraRaw, "crs:WhiteBalance"));
}

TEST_F(IsInternalPropertyTest_1920, CameraRaw_Exposure_IsNotInternal_1920) {
    EXPECT_FALSE(CallIsInternal(kXMP_NS_CameraRaw, "crs:Exposure"));
}

// ============================================================
// AdobeStockPhoto namespace - all internal
// ============================================================

TEST_F(IsInternalPropertyTest_1920, AdobeStockPhoto_AnyProp_IsInternal_1920) {
    EXPECT_TRUE(CallIsInternal(kXMP_NS_AdobeStockPhoto, "bmsp:SomeProperty"));
}

TEST_F(IsInternalPropertyTest_1920, AdobeStockPhoto_AnotherProp_IsInternal_1920) {
    EXPECT_TRUE(CallIsInternal(kXMP_NS_AdobeStockPhoto, "bmsp:AnotherProperty"));
}

// ============================================================
// XMP_MM namespace - all internal
// ============================================================

TEST_F(IsInternalPropertyTest_1920, XMPMM_DocumentID_IsInternal_1920) {
    EXPECT_TRUE(CallIsInternal(kXMP_NS_XMP_MM, "xmpMM:DocumentID"));
}

TEST_F(IsInternalPropertyTest_1920, XMPMM_InstanceID_IsInternal_1920) {
    EXPECT_TRUE(CallIsInternal(kXMP_NS_XMP_MM, "xmpMM:InstanceID"));
}

TEST_F(IsInternalPropertyTest_1920, XMPMM_History_IsInternal_1920) {
    EXPECT_TRUE(CallIsInternal(kXMP_NS_XMP_MM, "xmpMM:History"));
}

// ============================================================
// XMP Text namespace - all internal
// ============================================================

TEST_F(IsInternalPropertyTest_1920, XMPText_AnyProp_IsInternal_1920) {
    EXPECT_TRUE(CallIsInternal(kXMP_NS_XMP_Text, "xmpT:SomeProperty"));
}

// ============================================================
// XMP PagedFile namespace - all internal
// ============================================================

TEST_F(IsInternalPropertyTest_1920, XMPPagedFile_AnyProp_IsInternal_1920) {
    EXPECT_TRUE(CallIsInternal(kXMP_NS_XMP_PagedFile, "xmpTPg:SomeProperty"));
}

// ============================================================
// XMP Graphics namespace - all internal
// ============================================================

TEST_F(IsInternalPropertyTest_1920, XMPGraphics_AnyProp_IsInternal_1920) {
    EXPECT_TRUE(CallIsInternal(kXMP_NS_XMP_Graphics, "xmpG:SomeProperty"));
}

// ============================================================
// XMP Image namespace - all internal
// ============================================================

TEST_F(IsInternalPropertyTest_1920, XMPImage_AnyProp_IsInternal_1920) {
    EXPECT_TRUE(CallIsInternal(kXMP_NS_XMP_Image, "xmpGImg:SomeProperty"));
}

// ============================================================
// XMP Font namespace - all internal
// ============================================================

TEST_F(IsInternalPropertyTest_1920, XMPFont_AnyProp_IsInternal_1920) {
    EXPECT_TRUE(CallIsInternal(kXMP_NS_XMP_Font, "stFNT:SomeProperty"));
}

// ============================================================
// Unknown/unrecognized namespace - should return false
// ============================================================

TEST_F(IsInternalPropertyTest_1920, UnknownSchema_ReturnsNotInternal_1920) {
    EXPECT_FALSE(CallIsInternal("http://ns.example.com/unknown/", "unknown:SomeProperty"));
}

TEST_F(IsInternalPropertyTest_1920, EmptySchema_ReturnsNotInternal_1920) {
    EXPECT_FALSE(CallIsInternal("", ""));
}

TEST_F(IsInternalPropertyTest_1920, EmptySchemaWithProp_ReturnsNotInternal_1920) {
    EXPECT_FALSE(CallIsInternal("", "dc:format"));
}

TEST_F(IsInternalPropertyTest_1920, ValidSchemaEmptyProp_DC_ReturnsNotInternal_1920) {
    EXPECT_FALSE(CallIsInternal(kXMP_NS_DC, ""));
}

// ============================================================
// Boundary: case sensitivity tests
// ============================================================

TEST_F(IsInternalPropertyTest_1920, DC_Format_CaseSensitive_IsNotInternal_1920) {
    // "dc:Format" with capital F should not match "dc:format"
    EXPECT_FALSE(CallIsInternal(kXMP_NS_DC, "dc:Format"));
}

TEST_F(IsInternalPropertyTest_1920, TIFF_ImageDescription_WrongCase_IsInternal_1920) {
    // "tiff:imagedescription" should not match "tiff:ImageDescription"
    // so it stays as default internal for TIFF
    EXPECT_TRUE(CallIsInternal(kXMP_NS_TIFF, "tiff:imagedescription"));
}

TEST_F(IsInternalPropertyTest_1920, EXIF_UserComment_WrongCase_IsInternal_1920) {
    // "exif:usercomment" should not match "exif:UserComment"
    // so remains internal (EXIF default)
    EXPECT_TRUE(CallIsInternal(kXMP_NS_EXIF, "exif:usercomment"));
}

// ============================================================
// Boundary: property not in any special list for its schema
// ============================================================

TEST_F(IsInternalPropertyTest_1920, XMP_Thumbnails_IsNotInternal_1920) {
    EXPECT_FALSE(CallIsInternal(kXMP_NS_XMP, "xmp:Thumbnails"));
}

TEST_F(IsInternalPropertyTest_1920, Photoshop_DateCreated_IsNotInternal_1920) {
    EXPECT_FALSE(CallIsInternal(kXMP_NS_Photoshop, "photoshop:DateCreated"));
}
