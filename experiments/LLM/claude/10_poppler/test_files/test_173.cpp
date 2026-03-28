#include <gtest/gtest.h>
#include <memory>
#include "poppler/Stream.h"
#include "poppler/Object.h"

// Test fixture for BaseMemStream tests
class BaseMemStreamTest_173 : public ::testing::Test {
protected:
    void SetUp() override {
        // Set up a buffer with known data
        for (int i = 0; i < 256; i++) {
            buffer[i] = static_cast<unsigned char>(i);
        }
    }

    unsigned char buffer[256];
};

TEST_F(BaseMemStreamTest_173, ConstructAndGetStart_173) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buffer), 0, 256, std::move(dict));
    EXPECT_EQ(stream->getStart(), 0);
}

TEST_F(BaseMemStreamTest_173, ConstructWithNonZeroStart_173) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buffer), 10, 100, std::move(dict));
    EXPECT_EQ(stream->getStart(), 10);
}

TEST_F(BaseMemStreamTest_173, GetKind_173) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buffer), 0, 256, std::move(dict));
    EXPECT_EQ(stream->getKind(), strWeird);
}

TEST_F(BaseMemStreamTest_173, GetChar_173) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buffer), 0, 256, std::move(dict));
    stream->rewind();
    int ch = stream->getChar();
    EXPECT_EQ(ch, 0);
    ch = stream->getChar();
    EXPECT_EQ(ch, 1);
    ch = stream->getChar();
    EXPECT_EQ(ch, 2);
}

TEST_F(BaseMemStreamTest_173, LookChar_173) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buffer), 0, 256, std::move(dict));
    stream->rewind();
    int ch1 = stream->lookChar();
    int ch2 = stream->lookChar();
    EXPECT_EQ(ch1, ch2);
    EXPECT_EQ(ch1, 0);
}

TEST_F(BaseMemStreamTest_173, LookCharDoesNotAdvance_173) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buffer), 0, 256, std::move(dict));
    stream->rewind();
    int ch1 = stream->lookChar();
    int ch2 = stream->getChar();
    EXPECT_EQ(ch1, ch2);
}

TEST_F(BaseMemStreamTest_173, GetPos_173) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buffer), 0, 256, std::move(dict));
    stream->rewind();
    EXPECT_EQ(stream->getPos(), 0);
    stream->getChar();
    EXPECT_EQ(stream->getPos(), 1);
    stream->getChar();
    EXPECT_EQ(stream->getPos(), 2);
}

TEST_F(BaseMemStreamTest_173, Rewind_173) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buffer), 0, 256, std::move(dict));
    stream->rewind();
    stream->getChar();
    stream->getChar();
    stream->getChar();
    EXPECT_EQ(stream->getPos(), 3);
    bool result = stream->rewind();
    EXPECT_TRUE(result);
    EXPECT_EQ(stream->getPos(), 0);
}

TEST_F(BaseMemStreamTest_173, SetPosForward_173) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buffer), 0, 256, std::move(dict));
    stream->rewind();
    stream->setPos(10);
    EXPECT_EQ(stream->getPos(), 10);
    int ch = stream->getChar();
    EXPECT_EQ(ch, 10);
}

TEST_F(BaseMemStreamTest_173, SetPosToBeginning_173) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buffer), 0, 256, std::move(dict));
    stream->rewind();
    stream->getChar();
    stream->getChar();
    stream->setPos(0);
    EXPECT_EQ(stream->getPos(), 0);
}

TEST_F(BaseMemStreamTest_173, SetPosFromEnd_173) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buffer), 0, 256, std::move(dict));
    stream->rewind();
    // dir != 0 means from end
    stream->setPos(0, 1);
    // After setting pos from end with 0, should be at the end
    // The exact behavior depends on implementation, but we can check getPos
    Goffset pos = stream->getPos();
    EXPECT_GE(pos, 0);
}

TEST_F(BaseMemStreamTest_173, MoveStart_173) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buffer), 0, 256, std::move(dict));
    Goffset originalStart = stream->getStart();
    EXPECT_EQ(originalStart, 0);
    stream->moveStart(10);
    EXPECT_EQ(stream->getStart(), 10);
}

TEST_F(BaseMemStreamTest_173, MoveStartAffectsRewind_173) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buffer), 0, 256, std::move(dict));
    stream->moveStart(5);
    stream->rewind();
    // After moving start by 5, reading should start from position 5
    int ch = stream->getChar();
    EXPECT_EQ(ch, 5);
}

TEST_F(BaseMemStreamTest_173, MoveStartMultipleTimes_173) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buffer), 0, 256, std::move(dict));
    stream->moveStart(3);
    EXPECT_EQ(stream->getStart(), 3);
    stream->moveStart(7);
    EXPECT_EQ(stream->getStart(), 10);
}

TEST_F(BaseMemStreamTest_173, GetLength_173) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buffer), 0, 256, std::move(dict));
    EXPECT_EQ(stream->getLength(), 256);
}

TEST_F(BaseMemStreamTest_173, MoveStartReducesLength_173) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buffer), 0, 256, std::move(dict));
    stream->moveStart(10);
    EXPECT_EQ(stream->getLength(), 246);
}

