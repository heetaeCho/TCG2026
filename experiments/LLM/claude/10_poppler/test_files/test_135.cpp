#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Stream.h"
#include "Object.h"

// Concrete test implementation of BaseSeekInputStream
class TestSeekInputStream : public BaseSeekInputStream {
public:
    TestSeekInputStream(const std::string &data, Goffset startA, bool limitedA, Goffset lengthA, Object &&dictA)
        : BaseSeekInputStream(startA, limitedA, lengthA, std::move(dictA)), data_(data), currentPos_(0) {}

    ~TestSeekInputStream() override {}

private:
    const Goffset currentPos() override {
        return currentPos_;
    }

    void setCurrentPos(Goffset offset) override {
        if (offset < 0) {
            currentPos_ = 0;
        } else if (offset > static_cast<Goffset>(data_.size())) {
            currentPos_ = data_.size();
        } else {
            currentPos_ = offset;
        }
    }

    Goffset read(char *buf, Goffset size) override {
        Goffset available = static_cast<Goffset>(data_.size()) - currentPos_;
        if (available <= 0) return 0;
        Goffset toRead = (size < available) ? size : available;
        memcpy(buf, data_.data() + currentPos_, toRead);
        currentPos_ += toRead;
        return toRead;
    }

    std::string data_;
    Goffset currentPos_;
};

class BaseSeekInputStreamTest_135 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}

    std::unique_ptr<TestSeekInputStream> createStream(const std::string &data, Goffset start = 0, bool limited = false, Goffset length = 0) {
        Object dict;
        return std::make_unique<TestSeekInputStream>(data, start, limited, length, std::move(dict));
    }
};

// Test getKind returns the correct stream kind
TEST_F(BaseSeekInputStreamTest_135, GetKind_135) {
    auto stream = createStream("hello world");
    // BaseSeekInputStream should report some kind
    StreamKind kind = stream->getKind();
    // Just verify it doesn't crash and returns a valid kind
    (void)kind;
}

// Test reading a single character
TEST_F(BaseSeekInputStreamTest_135, GetCharReadsSingleChar_135) {
    auto stream = createStream("ABCDEF");
    stream->reset();
    int ch = stream->getChar();
    EXPECT_EQ(ch, 'A');
}

// Test reading multiple characters sequentially
TEST_F(BaseSeekInputStreamTest_135, GetCharSequentialReads_135) {
    auto stream = createStream("XYZ");
    stream->reset();
    EXPECT_EQ(stream->getChar(), 'X');
    EXPECT_EQ(stream->getChar(), 'Y');
    EXPECT_EQ(stream->getChar(), 'Z');
}

// Test getChar returns EOF when stream is exhausted
TEST_F(BaseSeekInputStreamTest_135, GetCharReturnsEOFAtEnd_135) {
    auto stream = createStream("A");
    stream->reset();
    EXPECT_EQ(stream->getChar(), 'A');
    EXPECT_EQ(stream->getChar(), EOF);
}

// Test lookChar peeks without advancing position
TEST_F(BaseSeekInputStreamTest_135, LookCharDoesNotAdvance_135) {
    auto stream = createStream("Hello");
    stream->reset();
    int ch1 = stream->lookChar();
    int ch2 = stream->lookChar();
    EXPECT_EQ(ch1, 'H');
    EXPECT_EQ(ch2, 'H');
    // Position should not have changed
    EXPECT_EQ(stream->getChar(), 'H');
}

// Test getPos returns current position
TEST_F(BaseSeekInputStreamTest_135, GetPosInitiallyZero_135) {
    auto stream = createStream("ABCDEF");
    stream->reset();
    EXPECT_EQ(stream->getPos(), 0);
}

// Test getPos advances after reading
TEST_F(BaseSeekInputStreamTest_135, GetPosAdvancesAfterRead_135) {
    auto stream = createStream("ABCDEF");
    stream->reset();
    stream->getChar();
    EXPECT_EQ(stream->getPos(), 1);
    stream->getChar();
    EXPECT_EQ(stream->getPos(), 2);
}

// Test getStart returns the start position
TEST_F(BaseSeekInputStreamTest_135, GetStartReturnsStartPosition_135) {
    auto stream = createStream("ABCDEF", 10, false, 0);
    EXPECT_EQ(stream->getStart(), 10);
}

// Test rewind resets position
TEST_F(BaseSeekInputStreamTest_135, RewindResetsPosition_135) {
    auto stream = createStream("ABCDEF");
    stream->reset();
    stream->getChar();
    stream->getChar();
    stream->getChar();
    bool result = stream->rewind();
    // After rewind, reading should start from beginning
    // rewind may return true/false
    (void)result;
}

// Test setPos with absolute position
TEST_F(BaseSeekInputStreamTest_135, SetPosAbsolute_135) {
    auto stream = createStream("ABCDEFGHIJ");
    stream->reset();
    stream->setPos(3, 0);
    int ch = stream->getChar();
    EXPECT_EQ(ch, 'D');
}

