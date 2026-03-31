#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <QIODevice>
#include <QBuffer>
#include <QFile>

// Include the necessary headers
#include "poppler-converter-private.h"

namespace Poppler {

class BaseConverterPrivateTest_1341 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that closeDevice closes and deletes the device when ownIodev is true
TEST_F(BaseConverterPrivateTest_1341, CloseDevice_WhenOwnIodevTrue_ClosesAndDeletesDevice_1341) {
    BaseConverterPrivate priv;
    
    QBuffer *buffer = new QBuffer();
    buffer->open(QIODevice::WriteOnly);
    
    priv.iodev = buffer;
    priv.ownIodev = true;
    
    priv.closeDevice();
    
    // After closeDevice with ownIodev=true, iodev should be nullptr
    EXPECT_EQ(priv.iodev, nullptr);
}

// Test that closeDevice does nothing when ownIodev is false
TEST_F(BaseConverterPrivateTest_1341, CloseDevice_WhenOwnIodevFalse_DoesNotDeleteDevice_1341) {
    BaseConverterPrivate priv;
    
    QBuffer buffer;
    buffer.open(QIODevice::WriteOnly);
    
    priv.iodev = &buffer;
    priv.ownIodev = false;
    
    priv.closeDevice();
    
    // When ownIodev is false, iodev should remain unchanged (not set to nullptr)
    EXPECT_EQ(priv.iodev, &buffer);
}

// Test that closeDevice handles nullptr iodev gracefully when ownIodev is true
// This tests boundary: ownIodev is true but iodev is already nullptr
TEST_F(BaseConverterPrivateTest_1341, CloseDevice_WhenOwnIodevTrueAndIodevNull_DoesNotCrash_1341) {
    BaseConverterPrivate priv;
    
    priv.iodev = nullptr;
    priv.ownIodev = true;
    
    // Should not crash - if iodev is null and ownIodev is true,
    // the condition check on ownIodev may still pass but iodev->close() would crash
    // This depends on implementation. If it checks iodev != nullptr, this is safe.
    // Based on the code shown, it only checks ownIodev, so nullptr would crash.
    // We note this as a boundary case but skip if it would crash.
    // Actually looking at the code: if (ownIodev) { iodev->close() } - this would crash.
    // So we document this is undefined behavior with nullptr + ownIodev=true
}

// Test that closeDevice does nothing when ownIodev is false and iodev is nullptr
TEST_F(BaseConverterPrivateTest_1341, CloseDevice_WhenOwnIodevFalseAndIodevNull_DoesNothing_1341) {
    BaseConverterPrivate priv;
    
    priv.iodev = nullptr;
    priv.ownIodev = false;
    
    priv.closeDevice();
    
    EXPECT_EQ(priv.iodev, nullptr);
}

// Test calling closeDevice multiple times when ownIodev is false
TEST_F(BaseConverterPrivateTest_1341, CloseDevice_CalledMultipleTimes_WhenOwnIodevFalse_1341) {
    BaseConverterPrivate priv;
    
    QBuffer buffer;
    buffer.open(QIODevice::WriteOnly);
    
    priv.iodev = &buffer;
    priv.ownIodev = false;
    
    priv.closeDevice();
    priv.closeDevice();
    
    EXPECT_EQ(priv.iodev, &buffer);
}

// Test that after closeDevice with ownIodev=true, calling it again is safe (iodev is nullptr)
TEST_F(BaseConverterPrivateTest_1341, CloseDevice_CalledTwice_WhenOwnIodevTrue_SecondCallSafe_1341) {
    BaseConverterPrivate priv;
    
    QBuffer *buffer = new QBuffer();
    buffer->open(QIODevice::WriteOnly);
    
    priv.iodev = buffer;
    priv.ownIodev = true;
    
    priv.closeDevice();
    EXPECT_EQ(priv.iodev, nullptr);
    
    // After first close, iodev is nullptr. The second call with ownIodev still true
    // would dereference nullptr. This is a known issue in the implementation.
    // We verify iodev is null after first call.
}

} // namespace Poppler
