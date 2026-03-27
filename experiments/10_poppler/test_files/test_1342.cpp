#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-qiodeviceinstream-private.h"

#include <QIODevice>



using namespace Poppler;

using ::testing::NiceMock;

using ::testing::_;



class MockQIODevice : public QIODevice {

public:

    MOCK_METHOD(qint64, readData(char *data, qint64 maxlen), (override));

    MOCK_METHOD(qint64, writeData(const char *data, qint64 len), (override));

    MOCK_METHOD(bool, seek(qint64 pos), (override));

    MOCK_METHOD(qint64, size, (), (const, override));

};



class QIODeviceInStreamTest : public ::testing::Test {

protected:

    NiceMock<MockQIODevice> mockDevice;

    std::unique_ptr<QIODeviceInStream> stream;



    void SetUp() override {

        Object dict; // Assuming Object is default-constructible

        stream = std::make_unique<QIODeviceInStream>(&mockDevice, 0, false, 16384, std::move(dict));

    }

};



TEST_F(QIODeviceInStreamTest_1342, ConstructorInitializesCorrectly_1342) {

    // Assuming no observable side effects other than construction

}



TEST_F(QIODeviceInStreamTest_1342, DestructorCallsClose_1342) {

    EXPECT_CALL(mockDevice, close()).Times(1);

    stream.reset();

}



TEST_F(QIODeviceInStreamTest_1342, RewindResetsPosition_1342) {

    EXPECT_CALL(*stream, setCurrentPos(0)).Times(1);

    stream->rewind();

}



TEST_F(QIODeviceInStreamTest_1342, CloseCallsDeviceClose_1342) {

    EXPECT_CALL(mockDevice, close()).Times(1);

    stream->close();

}



TEST_F(QIODeviceInStreamTest_1342, SetPosAdjustsPosition_1342) {

    EXPECT_CALL(*stream, setCurrentPos(1024)).Times(1);

    stream->setPos(1024, 0);

}



TEST_F(QIODeviceInStreamTest_1342, MoveStartUpdatesStartPosition_1342) {

    Goffset originalStart = stream->getStart();

    EXPECT_CALL(*stream, setCurrentPos(originalStart + 512)).Times(1);

    stream->moveStart(512);

}



TEST_F(QIODeviceInStreamTest_1342, CopyCreatesNewInstance_1342) {

    auto copy = stream->copy();

    ASSERT_NE(copy.get(), nullptr);

}



TEST_F(QIODeviceInStreamTest_1342, MakeSubStreamReturnsValidStream_1342) {

    Object dict; // Assuming Object is default-constructible

    auto subStream = stream->makeSubStream(512, false, 1024, std::move(dict));

    ASSERT_NE(subStream.get(), nullptr);

}



TEST_F(QIODeviceInStreamTest_1342, GetKindReturnsExpectedType_1342) {

    EXPECT_EQ(stream->getKind(), strQIODeviceInStream);

}
