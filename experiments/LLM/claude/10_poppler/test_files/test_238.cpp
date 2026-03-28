#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Stream.h"

// Mock Stream class to serve as the underlying stream for RGBGrayEncoder
// We need a concrete Stream implementation to pass to RGBGrayEncoder
class MemoryStream : public Stream {
public:
    MemoryStream(const unsigned char *data, int length)
        : buf(data), bufEnd(data + length), pos(data) {}

    StreamKind getKind() const override { return strWeird; }
    void reset() override { pos = buf; }
    int getChar() override {
        if (pos >= bufEnd) return EOF;
        return *pos++ & 0xff;
    }
    int lookChar() override {
        if (pos >= bufEnd) return EOF;
        return *pos & 0xff;
    }
    GooString *getPSFilter(int psLevel, const char *indent) { return nullptr; }
    bool isBinary(bool last) const override { return false; }
    int getPos() override { return (int)(pos - buf); }
    void setPos(Goffset offset, int direction) override {
        if (direction == 0) {
            pos = buf + offset;
        } else {
            pos = bufEnd + offset;
        }
        if (pos < buf) pos = buf;
        if (pos > bufEnd) pos = bufEnd;
    }
    Goffset getStart() override { return 0; }
    void close() override {}

private:
    const unsigned char *buf;
    const unsigned char *bufEnd;
    const unsigned char *pos;
};

class RGBGrayEncoderTest_238 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that RGBGrayEncoder returns EOF when underlying stream is empty
TEST_F(RGBGrayEncoderTest_238, EmptyStreamReturnsEOF_238) {
    unsigned char data[] = {};
    auto *memStream = new MemoryStream(data, 0);
    RGBGrayEncoder encoder(memStream);
    encoder.reset();
    
    int result = encoder.lookChar();
    EXPECT_EQ(result, EOF);
    
    int charResult = encoder.getChar();
    EXPECT_EQ(charResult, EOF);
}

// Test that RGBGrayEncoder converts RGB triplets to grayscale
TEST_F(RGBGrayEncoderTest_238, SingleRGBTripletConversion_238) {
    // A white pixel (255, 255, 255) should produce a gray value of 255
    unsigned char data[] = {255, 255, 255};
    auto *memStream = new MemoryStream(data, 3);
    RGBGrayEncoder encoder(memStream);
    encoder.reset();
    
    int result = encoder.lookChar();
    EXPECT_NE(result, EOF);
    EXPECT_GE(result, 0);
    EXPECT_LE(result, 255);
}

// Test that lookChar does not advance the position
TEST_F(RGBGrayEncoderTest_238, LookCharDoesNotAdvance_238) {
    unsigned char data[] = {100, 150, 200};
    auto *memStream = new MemoryStream(data, 3);
    RGBGrayEncoder encoder(memStream);
    encoder.reset();
    
    int first = encoder.lookChar();
    int second = encoder.lookChar();
    EXPECT_EQ(first, second);
}

// Test that getChar advances the position
TEST_F(RGBGrayEncoderTest_238, GetCharAdvancesPosition_238) {
    // Two RGB triplets -> two grayscale bytes
    unsigned char data[] = {255, 255, 255, 0, 0, 0};
    auto *memStream = new MemoryStream(data, 6);
    RGBGrayEncoder encoder(memStream);
    encoder.reset();
    
    int first = encoder.getChar();
    EXPECT_NE(first, EOF);
    
    // After reading first gray byte, we should get the second one
    int second = encoder.getChar();
    // second could be EOF or another value
    // After two reads, should be EOF
    int third = encoder.getChar();
    EXPECT_EQ(third, EOF);
}

// Test black pixel conversion
TEST_F(RGBGrayEncoderTest_238, BlackPixelConversion_238) {
    unsigned char data[] = {0, 0, 0};
    auto *memStream = new MemoryStream(data, 3);
    RGBGrayEncoder encoder(memStream);
    encoder.reset();
    
    int result = encoder.getChar();
    EXPECT_EQ(result, 0);
}

// Test white pixel conversion
TEST_F(RGBGrayEncoderTest_238, WhitePixelConversion_238) {
    unsigned char data[] = {255, 255, 255};
    auto *memStream = new MemoryStream(data, 3);
    RGBGrayEncoder encoder(memStream);
    encoder.reset();
    
    int result = encoder.getChar();
    EXPECT_EQ(result, 255);
}

// Test getKind returns expected stream kind
TEST_F(RGBGrayEncoderTest_238, GetKindReturnsCorrectType_238) {
    unsigned char data[] = {128, 128, 128};
    auto *memStream = new MemoryStream(data, 3);
    RGBGrayEncoder encoder(memStream);
    
    StreamKind kind = encoder.getKind();
    // Just verify it returns some valid kind
    (void)kind; // We can't predict the exact kind without knowing impl
}

