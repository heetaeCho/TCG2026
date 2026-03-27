#include <gtest/gtest.h>

#include "poppler/TextOutputDev.h"



class TextOutputDevTest_1227 : public ::testing::Test {

protected:

    TextOutputDev* text_output_dev;



    void SetUp() override {

        text_output_dev = new TextOutputDev(nullptr, nullptr, false, 0.0, false, false);

    }



    void TearDown() override {

        delete text_output_dev;

    }

};



TEST_F(TextOutputDevTest_1227, SetMinColSpacing1_NormalOperation_1227) {

    double new_spacing = 2.5;

    text_output_dev->setMinColSpacing1(new_spacing);

    EXPECT_DOUBLE_EQ(text_output_dev->getMinColSpacing1(), new_spacing);

}



TEST_F(TextOutputDevTest_1227, SetMinColSpacing1_BoundaryConditionZero_1227) {

    double zero_spacing = 0.0;

    text_output_dev->setMinColSpacing1(zero_spacing);

    EXPECT_DOUBLE_EQ(text_output_dev->getMinColSpacing1(), zero_spacing);

}



TEST_F(TextOutputDevTest_1227, SetMinColSpacing1_BoundaryConditionNegative_1227) {

    double negative_spacing = -1.0;

    text_output_dev->setMinColSpacing1(negative_spacing);

    EXPECT_DOUBLE_EQ(text_output_dev->getMinColSpacing1(), negative_spacing);

}



TEST_F(TextOutputDevTest_1227, SetMinColSpacing1_BoundaryConditionLargeValue_1227) {

    double large_spacing = 999999.99;

    text_output_dev->setMinColSpacing1(large_spacing);

    EXPECT_DOUBLE_EQ(text_output_dev->getMinColSpacing1(), large_spacing);

}
