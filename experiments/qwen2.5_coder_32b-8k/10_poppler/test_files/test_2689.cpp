#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/poppler/utils/pdftocairo.cc"

#include "./TestProjects/poppler/goo/GooString.h"

#include "./TestProjects/poppler/goo/ImgWriter.h"

#include "./TestProjects/poppler/goo/PNGWriter.h"

#include "./TestProjects/poppler/goo/JpegWriter.h"

#include "./TestProjects/poppler/goo/TiffWriter.h"



using namespace testing;



class MockFILE {

public:

    MOCK_METHOD(int, fclose, (), (throw()));

};



extern bool png;

extern bool jpeg;

extern bool tiff;

extern bool transp;

extern bool gray;

extern bool mono;

extern double x_resolution;

extern double y_resolution;

extern int jpegQuality;

extern bool jpegProgressive;

extern bool jpegOptimize;

extern char tiffCompressionStr[16];

extern unsigned char* icc_data;

extern int icc_data_size;

extern GfxLCMSProfilePtr profile;



class WritePageImageTest_2689 : public ::testing::Test {

protected:

    void SetUp() override {

        // Reset global variables

        png = false;

        jpeg = false;

        tiff = false;

        transp = false;

        gray = false;

        mono = false;

        x_resolution = 150.0;

        y_resolution = 150.0;

        jpegQuality = -1;

        jpegProgressive = false;

        jpegOptimize = false;

        memset(tiffCompressionStr, 0, sizeof(tiffCompressionStr));

        icc_data = nullptr;

        icc_data_size = 0;

        profile = nullptr;



        // Mock FILE

        mock_file = std::make_unique<MockFILE>();

    }



    void TearDown() override {

        // Clean up if necessary

    }



    GooString filename{"output.png"};

    FILE* file{nullptr};

    cairo_surface_t* surface{nullptr};



    std::unique_ptr<MockFILE> mock_file;

};



TEST_F(WritePageImageTest_2689, WritePNG_Transparent_RGBA_2689) {

    png = true;

    transp = true;



    EXPECT_CALL(*mock_file, fclose()).Times(1);



    writePageImage(&filename);

}



TEST_F(WritePageImageTest_2689, WritePNG_GrayScale_GRAY_2689) {

    png = true;

    gray = true;



    EXPECT_CALL(*mock_file, fclose()).Times(1);



    writePageImage(&filename);

}



TEST_F(WritePageImageTest_2689, WritePNG_Monochrome_MONOCHROME_2689) {

    png = true;

    mono = true;



    EXPECT_CALL(*mock_file, fclose()).Times(1);



    writePageImage(&filename);

}



TEST_F(WritePageImageTest_2689, WritePNG_RGB_2689) {

    png = true;



    EXPECT_CALL(*mock_file, fclose()).Times(1);



    writePageImage(&filename);

}



TEST_F(WritePageImageTest_2689, WriteJPEG_GrayScale_GRAY_2689) {

    jpeg = true;

    gray = true;



    EXPECT_CALL(*mock_file, fclose()).Times(1);



    writePageImage(&filename);

}



TEST_F(WritePageImageTest_2689, WriteJPEG_RGB_2689) {

    jpeg = true;



    EXPECT_CALL(*mock_file, fclose()).Times(1);



    writePageImage(&filename);

}



TEST_F(WritePageImageTest_2689, WriteTIFF_Transparent_RGBA_PREMULTIPLIED_2689) {

    tiff = true;

    transp = true;



    EXPECT_CALL(*mock_file, fclose()).Times(1);



    writePageImage(&filename);

}



TEST_F(WritePageImageTest_2689, WriteTIFF_GrayScale_GRAY_2689) {

    tiff = true;

    gray = true;



    EXPECT_CALL(*mock_file, fclose()).Times(1);



    writePageImage(&filename);

}



TEST_F(WritePageImageTest_2689, WriteTIFF_Monochrome_MONOCHROME_2689) {

    tiff = true;

    mono = true;



    EXPECT_CALL(*mock_file, fclose()).Times(1);



    writePageImage(&filename);

}



TEST_F(WritePageImageTest_2689, WriteTIFF_RGB_2689) {

    tiff = true;



    EXPECT_CALL(*mock_file, fclose()).Times(1);



    writePageImage(&filename);

}



TEST_F(WritePageImageTest_2689, WriteToStdout_2689) {

    filename = GooString{"fd://0"};



    EXPECT_CALL(*mock_file, fclose()).Times(0); // stdout does not need to be closed



    writePageImage(&filename);

}



TEST_F(WritePageImageTest_2689, WriteToFile_ErrorHandling_2689) {

    filename = GooString{"nonexistent/path/output.png"};



    EXPECT_CALL(*mock_file, fclose()).Times(0); // File will not be opened



    writePageImage(&filename);

}



TEST_F(WritePageImageTest_2689, WritePNG_ErrorDuringInit_2689) {

    png = true;



    FILE* mockFilePtr = fopen("output.png", "wb");

    EXPECT_CALL(*mock_file, fclose()).Times(1);



    // Mock the init function to return false

    ON_CALL(*(static_cast<PNGWriter*>(writer)), init(file, _, _, _, _))

        .WillByDefault(Return(false));



    writePageImage(&filename);

}



TEST_F(WritePageImageTest_2689, WriteJPEG_ErrorDuringInit_2689) {

    jpeg = true;



    FILE* mockFilePtr = fopen("output.jpg", "wb");

    EXPECT_CALL(*mock_file, fclose()).Times(1);



    // Mock the init function to return false

    ON_CALL(*(static_cast<JpegWriter*>(writer)), init(file, _, _, _, _))

        .WillByDefault(Return(false));



    writePageImage(&filename);

}



TEST_F(WritePageImageTest_2689, WriteTIFF_ErrorDuringInit_2689) {

    tiff = true;



    FILE* mockFilePtr = fopen("output.tiff", "wb");

    EXPECT_CALL(*mock_file, fclose()).Times(1);



    // Mock the init function to return false

    ON_CALL(*(static_cast<TiffWriter*>(writer)), init(file, _, _, _, _))

        .WillByDefault(Return(false));



    writePageImage(&filename);

}
