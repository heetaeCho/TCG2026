#include <gtest/gtest.h>
#include <QBuffer>
#include <QByteArray>
#include <QIODevice>
#include <cstdarg>
#include <cstdio>
#include <cstring>

// Since poppler_vasprintf is static in the .cc file, we need to include it
// or test through the public QIODeviceOutStream interface.
// We'll test through the public class interface.

#include "poppler-qiodeviceoutstream-private.h"

// If the header isn't available, we test the vasprintf function by 
// replicating its signature for testing purposes.
// However, the real tests should go through the QIODeviceOutStream class.

namespace {

// Helper to call vasprintf-style function
int call_poppler_vasprintf(char **buf_ptr, const char *format, ...) {
    va_list ap;
    va_start(ap, format);
    // We replicate the logic to test it, but since we can't access static function,
    // we test via QIODeviceOutStream
    va_list ap_copy;
    va_copy(ap_copy, ap);
    const size_t size = vsnprintf(nullptr, 0, format, ap_copy) + 1;
    va_end(ap_copy);
    *buf_ptr = new char[size];
    int result = vsnprintf(*buf_ptr, size, format, ap);
    va_end(ap);
    return result;
}

}

class QIODeviceOutStreamTest_1262 : public ::testing::Test {
protected:
    void SetUp() override {
        buffer.open(QIODevice::WriteOnly);
    }

    void TearDown() override {
        buffer.close();
    }

    QBuffer buffer;
};

TEST_F(QIODeviceOutStreamTest_1262, WriteSimpleString_1262) {
    Poppler::QIODeviceOutStream stream(&buffer);
    const char *data = "Hello, World!";
    stream.printf("%s", data);
    buffer.close();
    EXPECT_EQ(buffer.data(), QByteArray("Hello, World!"));
}

TEST_F(QIODeviceOutStreamTest_1262, WriteFormattedInt_1262) {
    Poppler::QIODeviceOutStream stream(&buffer);
    stream.printf("%d", 42);
    buffer.close();
    EXPECT_EQ(buffer.data(), QByteArray("42"));
}

TEST_F(QIODeviceOutStreamTest_1262, WriteFormattedFloat_1262) {
    Poppler::QIODeviceOutStream stream(&buffer);
    stream.printf("%.2f", 3.14);
    buffer.close();
    EXPECT_EQ(buffer.data(), QByteArray("3.14"));
}

TEST_F(QIODeviceOutStreamTest_1262, WriteEmptyString_1262) {
    Poppler::QIODeviceOutStream stream(&buffer);
    stream.printf("%s", "");
    buffer.close();
    EXPECT_EQ(buffer.data(), QByteArray(""));
}

TEST_F(QIODeviceOutStreamTest_1262, WriteMultipleFormats_1262) {
    Poppler::QIODeviceOutStream stream(&buffer);
    stream.printf("%s %d %c", "test", 123, 'A');
    buffer.close();
    EXPECT_EQ(buffer.data(), QByteArray("test 123 A"));
}

TEST_F(QIODeviceOutStreamTest_1262, WriteLongString_1262) {
    Poppler::QIODeviceOutStream stream(&buffer);
    std::string longStr(1000, 'x');
    stream.printf("%s", longStr.c_str());
    buffer.close();
    EXPECT_EQ(buffer.data().size(), 1000);
}

TEST_F(QIODeviceOutStreamTest_1262, WriteHexFormat_1262) {
    Poppler::QIODeviceOutStream stream(&buffer);
    stream.printf("%x", 255);
    buffer.close();
    EXPECT_EQ(buffer.data(), QByteArray("ff"));
}

TEST_F(QIODeviceOutStreamTest_1262, WriteMultipleCalls_1262) {
    Poppler::QIODeviceOutStream stream(&buffer);
    stream.printf("%s", "Hello");
    stream.printf(" %s", "World");
    buffer.close();
    EXPECT_EQ(buffer.data(), QByteArray("Hello World"));
}

TEST_F(QIODeviceOutStreamTest_1262, WriteNegativeNumber_1262) {
    Poppler::QIODeviceOutStream stream(&buffer);
    stream.printf("%d", -42);
    buffer.close();
    EXPECT_EQ(buffer.data(), QByteArray("-42"));
}

TEST_F(QIODeviceOutStreamTest_1262, WritePaddedFormat_1262) {
    Poppler::QIODeviceOutStream stream(&buffer);
    stream.printf("%010d", 42);
    buffer.close();
    EXPECT_EQ(buffer.data(), QByteArray("0000000042"));
}
