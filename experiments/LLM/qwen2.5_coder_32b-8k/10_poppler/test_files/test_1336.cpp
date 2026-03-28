#include <gtest/gtest.h>

#include "PSOutputDev.h"

#include <PDFDoc.h>



class PSOutputDevTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize a minimal PDFDoc object for construction purposes.

        // Note: In actual scenarios, this should be a valid PDF document.

        doc = new PDFDoc("dummy.pdf");

        psOutputDev = new PSOutputDev(nullptr, doc, "title", 1, (PSOutMode)0, 595, 842, false, false, 0, 0, 595, 842, (PSForceRasterize)0, false, nullptr, nullptr, (PSLevel)0);

    }



    void TearDown() override {

        delete psOutputDev;

        delete doc;

    }



    PSOutputDev* psOutputDev;

    PDFDoc* doc;

};



TEST_F(PSOutputDevTest_1336, SetEnableLZW_DefaultState_1336) {

    EXPECT_FALSE(psOutputDev->getEnableLZW());

}



TEST_F(PSOutputDevTest_1336, SetEnableLZW_Enable_1336) {

    psOutputDev->setEnableLZW(true);

    EXPECT_TRUE(psOutputDev->getEnableLZW());

}



TEST_F(PSOutputDevTest_1336, SetEnableLZW_Disable_1336) {

    psOutputDev->setEnableLZW(false);

    EXPECT_FALSE(psOutputDev->getEnableLZW());

}



TEST_F(PSOutputDevTest_1336, SetEnableLZW_ToggleTwice_1336) {

    psOutputDev->setEnableLZW(true);

    psOutputDev->setEnableLZW(false);

    EXPECT_FALSE(psOutputDev->getEnableLZW());

}
