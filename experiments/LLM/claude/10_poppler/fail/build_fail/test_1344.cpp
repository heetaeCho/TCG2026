#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <QBuffer>
#include <QIODevice>
#include <memory>

#include "poppler-qiodeviceinstream-private.h"
#include "Object.h"

using namespace Poppler;

class QIODeviceInStreamTest_1344 : public ::testing::Test {
protected:
    void SetUp() override {
        testData = QByteArray("Hello, World! This is test data for QIODeviceInStream.");
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

TEST_F(QIODeviceInStreamTest_1344, ConstructorCreatesStream_1344) {
    Object dict;
    QIODeviceInStream stream(buffer, 0, false, 0, std::move(dict));
    // If construction succeeds without crash, the test passes
    SUCCEED();
}

TEST_F(QIODeviceInStreamTest_1344, ConstructorWithLimitedStream_1344) {
    Object dict;
    QIODeviceInStream stream(buffer, 0, true, 10, std::move(dict));
    SUCCEED();
}

TEST_F(QIODeviceInStreamTest_1344, ConstructorWithOffset_1344) {
    Object dict;
    QIODeviceInStream stream(buffer, 5, false, 0, std::move(dict));
    SUCCEED();
}

TEST_F(QIODeviceInStreamTest_1344, ConstructorWithOffsetAndLimit_1344) {
    Object dict;
    QIODeviceInStream stream(buffer, 5, true, 10, std::move(dict));
    SUCCEED();
}

TEST_F(QIODeviceInStreamTest_1344, MakeSubStreamReturnsNonNull_1344) {
    Object dict;
    QIODeviceInStream stream(buffer, 0, false, 0, std::move(dict));

    Object subDict;
    auto subStream = stream.makeSubStream(0, true, 5, std::move(subDict));
    ASSERT_NE(subStream, nullptr);
}

TEST_F(QIODeviceInStreamTest_1344, MakeSubStreamWithOffset_1344) {
    Object dict;
    QIODeviceInStream stream(buffer, 0, false, 0, std::move(dict));

    Object subDict;
    auto subStream = stream.makeSubStream(5, true, 10, std::move(subDict));
    ASSERT_NE(subStream, nullptr);
}

TEST_F(QIODeviceInStreamTest_1344, MakeSubStreamUnlimited_1344) {
    Object dict;
    QIODeviceInStream stream(buffer, 0, false, 0, std::move(dict));

    Object subDict;
    auto subStream = stream.makeSubStream(0, false, 0, std::move(subDict));
    ASSERT_NE(subStream, nullptr);
}

TEST_F(QIODeviceInStreamTest_1344, CopyReturnsNonNull_1344) {
    Object dict;
    QIODeviceInStream stream(buffer, 0, false, 0, std::move(dict));

    auto copied = stream.copy();
    ASSERT_NE(copied, nullptr);
}

TEST_F(QIODeviceInStreamTest_1344, CopyWithLimitedStream_1344) {
    Object dict;
    QIODeviceInStream stream(buffer, 0, true, 10, std::move(dict));

    auto copied = stream.copy();
    ASSERT_NE(copied, nullptr);
}

TEST_F(QIODeviceInStreamTest_1344, ConstructorWithZeroLength_1344) {
    Object dict;
    QIODeviceInStream stream(buffer, 0, true, 0, std::move(dict));
    SUCCEED();
}

TEST_F(QIODeviceInStreamTest_1344, ConstructorWithLargeOffset_1344) {
    Object dict;
    Goffset largeOffset = testData.size() + 100;
    QIODeviceInStream stream(buffer, largeOffset, false, 0, std::move(dict));
    SUCCEED();
}

TEST_F(QIODeviceInStreamTest_1344, MakeSubStreamWithZeroLength_1344) {
    Object dict;
    QIODeviceInStream stream(buffer, 0, false, 0, std::move(dict));

    Object subDict;
    auto subStream = stream.makeSubStream(0, true, 0, std::move(subDict));
    ASSERT_NE(subStream, nullptr);
}

TEST_F(QIODeviceInStreamTest_1344, MakeSubStreamWithLargeOffset_1344) {
    Object dict;
    QIODeviceInStream stream(buffer, 0, false, 0, std::move(dict));

    Object subDict;
    Goffset largeOffset = testData.size() + 100;
    auto subStream = stream.makeSubStream(largeOffset, true, 5, std::move(subDict));
    ASSERT_NE(subStream, nullptr);
}

TEST_F(QIODeviceInStreamTest_1344, EmptyBufferConstruction_1344) {
    QByteArray emptyData;
    QBuffer emptyBuffer(&emptyData);
    emptyBuffer.open(QIODevice::ReadOnly);

    Object dict;
    QIODeviceInStream stream(&emptyBuffer, 0, false, 0, std::move(dict));
    SUCCEED();

    emptyBuffer.close();
}

TEST_F(QIODeviceInStreamTest_1344, EmptyBufferMakeSubStream_1344) {
    QByteArray emptyData;
    QBuffer emptyBuffer(&emptyData);
    emptyBuffer.open(QIODevice::ReadOnly);

    Object dict;
    QIODeviceInStream stream(&emptyBuffer, 0, false, 0, std::move(dict));

    Object subDict;
    auto subStream = stream.makeSubStream(0, true, 0, std::move(subDict));
    ASSERT_NE(subStream, nullptr);

    emptyBuffer.close();
}

TEST_F(QIODeviceInStreamTest_1344, EmptyBufferCopy_1344) {
    QByteArray emptyData;
    QBuffer emptyBuffer(&emptyData);
    emptyBuffer.open(QIODevice::ReadOnly);

    Object dict;
    QIODeviceInStream stream(&emptyBuffer, 0, false, 0, std::move(dict));

    auto copied = stream.copy();
    ASSERT_NE(copied, nullptr);

    emptyBuffer.close();
}

TEST_F(QIODeviceInStreamTest_1344, LargeDataConstruction_1344) {
    QByteArray largeData(1024 * 1024, 'A'); // 1MB of data
    QBuffer largeBuffer(&largeData);
    largeBuffer.open(QIODevice::ReadOnly);

    Object dict;
    QIODeviceInStream stream(&largeBuffer, 0, false, 0, std::move(dict));
    SUCCEED();

    largeBuffer.close();
}

TEST_F(QIODeviceInStreamTest_1344, LargeDataMakeSubStream_1344) {
    QByteArray largeData(1024 * 1024, 'A');
    QBuffer largeBuffer(&largeData);
    largeBuffer.open(QIODevice::ReadOnly);

    Object dict;
    QIODeviceInStream stream(&largeBuffer, 0, false, 0, std::move(dict));

    Object subDict;
    auto subStream = stream.makeSubStream(512, true, 1024, std::move(subDict));
    ASSERT_NE(subStream, nullptr);

    largeBuffer.close();
}

TEST_F(QIODeviceInStreamTest_1344, MultipleSubStreams_1344) {
    Object dict;
    QIODeviceInStream stream(buffer, 0, false, 0, std::move(dict));

    Object subDict1;
    auto sub1 = stream.makeSubStream(0, true, 5, std::move(subDict1));
    ASSERT_NE(sub1, nullptr);

    Object subDict2;
    auto sub2 = stream.makeSubStream(5, true, 5, std::move(subDict2));
    ASSERT_NE(sub2, nullptr);

    Object subDict3;
    auto sub3 = stream.makeSubStream(10, true, 5, std::move(subDict3));
    ASSERT_NE(sub3, nullptr);
}

TEST_F(QIODeviceInStreamTest_1344, DestructorDoesNotCrash_1344) {
    {
        Object dict;
        QIODeviceInStream stream(buffer, 0, false, 0, std::move(dict));
    }
    // If we reach here without crash, destruction succeeded
    SUCCEED();
}

TEST_F(QIODeviceInStreamTest_1344, StartAtEndOfData_1344) {
    Object dict;
    Goffset endOffset = testData.size();
    QIODeviceInStream stream(buffer, endOffset, true, 0, std::move(dict));
    SUCCEED();
}

TEST_F(QIODeviceInStreamTest_1344, LimitedWithExactDataLength_1344) {
    Object dict;
    QIODeviceInStream stream(buffer, 0, true, testData.size(), std::move(dict));
    SUCCEED();
}

TEST_F(QIODeviceInStreamTest_1344, LimitedExceedingDataLength_1344) {
    Object dict;
    QIODeviceInStream stream(buffer, 0, true, testData.size() + 100, std::move(dict));
    SUCCEED();
}
