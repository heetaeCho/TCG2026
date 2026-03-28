#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "Stream.h"

// We need to create a helper stream that feeds data to RunLengthStream.
// RunLengthStream expects a stream that provides run-length encoded data.
// 
// Run-length encoding format:
// - If byte n is 0-127: copy the next n+1 bytes literally
// - If byte n is 129-255: repeat the next byte (257-n) times
// - If byte n is 128: end of data (EOD marker)

// We'll use a MemStream to feed known data into RunLengthStream.

class RunLengthStreamTest_185 : public ::testing::Test {
protected:
    std::unique_ptr<RunLengthStream> createRunLengthStream(const unsigned char* data, int len) {
        // Create a copy of data that persists
        auto dataCopy = new char[len];
        memcpy(dataCopy, data, len);
        
        Object obj;
        auto memStream = std::make_unique<MemStream>(dataCopy, 0, len, std::move(obj));
        auto rls = std::make_unique<RunLengthStream>(std::move(memStream));
        rls->reset();
        return rls;
    }
};

// Test: EOD marker immediately - should return EOF on first getChar
TEST_F(RunLengthStreamTest_185, ImmediateEOD_185) {
    // 128 = EOD marker
    unsigned char data[] = { 128 };
    auto rls = createRunLengthStream(data, sizeof(data));
    
    int result = rls->getChar();
    EXPECT_EQ(EOF, result);
}

// Test: Single literal run of 1 byte followed by EOD
TEST_F(RunLengthStreamTest_185, SingleLiteralByte_185) {
    // 0 means copy next 1 byte literally, then 128 = EOD
    unsigned char data[] = { 0, 0x42, 128 };
    auto rls = createRunLengthStream(data, sizeof(data));
    
    int ch = rls->getChar();
    EXPECT_EQ(0x42, ch);
    
    ch = rls->getChar();
    EXPECT_EQ(EOF, ch);
}

// Test: Literal run of multiple bytes
TEST_F(RunLengthStreamTest_185, MultipleLiteralBytes_185) {
    // 2 means copy next 3 bytes literally
    unsigned char data[] = { 2, 0x41, 0x42, 0x43, 128 };
    auto rls = createRunLengthStream(data, sizeof(data));
    
    EXPECT_EQ(0x41, rls->getChar());
    EXPECT_EQ(0x42, rls->getChar());
    EXPECT_EQ(0x43, rls->getChar());
    EXPECT_EQ(EOF, rls->getChar());
}

// Test: Repeat run - byte 255 means repeat next byte (257-255)=2 times
TEST_F(RunLengthStreamTest_185, RepeatRun_185) {
    // 255 means repeat next byte 2 times
    unsigned char data[] = { 255, 0x58, 128 };
    auto rls = createRunLengthStream(data, sizeof(data));
    
    EXPECT_EQ(0x58, rls->getChar());
    EXPECT_EQ(0x58, rls->getChar());
    EXPECT_EQ(EOF, rls->getChar());
}

// Test: Repeat run with larger count - byte 129 means repeat (257-129)=128 times
TEST_F(RunLengthStreamTest_185, LargeRepeatRun_185) {
    // 129 means repeat next byte 128 times
    unsigned char data[] = { 129, 0xAA, 128 };
    auto rls = createRunLengthStream(data, sizeof(data));
    
    for (int i = 0; i < 128; i++) {
        int ch = rls->getChar();
        EXPECT_EQ(0xAA, ch) << "Mismatch at position " << i;
    }
    EXPECT_EQ(EOF, rls->getChar());
}

// Test: Multiple runs - literal then repeat then EOD
TEST_F(RunLengthStreamTest_185, MixedRuns_185) {
    // 1 = copy 2 bytes literally, then 253 = repeat next byte (257-253)=4 times
    unsigned char data[] = { 1, 0x10, 0x20, 253, 0x30, 128 };
    auto rls = createRunLengthStream(data, sizeof(data));
    
    EXPECT_EQ(0x10, rls->getChar());
    EXPECT_EQ(0x20, rls->getChar());
    EXPECT_EQ(0x30, rls->getChar());
    EXPECT_EQ(0x30, rls->getChar());
    EXPECT_EQ(0x30, rls->getChar());
    EXPECT_EQ(0x30, rls->getChar());
    EXPECT_EQ(EOF, rls->getChar());
}

// Test: lookChar should return the same char as getChar without consuming
TEST_F(RunLengthStreamTest_185, LookCharDoesNotConsume_185) {
    unsigned char data[] = { 0, 0x55, 128 };
    auto rls = createRunLengthStream(data, sizeof(data));
    
    int ch1 = rls->lookChar();
    int ch2 = rls->lookChar();
    EXPECT_EQ(ch1, ch2);
    EXPECT_EQ(0x55, ch1);
    
    // Now consume it
    int ch3 = rls->getChar();
    EXPECT_EQ(0x55, ch3);
    
    // Should be EOF now
    EXPECT_EQ(EOF, rls->getChar());
}

