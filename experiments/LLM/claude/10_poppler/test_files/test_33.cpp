#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "TiffWriter.h"

// We need to know the Format enum. Based on typical TiffWriter implementations:
// Format::RGB, Format::GRAY8, Format::CMYK, Format::MONOCHROME, etc.
// We'll use what's available from the header.

class TiffWriterTest_33 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    // Helper to create a temporary file
    FILE* createTempFile() {
        return tmpfile();
    }
};

// Test that TiffWriter supports CMYK
TEST_F(TiffWriterTest_33, SupportsCMYK_33) {
    TiffWriter writer(TiffWriter::RGB);
    EXPECT_TRUE(writer.supportCMYK());
}

// Test construction with RGB format
TEST_F(TiffWriterTest_33, ConstructWithRGB_33) {
    TiffWriter writer(TiffWriter::RGB);
    EXPECT_TRUE(writer.supportCMYK());
}

// Test construction with CMYK format
TEST_F(TiffWriterTest_33, ConstructWithCMYK_33) {
    TiffWriter writer(TiffWriter::CMYK);
    EXPECT_TRUE(writer.supportCMYK());
}

// Test construction with GRAY8 format
TEST_F(TiffWriterTest_33, ConstructWithGRAY8_33) {
    TiffWriter writer(TiffWriter::GRAY8);
    EXPECT_TRUE(writer.supportCMYK());
}

// Test construction with MONOCHROME format
TEST_F(TiffWriterTest_33, ConstructWithMONOCHROME_33) {
    TiffWriter writer(TiffWriter::MONOCHROME);
    EXPECT_TRUE(writer.supportCMYK());
}

// Test init with valid parameters (RGB)
TEST_F(TiffWriterTest_33, InitWithValidParamsRGB_33) {
    TiffWriter writer(TiffWriter::RGB);
    FILE* f = createTempFile();
    ASSERT_NE(f, nullptr);
    bool result = writer.init(f, 100, 100, 72.0, 72.0);
    EXPECT_TRUE(result);
    writer.close();
    fclose(f);
}

// Test init with valid parameters (CMYK)
TEST_F(TiffWriterTest_33, InitWithValidParamsCMYK_33) {
    TiffWriter writer(TiffWriter::CMYK);
    FILE* f = createTempFile();
    ASSERT_NE(f, nullptr);
    bool result = writer.init(f, 100, 100, 72.0, 72.0);
    EXPECT_TRUE(result);
    writer.close();
    fclose(f);
}

// Test init with nullptr file
TEST_F(TiffWriterTest_33, InitWithNullFile_33) {
    TiffWriter writer(TiffWriter::RGB);
    bool result = writer.init(nullptr, 100, 100, 72.0, 72.0);
    EXPECT_FALSE(result);
}

// Test init with zero width
TEST_F(TiffWriterTest_33, InitWithZeroWidth_33) {
    TiffWriter writer(TiffWriter::RGB);
    FILE* f = createTempFile();
    ASSERT_NE(f, nullptr);
    bool result = writer.init(f, 0, 100, 72.0, 72.0);
    // Zero width might fail or succeed depending on implementation
    writer.close();
    fclose(f);
}

// Test init with zero height
TEST_F(TiffWriterTest_33, InitWithZeroHeight_33) {
    TiffWriter writer(TiffWriter::RGB);
    FILE* f = createTempFile();
    ASSERT_NE(f, nullptr);
    bool result = writer.init(f, 100, 0, 72.0, 72.0);
    writer.close();
    fclose(f);
}

// Test writeRow with valid data after init (RGB)
TEST_F(TiffWriterTest_33, WriteRowRGB_33) {
    TiffWriter writer(TiffWriter::RGB);
    FILE* f = createTempFile();
    ASSERT_NE(f, nullptr);

    int width = 10;
    int height = 10;
    bool initResult = writer.init(f, width, height, 72.0, 72.0);
    ASSERT_TRUE(initResult);

    // RGB: 3 bytes per pixel
    unsigned char rowData[30];
    memset(rowData, 128, sizeof(rowData));
    unsigned char* rowPtr = rowData;

    bool writeResult = writer.writeRow(&rowPtr);
    EXPECT_TRUE(writeResult);

    writer.close();
    fclose(f);
}

// Test writePointers with valid data (RGB)
TEST_F(TiffWriterTest_33, WritePointersRGB_33) {
    TiffWriter writer(TiffWriter::RGB);
    FILE* f = createTempFile();
    ASSERT_NE(f, nullptr);

    int width = 10;
    int height = 5;
    bool initResult = writer.init(f, width, height, 72.0, 72.0);
    ASSERT_TRUE(initResult);

    // RGB: 3 bytes per pixel
    unsigned char rows[5][30];
    unsigned char* rowPtrs[5];
    for (int i = 0; i < 5; i++) {
        memset(rows[i], (i * 50) % 256, sizeof(rows[i]));
        rowPtrs[i] = rows[i];
    }

    bool writeResult = writer.writePointers(rowPtrs, 5);
    EXPECT_TRUE(writeResult);

    writer.close();
    fclose(f);
}

