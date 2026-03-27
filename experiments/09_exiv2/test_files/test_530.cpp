#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "TestProjects/exiv2/src/easyaccess.cpp"



using namespace Exiv2;

using ::testing::Return;



class ExifDataMock : public ExifData {

public:

    MOCK_CONST_METHOD1(findKey, const_iterator(const ExifKey& key));

};



TEST_F(ExifDataMock, ApertureValue_NormalOperation_530) {

    ExifDataMock mockExifData;

    Exifdatum apertureDatum("Exif.Photo.ApertureValue", Value::floatValue);

    EXPECT_CALL(mockExifData, findKey(_)).WillOnce(Return(&apertureDatum));



    const_iterator result = apertureValue(mockExifData);

    ASSERT_NE(result, mockExifData.end());

}



TEST_F(ExifDataMock, ApertureValue_NotFound_530) {

    ExifDataMock mockExifData;

    EXPECT_CALL(mockExifData, findKey(_)).WillOnce(Return(mockExifData.end()));



    const_iterator result = apertureValue(mockExifData);

    ASSERT_EQ(result, mockExifData.end());

}



TEST_F(ExifDataMock, ApertureValue_BoundaryConditions_530) {

    ExifDataMock mockExifData;

    Exifdatum apertureDatum("Exif.Photo.ApertureValue", Value::floatValue);

    EXPECT_CALL(mockExifData, findKey(_)).WillOnce(Return(&apertureDatum));



    const_iterator result = apertureValue(mockExifData);

    ASSERT_NE(result, mockExifData.end());



    Exifdatum emptyDatum;

    EXPECT_CALL(mockExifData, findKey(_)).WillOnce(Return(&emptyDatum));

    

    result = apertureValue(mockExifData);

    ASSERT_EQ(result, mockExifData.end());

}
