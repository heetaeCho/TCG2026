#include <gtest/gtest.h>
#include "properties.hpp"

namespace Exiv2 {

class XmpKeyTest_1266 : public ::testing::Test {
protected:
    XmpKey key1;
    XmpKey key2;

    XmpKeyTest_1266() : key1("prefix", "property"), key2("prefix", "property") {}
};

// Normal Operation Tests
TEST_F(XmpKeyTest_1266, KeyConstructorTest_1266) {
    EXPECT_EQ(key1.key(), "prefix:property");
    EXPECT_EQ(key2.key(), "prefix:property");
}

TEST_F(XmpKeyTest_1266, TagDescTest_1266) {
    EXPECT_EQ(key1.tagDesc(), "");
    EXPECT_EQ(key2.tagDesc(), "");
}

TEST_F(XmpKeyTest_1266, CloneTest_1266) {
    auto clonedKey = key1.clone();
    EXPECT_NE(&clonedKey, &key1);
    EXPECT_EQ(clonedKey->key(), key1.key());
}

// Boundary Conditions
TEST_F(XmpKeyTest_1266, EmptyConstructorTest_1266) {
    XmpKey emptyKey("");
    EXPECT_EQ(emptyKey.key(), "");
    EXPECT_EQ(emptyKey.tagDesc(), "");
}

TEST_F(XmpKeyTest_1266, EmptyTagDescTest_1266) {
    XmpKey emptyTagDescKey("empty", "");
    EXPECT_EQ(emptyTagDescKey.tagDesc(), "");
}

// Exceptional/Error Cases
TEST_F(XmpKeyTest_1266, InvalidTagTest_1266) {
    XmpKey invalidKey("invalid", "tag");
    EXPECT_EQ(invalidKey.tagDesc(), "");
}

// Verify External Interactions
// Here, the external interactions could involve checking the static methods or other related components.
// Since no external mocks are involved based on the current code provided, we won't add them in this example.

}  // namespace Exiv2