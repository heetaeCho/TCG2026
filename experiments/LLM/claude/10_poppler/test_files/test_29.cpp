#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstring>
#include <cstdio>
#include <vector>

// Include the JpegWriter header
#include "goo/JpegWriter.h"

class JpegWriterTest_29 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
        // Clean up any temp files
        std::remove(tmpFilename_.c_str());
    }

    std::string tmpFilename_ = "test_jpeg_output_29.jpg";

    // Helper to create a simple RGB row
    std::vector<unsigned char> createRGBRow(int width) {
        std::vector<unsigned char> row(width * 3);
        for (int i = 0; i < width * 3; i += 3) {
            row[i] = 255;     // R
            row[i + 1] = 0;   // G
            row[i + 2] = 0;   // B
        }
        return row;
    }

    // Helper to create a grayscale row
    std::vector<unsigned char> createGrayRow(int width) {
        std::vector<unsigned char> row(width);
        for (int i = 0; i < width; i++) {
            row[i] = 128;
        }
        return row;
    }
};

// Test default construction
TEST_F(JpegWriterTest_29, DefaultConstruction_29) {
    JpegWriter writer;
    // Default construction should succeed without throwing
    SUCCEED();
}

// Test construction with quality parameter
TEST_F(JpegWriterTest_29, ConstructionWithQuality_29) {
    JpegWriter writer(75);
    SUCCEED();
}

// Test construction with different quality values
TEST_F(JpegWriterTest_29, ConstructionWithMinQuality_29) {
    JpegWriter writer(0);
    SUCCEED();
}

TEST_F(JpegWriterTest_29, ConstructionWithMaxQuality_29) {
    JpegWriter writer(100);
    SUCCEED();
}

// Test basic RGB image writing workflow
TEST_F(JpegWriterTest_29, WriteBasicRGBImage_29) {
    JpegWriter writer;
    
    FILE *f = fopen(tmpFilename_.c_str(), "wb");
    ASSERT_NE(f, nullptr);
    
    bool initResult = writer.init(f, 10, 10, 3);
    EXPECT_TRUE(initResult);
    
    auto row = createRGBRow(10);
    for (int y = 0; y < 10; y++) {
        bool writeResult = writer.writeRow(row.data());
        EXPECT_TRUE(writeResult);
    }
    
    bool closeResult = writer.close();
    EXPECT_TRUE(closeResult);
    
    fclose(f);
    
    // Verify file is not empty
    FILE *fRead = fopen(tmpFilename_.c_str(), "rb");
    ASSERT_NE(fRead, nullptr);
    fseek(fRead, 0, SEEK_END);
    long fileSize = ftell(fRead);
    EXPECT_GT(fileSize, 0);
    fclose(fRead);
}

// Test grayscale image writing
TEST_F(JpegWriterTest_29, WriteGrayscaleImage_29) {
    JpegWriter writer;
    
    FILE *f = fopen(tmpFilename_.c_str(), "wb");
    ASSERT_NE(f, nullptr);
    
    bool initResult = writer.init(f, 8, 8, 1);
    EXPECT_TRUE(initResult);
    
    auto row = createGrayRow(8);
    for (int y = 0; y < 8; y++) {
        bool writeResult = writer.writeRow(row.data());
        EXPECT_TRUE(writeResult);
    }
    
    bool closeResult = writer.close();
    EXPECT_TRUE(closeResult);
    
    fclose(f);
}

// Test writing with specific quality
TEST_F(JpegWriterTest_29, WriteWithHighQuality_29) {
    JpegWriter writer(100);
    
    FILE *f = fopen(tmpFilename_.c_str(), "wb");
    ASSERT_NE(f, nullptr);
    
    bool initResult = writer.init(f, 4, 4, 3);
    EXPECT_TRUE(initResult);
    
    auto row = createRGBRow(4);
    for (int y = 0; y < 4; y++) {
        EXPECT_TRUE(writer.writeRow(row.data()));
    }
    
    EXPECT_TRUE(writer.close());
    fclose(f);
}

