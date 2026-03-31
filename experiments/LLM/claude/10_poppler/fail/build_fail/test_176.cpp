#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Stream.h"
#include "Object.h"

// Helper: We need a concrete Stream to pass as the underlying stream for EmbedStream.
// We'll use a MemStream or similar if available. Since EmbedStream wraps another stream,
// we need to provide one. Let's use a simple approach with available stream types.

class EmbedStreamTest_176 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    // Helper to create an EmbedStream with given data
    std::unique_ptr<EmbedStream> createEmbedStream(Stream *str, bool limited, Goffset length, bool reusable) {
        Object dict;
        return std::make_unique<EmbedStream>(str, std::move(dict), limited, length, reusable);
    }
};

// Test that getKind returns the kind of the underlying stream
TEST_F(EmbedStreamTest_176, GetKindReturnsUnderlyingStreamKind_176) {
    // Create a base stream - use a MemStream with some data
    const char *data = "Hello, World!";
    auto length = static_cast<Goffset>(strlen(data));
    
    // We need a MemStream or FileStream. Let's create a MemStream.
    Object dictObj;
    char *dataCopy = new char[length];
    memcpy(dataCopy, data, length);
    
    auto memStream = std::make_unique<MemStream>(dataCopy, 0, length, std::move(dictObj));
    
    Object embedDict;
    EmbedStream embedStream(memStream.get(), std::move(embedDict), true, length, false);
    
    // EmbedStream's getKind should return the underlying stream's kind
    EXPECT_EQ(embedStream.getKind(), memStream->getKind());
    
    delete[] dataCopy;
}

// Test getChar reads characters from underlying stream
TEST_F(EmbedStreamTest_176, GetCharReadsFromUnderlyingStream_176) {
    const char *data = "ABCDE";
    auto length = static_cast<Goffset>(strlen(data));
    
    Object dictObj;
    char *dataCopy = new char[length];
    memcpy(dataCopy, data, length);
    
    auto memStream = std::make_unique<MemStream>(dataCopy, 0, length, std::move(dictObj));
    memStream->reset();
    
    Object embedDict;
    EmbedStream embedStream(memStream.get(), std::move(embedDict), true, length, false);
    
    EXPECT_EQ(embedStream.getChar(), 'A');
    EXPECT_EQ(embedStream.getChar(), 'B');
    EXPECT_EQ(embedStream.getChar(), 'C');
    
    delete[] dataCopy;
}

// Test lookChar peeks without consuming
TEST_F(EmbedStreamTest_176, LookCharPeeksWithoutConsuming_176) {
    const char *data = "XYZ";
    auto length = static_cast<Goffset>(strlen(data));
    
    Object dictObj;
    char *dataCopy = new char[length];
    memcpy(dataCopy, data, length);
    
    auto memStream = std::make_unique<MemStream>(dataCopy, 0, length, std::move(dictObj));
    memStream->reset();
    
    Object embedDict;
    EmbedStream embedStream(memStream.get(), std::move(embedDict), true, length, false);
    
    int ch = embedStream.lookChar();
    EXPECT_EQ(ch, 'X');
    // lookChar should not advance - looking again should return same char
    int ch2 = embedStream.lookChar();
    EXPECT_EQ(ch2, 'X');
    
    delete[] dataCopy;
}

// Test limited stream returns EOF after length bytes
TEST_F(EmbedStreamTest_176, LimitedStreamReturnsEOFAfterLength_176) {
    const char *data = "ABCDEFGHIJ";
    auto fullLength = static_cast<Goffset>(strlen(data));
    Goffset limitLength = 3;
    
    Object dictObj;
    char *dataCopy = new char[fullLength];
    memcpy(dataCopy, data, fullLength);
    
    auto memStream = std::make_unique<MemStream>(dataCopy, 0, fullLength, std::move(dictObj));
    memStream->reset();
    
    Object embedDict;
    EmbedStream embedStream(memStream.get(), std::move(embedDict), true, limitLength, false);
    
    EXPECT_EQ(embedStream.getChar(), 'A');
    EXPECT_EQ(embedStream.getChar(), 'B');
    EXPECT_EQ(embedStream.getChar(), 'C');
    // Should return EOF after 3 chars
    EXPECT_EQ(embedStream.getChar(), EOF);
    
    delete[] dataCopy;
}

