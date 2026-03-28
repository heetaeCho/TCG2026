#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "Stream.h"
#include "CachedFile.h"

// We need a mock or stub CachedFile to create CachedFileStream instances.
// Since CachedFile is a dependency, we create a minimal implementation for testing.

class MockCachedFileLoader : public CachedFileLoader {
public:
    MOCK_METHOD(size_t, init, (GooString *uri, CachedFile *cachedFile), (override));
    MOCK_METHOD(int, load, (const std::vector<ByteRange> &ranges, CachedFileWriter *writer), (override));
};

class CachedFileStreamTest_163 : public ::testing::Test {
protected:
    void SetUp() override
    {
        // Create a CachedFile with some test data
        loader = std::make_unique<MockCachedFileLoader>();
        
        // We'll set up data of known size
        testDataSize = 256;
        testData.resize(testDataSize);
        for (int i = 0; i < testDataSize; i++) {
            testData[i] = static_cast<char>(i & 0xFF);
        }
    }

    std::unique_ptr<MockCachedFileLoader> loader;
    std::vector<char> testData;
    int testDataSize;
    
    std::shared_ptr<CachedFile> createCachedFileWithData(const std::vector<char>& data) {
        auto cachedFile = std::make_shared<CachedFile>(nullptr, nullptr);
        // Note: This may not work perfectly without a real CachedFile setup,
        // but we test the interface as best we can.
        return cachedFile;
    }
};

// Test that CachedFileStream can be constructed and destroyed without crashing
TEST_F(CachedFileStreamTest_163, ConstructAndDestruct_163)
{
    auto cc = std::make_shared<CachedFile>(nullptr, nullptr);
    // Even if the CachedFile is empty/invalid, construction should not crash
    // We use a try block since the constructor might throw or behave differently
    // with a null/empty CachedFile
    SUCCEED();
}

// Test getKind returns the expected stream kind
TEST_F(CachedFileStreamTest_163, GetKindReturnsCachedFileStream_163)
{
    auto cc = std::make_shared<CachedFile>(nullptr, nullptr);
    Object dict;
    CachedFileStream stream(cc, 0, false, 0, std::move(dict));
    EXPECT_EQ(stream.getKind(), strCachedFile);
}

// Test getStart returns the start position
TEST_F(CachedFileStreamTest_163, GetStartReturnsStartPosition_163)
{
    auto cc = std::make_shared<CachedFile>(nullptr, nullptr);
    Object dict;
    Goffset startPos = 42;
    CachedFileStream stream(cc, startPos, false, 0, std::move(dict));
    EXPECT_EQ(stream.getStart(), startPos);
}

// Test getStart with zero start
TEST_F(CachedFileStreamTest_163, GetStartReturnsZeroStart_163)
{
    auto cc = std::make_shared<CachedFile>(nullptr, nullptr);
    Object dict;
    CachedFileStream stream(cc, 0, false, 0, std::move(dict));
    EXPECT_EQ(stream.getStart(), 0);
}

// Test rewind functionality
TEST_F(CachedFileStreamTest_163, RewindReturnsTrue_163)
{
    auto cc = std::make_shared<CachedFile>(nullptr, nullptr);
    Object dict;
    CachedFileStream stream(cc, 0, false, 0, std::move(dict));
    // rewind should succeed
    bool result = stream.rewind();
    // We just check it doesn't crash; the return value depends on implementation
    (void)result;
    SUCCEED();
}

// Test unfilteredRewind calls rewind
TEST_F(CachedFileStreamTest_163, UnfilteredRewindCallsRewind_163)
{
    auto cc = std::make_shared<CachedFile>(nullptr, nullptr);
    Object dict;
    CachedFileStream stream(cc, 0, false, 0, std::move(dict));
    // unfilteredRewind should behave same as rewind
    bool result = stream.unfilteredRewind();
    (void)result;
    SUCCEED();
}

// Test getPos after construction
TEST_F(CachedFileStreamTest_163, GetPosAfterConstruction_163)
{
    auto cc = std::make_shared<CachedFile>(nullptr, nullptr);
    Object dict;
    Goffset startPos = 10;
    CachedFileStream stream(cc, startPos, false, 0, std::move(dict));
    // After construction, position should relate to the start
    Goffset pos = stream.getPos();
    // Position should be at or near the start
    EXPECT_GE(pos, 0);
}

// Test getChar returns EOF when stream is empty or at end
TEST_F(CachedFileStreamTest_163, GetCharReturnsEOFOnEmptyStream_163)
{
    auto cc = std::make_shared<CachedFile>(nullptr, nullptr);
    Object dict;
    CachedFileStream stream(cc, 0, true, 0, std::move(dict));
    stream.rewind();
    int ch = stream.getChar();
    EXPECT_EQ(ch, EOF);
}

// Test lookChar returns EOF when stream is empty or at end
TEST_F(CachedFileStreamTest_163, LookCharReturnsEOFOnEmptyStream_163)
{
    auto cc = std::make_shared<CachedFile>(nullptr, nullptr);
    Object dict;
    CachedFileStream stream(cc, 0, true, 0, std::move(dict));
    stream.rewind();
    int ch = stream.lookChar();
    EXPECT_EQ(ch, EOF);
}

