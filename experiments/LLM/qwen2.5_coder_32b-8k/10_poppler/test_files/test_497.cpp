#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "GfxState.h"

#include "Object.h"



using namespace testing;



class GfxTilingPatternTest : public ::testing::Test {

protected:

    std::unique_ptr<Object> resDictObj;

    std::unique_ptr<GfxTilingPattern> tilingPattern;



    void SetUp() override {

        resDictObj = std::make_unique<Object>(new Dict());

        tilingPattern = GfxTilingPattern::parse(resDictObj.get(), 1);

    }

};



TEST_F(GfxTilingPatternTest_497, GetResDict_ReturnsNullptr_WhenResDictIsNotADict_497) {

    resDictObj->setToNull();

    tilingPattern = GfxTilingPattern::parse(resDictObj.get(), 1);

    EXPECT_EQ(tilingPattern->getResDict(), nullptr);

}



TEST_F(GfxTilingPatternTest_497, GetResDict_ReturnsValidDictPointer_WhenResDictIsADict_497) {

    resDictObj->setToNull();

    resDictObj = std::make_unique<Object>(new Dict());

    tilingPattern = GfxTilingPattern::parse(resDictObj.get(), 1);

    EXPECT_NE(tilingPattern->getResDict(), nullptr);

}



TEST_F(GfxTilingPatternTest_497, GetResDict_ReturnsSameDictPointer_AsProvidedInConstructor_497) {

    tilingPattern = GfxTilingPattern::parse(resDictObj.get(), 1);

    EXPECT_EQ(tilingPattern->getResDict(), resDictObj->getDict());

}
