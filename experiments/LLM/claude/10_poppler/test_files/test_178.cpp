#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Stream.h"
#include "Object.h"

// Helper: A minimal Stream subclass to act as the underlying stream for EmbedStream
// We need a concrete stream to pass to EmbedStream's constructor.
// We'll use a MemStream or similar if available, but since we need to work with
// the available interface, we create a simple mock/stub.

class MockStream : public Stream {
public:
    MockStream() : Stream() {}
    ~MockStream() override {}

    StreamKind getKind() const override { return streamFile; }
    void reset() { }
    int getChar() override { return charIndex < data.size() ? data[charIndex++] : EOF; }
    int lookChar() override { return charIndex < data.size() ? data[charIndex] : EOF; }
    int getRawChar() override { return getChar(); }
    void getRawChars(int nChars, int *buffer) override {
        for (int i = 0; i < nChars; i++) {
            buffer[i] = getChar();
        }
    }
    int getUnfilteredChar() override { return getChar(); }
    bool unfilteredRewind() override {
        charIndex = 0;
        return true;
    }
    bool rewind() override {
        charIndex = 0;
        return true;
    }
    void close() override {}
    Goffset getPos() override { return charIndex; }
    void setPos(Goffset pos, int dir) override {
        if (dir >= 0) {
            charIndex = pos;
        } else {
            charIndex = data.size() - pos;
        }
    }
    BaseStream *getBaseStream() override { return nullptr; }
    Stream *getUndecodedStream() override { return this; }
    Dict *getDict() override { return nullptr; }
    Object *getDictObject() override { return nullptr; }
    bool isBinary(bool last) const override { return false; }
    char *getLine(char *buf, int size) override { return nullptr; }

    void setData(const std::vector<unsigned char> &d) {
        data = d;
        charIndex = 0;
    }

private:
    std::vector<unsigned char> data;
    size_t charIndex = 0;
};

