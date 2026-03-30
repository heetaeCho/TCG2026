#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/poppler/StructElement.h"
#include "./TestProjects/poppler/poppler/StructElement.cc"

// Mock class for the external dependency if needed
class MockOwnerMapEntry {
public:
    MOCK_METHOD(const Attribute::Owner, getOwner, (), (const));
};

// Test fixture for testing the `nameToOwner` function
class StructElementTest_1781 : public ::testing::Test {
protected:
    // You can initialize any shared resources here if needed
};

// Test for normal operation: Valid input name corresponding to a known owner
TEST_F(StructElementTest_1781, nameToOwner_ValidInput_1781) {
    const char* name = "UserProperties"; // Known owner
    Attribute::Owner result = nameToOwner(name);

    // Assert that the result corresponds to the correct enum value
    ASSERT_EQ(result, Attribute::UserProperties);
}

// Test for boundary condition: Empty string input
TEST_F(StructElementTest_1781, nameToOwner_EmptyString_1781) {
    const char* name = ""; // Empty name
    Attribute::Owner result = nameToOwner(name);

    // Assert that the result corresponds to the UnknownOwner
    ASSERT_EQ(result, Attribute::UnknownOwner);
}

// Test for boundary condition: Null pointer input
TEST_F(StructElementTest_1781, nameToOwner_NullPointer_1781) {
    const char* name = nullptr; // Null pointer
    Attribute::Owner result = nameToOwner(name);

    // Assert that the result corresponds to the UnknownOwner
    ASSERT_EQ(result, Attribute::UnknownOwner);
}

// Test for boundary condition: Unknown name input
TEST_F(StructElementTest_1781, nameToOwner_UnknownName_1781) {
    const char* name = "UnknownOwner"; // Name that is not mapped
    Attribute::Owner result = nameToOwner(name);

    // Assert that the result corresponds to the UnknownOwner
    ASSERT_EQ(result, Attribute::UnknownOwner);
}

// Test for exceptional/error case: Input name corresponding to invalid owner
TEST_F(StructElementTest_1781, nameToOwner_InvalidOwner_1781) {
    const char* name = "InvalidOwner"; // Invalid owner name
    Attribute::Owner result = nameToOwner(name);

    // Assert that the result corresponds to the UnknownOwner
    ASSERT_EQ(result, Attribute::UnknownOwner);
}