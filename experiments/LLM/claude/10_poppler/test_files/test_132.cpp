#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Stream.h"
#include "Object.h"

// Concrete test implementation of BaseSeekInputStream for testing purposes
class TestSeekInputStream : public BaseSeekInputStream {
public:
    TestSeekInputStream(const std::string &data, Goffset startA = 0, bool limitedA = false, Goffset lengthA = 0)
        : BaseSeekInputStream(startA, limitedA, lengthA, Object(objNull)),
          data_(data), currentPos_(0) {}

    TestSeekInputStream(Goffset startA, bool limitedA, Goffset lengthA)
        : BaseSeekInputStream(startA, limitedA, lengthA, Object(objNull)),
          data_(""), currentPos_(0) {}

    ~TestSeekInputStream() override = default;

    void setData(const std::string &data) { data_ = data; }

private:
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
        if (available <= 0) return 0;
        Goffset toRead = (size < available) ? size : available;
        memcpy(buf, data_.c_str() + currentPos_, toRead);
        currentPos_ += toRead;
        return toRead;
    }

    std::string data_;
    Goffset currentPos_;
};

class BaseSeekInputStreamTest_132 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that getKind returns strWeird
TEST_F(BaseSeekInputStreamTest_132, GetKindReturnsStrWeird_132) {
    TestSeekInputStream stream("hello", 0, false, 0);
    EXPECT_EQ(stream.getKind(), strWeird);
}

// Test reading characters from the stream
TEST_F(BaseSeekInputStreamTest_132, GetCharReadsSequentially_132) {
    TestSeekInputStream stream("ABC", 0, false, 0);
    stream.reset();
    EXPECT_EQ(stream.getChar(), 'A');
    EXPECT_EQ(stream.getChar(), 'B');
    EXPECT_EQ(stream.getChar(), 'C');
}

// Test getChar returns EOF at end of data
TEST_F(BaseSeekInputStreamTest_132, GetCharReturnsEOFAtEnd_132) {
    TestSeekInputStream stream("A", 0, false, 0);
    stream.reset();
    EXPECT_EQ(stream.getChar(), 'A');
    EXPECT_EQ(stream.getChar(), EOF);
}

// Test lookChar peeks without advancing
TEST_F(BaseSeekInputStreamTest_132, LookCharDoesNotAdvance_132) {
    TestSeekInputStream stream("XY", 0, false, 0);
    stream.reset();
    EXPECT_EQ(stream.lookChar(), 'X');
    EXPECT_EQ(stream.lookChar(), 'X');
    EXPECT_EQ(stream.getChar(), 'X');
    EXPECT_EQ(stream.lookChar(), 'Y');
}

// Test getPos returns current position
TEST_F(BaseSeekInputStreamTest_132, GetPosReturnsCurrentPosition_132) {
    TestSeekInputStream stream("ABCDEF", 0, false, 0);
    stream.reset();
    Goffset startPos = stream.getPos();
    stream.getChar();
    Goffset afterOne = stream.getPos();
    EXPECT_EQ(afterOne - startPos, 1);
}

// Test getStart returns the start offset
TEST_F(BaseSeekInputStreamTest_132, GetStartReturnsStartOffset_132) {
    TestSeekInputStream stream("hello", 10, false, 0);
    EXPECT_EQ(stream.getStart(), 10);
}

// Test rewind returns to beginning
TEST_F(BaseSeekInputStreamTest_132, RewindResetsPosition_132) {
    TestSeekInputStream stream("ABCD", 0, false, 0);
    stream.reset();
    stream.getChar(); // A
    stream.getChar(); // B
    bool result = stream.rewind();
    // After rewind we should be able to read from the start
    // The rewind should succeed
    // Read first char again
    int ch = stream.getChar();
    EXPECT_EQ(ch, 'A');
}

// Test empty stream returns EOF immediately
TEST_F(BaseSeekInputStreamTest_132, EmptyStreamReturnsEOF_132) {
    TestSeekInputStream stream("", 0, false, 0);
    stream.reset();
    EXPECT_EQ(stream.getChar(), EOF);
}

// Test lookChar on empty stream returns EOF
TEST_F(BaseSeekInputStreamTest_132, LookCharOnEmptyStreamReturnsEOF_132) {
    TestSeekInputStream stream("", 0, false, 0);
    stream.reset();
    EXPECT_EQ(stream.lookChar(), EOF);
}

