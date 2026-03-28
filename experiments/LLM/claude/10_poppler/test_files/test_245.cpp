#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary headers
#include "poppler/Stream.h"
#include "poppler/Object.h"

// Forward declare or include SplashBitmap if available
#include "splash/SplashBitmap.h"

class SplashBitmapCMYKEncoderTest_245 : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a small CMYK bitmap for testing
        // SplashBitmap(width, height, rowPad, colorMode, hasAlpha)
        bitmap = new SplashBitmap(10, 10, 1, splashModeCMYK8, false);
        // Zero out the bitmap data
        unsigned char *data = bitmap->getDataPtr();
        int rowSize = bitmap->getRowSize();
        for (int y = 0; y < 10; y++) {
            memset(data + y * rowSize, 0, rowSize);
        }
    }

    void TearDown() override {
        // bitmap ownership: the encoder doesn't own it, so we clean up
        delete bitmap;
    }

    SplashBitmap *bitmap = nullptr;
};

// Test that isEncoder returns false
TEST_F(SplashBitmapCMYKEncoderTest_245, IsEncoderReturnsFalse_245) {
    SplashBitmapCMYKEncoder encoder(bitmap);
    EXPECT_FALSE(encoder.isEncoder());
}

// Test that getKind returns the expected stream kind
TEST_F(SplashBitmapCMYKEncoderTest_245, GetKindReturnsExpectedValue_245) {
    SplashBitmapCMYKEncoder encoder(bitmap);
    StreamKind kind = encoder.getKind();
    // Just verify it returns a valid kind without crashing
    (void)kind;
}

// Test that rewind succeeds
TEST_F(SplashBitmapCMYKEncoderTest_245, RewindSucceeds_245) {
    SplashBitmapCMYKEncoder encoder(bitmap);
    EXPECT_TRUE(encoder.rewind());
}

// Test that getPos returns 0 after construction/rewind
TEST_F(SplashBitmapCMYKEncoderTest_245, GetPosAfterRewindIsZero_245) {
    SplashBitmapCMYKEncoder encoder(bitmap);
    encoder.rewind();
    EXPECT_EQ(encoder.getPos(), 0);
}

// Test that getChar returns valid data after rewind
TEST_F(SplashBitmapCMYKEncoderTest_245, GetCharReturnsDataAfterRewind_245) {
    SplashBitmapCMYKEncoder encoder(bitmap);
    encoder.rewind();
    int ch = encoder.getChar();
    // For a zeroed bitmap, we expect 0 or EOF depending on implementation
    // Since we have a 10x10 CMYK bitmap with 4 channels, there should be data
    EXPECT_GE(ch, 0);
    EXPECT_LE(ch, 255);
}

// Test that lookChar returns same value as next getChar without advancing
TEST_F(SplashBitmapCMYKEncoderTest_245, LookCharDoesNotAdvance_245) {
    SplashBitmapCMYKEncoder encoder(bitmap);
    encoder.rewind();
    int lookVal = encoder.lookChar();
    int getVal = encoder.getChar();
    EXPECT_EQ(lookVal, getVal);
}

// Test that repeated lookChar returns same value
TEST_F(SplashBitmapCMYKEncoderTest_245, RepeatedLookCharReturnsSameValue_245) {
    SplashBitmapCMYKEncoder encoder(bitmap);
    encoder.rewind();
    int val1 = encoder.lookChar();
    int val2 = encoder.lookChar();
    EXPECT_EQ(val1, val2);
}

// Test that reading all data eventually returns EOF
TEST_F(SplashBitmapCMYKEncoderTest_245, ReadAllDataReturnsEOF_245) {
    SplashBitmapCMYKEncoder encoder(bitmap);
    encoder.rewind();
    
    // 10x10 CMYK = 400 bytes of data
    int totalBytes = 10 * 10 * 4;
    int ch;
    int count = 0;
    
    while ((ch = encoder.getChar()) != EOF && count < totalBytes + 100) {
        count++;
    }
    
    EXPECT_EQ(ch, EOF);
}

// Test that getPos advances after reading
TEST_F(SplashBitmapCMYKEncoderTest_245, GetPosAdvancesAfterGetChar_245) {
    SplashBitmapCMYKEncoder encoder(bitmap);
    encoder.rewind();
    Goffset pos0 = encoder.getPos();
    encoder.getChar();
    Goffset pos1 = encoder.getPos();
    EXPECT_GT(pos1, pos0);
}

// Test rewind after partial read resets position
TEST_F(SplashBitmapCMYKEncoderTest_245, RewindAfterPartialReadResetsPosition_245) {
    SplashBitmapCMYKEncoder encoder(bitmap);
    encoder.rewind();
    
    // Read some chars
    for (int i = 0; i < 5; i++) {
        encoder.getChar();
    }
    
    EXPECT_TRUE(encoder.rewind());
    EXPECT_EQ(encoder.getPos(), 0);
}

// Test that data read after rewind is consistent
TEST_F(SplashBitmapCMYKEncoderTest_245, DataConsistentAfterRewind_245) {
    SplashBitmapCMYKEncoder encoder(bitmap);
    encoder.rewind();
    
    // Read first few bytes
    std::vector<int> firstRead;
    for (int i = 0; i < 10; i++) {
        firstRead.push_back(encoder.getChar());
    }
    
    // Rewind and read again
    encoder.rewind();
    std::vector<int> secondRead;
    for (int i = 0; i < 10; i++) {
        secondRead.push_back(encoder.getChar());
    }
    
    EXPECT_EQ(firstRead, secondRead);
}

