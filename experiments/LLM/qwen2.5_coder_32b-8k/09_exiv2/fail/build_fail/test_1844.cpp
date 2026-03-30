#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "exiv2/xmp_exiv2.hpp"

#include "TestProjects/exiv2/src/convert.cpp"



using namespace Exiv2;

using testing::_;

using testing::Return;



class ConverterTest_1844 : public ::testing::Test {

protected:

    void SetUp() override {

        exifData = std::make_unique<ExifData>();

        xmpData = std::make_unique<XmpData>();

        converter = std::make_unique<Converter>(*exifData, *xmpData);

    }



    std::unique_ptr<ExifData> exifData;

    std::unique_ptr<XmpData> xmpData;

    std::unique_ptr<Converter> converter;

};



TEST_F(ConverterTest_1844, CnvXmpComment_SimpleCase_1844) {

    const char* from = "Xmp.dc.creator";

    const char* to = "Exif.Image.Artist";



    // Add a key-value pair to XmpData

    XmpKey xmpKey(from);

    std::string value = "Test Creator";

    xmpData->add(xmpKey, new StringValue(value));



    converter->cnvXmpComment(from, to);



    EXPECT_EQ((*exifData)[to].toString(), "charset=Unicode Test Creator");

}



TEST_F(ConverterTest_1844, CnvXmpComment_KeyNotFound_1844) {

    const char* from = "Xmp.dc.nonexistent";

    const char* to = "Exif.Image.Artist";



    converter->cnvXmpComment(from, to);



    EXPECT_TRUE(exifData->findKey(to) == exifData->end());

}



TEST_F(ConverterTest_1844, CnvXmpComment_GetTextValueFails_1844) {

    const char* from = "Xmp.dc.creator";

    const char* to = "Exif.Image.Artist";



    // Add a key-value pair to XmpData with a non-string value

    XmpKey xmpKey(from);

    xmpData->add(xmpKey, new RationalValue(Rational(1, 2)));



    converter->cnvXmpComment(from, to);



    EXPECT_TRUE(exifData->findKey(to) == exifData->end());

}



TEST_F(ConverterTest_1844, CnvXmpComment_EraseFlagTrue_1844) {

    const char* from = "Xmp.dc.creator";

    const char* to = "Exif.Image.Artist";



    converter->setErase(true);



    // Add a key-value pair to XmpData

    XmpKey xmpKey(from);

    std::string value = "Test Creator";

    xmpData->add(xmpKey, new StringValue(value));



    converter->cnvXmpComment(from, to);



    EXPECT_TRUE(exifData->findKey(to) != exifData->end());

    EXPECT_TRUE(xmpData->findKey(xmpKey) == xmpData->end());

}



TEST_F(ConverterTest_1844, CnvXmpComment_EraseFlagFalse_1844) {

    const char* from = "Xmp.dc.creator";

    const char* to = "Exif.Image.Artist";



    converter->setErase(false);



    // Add a key-value pair to XmpData

    XmpKey xmpKey(from);

    std::string value = "Test Creator";

    xmpData->add(xmpKey, new StringValue(value));



    converter->cnvXmpComment(from, to);



    EXPECT_TRUE(exifData->findKey(to) != exifData->end());

    EXPECT_TRUE(xmpData->findKey(xmpKey) != xmpData->end());

}
