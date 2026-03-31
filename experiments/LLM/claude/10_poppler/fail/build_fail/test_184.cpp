#include <gtest/gtest.h>
#include <memory>
#include "Stream.h"

// Helper to create a minimal Stream for constructing RunLengthStream
// We need a concrete Stream implementation to pass as the underlying stream.
// Using a MemStream or similar if available, otherwise we need to find a suitable one.

// Based on the known dependencies, we'll create a simple in-memory stream to feed RunLengthStream.

class RunLengthStreamTest_184 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    // Helper: create a RunLengthStream wrapping raw data encoded in run-length format
    // Run-length encoding format for PDF:
    //   - length byte 0-127: copy next (length+1) bytes literally
    //   - length byte 129-255: repeat next byte (257-length) times
    //   - length byte 128: EOD (end of data)
    std::unique_ptr<RunLengthStream> createRunLengthStream(const unsigned char* data, int len) {
        // We need to wrap data in a MemStream, then wrap that in RunLengthStream
        // MemStream takes ownership of a copy or a buffer
        Object dictObj;
        auto memStream = std::make_unique<MemStream>(reinterpret_cast<const char*>(data), 0, len, Object(objNull));
        return std::make_unique<RunLengthStream>(std::move(memStream));
    }
};

// Test that getKind returns strRunLength
TEST_F(RunLengthStreamTest_184, GetKindReturnsRunLength_184) {
    // Minimal valid run-length data: EOD marker
    unsigned char data[] = { 128 }; // EOD
    auto stream = createRunLengthStream(data, sizeof(data));
    EXPECT_EQ(stream->getKind(), strRunLength);
}

// Test that an empty stream (just EOD) returns EOF on getChar
TEST_F(RunLengthStreamTest_184, EmptyStreamReturnsEOF_184) {
    unsigned char data[] = { 128 }; // EOD
    auto stream = createRunLengthStream(data, sizeof(data));
    stream->reset();
    EXPECT_EQ(stream->getChar(), EOF);
}

// Test that lookChar on an empty stream returns EOF
TEST_F(RunLengthStreamTest_184, EmptyStreamLookCharReturnsEOF_184) {
    unsigned char data[] = { 128 }; // EOD
    auto stream = createRunLengthStream(data, sizeof(data));
    stream->reset();
    EXPECT_EQ(stream->lookChar(), EOF);
}

// Test literal run: length byte 2 means copy next 3 bytes
TEST_F(RunLengthStreamTest_184, LiteralRunDecoding_184) {
    // length=2 -> copy 3 bytes, then EOD
    unsigned char data[] = { 2, 'A', 'B', 'C', 128 };
    auto stream = createRunLengthStream(data, sizeof(data));
    stream->reset();
    EXPECT_EQ(stream->getChar(), 'A');
    EXPECT_EQ(stream->getChar(), 'B');
    EXPECT_EQ(stream->getChar(), 'C');
    EXPECT_EQ(stream->getChar(), EOF);
}

// Test repeated run: length byte 253 means repeat next byte (257-253)=4 times
TEST_F(RunLengthStreamTest_184, RepeatedRunDecoding_184) {
    // length=253 -> repeat next byte 4 times, then EOD
    unsigned char data[] = { 253, 'X', 128 };
    auto stream = createRunLengthStream(data, sizeof(data));
    stream->reset();
    EXPECT_EQ(stream->getChar(), 'X');
    EXPECT_EQ(stream->getChar(), 'X');
    EXPECT_EQ(stream->getChar(), 'X');
    EXPECT_EQ(stream->getChar(), 'X');
    EXPECT_EQ(stream->getChar(), EOF);
}

// Test lookChar does not consume the character
TEST_F(RunLengthStreamTest_184, LookCharDoesNotConsume_184) {
    unsigned char data[] = { 0, 'Z', 128 }; // length=0 -> 1 byte literal
    auto stream = createRunLengthStream(data, sizeof(data));
    stream->reset();
    EXPECT_EQ(stream->lookChar(), 'Z');
    EXPECT_EQ(stream->lookChar(), 'Z'); // still 'Z'
    EXPECT_EQ(stream->getChar(), 'Z');  // now consume
    EXPECT_EQ(stream->getChar(), EOF);
}

