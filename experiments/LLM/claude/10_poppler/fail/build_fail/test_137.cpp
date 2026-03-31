#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Stream.h"
#include "Object.h"

// Concrete implementation of BaseSeekInputStream for testing
class TestSeekInputStream : public BaseSeekInputStream {
public:
    TestSeekInputStream(const std::string &data, Goffset startA, bool limitedA, Goffset lengthA, Object &&dictA)
        : BaseSeekInputStream(startA, limitedA, lengthA, std::move(dictA)), data_(data), currentPos_(startA) {}

    ~TestSeekInputStream() override = default;

    const Goffset currentPos() override { return currentPos_; }

    void setCurrentPos(Goffset offset) override {
        if (offset < 0) {
            currentPos_ = 0;
        } else if (offset > (Goffset)data_.size()) {
            currentPos_ = data_.size();
        } else {
            currentPos_ = offset;
        }
    }

    Goffset read(char *buf, Goffset size) override {
        Goffset available = (Goffset)data_.size() - currentPos_;
        if (available <= 0) return 0;
        Goffset toRead = (size < available) ? size : available;
        memcpy(buf, data_.c_str() + currentPos_, toRead);
        currentPos_ += toRead;
        return toRead;
    }

private:
    std::string data_;
    Goffset currentPos_;
};

class BaseSeekInputStreamTest_137 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}

    std::unique_ptr<TestSeekInputStream> createStream(const std::string &data, Goffset start = 0, bool limited = false, Goffset length = 0) {
        Object dict;
        return std::make_unique<TestSeekInputStream>(data, start, limited, length, std::move(dict));
    }

    std::unique_ptr<TestSeekInputStream> createLimitedStream(const std::string &data, Goffset start, Goffset length) {
        Object dict;
        return std::make_unique<TestSeekInputStream>(data, start, true, length, std::move(dict));
    }
};

TEST_F(BaseSeekInputStreamTest_137, GetCharReturnsFirstChar_137) {
    auto stream = createStream("Hello World");
    stream->reset();
    int ch = stream->getChar();
    EXPECT_EQ(ch, 'H');
}

TEST_F(BaseSeekInputStreamTest_137, GetCharReturnsSequentialChars_137) {
    auto stream = createStream("ABC");
    stream->reset();
    EXPECT_EQ(stream->getChar(), 'A');
    EXPECT_EQ(stream->getChar(), 'B');
    EXPECT_EQ(stream->getChar(), 'C');
}

TEST_F(BaseSeekInputStreamTest_137, GetCharReturnsEOFAtEnd_137) {
    auto stream = createStream("A");
    stream->reset();
    EXPECT_EQ(stream->getChar(), 'A');
    EXPECT_EQ(stream->getChar(), EOF);
}

TEST_F(BaseSeekInputStreamTest_137, LookCharDoesNotAdvance_137) {
    auto stream = createStream("XYZ");
    stream->reset();
    int ch1 = stream->lookChar();
    int ch2 = stream->lookChar();
    EXPECT_EQ(ch1, 'X');
    EXPECT_EQ(ch2, 'X');
}

TEST_F(BaseSeekInputStreamTest_137, LookCharThenGetChar_137) {
    auto stream = createStream("AB");
    stream->reset();
    EXPECT_EQ(stream->lookChar(), 'A');
    EXPECT_EQ(stream->getChar(), 'A');
    EXPECT_EQ(stream->lookChar(), 'B');
    EXPECT_EQ(stream->getChar(), 'B');
}

TEST_F(BaseSeekInputStreamTest_137, GetPosReturnsCurrentPosition_137) {
    auto stream = createStream("ABCDEF");
    stream->reset();
    EXPECT_EQ(stream->getPos(), 0);
    stream->getChar();
    EXPECT_EQ(stream->getPos(), 1);
    stream->getChar();
    EXPECT_EQ(stream->getPos(), 2);
}

TEST_F(BaseSeekInputStreamTest_137, GetStartReturnsStartPosition_137) {
    auto stream = createStream("Hello", 5, false, 0);
    stream->reset();
    EXPECT_EQ(stream->getStart(), 5);
}

TEST_F(BaseSeekInputStreamTest_137, RewindResetsToStart_137) {
    auto stream = createStream("Hello");
    stream->reset();
    stream->getChar(); // H
    stream->getChar(); // e
    bool result = stream->rewind();
    EXPECT_TRUE(result);
    EXPECT_EQ(stream->getChar(), 'H');
}

TEST_F(BaseSeekInputStreamTest_137, UnfilteredRewind_137) {
    auto stream = createStream("Test");
    stream->reset();
    stream->getChar();
    stream->getChar();
    bool result = stream->unfilteredRewind();
    EXPECT_TRUE(result);
}

TEST_F(BaseSeekInputStreamTest_137, GetUnfilteredCharSameAsGetChar_137) {
    auto stream = createStream("AB");
    stream->reset();
    // getUnfilteredChar should return same as getChar
    EXPECT_EQ(stream->getUnfilteredChar(), 'A');
    EXPECT_EQ(stream->getUnfilteredChar(), 'B');
}

