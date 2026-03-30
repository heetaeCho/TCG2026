#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "GfxFont.h"



using ::testing::_;

using ::testing::Return;

using ::testing::MockFunction;



class GfxFontTest_1144 : public ::testing::Test {

protected:

    class MockXRef : public XRef {

    public:

        MOCK_METHOD(void, dummy, (), (const));

    };



    class MockDict : public Dict {

    public:

        MOCK_METHOD(void, dummy, (), (const));

    };



    class MockPSOutputDev : public PSOutputDev {

    public:

        MOCK_METHOD(void, dummy, (), (const));

    };



    class MockGooString : public GooString {

    public:

        MOCK_METHOD(void, dummy, (), (const));

    };



    std::unique_ptr<MockXRef> mock_xref = std::make_unique<MockXRef>();

    std::unique_ptr<MockDict> mock_font_dict = std::make_unique<MockDict>();

    Ref id{42, 0};

    GfxFontType type{gfxFontUnknown};



    std::optional<std::string> name;

    GfxFont* font;



    void SetUp() override {

        name = "TestFont";

        font = GfxFont::makeFont(mock_xref.get(), "tag", id, mock_font_dict.get(), type).release();

    }



    void TearDown() override {

        delete font;

    }

};



TEST_F(GfxFontTest_1144, GetName_ReturnsProvidedName_1144) {

    EXPECT_EQ(font->getName(), name);

}



TEST_F(GfxFontTest_1144, IsSubset_DefaultValue_1144) {

    EXPECT_FALSE(font->isSubset());

}



TEST_F(GfxFontTest_1144, GetTag_ReturnsProvidedTag_1144) {

    EXPECT_EQ(font->getTag(), "tag");

}



TEST_F(GfxFontTest_1144, GetID_ReturnsProvidedID_1144) {

    EXPECT_EQ(*font->getID(), id);

}



TEST_F(GfxFontTest_1144, Matches_SameTag_ReturnsTrue_1144) {

    EXPECT_TRUE(font->matches("tag"));

}



TEST_F(GfxFontTest_1144, Matches_DifferentTag_ReturnsFalse_1144) {

    EXPECT_FALSE(font->matches("different_tag"));

}



TEST_F(GfxFontTest_1144, IsCIDFont_DefaultValue_1144) {

    EXPECT_FALSE(font->isCIDFont());

}



TEST_F(GfxFontTest_1144, GetEmbeddedFontID_DefaultValue_ReturnsFalse_1144) {

    Ref embID;

    EXPECT_FALSE(font->getEmbeddedFontID(&embID));

}



TEST_F(GfxFontTest_1144, InvalidateEmbeddedFont_DefaultValue_ReturnsFalse_1144) {

    EXPECT_FALSE(font->invalidateEmbeddedFont());

}



TEST_F(GfxFontTest_1144, GetEmbeddedFontName_DefaultValue_ReturnsNullptr_1144) {

    EXPECT_EQ(font->getEmbeddedFontName(), nullptr);

}



TEST_F(GfxFontTest_1144, IsOk_DefaultValue_ReturnsTrue_1144) {

    EXPECT_TRUE(font->isOk());

}
