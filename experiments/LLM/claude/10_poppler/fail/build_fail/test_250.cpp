#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary headers
#include "poppler/Stream.h"
#include "poppler/Object.h"
#include "splash/SplashBitmap.h"

// Test fixture for SplashBitmapCMYKEncoder
class SplashBitmapCMYKEncoderTest_250 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that getDict returns nullptr
TEST_F(SplashBitmapCMYKEncoderTest_250, GetDictReturnsNullptr_250) {
    // Create a small CMYK bitmap for testing
    SplashBitmap *bitmap = new SplashBitmap(10, 10, 4, splashModeCMYK8, false);
    SplashBitmapCMYKEncoder encoder(bitmap);
    
    Dict *result = encoder.getDict();
    EXPECT_EQ(result, nullptr);
    
    delete bitmap;
}

// Test that isEncoder returns true
TEST_F(SplashBitmapCMYKEncoderTest_250, IsEncoderReturnsTrue_250) {
    SplashBitmap *bitmap = new SplashBitmap(10, 10, 4, splashModeCMYK8, false);
    SplashBitmapCMYKEncoder encoder(bitmap);
    
    EXPECT_TRUE(encoder.isEncoder());
    
    delete bitmap;
}

// Test that isBinary returns expected value
TEST_F(SplashBitmapCMYKEncoderTest_250, IsBinaryTest_250) {
    SplashBitmap *bitmap = new SplashBitmap(10, 10, 4, splashModeCMYK8, false);
    SplashBitmapCMYKEncoder encoder(bitmap);
    
    // Binary encoder should return true
    bool result = encoder.isBinary(true);
    EXPECT_TRUE(result);
    
    delete bitmap;
}

// Test that getKind returns the appropriate stream kind
TEST_F(SplashBitmapCMYKEncoderTest_250, GetKindTest_250) {
    SplashBitmap *bitmap = new SplashBitmap(10, 10, 4, splashModeCMYK8, false);
    SplashBitmapCMYKEncoder encoder(bitmap);
    
    StreamKind kind = encoder.getKind();
    // Just verify it returns a valid kind value
    EXPECT_GE(static_cast<int>(kind), 0);
    
    delete bitmap;
}

// Test that rewind works without error
TEST_F(SplashBitmapCMYKEncoderTest_250, RewindTest_250) {
    SplashBitmap *bitmap = new SplashBitmap(10, 10, 4, splashModeCMYK8, false);
    SplashBitmapCMYKEncoder encoder(bitmap);
    
    bool result = encoder.rewind();
    EXPECT_TRUE(result);
    
    delete bitmap;
}

// Test that getPos returns a valid position after rewind
TEST_F(SplashBitmapCMYKEncoderTest_250, GetPosAfterRewind_250) {
    SplashBitmap *bitmap = new SplashBitmap(10, 10, 4, splashModeCMYK8, false);
    SplashBitmapCMYKEncoder encoder(bitmap);
    
    encoder.rewind();
    Goffset pos = encoder.getPos();
    EXPECT_GE(pos, 0);
    
    delete bitmap;
}

// Test getChar returns valid data or EOF
TEST_F(SplashBitmapCMYKEncoderTest_250, GetCharReturnsData_250) {
    SplashBitmap *bitmap = new SplashBitmap(2, 2, 4, splashModeCMYK8, false);
    SplashBitmapCMYKEncoder encoder(bitmap);
    
    encoder.rewind();
    int ch = encoder.getChar();
    // Should return a byte value [0, 255] or EOF (-1)
    EXPECT_GE(ch, -1);
    EXPECT_LE(ch, 255);
    
    delete bitmap;
}

// Test lookChar returns same value as getChar without advancing
TEST_F(SplashBitmapCMYKEncoderTest_250, LookCharDoesNotAdvance_250) {
    SplashBitmap *bitmap = new SplashBitmap(2, 2, 4, splashModeCMYK8, false);
    SplashBitmapCMYKEncoder encoder(bitmap);
    
    encoder.rewind();
    int ch1 = encoder.lookChar();
    int ch2 = encoder.lookChar();
    // lookChar should return the same value when called twice without getChar
    EXPECT_EQ(ch1, ch2);
    
    delete bitmap;
}