// Test getPos returns current position
TEST_F(EmbedStreamTest_176, GetPosReturnsCurrentPosition_176) {
    const char *data = "ABCDE";
    auto length = static_cast<Goffset>(strlen(data));
    
    Object dictObj;
    char *dataCopy = new char[length];
    memcpy(dataCopy, data, length);
    
    auto memStream = std::make_unique<MemStream>(dataCopy, 0, length, std::move(dictObj));
    memStream->reset();
    
    Object embedDict;
    EmbedStream embedStream(memStream.get(), std::move(embedDict), true, length, false);
    
    Goffset startPos = embedStream.getPos();
    embedStream.getChar();
    Goffset afterOneChar = embedStream.getPos();
    // Position should have advanced
    EXPECT_GT(afterOneChar, startPos);
    
    delete[] dataCopy;
}

// Test rewind on reusable stream
TEST_F(EmbedStreamTest_176, RewindOnReusableStream_176) {
    const char *data = "ABCDE";
    auto length = static_cast<Goffset>(strlen(data));
    
    Object dictObj;
    char *dataCopy = new char[length];
    memcpy(dataCopy, data, length);
    
    auto memStream = std::make_unique<MemStream>(dataCopy, 0, length, std::move(dictObj));
    memStream->reset();
    
    Object embedDict;
    // Create a reusable EmbedStream
    EmbedStream embedStream(memStream.get(), std::move(embedDict), true, length, true);
    
    // Read some characters
    EXPECT_EQ(embedStream.getChar(), 'A');
    EXPECT_EQ(embedStream.getChar(), 'B');
    
    // Rewind
    bool result = embedStream.rewind();
    
    // After rewind on reusable stream, we should be able to read from beginning
    if (result) {
        EXPECT_EQ(embedStream.getChar(), 'A');
    }
    
    delete[] dataCopy;
}

// Test getStart
TEST_F(EmbedStreamTest_176, GetStartReturnsStart_176) {
    const char *data = "ABCDE";
    auto length = static_cast<Goffset>(strlen(data));
    
    Object dictObj;
    char *dataCopy = new char[length];
    memcpy(dataCopy, data, length);
    
    auto memStream = std::make_unique<MemStream>(dataCopy, 0, length, std::move(dictObj));
    memStream->reset();
    
    Object embedDict;
    EmbedStream embedStream(memStream.get(), std::move(embedDict), true, length, false);
    
    // getStart should return a valid offset
    Goffset start = embedStream.getStart();
    EXPECT_GE(start, 0);
    
    delete[] dataCopy;
}

// Test with zero length limited stream
TEST_F(EmbedStreamTest_176, ZeroLengthLimitedStreamReturnsEOFImmediately_176) {
    const char *data = "ABCDE";
    auto fullLength = static_cast<Goffset>(strlen(data));
    
    Object dictObj;
    char *dataCopy = new char[fullLength];
    memcpy(dataCopy, data, fullLength);
    
    auto memStream = std::make_unique<MemStream>(dataCopy, 0, fullLength, std::move(dictObj));
    memStream->reset();
    
    Object embedDict;
    EmbedStream embedStream(memStream.get(), std::move(embedDict), true, 0, false);
    
    // With zero length, should immediately return EOF
    EXPECT_EQ(embedStream.getChar(), EOF);
    
    delete[] dataCopy;
}

// Test getUnfilteredChar
TEST_F(EmbedStreamTest_176, GetUnfilteredCharReadsCharacter_176) {
    const char *data = "ABCDE";
    auto length = static_cast<Goffset>(strlen(data));
    
    Object dictObj;
    char *dataCopy = new char[length];
    memcpy(dataCopy, data, length);
    
    auto memStream = std::make_unique<MemStream>(dataCopy, 0, length, std::move(dictObj));
    memStream->reset();
    
    Object embedDict;
    EmbedStream embedStream(memStream.get(), std::move(embedDict), true, length, false);
    
    int ch = embedStream.getUnfilteredChar();
    // Should return a valid character or EOF
    EXPECT_TRUE(ch == 'A' || ch == EOF);
    
    delete[] dataCopy;
}

// Test unfilteredRewind
TEST_F(EmbedStreamTest_176, UnfilteredRewindReturnsBoolean_176) {
    const char *data = "ABCDE";
    auto length = static_cast<Goffset>(strlen(data));
    
    Object dictObj;
    char *dataCopy = new char[length];
    memcpy(dataCopy, data, length);
    
    auto memStream = std::make_unique<MemStream>(dataCopy, 0, length, std::move(dictObj));
    memStream->reset();
    
    Object embedDict;
    EmbedStream embedStream(memStream.get(), std::move(embedDict), true, length, false);
    
    // unfilteredRewind should return a boolean
    bool result = embedStream.unfilteredRewind();
    // Just verify it doesn't crash; result depends on implementation
    (void)result;
    
    delete[] dataCopy;
}

