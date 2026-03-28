#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "tiffcomposite_int.hpp"
#include "types.hpp"  // For TypeInfo class

namespace Exiv2 { namespace Internal {

// Mock the TypeInfo class since it's a dependency
class MockTypeInfo {
public:
    MOCK_METHOD(const char*, typeName, (TypeId typeId), (const));
    MOCK_METHOD(TypeId, typeId, (const std::string& typeName), ());
    MOCK_METHOD(size_t, typeSize, (TypeId typeId), ());
};

} }

using ::testing::Return;

// Test fixture for ArrayDef tests
class ArrayDefTest_312 : public ::testing::Test {
protected:
    // Test setup can be done here, if necessary.
    Exiv2::Internal::ArrayDef arrayDef_;
    MockTypeInfo mockTypeInfo_;
};

// Normal operation test case
TEST_F(ArrayDefTest_312, SizeReturnsCorrectValue_312) {
    // Arrange
    uint16_t tag = 1;  // Example tag
    Exiv2::IfdId group = 2;  // Example group ID
    size_t expectedSize = 10;
    
    // Mocking the call to TypeInfo::typeSize (assumes typeId = 3 for this test)
    EXPECT_CALL(mockTypeInfo_, typeSize(3))
        .WillOnce(Return(5));  // Assume typeSize returns 5 for TypeId 3
    
    arrayDef_.count_ = 2;  // Set count to 2 for this test

    // Act
    size_t actualSize = arrayDef_.size(tag, group);

    // Assert
    EXPECT_EQ(actualSize, expectedSize);
}

// Boundary condition test case: zero count
TEST_F(ArrayDefTest_312, SizeReturnsZeroWhenCountIsZero_312) {
    // Arrange
    uint16_t tag = 1;
    Exiv2::IfdId group = 2;

    // Mocking the call to TypeInfo::typeSize (assumes typeId = 3 for this test)
    EXPECT_CALL(mockTypeInfo_, typeSize(3))
        .WillOnce(Return(5));  // Assume typeSize returns 5 for TypeId 3
    
    arrayDef_.count_ = 0;  // Set count to 0 for this test

    // Act
    size_t actualSize = arrayDef_.size(tag, group);

    // Assert
    EXPECT_EQ(actualSize, 0);  // With count_ = 0, the size should be 0
}

// Boundary condition test case: large count
TEST_F(ArrayDefTest_312, SizeReturnsCorrectValueWithLargeCount_312) {
    // Arrange
    uint16_t tag = 1;
    Exiv2::IfdId group = 2;
    size_t expectedSize = 1000000;
    
    // Mocking the call to TypeInfo::typeSize (assumes typeId = 3 for this test)
    EXPECT_CALL(mockTypeInfo_, typeSize(3))
        .WillOnce(Return(500000));  // Assume typeSize returns 500000 for TypeId 3
    
    arrayDef_.count_ = 2;  // Set count to 2 for this test

    // Act
    size_t actualSize = arrayDef_.size(tag, group);

    // Assert
    EXPECT_EQ(actualSize, expectedSize);  // With count_ = 2, the size should be 1000000
}

// Exceptional case: Invalid TypeId (could be tested with mocking)
TEST_F(ArrayDefTest_312, SizeThrowsExceptionOnInvalidTypeId_312) {
    // Arrange
    uint16_t tag = 1;
    Exiv2::IfdId group = 2;

    // Mocking the call to TypeInfo::typeSize to return an invalid result
    EXPECT_CALL(mockTypeInfo_, typeSize(999))  // Invalid TypeId
        .WillOnce(Return(0));  // Assume typeSize returns 0 for invalid TypeId

    arrayDef_.count_ = 2;  // Set count to 2 for this test

    // Act & Assert
    EXPECT_THROW(arrayDef_.size(tag, group), std::invalid_argument);  // Expect exception for invalid TypeId
}

} }