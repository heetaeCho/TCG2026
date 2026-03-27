#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "ImageEmbeddingUtils.cc"

#include "Error.h"



namespace ImageEmbeddingUtils {



using ::testing::_;

using ::testing::Invoke;

using ::testing::Return;



class MockLibpngInputStream : public LibpngInputStream {

public:

    MOCK_METHOD(png_size_t, readCallback(void* ptr, png_size_t size), (override));

};



TEST(PngEmbedderTest_1861, CreateValidPng_1861) {

    std::vector<char> validPngData = { 137, 80, 78, 71, 13, 10, 26, 10, 0, 0, 0, 13, 73, 72, 68, 82, 0, 0, 0, 1, 0, 0, 0, 1, 8, 4, 0, 0, 0, 29, -115, 119, 52, 0, 0, 0, 3, 80, 76, 84, 69, 255, 0, 0, 0, 255, 255, 255, -1, 107, -83, 4, 0, 0, 0, 1, 116, 82, 78, 83, 0, -97, -39, 21, 120, 0, 0, 0, 10, 49, 68, 65, 84, 120, -39, 99, 96, -49, 0, 1, 0, 1, -127, 39, -50, 88, 0, 0, 0, 0, 73, 69, 78, 68, -82, 66, 96, -126 };

    auto pngEmbedder = PngEmbedder::create(std::move(validPngData));

    EXPECT_NE(pngEmbedder, nullptr);

}



TEST(PngEmbedderTest_1861, CreateInvalidPng_1861) {

    std::vector<char> invalidPngData = { 0, 0, 0, 0 };

    auto pngEmbedder = PngEmbedder::create(std::move(invalidPngData));

    EXPECT_EQ(pngEmbedder, nullptr);

}



TEST(PngEmbedderTest_1861, CreateEmptyPng_1861) {

    std::vector<char> emptyPngData = {};

    auto pngEmbedder = PngEmbedder::create(std::move(emptyPngData));

    EXPECT_EQ(pngEmbedder, nullptr);

}



TEST(PngEmbedderTest_1861, CreatePngWithUnsupportedBitDepth_1861) {

    std::vector<char> unsupportedPngData = { 137, 80, 78, 71, 13, 10, 26, 10, 0, 0, 0, 13, 73, 72, 68, 82, 0, 0, 0, 1, 0, 0, 0, 1, 16, 4, 0, 0, 0, 29, -115, 119, 52, 0, 0, 0, 3, 80, 76, 84, 69, 255, 0, 0, 0, 255, 255, 255, -1, 107, -83, 4, 0, 0, 0, 1, 116, 82, 78, 83, 0, -97, -39, 21, 120, 0, 0, 0, 10, 49, 68, 65, 84, 120, -39, 99, 96, -49, 0, 1, 0, 1, -127, 39, -50, 88, 0, 0, 0, 0, 73, 69, 78, 68, -82, 66, 96, -126 };

    auto pngEmbedder = PngEmbedder::create(std::move(unsupportedPngData));

    EXPECT_EQ(pngEmbedder, nullptr);

}



TEST(PngEmbedderTest_1861, CreatePngWithValidBitDepth8_1861) {

    std::vector<char> validPngData8Bit = { 137, 80, 78, 71, 13, 10, 26, 10, 0, 0, 0, 13, 73, 72, 68, 82, 0, 0, 0, 1, 0, 0, 0, 1, 8, 4, 0, 0, 0, 29, -115, 119, 52, 0, 0, 0, 3, 80, 76, 84, 69, 255, 0, 0, 0, 255, 255, 255, -1, 107, -83, 4, 0, 0, 0, 1, 116, 82, 78, 83, 0, -97, -39, 21, 120, 0, 0, 0, 10, 49, 68, 65, 84, 120, -39, 99, 96, -49, 0, 1, 0, 1, -127, 39, -50, 88, 0, 0, 0, 0, 73, 69, 78, 68, -82, 66, 96, -126 };

    auto pngEmbedder = PngEmbedder::create(std::move(validPngData8Bit));

    EXPECT_NE(pngEmbedder, nullptr);

}



TEST(PngEmbedderTest_1861, CreatePngWithValidBitDepth16_1861) {

    std::vector<char> validPngData16Bit = { 137, 80, 78, 71, 13, 10, 26, 10, 0, 0, 0, 13, 73, 72, 68, 82, 0, 0, 0, 1, 0, 0, 0, 1, 16, 4, 0, 0, 0, 29, -115, 119, 52, 0, 0, 0, 3, 80, 76, 84, 69, 255, 0, 0, 0, 255, 255, 255, -1, 107, -83, 4, 0, 0, 0, 1, 116, 82, 78, 83, 0, -97, -39, 21, 120, 0, 0, 0, 10, 49, 68, 65, 84, 120, -39, 99, 96, -49, 0, 1, 0, 1, -127, 39, -50, 88, 0, 0, 0, 0, 73, 69, 78, 68, -82, 66, 96, -126 };

    auto pngEmbedder = PngEmbedder::create(std::move(validPngData16Bit));

    EXPECT_NE(pngEmbedder, nullptr);

}



} // namespace ImageEmbeddingUtils
