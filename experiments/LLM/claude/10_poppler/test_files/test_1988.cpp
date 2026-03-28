#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdio>
#include <cstring>

// Include necessary headers
extern "C" {
#include <jpeglib.h>
#include <jerror.h>
}

#include "Stream.h"
#include "DCTStream.h"

// We need to access the static function str_fill_input_buffer.
// Since it's static in the .cc file, we need to either:
// 1. Include the .cc file directly (not ideal but necessary for testing static functions)
// 2. Or declare it as extern if possible
// For testing purposes, we include the implementation file
// to get access to the static function.

// Forward declaration of the structure used internally
struct str_src_mgr {
    struct jpeg_source_mgr pub;
    JOCTET buffer;
    Stream *str;
    int index;
};

// We need to declare the function we're testing
// Since it's static in DCTStream.cc, we'll need to include the source or
// replicate the signature. Let's try including the source.
// Actually, the function is static so we must include the .cc to test it.
// We'll use a workaround: redefine static as nothing for testing.

// Alternative approach: create a mock Stream and test through DCTStream interface
// But since the prompt specifically asks about str_fill_input_buffer, let's create
// a mock stream and invoke the function through the decompression machinery.

// Mock Stream class for testing
class MockStream : public Stream {
public:
    MOCK_METHOD(StreamKind, getKind, (), (const, override));
    MOCK_METHOD(bool, rewind, (), (override));
    MOCK_METHOD(void, close, (), (override));
    MOCK_METHOD(int, getChar, (), (override));
    MOCK_METHOD(int, lookChar, (), (override));
    MOCK_METHOD(int, getRawChar, (), (override));
    MOCK_METHOD(void, getRawChars, (int nChars, int *buffer), (override));
    MOCK_METHOD(int, getUnfilteredChar, (), (override));
    MOCK_METHOD(bool, unfilteredRewind, (), (override));
    MOCK_METHOD(char*, getLine, (char *buf, int size), (override));
    MOCK_METHOD(unsigned int, discardChars, (unsigned int n), (override));
    MOCK_METHOD(Goffset, getPos, (), (override));
    MOCK_METHOD(void, setPos, (Goffset pos, int dir), (override));
    MOCK_METHOD(std::optional<std::string>, getPSFilter, (int psLevel, const char *indent), (override));
    MOCK_METHOD(bool, isBinary, (bool last), (const, override));
    MOCK_METHOD(BaseStream*, getBaseStream, (), (override));
    MOCK_METHOD(Stream*, getUndecodedStream, (), (override));
    MOCK_METHOD(Dict*, getDict, (), (override));
    MOCK_METHOD(Object*, getDictObject, (), (override));
    MOCK_METHOD(bool, isEncrypted, (), (const));
};

// Since str_fill_input_buffer is a static function in DCTStream.cc,
// we need to include the source file to access it for unit testing.
// We'll define a test-accessible version by including the source.

// Workaround: temporarily make static functions accessible
#define static
#include "DCTStream.cc"
#undef static

class StrFillInputBufferTest_1988 : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize a minimal jpeg_decompress_struct
        memset(&cinfo, 0, sizeof(cinfo));
        memset(&src_mgr, 0, sizeof(src_mgr));
        cinfo.src = (struct jpeg_source_mgr *)&src_mgr;
        mockStream = new MockStream();
        src_mgr.str = mockStream;
    }

    void TearDown() override {
        delete mockStream;
    }

    struct jpeg_decompress_struct cinfo;
    struct str_src_mgr src_mgr;
    MockStream *mockStream;
};

// Test: First call (index == 0) should return 0xFF and increment index
TEST_F(StrFillInputBufferTest_1988, FirstCallReturns0xFF_1988) {
    src_mgr.index = 0;

    boolean result = str_fill_input_buffer(&cinfo);

    EXPECT_EQ(result, TRUE);
    EXPECT_EQ(src_mgr.buffer, 0xFF);
    EXPECT_EQ(src_mgr.pub.bytes_in_buffer, 1u);
    EXPECT_EQ(src_mgr.pub.next_input_byte, &src_mgr.buffer);
    EXPECT_EQ(src_mgr.index, 1);
}

