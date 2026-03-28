#include <gtest/gtest.h>

#include "poppler/PSOutputDev.h"

#include <memory>



class PSOutputDevTest : public ::testing::Test {

protected:

    std::unique_ptr<PSOutputDev> ps_output_dev;



    void SetUp() override {

        // Assuming a mock PDFDoc and other necessary parameters are available

        // Here we use nullptr for simplicity, but in actual scenario these should be valid objects/parameters.

        ps_output_dev = std::make_unique<PSOutputDev>("dummy.ps", nullptr, nullptr, 1, PSOutMode::singlePage,

                                                     595, 842, false, false, 0, 0, 595, 842,

                                                     PSForceRasterize::none, false, nullptr, nullptr, PSLevel::level3);

    }

};



TEST_F(PSOutputDevTest_1298, InterpretType3Chars_ReturnsFalse_1298) {

    EXPECT_FALSE(ps_output_dev->interpretType3Chars());

}



TEST_F(PSOutputDevTest_1298, IsOk_NormalOperation_1298) {

    EXPECT_TRUE(ps_output_dev->isOk());

}



TEST_F(PSOutputDevTest_1298, SetAndCheckOffset_1298) {

    double x = 10.5, y = 20.3;

    ps_output_dev->setOffset(x, y);

    // Assuming there is a way to verify the offset was set correctly

    // For this test, we assume it's internal state and thus can't be directly verified.

}



TEST_F(PSOutputDevTest_1298, SetAndCheckScale_1298) {

    double x = 0.5, y = 0.5;

    ps_output_dev->setScale(x, y);

    // Assuming there is a way to verify the scale was set correctly

    // For this test, we assume it's internal state and thus can't be directly verified.

}



TEST_F(PSOutputDevTest_1298, SetAndCheckRotate_1298) {

    int rotateA = 90;

    ps_output_dev->setRotate(rotateA);

    // Assuming there is a way to verify the rotation was set correctly

    // For this test, we assume it's internal state and thus can't be directly verified.

}



TEST_F(PSOutputDevTest_1298, SetAndCheckClip_1298) {

    double llx = 0, lly = 0, urx = 595, ury = 842;

    ps_output_dev->setClip(llx, lly, urx, ury);

    // Assuming there is a way to verify the clip was set correctly

    // For this test, we assume it's internal state and thus can't be directly verified.

}



TEST_F(PSOutputDevTest_1298, SetAndCheckUnderlayCbk_1298) {

    void (*cbk)(PSOutputDev*, void*) = [](PSOutputDev*, void*){};

    void *data = nullptr;

    ps_output_dev->setUnderlayCbk(cbk, data);

    // Assuming there is a way to verify the callback was set correctly

    // For this test, we assume it's internal state and thus can't be directly verified.

}



TEST_F(PSOutputDevTest_1298, SetAndCheckOverlayCbk_1298) {

    void (*cbk)(PSOutputDev*, void*) = [](PSOutputDev*, void*){};

    void *data = nullptr;

    ps_output_dev->setOverlayCbk(cbk, data);

    // Assuming there is a way to verify the callback was set correctly

    // For this test, we assume it's internal state and thus can't be directly verified.

}



TEST_F(PSOutputDevTest_1298, SetAndCheckDisplayText_1298) {

    bool display = true;

    ps_output_dev->setDisplayText(display);

    EXPECT_TRUE(ps_output_dev->useDrawChar());

}



TEST_F(PSOutputDevTest_1298, SetAndCheckPSCenter_1298) {

    bool center = true;

    ps_output_dev->setPSCenter(center);

    // Assuming there is a way to verify the center was set correctly

    // For this test, we assume it's internal state and thus can't be directly verified.

}



TEST_F(PSOutputDevTest_1298, SetAndCheckPSExpandSmaller_1298) {

    bool expand = true;

    ps_output_dev->setPSExpandSmaller(expand);

    // Assuming there is a way to verify the expand smaller was set correctly

    // For this test, we assume it's internal state and thus can't be directly verified.

}



TEST_F(PSOutputDevTest_1298, SetAndCheckPSShrinkLarger_1298) {

    bool shrink = false;

    ps_output_dev->setPSShrinkLarger(shrink);

    // Assuming there is a way to verify the shrink larger was set correctly

    // For this test, we assume it's internal state and thus can't be directly verified.

}



TEST_F(PSOutputDevTest_1298, SetAndCheckOverprintPreview_1298) {

    bool overprintPreviewA = true;

    ps_output_dev->setOverprintPreview(overprintPreviewA);

    // Assuming there is a way to verify the overprint preview was set correctly

    // For this test, we assume it's internal state and thus can't be directly verified.

}



TEST_F(PSOutputDevTest_1298, SetAndCheckRasterAntialias_1298) {

    bool antialias = true;

    ps_output_dev->setRasterAntialias(antialias);

    // Assuming there is a way to verify the raster antialias was set correctly

    // For this test, we assume it's internal state and thus can't be directly verified.

}