// Test: lookChar on empty stream returns EOF
TEST_F(RunLengthStreamTest_185, LookCharOnEOD_185) {
    unsigned char data[] = { 128 };
    auto rls = createRunLengthStream(data, sizeof(data));
    
    EXPECT_EQ(EOF, rls->lookChar());
    EXPECT_EQ(EOF, rls->getChar());
}

// Test: getKind returns the correct stream kind
TEST_F(RunLengthStreamTest_185, GetKind_185) {
    unsigned char data[] = { 128 };
    auto rls = createRunLengthStream(data, sizeof(data));
    
    EXPECT_EQ(strRunLength, rls->getKind());
}

// Test: isBinary returns true
TEST_F(RunLengthStreamTest_185, IsBinary_185) {
    unsigned char data[] = { 128 };
    auto rls = createRunLengthStream(data, sizeof(data));
    
    EXPECT_TRUE(rls->isBinary(true));
    EXPECT_TRUE(rls->isBinary(false));
}

// Test: rewind resets the stream to the beginning
TEST_F(RunLengthStreamTest_185, Rewind_185) {
    unsigned char data[] = { 1, 0x41, 0x42, 128 };
    auto rls = createRunLengthStream(data, sizeof(data));
    
    EXPECT_EQ(0x41, rls->getChar());
    EXPECT_EQ(0x42, rls->getChar());
    EXPECT_EQ(EOF, rls->getChar());
    
    // Rewind and read again
    rls->reset();
    EXPECT_EQ(0x41, rls->getChar());
    EXPECT_EQ(0x42, rls->getChar());
    EXPECT_EQ(EOF, rls->getChar());
}

// Test: Literal run of max 128 bytes (length byte = 127)
TEST_F(RunLengthStreamTest_185, MaxLiteralRun_185) {
    // 127 means copy next 128 bytes literally
    std::vector<unsigned char> data;
    data.push_back(127); // copy 128 bytes
    for (int i = 0; i < 128; i++) {
        data.push_back(static_cast<unsigned char>(i & 0xFF));
    }
    data.push_back(128); // EOD
    
    auto rls = createRunLengthStream(data.data(), static_cast<int>(data.size()));
    
    for (int i = 0; i < 128; i++) {
        int ch = rls->getChar();
        EXPECT_EQ(i & 0xFF, ch) << "Mismatch at position " << i;
    }
    EXPECT_EQ(EOF, rls->getChar());
}

// Test: Multiple consecutive EOD calls return EOF
TEST_F(RunLengthStreamTest_185, MultipleEOFCalls_185) {
    unsigned char data[] = { 128 };
    auto rls = createRunLengthStream(data, sizeof(data));
    
    EXPECT_EQ(EOF, rls->getChar());
    EXPECT_EQ(EOF, rls->getChar());
    EXPECT_EQ(EOF, rls->getChar());
}

// Test: getChar returns unsigned byte values (0-255), not signed
TEST_F(RunLengthStreamTest_185, GetCharReturnsUnsigned_185) {
    // Test with byte value > 127 to ensure it's returned as unsigned
    unsigned char data[] = { 0, 0xFF, 128 };
    auto rls = createRunLengthStream(data, sizeof(data));
    
    int ch = rls->getChar();
    EXPECT_EQ(0xFF, ch);
    EXPECT_GT(ch, 0); // Should be positive (255), not negative (-1)
}

// Test: Repeat run with value 0x00
TEST_F(RunLengthStreamTest_185, RepeatRunWithZero_185) {
    // 254 means repeat next byte (257-254)=3 times
    unsigned char data[] = { 254, 0x00, 128 };
    auto rls = createRunLengthStream(data, sizeof(data));
    
    EXPECT_EQ(0x00, rls->getChar());
    EXPECT_EQ(0x00, rls->getChar());
    EXPECT_EQ(0x00, rls->getChar());
    EXPECT_EQ(EOF, rls->getChar());
}

// Test: getPSFilter
TEST_F(RunLengthStreamTest_185, GetPSFilter_185) {
    unsigned char data[] = { 128 };
    auto rls = createRunLengthStream(data, sizeof(data));
    
    // At PS level 1, RunLengthDecode may not be supported
    auto filter1 = rls->getPSFilter(1, "");
    // At PS level 2 or 3, it should return a filter string
    auto filter2 = rls->getPSFilter(2, "");
    // We just check they don't crash; exact behavior depends on implementation
}

// Test: Alternating literal and repeat runs
TEST_F(RunLengthStreamTest_185, AlternatingRuns_185) {
    unsigned char data[] = {
        0, 0x41,         // literal: 1 byte 'A'
        255, 0x42,       // repeat: 'B' x 2
        0, 0x43,         // literal: 1 byte 'C'
        255, 0x44,       // repeat: 'D' x 2
        128              // EOD
    };
    auto rls = createRunLengthStream(data, sizeof(data));
    
    EXPECT_EQ(0x41, rls->getChar()); // A
    EXPECT_EQ(0x42, rls->getChar()); // B
    EXPECT_EQ(0x42, rls->getChar()); // B
    EXPECT_EQ(0x43, rls->getChar()); // C
    EXPECT_EQ(0x44, rls->getChar()); // D
    EXPECT_EQ(0x44, rls->getChar()); // D
    EXPECT_EQ(EOF, rls->getChar());
}
