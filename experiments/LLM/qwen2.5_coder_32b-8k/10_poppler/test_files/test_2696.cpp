#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/poppler/utils/pdftocairo.cc"

#include "./TestProjects/poppler/goo/GooString.h"



// Mocking global variables for testing purposes

extern bool ::singleFile;

extern bool ::png;

extern bool ::jpeg;

extern bool ::tiff;



TEST(getImageFileName_2696, NormalOperationSinglePage_2696) {

    singleFile = true;

    png = true;

    jpeg = false;

    tiff = false;

    GooString outputFileName("output");

    auto result = getImageFileName(&outputFileName, 3, 1);

    EXPECT_EQ(result->toStr(), "output.png");

}



TEST(getImageFileName_2696, NormalOperationMultiplePages_2696) {

    singleFile = false;

    png = true;

    jpeg = false;

    tiff = false;

    GooString outputFileName("output");

    auto result = getImageFileName(&outputFileName, 3, 5);

    EXPECT_EQ(result->toStr(), "output-005.png");

}



TEST(getImageFileName_2696, JPEGOutput_2696) {

    singleFile = false;

    png = false;

    jpeg = true;

    tiff = false;

    GooString outputFileName("output");

    auto result = getImageFileName(&outputFileName, 3, 5);

    EXPECT_EQ(result->toStr(), "output-005.jpg");

}



TEST(getImageFileName_2696, TIFFOutput_2696) {

    singleFile = false;

    png = false;

    jpeg = false;

    tiff = true;

    GooString outputFileName("output");

    auto result = getImageFileName(&outputFileName, 3, 5);

    EXPECT_EQ(result->toStr(), "output-005.tif");

}



TEST(getImageFileName_2696, FDOutput_2696) {

    singleFile = false;

    png = true;

    jpeg = false;

    tiff = false;

    GooString outputFileName("fd://0");

    auto result = getImageFileName(&outputFileName, 3, 5);

    EXPECT_EQ(result->toStr(), "fd://0-005");

}



TEST(getImageFileName_2696, SingleFileWithExtension_2696) {

    singleFile = true;

    png = true;

    jpeg = false;

    tiff = false;

    GooString outputFileName("output.png");

    auto result = getImageFileName(&outputFileName, 3, 1);

    EXPECT_EQ(result->toStr(), "output.png.png");

}



TEST(getImageFileName_2696, BoundaryConditionSingleDigitPageNumber_2696) {

    singleFile = false;

    png = true;

    jpeg = false;

    tiff = false;

    GooString outputFileName("output");

    auto result = getImageFileName(&outputFileName, 1, 5);

    EXPECT_EQ(result->toStr(), "output-5.png");

}



TEST(getImageFileName_2696, BoundaryConditionMaxDigitsPageNumber_2696) {

    singleFile = false;

    png = true;

    jpeg = false;

    tiff = false;

    GooString outputFileName("output");

    auto result = getImageFileName(&outputFileName, 3, 999);

    EXPECT_EQ(result->toStr(), "output-999.png");

}



TEST(getImageFileName_2696, NoExtensionSingleFile_2696) {

    singleFile = true;

    png = false;

    jpeg = false;

    tiff = false;

    GooString outputFileName("output");

    auto result = getImageFileName(&outputFileName, 3, 1);

    EXPECT_EQ(result->toStr(), "output");

}



TEST(getImageFileName_2696, NoExtensionMultipleFiles_2696) {

    singleFile = false;

    png = false;

    jpeg = false;

    tiff = false;

    GooString outputFileName("output");

    auto result = getImageFileName(&outputFileName, 3, 1);

    EXPECT_EQ(result->toStr(), "output-001");

}
