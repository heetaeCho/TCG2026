#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <string>

#include <unordered_map>



// Mock GfxFont for testing purposes

class MockGfxFont : public GfxFont {

public:

    MOCK_METHOD(bool, isCIDFont, (), (const override));

};



// Mock GfxCIDFont for testing purposes

class MockGfxCIDFont : public GfxCIDFont {

public:

    using GfxCIDFont::GfxCIDFont;

    MOCK_METHOD(const GooString*, getCollection, (), (const override));

};



TEST(findSubstituteNameTest_1985, NormalOperationWithNoSuffix_1985) {

    MockGfxFont mockFont;

    std::unordered_map<std::string, std::string> fontFiles = {{"Arial", "path/to/Arial"}};

    std::unordered_map<std::string, std::string> substFiles = {{"Helvetica", "path/to/Helvetica"}};



    EXPECT_CALL(mockFont, isCIDFont()).WillOnce(::testing::Return(false));



    const char* result = findSubstituteName(&mockFont, fontFiles, substFiles, "Helvetica");

    ASSERT_STREQ(result, "path/to/Helvetica");

}



TEST(findSubstituteNameTest_1985, NormalOperationWithIdentityHSuffix_1985) {

    MockGfxFont mockFont;

    std::unordered_map<std::string, std::string> fontFiles = {{"Arial", "path/to/Arial"}};

    std::unordered_map<std::string, std::string> substFiles = {{"Helvetica", "path/to/Helvetica"}};



    EXPECT_CALL(mockFont, isCIDFont()).WillOnce(::testing::Return(false));



    const char* result = findSubstituteName(&mockFont, fontFiles, substFiles, "Helvetica-Identity-H");

    ASSERT_STREQ(result, "path/to/Helvetica");

}



TEST(findSubstituteNameTest_1985, NormalOperationWithIdentityVSuffix_1985) {

    MockGfxFont mockFont;

    std::unordered_map<std::string, std::string> fontFiles = {{"Arial", "path/to/Arial"}};

    std::unordered_map<std::string, std::string> substFiles = {{"Helvetica", "path/to/Helvetica"}};



    EXPECT_CALL(mockFont, isCIDFont()).WillOnce(::testing::Return(false));



    const char* result = findSubstituteName(&mockFont, fontFiles, substFiles, "Helvetica-Identity-V");

    ASSERT_STREQ(result, "path/to/Helvetica");

}



TEST(findSubstituteNameTest_1985, CIDFontWithAdobeCNS1Collection_1985) {

    MockGfxCIDFont mockCIDFont(Ref(), Ref(), "MockCIDFont", GfxFontType::cidType0, Ref());

    std::unordered_map<std::string, std::string> fontFiles = {{"Adobe-CNS1-UCS2-H", "path/to/Adobe-CNS1-UCS2-H"}};

    std::unordered_map<std::string, std::string> substFiles;



    EXPECT_CALL(mockCIDFont, isCIDFont()).WillOnce(::testing::Return(true));

    EXPECT_CALL(mockCIDFont, getCollection()).WillOnce(::testing::Return(new GooString("Adobe-CNS1")));



    const char* result = findSubstituteName(&mockCIDFont, fontFiles, substFiles, "SomeFont");

    ASSERT_STREQ(result, DEFAULT_CID_FONT_AC1_MSWIN);

}



TEST(findSubstituteNameTest_1985, CIDFontWithAdobeGB1Collection_1985) {

    MockGfxCIDFont mockCIDFont(Ref(), Ref(), "MockCIDFont", GfxFontType::cidType0, Ref());

    std::unordered_map<std::string, std::string> fontFiles = {{"Adobe-GB1-UCS2-H", "path/to/Adobe-GB1-UCS2-H"}};

    std::unordered_map<std::string, std::string> substFiles;



    EXPECT_CALL(mockCIDFont, isCIDFont()).WillOnce(::testing::Return(true));

    EXPECT_CALL(mockCIDFont, getCollection()).WillOnce(::testing::Return(new GooString("Adobe-GB1")));



    const char* result = findSubstituteName(&mockCIDFont, fontFiles, substFiles, "SomeFont");

    ASSERT_STREQ(result, DEFAULT_CID_FONT_AG1_MSWIN);

}



TEST(findSubstituteNameTest_1985, CIDFontWithAdobeJapan1Collection_1985) {

    MockGfxCIDFont mockCIDFont(Ref(), Ref(), "MockCIDFont", GfxFontType::cidType0, Ref());

    std::unordered_map<std::string, std::string> fontFiles = {{"Adobe-Japan1-UCS2-H", "path/to/Adobe-Japan1-UCS2-H"}};

    std::unordered_map<std::string, std::string> substFiles;



    EXPECT_CALL(mockCIDFont, isCIDFont()).WillOnce(::testing::Return(true));

    EXPECT_CALL(mockCIDFont, getCollection()).WillOnce(::testing::Return(new GooString("Adobe-Japan1")));



    const char* result = findSubstituteName(&mockCIDFont, fontFiles, substFiles, "SomeFont");

    ASSERT_STREQ(result, DEFAULT_CID_FONT_AJ1_MSWIN);

}



