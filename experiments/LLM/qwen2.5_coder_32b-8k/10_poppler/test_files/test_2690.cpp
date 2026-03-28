#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Mocking global variables and functions as needed

extern double ::x_resolution;

extern double ::y_resolution;

extern int ::paperWidth;

extern int ::paperHeight;

extern bool ::printing;

extern bool ::usePDFPageSize;



void getCropSize(double page_w, double page_h, double *width, double *height);



// Mock for getCropSize function

class MockUtils {

public:

    MOCK_STATIC_METHOD2(getCropSize, void(double, double, double*, double*));

};



using ::testing::Return;

using ::testing::_;



TEST(getOutputSizeTest_2690, NormalOperation_PrintingUsePDFPageSize_2690) {

    printing = true;

    usePDFPageSize = true;

    double page_w = 8.5 * 72; // A4 width in points

    double page_h = 11 * 72;  // A4 height in points



    double width = 0, height = 0;

    getOutputSize(page_w, page_h, &width, &height);



    EXPECT_EQ(width, page_w);

    EXPECT_EQ(height, page_h);

}



TEST(getOutputSizeTest_2690, NormalOperation_PrintingNotUsePDFPageSize_Portrait_2690) {

    printing = true;

    usePDFPageSize = false;

    paperWidth = 595;  // A4 width in points

    paperHeight = 842; // A4 height in points

    double page_w = 8.5 * 72; // A4 width in points

    double page_h = 11 * 72;  // A4 height in points



    double width = 0, height = 0;

    getOutputSize(page_w, page_h, &width, &height);



    EXPECT_EQ(width, paperWidth);

    EXPECT_EQ(height, paperHeight);

}



TEST(getOutputSizeTest_2690, NormalOperation_PrintingNotUsePDFPageSize_Landscape_2690) {

    printing = true;

    usePDFPageSize = false;

    paperWidth = 842; // A4 height in points

    paperHeight = 595;  // A4 width in points

    double page_w = 11 * 72;  // A4 height in points

    double page_h = 8.5 * 72; // A4 width in points



    double width = 0, height = 0;

    getOutputSize(page_w, page_h, &width, &height);



    EXPECT_EQ(width, paperWidth);

    EXPECT_EQ(height, paperHeight);

}



TEST(getOutputSizeTest_2690, BoundaryConditions_ZeroPageSize_2690) {

    printing = true;

    usePDFPageSize = false;

    double page_w = 0;

    double page_h = 0;



    double width = 0, height = 0;

    getOutputSize(page_w, page_h, &width, &height);



    EXPECT_EQ(width, paperWidth);

    EXPECT_EQ(height, paperHeight);

}



TEST(getOutputSizeTest_2690, BoundaryConditions_MaxPageSize_2690) {

    printing = true;

    usePDFPageSize = false;

    double page_w = 1e6; // Very large width

    double page_h = 1e6; // Very large height



    double width = 0, height = 0;

    getOutputSize(page_w, page_h, &width, &height);



    EXPECT_EQ(width, paperWidth);

    EXPECT_EQ(height, paperHeight);

}



TEST(getOutputSizeTest_2690, NotPrinting_UsePDFPageSize_Ignored_2690) {

    printing = false;

    usePDFPageSize = true; // This should be ignored

    double page_w = 8.5 * 72; // A4 width in points

    double page_h = 11 * 72;  // A4 height in points



    double expectedWidth = (page_w * x_resolution / 72.0);

    double expectedHeight = (page_h * y_resolution / 72.0);



    EXPECT_CALL(MockUtils::getCropSize, getCropSize(expectedWidth, expectedHeight, _, _)).Times(1)

        .WillOnce(testing::DoAll(

            testing::SetArgReferee<2>(expectedWidth),

            testing::SetArgReferee<3>(expectedHeight)));



    double width = 0, height = 0;

    getOutputSize(page_w, page_h, &width, &height);



    EXPECT_EQ(width, expectedWidth);

    EXPECT_EQ(height, expectedHeight);

}



TEST(getOutputSizeTest_2690, NotPrinting_NotUsePDFPageSize_Ignored_2690) {

    printing = false;

    usePDFPageSize = false; // This should be ignored

    double page_w = 8.5 * 72; // A4 width in points

    double page_h = 11 * 72;  // A4 height in points



    double expectedWidth = (page_w * x_resolution / 72.0);

    double expectedHeight = (page_h * y_resolution / 72.0);



    EXPECT_CALL(MockUtils::getCropSize, getCropSize(expectedWidth, expectedHeight, _, _)).Times(1)

        .WillOnce(testing::DoAll(

            testing::SetArgReferee<2>(expectedWidth),

            testing::SetArgReferee<3>(expectedHeight)));



    double width = 0, height = 0;

    getOutputSize(page_w, page_h, &width, &height);



    EXPECT_EQ(width, expectedWidth);

    EXPECT_EQ(height, expectedHeight);

}
