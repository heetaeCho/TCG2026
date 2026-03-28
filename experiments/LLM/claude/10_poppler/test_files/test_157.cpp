#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "Stream.h"
#include "CachedFile.h"

// A minimal CachedFileLoader for testing purposes
class TestCachedFileLoader : public CachedFileLoader {
public:
    ~TestCachedFileLoader() override = default;

    size_t init(GooString *url, CachedFile *cachedFile) override
    {
        // Return a known size for the test data
        return testData.size();
    }

    int load(const std::vector<ByteRange> &ranges, CachedFileWriter *writer) override
    {
        for (const auto &range : ranges) {
            size_t start = range.offset;
            size_t len = range.length;
            if (start + len > testData.size()) {
                len = testData.size() - start;
            }
            if (len > 0) {
                writer->write(testData.data() + start, len);
            }
        }
        return 0;
    }

    void setData(const std::vector<char> &data) { testData = data; }

    std::vector<char> testData;
};

class CachedFileStreamTest_157 : public ::testing::Test {
protected:
    void SetUp() override
    {
        // Create test data
        testData.resize(4096);
        for (size_t i = 0; i < testData.size(); i++) {
            testData[i] = static_cast<char>(i & 0xFF);
        }

        loader = new TestCachedFileLoader();
        loader->setData(testData);

        cachedFile = std::make_shared<CachedFile>(std::unique_ptr<CachedFileLoader>(loader));
    }

    std::vector<char> testData;
    TestCachedFileLoader *loader; // owned by cachedFile
    std::shared_ptr<CachedFile> cachedFile;

    std::unique_ptr<CachedFileStream> createStream(Goffset start = 0, bool limited = false, Goffset length = 0)
    {
        Object dict;
        return std::make_unique<CachedFileStream>(cachedFile, start, limited, length, std::move(dict));
    }
};

TEST_F(CachedFileStreamTest_157, GetKindReturnsCachedFile_157)
{
    auto stream = createStream();
    EXPECT_EQ(stream->getKind(), strCachedFile);
    stream->close();
}

TEST_F(CachedFileStreamTest_157, GetStartReturnsInitialStart_157)
{
    auto stream = createStream(100, false, 0);
    EXPECT_EQ(stream->getStart(), 100);
    stream->close();
}

TEST_F(CachedFileStreamTest_157, GetStartReturnsZeroWhenCreatedAtZero_157)
{
    auto stream = createStream(0, false, 0);
    EXPECT_EQ(stream->getStart(), 0);
    stream->close();
}

TEST_F(CachedFileStreamTest_157, RewindResetsPosition_157)
{
    auto stream = createStream(0, true, 100);
    // Read some characters
    stream->getChar();
    stream->getChar();
    stream->getChar();

    bool result = stream->rewind();
    EXPECT_TRUE(result);
    EXPECT_EQ(stream->getPos(), 0);
    stream->close();
}

TEST_F(CachedFileStreamTest_157, GetCharReadsSequentialBytes_157)
{
    auto stream = createStream(0, true, 10);
    for (int i = 0; i < 10; i++) {
        int c = stream->getChar();
        EXPECT_EQ(c, (i & 0xFF));
    }
    stream->close();
}

TEST_F(CachedFileStreamTest_157, LookCharDoesNotAdvancePosition_157)
{
    auto stream = createStream(0, true, 10);
    int c1 = stream->lookChar();
    Goffset pos1 = stream->getPos();
    int c2 = stream->lookChar();
    Goffset pos2 = stream->getPos();

    EXPECT_EQ(c1, c2);
    EXPECT_EQ(pos1, pos2);
    stream->close();
}

TEST_F(CachedFileStreamTest_157, GetCharAdvancesPosition_157)
{
    auto stream = createStream(0, true, 100);
    Goffset posBefore = stream->getPos();
    stream->getChar();
    Goffset posAfter = stream->getPos();
    EXPECT_EQ(posAfter, posBefore + 1);
    stream->close();
}

TEST_F(CachedFileStreamTest_157, GetPosReturnsCorrectPosition_157)
{
    auto stream = createStream(0, true, 100);
    EXPECT_EQ(stream->getPos(), 0);
    stream->getChar();
    EXPECT_EQ(stream->getPos(), 1);
    stream->getChar();
    EXPECT_EQ(stream->getPos(), 2);
    stream->close();
}

TEST_F(CachedFileStreamTest_157, LimitedStreamReturnsEOFAtEnd_157)
{
    auto stream = createStream(0, true, 5);
    for (int i = 0; i < 5; i++) {
        int c = stream->getChar();
        EXPECT_NE(c, EOF);
    }
    int c = stream->getChar();
    EXPECT_EQ(c, EOF);
    stream->close();
}

