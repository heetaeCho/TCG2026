#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "exiv2/metadatum.hpp"

namespace Exiv2 {

// Mock class for Key since we are not allowed to access private state
class MockKey : public Key {
public:
    MOCK_METHOD(Key::UniquePtr, clone_, (), (const, override));
    MOCK_METHOD(std::string, key, (), (const, override));
    MOCK_METHOD(const char*, familyName, (), (const, override));
    MOCK_METHOD(std::string, groupName, (), (const, override));
    MOCK_METHOD(std::string, tagName, (), (const, override));
    MOCK_METHOD(std::string, tagLabel, (), (const, override));
    MOCK_METHOD(std::string, tagDesc, (), (const, override));
    MOCK_METHOD(uint16_t, tag, (), (const, override));
    MOCK_METHOD(std::ostream&, write, (std::ostream& os), (const, override));
};

} // namespace Exiv2

// Test cases for Key class
class KeyTest_109 : public ::testing::Test {
protected:
    Exiv2::MockKey mockKey;

    // Setup function
    void SetUp() override {
        // Set up mock behavior
        ON_CALL(mockKey, clone_()).WillByDefault([]() {
            return std::make_unique<Exiv2::MockKey>();  // Return a new mock Key instance
        });
        ON_CALL(mockKey, key()).WillByDefault([]() {
            return std::string("mockKey");
        });
    }
};

// Test for normal operation: testing the clone function
TEST_F(KeyTest_109, Clone_109) {
    // Arrange: Define behavior for clone method
    EXPECT_CALL(mockKey, clone_()).Times(1);

    // Act: Call clone
    auto clonedKey = mockKey.clone();

    // Assert: Ensure that the clone was successfully created
    EXPECT_NE(clonedKey, nullptr);
}

// Test for normal operation: testing key() function
TEST_F(KeyTest_109, Key_109) {
    // Arrange: Define behavior for key() method
    EXPECT_CALL(mockKey, key()).Times(1).WillOnce(testing::Return("mockKey"));

    // Act: Call key
    std::string keyValue = mockKey.key();

    // Assert: Ensure the key returned is the expected one
    EXPECT_EQ(keyValue, "mockKey");
}

// Test for normal operation: testing familyName() function
TEST_F(KeyTest_109, FamilyName_109) {
    // Arrange: Define behavior for familyName method
    EXPECT_CALL(mockKey, familyName()).Times(1).WillOnce(testing::Return("mockFamily"));

    // Act: Call familyName
    const char* familyNameValue = mockKey.familyName();

    // Assert: Ensure the family name is correct
    EXPECT_STREQ(familyNameValue, "mockFamily");
}

// Test for normal operation: testing tag() function
TEST_F(KeyTest_109, Tag_109) {
    // Arrange: Define behavior for tag() method
    EXPECT_CALL(mockKey, tag()).Times(1).WillOnce(testing::Return(123));

    // Act: Call tag
    uint16_t tagValue = mockKey.tag();

    // Assert: Ensure the tag returned is correct
    EXPECT_EQ(tagValue, 123);
}

// Test for boundary condition: cloning an empty Key (expect empty UniquePtr)
TEST_F(KeyTest_109, CloneEmptyKey_109) {
    // Arrange: Set behavior for clone to return a null UniquePtr
    ON_CALL(mockKey, clone_()).WillByDefault([]() { return nullptr; });

    // Act: Call clone on the Key
    auto clonedKey = mockKey.clone();

    // Assert: Ensure that cloning an empty Key returns a null pointer
    EXPECT_EQ(clonedKey, nullptr);
}

// Test for exceptional case: Ensure that calling write() on Key does not crash
TEST_F(KeyTest_109, Write_109) {
    // Arrange: Define behavior for write method
    std::ostringstream os;
    EXPECT_CALL(mockKey, write(testing::_)).Times(1).WillOnce(testing::ReturnRef(os));

    // Act: Call write on Key
    mockKey.write(os);

    // Assert: Ensure the write function was invoked correctly
    EXPECT_FALSE(os.str().empty());
}

// Test for boundary condition: calling key() on Key object with edge-case empty string
TEST_F(KeyTest_109, KeyEmpty_109) {
    // Arrange: Define behavior for key() method to return an empty string
    EXPECT_CALL(mockKey, key()).Times(1).WillOnce(testing::Return(""));

    // Act: Call key
    std::string keyValue = mockKey.key();

    // Assert: Ensure that the key returned is empty
    EXPECT_EQ(keyValue, "");
}