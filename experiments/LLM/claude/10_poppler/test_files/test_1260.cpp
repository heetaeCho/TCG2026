#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <QBuffer>
#include <QIODevice>
#include <QByteArray>
#include "poppler-qiodeviceoutstream-private.h"

using namespace Poppler;

class QIODeviceOutStreamTest_1260 : public ::testing::Test {
protected:
    void SetUp() override {
        m_byteArray.clear();
        m_buffer = new QBuffer(&m_byteArray);
        m_buffer->open(QIODevice::ReadWrite);
    }

    void TearDown() override {
        if (m_buffer->isOpen()) {
            m_buffer->close();
        }
        delete m_buffer;
    }

    QByteArray m_byteArray;
    QBuffer *m_buffer;
};

TEST_F(QIODeviceOutStreamTest_1260, ConstructorInitializesWithDevice_1260) {
    QIODeviceOutStream stream(m_buffer);
    // After construction, position should be at 0
    EXPECT_EQ(stream.getPos(), 0);
}

TEST_F(QIODeviceOutStreamTest_1260, GetPosReturnsZeroInitially_1260) {
    QIODeviceOutStream stream(m_buffer);
    EXPECT_EQ(stream.getPos(), 0);
}

TEST_F(QIODeviceOutStreamTest_1260, PutSingleCharacter_1260) {
    QIODeviceOutStream stream(m_buffer);
    stream.put('A');
    EXPECT_EQ(stream.getPos(), 1);
    EXPECT_EQ(m_byteArray.size(), 1);
    EXPECT_EQ(m_byteArray.at(0), 'A');
}

TEST_F(QIODeviceOutStreamTest_1260, PutMultipleCharacters_1260) {
    QIODeviceOutStream stream(m_buffer);
    stream.put('H');
    stream.put('i');
    stream.put('!');
    EXPECT_EQ(stream.getPos(), 3);
    EXPECT_EQ(m_byteArray.size(), 3);
    EXPECT_EQ(m_byteArray, QByteArray("Hi!"));
}

TEST_F(QIODeviceOutStreamTest_1260, PutNullCharacter_1260) {
    QIODeviceOutStream stream(m_buffer);
    stream.put('\0');
    EXPECT_EQ(stream.getPos(), 1);
    EXPECT_EQ(m_byteArray.size(), 1);
    EXPECT_EQ(m_byteArray.at(0), '\0');
}

TEST_F(QIODeviceOutStreamTest_1260, PutNewlineCharacter_1260) {
    QIODeviceOutStream stream(m_buffer);
    stream.put('\n');
    EXPECT_EQ(stream.getPos(), 1);
    EXPECT_EQ(m_byteArray.at(0), '\n');
}

TEST_F(QIODeviceOutStreamTest_1260, PrintfSimpleString_1260) {
    QIODeviceOutStream stream(m_buffer);
    stream.printf("hello");
    EXPECT_EQ(m_byteArray, QByteArray("hello"));
    EXPECT_EQ(stream.getPos(), 5);
}

TEST_F(QIODeviceOutStreamTest_1260, PrintfWithIntegerFormat_1260) {
    QIODeviceOutStream stream(m_buffer);
    stream.printf("%d", 42);
    EXPECT_EQ(m_byteArray, QByteArray("42"));
}

TEST_F(QIODeviceOutStreamTest_1260, PrintfWithStringFormat_1260) {
    QIODeviceOutStream stream(m_buffer);
    stream.printf("%s %s", "hello", "world");
    EXPECT_EQ(m_byteArray, QByteArray("hello world"));
}

TEST_F(QIODeviceOutStreamTest_1260, PrintfWithFloatFormat_1260) {
    QIODeviceOutStream stream(m_buffer);
    stream.printf("%.2f", 3.14);
    EXPECT_EQ(m_byteArray, QByteArray("3.14"));
}

TEST_F(QIODeviceOutStreamTest_1260, PrintfEmptyString_1260) {
    QIODeviceOutStream stream(m_buffer);
    stream.printf("");
    EXPECT_EQ(stream.getPos(), 0);
    EXPECT_EQ(m_byteArray.size(), 0);
}

