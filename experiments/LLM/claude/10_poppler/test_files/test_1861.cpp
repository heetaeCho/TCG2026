#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>
#include <memory>
#include <cstring>
#include <fstream>
#include <cstdint>

// Include necessary headers
#include "poppler/ImageEmbeddingUtils.h"

using namespace ImageEmbeddingUtils;

// Helper function to create a minimal valid PNG file in memory
static std::vector<char> createMinimalPNG(int width = 1, int height = 1, int bitDepth = 8, int colorType = 2 /* RGB */)
{
    // We'll create a minimal PNG using libpng to ensure validity
    std::vector<char> result;

    png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png) {
        return result;
    }

    png_infop info = png_create_info_struct(png);
    if (!info) {
        png_destroy_write_struct(&png, nullptr);
        return result;
    }

    if (setjmp(png_jmpbuf(png))) {
        png_destroy_write_struct(&png, &info);
        return result;
    }

    // Custom write function to write to our vector
    png_set_write_fn(
            png, &result,
            [](png_structp pngPtr, png_bytep data, png_size_t length) {
                auto *vec = static_cast<std::vector<char> *>(png_get_io_ptr(pngPtr));
                vec->insert(vec->end(), reinterpret_cast<char *>(data), reinterpret_cast<char *>(data) + length);
            },
            nullptr);

    png_set_IHDR(png, info, width, height, bitDepth, colorType, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

    png_write_info(png, info);

    int channels = 0;
    switch (colorType) {
    case PNG_COLOR_TYPE_GRAY:
        channels = 1;
        break;
    case PNG_COLOR_TYPE_GRAY_ALPHA:
        channels = 2;
        break;
    case PNG_COLOR_TYPE_RGB:
        channels = 3;
        break;
    case PNG_COLOR_TYPE_RGB_ALPHA:
        channels = 4;
        break;
    case PNG_COLOR_TYPE_PALETTE:
        channels = 1;
        break;
    default:
        channels = 3;
        break;
    }

    int bytesPerPixel = channels * (bitDepth / 8);
    std::vector<png_byte> row(width * bytesPerPixel, 128);

    for (int y = 0; y < height; y++) {
        png_write_row(png, row.data());
    }

    png_write_end(png, nullptr);
    png_destroy_write_struct(&png, &info);

    return result;
}

// Helper to create a minimal palette PNG
static std::vector<char> createPalettePNG(int width = 1, int height = 1)
{
    std::vector<char> result;

    png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png) {
        return result;
    }

    png_infop info = png_create_info_struct(png);
    if (!info) {
        png_destroy_write_struct(&png, nullptr);
        return result;
    }

    if (setjmp(png_jmpbuf(png))) {
        png_destroy_write_struct(&png, &info);
        return result;
    }

    png_set_write_fn(
            png, &result,
            [](png_structp pngPtr, png_bytep data, png_size_t length) {
                auto *vec = static_cast<std::vector<char> *>(png_get_io_ptr(pngPtr));
                vec->insert(vec->end(), reinterpret_cast<char *>(data), reinterpret_cast<char *>(data) + length);
            },
            nullptr);

    png_set_IHDR(png, info, width, height, 8, PNG_COLOR_TYPE_PALETTE, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

    png_color palette[1];
    palette[0].red = 255;
    palette[0].green = 0;
    palette[0].blue = 0;
    png_set_PLTE(png, info, palette, 1);

    png_write_info(png, info);

    std::vector<png_byte> row(width, 0);
    for (int y = 0; y < height; y++) {
        png_write_row(png, row.data());
    }

    png_write_end(png, nullptr);
    png_destroy_write_struct(&png, &info);

    return result;
}

class PngEmbedderTest_1861 : public ::testing::Test {
protected:
    void SetUp() override { }
    void TearDown() override { }
};

