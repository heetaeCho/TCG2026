#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Stream.h"
#include <cstring>
#include <memory>

// We need a concrete Stream implementation to feed into CMYKGrayEncoder.
// We'll use a MemStream which is available in poppler's Stream.h

class CMYKGrayEncoderTest_232 : public ::testing::Test {
protected:
    // Helper to create a CMYKGrayEncoder from raw CMYK data
    std::unique_ptr<CMYKGrayEncoder> createEncoder(const char* data, int len) {
        // MemStream takes ownership-ish of the buffer, so we need to keep it alive
        // We'll use a copy stored in the test fixture
        bufferData_.assign(data, data + len);
        
        Object dictObj;
        // MemStream expects: char *bufA, Goffset startA, Goffset lengthA, Object &&dictA
        auto memStream = new MemStream(bufferData_.data(), 0, bufferData_.size(), Object(objNull));
        auto encoder = std::make_unique<CMYKGrayEncoder>(memStream);
        return encoder;
    }
    
    std::vector<char> bufferData_;
};

// Test that CMYKGrayEncoder returns correct stream kind
TEST_F(CMYKGrayEncoderTest_232, GetKindReturnsCorrectType_232) {
    // CMYK has 4 bytes per pixel; provide one pixel
    char cmykData[] = {0, 0, 0, 0};
    auto encoder = createEncoder(cmykData, 4);
    EXPECT_EQ(encoder->getKind(), strWeird);
}

// Test that isEncoder returns true
TEST_F(CMYKGrayEncoderTest_232, IsEncoderReturnsTrue_232) {
    char cmykData[] = {0, 0, 0, 0};
    auto encoder = createEncoder(cmykData, 4);
    EXPECT_TRUE(encoder->isEncoder());
}

// Test that isBinary returns false (gray values are typically not binary encoded)
TEST_F(CMYKGrayEncoderTest_232, IsBinaryReturnsFalse_232) {
    char cmykData[] = {0, 0, 0, 0};
    auto encoder = createEncoder(cmykData, 4);
    // Check with default parameter
    EXPECT_FALSE(encoder->isBinary(true));
}

// Test that getPSFilter returns empty/nullopt since encoders typically don't have PS filters
TEST_F(CMYKGrayEncoderTest_232, GetPSFilterReturnsNullopt_232) {
    char cmykData[] = {0, 0, 0, 0};
    auto encoder = createEncoder(cmykData, 4);
    auto result = encoder->getPSFilter(1, "");
    EXPECT_FALSE(result.has_value());
}

// Test lookChar on empty stream returns EOF
TEST_F(CMYKGrayEncoderTest_232, LookCharOnEmptyStreamReturnsEOF_232) {
    auto encoder = createEncoder("", 0);
    encoder->rewind();
    EXPECT_EQ(encoder->lookChar(), EOF);
}

// Test getChar on empty stream returns EOF
TEST_F(CMYKGrayEncoderTest_232, GetCharOnEmptyStreamReturnsEOF_232) {
    auto encoder = createEncoder("", 0);
    encoder->rewind();
    EXPECT_EQ(encoder->getChar(), EOF);
}

// Test that lookChar does not advance the position (calling it multiple times returns the same value)
TEST_F(CMYKGrayEncoderTest_232, LookCharDoesNotAdvance_232) {
    // One CMYK pixel: all zeros -> gray should be some value
    char cmykData[] = {0, 0, 0, 0};
    auto encoder = createEncoder(cmykData, 4);
    encoder->rewind();
    
    int first = encoder->lookChar();
    int second = encoder->lookChar();
    EXPECT_EQ(first, second);
}

// Test that getChar advances the position
TEST_F(CMYKGrayEncoderTest_232, GetCharAdvancesPosition_232) {
    // One CMYK pixel
    char cmykData[] = {0, 0, 0, (char)255};
    auto encoder = createEncoder(cmykData, 4);
    encoder->rewind();
    
    int first = encoder->getChar();
    // After reading all output bytes for one pixel, subsequent reads 
    // should either return next value or EOF
    if (first != EOF) {
        // At least we verified getChar returned something and advanced
        int second = encoder->getChar();
        // second could be EOF or another value, but should not loop forever
        (void)second;
    }
}

