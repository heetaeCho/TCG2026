#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Stream.h"
#include "splash/SplashBitmap.h"
#include "splash/SplashTypes.h"

class SplashBitmapCMYKEncoderTest_247 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    SplashBitmap* createCMYKBitmap(int width, int height) {
        // Create a CMYK bitmap (splashModeCMYK8 = 4 bytes per pixel)
        SplashBitmap* bmp = new SplashBitmap(width, height, 1, splashModeCMYK8, false);
        // Fill with known data
        SplashColorPtr data = bmp->getDataPtr();
        int rowSize = bmp->getRowSize();
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width * 4; x++) {
                data[y * rowSize + x] = (unsigned char)((y * width * 4 + x) & 0xFF);
            }
        }
        return bmp;
    }
};

// Test that the encoder can be constructed with a valid bitmap
TEST_F(SplashBitmapCMYKEncoderTest_247, ConstructWithValidBitmap_247) {
    SplashBitmap* bmp = createCMYKBitmap(10, 10);
    SplashBitmapCMYKEncoder encoder(bmp);
    // Should not crash
    delete bmp;
}

// Test getKind returns the expected stream kind
TEST_F(SplashBitmapCMYKEncoderTest_247, GetKind_247) {
    SplashBitmap* bmp = createCMYKBitmap(4, 4);
    SplashBitmapCMYKEncoder encoder(bmp);
    StreamKind kind = encoder.getKind();
    // Encoder streams typically have a specific kind
    EXPECT_NE(kind, strFile);
    delete bmp;
}

// Test isEncoder returns true
TEST_F(SplashBitmapCMYKEncoderTest_247, IsEncoder_247) {
    SplashBitmap* bmp = createCMYKBitmap(4, 4);
    SplashBitmapCMYKEncoder encoder(bmp);
    EXPECT_TRUE(encoder.isEncoder());
    delete bmp;
}

// Test isBinary returns expected value
TEST_F(SplashBitmapCMYKEncoderTest_247, IsBinary_247) {
    SplashBitmap* bmp = createCMYKBitmap(4, 4);
    SplashBitmapCMYKEncoder encoder(bmp);
    bool result = encoder.isBinary(true);
    EXPECT_TRUE(result);
    delete bmp;
}

// Test rewind succeeds
TEST_F(SplashBitmapCMYKEncoderTest_247, RewindSucceeds_247) {
    SplashBitmap* bmp = createCMYKBitmap(4, 4);
    SplashBitmapCMYKEncoder encoder(bmp);
    EXPECT_TRUE(encoder.rewind());
    delete bmp;
}

// Test unfilteredRewind calls rewind and returns same result
TEST_F(SplashBitmapCMYKEncoderTest_247, UnfilteredRewindSucceeds_247) {
    SplashBitmap* bmp = createCMYKBitmap(4, 4);
    SplashBitmapCMYKEncoder encoder(bmp);
    EXPECT_TRUE(encoder.unfilteredRewind());
    delete bmp;
}

// Test getChar reads bytes sequentially
TEST_F(SplashBitmapCMYKEncoderTest_247, GetCharReadsSequentially_247) {
    SplashBitmap* bmp = createCMYKBitmap(2, 2);
    SplashBitmapCMYKEncoder encoder(bmp);
    encoder.rewind();

    // Read all bytes (2 * 2 * 4 = 16 CMYK bytes)
    std::vector<int> bytes;
    for (int i = 0; i < 2 * 2 * 4; i++) {
        int ch = encoder.getChar();
        EXPECT_NE(ch, EOF) << "Unexpected EOF at byte " << i;
        bytes.push_back(ch);
    }
    delete bmp;
}

// Test getChar returns EOF after all data is read
TEST_F(SplashBitmapCMYKEncoderTest_247, GetCharReturnsEOFAtEnd_247) {
    SplashBitmap* bmp = createCMYKBitmap(1, 1);
    SplashBitmapCMYKEncoder encoder(bmp);
    encoder.rewind();

    // 1x1 CMYK = 4 bytes
    for (int i = 0; i < 4; i++) {
        int ch = encoder.getChar();
        EXPECT_NE(ch, EOF);
    }
    // Next should be EOF
    int ch = encoder.getChar();
    EXPECT_EQ(ch, EOF);
    delete bmp;
}

