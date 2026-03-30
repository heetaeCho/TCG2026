#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include "catch2/internal/catch_xmlwriter.hpp"



using namespace Catch;

using ::testing::_;

using ::testing::HasSubstr;



TEST_F(XmlEncodeTest_466, EncodeTo_NormalOperation_466) {

    XmlEncode xmlEncoder(StringRef("Hello <World>&"), ForWhat::ForTextNodes);

    std::ostringstream os;

    xmlEncoder.encodeTo(os);

    EXPECT_EQ(os.str(), "Hello &lt;World&gt;&amp;");

}



TEST_F(XmlEncodeTest_466, EncodeTo_BoundaryCondition_EmptyString_466) {

    XmlEncode xmlEncoder(StringRef(""), ForWhat::ForTextNodes);

    std::ostringstream os;

    xmlEncoder.encodeTo(os);

    EXPECT_EQ(os.str(), "");

}



TEST_F(XmlEncodeTest_466, EncodeTo_BoundaryCondition_SingleCharacter_466) {

    XmlEncode xmlEncoder(StringRef("A"), ForWhat::ForTextNodes);

    std::ostringstream os;

    xmlEncoder.encodeTo(os);

    EXPECT_EQ(os.str(), "A");

}



TEST_F(XmlEncodeTest_466, EncodeTo_ForAttributes_DoubleQuote_466) {

    XmlEncode xmlEncoder(StringRef("\"Hello\""), ForWhat::ForAttributes);

    std::ostringstream os;

    xmlEncoder.encodeTo(os);

    EXPECT_EQ(os.str(), "&quot;Hello&quot;");

}



TEST_F(XmlEncodeTest_466, EncodeTo_ForTextNodes_NoSpecialCharacters_466) {

    XmlEncode xmlEncoder(StringRef("NoSpecial"), ForWhat::ForTextNodes);

    std::ostringstream os;

    xmlEncoder.encodeTo(os);

    EXPECT_EQ(os.str(), "NoSpecial");

}



TEST_F(XmlEncodeTest_466, EncodeTo_GreaterThanInsideCDATA_466) {

    XmlEncode xmlEncoder(StringRef("]]>"), ForWhat::ForTextNodes);

    std::ostringstream os;

    xmlEncoder.encodeTo(os);

    EXPECT_EQ(os.str(), "&gt;");

}



TEST_F(XmlEncodeTest_466, EncodeTo_ControlCharacters_HexEscape_466) {

    XmlEncode xmlEncoder(StringRef("\x01\x02\x7F"), ForWhat::ForTextNodes);

    std::ostringstream os;

    xmlEncoder.encodeTo(os);

    EXPECT_EQ(os.str(), "&#x1;&#x2;&#x7F;");

}



TEST_F(XmlEncodeTest_466, EncodeTo_InvalidUTF8_HexEscape_466) {

    XmlEncode xmlEncoder(StringRef("\xC0\x80"), ForWhat::ForTextNodes); // Invalid UTF-8 sequence

    std::ostringstream os;

    xmlEncoder.encodeTo(os);

    EXPECT_EQ(os.str(), "&#xC0;&#x80;");

}



TEST_F(XmlEncodeTest_466, EncodeTo_UTF8MultibyteValid_466) {

    XmlEncode xmlEncoder(StringRef("\xC3\xA9"), ForWhat::ForTextNodes); // é

    std::ostringstream os;

    xmlEncoder.encodeTo(os);

    EXPECT_EQ(os.str(), "é");

}



TEST_F(XmlEncodeTest_466, EncodeTo_UTF8MultibyteInvalid_466) {

    XmlEncode xmlEncoder(StringRef("\xE0\xA0"), ForWhat::ForTextNodes); // Invalid UTF-8 sequence

    std::ostringstream os;

    xmlEncoder.encodeTo(os);

    EXPECT_EQ(os.str(), "&#xE0;&#xA0;");

}