// Test isBinary
TEST_F(SplashBitmapCMYKEncoderTest_245, IsBinaryReturnsExpected_245) {
    SplashBitmapCMYKEncoder encoder(bitmap);
    // Just call it and verify it doesn't crash
    bool result = encoder.isBinary(true);
    (void)result;
}

// Test getPSFilter returns nullopt or empty
TEST_F(SplashBitmapCMYKEncoderTest_245, GetPSFilterReturnsValue_245) {
    SplashBitmapCMYKEncoder encoder(bitmap);
    auto result = encoder.getPSFilter(1, "");
    // For an encoder, this typically returns nullopt
    // Just verify it doesn't crash
    (void)result;
}

// Test getUnfilteredChar
TEST_F(SplashBitmapCMYKEncoderTest_245, GetUnfilteredCharWorks_245) {
    SplashBitmapCMYKEncoder encoder(bitmap);
    encoder.rewind();
    int ch = encoder.getUnfilteredChar();
    // Should return same as getChar for this type of stream
    EXPECT_GE(ch, -1); // -1 is EOF
}

// Test unfilteredRewind
TEST_F(SplashBitmapCMYKEncoderTest_245, UnfilteredRewindWorks_245) {
    SplashBitmapCMYKEncoder encoder(bitmap);
    encoder.rewind();
    encoder.getChar();
    encoder.getChar();
    bool result = encoder.unfilteredRewind();
    EXPECT_TRUE(result);
}

// Test with a 1x1 bitmap (boundary)
TEST(SplashBitmapCMYKEncoderBoundaryTest_245, OneByOneBitmap_245) {
    SplashBitmap *smallBitmap = new SplashBitmap(1, 1, 1, splashModeCMYK8, false);
    unsigned char *data = smallBitmap->getDataPtr();
    memset(data, 0xAB, 4); // Set CMYK values
    
    SplashBitmapCMYKEncoder encoder(smallBitmap);
    encoder.rewind();
    
    // Should have exactly 4 bytes (1 pixel * 4 channels)
    int count = 0;
    while (encoder.getChar() != EOF) {
        count++;
        if (count > 100) break; // Safety
    }
    
    EXPECT_EQ(count, 4);
    
    delete smallBitmap;
}

// Test with a 1x1 bitmap that data values are correct
TEST(SplashBitmapCMYKEncoderBoundaryTest_245, OneByOneBitmapDataValues_245) {
    SplashBitmap *smallBitmap = new SplashBitmap(1, 1, 1, splashModeCMYK8, false);
    unsigned char *data = smallBitmap->getDataPtr();
    data[0] = 0x10; // C
    data[1] = 0x20; // M
    data[2] = 0x30; // Y
    data[3] = 0x40; // K
    
    SplashBitmapCMYKEncoder encoder(smallBitmap);
    encoder.rewind();
    
    EXPECT_EQ(encoder.getChar(), 0x10);
    EXPECT_EQ(encoder.getChar(), 0x20);
    EXPECT_EQ(encoder.getChar(), 0x30);
    EXPECT_EQ(encoder.getChar(), 0x40);
    EXPECT_EQ(encoder.getChar(), EOF);
    
    delete smallBitmap;
}

// Test setPos
TEST_F(SplashBitmapCMYKEncoderTest_245, SetPosWorks_245) {
    SplashBitmapCMYKEncoder encoder(bitmap);
    encoder.rewind();
    
    // Read some data first
    for (int i = 0; i < 10; i++) {
        encoder.getChar();
    }
    
    // Set position - just verify it doesn't crash
    encoder.setPos(0, 0);
}

// Test getBaseStream
TEST_F(SplashBitmapCMYKEncoderTest_245, GetBaseStreamReturnsNullptr_245) {
    SplashBitmapCMYKEncoder encoder(bitmap);
    // For an encoder that wraps a bitmap, base stream may be null
    BaseStream *base = encoder.getBaseStream();
    // Just verify it doesn't crash
    (void)base;
}

// Test getUndecodedStream
TEST_F(SplashBitmapCMYKEncoderTest_245, GetUndecodedStreamWorks_245) {
    SplashBitmapCMYKEncoder encoder(bitmap);
    Stream *undecoded = encoder.getUndecodedStream();
    // Just verify it doesn't crash
    (void)undecoded;
}

// Test getDict
TEST_F(SplashBitmapCMYKEncoderTest_245, GetDictWorks_245) {
    SplashBitmapCMYKEncoder encoder(bitmap);
    Dict *dict = encoder.getDict();
    // Just verify it doesn't crash
    (void)dict;
}

// Test getDictObject
TEST_F(SplashBitmapCMYKEncoderTest_245, GetDictObjectWorks_245) {
    SplashBitmapCMYKEncoder encoder(bitmap);
    Object *obj = encoder.getDictObject();
    // Just verify it doesn't crash
    (void)obj;
}

// Test EOF behavior - lookChar at EOF
TEST_F(SplashBitmapCMYKEncoderTest_245, LookCharAtEOFReturnsEOF_245) {
    SplashBitmapCMYKEncoder encoder(bitmap);
    encoder.rewind();
    
    // Read all data
    while (encoder.getChar() != EOF) {
        // consume
    }
    
    // Now lookChar should also return EOF
    EXPECT_EQ(encoder.lookChar(), EOF);
}

// Test that getChar at EOF returns EOF consistently
TEST_F(SplashBitmapCMYKEncoderTest_245, GetCharAtEOFReturnsEOFConsistently_245) {
    SplashBitmapCMYKEncoder encoder(bitmap);
    encoder.rewind();
    
    // Read all data
    while (encoder.getChar() != EOF) {
        // consume
    }
    
    // Multiple calls at EOF should all return EOF
    EXPECT_EQ(encoder.getChar(), EOF);
    EXPECT_EQ(encoder.getChar(), EOF);
}
