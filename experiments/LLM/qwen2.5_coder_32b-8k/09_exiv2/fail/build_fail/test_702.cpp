#include <gtest/gtest.h>

#include "exiv2/iptc.hpp"



namespace Exiv2 {

    class IptcDataTest : public ::testing::Test {

    protected:

        IptcData iptcData;

    };

}



using namespace Exiv2;



TEST_F(IptcDataTest_702, DetectCharset_UTF8CharacterSet_702) {

    IptcKey charsetKey("Iptc.Envelope.CharacterSet");

    Value* value = Value::create(asciiString);

    value->setDataArea(reinterpret_cast<const byte*>("\033%G"), 4); // ISO-2022 IR 87 -> UTF-8

    iptcData.add(charsetKey, value);



    const char* detectedCharset = iptcData.detectCharset();

    EXPECT_STREQ(detectedCharset, "UTF-8");

}



TEST_F(IptcDataTest_702, DetectCharset_AsciiOnly_702) {

    IptcKey key("Iptc.Application2.Byline");

    Value* value = Value::create(asciiString);

    value->setDataArea(reinterpret_cast<const byte*>("Byline"), 6);

    iptcData.add(key, value);



    const char* detectedCharset = iptcData.detectCharset();

    EXPECT_STREQ(detectedCharset, "ASCII");

}



TEST_F(IptcDataTest_702, DetectCharset_UTF8Content_702) {

    IptcKey key("Iptc.Application2.Caption");

    Value* value = Value::create(asciiString);

    value->setDataArea(reinterpret_cast<const byte*>("\xe2\x9c\x93"), 3); // UTF-8 checkmark

    iptcData.add(key, value);



    const char* detectedCharset = iptcData.detectCharset();

    EXPECT_STREQ(detectedCharset, "UTF-8");

}



TEST_F(IptcDataTest_702, DetectCharset_MixedContent_702) {

    IptcKey asciiKey("Iptc.Application2.Byline");

    Value* asciiValue = Value::create(asciiString);

    asciiValue->setDataArea(reinterpret_cast<const byte*>("Byline"), 6);

    iptcData.add(asciiKey, asciiValue);



    IptcKey utf8Key("Iptc.Application2.Caption");

    Value* utf8Value = Value::create(asciiString);

    utf8Value->setDataArea(reinterpret_cast<const byte*>("\xe2\x9c\x93"), 3); // UTF-8 checkmark

    iptcData.add(utf8Key, utf8Value);



    const char* detectedCharset = iptcData.detectCharset();

    EXPECT_STREQ(detectedCharset, "UTF-8");

}



TEST_F(IptcDataTest_702, DetectCharset_EmptyData_702) {

    const char* detectedCharset = iptcData.detectCharset();

    EXPECT_EQ(detectedCharset, nullptr);

}



TEST_F(IptcDataTest_702, DetectCharset_BrokenUTF8_702) {

    IptcKey key("Iptc.Application2.Caption");

    Value* value = Value::create(asciiString);

    value->setDataArea(reinterpret_cast<const byte*>("\xe2\x9c"), 2); // Incomplete UTF-8 sequence

    iptcData.add(key, value);



    const char* detectedCharset = iptcData.detectCharset();

    EXPECT_STREQ(detectedCharset, "ASCII");

}



TEST_F(IptcDataTest_702, DetectCharset_ErrorInValue_702) {

    IptcKey key("Iptc.Application2.Caption");

    Value* value = Value::create(asciiString);

    value->ok_ = false; // Simulate an error in the value

    iptcData.add(key, value);



    const char* detectedCharset = iptcData.detectCharset();

    EXPECT_EQ(detectedCharset, nullptr);

}
