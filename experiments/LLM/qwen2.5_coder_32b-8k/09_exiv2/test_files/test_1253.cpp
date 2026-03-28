#include <gtest/gtest.h>

#include "exiv2/properties.hpp"



namespace {



class XmpPropertiesTest_1253 : public ::testing::Test {

protected:

    Exiv2::XmpProperties xmpProperties;

};



TEST_F(XmpPropertiesTest_1253, NsDesc_ReturnsValidDescription_1253) {

    const char* desc = xmpProperties.nsDesc("dc");

    ASSERT_NE(desc, nullptr);

}



TEST_F(XmpPropertiesTest_1253, NsDesc_HandlesUnknownPrefix_1253) {

    const char* desc = xmpProperties.nsDesc("unknown_prefix");

    EXPECT_EQ(desc, "");

}



TEST_F(XmpPropertiesTest_1253, NsDesc_BoundaryCondition_EmptyString_1253) {

    const char* desc = xmpProperties.nsDesc("");

    EXPECT_EQ(desc, "");

}



TEST_F(XmpPropertiesTest_1253, NsDesc_BoundaryCondition_MaxLengthPrefix_1253) {

    std::string max_length_prefix(1024, 'a'); // Assuming a reasonable max length

    const char* desc = xmpProperties.nsDesc(max_length_prefix);

    EXPECT_EQ(desc, "");

}



TEST_F(XmpPropertiesTest_1253, NsDesc_BoundaryCondition_SpecialCharacters_1253) {

    const char* desc = xmpProperties.nsDesc("!@#$%^&*()");

    EXPECT_EQ(desc, "");

}



}  // namespace
