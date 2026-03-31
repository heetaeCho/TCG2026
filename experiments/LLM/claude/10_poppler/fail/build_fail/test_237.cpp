#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Stream.h"

// Mock Stream to serve as the underlying stream for RGBGrayEncoder
// We need a concrete Stream implementation to feed data to the encoder.

// Since we're working with the poppler Stream hierarchy, we need to create
// a test helper that provides data to the RGBGrayEncoder.

// MemStream or similar can be used if available. We'll use what's available
// in the poppler codebase.

class RGBGrayEncoderTest_237 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    // Helper to create an RGBGrayEncoder from raw RGB data
    std::unique_ptr<RGBGrayEncoder> createEncoder(const unsigned char* data, int len) {
        // Create a MemStream from the data
        // MemStream takes ownership semantics vary - we need to be careful
        Object obj;
        char* buf = (char*)gmalloc(len);
        memcpy(buf, data, len);
        auto memStream = new MemStream(buf, 0, len, std::move(obj));
        memStream->reset();
        auto encoder = std::make_unique<RGBGrayEncoder>(memStream);
        return encoder;
    }
};

// Test that getKind returns the expected stream kind
TEST_F(RGBGrayEncoderTest_237, GetKind_237) {
    unsigned char data[] = {255, 0, 0}; // One red pixel
    auto encoder = createEncoder(data, sizeof(data));
    encoder->reset();
    StreamKind kind = encoder->getKind();
    // RGBGrayEncoder should report its kind
    EXPECT_EQ(kind, strRGBGray);
}

// Test that isEncoder returns true
TEST_F(RGBGrayEncoderTest_237, IsEncoder_237) {
    unsigned char data[] = {255, 0, 0};
    auto encoder = createEncoder(data, sizeof(data));
    encoder->reset();
    EXPECT_TRUE(encoder->isEncoder());
}

// Test that isBinary returns the expected value
TEST_F(RGBGrayEncoderTest_237, IsBinary_237) {
    unsigned char data[] = {255, 0, 0};
    auto encoder = createEncoder(data, sizeof(data));
    encoder->reset();
    // Encoder may or may not be binary
    bool result = encoder->isBinary(true);
    // Just check it doesn't crash; the actual value depends on implementation
    (void)result;
}

// Test that getPSFilter returns nullopt (encoders typically don't have PS filters)
TEST_F(RGBGrayEncoderTest_237, GetPSFilter_237) {
    unsigned char data[] = {255, 0, 0};
    auto encoder = createEncoder(data, sizeof(data));
    encoder->reset();
    auto filter = encoder->getPSFilter(1, "");
    // Encoders typically return nullopt
    EXPECT_FALSE(filter.has_value());
}

// Test encoding a single white pixel (255, 255, 255) -> should produce gray 255
TEST_F(RGBGrayEncoderTest_237, SingleWhitePixel_237) {
    unsigned char data[] = {255, 255, 255};
    auto encoder = createEncoder(data, sizeof(data));
    encoder->reset();
    int ch = encoder->getChar();
    EXPECT_NE(ch, EOF);
    // White RGB should map to white gray (255)
    EXPECT_EQ(ch, 255);
    // After one pixel, should get EOF
    int ch2 = encoder->getChar();
    EXPECT_EQ(ch2, EOF);
}

// Test encoding a single black pixel (0, 0, 0) -> should produce gray 0
TEST_F(RGBGrayEncoderTest_237, SingleBlackPixel_237) {
    unsigned char data[] = {0, 0, 0};
    auto encoder = createEncoder(data, sizeof(data));
    encoder->reset();
    int ch = encoder->getChar();
    EXPECT_EQ(ch, 0);
    int ch2 = encoder->getChar();
    EXPECT_EQ(ch2, EOF);
}

// Test encoding a red pixel (255, 0, 0)
// Standard luminance: 0.299*R + 0.587*G + 0.114*B
// For (255, 0, 0): 0.299*255 = 76.245 -> approximately 76
TEST_F(RGBGrayEncoderTest_237, SingleRedPixel_237) {
    unsigned char data[] = {255, 0, 0};
    auto encoder = createEncoder(data, sizeof(data));
    encoder->reset();
    int ch = encoder->getChar();
    EXPECT_NE(ch, EOF);
    // Red should map to approximately 76 (depending on exact formula)
    EXPECT_GE(ch, 70);
    EXPECT_LE(ch, 85);
}

// Test encoding a green pixel (0, 255, 0)
// For (0, 255, 0): 0.587*255 = 149.685 -> approximately 150
TEST_F(RGBGrayEncoderTest_237, SingleGreenPixel_237) {
    unsigned char data[] = {0, 255, 0};
    auto encoder = createEncoder(data, sizeof(data));
    encoder->reset();
    int ch = encoder->getChar();
    EXPECT_NE(ch, EOF);
    EXPECT_GE(ch, 140);
    EXPECT_LE(ch, 160);
}

// Test encoding a blue pixel (0, 0, 255)
// For (0, 0, 255): 0.114*255 = 29.07 -> approximately 29
TEST_F(RGBGrayEncoderTest_237, SingleBluePixel_237) {
    unsigned char data[] = {0, 0, 255};
    auto encoder = createEncoder(data, sizeof(data));
    encoder->reset();
    int ch = encoder->getChar();
    EXPECT_NE(ch, EOF);
    EXPECT_GE(ch, 25);
    EXPECT_LE(ch, 35);
}

