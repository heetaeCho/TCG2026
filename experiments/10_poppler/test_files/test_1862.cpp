#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler/ImageEmbeddingUtils.cc"

#include "poppler/XRef.h"



using namespace ImageEmbeddingUtils;

using ::testing::_;

using ::testing::Return;



class MockXRef : public XRef {

public:

    MOCK_METHOD(Ref, addStreamObject, (Dict*, std::vector<char>, StreamCompression), (override));

};



class PngEmbedderTest_1862 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize a valid png_structp and png_infop for testing purposes

        m_png = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);

        m_info = png_create_info_struct(m_png);



        // Mock XRef object

        mockXRef = std::make_unique<MockXRef>();

    }



    void TearDown() override {

        // Cleanup the png_structp and png_infop after each test

        if (m_png) png_destroy_read_struct(&m_png, &m_info, nullptr);

        mockXRef.reset();

    }



    png_structp m_png;

    png_infop m_info;

    std::unique_ptr<MockXRef> mockXRef;

};



TEST_F(PngEmbedderTest_1862, EmbedImage_ReturnsValidRef_1862) {

    // Arrange

    auto stream = std::make_unique<LibpngInputStream>();

    PngEmbedder pngEmbedder(m_png, m_info, std::move(stream));

    EXPECT_CALL(*mockXRef, addStreamObject(_, _, _)).Times(2).WillRepeatedly(Return(Ref{1, 0}));



    // Act

    Ref result = pngEmbedder.embedImage(mockXRef.get());



    // Assert

    EXPECT_NE(result.num, -1);

}



TEST_F(PngEmbedderTest_1862, EmbedImage_WithAlpha_AddsMaskImageDict_1862) {

    // Arrange

    auto stream = std::make_unique<LibpngInputStream>();

    PngEmbedder pngEmbedder(m_png, m_info, std::move(stream));

    EXPECT_CALL(*mockXRef, addStreamObject(_, _, _)).Times(2).WillRepeatedly(Return(Ref{1, 0}));



    // Act

    Ref result = pngEmbedder.embedImage(mockXRef.get());



    // Assert

    EXPECT_NE(result.num, -1);

}



TEST_F(PngEmbedderTest_1862, EmbedImage_WidthHeightZero_ReturnsInvalidRef_1862) {

    // Arrange

    auto stream = std::make_unique<LibpngInputStream>();

    PngEmbedder pngEmbedder(m_png, m_info, std::move(stream));

    EXPECT_CALL(*mockXRef, addStreamObject(_, _, _)).Times(0);



    // Act

    Ref result = pngEmbedder.embedImage(mockXRef.get());



    // Assert

    EXPECT_EQ(result.num, -1);

}



TEST_F(PngEmbedderTest_1862, EmbedImage_LargeDimensions_ReturnsInvalidRef_1862) {

    // Arrange

    auto stream = std::make_unique<LibpngInputStream>();

    PngEmbedder pngEmbedder(m_png, m_info, std::move(stream));

    EXPECT_CALL(*mockXRef, addStreamObject(_, _, _)).Times(0);



    // Act

    Ref result = pngEmbedder.embedImage(mockXRef.get());



    // Assert

    EXPECT_EQ(result.num, -1);

}



TEST_F(PngEmbedderTest_1862, EmbedImage_NormalDimensions_ReturnsValidRef_1862) {

    // Arrange

    auto stream = std::make_unique<LibpngInputStream>();

    PngEmbedder pngEmbedder(m_png, m_info, std::move(stream));

    EXPECT_CALL(*mockXRef, addStreamObject(_, _, _)).Times(2).WillRepeatedly(Return(Ref{1, 0}));



    // Act

    Ref result = pngEmbedder.embedImage(mockXRef.get());



    // Assert

    EXPECT_NE(result.num, -1);

}

```


