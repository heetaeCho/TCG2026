#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-qiodeviceinstream-private.h"

#include "Object.h"

#include <QIODevice>



using namespace Poppler;

using ::testing::NiceMock;



class MockQIODevice : public QIODevice {

public:

    MOCK_METHOD(qint64, readData(char *data, qint64 maxlen), (override));

    MOCK_METHOD(bool, seek(qint64 pos), (override));

};



class QIODeviceInStreamTest_1343 : public ::testing::Test {

protected:

    NiceMock<MockQIODevice> mockDevice;

    Object dict = Object::null();

    Goffset start = 0;

    bool limited = false;

    Goffset length = 1024;



    void SetUp() override {

        qIODeviceInStream = std::make_unique<QIODeviceInStream>(&mockDevice, start, limited, length, std::move(dict));

    }



    std::unique_ptr<QIODeviceInStream> qIODeviceInStream;

};



TEST_F(QIODeviceInStreamTest_1343, CopyCreatesNewInstance_1343) {

    auto copy = qIODeviceInStream->copy();

    EXPECT_NE(copy.get(), qIODeviceInStream.get());

}



TEST_F(QIODeviceInStreamTest_1343, MakeSubStreamCreatesNewInstance_1343) {

    Object subDict = Object::null();

    Goffset subStart = 0;

    bool subLimited = false;

    Goffset subLength = 512;



    auto subStream = qIODeviceInStream->makeSubStream(subStart, subLimited, subLength, std::move(subDict));

    EXPECT_NE(subStream.get(), qIODeviceInStream.get());

}



TEST_F(QIODeviceInStreamTest_1343, CopyPreservesBaseSeekInputStreamProperties_1343) {

    auto copy = qIODeviceInStream->copy();

    EXPECT_EQ(copy->getStart(), start);

    EXPECT_EQ(copy->isLimited(), limited);

    EXPECT_EQ(copy->getLength(), length);

}



TEST_F(QIODeviceInStreamTest_1343, MakeSubStreamPreservesBaseSeekInputStreamProperties_1343) {

    Object subDict = Object::null();

    Goffset subStart = 0;

    bool subLimited = false;

    Goffset subLength = 512;



    auto subStream = qIODeviceInStream->makeSubStream(subStart, subLimited, subLength, std::move(subDict));

    EXPECT_EQ(subStream->getStart(), subStart);

    EXPECT_EQ(subStream->isLimited(), subLimited);

    EXPECT_EQ(subStream->getLength(), subLength);

}



TEST_F(QIODeviceInStreamTest_1343, DestructorDoesNotThrow_1343) {

    EXPECT_NO_THROW(qIODeviceInStream.reset());

}
