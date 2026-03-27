#include <gtest/gtest.h>

#include "exiv2/properties.hpp"

#include <string>



using namespace Exiv2;



class XmpPropertiesTest_1254 : public ::testing::Test {

protected:

    XmpProperties xmpProperties;

};



TEST_F(XmpPropertiesTest_1254, PropertyList_NormalOperation_1254) {

    const std::string prefix = "dc";

    const XmpPropertyInfo* result = xmpProperties.propertyList(prefix);

    EXPECT_NE(result, nullptr); // Assuming a valid prefix returns non-null

}



TEST_F(XmpPropertiesTest_1254, PropertyList_EmptyPrefix_1254) {

    const std::string emptyPrefix = "";

    const XmpPropertyInfo* result = xmpProperties.propertyList(emptyPrefix);

    EXPECT_EQ(result, nullptr); // Assuming an empty prefix returns null

}



TEST_F(XmpPropertiesTest_1254, PropertyList_UnknownPrefix_1254) {

    const std::string unknownPrefix = "unknown";

    const XmpPropertyInfo* result = xmpProperties.propertyList(unknownPrefix);

    EXPECT_EQ(result, nullptr); // Assuming an unknown prefix returns null

}



TEST_F(XmpPropertiesTest_1254, PropertyList_ValidPrefix_ReturnsValidPointer_1254) {

    const std::string validPrefix = "dc";

    const XmpPropertyInfo* result = xmpProperties.propertyList(validPrefix);

    EXPECT_NE(result, nullptr); // Assuming a valid prefix returns non-null

}



TEST_F(XmpPropertiesTest_1254, PropertyList_ValidPrefix_ReturnsConsistentPointer_1254) {

    const std::string validPrefix = "dc";

    const XmpPropertyInfo* result1 = xmpProperties.propertyList(validPrefix);

    const XmpPropertyInfo* result2 = xmpProperties.propertyList(validPrefix);

    EXPECT_EQ(result1, result2); // Assuming consistent results for the same prefix

}



TEST_F(XmpPropertiesTest_1254, PropertyList_ValidPrefix_ReturnsDifferentPointerForDifferentPrefixes_1254) {

    const std::string prefix1 = "dc";

    const std::string prefix2 = "xmp";

    const XmpPropertyInfo* result1 = xmpProperties.propertyList(prefix1);

    const XmpPropertyInfo* result2 = xmpProperties.propertyList(prefix2);

    EXPECT_NE(result1, result2); // Assuming different prefixes return different pointers

}
