#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "Stream.h"
#include "CachedFile.h"
#include "Object.h"

// We need a mock or real CachedFile to construct CachedFileStream.
// CachedFile is a dependency we need to provide.

// Helper class to create a CachedFile with in-memory data
class TestCachedFileLoader : public CachedFileLoader {
public:
    TestCachedFileLoader(const std::vector<char> &data) : data_(data) {}

    size_t init(GooString *url, CachedFile *cachedFile) override {
        cachedFile->cache(0, data_.data(), data_.size());
        return data_.size();
    }

    int load(const std::vector<ByteRange> &ranges, CachedFileWriter *writer) override {
        for (const auto &range : ranges) {
            size_t start = range.offset;
            size_t len = range.length;
            if (start + len > data_.size()) {
                len = data_.size() - start;
            }
            writer->write(data_.data() + start, len);
        }
        return 0;
    }

private:
    std::vector<char> data_;
};

class CachedFileStreamTest_162 : public ::testing::Test {
protected:
    void SetUp() override {}

    std::unique_ptr<CachedFileStream> createStream(const std::vector<char> &data,
                                                     Goffset start = 0,
                                                     bool limited = false,
                                                     Goffset length = 0) {
        auto loader = std::make_unique<TestCachedFileLoader>(data);
        auto cachedFile = std::make_shared<CachedFile>(std::move(loader));
        Object dict;
        if (!limited) {
            length = data.size();
            limited = true;
        }
        return std::make_unique<CachedFileStream>(cachedFile, start, limited, length, std::move(dict));
    }
};

TEST_F(CachedFileStreamTest_162, GetKindReturnsCachedFile_162) {
    std::vector<char> data = {'A', 'B', 'C'};
    auto stream = createStream(data);
    EXPECT_EQ(stream->getKind(), strCachedFile);
}

TEST_F(CachedFileStreamTest_162, GetCharReadsSequentially_162) {
    std::vector<char> data = {'H', 'e', 'l', 'l', 'o'};
    auto stream = createStream(data);
    stream->rewind();

    EXPECT_EQ(stream->getChar(), 'H');
    EXPECT_EQ(stream->getChar(), 'e');
    EXPECT_EQ(stream->getChar(), 'l');
    EXPECT_EQ(stream->getChar(), 'l');
    EXPECT_EQ(stream->getChar(), 'o');
}

TEST_F(CachedFileStreamTest_162, GetCharReturnsEOFAtEnd_162) {
    std::vector<char> data = {'A'};
    auto stream = createStream(data);
    stream->rewind();

    EXPECT_EQ(stream->getChar(), 'A');
    EXPECT_EQ(stream->getChar(), EOF);
}

TEST_F(CachedFileStreamTest_162, LookCharDoesNotAdvance_162) {
    std::vector<char> data = {'X', 'Y'};
    auto stream = createStream(data);
    stream->rewind();

    EXPECT_EQ(stream->lookChar(), 'X');
    EXPECT_EQ(stream->lookChar(), 'X');
    EXPECT_EQ(stream->getChar(), 'X');
    EXPECT_EQ(stream->lookChar(), 'Y');
}

TEST_F(CachedFileStreamTest_162, GetUnfilteredCharSameAsGetChar_162) {
    std::vector<char> data = {'A', 'B', 'C'};
    auto stream = createStream(data);
    stream->rewind();

    EXPECT_EQ(stream->getUnfilteredChar(), 'A');
    EXPECT_EQ(stream->getUnfilteredChar(), 'B');
    EXPECT_EQ(stream->getUnfilteredChar(), 'C');
    EXPECT_EQ(stream->getUnfilteredChar(), EOF);
}

TEST_F(CachedFileStreamTest_162, RewindResetsPosition_162) {
    std::vector<char> data = {'A', 'B', 'C'};
    auto stream = createStream(data);
    stream->rewind();

    EXPECT_EQ(stream->getChar(), 'A');
    EXPECT_EQ(stream->getChar(), 'B');

    stream->rewind();
    EXPECT_EQ(stream->getChar(), 'A');
}

TEST_F(CachedFileStreamTest_162, UnfilteredRewindResetsPosition_162) {
    std::vector<char> data = {'A', 'B', 'C'};
    auto stream = createStream(data);
    stream->rewind();

    stream->getChar();
    stream->getChar();

    bool result = stream->unfilteredRewind();
    EXPECT_TRUE(result);
    EXPECT_EQ(stream->getChar(), 'A');
}

TEST_F(CachedFileStreamTest_162, GetPosReturnsCurrentPosition_162) {
    std::vector<char> data = {'A', 'B', 'C', 'D'};
    auto stream = createStream(data);
    stream->rewind();

    EXPECT_EQ(stream->getPos(), 0);
    stream->getChar();
    EXPECT_EQ(stream->getPos(), 1);
    stream->getChar();
    EXPECT_EQ(stream->getPos(), 2);
}

TEST_F(CachedFileStreamTest_162, GetStartReturnsStartPosition_162) {
    std::vector<char> data = {'A', 'B', 'C', 'D', 'E'};
    auto stream = createStream(data, 2, true, 3);
    EXPECT_EQ(stream->getStart(), 2);
}

