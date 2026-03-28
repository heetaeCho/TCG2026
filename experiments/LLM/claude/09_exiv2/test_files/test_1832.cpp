#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>

// Note: The Converter class is defined in convert.cpp. We need to access it.
// Based on the interface, we use the public free functions and the Converter class.
// Since Converter may not be directly exposed in public headers, we test through
// the public API functions copyExifToXmp, copyXmpToExif, etc. if available,
// or we include the necessary internal headers.

// For direct testing of Converter, we may need to include the source or
// use the namespace directly. The code shows Converter is in namespace Exiv2.

// We'll test what we can through the observable public interface.

namespace {

using namespace Exiv2;

class ConverterExifXmpTest_1832 : public ::testing::Test {
protected:
    ExifData exifData;
    XmpData xmpData;
};

class ConverterIptcXmpTest_1832 : public ::testing::Test {
protected:
    IptcData iptcData;
    XmpData xmpData;
};

// Test the public free functions that wrap Converter functionality

TEST_F(ConverterExifXmpTest_1832, CopyExifToXmpEmptyData_1832) {
    // Converting empty exif data to xmp should not crash and xmp should remain empty
    copyExifToXmp(exifData, xmpData);
    EXPECT_TRUE(xmpData.empty());
}

TEST_F(ConverterExifXmpTest_1832, CopyXmpToExifEmptyData_1832) {
    // Converting empty xmp data to exif should not crash and exif should remain empty
    copyXmpToExif(xmpData, exifData);
    EXPECT_TRUE(exifData.empty());
}

TEST_F(ConverterIptcXmpTest_1832, CopyIptcToXmpEmptyData_1832) {
    copyIptcToXmp(iptcData, xmpData);
    EXPECT_TRUE(xmpData.empty());
}

TEST_F(ConverterIptcXmpTest_1832, CopyXmpToIptcEmptyData_1832) {
    copyXmpToIptc(xmpData, iptcData);
    EXPECT_TRUE(iptcData.empty());
}

TEST_F(ConverterExifXmpTest_1832, CopyExifToXmpWithImageDescription_1832) {
    // Add an Exif tag that should be convertible to XMP
    exifData["Exif.Image.ImageDescription"] = "Test image description";
    copyExifToXmp(exifData, xmpData);
    
    // The XMP data should now contain the equivalent XMP tag
    auto it = xmpData.findKey(XmpKey("Xmp.dc.description"));
    EXPECT_NE(it, xmpData.end());
}

TEST_F(ConverterExifXmpTest_1832, CopyXmpToExifWithDescription_1832) {
    xmpData["Xmp.dc.description"] = "Test description";
    copyXmpToExif(xmpData, exifData);
    
    auto it = exifData.findKey(ExifKey("Exif.Image.ImageDescription"));
    EXPECT_NE(it, exifData.end());
}

TEST_F(ConverterExifXmpTest_1832, CopyExifToXmpWithArtist_1832) {
    exifData["Exif.Image.Artist"] = "John Doe";
    copyExifToXmp(exifData, xmpData);
    
    auto it = xmpData.findKey(XmpKey("Xmp.dc.creator"));
    EXPECT_NE(it, xmpData.end());
}

TEST_F(ConverterExifXmpTest_1832, CopyExifToXmpWithCopyright_1832) {
    exifData["Exif.Image.Copyright"] = "Copyright 2023";
    copyExifToXmp(exifData, xmpData);
    
    auto it = xmpData.findKey(XmpKey("Xmp.dc.rights"));
    EXPECT_NE(it, xmpData.end());
}

TEST_F(ConverterExifXmpTest_1832, CopyExifToXmpWithExifVersion_1832) {
    exifData["Exif.Photo.ExifVersion"] = "0230";
    copyExifToXmp(exifData, xmpData);
    
    auto it = xmpData.findKey(XmpKey("Xmp.exif.ExifVersion"));
    EXPECT_NE(it, xmpData.end());
}

TEST_F(ConverterExifXmpTest_1832, CopyExifToXmpWithDateTimeOriginal_1832) {
    exifData["Exif.Photo.DateTimeOriginal"] = "2023:06:15 10:30:00";
    copyExifToXmp(exifData, xmpData);
    
    auto it = xmpData.findKey(XmpKey("Xmp.exif.DateTimeOriginal"));
    EXPECT_NE(it, xmpData.end());
}

TEST_F(ConverterExifXmpTest_1832, CopyXmpToExifWithDateTimeOriginal_1832) {
    xmpData["Xmp.exif.DateTimeOriginal"] = "2023-06-15T10:30:00";
    copyXmpToExif(xmpData, exifData);
    
    auto it = exifData.findKey(ExifKey("Exif.Photo.DateTimeOriginal"));
    EXPECT_NE(it, exifData.end());
}

TEST_F(ConverterExifXmpTest_1832, CopyExifToXmpWithGPSLatitude_1832) {
    exifData["Exif.GPSInfo.GPSLatitude"] = "51/1 30/1 0/1";
    exifData["Exif.GPSInfo.GPSLatitudeRef"] = "N";
    copyExifToXmp(exifData, xmpData);
    
    auto it = xmpData.findKey(XmpKey("Xmp.exif.GPSLatitude"));
    EXPECT_NE(it, xmpData.end());
}

TEST_F(ConverterExifXmpTest_1832, CopyExifToXmpWithFlash_1832) {
    exifData["Exif.Photo.Flash"] = uint16_t(1);
    copyExifToXmp(exifData, xmpData);
    
    // Flash should be converted to XMP struct
    auto it = xmpData.findKey(XmpKey("Xmp.exif.Flash"));
    // Flash may be stored as sub-properties
    bool found = false;
    for (auto xi = xmpData.begin(); xi != xmpData.end(); ++xi) {
        if (xi->key().find("Xmp.exif.Flash") != std::string::npos) {
            found = true;
            break;
        }
    }
    EXPECT_TRUE(found);
}

TEST_F(ConverterExifXmpTest_1832, CopyExifToXmpWithGPSVersionID_1832) {
    exifData["Exif.GPSInfo.GPSVersionID"] = "2 2 0 0";
    copyExifToXmp(exifData, xmpData);
    
    auto it = xmpData.findKey(XmpKey("Xmp.exif.GPSVersionID"));
    EXPECT_NE(it, xmpData.end());
}

TEST_F(ConverterExifXmpTest_1832, RoundTripExifXmpExif_1832) {
    // Test round-trip: Exif -> XMP -> Exif
    exifData["Exif.Image.ImageDescription"] = "Round trip test";
    
    copyExifToXmp(exifData, xmpData);
    
    ExifData exifData2;
    copyXmpToExif(xmpData, exifData2);
    
    auto it = exifData2.findKey(ExifKey("Exif.Image.ImageDescription"));
    EXPECT_NE(it, exifData2.end());
    if (it != exifData2.end()) {
        EXPECT_EQ(it->toString(), "Round trip test");
    }
}

TEST_F(ConverterIptcXmpTest_1832, CopyIptcToXmpWithCaption_1832) {
    iptcData["Iptc.Application2.Caption"] = "Test caption";
    copyIptcToXmp(iptcData, xmpData);
    
    auto it = xmpData.findKey(XmpKey("Xmp.dc.description"));
    EXPECT_NE(it, xmpData.end());
}

TEST_F(ConverterIptcXmpTest_1832, CopyXmpToIptcWithDescription_1832) {
    xmpData["Xmp.dc.description"] = "Test description for IPTC";
    copyXmpToIptc(xmpData, iptcData);
    
    auto it = iptcData.findKey(IptcKey("Iptc.Application2.Caption"));
    EXPECT_NE(it, iptcData.end());
}

TEST_F(ConverterIptcXmpTest_1832, CopyIptcToXmpWithKeywords_1832) {
    iptcData["Iptc.Application2.Keywords"] = "keyword1";
    copyIptcToXmp(iptcData, xmpData);
    
    auto it = xmpData.findKey(XmpKey("Xmp.dc.subject"));
    EXPECT_NE(it, xmpData.end());
}

TEST_F(ConverterIptcXmpTest_1832, CopyIptcToXmpWithCharset_1832) {
    iptcData["Iptc.Application2.Caption"] = "Test with charset";
    copyIptcToXmp(iptcData, xmpData, "UTF-8");
    
    auto it = xmpData.findKey(XmpKey("Xmp.dc.description"));
    EXPECT_NE(it, xmpData.end());
}

TEST_F(ConverterExifXmpTest_1832, MoveExifToXmpEmptyData_1832) {
    // moveExifToXmp should erase exif data after conversion
    exifData["Exif.Image.ImageDescription"] = "To be moved";
    moveExifToXmp(exifData, xmpData);
    
    // XMP should have the data
    auto xmpIt = xmpData.findKey(XmpKey("Xmp.dc.description"));
    EXPECT_NE(xmpIt, xmpData.end());
    
    // Exif should have the converted tag erased
    auto exifIt = exifData.findKey(ExifKey("Exif.Image.ImageDescription"));
    EXPECT_EQ(exifIt, exifData.end());
}

TEST_F(ConverterExifXmpTest_1832, MoveXmpToExif_1832) {
    xmpData["Xmp.dc.description"] = "To be moved to exif";
    moveXmpToExif(xmpData, exifData);
    
    auto exifIt = exifData.findKey(ExifKey("Exif.Image.ImageDescription"));
    EXPECT_NE(exifIt, exifData.end());
    
    // XMP converted tags should be erased
    auto xmpIt = xmpData.findKey(XmpKey("Xmp.dc.description"));
    EXPECT_EQ(xmpIt, xmpData.end());
}

TEST_F(ConverterIptcXmpTest_1832, MoveIptcToXmp_1832) {
    iptcData["Iptc.Application2.Caption"] = "Move IPTC to XMP";
    moveIptcToXmp(iptcData, xmpData);
    
    auto xmpIt = xmpData.findKey(XmpKey("Xmp.dc.description"));
    EXPECT_NE(xmpIt, xmpData.end());
    
    auto iptcIt = iptcData.findKey(IptcKey("Iptc.Application2.Caption"));
    EXPECT_EQ(iptcIt, iptcData.end());
}

TEST_F(ConverterIptcXmpTest_1832, MoveXmpToIptc_1832) {
    xmpData["Xmp.dc.description"] = "Move XMP to IPTC";
    moveXmpToIptc(xmpData, iptcData);
    
    auto iptcIt = iptcData.findKey(IptcKey("Iptc.Application2.Caption"));
    EXPECT_NE(iptcIt, iptcData.end());
    
    auto xmpIt = xmpData.findKey(XmpKey("Xmp.dc.description"));
    EXPECT_EQ(xmpIt, xmpData.end());
}

TEST_F(ConverterExifXmpTest_1832, CopyExifToXmpDoesNotOverwriteExisting_1832) {
    // If XMP already has a value, copyExifToXmp with default overwrite should overwrite
    xmpData["Xmp.dc.description"] = "Existing XMP description";
    exifData["Exif.Image.ImageDescription"] = "New from Exif";
    
    copyExifToXmp(exifData, xmpData);
    
    auto it = xmpData.findKey(XmpKey("Xmp.dc.description"));
    EXPECT_NE(it, xmpData.end());
}

TEST_F(ConverterExifXmpTest_1832, CopyExifToXmpWithUserComment_1832) {
    exifData["Exif.Photo.UserComment"] = "charset=\"Ascii\" User comment test";
    copyExifToXmp(exifData, xmpData);
    
    auto it = xmpData.findKey(XmpKey("Xmp.exif.UserComment"));
    EXPECT_NE(it, xmpData.end());
}

TEST_F(ConverterExifXmpTest_1832, CopyExifToXmpMultipleTags_1832) {
    exifData["Exif.Image.ImageDescription"] = "Description";
    exifData["Exif.Image.Artist"] = "Artist Name";
    exifData["Exif.Image.Copyright"] = "Copyright Notice";
    exifData["Exif.Photo.ExifVersion"] = "0230";
    
    copyExifToXmp(exifData, xmpData);
    
    EXPECT_NE(xmpData.findKey(XmpKey("Xmp.dc.description")), xmpData.end());
    EXPECT_NE(xmpData.findKey(XmpKey("Xmp.dc.creator")), xmpData.end());
    EXPECT_NE(xmpData.findKey(XmpKey("Xmp.dc.rights")), xmpData.end());
    EXPECT_NE(xmpData.findKey(XmpKey("Xmp.exif.ExifVersion")), xmpData.end());
}

TEST_F(ConverterExifXmpTest_1832, CopyExifToXmpWithGPSLongitude_1832) {
    exifData["Exif.GPSInfo.GPSLongitude"] = "0/1 7/1 3900/100";
    exifData["Exif.GPSInfo.GPSLongitudeRef"] = "W";
    copyExifToXmp(exifData, xmpData);
    
    auto it = xmpData.findKey(XmpKey("Xmp.exif.GPSLongitude"));
    EXPECT_NE(it, xmpData.end());
}

TEST_F(ConverterExifXmpTest_1832, CopyXmpToExifWithGPSCoordinates_1832) {
    xmpData["Xmp.exif.GPSLatitude"] = "51,30.0N";
    copyXmpToExif(xmpData, exifData);
    
    auto it = exifData.findKey(ExifKey("Exif.GPSInfo.GPSLatitude"));
    EXPECT_NE(it, exifData.end());
}

TEST_F(ConverterIptcXmpTest_1832, RoundTripIptcXmpIptc_1832) {
    iptcData["Iptc.Application2.Caption"] = "Round trip IPTC test";
    
    copyIptcToXmp(iptcData, xmpData);
    
    IptcData iptcData2;
    copyXmpToIptc(xmpData, iptcData2);
    
    auto it = iptcData2.findKey(IptcKey("Iptc.Application2.Caption"));
    EXPECT_NE(it, iptcData2.end());
    if (it != iptcData2.end()) {
        EXPECT_EQ(it->toString(), "Round trip IPTC test");
    }
}

TEST_F(ConverterIptcXmpTest_1832, CopyIptcToXmpWithByline_1832) {
    iptcData["Iptc.Application2.Byline"] = "Photographer Name";
    copyIptcToXmp(iptcData, xmpData);
    
    auto it = xmpData.findKey(XmpKey("Xmp.dc.creator"));
    EXPECT_NE(it, xmpData.end());
}

TEST_F(ConverterIptcXmpTest_1832, CopyIptcToXmpWithCopyrightNotice_1832) {
    iptcData["Iptc.Application2.Copyright"] = "Copyright 2023 Photographer";
    copyIptcToXmp(iptcData, xmpData);
    
    auto it = xmpData.findKey(XmpKey("Xmp.dc.rights"));
    EXPECT_NE(it, xmpData.end());
}

}  // namespace
