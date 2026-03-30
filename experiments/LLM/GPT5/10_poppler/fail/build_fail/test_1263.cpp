#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "poppler-qiodeviceoutstream.h"
#include "poppler-qiodeviceoutstream-private.h"

// Mock class for QIODevice
class MockQIODevice : public QIODevice {
public:
    MOCK_METHOD(size_t, write, (const char* data, size_t maxSize), (override));
    MOCK_METHOD(void, close, (), (override));
    MOCK_METHOD(qint64, pos, (), (const, override));
};

// Test for the constructor and printf function
TEST_F(QIODeviceOutStreamTest_1263, printfWritesCorrectData_1263) {
    MockQIODevice mockDevice;
    QIODeviceOutStream outStream(&mockDevice);

    const char* testString = "Test message %d";
    const char* expectedOutput = "Test message 42";

    // Expect that write will be called with the correct string
    EXPECT_CALL(mockDevice, write(testing::StrEq(expectedOutput), strlen(expectedOutput)))
        .WillOnce(testing::Return(strlen(expectedOutput)));

    // Call the printf method
    outStream.printf(testString, 42);
}

// Test for exceptional or error cases (invalid input to printf)
TEST_F(QIODeviceOutStreamTest_1263, printfHandlesInvalidInput_1263) {
    MockQIODevice mockDevice;
    QIODeviceOutStream outStream(&mockDevice);

    const char* invalidFormat = nullptr;

    // Expect no write to occur when invalid input is passed
    EXPECT_CALL(mockDevice, write(testing::_, testing::_)).Times(0);

    // Call the printf method with invalid input
    outStream.printf(invalidFormat);
}

// Test for the close function
TEST_F(QIODeviceOutStreamTest_1263, closeClosesDevice_1263) {
    MockQIODevice mockDevice;
    QIODeviceOutStream outStream(&mockDevice);

    // Expect the close method to be called
    EXPECT_CALL(mockDevice, close()).Times(1);

    // Call the close method of the QIODeviceOutStream
    outStream.close();
}

// Test for the getPos function
TEST_F(QIODeviceOutStreamTest_1263, getPosReturnsCorrectPosition_1263) {
    MockQIODevice mockDevice;
    QIODeviceOutStream outStream(&mockDevice);

    // Set up the expected behavior for pos
    EXPECT_CALL(mockDevice, pos()).WillOnce(testing::Return(100));

    // Verify the position returned by getPos
    EXPECT_EQ(outStream.getPos(), 100);
}

// Test for the put function
TEST_F(QIODeviceOutStreamTest_1263, putWritesCharToDevice_1263) {
    MockQIODevice mockDevice;
    QIODeviceOutStream outStream(&mockDevice);

    const char testChar = 'A';

    // Expect the put method to result in a write call to the device
    EXPECT_CALL(mockDevice, write(testing::_, testing::_)).WillOnce(testing::Return(1));

    // Call put method
    outStream.put(testChar);
}

// Test for boundary conditions with invalid character in put
TEST_F(QIODeviceOutStreamTest_1263, putHandlesInvalidCharacter_1263) {
    MockQIODevice mockDevice;
    QIODeviceOutStream outStream(&mockDevice);

    const char testChar = '\0';  // Null character

    // Expect the put method to not call write for invalid input
    EXPECT_CALL(mockDevice, write(testing::_, testing::_)).Times(0);

    // Call put method with null character
    outStream.put(testChar);
}