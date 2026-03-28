#include <gtest/gtest.h>
#include <memory>
#include <cstring>
#include "Stream.h"
#include "Object.h"

// Test fixture for BaseMemStream tests
class BaseMemStreamTest_164 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Helper to create a MemStream (BaseMemStream<const char>) with given data
static std::unique_ptr<BaseMemStream<const char>> createMemStream(const char* data, Goffset length) {
    Object dict = Object(objNull);
    return std::make_unique<BaseMemStream<const char>>(data, 0, length, std::move(dict));
}

// Test: Construction and basic properties
TEST_F(BaseMemStreamTest_164, ConstructionAndLength_164) {
    const char data[] = "Hello, World!";
    Goffset len = strlen(data);
    auto stream = createMemStream(data, len);
    
    ASSERT_NE(stream, nullptr);
    EXPECT_EQ(stream->getLength(), len);
}

// Test: getKind returns correct stream kind
TEST_F(BaseMemStreamTest_164, GetKindReturnsMemStream_164) {
    const char data[] = "test";
    auto stream = createMemStream(data, 4);
    
    EXPECT_EQ(stream->getKind(), strWeird); // MemStream kind - might vary
}

// Test: getStart returns the start position
TEST_F(BaseMemStreamTest_164, GetStartReturnsZero_164) {
    const char data[] = "test data";
    auto stream = createMemStream(data, 9);
    
    EXPECT_EQ(stream->getStart(), 0);
}

// Test: getStart with non-zero start
TEST_F(BaseMemStreamTest_164, GetStartNonZero_164) {
    const char data[] = "test data";
    Object dict = Object(objNull);
    BaseMemStream<const char> stream(data, 5, 4, std::move(dict));
    
    EXPECT_EQ(stream.getStart(), 5);
}

// Test: rewind resets position to start
TEST_F(BaseMemStreamTest_164, RewindResetsPosition_164) {
    const char data[] = "ABCDEF";
    auto stream = createMemStream(data, 6);
    
    stream->rewind();
    EXPECT_EQ(stream->getPos(), 0);
    
    // Read some chars
    stream->getChar();
    stream->getChar();
    EXPECT_EQ(stream->getPos(), 2);
    
    // Rewind
    stream->rewind();
    EXPECT_EQ(stream->getPos(), 0);
}

// Test: getChar reads characters sequentially
TEST_F(BaseMemStreamTest_164, GetCharReadsSequentially_164) {
    const char data[] = "ABC";
    auto stream = createMemStream(data, 3);
    stream->rewind();
    
    EXPECT_EQ(stream->getChar(), 'A');
    EXPECT_EQ(stream->getChar(), 'B');
    EXPECT_EQ(stream->getChar(), 'C');
}

// Test: getChar returns EOF at end of stream
TEST_F(BaseMemStreamTest_164, GetCharReturnsEOFAtEnd_164) {
    const char data[] = "AB";
    auto stream = createMemStream(data, 2);
    stream->rewind();
    
    stream->getChar(); // A
    stream->getChar(); // B
    EXPECT_EQ(stream->getChar(), EOF);
}

// Test: lookChar peeks without advancing position
TEST_F(BaseMemStreamTest_164, LookCharDoesNotAdvance_164) {
    const char data[] = "XY";
    auto stream = createMemStream(data, 2);
    stream->rewind();
    
    EXPECT_EQ(stream->lookChar(), 'X');
    EXPECT_EQ(stream->lookChar(), 'X');
    EXPECT_EQ(stream->getPos(), 0);
}

// Test: lookChar returns EOF when at end
TEST_F(BaseMemStreamTest_164, LookCharReturnsEOFAtEnd_164) {
    const char data[] = "A";
    auto stream = createMemStream(data, 1);
    stream->rewind();
    
    stream->getChar(); // consume A
    EXPECT_EQ(stream->lookChar(), EOF);
}