// Test writeRow with CMYK format
TEST_F(TiffWriterTest_33, WriteRowCMYK_33) {
    TiffWriter writer(TiffWriter::CMYK);
    FILE* f = createTempFile();
    ASSERT_NE(f, nullptr);

    int width = 10;
    int height = 10;
    bool initResult = writer.init(f, width, height, 72.0, 72.0);
    ASSERT_TRUE(initResult);

    // CMYK: 4 bytes per pixel
    unsigned char rowData[40];
    memset(rowData, 100, sizeof(rowData));
    unsigned char* rowPtr = rowData;

    bool writeResult = writer.writeRow(&rowPtr);
    EXPECT_TRUE(writeResult);

    writer.close();
    fclose(f);
}

// Test writeRow with GRAY8 format
TEST_F(TiffWriterTest_33, WriteRowGRAY8_33) {
    TiffWriter writer(TiffWriter::GRAY8);
    FILE* f = createTempFile();
    ASSERT_NE(f, nullptr);

    int width = 10;
    int height = 10;
    bool initResult = writer.init(f, width, height, 72.0, 72.0);
    ASSERT_TRUE(initResult);

    // GRAY8: 1 byte per pixel
    unsigned char rowData[10];
    memset(rowData, 200, sizeof(rowData));
    unsigned char* rowPtr = rowData;

    bool writeResult = writer.writeRow(&rowPtr);
    EXPECT_TRUE(writeResult);

    writer.close();
    fclose(f);
}

// Test writeRow with MONOCHROME format
TEST_F(TiffWriterTest_33, WriteRowMONOCHROME_33) {
    TiffWriter writer(TiffWriter::MONOCHROME);
    FILE* f = createTempFile();
    ASSERT_NE(f, nullptr);

    int width = 80;
    int height = 10;
    bool initResult = writer.init(f, width, height, 72.0, 72.0);
    ASSERT_TRUE(initResult);

    // Monochrome: 1 bit per pixel, 80 pixels = 10 bytes
    unsigned char rowData[10];
    memset(rowData, 0xAA, sizeof(rowData));
    unsigned char* rowPtr = rowData;

    bool writeResult = writer.writeRow(&rowPtr);
    EXPECT_TRUE(writeResult);

    writer.close();
    fclose(f);
}

// Test close without init
TEST_F(TiffWriterTest_33, CloseWithoutInit_33) {
    TiffWriter writer(TiffWriter::RGB);
    bool result = writer.close();
    EXPECT_TRUE(result);
}

// Test setCompressionString
TEST_F(TiffWriterTest_33, SetCompressionString_33) {
    TiffWriter writer(TiffWriter::RGB);
    writer.setCompressionString("none");
    FILE* f = createTempFile();
    ASSERT_NE(f, nullptr);
    bool initResult = writer.init(f, 10, 10, 72.0, 72.0);
    EXPECT_TRUE(initResult);
    writer.close();
    fclose(f);
}

// Test setCompressionString with lzw
TEST_F(TiffWriterTest_33, SetCompressionStringLZW_33) {
    TiffWriter writer(TiffWriter::RGB);
    writer.setCompressionString("lzw");
    FILE* f = createTempFile();
    ASSERT_NE(f, nullptr);
    bool initResult = writer.init(f, 10, 10, 72.0, 72.0);
    EXPECT_TRUE(initResult);
    writer.close();
    fclose(f);
}

// Test setCompressionString with jpeg
TEST_F(TiffWriterTest_33, SetCompressionStringJPEG_33) {
    TiffWriter writer(TiffWriter::RGB);
    writer.setCompressionString("jpeg");
    FILE* f = createTempFile();
    ASSERT_NE(f, nullptr);
    bool initResult = writer.init(f, 10, 10, 72.0, 72.0);
    EXPECT_TRUE(initResult);
    writer.close();
    fclose(f);
}

// Test setCompressionString with deflate
TEST_F(TiffWriterTest_33, SetCompressionStringDeflate_33) {
    TiffWriter writer(TiffWriter::RGB);
    writer.setCompressionString("deflate");
    FILE* f = createTempFile();
    ASSERT_NE(f, nullptr);
    bool initResult = writer.init(f, 10, 10, 72.0, 72.0);
    EXPECT_TRUE(initResult);
    writer.close();
    fclose(f);
}

