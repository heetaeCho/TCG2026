#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "Stream.h"
#include "CachedFile.h"

// We need a mock or concrete CachedFile implementation to test CachedFileStream.
// CachedFile is a dependency that CachedFileStream uses internally.

// Helper: Create a simple CachedFileLoader for testing
class TestCachedFileLoader : public CachedFileLoader {
public:
    TestCachedFileLoader(const std::string &data) : data_(data) { }

    size_t init(GooString *url, CachedFile *cachedFile) override {
        cachedFile_ = cachedFile;
        return data_.size();
    }

    int load(const std::vector<ByteRange> &ranges, CachedFileWriter *writer) override {
        for (const auto &range : ranges) {
            Goffset offset = range.offset;
            size_t length = range.length;
            if (offset + length > data_.size()) {
                length = data_.size() - offset;
            }
            writer->write(data_.c_str() + offset, length);
        }
        return 0;
    }

private:
    std::string data_;
    CachedFile *cachedFile_ = nullptr;
};

class CachedFileStreamTest_159 : public ::testing::Test {
protected:
    void SetUp() override {
        // Create test data
        testData_ = "Hello, World! This is a test of CachedFileStream.";
    }

    std::shared_ptr<CachedFile> createCachedFile(const std::string &data) {
        auto loader = std::make_unique<TestCachedFileLoader>(data);
        auto cf = std::make_shared<CachedFile>(std::move(loader), nullptr);
        return cf;
    }

    std::unique_ptr<CachedFileStream> createStream(const std::string &data,
                                                     Goffset start = 0,
                                                     bool limited = false,
                                                     Goffset length = 0) {
        auto cf = createCachedFile(data);
        cachedFiles_.push_back(cf); // keep alive
        Object dict;
        return std::make_unique<CachedFileStream>(cf, start, limited, length, std::move(dict));
    }

    std::string testData_;
    std::vector<std::shared_ptr<CachedFile>> cachedFiles_;
};

// Test that getKind returns the correct stream kind for CachedFileStream
TEST_F(CachedFileStreamTest_159, GetKind_159) {
    auto stream = createStream(testData_);
    EXPECT_EQ(stream->getKind(), strCachedFile);
}

// Test that lookChar returns the first character without advancing position
TEST_F(CachedFileStreamTest_159, LookCharReturnsFirstChar_159) {
    auto stream = createStream(testData_);
    stream->rewind();
    int ch = stream->lookChar();
    EXPECT_EQ(ch, 'H');
    // lookChar should not advance, calling again should return same char
    int ch2 = stream->lookChar();
    EXPECT_EQ(ch2, 'H');
}

// Test that getChar returns characters sequentially
TEST_F(CachedFileStreamTest_159, GetCharReturnsSequentialChars_159) {
    auto stream = createStream(testData_);
    stream->rewind();
    for (size_t i = 0; i < testData_.size(); i++) {
        int ch = stream->getChar();
        EXPECT_EQ(ch, (unsigned char)testData_[i]) << "Mismatch at position " << i;
    }
}

// Test that getChar returns EOF after all data is read
TEST_F(CachedFileStreamTest_159, GetCharReturnsEOFAtEnd_159) {
    auto stream = createStream(testData_, 0, true, testData_.size());
    stream->rewind();
    for (size_t i = 0; i < testData_.size(); i++) {
        stream->getChar();
    }
    int ch = stream->getChar();
    EXPECT_EQ(ch, EOF);
}

// Test that lookChar returns EOF when stream is at end
TEST_F(CachedFileStreamTest_159, LookCharReturnsEOFAtEnd_159) {
    auto stream = createStream(testData_, 0, true, testData_.size());
    stream->rewind();
    for (size_t i = 0; i < testData_.size(); i++) {
        stream->getChar();
    }
    int ch = stream->lookChar();
    EXPECT_EQ(ch, EOF);
}

