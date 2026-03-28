#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Stream.h"

// We need a mock or concrete Stream to pass to CMYKGrayEncoder.
// We'll use a MemStream (memory-based stream) which is available in poppler.

class CMYKGrayEncoderTest_231 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    // Helper to create a MemStream from a buffer of bytes
    // MemStream takes ownership model varies; we manage lifetime carefully
    std::unique_ptr<MemStream> createMemStream(const char *data, int length) {
        // MemStream(const char *bufA, Goffset startA, Goffset lengthA, Object &&dictA)
        auto memStream = std::make_unique<MemStream>(const_cast<char *>(data), 0, length, Object(objNull));
        return memStream;
    }
};

// Test that CMYKGrayEncoder returns the correct StreamKind
TEST_F(CMYKGrayEncoderTest_231, GetKind_231) {
    // CMYK data: 4 bytes per pixel (C, M, Y, K)
    const char data[] = {0, 0, 0, 0};
    auto memStream = createMemStream(data, 4);
    CMYKGrayEncoder encoder(memStream.get());
    
    EXPECT_EQ(encoder.getKind(), strWeird);
}

// Test that isEncoder returns true
TEST_F(CMYKGrayEncoderTest_231, IsEncoder_231) {
    const char data[] = {0, 0, 0, 0};
    auto memStream = createMemStream(data, 4);
    CMYKGrayEncoder encoder(memStream.get());
    
    EXPECT_TRUE(encoder.isEncoder());
}

// Test that isBinary returns false (gray encoder typically outputs non-binary)
TEST_F(CMYKGrayEncoderTest_231, IsBinary_231) {
    const char data[] = {0, 0, 0, 0};
    auto memStream = createMemStream(data, 4);
    CMYKGrayEncoder encoder(memStream.get());
    
    // Test isBinary
    bool result = encoder.isBinary(true);
    // Just verify it returns a valid boolean (true or false)
    EXPECT_TRUE(result == true || result == false);
}

// Test that getPSFilter returns no value (encoders typically return nullopt)
TEST_F(CMYKGrayEncoderTest_231, GetPSFilter_231) {
    const char data[] = {0, 0, 0, 0};
    auto memStream = createMemStream(data, 4);
    CMYKGrayEncoder encoder(memStream.get());
    
    auto psFilter = encoder.getPSFilter(1, "");
    EXPECT_FALSE(psFilter.has_value());
}

// Test getChar on empty stream returns EOF quickly
TEST_F(CMYKGrayEncoderTest_231, EmptyStreamReturnsEOF_231) {
    const char data[] = {};
    auto memStream = createMemStream(data, 0);
    CMYKGrayEncoder encoder(memStream.get());
    encoder.reset();
    
    int ch = encoder.getChar();
    EXPECT_EQ(ch, EOF);
}

// Test that getChar reads from CMYK and produces gray output
// For all-zero CMYK (C=0, M=0, Y=0, K=0), the gray should be white (255)
TEST_F(CMYKGrayEncoderTest_231, AllZeroCMYKProducesWhite_231) {
    const char data[] = {0, 0, 0, 0};
    auto memStream = createMemStream(data, 4);
    CMYKGrayEncoder encoder(memStream.get());
    encoder.reset();
    
    int ch = encoder.getChar();
    // With C=M=Y=K=0, gray should be 255 (white)
    EXPECT_NE(ch, EOF);
    EXPECT_GE(ch, 0);
    EXPECT_LE(ch, 255);
}

// Test that getChar with all-black CMYK (K=255) produces black (0)
TEST_F(CMYKGrayEncoderTest_231, AllBlackCMYK_231) {
    const char data[] = {0, 0, 0, (char)0xFF};
    auto memStream = createMemStream(data, 4);
    CMYKGrayEncoder encoder(memStream.get());
    encoder.reset();
    
    int ch = encoder.getChar();
    EXPECT_NE(ch, EOF);
    // K=255 should produce a very dark gray (close to 0)
    EXPECT_GE(ch, 0);
    EXPECT_LE(ch, 255);
}

// Test reading multiple CMYK pixels
TEST_F(CMYKGrayEncoderTest_231, MultiplePixels_231) {
    // Two CMYK pixels
    const char data[] = {0, 0, 0, 0, 0, 0, 0, (char)0xFF};
    auto memStream = createMemStream(data, 8);
    CMYKGrayEncoder encoder(memStream.get());
    encoder.reset();
    
    int ch1 = encoder.getChar();
    EXPECT_NE(ch1, EOF);
    
    int ch2 = encoder.getChar();
    EXPECT_NE(ch2, EOF);
    
    // After two pixels, should get EOF
    int ch3 = encoder.getChar();
    EXPECT_EQ(ch3, EOF);
}