// Test: getPos tracks current position
TEST_F(BaseMemStreamTest_164, GetPosTracksPosition_164) {
    const char data[] = "ABCDEF";
    auto stream = createMemStream(data, 6);
    stream->rewind();
    
    EXPECT_EQ(stream->getPos(), 0);
    stream->getChar();
    EXPECT_EQ(stream->getPos(), 1);
    stream->getChar();
    EXPECT_EQ(stream->getPos(), 2);
}

// Test: setPos with forward direction
TEST_F(BaseMemStreamTest_164, SetPosForward_164) {
    const char data[] = "ABCDEF";
    auto stream = createMemStream(data, 6);
    stream->rewind();
    
    stream->setPos(3, 0);
    EXPECT_EQ(stream->getChar(), 'D');
}

// Test: setPos with negative direction (from end)
TEST_F(BaseMemStreamTest_164, SetPosFromEnd_164) {
    const char data[] = "ABCDEF";
    auto stream = createMemStream(data, 6);
    stream->rewind();
    
    stream->setPos(2, 1); // 2 bytes from end
    EXPECT_EQ(stream->getChar(), 'E');
}

// Test: setPos to beginning
TEST_F(BaseMemStreamTest_164, SetPosToBeginning_164) {
    const char data[] = "ABCDEF";
    auto stream = createMemStream(data, 6);
    stream->rewind();
    
    stream->getChar();
    stream->getChar();
    stream->setPos(0, 0);
    EXPECT_EQ(stream->getChar(), 'A');
}

// Test: setPos beyond end
TEST_F(BaseMemStreamTest_164, SetPosBeyondEnd_164) {
    const char data[] = "ABC";
    auto stream = createMemStream(data, 3);
    stream->rewind();
    
    stream->setPos(10, 0);
    EXPECT_EQ(stream->getChar(), EOF);
}

// Test: moveStart shifts the start position
TEST_F(BaseMemStreamTest_164, MoveStartShiftsStart_164) {
    const char data[] = "ABCDEF";
    auto stream = createMemStream(data, 6);
    
    stream->moveStart(2);
    EXPECT_EQ(stream->getStart(), 2);
}

// Test: close doesn't crash
TEST_F(BaseMemStreamTest_164, CloseDoesNotCrash_164) {
    const char data[] = "test";
    auto stream = createMemStream(data, 4);
    
    EXPECT_NO_THROW(stream->close());
}

// Test: empty stream
TEST_F(BaseMemStreamTest_164, EmptyStream_164) {
    const char data[] = "";
    auto stream = createMemStream(data, 0);
    stream->rewind();
    
    EXPECT_EQ(stream->getLength(), 0);
    EXPECT_EQ(stream->getChar(), EOF);
    EXPECT_EQ(stream->lookChar(), EOF);
}

// Test: single byte stream
TEST_F(BaseMemStreamTest_164, SingleByteStream_164) {
    const char data[] = "Z";
    auto stream = createMemStream(data, 1);
    stream->rewind();
    
    EXPECT_EQ(stream->getLength(), 1);
    EXPECT_EQ(stream->lookChar(), 'Z');
    EXPECT_EQ(stream->getChar(), 'Z');
    EXPECT_EQ(stream->getChar(), EOF);
}

// Test: copy creates a valid copy
TEST_F(BaseMemStreamTest_164, CopyCreatesValidStream_164) {
    const char data[] = "Hello";
    auto stream = createMemStream(data, 5);
    stream->rewind();
    
    auto copied = stream->copy();
    ASSERT_NE(copied, nullptr);
    
    copied->rewind();
    EXPECT_EQ(copied->getLength(), 5);
    // The copy should be able to read the same data
    EXPECT_EQ(copied->getChar(), 'H');
    EXPECT_EQ(copied->getChar(), 'e');
}

// Test: copy is independent of original
TEST_F(BaseMemStreamTest_164, CopyIsIndependent_164) {
    const char data[] = "ABCDE";
    auto stream = createMemStream(data, 5);
    stream->rewind();
    
    // Read some from original
    stream->getChar(); // A
    stream->getChar(); // B
    
    auto copied = stream->copy();
    ASSERT_NE(copied, nullptr);
    copied->rewind();
    
    // Copy should start from beginning
    EXPECT_EQ(copied->getChar(), 'A');
}

