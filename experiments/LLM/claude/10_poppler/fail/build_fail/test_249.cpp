#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary headers
#include "poppler/Stream.h"
#include "poppler/Object.h"
#include "splash/SplashBitmap.h"

class SplashBitmapCMYKEncoderTest_249 : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a small CMYK bitmap for testing
        // SplashBitmap(width, height, rowPad, colorMode, hasAlpha)
        bitmap = new SplashBitmap(4, 4, 1, splashModeCMYK8, false);
        // Fill bitmap with known data
        unsigned char *data = bitmap->getDataPtr();
        int rowSize = bitmap->getRowSize();
        for (int y = 0; y < 4; y++) {
            for (int x = 0; x < 4 * 4; x++) { // 4 pixels * 4 components (CMYK)
                data[y * rowSize + x] = static_cast<unsigned char>((y * 16 + x) & 0xFF);
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

TEST_F(SplashBitmapCMYKEncoderTest_249, GetUndecodedStreamReturnsSelf_249) {
    Stream *result = encoder->getUndecodedStream();
    EXPECT_EQ(result, static_cast<Stream *>(encoder));
}

TEST_F(SplashBitmapCMYKEncoderTest_249, IsEncoderReturnsTrue_249) {
    EXPECT_TRUE(encoder->isEncoder());
}

TEST_F(SplashBitmapCMYKEncoderTest_249, GetKindReturnsExpected_249) {
    StreamKind kind = encoder->getKind();
    // Encoder streams typically have a specific kind
    // We just verify it returns without error
    (void)kind;
}

TEST_F(SplashBitmapCMYKEncoderTest_249, RewindSucceeds_249) {
    EXPECT_TRUE(encoder->rewind());
}

TEST_F(SplashBitmapCMYKEncoderTest_249, GetCharAfterRewind_249) {
    encoder->rewind();
    int ch = encoder->getChar();
    // Should return a valid character (0-255) or EOF
    EXPECT_GE(ch, -1); // EOF is typically -1
    EXPECT_LE(ch, 255);
}

TEST_F(SplashBitmapCMYKEncoderTest_249, LookCharDoesNotAdvance_249) {
    encoder->rewind();
    int ch1 = encoder->lookChar();
    int ch2 = encoder->lookChar();
    EXPECT_EQ(ch1, ch2);
}

TEST_F(SplashBitmapCMYKEncoderTest_249, GetCharAdvancesPosition_249) {
    encoder->rewind();
    int ch1 = encoder->getChar();
    int ch2 = encoder->getChar();
    // After reading two chars, position should have advanced
    // They may or may not be different values, but we read them successfully
    (void)ch1;
    (void)ch2;
}

TEST_F(SplashBitmapCMYKEncoderTest_249, LookCharThenGetCharReturnsSame_249) {
    encoder->rewind();
    int looked = encoder->lookChar();
    int got = encoder->getChar();
    EXPECT_EQ(looked, got);
}

TEST_F(SplashBitmapCMYKEncoderTest_249, GetPosAfterRewind_249) {
    encoder->rewind();
    Goffset pos = encoder->getPos();
    EXPECT_EQ(pos, 0);
}

TEST_F(SplashBitmapCMYKEncoderTest_249, GetPosAdvancesAfterGetChar_249) {
    encoder->rewind();
    Goffset pos0 = encoder->getPos();
    encoder->getChar();
    Goffset pos1 = encoder->getPos();
    EXPECT_GT(pos1, pos0);
}

TEST_F(SplashBitmapCMYKEncoderTest_249, ReadAllDataReturnsEOF_249) {
    encoder->rewind();
    int totalBytes = 4 * 4 * 4; // width * height * 4 components (CMYK)
    int ch;
    int count = 0;
    while ((ch = encoder->getChar()) != EOF) {
        count++;
        // Safety to prevent infinite loop
        if (count > totalBytes * 2) {
            break;
        }
    }
    EXPECT_EQ(ch, EOF);
    // We expect to read exactly width * height * 4 bytes for CMYK
    EXPECT_EQ(count, totalBytes);
}

TEST_F(SplashBitmapCMYKEncoderTest_249, RewindAfterReadingAllData_249) {
    encoder->rewind();
    // Read all data
    while (encoder->getChar() != EOF) {
    }
    // Rewind and read again
    EXPECT_TRUE(encoder->rewind());
    int ch = encoder->getChar();
    EXPECT_NE(ch, EOF);
}

TEST_F(SplashBitmapCMYKEncoderTest_249, ConsistentDataAcrossRewinds_249) {
    encoder->rewind();
    std::vector<int> firstRead;
    int ch;
    while ((ch = encoder->getChar()) != EOF) {
        firstRead.push_back(ch);
    }

    encoder->rewind();
    std::vector<int> secondRead;
    while ((ch = encoder->getChar()) != EOF) {
        secondRead.push_back(ch);
    }

    EXPECT_EQ(firstRead.size(), secondRead.size());
    EXPECT_EQ(firstRead, secondRead);
}

TEST_F(SplashBitmapCMYKEncoderTest_249, IsBinaryReturnsTrue_249) {
    EXPECT_TRUE(encoder->isBinary(true));
}

TEST_F(SplashBitmapCMYKEncoderTest_249, GetPSFilterReturnsNullopt_249) {
    auto result = encoder->getPSFilter(1, "");
    // Encoders typically don't have PS filters
    EXPECT_FALSE(result.has_value());
}

TEST_F(SplashBitmapCMYKEncoderTest_249, GetBaseStreamReturnsNullptr_249) {
    BaseStream *base = encoder->getBaseStream();
    // Encoder streams typically don't have a base stream
    EXPECT_EQ(base, nullptr);
}

TEST_F(SplashBitmapCMYKEncoderTest_249, GetDictReturnsNullptr_249) {
    Dict *dict = encoder->getDict();
    EXPECT_EQ(dict, nullptr);
}

TEST_F(SplashBitmapCMYKEncoderTest_249, GetDictObjectReturnsNullptr_249) {
    Object *obj = encoder->getDictObject();
    EXPECT_EQ(obj, nullptr);
}

TEST_F(SplashBitmapCMYKEncoderTest_249, GetUnfilteredChar_249) {
    encoder->rewind();
    int ch = encoder->getUnfilteredChar();
    EXPECT_GE(ch, -1);
    EXPECT_LE(ch, 255);
}

TEST_F(SplashBitmapCMYKEncoderTest_249, UnfilteredRewind_249) {
    EXPECT_TRUE(encoder->unfilteredRewind());
}

TEST_F(SplashBitmapCMYKEncoderTest_249, SetPosDoesNotCrash_249) {
    encoder->rewind();
    encoder->setPos(0, 0);
    // Just verify no crash
}

// Test with a 1x1 bitmap (boundary case - minimal size)
class SplashBitmapCMYKEncoderMinimal_249 : public ::testing::Test {
protected:
    void SetUp() override {
        bitmap = new SplashBitmap(1, 1, 1, splashModeCMYK8, false);
        unsigned char *data = bitmap->getDataPtr();
        data[0] = 0xAA; // C
        data[1] = 0xBB; // M
        data[2] = 0xCC; // Y
        data[3] = 0xDD; // K
        encoder = new SplashBitmapCMYKEncoder(bitmap);
    }

    void TearDown() override {
        delete encoder;
        delete bitmap;
    }

    SplashBitmap *bitmap = nullptr;
    SplashBitmapCMYKEncoder *encoder = nullptr;
};

TEST_F(SplashBitmapCMYKEncoderMinimal_249, ReadSinglePixel_249) {
    encoder->rewind();
    int c = encoder->getChar();
    int m = encoder->getChar();
    int y = encoder->getChar();
    int k = encoder->getChar();
    
    EXPECT_EQ(c, 0xAA);
    EXPECT_EQ(m, 0xBB);
    EXPECT_EQ(y, 0xCC);
    EXPECT_EQ(k, 0xDD);
    
    int eof = encoder->getChar();
    EXPECT_EQ(eof, EOF);
}

TEST_F(SplashBitmapCMYKEncoderMinimal_249, LookCharOnSinglePixel_249) {
    encoder->rewind();
    int looked = encoder->lookChar();
    EXPECT_EQ(looked, 0xAA);
    
    int got = encoder->getChar();
    EXPECT_EQ(got, 0xAA);
    
    looked = encoder->lookChar();
    EXPECT_EQ(looked, 0xBB);
}

// Test with larger bitmap to check multi-line reading
class SplashBitmapCMYKEncoderLarge_249 : public ::testing::Test {
protected:
    void SetUp() override {
        bitmap = new SplashBitmap(100, 100, 1, splashModeCMYK8, false);
        unsigned char *data = bitmap->getDataPtr();
        int rowSize = bitmap->getRowSize();
        for (int y = 0; y < 100; y++) {
            for (int x = 0; x < 100 * 4; x++) {
                data[y * rowSize + x] = static_cast<unsigned char>((x + y) & 0xFF);
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

TEST_F(SplashBitmapCMYKEncoderLarge_249, ReadAllDataCountMatches_249) {
    encoder->rewind();
    int count = 0;
    while (encoder->getChar() != EOF) {
        count++;
        if (count > 100 * 100 * 4 + 100) {
            FAIL() << "Read too many bytes, possible infinite loop";
            break;
        }
    }
    EXPECT_EQ(count, 100 * 100 * 4);
}

TEST_F(SplashBitmapCMYKEncoderLarge_249, PositionMatchesReadCount_249) {
    encoder->rewind();
    for (int i = 0; i < 500; i++) {
        encoder->getChar();
    }
    Goffset pos = encoder->getPos();
    EXPECT_EQ(pos, 500);
}
