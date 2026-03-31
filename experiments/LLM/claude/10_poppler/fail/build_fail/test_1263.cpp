#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <QBuffer>
#include <QIODevice>
#include "poppler-qiodeviceoutstream-private.h"

using namespace Poppler;

class QIODeviceOutStreamTest_1263 : public ::testing::Test {
protected:
    void SetUp() override {
        buffer = new QBuffer();
        buffer->open(QIODevice::ReadWrite);
        stream = new QIODeviceOutStream(buffer);
    }

    void TearDown() override {
        delete stream;
        delete buffer;
    }

    QBuffer *buffer;
    QIODeviceOutStream *stream;
};

// Test that constructor creates a valid stream object
TEST_F(QIODeviceOutStreamTest_1263, ConstructorCreatesValidStream_1263) {
    ASSERT_NE(stream, nullptr);
}

// Test put writes a single character
TEST_F(QIODeviceOutStreamTest_1263, PutWritesSingleCharacter_1263) {
    stream->put('A');
    buffer->seek(0);
    QByteArray data = buffer->readAll();
    EXPECT_EQ(data.size(), 1);
    EXPECT_EQ(data[0], 'A');
}

// Test put writes multiple characters sequentially
TEST_F(QIODeviceOutStreamTest_1263, PutWritesMultipleCharacters_1263) {
    stream->put('H');
    stream->put('i');
    buffer->seek(0);
    QByteArray data = buffer->readAll();
    EXPECT_EQ(data.size(), 2);
    EXPECT_EQ(data[0], 'H');
    EXPECT_EQ(data[1], 'i');
}

// Test printf with a simple string (no format specifiers)
TEST_F(QIODeviceOutStreamTest_1263, PrintfSimpleString_1263) {
    stream->printf("Hello");
    buffer->seek(0);
    QByteArray data = buffer->readAll();
    EXPECT_EQ(data, QByteArray("Hello"));
}

// Test printf with integer format specifier
TEST_F(QIODeviceOutStreamTest_1263, PrintfWithIntegerFormat_1263) {
    stream->printf("%d", 42);
    buffer->seek(0);
    QByteArray data = buffer->readAll();
    EXPECT_EQ(data, QByteArray("42"));
}

// Test printf with string format specifier
TEST_F(QIODeviceOutStreamTest_1263, PrintfWithStringFormat_1263) {
    stream->printf("%s", "world");
    buffer->seek(0);
    QByteArray data = buffer->readAll();
    EXPECT_EQ(data, QByteArray("world"));
}

// Test printf with multiple format specifiers
TEST_F(QIODeviceOutStreamTest_1263, PrintfWithMultipleFormatSpecifiers_1263) {
    stream->printf("%s %d %c", "test", 123, 'X');
    buffer->seek(0);
    QByteArray data = buffer->readAll();
    EXPECT_EQ(data, QByteArray("test 123 X"));
}

// Test printf with floating point format
TEST_F(QIODeviceOutStreamTest_1263, PrintfWithFloatFormat_1263) {
    stream->printf("%.2f", 3.14);
    buffer->seek(0);
    QByteArray data = buffer->readAll();
    EXPECT_EQ(data, QByteArray("3.14"));
}

// Test printf with empty string
TEST_F(QIODeviceOutStreamTest_1263, PrintfWithEmptyString_1263) {
    stream->printf("");
    buffer->seek(0);
    QByteArray data = buffer->readAll();
    EXPECT_EQ(data.size(), 0);
}

// Test getPos returns 0 initially
TEST_F(QIODeviceOutStreamTest_1263, GetPosInitiallyZero_1263) {
    Goffset pos = stream->getPos();
    EXPECT_EQ(pos, 0);
}

// Test getPos advances after put
TEST_F(QIODeviceOutStreamTest_1263, GetPosAdvancesAfterPut_1263) {
    stream->put('A');
    Goffset pos = stream->getPos();
    EXPECT_EQ(pos, 1);
}

// Test getPos advances after printf
TEST_F(QIODeviceOutStreamTest_1263, GetPosAdvancesAfterPrintf_1263) {
    stream->printf("Hello");
    Goffset pos = stream->getPos();
    EXPECT_EQ(pos, 5);
}

// Test getPos advances correctly after multiple operations
TEST_F(QIODeviceOutStreamTest_1263, GetPosAdvancesAfterMultipleOperations_1263) {
    stream->put('A');
    stream->printf("BC");
    stream->put('D');
    Goffset pos = stream->getPos();
    EXPECT_EQ(pos, 4);
}

// Test close can be called without error
TEST_F(QIODeviceOutStreamTest_1263, CloseDoesNotCrash_1263) {
    stream->put('A');
    stream->close();
    // Just verifying no crash
    SUCCEED();
}

// Test put with null character
TEST_F(QIODeviceOutStreamTest_1263, PutNullCharacter_1263) {
    stream->put('\0');
    Goffset pos = stream->getPos();
    EXPECT_EQ(pos, 1);
}

// Test put with special characters
TEST_F(QIODeviceOutStreamTest_1263, PutSpecialCharacters_1263) {
    stream->put('\n');
    stream->put('\t');
    stream->put('\r');
    buffer->seek(0);
    QByteArray data = buffer->readAll();
    EXPECT_EQ(data.size(), 3);
    EXPECT_EQ(data[0], '\n');
    EXPECT_EQ(data[1], '\t');
    EXPECT_EQ(data[2], '\r');
}

// Test printf with large formatted string
TEST_F(QIODeviceOutStreamTest_1263, PrintfLargeString_1263) {
    std::string largeStr(1000, 'A');
    stream->printf("%s", largeStr.c_str());
    buffer->seek(0);
    QByteArray data = buffer->readAll();
    EXPECT_EQ(data.size(), 1000);
}

// Test printf with negative integer
TEST_F(QIODeviceOutStreamTest_1263, PrintfNegativeInteger_1263) {
    stream->printf("%d", -42);
    buffer->seek(0);
    QByteArray data = buffer->readAll();
    EXPECT_EQ(data, QByteArray("-42"));
}

// Test printf with hex format
TEST_F(QIODeviceOutStreamTest_1263, PrintfHexFormat_1263) {
    stream->printf("%x", 255);
    buffer->seek(0);
    QByteArray data = buffer->readAll();
    EXPECT_EQ(data, QByteArray("ff"));
}

// Test printf with percent literal
TEST_F(QIODeviceOutStreamTest_1263, PrintfPercentLiteral_1263) {
    stream->printf("100%%");
    buffer->seek(0);
    QByteArray data = buffer->readAll();
    EXPECT_EQ(data, QByteArray("100%"));
}

// Test sequential printf calls accumulate data
TEST_F(QIODeviceOutStreamTest_1263, SequentialPrintfAccumulatesData_1263) {
    stream->printf("Hello");
    stream->printf(" ");
    stream->printf("World");
    buffer->seek(0);
    QByteArray data = buffer->readAll();
    EXPECT_EQ(data, QByteArray("Hello World"));
}

// Test mixed put and printf operations
TEST_F(QIODeviceOutStreamTest_1263, MixedPutAndPrintf_1263) {
    stream->put('(');
    stream->printf("%d", 42);
    stream->put(')');
    buffer->seek(0);
    QByteArray data = buffer->readAll();
    EXPECT_EQ(data, QByteArray("(42)"));
}

// Test printf with zero padded format
TEST_F(QIODeviceOutStreamTest_1263, PrintfZeroPaddedFormat_1263) {
    stream->printf("%05d", 42);
    buffer->seek(0);
    QByteArray data = buffer->readAll();
    EXPECT_EQ(data, QByteArray("00042"));
}
