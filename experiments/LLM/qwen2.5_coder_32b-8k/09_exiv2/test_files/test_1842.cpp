#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "convert.cpp"

#include "exiv2/exif.hpp"

#include "exiv2/xmp_exiv2.hpp"



using namespace Exiv2;

using testing::_;

using testing::NiceMock;



class MockExifData : public ExifData {

public:

    MOCK_METHOD(iterator, findKey, (const ExifKey& key), (override));

    MOCK_METHOD(void, add, (const ExifKey& key, const Value* pValue), (override));

    MOCK_METHOD(void, erase, (iterator pos), (override));

};



class MockXmpData : public XmpData {

public:

    MOCK_METHOD(Xmpdatum&, operator[], (const std::string& key), (override));

};



class ConverterTest_1842 : public ::testing::Test {

protected:

    NiceMock<MockExifData> mockExifData;

    NiceMock<MockXmpData> mockXmpData;

    Converter converter{mockExifData, mockXmpData};

};



TEST_F(ConverterTest_1842, CnvExifGPSCoord_KeyNotFound_1842) {

    EXPECT_CALL(mockExifData, findKey(_)).WillOnce(testing::Return(mockExifData.end()));

    converter.cnvExifGPSCoord("GPSLatitude", "Xmp.GPSAltitude");

}



TEST_F(ConverterTest_1842, CnvExifGPSCoord_TargetPrepareFailed_1842) {

    EXPECT_CALL(mockExifData, findKey(_)).WillOnce(testing::Return(mockExifData.begin()));

    EXPECT_CALL(mockExifData, end()).WillOnce(testing::Return(mockExifData.end()));

    EXPECT_CALL(mockExifData, begin()->count()).WillOnce(testing::Return(3));

    EXPECT_CALL(mockXmpData, operator[](_)).WillOnce(testing::ReturnRef(mockXmpData["key"]));

    EXPECT_CALL(converter, prepareXmpTarget("Xmp.GPSAltitude")).WillOnce(testing::Return(false));

    converter.cnvExifGPSCoord("GPSLatitude", "Xmp.GPSAltitude");

}



TEST_F(ConverterTest_1842, CnvExifGPSCoord_CountMismatch_1842) {

    EXPECT_CALL(mockExifData, findKey(_)).WillOnce(testing::Return(mockExifData.begin()));

    EXPECT_CALL(mockExifData, end()).WillOnce(testing::Return(mockExifData.end()));

    EXPECT_CALL(mockExifData, begin()->count()).WillOnce(testing::Return(2));

    converter.cnvExifGPSCoord("GPSLatitude", "Xmp.GPSAltitude");

}



TEST_F(ConverterTest_1842, CnvExifGPSCoord_RefKeyNotFound_1842) {

    EXPECT_CALL(mockExifData, findKey(_)).WillOnce(testing::Return(mockExifData.begin()))

                                         .WillOnce(testing::Return(mockExifData.end()));

    EXPECT_CALL(mockExifData, end()).WillOnce(testing::Return(mockExifData.end()));

    EXPECT_CALL(mockExifData, begin()->count()).WillOnce(testing::Return(3));

    converter.cnvExifGPSCoord("GPSLatitude", "Xmp.GPSAltitude");

}



TEST_F(ConverterTest_1842, CnvExifGPSCoord_ZeroDenominator_1842) {

    Exiv2::Exifdatum exifDatum(ExifKey("GPSLatitude"), new Value);

    exifDatum.setValue(Rational{1, 0});

    EXPECT_CALL(mockExifData, findKey(_)).WillOnce(testing::Return(&exifDatum))

                                         .WillOnce(testing::Return(&exifDatum));

    EXPECT_CALL(mockExifData, end()).WillOnce(testing::Return(mockExifData.end()));

    EXPECT_CALL(mockExifData, begin()->count()).WillOnce(testing::Return(3));

    converter.cnvExifGPSCoord("GPSLatitude", "Xmp.GPSAltitude");

}



TEST_F(ConverterTest_1842, CnvExifGPSCoord_NormalOperation_1842) {

    Exiv2::Exifdatum exifDatum(ExifKey("GPSLatitude"), new Value);

    exifDatum.setValue(Rational{30, 1});

    exifDatum.setValue(Rational{59, 1}, 1);

    exifDatum.setValue(Rational{48, 1}, 2);



    Exiv2::Exifdatum refExifDatum(ExifKey("GPSLatitudeRef"), new Value);

    refExifDatum.setValue(std::string{"N"});



    EXPECT_CALL(mockExifData, findKey(_)).WillOnce(testing::Return(&exifDatum))

                                         .WillOnce(testing::Return(&refExifDatum));

    EXPECT_CALL(mockExifData, end()).WillOnce(testing::Return(mockExifData.end()));

    EXPECT_CALL(mockExifData, begin()->count()).WillOnce(testing::Return(3));

    EXPECT_CALL(mockXmpData, operator[](_)).WillOnce(testing::ReturnRef(mockXmpData["key"]));

    EXPECT_CALL(converter, prepareXmpTarget("Xmp.GPSAltitude")).WillOnce(testing::Return(true));

    converter.cnvExifGPSCoord("GPSLatitude", "Xmp.GPSAltitude");

}



TEST_F(ConverterTest_1842, CnvExifGPSCoord_EraseEnabled_1842) {

    Exiv2::Exifdatum exifDatum(ExifKey("GPSLatitude"), new Value);

    exifDatum.setValue(Rational{30, 1});

    exifDatum.setValue(Rational{59, 1}, 1);

    exifDatum.setValue(Rational{48, 1}, 2);



    Exiv2::Exifdatum refExifDatum(ExifKey("GPSLatitudeRef"), new Value);

    refExifDatum.setValue(std::string{"N"});



    EXPECT_CALL(mockExifData, findKey(_)).WillOnce(testing::Return(&exifDatum))

                                         .WillOnce(testing::Return(&refExifDatum));

    EXPECT_CALL(mockExifData, end()).WillOnce(testing::Return(mockExifData.end()));

    EXPECT_CALL(mockExifData, begin()->count()).WillOnce(testing::Return(3));

    EXPECT_CALL(mockXmpData, operator[](_)).WillOnce(testing::ReturnRef(mockXmpData["key"]));

    EXPECT_CALL(converter, prepareXmpTarget("Xmp.GPSAltitude")).WillOnce(testing::Return(true));

    EXPECT_CALL(mockExifData, erase(&exifDatum)).Times(2);

    converter.setErase(true);

    converter.cnvExifGPSCoord("GPSLatitude", "Xmp.GPSAltitude");

}
