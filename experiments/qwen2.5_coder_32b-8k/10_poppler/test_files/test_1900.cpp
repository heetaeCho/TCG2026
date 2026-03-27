#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "GfxFont.h"

#include "GlobalParams.cc"



using namespace std;

using testing::_;

using testing::Return;



class MockGooString : public GooString {

public:

    MOCK_CONST_METHOD0(toStr, const std::string&());

};



class MockGfxCIDFont : public GfxCIDFont {

public:

    using GfxCIDFont::GfxCIDFont;

    MOCK_CONST_METHOD0(getCollection, const GooString*());

};



TEST_F(WriteBatchTest_1900, NormalOperation_AdobeGB1_1900) {

    MockGfxCIDFont font("tag", Ref(), "name", GfxFontType::unknown, Ref(), nullptr);

    MockGooString collection;

    EXPECT_CALL(collection, toStr()).WillOnce(Return("Adobe-GB1"));

    EXPECT_CALL(font, getCollection()).WillOnce(Return(&collection));



    const char* result = getFontLang(static_cast<const GfxFont&>(font));

    EXPECT_STREQ(result, "zh-cn");

}



TEST_F(WriteBatchTest_1900, NormalOperation_AdobeCNS1_1900) {

    MockGfxCIDFont font("tag", Ref(), "name", GfxFontType::unknown, Ref(), nullptr);

    MockGooString collection;

    EXPECT_CALL(collection, toStr()).WillOnce(Return("Adobe-CNS1"));

    EXPECT_CALL(font, getCollection()).WillOnce(Return(&collection));



    const char* result = getFontLang(static_cast<const GfxFont&>(font));

    EXPECT_STREQ(result, "zh-tw");

}



TEST_F(WriteBatchTest_1900, NormalOperation_AdobeJapan1_1900) {

    MockGfxCIDFont font("tag", Ref(), "name", GfxFontType::unknown, Ref(), nullptr);

    MockGooString collection;

    EXPECT_CALL(collection, toStr()).WillOnce(Return("Adobe-Japan1"));

    EXPECT_CALL(font, getCollection()).WillOnce(Return(&collection));



    const char* result = getFontLang(static_cast<const GfxFont&>(font));

    EXPECT_STREQ(result, "ja");

}



TEST_F(WriteBatchTest_1900, NormalOperation_AdobeJapan2_1900) {

    MockGfxCIDFont font("tag", Ref(), "name", GfxFontType::unknown, Ref(), nullptr);

    MockGooString collection;

    EXPECT_CALL(collection, toStr()).WillOnce(Return("Adobe-Japan2"));

    EXPECT_CALL(font, getCollection()).WillOnce(Return(&collection));



    const char* result = getFontLang(static_cast<const GfxFont&>(font));

    EXPECT_STREQ(result, "ja");

}



TEST_F(WriteBatchTest_1900, NormalOperation_AdobeKorea1_1900) {

    MockGfxCIDFont font("tag", Ref(), "name", GfxFontType::unknown, Ref(), nullptr);

    MockGooString collection;

    EXPECT_CALL(collection, toStr()).WillOnce(Return("Adobe-Korea1"));

    EXPECT_CALL(font, getCollection()).WillOnce(Return(&collection));



    const char* result = getFontLang(static_cast<const GfxFont&>(font));

    EXPECT_STREQ(result, "ko");

}



TEST_F(WriteBatchTest_1900, NormalOperation_AdobeUCS_1900) {

    MockGfxCIDFont font("tag", Ref(), "name", GfxFontType::unknown, Ref(), nullptr);

    MockGooString collection;

    EXPECT_CALL(collection, toStr()).WillOnce(Return("Adobe-UCS"));

    EXPECT_CALL(font, getCollection()).WillOnce(Return(&collection));



    const char* result = getFontLang(static_cast<const GfxFont&>(font));

    EXPECT_STREQ(result, "xx");

}



TEST_F(WriteBatchTest_1900, NormalOperation_AdobeIdentity_1900) {

    MockGfxCIDFont font("tag", Ref(), "name", GfxFontType::unknown, Ref(), nullptr);

    MockGooString collection;

    EXPECT_CALL(collection, toStr()).WillOnce(Return("Adobe-Identity"));

    EXPECT_CALL(font, getCollection()).WillOnce(Return(&collection));



    const char* result = getFontLang(static_cast<const GfxFont&>(font));

    EXPECT_STREQ(result, "xx");

}



TEST_F(WriteBatchTest_1900, BoundaryCondition_EmptyCollection_1900) {

    MockGfxCIDFont font("tag", Ref(), "name", GfxFontType::unknown, Ref(), nullptr);

    EXPECT_CALL(font, getCollection()).WillOnce(Return(nullptr));



    const char* result = getFontLang(static_cast<const GfxFont&>(font));

    EXPECT_STREQ(result, "xx");

}



TEST_F(WriteBatchTest_1900, BoundaryCondition_UnknownCollection_1900) {

    MockGfxCIDFont font("tag", Ref(), "name", GfxFontType::unknown, Ref(), nullptr);

    MockGooString collection;

    EXPECT_CALL(collection, toStr()).WillOnce(Return("Unknown-Collection"));

    EXPECT_CALL(font, getCollection()).WillOnce(Return(&collection));



    const char* result = getFontLang(static_cast<const GfxFont&>(font));

    EXPECT_STREQ(result, "xx");

}



TEST_F(WriteBatchTest_1900, ExceptionalCase_ErrorReporting_1900) {

    MockGfxCIDFont font("tag", Ref(), "name", GfxFontType::unknown, Ref(), nullptr);

    MockGooString collection;

    EXPECT_CALL(collection, toStr()).WillOnce(Return("Unknown-Collection"));

    EXPECT_CALL(font, getCollection()).WillOnce(Return(&collection));



    testing::internal::CaptureStderr();

    const char* result = getFontLang(static_cast<const GfxFont&>(font));

    std::string output = testing::internal::GetCapturedStderr();



    EXPECT_STREQ(result, "xx");

    EXPECT_THAT(output, testing::HasSubstr("Unknown CID font collection: Unknown-Collection"));

}