// Test lookChar doesn't advance position
TEST_F(SplashBitmapCMYKEncoderTest_247, LookCharDoesNotAdvance_247) {
    SplashBitmap* bmp = createCMYKBitmap(2, 2);
    SplashBitmapCMYKEncoder encoder(bmp);
    encoder.rewind();

    int first = encoder.lookChar();
    int second = encoder.lookChar();
    EXPECT_EQ(first, second);

    // After getChar, it should advance
    int read = encoder.getChar();
    EXPECT_EQ(first, read);

    int next = encoder.lookChar();
    // Next lookChar might differ from first
    // Just verify lookChar still works
    int nextAgain = encoder.lookChar();
    EXPECT_EQ(next, nextAgain);
    delete bmp;
}

// Test getPos returns 0 after rewind
TEST_F(SplashBitmapCMYKEncoderTest_247, GetPosAfterRewind_247) {
    SplashBitmap* bmp = createCMYKBitmap(4, 4);
    SplashBitmapCMYKEncoder encoder(bmp);
    encoder.rewind();
    EXPECT_EQ(encoder.getPos(), 0);
    delete bmp;
}

// Test getPos advances after reading
TEST_F(SplashBitmapCMYKEncoderTest_247, GetPosAdvancesAfterRead_247) {
    SplashBitmap* bmp = createCMYKBitmap(4, 4);
    SplashBitmapCMYKEncoder encoder(bmp);
    encoder.rewind();

    Goffset pos0 = encoder.getPos();
    encoder.getChar();
    Goffset pos1 = encoder.getPos();
    EXPECT_GT(pos1, pos0);
    delete bmp;
}

// Test rewind resets position after reading
TEST_F(SplashBitmapCMYKEncoderTest_247, RewindResetsPosition_247) {
    SplashBitmap* bmp = createCMYKBitmap(2, 2);
    SplashBitmapCMYKEncoder encoder(bmp);
    encoder.rewind();

    int firstByte = encoder.getChar();
    encoder.getChar();
    encoder.getChar();

    encoder.rewind();
    int afterRewind = encoder.getChar();
    EXPECT_EQ(firstByte, afterRewind);
    delete bmp;
}

// Test reading entire bitmap data and verifying consistency
TEST_F(SplashBitmapCMYKEncoderTest_247, ReadEntireBitmapConsistency_247) {
    int w = 3, h = 3;
    SplashBitmap* bmp = createCMYKBitmap(w, h);
    SplashBitmapCMYKEncoder encoder(bmp);
    encoder.rewind();

    std::vector<int> firstPass;
    int ch;
    while ((ch = encoder.getChar()) != EOF) {
        firstPass.push_back(ch);
    }

    // Rewind and read again
    encoder.rewind();
    std::vector<int> secondPass;
    while ((ch = encoder.getChar()) != EOF) {
        secondPass.push_back(ch);
    }

    EXPECT_EQ(firstPass.size(), secondPass.size());
    EXPECT_EQ(firstPass, secondPass);
    delete bmp;
}

// Test with a 1-pixel wide bitmap
TEST_F(SplashBitmapCMYKEncoderTest_247, SinglePixelWideBitmap_247) {
    SplashBitmap* bmp = createCMYKBitmap(1, 5);
    SplashBitmapCMYKEncoder encoder(bmp);
    encoder.rewind();

    int count = 0;
    while (encoder.getChar() != EOF) {
        count++;
    }
    // 1 * 5 * 4 = 20 bytes
    EXPECT_EQ(count, 20);
    delete bmp;
}

// Test with a 1-pixel tall bitmap
TEST_F(SplashBitmapCMYKEncoderTest_247, SinglePixelTallBitmap_247) {
    SplashBitmap* bmp = createCMYKBitmap(5, 1);
    SplashBitmapCMYKEncoder encoder(bmp);
    encoder.rewind();

    int count = 0;
    while (encoder.getChar() != EOF) {
        count++;
    }
    // 5 * 1 * 4 = 20 bytes
    EXPECT_EQ(count, 20);
    delete bmp;
}

