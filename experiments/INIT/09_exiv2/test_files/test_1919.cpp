#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>

// Mock for dependencies if needed, no mock required for the provided code
// Example: Mock XMP_VarString or other dependencies

class XMPUtilsTest : public ::testing::Test {
protected:
    // Setup and teardown methods if needed.
};

// Test case 1: Normal operation of ApplyQuotes
TEST_F(XMPUtilsTest, ApplyQuotes_NormalOperation_1919) {
    // Prepare the test input
    XMP_VarString item = "Hello world";
    UniCodePoint openQuote = 0x22;  // Unicode for double quote (")
    UniCodePoint closeQuote = 0x22; // Unicode for double quote (")
    bool allowCommas = false;
    
    // Call the function to test
    ApplyQuotes(&item, openQuote, closeQuote, allowCommas);
    
    // Verify the expected behavior (Check the quotes are applied correctly)
    ASSERT_EQ(item, "\"Hello world\"");
}

// Test case 2: ApplyQuotes with multiple spaces in the string
TEST_F(XMPUtilsTest, ApplyQuotes_MultipleSpaces_1919) {
    XMP_VarString item = "Hello   world";
    UniCodePoint openQuote = 0x22;  // Unicode for double quote (")
    UniCodePoint closeQuote = 0x22; // Unicode for double quote (")
    bool allowCommas = false;
    
    // Call the function to test
    ApplyQuotes(&item, openQuote, closeQuote, allowCommas);
    
    // Verify that multiple spaces don't interfere with the quotes
    ASSERT_EQ(item, "\"Hello   world\"");
}

// Test case 3: ApplyQuotes with commas disallowed
TEST_F(XMPUtilsTest, ApplyQuotes_DisallowCommas_1919) {
    XMP_VarString item = "Hello, world";
    UniCodePoint openQuote = 0x22;  // Unicode for double quote (")
    UniCodePoint closeQuote = 0x22; // Unicode for double quote (")
    bool allowCommas = false;
    
    // Call the function to test
    ApplyQuotes(&item, openQuote, closeQuote, allowCommas);
    
    // Check that the comma is not included
    ASSERT_EQ(item, "\"Hello\"");
}

// Test case 4: ApplyQuotes with commas allowed
TEST_F(XMPUtilsTest, ApplyQuotes_AllowCommas_1919) {
    XMP_VarString item = "Hello, world";
    UniCodePoint openQuote = 0x22;  // Unicode for double quote (")
    UniCodePoint closeQuote = 0x22; // Unicode for double quote (")
    bool allowCommas = true;
    
    // Call the function to test
    ApplyQuotes(&item, openQuote, closeQuote, allowCommas);
    
    // Check that the comma is included
    ASSERT_EQ(item, "\"Hello, world\"");
}

// Test case 5: ApplyQuotes with an empty string
TEST_F(XMPUtilsTest, ApplyQuotes_EmptyString_1919) {
    XMP_VarString item = "";
    UniCodePoint openQuote = 0x22;  // Unicode for double quote (")
    UniCodePoint closeQuote = 0x22; // Unicode for double quote (")
    bool allowCommas = false;
    
    // Call the function to test
    ApplyQuotes(&item, openQuote, closeQuote, allowCommas);
    
    // Verify that the result is just quotes around an empty string
    ASSERT_EQ(item, "\"\"");
}

// Test case 6: ApplyQuotes with a control character
TEST_F(XMPUtilsTest, ApplyQuotes_ControlCharacter_1919) {
    XMP_VarString item = "Hello\x01world";  // Including a control character (ASCII 1)
    UniCodePoint openQuote = 0x22;  // Unicode for double quote (")
    UniCodePoint closeQuote = 0x22; // Unicode for double quote (")
    bool allowCommas = false;
    
    // Call the function to test
    ApplyQuotes(&item, openQuote, closeQuote, allowCommas);
    
    // Check that the control character causes the item to be quoted properly
    ASSERT_EQ(item, "\"Hello\x01world\"");
}