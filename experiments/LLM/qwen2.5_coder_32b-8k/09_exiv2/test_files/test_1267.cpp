#include <gtest/gtest.h>

#include "exiv2/properties.hpp"



using namespace Exiv2;



class XmpKeyTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Set up any state needed for tests here.

    }



    void TearDown() override {

        // Clean up after each test, if needed.

    }

};



TEST_F(XmpKeyTest_1267, ConstructorWithString_1267) {

    XmpKey key("test_key");

    EXPECT_EQ(key.key(), "test_key");

}



TEST_F(XmpKeyTest_1267, ConstructorWithPrefixAndProperty_1267) {

    XmpKey key("prefix:", "property");

    EXPECT_EQ(key.key(), "prefix:property");

}



TEST_F(XmpKeyTest_1267, CopyConstructor_1267) {

    XmpKey original("original_key");

    XmpKey copy(original);

    EXPECT_EQ(copy.key(), original.key());

}



TEST_F(XmpKeyTest_1267, AssignmentOperator_1267) {

    XmpKey original("original_key");

    XmpKey target;

    target = original;

    EXPECT_EQ(target.key(), original.key());

}



TEST_F(XmpKeyTest_1267, CloneMethod_1267) {

    XmpKey key("test_key");

    auto clonedKey = key.clone();

    EXPECT_EQ(clonedKey->key(), key.key());

}



TEST_F(XmpKeyTest_1267, TagMethodReturnsZero_1267) {

    XmpKey key("test_key");

    EXPECT_EQ(key.tag(), 0);

}



// Assuming familyName, groupName, tagName, tagLabel, and tagDesc return empty strings by default

TEST_F(XmpKeyTest_1267, FamilyNameReturnsEmptyString_1267) {

    XmpKey key("test_key");

    EXPECT_STREQ(key.familyName(), "");

}



TEST_F(XmpKeyTest_1267, GroupNameReturnsEmptyString_1267) {

    XmpKey key("test_key");

    EXPECT_EQ(key.groupName(), "");

}



TEST_F(XmpKeyTest_1267, TagNameReturnsEmptyString_1267) {

    XmpKey key("test_key");

    EXPECT_EQ(key.tagName(), "");

}



TEST_F(XmpKeyTest_1267, TagLabelReturnsEmptyString_1267) {

    XmpKey key("test_key");

    EXPECT_EQ(key.tagLabel(), "");

}



TEST_F(XmpKeyTest_1267, TagDescReturnsEmptyString_1267) {

    XmpKey key("test_key");

    EXPECT_EQ(key.tagDesc(), "");

}



// Assuming ns returns an empty string by default

TEST_F(XmpKeyTest_1267, NamespaceReturnsEmptyString_1267) {

    XmpKey key("test_key");

    EXPECT_EQ(key.ns(), "");

}