// Test getPSFilter returns nullopt (typical for encoders)
TEST_F(SplashBitmapCMYKEncoderTest_247, GetPSFilter_247) {
    SplashBitmap* bmp = createCMYKBitmap(4, 4);
    SplashBitmapCMYKEncoder encoder(bmp);
    auto result = encoder.getPSFilter(1, "");
    // Encoders typically don't have PS filters
    EXPECT_FALSE(result.has_value());
    delete bmp;
}

// Test getUnfilteredChar reads the same as getChar after rewind
TEST_F(SplashBitmapCMYKEncoderTest_247, GetUnfilteredChar_247) {
    SplashBitmap* bmp = createCMYKBitmap(2, 2);
    SplashBitmapCMYKEncoder encoder(bmp);
    encoder.rewind();

    int ch = encoder.getUnfilteredChar();
    EXPECT_NE(ch, EOF);
    delete bmp;
}

// Test larger bitmap to exercise buffer refilling
TEST_F(SplashBitmapCMYKEncoderTest_247, LargerBitmapBufferRefill_247) {
    // Create a bitmap large enough to require multiple buffer fills
    int w = 100, h = 100;
    SplashBitmap* bmp = createCMYKBitmap(w, h);
    SplashBitmapCMYKEncoder encoder(bmp);
    encoder.rewind();

    int count = 0;
    while (encoder.getChar() != EOF) {
        count++;
    }
    // 100 * 100 * 4 = 40000 bytes
    EXPECT_EQ(count, w * h * 4);
    delete bmp;
}

// Test getBaseStream returns nullptr or valid pointer
TEST_F(SplashBitmapCMYKEncoderTest_247, GetBaseStream_247) {
    SplashBitmap* bmp = createCMYKBitmap(2, 2);
    SplashBitmapCMYKEncoder encoder(bmp);
    // For an encoder stream, getBaseStream may return nullptr
    BaseStream* base = encoder.getBaseStream();
    // Just verify it doesn't crash; the return value depends on implementation
    (void)base;
    delete bmp;
}

// Test getDict and getDictObject
TEST_F(SplashBitmapCMYKEncoderTest_247, GetDictAndDictObject_247) {
    SplashBitmap* bmp = createCMYKBitmap(2, 2);
    SplashBitmapCMYKEncoder encoder(bmp);
    // These may return nullptr for encoder streams
    Dict* dict = encoder.getDict();
    Object* dictObj = encoder.getDictObject();
    (void)dict;
    (void)dictObj;
    // Just verify no crash
    delete bmp;
}

// Test setPos (may be a no-op for encoder streams, but shouldn't crash)
TEST_F(SplashBitmapCMYKEncoderTest_247, SetPosDoesNotCrash_247) {
    SplashBitmap* bmp = createCMYKBitmap(4, 4);
    SplashBitmapCMYKEncoder encoder(bmp);
    encoder.rewind();
    encoder.setPos(0, 0);
    // Just verify no crash
    delete bmp;
}

// Test multiple rewinds
TEST_F(SplashBitmapCMYKEncoderTest_247, MultipleRewinds_247) {
    SplashBitmap* bmp = createCMYKBitmap(2, 2);
    SplashBitmapCMYKEncoder encoder(bmp);

    for (int iter = 0; iter < 5; iter++) {
        EXPECT_TRUE(encoder.rewind());
        int firstByte = encoder.getChar();
        EXPECT_NE(firstByte, EOF);
    }
    delete bmp;
}

// Test lookChar at EOF
TEST_F(SplashBitmapCMYKEncoderTest_247, LookCharAtEOF_247) {
    SplashBitmap* bmp = createCMYKBitmap(1, 1);
    SplashBitmapCMYKEncoder encoder(bmp);
    encoder.rewind();

    // Read all 4 bytes
    for (int i = 0; i < 4; i++) {
        encoder.getChar();
    }

    // lookChar at EOF should return EOF
    EXPECT_EQ(encoder.lookChar(), EOF);
    delete bmp;
}

// Test getUndecodedStream
TEST_F(SplashBitmapCMYKEncoderTest_247, GetUndecodedStream_247) {
    SplashBitmap* bmp = createCMYKBitmap(2, 2);
    SplashBitmapCMYKEncoder encoder(bmp);
    Stream* undecoded = encoder.getUndecodedStream();
    // For encoder streams this likely returns 'this' or nullptr
    (void)undecoded;
    delete bmp;
}
