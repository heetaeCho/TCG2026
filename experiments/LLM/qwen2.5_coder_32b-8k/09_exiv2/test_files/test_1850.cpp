#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "exiv2/xmp_exiv2.hpp"

#include "exiv2/value.hpp"

#include "convert.cpp"



using namespace Exiv2;

using testing::_;

using testing::Return;



class ConverterTest : public ::testing::Test {

protected:

    ExifData exifData_;

    XmpData xmpData_;

    Converter converter_{exifData_, xmpData_};



    void SetUp() override {

        // Clear any initial state

        exifData_.clear();

        xmpData_.clear();

    }

};



TEST_F(ConverterTest, CnvXmpGPSCoord_SuccessfulConversion_1850) {

    // Arrange

    const char* from = "Xmp.exif.GPSLatitude";

    const char* to = "Exif.GPSInfo.GPSLatitude";



    Xmpdatum xmpDatum(XmpKey(from), nullptr);

    xmpDatum.setValue("34, 12.345678 N");

    xmpData_.add(xmpDatum);



    // Act

    converter_.cnvXmpGPSCoord(from, to);



    // Assert

    auto pos = exifData_.findKey(ExifKey(to));

    ASSERT_NE(pos, exifData_.end());

    EXPECT_EQ(pos->toString(), "34 12/1 22379685/1000000");



    pos = exifData_.findKey(ExifKey(std::string(to) + "Ref"));

    ASSERT_NE(pos, exifData_.end());

    EXPECT_EQ(pos->toString(), "N");

}



TEST_F(ConverterTest, CnvXmpGPSCoord_EmptyValue_1850) {

    // Arrange

    const char* from = "Xmp.exif.GPSLatitude";

    const char* to = "Exif.GPSInfo.GPSLatitude";



    Xmpdatum xmpDatum(XmpKey(from), nullptr);

    xmpDatum.setValue("");

    xmpData_.add(xmpDatum);



    // Act

    converter_.cnvXmpGPSCoord(from, to);



    // Assert

    auto pos = exifData_.findKey(ExifKey(to));

    EXPECT_EQ(pos, exifData_.end());



    pos = exifData_.findKey(ExifKey(std::string(to) + "Ref"));

    EXPECT_EQ(pos, exifData_.end());

}



TEST_F(ConverterTest, CnvXmpGPSCoord_InvalidFormat_1850) {

    // Arrange

    const char* from = "Xmp.exif.GPSLatitude";

    const char* to = "Exif.GPSInfo.GPSLatitude";



    Xmpdatum xmpDatum(XmpKey(from), nullptr);

    xmpDatum.setValue("34, 12.345678"); // Missing reference character

    xmpData_.add(xmpDatum);



    // Act

    converter_.cnvXmpGPSCoord(from, to);



    // Assert

    auto pos = exifData_.findKey(ExifKey(to));

    EXPECT_EQ(pos, exifData_.end());



    pos = exifData_.findKey(ExifKey(std::string(to) + "Ref"));

    EXPECT_EQ(pos, exifData_.end());

}



TEST_F(ConverterTest, CnvXmpGPSCoord_InvalidReferenceChar_1850) {

    // Arrange

    const char* from = "Xmp.exif.GPSLatitude";

    const char* to = "Exif.GPSInfo.GPSLatitude";



    Xmpdatum xmpDatum(XmpKey(from), nullptr);

    xmpDatum.setValue("34, 12.345678 Q"); // Invalid reference character

    xmpData_.add(xmpDatum);



    // Act

    converter_.cnvXmpGPSCoord(from, to);



    // Assert

    auto pos = exifData_.findKey(ExifKey(to));

    EXPECT_EQ(pos, exifData_.end());



    pos = exifData_.findKey(ExifKey(std::string(to) + "Ref"));

    EXPECT_EQ(pos, exifData_.end());

}



TEST_F(ConverterTest, CnvXmpGPSCoord_MissingFromKey_1850) {

    // Arrange

    const char* from = "Xmp.exif.GPSLatitude";

    const char* to = "Exif.GPSInfo.GPSLatitude";



    // No XMP key added



    // Act

    converter_.cnvXmpGPSCoord(from, to);



    // Assert

    auto pos = exifData_.findKey(ExifKey(to));

    EXPECT_EQ(pos, exifData_.end());



    pos = exifData_.findKey(ExifKey(std::string(to) + "Ref"));

    EXPECT_EQ(pos, exifData_.end());

}
