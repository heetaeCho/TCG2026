#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Mock PDFDoc class to control behavior for testing

class MockPDFDoc : public PDFDoc {

public:

    MOCK_METHOD0(isOk, bool());

    MOCK_METHOD1(getPageMediaWidth, double(int));

    MOCK_METHOD1(getPageMediaHeight, double(int));

};



// Mock SplashOutputDev class to control behavior for testing

class MockSplashOutputDev : public SplashOutputDev {

public:

    MockSplashOutputDev(SplashColorMode colorModeA, int bitmapRowPadA, SplashColorPtr paperColorA, bool bitmapTopDownA,

                        SplashThinLineMode thinLineMode, bool overprintPreviewA)

        : SplashOutputDev(colorModeA, bitmapRowPadA, paperColorA, bitmapTopDownA, thinLineMode, overprintPreviewA) {}



    MOCK_METHOD0(takeBitmap, SplashBitmap*());

};



// Mock SplashBitmap class to control behavior for testing

class MockSplashBitmap : public SplashBitmap {

public:

    MockSplashBitmap(int widthA, int heightA, int rowPad, SplashColorMode modeA, bool alphaA, bool topDown,

                     const std::vector<std::unique_ptr<GfxSeparationColorSpace>>* separationList)

        : SplashBitmap(widthA, heightA, rowPad, modeA, alphaA, topDown, separationList) {}



    MOCK_METHOD2(writeImgFile, SplashError(SplashImageFileFormat format, const char *fileName, double hDPI, double vDPI,

                                            WriteImgParams* params));

};



// Test fixture for savePage functionality

class SavePageTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup global variables as needed

        lastPage = 1;

        x_resolution = 150.0;

        y_resolution = 150.0;

        useCropBox = false;

        png = true; // Assuming we're testing PNG for simplicity



        mockDoc = std::make_unique<MockPDFDoc>();

        mockOutputDev = std::make_unique<MockSplashOutputDev>(splashModeRGB8, 1, nullptr, false, splashThinLineDefault, false);

    }



    void TearDown() override {

        // Cleanup if necessary

    }



    std::unique_ptr<MockPDFDoc> mockDoc;

    std::unique_ptr<MockSplashOutputDev> mockOutputDev;

};



// Test case for normal operation with valid document and output device

TEST_F(SavePageTest, NormalOperation) {

    EXPECT_CALL(*mockDoc, isOk()).WillOnce(::testing::Return(true));

    EXPECT_CALL(*mockDoc, getPageMediaWidth(1)).WillOnce(::testing::Return(595.0));

    EXPECT_CALL(*mockDoc, getPageMediaHeight(1)).WillOnce(::testing::Return(842.0));



    auto mockBitmap = std::make_unique<MockSplashBitmap>(595, 842, 1, splashModeRGB8, false, false, nullptr);

    EXPECT_CALL(*mockOutputDev, takeBitmap()).WillOnce(::testing::Return(mockBitmap.release()));



    // Assuming the writeImgFile will be called with correct parameters

    SplashBitmap::WriteImgParams params;

    EXPECT_CALL(*static_cast<MockSplashBitmap*>(mockOutputDev->takeBitmap()), 

                writeImgFile(splashFormatPng, ::testing::StrEq("output.png"), 150.0, 150.0, &params))

        .WillOnce(::testing::Return(SplashError::NoError));



    savePage(mockDoc.get(), mockOutputDev.get(), "output.png");

}



// Test case for invalid document

TEST_F(SavePageTest, InvalidDocument) {

    EXPECT_CALL(*mockDoc, isOk()).WillOnce(::testing::Return(false));



    // Assuming function should handle gracefully without calling takeBitmap or writeImgFile

    savePage(mockDoc.get(), mockOutputDev.get(), "output.png");

}



// Test case for zero image dimensions (edge case)

TEST_F(SavePageTest, ZeroDimensions) {

    EXPECT_CALL(*mockDoc, isOk()).WillOnce(::testing::Return(true));

    EXPECT_CALL(*mockDoc, getPageMediaWidth(1)).WillOnce(::testing::Return(0.0));

    EXPECT_CALL(*mockDoc, getPageMediaHeight(1)).WillOnce(::testing::Return(0.0));



    // Assuming takeBitmap and writeImgFile should not be called in this case

    savePage(mockDoc.get(), mockOutputDev.get(), "output.png");

}



