#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/iptc.hpp"

#include "exiv2/xmp_exiv2.hpp"

#include "convert.cpp"  // Assuming this is how we include the partial implementation



using namespace Exiv2;

using ::testing::Return;

using ::testing::_;



class ConverterTest : public ::testing::Test {

protected:

    IptcData iptcData;

    XmpData xmpData;

    Converter converter{iptcData, xmpData};



    void SetUp() override {

        // Clear any existing data in the metadata containers

        iptcData.clear();

        xmpData.clear();

    }

};



TEST_F(ConverterTest_1851, CnvIptcValue_NormalOperation_1851) {

    Iptcdatum iptcDatum(IptcKey("IPTC.Application2.Caption"), new StringValue("Sample Caption"));

    iptcData.add(iptcDatum);



    converter.cnvIptcValue("IPTC.Application2.Caption", "XMP.dc.Description");



    EXPECT_EQ(xmpData["XMP.dc.Description"].toString(), "Sample Caption");

}



TEST_F(ConverterTest_1851, CnvIptcValue_KeyNotFound_1851) {

    converter.cnvIptcValue("NonExistentKey", "XMP.nonexistent");



    EXPECT_EQ(xmpData.findKey(XmpKey("XMP.nonexistent")), xmpData.end());

}



TEST_F(ConverterTest_1851, CnvIptcValue_ValueNotOk_1851) {

    auto* value = new StringValue("Invalid Value");

    value->ok_ = false;  // Force the value to be not ok



    Iptcdatum iptcDatum(IptcKey("IPTC.Application2.Caption"), value);

    iptcData.add(iptcDatum);



    converter.cnvIptcValue("IPTC.Application2.Caption", "XMP.dc.Description");



    EXPECT_EQ(xmpData.findKey(XmpKey("XMP.dc.Description")), xmpData.end());

}



TEST_F(ConverterTest_1851, CnvIptcValue_EraseEnabled_1851) {

    converter.setErase(true);



    Iptcdatum iptcDatum(IptcKey("IPTC.Application2.Caption"), new StringValue("Sample Caption"));

    iptcData.add(iptcDatum);



    converter.cnvIptcValue("IPTC.Application2.Caption", "XMP.dc.Description");



    EXPECT_EQ(xmpData["XMP.dc.Description"].toString(), "Sample Caption");

    EXPECT_EQ(iptcData.findKey(IptcKey("IPTC.Application2.Caption")), iptcData.end());

}



TEST_F(ConverterTest_1851, CnvIptcValue_CharsetConversion_1851) {

    Converter converterWithCharset{iqtData, xmpData, "ISO-8859-1"};



    Iptcdatum iptcDatum(IptcKey("IPTC.Application2.Caption"), new StringValue("\xe9"));  // 'é' in ISO-8859-1

    iptcData.add(iptcDatum);



    converterWithCharset.cnvIptcValue("IPTC.Application2.Caption", "XMP.dc.Description");



    EXPECT_EQ(xmpData["XMP.dc.Description"].toString(), "\xc3\xa9");  // 'é' in UTF-8

}



TEST_F(ConverterTest_1851, CnvIptcValue_MultipleEntries_1851) {

    Iptcdatum iptcDatum1(IptcKey("IPTC.Application2.Caption"), new StringValue("Caption 1"));

    Iptcdatum iptcDatum2(IptcKey("IPTC.Application2.Caption"), new StringValue("Caption 2"));



    iptcData.add(iptcDatum1);

    iptcData.add(iptcDatum2);



    converter.cnvIptcValue("IPTC.Application2.Caption", "XMP.dc.Description");



    EXPECT_EQ(xmpData["XMP.dc.Description"].toString(), "Caption 2");

}



TEST_F(ConverterTest_1851, CnvIptcValue_TargetNotPrepared_1851) {

    // Assuming prepareXmpTarget returns false in some cases

    testing::StrictMock<testing::NiceMock<IptcData>> mockIptcData;

    XmpData xmpData;



    Converter converter{mockIptcData, xmpData};



    Iptcdatum iptcDatum(IptcKey("IPTC.Application2.Caption"), new StringValue("Sample Caption"));

    iptcData.add(iptcDatum);



    EXPECT_CALL(mockIptcData, findKey(IptcKey("IPTC.Application2.Caption"))).WillOnce(Return(iptcData.begin()));

    EXPECT_CALL(converter, prepareXmpTarget("XMP.dc.Description", false)).WillOnce(Return(false));



    converter.cnvIptcValue("IPTC.Application2.Caption", "XMP.dc.Description");



    EXPECT_EQ(xmpData.findKey(XmpKey("XMP.dc.Description")), xmpData.end());

}
