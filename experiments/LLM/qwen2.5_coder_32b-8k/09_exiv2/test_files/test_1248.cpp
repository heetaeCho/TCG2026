#include <gtest/gtest.h>

#include "exiv2/properties.hpp"



using namespace Exiv2;



class XmpPropertiesTest_1248 : public ::testing::Test {

protected:

    XmpProperties xmpProperties;

};



TEST_F(XmpPropertiesTest_1248, Ns_ReturnsValidNamespaceForKnownPrefix_1248) {

    std::string result = xmpProperties.ns("dc");

    EXPECT_FALSE(result.empty());

}



TEST_F(XmpPropertiesTest_1248, Ns_ReturnsEmptyStringForUnknownPrefix_1248) {

    std::string result = xmpProperties.ns("unknown_prefix");

    EXPECT_TRUE(result.empty());

}



TEST_F(XmpPropertiesTest_1248, Ns_BoundaryConditionWithEmptyString_1248) {

    std::string result = xmpProperties.ns("");

    EXPECT_TRUE(result.empty());

}