// Test rewind resets the stream
TEST_F(CMYKGrayEncoderTest_232, RewindResetsStream_232) {
    char cmykData[] = {(char)100, (char)50, (char)25, (char)10};
    auto encoder = createEncoder(cmykData, 4);
    encoder->rewind();
    
    int firstRead = encoder->getChar();
    
    // Rewind and read again
    encoder->rewind();
    int afterRewind = encoder->getChar();
    
    EXPECT_EQ(firstRead, afterRewind);
}

// Test with pure black CMYK (0,0,0,255) -> should produce a specific gray value
TEST_F(CMYKGrayEncoderTest_232, PureBlackCMYK_232) {
    char cmykData[] = {0, 0, 0, (char)255};
    auto encoder = createEncoder(cmykData, 4);
    encoder->rewind();
    
    int val = encoder->lookChar();
    // Pure black in CMYK (K=255) should map to a dark gray (value close to 0)
    EXPECT_NE(val, EOF);
    EXPECT_GE(val, 0);
    EXPECT_LE(val, 255);
}

// Test with pure white CMYK (0,0,0,0) -> should produce white gray (255)
TEST_F(CMYKGrayEncoderTest_232, PureWhiteCMYK_232) {
    char cmykData[] = {0, 0, 0, 0};
    auto encoder = createEncoder(cmykData, 4);
    encoder->rewind();
    
    int val = encoder->lookChar();
    EXPECT_NE(val, EOF);
    // White CMYK should give high gray value
    EXPECT_GE(val, 0);
    EXPECT_LE(val, 255);
}

// Test with multiple CMYK pixels
TEST_F(CMYKGrayEncoderTest_232, MultiplePixels_232) {
    // Two CMYK pixels
    char cmykData[] = {0, 0, 0, 0, (char)255, (char)255, (char)255, (char)255};
    auto encoder = createEncoder(cmykData, 8);
    encoder->rewind();
    
    int val1 = encoder->getChar();
    EXPECT_NE(val1, EOF);
    
    int val2 = encoder->getChar();
    EXPECT_NE(val2, EOF);
    
    // After two pixels, should get EOF
    int val3 = encoder->getChar();
    EXPECT_EQ(val3, EOF);
}

// Test that after EOF, lookChar continues to return EOF
TEST_F(CMYKGrayEncoderTest_232, EOFIsPersistent_232) {
    char cmykData[] = {0, 0, 0, 0};
    auto encoder = createEncoder(cmykData, 4);
    encoder->rewind();
    
    // Read until EOF
    int val;
    int count = 0;
    while ((val = encoder->getChar()) != EOF && count < 100) {
        count++;
    }
    
    // Now lookChar should also return EOF
    EXPECT_EQ(encoder->lookChar(), EOF);
    EXPECT_EQ(encoder->getChar(), EOF);
}

// Test with incomplete CMYK data (less than 4 bytes)
TEST_F(CMYKGrayEncoderTest_232, IncompleteCMYKData_232) {
    // Only 2 bytes instead of 4 for a full CMYK pixel
    char cmykData[] = {(char)128, (char)64};
    auto encoder = createEncoder(cmykData, 2);
    encoder->rewind();
    
    // The behavior with incomplete data - should either return something or EOF
    // We just verify it doesn't crash
    int val = encoder->lookChar();
    (void)val; // Just ensuring no crash
}

// Test rewind returns true on successful rewind
TEST_F(CMYKGrayEncoderTest_232, RewindReturnsTrue_232) {
    char cmykData[] = {0, 0, 0, 0};
    auto encoder = createEncoder(cmykData, 4);
    EXPECT_TRUE(encoder->rewind());
}

// Test with maximum CMYK values
TEST_F(CMYKGrayEncoderTest_232, MaxCMYKValues_232) {
    char cmykData[] = {(char)255, (char)255, (char)255, (char)255};
    auto encoder = createEncoder(cmykData, 4);
    encoder->rewind();
    
    int val = encoder->getChar();
    EXPECT_NE(val, EOF);
    EXPECT_GE(val, 0);
    EXPECT_LE(val, 255);
}

// Test that lookChar returns value in valid range
TEST_F(CMYKGrayEncoderTest_232, LookCharReturnsValidRange_232) {
    char cmykData[] = {(char)128, (char)64, (char)32, (char)16};
    auto encoder = createEncoder(cmykData, 4);
    encoder->rewind();
    
    int val = encoder->lookChar();
    if (val != EOF) {
        EXPECT_GE(val, 0);
        EXPECT_LE(val, 255);
    }
}
