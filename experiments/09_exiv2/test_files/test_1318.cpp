#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/xmp_exiv2.hpp"

#include "XMP_Const.h"



using namespace Exiv2;



class XmpParserTest_1318 : public ::testing::Test {

protected:

    XmpData xmpData;

    std::string xmpPacket;

};



TEST_F(XmpParserTest_1318, EncodeEmptyXmpData_ReturnsZero_1318) {

    int result = XmpParser().encode(xmpPacket, xmpData, 0, 0);

    EXPECT_EQ(result, 0);

    EXPECT_TRUE(xmpPacket.empty());

}



TEST_F(XmpParserTest_1318, EncodeWithValidXmpData_ReturnsZero_1318) {

    Xmpdatum datum("http://purl.org/dc/elements/1.1/title", new Value(std::string("Sample Title")));

    xmpData.add(datum);

    int result = XmpParser().encode(xmpPacket, xmpData, 0, 0);

    EXPECT_EQ(result, 0);

    EXPECT_FALSE(xmpPacket.empty());

}



TEST_F(XmpParserTest_1318, EncodeWithLangAlt_ReturnsZero_1318) {

    LangAlt langAlt;

    langAlt["x-default"] = "Default Title";

    langAlt["en"] = "English Title";

    Xmpdatum datum("http://purl.org/dc/elements/1.1/title", new Value(langAlt));

    xmpData.add(datum);

    int result = XmpParser().encode(xmpPacket, xmpData, 0, 0);

    EXPECT_EQ(result, 0);

    EXPECT_FALSE(xmpPacket.empty());

}



TEST_F(XmpParserTest_1318, EncodeWithXmpBag_ReturnsZero_1318) {

    XmpArray bag(XmpArrayType::kArrayIsOrdered);

    bag.push_back("Item1");

    bag.push_back("Item2");

    Xmpdatum datum("http://purl.org/dc/elements/1.1/contributor", new Value(bag));

    xmpData.add(datum);

    int result = XmpParser().encode(xmpPacket, xmpData, 0, 0);

    EXPECT_EQ(result, 0);

    EXPECT_FALSE(xmpPacket.empty());

}



TEST_F(XmpParserTest_1318, EncodeWithXmpSeq_ReturnsZero_1318) {

    XmpArray seq(XmpArrayType::kArrayIsOrdered);

    seq.push_back("Item1");

    seq.push_back("Item2");

    Xmpdatum datum("http://purl.org/dc/elements/1.1/contributor", new Value(seq));

    xmpData.add(datum);

    int result = XmpParser().encode(xmpPacket, xmpData, 0, 0);

    EXPECT_EQ(result, 0);

    EXPECT_FALSE(xmpPacket.empty());

}



TEST_F(XmpParserTest_1318, EncodeWithXmpAlt_ReturnsZero_1318) {

    XmpArray alt(XmpArrayType::kArrayIsAlternate);

    alt.push_back("Item1");

    alt.push_back("Item2");

    Xmpdatum datum("http://purl.org/dc/elements/1.1/contributor", new Value(alt));

    xmpData.add(datum);

    int result = XmpParser().encode(xmpPacket, xmpData, 0, 0);

    EXPECT_EQ(result, 0);

    EXPECT_FALSE(xmpPacket.empty());

}



TEST_F(XmpParserTest_1318, EncodeWithInvalidXmpValue_ReturnsError_1318) {

    Xmpdatum datum("http://purl.org/dc/elements/1.1/title", new Value(static_cast<TypeId>(lastTypeId)));

    xmpData.add(datum);

    int result = XmpParser().encode(xmpPacket, xmpData, 0, 0);

    EXPECT_EQ(result, 45); // kerUnhandledXmpdatum

}



TEST_F(XmpParserTest_1318, EncodeWithInitializationFailure_ReturnsError_1318) {

    EXPECT_CALL(*this, XmpParser::Initialize()).WillOnce(::testing::Return(false));

    int result = XmpParser().encode(xmpPacket, xmpData, 0, 0);

    EXPECT_EQ(result, 41); // kerXMPToolkitError

}



TEST_F(XmpParserTest_1318, EncodeWithSerializeFailure_ReturnsError_1318) {

    EXPECT_CALL(*this, TXMPMeta::SerializeToBuffer(::testing::_, ::testing::_, ::testing::_))

        .WillOnce(::testing::Return(kXMPErr_NoMemory));

    int result = XmpParser().encode(xmpPacket, xmpData, 0, 0);

    EXPECT_EQ(result, 41); // kerXMPToolkitError

}
