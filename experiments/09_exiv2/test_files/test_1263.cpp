#include <gtest/gtest.h>

#include "exiv2/properties.hpp"



using namespace Exiv2;



class XmpKeyTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Any setup if needed in future

    }



    void TearDown() override {

        // Any teardown if needed in future

    }

};



TEST_F(XmpKeyTest_1263, GroupName_ReturnsPrefix_1263) {

    XmpKey key("prefix", "property");

    EXPECT_EQ(key.groupName(), "prefix");

}



TEST_F(XmpKeyTest_1263, DefaultConstructor_GroupName_EmptyString_1263) {

    XmpKey key;

    EXPECT_EQ(key.groupName(), "");

}



TEST_F(XmpKeyTest_1263, CopyConstructor_GroupName_SameAsOriginal_1263) {

    XmpKey original("prefix", "property");

    XmpKey copy = original;

    EXPECT_EQ(copy.groupName(), original.groupName());

}



TEST_F(XmpKeyTest_1263, AssignmentOperator_GroupName_SameAsAssigned_1263) {

    XmpKey original("prefix", "property");

    XmpKey assigned;

    assigned = original;

    EXPECT_EQ(assigned.groupName(), original.groupName());

}
