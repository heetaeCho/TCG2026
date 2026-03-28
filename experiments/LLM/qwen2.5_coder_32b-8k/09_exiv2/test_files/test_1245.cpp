#include <gtest/gtest.h>

#include "exiv2/properties.hpp"

#include <string>



using namespace Exiv2;



class XmpPropertiesTest : public ::testing::Test {

protected:

    XmpProperties xmpProperties;

};



TEST_F(XmpPropertiesTest_1245, UnregisterNsValidNamespace_1245) {

    // Assuming unregistering a valid namespace should not throw an exception

    std::string ns = "http://www.example.com/ns";

    EXPECT_NO_THROW(xmpProperties.unregisterNs(ns));

}



TEST_F(XmpPropertiesTest_1245, UnregisterNsEmptyString_1245) {

    // Boundary condition: unregistering with an empty string

    std::string ns = "";

    EXPECT_NO_THROW(xmpProperties.unregisterNs(ns));

}



TEST_F(XmpPropertiesTest_1245, UnregisterNsNonExistentNamespace_1245) {

    // Assuming unregistering a non-existent namespace should not throw an exception

    std::string ns = "http://www.nonexistent.com/ns";

    EXPECT_NO_THROW(xmpProperties.unregisterNs(ns));

}



TEST_F(XmpPropertiesTest_1245, UnregisterNsMaxSizeString_1245) {

    // Boundary condition: unregistering with a string of maximum size

    std::string ns(1024, 'a'); // Assuming 1024 is a reasonable max length for a namespace

    EXPECT_NO_THROW(xmpProperties.unregisterNs(ns));

}



TEST_F(XmpPropertiesTest_1245, UnregisterNsSpecialCharacters_1245) {

    // Test with special characters in the namespace

    std::string ns = "http://www.example.com/!@#$%^&*()";

    EXPECT_NO_THROW(xmpProperties.unregisterNs(ns));

}
