#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "convert.cpp"

#include "types.hpp"



using namespace Exiv2;

using ::testing::_;

using ::testing::InvokeWithoutArgs;



class MockConverter : public Converter {

public:

    MOCK_METHOD(void, cnvExifValue, (const char*, const char*), (override));

    MOCK_METHOD(void, cnvIptcValue, (const char*, const char*), (override));



    MockConverter(ExifData & exifData, XmpData & xmpData) : Converter(exifData, xmpData) {}

    MockConverter(IptcData & iptcData, XmpData & xmpData, const char * iptcCharset) : Converter(iptcData, xmpData, iptcCharset) {}



    void setConversion(Conversion conversion) {

        conversion_.push_back(conversion);

    }

};



class ConverterTest_1833 : public ::testing::Test {

protected:

    ExifData exifData;

    IptcData iptcData;

    XmpData xmpData;

    MockConverter converterExif{exifData, xmpData};

    MockConverter converterIptc{iptcData, xmpData, "charset"};

};



TEST_F(ConverterTest_1833, ConvertExifValueCalledWhenExifDataAvailable_1833) {

    Conversion conversion = {mdExif, "exifKey", "xmpKey", &MockConverter::cnvExifValue, nullptr};

    converterExif.setConversion(conversion);



    EXPECT_CALL(converterExif, cnvExifValue("exifKey", "xmpKey")).Times(1);

    converterExif.cnvToXmp();

}



TEST_F(ConverterTest_1833, ConvertIptcValueCalledWhenIptcDataAvailable_1833) {

    Conversion conversion = {mdIptc, "iptcKey", "xmpKey", &MockConverter::cnvIptcValue, nullptr};

    converterIptc.setConversion(conversion);



    EXPECT_CALL(converterIptc, cnvIptcValue("iptcKey", "xmpKey")).Times(1);

    converterIptc.cnvToXmp();

}



TEST_F(ConverterTest_1833, NoConversionWhenNoMatchingDataAvailable_1833) {

    Conversion conversion = {mdComment, "commentKey", "xmpKey", &MockConverter::cnvExifValue, nullptr};

    converterExif.setConversion(conversion);



    EXPECT_CALL(converterExif, cnvExifValue("commentKey", "xmpKey")).Times(0);

    converterExif.cnvToXmp();

}



TEST_F(ConverterTest_1833, MultipleConversionsCalled_1833) {

    Conversion conversion1 = {mdExif, "exifKey1", "xmpKey1", &MockConverter::cnvExifValue, nullptr};

    Conversion conversion2 = {mdIptc, "iptcKey2", "xmpKey2", &MockConverter::cnvIptcValue, nullptr};

    converterExif.setConversion(conversion1);

    converterIptc.setConversion(conversion2);



    EXPECT_CALL(converterExif, cnvExifValue("exifKey1", "xmpKey1")).Times(1);

    EXPECT_CALL(converterIptc, cnvIptcValue("iptcKey2", "xmpKey2")).Times(1);

    converterExif.cnvToXmp();

    converterIptc.cnvToXmp();

}



TEST_F(ConverterTest_1833, NoConversionsWhenNoDataAvailable_1833) {

    EXPECT_CALL(converterExif, cnvExifValue(_, _)).Times(0);

    converterExif.cnvToXmp();

}