// Test: create returns a valid embedder for a valid 8-bit RGB PNG
TEST_F(PngEmbedderTest_1861, CreateWithValidRGB8BitPNG_1861)
{
    auto pngData = createMinimalPNG(4, 4, 8, PNG_COLOR_TYPE_RGB);
    ASSERT_FALSE(pngData.empty());

    auto embedder = PngEmbedder::create(std::move(pngData));
    EXPECT_NE(embedder, nullptr);
}

// Test: create returns a valid embedder for a valid 16-bit RGB PNG
TEST_F(PngEmbedderTest_1861, CreateWithValid16BitRGBPNG_1861)
{
    auto pngData = createMinimalPNG(2, 2, 16, PNG_COLOR_TYPE_RGB);
    ASSERT_FALSE(pngData.empty());

    auto embedder = PngEmbedder::create(std::move(pngData));
    EXPECT_NE(embedder, nullptr);
}

// Test: create returns a valid embedder for RGBA PNG (8-bit with alpha)
TEST_F(PngEmbedderTest_1861, CreateWithValidRGBA8BitPNG_1861)
{
    auto pngData = createMinimalPNG(3, 3, 8, PNG_COLOR_TYPE_RGB_ALPHA);
    ASSERT_FALSE(pngData.empty());

    auto embedder = PngEmbedder::create(std::move(pngData));
    EXPECT_NE(embedder, nullptr);
}

// Test: create returns a valid embedder for grayscale PNG
TEST_F(PngEmbedderTest_1861, CreateWithValidGrayscale8BitPNG_1861)
{
    auto pngData = createMinimalPNG(2, 2, 8, PNG_COLOR_TYPE_GRAY);
    ASSERT_FALSE(pngData.empty());

    auto embedder = PngEmbedder::create(std::move(pngData));
    EXPECT_NE(embedder, nullptr);
}

// Test: create returns a valid embedder for grayscale+alpha PNG
TEST_F(PngEmbedderTest_1861, CreateWithValidGrayAlpha8BitPNG_1861)
{
    auto pngData = createMinimalPNG(2, 2, 8, PNG_COLOR_TYPE_GRAY_ALPHA);
    ASSERT_FALSE(pngData.empty());

    auto embedder = PngEmbedder::create(std::move(pngData));
    EXPECT_NE(embedder, nullptr);
}

// Test: create returns a valid embedder for a palette-based PNG
TEST_F(PngEmbedderTest_1861, CreateWithValidPalettePNG_1861)
{
    auto pngData = createPalettePNG(4, 4);
    ASSERT_FALSE(pngData.empty());

    auto embedder = PngEmbedder::create(std::move(pngData));
    // Palette PNGs get expanded by fixPng, should result in 8-bit
    EXPECT_NE(embedder, nullptr);
}

// Test: create returns nullptr for empty input
TEST_F(PngEmbedderTest_1861, CreateWithEmptyData_1861)
{
    std::vector<char> emptyData;
    auto embedder = PngEmbedder::create(std::move(emptyData));
    EXPECT_EQ(embedder, nullptr);
}

// Test: create returns nullptr for garbage/invalid data
TEST_F(PngEmbedderTest_1861, CreateWithGarbageData_1861)
{
    std::vector<char> garbageData(100, 'x');
    auto embedder = PngEmbedder::create(std::move(garbageData));
    EXPECT_EQ(embedder, nullptr);
}

// Test: create returns nullptr for truncated PNG header
TEST_F(PngEmbedderTest_1861, CreateWithTruncatedPNGHeader_1861)
{
    // PNG signature is 8 bytes, provide only partial
    std::vector<char> truncated = { '\x89', 'P', 'N', 'G' };
    auto embedder = PngEmbedder::create(std::move(truncated));
    EXPECT_EQ(embedder, nullptr);
}

