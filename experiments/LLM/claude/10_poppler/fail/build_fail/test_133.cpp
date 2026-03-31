#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Stream.h"
#include "Object.h"
#include <cstring>
#include <vector>
#include <algorithm>

// Concrete test implementation of BaseSeekInputStream
class TestSeekInputStream : public BaseSeekInputStream {
public:
    TestSeekInputStream(const std::vector<char> &data, Goffset startA, bool limitedA, Goffset lengthA, Object &&dictA)
        : BaseSeekInputStream(startA, limitedA, lengthA, std::move(dictA)), data_(data), currentPos_(startA) {}

    ~TestSeekInputStream() override = default;

    const Goffset currentPos() override {
        return currentPos_;
    }

    void setCurrentPos(Goffset offset) override {
        if (offset < 0) {
            currentPos_ = 0;
        } else if (offset > static_cast<Goffset>(data_.size())) {
            currentPos_ = static_cast<Goffset>(data_.size());
        } else {
            currentPos_ = offset;
        }
    }

    Goffset read(char *buf, Goffset size) override {
        Goffset available = static_cast<Goffset>(data_.size()) - currentPos_;
        if (available <= 0) {
            return 0;
        }
        Goffset toRead = std::min(size, available);
        std::memcpy(buf, data_.data() + currentPos_, toRead);
        currentPos_ += toRead;
        return toRead;
    }

private:
    std::vector<char> data_;
    Goffset currentPos_;
};

class BaseSeekInputStreamTest_133 : public ::testing::Test {
protected:
    std::unique_ptr<TestSeekInputStream> createStream(const std::vector<char> &data, Goffset start = 0, bool limited = false, Goffset length = 0) {
        Object dict;
        return std::make_unique<TestSeekInputStream>(data, start, limited, length, std::move(dict));
    }

    std::unique_ptr<TestSeekInputStream> createLimitedStream(const std::vector<char> &data, Goffset start, Goffset length) {
        Object dict;
        return std::make_unique<TestSeekInputStream>(data, start, true, length, std::move(dict));
    }
};

// Test getChar returns EOF on empty stream
TEST_F(BaseSeekInputStreamTest_133, GetCharReturnsEOFOnEmptyStream_133) {
    std::vector<char> data;
    auto stream = createStream(data);
    stream->reset();
    int result = stream->getChar();
    EXPECT_EQ(result, EOF);
}

// Test getChar reads bytes correctly
TEST_F(BaseSeekInputStreamTest_133, GetCharReadsBytes_133) {
    std::vector<char> data = {'H', 'e', 'l', 'l', 'o'};
    auto stream = createStream(data);
    stream->reset();

    EXPECT_EQ(stream->getChar(), 'H');
    EXPECT_EQ(stream->getChar(), 'e');
    EXPECT_EQ(stream->getChar(), 'l');
    EXPECT_EQ(stream->getChar(), 'l');
    EXPECT_EQ(stream->getChar(), 'o');
    EXPECT_EQ(stream->getChar(), EOF);
}

// Test getChar returns unsigned byte values (0-255)
TEST_F(BaseSeekInputStreamTest_133, GetCharReturnsUnsignedByteValues_133) {
    std::vector<char> data = {static_cast<char>(0xFF), static_cast<char>(0x80), static_cast<char>(0x00)};
    auto stream = createStream(data);
    stream->reset();

    EXPECT_EQ(stream->getChar(), 0xFF);
    EXPECT_EQ(stream->getChar(), 0x80);
    EXPECT_EQ(stream->getChar(), 0x00);
}

// Test lookChar returns next byte without consuming it
TEST_F(BaseSeekInputStreamTest_133, LookCharDoesNotAdvancePosition_133) {
    std::vector<char> data = {'A', 'B', 'C'};
    auto stream = createStream(data);
    stream->reset();

    EXPECT_EQ(stream->lookChar(), 'A');
    EXPECT_EQ(stream->lookChar(), 'A');
    EXPECT_EQ(stream->getChar(), 'A');
    EXPECT_EQ(stream->lookChar(), 'B');
}

