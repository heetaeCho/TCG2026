#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Stream.h"
#include "SplashBitmap.h"

class SplashBitmapCMYKEncoderTest_242 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that getKind returns strWeird
TEST_F(SplashBitmapCMYKEncoderTest_242, GetKindReturnsStrWeird_242) {
    // Create a CMYK bitmap (splashModeCMYK8 = 4 components)
    SplashBitmap bitmap(10, 10, 4, splashModeCMYK8, false);
    SplashBitmapCMYKEncoder encoder(&bitmap);
    
    EXPECT_EQ(encoder.getKind(), strWeird);
}

// Test that isEncoder returns true
TEST_F(SplashBitmapCMYKEncoderTest_242, IsEncoderReturnsTrue_242) {
    SplashBitmap bitmap(10, 10, 4, splashModeCMYK8, false);
    SplashBitmapCMYKEncoder encoder(&bitmap);
    
    EXPECT_TRUE(encoder.isEncoder());
}

// Test that isBinary returns expected value
TEST_F(SplashBitmapCMYKEncoderTest_242, IsBinaryTest_242) {
    SplashBitmap bitmap(10, 10, 4, splashModeCMYK8, false);
    SplashBitmapCMYKEncoder encoder(&bitmap);
    
    // Binary encoder should return true
    EXPECT_TRUE(encoder.isBinary(true));
    EXPECT_TRUE(encoder.isBinary(false));
}

// Test rewind functionality
TEST_F(SplashBitmapCMYKEncoderTest_242, RewindTest_242) {
    SplashBitmap bitmap(10, 10, 4, splashModeCMYK8, false);
    SplashBitmapCMYKEncoder encoder(&bitmap);
    
    // Rewind should succeed
    EXPECT_TRUE(encoder.rewind());
}

// Test getChar reads bytes from bitmap
TEST_F(SplashBitmapCMYKEncoderTest_242, GetCharReadsData_242) {
    SplashBitmap bitmap(2, 2, 4, splashModeCMYK8, false);
    SplashBitmapCMYKEncoder encoder(&bitmap);
    
    encoder.rewind();
    
    // Should be able to read characters; CMYK = 4 bytes per pixel, 2x2 = 16 bytes
    int ch = encoder.getChar();
    // We just verify it returns a valid byte or EOF
    EXPECT_TRUE(ch >= 0 || ch == EOF);
}

// Test lookChar does not advance position
TEST_F(SplashBitmapCMYKEncoderTest_242, LookCharDoesNotAdvance_242) {
    SplashBitmap bitmap(2, 2, 4, splashModeCMYK8, false);
    SplashBitmapCMYKEncoder encoder(&bitmap);
    
    encoder.rewind();
    
    int ch1 = encoder.lookChar();
    int ch2 = encoder.lookChar();
    
    // lookChar should return the same value when called twice without getChar
    EXPECT_EQ(ch1, ch2);
}

// Test that lookChar and getChar return the same value
TEST_F(SplashBitmapCMYKEncoderTest_242, LookCharMatchesGetChar_242) {
    SplashBitmap bitmap(2, 2, 4, splashModeCMYK8, false);
    SplashBitmapCMYKEncoder encoder(&bitmap);
    
    encoder.rewind();
    
    int looked = encoder.lookChar();
    int got = encoder.getChar();
    
    EXPECT_EQ(looked, got);
}

// Test getPos returns position
TEST_F(SplashBitmapCMYKEncoderTest_242, GetPosInitiallyZero_242) {
    SplashBitmap bitmap(2, 2, 4, splashModeCMYK8, false);
    SplashBitmapCMYKEncoder encoder(&bitmap);
    
    encoder.rewind();
    
    EXPECT_EQ(encoder.getPos(), 0);
}

// Test getPos advances after getChar
TEST_F(SplashBitmapCMYKEncoderTest_242, GetPosAdvancesAfterGetChar_242) {
    SplashBitmap bitmap(2, 2, 4, splashModeCMYK8, false);
    SplashBitmapCMYKEncoder encoder(&bitmap);
    
    encoder.rewind();
    Goffset pos0 = encoder.getPos();
    
    encoder.getChar();
    Goffset pos1 = encoder.getPos();
    
    EXPECT_GT(pos1, pos0);
}

// Test reading entire bitmap data
TEST_F(SplashBitmapCMYKEncoderTest_242, ReadEntireBitmapData_242) {
    int w = 3, h = 3;
    SplashBitmap bitmap(w, h, 4, splashModeCMYK8, false);
    SplashBitmapCMYKEncoder encoder(&bitmap);
    
    encoder.rewind();
    
    int count = 0;
    while (encoder.getChar() != EOF) {
        count++;
    }
    
    // CMYK = 4 bytes per pixel, so total = w * h * 4
    EXPECT_EQ(count, w * h * 4);
}

// Test EOF after all data is read
TEST_F(SplashBitmapCMYKEncoderTest_242, ReturnsEOFAfterAllData_242) {
    SplashBitmap bitmap(1, 1, 4, splashModeCMYK8, false);
    SplashBitmapCMYKEncoder encoder(&bitmap);
    
    encoder.rewind();
    
    // 1x1 CMYK = 4 bytes
    for (int i = 0; i < 4; i++) {
        int ch = encoder.getChar();
        EXPECT_NE(ch, EOF);
    }
    
    // Next should be EOF
    EXPECT_EQ(encoder.getChar(), EOF);
}

