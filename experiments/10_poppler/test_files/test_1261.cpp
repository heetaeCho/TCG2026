#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-qiodeviceoutstream-private.h"

#include <QIODevice>



using namespace testing;

using namespace Poppler;



class MockQIODevice : public QIODevice {

public:

    MOCK_METHOD1(putChar, bool(char c));

};



class QIODeviceOutStreamTest_1261 : public ::testing::Test {

protected:

    void SetUp() override {

        mockDevice = new NiceMock<MockQIODevice>;

        stream.reset(new QIODeviceOutStream(mockDevice));

    }



    void TearDown() override {

        stream.reset();

        delete mockDevice;

    }



    MockQIODevice* mockDevice;

    std::unique_ptr<QIODeviceOutStream> stream;

};



TEST_F(QIODeviceOutStreamTest_1261, PutCharIsCalledWithCorrectCharacter_1261) {

    EXPECT_CALL(*mockDevice, putChar('a')).Times(1);

    stream->put('a');

}



TEST_F(QIODeviceOutStreamTest_1261, PutCharIsNotCalledOnEmptyPut_1261) {

    EXPECT_CALL(*mockDevice, putChar(_)).Times(0);

}



TEST_F(QIODeviceOutStreamTest_1261, BoundaryCondition_PutWithNullCharacter_1261) {

    EXPECT_CALL(*mockDevice, putChar('\0')).Times(1);

    stream->put('\0');

}



TEST_F(QIODeviceOutStreamTest_1261, ExceptionalCase_DeviceIsNull_1261) {

    stream.reset(new QIODeviceOutStream(nullptr));

    EXPECT_DEATH(stream->put('a'), ".*");

}