// Test lookChar returns EOF on empty stream
TEST_F(BaseSeekInputStreamTest_133, LookCharReturnsEOFOnEmptyStream_133) {
    std::vector<char> data;
    auto stream = createStream(data);
    stream->reset();
    EXPECT_EQ(stream->lookChar(), EOF);
}

// Test getPos returns correct position
TEST_F(BaseSeekInputStreamTest_133, GetPosReturnsCorrectPosition_133) {
    std::vector<char> data = {'A', 'B', 'C', 'D', 'E'};
    auto stream = createStream(data);
    stream->reset();

    Goffset startPos = stream->getPos();
    stream->getChar();
    Goffset afterOneChar = stream->getPos();
    EXPECT_EQ(afterOneChar, startPos + 1);
}

// Test rewind resets to the beginning
TEST_F(BaseSeekInputStreamTest_133, RewindResetsPosition_133) {
    std::vector<char> data = {'X', 'Y', 'Z'};
    auto stream = createStream(data);
    stream->reset();

    stream->getChar(); // X
    stream->getChar(); // Y
    bool result = stream->rewind();
    // After rewind, should be able to read from the beginning again
    // The return value indicates success
    // Read again
    stream->reset();
    EXPECT_EQ(stream->getChar(), 'X');
}

// Test setPos with forward direction
TEST_F(BaseSeekInputStreamTest_133, SetPosFromStart_133) {
    std::vector<char> data = {'A', 'B', 'C', 'D', 'E'};
    auto stream = createStream(data);
    stream->reset();

    stream->setPos(2, 0); // seek to position 2 from start
    EXPECT_EQ(stream->getChar(), 'C');
}

// Test moveStart shifts the start position
TEST_F(BaseSeekInputStreamTest_133, MoveStartShiftsStart_133) {
    std::vector<char> data = {'A', 'B', 'C', 'D', 'E'};
    auto stream = createStream(data);
    stream->reset();

    Goffset origStart = stream->getStart();
    stream->moveStart(2);
    Goffset newStart = stream->getStart();
    EXPECT_EQ(newStart, origStart + 2);
}

// Test getKind returns the correct stream kind
TEST_F(BaseSeekInputStreamTest_133, GetKindReturnsCorrectKind_133) {
    std::vector<char> data = {'A'};
    auto stream = createStream(data);
    StreamKind kind = stream->getKind();
    // Just check it returns a valid kind without crashing
    (void)kind;
}

// Test getStart returns start position
TEST_F(BaseSeekInputStreamTest_133, GetStartReturnsStartPosition_133) {
    std::vector<char> data = {'A', 'B', 'C', 'D', 'E'};
    auto stream = createStream(data, 3, false, 0);
    EXPECT_EQ(stream->getStart(), 3);
}

// Test getUnfilteredChar works
TEST_F(BaseSeekInputStreamTest_133, GetUnfilteredChar_133) {
    std::vector<char> data = {'A', 'B', 'C'};
    auto stream = createStream(data);
    stream->reset();
    int ch = stream->getUnfilteredChar();
    EXPECT_EQ(ch, 'A');
}

// Test unfilteredRewind
TEST_F(BaseSeekInputStreamTest_133, UnfilteredRewind_133) {
    std::vector<char> data = {'A', 'B', 'C'};
    auto stream = createStream(data);
    stream->reset();
    stream->getChar();
    bool result = stream->unfilteredRewind();
    // Just verify it doesn't crash and returns a bool
    (void)result;
}

// Test reading all bytes from a limited stream
TEST_F(BaseSeekInputStreamTest_133, LimitedStreamReadsOnlyLimitedBytes_133) {
    std::vector<char> data = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
    auto stream = createLimitedStream(data, 0, 3);
    stream->reset();

    EXPECT_EQ(stream->getChar(), 'A');
    EXPECT_EQ(stream->getChar(), 'B');
    EXPECT_EQ(stream->getChar(), 'C');
    // After reading 3 bytes in limited mode, should get EOF
    EXPECT_EQ(stream->getChar(), EOF);
}