// Test isEncoder returns true
TEST_F(RGBGrayEncoderTest_238, IsEncoderReturnsTrue_238) {
    unsigned char data[] = {0};
    auto *memStream = new MemoryStream(data, 1);
    RGBGrayEncoder encoder(memStream);
    
    EXPECT_TRUE(encoder.isEncoder());
}

// Test isBinary
TEST_F(RGBGrayEncoderTest_238, IsBinaryCheck_238) {
    unsigned char data[] = {0};
    auto *memStream = new MemoryStream(data, 1);
    RGBGrayEncoder encoder(memStream);
    
    // Just verify it returns a valid bool
    bool result = encoder.isBinary(true);
    (void)result;
}

// Test getPSFilter returns empty optional
TEST_F(RGBGrayEncoderTest_238, GetPSFilterReturnsNone_238) {
    unsigned char data[] = {0};
    auto *memStream = new MemoryStream(data, 1);
    RGBGrayEncoder encoder(memStream);
    
    auto result = encoder.getPSFilter(1, "");
    // Encoders typically return empty optional for PS filters
    EXPECT_FALSE(result.has_value());
}

// Test rewind functionality
TEST_F(RGBGrayEncoderTest_238, RewindResetsPosition_238) {
    unsigned char data[] = {128, 128, 128};
    auto *memStream = new MemoryStream(data, 3);
    RGBGrayEncoder encoder(memStream);
    encoder.reset();
    
    int firstRead = encoder.getChar();
    EXPECT_NE(firstRead, EOF);
    
    // After getChar, next should be EOF (only one triplet)
    int shouldBeEOF = encoder.getChar();
    EXPECT_EQ(shouldBeEOF, EOF);
    
    // Rewind and read again
    bool rewound = encoder.rewind();
    if (rewound) {
        int afterRewind = encoder.getChar();
        EXPECT_EQ(afterRewind, firstRead);
    }
}

// Test multiple RGB triplets
TEST_F(RGBGrayEncoderTest_238, MultipleTripletsConversion_238) {
    unsigned char data[] = {
        255, 0, 0,     // Red
        0, 255, 0,     // Green
        0, 0, 255,     // Blue
        128, 128, 128  // Gray
    };
    auto *memStream = new MemoryStream(data, 12);
    RGBGrayEncoder encoder(memStream);
    encoder.reset();
    
    // Should produce 4 grayscale bytes
    int count = 0;
    while (encoder.getChar() != EOF) {
        count++;
    }
    EXPECT_EQ(count, 4);
}

// Test that gray conversion of pure gray input preserves approximate value
TEST_F(RGBGrayEncoderTest_238, PureGrayPreservation_238) {
    unsigned char data[] = {128, 128, 128};
    auto *memStream = new MemoryStream(data, 3);
    RGBGrayEncoder encoder(memStream);
    encoder.reset();
    
    int result = encoder.getChar();
    // For equal R=G=B, the grayscale should be approximately the same value
    EXPECT_NEAR(result, 128, 2);
}

// Test partial triplet (incomplete RGB data)
TEST_F(RGBGrayEncoderTest_238, PartialTripletHandling_238) {
    // Only 2 bytes instead of 3 for a full RGB triplet
    unsigned char data[] = {200, 100};
    auto *memStream = new MemoryStream(data, 2);
    RGBGrayEncoder encoder(memStream);
    encoder.reset();
    
    // Behavior with incomplete triplet - just verify no crash
    int result = encoder.lookChar();
    // Could be EOF or some value depending on implementation
    (void)result;
}

// Test lookChar followed by getChar returns same value
TEST_F(RGBGrayEncoderTest_238, LookCharThenGetCharSameValue_238) {
    unsigned char data[] = {50, 100, 150};
    auto *memStream = new MemoryStream(data, 3);
    RGBGrayEncoder encoder(memStream);
    encoder.reset();
    
    int looked = encoder.lookChar();
    int got = encoder.getChar();
    EXPECT_EQ(looked, got);
}

// Test that returned values are within valid byte range
TEST_F(RGBGrayEncoderTest_238, OutputInValidByteRange_238) {
    unsigned char data[] = {
        0, 0, 0,
        127, 127, 127,
        255, 255, 255,
        255, 0, 0,
        0, 255, 0,
        0, 0, 255
    };
    auto *memStream = new MemoryStream(data, 18);
    RGBGrayEncoder encoder(memStream);
    encoder.reset();
    
    int val;
    while ((val = encoder.getChar()) != EOF) {
        EXPECT_GE(val, 0);
        EXPECT_LE(val, 255);
    }
}
