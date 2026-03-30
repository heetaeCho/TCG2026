#include <gtest/gtest.h>

#include "exiv2/properties.hpp"



using namespace Exiv2;



class XmpKeyTest : public ::testing::Test {

protected:

    void SetUp() override {}

    void TearDown() override {}



    std::string validXmpKey = "Xmp.dc.title";

};



TEST_F(XmpKeyTest_2178, ConstructorWithSingleString_ValidKey_2178) {

    XmpKey xmpKey(validXmpKey);

    EXPECT_EQ(xmpKey.key(), validXmpKey);

}



TEST_F(XmpKeyTest_2178, ConstructorWithPrefixAndProperty_ValidKey_2178) {

    std::string prefix = "Xmp.dc";

    std::string property = "title";

    XmpKey xmpKey(prefix, property);

    EXPECT_EQ(xmpKey.key(), validXmpKey);

}



TEST_F(XmpKeyTest_2178, CopyConstructor_ValidKey_2178) {

    XmpKey original(validXmpKey);

    XmpKey copy(original);

    EXPECT_EQ(copy.key(), original.key());

}



TEST_F(XmpKeyTest_2178, AssignmentOperator_ValidKey_2178) {

    XmpKey original(validXmpKey);

    XmpKey assigned;

    assigned = original;

    EXPECT_EQ(assigned.key(), original.key());

}



TEST_F(XmpKeyTest_2178, KeyFunction_ReturnsCorrectKey_2178) {

    XmpKey xmpKey(validXmpKey);

    EXPECT_EQ(xmpKey.key(), validXmpKey);

}



TEST_F(XmpKeyTest_2178, CloneFunction_ReturnsNewInstanceWithSameKey_2178) {

    XmpKey original(validXmpKey);

    XmpKey* cloned = dynamic_cast<XmpKey*>(original.clone().release());

    EXPECT_NE(cloned, nullptr);

    EXPECT_EQ(cloned->key(), validXmpKey);

    delete cloned;

}



TEST_F(XmpKeyTest_2178, FamilyName_ReturnsExpectedValue_2178) {

    XmpKey xmpKey(validXmpKey);

    EXPECT_STREQ(xmpKey.familyName(), "Xmp");

}



TEST_F(XmpKeyTest_2178, GroupName_ReturnsExpectedValue_2178) {

    XmpKey xmpKey(validXmpKey);

    EXPECT_EQ(xmpKey.groupName(), "dc");

}



TEST_F(XmpKeyTest_2178, TagName_ReturnsExpectedValue_2178) {

    XmpKey xmpKey(validXmpKey);

    EXPECT_EQ(xmpKey.tagName(), "title");

}



TEST_F(XmpKeyTest_2178, TagLabel_ReturnsEmptyString_2178) {

    XmpKey xmpKey(validXmpKey);

    EXPECT_EQ(xmpKey.tagLabel(), "");

}



TEST_F(XmpKeyTest_2178, TagDesc_ReturnsEmptyString_2178) {

    XmpKey xmpKey(validXmpKey);

    EXPECT_EQ(xmpKey.tagDesc(), "");

}



TEST_F(XmpKeyTest_2178, Tag_ReturnsZero_2178) {

    XmpKey xmpKey(validXmpKey);

    EXPECT_EQ(xmpKey.tag(), 0);

}



TEST_F(XmpKeyTest_2178, Ns_ReturnsExpectedNamespace_2178) {

    XmpKey xmpKey(validXmpKey);

    EXPECT_EQ(xmpKey.ns(), "http://purl.org/dc/elements/1.1/");

}



TEST_F(XmpKeyTest_2178, InvalidKey_ConstructorThrowsNoException_2178) {

    std::string invalidKey = "Invalid.Key";

    EXPECT_NO_THROW(XmpKey xmpKey(invalidKey));

}
