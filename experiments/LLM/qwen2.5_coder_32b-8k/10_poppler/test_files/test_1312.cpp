#include <gtest/gtest.h>

#include "PSOutputDev.h"



class PSOutputDevTest_1312 : public ::testing::Test {

protected:

    PDFDoc* doc;

    char psTitle[50] = "test_title";

    int paperWidth = 595;

    int paperHeight = 842;

    bool noCrop = false;

    bool duplex = false;

    int imgLLX = 0;

    int imgLLY = 0;

    int imgURX = 595;

    int imgURY = 842;

    PSForceRasterize forceRasterizeA = psfrNone;

    bool manualCtrlA = false;

    PSOutputDev* psOutputDev;



    void SetUp() override {

        doc = new PDFDoc(); // Assuming PDFDoc constructor exists and is mockable if needed

        psOutputDev = new PSOutputDev(

            "test_file.ps", 

            doc, 

            psTitle, 

            pages, 

            psomNone, 

            paperWidth, 

            paperHeight, 

            noCrop, 

            duplex, 

            imgLLX, 

            imgLLY, 

            imgURX, 

            imgURY, 

            forceRasterizeA, 

            manualCtrlA,

            nullptr, 

            nullptr, 

            psLevel2

        );

    }



    void TearDown() override {

        delete psOutputDev;

        delete doc;

    }



private:

    std::vector<int> pages = {1};

};



TEST_F(PSOutputDevTest_1312, SetForceRasterize_NormalOperation_1312) {

    PSForceRasterize newValue = psfrAlways;

    psOutputDev->setForceRasterize(newValue);

}



TEST_F(PSOutputDevTest_1312, SetForceRasterize_BoundaryConditions_1312) {

    // Test with boundary conditions

    PSForceRasterize minVal = psfrNone;

    psOutputDev->setForceRasterize(minVal);



    PSForceRasterize maxVal = psfrAlways;

    psOutputDev->setForceRasterize(maxVal);

}



TEST_F(PSOutputDevTest_1312, SetForceRasterize_ExceptionalCases_1312) {

    // Assuming no exceptional cases for enum values in setForceRasterize

    // If there are specific exceptional conditions, they should be tested here

}