// Test writing all rows
TEST_F(TiffWriterTest_33, WriteAllRowsRGB_33) {
    TiffWriter writer(TiffWriter::RGB);
    FILE* f = createTempFile();
    ASSERT_NE(f, nullptr);

    int width = 5;
    int height = 3;
    bool initResult = writer.init(f, width, height, 96.0, 96.0);
    ASSERT_TRUE(initResult);

    unsigned char rowData[15]; // 5 pixels * 3 channels
    memset(rowData, 255, sizeof(rowData));
    unsigned char* rowPtr = rowData;

    for (int i = 0; i < height; i++) {
        bool writeResult = writer.writeRow(&rowPtr);
        EXPECT_TRUE(writeResult);
    }

    bool closeResult = writer.close();
    EXPECT_TRUE(closeResult);
    fclose(f);
}

// Test writing all rows using writePointers
TEST_F(TiffWriterTest_33, WriteAllRowsViaPointers_33) {
    TiffWriter writer(TiffWriter::RGB);
    FILE* f = createTempFile();
    ASSERT_NE(f, nullptr);

    int width = 5;
    int height = 3;
    bool initResult = writer.init(f, width, height, 96.0, 96.0);
    ASSERT_TRUE(initResult);

    unsigned char rows[3][15];
    unsigned char* rowPtrs[3];
    for (int i = 0; i < 3; i++) {
        memset(rows[i], i * 80, 15);
        rowPtrs[i] = rows[i];
    }

    bool writeResult = writer.writePointers(rowPtrs, 3);
    EXPECT_TRUE(writeResult);

    bool closeResult = writer.close();
    EXPECT_TRUE(closeResult);
    fclose(f);
}

// Test with large dimensions
TEST_F(TiffWriterTest_33, InitWithLargeDimensions_33) {
    TiffWriter writer(TiffWriter::RGB);
    FILE* f = createTempFile();
    ASSERT_NE(f, nullptr);
    bool result = writer.init(f, 10000, 10000, 300.0, 300.0);
    EXPECT_TRUE(result);
    writer.close();
    fclose(f);
}

// Test with 1x1 image
TEST_F(TiffWriterTest_33, InitWithMinimalDimensions_33) {
    TiffWriter writer(TiffWriter::RGB);
    FILE* f = createTempFile();
    ASSERT_NE(f, nullptr);
    bool initResult = writer.init(f, 1, 1, 72.0, 72.0);
    ASSERT_TRUE(initResult);

    unsigned char rowData[3] = {255, 0, 0};
    unsigned char* rowPtr = rowData;
    bool writeResult = writer.writeRow(&rowPtr);
    EXPECT_TRUE(writeResult);

    bool closeResult = writer.close();
    EXPECT_TRUE(closeResult);
    fclose(f);
}

// Test that copy constructor is deleted
TEST_F(TiffWriterTest_33, CopyConstructorDeleted_33) {
    EXPECT_FALSE(std::is_copy_constructible<TiffWriter>::value);
}

// Test that copy assignment is deleted
TEST_F(TiffWriterTest_33, CopyAssignmentDeleted_33) {
    EXPECT_FALSE(std::is_copy_assignable<TiffWriter>::value);
}

// Test with different DPI values
TEST_F(TiffWriterTest_33, InitWithHighDPI_33) {
    TiffWriter writer(TiffWriter::RGB);
    FILE* f = createTempFile();
    ASSERT_NE(f, nullptr);
    bool result = writer.init(f, 100, 100, 600.0, 600.0);
    EXPECT_TRUE(result);
    writer.close();
    fclose(f);
}

// Test with asymmetric DPI
TEST_F(TiffWriterTest_33, InitWithAsymmetricDPI_33) {
    TiffWriter writer(TiffWriter::RGB);
    FILE* f = createTempFile();
    ASSERT_NE(f, nullptr);
    bool result = writer.init(f, 100, 100, 72.0, 300.0);
    EXPECT_TRUE(result);
    writer.close();
    fclose(f);
}

// Test setCompressionString with nullptr
TEST_F(TiffWriterTest_33, SetCompressionStringNull_33) {
    TiffWriter writer(TiffWriter::RGB);
    writer.setCompressionString(nullptr);
    FILE* f = createTempFile();
    ASSERT_NE(f, nullptr);
    bool initResult = writer.init(f, 10, 10, 72.0, 72.0);
    EXPECT_TRUE(initResult);
    writer.close();
    fclose(f);
}

// Test negative dimensions
TEST_F(TiffWriterTest_33, InitWithNegativeWidth_33) {
    TiffWriter writer(TiffWriter::RGB);
    FILE* f = createTempFile();
    ASSERT_NE(f, nullptr);
    bool result = writer.init(f, -1, 100, 72.0, 72.0);
    // Negative width should likely fail
    writer.close();
    fclose(f);
}

// Test negative height
TEST_F(TiffWriterTest_33, InitWithNegativeHeight_33) {
    TiffWriter writer(TiffWriter::RGB);
    FILE* f = createTempFile();
    ASSERT_NE(f, nullptr);
    bool result = writer.init(f, 100, -1, 72.0, 72.0);
    writer.close();
    fclose(f);
}