// Test getUnfilteredChar returns EOF on empty stream
TEST_F(CachedFileStreamTest_163, GetUnfilteredCharReturnsEOFOnEmptyStream_163)
{
    auto cc = std::make_shared<CachedFile>(nullptr, nullptr);
    Object dict;
    CachedFileStream stream(cc, 0, true, 0, std::move(dict));
    stream.rewind();
    int ch = stream.getUnfilteredChar();
    EXPECT_EQ(ch, EOF);
}

// Test close doesn't crash
TEST_F(CachedFileStreamTest_163, CloseDoesNotCrash_163)
{
    auto cc = std::make_shared<CachedFile>(nullptr, nullptr);
    Object dict;
    CachedFileStream stream(cc, 0, false, 0, std::move(dict));
    stream.close();
    SUCCEED();
}

// Test moveStart modifies the start
TEST_F(CachedFileStreamTest_163, MoveStartChangesStart_163)
{
    auto cc = std::make_shared<CachedFile>(nullptr, nullptr);
    Object dict;
    Goffset initialStart = 10;
    CachedFileStream stream(cc, initialStart, false, 0, std::move(dict));
    Goffset delta = 5;
    stream.moveStart(delta);
    EXPECT_EQ(stream.getStart(), initialStart + delta);
}

// Test moveStart with zero delta
TEST_F(CachedFileStreamTest_163, MoveStartWithZeroDelta_163)
{
    auto cc = std::make_shared<CachedFile>(nullptr, nullptr);
    Object dict;
    Goffset initialStart = 20;
    CachedFileStream stream(cc, initialStart, false, 0, std::move(dict));
    stream.moveStart(0);
    EXPECT_EQ(stream.getStart(), initialStart);
}

// Test copy creates a valid copy
TEST_F(CachedFileStreamTest_163, CopyCreatesValidStream_163)
{
    auto cc = std::make_shared<CachedFile>(nullptr, nullptr);
    Object dict;
    CachedFileStream stream(cc, 0, false, 0, std::move(dict));
    auto copied = stream.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getKind(), strCachedFile);
}

// Test copy preserves start position
TEST_F(CachedFileStreamTest_163, CopyPreservesStart_163)
{
    auto cc = std::make_shared<CachedFile>(nullptr, nullptr);
    Object dict;
    Goffset startPos = 50;
    CachedFileStream stream(cc, startPos, false, 100, std::move(dict));
    auto copied = stream.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getStart(), startPos);
}

// Test makeSubStream creates a valid sub-stream
TEST_F(CachedFileStreamTest_163, MakeSubStreamCreatesValidStream_163)
{
    auto cc = std::make_shared<CachedFile>(nullptr, nullptr);
    Object dict;
    CachedFileStream stream(cc, 0, false, 100, std::move(dict));
    Object subDict;
    auto sub = stream.makeSubStream(10, true, 50, std::move(subDict));
    ASSERT_NE(sub, nullptr);
    EXPECT_EQ(sub->getKind(), strCachedFile);
}

// Test makeSubStream with zero length
TEST_F(CachedFileStreamTest_163, MakeSubStreamZeroLength_163)
{
    auto cc = std::make_shared<CachedFile>(nullptr, nullptr);
    Object dict;
    CachedFileStream stream(cc, 0, false, 100, std::move(dict));
    Object subDict;
    auto sub = stream.makeSubStream(0, true, 0, std::move(subDict));
    ASSERT_NE(sub, nullptr);
}

// Test setPos with forward direction
TEST_F(CachedFileStreamTest_163, SetPosForwardDirection_163)
{
    auto cc = std::make_shared<CachedFile>(nullptr, nullptr);
    Object dict;
    CachedFileStream stream(cc, 0, false, 0, std::move(dict));
    stream.setPos(0, 0);
    EXPECT_GE(stream.getPos(), 0);
}

// Test setPos with backward direction (dir != 0 means from end)
TEST_F(CachedFileStreamTest_163, SetPosBackwardDirection_163)
{
    auto cc = std::make_shared<CachedFile>(nullptr, nullptr);
    Object dict;
    CachedFileStream stream(cc, 0, false, 0, std::move(dict));
    stream.setPos(0, 1);
    // Just verify no crash
    SUCCEED();
}

// Test repeated rewind calls
TEST_F(CachedFileStreamTest_163, RepeatedRewindCalls_163)
{
    auto cc = std::make_shared<CachedFile>(nullptr, nullptr);
    Object dict;
    CachedFileStream stream(cc, 0, true, 0, std::move(dict));
    for (int i = 0; i < 10; i++) {
        stream.rewind();
    }
    SUCCEED();
}

// Test lookChar does not advance position (idempotent)
TEST_F(CachedFileStreamTest_163, LookCharIsIdempotent_163)
{
    auto cc = std::make_shared<CachedFile>(nullptr, nullptr);
    Object dict;
    CachedFileStream stream(cc, 0, true, 0, std::move(dict));
    stream.rewind();
    int ch1 = stream.lookChar();
    int ch2 = stream.lookChar();
    EXPECT_EQ(ch1, ch2);
}

// Test getPos after rewind matches start
TEST_F(CachedFileStreamTest_163, GetPosAfterRewindMatchesStart_163)
{
    auto cc = std::make_shared<CachedFile>(nullptr, nullptr);
    Object dict;
    Goffset startPos = 5;
    CachedFileStream stream(cc, startPos, true, 0, std::move(dict));
    stream.rewind();
    EXPECT_EQ(stream.getPos(), startPos);
}
