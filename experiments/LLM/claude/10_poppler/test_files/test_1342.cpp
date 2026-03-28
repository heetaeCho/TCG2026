#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <QBuffer>
#include <QByteArray>
#include <QIODevice>

#include "poppler-qiodeviceinstream-private.h"
#include "Object.h"

class QIODeviceInStreamTest_1342 : public ::testing::Test {
protected:
    void SetUp() override {
        testData = QByteArray("Hello, World! This is a test buffer for QIODeviceInStream testing. "
                              "It contains enough data to test various read operations and boundary conditions.");
        buffer = new QBuffer(&testData);
        buffer->open(QIODevice::ReadOnly);
    }

    void TearDown() override {
        if (buffer->isOpen()) {
            buffer->close();
        }
        delete buffer;
    }

    QByteArray testData;
    QBuffer *buffer;
};

TEST_F(QIODeviceInStreamTest_1342, ConstructionUnlimited_1342) {
    Object dict;
    Poppler::QIODeviceInStream stream(buffer, 0, false, 0, std::move(dict));
    EXPECT_EQ(stream.getKind(), strWeird);
}

TEST_F(QIODeviceInStreamTest_1342, ConstructionLimited_1342) {
    Object dict;
    Poppler::QIODeviceInStream stream(buffer, 0, true, 10, std::move(dict));
    EXPECT_EQ(stream.getKind(), strWeird);
}

TEST_F(QIODeviceInStreamTest_1342, GetStartReturnsStartPosition_1342) {
    Object dict;
    Goffset startPos = 5;
    Poppler::QIODeviceInStream stream(buffer, startPos, false, 0, std::move(dict));
    EXPECT_EQ(stream.getStart(), startPos);
}

TEST_F(QIODeviceInStreamTest_1342, GetStartReturnsZero_1342) {
    Object dict;
    Poppler::QIODeviceInStream stream(buffer, 0, false, 0, std::move(dict));
    EXPECT_EQ(stream.getStart(), 0);
}

TEST_F(QIODeviceInStreamTest_1342, ReadCharFromBeginning_1342) {
    Object dict;
    Poppler::QIODeviceInStream stream(buffer, 0, false, 0, std::move(dict));
    stream.rewind();
    int ch = stream.getChar();
    EXPECT_EQ(ch, 'H');
}

TEST_F(QIODeviceInStreamTest_1342, ReadMultipleChars_1342) {
    Object dict;
    Poppler::QIODeviceInStream stream(buffer, 0, false, 0, std::move(dict));
    stream.rewind();
    
    std::string result;
    for (int i = 0; i < 5; i++) {
        int ch = stream.getChar();
        ASSERT_NE(ch, EOF);
        result += static_cast<char>(ch);
    }
    EXPECT_EQ(result, "Hello");
}

TEST_F(QIODeviceInStreamTest_1342, LookCharDoesNotAdvance_1342) {
    Object dict;
    Poppler::QIODeviceInStream stream(buffer, 0, false, 0, std::move(dict));
    stream.rewind();
    
    int ch1 = stream.lookChar();
    int ch2 = stream.lookChar();
    EXPECT_EQ(ch1, ch2);
    EXPECT_EQ(ch1, 'H');
}

TEST_F(QIODeviceInStreamTest_1342, GetCharAfterLookChar_1342) {
    Object dict;
    Poppler::QIODeviceInStream stream(buffer, 0, false, 0, std::move(dict));
    stream.rewind();
    
    int looked = stream.lookChar();
    int got = stream.getChar();
    EXPECT_EQ(looked, got);
    EXPECT_EQ(got, 'H');
    
    // Next char should be different
    int next = stream.getChar();
    EXPECT_EQ(next, 'e');
}

TEST_F(QIODeviceInStreamTest_1342, GetPosAfterRewind_1342) {
    Object dict;
    Poppler::QIODeviceInStream stream(buffer, 0, false, 0, std::move(dict));
    stream.rewind();
    EXPECT_EQ(stream.getPos(), 0);
}

TEST_F(QIODeviceInStreamTest_1342, GetPosAdvancesAfterRead_1342) {
    Object dict;
    Poppler::QIODeviceInStream stream(buffer, 0, false, 0, std::move(dict));
    stream.rewind();
    
    stream.getChar();
    EXPECT_EQ(stream.getPos(), 1);
    
    stream.getChar();
    EXPECT_EQ(stream.getPos(), 2);
}

