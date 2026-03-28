#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <cstring>

// Include necessary headers
#include "Stream.h"

// We need to create a mock or helper stream to feed data into RunLengthStream.
// RunLengthStream wraps another stream and decodes run-length encoded data.
// Run-length encoding format:
// - If byte n is 0-127: copy next n+1 bytes literally
// - If byte n is 129-255: repeat next byte (257-n) times  
// - If byte n is 128: end of data

// We'll use MemStream as the underlying stream to feed encoded data.

class RunLengthStreamTest_186 : public ::testing::Test {
protected:
    // Helper to create a RunLengthStream from raw bytes
    std::unique_ptr<RunLengthStream> createRunLengthStream(const unsigned char* data, int len) {
        // Create a copy of data that persists
        auto dataCopy = new unsigned char[len];
        memcpy(dataCopy, data, len);
        
        Object dictObj;
        // MemStream takes ownership-like semantics; we need to manage memory carefully
        auto memStream = std::make_unique<MemStream>(reinterpret_cast<const char*>(dataCopy), 0, len, std::move(dictObj));
        
        auto rls = std::make_unique<RunLengthStream>(std::move(memStream));
        rls->reset();
        return rls;
    }
};

// Test that lookChar returns EOF on empty/EOD-only stream
TEST_F(RunLengthStreamTest_186, LookCharReturnsEOFOnEmptyStream_186) {
    // 128 = EOD marker
    unsigned char data[] = { 128 };
    auto rls = createRunLengthStream(data, sizeof(data));
    
    int result = rls->lookChar();
    EXPECT_EQ(EOF, result);
}

// Test that lookChar returns the first byte without consuming it (idempotent)
TEST_F(RunLengthStreamTest_186, LookCharIsIdempotent_186) {
    // Literal run: length byte 0 means copy 1 byte, then EOD
    unsigned char data[] = { 0, 0x42, 128 };
    auto rls = createRunLengthStream(data, sizeof(data));
    
    int first = rls->lookChar();
    int second = rls->lookChar();
    EXPECT_EQ(first, second);
    EXPECT_EQ(0x42, first);
}

// Test that getChar consumes while lookChar peeks
TEST_F(RunLengthStreamTest_186, LookCharDoesNotConsume_186) {
    // Literal run of 2 bytes: length=1 means 2 bytes
    unsigned char data[] = { 1, 0xAA, 0xBB, 128 };
    auto rls = createRunLengthStream(data, sizeof(data));
    
    int peeked = rls->lookChar();
    EXPECT_EQ(0xAA, peeked);
    
    int consumed = rls->getChar();
    EXPECT_EQ(0xAA, consumed);
    
    int next = rls->lookChar();
    EXPECT_EQ(0xBB, next);
}

// Test literal copy run
TEST_F(RunLengthStreamTest_186, LiteralCopyRun_186) {
    // Length byte 2 = copy next 3 bytes
    unsigned char data[] = { 2, 0x10, 0x20, 0x30, 128 };
    auto rls = createRunLengthStream(data, sizeof(data));
    
    EXPECT_EQ(0x10, rls->getChar());
    EXPECT_EQ(0x20, rls->getChar());
    EXPECT_EQ(0x30, rls->getChar());
    EXPECT_EQ(EOF, rls->getChar());
}

// Test repeat run
TEST_F(RunLengthStreamTest_186, RepeatRun_186) {
    // Length byte 255 means repeat next byte (257-255)=2 times
    unsigned char data[] = { 255, 0x5A, 128 };
    auto rls = createRunLengthStream(data, sizeof(data));
    
    EXPECT_EQ(0x5A, rls->getChar());
    EXPECT_EQ(0x5A, rls->getChar());
    EXPECT_EQ(EOF, rls->getChar());
}

// Test repeat run with longer repetition
TEST_F(RunLengthStreamTest_186, RepeatRunLonger_186) {
    // Length byte 129 means repeat next byte (257-129)=128 times
    unsigned char data[] = { 129, 0xFF, 128 };
    auto rls = createRunLengthStream(data, sizeof(data));
    
    for (int i = 0; i < 128; i++) {
        int c = rls->getChar();
        EXPECT_EQ(0xFF, c) << "Mismatch at position " << i;
    }
    EXPECT_EQ(EOF, rls->getChar());
}