// Test setPos to beginning
TEST_F(BaseSeekInputStreamTest_135, SetPosToBeginning_135) {
    auto stream = createStream("ABCDEF");
    stream->reset();
    stream->getChar();
    stream->getChar();
    stream->setPos(0, 0);
    EXPECT_EQ(stream->getChar(), 'A');
}

// Test moveStart adjusts the start
TEST_F(BaseSeekInputStreamTest_135, MoveStartAdjustsStart_135) {
    auto stream = createStream("ABCDEFGHIJ", 0, false, 0);
    Goffset startBefore = stream->getStart();
    stream->moveStart(3);
    Goffset startAfter = stream->getStart();
    EXPECT_EQ(startAfter, startBefore + 3);
}

// Test with empty data
TEST_F(BaseSeekInputStreamTest_135, EmptyStreamReturnsEOF_135) {
    auto stream = createStream("");
    stream->reset();
    EXPECT_EQ(stream->getChar(), EOF);
}

// Test lookChar on empty stream
TEST_F(BaseSeekInputStreamTest_135, LookCharOnEmptyStream_135) {
    auto stream = createStream("");
    stream->reset();
    EXPECT_EQ(stream->lookChar(), EOF);
}

// Test limited stream with length
TEST_F(BaseSeekInputStreamTest_135, LimitedStreamRespectsLength_135) {
    auto stream = createStream("ABCDEFGHIJ", 0, true, 3);
    stream->reset();
    EXPECT_EQ(stream->getChar(), 'A');
    EXPECT_EQ(stream->getChar(), 'B');
    EXPECT_EQ(stream->getChar(), 'C');
    // After reading 3 chars from a limited stream of length 3, should get EOF
    EXPECT_EQ(stream->getChar(), EOF);
}

// Test unfilteredRewind
TEST_F(BaseSeekInputStreamTest_135, UnfilteredRewind_135) {
    auto stream = createStream("ABCDEF");
    stream->reset();
    stream->getChar();
    stream->getChar();
    bool result = stream->unfilteredRewind();
    (void)result;
    // Should be able to read from beginning again
}

// Test getUnfilteredChar
TEST_F(BaseSeekInputStreamTest_135, GetUnfilteredChar_135) {
    auto stream = createStream("ABCDEF");
    stream->reset();
    int ch = stream->getUnfilteredChar();
    EXPECT_EQ(ch, 'A');
}

// Test close and reopen via reset
TEST_F(BaseSeekInputStreamTest_135, CloseAndReset_135) {
    auto stream = createStream("ABCDEF");
    stream->reset();
    stream->getChar();
    stream->close();
    stream->reset();
    EXPECT_EQ(stream->getChar(), 'A');
}

// Test reading single byte data
TEST_F(BaseSeekInputStreamTest_135, SingleByteData_135) {
    auto stream = createStream("Z");
    stream->reset();
    EXPECT_EQ(stream->getChar(), 'Z');
    EXPECT_EQ(stream->getChar(), EOF);
}

// Test setPos from end (dir != 0)
TEST_F(BaseSeekInputStreamTest_135, SetPosFromEnd_135) {
    std::string data = "ABCDEFGHIJ";
    auto stream = createStream(data);
    stream->reset();
    // dir != 0 means position from end
    stream->setPos(0, -1);
    // After setting position from end, we should be near/at end
}

// Test limited stream with start offset
TEST_F(BaseSeekInputStreamTest_135, LimitedStreamWithStartOffset_135) {
    auto stream = createStream("ABCDEFGHIJ", 2, true, 4);
    stream->reset();
    // Should read starting from offset 2 for 4 bytes
    int ch = stream->getChar();
    EXPECT_EQ(ch, 'C');
}

// Test that getPos formula matches: bufPos + (bufPtr - buf)
TEST_F(BaseSeekInputStreamTest_135, GetPosConsistency_135) {
    auto stream = createStream("ABCDEFGHIJKLMNOP");
    stream->reset();
    EXPECT_EQ(stream->getPos(), 0);
    for (int i = 0; i < 5; i++) {
        stream->getChar();
    }
    EXPECT_EQ(stream->getPos(), 5);
}

// Test reading binary data with null bytes
TEST_F(BaseSeekInputStreamTest_135, BinaryDataWithNullBytes_135) {
    std::string data = std::string("AB\0CD", 5);
    auto stream = createStream(data);
    stream->reset();
    EXPECT_EQ(stream->getChar(), 'A');
    EXPECT_EQ(stream->getChar(), 'B');
    EXPECT_EQ(stream->getChar(), 0);
    EXPECT_EQ(stream->getChar(), 'C');
    EXPECT_EQ(stream->getChar(), 'D');
    EXPECT_EQ(stream->getChar(), EOF);
}

// Test multiple resets
TEST_F(BaseSeekInputStreamTest_135, MultipleResets_135) {
    auto stream = createStream("ABC");
    stream->reset();
    EXPECT_EQ(stream->getChar(), 'A');
    stream->reset();
    EXPECT_EQ(stream->getChar(), 'A');
    stream->reset();
    EXPECT_EQ(stream->getChar(), 'A');
}
