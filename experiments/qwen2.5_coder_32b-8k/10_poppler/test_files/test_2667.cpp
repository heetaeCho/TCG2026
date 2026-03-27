#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/poppler/utils/pdfinfo.cc"

#include "./TestProjects/poppler/poppler/PDFRectangle.h"

#include <cstdio>

#include <sstream>



using ::testing::_;

using ::testing::InvokeWithoutArgs;

using ::testing::Return;



class PrintBoxTest_2667 : public ::testing::Test {

protected:

    std::ostringstream capturedOutput;

    void SetUp() override {

        // Redirect stdout to capture output of printBox function

        std::streambuf* origOutBuffer = std::cout.rdbuf(capturedOutput.rdbuf());

    }



    void TearDown() override {

        // Restore original stdout

        std::cout.rdbuf(capturedOutput.rdbuf(NULL));

    }

};



TEST_F(PrintBoxTest_2667, PrintValidRectangle_2667) {

    PDFRectangle rect(1.1234, 2.5678, 3.9012, 4.3456);

    printBox("Rect:", &rect);

    EXPECT_EQ(capturedOutput.str(), "Rect:     1.12     2.57     3.90     4.35\n");

}



TEST_F(PrintBoxTest_2667, PrintRectangleAtOrigin_2667) {

    PDFRectangle rect(0.0, 0.0, 0.0, 0.0);

    printBox("Rect:", &rect);

    EXPECT_EQ(capturedOutput.str(), "Rect:     0.00     0.00     0.00     0.00\n");

}



TEST_F(PrintBoxTest_2667, PrintLargeRectangleValues_2667) {

    PDFRectangle rect(123456.123, 654321.987, 987654.321, 432165.789);

    printBox("Rect:", &rect);

    EXPECT_EQ(capturedOutput.str(), "Rect:123456.12654322.00987654.32432166.00\n");

}



TEST_F(PrintBoxTest_2667, PrintNegativeRectangleValues_2667) {

    PDFRectangle rect(-1.1234, -2.5678, -3.9012, -4.3456);

    printBox("Rect:", &rect);

    EXPECT_EQ(capturedOutput.str(), "Rect:    -1.12    -2.57    -3.90    -4.35\n");

}