TEST_F(CachedFileStreamTest_157, SetPosFromStart_157)
{
    auto stream = createStream(0, true, 100);
    stream->setPos(50, 0);
    EXPECT_EQ(stream->getPos(), 50);
    stream->close();
}

TEST_F(CachedFileStreamTest_157, SetPosFromEnd_157)
{
    auto stream = createStream(0, false, 0);
    // dir = -1 means from end
    stream->setPos(10, -1);
    Goffset pos = stream->getPos();
    // Position should be near the end of the data
    EXPECT_GE(pos, 0);
    stream->close();
}

TEST_F(CachedFileStreamTest_157, MoveStartAdvancesStart_157)
{
    auto stream = createStream(10, true, 100);
    EXPECT_EQ(stream->getStart(), 10);
    stream->moveStart(5);
    EXPECT_EQ(stream->getStart(), 15);
    stream->close();
}

TEST_F(CachedFileStreamTest_157, CopyCreatesValidStream_157)
{
    auto stream = createStream(0, true, 100);
    auto copied = stream->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getKind(), strCachedFile);
    EXPECT_EQ(copied->getStart(), stream->getStart());
    stream->close();
    copied->close();
}

TEST_F(CachedFileStreamTest_157, MakeSubStreamCreatesValidStream_157)
{
    auto stream = createStream(0, false, 0);
    Object dict;
    auto sub = stream->makeSubStream(10, true, 50, std::move(dict));
    ASSERT_NE(sub, nullptr);
    EXPECT_EQ(sub->getKind(), strCachedFile);
    stream->close();
    sub->close();
}

TEST_F(CachedFileStreamTest_157, GetCharWithOffset_157)
{
    auto stream = createStream(5, true, 10);
    int c = stream->getChar();
    EXPECT_EQ(c, (5 & 0xFF));
    stream->close();
}

TEST_F(CachedFileStreamTest_157, GetUnfilteredCharMatchesGetChar_157)
{
    auto stream = createStream(0, true, 10);
    auto stream2 = createStream(0, true, 10);

    int c1 = stream->getChar();
    int c2 = stream2->getUnfilteredChar();
    EXPECT_EQ(c1, c2);

    stream->close();
    stream2->close();
}

TEST_F(CachedFileStreamTest_157, UnfilteredRewindWorks_157)
{
    auto stream = createStream(0, true, 100);
    stream->getChar();
    stream->getChar();
    bool result = stream->unfilteredRewind();
    EXPECT_TRUE(result);
    stream->close();
}

TEST_F(CachedFileStreamTest_157, CloseDoesNotCrash_157)
{
    auto stream = createStream(0, true, 100);
    stream->getChar();
    stream->close();
    // No crash expected
}

TEST_F(CachedFileStreamTest_157, ZeroLengthLimitedStream_157)
{
    auto stream = createStream(0, true, 0);
    int c = stream->getChar();
    EXPECT_EQ(c, EOF);
    stream->close();
}

TEST_F(CachedFileStreamTest_157, ReadAcrossBufferBoundary_157)
{
    // cachedStreamBufSize is 1024, read more than that
    auto stream = createStream(0, true, 2048);
    for (int i = 0; i < 2048; i++) {
        int c = stream->getChar();
        EXPECT_EQ(c, (i & 0xFF)) << "Mismatch at byte " << i;
    }
    int c = stream->getChar();
    EXPECT_EQ(c, EOF);
    stream->close();
}

TEST_F(CachedFileStreamTest_157, RewindAfterEOF_157)
{
    auto stream = createStream(0, true, 5);
    for (int i = 0; i < 10; i++) {
        stream->getChar(); // Read past end
    }
    bool result = stream->rewind();
    EXPECT_TRUE(result);
    // After rewind, should be able to read again
    int c = stream->getChar();
    EXPECT_EQ(c, 0);
    stream->close();
}

TEST_F(CachedFileStreamTest_157, SetPosToZero_157)
{
    auto stream = createStream(0, true, 100);
    stream->getChar();
    stream->getChar();
    stream->setPos(0, 0);
    EXPECT_EQ(stream->getPos(), 0);
    int c = stream->getChar();
    EXPECT_EQ(c, 0);
    stream->close();
}

TEST_F(CachedFileStreamTest_157, LookCharAfterEOF_157)
{
    auto stream = createStream(0, true, 1);
    stream->getChar(); // Read the only byte
    int c = stream->lookChar();
    EXPECT_EQ(c, EOF);
    stream->close();
}

TEST_F(CachedFileStreamTest_157, MakeSubStreamStartAndLength_157)
{
    auto stream = createStream(0, false, 0);
    Object dict;
    auto sub = stream->makeSubStream(10, true, 5, std::move(dict));

    // The substream should read from offset 10, limited to 5 bytes
    int c = sub->getChar();
    EXPECT_EQ(c, (10 & 0xFF));

    stream->close();
    sub->close();
}
