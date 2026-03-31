#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <QBuffer>
#include <QIODevice>
#include <QByteArray>
#include "poppler-qiodeviceoutstream-private.h"

using namespace Poppler;

class QIODeviceOutStreamTest_1261 : public ::testing::Test {
protected:
    void SetUp() override {
        buffer = new QBuffer(&byteArray);
        buffer->open(QIODevice::WriteOnly);
    }

    void TearDown() override {
        delete buffer;
    }

    QByteArray byteArray;
    QBuffer *buffer;
};

// Test construction with a valid QIODevice
TEST_F(QIODeviceOutStreamTest_1261, ConstructionWithValidDevice_1261) {
    QIODeviceOutStream stream(buffer);
    // Should construct without error
    EXPECT_EQ(stream.getPos(), 0);
}

// Test put writes a single character
TEST_F(QIODeviceOutStreamTest_1261, PutWritesSingleCharacter_1261) {
    QIODeviceOutStream stream(buffer);
    stream.put('A');
    buffer->close();
    EXPECT_EQ(byteArray.size(), 1);
    EXPECT_EQ(byteArray.at(0), 'A');
}

// Test put writes multiple characters sequentially
TEST_F(QIODeviceOutStreamTest_1261, PutWritesMultipleCharacters_1261) {
    QIODeviceOutStream stream(buffer);
    stream.put('H');
    stream.put('e');
    stream.put('l');
    stream.put('l');
    stream.put('o');
    buffer->close();
    EXPECT_EQ(byteArray, QByteArray("Hello"));
}

// Test put with null character
TEST_F(QIODeviceOutStreamTest_1261, PutNullCharacter_1261) {
    QIODeviceOutStream stream(buffer);
    stream.put('\0');
    buffer->close();
    EXPECT_EQ(byteArray.size(), 1);
    EXPECT_EQ(byteArray.at(0), '\0');
}

// Test put with special characters
TEST_F(QIODeviceOutStreamTest_1261, PutSpecialCharacters_1261) {
    QIODeviceOutStream stream(buffer);
    stream.put('\n');
    stream.put('\t');
    stream.put('\r');
    buffer->close();
    EXPECT_EQ(byteArray.size(), 3);
    EXPECT_EQ(byteArray.at(0), '\n');
    EXPECT_EQ(byteArray.at(1), '\t');
    EXPECT_EQ(byteArray.at(2), '\r');
}

// Test getPos returns correct position after put
TEST_F(QIODeviceOutStreamTest_1261, GetPosAfterPut_1261) {
    QIODeviceOutStream stream(buffer);
    EXPECT_EQ(stream.getPos(), 0);
    stream.put('A');
    EXPECT_EQ(stream.getPos(), 1);
    stream.put('B');
    EXPECT_EQ(stream.getPos(), 2);
}

// Test getPos returns correct position initially
TEST_F(QIODeviceOutStreamTest_1261, GetPosInitiallyZero_1261) {
    QIODeviceOutStream stream(buffer);
    EXPECT_EQ(stream.getPos(), 0);
}

// Test close operation
TEST_F(QIODeviceOutStreamTest_1261, CloseStream_1261) {
    QIODeviceOutStream stream(buffer);
    stream.put('X');
    stream.close();
    // After close, the data should have been flushed
    EXPECT_EQ(byteArray.size(), 1);
    EXPECT_EQ(byteArray.at(0), 'X');
}

// Test printf with simple string
TEST_F(QIODeviceOutStreamTest_1261, PrintfSimpleString_1261) {
    QIODeviceOutStream stream(buffer);
    stream.printf("hello");
    buffer->close();
    EXPECT_EQ(byteArray, QByteArray("hello"));
}

// Test printf with format specifiers
TEST_F(QIODeviceOutStreamTest_1261, PrintfWithIntegerFormat_1261) {
    QIODeviceOutStream stream(buffer);
    stream.printf("%d", 42);
    buffer->close();
    EXPECT_EQ(byteArray, QByteArray("42"));
}

// Test printf with string format
TEST_F(QIODeviceOutStreamTest_1261, PrintfWithStringFormat_1261) {
    QIODeviceOutStream stream(buffer);
    stream.printf("%s", "world");
    buffer->close();
    EXPECT_EQ(byteArray, QByteArray("world"));
}

// Test printf with float format
TEST_F(QIODeviceOutStreamTest_1261, PrintfWithFloatFormat_1261) {
    QIODeviceOutStream stream(buffer);
    stream.printf("%.2f", 3.14);
    buffer->close();
    EXPECT_EQ(byteArray, QByteArray("3.14"));
}

// Test printf with empty string
TEST_F(QIODeviceOutStreamTest_1261, PrintfEmptyString_1261) {
    QIODeviceOutStream stream(buffer);
    stream.printf("");
    buffer->close();
    EXPECT_EQ(byteArray.size(), 0);
}

// Test getPos after printf
TEST_F(QIODeviceOutStreamTest_1261, GetPosAfterPrintf_1261) {
    QIODeviceOutStream stream(buffer);
    stream.printf("test");
    EXPECT_EQ(stream.getPos(), 4);
}

// Test mixed put and printf
TEST_F(QIODeviceOutStreamTest_1261, MixedPutAndPrintf_1261) {
    QIODeviceOutStream stream(buffer);
    stream.put('A');
    stream.printf("BC");
    stream.put('D');
    buffer->close();
    EXPECT_EQ(byteArray, QByteArray("ABCD"));
    EXPECT_EQ(byteArray.size(), 4);
}

// Test put with high-value byte
TEST_F(QIODeviceOutStreamTest_1261, PutHighValueByte_1261) {
    QIODeviceOutStream stream(buffer);
    stream.put(static_cast<char>(0xFF));
    buffer->close();
    EXPECT_EQ(byteArray.size(), 1);
    EXPECT_EQ(static_cast<unsigned char>(byteArray.at(0)), 0xFF);
}

// Test writing a large number of characters
TEST_F(QIODeviceOutStreamTest_1261, PutLargeNumberOfCharacters_1261) {
    QIODeviceOutStream stream(buffer);
    const int count = 10000;
    for (int i = 0; i < count; ++i) {
        stream.put('X');
    }
    buffer->close();
    EXPECT_EQ(byteArray.size(), count);
}

// Test getPos after large write
TEST_F(QIODeviceOutStreamTest_1261, GetPosAfterLargeWrite_1261) {
    QIODeviceOutStream stream(buffer);
    const int count = 500;
    for (int i = 0; i < count; ++i) {
        stream.put('A');
    }
    EXPECT_EQ(stream.getPos(), count);
}

// Test printf with multiple format specifiers
TEST_F(QIODeviceOutStreamTest_1261, PrintfMultipleFormatSpecifiers_1261) {
    QIODeviceOutStream stream(buffer);
    stream.printf("%d %s %.1f", 10, "items", 2.5);
    buffer->close();
    EXPECT_EQ(byteArray, QByteArray("10 items 2.5"));
}

// Test destruction cleans up properly (no crash)
TEST_F(QIODeviceOutStreamTest_1261, DestructionDoesNotCrash_1261) {
    {
        QIODeviceOutStream stream(buffer);
        stream.put('Z');
    }
    // If we reach here, destruction didn't crash
    SUCCEED();
}

// Test printf with newline characters
TEST_F(QIODeviceOutStreamTest_1261, PrintfWithNewlines_1261) {
    QIODeviceOutStream stream(buffer);
    stream.printf("line1\nline2\n");
    buffer->close();
    EXPECT_EQ(byteArray, QByteArray("line1\nline2\n"));
}
