#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "xmp_exiv2.hpp"
#include "value.hpp"
#include "types.hpp"

namespace Exiv2 {

class MockXmpKey : public XmpKey {
public:
    MOCK_METHOD(XmpKey::UniquePtr, clone, (), (const, override));
};

class MockValue : public Value {
public:
    MOCK_METHOD(TypeId, typeId, (), (const, override));
    MOCK_METHOD(bool, ok, (), (const, override));
};

// Unit tests for Xmpdatum::typeId()
class XmpdatumTest_1286 : public ::testing::Test {
protected:
    MockXmpKey mockKey;
    MockValue mockValue;

    XmpdatumTest_1286()
        : mockKey(), mockValue(TypeId::unsignedByte) {}

    Xmpdatum createXmpdatum() {
        return Xmpdatum(mockKey, &mockValue);
    }
};

// Test normal operation: When value is valid, return typeId from Value
TEST_F(XmpdatumTest_1286, TypeId_ReturnsTypeFromValue_1286) {
    // Arrange
    TypeId expectedType = TypeId::unsignedByte;
    EXPECT_CALL(mockValue, typeId())
        .WillOnce(testing::Return(expectedType));
    
    Xmpdatum xmpDatum = createXmpdatum();
    
    // Act
    TypeId result = xmpDatum.typeId();
    
    // Assert
    EXPECT_EQ(result, expectedType);
}

// Test when the value is invalid: Should return invalidTypeId
TEST_F(XmpdatumTest_1286, TypeId_ReturnsInvalidWhenValueIsNull_1287) {
    // Arrange
    Xmpdatum xmpDatum(mockKey, nullptr);
    
    // Act
    TypeId result = xmpDatum.typeId();
    
    // Assert
    EXPECT_EQ(result, TypeId::invalidTypeId);
}

// Test when value is valid but ok() returns false: Should still return typeId
TEST_F(XmpdatumTest_1286, TypeId_ReturnsTypeFromValueEvenIfNotOk_1288) {
    // Arrange
    TypeId expectedType = TypeId::unsignedShort;
    EXPECT_CALL(mockValue, ok())
        .WillOnce(testing::Return(false));
    EXPECT_CALL(mockValue, typeId())
        .WillOnce(testing::Return(expectedType));
    
    Xmpdatum xmpDatum = createXmpdatum();
    
    // Act
    TypeId result = xmpDatum.typeId();
    
    // Assert
    EXPECT_EQ(result, expectedType);
}

// Test that the clone method on XmpKey is called correctly
TEST_F(XmpdatumTest_1286, TypeId_ClonesXmpKey_1289) {
    // Arrange
    EXPECT_CALL(mockKey, clone())
        .WillOnce(testing::Return(std::make_unique<MockXmpKey>()));
    
    Xmpdatum xmpDatum(mockKey, &mockValue);
    
    // Act
    TypeId result = xmpDatum.typeId();
    
    // Assert
    // Ensure the clone method is invoked
    testing::Mock::VerifyAndClearExpectations(&mockKey);
    EXPECT_EQ(result, TypeId::unsignedByte); // Assume TypeId is returned correctly
}

}  // namespace Exiv2