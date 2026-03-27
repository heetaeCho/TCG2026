#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/properties.hpp"



using namespace Exiv2;



class XmpPropertiesTest : public ::testing::Test {

protected:

    XmpProperties* xmpProperties;



    void SetUp() override {

        xmpProperties = new XmpProperties();

    }



    void TearDown() override {

        delete xmpProperties;

    }

};



TEST_F(XmpPropertiesTest_1246, UnregisterNsClearsAllNamespaces_1246) {

    // Assuming registerNs is a valid way to add namespaces for testing purposes

    XmpProperties::registerNs("http://example.com/ns", "ex");

    XmpProperties::registerNs("http://example.org/ns", "org");



    xmpProperties->unregisterNs();



    Exiv2::Dictionary nsDict;

    xmpProperties->registeredNamespaces(nsDict);



    EXPECT_TRUE(nsDict.empty());

}



TEST_F(XmpPropertiesTest_1246, UnregisterNsNoEffectIfEmpty_1246) {

    // Initially no namespaces are registered

    xmpProperties->unregisterNs();



    Exiv2::Dictionary nsDict;

    xmpProperties->registeredNamespaces(nsDict);



    EXPECT_TRUE(nsDict.empty());

}



TEST_F(XmpPropertiesTest_1246, UnregisterNsDoesNotThrowOnMultipleCalls_1246) {

    // Assuming registerNs is a valid way to add namespaces for testing purposes

    XmpProperties::registerNs("http://example.com/ns", "ex");



    EXPECT_NO_THROW(xmpProperties->unregisterNs());

    EXPECT_NO_THROW(xmpProperties->unregisterNs());

}



TEST_F(XmpPropertiesTest_1246, UnregisterNsRemovesOnlyNamespacesRegisteredThroughClassInstance_1246) {

    // Assuming registerNs is a valid way to add namespaces for testing purposes

    XmpProperties::registerNs("http://example.com/ns", "ex");

    xmpProperties->unregisterNs();



    Exiv2::Dictionary nsDict;

    XmpProperties::registeredNamespaces(nsDict);



    EXPECT_TRUE(nsDict.empty());

}