TEST_F(QIODeviceOutStreamTest_1260, PrintfMultipleCalls_1260) {
    QIODeviceOutStream stream(m_buffer);
    stream.printf("abc");
    stream.printf("def");
    EXPECT_EQ(m_byteArray, QByteArray("abcdef"));
    EXPECT_EQ(stream.getPos(), 6);
}

TEST_F(QIODeviceOutStreamTest_1260, CloseStream_1260) {
    QIODeviceOutStream stream(m_buffer);
    stream.put('X');
    stream.close();
    // After close, the data written before should still be in the buffer
    EXPECT_EQ(m_byteArray, QByteArray("X"));
}

TEST_F(QIODeviceOutStreamTest_1260, GetPosAfterMultipleOperations_1260) {
    QIODeviceOutStream stream(m_buffer);
    stream.put('A');
    EXPECT_EQ(stream.getPos(), 1);
    stream.printf("BCD");
    EXPECT_EQ(stream.getPos(), 4);
    stream.put('E');
    EXPECT_EQ(stream.getPos(), 5);
}

TEST_F(QIODeviceOutStreamTest_1260, PutSpecialCharacters_1260) {
    QIODeviceOutStream stream(m_buffer);
    stream.put('\t');
    stream.put('\r');
    stream.put('\n');
    EXPECT_EQ(stream.getPos(), 3);
    EXPECT_EQ(m_byteArray.at(0), '\t');
    EXPECT_EQ(m_byteArray.at(1), '\r');
    EXPECT_EQ(m_byteArray.at(2), '\n');
}

TEST_F(QIODeviceOutStreamTest_1260, PrintfWithHexFormat_1260) {
    QIODeviceOutStream stream(m_buffer);
    stream.printf("%x", 255);
    EXPECT_EQ(m_byteArray, QByteArray("ff"));
}

TEST_F(QIODeviceOutStreamTest_1260, PrintfWithMultipleFormats_1260) {
    QIODeviceOutStream stream(m_buffer);
    stream.printf("%d %s %.1f", 10, "items", 3.5);
    EXPECT_EQ(m_byteArray, QByteArray("10 items 3.5"));
}

TEST_F(QIODeviceOutStreamTest_1260, LargeDataWrite_1260) {
    QIODeviceOutStream stream(m_buffer);
    for (int i = 0; i < 1000; i++) {
        stream.put('X');
    }
    EXPECT_EQ(stream.getPos(), 1000);
    EXPECT_EQ(m_byteArray.size(), 1000);
}

TEST_F(QIODeviceOutStreamTest_1260, DestructorDoesNotCrash_1260) {
    {
        QIODeviceOutStream stream(m_buffer);
        stream.put('A');
        stream.printf("test");
    }
    // If we reach here without crash, destructor worked fine
    EXPECT_EQ(m_byteArray, QByteArray("Atest"));
}

TEST_F(QIODeviceOutStreamTest_1260, PutBinaryData_1260) {
    QIODeviceOutStream stream(m_buffer);
    for (int i = 0; i < 256; i++) {
        stream.put(static_cast<char>(i));
    }
    EXPECT_EQ(stream.getPos(), 256);
    EXPECT_EQ(m_byteArray.size(), 256);
    for (int i = 0; i < 256; i++) {
        EXPECT_EQ(static_cast<unsigned char>(m_byteArray.at(i)), static_cast<unsigned char>(i));
    }
}

TEST_F(QIODeviceOutStreamTest_1260, PrintfWithPercentSign_1260) {
    QIODeviceOutStream stream(m_buffer);
    stream.printf("100%%");
    EXPECT_EQ(m_byteArray, QByteArray("100%"));
}

TEST_F(QIODeviceOutStreamTest_1260, BufferWithPreExistingData_1260) {
    // Write some data to buffer before creating the stream
    m_buffer->write("pre");
    Goffset prePos = m_buffer->pos();

    QIODeviceOutStream stream(m_buffer);
    EXPECT_EQ(stream.getPos(), prePos);

    stream.put('X');
    EXPECT_EQ(stream.getPos(), prePos + 1);
}
