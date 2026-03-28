#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "exiv2/xmp_exiv2.hpp"

#include "./TestProjects/exiv2/src/convert.cpp"



using namespace Exiv2;

using ::testing::_;

using ::testing::Return;



class ConverterTest : public ::testing::Test {

protected:

    ExifData exifData_;

    XmpData xmpData_;

    Converter converter_{exifData_, xmpData_};



    void addExifDatum(const std::string& key, const std::vector<int64_t>& values) {

        Exifdatum datum(ExifKey(key), nullptr);

        for (const auto& value : values) {

            datum.setValue(value);

        }

        exifData_.add(datum.key(), &datum.value());

    }



    void clearData() {

        exifData_.clear();

        xmpData_.clear();

    }

};



TEST_F(ConverterTest, cnvExifGPSVersion_NoSource_1840) {

    converter_.cnvExifGPSVersion("Exif.GPSInfo.GPSVersionID", "Xmp.gps.VersionID");

    EXPECT_TRUE(xmpData_.findKey(XmpKey("Xmp.gps.VersionID")) == xmpData_.end());

}



TEST_F(ConverterTest, cnvExifGPSVersion_OneValue_1840) {

    addExifDatum("Exif.GPSInfo.GPSVersionID", {2});

    converter_.cnvExifGPSVersion("Exif.GPSInfo.GPSVersionID", "Xmp.gps.VersionID");

    EXPECT_EQ(xmpData_["Xmp.gps.VersionID"].toString(), "2");

}



TEST_F(ConverterTest, cnvExifGPSVersion_TwoValues_1840) {

    addExifDatum("Exif.GPSInfo.GPSVersionID", {2, 3});

    converter_.cnvExifGPSVersion("Exif.GPSInfo.GPSVersionID", "Xmp.gps.VersionID");

    EXPECT_EQ(xmpData_["Xmp.gps.VersionID"].toString(), "2.3");

}



TEST_F(ConverterTest, cnvExifGPSVersion_ThreeValues_1840) {

    addExifDatum("Exif.GPSInfo.GPSVersionID", {2, 3, 0});

    converter_.cnvExifGPSVersion("Exif.GPSInfo.GPSVersionID", "Xmp.gps.VersionID");

    EXPECT_EQ(xmpData_["Xmp.gps.VersionID"].toString(), "2.3.0");

}



TEST_F(ConverterTest, cnvExifGPSVersion_FourValues_1840) {

    addExifDatum("Exif.GPSInfo.GPSVersionID", {2, 3, 0, 0});

    converter_.cnvExifGPSVersion("Exif.GPSInfo.GPSVersionID", "Xmp.gps.VersionID");

    EXPECT_EQ(xmpData_["Xmp.gps.VersionID"].toString(), "2.3.0.0");

}



TEST_F(ConverterTest, cnvExifGPSVersion_PrepareXmpTargetFails_1840) {

    EXPECT_CALL(*reinterpret_cast<XmpData*>(&xmpData_), add(_, _)).WillOnce(Return(-1));

    addExifDatum("Exif.GPSInfo.GPSVersionID", {2, 3});

    converter_.cnvExifGPSVersion("Exif.GPSInfo.GPSVersionID", "Xmp.gps.VersionID");

    EXPECT_TRUE(xmpData_.findKey(XmpKey("Xmp.gps.VersionID")) == xmpData_.end());

}
