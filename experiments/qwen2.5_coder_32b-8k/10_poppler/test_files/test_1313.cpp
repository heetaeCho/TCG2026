#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/PSOutputDev.h"



class PSOutputDevTest_1313 : public ::testing::Test {

protected:

    PDFDoc* mockDoc;

    char psTitle[256] = "TestDocument";



    void SetUp() override {

        // Assuming a mock PDFDoc is provided or can be constructed for testing

        mockDoc = new PDFDoc();

    }



    void TearDown() override {

        delete mockDoc;

    }

};



TEST_F(PSOutputDevTest_1313, SetRasterResolution_NormalOperation_1313) {

    PSOutputDev psOutput(mockDoc, psTitle, nullptr, PSOutMode::normal, 595, 842, false, false, 0, 0, 595, 842, PSForceRasterize::none, true, nullptr, nullptr, PSLevel::level1);

    psOutput.setRasterResolution(300.0);

    // Since the internal state cannot be directly accessed, we assume that setting the resolution does not throw any exceptions and the function executes normally.

}



TEST_F(PSOutputDevTest_1313, SetRasterResolution_BoundaryCondition_Zero_1313) {

    PSOutputDev psOutput(mockDoc, psTitle, nullptr, PSOutMode::normal, 595, 842, false, false, 0, 0, 595, 842, PSForceRasterize::none, true, nullptr, nullptr, PSLevel::level1);

    EXPECT_NO_THROW(psOutput.setRasterResolution(0.0));

}



TEST_F(PSOutputDevTest_1313, SetRasterResolution_BoundaryCondition_Negative_1313) {

    PSOutputDev psOutput(mockDoc, psTitle, nullptr, PSOutMode::normal, 595, 842, false, false, 0, 0, 595, 842, PSForceRasterize::none, true, nullptr, nullptr, PSLevel::level1);

    EXPECT_NO_THROW(psOutput.setRasterResolution(-300.0));

}



TEST_F(PSOutputDevTest_1313, SetRasterResolution_BoundaryCondition_HighValue_1313) {

    PSOutputDev psOutput(mockDoc, psTitle, nullptr, PSOutMode::normal, 595, 842, false, false, 0, 0, 595, 842, PSForceRasterize::none, true, nullptr, nullptr, PSLevel::level1);

    EXPECT_NO_THROW(psOutput.setRasterResolution(1200.0));

}



TEST_F(PSOutputDevTest_1313, SetRasterMono_NormalOperation_1313) {

    PSOutputDev psOutput(mockDoc, psTitle, nullptr, PSOutMode::normal, 595, 842, false, false, 0, 0, 595, 842, PSForceRasterize::none, true, nullptr, nullptr, PSLevel::level1);

    EXPECT_NO_THROW(psOutput.setRasterMono());

}



TEST_F(PSOutputDevTest_1313, SetUncompressPreloadedImages_NormalOperation_1313) {

    PSOutputDev psOutput(mockDoc, psTitle, nullptr, PSOutMode::normal, 595, 842, false, false, 0, 0, 595, 842, PSForceRasterize::none, true, nullptr, nullptr, PSLevel::level1);

    EXPECT_NO_THROW(psOutput.setUncompressPreloadedImages(true));

}



TEST_F(PSOutputDevTest_1313, SetEmbedType1_NormalOperation_1313) {

    PSOutputDev psOutput(mockDoc, psTitle, nullptr, PSOutMode::normal, 595, 842, false, false, 0, 0, 595, 842, PSForceRasterize::none, true, nullptr, nullptr, PSLevel::level1);

    EXPECT_NO_THROW(psOutput.setEmbedType1(true));

}



TEST_F(PSOutputDevTest_1313, SetEmbedTrueType_NormalOperation_1313) {

    PSOutputDev psOutput(mockDoc, psTitle, nullptr, PSOutMode::normal, 595, 842, false, false, 0, 0, 595, 842, PSForceRasterize::none, true, nullptr, nullptr, PSLevel::level1);

    EXPECT_NO_THROW(psOutput.setEmbedTrueType(true));

}



TEST_F(PSOutputDevTest_1313, SetEmbedCIDPostScript_NormalOperation_1313) {

    PSOutputDev psOutput(mockDoc, psTitle, nullptr, PSOutMode::normal, 595, 842, false, false, 0, 0, 595, 842, PSForceRasterize::none, true, nullptr, nullptr, PSLevel::level1);

    EXPECT_NO_THROW(psOutput.setEmbedCIDPostScript(true));

}



