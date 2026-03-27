#include <gtest/gtest.h>

#include "PSOutputDev.h"

#include <memory>



// Mock dependencies if needed

class MockPDFDoc : public PDFDoc {

public:

    MockPDFDoc() = default;

};



TEST_F(PSOutputDevTest_1299, NeedClipToCropBoxReturnsTrueForEPSMode_1299) {

    PSOutMode mode = psModeEPS;

    std::unique_ptr<MockPDFDoc> doc(new MockPDFDoc());

    char* psTitle = const_cast<char*>("testTitle");

    int paperWidth = 500;

    int paperHeight = 600;

    bool noCrop = false;

    bool duplex = false;

    int imgLLX = 0;

    int imgLLY = 0;

    int imgURX = 100;

    int imgURY = 200;

    PSForceRasterize forceRasterize = psForceRasterizeNone;

    bool manualCtrl = false;

    PSOutCustomCodeCbk customCodeCbk = nullptr;

    void* customCodeCbkData = nullptr;

    PSLevel level = psLevel2;



    PSOutputDev outputDev("", doc.get(), psTitle, 1, mode, paperWidth, paperHeight, noCrop, duplex, imgLLX, imgLLY, imgURX, imgURY, forceRasterize, manualCtrl, customCodeCbk, customCodeCbkData, level);

    EXPECT_TRUE(outputDev.needClipToCropBox());

}



TEST_F(PSOutputDevTest_1299, NeedClipToCropBoxReturnsFalseForNonEPSMode_1299) {

    PSOutMode mode = psModePS;

    std::unique_ptr<MockPDFDoc> doc(new MockPDFDoc());

    char* psTitle = const_cast<char*>("testTitle");

    int paperWidth = 500;

    int paperHeight = 600;

    bool noCrop = false;

    bool duplex = false;

    int imgLLX = 0;

    int imgLLY = 0;

    int imgURX = 100;

    int imgURY = 200;

    PSForceRasterize forceRasterize = psForceRasterizeNone;

    bool manualCtrl = false;

    PSOutCustomCodeCbk customCodeCbk = nullptr;

    void* customCodeCbkData = nullptr;

    PSLevel level = psLevel2;



    PSOutputDev outputDev("", doc.get(), psTitle, 1, mode, paperWidth, paperHeight, noCrop, duplex, imgLLX, imgLLY, imgURX, imgURY, forceRasterize, manualCtrl, customCodeCbk, customCodeCbkData, level);

    EXPECT_FALSE(outputDev.needClipToCropBox());

}