TEST_F(PSOutputDevTest_1298, SetAndCheckForceRasterize_1298) {

    PSForceRasterize forceRasterizeA = PSForceRasterize::all;

    ps_output_dev->setForceRasterize(forceRasterizeA);

    // Assuming there is a way to verify the force rasterize was set correctly

    // For this test, we assume it's internal state and thus can't be directly verified.

}



TEST_F(PSOutputDevTest_1298, SetAndCheckRasterResolution_1298) {

    double resolution = 300.0;

    ps_output_dev->setRasterResolution(resolution);

    // Assuming there is a way to verify the raster resolution was set correctly

    // For this test, we assume it's internal state and thus can't be directly verified.

}



TEST_F(PSOutputDevTest_1298, SetAndCheckRasterMono_1298) {

    ps_output_dev->setRasterMono();

    // Assuming there is a way to verify the raster mono was set correctly

    // For this test, we assume it's internal state and thus can't be directly verified.

}



TEST_F(PSOutputDevTest_1298, SetAndCheckUncompressPreloadedImages_1298) {

    bool b = true;

    ps_output_dev->setUncompressPreloadedImages(b);

    // Assuming there is a way to verify the uncompress preloaded images was set correctly

    // For this test, we assume it's internal state and thus can't be directly verified.

}



TEST_F(PSOutputDevTest_1298, SetAndCheckEmbedType1_1298) {

    bool b = true;

    ps_output_dev->setEmbedType1(b);

    EXPECT_TRUE(ps_output_dev->getEmbedType1());

}



TEST_F(PSOutputDevTest_1298, SetAndCheckEmbedTrueType_1298) {

    bool b = true;

    ps_output_dev->setEmbedTrueType(b);

    EXPECT_TRUE(ps_output_dev->getEmbedTrueType());

}



TEST_F(PSOutputDevTest_1298, SetAndCheckEmbedCIDPostScript_1298) {

    bool b = true;

    ps_output_dev->setEmbedCIDPostScript(b);

    EXPECT_TRUE(ps_output_dev->getEmbedCIDPostScript());

}



TEST_F(PSOutputDevTest_1298, SetAndCheckEmbedCIDTrueType_1298) {

    bool b = true;

    ps_output_dev->setEmbedCIDTrueType(b);

    EXPECT_TRUE(ps_output_dev->getEmbedCIDTrueType());

}



TEST_F(PSOutputDevTest_1298, SetAndCheckFontPassthrough_1298) {

    bool b = true;

    ps_output_dev->setFontPassthrough(b);

    EXPECT_TRUE(ps_output_dev->getFontPassthrough());

}



TEST_F(PSOutputDevTest_1298, SetAndCheckOptimizeColorSpace_1298) {

    bool b = true;

    ps_output_dev->setOptimizeColorSpace(b);

    EXPECT_TRUE(ps_output_dev->getOptimizeColorSpace());

}



TEST_F(PSOutputDevTest_1298, SetAndCheckPassLevel1CustomColor_1298) {

    bool b = true;

    ps_output_dev->setPassLevel1CustomColor(b);

    EXPECT_TRUE(ps_output_dev->getPassLevel1CustomColor());

}



TEST_F(PSOutputDevTest_1298, SetAndCheckPreloadImagesForms_1298) {

    bool b = true;

    ps_output_dev->setPreloadImagesForms(b);

    // Assuming there is a way to verify the preload images forms was set correctly

    // For this test, we assume it's internal state and thus can't be directly verified.

}



TEST_F(PSOutputDevTest_1298, SetAndCheckGenerateOPI_1298) {

    bool b = true;

    ps_output_dev->setGenerateOPI(b);

    // Assuming there is a way to verify the generate OPI was set correctly

    // For this test, we assume it's internal state and thus can't be directly verified.

}



TEST_F(PSOutputDevTest_1298, SetAndCheckUseASCIIHex_1298) {

    bool b = true;

    ps_output_dev->setUseASCIIHex(b);

    // Assuming there is a way to verify the use ASCII hex was set correctly

    // For this test, we assume it's internal state and thus can't be directly verified.

}



TEST_F(PSOutputDevTest_1298, SetAndCheckUseBinary_1298) {

    bool b = true;

    ps_output_dev->setUseBinary(b);

    // Assuming there is a way to verify the use binary was set correctly

    // For this test, we assume it's internal state and thus can't be directly verified.

}



TEST_F(PSOutputDevTest_1298, SetAndCheckEnableLZW_1298) {

    bool b = true;

    ps_output_dev->setEnableLZW(b);

    EXPECT_TRUE(ps_output_dev->getEnableLZW());

}



TEST_F(PSOutputDevTest_1298, SetAndCheckEnableFlate_1298) {

    bool b = true;

    ps_output_dev->setEnableFlate(b);

    EXPECT_TRUE(ps_output_dev->getEnableFlate());

}
