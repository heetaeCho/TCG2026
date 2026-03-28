#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include "exiv2/properties.hpp"
#include "exiv2/value.hpp"
#include "exiv2/types.hpp"

namespace {

class XmpPropertiesTest_1255 : public ::testing::Test {
protected:
    void SetUp() override {
        // Unregister all custom namespaces to start clean
        Exiv2::XmpProperties::unregisterNs();
    }

    void TearDown() override {
        // Clean up any registered namespaces
        Exiv2::XmpProperties::unregisterNs();
    }
};

// Test nsInfo with a known built-in prefix
TEST_F(XmpPropertiesTest_1255, NsInfoReturnsNonNullForKnownPrefix_1255) {
    const Exiv2::XmpNsInfo* info = Exiv2::XmpProperties::nsInfo("dc");
    ASSERT_NE(info, nullptr);
}

// Test nsInfo with an unknown prefix
TEST_F(XmpPropertiesTest_1255, NsInfoReturnsNullForUnknownPrefix_1255) {
    const Exiv2::XmpNsInfo* info = Exiv2::XmpProperties::nsInfo("nonexistent_prefix_xyz");
    EXPECT_EQ(info, nullptr);
}

// Test nsInfo with empty prefix
TEST_F(XmpPropertiesTest_1255, NsInfoReturnsNullForEmptyPrefix_1255) {
    const Exiv2::XmpNsInfo* info = Exiv2::XmpProperties::nsInfo("");
    EXPECT_EQ(info, nullptr);
}

// Test ns() returns namespace for known prefix
TEST_F(XmpPropertiesTest_1255, NsReturnsNamespaceForKnownPrefix_1255) {
    std::string nsUri = Exiv2::XmpProperties::ns("dc");
    EXPECT_FALSE(nsUri.empty());
    EXPECT_EQ(nsUri, "http://purl.org/dc/elements/1.1/");
}

// Test ns() returns empty for unknown prefix
TEST_F(XmpPropertiesTest_1255, NsReturnsEmptyForUnknownPrefix_1255) {
    std::string nsUri = Exiv2::XmpProperties::ns("nonexistent_prefix_xyz");
    EXPECT_TRUE(nsUri.empty());
}

// Test prefix() returns prefix for known namespace
TEST_F(XmpPropertiesTest_1255, PrefixReturnsKnownPrefixForKnownNs_1255) {
    std::string pfx = Exiv2::XmpProperties::prefix("http://purl.org/dc/elements/1.1/");
    EXPECT_EQ(pfx, "dc");
}

// Test prefix() returns empty for unknown namespace
TEST_F(XmpPropertiesTest_1255, PrefixReturnsEmptyForUnknownNs_1255) {
    std::string pfx = Exiv2::XmpProperties::prefix("http://nonexistent.example.com/ns/");
    EXPECT_TRUE(pfx.empty());
}

// Test registerNs and then retrieve it
TEST_F(XmpPropertiesTest_1255, RegisterNsAndRetrieve_1255) {
    const std::string testNs = "http://test.example.com/ns/1255/";
    const std::string testPrefix = "test1255";

    Exiv2::XmpProperties::registerNs(testNs, testPrefix);

    std::string retrievedNs = Exiv2::XmpProperties::ns(testPrefix);
    EXPECT_EQ(retrievedNs, testNs);

    std::string retrievedPrefix = Exiv2::XmpProperties::prefix(testNs);
    EXPECT_EQ(retrievedPrefix, testPrefix);

    // Clean up
    Exiv2::XmpProperties::unregisterNs(testNs);
}

// Test unregisterNs removes a specific custom namespace
TEST_F(XmpPropertiesTest_1255, UnregisterNsRemovesSpecificNamespace_1255) {
    const std::string testNs = "http://test.example.com/ns/unregister/";
    const std::string testPrefix = "testunreg";

    Exiv2::XmpProperties::registerNs(testNs, testPrefix);
    std::string retrievedNs = Exiv2::XmpProperties::ns(testPrefix);
    EXPECT_EQ(retrievedNs, testNs);

    Exiv2::XmpProperties::unregisterNs(testNs);

    // After unregistering, the custom namespace should not be found via prefix lookup
    std::string afterUnregNs = Exiv2::XmpProperties::ns(testPrefix);
    EXPECT_TRUE(afterUnregNs.empty());
}

// Test unregisterNs (no args) removes all custom namespaces
TEST_F(XmpPropertiesTest_1255, UnregisterNsAllRemovesAllCustom_1255) {
    Exiv2::XmpProperties::registerNs("http://test1.example.com/", "testa");
    Exiv2::XmpProperties::registerNs("http://test2.example.com/", "testb");

    EXPECT_FALSE(Exiv2::XmpProperties::ns("testa").empty());
    EXPECT_FALSE(Exiv2::XmpProperties::ns("testb").empty());

    Exiv2::XmpProperties::unregisterNs();

    EXPECT_TRUE(Exiv2::XmpProperties::ns("testa").empty());
    EXPECT_TRUE(Exiv2::XmpProperties::ns("testb").empty());

    // Built-in namespaces should still work
    EXPECT_FALSE(Exiv2::XmpProperties::ns("dc").empty());
}

// Test propertyList for known prefix returns non-null
TEST_F(XmpPropertiesTest_1255, PropertyListReturnsNonNullForKnownPrefix_1255) {
    const Exiv2::XmpPropertyInfo* list = Exiv2::XmpProperties::propertyList("dc");
    EXPECT_NE(list, nullptr);
}

// Test propertyList for unknown prefix returns null
TEST_F(XmpPropertiesTest_1255, PropertyListReturnsNullForUnknownPrefix_1255) {
    const Exiv2::XmpPropertyInfo* list = Exiv2::XmpProperties::propertyList("nonexistent_prefix_xyz");
    EXPECT_EQ(list, nullptr);
}

// Test nsDesc for known prefix returns non-null
TEST_F(XmpPropertiesTest_1255, NsDescReturnsNonNullForKnownPrefix_1255) {
    const char* desc = Exiv2::XmpProperties::nsDesc("dc");
    EXPECT_NE(desc, nullptr);
}

// Test nsDesc for unknown prefix
TEST_F(XmpPropertiesTest_1255, NsDescReturnsNullForUnknownPrefix_1255) {
    const char* desc = Exiv2::XmpProperties::nsDesc("nonexistent_prefix_xyz");
    EXPECT_EQ(desc, nullptr);
}

// Test propertyTitle for known XmpKey
TEST_F(XmpPropertiesTest_1255, PropertyTitleForKnownKey_1255) {
    Exiv2::XmpKey key("Xmp.dc.title");
    const char* title = Exiv2::XmpProperties::propertyTitle(key);
    EXPECT_NE(title, nullptr);
}

// Test propertyDesc for known XmpKey
TEST_F(XmpPropertiesTest_1255, PropertyDescForKnownKey_1255) {
    Exiv2::XmpKey key("Xmp.dc.title");
    const char* desc = Exiv2::XmpProperties::propertyDesc(key);
    EXPECT_NE(desc, nullptr);
}

// Test propertyType for known XmpKey returns a valid type
TEST_F(XmpPropertiesTest_1255, PropertyTypeForKnownKey_1255) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::TypeId type = Exiv2::XmpProperties::propertyType(key);
    EXPECT_NE(type, Exiv2::invalidTypeId);
}

