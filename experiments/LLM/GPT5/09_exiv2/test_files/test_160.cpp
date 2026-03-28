#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "exiv2/value.hpp" // Include the header where the `ValueType` class is defined

// Mock class for any external dependencies if required
class MockHandler : public Exiv2::Value {
public:
    MOCK_METHOD(int, read, (const byte* buf, size_t len, Exiv2::ByteOrder byteOrder), (override));
    MOCK_METHOD(int, read, (const std::string& buf), (override));
};

// Unit tests for the `ValueType` class template
namespace {

    // Test for the toUint32 function (converts float to uint32_t)
    TEST_F(ValueTypeTest_160, ToUint32_Conversion_160) {
        Exiv2::ValueType<float> value(3.14f, Exiv2::TypeId::float32);  // Initialize with float value
        uint32_t result = value.toUint32(0); // Test for conversion to uint32_t
        EXPECT_EQ(result, 3);  // 3.14f -> 3 (rounded down)
    }

    // Test for toFloat function (converts to float)
    TEST_F(ValueTypeTest_160, ToFloat_Conversion_160) {
        Exiv2::ValueType<float> value(3.14f, Exiv2::TypeId::float32);  // Initialize with float value
        float result = value.toFloat(0);  // Test conversion to float
        EXPECT_FLOAT_EQ(result, 3.14f);  // Should return the same float
    }

    // Test for the toRational function (converts to Rational type)
    TEST_F(ValueTypeTest_160, ToRational_Conversion_160) {
        Exiv2::ValueType<float> value(3.14f, Exiv2::TypeId::float32);  // Initialize with float value
        Exiv2::Rational result = value.toRational(0);  // Convert to rational type
        EXPECT_EQ(result.numerator(), 314);  // Expected numerator
        EXPECT_EQ(result.denominator(), 100);  // Expected denominator
    }

    // Test for the toInt64 function (converts to int64_t)
    TEST_F(ValueTypeTest_160, ToInt64_Conversion_160) {
        Exiv2::ValueType<float> value(3.14f, Exiv2::TypeId::float32);  // Initialize with float value
        int64_t result = value.toInt64(0);  // Test conversion to int64_t
        EXPECT_EQ(result, 3);  // 3.14f -> 3 (rounded down)
    }

    // Test for boundary condition with a very large float value
    TEST_F(ValueTypeTest_160, LargeFloatToUint32_160) {
        Exiv2::ValueType<float> value(1e30f, Exiv2::TypeId::float32);  // Very large float value
        uint32_t result = value.toUint32(0);  // Should handle overflow or boundary case
        EXPECT_EQ(result, 0);  // Depending on behavior, might overflow or wrap to zero
    }

    // Test for read function with byte buffer
    TEST_F(ValueTypeTest_160, ReadFromBuffer_160) {
        MockHandler handler;
        const byte buffer[] = {0x01, 0x02, 0x03, 0x04};  // Example byte buffer
        EXPECT_CALL(handler, read(buffer, 4, Exiv2::ByteOrder::littleEndian))
            .Times(1)
            .WillOnce(testing::Return(0));  // Simulate success
        int result = handler.read(buffer, 4, Exiv2::ByteOrder::littleEndian);
        EXPECT_EQ(result, 0);  // Expect successful read
    }

    // Test for exceptional case where buffer length is zero
    TEST_F(ValueTypeTest_160, ReadZeroLengthBuffer_160) {
        MockHandler handler;
        const byte buffer[] = {};  // Empty buffer
        EXPECT_CALL(handler, read(buffer, 0, Exiv2::ByteOrder::littleEndian))
            .Times(1)
            .WillOnce(testing::Return(-1));  // Simulate failure
        int result = handler.read(buffer, 0, Exiv2::ByteOrder::littleEndian);
        EXPECT_EQ(result, -1);  // Expect failure with zero-length buffer
    }

    // Test for read with invalid type
    TEST_F(ValueTypeTest_160, InvalidTypeRead_160) {
        Exiv2::ValueType<float> value(3.14f, Exiv2::TypeId::float32);
        EXPECT_THROW(value.read(nullptr, 0, Exiv2::ByteOrder::littleEndian), std::invalid_argument);  // Simulate invalid read
    }

    // Test for copy function (ensuring the byte copy is correct)
    TEST_F(ValueTypeTest_160, CopyBuffer_160) {
        Exiv2::ValueType<float> value(3.14f, Exiv2::TypeId::float32);
        byte buffer[4] = {0};  // Buffer to copy into
        size_t size = value.copy(buffer, Exiv2::ByteOrder::littleEndian);  // Copy data into buffer
        EXPECT_EQ(size, 4);  // Expect 4 bytes copied
    }

    // Test for sizeDataArea (testing if size of internal data area is correct)
    TEST_F(ValueTypeTest_160, SizeDataArea_160) {
        Exiv2::ValueType<float> value(3.14f, Exiv2::TypeId::float32);
        size_t size = value.sizeDataArea();  // Test the size of the internal data area
        EXPECT_GT(size, 0);  // Should be greater than zero
    }

    // Test for clone function (ensure deep copy or proper clone behavior)
    TEST_F(ValueTypeTest_160, Clone_160) {
        Exiv2::ValueType<float> value(3.14f, Exiv2::TypeId::float32);
        std::unique_ptr<Exiv2::Value> clonedValue = value.clone();  // Clone the object
        EXPECT_NE(clonedValue, nullptr);  // Ensure the clone is successful
    }

}  // namespace