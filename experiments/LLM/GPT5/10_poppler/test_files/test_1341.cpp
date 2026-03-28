#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace Poppler {

    class MockIODevice : public QIODevice {
    public:
        MOCK_METHOD(void, close, (), (override));
    };

    class BaseConverterPrivateTest : public ::testing::Test {
    protected:
        BaseConverterPrivateTest() {
            baseConverterPrivate.document = nullptr;
            baseConverterPrivate.iodev = nullptr;
            baseConverterPrivate.ownIodev = true;
        }

        BaseConverterPrivate baseConverterPrivate;
        MockIODevice mockIODevice;
    };

    // Test Case: Verifying normal operation of closeDevice when ownIodev is true and iodev is not null
    TEST_F(BaseConverterPrivateTest, CloseDeviceWhenOwnIODevice_1341) {
        // Arrange
        baseConverterPrivate.iodev = &mockIODevice;

        // Expectation: The close method of iodev should be called
        EXPECT_CALL(mockIODevice, close()).Times(1);

        // Act
        baseConverterPrivate.closeDevice();

        // Assert: The iodev should be set to nullptr after close
        EXPECT_EQ(baseConverterPrivate.iodev, nullptr);
    }

    // Test Case: Verifying that nothing happens when ownIodev is false
    TEST_F(BaseConverterPrivateTest, CloseDeviceWhenNotOwnIODevice_1342) {
        // Arrange
        baseConverterPrivate.ownIodev = false;
        baseConverterPrivate.iodev = &mockIODevice;

        // Expectation: The close method of iodev should NOT be called because ownIodev is false
        EXPECT_CALL(mockIODevice, close()).Times(0);

        // Act
        baseConverterPrivate.closeDevice();

        // Assert: The iodev should remain unchanged
        EXPECT_EQ(baseConverterPrivate.iodev, &mockIODevice);
    }

    // Test Case: Verifying behavior when iodev is already null
    TEST_F(BaseConverterPrivateTest, CloseDeviceWhenIODeviceIsNull_1343) {
        // Arrange: iodev is already null, so nothing should happen
        baseConverterPrivate.iodev = nullptr;

        // Expectation: The close method of iodev should NOT be called
        EXPECT_CALL(mockIODevice, close()).Times(0);

        // Act
        baseConverterPrivate.closeDevice();

        // Assert: iodev should remain null
        EXPECT_EQ(baseConverterPrivate.iodev, nullptr);
    }

    // Test Case: Verifying that delete is called when closing the device
    TEST_F(BaseConverterPrivateTest, DeleteIODeviceWhenClosed_1344) {
        // Arrange
        baseConverterPrivate.iodev = &mockIODevice;

        // Expectation: The delete operator will be called on iodev after close
        EXPECT_CALL(mockIODevice, close()).Times(1);

        // Act
        baseConverterPrivate.closeDevice();

        // Assert: iodev should be null after delete
        EXPECT_EQ(baseConverterPrivate.iodev, nullptr);
    }
}