// Test propertyInfo for known XmpKey
TEST_F(XmpPropertiesTest_1255, PropertyInfoForKnownKey_1255) {
    Exiv2::XmpKey key("Xmp.dc.title");
    const Exiv2::XmpPropertyInfo* info = Exiv2::XmpProperties::propertyInfo(key);
    EXPECT_NE(info, nullptr);
}

// Test propertyInfo for unknown property returns null
TEST_F(XmpPropertiesTest_1255, PropertyInfoForUnknownProperty_1255) {
    Exiv2::XmpKey key("Xmp.dc.nonExistentPropertyXyz");
    const Exiv2::XmpPropertyInfo* info = Exiv2::XmpProperties::propertyInfo(key);
    EXPECT_EQ(info, nullptr);
}

// Test registeredNamespaces returns a dictionary with built-in namespaces
TEST_F(XmpPropertiesTest_1255, RegisteredNamespacesContainsBuiltIn_1255) {
    Exiv2::Dictionary nsDict;
    Exiv2::XmpProperties::registeredNamespaces(nsDict);
    EXPECT_FALSE(nsDict.empty());
    // dc should be present
    auto it = nsDict.find("http://purl.org/dc/elements/1.1/");
    EXPECT_NE(it, nsDict.end());
}

// Test registeredNamespaces includes custom registered namespace
TEST_F(XmpPropertiesTest_1255, RegisteredNamespacesIncludesCustom_1255) {
    const std::string testNs = "http://test.example.com/ns/dict/";
    const std::string testPrefix = "testdict";

    Exiv2::XmpProperties::registerNs(testNs, testPrefix);

    Exiv2::Dictionary nsDict;
    Exiv2::XmpProperties::registeredNamespaces(nsDict);

    auto it = nsDict.find(testNs);
    EXPECT_NE(it, nsDict.end());
    if (it != nsDict.end()) {
        EXPECT_EQ(it->second, testPrefix);
    }

    Exiv2::XmpProperties::unregisterNs(testNs);
}