// Test rewind resets position to start
TEST_F(CachedFileStreamTest_159, RewindResetsPosition_159) {
    auto stream = createStream(testData_);
    stream->rewind();
    stream->getChar(); // 'H'
    stream->getChar(); // 'e'
    stream->rewind();
    int ch = stream->getChar();
    EXPECT_EQ(ch, 'H');
}

// Test getPos returns current position
TEST_F(CachedFileStreamTest_159, GetPosReturnsCurrentPosition_159) {
    auto stream = createStream(testData_);
    stream->rewind();
    Goffset pos0 = stream->getPos();
    stream->getChar();
    Goffset pos1 = stream->getPos();
    EXPECT_EQ(pos1, pos0 + 1);
}

// Test getStart returns the start offset
TEST_F(CachedFileStreamTest_159, GetStartReturnsStartOffset_159) {
    Goffset startOffset = 5;
    auto stream = createStream(testData_, startOffset, true, 10);
    EXPECT_EQ(stream->getStart(), startOffset);
}

// Test limited stream only reads specified length
TEST_F(CachedFileStreamTest_159, LimitedStreamRespectsLength_159) {
    Goffset length = 5;
    auto stream = createStream(testData_, 0, true, length);
    stream->rewind();
    std::string result;
    for (Goffset i = 0; i < length; i++) {
        int ch = stream->getChar();
        ASSERT_NE(ch, EOF);
        result += (char)ch;
    }
    EXPECT_EQ(result, testData_.substr(0, length));
    // Next read should be EOF
    int ch = stream->getChar();
    EXPECT_EQ(ch, EOF);
}

// Test stream with start offset reads from correct position
TEST_F(CachedFileStreamTest_159, StartOffsetReadsFromCorrectPosition_159) {
    Goffset start = 7;
    Goffset length = 5;
    auto stream = createStream(testData_, start, true, length);
    stream->rewind();
    std::string result;
    for (Goffset i = 0; i < length; i++) {
        int ch = stream->getChar();
        if (ch == EOF) break;
        result += (char)ch;
    }
    EXPECT_EQ(result, testData_.substr(start, length));
}

// Test setPos with dir=0 (from start)
TEST_F(CachedFileStreamTest_159, SetPosFromStart_159) {
    auto stream = createStream(testData_, 0, true, testData_.size());
    stream->rewind();
    stream->setPos(5, 0);
    int ch = stream->getChar();
    EXPECT_EQ(ch, (unsigned char)testData_[5]);
}

// Test copy creates a working copy
TEST_F(CachedFileStreamTest_159, CopyCreatesWorkingStream_159) {
    auto stream = createStream(testData_, 0, true, testData_.size());
    stream->rewind();
    auto copyStream = stream->copy();
    ASSERT_NE(copyStream, nullptr);
    copyStream->rewind();
    int ch = copyStream->getChar();
    EXPECT_EQ(ch, 'H');
}

// Test makeSubStream creates a substream
TEST_F(CachedFileStreamTest_159, MakeSubStreamWorks_159) {
    auto stream = createStream(testData_, 0, false, 0);
    Object dict;
    auto subStream = stream->makeSubStream(3, true, 5, std::move(dict));
    ASSERT_NE(subStream, nullptr);
    subStream->rewind();
    std::string result;
    for (int i = 0; i < 5; i++) {
        int ch = subStream->getChar();
        if (ch == EOF) break;
        result += (char)ch;
    }
    EXPECT_EQ(result, testData_.substr(3, 5));
}

// Test moveStart shifts the start position
TEST_F(CachedFileStreamTest_159, MoveStartShiftsStart_159) {
    auto stream = createStream(testData_, 0, true, testData_.size());
    Goffset originalStart = stream->getStart();
    stream->moveStart(3);
    EXPECT_EQ(stream->getStart(), originalStart + 3);
}

// Test empty data stream
TEST_F(CachedFileStreamTest_159, EmptyDataReturnsEOF_159) {
    auto stream = createStream("", 0, true, 0);
    stream->rewind();
    int ch = stream->lookChar();
    EXPECT_EQ(ch, EOF);
    ch = stream->getChar();
    EXPECT_EQ(ch, EOF);
}

