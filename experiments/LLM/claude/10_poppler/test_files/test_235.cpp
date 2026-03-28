#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Stream.h"
#include <memory>

// We need a concrete Stream to feed into CMYKGrayEncoder.
// MemStream is typically available in poppler for this purpose.

class CMYKGrayEncoderTest_235 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    // Helper to create a MemStream from CMYK data
    // Each CMYK pixel is 4 bytes (C, M, Y, K)
    std::unique_ptr<MemStream> createMemStream(const char* data, int length) {
        // MemStream takes ownership semantics vary; we copy data
        char* buf = (char*)gmalloc(length);
        memcpy(buf, data, length);
        Object obj;
        auto stream = std::make_unique<MemStream>(buf, 0, length, Object(objNull));
        return stream;
    }
};

// Test that isEncoder returns true
TEST_F(CMYKGrayEncoderTest_235, IsEncoderReturnsTrue_235) {
    // Create a minimal CMYK stream (4 bytes = 1 pixel)
    const char cmykData[] = {0, 0, 0, 0};
    auto memStream = createMemStream(cmykData, 4);
    CMYKGrayEncoder encoder(memStream.get());
    
    EXPECT_TRUE(encoder.isEncoder());
}

// Test getKind returns the expected stream kind
TEST_F(CMYKGrayEncoderTest_235, GetKindReturnsCorrectKind_235) {
    const char cmykData[] = {0, 0, 0, 0};
    auto memStream = createMemStream(cmykData, 4);
    CMYKGrayEncoder encoder(memStream.get());
    
    StreamKind kind = encoder.getKind();
    // CMYKGrayEncoder should have a specific kind; we verify it's valid
    // Based on poppler, it should be strWeird or a specific encoder kind
    EXPECT_EQ(kind, strWeird);
}

// Test that getPSFilter returns nullopt (encoders typically don't support PS filters)
TEST_F(CMYKGrayEncoderTest_235, GetPSFilterReturnsNullopt_235) {
    const char cmykData[] = {0, 0, 0, 0};
    auto memStream = createMemStream(cmykData, 4);
    CMYKGrayEncoder encoder(memStream.get());
    
    auto result = encoder.getPSFilter(1, "");
    EXPECT_FALSE(result.has_value());
}

// Test isBinary
TEST_F(CMYKGrayEncoderTest_235, IsBinaryReturnsFalse_235) {
    const char cmykData[] = {0, 0, 0, 0};
    auto memStream = createMemStream(cmykData, 4);
    CMYKGrayEncoder encoder(memStream.get());
    
    // Test isBinary behavior
    bool binary = encoder.isBinary(true);
    EXPECT_FALSE(binary);
}

// Test reading from a stream with all zeros (pure white in CMYK -> gray value)
TEST_F(CMYKGrayEncoderTest_235, AllZeroCMYKProducesWhiteGray_235) {
    // CMYK (0,0,0,0) means no ink = white = gray 255
    const char cmykData[] = {0, 0, 0, 0};
    auto memStream = createMemStream(cmykData, 4);
    CMYKGrayEncoder encoder(memStream.get());
    
    encoder.reset();
    
    int ch = encoder.getChar();
    EXPECT_GE(ch, 0);
    EXPECT_LE(ch, 255);
    // For CMYK (0,0,0,0) -> gray should be 255 (white)
    EXPECT_EQ(ch, 255);
}

// Test reading from a stream with full black (K=255)
TEST_F(CMYKGrayEncoderTest_235, FullBlackCMYKProducesBlackGray_235) {
    // CMYK (0,0,0,255) -> full black -> gray 0
    const char cmykData[] = {0, 0, 0, (char)255};
    auto memStream = createMemStream(cmykData, 4);
    CMYKGrayEncoder encoder(memStream.get());
    
    encoder.reset();
    
    int ch = encoder.getChar();
    EXPECT_GE(ch, 0);
    EXPECT_LE(ch, 255);
    EXPECT_EQ(ch, 0);
}

// Test that lookChar doesn't advance the stream position
TEST_F(CMYKGrayEncoderTest_235, LookCharDoesNotAdvance_235) {
    const char cmykData[] = {0, 0, 0, 0};
    auto memStream = createMemStream(cmykData, 4);
    CMYKGrayEncoder encoder(memStream.get());
    
    encoder.reset();
    
    int ch1 = encoder.lookChar();
    int ch2 = encoder.lookChar();
    EXPECT_EQ(ch1, ch2);
    
    // Now getChar should return the same value
    int ch3 = encoder.getChar();
    EXPECT_EQ(ch1, ch3);
}

