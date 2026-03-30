#include <gtest/gtest.h>

#include "PSOutputDev.h"



class PSOutputDevTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Create an instance of PSOutputDev with some default values.

        pdfDoc = new PDFDoc("dummy.pdf");

        psOutputDev = new PSOutputDev(

            "output.ps", 

            pdfDoc, 

            const_cast<char*>("testTitle"), 

            pages, 

            static_cast<PSOutMode>(0), 

            595, 

            842, 

            false, 

            false, 

            0, 

            0, 

            595, 

            842, 

            PSForceRasterize::none,

            false, 

            nullptr, 

            nullptr, 

            static_cast<PSLevel>(3)

        );

    }



    void TearDown() override {

        delete psOutputDev;

        delete pdfDoc;

    }



    PDFDoc* pdfDoc;

    PSOutputDev* psOutputDev;

    std::vector<int> pages = {1};

};



TEST_F(PSOutputDevTest_1323, EnableLZWInitiallyDisabled_1323) {

    EXPECT_FALSE(psOutputDev->getEnableLZW());

}



TEST_F(PSOutputDevTest_1323, SetEnableLZWToTrueAndGetItBack_1323) {

    psOutputDev->setEnableLZW(true);

    EXPECT_TRUE(psOutputDev->getEnableLZW());

}



TEST_F(PSOutputDevTest_1323, SetEnableLZWToFalseAndGetItBack_1323) {

    psOutputDev->setEnableLZW(false);

    EXPECT_FALSE(psOutputDev->getEnableLZW());

}
