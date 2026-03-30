#include <gtest/gtest.h>
#include "exiv2/value.hpp"

// Mocking required dependencies
class MockByteOrder {
public:
    MOCK_METHOD(int, getByteOrder, (), (const));
};

// Test suite for `Exiv2::toData`
namespace Exiv2 {

class ToDataTest_143 : public ::testing::Test {
protected:
    // Setup and teardown can be added here if needed for mock dependencies
    void SetUp() override {
        // Any setup code if required
    }

    void TearDown() override {
        // Any cleanup code if required
    }
};

// Test normal operation for toData function
TEST_F(ToDataTest_143, NormalOperation_143) {
    byte buffer[10];
    int32_t value = 42;
    ByteOrder byteOrder;

    // We expect l2Data to be called within toData with correct arguments
    EXPECT_CALL(byteOrder, getByteOrder()).WillOnce(testing::Return(ByteOrder::LittleEndian));
    size_t result = Exiv2::toData(buffer, value, byteOrder);

    EXPECT_GT(result, 0);  // Ensure that data was written to buffer
}

// Test boundary condition with minimum byte buffer size
TEST_F(ToDataTest_143, BoundaryCondition_MinBufferSize_143) {
    byte buffer[1];  // Small buffer
    int32_t value = 1;
    ByteOrder byteOrder;

    // Mock byte order method
    EXPECT_CALL(byteOrder, getByteOrder()).WillOnce(testing::Return(ByteOrder::BigEndian));

    size_t result = Exiv2::toData(buffer, value, byteOrder);
    
    EXPECT_EQ(result, 1);  // Expect result size to match the buffer size
}

// Test boundary condition with large value
TEST_F(ToDataTest_143, BoundaryCondition_LargeValue_143) {
    byte buffer[4];
    int32_t value = 0x7FFFFFFF;  // Maximum 32-bit value
    ByteOrder byteOrder;

    EXPECT_CALL(byteOrder, getByteOrder()).WillOnce(testing::Return(ByteOrder::LittleEndian));

    size_t result = Exiv2::toData(buffer, value, byteOrder);

    EXPECT_EQ(result, sizeof(int32_t));  // Ensure result matches size of an int32_t
}

// Test exceptional case: invalid buffer
TEST_F(ToDataTest_143, Exception_InvalidBuffer_143) {
    byte* buffer = nullptr;
    int32_t value = 42;
    ByteOrder byteOrder;

    EXPECT_CALL(byteOrder, getByteOrder()).WillOnce(testing::Return(ByteOrder::LittleEndian));

    size_t result = Exiv2::toData(buffer, value, byteOrder);

    EXPECT_EQ(result, 0);  // Expect 0 when buffer is invalid
}

// Test exceptional case: invalid byte order
TEST_F(ToDataTest_143, Exception_InvalidByteOrder_143) {
    byte buffer[10];
    int32_t value = 10;
    ByteOrder byteOrder;

    // Simulate an invalid ByteOrder scenario
    EXPECT_CALL(byteOrder, getByteOrder()).WillOnce(testing::Return(ByteOrder::Invalid));

    size_t result = Exiv2::toData(buffer, value, byteOrder);

    EXPECT_EQ(result, 0);  // Expect 0 for invalid byte order
}

}  // namespace Exiv2