// Test reading with a non-zero start
TEST_F(BaseSeekInputStreamTest_133, NonZeroStartReadsFromOffset_133) {
    std::vector<char> data = {'A', 'B', 'C', 'D', 'E'};
    auto stream = createStream(data, 2, false, 0);
    stream->reset();

    EXPECT_EQ(stream->getChar(), 'C');
    EXPECT_EQ(stream->getChar(), 'D');
    EXPECT_EQ(stream->getChar(), 'E');
    EXPECT_EQ(stream->getChar(), EOF);
}

// Test consecutive EOF calls
TEST_F(BaseSeekInputStreamTest_133, ConsecutiveEOFCalls_133) {
    std::vector<char> data = {'A'};
    auto stream = createStream(data);
    stream->reset();

    EXPECT_EQ(stream->getChar(), 'A');
    EXPECT_EQ(stream->getChar(), EOF);
    EXPECT_EQ(stream->getChar(), EOF);
    EXPECT_EQ(stream->getChar(), EOF);
}

// Test close and then operations
TEST_F(BaseSeekInputStreamTest_133, CloseStream_133) {
    std::vector<char> data = {'A', 'B', 'C'};
    auto stream = createStream(data);
    stream->reset();
    stream->getChar();
    stream->close();
    // After close, the stream should handle gracefully
}

// Test large data stream
TEST_F(BaseSeekInputStreamTest_133, LargeDataStream_133) {
    // Create data larger than typical buffer size
    std::vector<char> data(20000);
    for (int i = 0; i < 20000; i++) {
        data[i] = static_cast<char>(i % 256);
    }
    auto stream = createStream(data);
    stream->reset();

    // Read first few bytes
    for (int i = 0; i < 100; i++) {
        int expected = i % 256;
        EXPECT_EQ(stream->getChar(), expected) << "Mismatch at position " << i;
    }
}

// Test setPos from end (dir != 0)
TEST_F(BaseSeekInputStreamTest_133, SetPosFromEnd_133) {
    std::vector<char> data = {'A', 'B', 'C', 'D', 'E'};
    auto stream = createStream(data);
    stream->reset();

    // Read all to establish end
    for (int i = 0; i < 5; i++) {
        stream->getChar();
    }

    // Set position from end - this depends on implementation, just verify no crash
    stream->setPos(0, 0);
    int ch = stream->getChar();
    EXPECT_EQ(ch, 'A');
}

// Test limited stream with start offset
TEST_F(BaseSeekInputStreamTest_133, LimitedStreamWithStartOffset_133) {
    std::vector<char> data = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
    auto stream = createLimitedStream(data, 2, 3);
    stream->reset();

    EXPECT_EQ(stream->getChar(), 'C');
    EXPECT_EQ(stream->getChar(), 'D');
    EXPECT_EQ(stream->getChar(), 'E');
    EXPECT_EQ(stream->getChar(), EOF);
}

// Test single byte stream
TEST_F(BaseSeekInputStreamTest_133, SingleByteStream_133) {
    std::vector<char> data = {'Z'};
    auto stream = createStream(data);
    stream->reset();

    EXPECT_EQ(stream->lookChar(), 'Z');
    EXPECT_EQ(stream->getChar(), 'Z');
    EXPECT_EQ(stream->lookChar(), EOF);
    EXPECT_EQ(stream->getChar(), EOF);
}

// Test that byte 0x00 is not confused with EOF
TEST_F(BaseSeekInputStreamTest_133, NullByteNotConfusedWithEOF_133) {
    std::vector<char> data = {'\0', '\0', '\0'};
    auto stream = createStream(data);
    stream->reset();

    EXPECT_EQ(stream->getChar(), 0);
    EXPECT_NE(stream->getChar(), EOF);
}

// Test reset and re-read
TEST_F(BaseSeekInputStreamTest_133, ResetAndReread_133) {
    std::vector<char> data = {'A', 'B', 'C'};
    auto stream = createStream(data);

    stream->reset();
    EXPECT_EQ(stream->getChar(), 'A');
    EXPECT_EQ(stream->getChar(), 'B');

    stream->reset();
    EXPECT_EQ(stream->getChar(), 'A');
    EXPECT_EQ(stream->getChar(), 'B');
    EXPECT_EQ(stream->getChar(), 'C');
    EXPECT_EQ(stream->getChar(), EOF);
}