// Test printProperties does not crash for known prefix
TEST_F(XmpPropertiesTest_1255, PrintPropertiesDoesNotCrashForKnownPrefix_1255) {
    std::ostringstream os;
    EXPECT_NO_THROW(Exiv2::XmpProperties::printProperties(os, "dc"));
    EXPECT_FALSE(os.str().empty());
}

// Test printProperties for unknown prefix
TEST_F(XmpPropertiesTest_1255, PrintPropertiesForUnknownPrefix_1255) {
    std::ostringstream os;
    // This may throw or produce empty output; we just verify no undefined behavior
    try {
        Exiv2::XmpProperties::printProperties(os, "nonexistent_prefix_xyz");
    } catch (...) {
        // acceptable
    }
}

// Test printProperty does not crash
TEST_F(XmpPropertiesTest_1255, PrintPropertyDoesNotCrash_1255) {
    std::ostringstream os;
    Exiv2::XmpTextValue val("test value");
    EXPECT_NO_THROW(Exiv2::XmpProperties::printProperty(os, "Xmp.dc.title", val));
}

// Test lookupNsRegistry for non-registered prefix returns null
TEST_F(XmpPropertiesTest_1255, LookupNsRegistryReturnsNullForUnregistered_1255) {
    Exiv2::XmpNsInfo::Prefix prefix("nonexistent_prefix_xyz");
    const Exiv2::XmpNsInfo* info = Exiv2::XmpProperties::lookupNsRegistry(prefix);
    EXPECT_EQ(info, nullptr);
}

// Test lookupNsRegistry for registered custom prefix returns non-null
TEST_F(XmpPropertiesTest_1255, LookupNsRegistryReturnsNonNullForRegistered_1255) {
    const std::string testNs = "http://test.example.com/ns/lookup/";
    const std::string testPrefix = "testlookup";

    Exiv2::XmpProperties::registerNs(testNs, testPrefix);

    Exiv2::XmpNsInfo::Prefix prefix(testPrefix);
    const Exiv2::XmpNsInfo* info = Exiv2::XmpProperties::lookupNsRegistry(prefix);
    EXPECT_NE(info, nullptr);

    Exiv2::XmpProperties::unregisterNs(testNs);
}

