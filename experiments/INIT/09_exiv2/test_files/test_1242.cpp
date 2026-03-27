#include <gtest/gtest.h>
#include <string>
#include "properties.hpp"  // Adjust the path based on your project structure

namespace Exiv2 {

    // Test class for the XmpPropertyInfo
    class XmpPropertyInfoTest : public ::testing::Test {
    protected:
        XmpPropertyInfo property;
    };

    // TEST_ID 1242: Test for equality when the names match exactly
    TEST_F(XmpPropertyInfoTest, EqualsWhenNamesMatch_1242) {
        // Set up the property with a known name
        property.name_ = "testProperty";

        // Check equality
        EXPECT_TRUE(property == "testProperty");
    }

    // TEST_ID 1243: Test for equality when the names do not match
    TEST_F(XmpPropertyInfoTest, NotEqualsWhenNamesDoNotMatch_1243) {
        // Set up the property with a known name
        property.name_ = "testProperty";

        // Check inequality
        EXPECT_FALSE(property == "anotherProperty");
    }

    // TEST_ID 1244: Test for empty string comparison
    TEST_F(XmpPropertyInfoTest, EqualsWithEmptyString_1244) {
        // Set up the property with a non-empty name
        property.name_ = "testProperty";

        // Check if empty string is not equal
        EXPECT_FALSE(property == "");
    }

    // TEST_ID 1245: Test for empty property name comparison
    TEST_F(XmpPropertyInfoTest, EqualsWithEmptyPropertyName_1245) {
        // Set up the property with an empty name
        property.name_ = "";

        // Check if empty property name equals empty string
        EXPECT_TRUE(property == "");
    }

    // TEST_ID 1246: Test for case sensitivity in comparison
    TEST_F(XmpPropertyInfoTest, CaseSensitiveComparison_1246) {
        // Set up the property with a known name
        property.name_ = "TestProperty";

        // Check for case-sensitive inequality
        EXPECT_FALSE(property == "testproperty");
    }
}