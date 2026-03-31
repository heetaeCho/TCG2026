#include <gtest/gtest.h>
#include <memory>
#include "poppler/Stream.h"
#include "poppler/Object.h"

// Test fixture for BaseMemStream
class BaseMemStreamTest_171 : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a buffer with known content
        for (int i = 0; i < bufSize; i++) {
            buffer[i] = static_cast<unsigned char>(i & 0xFF);
        }
    }

    static const int bufSize = 256;
    unsigned char buffer[256];
};

// Test: setPos with dir >= 0 sets position to given pos
TEST_F(BaseMemStreamTest_171, SetPosForwardSetsPosition_171) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buffer), 0, bufSize, std::move(dict));
    
    stream->setPos(10, 0);
    EXPECT_EQ(stream->getPos(), 10);
}

// Test: setPos with dir >= 0 at position 0
TEST_F(BaseMemStreamTest_171, SetPosForwardAtZero_171) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buffer), 0, bufSize, std::move(dict));
    
    stream->setPos(0, 0);
    EXPECT_EQ(stream->getPos(), 0);
}

// Test: setPos with dir >= 0 at end of stream
TEST_F(BaseMemStreamTest_171, SetPosForwardAtEnd_171) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buffer), 0, bufSize, std::move(dict));
    
    stream->setPos(bufSize, 0);
    EXPECT_EQ(stream->getPos(), bufSize);
}

// Test: setPos with dir >= 0 beyond end clamps to end
TEST_F(BaseMemStreamTest_171, SetPosForwardBeyondEndClampsToEnd_171) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buffer), 0, bufSize, std::move(dict));
    
    stream->setPos(bufSize + 100, 0);
    EXPECT_EQ(stream->getPos(), bufSize);
}

// Test: setPos with dir >= 0 with negative pos clamps to start
TEST_F(BaseMemStreamTest_171, SetPosForwardNegativeClampsToStart_171) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buffer), 0, bufSize, std::move(dict));
    
    stream->setPos(-5, 0);
    EXPECT_EQ(stream->getPos(), 0);
}

// Test: setPos with dir < 0 sets position relative to end
TEST_F(BaseMemStreamTest_171, SetPosBackwardFromEnd_171) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buffer), 0, bufSize, std::move(dict));
    
    stream->setPos(10, -1);
    // Position should be start + length - pos = 0 + 256 - 10 = 246
    EXPECT_EQ(stream->getPos(), bufSize - 10);
}

// Test: setPos with dir < 0, pos = 0 means end of stream
TEST_F(BaseMemStreamTest_171, SetPosBackwardZeroMeansEnd_171) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buffer), 0, bufSize, std::move(dict));
    
    stream->setPos(0, -1);
    EXPECT_EQ(stream->getPos(), bufSize);
}

// Test: setPos with dir < 0 beyond stream length clamps to start
TEST_F(BaseMemStreamTest_171, SetPosBackwardBeyondLengthClampsToStart_171) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buffer), 0, bufSize, std::move(dict));
    
    stream->setPos(bufSize + 100, -1);
    EXPECT_EQ(stream->getPos(), 0);
}

// Test: setPos with dir < 0 exactly at length means position 0
TEST_F(BaseMemStreamTest_171, SetPosBackwardExactlyLengthMeansStart_171) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buffer), 0, bufSize, std::move(dict));
    
    stream->setPos(bufSize, -1);
    EXPECT_EQ(stream->getPos(), 0);
}

// Test: setPos with positive dir value (dir = 1) treats as forward
TEST_F(BaseMemStreamTest_171, SetPosWithPositiveDir_171) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buffer), 0, bufSize, std::move(dict));
    
    stream->setPos(50, 1);
    EXPECT_EQ(stream->getPos(), 50);
}

// Test: getChar after setPos reads correct character
TEST_F(BaseMemStreamTest_171, GetCharAfterSetPos_171) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buffer), 0, bufSize, std::move(dict));
    
    stream->setPos(42, 0);
    int ch = stream->getChar();
    EXPECT_EQ(ch, 42);
}

// Test: lookChar after setPos reads correct character without advancing
TEST_F(BaseMemStreamTest_171, LookCharAfterSetPos_171) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buffer), 0, bufSize, std::move(dict));
    
    stream->setPos(42, 0);
    int ch1 = stream->lookChar();
    int ch2 = stream->lookChar();
    EXPECT_EQ(ch1, 42);
    EXPECT_EQ(ch2, 42);
    EXPECT_EQ(stream->getPos(), 42);
}

// Test: rewind resets position to start
TEST_F(BaseMemStreamTest_171, RewindResetsToStart_171) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buffer), 0, bufSize, std::move(dict));
    
    stream->setPos(100, 0);
    EXPECT_EQ(stream->getPos(), 100);
    stream->rewind();
    EXPECT_EQ(stream->getPos(), 0);
}

// Test: getStart returns the start position
TEST_F(BaseMemStreamTest_171, GetStartReturnsStart_171) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buffer), 0, bufSize, std::move(dict));
    
    EXPECT_EQ(stream->getStart(), 0);
}