// Test encoding multiple pixels
TEST_F(RGBGrayEncoderTest_237, MultiplePixels_237) {
    unsigned char data[] = {
        255, 255, 255,  // white
        0, 0, 0,        // black
        128, 128, 128   // gray
    };
    auto encoder = createEncoder(data, sizeof(data));
    encoder->reset();

    int ch1 = encoder->getChar();
    EXPECT_EQ(ch1, 255); // white

    int ch2 = encoder->getChar();
    EXPECT_EQ(ch2, 0); // black

    int ch3 = encoder->getChar();
    EXPECT_NE(ch3, EOF);
    // (128, 128, 128) should map to approximately 128
    EXPECT_GE(ch3, 125);
    EXPECT_LE(ch3, 131);

    int ch4 = encoder->getChar();
    EXPECT_EQ(ch4, EOF);
}

// Test empty stream returns EOF immediately
TEST_F(RGBGrayEncoderTest_237, EmptyStream_237) {
    unsigned char data[] = {};
    Object obj;
    auto memStream = new MemStream(nullptr, 0, 0, std::move(obj));
    memStream->reset();
    RGBGrayEncoder encoder(memStream);
    encoder.reset();
    int ch = encoder.getChar();
    EXPECT_EQ(ch, EOF);
}

// Test lookChar doesn't consume the character
TEST_F(RGBGrayEncoderTest_237, LookCharDoesNotConsume_237) {
    unsigned char data[] = {255, 255, 255};
    auto encoder = createEncoder(data, sizeof(data));
    encoder->reset();

    int looked = encoder->lookChar();
    int got = encoder->getChar();
    EXPECT_EQ(looked, got);
    EXPECT_EQ(looked, 255);
}

// Test lookChar returns EOF on empty
TEST_F(RGBGrayEncoderTest_237, LookCharEOFOnEmpty_237) {
    Object obj;
    auto memStream = new MemStream(nullptr, 0, 0, std::move(obj));
    memStream->reset();
    RGBGrayEncoder encoder(memStream);
    encoder.reset();
    int looked = encoder.lookChar();
    EXPECT_EQ(looked, EOF);
}

// Test rewind and re-read
TEST_F(RGBGrayEncoderTest_237, RewindAndReread_237) {
    unsigned char data[] = {100, 150, 200};
    auto encoder = createEncoder(data, sizeof(data));
    encoder->reset();

    int first_read = encoder->getChar();
    EXPECT_NE(first_read, EOF);

    // After reading, should get EOF
    int eof_check = encoder->getChar();
    EXPECT_EQ(eof_check, EOF);

    // Rewind and read again
    bool rewound = encoder->reset();
    int second_read = encoder->getChar();
    EXPECT_EQ(first_read, second_read);
}

// Test that getChar returns values in 0-255 range
TEST_F(RGBGrayEncoderTest_237, OutputInValidRange_237) {
    unsigned char data[] = {
        0, 0, 0,
        255, 255, 255,
        128, 64, 32,
        200, 100, 50,
        10, 20, 30
    };
    auto encoder = createEncoder(data, sizeof(data));
    encoder->reset();

    for (int i = 0; i < 5; i++) {
        int ch = encoder->getChar();
        ASSERT_NE(ch, EOF) << "Unexpected EOF at pixel " << i;
        EXPECT_GE(ch, 0);
        EXPECT_LE(ch, 255);
    }
    EXPECT_EQ(encoder->getChar(), EOF);
}

// Test with incomplete pixel data (only 1 or 2 bytes instead of 3)
// The behavior depends on implementation - it may produce EOF or partial result
TEST_F(RGBGrayEncoderTest_237, IncompletePixelData_237) {
    // Only 2 bytes - not enough for a full RGB triple
    unsigned char data[] = {128, 64};
    auto encoder = createEncoder(data, sizeof(data));
    encoder->reset();

    // Implementation may handle this differently - just ensure no crash
    int ch = encoder->getChar();
    // Could be EOF or some value - just don't crash
    (void)ch;
}

// Test with a larger dataset
TEST_F(RGBGrayEncoderTest_237, LargerDataset_237) {
    const int numPixels = 1000;
    const int dataSize = numPixels * 3;
    unsigned char* data = new unsigned char[dataSize];
    for (int i = 0; i < dataSize; i++) {
        data[i] = (unsigned char)(i % 256);
    }

    auto encoder = createEncoder(data, dataSize);
    encoder->reset();

    int count = 0;
    while (encoder->getChar() != EOF) {
        count++;
    }
    // Should produce exactly numPixels gray values
    EXPECT_EQ(count, numPixels);

    delete[] data;
}

// Test that gray (128, 128, 128) maps to approximately 128
TEST_F(RGBGrayEncoderTest_237, NeutralGrayMapping_237) {
    unsigned char data[] = {128, 128, 128};
    auto encoder = createEncoder(data, sizeof(data));
    encoder->reset();
    int ch = encoder->getChar();
    // Neutral gray should map to itself approximately
    // 0.299*128 + 0.587*128 + 0.114*128 = 128
    EXPECT_GE(ch, 126);
    EXPECT_LE(ch, 130);
}
