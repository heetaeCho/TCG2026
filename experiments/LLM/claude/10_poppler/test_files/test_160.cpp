#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "Stream.h"
#include "CachedFile.h"
#include "Object.h"

// Mock CachedFile for testing
class MockCachedFileLoader : public CachedFileLoader {
public:
    MOCK_METHOD(size_t, init, (CachedFile *cachedFile), (override));
    MOCK_METHOD(int, load, (const std::vector<ByteRange> &ranges, CachedFileWriter *writer), (override));
};

class CachedFileStreamTest_160 : public ::testing::Test {
protected:
    void SetUp() override {
        loader = std::make_unique<MockCachedFileLoader>();
        // Set up a mock loader that reports a reasonable file size
        ON_CALL(*loader, init(::testing::_)).WillByDefault(::testing::Return(4096));
        ON_CALL(*loader, load(::testing::_, ::testing::_)).WillByDefault(::testing::Return(0));
    }

    std::unique_ptr<MockCachedFileLoader> loader;

    std::shared_ptr<CachedFile> createCachedFile() {
        auto cf = std::make_shared<CachedFile>(loader.get(), nullptr);
        return cf;
    }
};

TEST_F(CachedFileStreamTest_160, ConstructorCreatesValidStream_160) {
    auto cc = createCachedFile();
    Object dict;
    CachedFileStream stream(cc, 0, false, 0, std::move(dict));
    // Should be constructible without crash
    SUCCEED();
}

TEST_F(CachedFileStreamTest_160, GetPosReturnsInitialPosition_160) {
    auto cc = createCachedFile();
    Object dict;
    CachedFileStream stream(cc, 0, false, 0, std::move(dict));
    stream.rewind();
    Goffset pos = stream.getPos();
    EXPECT_GE(pos, 0);
}

TEST_F(CachedFileStreamTest_160, GetStartReturnsStartOffset_160) {
    auto cc = createCachedFile();
    Object dict;
    Goffset startOffset = 100;
    CachedFileStream stream(cc, startOffset, false, 0, std::move(dict));
    Goffset start = stream.getStart();
    EXPECT_EQ(start, startOffset);
}

TEST_F(CachedFileStreamTest_160, GetKindReturnsCachedFileKind_160) {
    auto cc = createCachedFile();
    Object dict;
    CachedFileStream stream(cc, 0, false, 0, std::move(dict));
    StreamKind kind = stream.getKind();
    EXPECT_EQ(kind, strCachedFile);
}

TEST_F(CachedFileStreamTest_160, RewindReturnsTrue_160) {
    auto cc = createCachedFile();
    Object dict;
    CachedFileStream stream(cc, 0, false, 0, std::move(dict));
    bool result = stream.rewind();
    EXPECT_TRUE(result);
}

TEST_F(CachedFileStreamTest_160, GetPosAfterRewind_160) {
    auto cc = createCachedFile();
    Object dict;
    Goffset startA = 50;
    CachedFileStream stream(cc, startA, false, 0, std::move(dict));
    stream.rewind();
    Goffset pos = stream.getPos();
    EXPECT_EQ(pos, startA);
}

TEST_F(CachedFileStreamTest_160, SetPosFromStart_160) {
    auto cc = createCachedFile();
    Object dict;
    CachedFileStream stream(cc, 0, false, 0, std::move(dict));
    stream.setPos(100, 0);
    Goffset pos = stream.getPos();
    EXPECT_EQ(pos, 100);
}

TEST_F(CachedFileStreamTest_160, SetPosFromEnd_160) {
    auto cc = createCachedFile();
    Object dict;
    CachedFileStream stream(cc, 0, false, 0, std::move(dict));
    // dir = -1 means from end
    stream.setPos(0, -1);
    Goffset pos = stream.getPos();
    EXPECT_GE(pos, 0);
}

TEST_F(CachedFileStreamTest_160, CopyCreatesNewStream_160) {
    auto cc = createCachedFile();
    Object dict;
    CachedFileStream stream(cc, 0, false, 0, std::move(dict));
    auto copied = stream.copy();
    EXPECT_NE(copied, nullptr);
}

TEST_F(CachedFileStreamTest_160, MakeSubStreamCreatesNewStream_160) {
    auto cc = createCachedFile();
    Object dict;
    CachedFileStream stream(cc, 0, false, 0, std::move(dict));
    Object subDict;
    auto sub = stream.makeSubStream(10, true, 100, std::move(subDict));
    EXPECT_NE(sub, nullptr);
}

