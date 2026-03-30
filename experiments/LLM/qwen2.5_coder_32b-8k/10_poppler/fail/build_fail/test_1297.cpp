#include <gtest/gtest.h>

#include "PSOutputDev.h"

#include <memory>



class PSOutputDevTest : public ::testing::Test {

protected:

    std::unique_ptr<PSOutputDev> ps_output_dev;



    void SetUp() override {

        // Initialize PSOutputDev with minimal parameters

        pdfDoc = new PDFDoc();

        ps_output_dev = std::make_unique<PSOutputDev>("dummy.ps", pdfDoc, nullptr, 0, static_cast<PSOutMode>(1), 612, 792, false, false, 0, 0, 612, 792, PSForceRasterize::none, false, nullptr, nullptr, static_cast<PSLevel>(3));

    }



    void TearDown() override {

        // Clean up resources

        delete pdfDoc;

    }



private:

    PDFDoc* pdfDoc;

};



TEST_F(PSOutputDevTest_1297, UseDrawForm_ReturnsFalseByDefault_1297) {

    EXPECT_FALSE(ps_output_dev->useDrawForm());

}



TEST_F(PSOutputDevTest_1297, SetPreloadImagesForms_AffectsUseDrawForm_1297) {

    ps_output_dev->setPreloadImagesForms(true);

    EXPECT_TRUE(ps_output_dev->useDrawForm());



    ps_output_dev->setPreloadImagesForms(false);

    EXPECT_FALSE(ps_output_dev->useDrawForm());

}
