#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "xmp_exiv2.hpp"
#include "value.hpp"

using namespace Exiv2;

// Mock Value class to simulate dependencies
class MockValue : public Value {
public:
    MockValue(TypeId typeId) : Value(typeId) {}
    MOCK_METHOD(int, read, (const byte* buf, size_t len, ByteOrder byteOrder), (override));
    MOCK_METHOD(int, read, (const std::string& buf), (override));
    MOCK_METHOD(const size_t, size, (), (const, override));
    MOCK_METHOD(std::string, toString, (), (const, override));
    MOCK_METHOD(const Rational, toRational, (size_t n), (const, override));
    MOCK_METHOD(int64_t, toInt64, (size_t n), (const, override));
    MOCK_METHOD(float, toFloat, (size_t n), (const, override));
    MOCK_METHOD(Value::UniquePtr, clone, (), (const, override));
};

// Test Fixture for Xmpdatum
class XmpdatumTest : public ::testing::Test {
protected:
    XmpKey key;
    MockValue* mockValue;
    Xmpdatum* xmpdatum;

    void SetUp() override {
        mockValue = new MockValue(TypeId::string);
        xmpdatum = new Xmpdatum(key, mockValue);
    }

    void TearDown() override {
        delete xmpdatum;
        delete mockValue;
    }
};

// TEST_ID: 1300
TEST_F(XmpdatumTest, SetValue_Success_1300) {
    // Arrange
    const Value* newValue = new MockValue(TypeId::string);
    
    // Act
    xmpdatum->setValue(newValue);
    
    // Assert
    EXPECT_EQ(xmpdatum->getValue().get(), newValue);
}

// TEST_ID: 1301
TEST_F(XmpdatumTest, SetValue_NullPointer_1301) {
    // Act
    xmpdatum->setValue(nullptr);
    
    // Assert
    EXPECT_EQ(xmpdatum->getValue(), nullptr);
}

// TEST_ID: 1302
TEST_F(XmpdatumTest, SetValue_ExistingValue_1302) {
    // Arrange
    const Value* existingValue = new MockValue(TypeId::string);
    xmpdatum->setValue(existingValue);
    
    // Act
    const Value* newValue = new MockValue(TypeId::string);
    xmpdatum->setValue(newValue);
    
    // Assert
    EXPECT_EQ(xmpdatum->getValue().get(), newValue);
}

// TEST_ID: 1303
TEST_F(XmpdatumTest, SetValue_CloneCalled_1303) {
    // Arrange
    const Value* newValue = new MockValue(TypeId::string);
    
    // Expect that clone is called when setValue is executed
    EXPECT_CALL(*mockValue, clone()).WillOnce(testing::Return(newValue));

    // Act
    xmpdatum->setValue(newValue);
    
    // Assert
    EXPECT_EQ(xmpdatum->getValue().get(), newValue);
}

// TEST_ID: 1304
TEST_F(XmpdatumTest, SetValue_ErrorCase_1304) {
    // Arrange
    const Value* badValue = nullptr;

    // Act and Assert
    EXPECT_THROW(xmpdatum->setValue(badValue), std::invalid_argument);
}