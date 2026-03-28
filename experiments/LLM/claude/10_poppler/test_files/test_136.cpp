#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Stream.h"
#include "Object.h"

// Concrete test implementation of BaseSeekInputStream
class TestSeekInputStream : public BaseSeekInputStream {
public:
    TestSeekInputStream(const std::string &data, Goffset startA, bool limitedA, Goffset lengthA, Object &&dictA)
        : BaseSeekInputStream(startA, limitedA, lengthA, std::move(dictA)), data_(data), currentPos_(startA) {}

    ~TestSeekInputStream() override {}

    const Goffset currentPos() override {
        return currentPos_;
    }

    void setCurrentPos(Goffset offset) override {
        if (offset < 0) offset = 0;
        currentPos_ = offset;
    }

    Goffset read(char *buf, Goffset size) override {
        if (currentPos_ >= (Goffset)data_.size()) return 0;
        Goffset available = (Goffset)data_.size() - currentPos_;
        Goffset toRead = (size < available) ? size : available;
        memcpy(buf, data_.c_str() + currentPos_, toRead);
        currentPos_ += toRead;
        return toRead;
    }

private:
    std::string data_;
    Goffset currentPos_;
};

class BaseSeekInputStreamTest_136 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}

    std::unique_ptr<TestSeekInputStream> createStream(const std::string &data, Goffset start = 0, bool limited = false, Goffset length = 0) {
        Object dict;
        return std::make_unique<TestSeekInputStream>(data, start, limited, length, std::move(dict));
    }
};

// Test getStart returns the start position
TEST_F(BaseSeekInputStreamTest_136, GetStartReturnsStartPosition_136) {
    auto stream = createStream("Hello World", 5, false, 0);
    EXPECT_EQ(stream->getStart(), 5);
}

TEST_F(BaseSeekInputStreamTest_136, GetStartReturnsZeroWhenStartIsZero_136) {
    auto stream = createStream("Hello World", 0, false, 0);
    EXPECT_EQ(stream->getStart(), 0);
}

TEST_F(BaseSeekInputStreamTest_136, GetStartWithLargeOffset_136) {
    auto stream = createStream("Hello World", 1000000, false, 0);
    EXPECT_EQ(stream->getStart(), 1000000);
}

// Test getKind returns the correct stream kind
TEST_F(BaseSeekInputStreamTest_136, GetKindReturnsCorrectKind_136) {
    auto stream = createStream("Hello World", 0, false, 0);
    // BaseSeekInputStream should have a defined StreamKind
    StreamKind kind = stream->getKind();
    // Just verify it returns without error; the specific kind depends on implementation
    (void)kind;
}

// Test rewind functionality
TEST_F(BaseSeekInputStreamTest_136, RewindResetsPosition_136) {
    auto stream = createStream("Hello World", 0, false, 0);
    // Read some characters
    stream->getChar();
    stream->getChar();
    // Rewind
    bool result = stream->rewind();
    EXPECT_TRUE(result);
    // After rewind, position should be at start
    EXPECT_EQ(stream->getPos(), 0);
}

// Test getChar reads characters sequentially
TEST_F(BaseSeekInputStreamTest_136, GetCharReadsSequentially_136) {
    auto stream = createStream("ABC", 0, false, 0);
    stream->rewind();
    EXPECT_EQ(stream->getChar(), 'A');
    EXPECT_EQ(stream->getChar(), 'B');
    EXPECT_EQ(stream->getChar(), 'C');
}

// Test getChar returns EOF at end of stream
TEST_F(BaseSeekInputStreamTest_136, GetCharReturnsEOFAtEnd_136) {
    auto stream = createStream("A", 0, true, 1);
    stream->rewind();
    stream->getChar(); // 'A'
    int ch = stream->getChar();
    EXPECT_EQ(ch, EOF);
}

// Test lookChar does not advance position
TEST_F(BaseSeekInputStreamTest_136, LookCharDoesNotAdvance_136) {
    auto stream = createStream("XYZ", 0, false, 0);
    stream->rewind();
    int ch1 = stream->lookChar();
    int ch2 = stream->lookChar();
    EXPECT_EQ(ch1, ch2);
    EXPECT_EQ(ch1, 'X');
}

// Test getPos returns current position
TEST_F(BaseSeekInputStreamTest_136, GetPosReturnsCurrentPosition_136) {
    auto stream = createStream("Hello", 0, false, 0);
    stream->rewind();
    EXPECT_EQ(stream->getPos(), 0);
    stream->getChar();
    EXPECT_EQ(stream->getPos(), 1);
}

// Test setPos with absolute positioning
TEST_F(BaseSeekInputStreamTest_136, SetPosAbsolute_136) {
    auto stream = createStream("Hello World", 0, false, 0);
    stream->rewind();
    stream->setPos(5, 0);
    int ch = stream->getChar();
    EXPECT_EQ(ch, ' ');
}