// Test: Second call (index == 1) should return 0xD8 and increment index
TEST_F(StrFillInputBufferTest_1988, SecondCallReturns0xD8_1988) {
    src_mgr.index = 1;

    boolean result = str_fill_input_buffer(&cinfo);

    EXPECT_EQ(result, TRUE);
    EXPECT_EQ(src_mgr.buffer, 0xD8);
    EXPECT_EQ(src_mgr.pub.bytes_in_buffer, 1u);
    EXPECT_EQ(src_mgr.pub.next_input_byte, &src_mgr.buffer);
    EXPECT_EQ(src_mgr.index, 2);
}

// Test: Third and subsequent calls (index >= 2) should read from stream
TEST_F(StrFillInputBufferTest_1988, SubsequentCallsReadFromStream_1988) {
    src_mgr.index = 2;

    EXPECT_CALL(*mockStream, getChar())
        .WillOnce(::testing::Return(0x42));

    boolean result = str_fill_input_buffer(&cinfo);

    EXPECT_EQ(result, TRUE);
    EXPECT_EQ(src_mgr.buffer, 0x42);
    EXPECT_EQ(src_mgr.pub.bytes_in_buffer, 1u);
    EXPECT_EQ(src_mgr.pub.next_input_byte, &src_mgr.buffer);
}

// Test: Stream returns EOF should cause FALSE return
TEST_F(StrFillInputBufferTest_1988, StreamReturnsEOF_1988) {
    src_mgr.index = 2;

    EXPECT_CALL(*mockStream, getChar())
        .WillOnce(::testing::Return(EOF));

    boolean result = str_fill_input_buffer(&cinfo);

    EXPECT_EQ(result, FALSE);
    EXPECT_EQ(src_mgr.pub.bytes_in_buffer, 1u);
    EXPECT_EQ(src_mgr.pub.next_input_byte, &src_mgr.buffer);
}

// Test: Multiple sequential calls simulate reading SOI marker then stream data
TEST_F(StrFillInputBufferTest_1988, SequentialCallsProduceSOIThenStreamData_1988) {
    src_mgr.index = 0;

    // First call: 0xFF
    boolean result1 = str_fill_input_buffer(&cinfo);
    EXPECT_EQ(result1, TRUE);
    EXPECT_EQ(src_mgr.buffer, 0xFF);
    EXPECT_EQ(src_mgr.index, 1);

    // Second call: 0xD8
    boolean result2 = str_fill_input_buffer(&cinfo);
    EXPECT_EQ(result2, TRUE);
    EXPECT_EQ(src_mgr.buffer, 0xD8);
    EXPECT_EQ(src_mgr.index, 2);

    // Third call: from stream
    EXPECT_CALL(*mockStream, getChar())
        .WillOnce(::testing::Return(0xAB));
    boolean result3 = str_fill_input_buffer(&cinfo);
    EXPECT_EQ(result3, TRUE);
    EXPECT_EQ(src_mgr.buffer, 0xAB);
}

// Test: Stream data with zero byte
TEST_F(StrFillInputBufferTest_1988, StreamReturnsZeroByte_1988) {
    src_mgr.index = 2;

    EXPECT_CALL(*mockStream, getChar())
        .WillOnce(::testing::Return(0x00));

    boolean result = str_fill_input_buffer(&cinfo);

    EXPECT_EQ(result, TRUE);
    EXPECT_EQ(src_mgr.buffer, 0x00);
}

// Test: Stream returns 0xFF (valid JPEG marker byte)
TEST_F(StrFillInputBufferTest_1988, StreamReturns0xFF_1988) {
    src_mgr.index = 2;

    EXPECT_CALL(*mockStream, getChar())
        .WillOnce(::testing::Return(0xFF));

    boolean result = str_fill_input_buffer(&cinfo);

    EXPECT_EQ(result, TRUE);
    EXPECT_EQ(src_mgr.buffer, 0xFF);
}

