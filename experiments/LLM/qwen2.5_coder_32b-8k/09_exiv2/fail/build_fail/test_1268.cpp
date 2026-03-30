#include <gtest/gtest.h>

#include <gmock/gmock-matchers.h>

#include "exiv2/properties.hpp"

#include <string>



using namespace Exiv2;



class XmpKeyTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code, if any

    }



    void TearDown() override {

        // Teardown code, if any

    }

};



TEST_F(XmpKeyTest_Ns_ReturnsExpectedNamespace_1268) {

    XmpKey key("prefix", "property");

    EXPECT_EQ(key.ns(), XmpProperties::ns("prefix"));

}



TEST_F(XmpKeyTest_DefaultConstructor_ThrowsNoException_1268) {

    EXPECT_NO_THROW(XmpKey key);

}



TEST_F(XmpKeyTest_CopyConstructor_CopiesNamespace_1268) {

    XmpKey original("prefix", "property");

    XmpKey copy(original);

    EXPECT_EQ(copy.ns(), original.ns());

}



TEST_F(XmpKeyTest_AssignmentOperator_PreservesNamespace_1268) {

    XmpKey key1("prefix1", "property1");

    XmpKey key2("prefix2", "property2");

    key2 = key1;

    EXPECT_EQ(key2.ns(), key1.ns());

}



TEST_F(XmpKeyTest_EmptyPrefix_ReturnsEmptyNamespace_1268) {

    XmpKey key("", "property");

    EXPECT_EQ(key.ns(), "");

}



TEST_F(XmpKeyTest_EmptyProperty_ReturnsExpectedNamespace_1268) {

    XmpKey key("prefix", "");

    EXPECT_EQ(key.ns(), XmpProperties::ns("prefix"));

}
