#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Stream.h"
#include "Object.h"
#include "Dict.h"
#include "GooString.h"

// We need a concrete subclass of BaseStream to test it, since BaseStream
// has pure virtual methods inherited from Stream. We'll use FileStream
// or a minimal concrete implementation if available.
// In poppler, FileStream is a concrete subclass of BaseStream.

#include <cstdio>
#include <cstring>
#include <memory>

// Helper to create a temporary file for FileStream testing
class BaseStreamTest_126 : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a temporary file with some content
        tmpFile = tmpfile();
        if (tmpFile) {
            const char *data = "Hello, World! This is test data for BaseStream.";
            fwrite(data, 1, strlen(data), tmpFile);
            fflush(tmpFile);
            rewind(tmpFile);
            dataLen = strlen(data);
        }
    }

    void TearDown() override {
        if (tmpFile) {
            fclose(tmpFile);
            tmpFile = nullptr;
        }
    }

    FILE *tmpFile = nullptr;
    size_t dataLen = 0;
};

// Test that getBaseStream returns this pointer
TEST_F(BaseStreamTest_126, GetBaseStreamReturnsSelf_126) {
    if (!tmpFile) GTEST_SKIP() << "Could not create temp file";

    Object dictObj;
    auto stream = std::make_unique<FileStream>(tmpFile, 0, false, dataLen, std::move(dictObj));

    BaseStream *base = stream->getBaseStream();
    EXPECT_EQ(base, stream.get());
}

// Test that getLength returns the correct length
TEST_F(BaseStreamTest_126, GetLengthReturnsCorrectValue_126) {
    if (!tmpFile) GTEST_SKIP() << "Could not create temp file";

    Object dictObj;
    Goffset expectedLen = static_cast<Goffset>(dataLen);
    auto stream = std::make_unique<FileStream>(tmpFile, 0, true, expectedLen, std::move(dictObj));

    EXPECT_EQ(stream->getLength(), expectedLen);
}

// Test that getStart returns the starting position
TEST_F(BaseStreamTest_126, GetStartReturnsStartPosition_126) {
    if (!tmpFile) GTEST_SKIP() << "Could not create temp file";

    Object dictObj;
    Goffset startPos = 5;
    auto stream = std::make_unique<FileStream>(tmpFile, startPos, true, dataLen - startPos, std::move(dictObj));

    EXPECT_EQ(stream->getStart(), startPos);
}

// Test that getDict returns the dictionary
TEST_F(BaseStreamTest_126, GetDictReturnsDict_126) {
    if (!tmpFile) GTEST_SKIP() << "Could not create temp file";

    Object dictObj;
    auto stream = std::make_unique<FileStream>(tmpFile, 0, false, dataLen, std::move(dictObj));

    // getDict may return nullptr if the dict object is not a dict type
    // but getDictObject should return a valid pointer
    Object *dictObjPtr = stream->getDictObject();
    EXPECT_NE(dictObjPtr, nullptr);
}

// Test that isBinary returns true for BaseStream
TEST_F(BaseStreamTest_126, IsBinaryReturnsTrue_126) {
    if (!tmpFile) GTEST_SKIP() << "Could not create temp file";

    Object dictObj;
    auto stream = std::make_unique<FileStream>(tmpFile, 0, false, dataLen, std::move(dictObj));

    EXPECT_TRUE(stream->isBinary());
    EXPECT_TRUE(stream->isBinary(true));
    EXPECT_TRUE(stream->isBinary(false));
}

// Test that getUndecodedStream returns the stream itself
TEST_F(BaseStreamTest_126, GetUndecodedStreamReturnsSelf_126) {
    if (!tmpFile) GTEST_SKIP() << "Could not create temp file";

    Object dictObj;
    auto stream = std::make_unique<FileStream>(tmpFile, 0, false, dataLen, std::move(dictObj));

    Stream *undecoded = stream->getUndecodedStream();
    EXPECT_EQ(undecoded, stream.get());
}

// Test moveStart changes the start position
TEST_F(BaseStreamTest_126, MoveStartChangesStart_126) {
    if (!tmpFile) GTEST_SKIP() << "Could not create temp file";

    Object dictObj;
    auto stream = std::make_unique<FileStream>(tmpFile, 0, true, dataLen, std::move(dictObj));

    Goffset originalStart = stream->getStart();
    Goffset delta = 5;
    stream->moveStart(delta);

    EXPECT_EQ(stream->getStart(), originalStart + delta);
}

