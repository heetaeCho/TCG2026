#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"



namespace Exiv2 {

    class ExifData;

    ExifData::const_iterator exposureBiasValue(const ExifData& ed);

}



using namespace Exiv2;



class ExposureBiasValueTest_532 : public ::testing::Test {

protected:

    ExifData exifData;

};



TEST_F(ExposureBiasValueTest_532, NormalOperation_ExposureBiasValueFound_532) {

    // Arrange

    const std::string key = "Exif.Photo.ExposureBiasValue";

    ExivData::Exifdatum datum(key);

    exifData.add(datum);



    // Act

    auto result = exposureBiasValue(exifData);



    // Assert

    EXPECT_EQ(result->key(), key);

}



TEST_F(ExposureBiasValueTest_532, NormalOperation_SecondKeyFound_532) {

    // Arrange

    const std::string key = "Exif.Image.ExposureBiasValue";

    ExivData::Exifdatum datum(key);

    exifData.add(datum);



    // Act

    auto result = exposureBiasValue(exifData);



    // Assert

    EXPECT_EQ(result->key(), key);

}



TEST_F(ExposureBiasValueTest_532, NormalOperation_ThirdKeyFound_532) {

    // Arrange

    const std::string key = "Exif.MinoltaCs5D.ExposureManualBias";

    ExivData::Exifdatum datum(key);

    exifData.add(datum);



    // Act

    auto result = exposureBiasValue(exifData);



    // Assert

    EXPECT_EQ(result->key(), key);

}



TEST_F(ExposureBiasValueTest_532, NormalOperation_FourthKeyFound_532) {

    // Arrange

    const std::string key = "Exif.OlympusRd.ExposureBiasValue";

    ExivData::Exifdatum datum(key);

    exifData.add(datum);



    // Act

    auto result = exposureBiasValue(exifData);



    // Assert

    EXPECT_EQ(result->key(), key);

}



TEST_F(ExposureBiasValueTest_532, NormalOperation_FifthKeyFound_532) {

    // Arrange

    const std::string key = "Exif.OlympusRd2.ExposureBiasValue";

    ExivData::Exifdatum datum(key);

    exifData.add(datum);



    // Act

    auto result = exposureBiasValue(exifData);



    // Assert

    EXPECT_EQ(result->key(), key);

}



TEST_F(ExposureBiasValueTest_532, BoundaryCondition_NoMatchingKeys_532) {

    // Arrange

    const std::string key = "Nonexistent.Key";

    ExivData::Exifdatum datum(key);

    exifData.add(datum);



    // Act

    auto result = exposureBiasValue(exifData);



    // Assert

    EXPECT_EQ(result, exifData.end());

}



TEST_F(ExposureBiasValueTest_532, BoundaryCondition_EmptyExifData_532) {

    // Arrange (exifData is empty)



    // Act

    auto result = exposureBiasValue(exifData);



    // Assert

    EXPECT_EQ(result, exifData.end());

}
