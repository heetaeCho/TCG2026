#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <QIODevice>
#include <QFile>

namespace Poppler {
    class BaseConverterPrivate {
    public:
        QString outputFileName;
        QIODevice *iodev = nullptr;
        bool ownIodev = true;

        QIODevice *openDevice() {
            if (!iodev) {
                Q_ASSERT(!outputFileName.isEmpty());
                auto *f = new QFile(outputFileName);
                iodev = f;
                ownIodev = true;
            }
            Q_ASSERT(iodev);
            if (!iodev->isOpen()) {
                if (!iodev->open(QIODevice::WriteOnly)) {
                    if (ownIodev) {
                        delete iodev;
                        iodev = nullptr;
                    } else {
                        return nullptr;
                    }
                }
            }
            return iodev;
        }
    };
}

class MockIODevice : public QIODevice {
public:
    MOCK_METHOD(bool, open, (QIODevice::OpenMode mode), (override));
    MOCK_METHOD(void, close, (), (override));
};

class BaseConverterPrivateTest_1340 : public testing::Test {
protected:
    Poppler::BaseConverterPrivate converter;
};

TEST_F(BaseConverterPrivateTest_1340, OpenDevice_NormalOperation_1340) {
    // Test the normal operation where openDevice succeeds.
    converter.outputFileName = "output.pdf";

    MockIODevice *mockIODevice = new MockIODevice();
    converter.iodev = mockIODevice;

    EXPECT_CALL(*mockIODevice, open(QIODevice::WriteOnly))
        .WillOnce(testing::Return(true));

    QIODevice *device = converter.openDevice();
    ASSERT_NE(device, nullptr);
}

TEST_F(BaseConverterPrivateTest_1340, OpenDevice_FailureToOpen_1340) {
    // Test the case where openDevice fails to open the device.
    converter.outputFileName = "output.pdf";

    MockIODevice *mockIODevice = new MockIODevice();
    converter.iodev = mockIODevice;

    EXPECT_CALL(*mockIODevice, open(QIODevice::WriteOnly))
        .WillOnce(testing::Return(false));

    QIODevice *device = converter.openDevice();
    ASSERT_EQ(device, nullptr);
}

TEST_F(BaseConverterPrivateTest_1340, OpenDevice_EmptyFileName_1340) {
    // Test the case where openDevice is called with an empty file name.
    converter.outputFileName = "";

    MockIODevice *mockIODevice = new MockIODevice();
    converter.iodev = mockIODevice;

    // Since outputFileName is empty, the device should not be opened.
    EXPECT_CALL(*mockIODevice, open(QIODevice::WriteOnly))
        .Times(0);

    QIODevice *device = converter.openDevice();
    ASSERT_EQ(device, nullptr);
}

TEST_F(BaseConverterPrivateTest_1340, OpenDevice_DeleteOnError_1340) {
    // Test that the device is deleted if an error occurs.
    converter.outputFileName = "output.pdf";

    MockIODevice *mockIODevice = new MockIODevice();
    converter.iodev = mockIODevice;

    EXPECT_CALL(*mockIODevice, open(QIODevice::WriteOnly))
        .WillOnce(testing::Return(false));

    QIODevice *device = converter.openDevice();
    ASSERT_EQ(device, nullptr);
    // Verify that the device is deleted after failure
    EXPECT_CALL(*mockIODevice, close()).Times(1);
}

TEST_F(BaseConverterPrivateTest_1340, OpenDevice_NoDeleteWhenNotOwned_1340) {
    // Test that the device is not deleted if it is not owned by the converter.
    converter.outputFileName = "output.pdf";
    converter.ownIodev = false;

    MockIODevice *mockIODevice = new MockIODevice();
    converter.iodev = mockIODevice;

    EXPECT_CALL(*mockIODevice, open(QIODevice::WriteOnly))
        .WillOnce(testing::Return(false));

    QIODevice *device = converter.openDevice();
    ASSERT_EQ(device, nullptr);
    // Ensure the device is not deleted
    EXPECT_CALL(*mockIODevice, close()).Times(0);
}