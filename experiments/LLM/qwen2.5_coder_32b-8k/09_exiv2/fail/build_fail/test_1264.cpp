#include <gtest/gtest.h>

#include "exiv2/properties.hpp"



using namespace Exiv2;



class XmpKeyTest_1264 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



// Test normal operation of tagName()

TEST_F(XmpKeyTest_1264, TagName_ReturnsCorrectProperty_1264) {

    XmpKey xmpKey("prefix", "property");

    EXPECT_EQ(xmpKey.tagName(), "property");

}



// Test boundary condition with empty property

TEST_F(XmpKeyTest_1264, TagName_EmptyProperty_ReturnsEmptyString_1264) {

    XmpKey xmpKey("prefix", "");

    EXPECT_EQ(xmpKey.tagName(), "");

}



// Test boundary condition with empty prefix and property

TEST_F(XmpKeyTest_1264, TagName_EmptyPrefixAndProperty_ReturnsEmptyString_1264) {

    XmpKey xmpKey("", "");

    EXPECT_EQ(xmpKey.tagName(), "");

}



// Test normal operation of copy constructor

TEST_F(XmpKeyTest_1264, CopyConstructor_CopiesTagNameCorrectly_1264) {

    XmpKey original("prefix", "property");

    XmpKey copy(original);

    EXPECT_EQ(copy.tagName(), "property");

}



// Test normal operation of assignment operator

TEST_F(XmpKeyTest_1264, AssignmentOperator_AssignsTagNameCorrectly_1264) {

    XmpKey original("prefix", "originalProperty");

    XmpKey assigned;

    assigned = original;

    EXPECT_EQ(assigned.tagName(), "originalProperty");

}



// Test normal operation of clone method

TEST_F(XmpKeyTest_1264, Clone_ClonesTagNameCorrectly_1264) {

    XmpKey original("prefix", "property");

    auto clone = dynamic_cast<XmpKey*>(original.clone().release());

    EXPECT_EQ(clone->tagName(), "property");

    delete clone;

}



// Test boundary condition with very long property string

TEST_F(XmpKeyTest_1264, TagName_VeryLongProperty_ReturnsCorrectString_1264) {

    std::string longProperty(1000, 'a');

    XmpKey xmpKey("prefix", longProperty);

    EXPECT_EQ(xmpKey.tagName(), longProperty);

}