// Test that getFileName returns nullptr for FileStream created from FILE*
TEST_F(BaseStreamTest_126, GetFileNameReturnsNullForFilePtrStream_126) {
    if (!tmpFile) GTEST_SKIP() << "Could not create temp file";

    Object dictObj;
    auto stream = std::make_unique<FileStream>(tmpFile, 0, false, dataLen, std::move(dictObj));

    GooString *fileName = stream->getFileName();
    // FileStream created from FILE* typically has no filename
    EXPECT_EQ(fileName, nullptr);
}

// Test that makeSubStream creates a valid substream
TEST_F(BaseStreamTest_126, MakeSubStreamCreatesValidStream_126) {
    if (!tmpFile) GTEST_SKIP() << "Could not create temp file";

    Object dictObj;
    auto stream = std::make_unique<FileStream>(tmpFile, 0, false, dataLen, std::move(dictObj));

    Object subDictObj;
    auto subStream = stream->makeSubStream(0, true, 10, std::move(subDictObj));

    EXPECT_NE(subStream, nullptr);
    EXPECT_NE(subStream->getBaseStream(), nullptr);
}

// Test setPos and reading after repositioning
TEST_F(BaseStreamTest_126, SetPosFromBeginning_126) {
    if (!tmpFile) GTEST_SKIP() << "Could not create temp file";

    Object dictObj;
    auto stream = std::make_unique<FileStream>(tmpFile, 0, false, dataLen, std::move(dictObj));

    stream->reset();
    stream->setPos(0, 0); // Set to beginning

    int ch = stream->getChar();
    EXPECT_EQ(ch, 'H'); // "Hello, World!..."
}

// Test setPos from end
TEST_F(BaseStreamTest_126, SetPosFromEnd_126) {
    if (!tmpFile) GTEST_SKIP() << "Could not create temp file";

    Object dictObj;
    auto stream = std::make_unique<FileStream>(tmpFile, 0, false, dataLen, std::move(dictObj));

    stream->reset();
    stream->setPos(0, -1); // Set to end (or near end)

    // After setting to end, reading should give EOF or the last character
    // depending on exact behavior
    // This just tests that it doesn't crash
}

// Test copy creates a valid copy
TEST_F(BaseStreamTest_126, CopyCreatesValidStream_126) {
    if (!tmpFile) GTEST_SKIP() << "Could not create temp file";

    Object dictObj;
    auto stream = std::make_unique<FileStream>(tmpFile, 0, false, dataLen, std::move(dictObj));

    auto copyStream = stream->copy();
    // copy may return nullptr for some stream types
    if (copyStream) {
        EXPECT_NE(copyStream->getBaseStream(), nullptr);
    }
}

// Test with zero-length stream
TEST_F(BaseStreamTest_126, ZeroLengthStream_126) {
    if (!tmpFile) GTEST_SKIP() << "Could not create temp file";

    Object dictObj;
    auto stream = std::make_unique<FileStream>(tmpFile, 0, true, 0, std::move(dictObj));

    EXPECT_EQ(stream->getLength(), 0);

    stream->reset();
    int ch = stream->getChar();
    EXPECT_EQ(ch, EOF);
}

// Test reading characters sequentially
TEST_F(BaseStreamTest_126, ReadSequentialChars_126) {
    if (!tmpFile) GTEST_SKIP() << "Could not create temp file";

    Object dictObj;
    auto stream = std::make_unique<FileStream>(tmpFile, 0, true, dataLen, std::move(dictObj));

    stream->reset();

    EXPECT_EQ(stream->getChar(), 'H');
    EXPECT_EQ(stream->getChar(), 'e');
    EXPECT_EQ(stream->getChar(), 'l');
    EXPECT_EQ(stream->getChar(), 'l');
    EXPECT_EQ(stream->getChar(), 'o');
}

// Test lookChar does not advance position
TEST_F(BaseStreamTest_126, LookCharDoesNotAdvance_126) {
    if (!tmpFile) GTEST_SKIP() << "Could not create temp file";

    Object dictObj;
    auto stream = std::make_unique<FileStream>(tmpFile, 0, true, dataLen, std::move(dictObj));

    stream->reset();

    int ch1 = stream->lookChar();
    int ch2 = stream->lookChar();
    EXPECT_EQ(ch1, ch2);
    EXPECT_EQ(ch1, 'H');
}

// Test getPos returns current position
TEST_F(BaseStreamTest_126, GetPosReturnsCurrentPosition_126) {
    if (!tmpFile) GTEST_SKIP() << "Could not create temp file";

    Object dictObj;
    auto stream = std::make_unique<FileStream>(tmpFile, 0, true, dataLen, std::move(dictObj));

    stream->reset();
    Goffset pos0 = stream->getPos();

    stream->getChar(); // Read one character
    Goffset pos1 = stream->getPos();

    EXPECT_EQ(pos1, pos0 + 1);
}