TEST_F(QIODeviceInStreamTest_1342, SetPosFromBeginning_1342) {
    Object dict;
    Poppler::QIODeviceInStream stream(buffer, 0, false, 0, std::move(dict));
    stream.rewind();
    
    stream.setPos(5, 0);
    int ch = stream.getChar();
    EXPECT_EQ(ch, testData.at(5));
}

TEST_F(QIODeviceInStreamTest_1342, RewindReturnsToStart_1342) {
    Object dict;
    Poppler::QIODeviceInStream stream(buffer, 0, false, 0, std::move(dict));
    stream.rewind();
    
    // Read some chars
    stream.getChar();
    stream.getChar();
    stream.getChar();
    
    // Rewind
    bool result = stream.rewind();
    EXPECT_TRUE(result);
    
    // Should be back at start
    int ch = stream.getChar();
    EXPECT_EQ(ch, 'H');
}

TEST_F(QIODeviceInStreamTest_1342, LimitedStreamReadsOnlyLength_1342) {
    Object dict;
    Goffset length = 5;
    Poppler::QIODeviceInStream stream(buffer, 0, true, length, std::move(dict));
    stream.rewind();
    
    std::string result;
    for (Goffset i = 0; i < length; i++) {
        int ch = stream.getChar();
        ASSERT_NE(ch, EOF) << "Unexpected EOF at position " << i;
        result += static_cast<char>(ch);
    }
    EXPECT_EQ(result, "Hello");
    
    // After reading 'length' bytes, next read should return EOF
    int ch = stream.getChar();
    EXPECT_EQ(ch, EOF);
}

TEST_F(QIODeviceInStreamTest_1342, LimitedStreamWithOffset_1342) {
    Object dict;
    Goffset start = 7;
    Goffset length = 5;
    Poppler::QIODeviceInStream stream(buffer, start, true, length, std::move(dict));
    stream.rewind();
    
    std::string result;
    for (Goffset i = 0; i < length; i++) {
        int ch = stream.getChar();
        if (ch == EOF) break;
        result += static_cast<char>(ch);
    }
    EXPECT_EQ(result, "World");
}

TEST_F(QIODeviceInStreamTest_1342, CopyCreatesNewStream_1342) {
    Object dict;
    Poppler::QIODeviceInStream stream(buffer, 0, false, 0, std::move(dict));
    
    auto copy = stream.copy();
    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->getKind(), strWeird);
}

TEST_F(QIODeviceInStreamTest_1342, MakeSubStreamCreatesStream_1342) {
    Object dict;
    Poppler::QIODeviceInStream stream(buffer, 0, false, 0, std::move(dict));
    
    Object subDict;
    auto subStream = stream.makeSubStream(0, true, 5, std::move(subDict));
    ASSERT_NE(subStream, nullptr);
}

TEST_F(QIODeviceInStreamTest_1342, EmptyBuffer_1342) {
    QByteArray emptyData;
    QBuffer emptyBuffer(&emptyData);
    emptyBuffer.open(QIODevice::ReadOnly);
    
    Object dict;
    Poppler::QIODeviceInStream stream(&emptyBuffer, 0, false, 0, std::move(dict));
    stream.rewind();
    
    int ch = stream.getChar();
    EXPECT_EQ(ch, EOF);
    
    emptyBuffer.close();
}

TEST_F(QIODeviceInStreamTest_1342, EmptyBufferLimited_1342) {
    QByteArray emptyData;
    QBuffer emptyBuffer(&emptyData);
    emptyBuffer.open(QIODevice::ReadOnly);
    
    Object dict;
    Poppler::QIODeviceInStream stream(&emptyBuffer, 0, true, 0, std::move(dict));
    stream.rewind();
    
    int ch = stream.getChar();
    EXPECT_EQ(ch, EOF);
    
    emptyBuffer.close();
}

TEST_F(QIODeviceInStreamTest_1342, SingleByteBuffer_1342) {
    QByteArray singleByte("X");
    QBuffer singleBuffer(&singleByte);
    singleBuffer.open(QIODevice::ReadOnly);
    
    Object dict;
    Poppler::QIODeviceInStream stream(&singleBuffer, 0, true, 1, std::move(dict));
    stream.rewind();
    
    int ch = stream.getChar();
    EXPECT_EQ(ch, 'X');
    
    ch = stream.getChar();
    EXPECT_EQ(ch, EOF);
    
    singleBuffer.close();
}

