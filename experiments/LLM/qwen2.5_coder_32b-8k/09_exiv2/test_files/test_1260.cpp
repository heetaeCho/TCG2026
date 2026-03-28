#include <gtest/gtest.h>

#include "exiv2/properties.hpp"



using namespace Exiv2;



class XmpKeyTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup can be used to initialize common objects or states if necessary.

    }



    void TearDown() override {

        // Cleanup can be done here if necessary.

    }

};



TEST_F(XmpKeyTest_1260, ConstructorWithKeyString_1260) {

    XmpKey key("example");

    EXPECT_EQ(key.key(), "example");

}



TEST_F(XmpKeyTest_1260, ConstructorWithPrefixAndProperty_1260) {

    XmpKey key("prefix:", "property");

    EXPECT_EQ(key.key(), "prefix:property");

}



TEST_F(XmpKeyTest_1260, CopyConstructor_1260) {

    XmpKey original("example");

    XmpKey copy(original);

    EXPECT_EQ(copy.key(), "example");

}



TEST_F(XmpKeyTest_1260, AssignmentOperator_1260) {

    XmpKey original("example");

    XmpKey assigned;

    assigned = original;

    EXPECT_EQ(assigned.key(), "example");

}



TEST_F(XmpKeyTest_1260, CloneFunctionReturnsNewInstance_1260) {

    XmpKey original("example");

    auto clone = original.clone();

    EXPECT_NE(&original, clone.get());

    EXPECT_EQ(original.key(), clone->key());

}



TEST_F(XmpKeyTest_1260, FamilyName_ReturnsExpectedValue_1260) {

    XmpKey key("http://ns.adobe.com/photoshop/1.0/", "DateCreated");

    // Assuming familyName returns the prefix without trailing slash

    EXPECT_EQ(key.familyName(), "http://ns.adobe.com/photoshop/1.0");

}



TEST_F(XmpKeyTest_1260, GroupName_ReturnsExpectedValue_1260) {

    XmpKey key("prefix:", "property");

    // Assuming groupName returns an empty string or the prefix

    EXPECT_EQ(key.groupName(), "");

}



TEST_F(XmpKeyTest_1260, TagName_ReturnsExpectedValue_1260) {

    XmpKey key("prefix:", "property");

    EXPECT_EQ(key.tagName(), "property");

}



TEST_F(XmpKeyTest_1260, TagLabel_ReturnsEmptyString_1260) {

    XmpKey key("example");

    EXPECT_EQ(key.tagLabel(), "");

}



TEST_F(XmpKeyTest_1260, TagDesc_ReturnsEmptyString_1260) {

    XmpKey key("example");

    EXPECT_EQ(key.tagDesc(), "");

}



TEST_F(XmpKeyTest_1260, Tag_ReturnsZero_1260) {

    XmpKey key("example");

    EXPECT_EQ(key.tag(), 0);

}



TEST_F(XmpKeyTest_1260, Ns_ReturnsExpectedNamespace_1260) {

    XmpKey key("http://ns.adobe.com/photoshop/1.0/", "DateCreated");

    EXPECT_EQ(key.ns(), "http://ns.adobe.com/photoshop/1.0/");

}
