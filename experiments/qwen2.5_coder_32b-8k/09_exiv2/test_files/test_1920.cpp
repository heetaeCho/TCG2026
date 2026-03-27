#include <gtest/gtest.h>

#include "XMPUtils-FileInfo.cpp"



// Mock class for any external collaborators if needed

class XMP_VarStringMock : public XMP_VarString {

public:

    MOCK_METHOD(std::string, c_str, (), (const override));

};



TEST(IsInternalPropertyTest_1920, NormalOperation_DC_InternalProperties_1920) {

    EXPECT_TRUE(IsInternalProperty("http://purl.org/dc/elements/1.1/", "dc:format"));

    EXPECT_TRUE(IsInternalProperty("http://purl.org/dc/elements/1.1/", "dc:language"));

}



TEST(IsInternalPropertyTest_1920, NormalOperation_DC_NonInternalProperties_1920) {

    EXPECT_FALSE(IsInternalProperty("http://purl.org/dc/elements/1.1/", "dc:title"));

}



TEST(IsInternalPropertyTest_1920, NormalOperation_XMP_InternalProperties_1920) {

    EXPECT_TRUE(IsInternalProperty("http://ns.adobe.com/xap/1.0/", "xmp:BaseURL"));

    EXPECT_TRUE(IsInternalProperty("http://ns.adobe.com/xap/1.0/", "xmp:CreatorTool"));

    EXPECT_TRUE(IsInternalProperty("http://ns.adobe.com/xap/1.0/", "xmp:Format"));

    EXPECT_TRUE(IsInternalProperty("http://ns.adobe.com/xap/1.0/", "xmp:Locale"));

    EXPECT_TRUE(IsInternalProperty("http://ns.adobe.com/xap/1.0/", "xmp:MetadataDate"));

    EXPECT_TRUE(IsInternalProperty("http://ns.adobe.com/xap/1.0/", "xmp:ModifyDate"));

}



TEST(IsInternalPropertyTest_1920, NormalOperation_XMP_NonInternalProperties_1920) {

    EXPECT_FALSE(IsInternalProperty("http://ns.adobe.com/xap/1.0/", "xmp:Title"));

}



TEST(IsInternalPropertyTest_1920, NormalOperation_PDF_InternalProperties_1920) {

    EXPECT_TRUE(IsInternalProperty("http://ns.adobe.com/pdf/1.3/", "pdf:BaseURL"));

    EXPECT_TRUE(IsInternalProperty("http://ns.adobe.com/pdf/1.3/", "pdf:Creator"));

    EXPECT_TRUE(IsInternalProperty("http://ns.adobe.com/pdf/1.3/", "pdf:ModDate"));

    EXPECT_TRUE(IsInternalProperty("http://ns.adobe.com/pdf/1.3/", "pdf:PDFVersion"));

    EXPECT_TRUE(IsInternalProperty("http://ns.adobe.com/pdf/1.3/", "pdf:Producer"));

}



TEST(IsInternalPropertyTest_1920, NormalOperation_PDF_NonInternalProperties_1920) {

    EXPECT_FALSE(IsInternalProperty("http://ns.adobe.com/pdf/1.3/", "pdf:Keywords"));

}



TEST(IsInternalPropertyTest_1920, NormalOperation_TIFF_InternalProperties_1920) {

    EXPECT_TRUE(IsInternalProperty("http://ns.adobe.com/tiff/1.0/", "tiff:Make"));

}



TEST(IsInternalPropertyTest_1920, NormalOperation_TIFF_NonInternalProperties_1920) {

    EXPECT_FALSE(IsInternalProperty("http://ns.adobe.com/tiff/1.0/", "tiff:ImageDescription"));

    EXPECT_FALSE(IsInternalProperty("http://ns.adobe.com/tiff/1.0/", "tiff:Artist"));

    EXPECT_FALSE(IsInternalProperty("http://ns.adobe.com/tiff/1.0/", "tiff:Copyright"));

}