// Test writing with low quality
TEST_F(JpegWriterTest_29, WriteWithLowQuality_29) {
    JpegWriter writer(1);
    
    FILE *f = fopen(tmpFilename_.c_str(), "wb");
    ASSERT_NE(f, nullptr);
    
    bool initResult = writer.init(f, 4, 4, 3);
    EXPECT_TRUE(initResult);
    
    auto row = createRGBRow(4);
    for (int y = 0; y < 4; y++) {
        EXPECT_TRUE(writer.writeRow(row.data()));
    }
    
    EXPECT_TRUE(writer.close());
    fclose(f);
}

// Test single pixel image (boundary)
TEST_F(JpegWriterTest_29, WriteSinglePixelImage_29) {
    JpegWriter writer;
    
    FILE *f = fopen(tmpFilename_.c_str(), "wb");
    ASSERT_NE(f, nullptr);
    
    bool initResult = writer.init(f, 1, 1, 3);
    EXPECT_TRUE(initResult);
    
    unsigned char pixel[3] = {255, 128, 0};
    EXPECT_TRUE(writer.writeRow(pixel));
    
    EXPECT_TRUE(writer.close());
    fclose(f);
}

// Test larger image
TEST_F(JpegWriterTest_29, WriteLargerImage_29) {
    JpegWriter writer(90);
    
    FILE *f = fopen(tmpFilename_.c_str(), "wb");
    ASSERT_NE(f, nullptr);
    
    int width = 256;
    int height = 256;
    bool initResult = writer.init(f, width, height, 3);
    EXPECT_TRUE(initResult);
    
    auto row = createRGBRow(width);
    for (int y = 0; y < height; y++) {
        EXPECT_TRUE(writer.writeRow(row.data()));
    }
    
    EXPECT_TRUE(writer.close());
    fclose(f);
    
    // Verify file was written and has reasonable size
    FILE *fRead = fopen(tmpFilename_.c_str(), "rb");
    ASSERT_NE(fRead, nullptr);
    fseek(fRead, 0, SEEK_END);
    long fileSize = ftell(fRead);
    EXPECT_GT(fileSize, 0);
    fclose(fRead);
}

// Test JPEG file starts with correct magic bytes (SOI marker)
TEST_F(JpegWriterTest_29, OutputHasJPEGMagicBytes_29) {
    JpegWriter writer;
    
    FILE *f = fopen(tmpFilename_.c_str(), "wb");
    ASSERT_NE(f, nullptr);
    
    writer.init(f, 2, 2, 3);
    
    auto row = createRGBRow(2);
    for (int y = 0; y < 2; y++) {
        writer.writeRow(row.data());
    }
    writer.close();
    fclose(f);
    
    // Check JPEG SOI marker (0xFF 0xD8)
    FILE *fRead = fopen(tmpFilename_.c_str(), "rb");
    ASSERT_NE(fRead, nullptr);
    unsigned char header[2];
    size_t read = fread(header, 1, 2, fRead);
    EXPECT_EQ(read, 2u);
    EXPECT_EQ(header[0], 0xFF);
    EXPECT_EQ(header[1], 0xD8);
    fclose(fRead);
}

// Test that higher quality produces larger file than lower quality
TEST_F(JpegWriterTest_29, HigherQualityProducesLargerFile_29) {
    std::string lowQualFile = "test_lowq_29.jpg";
    std::string highQualFile = "test_highq_29.jpg";
    
    int width = 64;
    int height = 64;
    
    // Create varied pixel data
    std::vector<unsigned char> row(width * 3);
    for (int i = 0; i < width * 3; i++) {
        row[i] = static_cast<unsigned char>(i % 256);
    }
    
    // Write low quality
    {
        JpegWriter writer(10);
        FILE *f = fopen(lowQualFile.c_str(), "wb");
        ASSERT_NE(f, nullptr);
        writer.init(f, width, height, 3);
        for (int y = 0; y < height; y++) {
            writer.writeRow(row.data());
        }
        writer.close();
        fclose(f);
    }
    
    // Write high quality
    {
        JpegWriter writer(100);
        FILE *f = fopen(highQualFile.c_str(), "wb");
        ASSERT_NE(f, nullptr);
        writer.init(f, width, height, 3);
        for (int y = 0; y < height; y++) {
            writer.writeRow(row.data());
        }
        writer.close();
        fclose(f);
    }
    
    // Compare sizes
    FILE *fLow = fopen(lowQualFile.c_str(), "rb");
    ASSERT_NE(fLow, nullptr);
    fseek(fLow, 0, SEEK_END);
    long lowSize = ftell(fLow);
    fclose(fLow);
    
    FILE *fHigh = fopen(highQualFile.c_str(), "rb");
    ASSERT_NE(fHigh, nullptr);
    fseek(fHigh, 0, SEEK_END);
    long highSize = ftell(fHigh);
    fclose(fHigh);
    
    EXPECT_GT(highSize, lowSize);
    
    std::remove(lowQualFile.c_str());
    std::remove(highQualFile.c_str());
}