// Test moveStart adjusts the start position
TEST_F(BaseSeekInputStreamTest_136, MoveStartAdjustsStart_136) {
    auto stream = createStream("Hello World", 0, false, 0);
    stream->moveStart(3);
    EXPECT_EQ(stream->getStart(), 3);
}

// Test close does not crash
TEST_F(BaseSeekInputStreamTest_136, CloseDoesNotCrash_136) {
    auto stream = createStream("Hello World", 0, false, 0);
    stream->rewind();
    stream->getChar();
    stream->close();
    // After close, the stream should be in a valid state (no crash)
}

// Test limited stream respects length
TEST_F(BaseSeekInputStreamTest_136, LimitedStreamRespectsLength_136) {
    auto stream = createStream("Hello World", 0, true, 5);
    stream->rewind();
    std::string result;
    int ch;
    while ((ch = stream->getChar()) != EOF) {
        result += (char)ch;
    }
    EXPECT_EQ(result, "Hello");
}

// Test unlimited stream reads all data
TEST_F(BaseSeekInputStreamTest_136, UnlimitedStreamReadsAllData_136) {
    std::string data = "Hello World";
    auto stream = createStream(data, 0, false, 0);
    stream->rewind();
    std::string result;
    int ch;
    while ((ch = stream->getChar()) != EOF) {
        result += (char)ch;
    }
    EXPECT_EQ(result, data);
}

// Test getUnfilteredChar
TEST_F(BaseSeekInputStreamTest_136, GetUnfilteredCharReadsChar_136) {
    auto stream = createStream("Test", 0, false, 0);
    stream->rewind();
    int ch = stream->getUnfilteredChar();
    EXPECT_EQ(ch, 'T');
}

// Test unfilteredRewind
TEST_F(BaseSeekInputStreamTest_136, UnfilteredRewindWorks_136) {
    auto stream = createStream("Test", 0, false, 0);
    stream->rewind();
    stream->getChar();
    stream->getChar();
    bool result = stream->unfilteredRewind();
    EXPECT_TRUE(result);
}

// Test with empty data
TEST_F(BaseSeekInputStreamTest_136, EmptyStreamReturnsEOF_136) {
    auto stream = createStream("", 0, false, 0);
    stream->rewind();
    int ch = stream->getChar();
    EXPECT_EQ(ch, EOF);
}

// Test with start beyond data
TEST_F(BaseSeekInputStreamTest_136, StartBeyondDataReturnsEOF_136) {
    auto stream = createStream("Hello", 100, false, 0);
    stream->rewind();
    int ch = stream->getChar();
    EXPECT_EQ(ch, EOF);
}

// Test rewind after close
TEST_F(BaseSeekInputStreamTest_136, RewindAfterClose_136) {
    auto stream = createStream("Hello", 0, false, 0);
    stream->rewind();
    stream->getChar();
    stream->close();
    bool result = stream->rewind();
    // Should be able to rewind after close
    (void)result;
}

// Test limited stream with zero length
TEST_F(BaseSeekInputStreamTest_136, LimitedStreamZeroLength_136) {
    auto stream = createStream("Hello World", 0, true, 0);
    stream->rewind();
    int ch = stream->getChar();
    EXPECT_EQ(ch, EOF);
}

// Test setPos with direction parameter
TEST_F(BaseSeekInputStreamTest_136, SetPosFromEnd_136) {
    std::string data = "Hello World";
    auto stream = createStream(data, 0, true, data.size());
    stream->rewind();
    // dir != 0 means seek from end
    stream->setPos(0, -1);
    // The position should be at or near the end
}

// Test getStart remains constant after operations
TEST_F(BaseSeekInputStreamTest_136, GetStartConstantAfterReads_136) {
    auto stream = createStream("Hello World", 7, false, 0);
    stream->rewind();
    stream->getChar();
    stream->getChar();
    EXPECT_EQ(stream->getStart(), 7);
}

// Test multiple rewinds
TEST_F(BaseSeekInputStreamTest_136, MultipleRewinds_136) {
    auto stream = createStream("ABC", 0, false, 0);
    for (int i = 0; i < 3; i++) {
        stream->rewind();
        EXPECT_EQ(stream->getChar(), 'A');
    }
}

// Test large data
TEST_F(BaseSeekInputStreamTest_136, LargeData_136) {
    std::string largeData(100000, 'X');
    auto stream = createStream(largeData, 0, false, 0);
    stream->rewind();
    int ch = stream->getChar();
    EXPECT_EQ(ch, 'X');
    // Seek to near the end
    stream->setPos(99999, 0);
    ch = stream->getChar();
    EXPECT_EQ(ch, 'X');
}

// Test moveStart multiple times
TEST_F(BaseSeekInputStreamTest_136, MoveStartMultipleTimes_136) {
    auto stream = createStream("Hello World", 0, false, 0);
    stream->moveStart(2);
    EXPECT_EQ(stream->getStart(), 2);
    stream->moveStart(3);
    EXPECT_EQ(stream->getStart(), 5);
}
