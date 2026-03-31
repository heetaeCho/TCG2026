#include <gtest/gtest.h>
#include <string_view>
#include <string>

// Include the necessary headers
#include "makernote_int.hpp"

using namespace Exiv2::Internal;

class TiffMnRegistryTest_1429 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that an exact match of make_ returns true
TEST_F(TiffMnRegistryTest_1429, ExactMatchReturnsTrue_1429) {
    TiffMnRegistry registry;
    registry.make_ = "Canon";
    
    std::string_view key("Canon");
    EXPECT_TRUE(registry == key);
}

// Test that a key starting with make_ (prefix match) returns true
TEST_F(TiffMnRegistryTest_1429, PrefixMatchReturnsTrue_1429) {
    TiffMnRegistry registry;
    registry.make_ = "Canon";
    
    std::string_view key("Canon EOS 5D");
    EXPECT_TRUE(registry == key);
}

// Test that a key not starting with make_ returns false
TEST_F(TiffMnRegistryTest_1429, NonMatchReturnsFalse_1429) {
    TiffMnRegistry registry;
    registry.make_ = "Canon";
    
    std::string_view key("Nikon");
    EXPECT_FALSE(registry == key);
}

// Test that an empty key returns false (since empty string doesn't start_with any non-empty make_)
TEST_F(TiffMnRegistryTest_1429, EmptyKeyReturnsFalse_1429) {
    TiffMnRegistry registry;
    registry.make_ = "Canon";
    
    std::string_view key("");
    EXPECT_FALSE(registry == key);
}

// Test that a key starting with '-' always returns false
TEST_F(TiffMnRegistryTest_1429, KeyStartingWithDashReturnsFalse_1429) {
    TiffMnRegistry registry;
    registry.make_ = "-Canon";
    
    std::string_view key("-Canon");
    EXPECT_FALSE(registry == key);
}

// Test that a key starting with '-' returns false even if it would otherwise match
TEST_F(TiffMnRegistryTest_1429, KeyStartingWithDashPrefixReturnsFalse_1429) {
    TiffMnRegistry registry;
    registry.make_ = "-";
    
    std::string_view key("-something");
    EXPECT_FALSE(registry == key);
}

// Test with empty make_ - any non-dash key should match since starts_with("") is always true
TEST_F(TiffMnRegistryTest_1429, EmptyMakeMatchesNonDashKey_1429) {
    TiffMnRegistry registry;
    registry.make_ = "";
    
    std::string_view key("Anything");
    EXPECT_TRUE(registry == key);
}

// Test with empty make_ and empty key - empty doesn't start with '-' check but empty key
// empty key: key.empty() is true, so we skip the dash check, then "".starts_with("") is true
TEST_F(TiffMnRegistryTest_1429, EmptyMakeAndEmptyKey_1429) {
    TiffMnRegistry registry;
    registry.make_ = "";
    
    std::string_view key("");
    // empty key: key.empty() is true, so the dash check is skipped
    // "".starts_with("") is true
    EXPECT_TRUE(registry == key);
}

// Test partial match where key is shorter than make_
TEST_F(TiffMnRegistryTest_1429, KeyShorterThanMakeReturnsFalse_1429) {
    TiffMnRegistry registry;
    registry.make_ = "Canon EOS";
    
    std::string_view key("Canon");
    EXPECT_FALSE(registry == key);
}

// Test case sensitivity
TEST_F(TiffMnRegistryTest_1429, CaseSensitiveMatchFails_1429) {
    TiffMnRegistry registry;
    registry.make_ = "Canon";
    
    std::string_view key("canon");
    EXPECT_FALSE(registry == key);
}

// Test case sensitivity - uppercase vs lowercase
TEST_F(TiffMnRegistryTest_1429, CaseSensitiveMatchUppercase_1429) {
    TiffMnRegistry registry;
    registry.make_ = "canon";
    
    std::string_view key("Canon");
    EXPECT_FALSE(registry == key);
}

// Test single character make_ match
TEST_F(TiffMnRegistryTest_1429, SingleCharMakeMatch_1429) {
    TiffMnRegistry registry;
    registry.make_ = "N";
    
    std::string_view key("Nikon");
    EXPECT_TRUE(registry == key);
}

// Test single character key with longer make_
TEST_F(TiffMnRegistryTest_1429, SingleCharKeyWithLongerMake_1429) {
    TiffMnRegistry registry;
    registry.make_ = "Nikon";
    
    std::string_view key("N");
    EXPECT_FALSE(registry == key);
}

// Test key with just a dash character
TEST_F(TiffMnRegistryTest_1429, KeyIsJustDash_1429) {
    TiffMnRegistry registry;
    registry.make_ = "";
    
    std::string_view key("-");
    EXPECT_FALSE(registry == key);
}

// Test with special characters in make_ and key
TEST_F(TiffMnRegistryTest_1429, SpecialCharactersMatch_1429) {
    TiffMnRegistry registry;
    registry.make_ = "OLYMPUS ";
    
    std::string_view key("OLYMPUS OPTICAL CO.,LTD");
    EXPECT_TRUE(registry == key);
}

// Test with spaces
TEST_F(TiffMnRegistryTest_1429, SpacesInMakeAndKey_1429) {
    TiffMnRegistry registry;
    registry.make_ = "SONY ";
    
    std::string_view key("SONY DSC");
    EXPECT_TRUE(registry == key);
}

// Test that key with dash but make_ doesn't start with dash returns false
TEST_F(TiffMnRegistryTest_1429, DashKeyNonDashMake_1429) {
    TiffMnRegistry registry;
    registry.make_ = "Canon";
    
    std::string_view key("-Canon");
    EXPECT_FALSE(registry == key);
}