// Test lookChar followed by getChar returns same value
TEST_F(SplashBitmapCMYKEncoderTest_250, LookCharMatchesGetChar_250) {
    SplashBitmap *bitmap = new SplashBitmap(2, 2, 4, splashModeCMYK8, false);
    SplashBitmapCMYKEncoder encoder(bitmap);
    
    encoder.rewind();
    int lookVal = encoder.lookChar();
    int getVal = encoder.getChar();
    EXPECT_EQ(lookVal, getVal);
    
    delete bitmap;
}

// Test reading all data from a small bitmap
TEST_F(SplashBitmapCMYKEncoderTest_250, ReadEntireBitmap_250) {
    const int w = 3;
    const int h = 3;
    SplashBitmap *bitmap = new SplashBitmap(w, h, 4, splashModeCMYK8, false);
    SplashBitmapCMYKEncoder encoder(bitmap);
    
    encoder.rewind();
    
    int byteCount = 0;
    int ch;
    while ((ch = encoder.getChar()) != EOF) {
        EXPECT_GE(ch, 0);
        EXPECT_LE(ch, 255);
        byteCount++;
        // Safety limit to avoid infinite loop
        if (byteCount > w * h * 4 + 100) {
            FAIL() << "Too many bytes read, possible infinite loop";
            break;
        }
    }
    
    // For a CMYK bitmap of w*h pixels, we expect w*h*4 bytes
    EXPECT_EQ(byteCount, w * h * 4);
    
    delete bitmap;
}

// Test that after reading all data, getChar returns EOF
TEST_F(SplashBitmapCMYKEncoderTest_250, EOFAfterAllData_250) {
    SplashBitmap *bitmap = new SplashBitmap(1, 1, 4, splashModeCMYK8, false);
    SplashBitmapCMYKEncoder encoder(bitmap);
    
    encoder.rewind();
    
    // Read all bytes (1 pixel * 4 components = 4 bytes for CMYK)
    for (int i = 0; i < 4; i++) {
        int ch = encoder.getChar();
        EXPECT_NE(ch, EOF);
    }
    
    // Next read should be EOF
    int ch = encoder.getChar();
    EXPECT_EQ(ch, EOF);
    
    delete bitmap;
}

// Test getDict returns nullptr consistently
TEST_F(SplashBitmapCMYKEncoderTest_250, GetDictConsistentlyNull_250) {
    SplashBitmap *bitmap = new SplashBitmap(5, 5, 4, splashModeCMYK8, false);
    SplashBitmapCMYKEncoder encoder(bitmap);
    
    EXPECT_EQ(encoder.getDict(), nullptr);
    EXPECT_EQ(encoder.getDict(), nullptr);
    
    delete bitmap;
}

// Test getPSFilter returns empty optional
TEST_F(SplashBitmapCMYKEncoderTest_250, GetPSFilterTest_250) {
    SplashBitmap *bitmap = new SplashBitmap(5, 5, 4, splashModeCMYK8, false);
    SplashBitmapCMYKEncoder encoder(bitmap);
    
    auto result = encoder.getPSFilter(1, "");
    // Encoders typically don't have PS filters
    EXPECT_FALSE(result.has_value());
    
    delete bitmap;
}

// Test getBaseStream returns nullptr for an encoder stream
TEST_F(SplashBitmapCMYKEncoderTest_250, GetBaseStreamTest_250) {
    SplashBitmap *bitmap = new SplashBitmap(5, 5, 4, splashModeCMYK8, false);
    SplashBitmapCMYKEncoder encoder(bitmap);
    
    BaseStream *base = encoder.getBaseStream();
    EXPECT_EQ(base, nullptr);
    
    delete bitmap;
}