TEST(IsInternalPropertyTest_1920, NormalOperation_EXIF_InternalProperties_1920) {

    EXPECT_TRUE(IsInternalProperty("http://ns.adobe.com/exif/1.0/", "exif:FocalLength"));

}



TEST(IsInternalPropertyTest_1920, NormalOperation_EXIF_NonInternalProperties_1920) {

    EXPECT_FALSE(IsInternalProperty("http://ns.adobe.com/exif/1.0/", "exif:UserComment"));

}



TEST(IsInternalPropertyTest_1920, NormalOperation_EXIF_Aux_InternalProperties_1920) {

    EXPECT_TRUE(IsInternalProperty("http://ns.adobe.com/exif/aux/", "exif:AuxLensModel"));

}



TEST(IsInternalPropertyTest_1920, NormalOperation_Photoshop_InternalProperties_1920) {

    EXPECT_TRUE(IsInternalProperty("http://ns.adobe.com/photoshop/1.0/", "photoshop:ICCProfile"));

}



TEST(IsInternalPropertyTest_1920, NormalOperation_CameraRaw_InternalProperties_1920) {

    EXPECT_TRUE(IsInternalProperty("http://ns.adobe.com/camera-raw-settings/1.0/", "crs:Version"));

    EXPECT_TRUE(IsInternalProperty("http://ns.adobe.com/camera-raw-settings/1.0/", "crs:RawFileName"));

    EXPECT_TRUE(IsInternalProperty("http://ns.adobe.com/camera-raw-settings/1.0/", "crs:ToneCurveName"));

}



TEST(IsInternalPropertyTest_1920, NormalOperation_AdobeStockPhoto_InternalProperties_1920) {

    EXPECT_TRUE(IsInternalProperty("http://ns.adobe.com/bmsp/1.0/", "bmsp:Provider"));

}



TEST(IsInternalPropertyTest_1920, NormalOperation_XMP_MM_InternalProperties_1920) {

    EXPECT_TRUE(IsInternalProperty("http://ns.adobe.com/xap/1.0/mm/", "xmpMM:DocumentID"));

}



TEST(IsInternalPropertyTest_1920, NormalOperation_XMP_Text_InternalProperties_1920) {

    EXPECT_TRUE(IsInternalProperty("http://ns.adobe.com/xmp/1.0/t/", "xmpT:Title"));

}



TEST(IsInternalPropertyTest_1920, NormalOperation_XMP_PagedFile_InternalProperties_1920) {

    EXPECT_TRUE(IsInternalProperty("http://ns.adobe.com/xap/1.0/t/pg/", "xmpTPg:NPages"));

}



TEST(IsInternalPropertyTest_1920, NormalOperation_XMP_Graphics_InternalProperties_1920) {

    EXPECT_TRUE(IsInternalProperty("http://ns.adobe.com/xap/1.0/g/", "xmpG:GraphicsType"));

}



TEST(IsInternalPropertyTest_1920, NormalOperation_XMP_Image_InternalProperties_1920) {

    EXPECT_TRUE(IsInternalProperty("http://ns.adobe.com/xap/1.0/g/img/", "xmpGImg:ImageHeight"));

}



TEST(IsInternalPropertyTest_1920, NormalOperation_XMP_Font_InternalProperties_1920) {

    EXPECT_TRUE(IsInternalProperty("http://ns.adobe.com/xap/1.0/sType/font#", "stFNT:FontFamily"));

}



TEST(IsInternalPropertyTest_1920, BoundaryCondition_EmptySchema_1920) {

    EXPECT_FALSE(IsInternalProperty("", "dc:title"));

}



TEST(IsInternalPropertyTest_1920, BoundaryCondition_EmptyProperty_1920) {

    EXPECT_FALSE(IsInternalProperty("http://purl.org/dc/elements/1.1/", ""));

}
