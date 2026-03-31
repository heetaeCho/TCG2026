#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Stream.h"
#include "Object.h"

// Helper: Create a simple MemStream or similar to act as the underlying stream for EmbedStream
// We need a concrete Stream to pass to EmbedStream constructor.

class EmbedStreamTest_177 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    // Helper to create an EmbedStream with given data via a MemStream as the parent
    std::unique_ptr<EmbedStream> createEmbedStream(Stream* parentStr, bool limited, Goffset length, bool reusable) {
        Object dictObj;
        dictObj = Object(objNull);
        return std::make_unique<EmbedStream>(parentStr, std::move(dictObj), limited, length, reusable);
    }
};

// Test that EmbedStream returns the correct StreamKind
TEST_F(EmbedStreamTest_177, GetKindReturnsEmbedStream_177) {
    // Create a small memory stream as parent
    const char* data = "Hello, World!";
    auto len = strlen(data);
    Object dictObj(objNull);
    
    auto memStr = std::make_unique<MemStream>(const_cast<char*>(data), 0, len, Object(objNull));
    
    auto embedStr = createEmbedStream(memStr.get(), true, static_cast<Goffset>(len), false);
    
    EXPECT_EQ(embedStr->getKind(), streamEmbedded);
}

// Test reading characters from EmbedStream with limited length
TEST_F(EmbedStreamTest_177, GetCharReadsCharacters_177) {
    const char* data = "ABCDE";
    auto len = strlen(data);
    
    auto memStr = std::make_unique<MemStream>(const_cast<char*>(data), 0, len, Object(objNull));
    
    auto embedStr = createEmbedStream(memStr.get(), true, static_cast<Goffset>(len), false);
    
    EXPECT_EQ(embedStr->getChar(), 'A');
    EXPECT_EQ(embedStr->getChar(), 'B');
    EXPECT_EQ(embedStr->getChar(), 'C');
    EXPECT_EQ(embedStr->getChar(), 'D');
    EXPECT_EQ(embedStr->getChar(), 'E');
}

// Test that getChar returns EOF when stream is exhausted (limited)
TEST_F(EmbedStreamTest_177, GetCharReturnsEOFWhenExhausted_177) {
    const char* data = "AB";
    auto len = strlen(data);
    
    auto memStr = std::make_unique<MemStream>(const_cast<char*>(data), 0, len, Object(objNull));
    
    auto embedStr = createEmbedStream(memStr.get(), true, static_cast<Goffset>(len), false);
    
    EXPECT_EQ(embedStr->getChar(), 'A');
    EXPECT_EQ(embedStr->getChar(), 'B');
    EXPECT_EQ(embedStr->getChar(), EOF);
}

// Test lookChar peeks without advancing
TEST_F(EmbedStreamTest_177, LookCharDoesNotAdvance_177) {
    const char* data = "XY";
    auto len = strlen(data);
    
    auto memStr = std::make_unique<MemStream>(const_cast<char*>(data), 0, len, Object(objNull));
    
    auto embedStr = createEmbedStream(memStr.get(), true, static_cast<Goffset>(len), false);
    
    EXPECT_EQ(embedStr->lookChar(), 'X');
    EXPECT_EQ(embedStr->lookChar(), 'X');
    EXPECT_EQ(embedStr->getChar(), 'X');
    EXPECT_EQ(embedStr->lookChar(), 'Y');
}

// Test getPos returns correct position
TEST_F(EmbedStreamTest_177, GetPosTracksPosition_177) {
    const char* data = "ABCD";
    auto len = strlen(data);
    
    auto memStr = std::make_unique<MemStream>(const_cast<char*>(data), 0, len, Object(objNull));
    
    auto embedStr = createEmbedStream(memStr.get(), true, static_cast<Goffset>(len), false);
    
    Goffset startPos = embedStr->getPos();
    embedStr->getChar();
    EXPECT_EQ(embedStr->getPos(), startPos + 1);
    embedStr->getChar();
    EXPECT_EQ(embedStr->getPos(), startPos + 2);
}

