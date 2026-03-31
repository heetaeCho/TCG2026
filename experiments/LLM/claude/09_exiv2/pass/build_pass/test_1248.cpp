#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>

#include "exiv2/properties.hpp"
#include "exiv2/value.hpp"
#include "exiv2/xmp_exiv2.hpp"

namespace {

class XmpPropertiesTest_1248 : public ::testing::Test {
protected:
    void SetUp() override {
        // Unregister all custom namespaces to start fresh
        Exiv2::XmpProperties::unregisterNs();
    }

    void TearDown() override {
        // Clean up any registered namespaces
        Exiv2::XmpProperties::unregisterNs();
    }
};

// Test that ns() returns the correct namespace for a well-known prefix
TEST_F(XmpPropertiesTest_1248, NsReturnsCorrectNamespaceForKnownPrefix_1248) {
    std::string result = Exiv2::XmpProperties::ns("dc");
    EXPECT_EQ(result, "http://purl.org/dc/elements/1.1/");
}

// Test that ns() returns the correct namespace for "xmp" prefix
TEST_F(XmpPropertiesTest_1248, NsReturnsCorrectNamespaceForXmpPrefix_1248) {
    std::string result = Exiv2::XmpProperties::ns("xmp");
    EXPECT_EQ(result, "http://ns.adobe.com/xap/1.0/");
}

// Test that ns() returns the correct namespace for "exif" prefix
TEST_F(XmpPropertiesTest_1248, NsReturnsCorrectNamespaceForExifPrefix_1248) {
    std::string result = Exiv2::XmpProperties::ns("exif");
    EXPECT_EQ(result, "http://ns.adobe.com/exif/1.0/");
}

// Test that ns() returns the correct namespace for "tiff" prefix
TEST_F(XmpPropertiesTest_1248, NsReturnsCorrectNamespaceForTiffPrefix_1248) {
    std::string result = Exiv2::XmpProperties::ns("tiff");
    EXPECT_EQ(result, "http://ns.adobe.com/tiff/1.0/");
}

// Test that ns() throws for an unknown prefix
TEST_F(XmpPropertiesTest_1248, NsThrowsForUnknownPrefix_1248) {
    EXPECT_THROW(Exiv2::XmpProperties::ns("nonexistent_prefix_xyz"), std::exception);
}

// Test that prefix() returns the correct prefix for a well-known namespace
TEST_F(XmpPropertiesTest_1248, PrefixReturnsCorrectPrefixForKnownNs_1248) {
    std::string result = Exiv2::XmpProperties::prefix("http://purl.org/dc/elements/1.1/");
    EXPECT_EQ(result, "dc");
}

// Test that prefix() returns empty string for unknown namespace
TEST_F(XmpPropertiesTest_1248, PrefixReturnsEmptyForUnknownNs_1248) {
    std::string result = Exiv2::XmpProperties::prefix("http://nonexistent.example.com/");
    EXPECT_TRUE(result.empty());
}

// Test registerNs and then retrieve via ns()
TEST_F(XmpPropertiesTest_1248, RegisterNsAndRetrieveViaPrefix_1248) {
    Exiv2::XmpProperties::registerNs("http://example.com/test/", "testprefix");
    std::string result = Exiv2::XmpProperties::ns("testprefix");
    EXPECT_EQ(result, "http://example.com/test/");
}

// Test registerNs and then retrieve prefix via ns
TEST_F(XmpPropertiesTest_1248, RegisterNsAndRetrievePrefix_1248) {
    Exiv2::XmpProperties::registerNs("http://example.com/test2/", "testpfx2");
    std::string result = Exiv2::XmpProperties::prefix("http://example.com/test2/");
    EXPECT_EQ(result, "testpfx2");
}

// Test unregisterNs removes specific namespace
TEST_F(XmpPropertiesTest_1248, UnregisterNsRemovesSpecificNamespace_1248) {
    Exiv2::XmpProperties::registerNs("http://example.com/unreg/", "unregpfx");
    std::string result = Exiv2::XmpProperties::ns("unregpfx");
    EXPECT_EQ(result, "http://example.com/unreg/");

    Exiv2::XmpProperties::unregisterNs("http://example.com/unreg/");
    EXPECT_THROW(Exiv2::XmpProperties::ns("unregpfx"), std::exception);
}

// Test unregisterNs() removes all custom namespaces
TEST_F(XmpPropertiesTest_1248, UnregisterAllNsRemovesCustomNamespaces_1248) {
    Exiv2::XmpProperties::registerNs("http://example.com/all1/", "allpfx1");
    Exiv2::XmpProperties::registerNs("http://example.com/all2/", "allpfx2");

    Exiv2::XmpProperties::unregisterNs();

    EXPECT_THROW(Exiv2::XmpProperties::ns("allpfx1"), std::exception);
    EXPECT_THROW(Exiv2::XmpProperties::ns("allpfx2"), std::exception);
}

// Test that built-in namespaces are not removed by unregisterNs()
TEST_F(XmpPropertiesTest_1248, UnregisterAllDoesNotRemoveBuiltinNamespaces_1248) {
    Exiv2::XmpProperties::unregisterNs();
    // Built-in namespaces should still work
    std::string result = Exiv2::XmpProperties::ns("dc");
    EXPECT_EQ(result, "http://purl.org/dc/elements/1.1/");
}

// Test nsInfo returns non-null for known prefix
TEST_F(XmpPropertiesTest_1248, NsInfoReturnsNonNullForKnownPrefix_1248) {
    const Exiv2::XmpNsInfo* info = Exiv2::XmpProperties::nsInfo("dc");
    ASSERT_NE(info, nullptr);
    EXPECT_STREQ(info->ns_, "http://purl.org/dc/elements/1.1/");
}

// Test nsInfo throws for unknown prefix
TEST_F(XmpPropertiesTest_1248, NsInfoThrowsForUnknownPrefix_1248) {
    EXPECT_THROW(Exiv2::XmpProperties::nsInfo("nonexistent_xyz"), std::exception);
}

// Test nsDesc returns non-null for known prefix
TEST_F(XmpPropertiesTest_1248, NsDescReturnsNonNullForKnownPrefix_1248) {
    const char* desc = Exiv2::XmpProperties::nsDesc("dc");
    EXPECT_NE(desc, nullptr);
}

// Test propertyList returns non-null for known prefix
TEST_F(XmpPropertiesTest_1248, PropertyListReturnsNonNullForKnownPrefix_1248) {
    const Exiv2::XmpPropertyInfo* list = Exiv2::XmpProperties::propertyList("dc");
    EXPECT_NE(list, nullptr);
}

// Test lookupNsRegistry returns null for unregistered prefix
TEST_F(XmpPropertiesTest_1248, LookupNsRegistryReturnsNullForUnregistered_1248) {
    const Exiv2::XmpNsInfo* result = Exiv2::XmpProperties::lookupNsRegistry(Exiv2::XmpNsInfo::Prefix{"nonexistent"});
    EXPECT_EQ(result, nullptr);
}

// Test lookupNsRegistry returns non-null for registered prefix
TEST_F(XmpPropertiesTest_1248, LookupNsRegistryReturnsNonNullForRegistered_1248) {
    Exiv2::XmpProperties::registerNs("http://example.com/lookup/", "lookuppfx");
    const Exiv2::XmpNsInfo* result = Exiv2::XmpProperties::lookupNsRegistry(Exiv2::XmpNsInfo::Prefix{"lookuppfx"});
    EXPECT_NE(result, nullptr);
    EXPECT_STREQ(result->ns_, "http://example.com/lookup/");
}

// Test registeredNamespaces populates dictionary
TEST_F(XmpPropertiesTest_1248, RegisteredNamespacesPopulatesDictionary_1248) {
    Exiv2::XmpProperties::registerNs("http://example.com/dict/", "dictpfx");
    Exiv2::Dictionary nsDict;
    Exiv2::XmpProperties::registeredNamespaces(nsDict);
    // The dictionary should contain at least our registered namespace
    EXPECT_FALSE(nsDict.empty());
    // Check that our custom namespace is present
    auto it = nsDict.find("http://example.com/dict/");
    EXPECT_NE(it, nsDict.end());
    if (it != nsDict.end()) {
        EXPECT_EQ(it->second, "dictpfx");
    }
}

// Test registeredNamespaces includes built-in namespaces
TEST_F(XmpPropertiesTest_1248, RegisteredNamespacesIncludesBuiltins_1248) {
    Exiv2::Dictionary nsDict;
    Exiv2::XmpProperties::registeredNamespaces(nsDict);
    EXPECT_FALSE(nsDict.empty());
}

// Test printProperties does not crash for a known prefix
TEST_F(XmpPropertiesTest_1248, PrintPropertiesDoesNotCrashForKnownPrefix_1248) {
    std::ostringstream os;
    EXPECT_NO_THROW(Exiv2::XmpProperties::printProperties(os, "dc"));
    EXPECT_FALSE(os.str().empty());
}

// Test propertyTitle for a known XmpKey
TEST_F(XmpPropertiesTest_1248, PropertyTitleForKnownKey_1248) {
    Exiv2::XmpKey key("Xmp.dc.creator");
    const char* title = Exiv2::XmpProperties::propertyTitle(key);
    // title may or may not be null depending on the property, but should not crash
    // For dc.creator, it should have a title
    EXPECT_NE(title, nullptr);
}

// Test propertyDesc for a known XmpKey
TEST_F(XmpPropertiesTest_1248, PropertyDescForKnownKey_1248) {
    Exiv2::XmpKey key("Xmp.dc.creator");
    const char* desc = Exiv2::XmpProperties::propertyDesc(key);
    EXPECT_NE(desc, nullptr);
}

// Test propertyType for a known XmpKey
TEST_F(XmpPropertiesTest_1248, PropertyTypeForKnownKey_1248) {
    Exiv2::XmpKey key("Xmp.dc.creator");
    Exiv2::TypeId type = Exiv2::XmpProperties::propertyType(key);
    EXPECT_NE(type, Exiv2::invalidTypeId);
}

// Test propertyInfo for a known XmpKey
TEST_F(XmpPropertiesTest_1248, PropertyInfoForKnownKey_1248) {
    Exiv2::XmpKey key("Xmp.dc.creator");
    const Exiv2::XmpPropertyInfo* info = Exiv2::XmpProperties::propertyInfo(key);
    EXPECT_NE(info, nullptr);
}

// Test re-registering a namespace with the same prefix updates it
TEST_F(XmpPropertiesTest_1248, ReRegisterNamespaceUpdates_1248) {
    Exiv2::XmpProperties::registerNs("http://example.com/v1/", "mypfx");
    std::string ns1 = Exiv2::XmpProperties::ns("mypfx");
    EXPECT_EQ(ns1, "http://example.com/v1/");

    Exiv2::XmpProperties::registerNs("http://example.com/v2/", "mypfx");
    std::string ns2 = Exiv2::XmpProperties::ns("mypfx");
    EXPECT_EQ(ns2, "http://example.com/v2/");
}

// Test ns() for registered custom namespace via the registry path
TEST_F(XmpPropertiesTest_1248, NsUsesRegistryForCustomNamespace_1248) {
    Exiv2::XmpProperties::registerNs("http://example.com/custom/", "custpfx");
    std::string result = Exiv2::XmpProperties::ns("custpfx");
    EXPECT_EQ(result, "http://example.com/custom/");
}

// Test printProperty doesn't crash
TEST_F(XmpPropertiesTest_1248, PrintPropertyDoesNotCrash_1248) {
    std::ostringstream os;
    Exiv2::XmpTextValue value("test");
    EXPECT_NO_THROW(Exiv2::XmpProperties::printProperty(os, "Xmp.dc.creator", value));
}

// Test ns() with empty prefix throws
TEST_F(XmpPropertiesTest_1248, NsThrowsForEmptyPrefix_1248) {
    EXPECT_THROW(Exiv2::XmpProperties::ns(""), std::exception);
}

// Test prefix() with empty namespace returns empty
TEST_F(XmpPropertiesTest_1248, PrefixReturnsEmptyForEmptyNs_1248) {
    std::string result = Exiv2::XmpProperties::prefix("");
    EXPECT_TRUE(result.empty());
}

// Test unregisterNs for a namespace that was never registered doesn't crash
TEST_F(XmpPropertiesTest_1248, UnregisterNonexistentNsDoesNotCrash_1248) {
    EXPECT_NO_THROW(Exiv2::XmpProperties::unregisterNs("http://nonexistent.example.com/"));
}

// Test multiple register/unregister cycles
TEST_F(XmpPropertiesTest_1248, MultipleRegisterUnregisterCycles_1248) {
    for (int i = 0; i < 5; ++i) {
        Exiv2::XmpProperties::registerNs("http://example.com/cycle/", "cyclepfx");
        EXPECT_EQ(Exiv2::XmpProperties::ns("cyclepfx"), "http://example.com/cycle/");
        Exiv2::XmpProperties::unregisterNs("http://example.com/cycle/");
        EXPECT_THROW(Exiv2::XmpProperties::ns("cyclepfx"), std::exception);
    }
}

// Test propertyList returns null or throws for unknown prefix
TEST_F(XmpPropertiesTest_1248, PropertyListForUnknownPrefix_1248) {
    EXPECT_THROW(Exiv2::XmpProperties::propertyList("nonexistent_xyz"), std::exception);
}

// Test "xmpRights" prefix
TEST_F(XmpPropertiesTest_1248, NsReturnsCorrectForXmpRightsPrefix_1248) {
    std::string result = Exiv2::XmpProperties::ns("xmpRights");
    EXPECT_FALSE(result.empty());
}

// Test "photoshop" prefix
TEST_F(XmpPropertiesTest_1248, NsReturnsCorrectForPhotoshopPrefix_1248) {
    std::string result = Exiv2::XmpProperties::ns("photoshop");
    EXPECT_FALSE(result.empty());
}

}  // namespace
