#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Stream.h"
#include "Object.h"
#include <cstring>
#include <memory>

class BaseMemStreamTest_169 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test lookChar on a non-empty stream returns the first byte
TEST_F(BaseMemStreamTest_169, LookCharReturnsFirstByte_169) {
    unsigned char data[] = {0x41, 0x42, 0x43}; // 'A', 'B', 'C'
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(data), 0, 3, std::move(dict));
    stream->reset();
    int ch = stream->lookChar();
    EXPECT_EQ(ch, 0x41);
}

// Test lookChar does not advance the position
TEST_F(BaseMemStreamTest_169, LookCharDoesNotAdvancePosition_169) {
    unsigned char data[] = {0x41, 0x42, 0x43};
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(data), 0, 3, std::move(dict));
    stream->reset();
    int ch1 = stream->lookChar();
    int ch2 = stream->lookChar();
    EXPECT_EQ(ch1, ch2);
    EXPECT_EQ(ch1, 0x41);
}

// Test lookChar returns EOF when stream is empty
TEST_F(BaseMemStreamTest_169, LookCharReturnsEOFOnEmptyStream_169) {
    unsigned char data[] = {0x00};
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(data), 0, 0, std::move(dict));
    stream->reset();
    int ch = stream->lookChar();
    EXPECT_EQ(ch, EOF);
}

// Test lookChar returns EOF after reading all bytes
TEST_F(BaseMemStreamTest_169, LookCharReturnsEOFAtEnd_169) {
    unsigned char data[] = {0x41};
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(data), 0, 1, std::move(dict));
    stream->reset();
    stream->getChar(); // consume the one byte
    int ch = stream->lookChar();
    EXPECT_EQ(ch, EOF);
}

// Test lookChar returns correct value for byte with high bit set (0xff)
TEST_F(BaseMemStreamTest_169, LookCharHandlesHighBitByte_169) {
    unsigned char data[] = {0xFF};
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(data), 0, 1, std::move(dict));
    stream->reset();
    int ch = stream->lookChar();
    EXPECT_EQ(ch, 0xFF);
    EXPECT_NE(ch, EOF); // 0xFF should not be confused with EOF (-1)
}

// Test lookChar returns correct value for zero byte
TEST_F(BaseMemStreamTest_169, LookCharHandlesZeroByte_169) {
    unsigned char data[] = {0x00, 0x42};
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(data), 0, 2, std::move(dict));
    stream->reset();
    int ch = stream->lookChar();
    EXPECT_EQ(ch, 0x00);
}

// Test getChar advances position and lookChar reflects the next byte
TEST_F(BaseMemStreamTest_169, LookCharAfterGetCharShowsNextByte_169) {
    unsigned char data[] = {0x41, 0x42, 0x43};
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(data), 0, 3, std::move(dict));
    stream->reset();
    
    int first = stream->getChar();
    EXPECT_EQ(first, 0x41);
    
    int looked = stream->lookChar();
    EXPECT_EQ(looked, 0x42);
}

// Test getChar returns bytes in sequence
TEST_F(BaseMemStreamTest_169, GetCharReturnsSequentialBytes_169) {
    unsigned char data[] = {0x10, 0x20, 0x30, 0x40};
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(data), 0, 4, std::move(dict));
    stream->reset();
    
    EXPECT_EQ(stream->getChar(), 0x10);
    EXPECT_EQ(stream->getChar(), 0x20);
    EXPECT_EQ(stream->getChar(), 0x30);
    EXPECT_EQ(stream->getChar(), 0x40);
    EXPECT_EQ(stream->getChar(), EOF);
}

// Test getChar returns EOF on empty stream
TEST_F(BaseMemStreamTest_169, GetCharReturnsEOFOnEmptyStream_169) {
    unsigned char data[] = {0x00};
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(data), 0, 0, std::move(dict));
    stream->reset();
    EXPECT_EQ(stream->getChar(), EOF);
}

