#include <gtest/gtest.h>

#include "PSOutputDev.h"

#include <memory>



class PSOutputDevTest : public ::testing::Test {

protected:

    PDFDoc* mockPDFDoc;

    char psTitle[256] = "test_title";

    int paperWidth = 595; // A4 width in points

    int paperHeight = 842; // A4 height in points



    void SetUp() override {

        mockPDFDoc = new PDFDoc();

    }



    void TearDown() override {

        delete mockPDFDoc;

    }

};



TEST_F(PSOutputDevTest_1294, useDrawCharReturnsFalse_1294) {

    PSOutputDev psOut(nullptr, mockPDFDoc, psTitle, 1, psModeMono, paperWidth, paperHeight, false, false, 0, 0, paperWidth, paperHeight, forceRasterizeAlways, true, nullptr, nullptr, psLevel2);

    EXPECT_FALSE(psOut.useDrawChar());

}



TEST_F(PSOutputDevTest_1294, useTilingPatternFillReturnsTrue_1294) {

    PSOutputDev psOut(nullptr, mockPDFDoc, psTitle, 1, psModeMono, paperWidth, paperHeight, false, false, 0, 0, paperWidth, paperHeight, forceRasterizeAlways, true, nullptr, nullptr, psLevel2);

    EXPECT_TRUE(psOut.useTilingPatternFill());

}



TEST_F(PSOutputDevTest_1294, useShadedFillsReturnsTrueForTypeAxial_1294) {

    PSOutputDev psOut(nullptr, mockPDFDoc, psTitle, 1, psModeMono, paperWidth, paperHeight, false, false, 0, 0, paperWidth, paperHeight, forceRasterizeAlways, true, nullptr, nullptr, psLevel2);

    EXPECT_TRUE(psOut.useShadedFills(gfxAxialShading));

}



TEST_F(PSOutputDevTest_1294, useShadedFillsReturnsTrueForTypeRadial_1294) {

    PSOutputDev psOut(nullptr, mockPDFDoc, psTitle, 1, psModeMono, paperWidth, paperHeight, false, false, 0, 0, paperWidth, paperHeight, forceRasterizeAlways, true, nullptr, nullptr, psLevel2);

    EXPECT_TRUE(psOut.useShadedFills(gfxRadialShading));

}



TEST_F(PSOutputDevTest_1294, useShadedFillsReturnsTrueForTypePatchMesh_1294) {

    PSOutputDev psOut(nullptr, mockPDFDoc, psTitle, 1, psModeMono, paperWidth, paperHeight, false, false, 0, 0, paperWidth, paperHeight, forceRasterizeAlways, true, nullptr, nullptr, psLevel2);

    EXPECT_TRUE(psOut.useShadedFills(gfxPatchMeshShading));

}



TEST_F(PSOutputDevTest_1294, useDrawFormReturnsTrue_1294) {

    PSOutputDev psOut(nullptr, mockPDFDoc, psTitle, 1, psModeMono, paperWidth, paperHeight, false, false, 0, 0, paperWidth, paperHeight, forceRasterizeAlways, true, nullptr, nullptr, psLevel2);

    EXPECT_TRUE(psOut.useDrawForm());

}



TEST_F(PSOutputDevTest_1294, interpretType3CharsReturnsFalse_1294) {

    PSOutputDev psOut(nullptr, mockPDFDoc, psTitle, 1, psModeMono, paperWidth, paperHeight, false, false, 0, 0, paperWidth, paperHeight, forceRasterizeAlways, true, nullptr, nullptr, psLevel2);

    EXPECT_FALSE(psOut.interpretType3Chars());

}



TEST_F(PSOutputDevTest_1294, needClipToCropBoxReturnsTrue_1294) {

    PSOutputDev psOut(nullptr, mockPDFDoc, psTitle, 1, psModeMono, paperWidth, paperHeight, false, false, 0, 0, paperWidth, paperHeight, forceRasterizeAlways, true, nullptr, nullptr, psLevel2);

    EXPECT_TRUE(psOut.needClipToCropBox());

}



TEST_F(PSOutputDevTest_1294, isOkReturnsTrueAfterInitialization_1294) {

    PSOutputDev psOut(nullptr, mockPDFDoc, psTitle, 1, psModeMono, paperWidth, paperHeight, false, false, 0, 0, paperWidth, paperHeight, forceRasterizeAlways, true, nullptr, nullptr, psLevel2);

    EXPECT_TRUE(psOut.isOk());

}



TEST_F(PSOutputDevTest_1294, upsideDownReturnsFalseByDefault_1294) {

    PSOutputDev psOut(nullptr, mockPDFDoc, psTitle, 1, psModeMono, paperWidth, paperHeight, false, false, 0, 0, paperWidth, paperHeight, forceRasterizeAlways, true, nullptr, nullptr, psLevel2);

    EXPECT_FALSE(psOut.upsideDown());

}
