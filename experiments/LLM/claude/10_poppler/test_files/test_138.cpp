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
        : BaseSeekInputStream(startA, limitedA, lengthA, std::move(dictA)), data_(data), pos_(0) {}

    ~TestSeekInputStream() override {}

    const Goffset currentPos() override {
        return pos_;
    }

    void setCurrentPos(Goffset offset) override {
        if (offset < 0) {
            pos_ = 0;
        } else if (offset > static_cast<Goffset>(data_.size())) {
            pos_ = static_cast<Goffset>(data_.size());
        } else {
            pos_ = offset;
        }
    }

    Goffset read(char *buf, Goffset size) override {
        Goffset available = static_cast<Goffset>(data_.size()) - pos_;
        if (available <= 0) {
            return 0;
        }
        Goffset toRead = std::min(size, available);
        memcpy(buf, data_.data() + pos_, toRead);
        pos_ += toRead;
        return toRead;
    }

private:
    std::vector<char> data_;
    Goffset pos_;
};

class BaseSeekInputStreamTest_138 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}

    std::unique_ptr<TestSeekInputStream> createStream(const std::vector<char> &data,
                                                       Goffset start = 0,
                                                       bool limited = false,
                                                       Goffset length = 0) {
        Object dict;
        return std::make_unique<TestSeekInputStream>(data, start, limited, length, std::move(dict));
    }

    std::unique_ptr<TestSeekInputStream> createStreamWithData(const std::string &str,
                                                               Goffset start = 0,
                                                               bool limited = false,
                                                               Goffset length = 0) {
        std::vector<char> data(str.begin(), str.end());
        return createStream(data, start, limited, length);
    }
};

// Test getKind returns the expected stream kind
TEST_F(BaseSeekInputStreamTest_138, GetKind_138) {
    auto stream = createStreamWithData("hello");
    // BaseSeekInputStream should report some kind; just verify it doesn't crash
    StreamKind kind = stream->getKind();
    (void)kind; // We just verify it's callable
}

// Test reading characters from a non-empty stream
TEST_F(BaseSeekInputStreamTest_138, GetCharReadsSequentially_138) {
    auto stream = createStreamWithData("ABCD");
    stream->reset();
    EXPECT_EQ('A', stream->getChar());
    EXPECT_EQ('B', stream->getChar());
    EXPECT_EQ('C', stream->getChar());
    EXPECT_EQ('D', stream->getChar());
}

// Test getChar returns EOF at end of data
TEST_F(BaseSeekInputStreamTest_138, GetCharReturnsEOFAtEnd_138) {
    auto stream = createStreamWithData("A");
    stream->reset();
    EXPECT_EQ('A', stream->getChar());
    EXPECT_EQ(EOF, stream->getChar());
}

// Test lookChar peeks without advancing
TEST_F(BaseSeekInputStreamTest_138, LookCharDoesNotAdvance_138) {
    auto stream = createStreamWithData("XY");
    stream->reset();
    int c1 = stream->lookChar();
    int c2 = stream->lookChar();
    EXPECT_EQ(c1, c2);
    EXPECT_EQ('X', c1);
}

// Test lookChar then getChar returns same character
TEST_F(BaseSeekInputStreamTest_138, LookCharThenGetChar_138) {
    auto stream = createStreamWithData("Z");
    stream->reset();
    int peeked = stream->lookChar();
    int read = stream->getChar();
    EXPECT_EQ(peeked, read);
    EXPECT_EQ('Z', read);
}

// Test getPos tracks position
TEST_F(BaseSeekInputStreamTest_138, GetPosTracksPosition_138) {
    auto stream = createStreamWithData("ABCDEF");
    stream->reset();
    Goffset startPos = stream->getPos();
    stream->getChar();
    Goffset afterOne = stream->getPos();
    EXPECT_GT(afterOne, startPos);
}

