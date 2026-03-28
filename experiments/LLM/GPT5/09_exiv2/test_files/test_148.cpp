#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "exiv2/value.hpp"

namespace Exiv2 {

class ValueTypeTest_148 : public testing::Test {
protected:
    // Set up any shared test objects here.
    // For example, initializing a ValueType for a certain type
    ValueType<int> valueInt;
    ValueType<double> valueDouble;
};

TEST_F(ValueTypeTest_148, Constructor_IntType_148) {
    // Test construction of ValueType with int type
    EXPECT_EQ(valueInt.typeId(), TypeId::Int);
}

TEST_F(ValueTypeTest_148, Constructor_DoubleType_148) {
    // Test construction of ValueType with double type
    EXPECT_EQ(valueDouble.typeId(), TypeId::Double);
}

TEST_F(ValueTypeTest_148, Read_Buffer_IntType_148) {
    const byte buf[] = { 0, 0, 0, 1 };
    int len = sizeof(buf);
    ByteOrder byteOrder = ByteOrder::BigEndian;
    
    // Verify read functionality for int type
    EXPECT_EQ(valueInt.read(buf, len, byteOrder), 0);
    EXPECT_EQ(valueInt.count(), 1);  // Assuming the buffer contains one int.
}

TEST_F(ValueTypeTest_148, Read_Buffer_DoubleType_148) {
    const byte buf[] = { 0, 0, 0, 0, 0, 0, 240, 63 };  // 1.0 as double
    int len = sizeof(buf);
    ByteOrder byteOrder = ByteOrder::BigEndian;
    
    // Verify read functionality for double type
    EXPECT_EQ(valueDouble.read(buf, len, byteOrder), 0);
    EXPECT_EQ(valueDouble.count(), 1);  // Assuming the buffer contains one double.
}

TEST_F(ValueTypeTest_148, SetDataArea_Success_148) {
    const byte buf[] = { 1, 2, 3, 4 };
    int len = sizeof(buf);
    
    // Verify setting data area with valid buffer
    EXPECT_EQ(valueInt.setDataArea(buf, len), 0);
    EXPECT_EQ(valueInt.sizeDataArea(), len);
}

TEST_F(ValueTypeTest_148, SetDataArea_EmptyBuffer_148) {
    const byte buf[] = {};
    int len = sizeof(buf);
    
    // Verify setting data area with empty buffer (edge case)
    EXPECT_EQ(valueInt.setDataArea(buf, len), 0);
    EXPECT_EQ(valueInt.sizeDataArea(), 0);
}

TEST_F(ValueTypeTest_148, Clone_148) {
    ValueType<int> clonedValue = *valueInt.clone();
    
    // Verify cloning functionality
    EXPECT_EQ(clonedValue.typeId(), valueInt.typeId());
    EXPECT_EQ(clonedValue.count(), valueInt.count());
}

TEST_F(ValueTypeTest_148, ToString_IntType_148) {
    const byte buf[] = { 1, 2, 3, 4 };
    int len = sizeof(buf);
    ByteOrder byteOrder = ByteOrder::BigEndian;
    
    valueInt.read(buf, len, byteOrder);
    EXPECT_EQ(valueInt.toString(), "ValueType: Int, count: 1");
}

TEST_F(ValueTypeTest_148, ToInt64_Valid_148) {
    const byte buf[] = { 0, 0, 0, 1 };
    int len = sizeof(buf);
    ByteOrder byteOrder = ByteOrder::BigEndian;
    
    valueInt.read(buf, len, byteOrder);
    EXPECT_EQ(valueInt.toInt64(0), 1);
}

TEST_F(ValueTypeTest_148, ToInt64_Invalid_148) {
    // Test invalid case where the size does not match
    const byte buf[] = { 0, 0, 0 };  // Incomplete data for int
    int len = sizeof(buf);
    ByteOrder byteOrder = ByteOrder::BigEndian;

    valueInt.read(buf, len, byteOrder);
    EXPECT_THROW(valueInt.toInt64(0), std::out_of_range);
}

TEST_F(ValueTypeTest_148, BoundaryCondition_LargeData_148) {
    // Test boundary conditions with large data size
    const byte buf[1000000] = {};  // Simulate large data buffer
    ByteOrder byteOrder = ByteOrder::BigEndian;
    
    EXPECT_EQ(valueInt.read(buf, sizeof(buf), byteOrder), 0);
    EXPECT_EQ(valueInt.count(), 1000000 / sizeof(int));  // Assuming each int is 4 bytes
}

TEST_F(ValueTypeTest_148, Write_148) {
    std::ostringstream os;
    
    // Test the write method for ValueType
    valueInt.write(os);
    EXPECT_NE(os.str().find("ValueType"), std::string::npos);  // Check if the string contains "ValueType"
}

} // namespace Exiv2