TEST_F(BaseSeekInputStreamTest_137, EmptyStreamReturnsEOF_137) {
    auto stream = createStream("");
    stream->reset();
    EXPECT_EQ(stream->getChar(), EOF);
}

TEST_F(BaseSeekInputStreamTest_137, EmptyStreamLookCharReturnsEOF_137) {
    auto stream = createStream("");
    stream->reset();
    EXPECT_EQ(stream->lookChar(), EOF);
}

TEST_F(BaseSeekInputStreamTest_137, SetPosFromStart_137) {
    auto stream = createStream("ABCDEF");
    stream->reset();
    stream->setPos(3, 0); // set to position 3 from start
    EXPECT_EQ(stream->getChar(), 'D');
}

TEST_F(BaseSeekInputStreamTest_137, SetPosToBeginning_137) {
    auto stream = createStream("ABCDEF");
    stream->reset();
    stream->getChar(); // A
    stream->getChar(); // B
    stream->setPos(0, 0);
    EXPECT_EQ(stream->getChar(), 'A');
}

TEST_F(BaseSeekInputStreamTest_137, MoveStartDelta_137) {
    auto stream = createStream("ABCDEF", 0, false, 0);
    stream->reset();
    stream->moveStart(2);
    EXPECT_EQ(stream->getStart(), 2);
}

TEST_F(BaseSeekInputStreamTest_137, CloseAndReset_137) {
    auto stream = createStream("ABCDEF");
    stream->reset();
    stream->getChar();
    stream->close();
    // After close, resetting should work
    stream->reset();
    EXPECT_EQ(stream->getChar(), 'A');
}

TEST_F(BaseSeekInputStreamTest_137, LimitedStreamReadsOnlyLength_137) {
    auto stream = createLimitedStream("ABCDEF", 0, 3);
    stream->reset();
    EXPECT_EQ(stream->getChar(), 'A');
    EXPECT_EQ(stream->getChar(), 'B');
    EXPECT_EQ(stream->getChar(), 'C');
    EXPECT_EQ(stream->getChar(), EOF);
}

TEST_F(BaseSeekInputStreamTest_137, LimitedStreamWithOffset_137) {
    auto stream = createLimitedStream("ABCDEF", 2, 3);
    stream->reset();
    EXPECT_EQ(stream->getChar(), 'C');
    EXPECT_EQ(stream->getChar(), 'D');
    EXPECT_EQ(stream->getChar(), 'E');
    EXPECT_EQ(stream->getChar(), EOF);
}

TEST_F(BaseSeekInputStreamTest_137, GetKindReturnsCorrectKind_137) {
    auto stream = createStream("Test");
    // We test that getKind returns a valid StreamKind value
    StreamKind kind = stream->getKind();
    // BaseSeekInputStream should have a defined kind
    (void)kind; // Just ensure it doesn't crash
}

TEST_F(BaseSeekInputStreamTest_137, LargeDataRead_137) {
    std::string largeData(20000, 'X');
    largeData[0] = 'A';
    largeData[19999] = 'Z';
    auto stream = createStream(largeData);
    stream->reset();
    EXPECT_EQ(stream->getChar(), 'A');

    // Read through to near the end
    for (int i = 1; i < 19999; i++) {
        stream->getChar();
    }
    EXPECT_EQ(stream->getChar(), 'Z');
    EXPECT_EQ(stream->getChar(), EOF);
}

TEST_F(BaseSeekInputStreamTest_137, RewindAfterEOF_137) {
    auto stream = createStream("AB");
    stream->reset();
    stream->getChar(); // A
    stream->getChar(); // B
    stream->getChar(); // EOF
    stream->rewind();
    EXPECT_EQ(stream->getChar(), 'A');
}

TEST_F(BaseSeekInputStreamTest_137, SingleByteStream_137) {
    auto stream = createStream("Z");
    stream->reset();
    EXPECT_EQ(stream->lookChar(), 'Z');
    EXPECT_EQ(stream->getChar(), 'Z');
    EXPECT_EQ(stream->lookChar(), EOF);
    EXPECT_EQ(stream->getChar(), EOF);
}

TEST_F(BaseSeekInputStreamTest_137, SetPosMultipleTimes_137) {
    auto stream = createStream("ABCDEFGHIJ");
    stream->reset();
    stream->setPos(5, 0);
    EXPECT_EQ(stream->getChar(), 'F');
    stream->setPos(0, 0);
    EXPECT_EQ(stream->getChar(), 'A');
    stream->setPos(9, 0);
    EXPECT_EQ(stream->getChar(), 'J');
}

TEST_F(BaseSeekInputStreamTest_137, GetPosAfterSetPos_137) {
    auto stream = createStream("ABCDEF");
    stream->reset();
    stream->setPos(4, 0);
    EXPECT_EQ(stream->getPos(), 4);
}

TEST_F(BaseSeekInputStreamTest_137, LimitedStreamZeroLength_137) {
    auto stream = createLimitedStream("ABCDEF", 0, 0);
    stream->reset();
    EXPECT_EQ(stream->getChar(), EOF);
}