// Test setPos with direction 0 (from start)
TEST_F(BaseSeekInputStreamTest_132, SetPosFromStart_132) {
    TestSeekInputStream stream("ABCDEFGH", 0, false, 0);
    stream.reset();
    stream.setPos(3, 0);
    EXPECT_EQ(stream.getChar(), 'D');
}

// Test moveStart adjusts the start position
TEST_F(BaseSeekInputStreamTest_132, MoveStartAdjustsStart_132) {
    TestSeekInputStream stream("ABCDEFGH", 0, false, 0);
    stream.moveStart(2);
    EXPECT_EQ(stream.getStart(), 2);
}

// Test limited stream with specific length
TEST_F(BaseSeekInputStreamTest_132, LimitedStreamRespectsLength_132) {
    TestSeekInputStream stream("ABCDEFGHIJ", 0, true, 3);
    stream.reset();
    EXPECT_EQ(stream.getChar(), 'A');
    EXPECT_EQ(stream.getChar(), 'B');
    EXPECT_EQ(stream.getChar(), 'C');
    // Should get EOF after reading 3 characters
    EXPECT_EQ(stream.getChar(), EOF);
}

// Test getUnfilteredChar
TEST_F(BaseSeekInputStreamTest_132, GetUnfilteredCharReadsCharacter_132) {
    TestSeekInputStream stream("MNO", 0, false, 0);
    stream.reset();
    int ch = stream.getUnfilteredChar();
    EXPECT_EQ(ch, 'M');
}

// Test unfilteredRewind
TEST_F(BaseSeekInputStreamTest_132, UnfilteredRewind_132) {
    TestSeekInputStream stream("PQR", 0, false, 0);
    stream.reset();
    stream.getChar();
    stream.getChar();
    bool result = stream.unfilteredRewind();
    // After unfiltered rewind, should read from start
    int ch = stream.getChar();
    EXPECT_EQ(ch, 'P');
}

// Test close and then operations
TEST_F(BaseSeekInputStreamTest_132, CloseStream_132) {
    TestSeekInputStream stream("Test", 0, false, 0);
    stream.reset();
    stream.getChar();
    stream.close();
    // After close, behavior may vary - just verify it doesn't crash
}

// Test with non-zero start offset
TEST_F(BaseSeekInputStreamTest_132, NonZeroStartOffset_132) {
    TestSeekInputStream stream("ABCDEFGH", 3, false, 0);
    EXPECT_EQ(stream.getStart(), 3);
}

// Test reading single byte data
TEST_F(BaseSeekInputStreamTest_132, SingleByteData_132) {
    TestSeekInputStream stream("Z", 0, false, 0);
    stream.reset();
    EXPECT_EQ(stream.getChar(), 'Z');
    EXPECT_EQ(stream.getChar(), EOF);
}

// Test binary data (non-printable characters)
TEST_F(BaseSeekInputStreamTest_132, BinaryData_132) {
    std::string binaryData;
    binaryData.push_back('\x00');
    binaryData.push_back('\x01');
    binaryData.push_back('\xFF');
    TestSeekInputStream stream(binaryData, 0, false, 0);
    stream.reset();
    EXPECT_EQ(stream.getChar(), 0x00);
    EXPECT_EQ(stream.getChar(), 0x01);
    EXPECT_EQ(stream.getChar(), 0xFF);
    EXPECT_EQ(stream.getChar(), EOF);
}

// Test limited stream with length zero
TEST_F(BaseSeekInputStreamTest_132, LimitedStreamZeroLength_132) {
    TestSeekInputStream stream("ABCDEF", 0, true, 0);
    stream.reset();
    EXPECT_EQ(stream.getChar(), EOF);
}

// Test setPos to position 0
TEST_F(BaseSeekInputStreamTest_132, SetPosToZero_132) {
    TestSeekInputStream stream("ABCDEF", 0, false, 0);
    stream.reset();
    stream.getChar();
    stream.getChar();
    stream.getChar();
    stream.setPos(0, 0);
    EXPECT_EQ(stream.getChar(), 'A');
}

// Test multiple rewinds
TEST_F(BaseSeekInputStreamTest_132, MultipleRewinds_132) {
    TestSeekInputStream stream("AB", 0, false, 0);
    stream.reset();
    stream.getChar();
    stream.rewind();
    EXPECT_EQ(stream.getChar(), 'A');
    stream.rewind();
    EXPECT_EQ(stream.getChar(), 'A');
}