// Test rewind resets the stream to beginning
TEST_F(RunLengthStreamTest_184, RewindResetsStream_184) {
    unsigned char data[] = { 1, 'A', 'B', 128 }; // 2 literal bytes
    auto stream = createRunLengthStream(data, sizeof(data));
    stream->reset();
    EXPECT_EQ(stream->getChar(), 'A');
    EXPECT_EQ(stream->getChar(), 'B');
    EXPECT_EQ(stream->getChar(), EOF);

    // Rewind and read again
    bool result = stream->reset();
    EXPECT_EQ(stream->getChar(), 'A');
    EXPECT_EQ(stream->getChar(), 'B');
    EXPECT_EQ(stream->getChar(), EOF);
}

// Test isBinary returns true (run-length is a binary filter)
TEST_F(RunLengthStreamTest_184, IsBinaryReturnsTrue_184) {
    unsigned char data[] = { 128 };
    auto stream = createRunLengthStream(data, sizeof(data));
    EXPECT_TRUE(stream->isBinary(true));
    EXPECT_TRUE(stream->isBinary(false));
}

// Test multiple runs: literal then repeat then EOD
TEST_F(RunLengthStreamTest_184, MultipleRuns_184) {
    // Literal run: length=1 -> 2 bytes: 'H', 'i'
    // Repeat run: length=254 -> repeat '!' 3 times (257-254=3)
    // EOD
    unsigned char data[] = { 1, 'H', 'i', 254, '!', 128 };
    auto stream = createRunLengthStream(data, sizeof(data));
    stream->reset();
    EXPECT_EQ(stream->getChar(), 'H');
    EXPECT_EQ(stream->getChar(), 'i');
    EXPECT_EQ(stream->getChar(), '!');
    EXPECT_EQ(stream->getChar(), '!');
    EXPECT_EQ(stream->getChar(), '!');
    EXPECT_EQ(stream->getChar(), EOF);
}

// Test single literal byte (length=0)
TEST_F(RunLengthStreamTest_184, SingleLiteralByte_184) {
    unsigned char data[] = { 0, 0xFF, 128 };
    auto stream = createRunLengthStream(data, sizeof(data));
    stream->reset();
    EXPECT_EQ(stream->getChar(), 0xFF);
    EXPECT_EQ(stream->getChar(), EOF);
}

// Test maximum literal run: length=127 -> 128 bytes
TEST_F(RunLengthStreamTest_184, MaxLiteralRun_184) {
    unsigned char data[128 + 2]; // 1 length byte + 128 data bytes + 1 EOD
    data[0] = 127; // 128 literal bytes
    for (int i = 0; i < 128; i++) {
        data[i + 1] = static_cast<unsigned char>(i);
    }
    data[129] = 128; // EOD
    auto stream = createRunLengthStream(data, sizeof(data));
    stream->reset();
    for (int i = 0; i < 128; i++) {
        EXPECT_EQ(stream->getChar(), i) << "Failed at index " << i;
    }
    EXPECT_EQ(stream->getChar(), EOF);
}

// Test maximum repeat run: length=129 -> repeat 128 times (257-129=128)
TEST_F(RunLengthStreamTest_184, MaxRepeatRun_184) {
    unsigned char data[] = { 129, 'R', 128 };
    auto stream = createRunLengthStream(data, sizeof(data));
    stream->reset();
    for (int i = 0; i < 128; i++) {
        EXPECT_EQ(stream->getChar(), 'R') << "Failed at repeat index " << i;
    }
    EXPECT_EQ(stream->getChar(), EOF);
}

// Test getPSFilter returns a value for sufficient psLevel
TEST_F(RunLengthStreamTest_184, GetPSFilter_184) {
    unsigned char data[] = { 128 };
    auto stream = createRunLengthStream(data, sizeof(data));
    // RunLengthDecode is available at PS level 2+
    auto result = stream->getPSFilter(2, "");
    // We just check it returns something or nothing - behavior depends on implementation
    // At level 1, it likely returns nullopt
    auto result1 = stream->getPSFilter(1, "");
    // We can't assert exact values without knowing implementation, 
    // but we verify no crash and the function is callable
}
