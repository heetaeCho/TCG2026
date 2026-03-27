#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <QIODevice>

#include <poppler-qiodeviceoutstream-private.h>



using namespace Poppler;

using ::testing::_;

using ::testing::InSequence;

using ::testing::InvokeWithoutArgs;

using ::testing::Return;



class QIODeviceOutStreamTest : public ::testing::Test {

protected:

    QIODeviceOutStreamTest() : device(new QBuffer()), stream(device) {

        device->open(QIODevice::WriteOnly);

    }



    ~QIODeviceOutStreamTest() override {

        delete device;

    }



    QIODevice* device;

    QIODeviceOutStream stream;

};



TEST_F(QIODeviceOutStreamTest_1263, WriteSimpleString_1263) {

    stream.printf("Hello");

    EXPECT_EQ(device->readAll(), QByteArray("Hello"));

}



TEST_F(QIODeviceOutStreamTest_1263, WriteFormattedString_1263) {

    stream.printf("%s %d", "Number", 42);

    EXPECT_EQ(device->readAll(), QByteArray("Number 42"));

}



TEST_F(QIODeviceOutStreamTest_1263, BoundaryConditionEmptyString_1263) {

    stream.printf("");

    EXPECT_EQ(device->readAll(), QByteArray(""));

}



TEST_F(QIODeviceOutStreamTest_1263, BoundaryConditionSingleCharacter_1263) {

    stream.printf("%c", 'A');

    EXPECT_EQ(device->readAll(), QByteArray("A"));

}



TEST_F(QIODeviceOutStreamTest_1263, ExceptionalCaseNullFormatString_1263) {

    // This test is more theoretical as passing a nullptr to printf is undefined behavior.

    // However, we can still check if the application crashes or behaves unexpectedly.

    stream.printf(nullptr);

    EXPECT_EQ(device->readAll(), QByteArray(""));

}



TEST_F(QIODeviceOutStreamTest_1263, ExternalInteractionWithDevice_1263) {

    ::testing::StrictMock<::testing::NiceMock<QIODeviceMock>> mockDevice;

    QIODeviceOutStream mockStream(&mockDevice);



    EXPECT_CALL(mockDevice, write("Hello", 5)).WillOnce(Return(5));

    mockStream.printf("Hello");

}



class QIODeviceMock : public QIODevice {

public:

    MOCK_METHOD(qint64, write, (const char *data, qint64 maxlen), (override));

};



TEST_F(QIODeviceOutStreamTest_1263, ExternalInteractionWithDeviceMultipleWrites_1263) {

    ::testing::StrictMock<::testing::NiceMock<QIODeviceMock>> mockDevice;

    QIODeviceOutStream mockStream(&mockDevice);



    InSequence s;

    EXPECT_CALL(mockDevice, write("Hello", 5)).WillOnce(Return(5));

    EXPECT_CALL(mockDevice, write(" ", 1)).WillOnce(Return(1));

    EXPECT_CALL(mockDevice, write("World", 5)).WillOnce(Return(5));



    mockStream.printf("%s %s", "Hello", "World");

}
