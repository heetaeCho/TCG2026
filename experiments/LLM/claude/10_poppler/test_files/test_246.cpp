#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "poppler/Stream.h"
#include "poppler/SplashOutputDev.h"
#include "splash/SplashBitmap.h"
#include "splash/SplashTypes.h"

class SplashBitmapCMYKEncoderTest_246 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    SplashBitmap* createCMYKBitmap(int w, int h) {
        // Create a CMYK bitmap (splashModeCMYK8 = 4 bytes per pixel)
        SplashBitmap* bmp = new SplashBitmap(w, h, 4 * w, splashModeCMYK8, false);
        // Fill with some known data
        SplashColorPtr data = bmp->getDataPtr();
        int rowSize = bmp->getRowSize();
        for (int y = 0; y < h; y++) {
            for (int x = 0; x < w * 4; x++) {
                data[y * rowSize + x] = (unsigned char)((x + y) & 0xFF);
            }
        }
        return bmp;
    }
};

// Test that the encoder can be constructed with a valid CMYK bitmap
TEST_F(SplashBitmapCMYKEncoderTest_246, ConstructorWithValidBitmap_246) {
    SplashBitmap* bmp = createCMYKBitmap(10, 10);
    SplashBitmapCMYKEncoder* encoder = new SplashBitmapCMYKEncoder(bmp);
    ASSERT_NE(encoder, nullptr);
    delete encoder;
    delete bmp;
}

// Test getKind returns the expected stream kind
TEST_F(SplashBitmapCMYKEncoderTest_246, GetKind_246) {
    SplashBitmap* bmp = createCMYKBitmap(4, 4);
    SplashBitmapCMYKEncoder encoder(bmp);
    StreamKind kind = encoder.getKind();
    // Encoder streams typically return a specific kind
    EXPECT_EQ(kind, strWeird);
    delete bmp;
}

// Test isEncoder returns true
TEST_F(SplashBitmapCMYKEncoderTest_246, IsEncoder_246) {
    SplashBitmap* bmp = createCMYKBitmap(4, 4);
    SplashBitmapCMYKEncoder encoder(bmp);
    EXPECT_TRUE(encoder.isEncoder());
    delete bmp;
}

// Test isBinary returns true
TEST_F(SplashBitmapCMYKEncoderTest_246, IsBinary_246) {
    SplashBitmap* bmp = createCMYKBitmap(4, 4);
    SplashBitmapCMYKEncoder encoder(bmp);
    EXPECT_TRUE(encoder.isBinary(true));
    delete bmp;
}

// Test rewind functionality
TEST_F(SplashBitmapCMYKEncoderTest_246, Rewind_246) {
    SplashBitmap* bmp = createCMYKBitmap(4, 4);
    SplashBitmapCMYKEncoder encoder(bmp);
    
    // Read some chars
    encoder.getChar();
    encoder.getChar();
    
    // Rewind
    bool result = encoder.rewind();
    EXPECT_TRUE(result);
    
    // After rewind, position should be at start
    EXPECT_EQ(encoder.getPos(), 0);
    delete bmp;
}

// Test getChar reads bytes sequentially
TEST_F(SplashBitmapCMYKEncoderTest_246, GetCharSequential_246) {
    SplashBitmap* bmp = createCMYKBitmap(2, 2);
    SplashBitmapCMYKEncoder encoder(bmp);
    encoder.rewind();
    
    // Read first char
    int ch1 = encoder.getChar();
    EXPECT_NE(ch1, EOF);
    
    // Read second char
    int ch2 = encoder.getChar();
    EXPECT_NE(ch2, EOF);
    delete bmp;
}

// Test lookChar does not advance position
TEST_F(SplashBitmapCMYKEncoderTest_246, LookCharDoesNotAdvance_246) {
    SplashBitmap* bmp = createCMYKBitmap(4, 4);
    SplashBitmapCMYKEncoder encoder(bmp);
    encoder.rewind();
    
    int ch1 = encoder.lookChar();
    int ch2 = encoder.lookChar();
    
    // lookChar should return the same value when called twice
    EXPECT_EQ(ch1, ch2);
    delete bmp;
}

