#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-converter-private.h"



using namespace Poppler;

using ::testing::NiceMock;

using ::testing::_;



class MockQIODevice : public QIODevice {

public:

    MOCK_METHOD(void, close, (), (override));

};



class BaseConverterPrivateTest_1341 : public ::testing::Test {

protected:

    void SetUp() override {

        mockIodev = new NiceMock<MockQIODevice>;

        baseConverterPrivate.iodev = mockIodev;

        baseConverterPrivate.ownIodev = true;

    }



    void TearDown() override {

        delete mockIodev;

    }



    BaseConverterPrivate baseConverterPrivate;

    MockQIODevice* mockIodev;

};



TEST_F(BaseConverterPrivateTest_1341, CloseDevice_CallsCloseOnOwnedDevice_1341) {

    EXPECT_CALL(*mockIodev, close()).Times(1);

    baseConverterPrivate.closeDevice();

}



TEST_F(BaseConverterPrivateTest_1341, CloseDevice_DeletesOwnedDevice_1341) {

    EXPECT_CALL(*mockIodev, close()).WillOnce(::testing::Return());

    baseConverterPrivate.closeDevice();

    EXPECT_EQ(baseConverterPrivate.iodev, nullptr);

}



TEST_F(BaseConverterPrivateTest_1341, CloseDevice_DoesNotDeleteNonOwnedDevice_1341) {

    baseConverterPrivate.ownIodev = false;

    baseConverterPrivate.closeDevice();

    EXPECT_NE(baseConverterPrivate.iodev, nullptr);

}



TEST_F(BaseConverterPrivateTest_1341, CloseDevice_SetsIODeviceToNullptrAfterDeletion_1341) {

    EXPECT_CALL(*mockIodev, close()).WillOnce(::testing::Return());

    baseConverterPrivate.closeDevice();

    EXPECT_EQ(baseConverterPrivate.iodev, nullptr);

}



TEST_F(BaseConverterPrivateTest_1341, CloseDevice_NoopIfIODeviceIsNull_1341) {

    baseConverterPrivate.iodev = nullptr;

    baseConverterPrivate.closeDevice();  // Should not crash or call close

}
