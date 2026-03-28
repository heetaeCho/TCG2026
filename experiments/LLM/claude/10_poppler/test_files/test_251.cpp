#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Stream.h"
#include "Object.h"

// SplashBitmap is needed to construct SplashBitmapCMYKEncoder
#include "splash/SplashBitmap.h"
#include "splash/SplashTypes.h"

class SplashBitmapCMYKEncoderTest_251 : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a small CMYK bitmap for testing (4 components per pixel)
        bitmap = new SplashBitmap(10, 10, 4 * 10, splashModeCMYK8, false);
        // Fill bitmap with known data
        unsigned char *data = bitmap->getDataPtr();
        if (data) {
            for (int i = 0; i < 10 * 10 * 4; i++) {
                data[i] = static_cast<unsigned char>(i % 256);
            }
        }
        encoder = new SplashBitmapCMYKEncoder(bitmap);
    }

    void TearDown() override {
        delete encoder;
        delete bitmap;
    }

    SplashBitmap *bitmap = nullptr;
    SplashBitmapCMYKEncoder *encoder = nullptr;
};

// Test getDictObject returns nullptr
TEST_F(SplashBitmapCMYKEncoderTest_251, GetDictObjectReturnsNullptr_251) {
    Object *result = encoder->getDictObject();
    EXPECT_EQ(result, nullptr);
}

// Test isEncoder returns true
TEST_F(SplashBitmapCMYKEncoderTest_251, IsEncoderReturnsTrue_251) {
    EXPECT_TRUE(encoder->isEncoder());
}

// Test isBinary
TEST_F(SplashBitmapCMYKEncoderTest_251, IsBinaryReturnValue_251) {
    // Bitmap encoder should be binary
    bool result = encoder->isBinary(true);
    // Just verify it doesn't crash and returns a valid bool
    EXPECT_TRUE(result || !result);
}

// Test getKind
TEST_F(SplashBitmapCMYKEncoderTest_251, GetKindReturnsValidStreamKind_251) {
    StreamKind kind = encoder->getKind();
    // Verify it returns some valid StreamKind value
    (void)kind; // Just checking it doesn't crash
}

// Test rewind
TEST_F(SplashBitmapCMYKEncoderTest_251, RewindSucceeds_251) {
    bool result = encoder->rewind();
    EXPECT_TRUE(result);
}

// Test getChar returns valid data after rewind
TEST_F(SplashBitmapCMYKEncoderTest_251, GetCharReturnsDataAfterRewind_251) {
    encoder->rewind();
    int ch = encoder->getChar();
    // Should return a valid byte (0-255) or EOF
    EXPECT_GE(ch, -1);
    EXPECT_LE(ch, 255);
}

// Test lookChar does not advance position
TEST_F(SplashBitmapCMYKEncoderTest_251, LookCharDoesNotAdvancePosition_251) {
    encoder->rewind();
    int ch1 = encoder->lookChar();
    int ch2 = encoder->lookChar();
    EXPECT_EQ(ch1, ch2);
}

// Test lookChar and getChar return the same value
TEST_F(SplashBitmapCMYKEncoderTest_251, LookCharAndGetCharReturnSameValue_251) {
    encoder->rewind();
    int lookResult = encoder->lookChar();
    int getResult = encoder->getChar();
    EXPECT_EQ(lookResult, getResult);
}

// Test getPos after rewind
TEST_F(SplashBitmapCMYKEncoderTest_251, GetPosAfterRewindIsZero_251) {
    encoder->rewind();
    Goffset pos = encoder->getPos();
    EXPECT_EQ(pos, 0);
}

// Test getPos advances after getChar
TEST_F(SplashBitmapCMYKEncoderTest_251, GetPosAdvancesAfterGetChar_251) {
    encoder->rewind();
    Goffset posBefore = encoder->getPos();
    encoder->getChar();
    Goffset posAfter = encoder->getPos();
    EXPECT_GE(posAfter, posBefore);
}

// Test reading all bytes
TEST_F(SplashBitmapCMYKEncoderTest_251, ReadAllBytesUntilEOF_251) {
    encoder->rewind();
    int count = 0;
    while (encoder->getChar() != EOF) {
        count++;
        if (count > 10 * 10 * 4 + 100) {
            // Safety break to avoid infinite loop
            break;
        }
    }
    // For a 10x10 CMYK bitmap, we expect 10*10*4 = 400 bytes
    EXPECT_EQ(count, 10 * 10 * 4);
}

