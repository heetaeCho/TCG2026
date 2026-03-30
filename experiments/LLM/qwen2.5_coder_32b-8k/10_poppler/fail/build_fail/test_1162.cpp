#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/poppler/GfxFont.h"



using namespace ::testing;



class GfxFontTest_1162 : public Test {

protected:

    GfxFont* font = nullptr;

    std::string tag = "testTag";

    Ref id = {42, 0};

    std::optional<std::string> name = "testName";

    GfxFontType type = gfxFontType1;



    void SetUp() override {

        font = new GfxFont(tag.c_str(), id, std::move(name), type, id);

    }



    void TearDown() override {

        delete font;

    }

};



TEST_F(GfxFontTest_1162, GetTag_ReturnsCorrectTag_1162) {

    EXPECT_EQ(font->getTag(), tag);

}



TEST_F(GfxFontTest_1162, GetID_ReturnsCorrectID_1162) {

    EXPECT_EQ(*font->getID(), id);

}



TEST_F(GfxFontTest_1162, GetName_ReturnsCorrectName_1162) {

    EXPECT_EQ(font->getName(), name);

}



TEST_F(GfxFontTest_1162, GetType_ReturnsCorrectType_1162) {

    EXPECT_EQ(font->getType(), type);

}



TEST_F(GfxFontTest_1162, IsCIDFont_Default_ReturnsFalse_1162) {

    EXPECT_FALSE(font->isCIDFont());

}



TEST_F(GfxFontTest_1162, GetEncodingName_ReturnsDefaultEmptyString_1162) {

    EXPECT_TRUE(font->getEncodingName().empty());

}
