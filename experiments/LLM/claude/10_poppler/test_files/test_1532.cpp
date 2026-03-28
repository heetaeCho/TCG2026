#include <gtest/gtest.h>
#include <memory>
#include "poppler/Decrypt.h"
#include "poppler/Stream.h"
#include "poppler/Object.h"

// We need a concrete Stream to use as input to BaseCryptStream
// MemStream is available in poppler
class BaseCryptStreamTest_1532 : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a simple buffer for MemStream
        bufSize = 64;
        buf = new char[bufSize];
        for (int i = 0; i < bufSize; i++) {
            buf[i] = static_cast<char>(i);
        }
        
        fileKey = new unsigned char[16];
        memset(fileKey, 0, 16);
    }

    void TearDown() override {
        delete[] fileKey;
        // buf is owned by MemStream after creation, or we manage it
    }

    std::unique_ptr<BaseCryptStream> createStream(CryptAlgorithm algo, int keyLength) {
        char *bufCopy = new char[bufSize];
        memcpy(bufCopy, buf, bufSize);
        
        auto memStream = std::make_unique<MemStream>(bufCopy, 0, bufSize, Object(objNull));
        Ref ref;
        ref.num = 1;
        ref.gen = 0;
        // Note: EncryptStream and DecryptStream are the concrete classes
        // BaseCryptStream is abstract-ish but EncryptStream/DecryptStream derive from it
        // We'll use DecryptStream as a concrete instantiation
        return std::make_unique<DecryptStream>(std::move(memStream), fileKey, algo, keyLength, ref);
    }

    char *buf;
    int bufSize;
    unsigned char *fileKey;
};

TEST_F(BaseCryptStreamTest_1532, GetKindReturnsCrypt_1532) {
    auto stream = createStream(cryptRC4, 16);
    EXPECT_EQ(stream->getKind(), strCrypt);
}

TEST_F(BaseCryptStreamTest_1532, GetKindReturnsCryptForAES_1532) {
    auto stream = createStream(cryptAES, 16);
    EXPECT_EQ(stream->getKind(), strCrypt);
}

TEST_F(BaseCryptStreamTest_1532, GetKindReturnsCryptForAES256_1532) {
    auto stream = createStream(cryptAES256, 32);
    EXPECT_EQ(stream->getKind(), strCrypt);
}

TEST_F(BaseCryptStreamTest_1532, InitialPositionIsZero_1532) {
    auto stream = createStream(cryptRC4, 16);
    stream->reset();
    EXPECT_EQ(stream->getPos(), 0);
}

TEST_F(BaseCryptStreamTest_1532, RewindResetsPosition_1532) {
    auto stream = createStream(cryptRC4, 16);
    stream->reset();
    // Read some characters
    stream->getChar();
    stream->getChar();
    EXPECT_GT(stream->getPos(), 0);
    
    // Rewind should reset
    bool result = stream->rewind();
    EXPECT_TRUE(result);
}

TEST_F(BaseCryptStreamTest_1532, GetCharAdvancesPosition_1532) {
    auto stream = createStream(cryptRC4, 16);
    stream->reset();
    Goffset posBefore = stream->getPos();
    int ch = stream->getChar();
    Goffset posAfter = stream->getPos();
    // getChar should advance position by 1 (if not EOF)
    if (ch != EOF) {
        EXPECT_EQ(posAfter, posBefore + 1);
    }
}

TEST_F(BaseCryptStreamTest_1532, LookCharDoesNotAdvancePosition_1532) {
    auto stream = createStream(cryptRC4, 16);
    stream->reset();
    Goffset posBefore = stream->getPos();
    int ch = stream->lookChar();
    Goffset posAfter = stream->getPos();
    EXPECT_EQ(posBefore, posAfter);
}

TEST_F(BaseCryptStreamTest_1532, LookCharAndGetCharReturnSameValue_1532) {
    auto stream = createStream(cryptRC4, 16);
    stream->reset();
    int looked = stream->lookChar();
    int got = stream->getChar();
    EXPECT_EQ(looked, got);
}

TEST_F(BaseCryptStreamTest_1532, IsBinaryReturnsTrue_1532) {
    auto stream = createStream(cryptRC4, 16);
    // Crypt streams are typically binary
    EXPECT_TRUE(stream->isBinary(true));
}

TEST_F(BaseCryptStreamTest_1532, GetUndecodedStreamReturnsNonNull_1532) {
    auto stream = createStream(cryptRC4, 16);
    Stream *undecoded = stream->getUndecodedStream();
    EXPECT_NE(undecoded, nullptr);
}

TEST_F(BaseCryptStreamTest_1532, ReadEntireStreamRC4_1532) {
    auto stream = createStream(cryptRC4, 16);
    stream->reset();
    int count = 0;
    while (stream->getChar() != EOF) {
        count++;
        if (count > bufSize * 2) {
            break; // Safety to avoid infinite loop
        }
    }
    // Should have read some characters (the decrypted output)
    EXPECT_GT(count, 0);
    EXPECT_LE(count, bufSize * 2);
}

TEST_F(BaseCryptStreamTest_1532, EncryptStreamGetKind_1532) {
    char *bufCopy = new char[bufSize];
    memcpy(bufCopy, buf, bufSize);
    
    auto memStream = std::make_unique<MemStream>(bufCopy, 0, bufSize, Object(objNull));
    Ref ref;
    ref.num = 1;
    ref.gen = 0;
    
    auto encStream = std::make_unique<EncryptStream>(std::move(memStream), fileKey, cryptRC4, 16, ref);
    EXPECT_EQ(encStream->getKind(), strCrypt);
}

TEST_F(BaseCryptStreamTest_1532, MultipleRewinds_1532) {
    auto stream = createStream(cryptRC4, 16);
    stream->reset();
    
    int firstChar = stream->getChar();
    
    stream->rewind();
    stream->reset();
    
    int firstCharAgain = stream->getChar();
    
    // After rewind and reset, should get same first character
    EXPECT_EQ(firstChar, firstCharAgain);
}

TEST_F(BaseCryptStreamTest_1532, ConsecutiveGetCharsReturnDifferentPositions_1532) {
    auto stream = createStream(cryptRC4, 16);
    stream->reset();
    
    stream->getChar();
    Goffset pos1 = stream->getPos();
    stream->getChar();
    Goffset pos2 = stream->getPos();
    
    EXPECT_EQ(pos2, pos1 + 1);
}
