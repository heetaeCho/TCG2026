#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include "exiv2/properties.hpp"
#include "exiv2/value.hpp"
#include "exiv2/types.hpp"

namespace {

class XmpPropertiesTest_1245 : public ::testing::Test {
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

// Test registering a custom namespace and retrieving its prefix
TEST_F(XmpPropertiesTest_1245, RegisterNsAndGetPrefix_1245) {
    const std::string ns = "http://example.com/test/";
    const std::string pfx = "mytest";
    Exiv2::XmpProperties::registerNs(ns, pfx);

    std::string result = Exiv2::XmpProperties::prefix(ns);
    EXPECT_EQ(result, pfx);
}

// Test registering a custom namespace and retrieving its namespace from prefix
TEST_F(XmpPropertiesTest_1245, RegisterNsAndGetNs_1245) {
    const std::string ns = "http://example.com/test2/";
    const std::string pfx = "mytest2";
    Exiv2::XmpProperties::registerNs(ns, pfx);

    std::string result = Exiv2::XmpProperties::ns(pfx);
    EXPECT_EQ(result, ns);
}

// Test unregistering a specific namespace
TEST_F(XmpPropertiesTest_1245, UnregisterSpecificNs_1245) {
    const std::string ns = "http://example.com/unreg/";
    const std::string pfx = "unreg";
    Exiv2::XmpProperties::registerNs(ns, pfx);

    // Verify it exists
    std::string result = Exiv2::XmpProperties::prefix(ns);
    EXPECT_EQ(result, pfx);

    // Unregister it
    Exiv2::XmpProperties::unregisterNs(ns);

    // After unregistering, prefix should return empty string
    result = Exiv2::XmpProperties::prefix(ns);
    EXPECT_TRUE(result.empty());
}

// Test unregistering all custom namespaces
TEST_F(XmpPropertiesTest_1245, UnregisterAllNs_1245) {
    Exiv2::XmpProperties::registerNs("http://example.com/a/", "nsa");
    Exiv2::XmpProperties::registerNs("http://example.com/b/", "nsb");

    EXPECT_EQ(Exiv2::XmpProperties::prefix("http://example.com/a/"), "nsa");
    EXPECT_EQ(Exiv2::XmpProperties::prefix("http://example.com/b/"), "nsb");

    Exiv2::XmpProperties::unregisterNs();

    EXPECT_TRUE(Exiv2::XmpProperties::prefix("http://example.com/a/").empty());
    EXPECT_TRUE(Exiv2::XmpProperties::prefix("http://example.com/b/").empty());
}

// Test that built-in namespaces are accessible (dc namespace)
TEST_F(XmpPropertiesTest_1245, BuiltInNsDc_1245) {
    std::string result = Exiv2::XmpProperties::ns("dc");
    EXPECT_FALSE(result.empty());
    EXPECT_EQ(result, "http://purl.org/dc/elements/1.1/");
}

// Test that built-in prefix can be retrieved from namespace
TEST_F(XmpPropertiesTest_1245, BuiltInPrefixDc_1245) {
    std::string result = Exiv2::XmpProperties::prefix("http://purl.org/dc/elements/1.1/");
    EXPECT_EQ(result, "dc");
}

// Test nsInfo for a known built-in prefix
TEST_F(XmpPropertiesTest_1245, NsInfoForKnownPrefix_1245) {
    const Exiv2::XmpNsInfo* info = Exiv2::XmpProperties::nsInfo("dc");
    EXPECT_NE(info, nullptr);
}

// Test nsInfo for an unknown prefix
TEST_F(XmpPropertiesTest_1245, NsInfoForUnknownPrefix_1245) {
    const Exiv2::XmpNsInfo* info = Exiv2::XmpProperties::nsInfo("nonexistent_prefix_xyz");
    EXPECT_EQ(info, nullptr);
}

// Test nsDesc for a known prefix
TEST_F(XmpPropertiesTest_1245, NsDescForKnownPrefix_1245) {
    const char* desc = Exiv2::XmpProperties::nsDesc("dc");
    EXPECT_NE(desc, nullptr);
}

// Test propertyList for a known prefix
TEST_F(XmpPropertiesTest_1245, PropertyListForKnownPrefix_1245) {
    const Exiv2::XmpPropertyInfo* plist = Exiv2::XmpProperties::propertyList("dc");
    EXPECT_NE(plist, nullptr);
}

// Test propertyList for an unknown prefix returns nullptr
TEST_F(XmpPropertiesTest_1245, PropertyListForUnknownPrefix_1245) {
    const Exiv2::XmpPropertyInfo* plist = Exiv2::XmpProperties::propertyList("nonexistent_prefix_xyz");
    EXPECT_EQ(plist, nullptr);
}

// Test registeredNamespaces returns a non-empty dictionary
TEST_F(XmpPropertiesTest_1245, RegisteredNamespacesNotEmpty_1245) {
    Exiv2::Dictionary nsDict;
    Exiv2::XmpProperties::registeredNamespaces(nsDict);
    // There should be at least the built-in namespaces
    EXPECT_FALSE(nsDict.empty());
}

// Test registeredNamespaces includes a custom registered namespace
TEST_F(XmpPropertiesTest_1245, RegisteredNamespacesIncludesCustom_1245) {
    const std::string ns = "http://example.com/custom/";
    const std::string pfx = "customns";
    Exiv2::XmpProperties::registerNs(ns, pfx);

    Exiv2::Dictionary nsDict;
    Exiv2::XmpProperties::registeredNamespaces(nsDict);

    auto it = nsDict.find(pfx);
    EXPECT_NE(it, nsDict.end());
    if (it != nsDict.end()) {
        EXPECT_EQ(it->second, ns);
    }
}

// Test prefix for unknown namespace returns empty string
TEST_F(XmpPropertiesTest_1245, PrefixForUnknownNsReturnsEmpty_1245) {
    std::string result = Exiv2::XmpProperties::prefix("http://totally.unknown.namespace/");
    EXPECT_TRUE(result.empty());
}

// Test ns for unknown prefix returns empty string
TEST_F(XmpPropertiesTest_1245, NsForUnknownPrefixReturnsEmpty_1245) {
    std::string result = Exiv2::XmpProperties::ns("totally_unknown_prefix");
    EXPECT_TRUE(result.empty());
}

// Test propertyTitle for a known XmpKey
TEST_F(XmpPropertiesTest_1245, PropertyTitleForKnownKey_1245) {
    Exiv2::XmpKey key("Xmp.dc.title");
    const char* title = Exiv2::XmpProperties::propertyTitle(key);
    EXPECT_NE(title, nullptr);
}

// Test propertyDesc for a known XmpKey
TEST_F(XmpPropertiesTest_1245, PropertyDescForKnownKey_1245) {
    Exiv2::XmpKey key("Xmp.dc.title");
    const char* desc = Exiv2::XmpProperties::propertyDesc(key);
    EXPECT_NE(desc, nullptr);
}

// Test propertyType for a known XmpKey
TEST_F(XmpPropertiesTest_1245, PropertyTypeForKnownKey_1245) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::TypeId type = Exiv2::XmpProperties::propertyType(key);
    EXPECT_NE(type, Exiv2::invalidTypeId);
}

// Test propertyInfo for a known XmpKey
TEST_F(XmpPropertiesTest_1245, PropertyInfoForKnownKey_1245) {
    Exiv2::XmpKey key("Xmp.dc.title");
    const Exiv2::XmpPropertyInfo* info = Exiv2::XmpProperties::propertyInfo(key);
    EXPECT_NE(info, nullptr);
}

// Test printProperties doesn't crash for a known prefix
TEST_F(XmpPropertiesTest_1245, PrintPropertiesForKnownPrefix_1245) {
    std::ostringstream oss;
    EXPECT_NO_THROW(Exiv2::XmpProperties::printProperties(oss, "dc"));
    EXPECT_FALSE(oss.str().empty());
}

// Test printProperty doesn't crash
TEST_F(XmpPropertiesTest_1245, PrintPropertyForKnownKey_1245) {
    std::ostringstream oss;
    Exiv2::XmpTextValue value("test value");
    EXPECT_NO_THROW(Exiv2::XmpProperties::printProperty(oss, "Xmp.dc.title", value));
}

// Test re-registering the same namespace with a different prefix
TEST_F(XmpPropertiesTest_1245, ReRegisterNsWithDifferentPrefix_1245) {
    const std::string ns = "http://example.com/rereg/";
    Exiv2::XmpProperties::registerNs(ns, "pfx1");
    EXPECT_EQ(Exiv2::XmpProperties::prefix(ns), "pfx1");

    Exiv2::XmpProperties::registerNs(ns, "pfx2");
    std::string result = Exiv2::XmpProperties::prefix(ns);
    // After re-registration, the prefix should be updated
    EXPECT_EQ(result, "pfx2");
}

// Test lookupNsRegistry for a registered custom namespace
TEST_F(XmpPropertiesTest_1245, LookupNsRegistryForRegisteredNs_1245) {
    const std::string ns = "http://example.com/lookup/";
    const std::string pfx = "lookupns";
    Exiv2::XmpProperties::registerNs(ns, pfx);

    Exiv2::XmpNsInfo::Prefix prefix_obj(pfx);
    const Exiv2::XmpNsInfo* info = Exiv2::XmpProperties::lookupNsRegistry(prefix_obj);
    EXPECT_NE(info, nullptr);
}

// Test lookupNsRegistry for an unregistered namespace returns nullptr
TEST_F(XmpPropertiesTest_1245, LookupNsRegistryForUnregisteredNs_1245) {
    Exiv2::XmpNsInfo::Prefix prefix_obj("nonexistent_ns_xyz");
    const Exiv2::XmpNsInfo* info = Exiv2::XmpProperties::lookupNsRegistry(prefix_obj);
    EXPECT_EQ(info, nullptr);
}

// Test unregistering a namespace that was never registered (should not throw)
TEST_F(XmpPropertiesTest_1245, UnregisterNonexistentNs_1245) {
    EXPECT_NO_THROW(Exiv2::XmpProperties::unregisterNs("http://nonexistent.example.com/"));
}

// Test that built-in namespaces like xmp are accessible
TEST_F(XmpPropertiesTest_1245, BuiltInNsXmp_1245) {
    std::string result = Exiv2::XmpProperties::ns("xmp");
    EXPECT_FALSE(result.empty());
}

// Test that built-in namespaces like exif are accessible
TEST_F(XmpPropertiesTest_1245, BuiltInNsExif_1245) {
    std::string result = Exiv2::XmpProperties::ns("exif");
    EXPECT_FALSE(result.empty());
}

// Test that built-in namespaces like tiff are accessible
TEST_F(XmpPropertiesTest_1245, BuiltInNsTiff_1245) {
    std::string result = Exiv2::XmpProperties::ns("tiff");
    EXPECT_FALSE(result.empty());
}

// Test registering with empty strings
TEST_F(XmpPropertiesTest_1245, RegisterWithEmptyStrings_1245) {
    // This tests boundary behavior - registering with empty ns/prefix
    // The behavior depends on implementation, but it shouldn't crash
    try {
        Exiv2::XmpProperties::registerNs("", "");
    } catch (...) {
        // It's acceptable if this throws
    }
}

// Test that after unregisterNs(), built-in namespaces still work
TEST_F(XmpPropertiesTest_1245, BuiltInNsSurviveUnregisterAll_1245) {
    Exiv2::XmpProperties::registerNs("http://example.com/temp/", "tempns");
    Exiv2::XmpProperties::unregisterNs();

    // Built-in namespaces should still be accessible
    std::string result = Exiv2::XmpProperties::ns("dc");
    EXPECT_EQ(result, "http://purl.org/dc/elements/1.1/");
}

// Test multiple register/unregister cycles
TEST_F(XmpPropertiesTest_1245, MultipleRegisterUnregisterCycles_1245) {
    for (int i = 0; i < 5; ++i) {
        const std::string ns = "http://example.com/cycle/";
        const std::string pfx = "cycle";
        Exiv2::XmpProperties::registerNs(ns, pfx);
        EXPECT_EQ(Exiv2::XmpProperties::prefix(ns), pfx);
        Exiv2::XmpProperties::unregisterNs(ns);
        EXPECT_TRUE(Exiv2::XmpProperties::prefix(ns).empty());
    }
}

// Test registering multiple namespaces
TEST_F(XmpPropertiesTest_1245, RegisterMultipleNamespaces_1245) {
    Exiv2::XmpProperties::registerNs("http://example.com/ns1/", "ns1");
    Exiv2::XmpProperties::registerNs("http://example.com/ns2/", "ns2");
    Exiv2::XmpProperties::registerNs("http://example.com/ns3/", "ns3");

    EXPECT_EQ(Exiv2::XmpProperties::prefix("http://example.com/ns1/"), "ns1");
    EXPECT_EQ(Exiv2::XmpProperties::prefix("http://example.com/ns2/"), "ns2");
    EXPECT_EQ(Exiv2::XmpProperties::prefix("http://example.com/ns3/"), "ns3");

    EXPECT_EQ(Exiv2::XmpProperties::ns("ns1"), "http://example.com/ns1/");
    EXPECT_EQ(Exiv2::XmpProperties::ns("ns2"), "http://example.com/ns2/");
    EXPECT_EQ(Exiv2::XmpProperties::ns("ns3"), "http://example.com/ns3/");
}

}  // namespace
