#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "GfxState.h"



using namespace testing;



class GfxStateTest : public ::testing::Test {

protected:

    GfxStateTest()

        : pageBox(new PDFRectangle(0, 0, 100, 200)),

          gfxState(300.0, 400.0, pageBox.get(), 0, false) {}



    std::unique_ptr<PDFRectangle> pageBox;

    GfxState gfxState;

};



TEST_F(GfxStateTest_588, GetStrokePattern_ReturnsNullptrByDefault_588) {

    EXPECT_EQ(gfxState.getStrokePattern(), nullptr);

}



TEST_F(GfxStateTest_588, SetAndGetStrokePattern_NormalOperation_588) {

    auto pattern = std::make_unique<GfxPattern>();

    GfxPattern* rawPattern = pattern.get();

    gfxState.setStrokePattern(std::move(pattern));

    EXPECT_EQ(gfxState.getStrokePattern(), rawPattern);

}



TEST_F(GfxStateTest_588, SetAndGetStrokePattern_MultipleTimes_588) {

    auto pattern1 = std::make_unique<GfxPattern>();

    GfxPattern* rawPattern1 = pattern1.get();

    gfxState.setStrokePattern(std::move(pattern1));

    EXPECT_EQ(gfxState.getStrokePattern(), rawPattern1);



    auto pattern2 = std::make_unique<GfxPattern>();

    GfxPattern* rawPattern2 = pattern2.get();

    gfxState.setStrokePattern(std::move(pattern2));

    EXPECT_EQ(gfxState.getStrokePattern(), rawPattern2);

}



TEST_F(GfxStateTest_588, SetAndGetStrokePattern_Nullptr_588) {

    auto pattern = std::make_unique<GfxPattern>();

    gfxState.setStrokePattern(std::move(pattern));

    gfxState.setStrokePattern(nullptr);

    EXPECT_EQ(gfxState.getStrokePattern(), nullptr);

}
