#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/qt5/src/poppler-qiodeviceoutstream.h"
#include "./TestProjects/poppler/qt5/src/poppler-qiodeviceoutstream-private.h"

using ::testing::_;
using ::testing::Mock;
using ::testing::Return;

class MockQIODevice : public QIODevice {
public:
    MOCK_METHOD(Goffset, pos, (), (const, override));
    MOCK_METHOD(void, close, (), (override));
    MOCK_METHOD(size_t, write, (int data), (override));
    MOCK_METHOD(void, printf, (const char *format), (override));
};

class QIODeviceOutStreamTest_1260 : public ::testing::Test {
protected:
    MockQIODevice mockDevice;
    Poppler::QIODeviceOutStream outStream{&mockDevice};

    QIODeviceOutStreamTest_1260() = default;

    void SetUp() override {
        // Initialize or set up mocks if needed
    }

    void TearDown() override {
        // Cleanup if necessary
    }
};

// Normal Operation: Test getPos() method
TEST_F(QIODeviceOutStreamTest_1260, GetPosReturnsCorrectPosition_1260) {
    // Arrange: Mock the behavior of pos()
    EXPECT_CALL(mockDevice, pos()).WillOnce(Return(100));

    // Act: Call the method
    Goffset pos = outStream.getPos();

    // Assert: Verify the returned position
    EXPECT_EQ(pos, 100);
}

// Boundary Condition: Test getPos() when position is zero
TEST_F(QIODeviceOutStreamTest_1260, GetPosReturnsZeroPosition_1261) {
    // Arrange: Mock the behavior of pos()
    EXPECT_CALL(mockDevice, pos()).WillOnce(Return(0));

    // Act: Call the method
    Goffset pos = outStream.getPos();

    // Assert: Verify the returned position is zero
    EXPECT_EQ(pos, 0);
}

// Normal Operation: Test the close() method
TEST_F(QIODeviceOutStreamTest_1262, CloseCallsDeviceClose_1262) {
    // Arrange: Mock the behavior of close
    EXPECT_CALL(mockDevice, close()).Times(1);

    // Act: Call the close method
    outStream.close();

    // Assert: Verify that close() was called
    Mock::VerifyAndClearExpectations(&mockDevice);
}

// Exceptional Case: Test write() method with invalid data
TEST_F(QIODeviceOutStreamTest_1263, WriteHandlesInvalidData_1263) {
    // Arrange: Mock the behavior of write to return 0 (failure)
    EXPECT_CALL(mockDevice, write(_)).WillOnce(Return(0));

    // Act: Call write with invalid data (for example, -1)
    size_t result = outStream.write(-1);

    // Assert: Verify that write() returned 0 (failure)
    EXPECT_EQ(result, 0);
}

// Normal Operation: Test printf() method
TEST_F(QIODeviceOutStreamTest_1264, PrintfWritesFormattedOutput_1264) {
    // Arrange: Mock printf to verify it gets called
    EXPECT_CALL(mockDevice, printf("Hello, World!")).Times(1);

    // Act: Call printf with the string
    outStream.printf("Hello, World!");

    // Assert: Verify printf was called correctly
    Mock::VerifyAndClearExpectations(&mockDevice);
}