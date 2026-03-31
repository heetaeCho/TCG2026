#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <QIODevice>
#include <QFile>
#include <QBuffer>
#include <QTemporaryFile>
#include <QTemporaryDir>
#include <QString>

// Include the necessary headers
#include "poppler-converter-private.h"

using namespace Poppler;

class BaseConverterPrivateTest_1340 : public ::testing::Test {
protected:
    void SetUp() override {
        tempDir = new QTemporaryDir();
        ASSERT_TRUE(tempDir->isValid());
    }

    void TearDown() override {
        delete tempDir;
    }

    QTemporaryDir *tempDir = nullptr;
};

// Test that openDevice returns a valid device when outputFileName is set
TEST_F(BaseConverterPrivateTest_1340, OpenDeviceWithValidFileName_1340) {
    BaseConverterPrivate priv;
    QString filePath = tempDir->filePath("test_output.pdf");
    priv.outputFileName = filePath;
    priv.iodev = nullptr;
    priv.ownIodev = true;

    QIODevice *dev = priv.openDevice();
    ASSERT_NE(dev, nullptr);
    EXPECT_TRUE(dev->isOpen());
    EXPECT_TRUE(dev->isWritable());

    priv.closeDevice();
}

// Test that openDevice uses an already set QIODevice
TEST_F(BaseConverterPrivateTest_1340, OpenDeviceWithExternalIODevice_1340) {
    BaseConverterPrivate priv;
    QBuffer buffer;
    priv.iodev = &buffer;
    priv.ownIodev = false;

    QIODevice *dev = priv.openDevice();
    ASSERT_NE(dev, nullptr);
    EXPECT_TRUE(dev->isOpen());
    EXPECT_EQ(dev, &buffer);

    priv.closeDevice();
}

// Test that openDevice returns same device if already open
TEST_F(BaseConverterPrivateTest_1340, OpenDeviceAlreadyOpen_1340) {
    BaseConverterPrivate priv;
    QBuffer buffer;
    buffer.open(QIODevice::WriteOnly);
    priv.iodev = &buffer;
    priv.ownIodev = false;

    QIODevice *dev = priv.openDevice();
    ASSERT_NE(dev, nullptr);
    EXPECT_TRUE(dev->isOpen());
    EXPECT_EQ(dev, &buffer);

    priv.closeDevice();
}

// Test that openDevice with an external device that fails to open returns nullptr
TEST_F(BaseConverterPrivateTest_1340, OpenDeviceExternalFailsToOpen_1340) {
    BaseConverterPrivate priv;
    // Use a QFile with an invalid path that can't be opened for writing
    QFile invalidFile("/nonexistent_dir_abc123/nonexistent_subdir/file.pdf");
    priv.iodev = &invalidFile;
    priv.ownIodev = false;

    QIODevice *dev = priv.openDevice();
    // When ownIodev is false and open fails, it returns nullptr
    EXPECT_EQ(dev, nullptr);
}

// Test that openDevice with invalid fileName (own device) handles failure
TEST_F(BaseConverterPrivateTest_1340, OpenDeviceWithInvalidFileName_1340) {
    BaseConverterPrivate priv;
    priv.outputFileName = QString("/nonexistent_dir_xyz789/impossible_path/output.pdf");
    priv.iodev = nullptr;
    priv.ownIodev = true;

    QIODevice *dev = priv.openDevice();
    // When ownIodev is true and open fails, it deletes iodev and sets it to nullptr
    // The device pointer returned should reflect this
    // Based on the code: if open fails and ownIodev, it deletes and nulls iodev
    // but doesn't return - this means it falls through to return iodev which is nullptr
    // Actually looking at the code more carefully, after the delete block there's no return,
    // so it falls to "return iodev" which is nullptr
    EXPECT_EQ(dev, nullptr);
}

// Test closeDevice after openDevice with file
TEST_F(BaseConverterPrivateTest_1340, CloseDeviceAfterOpen_1340) {
    BaseConverterPrivate priv;
    QString filePath = tempDir->filePath("test_close.pdf");
    priv.outputFileName = filePath;
    priv.iodev = nullptr;
    priv.ownIodev = true;

    QIODevice *dev = priv.openDevice();
    ASSERT_NE(dev, nullptr);
    EXPECT_TRUE(dev->isOpen());

    priv.closeDevice();
    // After closeDevice, the device should be cleaned up
    // We can verify by checking iodev is reset
    EXPECT_EQ(priv.iodev, nullptr);
}

// Test closeDevice with external device (ownIodev = false)
TEST_F(BaseConverterPrivateTest_1340, CloseDeviceExternalNotOwned_1340) {
    BaseConverterPrivate priv;
    QBuffer buffer;
    priv.iodev = &buffer;
    priv.ownIodev = false;

    QIODevice *dev = priv.openDevice();
    ASSERT_NE(dev, nullptr);

    priv.closeDevice();
    // External device should not be deleted, but may be closed
}

// Test multiple opens return the same device
TEST_F(BaseConverterPrivateTest_1340, MultipleOpensReturnSameDevice_1340) {
    BaseConverterPrivate priv;
    QBuffer buffer;
    buffer.open(QIODevice::WriteOnly);
    priv.iodev = &buffer;
    priv.ownIodev = false;

    QIODevice *dev1 = priv.openDevice();
    QIODevice *dev2 = priv.openDevice();
    EXPECT_EQ(dev1, dev2);
    EXPECT_EQ(dev1, &buffer);

    priv.closeDevice();
}

// Test that a writable file is actually created on disk
TEST_F(BaseConverterPrivateTest_1340, FileCreatedOnDisk_1340) {
    BaseConverterPrivate priv;
    QString filePath = tempDir->filePath("created_file.pdf");
    priv.outputFileName = filePath;
    priv.iodev = nullptr;
    priv.ownIodev = true;

    QIODevice *dev = priv.openDevice();
    ASSERT_NE(dev, nullptr);

    // Write some data
    QByteArray testData("test data");
    dev->write(testData);

    priv.closeDevice();

    // Verify the file exists and has the data
    QFile checkFile(filePath);
    ASSERT_TRUE(checkFile.exists());
    ASSERT_TRUE(checkFile.open(QIODevice::ReadOnly));
    QByteArray readData = checkFile.readAll();
    EXPECT_EQ(readData, testData);
    checkFile.close();
}