TEST_F(BaseMemStreamTest_173, ReadAllChars_173) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buffer), 0, 10, std::move(dict));
    stream->rewind();
    for (int i = 0; i < 10; i++) {
        int ch = stream->getChar();
        EXPECT_EQ(ch, i);
    }
    // Reading past end should return EOF
    int ch = stream->getChar();
    EXPECT_EQ(ch, EOF);
}

TEST_F(BaseMemStreamTest_173, LookCharAtEOF_173) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buffer), 0, 1, std::move(dict));
    stream->rewind();
    stream->getChar(); // read the only char
    int ch = stream->lookChar();
    EXPECT_EQ(ch, EOF);
}

TEST_F(BaseMemStreamTest_173, EmptyStream_173) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buffer), 0, 0, std::move(dict));
    stream->rewind();
    int ch = stream->getChar();
    EXPECT_EQ(ch, EOF);
}

TEST_F(BaseMemStreamTest_173, EmptyStreamLookChar_173) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buffer), 0, 0, std::move(dict));
    stream->rewind();
    int ch = stream->lookChar();
    EXPECT_EQ(ch, EOF);
}

TEST_F(BaseMemStreamTest_173, Copy_173) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buffer), 0, 256, std::move(dict));
    auto copy = stream->copy();
    ASSERT_NE(copy, nullptr);
    copy->rewind();
    int ch = copy->getChar();
    EXPECT_EQ(ch, 0);
}

TEST_F(BaseMemStreamTest_173, MakeSubStream_173) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buffer), 0, 256, std::move(dict));
    Object subDict;
    auto sub = stream->makeSubStream(10, true, 20, std::move(subDict));
    ASSERT_NE(sub, nullptr);
    sub->rewind();
    int ch = sub->getChar();
    EXPECT_EQ(ch, 10);
}

TEST_F(BaseMemStreamTest_173, GetBaseStream_173) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buffer), 0, 256, std::move(dict));
    BaseStream *base = stream->getBaseStream();
    EXPECT_EQ(base, stream.get());
}

TEST_F(BaseMemStreamTest_173, Close_173) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buffer), 0, 256, std::move(dict));
    stream->rewind();
    stream->getChar();
    stream->close();
    // After close, rewind should still work
    stream->rewind();
    int ch = stream->getChar();
    EXPECT_EQ(ch, 0);
}

TEST_F(BaseMemStreamTest_173, UnfilteredRewind_173) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buffer), 0, 256, std::move(dict));
    stream->rewind();
    stream->getChar();
    stream->getChar();
    bool result = stream->unfilteredRewind();
    EXPECT_TRUE(result);
}

TEST_F(BaseMemStreamTest_173, GetUnfilteredChar_173) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buffer), 0, 256, std::move(dict));
    stream->rewind();
    int ch = stream->getUnfilteredChar();
    EXPECT_EQ(ch, 0);
}

TEST_F(BaseMemStreamTest_173, SetPosWithNonZeroStart_173) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buffer), 5, 100, std::move(dict));
    stream->rewind();
    stream->setPos(10);
    int ch = stream->getChar();
    EXPECT_EQ(ch, 10);
}

TEST_F(BaseMemStreamTest_173, SetPosBeyondEnd_173) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buffer), 0, 10, std::move(dict));
    stream->rewind();
    stream->setPos(100);
    // Position should be clamped or at end
    int ch = stream->getChar();
    EXPECT_EQ(ch, EOF);
}

TEST_F(BaseMemStreamTest_173, IsBinary_173) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buffer), 0, 256, std::move(dict));
    // BaseStream::isBinary should return true by default for binary streams
    bool binary = stream->isBinary();
    EXPECT_TRUE(binary);
}

TEST_F(BaseMemStreamTest_173, GetPosAfterRewind_173) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buffer), 5, 100, std::move(dict));
    stream->rewind();
    EXPECT_EQ(stream->getPos(), 5);
}

TEST_F(BaseMemStreamTest_173, SequentialReads_173) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buffer), 0, 256, std::move(dict));
    stream->rewind();
    for (int i = 0; i < 256; i++) {
        int ch = stream->getChar();
        EXPECT_EQ(ch, i) << "Failed at index " << i;
    }
    EXPECT_EQ(stream->getChar(), EOF);
}

TEST_F(BaseMemStreamTest_173, MoveStartZeroDelta_173) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buffer), 0, 256, std::move(dict));
    stream->moveStart(0);
    EXPECT_EQ(stream->getStart(), 0);
    EXPECT_EQ(stream->getLength(), 256);
}

TEST_F(BaseMemStreamTest_173, GetDict_173) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buffer), 0, 256, std::move(dict));
    // getDict should return a non-null value (or null dict)
    // We just test it doesn't crash
    Dict *d = stream->getDict();
    // For a null dict object, this may return nullptr
    (void)d;
}

TEST_F(BaseMemStreamTest_173, GetDictObject_173) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buffer), 0, 256, std::move(dict));
    Object *dictObj = stream->getDictObject();
    EXPECT_NE(dictObj, nullptr);
}