// Test lookChar matches subsequent getChar
TEST_F(SplashBitmapCMYKEncoderTest_246, LookCharMatchesGetChar_246) {
    SplashBitmap* bmp = createCMYKBitmap(4, 4);
    SplashBitmapCMYKEncoder encoder(bmp);
    encoder.rewind();
    
    int looked = encoder.lookChar();
    int got = encoder.getChar();
    
    EXPECT_EQ(looked, got);
    delete bmp;
}

// Test getUnfilteredChar delegates to getChar
TEST_F(SplashBitmapCMYKEncoderTest_246, GetUnfilteredCharDelegatesToGetChar_246) {
    SplashBitmap* bmp = createCMYKBitmap(4, 4);
    SplashBitmapCMYKEncoder encoder1(bmp);
    
    // Create a second encoder with the same bitmap to compare
    SplashBitmap* bmp2 = createCMYKBitmap(4, 4);
    SplashBitmapCMYKEncoder encoder2(bmp2);
    
    encoder1.rewind();
    encoder2.rewind();
    
    int charVal = encoder1.getChar();
    int unfilteredVal = encoder2.getUnfilteredChar();
    
    EXPECT_EQ(charVal, unfilteredVal);
    delete bmp;
    delete bmp2;
}

// Test getPos starts at 0 after rewind
TEST_F(SplashBitmapCMYKEncoderTest_246, GetPosStartsAtZero_246) {
    SplashBitmap* bmp = createCMYKBitmap(4, 4);
    SplashBitmapCMYKEncoder encoder(bmp);
    encoder.rewind();
    
    EXPECT_EQ(encoder.getPos(), 0);
    delete bmp;
}

// Test getPos advances after reading
TEST_F(SplashBitmapCMYKEncoderTest_246, GetPosAdvancesAfterRead_246) {
    SplashBitmap* bmp = createCMYKBitmap(4, 4);
    SplashBitmapCMYKEncoder encoder(bmp);
    encoder.rewind();
    
    Goffset pos0 = encoder.getPos();
    encoder.getChar();
    Goffset pos1 = encoder.getPos();
    
    EXPECT_GT(pos1, pos0);
    delete bmp;
}

// Test reading entire bitmap data for small bitmap
TEST_F(SplashBitmapCMYKEncoderTest_246, ReadEntireBitmap_246) {
    int w = 2, h = 2;
    SplashBitmap* bmp = createCMYKBitmap(w, h);
    SplashBitmapCMYKEncoder encoder(bmp);
    encoder.rewind();
    
    int totalBytes = w * h * 4; // CMYK = 4 bytes per pixel
    int count = 0;
    while (encoder.getChar() != EOF) {
        count++;
        if (count > totalBytes + 100) break; // safety guard
    }
    
    // Should read exactly w * h * 4 bytes
    EXPECT_EQ(count, totalBytes);
    delete bmp;
}

// Test EOF after reading all data
TEST_F(SplashBitmapCMYKEncoderTest_246, EOFAfterAllData_246) {
    int w = 1, h = 1;
    SplashBitmap* bmp = createCMYKBitmap(w, h);
    SplashBitmapCMYKEncoder encoder(bmp);
    encoder.rewind();
    
    // Read 4 bytes (CMYK for 1 pixel)
    for (int i = 0; i < 4; i++) {
        int ch = encoder.getChar();
        EXPECT_NE(ch, EOF);
    }
    
    // Next read should be EOF
    int ch = encoder.getChar();
    EXPECT_EQ(ch, EOF);
    delete bmp;
}

// Test getPSFilter returns nullopt
TEST_F(SplashBitmapCMYKEncoderTest_246, GetPSFilter_246) {
    SplashBitmap* bmp = createCMYKBitmap(4, 4);
    SplashBitmapCMYKEncoder encoder(bmp);
    
    auto result = encoder.getPSFilter(1, "");
    // Encoder streams typically don't have PS filters
    EXPECT_FALSE(result.has_value());
    delete bmp;
}

