#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "properties.hpp"  // Include the header where XmpKey is declared

namespace Exiv2 {

class XmpKeyTest : public ::testing::Test {
protected:
    // Helper function to create XmpKey objects for testing
    XmpKey createXmpKey(const std::string& prefix, const std::string& property) {
        return XmpKey(prefix, property);
    }

    XmpKey defaultXmpKey = XmpKey("defaultPrefix", "defaultProperty");
};

// Test for constructor with a single key
TEST_F(XmpKeyTest, ConstructorWithKey_1265) {
    XmpKey key("prefix", "property");
    EXPECT_EQ(key.tagName(), "property");
    EXPECT_EQ(key.tagLabel(), "property");
}

// Test for constructor with prefix and property
TEST_F(XmpKeyTest, ConstructorWithPrefixAndProperty_1266) {
    XmpKey key("prefix", "property");
    EXPECT_EQ(key.ns(), "prefix");
    EXPECT_EQ(key.key(), "prefix:property");
}

// Test for copy constructor
TEST_F(XmpKeyTest, CopyConstructor_1267) {
    XmpKey original("prefix", "property");
    XmpKey copy = original;

    EXPECT_EQ(copy.ns(), original.ns());
    EXPECT_EQ(copy.key(), original.key());
    EXPECT_EQ(copy.tagName(), original.tagName());
}

// Test for assignment operator
TEST_F(XmpKeyTest, AssignmentOperator_1268) {
    XmpKey key1("prefix1", "property1");
    XmpKey key2("prefix2", "property2");

    key2 = key1;

    EXPECT_EQ(key2.ns(), key1.ns());
    EXPECT_EQ(key2.key(), key1.key());
}

// Test for tagDesc method (expecting an empty description for this test case)
TEST_F(XmpKeyTest, TagDesc_1269) {
    XmpKey key("prefix", "property");
    EXPECT_EQ(key.tagDesc(), "");
}

// Test for tagLabel with a valid value
TEST_F(XmpKeyTest, TagLabel_1270) {
    XmpKey key("prefix", "property");
    EXPECT_EQ(key.tagLabel(), "property");
}

// Boundary condition test for a very long key string
TEST_F(XmpKeyTest, LongKeyString_1271) {
    std::string longKey(1000, 'a');  // Key with 1000 'a's
    XmpKey key("prefix", longKey);

    EXPECT_EQ(key.key(), "prefix:" + longKey);
}

// Exceptional case: Checking behavior with an empty property
TEST_F(XmpKeyTest, EmptyProperty_1272) {
    XmpKey key("prefix", "");
    EXPECT_EQ(key.tagName(), "");
    EXPECT_EQ(key.key(), "prefix:");
}

// Exceptional case: Checking behavior with empty prefix
TEST_F(XmpKeyTest, EmptyPrefix_1273) {
    XmpKey key("", "property");
    EXPECT_EQ(key.tagName(), "property");
    EXPECT_EQ(key.key(), ":property");
}

// Test clone function, verifying that it creates a new object with the same values
TEST_F(XmpKeyTest, Clone_1274) {
    XmpKey key("prefix", "property");
    auto clonedKey = key.clone();
    
    EXPECT_EQ(clonedKey->ns(), key.ns());
    EXPECT_EQ(clonedKey->key(), key.key());
    EXPECT_EQ(clonedKey->tagName(), key.tagName());
}

}  // namespace Exiv2