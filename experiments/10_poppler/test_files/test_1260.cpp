#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-qiodeviceoutstream-private.h"

#include <QIODevice>



using namespace Poppler;

using ::testing::_;

using ::testing::Return;



class MockQIODevice : public QIODevice {

public:

    MOCK_METHOD(qint64, pos, (), (const override));

    MOCK_METHOD(bool, open, (OpenMode mode), (override));

};



class QIODeviceOutStreamTest_1260 : public ::testing::Test {

protected:

    void SetUp() override {

        mockDevice = new MockQIODevice();

        stream = new QIODeviceOutStream(mockDevice);

    }



    void TearDown() override {

        delete stream;

        delete mockDevice;

    }



    MockQIODevice* mockDevice;

    QIODeviceOutStream* stream;

};



TEST_F(QIODeviceOutStreamTest_1260, GetPosReturnsCorrectPosition_1260) {

    EXPECT_CALL(*mockDevice, pos()).WillOnce(Return(42));

    EXPECT_EQ(stream->getPos(), 42);

}



TEST_F(QIODeviceOutStreamTest_1260, GetPosBoundaryConditionZero_1260) {

    EXPECT_CALL(*mockDevice, pos()).WillOnce(Return(0));

    EXPECT_EQ(stream->getPos(), 0);

}



TEST_F(QIODeviceOutStreamTest_1260, GetPosBoundaryConditionMax_1260) {

    EXPECT_CALL(*mockDevice, pos()).WillOnce(Return(std::numeric_limits<qint64>::max()));

    EXPECT_EQ(stream->getPos(), static_cast<Goffset>(std::numeric_limits<qint64>::max()));

}



TEST_F(QIODeviceOutStreamTest_1260, CloseInvokesIODeviceClose_1260) {

    EXPECT_CALL(*mockDevice, open(_)).WillOnce(Return(true));

    mockDevice->open(QIODevice::WriteOnly);

    EXPECT_CALL(*mockDevice, close()).Times(1);

    stream->close();

}



TEST_F(QIODeviceOutStreamTest_1260, PutCharInvokesIODeviceWrite_1260) {

    EXPECT_CALL(*mockDevice, write(_, _)).WillOnce(Return(1));

    mockDevice->open(QIODevice::WriteOnly);

    stream->put('a');

}