// Test rewind resets position
TEST_F(BaseMemStreamTest_169, RewindResetsPosition_169) {
    unsigned char data[] = {0x41, 0x42, 0x43};
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(data), 0, 3, std::move(dict));
    stream->reset();
    
    stream->getChar();
    stream->getChar();
    
    bool result = stream->rewind();
    EXPECT_TRUE(result);
    
    int ch = stream->lookChar();
    EXPECT_EQ(ch, 0x41);
}

// Test getPos returns current position
TEST_F(BaseMemStreamTest_169, GetPosReturnsCorrectPosition_169) {
    unsigned char data[] = {0x41, 0x42, 0x43};
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(data), 0, 3, std::move(dict));
    stream->reset();
    
    EXPECT_EQ(stream->getPos(), 0);
    stream->getChar();
    EXPECT_EQ(stream->getPos(), 1);
    stream->getChar();
    EXPECT_EQ(stream->getPos(), 2);
}

// Test setPos sets position correctly
TEST_F(BaseMemStreamTest_169, SetPosSetsPositionCorrectly_169) {
    unsigned char data[] = {0x41, 0x42, 0x43, 0x44, 0x45};
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(data), 0, 5, std::move(dict));
    stream->reset();
    
    stream->setPos(3);
    int ch = stream->lookChar();
    EXPECT_EQ(ch, 0x44);
}

// Test setPos with dir=-1 sets position from end
TEST_F(BaseMemStreamTest_169, SetPosFromEnd_169) {
    unsigned char data[] = {0x41, 0x42, 0x43, 0x44, 0x45};
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(data), 0, 5, std::move(dict));
    stream->reset();
    
    stream->setPos(0, -1); // seek to end
    int ch = stream->lookChar();
    EXPECT_EQ(ch, EOF);
}

// Test getKind returns the correct stream kind
TEST_F(BaseMemStreamTest_169, GetKindReturnsMemStream_169) {
    unsigned char data[] = {0x41};
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(data), 0, 1, std::move(dict));
    EXPECT_EQ(stream->getKind(), strWeird);
}

// Test getStart returns the start offset
TEST_F(BaseMemStreamTest_169, GetStartReturnsStartOffset_169) {
    unsigned char data[] = {0x41, 0x42, 0x43};
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(data), 0, 3, std::move(dict));
    EXPECT_EQ(stream->getStart(), 0);
}

// Test moveStart moves the start
TEST_F(BaseMemStreamTest_169, MoveStartMovesStartForward_169) {
    unsigned char data[] = {0x41, 0x42, 0x43, 0x44};
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(data), 0, 4, std::move(dict));
    
    stream->moveStart(2);
    EXPECT_EQ(stream->getStart(), 2);
}

// Test lookChar with various byte values ensures masking with 0xff
TEST_F(BaseMemStreamTest_169, LookCharMasksWith0xFF_169) {
    unsigned char data[] = {0x80, 0x7F, 0xFE, 0x01};
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(data), 0, 4, std::move(dict));
    stream->reset();
    
    EXPECT_EQ(stream->lookChar(), 0x80);
    stream->getChar();
    EXPECT_EQ(stream->lookChar(), 0x7F);
    stream->getChar();
    EXPECT_EQ(stream->lookChar(), 0xFE);
    stream->getChar();
    EXPECT_EQ(stream->lookChar(), 0x01);
    stream->getChar();
    EXPECT_EQ(stream->lookChar(), EOF);
}

// Test copy creates a valid copy
TEST_F(BaseMemStreamTest_169, CopyCreatesValidStream_169) {
    unsigned char data[] = {0x41, 0x42, 0x43};
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(data), 0, 3, std::move(dict));
    
    auto copied = stream->copy();
    ASSERT_NE(copied, nullptr);
    copied->reset();
    
    EXPECT_EQ(copied->getChar(), 0x41);
    EXPECT_EQ(copied->getChar(), 0x42);
    EXPECT_EQ(copied->getChar(), 0x43);
    EXPECT_EQ(copied->getChar(), EOF);
}

