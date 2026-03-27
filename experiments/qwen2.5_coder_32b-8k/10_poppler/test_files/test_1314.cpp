#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/PSOutputDev.h"

#include "TestProjects/poppler/splash/SplashTypes.h"



class PSOutputDevTest : public ::testing::Test {

protected:

    PDFDoc* doc;

    char psTitle[256] = "test_title";

    int paperWidth = 800;

    int paperHeight = 600;

    bool noCrop = false;

    bool duplex = false;

    int imgLLX = 0;

    int imgLLY = 0;

    int imgURX = 800;

    int imgURY = 600;

    PSForceRasterize forceRasterize = psForceRasterizeNone;

    bool manualCtrl = false;



    void (*customCodeCbk)(PSOutputDev*, PSOutCustomCodeLocation, int, void*) = nullptr;

    void* customCodeCbkData = nullptr;

    PSLevel level = psLevel2;



    PSOutputDevTest() : doc(nullptr) {

        // Initialize the document if necessary

    }



    virtual ~PSOutputDevTest() {

        // Clean up if necessary

    }



    virtual void SetUp() override {

        // Create an instance of PSOutputDev before each test

        outputDev = new PSOutputDev("test.ps", doc, psTitle, 1, psModeMono, paperWidth, paperHeight, noCrop, duplex,

                                    imgLLX, imgLLY, imgURX, imgURY, forceRasterize, manualCtrl, customCodeCbk, customCodeCbkData, level);

    }



    virtual void TearDown() override {

        // Clean up after each test

        delete outputDev;

    }



protected:

    PSOutputDev* outputDev;

};



TEST_F(PSOutputDevTest_1314, SetRasterMono_SetsCorrectColorFormat_1314) {

    // Act

    outputDev->setRasterMono();



    // Assert

    EXPECT_EQ(outputDev->processColorFormat, splashModeMono8);

}



TEST_F(PSOutputDevTest_1314, SetRasterMono_SetsProcessColorFormatSpecifiedTrue_1314) {

    // Act

    outputDev->setRasterMono();



    // Assert

    EXPECT_TRUE(outputDev->processColorFormatSpecified);

}