// Test: Large index value still reads from stream
TEST_F(StrFillInputBufferTest_1988, LargeIndexReadsFromStream_1988) {
    src_mgr.index = 10000;

    EXPECT_CALL(*mockStream, getChar())
        .WillOnce(::testing::Return(0x55));

    boolean result = str_fill_input_buffer(&cinfo);

    EXPECT_EQ(result, TRUE);
    EXPECT_EQ(src_mgr.buffer, 0x55);
}

// Test: Multiple reads from stream until EOF
TEST_F(StrFillInputBufferTest_1988, MultipleReadsUntilEOF_1988) {
    src_mgr.index = 2;

    EXPECT_CALL(*mockStream, getChar())
        .WillOnce(::testing::Return(0x10))
        .WillOnce(::testing::Return(0x20))
        .WillOnce(::testing::Return(EOF));

    // First stream read
    boolean result1 = str_fill_input_buffer(&cinfo);
    EXPECT_EQ(result1, TRUE);
    EXPECT_EQ(src_mgr.buffer, 0x10);

    // Second stream read
    boolean result2 = str_fill_input_buffer(&cinfo);
    EXPECT_EQ(result2, TRUE);
    EXPECT_EQ(src_mgr.buffer, 0x20);

    // Third stream read - EOF
    boolean result3 = str_fill_input_buffer(&cinfo);
    EXPECT_EQ(result3, FALSE);
}

// Test: next_input_byte always points to buffer
TEST_F(StrFillInputBufferTest_1988, NextInputBytePointsToBuffer_1988) {
    src_mgr.index = 0;

    str_fill_input_buffer(&cinfo);
    EXPECT_EQ(src_mgr.pub.next_input_byte, &src_mgr.buffer);

    str_fill_input_buffer(&cinfo);
    EXPECT_EQ(src_mgr.pub.next_input_byte, &src_mgr.buffer);

    EXPECT_CALL(*mockStream, getChar())
        .WillOnce(::testing::Return(0x77));
    str_fill_input_buffer(&cinfo);
    EXPECT_EQ(src_mgr.pub.next_input_byte, &src_mgr.buffer);
}

// Test: bytes_in_buffer is always 1
TEST_F(StrFillInputBufferTest_1988, BytesInBufferAlwaysOne_1988) {
    src_mgr.index = 0;

    str_fill_input_buffer(&cinfo);
    EXPECT_EQ(src_mgr.pub.bytes_in_buffer, 1u);

    str_fill_input_buffer(&cinfo);
    EXPECT_EQ(src_mgr.pub.bytes_in_buffer, 1u);

    EXPECT_CALL(*mockStream, getChar())
        .WillOnce(::testing::Return(EOF));
    str_fill_input_buffer(&cinfo);
    EXPECT_EQ(src_mgr.pub.bytes_in_buffer, 1u);
}

// Test: Index 2 boundary - exactly at the transition from hardcoded to stream
TEST_F(StrFillInputBufferTest_1988, IndexTwoBoundary_1988) {
    // Test index = 2 reads from stream (not hardcoded)
    src_mgr.index = 2;

    EXPECT_CALL(*mockStream, getChar())
        .WillOnce(::testing::Return(0xE0)); // JFIF marker

    boolean result = str_fill_input_buffer(&cinfo);
    EXPECT_EQ(result, TRUE);
    EXPECT_EQ(src_mgr.buffer, 0xE0);
    // Index should not be modified for index >= 2
    EXPECT_EQ(src_mgr.index, 2);
}

// Test: Stream returns maximum byte value (255)
TEST_F(StrFillInputBufferTest_1988, StreamReturnsMaxByte_1988) {
    src_mgr.index = 2;

    EXPECT_CALL(*mockStream, getChar())
        .WillOnce(::testing::Return(255));

    boolean result = str_fill_input_buffer(&cinfo);

    EXPECT_EQ(result, TRUE);
    EXPECT_EQ(src_mgr.buffer, 255);
}