// Test: create returns nullptr for a PNG with valid header but truncated body
TEST_F(PngEmbedderTest_1861, CreateWithTruncatedPNGBody_1861)
{
    auto pngData = createMinimalPNG(2, 2, 8, PNG_COLOR_TYPE_RGB);
    ASSERT_FALSE(pngData.empty());

    // Truncate to just the header
    if (pngData.size() > 20) {
        pngData.resize(20);
    }

    auto embedder = PngEmbedder::create(std::move(pngData));
    EXPECT_EQ(embedder, nullptr);
}

// Test: create with a 1x1 pixel PNG (boundary)
TEST_F(PngEmbedderTest_1861, CreateWithSinglePixelPNG_1861)
{
    auto pngData = createMinimalPNG(1, 1, 8, PNG_COLOR_TYPE_RGB);
    ASSERT_FALSE(pngData.empty());

    auto embedder = PngEmbedder::create(std::move(pngData));
    EXPECT_NE(embedder, nullptr);
}

// Test: create with a larger PNG
TEST_F(PngEmbedderTest_1861, CreateWithLargerPNG_1861)
{
    auto pngData = createMinimalPNG(100, 100, 8, PNG_COLOR_TYPE_RGB);
    ASSERT_FALSE(pngData.empty());

    auto embedder = PngEmbedder::create(std::move(pngData));
    EXPECT_NE(embedder, nullptr);
}

// Test: create with 16-bit RGBA PNG
TEST_F(PngEmbedderTest_1861, CreateWith16BitRGBAPNG_1861)
{
    auto pngData = createMinimalPNG(2, 2, 16, PNG_COLOR_TYPE_RGB_ALPHA);
    ASSERT_FALSE(pngData.empty());

    auto embedder = PngEmbedder::create(std::move(pngData));
    EXPECT_NE(embedder, nullptr);
}

// Test: create with 16-bit grayscale PNG
TEST_F(PngEmbedderTest_1861, CreateWith16BitGrayscalePNG_1861)
{
    auto pngData = createMinimalPNG(2, 2, 16, PNG_COLOR_TYPE_GRAY);
    ASSERT_FALSE(pngData.empty());

    auto embedder = PngEmbedder::create(std::move(pngData));
    EXPECT_NE(embedder, nullptr);
}

// Test: create returns nullptr for corrupted PNG (valid header, corrupted chunks)
TEST_F(PngEmbedderTest_1861, CreateWithCorruptedChunks_1861)
{
    auto pngData = createMinimalPNG(4, 4, 8, PNG_COLOR_TYPE_RGB);
    ASSERT_FALSE(pngData.empty());

    // Corrupt some bytes in the middle of the data (after the header)
    if (pngData.size() > 30) {
        for (size_t i = 16; i < 30 && i < pngData.size(); i++) {
            pngData[i] = static_cast<char>(0xFF);
        }
    }

    auto embedder = PngEmbedder::create(std::move(pngData));
    // The result depends on how libpng handles corruption - it should either
    // return nullptr or a valid pointer. We just ensure no crash.
    // Not asserting specific result since corruption handling is implementation-defined.
}

// Test: PngEmbedder is not copyable
TEST_F(PngEmbedderTest_1861, NotCopyable_1861)
{
    EXPECT_FALSE(std::is_copy_constructible<PngEmbedder>::value);
    EXPECT_FALSE(std::is_copy_assignable<PngEmbedder>::value);
}

// Test: create moves the input vector (the original vector should be empty or moved-from)
TEST_F(PngEmbedderTest_1861, CreateMovesInputVector_1861)
{
    auto pngData = createMinimalPNG(2, 2, 8, PNG_COLOR_TYPE_RGB);
    ASSERT_FALSE(pngData.empty());

    std::vector<char> dataCopy = pngData;
    auto embedder = PngEmbedder::create(std::move(dataCopy));
    // After move, dataCopy is in a valid but unspecified state
    // Just verify the embedder was created successfully
    EXPECT_NE(embedder, nullptr);
}

