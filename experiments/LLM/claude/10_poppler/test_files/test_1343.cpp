#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <QBuffer>
#include <QByteArray>
#include <QIODevice>
#include <memory>

// Include the necessary headers
#include "poppler-qiodeviceinstream-private.h"
#include "Object.h"
#include "Stream.h"

using namespace Poppler;

class QIODeviceInStreamTest_1343 : public ::testing::Test {
protected:
    void SetUp() override {
        testData = QByteArray("Hello, World! This is test data for QIODeviceInStream.");
        buffer = new QBuffer(&testData);
        buffer->open(QIODevice::ReadOnly);
    }

    void TearDown() override {
        buffer->close();
        delete buffer;
    }

    QByteArray testData;
    QBuffer *buffer;
};

// Test basic construction and destruction
TEST_F(QIODeviceInStreamTest_1343, ConstructionAndDestruction_1343) {
    Object dict;
    auto stream = std::make_unique<QIODeviceInStream>(buffer, 0, false, testData.size(), std::move(dict));
    ASSERT_NE(stream, nullptr);
}

// Test copy returns a non-null unique_ptr
TEST_F(QIODeviceInStreamTest_1343, CopyReturnsNonNull_1343) {
    Object dict;
    auto stream = std::make_unique<QIODeviceInStream>(buffer, 0, false, testData.size(), std::move(dict));
    auto copied = stream->copy();
    ASSERT_NE(copied, nullptr);
}

// Test makeSubStream returns a non-null unique_ptr
TEST_F(QIODeviceInStreamTest_1343, MakeSubStreamReturnsNonNull_1343) {
    Object dict;
    auto stream = std::make_unique<QIODeviceInStream>(buffer, 0, false, testData.size(), std::move(dict));
    Object subDict;
    auto subStream = stream->makeSubStream(0, true, 10, std::move(subDict));
    ASSERT_NE(subStream, nullptr);
}

// Test reading characters after rewind
TEST_F(QIODeviceInStreamTest_1343, RewindAndReadChar_1343) {
    Object dict;
    auto stream = std::make_unique<QIODeviceInStream>(buffer, 0, false, testData.size(), std::move(dict));
    ASSERT_TRUE(stream->rewind());
    int ch = stream->getChar();
    EXPECT_EQ(ch, 'H');
}

// Test reading multiple characters
TEST_F(QIODeviceInStreamTest_1343, ReadMultipleChars_1343) {
    Object dict;
    auto stream = std::make_unique<QIODeviceInStream>(buffer, 0, false, testData.size(), std::move(dict));
    stream->rewind();

    std::string result;
    for (int i = 0; i < 5; i++) {
        int ch = stream->getChar();
        ASSERT_NE(ch, EOF);
        result += static_cast<char>(ch);
    }
    EXPECT_EQ(result, "Hello");
}

// Test reading with a buffer using getChars (via streamGetChars)
TEST_F(QIODeviceInStreamTest_1343, GetCharsBuffer_1343) {
    Object dict;
    auto stream = std::make_unique<QIODeviceInStream>(buffer, 0, false, testData.size(), std::move(dict));
    stream->rewind();

    unsigned char buf[13];
    int nRead = stream->getChars(13, buf);
    EXPECT_EQ(nRead, 13);
    EXPECT_EQ(std::string(reinterpret_cast<char*>(buf), 13), "Hello, World!");
}

// Test getPos after reading
TEST_F(QIODeviceInStreamTest_1343, GetPosAfterRead_1343) {
    Object dict;
    auto stream = std::make_unique<QIODeviceInStream>(buffer, 0, false, testData.size(), std::move(dict));
    stream->rewind();
    EXPECT_EQ(stream->getPos(), 0);

    stream->getChar();
    EXPECT_EQ(stream->getPos(), 1);
}

// Test setPos to a specific position
TEST_F(QIODeviceInStreamTest_1343, SetPosForward_1343) {
    Object dict;
    auto stream = std::make_unique<QIODeviceInStream>(buffer, 0, false, testData.size(), std::move(dict));
    stream->rewind();
    stream->setPos(7, 0); // Move to position 7
    int ch = stream->getChar();
    EXPECT_EQ(ch, 'W');
}

