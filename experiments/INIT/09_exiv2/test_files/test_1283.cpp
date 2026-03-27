#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "exiv2/xmp_exiv2.hpp"  // Assuming the header where Xmpdatum is declared

namespace Exiv2 {

// Mock class for XmpKey (since it is used in Xmpdatum)
class MockXmpKey : public XmpKey {
public:
    MOCK_METHOD(std::string, tagLabel, (), (const, override));
};

// Test fixture class for Xmpdatum
class XmpdatumTest : public ::testing::Test {
protected:
    // Helper function to create a mock Xmpdatum with a mocked key
    std::unique_ptr<Xmpdatum> createXmpdatumWithMockKey() {
        auto mockKey = std::make_unique<MockXmpKey>("prefix", "property");
        auto mockValue = std::make_unique<Value>(); // Mock or set a proper value if needed
        return std::make_unique<Xmpdatum>(*mockKey, mockValue.get());
    }
};

// Normal operation test for tagLabel()
TEST_F(XmpdatumTest, tagLabel_ReturnsCorrectTagLabel_1283) {
    // Arrange
    auto mockXmpdatum = createXmpdatumWithMockKey();
    EXPECT_CALL(*mockXmpdatum->key(), tagLabel()).WillOnce(::testing::Return("TestTagLabel"));

    // Act
    std::string result = mockXmpdatum->tagLabel();

    // Assert
    EXPECT_EQ(result, "TestTagLabel");
}

// Boundary condition test for tagLabel() with empty key
TEST_F(XmpdatumTest, tagLabel_ReturnsEmptyString_WhenKeyIsNull_1284) {
    // Arrange
    auto mockKey = std::make_unique<MockXmpKey>("", "");
    auto mockValue = std::make_unique<Value>(); // Mock or set a proper value if needed
    auto mockXmpdatum = std::make_unique<Xmpdatum>(*mockKey, mockValue.get());

    // Act
    std::string result = mockXmpdatum->tagLabel();

    // Assert
    EXPECT_EQ(result, "");
}

// Exceptional test case for tagLabel() with uninitialized key
TEST_F(XmpdatumTest, tagLabel_ThrowsException_WhenKeyIsUninitialized_1285) {
    // Arrange
    auto mockXmpdatum = std::make_unique<Xmpdatum>(XmpKey("", ""), nullptr);

    // Act and Assert
    EXPECT_THROW(mockXmpdatum->tagLabel(), std::runtime_error);
}

}  // namespace Exiv2