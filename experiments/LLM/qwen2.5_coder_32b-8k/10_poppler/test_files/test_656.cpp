#include <gtest/gtest.h>

#include "GfxState.h"

#include <memory>



class GfxColorSpaceMock : public GfxColorSpace {

public:

    MOCK_METHOD(void, use, (), (override));

};



using ::testing::NiceMock;



class GfxStateTest : public ::testing::Test {

protected:

    double hDPI = 300.0;

    double vDPI = 300.0;

    PDFRectangle pageBox = {0, 0, 612, 792};

    int rotate = 0;



    GfxState* state;



    void SetUp() override {

        state = new GfxState(hDPI, vDPI, &pageBox, rotate, false);

    }



    void TearDown() override {

        delete state;

    }

};



TEST_F(GfxStateTest_656, SetDefaultRGBColorSpace_SuccessfulSet_656) {

    auto colorSpace = std::make_unique<NiceMock<GfxColorSpaceMock>>();

    EXPECT_CALL(*colorSpace, use()).Times(1);



    state->setDefaultRGBColorSpace(std::move(colorSpace));

}



TEST_F(GfxStateTest_656, SetDefaultRGBColorSpace_NullPtrHandling_656) {

    state->setDefaultRGBColorSpace(nullptr);

    // No crash expected

}