// Test with limited stream
TEST_F(QIODeviceInStreamTest_1343, LimitedStream_1343) {
    Object dict;
    auto stream = std::make_unique<QIODeviceInStream>(buffer, 0, true, 5, std::move(dict));
    stream->rewind();

    EXPECT_EQ(stream->getLength(), 5);
}

// Test with offset start
TEST_F(QIODeviceInStreamTest_1343, OffsetStart_1343) {
    Object dict;
    auto stream = std::make_unique<QIODeviceInStream>(buffer, 7, false, testData.size() - 7, std::move(dict));
    stream->rewind();
    int ch = stream->getChar();
    EXPECT_EQ(ch, 'W');
}

// Test getStart returns the correct start position
TEST_F(QIODeviceInStreamTest_1343, GetStartReturnsCorrectValue_1343) {
    Object dict;
    Goffset startPos = 10;
    auto stream = std::make_unique<QIODeviceInStream>(buffer, startPos, false, testData.size() - startPos, std::move(dict));
    EXPECT_EQ(stream->getStart(), startPos);
}

// Test getLength returns the correct length
TEST_F(QIODeviceInStreamTest_1343, GetLengthReturnsCorrectValue_1343) {
    Object dict;
    Goffset len = 20;
    auto stream = std::make_unique<QIODeviceInStream>(buffer, 0, true, len, std::move(dict));
    EXPECT_EQ(stream->getLength(), len);
}

// Test close and then attempt to rewind
TEST_F(QIODeviceInStreamTest_1343, CloseAndRewind_1343) {
    Object dict;
    auto stream = std::make_unique<QIODeviceInStream>(buffer, 0, false, testData.size(), std::move(dict));
    stream->rewind();
    stream->getChar();
    stream->close();
    // After close, rewind should still work (re-opens for reading)
    bool rewound = stream->rewind();
    EXPECT_TRUE(rewound);
}

// Test getDict returns a valid dict
TEST_F(QIODeviceInStreamTest_1343, GetDictReturnsDict_1343) {
    Object dict;
    auto stream = std::make_unique<QIODeviceInStream>(buffer, 0, false, testData.size(), std::move(dict));
    // getDict() should return something (may be nullptr if dict is null-type, but should not crash)
    Dict *d = stream->getDict();
    // For a default-constructed Object (objNone), getDict may return nullptr
    // We just test it doesn't crash
    (void)d;
}

// Test with empty QBuffer
TEST_F(QIODeviceInStreamTest_1343, EmptyBuffer_1343) {
    QByteArray emptyData;
    QBuffer emptyBuffer(&emptyData);
    emptyBuffer.open(QIODevice::ReadOnly);

    Object dict;
    auto stream = std::make_unique<QIODeviceInStream>(&emptyBuffer, 0, false, 0, std::move(dict));
    stream->rewind();
    int ch = stream->getChar();
    EXPECT_EQ(ch, EOF);

    emptyBuffer.close();
}

// Test reading at the exact boundary of the data
TEST_F(QIODeviceInStreamTest_1343, ReadAtBoundary_1343) {
    Object dict;
    Goffset dataLen = testData.size();
    auto stream = std::make_unique<QIODeviceInStream>(buffer, 0, true, dataLen, std::move(dict));
    stream->rewind();

    unsigned char buf[256];
    int nRead = stream->getChars(static_cast<int>(dataLen), buf);
    EXPECT_EQ(nRead, static_cast<int>(dataLen));
    EXPECT_EQ(std::string(reinterpret_cast<char*>(buf), dataLen), std::string(testData.constData(), dataLen));

    // Next read should return EOF
    int ch = stream->getChar();
    EXPECT_EQ(ch, EOF);
}

// Test copy produces a stream that can read the same data
TEST_F(QIODeviceInStreamTest_1343, CopyProducesReadableStream_1343) {
    Object dict;
    auto stream = std::make_unique<QIODeviceInStream>(buffer, 0, false, testData.size(), std::move(dict));
    auto copied = stream->copy();
    ASSERT_NE(copied, nullptr);

    copied->rewind();
    int ch = copied->getChar();
    EXPECT_EQ(ch, 'H');
}