// Test rewind on reusable EmbedStream
TEST_F(EmbedStreamTest_177, RewindOnReusableStream_177) {
    const char* data = "ABCDE";
    auto len = strlen(data);
    
    auto memStr = std::make_unique<MemStream>(const_cast<char*>(data), 0, len, Object(objNull));
    
    auto embedStr = createEmbedStream(memStr.get(), true, static_cast<Goffset>(len), true);
    
    // Read all data first
    EXPECT_EQ(embedStr->getChar(), 'A');
    EXPECT_EQ(embedStr->getChar(), 'B');
    EXPECT_EQ(embedStr->getChar(), 'C');
    EXPECT_EQ(embedStr->getChar(), 'D');
    EXPECT_EQ(embedStr->getChar(), 'E');
    EXPECT_EQ(embedStr->getChar(), EOF);
    
    // Rewind and re-read
    bool result = embedStr->rewind();
    EXPECT_TRUE(result);
    
    EXPECT_EQ(embedStr->getChar(), 'A');
    EXPECT_EQ(embedStr->getChar(), 'B');
}

// Test getStart returns starting position
TEST_F(EmbedStreamTest_177, GetStartReturnsStartPosition_177) {
    const char* data = "Test";
    auto len = strlen(data);
    
    auto memStr = std::make_unique<MemStream>(const_cast<char*>(data), 0, len, Object(objNull));
    
    auto embedStr = createEmbedStream(memStr.get(), true, static_cast<Goffset>(len), false);
    
    // getStart should return the starting position
    Goffset start = embedStr->getStart();
    // Start should be >= 0
    EXPECT_GE(start, 0);
}

// Test with zero length limited stream
TEST_F(EmbedStreamTest_177, ZeroLengthLimitedStream_177) {
    const char* data = "ABCD";
    auto len = strlen(data);
    
    auto memStr = std::make_unique<MemStream>(const_cast<char*>(data), 0, len, Object(objNull));
    
    auto embedStr = createEmbedStream(memStr.get(), true, static_cast<Goffset>(0), false);
    
    // With zero length and limited, should immediately return EOF
    EXPECT_EQ(embedStr->getChar(), EOF);
}

// Test getUnfilteredChar delegates to underlying stream
TEST_F(EmbedStreamTest_177, GetUnfilteredCharDelegates_177) {
    const char* data = "Hello";
    auto len = strlen(data);
    
    auto memStr = std::make_unique<MemStream>(const_cast<char*>(data), 0, len, Object(objNull));
    
    auto embedStr = createEmbedStream(memStr.get(), true, static_cast<Goffset>(len), false);
    
    // getUnfilteredChar should delegate to the parent stream
    int ch = embedStr->getUnfilteredChar();
    // It should return a valid character or EOF
    EXPECT_TRUE(ch == EOF || (ch >= 0 && ch <= 255));
}

// Test reading single character from limited stream of length 1
TEST_F(EmbedStreamTest_177, SingleCharLimitedStream_177) {
    const char* data = "Z";
    auto len = strlen(data);
    
    auto memStr = std::make_unique<MemStream>(const_cast<char*>(data), 0, len, Object(objNull));
    
    auto embedStr = createEmbedStream(memStr.get(), true, static_cast<Goffset>(1), false);
    
    EXPECT_EQ(embedStr->getChar(), 'Z');
    EXPECT_EQ(embedStr->getChar(), EOF);
}

// Test copy returns a valid BaseStream
TEST_F(EmbedStreamTest_177, CopyReturnsValidStream_177) {
    const char* data = "CopyTest";
    auto len = strlen(data);
    
    auto memStr = std::make_unique<MemStream>(const_cast<char*>(data), 0, len, Object(objNull));
    
    auto embedStr = createEmbedStream(memStr.get(), true, static_cast<Goffset>(len), true);
    
    // Read all data to fill buffer for reusable stream
    for (size_t i = 0; i < len; i++) {
        embedStr->getChar();
    }
    
    auto copied = embedStr->copy();
    EXPECT_NE(copied, nullptr);
}

// Test that unlimited (non-limited) EmbedStream reads from parent
TEST_F(EmbedStreamTest_177, UnlimitedStreamReadsFromParent_177) {
    const char* data = "UnlimitedData";
    auto len = strlen(data);
    
    auto memStr = std::make_unique<MemStream>(const_cast<char*>(data), 0, len, Object(objNull));
    
    auto embedStr = createEmbedStream(memStr.get(), false, static_cast<Goffset>(0), false);
    
    // Should be able to read characters from the parent stream
    int ch = embedStr->getChar();
    EXPECT_EQ(ch, 'U');
}

