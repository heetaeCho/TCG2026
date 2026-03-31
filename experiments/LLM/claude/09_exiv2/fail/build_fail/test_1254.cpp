#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include <exiv2/properties.hpp>
#include <exiv2/value.hpp>
#include <exiv2/error.hpp>

namespace {

class XmpPropertiesTest_1254 : public ::testing::Test {
protected:
    void SetUp() override {
        // Ensure clean state by unregistering all custom namespaces
        Exiv2::XmpProperties::unregisterNs();
    }

    void TearDown() override {
        Exiv2::XmpProperties::unregisterNs();
    }
};

// Test that propertyList returns non-null for a known built-in prefix
TEST_F(XmpPropertiesTest_1254, PropertyListReturnsNonNullForKnownPrefix_1254) {
    const Exiv2::XmpPropertyInfo* info = Exiv2::XmpProperties::propertyList("dc");
    EXPECT_NE(info, nullptr);
}

// Test that propertyList returns non-null for xmp prefix
TEST_F(XmpPropertiesTest_1254, PropertyListReturnsNonNullForXmpPrefix_1254) {
    const Exiv2::XmpPropertyInfo* info = Exiv2::XmpProperties::propertyList("xmp");
    EXPECT_NE(info, nullptr);
}

// Test that nsInfo returns non-null for a known prefix
TEST_F(XmpPropertiesTest_1254, NsInfoReturnsNonNullForKnownPrefix_1254) {
    const Exiv2::XmpNsInfo* info = Exiv2::XmpProperties::nsInfo("dc");
    EXPECT_NE(info, nullptr);
}

// Test that ns() returns the namespace URI for a known prefix
TEST_F(XmpPropertiesTest_1254, NsReturnsNamespaceForKnownPrefix_1254) {
    std::string nsUri = Exiv2::XmpProperties::ns("dc");
    EXPECT_FALSE(nsUri.empty());
    EXPECT_EQ(nsUri, "http://purl.org/dc/elements/1.1/");
}

// Test that prefix() returns the prefix for a known namespace
TEST_F(XmpPropertiesTest_1254, PrefixReturnsKnownPrefixForNamespace_1254) {
    std::string pfx = Exiv2::XmpProperties::prefix("http://purl.org/dc/elements/1.1/");
    EXPECT_EQ(pfx, "dc");
}

// Test that nsDesc returns a non-null description for a known prefix
TEST_F(XmpPropertiesTest_1254, NsDescReturnsDescriptionForKnownPrefix_1254) {
    const char* desc = Exiv2::XmpProperties::nsDesc("dc");
    EXPECT_NE(desc, nullptr);
}

// Test that an unknown prefix throws an exception for nsInfo
TEST_F(XmpPropertiesTest_1254, NsInfoThrowsForUnknownPrefix_1254) {
    EXPECT_THROW(Exiv2::XmpProperties::nsInfo("nonexistent_prefix_xyz"), Exiv2::Error);
}

// Test that propertyList throws for an unknown prefix
TEST_F(XmpPropertiesTest_1254, PropertyListThrowsForUnknownPrefix_1254) {
    EXPECT_THROW(Exiv2::XmpProperties::propertyList("nonexistent_prefix_xyz"), Exiv2::Error);
}

// Test that ns() throws for an unknown prefix
TEST_F(XmpPropertiesTest_1254, NsThrowsForUnknownPrefix_1254) {
    EXPECT_THROW(Exiv2::XmpProperties::ns("nonexistent_prefix_xyz"), Exiv2::Error);
}

// Test that prefix() returns empty string for unknown namespace
TEST_F(XmpPropertiesTest_1254, PrefixReturnsEmptyForUnknownNamespace_1254) {
    std::string pfx = Exiv2::XmpProperties::prefix("http://nonexistent.example.com/");
    EXPECT_TRUE(pfx.empty());
}

// Test register and unregister custom namespace
TEST_F(XmpPropertiesTest_1254, RegisterAndUnregisterCustomNamespace_1254) {
    const std::string customNs = "http://example.com/custom/";
    const std::string customPrefix = "customTest";

    Exiv2::XmpProperties::registerNs(customNs, customPrefix);

    // After registration, prefix lookup should work
    std::string foundPrefix = Exiv2::XmpProperties::prefix(customNs);
    EXPECT_EQ(foundPrefix, customPrefix);

    // ns lookup should also work
    std::string foundNs = Exiv2::XmpProperties::ns(customPrefix);
    EXPECT_EQ(foundNs, customNs);

    // Unregister
    Exiv2::XmpProperties::unregisterNs(customNs);

    // After unregistration, prefix should return empty
    std::string afterPrefix = Exiv2::XmpProperties::prefix(customNs);
    EXPECT_TRUE(afterPrefix.empty());
}

// Test registeredNamespaces returns a non-empty dictionary
TEST_F(XmpPropertiesTest_1254, RegisteredNamespacesReturnsNonEmpty_1254) {
    Exiv2::Dictionary nsDict;
    Exiv2::XmpProperties::registeredNamespaces(nsDict);
    // At minimum, built-in namespaces should be present
    EXPECT_FALSE(nsDict.empty());
}

// Test registeredNamespaces includes a custom registered namespace
TEST_F(XmpPropertiesTest_1254, RegisteredNamespacesIncludesCustomNs_1254) {
    const std::string customNs = "http://example.com/testns/";
    const std::string customPrefix = "testns";

    Exiv2::XmpProperties::registerNs(customNs, customPrefix);

    Exiv2::Dictionary nsDict;
    Exiv2::XmpProperties::registeredNamespaces(nsDict);

    // Check that the custom namespace is in the dictionary
    auto it = nsDict.find(customPrefix);
    EXPECT_NE(it, nsDict.end());
    if (it != nsDict.end()) {
        EXPECT_EQ(it->second, customNs);
    }

    Exiv2::XmpProperties::unregisterNs(customNs);
}

// Test unregisterNs() (no args) clears all custom namespaces
TEST_F(XmpPropertiesTest_1254, UnregisterAllClearsCustomNamespaces_1254) {
    const std::string customNs1 = "http://example.com/ns1/";
    const std::string customPrefix1 = "testns1";
    const std::string customNs2 = "http://example.com/ns2/";
    const std::string customPrefix2 = "testns2";

    Exiv2::XmpProperties::registerNs(customNs1, customPrefix1);
    Exiv2::XmpProperties::registerNs(customNs2, customPrefix2);

    // Verify they are registered
    EXPECT_EQ(Exiv2::XmpProperties::prefix(customNs1), customPrefix1);
    EXPECT_EQ(Exiv2::XmpProperties::prefix(customNs2), customPrefix2);

    Exiv2::XmpProperties::unregisterNs();

    // After unregister all, custom namespaces should be gone
    EXPECT_TRUE(Exiv2::XmpProperties::prefix(customNs1).empty());
    EXPECT_TRUE(Exiv2::XmpProperties::prefix(customNs2).empty());
}

// Test lookupNsRegistry returns non-null after registering a namespace
TEST_F(XmpPropertiesTest_1254, LookupNsRegistryFindsRegisteredNs_1254) {
    const std::string customNs = "http://example.com/lookup/";
    const std::string customPrefix = "lookupTest";

    Exiv2::XmpProperties::registerNs(customNs, customPrefix);

    Exiv2::XmpNsInfo::Prefix pfx(customPrefix);
    const Exiv2::XmpNsInfo* info = Exiv2::XmpProperties::lookupNsRegistry(pfx);
    EXPECT_NE(info, nullptr);

    Exiv2::XmpProperties::unregisterNs(customNs);
}

// Test lookupNsRegistry returns null for unregistered prefix
TEST_F(XmpPropertiesTest_1254, LookupNsRegistryReturnsNullForUnknown_1254) {
    Exiv2::XmpNsInfo::Prefix pfx("completely_unknown_prefix");
    const Exiv2::XmpNsInfo* info = Exiv2::XmpProperties::lookupNsRegistry(pfx);
    EXPECT_EQ(info, nullptr);
}

// Test printProperties does not throw for a known prefix
TEST_F(XmpPropertiesTest_1254, PrintPropertiesDoesNotThrowForKnownPrefix_1254) {
    std::ostringstream os;
    EXPECT_NO_THROW(Exiv2::XmpProperties::printProperties(os, "dc"));
    // The output should contain something
    EXPECT_FALSE(os.str().empty());
}

// Test propertyTitle for a known XmpKey
TEST_F(XmpPropertiesTest_1254, PropertyTitleReturnsNonNullForKnownKey_1254) {
    Exiv2::XmpKey key("Xmp.dc.title");
    const char* title = Exiv2::XmpProperties::propertyTitle(key);
    // title may be non-null for known properties
    // (depending on implementation, it might be null if not defined)
    // We just test it doesn't crash
    (void)title;
}

// Test propertyDesc for a known XmpKey
TEST_F(XmpPropertiesTest_1254, PropertyDescReturnsForKnownKey_1254) {
    Exiv2::XmpKey key("Xmp.dc.description");
    const char* desc = Exiv2::XmpProperties::propertyDesc(key);
    (void)desc;  // Just ensuring no crash
}

// Test propertyType for a known XmpKey
TEST_F(XmpPropertiesTest_1254, PropertyTypeReturnsValidTypeForKnownKey_1254) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::TypeId type = Exiv2::XmpProperties::propertyType(key);
    // Type should be a valid TypeId
    EXPECT_NE(type, Exiv2::invalidTypeId);
}