// Test case for JPEG output

TEST_F(SavePageTest, JPEGOuput) {

    jpeg = true;  // Set global variable to test JPEG output



    EXPECT_CALL(*mockDoc, isOk()).WillOnce(::testing::Return(true));

    EXPECT_CALL(*mockDoc, getPageMediaWidth(1)).WillOnce(::testing::Return(595.0));

    EXPECT_CALL(*mockDoc, getPageMediaHeight(1)).WillOnce(::testing::Return(842.0));



    auto mockBitmap = std::make_unique<MockSplashBitmap>(595, 842, 1, splashModeRGB8, false, false, nullptr);

    EXPECT_CALL(*mockOutputDev, takeBitmap()).WillOnce(::testing::Return(mockBitmap.release()));



    // Assuming the writeImgFile will be called with correct parameters

    SplashBitmap::WriteImgParams params;

    EXPECT_CALL(*static_cast<MockSplashBitmap*>(mockOutputDev->takeBitmap()), 

                writeImgFile(splashFormatJpeg, ::testing::StrEq("output.jpg"), 150.0, 150.0, &params))

        .WillOnce(::testing::Return(SplashError::NoError));



    savePage(mockDoc.get(), mockOutputDev.get(), "output.jpg");

}



// Test case for TIFF output

TEST_F(SavePageTest, TIFFOuput) {

    tiff = true;  // Set global variable to test TIFF output



    EXPECT_CALL(*mockDoc, isOk()).WillOnce(::testing::Return(true));

    EXPECT_CALL(*mockDoc, getPageMediaWidth(1)).WillOnce(::testing::Return(595.0));

    EXPECT_CALL(*mockDoc, getPageMediaHeight(1)).WillOnce(::testing::Return(842.0));



    auto mockBitmap = std::make_unique<MockSplashBitmap>(595, 842, 1, splashModeRGB8, false, false, nullptr);

    EXPECT_CALL(*mockOutputDev, takeBitmap()).WillOnce(::testing::Return(mockBitmap.release()));



    // Assuming the writeImgFile will be called with correct parameters

    SplashBitmap::WriteImgParams params;

    EXPECT_CALL(*static_cast<MockSplashBitmap*>(mockOutputDev->takeBitmap()), 

                writeImgFile(splashFormatTiff, ::testing::StrEq("output.tiff"), 150.0, 150.0, &params))

        .WillOnce(::testing::Return(SplashError::NoError));



    savePage(mockDoc.get(), mockOutputDev.get(), "output.tiff");

}



// Test case for JPEGCMYK output

TEST_F(SavePageTest, JPEGCMYKOuput) {

    jpegcmyk = true;  // Set global variable to test JPEGCMYK output



    EXPECT_CALL(*mockDoc, isOk()).WillOnce(::testing::Return(true));

    EXPECT_CALL(*mockDoc, getPageMediaWidth(1)).WillOnce(::testing::Return(595.0));

    EXPECT_CALL(*mockDoc, getPageMediaHeight(1)).WillOnce(::testing::Return(842.0));



    auto mockBitmap = std::make_unique<MockSplashBitmap>(595, 842, 1, splashModeCMYK8, false, false, nullptr);

    EXPECT_CALL(*mockOutputDev, takeBitmap()).WillOnce(::testing::Return(mockBitmap.release()));



    // Assuming the writeImgFile will be called with correct parameters

    SplashBitmap::WriteImgParams params;

    EXPECT_CALL(*static_cast<MockSplashBitmap*>(mockOutputDev->takeBitmap()), 

                writeImgFile(splashFormatJpegCMYK, ::testing::StrEq("output.cmyk.jpg"), 150.0, 150.0, &params))

        .WillOnce(::testing::Return(SplashError::NoError));



    savePage(mockDoc.get(), mockOutputDev.get(), "output.cmyk.jpg");

}
