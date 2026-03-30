#include <gtest/gtest.h>

#include <exiv2/properties.hpp>



using namespace Exiv2;



class XmpPropertiesTest : public ::testing::Test {

protected:

    XmpProperties xmpProperties;

};



TEST_F(XmpPropertiesTest, Prefix_ReturnsCorrectPrefix_1247) {

    EXPECT_EQ(xmpProperties.prefix("http://purl.org/dc/elements/1.1/"), "dc");

}



TEST_F(XmpPropertiesTest, Prefix_AddsSlashIfMissing_1247) {

    EXPECT_EQ(xmpProperties.prefix("http://www.digikam.org/ns/1.0"), "digiKam");

}



TEST_F(XmpPropertiesTest, Prefix_ReturnsEmptyForUnknownNamespace_1247) {

    EXPECT_EQ(xmpProperties.prefix("unknown_namespace"), "");

}



TEST_F(XmpPropertiesTest, Prefix_HandlesHashEndingNamespace_1247) {

    EXPECT_EQ(xmpProperties.prefix("http://ns.microsoft.com/photo/1.2/t/RegionInfo#"), "MPRI");

}



TEST_F(XmpPropertiesTest, Prefix_IgnoresTrailingSlashInKnownNamespace_1247) {

    EXPECT_EQ(xmpProperties.prefix("http://purl.org/dc/elements/1.1//"), "dc");

}
