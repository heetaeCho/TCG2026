#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/properties.hpp"

#include "exiv2/xmp_exiv2.hpp"



using namespace Exiv2;

using ::testing::MockFunction;



class XmpPropertiesTest_1256 : public ::testing::Test {

protected:

    Dictionary nsDict;

};



TEST_F(XmpPropertiesTest_1256, RegisteredNamespaces_PopulatesDictionaryWithAllKnownNamespaces_1256) {

    XmpProperties xmpProperties;

    xmpProperties.registeredNamespaces(nsDict);

    

    // Assuming that there are 47 entries in the global xmpNsInfo array

    EXPECT_EQ(47, nsDict.size());

}



TEST_F(XmpPropertiesTest_1256, RegisteredNamespaces_AddsCorrectNamespaceAndPrefix_1256) {

    XmpProperties xmpProperties;

    xmpProperties.registeredNamespaces(nsDict);

    

    // Example check for the first namespace

    EXPECT_EQ("http://purl.org/dc/elements/1.1/", nsDict["dc"].first);

}



TEST_F(XmpPropertiesTest_1256, RegisteredNamespaces_HandlesEmptyDictionary_1256) {

    XmpProperties xmpProperties;

    Dictionary emptyDict;

    xmpProperties.registeredNamespaces(emptyDict);

    

    EXPECT_EQ(47, emptyDict.size());

}



// Exceptional or error cases are not directly observable from the interface

// as it doesn't throw exceptions and always populates the dictionary.



TEST_F(XmpPropertiesTest_1256, RegisteredNamespaces_MultipleCallsConsistentResults_1256) {

    XmpProperties xmpProperties;

    xmpProperties.registeredNamespaces(nsDict);

    Dictionary nsDictCopy;

    xmpProperties.registeredNamespaces(nsDictCopy);



    EXPECT_EQ(nsDict, nsDictCopy);

}
