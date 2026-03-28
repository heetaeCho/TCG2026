#include <gtest/gtest.h>

#include "convert.cpp"

#include "datasets.hpp"

#include "iptc.hpp"

#include "xmp_exiv2.hpp"

#include "error.hpp"

#include "value.hpp"

#include "types.hpp"



using namespace Exiv2;



class ConverterTest : public ::testing::Test {

protected:

    void SetUp() override {

        xmpData = std::make_unique<XmpData>();

        iptcData = std::make_unique<IptcData>();

        converter = std::make_unique<Converter>(*iptcData, *xmpData);

    }



    std::unique_ptr<XmpData> xmpData;

    std::unique_ptr<IptcData> iptcData;

    std::unique_ptr<Converter> converter;

};



TEST_F(ConverterTest_1852, CnvXmpValueToIptc_XmpKeyNotFound_1852) {

    converter->cnvXmpValueToIptc("NonExistentXmpKey", "SomeIptcKey");

    EXPECT_EQ(iptcData->findKey(IptcKey("SomeIptcKey")), iptcData->end());

}



TEST_F(ConverterTest_1852, CnvXmpValueToIptc_PrepareIptcTargetFails_1852) {

    ON_CALL(*iptcData, add(_, _)).WillByDefault(::testing::Return(-1));

    xmpData->add(XmpKey("Exif.Image.Artist"), new AsciiValue("ArtistName"));

    converter->cnvXmpValueToIptc("Exif.Image.Artist", "NonExistentIptcKey");

    EXPECT_EQ(iptcData->findKey(IptcKey("NonExistentIptcKey")), iptcData->end());

}



TEST_F(ConverterTest_1852, CnvXmpValueToIptc_XmpTextConversionSuccess_1852) {

    xmpData->add(XmpKey("Exif.Image.Artist"), new AsciiValue("ArtistName"));

    converter->cnvXmpValueToIptc("Exif.Image.Artist", "Iptc.Application2.Byline");

    auto iptcEntry = iptcData->findKey(IptcKey("Iptc.Application2.Byline"));

    EXPECT_NE(iptcEntry, iptcData->end());

    EXPECT_EQ(iptcEntry->toString(), "ArtistName");

}



TEST_F(ConverterTest_1852, CnvXmpValueToIptc_LangAltConversionSuccess_1852) {

    Xmpdatum xmpDatum(XmpKey("dc.description"), new LangAltValue);

    static_cast<LangAltValue&>(*xmpDatum.getValue()).add("en", "EnglishDescription");

    xmpData->add(xmpDatum);

    converter->cnvXmpValueToIptc("dc.description", "Iptc.Application2.Caption");

    auto iptcEntry = iptcData->findKey(IptcKey("Iptc.Application2.Caption"));

    EXPECT_NE(iptcEntry, iptcData->end());

    EXPECT_EQ(iptcEntry->toString(), "EnglishDescription");

}



TEST_F(ConverterTest_1852, CnvXmpValueToIptc_MultiValueConversionSuccess_1852) {

    Xmpdatum xmpDatum(XmpKey("dc.subject"), new ArrayValue);

    static_cast<ArrayValue&>(*xmpDatum.getValue()).push_back("Subject1");

    static_cast<ArrayValue&>(*xmpDatum.getValue()).push_back("Subject2");

    xmpData->add(xmpDatum);

    converter->cnvXmpValueToIptc("dc.subject", "Iptc.Application2.Keywords");

    auto iptcEntry = iptcData->findKey(IptcKey("Iptc.Application2.Keywords"));

    EXPECT_NE(iptcEntry, iptcData->end());

    EXPECT_EQ(iptcEntry->toString(), "Subject1");

}



TEST_F(ConverterTest_1852, CnvXmpValueToIptc_ValueConversionFails_1852) {

    Xmpdatum xmpDatum(XmpKey("Exif.Image.Artist"), new AsciiValue);

    static_cast<AsciiValue&>(*xmpDatum.getValue()).setValue("");

    xmpData->add(xmpDatum);

    converter->cnvXmpValueToIptc("Exif.Image.Artist", "Iptc.Application2.Byline");

    auto iptcEntry = iptcData->findKey(IptcKey("Iptc.Application2.Byline"));

    EXPECT_EQ(iptcEntry, iptcData->end());

}



TEST_F(ConverterTest_1852, CnvXmpValueToIptc_CharacterSetSet_1852) {

    xmpData->add(XmpKey("Exif.Image.Artist"), new AsciiValue("ArtistName"));

    converter->cnvXmpValueToIptc("Exif.Image.Artist", "Iptc.Application2.Byline");

    auto charsetEntry = iptcData->findKey(IptcKey("Iptc.Envelope.CharacterSet"));

    EXPECT_NE(charsetEntry, iptcData->end());

    EXPECT_EQ(charsetEntry->toString(), "\033%G");

}



TEST_F(ConverterTest_1852, CnvXmpValueToIptc_XmpDataEraseOnSuccess_1852) {

    xmpData->add(XmpKey("Exif.Image.Artist"), new AsciiValue("ArtistName"));

    converter->setErase(true);

    converter->cnvXmpValueToIptc("Exif.Image.Artist", "Iptc.Application2.Byline");

    EXPECT_EQ(xmpData->findKey(XmpKey("Exif.Image.Artist")), xmpData->end());

}



TEST_F(ConverterTest_1852, CnvXmpValueToIptc_XmpDataNotErasedOnFailure_1852) {

    converter->setErase(true);

    converter->cnvXmpValueToIptc("NonExistentXmpKey", "SomeIptcKey");

    EXPECT_NE(xmpData->findKey(XmpKey("NonExistentXmpKey")), xmpData->end());

}