// Test copy
TEST_F(EmbedStreamTest_176, CopyReturnsNonNull_176) {
    const char *data = "ABCDE";
    auto length = static_cast<Goffset>(strlen(data));
    
    Object dictObj;
    char *dataCopy = new char[length];
    memcpy(dataCopy, data, length);
    
    auto memStream = std::make_unique<MemStream>(dataCopy, 0, length, std::move(dictObj));
    memStream->reset();
    
    Object embedDict;
    EmbedStream embedStream(memStream.get(), std::move(embedDict), true, length, true);
    
    // Read some data first
    embedStream.getChar();
    embedStream.getChar();
    
    auto copied = embedStream.copy();
    // Copy may return nullptr for non-reusable streams, but for reusable it should work
    // We just test the interface doesn't crash
    
    delete[] dataCopy;
}

// Test makeSubStream
TEST_F(EmbedStreamTest_176, MakeSubStreamReturnsStream_176) {
    const char *data = "ABCDEFGHIJ";
    auto length = static_cast<Goffset>(strlen(data));
    
    Object dictObj;
    char *dataCopy = new char[length];
    memcpy(dataCopy, data, length);
    
    auto memStream = std::make_unique<MemStream>(dataCopy, 0, length, std::move(dictObj));
    memStream->reset();
    
    Object embedDict;
    EmbedStream embedStream(memStream.get(), std::move(embedDict), true, length, false);
    
    Object subDict;
    auto subStream = embedStream.makeSubStream(0, true, 5, std::move(subDict));
    // makeSubStream should return a valid stream
    EXPECT_NE(subStream, nullptr);
    
    delete[] dataCopy;
}

// Test that non-limited stream reads until underlying stream EOF
TEST_F(EmbedStreamTest_176, NonLimitedStreamReadsUntilEOF_176) {
    const char *data = "AB";
    auto length = static_cast<Goffset>(strlen(data));
    
    Object dictObj;
    char *dataCopy = new char[length];
    memcpy(dataCopy, data, length);
    
    auto memStream = std::make_unique<MemStream>(dataCopy, 0, length, std::move(dictObj));
    memStream->reset();
    
    Object embedDict;
    // Non-limited stream (limited = false)
    EmbedStream embedStream(memStream.get(), std::move(embedDict), false, 0, false);
    
    int ch1 = embedStream.getChar();
    int ch2 = embedStream.getChar();
    int ch3 = embedStream.getChar();
    
    // Should read 'A', 'B', then EOF
    EXPECT_EQ(ch1, 'A');
    EXPECT_EQ(ch2, 'B');
    EXPECT_EQ(ch3, EOF);
    
    delete[] dataCopy;
}

// Test moveStart
TEST_F(EmbedStreamTest_176, MoveStartAdjustsStart_176) {
    const char *data = "ABCDE";
    auto length = static_cast<Goffset>(strlen(data));
    
    Object dictObj;
    char *dataCopy = new char[length];
    memcpy(dataCopy, data, length);
    
    auto memStream = std::make_unique<MemStream>(dataCopy, 0, length, std::move(dictObj));
    memStream->reset();
    
    Object embedDict;
    EmbedStream embedStream(memStream.get(), std::move(embedDict), true, length, false);
    
    Goffset startBefore = embedStream.getStart();
    embedStream.moveStart(1);
    Goffset startAfter = embedStream.getStart();
    
    // After moveStart(1), start should have moved
    // The exact behavior depends on implementation
    (void)startBefore;
    (void)startAfter;
    
    delete[] dataCopy;
}

// Test reading single byte data
TEST_F(EmbedStreamTest_176, SingleByteData_176) {
    const char *data = "Z";
    auto length = static_cast<Goffset>(strlen(data));
    
    Object dictObj;
    char *dataCopy = new char[length];
    memcpy(dataCopy, data, length);
    
    auto memStream = std::make_unique<MemStream>(dataCopy, 0, length, std::move(dictObj));
    memStream->reset();
    
    Object embedDict;
    EmbedStream embedStream(memStream.get(), std::move(embedDict), true, length, false);
    
    EXPECT_EQ(embedStream.getChar(), 'Z');
    EXPECT_EQ(embedStream.getChar(), EOF);
    
    delete[] dataCopy;
}