// Test writing with progressive mode if supported
TEST_F(JpegWriterTest_29, WriteProgressiveImage_29) {
    JpegWriter writer;
    writer.setProgressive(true);
    
    FILE *f = fopen(tmpFilename_.c_str(), "wb");
    ASSERT_NE(f, nullptr);
    
    bool initResult = writer.init(f, 16, 16, 3);
    EXPECT_TRUE(initResult);
    
    auto row = createRGBRow(16);
    for (int y = 0; y < 16; y++) {
        EXPECT_TRUE(writer.writeRow(row.data()));
    }
    
    EXPECT_TRUE(writer.close());
    fclose(f);
}

// Test non-progressive mode
TEST_F(JpegWriterTest_29, WriteNonProgressiveImage_29) {
    JpegWriter writer;
    writer.setProgressive(false);
    
    FILE *f = fopen(tmpFilename_.c_str(), "wb");
    ASSERT_NE(f, nullptr);
    
    bool initResult = writer.init(f, 16, 16, 3);
    EXPECT_TRUE(initResult);
    
    auto row = createRGBRow(16);
    for (int y = 0; y < 16; y++) {
        EXPECT_TRUE(writer.writeRow(row.data()));
    }
    
    EXPECT_TRUE(writer.close());
    fclose(f);
}

// Test wide but short image
TEST_F(JpegWriterTest_29, WriteWideShortImage_29) {
    JpegWriter writer;
    
    FILE *f = fopen(tmpFilename_.c_str(), "wb");
    ASSERT_NE(f, nullptr);
    
    int width = 1000;
    int height = 1;
    bool initResult = writer.init(f, width, height, 3);
    EXPECT_TRUE(initResult);
    
    auto row = createRGBRow(width);
    EXPECT_TRUE(writer.writeRow(row.data()));
    
    EXPECT_TRUE(writer.close());
    fclose(f);
}

// Test narrow but tall image
TEST_F(JpegWriterTest_29, WriteNarrowTallImage_29) {
    JpegWriter writer;
    
    FILE *f = fopen(tmpFilename_.c_str(), "wb");
    ASSERT_NE(f, nullptr);
    
    int width = 1;
    int height = 100;
    bool initResult = writer.init(f, width, height, 3);
    EXPECT_TRUE(initResult);
    
    unsigned char pixel[3] = {100, 200, 50};
    for (int y = 0; y < height; y++) {
        EXPECT_TRUE(writer.writeRow(pixel));
    }
    
    EXPECT_TRUE(writer.close());
    fclose(f);
}

// Test with all black pixels
TEST_F(JpegWriterTest_29, WriteAllBlackImage_29) {
    JpegWriter writer;
    
    FILE *f = fopen(tmpFilename_.c_str(), "wb");
    ASSERT_NE(f, nullptr);
    
    int width = 16;
    int height = 16;
    writer.init(f, width, height, 3);
    
    std::vector<unsigned char> row(width * 3, 0);
    for (int y = 0; y < height; y++) {
        EXPECT_TRUE(writer.writeRow(row.data()));
    }
    
    EXPECT_TRUE(writer.close());
    fclose(f);
}

// Test with all white pixels
TEST_F(JpegWriterTest_29, WriteAllWhiteImage_29) {
    JpegWriter writer;
    
    FILE *f = fopen(tmpFilename_.c_str(), "wb");
    ASSERT_NE(f, nullptr);
    
    int width = 16;
    int height = 16;
    writer.init(f, width, height, 3);
    
    std::vector<unsigned char> row(width * 3, 255);
    for (int y = 0; y < height; y++) {
        EXPECT_TRUE(writer.writeRow(row.data()));
    }
    
    EXPECT_TRUE(writer.close());
    fclose(f);
}
