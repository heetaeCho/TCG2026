#include <gtest/gtest.h>

#include "exiv2/properties.hpp"

#include "exiv2/key.hpp"



namespace Exiv2 {



class XmpPropertiesTest : public ::testing::Test {

protected:

    XmpProperties xmpProperties;

};



TEST_F(XmpPropertiesTest_NormalOperation_1249, PropertyTitle_ReturnsCorrectTitleForValidKey_1249) {

    XmpKey key("Xmp.dc.title");

    const char* title = xmpProperties.propertyTitle(key);

    ASSERT_NE(title, nullptr);

    // Assuming a valid key should return a non-empty string

    EXPECT_STRNE(title, "");

}



TEST_F(XmpPropertiesTest_BoundaryConditions_1249, PropertyTitle_ReturnsNullForEmptyKey_1249) {

    XmpKey emptyKey("");

    const char* title = xmpProperties.propertyTitle(emptyKey);

    EXPECT_EQ(title, nullptr);

}



TEST_F(XmpPropertiesTest_ErrorCases_1249, PropertyTitle_ReturnsNullForInvalidKey_1249) {

    XmpKey invalidKey("Invalid.Key");

    const char* title = xmpProperties.propertyTitle(invalidKey);

    EXPECT_EQ(title, nullptr);

}



}  // namespace Exiv2