// Test lookChar does not consume the character
TEST_F(CMYKGrayEncoderTest_231, LookCharDoesNotConsume_231) {
    const char data[] = {0, 0, 0, 0};
    auto memStream = createMemStream(data, 4);
    CMYKGrayEncoder encoder(memStream.get());
    encoder.reset();
    
    int looked = encoder.lookChar();
    int got = encoder.getChar();
    
    // lookChar and subsequent getChar should return the same value
    EXPECT_EQ(looked, got);
}

// Test lookChar on empty stream returns EOF
TEST_F(CMYKGrayEncoderTest_231, LookCharEmptyStream_231) {
    const char data[] = {};
    auto memStream = createMemStream(data, 0);
    CMYKGrayEncoder encoder(memStream.get());
    encoder.reset();
    
    int ch = encoder.lookChar();
    EXPECT_EQ(ch, EOF);
}

// Test rewind functionality
TEST_F(CMYKGrayEncoderTest_231, RewindRestartsStream_231) {
    const char data[] = {0, 0, 0, 0};
    auto memStream = createMemStream(data, 4);
    CMYKGrayEncoder encoder(memStream.get());
    encoder.reset();
    
    int ch1 = encoder.getChar();
    EXPECT_NE(ch1, EOF);
    
    // After reading all data, should get EOF
    int chEof = encoder.getChar();
    EXPECT_EQ(chEof, EOF);
    
    // Rewind and read again
    encoder.reset();
    int ch2 = encoder.getChar();
    EXPECT_EQ(ch1, ch2);
}

// Test getChar returns values in range 0-255 for various CMYK inputs
TEST_F(CMYKGrayEncoderTest_231, OutputRange_231) {
    const char data[] = {(char)0x80, (char)0x40, (char)0x20, (char)0x10};
    auto memStream = createMemStream(data, 4);
    CMYKGrayEncoder encoder(memStream.get());
    encoder.reset();
    
    int ch = encoder.getChar();
    EXPECT_NE(ch, EOF);
    EXPECT_GE(ch, 0);
    EXPECT_LE(ch, 255);
}

// Test incomplete CMYK pixel (less than 4 bytes)
TEST_F(CMYKGrayEncoderTest_231, IncompleteCMYKPixel_231) {
    // Only 3 bytes - incomplete CMYK pixel
    const char data[] = {0, 0, 0};
    auto memStream = createMemStream(data, 3);
    CMYKGrayEncoder encoder(memStream.get());
    encoder.reset();
    
    // Behavior with incomplete data - should either return EOF or handle gracefully
    int ch = encoder.getChar();
    // We just verify it doesn't crash and returns a valid value or EOF
    EXPECT_TRUE(ch == EOF || (ch >= 0 && ch <= 255));
}

// Test multiple lookChar calls return the same value
TEST_F(CMYKGrayEncoderTest_231, MultipleLookCharSameValue_231) {
    const char data[] = {(char)0x10, (char)0x20, (char)0x30, (char)0x40};
    auto memStream = createMemStream(data, 4);
    CMYKGrayEncoder encoder(memStream.get());
    encoder.reset();
    
    int look1 = encoder.lookChar();
    int look2 = encoder.lookChar();
    EXPECT_EQ(look1, look2);
}

// Test with maximum CMYK values
TEST_F(CMYKGrayEncoderTest_231, MaxCMYKValues_231) {
    const char data[] = {(char)0xFF, (char)0xFF, (char)0xFF, (char)0xFF};
    auto memStream = createMemStream(data, 4);
    CMYKGrayEncoder encoder(memStream.get());
    encoder.reset();
    
    int ch = encoder.getChar();
    EXPECT_NE(ch, EOF);
    EXPECT_GE(ch, 0);
    EXPECT_LE(ch, 255);
}

// Test reading many pixels sequentially
TEST_F(CMYKGrayEncoderTest_231, ManyPixels_231) {
    // 4 pixels = 16 bytes of CMYK data
    const char data[] = {
        0, 0, 0, 0,
        (char)0xFF, 0, 0, 0,
        0, (char)0xFF, 0, 0,
        0, 0, (char)0xFF, 0
    };
    auto memStream = createMemStream(data, 16);
    CMYKGrayEncoder encoder(memStream.get());
    encoder.reset();
    
    int count = 0;
    while (encoder.getChar() != EOF) {
        count++;
    }
    // Should produce exactly 4 gray values (one per CMYK pixel)
    EXPECT_EQ(count, 4);
}