// Test lookChar returns EOF when at end
TEST_F(SplashBitmapCMYKEncoderTest_242, LookCharReturnsEOFAtEnd_242) {
    SplashBitmap bitmap(1, 1, 4, splashModeCMYK8, false);
    SplashBitmapCMYKEncoder encoder(&bitmap);
    
    encoder.rewind();
    
    // Read all bytes
    for (int i = 0; i < 4; i++) {
        encoder.getChar();
    }
    
    EXPECT_EQ(encoder.lookChar(), EOF);
}

// Test rewind after partial read
TEST_F(SplashBitmapCMYKEncoderTest_242, RewindAfterPartialRead_242) {
    SplashBitmap bitmap(2, 2, 4, splashModeCMYK8, false);
    SplashBitmapCMYKEncoder encoder(&bitmap);
    
    encoder.rewind();
    
    // Read some bytes
    encoder.getChar();
    encoder.getChar();
    
    // Rewind
    encoder.rewind();
    
    // Position should be back to 0
    EXPECT_EQ(encoder.getPos(), 0);
    
    // Should be able to read from the start again
    int ch = encoder.getChar();
    EXPECT_NE(ch, EOF);
}

// Test getPSFilter returns nullopt (encoders typically don't have PS filters)
TEST_F(SplashBitmapCMYKEncoderTest_242, GetPSFilterReturnsNullopt_242) {
    SplashBitmap bitmap(2, 2, 4, splashModeCMYK8, false);
    SplashBitmapCMYKEncoder encoder(&bitmap);
    
    auto result = encoder.getPSFilter(1, "");
    // Encoders typically return nullopt/empty
    EXPECT_FALSE(result.has_value());
}

// Test unfilteredRewind
TEST_F(SplashBitmapCMYKEncoderTest_242, UnfilteredRewindTest_242) {
    SplashBitmap bitmap(2, 2, 4, splashModeCMYK8, false);
    SplashBitmapCMYKEncoder encoder(&bitmap);
    
    encoder.rewind();
    encoder.getChar();
    
    bool result = encoder.unfilteredRewind();
    EXPECT_TRUE(result);
}

// Test getUnfilteredChar
TEST_F(SplashBitmapCMYKEncoderTest_242, GetUnfilteredCharTest_242) {
    SplashBitmap bitmap(2, 2, 4, splashModeCMYK8, false);
    SplashBitmapCMYKEncoder encoder(&bitmap);
    
    encoder.rewind();
    
    int ch = encoder.getUnfilteredChar();
    EXPECT_TRUE(ch >= 0 || ch == EOF);
}

// Test with 1x1 bitmap (minimal size)
TEST_F(SplashBitmapCMYKEncoderTest_242, MinimalBitmap_242) {
    SplashBitmap bitmap(1, 1, 4, splashModeCMYK8, false);
    SplashBitmapCMYKEncoder encoder(&bitmap);
    
    encoder.rewind();
    
    int count = 0;
    while (encoder.getChar() != EOF) {
        count++;
    }
    
    EXPECT_EQ(count, 4);  // 1 pixel * 4 CMYK components
}

// Test getBaseStream returns nullptr for encoder
TEST_F(SplashBitmapCMYKEncoderTest_242, GetBaseStreamTest_242) {
    SplashBitmap bitmap(2, 2, 4, splashModeCMYK8, false);
    SplashBitmapCMYKEncoder encoder(&bitmap);
    
    BaseStream* base = encoder.getBaseStream();
    // Encoder streams typically don't have a base stream
    EXPECT_EQ(base, nullptr);
}

// Test getUndecodedStream
TEST_F(SplashBitmapCMYKEncoderTest_242, GetUndecodedStreamTest_242) {
    SplashBitmap bitmap(2, 2, 4, splashModeCMYK8, false);
    SplashBitmapCMYKEncoder encoder(&bitmap);
    
    Stream* undecoded = encoder.getUndecodedStream();
    // Should return itself or nullptr
    EXPECT_TRUE(undecoded == &encoder || undecoded == nullptr);
}

// Test multiple rewinds
TEST_F(SplashBitmapCMYKEncoderTest_242, MultipleRewinds_242) {
    SplashBitmap bitmap(2, 2, 4, splashModeCMYK8, false);
    SplashBitmapCMYKEncoder encoder(&bitmap);
    
    for (int r = 0; r < 3; r++) {
        encoder.rewind();
        EXPECT_EQ(encoder.getPos(), 0);
        
        int first = encoder.getChar();
        EXPECT_NE(first, EOF);
    }
}

// Test consistency: reading data after rewind gives same results
TEST_F(SplashBitmapCMYKEncoderTest_242, ConsistentDataAfterRewind_242) {
    SplashBitmap bitmap(2, 2, 4, splashModeCMYK8, false);
    SplashBitmapCMYKEncoder encoder(&bitmap);
    
    encoder.rewind();
    std::vector<int> firstRead;
    int ch;
    while ((ch = encoder.getChar()) != EOF) {
        firstRead.push_back(ch);
    }
    
    encoder.rewind();
    std::vector<int> secondRead;
    while ((ch = encoder.getChar()) != EOF) {
        secondRead.push_back(ch);
    }
    
    EXPECT_EQ(firstRead, secondRead);
}
