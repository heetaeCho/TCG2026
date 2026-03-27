#include <gtest/gtest.h>

#include "GfxState.h"



class GfxStateTest_622 : public ::testing::Test {

protected:

    double hDPI = 300;

    double vDPI = 300;

    PDFRectangle pageBox = {0, 0, 595.2756, 841.8898};

    int rotate = 0;



    GfxState *gfxState;



    void SetUp() override {

        gfxState = new GfxState(hDPI, vDPI, &pageBox, rotate, false);

    }



    void TearDown() override {

        delete gfxState;

    }

};



TEST_F(GfxStateTest_622, GetLineY_DefaultValue_622) {

    EXPECT_DOUBLE_EQ(0.0, gfxState->getLineY());

}



// No setters are available for lineY in the public interface,

// so boundary conditions and exceptional cases related to lineY cannot be directly tested.

```