TEST_F(CachedFileStreamTest_160, MoveStartAdjustsStart_160) {
    auto cc = createCachedFile();
    Object dict;
    CachedFileStream stream(cc, 0, false, 0, std::move(dict));
    Goffset delta = 50;
    stream.moveStart(delta);
    Goffset newStart = stream.getStart();
    EXPECT_EQ(newStart, delta);
}

TEST_F(CachedFileStreamTest_160, GetCharAtEOFReturnsEOF_160) {
    auto cc = createCachedFile();
    Object dict;
    // Create a limited stream of length 0
    CachedFileStream stream(cc, 0, true, 0, std::move(dict));
    stream.rewind();
    int ch = stream.getChar();
    EXPECT_EQ(ch, EOF);
}

TEST_F(CachedFileStreamTest_160, LookCharAtEOFReturnsEOF_160) {
    auto cc = createCachedFile();
    Object dict;
    // Create a limited stream of length 0
    CachedFileStream stream(cc, 0, true, 0, std::move(dict));
    stream.rewind();
    int ch = stream.lookChar();
    EXPECT_EQ(ch, EOF);
}

TEST_F(CachedFileStreamTest_160, UnfilteredRewindWorks_160) {
    auto cc = createCachedFile();
    Object dict;
    CachedFileStream stream(cc, 0, false, 0, std::move(dict));
    bool result = stream.unfilteredRewind();
    EXPECT_TRUE(result);
}

TEST_F(CachedFileStreamTest_160, GetUnfilteredCharBehavesLikeGetChar_160) {
    auto cc = createCachedFile();
    Object dict;
    CachedFileStream stream(cc, 0, true, 0, std::move(dict));
    stream.rewind();
    int ch = stream.getUnfilteredChar();
    EXPECT_EQ(ch, EOF);
}

TEST_F(CachedFileStreamTest_160, CloseDoesNotCrash_160) {
    auto cc = createCachedFile();
    Object dict;
    CachedFileStream stream(cc, 0, false, 0, std::move(dict));
    stream.close();
    SUCCEED();
}

TEST_F(CachedFileStreamTest_160, LookCharDoesNotAdvancePosition_160) {
    auto cc = createCachedFile();
    Object dict;
    CachedFileStream stream(cc, 0, false, 4096, std::move(dict));
    stream.rewind();
    Goffset posBefore = stream.getPos();
    stream.lookChar();
    Goffset posAfter = stream.getPos();
    EXPECT_EQ(posBefore, posAfter);
}

TEST_F(CachedFileStreamTest_160, GetCharAdvancesPosition_160) {
    auto cc = createCachedFile();
    Object dict;
    CachedFileStream stream(cc, 0, false, 4096, std::move(dict));
    stream.rewind();
    Goffset posBefore = stream.getPos();
    int ch = stream.getChar();
    if (ch != EOF) {
        Goffset posAfter = stream.getPos();
        EXPECT_EQ(posAfter, posBefore + 1);
    }
}

TEST_F(CachedFileStreamTest_160, SetPosZeroFromStart_160) {
    auto cc = createCachedFile();
    Object dict;
    CachedFileStream stream(cc, 0, false, 0, std::move(dict));
    stream.setPos(0, 0);
    Goffset pos = stream.getPos();
    EXPECT_EQ(pos, 0);
}

TEST_F(CachedFileStreamTest_160, MoveStartWithZeroDelta_160) {
    auto cc = createCachedFile();
    Object dict;
    Goffset initialStart = 200;
    CachedFileStream stream(cc, initialStart, false, 0, std::move(dict));
    stream.moveStart(0);
    Goffset start = stream.getStart();
    EXPECT_EQ(start, initialStart);
}

TEST_F(CachedFileStreamTest_160, LimitedStreamRespectsLength_160) {
    auto cc = createCachedFile();
    Object dict;
    // Limited stream of length 5
    CachedFileStream stream(cc, 0, true, 5, std::move(dict));
    stream.rewind();
    int count = 0;
    while (stream.getChar() != EOF) {
        count++;
        if (count > 10) break; // safety
    }
    EXPECT_LE(count, 5);
}

TEST_F(CachedFileStreamTest_160, MultipleRewindsWork_160) {
    auto cc = createCachedFile();
    Object dict;
    CachedFileStream stream(cc, 10, false, 0, std::move(dict));
    
    stream.rewind();
    Goffset pos1 = stream.getPos();
    
    stream.setPos(50, 0);
    
    stream.rewind();
    Goffset pos2 = stream.getPos();
    
    EXPECT_EQ(pos1, pos2);
}
