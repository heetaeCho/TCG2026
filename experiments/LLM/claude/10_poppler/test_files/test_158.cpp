#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "poppler/CachedFile.h"
#include "poppler/Stream.h"
#include "poppler/Object.h"

// Mock CachedFileLoader for creating CachedFile instances
class MockCachedFileLoader : public CachedFileLoader {
public:
    MOCK_METHOD(size_t, init, (GooString *url, CachedFile *cachedFile), (override));
    MOCK_METHOD(int, load, (const std::vector<ByteRange> &ranges, CachedFileWriter *writer), (override));
};

class CachedFileStreamTest_158 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    std::shared_ptr<CachedFile> createCachedFileWithData(const std::vector<unsigned char> &data) {
        auto loader = std::make_unique<MockCachedFileLoader>();
        
        // We expect init to return the size of data
        ON_CALL(*loader, init(testing::_, testing::_))
            .WillByDefault(testing::Invoke([&data](GooString *, CachedFile *cf) -> size_t {
                return data.size();
            }));
        
        // When load is called, write the data
        ON_CALL(*loader, load(testing::_, testing::_))
            .WillByDefault(testing::Invoke([&data](const std::vector<ByteRange> &ranges, CachedFileWriter *writer) -> int {
                for (const auto &range : ranges) {
                    if (range.offset + range.length <= (int)data.size()) {
                        writer->write(reinterpret_cast<const char *>(data.data() + range.offset), range.length);
                    }
                }
                return 0;
            }));

        auto cachedFile = std::make_shared<CachedFile>(nullptr, std::move(loader));
        return cachedFile;
    }
};

// Test that getChar returns EOF on an empty stream
TEST_F(CachedFileStreamTest_158, GetCharReturnsEOFOnEmptyStream_158) {
    std::vector<unsigned char> data;
    auto cf = createCachedFileWithData(data);
    Object dict;
    CachedFileStream stream(cf, 0, true, 0, std::move(dict));
    
    int ch = stream.getChar();
    EXPECT_EQ(ch, EOF);
}

// Test that getChar reads bytes correctly
TEST_F(CachedFileStreamTest_158, GetCharReadsBytes_158) {
    std::vector<unsigned char> data = {0x41, 0x42, 0x43}; // 'A', 'B', 'C'
    auto cf = createCachedFileWithData(data);
    Object dict;
    CachedFileStream stream(cf, 0, true, 3, std::move(dict));
    
    EXPECT_EQ(stream.getChar(), 0x41);
    EXPECT_EQ(stream.getChar(), 0x42);
    EXPECT_EQ(stream.getChar(), 0x43);
    EXPECT_EQ(stream.getChar(), EOF);
}

// Test that lookChar does not advance the position
TEST_F(CachedFileStreamTest_158, LookCharDoesNotAdvance_158) {
    std::vector<unsigned char> data = {0x41, 0x42};
    auto cf = createCachedFileWithData(data);
    Object dict;
    CachedFileStream stream(cf, 0, true, 2, std::move(dict));
    
    int ch1 = stream.lookChar();
    int ch2 = stream.lookChar();
    EXPECT_EQ(ch1, ch2);
    EXPECT_EQ(ch1, 0x41);
}

// Test that getPos returns correct position after reads
TEST_F(CachedFileStreamTest_158, GetPosReturnsCorrectPosition_158) {
    std::vector<unsigned char> data = {0x01, 0x02, 0x03, 0x04};
    auto cf = createCachedFileWithData(data);
    Object dict;
    CachedFileStream stream(cf, 0, true, 4, std::move(dict));
    
    EXPECT_EQ(stream.getPos(), 0);
    stream.getChar();
    EXPECT_EQ(stream.getPos(), 1);
    stream.getChar();
    EXPECT_EQ(stream.getPos(), 2);
}