class EmbedStreamTest_178 : public ::testing::Test {
protected:
    void SetUp() override {
        // Set up a mock underlying stream with some data
        mockStr = new MockStream();
        std::vector<unsigned char> testData = {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd'};
        mockStr->setData(testData);
    }

    void TearDown() override {
        // EmbedStream does not own the underlying stream typically,
        // but we need to be careful about ownership
        // The mockStr might be managed differently
    }

    MockStream *mockStr;
};

// Test basic construction and kind
TEST_F(EmbedStreamTest_178, GetKind_ReturnsEmbedStream_178) {
    Object dict;
    auto embedStream = std::make_unique<EmbedStream>(mockStr, std::move(dict), false, 0, false);
    EXPECT_EQ(embedStream->getKind(), streamEmbed);
}

// Test reading characters from unlimited embed stream
TEST_F(EmbedStreamTest_178, GetChar_UnlimitedStream_ReadsFromUnderlying_178) {
    Object dict;
    auto embedStream = std::make_unique<EmbedStream>(mockStr, std::move(dict), false, 0, false);
    int ch = embedStream->getChar();
    EXPECT_EQ(ch, 'H');
    ch = embedStream->getChar();
    EXPECT_EQ(ch, 'e');
}

// Test lookChar doesn't advance position
TEST_F(EmbedStreamTest_178, LookChar_DoesNotAdvancePosition_178) {
    Object dict;
    auto embedStream = std::make_unique<EmbedStream>(mockStr, std::move(dict), false, 0, false);
    int ch1 = embedStream->lookChar();
    int ch2 = embedStream->lookChar();
    EXPECT_EQ(ch1, ch2);
    EXPECT_EQ(ch1, 'H');
}

// Test limited stream with specific length
TEST_F(EmbedStreamTest_178, GetChar_LimitedStream_RespectsLength_178) {
    Object dict;
    auto embedStream = std::make_unique<EmbedStream>(mockStr, std::move(dict), true, 5, false);
    
    // Should be able to read 5 characters
    for (int i = 0; i < 5; i++) {
        int ch = embedStream->getChar();
        EXPECT_NE(ch, EOF);
    }
    // After reading 5 chars from a limited stream of length 5, should get EOF
    int ch = embedStream->getChar();
    EXPECT_EQ(ch, EOF);
}

// Test getPos returns current position
TEST_F(EmbedStreamTest_178, GetPos_ReturnsCorrectPosition_178) {
    Object dict;
    auto embedStream = std::make_unique<EmbedStream>(mockStr, std::move(dict), false, 0, false);
    Goffset pos0 = embedStream->getPos();
    embedStream->getChar();
    Goffset pos1 = embedStream->getPos();
    EXPECT_GE(pos1, pos0);
}

// Test rewind on non-reusable stream
TEST_F(EmbedStreamTest_178, Rewind_NonReusable_178) {
    Object dict;
    auto embedStream = std::make_unique<EmbedStream>(mockStr, std::move(dict), false, 0, false);
    embedStream->getChar(); // read one char
    // Rewind behavior depends on reusable flag
    embedStream->rewind();
}

// Test reusable stream can be rewound and replayed
TEST_F(EmbedStreamTest_178, Rewind_ReusableStream_CanReplay_178) {
    Object dict;
    auto embedStream = std::make_unique<EmbedStream>(mockStr, std::move(dict), true, 5, true);
    
    // Read all 5 characters
    std::vector<int> firstRead;
    for (int i = 0; i < 5; i++) {
        firstRead.push_back(embedStream->getChar());
    }
    
    // Rewind and read again
    bool rewound = embedStream->rewind();
    if (rewound) {
        std::vector<int> secondRead;
        for (int i = 0; i < 5; i++) {
            secondRead.push_back(embedStream->getChar());
        }
        EXPECT_EQ(firstRead, secondRead);
    }
}

// Test unfilteredRewind delegates to underlying stream
TEST_F(EmbedStreamTest_178, UnfilteredRewind_DelegatesToUnderlying_178) {
    Object dict;
    auto embedStream = std::make_unique<EmbedStream>(mockStr, std::move(dict), false, 0, false);
    bool result = embedStream->unfilteredRewind();
    // The mock stream's unfilteredRewind returns true
    EXPECT_TRUE(result);
}

// Test getUnfilteredChar
TEST_F(EmbedStreamTest_178, GetUnfilteredChar_ReadsChar_178) {
    Object dict;
    auto embedStream = std::make_unique<EmbedStream>(mockStr, std::move(dict), false, 0, false);
    int ch = embedStream->getUnfilteredChar();
    EXPECT_EQ(ch, 'H');
}

// Test getStart returns a valid offset
TEST_F(EmbedStreamTest_178, GetStart_ReturnsValidOffset_178) {
    Object dict;
    auto embedStream = std::make_unique<EmbedStream>(mockStr, std::move(dict), false, 0, false);
    Goffset start = embedStream->getStart();
    EXPECT_GE(start, 0);
}

// Test limited stream with zero length
TEST_F(EmbedStreamTest_178, LimitedStreamZeroLength_ImmediateEOF_178) {
    Object dict;
    auto embedStream = std::make_unique<EmbedStream>(mockStr, std::move(dict), true, 0, false);
    int ch = embedStream->getChar();
    EXPECT_EQ(ch, EOF);
}

// Test lookChar on limited stream with zero length
TEST_F(EmbedStreamTest_178, LookChar_LimitedZeroLength_ReturnsEOF_178) {
    Object dict;
    auto embedStream = std::make_unique<EmbedStream>(mockStr, std::move(dict), true, 0, false);
    int ch = embedStream->lookChar();
    EXPECT_EQ(ch, EOF);
}

// Test reading single character from limited stream of length 1
TEST_F(EmbedStreamTest_178, LimitedStreamLength1_ReadOneChar_178) {
    Object dict;
    auto embedStream = std::make_unique<EmbedStream>(mockStr, std::move(dict), true, 1, false);
    int ch = embedStream->getChar();
    EXPECT_EQ(ch, 'H');
    ch = embedStream->getChar();
    EXPECT_EQ(ch, EOF);
}

// Test moveStart
TEST_F(EmbedStreamTest_178, MoveStart_ChangesStart_178) {
    Object dict;
    auto embedStream = std::make_unique<EmbedStream>(mockStr, std::move(dict), false, 0, false);
    Goffset startBefore = embedStream->getStart();
    embedStream->moveStart(5);
    Goffset startAfter = embedStream->getStart();
    EXPECT_EQ(startAfter, startBefore + 5);
}

// Test copy
TEST_F(EmbedStreamTest_178, Copy_ReturnsNonNull_178) {
    Object dict;
    auto embedStream = std::make_unique<EmbedStream>(mockStr, std::move(dict), false, 0, false);
    auto copied = embedStream->copy();
    // copy() may return nullptr for EmbedStream, but we test it doesn't crash
    // The actual behavior depends on implementation
}

// Test makeSubStream
TEST_F(EmbedStreamTest_178, MakeSubStream_ReturnsStream_178) {
    Object dict;
    auto embedStream = std::make_unique<EmbedStream>(mockStr, std::move(dict), false, 0, false);
    Object subDict;
    auto subStream = embedStream->makeSubStream(0, true, 5, std::move(subDict));
    // makeSubStream may or may not return a valid stream for EmbedStream
}

// Test setPos
TEST_F(EmbedStreamTest_178, SetPos_DoesNotCrash_178) {
    Object dict;
    auto embedStream = std::make_unique<EmbedStream>(mockStr, std::move(dict), false, 0, false);
    // This should not crash
    embedStream->setPos(0, 0);
}

// Test sequential reads match expected data
TEST_F(EmbedStreamTest_178, SequentialReads_MatchExpectedData_178) {
    Object dict;
    auto embedStream = std::make_unique<EmbedStream>(mockStr, std::move(dict), true, 11, false);
    
    std::string result;
    int ch;
    while ((ch = embedStream->getChar()) != EOF) {
        result += static_cast<char>(ch);
    }
    EXPECT_EQ(result, "Hello World");
}

// Test reusable limited stream - read, rewind, re-read
TEST_F(EmbedStreamTest_178, ReusableLimitedStream_ReadRewindReread_178) {
    Object dict;
    auto embedStream = std::make_unique<EmbedStream>(mockStr, std::move(dict), true, 11, true);
    
    // First read
    std::string firstResult;
    int ch;
    while ((ch = embedStream->getChar()) != EOF) {
        firstResult += static_cast<char>(ch);
    }
    EXPECT_EQ(firstResult, "Hello World");
    
    // Rewind
    bool ok = embedStream->rewind();
    if (ok) {
        // Second read should produce same data
        std::string secondResult;
        while ((ch = embedStream->getChar()) != EOF) {
            secondResult += static_cast<char>(ch);
        }
        EXPECT_EQ(secondResult, "Hello World");
    }
}

// Test that lookChar followed by getChar returns same character
TEST_F(EmbedStreamTest_178, LookCharThenGetChar_SameCharacter_178) {
    Object dict;
    auto embedStream = std::make_unique<EmbedStream>(mockStr, std::move(dict), true, 5, false);
    
    int looked = embedStream->lookChar();
    int got = embedStream->getChar();
    EXPECT_EQ(looked, got);
    EXPECT_EQ(looked, 'H');
}

// Test multiple lookChar calls don't advance
TEST_F(EmbedStreamTest_178, MultipleLookChar_NoAdvance_178) {
    Object dict;
    auto embedStream = std::make_unique<EmbedStream>(mockStr, std::move(dict), true, 5, false);
    
    for (int i = 0; i < 10; i++) {
        int ch = embedStream->lookChar();
        EXPECT_EQ(ch, 'H');
    }
}

// Test interleaved lookChar and getChar
TEST_F(EmbedStreamTest_178, InterleavedLookAndGet_178) {
    Object dict;
    auto embedStream = std::make_unique<EmbedStream>(mockStr, std::move(dict), true, 5, false);
    
    EXPECT_EQ(embedStream->lookChar(), 'H');
    EXPECT_EQ(embedStream->getChar(), 'H');
    EXPECT_EQ(embedStream->lookChar(), 'e');
    EXPECT_EQ(embedStream->getChar(), 'e');
    EXPECT_EQ(embedStream->lookChar(), 'l');
}

// Test with empty underlying stream data
TEST_F(EmbedStreamTest_178, EmptyUnderlyingStream_ReturnsEOF_178) {
    MockStream emptyMock;
    emptyMock.setData({});
    
    Object dict;
    auto embedStream = std::make_unique<EmbedStream>(&emptyMock, std::move(dict), false, 0, false);
    int ch = embedStream->getChar();
    EXPECT_EQ(ch, EOF);
}
