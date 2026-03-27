#include <gtest/gtest.h>

#include "exiv2/properties.hpp"



using namespace Exiv2;



class XmpPropertiesTest_1243 : public ::testing::Test {

protected:

    XmpNsInfo::Prefix prefix;

    const XmpNsInfo* result;



    void SetUp() override {

        // Initialize with a default value

        prefix.prefix_ = "default";

    }

};



TEST_F(XmpPropertiesTest_1243, LookupNsRegistry_ReturnsValidPointerForExistingPrefix_1243) {

    prefix.prefix_ = "exif";

    result = XmpProperties::lookupNsRegistry(prefix);

    EXPECT_NE(result, nullptr);

}



TEST_F(XmpPropertiesTest_1243, LookupNsRegistry_ReturnsNullptrForNonexistentPrefix_1243) {

    prefix.prefix_ = "nonexistent";

    result = XmpProperties::lookupNsRegistry(prefix);

    EXPECT_EQ(result, nullptr);

}



TEST_F(XmpPropertiesTest_1243, LookupNsRegistry_HandlesEmptyString_1243) {

    prefix.prefix_ = "";

    result = XmpProperties::lookupNsRegistry(prefix);

    EXPECT_EQ(result, nullptr);

}