TEST_F(PSOutputDevTest_1313, SetEmbedCIDTrueType_NormalOperation_1313) {

    PSOutputDev psOutput(mockDoc, psTitle, nullptr, PSOutMode::normal, 595, 842, false, false, 0, 0, 595, 842, PSForceRasterize::none, true, nullptr, nullptr, PSLevel::level1);

    EXPECT_NO_THROW(psOutput.setEmbedCIDTrueType(true));

}



TEST_F(PSOutputDevTest_1313, SetFontPassthrough_NormalOperation_1313) {

    PSOutputDev psOutput(mockDoc, psTitle, nullptr, PSOutMode::normal, 595, 842, false, false, 0, 0, 595, 842, PSForceRasterize::none, true, nullptr, nullptr, PSLevel::level1);

    EXPECT_NO_THROW(psOutput.setFontPassthrough(true));

}



TEST_F(PSOutputDevTest_1313, SetOptimizeColorSpace_NormalOperation_1313) {

    PSOutputDev psOutput(mockDoc, psTitle, nullptr, PSOutMode::normal, 595, 842, false, false, 0, 0, 595, 842, PSForceRasterize::none, true, nullptr, nullptr, PSLevel::level1);

    EXPECT_NO_THROW(psOutput.setOptimizeColorSpace(true));

}



TEST_F(PSOutputDevTest_1313, SetPassLevel1CustomColor_NormalOperation_1313) {

    PSOutputDev psOutput(mockDoc, psTitle, nullptr, PSOutMode::normal, 595, 842, false, false, 0, 0, 595, 842, PSForceRasterize::none, true, nullptr, nullptr, PSLevel::level1);

    EXPECT_NO_THROW(psOutput.setPassLevel1CustomColor(true));

}



TEST_F(PSOutputDevTest_1313, SetPreloadImagesForms_NormalOperation_1313) {

    PSOutputDev psOutput(mockDoc, psTitle, nullptr, PSOutMode::normal, 595, 842, false, false, 0, 0, 595, 842, PSForceRasterize::none, true, nullptr, nullptr, PSLevel::level1);

    EXPECT_NO_THROW(psOutput.setPreloadImagesForms(true));

}



TEST_F(PSOutputDevTest_1313, SetGenerateOPI_NormalOperation_1313) {

    PSOutputDev psOutput(mockDoc, psTitle, nullptr, PSOutMode::normal, 595, 842, false, false, 0, 0, 595, 842, PSForceRasterize::none, true, nullptr, nullptr, PSLevel::level1);

    EXPECT_NO_THROW(psOutput.setGenerateOPI(true));

}



TEST_F(PSOutputDevTest_1313, SetUseASCIIHex_NormalOperation_1313) {

    PSOutputDev psOutput(mockDoc, psTitle, nullptr, PSOutMode::normal, 595, 842, false, false, 0, 0, 595, 842, PSForceRasterize::none, true, nullptr, nullptr, PSLevel::level1);

    EXPECT_NO_THROW(psOutput.setUseASCIIHex(true));

}



TEST_F(PSOutputDevTest_1313, SetUseBinary_NormalOperation_1313) {

    PSOutputDev psOutput(mockDoc, psTitle, nullptr, PSOutMode::normal, 595, 842, false, false, 0, 0, 595, 842, PSForceRasterize::none, true, nullptr, nullptr, PSLevel::level1);

    EXPECT_NO_THROW(psOutput.setUseBinary(true));

}



TEST_F(PSOutputDevTest_1313, SetEnableLZW_NormalOperation_1313) {

    PSOutputDev psOutput(mockDoc, psTitle, nullptr, PSOutMode::normal, 595, 842, false, false, 0, 0, 595, 842, PSForceRasterize::none, true, nullptr, nullptr, PSLevel::level1);

    EXPECT_NO_THROW(psOutput.setEnableLZW(true));

}



TEST_F(PSOutputDevTest_1313, SetEnableFlate_NormalOperation_1313) {

    PSOutputDev psOutput(mockDoc, psTitle, nullptr, PSOutMode::normal, 595, 842, false, false, 0, 0, 595, 842, PSForceRasterize::none, true, nullptr, nullptr, PSLevel::level1);

    EXPECT_NO_THROW(psOutput.setEnableFlate(true));

}



TEST_F(PSOutputDevTest_1313, SetProcessColorFormat_NormalOperation_1313) {

    PSOutputDev psOutput(mockDoc, psTitle, nullptr, PSOutMode::normal, 595, 842, false, false, 0, 0, 595, 842, PSForceRasterize::none, true, nullptr, nullptr, PSLevel::level1);

    EXPECT_NO_THROW(psOutput.setProcessColorFormat(SplashColorMode::modeMono));

}