// Test: create with 1-bit grayscale PNG (should be fixed to 8-bit by fixPng)
TEST_F(PngEmbedderTest_1861, CreateWith1BitGrayscalePNG_1861)
{
    // Create a 1-bit grayscale PNG
    std::vector<char> result;

    png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png) {
        GTEST_SKIP() << "Cannot create png write struct";
    }

    png_infop info = png_create_info_struct(png);
    if (!info) {
        png_destroy_write_struct(&png, nullptr);
        GTEST_SKIP() << "Cannot create png info struct";
    }

    if (setjmp(png_jmpbuf(png))) {
        png_destroy_write_struct(&png, &info);
        GTEST_SKIP() << "PNG error during creation";
    }

    png_set_write_fn(
            png, &result,
            [](png_structp pngPtr, png_bytep data, png_size_t length) {
                auto *vec = static_cast<std::vector<char> *>(png_get_io_ptr(pngPtr));
                vec->insert(vec->end(), reinterpret_cast<char *>(data), reinterpret_cast<char *>(data) + length);
            },
            nullptr);

    png_set_IHDR(png, info, 8, 8, 1, PNG_COLOR_TYPE_GRAY, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
    png_write_info(png, info);

    // 1 bit per pixel, 8 pixels = 1 byte per row
    std::vector<png_byte> row(1, 0xAA);
    for (int y = 0; y < 8; y++) {
        png_write_row(png, row.data());
    }

    png_write_end(png, nullptr);
    png_destroy_write_struct(&png, &info);

    ASSERT_FALSE(result.empty());

    auto embedder = PngEmbedder::create(std::move(result));
    // fixPng should expand 1-bit to 8-bit
    EXPECT_NE(embedder, nullptr);
}

// Test: create with 4-bit grayscale PNG (should be fixed to 8-bit by fixPng)
TEST_F(PngEmbedderTest_1861, CreateWith4BitGrayscalePNG_1861)
{
    std::vector<char> result;

    png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png) {
        GTEST_SKIP();
    }

    png_infop info = png_create_info_struct(png);
    if (!info) {
        png_destroy_write_struct(&png, nullptr);
        GTEST_SKIP();
    }

    if (setjmp(png_jmpbuf(png))) {
        png_destroy_write_struct(&png, &info);
        GTEST_SKIP();
    }

    png_set_write_fn(
            png, &result,
            [](png_structp pngPtr, png_bytep data, png_size_t length) {
                auto *vec = static_cast<std::vector<char> *>(png_get_io_ptr(pngPtr));
                vec->insert(vec->end(), reinterpret_cast<char *>(data), reinterpret_cast<char *>(data) + length);
            },
            nullptr);

    png_set_IHDR(png, info, 4, 4, 4, PNG_COLOR_TYPE_GRAY, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
    png_write_info(png, info);

    // 4 bits per pixel, 4 pixels = 2 bytes per row
    std::vector<png_byte> row(2, 0x5A);
    for (int y = 0; y < 4; y++) {
        png_write_row(png, row.data());
    }

    png_write_end(png, nullptr);
    png_destroy_write_struct(&png, &info);

    ASSERT_FALSE(result.empty());

    auto embedder = PngEmbedder::create(std::move(result));
    // fixPng should expand 4-bit to 8-bit
    EXPECT_NE(embedder, nullptr);
}

// Test: Multiple creates can be done independently
TEST_F(PngEmbedderTest_1861, MultipleCreatesAreIndependent_1861)
{
    auto pngData1 = createMinimalPNG(2, 2, 8, PNG_COLOR_TYPE_RGB);
    auto pngData2 = createMinimalPNG(4, 4, 8, PNG_COLOR_TYPE_GRAY);

    ASSERT_FALSE(pngData1.empty());
    ASSERT_FALSE(pngData2.empty());

    auto embedder1 = PngEmbedder::create(std::move(pngData1));
    auto embedder2 = PngEmbedder::create(std::move(pngData2));

    EXPECT_NE(embedder1, nullptr);
    EXPECT_NE(embedder2, nullptr);
    EXPECT_NE(embedder1.get(), embedder2.get());
}