// Test rewind functionality
TEST_F(CMYKGrayEncoderTest_235, RewindResetsStream_235) {
    const char cmykData[] = {0, 0, 0, 0};
    auto memStream = createMemStream(cmykData, 4);
    CMYKGrayEncoder encoder(memStream.get());
    
    encoder.reset();
    
    int ch1 = encoder.getChar();
    EXPECT_NE(ch1, EOF);
    
    // After reading, rewind and read again
    encoder.reset();
    
    int ch2 = encoder.getChar();
    EXPECT_EQ(ch1, ch2);
}

// Test that reading past end of stream returns EOF
TEST_F(CMYKGrayEncoderTest_235, ReadPastEndReturnsEOF_235) {
    // Only 1 CMYK pixel (4 bytes) -> 1 gray byte output
    const char cmykData[] = {0, 0, 0, 0};
    auto memStream = createMemStream(cmykData, 4);
    CMYKGrayEncoder encoder(memStream.get());
    
    encoder.reset();
    
    int ch = encoder.getChar();
    EXPECT_NE(ch, EOF);
    
    // Second read should return EOF since there's only 1 pixel
    ch = encoder.getChar();
    EXPECT_EQ(ch, EOF);
}

// Test empty stream
TEST_F(CMYKGrayEncoderTest_235, EmptyStreamReturnsEOF_235) {
    auto memStream = createMemStream("", 0);
    CMYKGrayEncoder encoder(memStream.get());
    
    encoder.reset();
    
    int ch = encoder.getChar();
    EXPECT_EQ(ch, EOF);
}

// Test multiple CMYK pixels
TEST_F(CMYKGrayEncoderTest_235, MultiplePixelsProduceMultipleGrayValues_235) {
    // 2 CMYK pixels
    const char cmykData[] = {
        0, 0, 0, 0,           // white
        0, 0, 0, (char)255    // black
    };
    auto memStream = createMemStream(cmykData, 8);
    CMYKGrayEncoder encoder(memStream.get());
    
    encoder.reset();
    
    int ch1 = encoder.getChar();
    EXPECT_EQ(ch1, 255); // white
    
    int ch2 = encoder.getChar();
    EXPECT_EQ(ch2, 0); // black
    
    int ch3 = encoder.getChar();
    EXPECT_EQ(ch3, EOF);
}

// Test with partial CMYK data (less than 4 bytes)
TEST_F(CMYKGrayEncoderTest_235, PartialCMYKDataHandled_235) {
    // Only 2 bytes, not enough for a complete CMYK pixel
    const char cmykData[] = {0, 0};
    auto memStream = createMemStream(cmykData, 2);
    CMYKGrayEncoder encoder(memStream.get());
    
    encoder.reset();
    
    // Should return EOF since there's not a complete CMYK pixel
    int ch = encoder.getChar();
    EXPECT_EQ(ch, EOF);
}

// Test with cyan component only
TEST_F(CMYKGrayEncoderTest_235, CyanComponentAffectsGray_235) {
    // CMYK (255, 0, 0, 0) - full cyan
    const char cmykData[] = {(char)255, 0, 0, 0};
    auto memStream = createMemStream(cmykData, 4);
    CMYKGrayEncoder encoder(memStream.get());
    
    encoder.reset();
    
    int ch = encoder.getChar();
    EXPECT_GE(ch, 0);
    EXPECT_LE(ch, 255);
    // Gray should be less than 255 since cyan contributes to darkness
    EXPECT_LT(ch, 255);
}

// Test lookChar on empty stream
TEST_F(CMYKGrayEncoderTest_235, LookCharOnEmptyStreamReturnsEOF_235) {
    auto memStream = createMemStream("", 0);
    CMYKGrayEncoder encoder(memStream.get());
    
    encoder.reset();
    
    int ch = encoder.lookChar();
    EXPECT_EQ(ch, EOF);
}

// Test multiple rewinds
TEST_F(CMYKGrayEncoderTest_235, MultipleRewindsWork_235) {
    const char cmykData[] = {(char)128, (char)64, (char)32, (char)16};
    auto memStream = createMemStream(cmykData, 4);
    CMYKGrayEncoder encoder(memStream.get());
    
    encoder.reset();
    int ch1 = encoder.getChar();
    
    encoder.reset();
    int ch2 = encoder.getChar();
    
    encoder.reset();
    int ch3 = encoder.getChar();
    
    EXPECT_EQ(ch1, ch2);
    EXPECT_EQ(ch2, ch3);
}
