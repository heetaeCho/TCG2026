#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/properties.hpp"

#include <string>



using namespace Exiv2;

using ::testing::Return;



class XmpPropertiesTest : public ::testing::Test {

protected:

    XmpKey key1;

    XmpKey key2;

    XmpKey nestedKey;



    XmpPropertiesTest()

        : key1("Xmp.dc.title"),

          key2("Xmp.dc.description"),

          nestedKey("Xmp.iptcExt:Cities/City[1]/CityName") {}



    ~XmpPropertiesTest() override = default;

};



TEST_F(XmpPropertiesTest, PropertyInfo_ReturnsValidPointerForExistingProperty_1252) {

    const XmpPropertyInfo* info = XmpProperties::propertyInfo(key1);

    EXPECT_NE(info, nullptr);

}



TEST_F(XmpPropertiesTest, PropertyInfo_ReturnsNullptrForNonexistentProperty_1252) {

    XmpKey invalidKey("Xmp.dc.nonexistent");

    const XmpPropertyInfo* info = XmpProperties::propertyInfo(invalidKey);

    EXPECT_EQ(info, nullptr);

}



TEST_F(XmpPropertiesTest, PropertyInfo_HandlesNestedKeysCorrectly_1252) {

    const XmpPropertyInfo* info = XmpProperties::propertyInfo(nestedKey);

    EXPECT_NE(info, nullptr);

}



TEST_F(XmpPropertiesTest, PropertyInfo_ReturnsValidPointerForDifferentPrefix_1252) {

    const XmpPropertyInfo* info = XmpProperties::propertyInfo(key2);

    EXPECT_NE(info, nullptr);

}



TEST_F(XmpPropertiesTest, PropertyInfo_CorrectlyIdentifiesPropertyName_1252) {

    const XmpPropertyInfo* info = XmpProperties::propertyInfo(key1);

    ASSERT_NE(info, nullptr);

    EXPECT_TRUE(*info == "title");

}



TEST_F(XmpPropertiesTest, PropertyInfo_ReturnsNullptrForEmptyKey_1252) {

    XmpKey emptyKey("");

    const XmpPropertyInfo* info = XmpProperties::propertyInfo(emptyKey);

    EXPECT_EQ(info, nullptr);

}
