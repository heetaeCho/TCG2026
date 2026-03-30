#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Mock classes for Stream and GfxImageColorMap

class MockStream : public Stream {

public:

    MOCK_METHOD(bool, rewind, (), (override));

    MOCK_METHOD(void, close, (), (override));

};



class MockGfxImageColorMap : public GfxImageColorMap {

public:

    using GfxImageColorMap::GfxImageColorMap;

    MOCK_METHOD(GfxColorSpaceMode, getMode, (), (const, override));

    MOCK_METHOD(int, getNumPixelComps, (), (const, override));

    MOCK_METHOD(int, getBits, (), (const, override));

};



// Test Fixture

class RescaleDrawImageTest : public ::testing::Test {

protected:

    std::unique_ptr<MockStream> mockStream;

    std::unique_ptr<MockGfxImageColorMap> mockColorMap;



    void SetUp() override {

        mockStream = std::make_unique<MockStream>();

        mockColorMap = std::make_unique<MockGfxImageColorMap>(1, nullptr, std::make_unique<GfxColorSpace>());

    }

};



// Normal Operation

TEST_F(RescaleDrawImageTest, GetSourceImage_Success_1930) {

    EXPECT_CALL(*mockStream, rewind()).WillOnce(testing::Return(true));



    RescaleDrawImage rescaleDrawImage;

    cairo_surface_t* image = rescaleDrawImage.getSourceImage(mockStream.get(), 100, 100, 50, 50, false, mockColorMap.get(), nullptr);



    ASSERT_NE(image, nullptr);

    cairo_surface_destroy(image);

}



// Boundary Conditions

TEST_F(RescaleDrawImageTest, GetSourceImage_MaxCairoSize_1930) {

    EXPECT_CALL(*mockStream, rewind()).WillOnce(testing::Return(true));



    RescaleDrawImage rescaleDrawImage;

    cairo_surface_t* image = rescaleDrawImage.getSourceImage(mockStream.get(), ::MAX_CAIRO_IMAGE_SIZE, ::MAX_CAIRO_IMAGE_SIZE, 50, 50, false, mockColorMap.get(), nullptr);



    ASSERT_NE(image, nullptr);

    cairo_surface_destroy(image);

}



TEST_F(RescaleDrawImageTest, GetSourceImage_ZeroScaledDimensions_1930) {

    EXPECT_CALL(*mockStream, rewind()).WillOnce(testing::Return(true));



    RescaleDrawImage rescaleDrawImage;

    cairo_surface_t* image = rescaleDrawImage.getSourceImage(mockStream.get(), 100, 100, 0, 0, false, mockColorMap.get(), nullptr);



    ASSERT_NE(image, nullptr);

    cairo_surface_destroy(image);

}



// Exceptional or Error Cases

TEST_F(RescaleDrawImageTest, GetSourceImage_StreamRewindFail_1930) {

    EXPECT_CALL(*mockStream, rewind()).WillOnce(testing::Return(false));



    RescaleDrawImage rescaleDrawImage;

    cairo_surface_t* image = rescaleDrawImage.getSourceImage(mockStream.get(), 100, 100, 50, 50, false, mockColorMap.get(), nullptr);



    ASSERT_EQ(image, nullptr);

}



TEST_F(RescaleDrawImageTest, GetSourceImage_MaxPrintSize_1930) {

    EXPECT_CALL(*mockStream, rewind()).WillOnce(testing::Return(true));



    RescaleDrawImage rescaleDrawImage;

    cairo_surface_t* image = rescaleDrawImage.getSourceImage(mockStream.get(), ::MAX_PRINT_IMAGE_SIZE * 2, ::MAX_PRINT_IMAGE_SIZE * 2, 50, 50, true, mockColorMap.get(), nullptr);



    ASSERT_NE(image, nullptr);

    cairo_surface_destroy(image);

}



// Verification of External Interactions

TEST_F(RescaleDrawImageTest, GetSourceImage_StreamCloseCalled_1930) {

    EXPECT_CALL(*mockStream, rewind()).WillOnce(testing::Return(true));

    EXPECT_CALL(*mockStream, close());



    RescaleDrawImage rescaleDrawImage;

    cairo_surface_t* image = rescaleDrawImage.getSourceImage(mockStream.get(), 100, 100, 50, 50, false, mockColorMap.get(), nullptr);



    if (image) {

        cairo_surface_destroy(image);

    }

}