TEST_F(CachedFileStreamTest_162, SetPosFromBeginning_162) {
    std::vector<char> data = {'A', 'B', 'C', 'D', 'E'};
    auto stream = createStream(data);
    stream->rewind();

    stream->setPos(3, 0);
    EXPECT_EQ(stream->getChar(), 'D');
}

TEST_F(CachedFileStreamTest_162, SetPosFromEnd_162) {
    std::vector<char> data = {'A', 'B', 'C', 'D', 'E'};
    auto stream = createStream(data);
    stream->rewind();

    // dir < 0 means from end
    stream->setPos(0, -1);
    // After setting pos from end with offset 0, should be at end
    // The exact behavior depends on implementation
    // We just verify it doesn't crash
    stream->getChar(); // may be EOF or last char depending on implementation
}

TEST_F(CachedFileStreamTest_162, EmptyStream_162) {
    std::vector<char> data;
    auto stream = createStream(data);
    stream->rewind();

    EXPECT_EQ(stream->getChar(), EOF);
    EXPECT_EQ(stream->lookChar(), EOF);
}

TEST_F(CachedFileStreamTest_162, LimitedSubstream_162) {
    std::vector<char> data = {'A', 'B', 'C', 'D', 'E'};
    auto stream = createStream(data, 1, true, 3);
    stream->rewind();

    EXPECT_EQ(stream->getChar(), 'B');
    EXPECT_EQ(stream->getChar(), 'C');
    EXPECT_EQ(stream->getChar(), 'D');
    EXPECT_EQ(stream->getChar(), EOF);
}

TEST_F(CachedFileStreamTest_162, MoveStartAdjustsStart_162) {
    std::vector<char> data = {'A', 'B', 'C', 'D', 'E'};
    auto stream = createStream(data, 0, true, 5);

    stream->moveStart(2);
    EXPECT_EQ(stream->getStart(), 2);

    stream->rewind();
    EXPECT_EQ(stream->getChar(), 'C');
}

TEST_F(CachedFileStreamTest_162, CopyCreatesIndependentStream_162) {
    std::vector<char> data = {'A', 'B', 'C'};
    auto stream = createStream(data);
    stream->rewind();
    stream->getChar(); // advance to 'B'

    auto copied = stream->copy();
    ASSERT_NE(copied, nullptr);

    copied->rewind();
    EXPECT_EQ(copied->getChar(), 'A');
    // Original should still be at position after 'A'
    EXPECT_EQ(stream->getChar(), 'B');
}

TEST_F(CachedFileStreamTest_162, MakeSubStreamCreatesSubstream_162) {
    std::vector<char> data = {'A', 'B', 'C', 'D', 'E'};
    auto stream = createStream(data);

    Object dict;
    auto sub = stream->makeSubStream(2, true, 2, std::move(dict));
    ASSERT_NE(sub, nullptr);

    sub->rewind();
    EXPECT_EQ(sub->getChar(), 'C');
    EXPECT_EQ(sub->getChar(), 'D');
    EXPECT_EQ(sub->getChar(), EOF);
}

TEST_F(CachedFileStreamTest_162, CloseDoesNotCrash_162) {
    std::vector<char> data = {'A', 'B'};
    auto stream = createStream(data);
    stream->rewind();
    stream->getChar();
    stream->close();
    // After close, operations should still not crash
    // (behavior after close may vary)
}

TEST_F(CachedFileStreamTest_162, LargeData_162) {
    // Test with data larger than cachedStreamBufSize (1024)
    std::vector<char> data(2048);
    for (int i = 0; i < 2048; i++) {
        data[i] = static_cast<char>(i % 256);
    }
    auto stream = createStream(data);
    stream->rewind();

    for (int i = 0; i < 2048; i++) {
        int c = stream->getChar();
        ASSERT_EQ(c, static_cast<unsigned char>(data[i])) << "Mismatch at position " << i;
    }
    EXPECT_EQ(stream->getChar(), EOF);
}

TEST_F(CachedFileStreamTest_162, SetPosToZero_162) {
    std::vector<char> data = {'A', 'B', 'C'};
    auto stream = createStream(data);
    stream->rewind();

    stream->getChar();
    stream->getChar();
    stream->setPos(0, 0);
    EXPECT_EQ(stream->getChar(), 'A');
}

TEST_F(CachedFileStreamTest_162, SingleByteStream_162) {
    std::vector<char> data = {'Z'};
    auto stream = createStream(data);
    stream->rewind();

    EXPECT_EQ(stream->lookChar(), 'Z');
    EXPECT_EQ(stream->getChar(), 'Z');
    EXPECT_EQ(stream->lookChar(), EOF);
    EXPECT_EQ(stream->getChar(), EOF);
}

TEST_F(CachedFileStreamTest_162, RewindReturnsTrueOnSuccess_162) {
    std::vector<char> data = {'A', 'B'};
    auto stream = createStream(data);
    EXPECT_TRUE(stream->rewind());
}

TEST_F(CachedFileStreamTest_162, GetPosAfterRewind_162) {
    std::vector<char> data = {'A', 'B', 'C'};
    auto stream = createStream(data);
    stream->rewind();
    stream->getChar();
    stream->getChar();
    stream->rewind();
    EXPECT_EQ(stream->getPos(), 0);
}