TEST_F(QIODeviceInStreamTest_1342, MoveStartAdjustsStart_1342) {
    Object dict;
    Poppler::QIODeviceInStream stream(buffer, 0, false, 0, std::move(dict));
    
    stream.moveStart(5);
    EXPECT_EQ(stream.getStart(), 5);
}

TEST_F(QIODeviceInStreamTest_1342, CloseAndDestructor_1342) {
    Object dict;
    {
        Poppler::QIODeviceInStream stream(buffer, 0, false, 0, std::move(dict));
        stream.rewind();
        stream.getChar();
        stream.close();
    }
    // No crash means success
    SUCCEED();
}

TEST_F(QIODeviceInStreamTest_1342, UnfilteredRewind_1342) {
    Object dict;
    Poppler::QIODeviceInStream stream(buffer, 0, false, 0, std::move(dict));
    stream.rewind();
    
    stream.getChar();
    stream.getChar();
    
    bool result = stream.unfilteredRewind();
    EXPECT_TRUE(result);
}

TEST_F(QIODeviceInStreamTest_1342, GetUnfilteredChar_1342) {
    Object dict;
    Poppler::QIODeviceInStream stream(buffer, 0, false, 0, std::move(dict));
    stream.rewind();
    
    int ch = stream.getUnfilteredChar();
    EXPECT_EQ(ch, 'H');
}

TEST_F(QIODeviceInStreamTest_1342, LargeBufferReading_1342) {
    // Create a large buffer exceeding typical internal buffer size (16384)
    QByteArray largeData(32768, 'A');
    // Put a marker at position 16384
    largeData[16384] = 'B';
    QBuffer largeBuffer(&largeData);
    largeBuffer.open(QIODevice::ReadOnly);
    
    Object dict;
    Poppler::QIODeviceInStream stream(&largeBuffer, 0, false, 0, std::move(dict));
    stream.rewind();
    
    // Seek to position 16384 and read the marker
    stream.setPos(16384, 0);
    int ch = stream.getChar();
    EXPECT_EQ(ch, 'B');
    
    largeBuffer.close();
}

TEST_F(QIODeviceInStreamTest_1342, SetPosFromEnd_1342) {
    Object dict;
    Poppler::QIODeviceInStream stream(buffer, 0, true, static_cast<Goffset>(testData.size()), std::move(dict));
    stream.rewind();
    
    // Set position from end (dir != 0 typically means from end)
    stream.setPos(0, -1);
    // After setting to end, getChar should return EOF or the last char depending on implementation
    // We just verify no crash
    SUCCEED();
}

TEST_F(QIODeviceInStreamTest_1342, ReadFromNonZeroStart_1342) {
    Object dict;
    Goffset start = 13; // After "Hello, World!"
    Poppler::QIODeviceInStream stream(buffer, start, false, 0, std::move(dict));
    stream.rewind();
    
    int ch = stream.getChar();
    EXPECT_EQ(ch, testData.at(static_cast<int>(start)));
}

TEST_F(QIODeviceInStreamTest_1342, BinaryData_1342) {
    QByteArray binaryData;
    binaryData.append('\x00');
    binaryData.append('\x01');
    binaryData.append('\xFF');
    binaryData.append('\x80');
    QBuffer binaryBuffer(&binaryData);
    binaryBuffer.open(QIODevice::ReadOnly);
    
    Object dict;
    Poppler::QIODeviceInStream stream(&binaryBuffer, 0, true, 4, std::move(dict));
    stream.rewind();
    
    EXPECT_EQ(stream.getChar(), 0x00);
    EXPECT_EQ(stream.getChar(), 0x01);
    EXPECT_EQ(stream.getChar(), 0xFF);
    EXPECT_EQ(stream.getChar(), 0x80);
    EXPECT_EQ(stream.getChar(), EOF);
    
    binaryBuffer.close();
}

TEST_F(QIODeviceInStreamTest_1342, StreamKind_1342) {
    Object dict;
    Poppler::QIODeviceInStream stream(buffer, 0, false, 0, std::move(dict));
    // QIODeviceInStream should return strWeird as its kind (from BaseSeekInputStream)
    EXPECT_EQ(stream.getKind(), strWeird);
}
