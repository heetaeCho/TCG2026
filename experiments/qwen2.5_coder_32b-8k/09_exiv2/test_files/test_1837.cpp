#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "exiv2/xmp_exiv2.hpp"



using namespace testing;

using namespace Exiv2;



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



TEST_F(ConverterTest_NormalOperation_1837, ConvertExifArray_SuccessfulConversion_1837) {

    ExifKey fromKey("Exif.Image.Artist");

    Exifdatum exifDatum(fromKey, new StringValue);

    exifDatum.setValue("John Doe");

    exifData_.add(exifDatum);



    converter_.cnvExifArray("Exif.Image.Artist", "Xmp.dc.creator");



    EXPECT_EQ(xmpData_["Xmp.dc.creator"].toString(), "John Doe");

}



TEST_F(ConverterTest_BoundaryConditions_1837, ConvertExifArray_EmptySourceKey_1837) {

    converter_.cnvExifArray("", "Xmp.dc.creator");



    EXPECT_TRUE(xmpData_.empty());

}



TEST_F(ConverterTest_BoundaryConditions_1837, ConvertExifArray_EmptyTargetKey_1837) {

    ExifKey fromKey("Exif.Image.Artist");

    Exifdatum exifDatum(fromKey, new StringValue);

    exifDatum.setValue("John Doe");

    exifData_.add(exifDatum);



    converter_.cnvExifArray("Exif.Image.Artist", "");



    EXPECT_TRUE(xmpData_.empty());

}



TEST_F(ConverterTest_ErrorCases_1837, ConvertExifArray_SourceKeyNotFound_1837) {

    converter_.cnvExifArray("NonExistent.Key", "Xmp.dc.creator");



    EXPECT_TRUE(xmpData_.empty());

}



TEST_F(ConverterTest_ErrorCases_1837, ConvertExifArray_ValueConversionFailure_1837) {

    ExifKey fromKey("Exif.Image.Artist");

    Exifdatum exifDatum(fromKey, new StringValue);

    exifDatum.setValue("").value().ok_ = false;

    exifData_.add(exifDatum);



    converter_.cnvExifArray("Exif.Image.Artist", "Xmp.dc.creator");



    EXPECT_TRUE(xmpData_.empty());

}



TEST_F(ConverterTest_VerifyExternalInteractions_1837, ConvertExifArray_LogWarningOnConversionFailure_1837) {

    ExifKey fromKey("Exif.Image.Artist");

    Exifdatum exifDatum(fromKey, new StringValue);

    exifDatum.setValue("").value().ok_ = false;

    exifData_.add(exifDatum);



    testing::internal::CaptureStderr();

    converter_.cnvExifArray("Exif.Image.Artist", "Xmp.dc.creator");

    std::string output = testing::internal::GetCapturedStderr();



    EXPECT_TRUE(output.find("Failed to convert Exif.Image.Artist to Xmp.dc.creator") != std::string::npos);

}
