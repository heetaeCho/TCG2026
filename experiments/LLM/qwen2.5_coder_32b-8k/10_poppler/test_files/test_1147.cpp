#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler/GfxFont.h"

#include "poppler/Object.h"



using namespace testing;



// Mock class for XRef and Dict if needed in future tests

class MockXRef : public XRef {

public:

    MOCK_METHOD(void, someMethod, (), (const));

};



class MockDict : public Dict {

public:

    MOCK_METHOD(void, someMethod, (), (const));

};



class GfxFontTest_1147 : public ::testing::Test {

protected:

    Ref validEmbFontID;

    Ref invalidEmbFontID;



    void SetUp() override {

        validEmbFontID = {123, 456};

        invalidEmbFontID = Ref::INVALID();

    }

};



TEST_F(GfxFontTest_1147, GetEmbeddedFontID_Valid_1147) {

    GfxFont font("tag", validEmbFontID, "name", gfxFontType1, validEmbFontID);

    Ref embID;

    EXPECT_TRUE(font.getEmbeddedFontID(&embID));

    EXPECT_EQ(embID.num, 123);

    EXPECT_EQ(embID.gen, 456);

}



TEST_F(GfxFontTest_1147, GetEmbeddedFontID_Invalid_1147) {

    GfxFont font("tag", invalidEmbFontID, "name", gfxFontType1, invalidEmbFontID);

    Ref embID;

    EXPECT_FALSE(font.getEmbeddedFontID(&embID));

}



TEST_F(GfxFontTest_1147, GetEmbeddedFontID_NullPtr_1147) {

    GfxFont font("tag", validEmbFontID, "name", gfxFontType1, validEmbFontID);

    EXPECT_DEATH(font.getEmbeddedFontID(nullptr), "");

}