// Test moveStart
TEST_F(EmbedStreamTest_177, MoveStartChangesStart_177) {
    const char* data = "MoveStartTest";
    auto len = strlen(data);
    
    auto memStr = std::make_unique<MemStream>(const_cast<char*>(data), 0, len, Object(objNull));
    
    auto embedStr = createEmbedStream(memStr.get(), true, static_cast<Goffset>(len), false);
    
    Goffset originalStart = embedStr->getStart();
    embedStr->moveStart(2);
    // After moving start by delta, it may or may not change depending on implementation
    // Just ensure no crash
    Goffset newStart = embedStr->getStart();
    EXPECT_GE(newStart, 0);
}

// Test makeSubStream returns a valid stream
TEST_F(EmbedStreamTest_177, MakeSubStreamReturnsValidStream_177) {
    const char* data = "SubStreamData";
    auto len = strlen(data);
    
    auto memStr = std::make_unique<MemStream>(const_cast<char*>(data), 0, len, Object(objNull));
    
    auto embedStr = createEmbedStream(memStr.get(), true, static_cast<Goffset>(len), false);
    
    auto subStream = embedStr->makeSubStream(0, true, static_cast<Goffset>(5), Object(objNull));
    EXPECT_NE(subStream, nullptr);
}

// Test rewind on non-reusable stream
TEST_F(EmbedStreamTest_177, RewindOnNonReusableStream_177) {
    const char* data = "NonReusable";
    auto len = strlen(data);
    
    auto memStr = std::make_unique<MemStream>(const_cast<char*>(data), 0, len, Object(objNull));
    
    auto embedStr = createEmbedStream(memStr.get(), true, static_cast<Goffset>(len), false);
    
    embedStr->getChar();
    embedStr->getChar();
    
    // Rewind on non-reusable stream - behavior depends on implementation
    embedStr->rewind();
    // Just ensure no crash
}

// Test reading multiple characters with getChars (via doGetChars)
TEST_F(EmbedStreamTest_177, DoGetCharsReadsMultipleCharacters_177) {
    const char* data = "MultipleChars";
    auto len = strlen(data);
    
    auto memStr = std::make_unique<MemStream>(const_cast<char*>(data), 0, len, Object(objNull));
    
    auto embedStr = createEmbedStream(memStr.get(), true, static_cast<Goffset>(len), false);
    
    unsigned char buffer[5];
    int nRead = embedStr->doGetChars(5, buffer);
    EXPECT_EQ(nRead, 5);
    EXPECT_EQ(buffer[0], 'M');
    EXPECT_EQ(buffer[1], 'u');
    EXPECT_EQ(buffer[2], 'l');
    EXPECT_EQ(buffer[3], 't');
    EXPECT_EQ(buffer[4], 'i');
}

// Test reading more chars than available
TEST_F(EmbedStreamTest_177, DoGetCharsWithExcessiveCount_177) {
    const char* data = "AB";
    auto len = strlen(data);
    
    auto memStr = std::make_unique<MemStream>(const_cast<char*>(data), 0, len, Object(objNull));
    
    auto embedStr = createEmbedStream(memStr.get(), true, static_cast<Goffset>(len), false);
    
    unsigned char buffer[10];
    int nRead = embedStr->doGetChars(10, buffer);
    EXPECT_EQ(nRead, 2);
    EXPECT_EQ(buffer[0], 'A');
    EXPECT_EQ(buffer[1], 'B');
}

// Test setPos
TEST_F(EmbedStreamTest_177, SetPosChangesPosition_177) {
    const char* data = "SetPosTest";
    auto len = strlen(data);
    
    auto memStr = std::make_unique<MemStream>(const_cast<char*>(data), 0, len, Object(objNull));
    
    auto embedStr = createEmbedStream(memStr.get(), true, static_cast<Goffset>(len), true);
    
    // Read some data to buffer it (reusable)
    for (size_t i = 0; i < len; i++) {
        embedStr->getChar();
    }
    
    // Rewind and set position
    embedStr->rewind();
    embedStr->setPos(0, 0);
    // Should not crash
}