// Test getUndecodedStream returns appropriate value
TEST_F(SplashBitmapCMYKEncoderTest_250, GetUndecodedStreamTest_250) {
    SplashBitmap *bitmap = new SplashBitmap(5, 5, 4, splashModeCMYK8, false);
    SplashBitmapCMYKEncoder encoder(bitmap);
    
    Stream *undecoded = encoder.getUndecodedStream();
    // For an encoder, getUndecodedStream typically returns this
    EXPECT_NE(undecoded, nullptr);
    
    delete bitmap;
}

// Test unfilteredRewind
TEST_F(SplashBitmapCMYKEncoderTest_250, UnfilteredRewindTest_250) {
    SplashBitmap *bitmap = new SplashBitmap(5, 5, 4, splashModeCMYK8, false);
    SplashBitmapCMYKEncoder encoder(bitmap);
    
    encoder.rewind();
    encoder.getChar(); // advance
    
    bool result = encoder.unfilteredRewind();
    EXPECT_TRUE(result);
    
    delete bitmap;
}

// Test getUnfilteredChar returns valid data
TEST_F(SplashBitmapCMYKEncoderTest_250, GetUnfilteredCharTest_250) {
    SplashBitmap *bitmap = new SplashBitmap(2, 2, 4, splashModeCMYK8, false);
    SplashBitmapCMYKEncoder encoder(bitmap);
    
    encoder.rewind();
    int ch = encoder.getUnfilteredChar();
    EXPECT_GE(ch, -1);
    EXPECT_LE(ch, 255);
    
    delete bitmap;
}

// Test rewind resets position
TEST_F(SplashBitmapCMYKEncoderTest_250, RewindResetsPosition_250) {
    SplashBitmap *bitmap = new SplashBitmap(2, 2, 4, splashModeCMYK8, false);
    SplashBitmapCMYKEncoder encoder(bitmap);
    
    encoder.rewind();
    int firstChar = encoder.getChar();
    
    // Read a few more
    encoder.getChar();
    encoder.getChar();
    
    // Rewind
    encoder.rewind();
    int afterRewind = encoder.getChar();
    
    // After rewind, we should get the same first character
    EXPECT_EQ(firstChar, afterRewind);
    
    delete bitmap;
}

// Test with 1x1 bitmap (boundary)
TEST_F(SplashBitmapCMYKEncoderTest_250, SinglePixelBitmap_250) {
    SplashBitmap *bitmap = new SplashBitmap(1, 1, 4, splashModeCMYK8, false);
    SplashBitmapCMYKEncoder encoder(bitmap);
    
    encoder.rewind();
    
    int byteCount = 0;
    while (encoder.getChar() != EOF) {
        byteCount++;
        if (byteCount > 100) {
            FAIL() << "Too many bytes for 1x1 bitmap";
            break;
        }
    }
    
    EXPECT_EQ(byteCount, 4); // 1 pixel * 4 CMYK components
    
    delete bitmap;
}

// Test getDictObject
TEST_F(SplashBitmapCMYKEncoderTest_250, GetDictObjectTest_250) {
    SplashBitmap *bitmap = new SplashBitmap(5, 5, 4, splashModeCMYK8, false);
    SplashBitmapCMYKEncoder encoder(bitmap);
    
    Object *dictObj = encoder.getDictObject();
    // Just verify it doesn't crash and returns something
    // (could be nullptr or a valid object depending on implementation)
    (void)dictObj;
    
    delete bitmap;
}

// Test position advances with getChar
TEST_F(SplashBitmapCMYKEncoderTest_250, PositionAdvancesWithGetChar_250) {
    SplashBitmap *bitmap = new SplashBitmap(5, 5, 4, splashModeCMYK8, false);
    SplashBitmapCMYKEncoder encoder(bitmap);
    
    encoder.rewind();
    Goffset pos0 = encoder.getPos();
    encoder.getChar();
    Goffset pos1 = encoder.getPos();
    
    EXPECT_GT(pos1, pos0);
    
    delete bitmap;
}
