#include <gtest/gtest.h>

#include "poppler/PSOutputDev.h"



class PSOutputDevTest_1326 : public ::testing::Test {

protected:

    PSOutputDev* ps_output_dev;



    void SetUp() override {

        // Assuming a simple constructor for demonstration purposes.

        // The actual constructor might require more parameters.

        ps_output_dev = new PSOutputDev(nullptr, nullptr, nullptr, std::vector<int>(), psOutModeBinary, 612, 792, false, false, 0, 0, 612, 792, forceRasterizeNone, false, nullptr, nullptr, psLevel2);

    }



    void TearDown() override {

        delete ps_output_dev;

    }

};



TEST_F(PSOutputDevTest_1326, SetEmbedTrueType_DefaultValue_1326) {

    EXPECT_FALSE(ps_output_dev->getEmbedTrueType());

}



TEST_F(PSOutputDevTest_1326, SetEmbedTrueType_ToTrue_1326) {

    ps_output_dev->setEmbedTrueType(true);

    EXPECT_TRUE(ps_output_dev->getEmbedTrueType());

}



TEST_F(PSOutputDevTest_1326, SetEmbedTrueType_ToFalse_1326) {

    ps_output_dev->setEmbedTrueType(false);

    EXPECT_FALSE(ps_output_dev->getEmbedTrueType());

}