// Test close and rewind behavior
TEST_F(CachedFileStreamTest_159, CloseAndRewind_159) {
    auto stream = createStream(testData_, 0, true, testData_.size());
    stream->rewind();
    stream->getChar();
    stream->close();
    // After close and rewind, stream should work again
    bool rewound = stream->rewind();
    if (rewound) {
        int ch = stream->lookChar();
        EXPECT_EQ(ch, 'H');
    }
}

// Test getUnfilteredChar behaves like getChar for base stream
TEST_F(CachedFileStreamTest_159, GetUnfilteredChar_159) {
    auto stream = createStream(testData_, 0, true, testData_.size());
    stream->rewind();
    int ch = stream->getUnfilteredChar();
    EXPECT_EQ(ch, 'H');
}

// Test unfilteredRewind
TEST_F(CachedFileStreamTest_159, UnfilteredRewind_159) {
    auto stream = createStream(testData_, 0, true, testData_.size());
    stream->rewind();
    stream->getChar();
    stream->getChar();
    bool result = stream->unfilteredRewind();
    // unfilteredRewind should succeed for a base stream
    if (result) {
        int ch = stream->getChar();
        EXPECT_EQ(ch, 'H');
    }
}

// Test reading data larger than cachedStreamBufSize (1024 bytes)
TEST_F(CachedFileStreamTest_159, LargeDataReadAcrossBufferBoundary_159) {
    // Create data larger than the buffer size
    std::string largeData(2048, 'A');
    for (size_t i = 0; i < largeData.size(); i++) {
        largeData[i] = 'A' + (i % 26);
    }
    auto stream = createStream(largeData, 0, true, largeData.size());
    stream->rewind();
    for (size_t i = 0; i < largeData.size(); i++) {
        int ch = stream->getChar();
        EXPECT_EQ(ch, (unsigned char)largeData[i]) << "Mismatch at position " << i;
    }
    int ch = stream->getChar();
    EXPECT_EQ(ch, EOF);
}

// Test lookChar followed by getChar returns same character
TEST_F(CachedFileStreamTest_159, LookCharThenGetCharSameValue_159) {
    auto stream = createStream(testData_, 0, true, testData_.size());
    stream->rewind();
    int looked = stream->lookChar();
    int got = stream->getChar();
    EXPECT_EQ(looked, got);
    EXPECT_EQ(looked, 'H');
}

// Test binary data (values 0-255)
TEST_F(CachedFileStreamTest_159, BinaryDataHandling_159) {
    std::string binaryData;
    for (int i = 0; i < 256; i++) {
        binaryData += (char)i;
    }
    auto stream = createStream(binaryData, 0, true, binaryData.size());
    stream->rewind();
    for (int i = 0; i < 256; i++) {
        int ch = stream->getChar();
        EXPECT_EQ(ch, i) << "Mismatch at byte value " << i;
    }
}

// Test that lookChar properly handles 0xff byte (should return 255, not -1/EOF)
TEST_F(CachedFileStreamTest_159, LookCharHandles0xFF_159) {
    std::string data;
    data += (char)0xFF;
    auto stream = createStream(data, 0, true, 1);
    stream->rewind();
    int ch = stream->lookChar();
    EXPECT_EQ(ch, 0xFF);
    EXPECT_NE(ch, EOF);
}

// Test setPos with dir=1 (from end)
TEST_F(CachedFileStreamTest_159, SetPosFromEnd_159) {
    auto stream = createStream(testData_, 0, true, testData_.size());
    stream->rewind();
    // Set position from the end
    stream->setPos(0, 1);
    // This should position near/at the end; behavior depends on implementation
    // Just verify no crash and we can read
    int ch = stream->lookChar();
    // ch could be EOF or last char depending on exact semantics
    (void)ch;
}
