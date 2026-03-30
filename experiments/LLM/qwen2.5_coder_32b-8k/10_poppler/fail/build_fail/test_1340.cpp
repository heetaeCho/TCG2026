#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <QFile>

#include <QTemporaryFile>

#include <QIODevice>



// Mock QIODevice for testing purposes

class MockQIODevice : public QIODevice {

public:

    MOCK_METHOD(bool, open, (QIODevice::OpenMode mode), override);

    MOCK_METHOD(void, close, (), override);

};



// Test fixture class

class BaseConverterPrivateTest_1340 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup any common state before tests

        baseConverterPrivate = new Poppler::BaseConverterPrivate();

    }



    void TearDown() override {

        // Cleanup after each test

        delete baseConverterPrivate;

    }



    Poppler::BaseConverterPrivate* baseConverterPrivate;

};



// Test normal operation with a valid file name

TEST_F(BaseConverterPrivateTest_1340, OpenDevice_ValidFileName_1340) {

    QTemporaryFile tempFile;

    ASSERT_TRUE(tempFile.open());



    baseConverterPrivate->outputFileName = tempFile.fileName();

    auto* device = baseConverterPrivate->openDevice();



    EXPECT_NE(device, nullptr);

    EXPECT_EQ(device->isOpen(), true);

}



// Test boundary condition with an empty file name

TEST_F(BaseConverterPrivateTest_1340, OpenDevice_EmptyFileName_1340) {

    baseConverterPrivate->outputFileName = "";

    auto* device = baseConverterPrivate->openDevice();



    EXPECT_EQ(device, nullptr);

}



// Test exceptional case where the QFile cannot be opened

TEST_F(BaseConverterPrivateTest_1340, OpenDevice_FileOpenFailed_1340) {

    MockQIODevice mockDevice;

    ON_CALL(mockDevice, open(_)).WillByDefault(testing::Return(false));



    baseConverterPrivate->iodev = &mockDevice;

    auto* device = baseConverterPrivate->openDevice();



    EXPECT_EQ(device, nullptr);

}



// Test that the device is closed when it is owned by BaseConverterPrivate

TEST_F(BaseConverterPrivateTest_1340, OpenDevice_OwnedDeviceClosedOnFailure_1340) {

    MockQIODevice mockDevice;

    ON_CALL(mockDevice, open(_)).WillByDefault(testing::Return(false));



    baseConverterPrivate->iodev = &mockDevice;

    EXPECT_CALL(mockDevice, close()).Times(1);



    auto* device = baseConverterPrivate->openDevice();

    EXPECT_EQ(device, nullptr);

}



// Test that the device is not closed when it is not owned by BaseConverterPrivate

TEST_F(BaseConverterPrivateTest_1340, OpenDevice_NotOwnedDeviceNotClosedOnFailure_1340) {

    MockQIODevice mockDevice;

    ON_CALL(mockDevice, open(_)).WillByDefault(testing::Return(false));



    baseConverterPrivate->iodev = &mockDevice;

    baseConverterPrivate->ownIodev = false;

    EXPECT_CALL(mockDevice, close()).Times(0);



    auto* device = baseConverterPrivate->openDevice();

    EXPECT_EQ(device, nullptr);

}
