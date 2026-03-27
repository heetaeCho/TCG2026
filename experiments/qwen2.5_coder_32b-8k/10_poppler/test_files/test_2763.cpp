#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-private.h"

#include "FontInfo.h"



using namespace Poppler;

using ::testing::NiceMock;



class MockFontInfo : public FontInfo {

public:

    MOCK_CONST_METHOD0(getName, const std::optional<std::string>&());

    MOCK_CONST_METHOD0(getSubstituteName, const std::optional<std::string>&());

    MOCK_CONST_METHOD0(getFile, const std::optional<std::string>&());

    MOCK_CONST_METHOD0(getEmbedded, bool());

    MOCK_CONST_METHOD0(getSubset, bool());

    MOCK_CONST_METHOD0(getType, FontInfo::Type());

    MOCK_CONST_METHOD0(getEmbRef, Ref());



    MockFontInfo() : FontInfo(nullptr, nullptr) {}

};



class FontInfoDataTest_2763 : public ::testing::Test {

protected:

    NiceMock<MockFontInfo> mockFontInfo;

    FontInfoData fontInfoData;



    void SetUp() override {

        fontInfoData = FontInfoData(&mockFontInfo);

    }

};



TEST_F(FontInfoDataTest_2763, FontNameIsSetCorrectly_2763) {

    const std::string expectedName = "Arial";

    EXPECT_CALL(mockFontInfo, getName()).WillOnce(::testing::Return(std::optional<std::string>(expectedName)));

    EXPECT_EQ(fontInfoData.fontName.toStdString(), expectedName);

}



TEST_F(FontInfoDataTest_2763, FontSubstituteNameIsSetCorrectly_2763) {

    const std::string expectedSubstituteName = "ArialMT";

    EXPECT_CALL(mockFontInfo, getSubstituteName()).WillOnce(::testing::Return(std::optional<std::string>(expectedSubstituteName)));

    EXPECT_EQ(fontInfoData.fontSubstituteName.toStdString(), expectedSubstituteName);

}



TEST_F(FontInfoDataTest_2763, FontFileIsSetCorrectly_2763) {

    const std::string expectedFile = "/path/to/font/file.ttf";

    EXPECT_CALL(mockFontInfo, getFile()).WillOnce(::testing::Return(std::optional<std::string>(expectedFile)));

    EXPECT_EQ(fontInfoData.fontFile.toStdString(), expectedFile);

}



TEST_F(FontInfoDataTest_2763, IsEmbeddedIsSetCorrectly_2763) {

    EXPECT_CALL(mockFontInfo, getEmbedded()).WillOnce(::testing::Return(true));

    EXPECT_TRUE(fontInfoData.isEmbedded);



    EXPECT_CALL(mockFontInfo, getEmbedded()).WillOnce(::testing::Return(false));

    fontInfoData = FontInfoData(&mockFontInfo);

    EXPECT_FALSE(fontInfoData.isEmbedded);

}



TEST_F(FontInfoDataTest_2763, IsSubsetIsSetCorrectly_2763) {

    EXPECT_CALL(mockFontInfo, getSubset()).WillOnce(::testing::Return(true));

    EXPECT_TRUE(fontInfoData.isSubset);



    EXPECT_CALL(mockFontInfo, getSubset()).WillOnce(::testing::Return(false));

    fontInfoData = FontInfoData(&mockFontInfo);

    EXPECT_FALSE(fontInfoData.isSubset);

}



TEST_F(FontInfoDataTest_2763, FontTypeIsSetCorrectly_2763) {

    const FontInfo::Type expectedType = FontInfo::TrueType;

    EXPECT_CALL(mockFontInfo, getType()).WillOnce(::testing::Return(expectedType));

    EXPECT_EQ(fontInfoData.type, expectedType);

}



TEST_F(FontInfoDataTest_2763, EmbRefIsSetCorrectly_2763) {

    Ref expectedEmbRef = {42, 0};

    EXPECT_CALL(mockFontInfo, getEmbRef()).WillOnce(::testing::Return(expectedEmbRef));

    EXPECT_EQ(fontInfoData.embRef.num, expectedEmbRef.num);

    EXPECT_EQ(fontInfoData.embRef.gen, expectedEmbRef.gen);

}



TEST_F(FontInfoDataTest_2763, FontNameIsNotSetWhenOptionalIsEmpty_2763) {

    EXPECT_CALL(mockFontInfo, getName()).WillOnce(::testing::Return(std::optional<std::string>()));

    EXPECT_TRUE(fontInfoData.fontName.isEmpty());

}



TEST_F(FontInfoDataTest_2763, FontSubstituteNameIsNotSetWhenOptionalIsEmpty_2763) {

    EXPECT_CALL(mockFontInfo, getSubstituteName()).WillOnce(::testing::Return(std::optional<std::string>()));

    EXPECT_TRUE(fontInfoData.fontSubstituteName.isEmpty());

}



TEST_F(FontInfoDataTest_2763, FontFileIsNotSetWhenOptionalIsEmpty_2763) {

    EXPECT_CALL(mockFontInfo, getFile()).WillOnce(::testing::Return(std::optional<std::string>()));

    EXPECT_TRUE(fontInfoData.fontFile.isEmpty());

}
