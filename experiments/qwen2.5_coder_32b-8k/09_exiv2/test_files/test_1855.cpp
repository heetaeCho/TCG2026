#include <gtest/gtest.h>

#include "exiv2/exif.hpp"

#include "exiv2/xmp_exiv2.hpp"

#include "./TestProjects/exiv2/src/convert.cpp"



using namespace Exiv2;



class ConvertTest_1855 : public ::testing::Test {

protected:

    ExifData exifData_;

    XmpData xmpData_;



    void SetUp() override {

        // Set up any necessary preconditions for tests

    }

};



TEST_F(ConvertTest_1855, CopyExifToXmp_EmptyExif_1855) {

    copyExifToXmp(exifData_, xmpData_);

    EXPECT_EQ(xmpData_.count(), 0);

}



TEST_F(ConvertTest_1855, CopyExifToXmp_SingleEntry_1855) {

    ExifKey key("Exif.Image.Artist");

    Value* value = new StringValue("John Doe");

    exifData_.add(key, value);



    copyExifToXmp(exifData_, xmpData_);

    

    EXPECT_EQ(xmpData_.count(), 1);

    Xmpdatum xmpDatum = xmpData_["Xmp.tiff.Artist"];

    EXPECT_STREQ(xmpDatum.value().c_str(), "John Doe");

}



TEST_F(ConvertTest_1855, CopyExifToXmp_MultipleEntries_1855) {

    exifData_.add(ExifKey("Exif.Image.Artist"), new StringValue("John Doe"));

    exifData_.add(ExifKey("Exif.Image.Copyright"), new StringValue("Example Corp"));



    copyExifToXmp(exifData_, xmpData_);



    EXPECT_EQ(xmpData_.count(), 2);

    Xmpdatum artistDatum = xmpData_["Xmp.tiff.Artist"];

    EXPECT_STREQ(artistDatum.value().c_str(), "John Doe");

    Xmpdatum copyrightDatum = xmpData_["Xmp.dc.rights"];

    EXPECT_STREQ(copyrightDatum.value().c_str(), "Example Corp");

}



TEST_F(ConvertTest_1855, CopyExifToXmp_NoOverwrite_1855) {

    exifData_.add(ExifKey("Exif.Image.Artist"), new StringValue("John Doe"));

    xmpData_.add(XmpKey("Xmp.tiff.Artist"), new StringValue("Original Artist"));



    copyExifToXmp(exifData_, xmpData_);



    EXPECT_EQ(xmpData_.count(), 1);

    Xmpdatum artistDatum = xmpData_["Xmp.tiff.Artist"];

    EXPECT_STREQ(artistDatum.value().c_str(), "Original Artist");

}



TEST_F(ConvertTest_1855, CopyExifToXmp_Overwrite_1855) {

    exifData_.add(ExifKey("Exif.Image.Artist"), new StringValue("John Doe"));

    xmpData_.add(XmpKey("Xmp.tiff.Artist"), new StringValue("Original Artist"));



    Converter converter(exifData_, xmpData_);

    converter.setOverwrite(true);

    converter.cnvToXmp();



    EXPECT_EQ(xmpData_.count(), 1);

    Xmpdatum artistDatum = xmpData_["Xmp.tiff.Artist"];

    EXPECT_STREQ(artistDatum.value().c_str(), "John Doe");

}



TEST_F(ConvertTest_1855, CopyExifToXmp_EraseFirst_1855) {

    exifData_.add(ExifKey("Exif.Image.Artist"), new StringValue("John Doe"));

    xmpData_.add(XmpKey("Xmp.tiff.Artist"), new StringValue("Original Artist"));



    Converter converter(exifData_, xmpData_);

    converter.setErase(true);

    converter.cnvToXmp();



    EXPECT_EQ(xmpData_.count(), 1);

    Xmpdatum artistDatum = xmpData_["Xmp.tiff.Artist"];

    EXPECT_STREQ(artistDatum.value().c_str(), "John Doe");

}
