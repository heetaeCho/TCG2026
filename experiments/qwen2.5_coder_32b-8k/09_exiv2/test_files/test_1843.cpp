#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "exiv2/xmp_exiv2.hpp"

#include "./TestProjects/exiv2/src/convert.cpp"



using namespace Exiv2;



class ConverterTest : public ::testing::Test {

protected:

    ExifData exifData;

    XmpData xmpData;

    Converter converter{exifData, xmpData};

};



TEST_F(ConverterTest_1843, CnvXmpValue_SuccessfulConversion_1843) {

    // Arrange

    const char* from = "xmp:ExistingKey";

    const char* to = "Exif:NewKey";

    Xmpdatum xmpDatum{XmpKey(from), new Value};

    std::string value = "SampleValue";

    xmpDatum.setValue(value);

    xmpData.add(xmpDatum);



    // Act

    converter.cnvXmpValue(from, to);



    // Assert

    EXPECT_EQ(exifData.findKey(ExifKey(to))->value(), value);

}



TEST_F(ConverterTest_1843, CnvXmpValue_XmpKeyNotFound_1843) {

    // Arrange

    const char* from = "xmp:NonExistingKey";

    const char* to = "Exif:NewKey";



    // Act & Assert

    EXPECT_NO_THROW(converter.cnvXmpValue(from, to));

}



TEST_F(ConverterTest_1843, CnvXmpValue_PrepareExifTargetFailed_1843) {

    // Arrange

    const char* from = "xmp:ExistingKey";

    const char* to = "Exif:NewKey";

    Xmpdatum xmpDatum{XmpKey(from), new Value};

    std::string value = "SampleValue";

    xmpDatum.setValue(value);

    xmpData.add(xmpDatum);



    // Mocking prepareExifTarget function to always return false

    converter.erase_ = true;  // Ensure erase is set to true for testing



    // Act

    converter.cnvXmpValue(from, to);



    // Assert

    EXPECT_EQ(exifData.findKey(ExifKey(to)), exifData.end());

}



TEST_F(ConverterTest_1843, CnvXmpValue_GetTextValueFailed_1843) {

    // Arrange

    const char* from = "xmp:ExistingKey";

    const char* to = "Exif:NewKey";

    Xmpdatum xmpDatum{XmpKey(from), new Value};

    std::string value = "";

    xmpDatum.setValue(value);

    xmpData.add(xmpDatum);



    // Act

    converter.cnvXmpValue(from, to);



    // Assert

    EXPECT_EQ(exifData.findKey(ExifKey(to)), exifData.end());

}



TEST_F(ConverterTest_1843, CnvXmpValue_EraseAfterConversion_1843) {

    // Arrange

    const char* from = "xmp:ExistingKey";

    const char* to = "Exif:NewKey";

    Xmpdatum xmpDatum{XmpKey(from), new Value};

    std::string value = "SampleValue";

    xmpDatum.setValue(value);

    xmpData.add(xmpDatum);



    converter.erase_ = true;  // Ensure erase is set to true for testing



    // Act

    converter.cnvXmpValue(from, to);



    // Assert

    EXPECT_EQ(xmpData.findKey(XmpKey(from)), xmpData.end());

}



TEST_F(ConverterTest_1843, CnvXmpValue_NoEraseAfterConversion_1843) {

    // Arrange

    const char* from = "xmp:ExistingKey";

    const char* to = "Exif:NewKey";

    Xmpdatum xmpDatum{XmpKey(from), new Value};

    std::string value = "SampleValue";

    xmpDatum.setValue(value);

    xmpData.add(xmpDatum);



    converter.erase_ = false;  // Ensure erase is set to false for testing



    // Act

    converter.cnvXmpValue(from, to);



    // Assert

    EXPECT_NE(xmpData.findKey(XmpKey(from)), xmpData.end());

}



TEST_F(ConverterTest_1843, CnvXmpValue_SetValueFailed_1843) {

    // Arrange

    const char* from = "xmp:ExistingKey";

    const char* to = "Exif:NewKey";

    Xmpdatum xmpDatum{XmpKey(from), new Value};

    std::string value = "SampleValue";

    xmpDatum.setValue(value);

    xmpData.add(xmpDatum);



    // Mocking setValue function to always return non-zero

    ExifKey key(to);

    Exifdatum ed(key);

    EXPECT_CALL(*ed.value_.get(), setValue(::testing::_)).WillOnce(testing::Return(1));



    // Act

    converter.cnvXmpValue(from, to);



    // Assert

    EXPECT_EQ(exifData.findKey(ExifKey(to)), exifData.end());

}

```