// Test rewind resets position to start
TEST_F(CachedFileStreamTest_158, RewindResetsPosition_158) {
    std::vector<unsigned char> data = {0x10, 0x20, 0x30};
    auto cf = createCachedFileWithData(data);
    Object dict;
    CachedFileStream stream(cf, 0, true, 3, std::move(dict));
    
    stream.getChar();
    stream.getChar();
    EXPECT_EQ(stream.getPos(), 2);
    
    bool result = stream.rewind();
    EXPECT_TRUE(result);
    EXPECT_EQ(stream.getPos(), 0);
    EXPECT_EQ(stream.getChar(), 0x10);
}

// Test getKind returns correct stream kind
TEST_F(CachedFileStreamTest_158, GetKindReturnsCachedFileStream_158) {
    std::vector<unsigned char> data = {0x01};
    auto cf = createCachedFileWithData(data);
    Object dict;
    CachedFileStream stream(cf, 0, true, 1, std::move(dict));
    
    EXPECT_EQ(stream.getKind(), strCachedFile);
}

// Test getStart returns the start position
TEST_F(CachedFileStreamTest_158, GetStartReturnsStartPosition_158) {
    std::vector<unsigned char> data = {0x01, 0x02, 0x03, 0x04, 0x05};
    auto cf = createCachedFileWithData(data);
    Object dict;
    CachedFileStream stream(cf, 2, true, 3, std::move(dict));
    
    EXPECT_EQ(stream.getStart(), 2);
}

// Test stream with offset start
TEST_F(CachedFileStreamTest_158, StreamWithOffsetStart_158) {
    std::vector<unsigned char> data = {0x01, 0x02, 0x03, 0x04, 0x05};
    auto cf = createCachedFileWithData(data);
    Object dict;
    CachedFileStream stream(cf, 2, true, 3, std::move(dict));
    
    EXPECT_EQ(stream.getChar(), 0x03);
    EXPECT_EQ(stream.getChar(), 0x04);
    EXPECT_EQ(stream.getChar(), 0x05);
    EXPECT_EQ(stream.getChar(), EOF);
}

// Test that getChar returns values in range 0-255 (unsigned byte)
TEST_F(CachedFileStreamTest_158, GetCharReturnsUnsignedByte_158) {
    std::vector<unsigned char> data = {0xFF, 0x80, 0x00};
    auto cf = createCachedFileWithData(data);
    Object dict;
    CachedFileStream stream(cf, 0, true, 3, std::move(dict));
    
    int ch = stream.getChar();
    EXPECT_EQ(ch, 0xFF);
    EXPECT_GE(ch, 0);
    EXPECT_LE(ch, 255);
    
    ch = stream.getChar();
    EXPECT_EQ(ch, 0x80);
    EXPECT_GE(ch, 0);
    EXPECT_LE(ch, 255);
    
    ch = stream.getChar();
    EXPECT_EQ(ch, 0x00);
    EXPECT_GE(ch, 0);
    EXPECT_LE(ch, 255);
}

// Test setPos with absolute position
TEST_F(CachedFileStreamTest_158, SetPosAbsolute_158) {
    std::vector<unsigned char> data = {0x10, 0x20, 0x30, 0x40, 0x50};
    auto cf = createCachedFileWithData(data);
    Object dict;
    CachedFileStream stream(cf, 0, true, 5, std::move(dict));
    
    stream.setPos(3, 0); // absolute position 3
    EXPECT_EQ(stream.getChar(), 0x40);
}

// Test close and subsequent operations
TEST_F(CachedFileStreamTest_158, CloseStream_158) {
    std::vector<unsigned char> data = {0x01, 0x02};
    auto cf = createCachedFileWithData(data);
    Object dict;
    CachedFileStream stream(cf, 0, true, 2, std::move(dict));
    
    stream.getChar();
    stream.close();
    // After close, the stream should be in a closed state
    // Rewind should restore it
    stream.rewind();
    EXPECT_EQ(stream.getChar(), 0x01);
}