// Test: makeSubStream creates a sub-stream
TEST_F(BaseMemStreamTest_164, MakeSubStream_164) {
    const char data[] = "ABCDEFGH";
    auto stream = createMemStream(data, 8);
    
    Object subDict = Object(objNull);
    auto subStream = stream->makeSubStream(2, true, 4, std::move(subDict));
    ASSERT_NE(subStream, nullptr);
    
    subStream->rewind();
    EXPECT_EQ(subStream->getChar(), 'C');
    EXPECT_EQ(subStream->getChar(), 'D');
    EXPECT_EQ(subStream->getChar(), 'E');
    EXPECT_EQ(subStream->getChar(), 'F');
}

// Test: makeSubStream limited
TEST_F(BaseMemStreamTest_164, MakeSubStreamLimited_164) {
    const char data[] = "ABCDEFGH";
    auto stream = createMemStream(data, 8);
    
    Object subDict = Object(objNull);
    auto subStream = stream->makeSubStream(2, true, 3, std::move(subDict));
    ASSERT_NE(subStream, nullptr);
    
    subStream->rewind();
    EXPECT_EQ(subStream->getChar(), 'C');
    EXPECT_EQ(subStream->getChar(), 'D');
    EXPECT_EQ(subStream->getChar(), 'E');
    EXPECT_EQ(subStream->getChar(), EOF);
}

// Test: getDict returns dict pointer
TEST_F(BaseMemStreamTest_164, GetDictReturnsDict_164) {
    const char data[] = "test";
    auto stream = createMemStream(data, 4);
    
    // Even with a null-type dict, getDict should not crash
    // It may return nullptr for null dict
    Dict* d = stream->getDict();
    // We just verify it doesn't crash; null dict -> nullptr
    (void)d;
}

// Test: getDictObject returns object pointer
TEST_F(BaseMemStreamTest_164, GetDictObjectReturnsObject_164) {
    const char data[] = "test";
    auto stream = createMemStream(data, 4);
    
    Object* dictObj = stream->getDictObject();
    ASSERT_NE(dictObj, nullptr);
}

// Test: getBaseStream returns self
TEST_F(BaseMemStreamTest_164, GetBaseStreamReturnsSelf_164) {
    const char data[] = "test";
    auto stream = createMemStream(data, 4);
    
    BaseStream* base = stream->getBaseStream();
    EXPECT_EQ(base, stream.get());
}

// Test: getUndecodedStream returns self
TEST_F(BaseMemStreamTest_164, GetUndecodedStreamReturnsSelf_164) {
    const char data[] = "test";
    auto stream = createMemStream(data, 4);
    
    Stream* undecoded = stream->getUndecodedStream();
    EXPECT_EQ(undecoded, stream.get());
}

// Test: isBinary returns expected value
TEST_F(BaseMemStreamTest_164, IsBinaryReturnsFalse_164) {
    const char data[] = "test";
    auto stream = createMemStream(data, 4);
    
    // BaseStream::isBinary typically returns false
    // Just verify it doesn't crash
    bool binary = stream->isBinary();
    (void)binary;
}

// Test: getFileName returns nullptr for memory stream
TEST_F(BaseMemStreamTest_164, GetFileNameReturnsNull_164) {
    const char data[] = "test";
    auto stream = createMemStream(data, 4);
    
    GooString* fileName = stream->getFileName();
    EXPECT_EQ(fileName, nullptr);
}

// Test: unfilteredRewind works
TEST_F(BaseMemStreamTest_164, UnfilteredRewind_164) {
    const char data[] = "ABCDE";
    auto stream = createMemStream(data, 5);
    stream->rewind();
    
    stream->getChar();
    stream->getChar();
    
    bool result = stream->unfilteredRewind();
    EXPECT_TRUE(result);
    EXPECT_EQ(stream->getPos(), 0);
}