// Test unfilteredRewind
TEST_F(SplashBitmapCMYKEncoderTest_246, UnfilteredRewind_246) {
    SplashBitmap* bmp = createCMYKBitmap(4, 4);
    SplashBitmapCMYKEncoder encoder(bmp);
    
    encoder.getChar();
    encoder.getChar();
    
    bool result = encoder.unfilteredRewind();
    EXPECT_TRUE(result);
    delete bmp;
}

// Test with 1x1 bitmap (boundary)
TEST_F(SplashBitmapCMYKEncoderTest_246, BoundaryOnePixel_246) {
    SplashBitmap* bmp = createCMYKBitmap(1, 1);
    SplashBitmapCMYKEncoder encoder(bmp);
    encoder.rewind();
    
    // Should be able to read exactly 4 bytes
    for (int i = 0; i < 4; i++) {
        EXPECT_NE(encoder.getChar(), EOF);
    }
    EXPECT_EQ(encoder.getChar(), EOF);
    delete bmp;
}

// Test rewind after reading all data allows re-reading
TEST_F(SplashBitmapCMYKEncoderTest_246, RewindAfterFullRead_246) {
    SplashBitmap* bmp = createCMYKBitmap(2, 2);
    SplashBitmapCMYKEncoder encoder(bmp);
    encoder.rewind();
    
    // Read all data
    std::vector<int> firstRead;
    int ch;
    while ((ch = encoder.getChar()) != EOF) {
        firstRead.push_back(ch);
    }
    
    // Rewind and read again
    encoder.rewind();
    std::vector<int> secondRead;
    while ((ch = encoder.getChar()) != EOF) {
        secondRead.push_back(ch);
    }
    
    // Both reads should produce the same data
    EXPECT_EQ(firstRead.size(), secondRead.size());
    EXPECT_EQ(firstRead, secondRead);
    delete bmp;
}

// Test getBaseStream returns nullptr for encoder
TEST_F(SplashBitmapCMYKEncoderTest_246, GetBaseStream_246) {
    SplashBitmap* bmp = createCMYKBitmap(4, 4);
    SplashBitmapCMYKEncoder encoder(bmp);
    
    BaseStream* base = encoder.getBaseStream();
    EXPECT_EQ(base, nullptr);
    delete bmp;
}

// Test getUndecodedStream returns this for encoder
TEST_F(SplashBitmapCMYKEncoderTest_246, GetUndecodedStream_246) {
    SplashBitmap* bmp = createCMYKBitmap(4, 4);
    SplashBitmapCMYKEncoder encoder(bmp);
    
    Stream* undecoded = encoder.getUndecodedStream();
    EXPECT_EQ(undecoded, &encoder);
    delete bmp;
}

// Test getDict returns nullptr for encoder
TEST_F(SplashBitmapCMYKEncoderTest_246, GetDict_246) {
    SplashBitmap* bmp = createCMYKBitmap(4, 4);
    SplashBitmapCMYKEncoder encoder(bmp);
    
    Dict* dict = encoder.getDict();
    EXPECT_EQ(dict, nullptr);
    delete bmp;
}

// Test getDictObject returns nullptr for encoder
TEST_F(SplashBitmapCMYKEncoderTest_246, GetDictObject_246) {
    SplashBitmap* bmp = createCMYKBitmap(4, 4);
    SplashBitmapCMYKEncoder encoder(bmp);
    
    Object* dictObj = encoder.getDictObject();
    EXPECT_EQ(dictObj, nullptr);
    delete bmp;
}

// Test larger bitmap
TEST_F(SplashBitmapCMYKEncoderTest_246, LargerBitmap_246) {
    int w = 100, h = 100;
    SplashBitmap* bmp = createCMYKBitmap(w, h);
    SplashBitmapCMYKEncoder encoder(bmp);
    encoder.rewind();
    
    int totalExpected = w * h * 4;
    int count = 0;
    while (encoder.getChar() != EOF) {
        count++;
        if (count > totalExpected + 100) break;
    }
    
    EXPECT_EQ(count, totalExpected);
    delete bmp;
}