// Test rewind returns to beginning
TEST_F(BaseSeekInputStreamTest_138, RewindGoesBackToStart_138) {
    auto stream = createStreamWithData("Hello");
    stream->reset();
    stream->getChar();
    stream->getChar();
    bool result = stream->rewind();
    EXPECT_TRUE(result);
    EXPECT_EQ('H', stream->getChar());
}

// Test unfilteredRewind delegates to rewind
TEST_F(BaseSeekInputStreamTest_138, UnfilteredRewindCallsRewind_138) {
    auto stream = createStreamWithData("Test");
    stream->reset();
    stream->getChar();
    stream->getChar();
    bool result = stream->unfilteredRewind();
    EXPECT_TRUE(result);
    EXPECT_EQ('T', stream->getChar());
}

// Test empty stream returns EOF immediately
TEST_F(BaseSeekInputStreamTest_138, EmptyStreamReturnsEOF_138) {
    auto stream = createStreamWithData("");
    stream->reset();
    EXPECT_EQ(EOF, stream->getChar());
}

// Test empty stream lookChar returns EOF
TEST_F(BaseSeekInputStreamTest_138, EmptyStreamLookCharReturnsEOF_138) {
    auto stream = createStreamWithData("");
    stream->reset();
    EXPECT_EQ(EOF, stream->lookChar());
}

// Test getStart returns the start offset
TEST_F(BaseSeekInputStreamTest_138, GetStartReturnsStartOffset_138) {
    auto stream = createStreamWithData("data", 10, false, 0);
    EXPECT_EQ(10, stream->getStart());
}

// Test getStart with zero offset
TEST_F(BaseSeekInputStreamTest_138, GetStartReturnsZero_138) {
    auto stream = createStreamWithData("data", 0, false, 0);
    EXPECT_EQ(0, stream->getStart());
}

// Test setPos with absolute position (dir=0)
TEST_F(BaseSeekInputStreamTest_138, SetPosAbsolute_138) {
    auto stream = createStreamWithData("ABCDEF");
    stream->reset();
    stream->setPos(2, 0);
    EXPECT_EQ('C', stream->getChar());
}

// Test setPos from end (dir!=0, typically dir=-1 or similar)
TEST_F(BaseSeekInputStreamTest_138, SetPosFromEnd_138) {
    std::string data = "ABCDEF";
    auto stream = createStreamWithData(data);
    stream->reset();
    // setPos with dir != 0 typically seeks from end
    stream->setPos(0, 1);
    // Behavior depends on implementation; just verify no crash
    // and that we can still read or get EOF
    int c = stream->getChar();
    (void)c;
}

// Test moveStart shifts the start position
TEST_F(BaseSeekInputStreamTest_138, MoveStartShiftsDelta_138) {
    auto stream = createStreamWithData("ABCDEF", 0, false, 0);
    Goffset originalStart = stream->getStart();
    stream->moveStart(3);
    Goffset newStart = stream->getStart();
    EXPECT_EQ(originalStart + 3, newStart);
}

// Test close and then rewind
TEST_F(BaseSeekInputStreamTest_138, CloseAndRewind_138) {
    auto stream = createStreamWithData("data");
    stream->reset();
    stream->getChar();
    stream->close();
    // After close, rewind should still work to re-open
    bool result = stream->rewind();
    // Just verify it doesn't crash; result may vary
    (void)result;
}

// Test getUnfilteredChar reads like getChar
TEST_F(BaseSeekInputStreamTest_138, GetUnfilteredChar_138) {
    auto stream = createStreamWithData("AB");
    stream->reset();
    int c = stream->getUnfilteredChar();
    EXPECT_EQ('A', c);
}

// Test limited stream respects length
TEST_F(BaseSeekInputStreamTest_138, LimitedStreamRespectsLength_138) {
    auto stream = createStreamWithData("ABCDEFGHIJ", 0, true, 3);
    stream->reset();
    EXPECT_EQ('A', stream->getChar());
    EXPECT_EQ('B', stream->getChar());
    EXPECT_EQ('C', stream->getChar());
    // After 3 chars, should get EOF if limited
    EXPECT_EQ(EOF, stream->getChar());
}