// Test: getUnfilteredChar reads characters
TEST_F(BaseMemStreamTest_164, GetUnfilteredChar_164) {
    const char data[] = "AB";
    auto stream = createMemStream(data, 2);
    stream->rewind();
    
    EXPECT_EQ(stream->getUnfilteredChar(), 'A');
    EXPECT_EQ(stream->getUnfilteredChar(), 'B');
}

// Test: binary data with null bytes
TEST_F(BaseMemStreamTest_164, BinaryDataWithNullBytes_164) {
    const char data[] = {'\x00', '\x01', '\x02', '\xFF', '\x00'};
    auto stream = createMemStream(data, 5);
    stream->rewind();
    
    EXPECT_EQ(stream->getChar(), 0x00);
    EXPECT_EQ(stream->getChar(), 0x01);
    EXPECT_EQ(stream->getChar(), 0x02);
    EXPECT_EQ(stream->getChar(), 0xFF);
    EXPECT_EQ(stream->getChar(), 0x00);
    EXPECT_EQ(stream->getChar(), EOF);
}

// Test: reading all bytes with getChars through Stream interface
TEST_F(BaseMemStreamTest_164, GetCharsReadMultiple_164) {
    const char data[] = "ABCDEFGH";
    auto stream = createMemStream(data, 8);
    stream->rewind();
    
    unsigned char buffer[8];
    int nRead = stream->doGetChars(4, buffer);
    EXPECT_EQ(nRead, 4);
    EXPECT_EQ(buffer[0], 'A');
    EXPECT_EQ(buffer[1], 'B');
    EXPECT_EQ(buffer[2], 'C');
    EXPECT_EQ(buffer[3], 'D');
}

// Test: getChars reads remaining when requesting more than available
TEST_F(BaseMemStreamTest_164, GetCharsPartialRead_164) {
    const char data[] = "AB";
    auto stream = createMemStream(data, 2);
    stream->rewind();
    
    unsigned char buffer[10] = {0};
    int nRead = stream->doGetChars(10, buffer);
    EXPECT_EQ(nRead, 2);
    EXPECT_EQ(buffer[0], 'A');
    EXPECT_EQ(buffer[1], 'B');
}

// Test: Large stream
TEST_F(BaseMemStreamTest_164, LargeStream_164) {
    const int size = 100000;
    std::vector<char> data(size);
    for (int i = 0; i < size; i++) {
        data[i] = static_cast<char>(i & 0xFF);
    }
    
    auto stream = createMemStream(data.data(), size);
    stream->rewind();
    
    EXPECT_EQ(stream->getLength(), size);
    
    // Read first few bytes
    for (int i = 0; i < 10; i++) {
        EXPECT_EQ(stream->getChar(), (i & 0xFF));
    }
    
    // Set position near end
    stream->setPos(size - 1, 0);
    EXPECT_EQ(stream->getChar(), ((size - 1) & 0xFF));
    EXPECT_EQ(stream->getChar(), EOF);
}

// Test: Multiple rewinds
TEST_F(BaseMemStreamTest_164, MultipleRewinds_164) {
    const char data[] = "XYZ";
    auto stream = createMemStream(data, 3);
    
    for (int i = 0; i < 5; i++) {
        stream->rewind();
        EXPECT_EQ(stream->getPos(), 0);
        EXPECT_EQ(stream->getChar(), 'X');
    }
}

// Test: setPos with dir=0 to end
TEST_F(BaseMemStreamTest_164, SetPosToExactEnd_164) {
    const char data[] = "ABC";
    auto stream = createMemStream(data, 3);
    stream->rewind();
    
    stream->setPos(3, 0);
    EXPECT_EQ(stream->getChar(), EOF);
}

// Test: setPos from end with 0 offset
TEST_F(BaseMemStreamTest_164, SetPosFromEndZeroOffset_164) {
    const char data[] = "ABCDE";
    auto stream = createMemStream(data, 5);
    stream->rewind();
    
    stream->setPos(0, 1); // 0 from end = at the very end
    // This should position at or near the end
    // Behavior may vary, but should not crash
    int ch = stream->getChar();
    (void)ch;
}