// Test nsInfo for xmp prefix (another built-in)
TEST_F(XmpPropertiesTest_1255, NsInfoForXmpPrefix_1255) {
    const Exiv2::XmpNsInfo* info = Exiv2::XmpProperties::nsInfo("xmp");
    ASSERT_NE(info, nullptr);
}

// Test nsInfo for exif prefix
TEST_F(XmpPropertiesTest_1255, NsInfoForExifPrefix_1255) {
    const Exiv2::XmpNsInfo* info = Exiv2::XmpProperties::nsInfo("exif");
    ASSERT_NE(info, nullptr);
}

// Test nsInfo for tiff prefix
TEST_F(XmpPropertiesTest_1255, NsInfoForTiffPrefix_1255) {
    const Exiv2::XmpNsInfo* info = Exiv2::XmpProperties::nsInfo("tiff");
    ASSERT_NE(info, nullptr);
}

// Test registering the same namespace twice with different prefix (overwrite behavior)
TEST_F(XmpPropertiesTest_1255, RegisterSameNsTwiceDifferentPrefix_1255) {
    const std::string testNs = "http://test.example.com/ns/duplicate/";
    
    Exiv2::XmpProperties::registerNs(testNs, "first");
    Exiv2::XmpProperties::registerNs(testNs, "second");

    // The prefix should be the latest registration
    std::string pfx = Exiv2::XmpProperties::prefix(testNs);
    EXPECT_EQ(pfx, "second");

    Exiv2::XmpProperties::unregisterNs(testNs);
}

// Test that built-in namespaces are not removed by unregisterNs(ns)
TEST_F(XmpPropertiesTest_1255, UnregisterBuiltInNsDoesNotRemove_1255) {
    std::string dcNs = Exiv2::XmpProperties::ns("dc");
    EXPECT_FALSE(dcNs.empty());

    // Attempting to unregister a built-in namespace
    try {
        Exiv2::XmpProperties::unregisterNs(dcNs);
    } catch (...) {
        // May throw or silently ignore
    }

    // dc should still be available since it's built-in
    std::string dcNsAfter = Exiv2::XmpProperties::ns("dc");
    EXPECT_FALSE(dcNsAfter.empty());
}

// Test nsInfo for custom registered prefix
TEST_F(XmpPropertiesTest_1255, NsInfoForCustomRegisteredPrefix_1255) {
    const std::string testNs = "http://test.example.com/ns/nsinfo/";
    const std::string testPrefix = "testnsinfo";

    Exiv2::XmpProperties::registerNs(testNs, testPrefix);

    const Exiv2::XmpNsInfo* info = Exiv2::XmpProperties::nsInfo(testPrefix);
    EXPECT_NE(info, nullptr);

    Exiv2::XmpProperties::unregisterNs(testNs);
}

// Test that after unregistering a custom ns, nsInfo returns null for that prefix
TEST_F(XmpPropertiesTest_1255, NsInfoNullAfterUnregister_1255) {
    const std::string testNs = "http://test.example.com/ns/unreg2/";
    const std::string testPrefix = "testunreg2";

    Exiv2::XmpProperties::registerNs(testNs, testPrefix);
    EXPECT_NE(Exiv2::XmpProperties::nsInfo(testPrefix), nullptr);

    Exiv2::XmpProperties::unregisterNs(testNs);
    const Exiv2::XmpNsInfo* info = Exiv2::XmpProperties::nsInfo(testPrefix);
    EXPECT_EQ(info, nullptr);
}

// Test multiple known prefixes
TEST_F(XmpPropertiesTest_1255, MultipleKnownPrefixes_1255) {
    std::vector<std::string> knownPrefixes = {"dc", "xmp", "xmpRights", "xmpMM", "xmpBJ", "xmpTPg"};
    for (const auto& pfx : knownPrefixes) {
        std::string nsUri = Exiv2::XmpProperties::ns(pfx);
        EXPECT_FALSE(nsUri.empty()) << "Expected non-empty ns for prefix: " << pfx;
    }
}

} // namespace