// Test limited stream with zero length
TEST_F(BaseSeekInputStreamTest_138, LimitedStreamZeroLength_138) {
    auto stream = createStreamWithData("ABCDEF", 0, true, 0);
    stream->reset();
    EXPECT_EQ(EOF, stream->getChar());
}

// Test reading a large amount of data
TEST_F(BaseSeekInputStreamTest_138, LargeDataRead_138) {
    // Create data larger than typical buffer size (16384)
    std::vector<char> data(20000);
    for (size_t i = 0; i < data.size(); i++) {
        data[i] = static_cast<char>('A' + (i % 26));
    }
    auto stream = createStream(data);
    stream->reset();

    for (int i = 0; i < 20000; i++) {
        int c = stream->getChar();
        ASSERT_NE(EOF, c) << "Unexpected EOF at position " << i;
        EXPECT_EQ(static_cast<unsigned char>('A' + (i % 26)), static_cast<unsigned char>(c));
    }
    EXPECT_EQ(EOF, stream->getChar());
}

// Test multiple rewinds
TEST_F(BaseSeekInputStreamTest_138, MultipleRewinds_138) {
    auto stream = createStreamWithData("XYZ");
    stream->reset();
    EXPECT_EQ('X', stream->getChar());
    
    stream->rewind();
    EXPECT_EQ('X', stream->getChar());
    
    stream->rewind();
    EXPECT_EQ('X', stream->getChar());
}

// Test setPos to position 0
TEST_F(BaseSeekInputStreamTest_138, SetPosToZero_138) {
    auto stream = createStreamWithData("ABCDE");
    stream->reset();
    stream->getChar();
    stream->getChar();
    stream->setPos(0, 0);
    EXPECT_EQ('A', stream->getChar());
}

// Test reading single byte stream
TEST_F(BaseSeekInputStreamTest_138, SingleByteStream_138) {
    auto stream = createStreamWithData("Q");
    stream->reset();
    EXPECT_EQ('Q', stream->getChar());
    EXPECT_EQ(EOF, stream->getChar());
    stream->rewind();
    EXPECT_EQ('Q', stream->lookChar());
    EXPECT_EQ('Q', stream->getChar());
    EXPECT_EQ(EOF, stream->lookChar());
}

// Test with binary data including null bytes
TEST_F(BaseSeekInputStreamTest_138, BinaryDataWithNulls_138) {
    std::vector<char> data = {'\x00', '\x01', '\x02', '\xFF', '\x00'};
    auto stream = createStream(data);
    stream->reset();
    EXPECT_EQ(0x00, stream->getChar());
    EXPECT_EQ(0x01, stream->getChar());
    EXPECT_EQ(0x02, stream->getChar());
    EXPECT_EQ(0xFF, stream->getChar());
    EXPECT_EQ(0x00, stream->getChar());
    EXPECT_EQ(EOF, stream->getChar());
}

// Test moveStart with zero delta
TEST_F(BaseSeekInputStreamTest_138, MoveStartZeroDelta_138) {
    auto stream = createStreamWithData("ABCDEF", 5, false, 0);
    Goffset originalStart = stream->getStart();
    stream->moveStart(0);
    EXPECT_EQ(originalStart, stream->getStart());
}

// Test limited stream with start offset
TEST_F(BaseSeekInputStreamTest_138, LimitedStreamWithStartOffset_138) {
    // Data from offset 2, limited to 3 bytes
    auto stream = createStreamWithData("ABCDEFGHIJ", 2, true, 3);
    stream->reset();
    // Should read starting from offset 2 for 3 bytes
    int c1 = stream->getChar();
    int c2 = stream->getChar();
    int c3 = stream->getChar();
    EXPECT_NE(EOF, c1);
    EXPECT_NE(EOF, c2);
    EXPECT_NE(EOF, c3);
    EXPECT_EQ(EOF, stream->getChar());
}
