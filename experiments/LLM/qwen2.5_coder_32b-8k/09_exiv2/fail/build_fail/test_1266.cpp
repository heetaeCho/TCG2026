#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/properties.hpp"



namespace Exiv2 {

    class XmpKey;

}



using namespace testing;



class XmpKeyTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if necessary

    }



    void TearDown() override {

        // Teardown code if necessary

    }

};



TEST_F(XmpKeyTest_1266, TagDesc_ReturnsNonEmptyStringWhenPropertyExists_1266) {

    Exiv2::XmpKey xmpKey("prefix", "property");

    EXPECT_FALSE(xmpKey.tagDesc().empty());

}



TEST_F(XmpKeyTest_1266, TagDesc_ReturnsEmptyStringWhenPropertyDoesNotExist_1266) {

    Exiv2::XmpKey xmpKey("nonexistent_prefix", "nonexistent_property");

    EXPECT_TRUE(xmpKey.tagDesc().empty());

}



TEST_F(XmpKeyTest_1266, TagDesc_HandlesDefaultConstructedKey_1266) {

    Exiv2::XmpKey defaultConstructedKey;

    EXPECT_TRUE(defaultConstructedKey.tagDesc().empty());

}



TEST_F(XmpKeyTest_1266, TagDesc_HandlesCopyConstructedKey_1266) {

    Exiv2::XmpKey originalKey("prefix", "property");

    Exiv2::XmpKey copyConstructedKey = originalKey;

    EXPECT_EQ(originalKey.tagDesc(), copyConstructedKey.tagDesc());

}



TEST_F(XmpKeyTest_1266, TagDesc_HandlesAssignmentOperator_1266) {

    Exiv2::XmpKey originalKey("prefix", "property");

    Exiv2::XmpKey assignedKey;

    assignedKey = originalKey;

    EXPECT_EQ(originalKey.tagDesc(), assignedKey.tagDesc());

}



TEST_F(XmpKeyTest_1266, TagDesc_HandlesDifferentProperties_1266) {

    Exiv2::XmpKey key1("prefix", "property1");

    Exiv2::XmpKey key2("prefix", "property2");

    EXPECT_NE(key1.tagDesc(), key2.tagDesc());

}



TEST_F(XmpKeyTest_1266, TagDesc_HandlesEmptyPrefixAndProperty_1266) {

    Exiv2::XmpKey emptyKey("", "");

    EXPECT_TRUE(emptyKey.tagDesc().empty());

}
