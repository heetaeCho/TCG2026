#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include "properties.hpp" // Ensure this includes the necessary Exiv2::XmpKey declaration

// Mock class for dependencies if needed (none inferred from the given code, but can be added later if necessary)

// Unit tests for Exiv2::XmpKey
namespace Exiv2 {

class XmpKeyTest : public ::testing::Test {
protected:
    // Set up necessary resources for each test, if needed.
    XmpKeyTest() = default;
    ~XmpKeyTest() override = default;
};

// Test case for XmpKey::tagName - Normal Operation
TEST_F(XmpKeyTest, TagName_NormalOperation_1264) {
    // Arrange
    std::string property = "exampleProperty";
    XmpKey xmpKey("prefix", property);

    // Act
    std::string tagName = xmpKey.tagName();

    // Assert
    EXPECT_EQ(tagName, property);
}

// Test case for XmpKey::tagName - Boundary condition with an empty string
TEST_F(XmpKeyTest, TagName_EmptyProperty_1265) {
    // Arrange
    std::string property = "";
    XmpKey xmpKey("prefix", property);

    // Act
    std::string tagName = xmpKey.tagName();

    // Assert
    EXPECT_EQ(tagName, property);  // Expecting an empty string as the tag name
}

// Test case for XmpKey::tagName - Boundary condition with special characters
TEST_F(XmpKeyTest, TagName_SpecialCharacters_1266) {
    // Arrange
    std::string property = "!@#$%^&*()";
    XmpKey xmpKey("prefix", property);

    // Act
    std::string tagName = xmpKey.tagName();

    // Assert
    EXPECT_EQ(tagName, property);  // Expecting the special characters to be handled correctly
}

// Test case for XmpKey::tagName - Normal operation with default constructor
TEST_F(XmpKeyTest, TagName_DefaultConstructor_1267) {
    // Arrange
    std::string property = "defaultProperty";
    XmpKey xmpKey("prefix", property);

    // Act
    std::string tagName = xmpKey.tagName();

    // Assert
    EXPECT_EQ(tagName, property);
}

// Test case for XmpKey::tagName - Exceptional case with invalid string (e.g., null or non-UTF characters)
TEST_F(XmpKeyTest, TagName_InvalidProperty_1268) {
    // Arrange
    std::string property = "\x80";  // Invalid byte in UTF-8
    XmpKey xmpKey("prefix", property);

    // Act
    std::string tagName = xmpKey.tagName();

    // Assert
    EXPECT_EQ(tagName, property);  // Should return the string as is, but it may depend on how your code handles encoding errors
}

}  // namespace Exiv2