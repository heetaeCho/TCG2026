#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "Stream.h"
#include "CachedFile.h"
#include "Object.h"

// We need a CachedFileLoader implementation for creating CachedFile instances
class TestCachedFileLoader : public CachedFileLoader {
public:
    TestCachedFileLoader(const std::vector<char> &data) : data_(data) {}

    size_t init(GooString *url, CachedFile *cachedFile) override
    {
        cachedFile->cache(0, data_.data(), data_.size());
        return data_.size();
    }

    int load(const std::vector<ByteRange> &ranges, CachedFileWriter *writer) override
    {
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

class CachedFileStreamTest_161 : public ::testing::Test {
protected:
    void SetUp() override {}

    std::shared_ptr<CachedFile> createCachedFile(const std::vector<char> &data)
    {
        auto loader = std::make_unique<TestCachedFileLoader>(data);
        auto cf = std::make_shared<CachedFile>(new GooString("test"), std::move(loader));
        return cf;
    }

    std::unique_ptr<CachedFileStream> createStream(const std::vector<char> &data, Goffset start = 0, bool limited = false, Goffset length = 0)
    {
        auto cf = createCachedFile(data);
        cachedFiles_.push_back(cf);
        return std::make_unique<CachedFileStream>(cf, start, limited, length, Object(objNull));
    }

    std::vector<std::shared_ptr<CachedFile>> cachedFiles_;
};

TEST_F(CachedFileStreamTest_161, GetStartReturnsInitialStart_161)
{
    std::vector<char> data(100, 'A');
    auto stream = createStream(data, 0, false, 0);
    EXPECT_EQ(stream->getStart(), 0);
}

TEST_F(CachedFileStreamTest_161, GetStartReturnsNonZeroStart_161)
{
    std::vector<char> data(100, 'A');
    auto stream = createStream(data, 50, false, 0);
    EXPECT_EQ(stream->getStart(), 50);
}

TEST_F(CachedFileStreamTest_161, GetKindReturnsCachedFile_161)
{
    std::vector<char> data(100, 'A');
    auto stream = createStream(data, 0, false, 0);
    EXPECT_EQ(stream->getKind(), strCachedFile);
}

TEST_F(CachedFileStreamTest_161, RewindResetsPosition_161)
{
    std::vector<char> data(100, 'B');
    auto stream = createStream(data, 0, true, 100);
    stream->reset();
    // Read a character to advance position
    stream->getChar();
    // Rewind should go back to start
    bool result = stream->rewind();
    EXPECT_TRUE(result);
    EXPECT_EQ(stream->getPos(), 0);
}

TEST_F(CachedFileStreamTest_161, GetCharReadsBytes_161)
{
    std::vector<char> data = {'H', 'e', 'l', 'l', 'o'};
    auto stream = createStream(data, 0, true, 5);
    stream->reset();
    EXPECT_EQ(stream->getChar(), 'H');
    EXPECT_EQ(stream->getChar(), 'e');
    EXPECT_EQ(stream->getChar(), 'l');
    EXPECT_EQ(stream->getChar(), 'l');
    EXPECT_EQ(stream->getChar(), 'o');
}

TEST_F(CachedFileStreamTest_161, LookCharDoesNotAdvance_161)
{
    std::vector<char> data = {'X', 'Y', 'Z'};
    auto stream = createStream(data, 0, true, 3);
    stream->reset();
    int ch1 = stream->lookChar();
    int ch2 = stream->lookChar();
    EXPECT_EQ(ch1, ch2);
    EXPECT_EQ(ch1, 'X');
}

TEST_F(CachedFileStreamTest_161, GetPosAdvancesAfterRead_161)
{
    std::vector<char> data(10, 'A');
    auto stream = createStream(data, 0, true, 10);
    stream->reset();
    EXPECT_EQ(stream->getPos(), 0);
    stream->getChar();
    EXPECT_EQ(stream->getPos(), 1);
    stream->getChar();
    EXPECT_EQ(stream->getPos(), 2);
}

TEST_F(CachedFileStreamTest_161, GetCharReturnsEOFAtEnd_161)
{
    std::vector<char> data = {'A'};
    auto stream = createStream(data, 0, true, 1);
    stream->reset();
    EXPECT_EQ(stream->getChar(), 'A');
    EXPECT_EQ(stream->getChar(), EOF);
}

TEST_F(CachedFileStreamTest_161, MoveStartChangesStart_161)
{
    std::vector<char> data(100, 'A');
    auto stream = createStream(data, 10, false, 0);
    EXPECT_EQ(stream->getStart(), 10);
    stream->moveStart(5);
    EXPECT_EQ(stream->getStart(), 15);
}

TEST_F(CachedFileStreamTest_161, SetPosFromBeginning_161)
{
    std::vector<char> data(100, 'C');
    data[50] = 'Z';
    auto stream = createStream(data, 0, true, 100);
    stream->reset();
    stream->setPos(50, 0);
    EXPECT_EQ(stream->getChar(), 'Z');
}

TEST_F(CachedFileStreamTest_161, CopyCreatesNewStream_161)
{
    std::vector<char> data = {'A', 'B', 'C', 'D', 'E'};
    auto stream = createStream(data, 0, true, 5);
    auto copied = stream->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getStart(), stream->getStart());
}

TEST_F(CachedFileStreamTest_161, MakeSubStreamCreatesSubStream_161)
{
    std::vector<char> data(100, 'M');
    data[20] = 'N';
    auto stream = createStream(data, 0, false, 0);
    auto sub = stream->makeSubStream(20, true, 10, Object(objNull));
    ASSERT_NE(sub, nullptr);
    sub->reset();
    EXPECT_EQ(sub->getChar(), 'N');
}

TEST_F(CachedFileStreamTest_161, EmptyStreamReturnsEOF_161)
{
    std::vector<char> data;
    // With 0 length limited stream
    auto cf = createCachedFile(data);
    cachedFiles_.push_back(cf);
    // Note: CachedFile might not support empty, but limited=true with length=0
    auto stream = std::make_unique<CachedFileStream>(cf, 0, true, 0, Object(objNull));
    stream->reset();
    EXPECT_EQ(stream->getChar(), EOF);
}

TEST_F(CachedFileStreamTest_161, LimitedStreamRespectsLength_161)
{
    std::vector<char> data = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
    auto stream = createStream(data, 2, true, 3);
    stream->reset();
    EXPECT_EQ(stream->getChar(), 'C');
    EXPECT_EQ(stream->getChar(), 'D');
    EXPECT_EQ(stream->getChar(), 'E');
    EXPECT_EQ(stream->getChar(), EOF);
}

TEST_F(CachedFileStreamTest_161, UnfilteredRewind_161)
{
    std::vector<char> data(50, 'Q');
    auto stream = createStream(data, 0, true, 50);
    stream->reset();
    stream->getChar();
    bool result = stream->unfilteredRewind();
    EXPECT_TRUE(result);
}

TEST_F(CachedFileStreamTest_161, GetUnfilteredChar_161)
{
    std::vector<char> data = {'R', 'S', 'T'};
    auto stream = createStream(data, 0, true, 3);
    stream->reset();
    int ch = stream->getUnfilteredChar();
    EXPECT_EQ(ch, 'R');
}

TEST_F(CachedFileStreamTest_161, CloseDoesNotCrash_161)
{
    std::vector<char> data(10, 'Z');
    auto stream = createStream(data, 0, true, 10);
    stream->reset();
    stream->close();
    // Verify no crash; calling close should be safe
}

TEST_F(CachedFileStreamTest_161, LargeDataStream_161)
{
    // Test with data larger than cachedStreamBufSize (1024)
    std::vector<char> data(2048, 'L');
    data[1500] = 'W';
    auto stream = createStream(data, 0, true, 2048);
    stream->reset();
    stream->setPos(1500, 0);
    EXPECT_EQ(stream->getChar(), 'W');
}

TEST_F(CachedFileStreamTest_161, SetPosFromEnd_161)
{
    std::vector<char> data(100, 'P');
    data[99] = 'E';
    auto stream = createStream(data, 0, true, 100);
    stream->reset();
    // dir != 0 means from end
    stream->setPos(1, -1);
    // Should position near the end
    int ch = stream->getChar();
    EXPECT_EQ(ch, 'E');
}

TEST_F(CachedFileStreamTest_161, MultipleResetCalls_161)
{
    std::vector<char> data = {'1', '2', '3'};
    auto stream = createStream(data, 0, true, 3);
    stream->reset();
    EXPECT_EQ(stream->getChar(), '1');
    stream->reset();
    EXPECT_EQ(stream->getChar(), '1');
    stream->reset();
    EXPECT_EQ(stream->getChar(), '1');
}

TEST_F(CachedFileStreamTest_161, MoveStartByZero_161)
{
    std::vector<char> data(50, 'A');
    auto stream = createStream(data, 25, false, 0);
    stream->moveStart(0);
    EXPECT_EQ(stream->getStart(), 25);
}