// Test makeSubStream with limited range
TEST_F(QIODeviceInStreamTest_1343, MakeSubStreamLimitedRange_1343) {
    Object dict;
    auto stream = std::make_unique<QIODeviceInStream>(buffer, 0, false, testData.size(), std::move(dict));
    Object subDict;
    auto subStream = stream->makeSubStream(7, true, 5, std::move(subDict));
    ASSERT_NE(subStream, nullptr);

    subStream->rewind();
    std::string result;
    for (int i = 0; i < 5; i++) {
        int ch = subStream->getChar();
        if (ch == EOF) break;
        result += static_cast<char>(ch);
    }
    EXPECT_EQ(result, "World");
}

// Test moveStart shifts the start position
TEST_F(QIODeviceInStreamTest_1343, MoveStartShiftsPosition_1343) {
    Object dict;
    auto stream = std::make_unique<QIODeviceInStream>(buffer, 0, false, testData.size(), std::move(dict));
    EXPECT_EQ(stream->getStart(), 0);

    stream->moveStart(5);
    EXPECT_EQ(stream->getStart(), 5);

    stream->rewind();
    int ch = stream->getChar();
    EXPECT_EQ(ch, ',');
}

// Test getKind returns the correct kind
TEST_F(QIODeviceInStreamTest_1343, GetKindReturnsCorrectType_1343) {
    Object dict;
    auto stream = std::make_unique<QIODeviceInStream>(buffer, 0, false, testData.size(), std::move(dict));
    // BaseSeekInputStream should report its stream kind
    StreamKind kind = stream->getKind();
    // We don't know the exact kind, just make sure it doesn't crash
    (void)kind;
}

// Test lookChar does not advance position
TEST_F(QIODeviceInStreamTest_1343, LookCharDoesNotAdvance_1343) {
    Object dict;
    auto stream = std::make_unique<QIODeviceInStream>(buffer, 0, false, testData.size(), std::move(dict));
    stream->rewind();

    int ch1 = stream->lookChar();
    int ch2 = stream->lookChar();
    EXPECT_EQ(ch1, ch2);
    EXPECT_EQ(ch1, 'H');
}

// Test setPos with dir=1 (from end)
TEST_F(QIODeviceInStreamTest_1343, SetPosFromEnd_1343) {
    Object dict;
    Goffset dataLen = testData.size();
    auto stream = std::make_unique<QIODeviceInStream>(buffer, 0, true, dataLen, std::move(dict));
    stream->rewind();

    // setPos with dir != 0 typically means from end
    stream->setPos(0, 1);
    // After setting to end, getChar should return the last char or EOF depending on implementation
    // We just verify no crash
    int ch = stream->getChar();
    (void)ch;
}

// Test with large offset start near end of data
TEST_F(QIODeviceInStreamTest_1343, LargeOffsetStart_1343) {
    Object dict;
    Goffset startPos = testData.size() - 1;
    auto stream = std::make_unique<QIODeviceInStream>(buffer, startPos, true, 1, std::move(dict));
    stream->rewind();
    int ch = stream->getChar();
    EXPECT_EQ(ch, testData.at(testData.size() - 1));

    int ch2 = stream->getChar();
    EXPECT_EQ(ch2, EOF);
}

// Test getBaseStream returns this
TEST_F(QIODeviceInStreamTest_1343, GetBaseStreamReturnsSelf_1343) {
    Object dict;
    auto stream = std::make_unique<QIODeviceInStream>(buffer, 0, false, testData.size(), std::move(dict));
    BaseStream *base = stream->getBaseStream();
    EXPECT_EQ(base, stream.get());
}

// Test getDictObject returns non-null
TEST_F(QIODeviceInStreamTest_1343, GetDictObjectReturnsNonNull_1343) {
    Object dict;
    auto stream = std::make_unique<QIODeviceInStream>(buffer, 0, false, testData.size(), std::move(dict));
    Object *dictObj = stream->getDictObject();
    ASSERT_NE(dictObj, nullptr);
}

// Test isBinary returns expected value
TEST_F(QIODeviceInStreamTest_1343, IsBinaryCheck_1343) {
    Object dict;
    auto stream = std::make_unique<QIODeviceInStream>(buffer, 0, false, testData.size(), std::move(dict));
    // BaseStream::isBinary should return a boolean
    bool binary = stream->isBinary();
    // We just verify it returns without error
    (void)binary;
}