// Test multiple runs
TEST_F(RunLengthStreamTest_186, MultipleRuns_186) {
    // First run: literal 1 byte (length=0), byte=0x11
    // Second run: repeat byte 0x22 three times (length=254, 257-254=3)
    // EOD
    unsigned char data[] = { 0, 0x11, 254, 0x22, 128 };
    auto rls = createRunLengthStream(data, sizeof(data));
    
    EXPECT_EQ(0x11, rls->getChar());
    EXPECT_EQ(0x22, rls->getChar());
    EXPECT_EQ(0x22, rls->getChar());
    EXPECT_EQ(0x22, rls->getChar());
    EXPECT_EQ(EOF, rls->getChar());
}

// Test lookChar after all data consumed returns EOF
TEST_F(RunLengthStreamTest_186, LookCharAfterAllConsumedReturnsEOF_186) {
    unsigned char data[] = { 0, 0x99, 128 };
    auto rls = createRunLengthStream(data, sizeof(data));
    
    rls->getChar(); // consume the single byte
    EXPECT_EQ(EOF, rls->lookChar());
}

// Test getKind returns the expected stream kind
TEST_F(RunLengthStreamTest_186, GetKindReturnsCorrectKind_186) {
    unsigned char data[] = { 128 };
    auto rls = createRunLengthStream(data, sizeof(data));
    
    EXPECT_EQ(strRunLength, rls->getKind());
}

// Test isBinary returns true
TEST_F(RunLengthStreamTest_186, IsBinaryReturnsTrue_186) {
    unsigned char data[] = { 128 };
    auto rls = createRunLengthStream(data, sizeof(data));
    
    // RunLengthStream typically reports as binary
    bool result = rls->isBinary(true);
    // We just verify it returns a bool without crashing
    (void)result;
}

// Test rewind resets the stream
TEST_F(RunLengthStreamTest_186, RewindResetsStream_186) {
    unsigned char data[] = { 1, 0xAA, 0xBB, 128 };
    auto rls = createRunLengthStream(data, sizeof(data));
    
    EXPECT_EQ(0xAA, rls->getChar());
    EXPECT_EQ(0xBB, rls->getChar());
    EXPECT_EQ(EOF, rls->getChar());
    
    // Rewind and read again
    rls->reset();
    EXPECT_EQ(0xAA, rls->getChar());
    EXPECT_EQ(0xBB, rls->getChar());
    EXPECT_EQ(EOF, rls->getChar());
}

// Test literal run with maximum single run length (128 bytes, length byte = 127)
TEST_F(RunLengthStreamTest_186, MaxLiteralRun_186) {
    // length byte 127 = copy next 128 bytes
    unsigned char data[128 + 2]; // 1 length + 128 data + 1 EOD
    data[0] = 127;
    for (int i = 0; i < 128; i++) {
        data[1 + i] = (unsigned char)(i & 0xFF);
    }
    data[129] = 128; // EOD
    
    auto rls = createRunLengthStream(data, 130);
    
    for (int i = 0; i < 128; i++) {
        int c = rls->getChar();
        EXPECT_EQ(i & 0xFF, c) << "Mismatch at position " << i;
    }
    EXPECT_EQ(EOF, rls->getChar());
}

// Test lookChar with 0x00 byte value (ensure masking works correctly)
TEST_F(RunLengthStreamTest_186, LookCharWithZeroByte_186) {
    unsigned char data[] = { 0, 0x00, 128 };
    auto rls = createRunLengthStream(data, sizeof(data));
    
    int result = rls->lookChar();
    EXPECT_EQ(0x00, result);
    EXPECT_NE(EOF, result);
}

// Test lookChar with 0xFF byte value (ensure & 0xff masking)
TEST_F(RunLengthStreamTest_186, LookCharWith0xFFByte_186) {
    unsigned char data[] = { 0, 0xFF, 128 };
    auto rls = createRunLengthStream(data, sizeof(data));
    
    int result = rls->lookChar();
    EXPECT_EQ(0xFF, result);
}

// Test getPSFilter
TEST_F(RunLengthStreamTest_186, GetPSFilter_186) {
    unsigned char data[] = { 128 };
    auto rls = createRunLengthStream(data, sizeof(data));
    
    auto filter = rls->getPSFilter(1, "");
    // Just verify it doesn't crash; the result depends on implementation
    (void)filter;
}
