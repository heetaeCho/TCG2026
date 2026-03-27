#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include "exiv2/xmp_exiv2.hpp"
#include "exiv2/properties.hpp"

namespace Exiv2 {

class MockXmpKey : public XmpKey {
public:
    MOCK_METHOD(std::string, groupName, (), (const, override));
    MOCK_METHOD(std::string, key, (), (const, override));
    MOCK_METHOD(std::string, familyName, (), (const, override));
};

class MockValue : public Value {
public:
    MOCK_METHOD(std::string, toString, (), (const, override));
};

// Unit Test for Xmpdatum::groupName
TEST_F(XmpdatumTest_1281, GroupNameReturnsExpectedValue_1281) {
    // Arrange
    MockXmpKey mockKey;
    MockValue mockValue;
    Xmpdatum xmp(mockKey, &mockValue);
    
    std::string expectedGroupName = "testGroup";
    EXPECT_CALL(mockKey, groupName()).WillOnce(testing::Return(expectedGroupName));

    // Act
    std::string result = xmp.groupName();

    // Assert
    EXPECT_EQ(result, expectedGroupName);
}

// Unit Test for Xmpdatum::groupName when key is null
TEST_F(XmpdatumTest_1282, GroupNameReturnsEmptyWhenKeyIsNull_1282) {
    // Arrange
    MockValue mockValue;
    Xmpdatum xmp(nullptr, &mockValue);

    // Act
    std::string result = xmp.groupName();

    // Assert
    EXPECT_EQ(result, "");
}

// Unit Test for Xmpdatum::groupName with a mock Value
TEST_F(XmpdatumTest_1283, GroupNameCallsMockValueToString_1283) {
    // Arrange
    MockXmpKey mockKey;
    MockValue mockValue;
    Xmpdatum xmp(mockKey, &mockValue);
    
    std::string expectedGroupName = "testGroup";
    std::string expectedValue = "testValue";
    
    EXPECT_CALL(mockKey, groupName()).WillOnce(testing::Return(expectedGroupName));
    EXPECT_CALL(mockValue, toString()).WillOnce(testing::Return(expectedValue));

    // Act
    std::string result = xmp.groupName();

    // Assert
    EXPECT_EQ(result, expectedGroupName);
}

// Unit Test for Xmpdatum::groupName when Value is nullptr
TEST_F(XmpdatumTest_1284, GroupNameReturnsEmptyWhenValueIsNull_1284) {
    // Arrange
    MockXmpKey mockKey;
    Xmpdatum xmp(mockKey, nullptr);

    // Act
    std::string result = xmp.groupName();

    // Assert
    EXPECT_EQ(result, "");
}

} // namespace Exiv2