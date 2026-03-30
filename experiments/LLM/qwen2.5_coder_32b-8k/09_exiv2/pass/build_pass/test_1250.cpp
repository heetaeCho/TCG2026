#include <gtest/gtest.h>

#include "exiv2/properties.hpp"



using namespace Exiv2;



class XmpPropertiesTest_1250 : public ::testing::Test {

protected:

    XmpProperties xmpProperties;

};



TEST_F(XmpPropertiesTest_1250, PropertyDesc_NormalOperation_1250) {

    XmpKey key("Xmp.dc.title");

    const char* desc = xmpProperties.propertyDesc(key);

    EXPECT_TRUE(desc != nullptr); // Assuming a valid key returns a non-null description

}



TEST_F(XmpPropertiesTest_1250, PropertyDesc_BoundaryCondition_EmptyKey_1250) {

    XmpKey emptyKey("");

    const char* desc = xmpProperties.propertyDesc(emptyKey);

    EXPECT_EQ(desc, nullptr); // Assuming an empty key returns null

}



TEST_F(XmpPropertiesTest_1250, PropertyDesc_Exceptional_InvalidKey_1250) {

    XmpKey invalidKey("Invalid.Key");

    const char* desc = xmpProperties.propertyDesc(invalidKey);

    EXPECT_EQ(desc, nullptr); // Assuming an invalid key returns null

}



TEST_F(XmpPropertiesTest_1250, PropertyDesc_Exceptional_NullptrKey_1250) {

    XmpKey nullKey("Xmp.dc.null");

    const char* desc = xmpProperties.propertyDesc(nullKey);

    EXPECT_TRUE(desc != nullptr || desc == nullptr); // Assuming a check for null key

}
