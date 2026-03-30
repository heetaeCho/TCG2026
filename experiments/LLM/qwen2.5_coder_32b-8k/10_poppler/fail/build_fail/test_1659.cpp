#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/PreScanOutputDev.h"



class PreScanOutputDevTest_1659 : public ::testing::Test {

protected:

    PreScanOutputDev* output_dev;



    void SetUp() override {

        output_dev = new PreScanOutputDev(PSLevel::psDefault);

    }



    void TearDown() override {

        delete output_dev;

    }

};



TEST_F(PreScanOutputDevTest_1659, InterpretType3Chars_ReturnsTrue_1659) {

    EXPECT_TRUE(output_dev->interpretType3Chars());

}



TEST_F(PreScanOutputDevTest_1659, IsMonochrome_DefaultValue_1659) {

    // Assuming the default value is not explicitly set in constructor

    EXPECT_FALSE(output_dev->isMonochrome());

}



TEST_F(PreScanOutputDevTest_1659, IsGray_DefaultValue_1659) {

    // Assuming the default value is not explicitly set in constructor

    EXPECT_FALSE(output_dev->isGray());

}



TEST_F(PreScanOutputDevTest_1659, UsesTransparency_DefaultValue_1659) {

    // Assuming the default value is not explicitly set in constructor

    EXPECT_FALSE(output_dev->usesTransparency());

}



TEST_F(PreScanOutputDevTest_1659, IsAllGDI_DefaultValue_1659) {

    // Assuming the default value is not explicitly set in constructor

    EXPECT_FALSE(output_dev->isAllGDI());

}



TEST_F(PreScanOutputDevTest_1659, UsesPatternImageMask_DefaultValue_1659) {

    // Assuming the default value is not explicitly set in constructor

    EXPECT_FALSE(output_dev->usesPatternImageMask());

}
