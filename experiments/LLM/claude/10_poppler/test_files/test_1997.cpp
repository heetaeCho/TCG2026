#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "JPEG2000Stream.h"
#include "Stream.h"
#include <cstring>
#include <vector>

// A minimal MemStream-based test to exercise JPXStream through its public interface
class JPXStreamTest_1997 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    // Helper to create a minimal JPEG2000 stream from raw bytes
    std::unique_ptr<JPXStream> createJPXStream(const unsigned char *data, int len) {
        // We need a base stream. Using a MemStream.
        Object dictObj;
        dictObj.initNull();
        // MemStream takes ownership-like semantics; we need to keep data alive
        auto *dataCopy = new char[len];
        std::memcpy(dataCopy, data, len);
        MemStream *memStream = new MemStream(dataCopy, 0, len, std::move(dictObj));
        auto jpxStream = std::make_unique<JPXStream>(memStream);
        return jpxStream;
    }
};

// Test that creating a JPXStream with empty/invalid data returns EOF on getChar
TEST_F(JPXStreamTest_1997, EmptyStreamReturnsEOF_1997) {
    const unsigned char emptyData[] = {0};
    auto jpx = createJPXStream(emptyData, 0);
    jpx->reset();
    int ch = jpx->getChar();
    EXPECT_EQ(ch, EOF);
}

// Test that creating a JPXStream with invalid JPEG2000 data returns EOF
TEST_F(JPXStreamTest_1997, InvalidDataReturnsEOF_1997) {
    const unsigned char invalidData[] = {0x00, 0x01, 0x02, 0x03, 0x04};
    auto jpx = createJPXStream(invalidData, sizeof(invalidData));
    jpx->reset();
    int ch = jpx->getChar();
    EXPECT_EQ(ch, EOF);
}

// Test that lookChar on invalid stream returns EOF
TEST_F(JPXStreamTest_1997, LookCharOnInvalidStreamReturnsEOF_1997) {
    const unsigned char invalidData[] = {0xFF, 0xFE, 0x00, 0x01};
    auto jpx = createJPXStream(invalidData, sizeof(invalidData));
    jpx->reset();
    int ch = jpx->lookChar();
    EXPECT_EQ(ch, EOF);
}

// Test that lookChar is idempotent (calling it twice returns same value)
TEST_F(JPXStreamTest_1997, LookCharIsIdempotent_1997) {
    const unsigned char invalidData[] = {0x00, 0x00, 0x00};
    auto jpx = createJPXStream(invalidData, sizeof(invalidData));
    jpx->reset();
    int ch1 = jpx->lookChar();
    int ch2 = jpx->lookChar();
    EXPECT_EQ(ch1, ch2);
}

// Test getPos returns a valid position
TEST_F(JPXStreamTest_1997, GetPosReturnsValidPosition_1997) {
    const unsigned char data[] = {0x00};
    auto jpx = createJPXStream(data, sizeof(data));
    jpx->reset();
    Goffset pos = jpx->getPos();
    EXPECT_GE(pos, 0);
}

// Test that after reset, repeated getChar on empty data consistently returns EOF
TEST_F(JPXStreamTest_1997, RepeatedGetCharOnEmptyReturnsEOF_1997) {
    const unsigned char data[] = {0x00};
    auto jpx = createJPXStream(data, 0);
    jpx->reset();
    for (int i = 0; i < 10; i++) {
        EXPECT_EQ(jpx->getChar(), EOF);
    }
}

// Test getKind returns expected stream kind
TEST_F(JPXStreamTest_1997, GetKindReturnsJPXStreamKind_1997) {
    const unsigned char data[] = {0x00};
    auto jpx = createJPXStream(data, sizeof(data));
    StreamKind kind = jpx->getKind();
    EXPECT_EQ(kind, strJPX);
}
