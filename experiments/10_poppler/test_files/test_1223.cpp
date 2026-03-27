#include <gtest/gtest.h>

#include "TextOutputDev.h"



class TextOutputDevTest : public ::testing::Test {

protected:

    TextOutputDev *text_output_dev;



    void SetUp() override {

        text_output_dev = new TextOutputDev(nullptr, nullptr, false, 0.0, false, false);

    }



    void TearDown() override {

        delete text_output_dev;

    }

};



TEST_F(TextOutputDevTest_1223, EnableHTMLExtras_DefaultValue_1223) {

    EXPECT_FALSE(text_output_dev->isOk());

}



TEST_F(TextOutputDevTest_1223, EnableHTMLExtras_EnableTrue_1223) {

    text_output_dev->enableHTMLExtras(true);

    EXPECT_TRUE(text_output_dev->isOk());

}



TEST_F(TextOutputDevTest_1223, EnableHTMLExtras_EnableFalse_1223) {

    text_output_dev->enableHTMLExtras(false);

    EXPECT_FALSE(text_output_dev->isOk());

}



TEST_F(TextOutputDevTest_1223, EnableHTMLExtras_ToggleMultipleTimes_1223) {

    text_output_dev->enableHTMLExtras(true);

    EXPECT_TRUE(text_output_dev->isOk());



    text_output_dev->enableHTMLExtras(false);

    EXPECT_FALSE(text_output_dev->isOk());



    text_output_dev->enableHTMLExtras(true);

    EXPECT_TRUE(text_output_dev->isOk());

}



TEST_F(TextOutputDevTest_1223, EnableHTMLExtras_BoundaryConditions_1223) {

    // Testing boundary conditions for boolean values

    text_output_dev->enableHTMLExtras(true);

    EXPECT_TRUE(text_output_dev->isOk());



    text_output_dev->enableHTMLExtras(false);

    EXPECT_FALSE(text_output_dev->isOk());

}



TEST_F(TextOutputDevTest_1223, EnableHTMLExtras_ExceptionalCases_1223) {

    // Since the method does not throw exceptions or have exceptional cases based on the interface,

    // this test case is a placeholder to ensure completeness.

    EXPECT_NO_THROW(text_output_dev->enableHTMLExtras(true));

    EXPECT_NO_THROW(text_output_dev->enableHTMLExtras(false));

}