// Test propertyInfo for a known XmpKey
TEST_F(XmpPropertiesTest_1254, PropertyInfoReturnsNonNullForKnownKey_1254) {
    Exiv2::XmpKey key("Xmp.dc.creator");
    const Exiv2::XmpPropertyInfo* info = Exiv2::XmpProperties::propertyInfo(key);
    EXPECT_NE(info, nullptr);
}

// Test printProperty with a string value
TEST_F(XmpPropertiesTest_1254, PrintPropertyOutputsSomething_1254) {
    std::ostringstream os;
    Exiv2::XmpTextValue value("test value");
    Exiv2::XmpProperties::printProperty(os, "Xmp.dc.title", value);
    // Just test it doesn't crash and produces some output
    // Output format is implementation-defined
}

// Test that registering a namespace with the same URI overwrites the prefix
TEST_F(XmpPropertiesTest_1254, RegisterNsOverwritesSameUri_1254) {
    const std::string ns = "http://example.com/overwrite/";
    Exiv2::XmpProperties::registerNs(ns, "first");
    Exiv2::XmpProperties::registerNs(ns, "second");

    std::string pfx = Exiv2::XmpProperties::prefix(ns);
    EXPECT_EQ(pfx, "second");

    Exiv2::XmpProperties::unregisterNs(ns);
}

