#include <gtest/gtest.h>

#include "TestProjects/poppler/utils/pdftohtml.cc"



class SplashOutputDevNoTextTest : public ::testing::Test {

protected:

    SplashOutputDevNoText* splash_output_dev_no_text;



    void SetUp() override {

        splash_output_dev_no_text = new SplashOutputDevNoText();

    }



    void TearDown() override {

        delete splash_output_dev_no_text;

    }

};



TEST_F(SplashOutputDevNoTextTest, BeginType3CharReturnsFalse_2714) {

    GfxState state; // Mock or dummy object as we do not interact with it internally

    double x = 0.0, y = 0.0, dx = 0.0, dy = 0.0;

    CharCode code = 0;

    Unicode u[1] = { 'A' };

    int uLen = 1;



    bool result = splash_output_dev_no_text->beginType3Char(&state, x, y, dx, dy, code, u, uLen);

    EXPECT_FALSE(result);

}