TEST(findSubstituteNameTest_1985, CIDFontWithAdobeJapan2Collection_1985) {

    MockGfxCIDFont mockCIDFont(Ref(), Ref(), "MockCIDFont", GfxFontType::cidType0, Ref());

    std::unordered_map<std::string, std::string> fontFiles = {{"Adobe-Japan2-UCS2-H", "path/to/Adobe-Japan2-UCS2-H"}};

    std::unordered_map<std::string, std::string> substFiles;



    EXPECT_CALL(mockCIDFont, isCIDFont()).WillOnce(::testing::Return(true));

    EXPECT_CALL(mockCIDFont, getCollection()).WillOnce(::testing::Return(new GooString("Adobe-Japan2")));



    const char* result = findSubstituteName(&mockCIDFont, fontFiles, substFiles, "SomeFont");

    ASSERT_STREQ(result, DEFAULT_CID_FONT_AJ2_MSWIN);

}



TEST(findSubstituteNameTest_1985, CIDFontWithAdobeKorea1Collection_1985) {

    MockGfxCIDFont mockCIDFont(Ref(), Ref(), "MockCIDFont", GfxFontType::cidType0, Ref());

    std::unordered_map<std::string, std::string> fontFiles = {{"Adobe-Korea1-UCS2-H", "path/to/Adobe-Korea1-UCS2-H"}};

    std::unordered_map<std::string, std::string> substFiles;



    EXPECT_CALL(mockCIDFont, isCIDFont()).WillOnce(::testing::Return(true));

    EXPECT_CALL(mockCIDFont, getCollection()).WillOnce(::testing::Return(new GooString("Adobe-Korea1")));



    const char* result = findSubstituteName(&mockCIDFont, fontFiles, substFiles, "SomeFont");

    ASSERT_STREQ(result, DEFAULT_CID_FONT_AK1_MSWIN);

}



TEST(findSubstituteNameTest_1985, CIDFontWithUnknownCollection_1985) {

    MockGfxCIDFont mockCIDFont(Ref(), Ref(), "MockCIDFont", GfxFontType::cidType0, Ref());

    std::unordered_map<std::string, std::string> fontFiles = {{"Adobe-CNS1-UCS2-H", "path/to/Adobe-CNS1-UCS2-H"}};

    std::unordered_map<std::string, std::string> substFiles;



    EXPECT_CALL(mockCIDFont, isCIDFont()).WillOnce(::testing::Return(true));

    EXPECT_CALL(mockCIDFont, getCollection()).WillOnce(::testing::Return(new GooString("UnknownCollection")));



    const char* result = findSubstituteName(&mockCIDFont, fontFiles, substFiles, "SomeFont");

    ASSERT_STREQ(result, DEFAULT_CID_FONT_MSWIN);

}



TEST(findSubstituteNameTest_1985, CIDFontWithNoMatchingDefaultCIDFont_1985) {

    MockGfxCIDFont mockCIDFont(Ref(), Ref(), "MockCIDFont", GfxFontType::cidType0, Ref());

    std::unordered_map<std::string, std::string> fontFiles;

    std::unordered_map<std::string, std::string> substFiles;



    EXPECT_CALL(mockCIDFont, isCIDFont()).WillOnce(::testing::Return(true));

    EXPECT_CALL(mockCIDFont, getCollection()).WillOnce(::testing::Return(new GooString("Adobe-CNS1")));



    const char* result = findSubstituteName(&mockCIDFont, fontFiles, substFiles, "SomeFont");

    ASSERT_STREQ(result, DEFAULT_SUBSTITUTE_FONT);

}



TEST(findSubstituteNameTest_1985, NonCIDFontWithNoSubstitution_1985) {

    MockGfxFont mockFont;

    std::unordered_map<std::string, std::string> fontFiles;

    std::unordered_map<std::string, std::string> substFiles;



    EXPECT_CALL(mockFont, isCIDFont()).WillOnce(::testing::Return(false));



    const char* result = findSubstituteName(&mockFont, fontFiles, substFiles, "SomeFont");

    ASSERT_STREQ(result, DEFAULT_SUBSTITUTE_FONT);

}



TEST(findSubstituteNameTest_1985, NullOrigName_1985) {

    MockGfxFont mockFont;

    std::unordered_map<std::string, std::string> fontFiles = {{"Arial", "path/to/Arial"}};

    std::unordered_map<std::string, std::string> substFiles = {{"Helvetica", "path/to/Helvetica"}};



    EXPECT_CALL(mockFont, isCIDFont()).WillOnce(::testing::Return(false));



    const char* result = findSubstituteName(&mockFont, fontFiles, substFiles, nullptr);

    ASSERT_EQ(result, nullptr);

}



TEST(findSubstituteNameTest_1985, EmptyOrigName_1985) {

    MockGfxFont mockFont;

    std::unordered_map<std::string, std::string> fontFiles = {{"Arial", "path/to/Arial"}};

    std::unordered_map<std::string, std::string> substFiles = {{"Helvetica", "path/to/Helvetica"}};



    EXPECT_CALL(mockFont, isCIDFont()).WillOnce(::testing::Return(false));



    const char* result = findSubstituteName(&mockFont, fontFiles, substFiles, "");

    ASSERT_STREQ(result, DEFAULT_SUBSTITUTE_FONT);

}