// Test: moveStart changes the start position
TEST_F(BaseMemStreamTest_171, MoveStartChangesStart_171) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buffer), 0, bufSize, std::move(dict));
    
    stream->moveStart(10);
    EXPECT_EQ(stream->getStart(), 10);
}

// Test: setPos with zero-length stream
TEST_F(BaseMemStreamTest_171, SetPosWithZeroLengthStream_171) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buffer), 0, 0, std::move(dict));
    
    stream->setPos(0, 0);
    EXPECT_EQ(stream->getPos(), 0);
    
    stream->setPos(10, 0);
    EXPECT_EQ(stream->getPos(), 0);
}

// Test: setPos backward with zero-length stream
TEST_F(BaseMemStreamTest_171, SetPosBackwardWithZeroLengthStream_171) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buffer), 0, 0, std::move(dict));
    
    stream->setPos(0, -1);
    EXPECT_EQ(stream->getPos(), 0);
}

// Test: getChar at end of stream returns EOF
TEST_F(BaseMemStreamTest_171, GetCharAtEndReturnsEOF_171) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buffer), 0, bufSize, std::move(dict));
    
    stream->setPos(bufSize, 0);
    int ch = stream->getChar();
    EXPECT_EQ(ch, EOF);
}

// Test: getKind returns memStream kind
TEST_F(BaseMemStreamTest_171, GetKindReturnsMemStream_171) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buffer), 0, bufSize, std::move(dict));
    
    EXPECT_EQ(stream->getKind(), strWeird);
}

// Test: Sequential reads advance position
TEST_F(BaseMemStreamTest_171, SequentialReadsAdvancePosition_171) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buffer), 0, bufSize, std::move(dict));
    
    stream->setPos(0, 0);
    stream->getChar();
    stream->getChar();
    stream->getChar();
    EXPECT_EQ(stream->getPos(), 3);
}

// Test: setPos with non-zero start
TEST_F(BaseMemStreamTest_171, SetPosWithNonZeroStart_171) {
    Object dict;
    Goffset startOffset = 10;
    Goffset length = 100;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buffer), startOffset, length, std::move(dict));
    
    stream->setPos(startOffset + 50, 0);
    EXPECT_EQ(stream->getPos(), startOffset + 50);
}

// Test: setPos backward with non-zero start
TEST_F(BaseMemStreamTest_171, SetPosBackwardWithNonZeroStart_171) {
    Object dict;
    Goffset startOffset = 10;
    Goffset length = 100;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buffer), startOffset, length, std::move(dict));
    
    stream->setPos(20, -1);
    // Position should be start + length - pos = 10 + 100 - 20 = 90
    EXPECT_EQ(stream->getPos(), startOffset + length - 20);
}

// Test: copy creates a valid copy
TEST_F(BaseMemStreamTest_171, CopyCreatesValidCopy_171) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buffer), 0, bufSize, std::move(dict));
    
    auto copy = stream->copy();
    ASSERT_NE(copy, nullptr);
    
    copy->setPos(42, 0);
    int ch = copy->getChar();
    EXPECT_EQ(ch, 42);
}

// Test: setPos default dir parameter
TEST_F(BaseMemStreamTest_171, SetPosDefaultDir_171) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buffer), 0, bufSize, std::move(dict));
    
    // Default dir = 0, which is >= 0, so forward
    stream->setPos(77);
    EXPECT_EQ(stream->getPos(), 77);
}

// Test: setPos with dir = -1 and pos = 1 means one before end
TEST_F(BaseMemStreamTest_171, SetPosBackwardOneFromEnd_171) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buffer), 0, bufSize, std::move(dict));
    
    stream->setPos(1, -1);
    EXPECT_EQ(stream->getPos(), bufSize - 1);
    int ch = stream->getChar();
    EXPECT_EQ(ch, (bufSize - 1) & 0xFF);
}

// Test: Multiple setPos calls work correctly
TEST_F(BaseMemStreamTest_171, MultipleSetPosCalls_171) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buffer), 0, bufSize, std::move(dict));
    
    stream->setPos(10, 0);
    EXPECT_EQ(stream->getPos(), 10);
    
    stream->setPos(200, 0);
    EXPECT_EQ(stream->getPos(), 200);
    
    stream->setPos(5, -1);
    EXPECT_EQ(stream->getPos(), bufSize - 5);
    
    stream->setPos(0, 0);
    EXPECT_EQ(stream->getPos(), 0);
}

// Test: getLength returns correct length
TEST_F(BaseMemStreamTest_171, GetLengthReturnsCorrectLength_171) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buffer), 0, bufSize, std::move(dict));
    
    EXPECT_EQ(stream->getLength(), bufSize);
}

// Test: Small buffer stream
TEST_F(BaseMemStreamTest_171, SmallBufferStream_171) {
    unsigned char smallBuf[1] = {0x42};
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(smallBuf), 0, 1, std::move(dict));
    
    stream->setPos(0, 0);
    EXPECT_EQ(stream->getPos(), 0);
    
    int ch = stream->getChar();
    EXPECT_EQ(ch, 0x42);
    EXPECT_EQ(stream->getPos(), 1);
    
    ch = stream->getChar();
    EXPECT_EQ(ch, EOF);
}