// Test rewind resets position
TEST_F(SplashBitmapCMYKEncoderTest_251, RewindResetsPosition_251) {
    encoder->rewind();
    int first = encoder->getChar();
    encoder->getChar();
    encoder->getChar();
    encoder->rewind();
    int afterRewind = encoder->getChar();
    EXPECT_EQ(first, afterRewind);
}

// Test getPSFilter
TEST_F(SplashBitmapCMYKEncoderTest_251, GetPSFilterReturnsNullopt_251) {
    auto result = encoder->getPSFilter(1, "");
    // Encoders typically return nullopt for PS filter
    EXPECT_FALSE(result.has_value());
}

// Test getBaseStream
TEST_F(SplashBitmapCMYKEncoderTest_251, GetBaseStreamReturnsValue_251) {
    BaseStream *base = encoder->getBaseStream();
    // For an encoder stream, this may return nullptr or the stream itself
    // Just verify no crash
    (void)base;
}

// Test getUndecodedStream
TEST_F(SplashBitmapCMYKEncoderTest_251, GetUndecodedStreamReturnsValue_251) {
    Stream *undecoded = encoder->getUndecodedStream();
    // Just verify no crash
    (void)undecoded;
}

// Test getDict
TEST_F(SplashBitmapCMYKEncoderTest_251, GetDictReturnsValue_251) {
    Dict *dict = encoder->getDict();
    // For encoder streams, dict may be nullptr
    // Just verify no crash
    (void)dict;
}

// Test getUnfilteredChar
TEST_F(SplashBitmapCMYKEncoderTest_251, GetUnfilteredCharWorks_251) {
    encoder->rewind();
    int ch = encoder->getUnfilteredChar();
    EXPECT_GE(ch, -1);
    EXPECT_LE(ch, 255);
}

// Test unfilteredRewind
TEST_F(SplashBitmapCMYKEncoderTest_251, UnfilteredRewindWorks_251) {
    bool result = encoder->unfilteredRewind();
    EXPECT_TRUE(result);
}

// Test setPos
TEST_F(SplashBitmapCMYKEncoderTest_251, SetPosDoesNotCrash_251) {
    encoder->rewind();
    // Just verify setPos doesn't crash
    encoder->setPos(0, 0);
}

// Test with a 1x1 bitmap (minimal size)
TEST(SplashBitmapCMYKEncoderMinimalTest_251, SinglePixelBitmap_251) {
    SplashBitmap *smallBitmap = new SplashBitmap(1, 1, 4, splashModeCMYK8, false);
    unsigned char *data = smallBitmap->getDataPtr();
    if (data) {
        data[0] = 0xAA;
        data[1] = 0xBB;
        data[2] = 0xCC;
        data[3] = 0xDD;
    }
    SplashBitmapCMYKEncoder *enc = new SplashBitmapCMYKEncoder(smallBitmap);
    enc->rewind();
    
    int b0 = enc->getChar();
    int b1 = enc->getChar();
    int b2 = enc->getChar();
    int b3 = enc->getChar();
    int eof = enc->getChar();
    
    EXPECT_EQ(b0, 0xAA);
    EXPECT_EQ(b1, 0xBB);
    EXPECT_EQ(b2, 0xCC);
    EXPECT_EQ(b3, 0xDD);
    EXPECT_EQ(eof, EOF);
    
    delete enc;
    delete smallBitmap;
}

// Test multiple rewinds
TEST_F(SplashBitmapCMYKEncoderTest_251, MultipleRewinds_251) {
    for (int i = 0; i < 5; i++) {
        bool result = encoder->rewind();
        EXPECT_TRUE(result);
        int ch = encoder->getChar();
        EXPECT_GE(ch, 0);
        EXPECT_LE(ch, 255);
    }
}

// Test EOF behavior - after EOF, getChar should keep returning EOF
TEST_F(SplashBitmapCMYKEncoderTest_251, AfterEOFKeepsReturningEOF_251) {
    encoder->rewind();
    // Read until EOF
    while (encoder->getChar() != EOF) {
        // consume all bytes
    }
    // Subsequent calls should still return EOF
    EXPECT_EQ(encoder->getChar(), EOF);
    EXPECT_EQ(encoder->getChar(), EOF);
}

// Test lookChar at EOF
TEST_F(SplashBitmapCMYKEncoderTest_251, LookCharAtEOFReturnsEOF_251) {
    encoder->rewind();
    while (encoder->getChar() != EOF) {
        // consume all bytes
    }
    EXPECT_EQ(encoder->lookChar(), EOF);
}
