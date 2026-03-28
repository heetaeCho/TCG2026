#include <gtest/gtest.h>

#include "exiv2/properties.hpp"

#include "exiv2/types.hpp"



using namespace Exiv2;



class XmpPropertiesTest_1251 : public ::testing::Test {

protected:

    XmpProperties xmpProperties;

};



TEST_F(XmpPropertiesTest_1251, PropertyType_ReturnsDefaultForUnknownKey_1251) {

    XmpKey unknownKey("unknown/property");

    EXPECT_EQ(xmpProperties.propertyType(unknownKey), xmpText);

}



TEST_F(XmpPropertiesTest_1251, PropertyType_ReturnsCorrectTypeForKnownKey_1251) {

    // Assuming there is a known key with type 'asciiString' for testing

    XmpKey knownKey("known/property");

    EXPECT_EQ(xmpProperties.propertyType(knownKey), asciiString);

}



TEST_F(XmpPropertiesTest_1251, PropertyType_HandlesEmptyKeyGracefully_1251) {

    XmpKey emptyKey("");

    EXPECT_EQ(xmpProperties.propertyType(emptyKey), xmpText);

}
