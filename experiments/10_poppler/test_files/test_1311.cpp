#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/PSOutputDev.h"



class PSOutputDevTest : public ::testing::Test {

protected:

    std::unique_ptr<PSOutputDev> psOutputDev;



    void SetUp() override {

        // Initialize the PSOutputDev with dummy parameters

        psOutputDev = std::make_unique<PSOutputDev>(

            "dummy_file.ps", nullptr, strdup("DummyTitle"), 1,

            (PSOutMode)0, 595, 842, false, false, 0, 0, 595, 842,

            (PSForceRasterize)0, false, nullptr, nullptr, (PSLevel)0);

    }



    void TearDown() override {

        free(psOutputDev->psTitle); // Clean up the allocated memory for psTitle

    }

};



TEST_F(PSOutputDevTest_1311, SetRasterAntialias_DefaultValue_1311) {

    EXPECT_EQ(psOutputDev->rasterAntialias, false);

}



TEST_F(PSOutputDevTest_1311, SetRasterAntialias_Enable_1311) {

    psOutputDev->setRasterAntialias(true);

    EXPECT_EQ(psOutputDev->rasterAntialias, true);

}



TEST_F(PSOutputDevTest_1311, SetRasterAntialias_Disable_1311) {

    psOutputDev->setRasterAntialias(false);

    EXPECT_EQ(psOutputDev->rasterAntialias, false);

}