// Test makeSubStream creates a valid sub-stream
TEST_F(BaseMemStreamTest_169, MakeSubStreamCreatesValidStream_169) {
    unsigned char data[] = {0x41, 0x42, 0x43, 0x44, 0x45};
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(data), 0, 5, std::move(dict));
    
    Object subDict;
    auto subStream = stream->makeSubStream(1, true, 3, std::move(subDict));
    ASSERT_NE(subStream, nullptr);
    subStream->reset();
    
    EXPECT_EQ(subStream->getChar(), 0x42);
    EXPECT_EQ(subStream->getChar(), 0x43);
    EXPECT_EQ(subStream->getChar(), 0x44);
    EXPECT_EQ(subStream->getChar(), EOF);
}

// Test repeated lookChar calls at EOF always return EOF
TEST_F(BaseMemStreamTest_169, RepeatedLookCharAtEOFReturnsEOF_169) {
    unsigned char data[] = {0x41};
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(data), 0, 1, std::move(dict));
    stream->reset();
    stream->getChar();
    
    EXPECT_EQ(stream->lookChar(), EOF);
    EXPECT_EQ(stream->lookChar(), EOF);
    EXPECT_EQ(stream->lookChar(), EOF);
}

// Test close and then operations
TEST_F(BaseMemStreamTest_169, CloseStream_169) {
    unsigned char data[] = {0x41, 0x42};
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(data), 0, 2, std::move(dict));
    stream->reset();
    stream->close();
    // After close, behavior may vary but shouldn't crash
    // Re-reset should work
    stream->reset();
    EXPECT_EQ(stream->lookChar(), 0x41);
}

// Test single byte stream
TEST_F(BaseMemStreamTest_169, SingleByteStream_169) {
    unsigned char data[] = {0xAB};
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(data), 0, 1, std::move(dict));
    stream->reset();
    
    EXPECT_EQ(stream->lookChar(), 0xAB);
    EXPECT_EQ(stream->getChar(), 0xAB);
    EXPECT_EQ(stream->lookChar(), EOF);
    EXPECT_EQ(stream->getChar(), EOF);
}

// Test stream with start offset
TEST_F(BaseMemStreamTest_169, StreamWithStartOffset_169) {
    unsigned char data[] = {0x41, 0x42, 0x43, 0x44, 0x45};
    Object dict;
    // Create stream starting at offset 2
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(data + 2), 2, 3, std::move(dict));
    stream->reset();
    
    EXPECT_EQ(stream->lookChar(), 0x43);
    EXPECT_EQ(stream->getStart(), 2);
}

// Test getUnfilteredChar
TEST_F(BaseMemStreamTest_169, GetUnfilteredChar_169) {
    unsigned char data[] = {0x41, 0x42, 0x43};
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(data), 0, 3, std::move(dict));
    stream->reset();
    
    int ch = stream->getUnfilteredChar();
    EXPECT_EQ(ch, 0x41);
}

// Test unfilteredRewind
TEST_F(BaseMemStreamTest_169, UnfilteredRewind_169) {
    unsigned char data[] = {0x41, 0x42, 0x43};
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(data), 0, 3, std::move(dict));
    stream->reset();
    
    stream->getChar();
    stream->getChar();
    bool result = stream->unfilteredRewind();
    EXPECT_TRUE(result);
    
    EXPECT_EQ(stream->lookChar(), 0x41);
}

// Test large stream lookChar
TEST_F(BaseMemStreamTest_169, LargeStreamLookChar_169) {
    const int size = 65536;
    unsigned char data[size];
    for (int i = 0; i < size; i++) {
        data[i] = static_cast<unsigned char>(i & 0xFF);
    }
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(data), 0, size, std::move(dict));
    stream->reset();
    
    EXPECT_EQ(stream->lookChar(), 0x00);
    
    // Seek near end
    stream->setPos(size - 1);
    EXPECT_EQ(stream->lookChar(), static_cast<int>((size - 1) & 0xFF));
    
    stream->getChar();
    EXPECT_EQ(stream->lookChar(), EOF);
}