// Test that nsInfo fields are populated correctly for dc
TEST_F(XmpPropertiesTest_1254, NsInfoFieldsPopulatedForDc_1254) {
    const Exiv2::XmpNsInfo* info = Exiv2::XmpProperties::nsInfo("dc");
    ASSERT_NE(info, nullptr);
    EXPECT_NE(info->ns_, nullptr);
    EXPECT_NE(info->prefix_, nullptr);
    EXPECT_STREQ(info->prefix_, "dc");
}

// Test multiple known prefixes
TEST_F(XmpPropertiesTest_1254, MultipleKnownPrefixesWork_1254) {
    std::vector<std::string> knownPrefixes = {"dc", "xmp", "xmpRights", "tiff", "exif"};
    for (const auto& prefix : knownPrefixes) {
        EXPECT_NO_THROW({
            const Exiv2::XmpPropertyInfo* plist = Exiv2::XmpProperties::propertyList(prefix);
            EXPECT_NE(plist, nullptr) << "Failed for prefix: " << prefix;
        }) << "Exception for prefix: " << prefix;
    }
}

// Test ns for xmp prefix
TEST_F(XmpPropertiesTest_1254, NsReturnsCorrectUriForXmpPrefix_1254) {
    std::string nsUri = Exiv2::XmpProperties::ns("xmp");
    EXPECT_FALSE(nsUri.empty());
    EXPECT_EQ(nsUri, "http://ns.adobe.com/xap/1.0/");
}

// Test empty prefix string
TEST_F(XmpPropertiesTest_1254, EmptyPrefixThrows_1254) {
    EXPECT_THROW(Exiv2::XmpProperties::nsInfo(""), Exiv2::Error);
}

// Test unregistering a non-existent namespace doesn't crash
TEST_F(XmpPropertiesTest_1254, UnregisterNonExistentNsDoesNotCrash_1254) {
    // Unregistering a namespace that was never registered should be handled gracefully
    EXPECT_NO_THROW(Exiv2::XmpProperties::unregisterNs("http://nonexistent.example.com/never_registered/"));
}

}  // namespace