// Test copy creates a valid copy
TEST_F(CachedFileStreamTest_158, CopyCreatesValidStream_158) {
    std::vector<unsigned char> data = {0xAA, 0xBB, 0xCC};
    auto cf = createCachedFileWithData(data);
    Object dict;
    CachedFileStream stream(cf, 0, true, 3, std::move(dict));
    
    auto copied = stream.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getKind(), strCachedFile);
}

// Test makeSubStream creates a valid sub-stream
TEST_F(CachedFileStreamTest_158, MakeSubStreamCreatesValidStream_158) {
    std::vector<unsigned char> data = {0x01, 0x02, 0x03, 0x04, 0x05};
    auto cf = createCachedFileWithData(data);
    Object dict;
    CachedFileStream stream(cf, 0, true, 5, std::move(dict));
    
    Object subDict;
    auto subStream = stream.makeSubStream(1, true, 3, std::move(subDict));
    ASSERT_NE(subStream, nullptr);
}

// Test getUnfilteredChar behaves like getChar for base stream
TEST_F(CachedFileStreamTest_158, GetUnfilteredChar_158) {
    std::vector<unsigned char> data = {0x41, 0x42};
    auto cf = createCachedFileWithData(data);
    Object dict;
    CachedFileStream stream(cf, 0, true, 2, std::move(dict));
    
    int ch = stream.getUnfilteredChar();
    EXPECT_EQ(ch, 0x41);
}

// Test unfilteredRewind
TEST_F(CachedFileStreamTest_158, UnfilteredRewind_158) {
    std::vector<unsigned char> data = {0x41, 0x42};
    auto cf = createCachedFileWithData(data);
    Object dict;
    CachedFileStream stream(cf, 0, true, 2, std::move(dict));
    
    stream.getChar();
    stream.getChar();
    bool result = stream.unfilteredRewind();
    EXPECT_TRUE(result);
    EXPECT_EQ(stream.getChar(), 0x41);
}

// Test moveStart adjusts the start position
TEST_F(CachedFileStreamTest_158, MoveStartAdjustsStart_158) {
    std::vector<unsigned char> data = {0x01, 0x02, 0x03, 0x04, 0x05};
    auto cf = createCachedFileWithData(data);
    Object dict;
    CachedFileStream stream(cf, 0, true, 5, std::move(dict));
    
    Goffset originalStart = stream.getStart();
    stream.moveStart(2);
    EXPECT_EQ(stream.getStart(), originalStart + 2);
}

// Test reading past limited length returns EOF
TEST_F(CachedFileStreamTest_158, ReadPastLimitedLengthReturnsEOF_158) {
    std::vector<unsigned char> data = {0x01, 0x02, 0x03, 0x04, 0x05};
    auto cf = createCachedFileWithData(data);
    Object dict;
    // Limited stream of length 2 starting at offset 0
    CachedFileStream stream(cf, 0, true, 2, std::move(dict));
    
    EXPECT_EQ(stream.getChar(), 0x01);
    EXPECT_EQ(stream.getChar(), 0x02);
    EXPECT_EQ(stream.getChar(), EOF);
}

// Test lookChar returns EOF on empty stream
TEST_F(CachedFileStreamTest_158, LookCharReturnsEOFOnEmptyStream_158) {
    std::vector<unsigned char> data;
    auto cf = createCachedFileWithData(data);
    Object dict;
    CachedFileStream stream(cf, 0, true, 0, std::move(dict));
    
    EXPECT_EQ(stream.lookChar(), EOF);
}

// Test multiple rewinds
TEST_F(CachedFileStreamTest_158, MultipleRewinds_158) {
    std::vector<unsigned char> data = {0xDE, 0xAD};
    auto cf = createCachedFileWithData(data);
    Object dict;
    CachedFileStream stream(cf, 0, true, 2, std::move(dict));
    
    for (int i = 0; i < 3; i++) {
        EXPECT_EQ(stream.getChar(), 0xDE);
        EXPECT_EQ(stream.getChar(), 0xAD);
        EXPECT_EQ(stream.getChar(), EOF);
        stream.rewind();
    }
}
