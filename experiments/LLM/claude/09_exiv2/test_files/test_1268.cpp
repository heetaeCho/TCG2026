#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>
#include <map>

#include "exiv2/properties.hpp"
#include "exiv2/value.hpp"

namespace {

using namespace Exiv2;

// =============================================================================
// XmpKey Tests
// =============================================================================

class XmpKeyTest_1268 : public ::testing::Test {
protected:
    void SetUp() override {
        // Ensure clean state by unregistering custom namespaces
        XmpProperties::unregisterNs();
    }

    void TearDown() override {
        XmpProperties::unregisterNs();
    }
};

// Test constructing XmpKey from a full key string (standard namespace)
TEST_F(XmpKeyTest_1268, ConstructFromKeyString_1268) {
    XmpKey key("Xmp.dc.title");
    EXPECT_EQ(key.key(), "Xmp.dc.title");
    EXPECT_STREQ(key.familyName(), "Xmp");
    EXPECT_EQ(key.groupName(), "dc");
    EXPECT_EQ(key.tagName(), "title");
}

// Test constructing XmpKey from prefix and property
TEST_F(XmpKeyTest_1268, ConstructFromPrefixAndProperty_1268) {
    XmpKey key("dc", "creator");
    EXPECT_EQ(key.key(), "Xmp.dc.creator");
    EXPECT_EQ(key.groupName(), "dc");
    EXPECT_EQ(key.tagName(), "creator");
}

// Test copy constructor
TEST_F(XmpKeyTest_1268, CopyConstructor_1268) {
    XmpKey key1("Xmp.dc.title");
    XmpKey key2(key1);
    EXPECT_EQ(key1.key(), key2.key());
    EXPECT_EQ(key1.groupName(), key2.groupName());
    EXPECT_EQ(key1.tagName(), key2.tagName());
}

// Test assignment operator
TEST_F(XmpKeyTest_1268, AssignmentOperator_1268) {
    XmpKey key1("Xmp.dc.title");
    XmpKey key2("Xmp.dc.creator");
    key2 = key1;
    EXPECT_EQ(key1.key(), key2.key());
    EXPECT_EQ(key1.tagName(), key2.tagName());
}

// Test clone
TEST_F(XmpKeyTest_1268, Clone_1268) {
    XmpKey key("Xmp.dc.subject");
    auto cloned = key.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(key.key(), cloned->key());
    EXPECT_EQ(key.groupName(), cloned->groupName());
    EXPECT_EQ(key.tagName(), cloned->tagName());
}

// Test familyName always returns "Xmp"
TEST_F(XmpKeyTest_1268, FamilyNameIsXmp_1268) {
    XmpKey key("Xmp.dc.title");
    EXPECT_STREQ(key.familyName(), "Xmp");
}

// Test ns() returns the namespace URI for a known prefix
TEST_F(XmpKeyTest_1268, NsReturnsNamespaceUri_1268) {
    XmpKey key("Xmp.dc.title");
    std::string nsUri = key.ns();
    EXPECT_FALSE(nsUri.empty());
    // Dublin Core namespace
    EXPECT_EQ(nsUri, "http://purl.org/dc/elements/1.1/");
}

// Test tagLabel for a known property
TEST_F(XmpKeyTest_1268, TagLabelForKnownProperty_1268) {
    XmpKey key("Xmp.dc.title");
    std::string label = key.tagLabel();
    // Should return a non-empty label for known properties
    EXPECT_FALSE(label.empty());
}

// Test tagDesc for a known property
TEST_F(XmpKeyTest_1268, TagDescForKnownProperty_1268) {
    XmpKey key("Xmp.dc.title");
    std::string desc = key.tagDesc();
    // Might be empty or non-empty depending on data, but shouldn't throw
}

// Test tag() returns a value
TEST_F(XmpKeyTest_1268, TagReturnsValue_1268) {
    XmpKey key("Xmp.dc.title");
    uint16_t tag = key.tag();
    // tag() should return some value (usually 0 for XMP)
    (void)tag; // Just verifying no exception
}

// Test constructing with invalid key should throw
TEST_F(XmpKeyTest_1268, ConstructFromInvalidKeyThrows_1268) {
    EXPECT_THROW(XmpKey("invalid_key_no_dots"), std::exception);
}

// Test constructing with unknown prefix
TEST_F(XmpKeyTest_1268, ConstructFromUnknownPrefixThrows_1268) {
    EXPECT_THROW(XmpKey("Xmp.unknownprefix12345.property"), std::exception);
}

// =============================================================================
// XmpProperties Tests
// =============================================================================

class XmpPropertiesTest_1268 : public ::testing::Test {
protected:
    void SetUp() override {
        XmpProperties::unregisterNs();
    }

    void TearDown() override {
        XmpProperties::unregisterNs();
    }
};

// Test ns() for known prefix "dc"
TEST_F(XmpPropertiesTest_1268, NsForKnownPrefix_1268) {
    std::string ns = XmpProperties::ns("dc");
    EXPECT_EQ(ns, "http://purl.org/dc/elements/1.1/");
}

// Test prefix() for known namespace
TEST_F(XmpPropertiesTest_1268, PrefixForKnownNamespace_1268) {
    std::string prefix = XmpProperties::prefix("http://purl.org/dc/elements/1.1/");
    EXPECT_EQ(prefix, "dc");
}

// Test ns() for unknown prefix throws or returns empty
TEST_F(XmpPropertiesTest_1268, NsForUnknownPrefix_1268) {
    EXPECT_THROW(XmpProperties::ns("totally_unknown_prefix_xyz"), std::exception);
}

// Test prefix() for unknown namespace returns empty
TEST_F(XmpPropertiesTest_1268, PrefixForUnknownNamespace_1268) {
    std::string prefix = XmpProperties::prefix("http://nonexistent.example.com/ns/");
    EXPECT_TRUE(prefix.empty());
}

// Test registerNs and then retrieve with ns/prefix
TEST_F(XmpPropertiesTest_1268, RegisterAndRetrieveCustomNamespace_1268) {
    XmpProperties::registerNs("http://example.com/test/", "mytest");
    std::string ns = XmpProperties::ns("mytest");
    EXPECT_EQ(ns, "http://example.com/test/");
    std::string prefix = XmpProperties::prefix("http://example.com/test/");
    EXPECT_EQ(prefix, "mytest");
}

// Test unregisterNs for specific namespace
TEST_F(XmpPropertiesTest_1268, UnregisterSpecificNamespace_1268) {
    XmpProperties::registerNs("http://example.com/unreg/", "unreg");
    std::string ns = XmpProperties::ns("unreg");
    EXPECT_EQ(ns, "http://example.com/unreg/");
    
    XmpProperties::unregisterNs("http://example.com/unreg/");
    // After unregistration, the prefix should not be found (for custom ns)
    EXPECT_THROW(XmpProperties::ns("unreg"), std::exception);
}

// Test unregisterNs() clears all custom registrations
TEST_F(XmpPropertiesTest_1268, UnregisterAllCustomNamespaces_1268) {
    XmpProperties::registerNs("http://example.com/a/", "testa");
    XmpProperties::registerNs("http://example.com/b/", "testb");
    
    XmpProperties::unregisterNs();
    
    EXPECT_THROW(XmpProperties::ns("testa"), std::exception);
    EXPECT_THROW(XmpProperties::ns("testb"), std::exception);
    
    // Built-in namespaces should still work
    std::string ns = XmpProperties::ns("dc");
    EXPECT_EQ(ns, "http://purl.org/dc/elements/1.1/");
}

// Test registeredNamespaces contains known namespaces
TEST_F(XmpPropertiesTest_1268, RegisteredNamespacesContainsKnown_1268) {
    Exiv2::Dictionary nsDict;
    XmpProperties::registeredNamespaces(nsDict);
    // Should contain dc namespace
    EXPECT_TRUE(nsDict.find("http://purl.org/dc/elements/1.1/") != nsDict.end() ||
                nsDict.find("dc") != nsDict.end());
}

// Test registeredNamespaces includes custom registration
TEST_F(XmpPropertiesTest_1268, RegisteredNamespacesIncludesCustom_1268) {
    XmpProperties::registerNs("http://example.com/custom/", "cust");
    Exiv2::Dictionary nsDict;
    XmpProperties::registeredNamespaces(nsDict);
    // Should find the custom namespace
    bool found = false;
    for (const auto& entry : nsDict) {
        if (entry.first == "http://example.com/custom/" || entry.second == "cust") {
            found = true;
            break;
        }
    }
    EXPECT_TRUE(found);
}

// Test propertyTitle for a known property
TEST_F(XmpPropertiesTest_1268, PropertyTitleForKnownProperty_1268) {
    XmpKey key("Xmp.dc.title");
    const char* title = XmpProperties::propertyTitle(key);
    // Should be non-null for known properties
    if (title) {
        EXPECT_GT(strlen(title), 0u);
    }
}

// Test propertyDesc for a known property
TEST_F(XmpPropertiesTest_1268, PropertyDescForKnownProperty_1268) {
    XmpKey key("Xmp.dc.title");
    const char* desc = XmpProperties::propertyDesc(key);
    // May or may not be null, but shouldn't crash
    (void)desc;
}

// Test propertyType for a known property
TEST_F(XmpPropertiesTest_1268, PropertyTypeForKnownProperty_1268) {
    XmpKey key("Xmp.dc.title");
    TypeId type = XmpProperties::propertyType(key);
    // dc:title is typically xmpText or langAlt
    EXPECT_NE(type, invalidTypeId);
}

// Test propertyInfo for a known property
TEST_F(XmpPropertiesTest_1268, PropertyInfoForKnownProperty_1268) {
    XmpKey key("Xmp.dc.title");
    const XmpPropertyInfo* info = XmpProperties::propertyInfo(key);
    EXPECT_NE(info, nullptr);
}

// Test propertyInfo for unknown property returns null
TEST_F(XmpPropertiesTest_1268, PropertyInfoForUnknownProperty_1268) {
    XmpProperties::registerNs("http://example.com/proptest/", "proptest");
    XmpKey key("Xmp.proptest.nonexistent");
    const XmpPropertyInfo* info = XmpProperties::propertyInfo(key);
    EXPECT_EQ(info, nullptr);
}

// Test nsDesc for a known prefix
TEST_F(XmpPropertiesTest_1268, NsDescForKnownPrefix_1268) {
    const char* desc = XmpProperties::nsDesc("dc");
    EXPECT_NE(desc, nullptr);
    EXPECT_GT(strlen(desc), 0u);
}

// Test propertyList for a known prefix
TEST_F(XmpPropertiesTest_1268, PropertyListForKnownPrefix_1268) {
    const XmpPropertyInfo* list = XmpProperties::propertyList("dc");
    EXPECT_NE(list, nullptr);
}

// Test propertyList for unknown prefix returns null
TEST_F(XmpPropertiesTest_1268, PropertyListForUnknownPrefix_1268) {
    XmpProperties::registerNs("http://example.com/pl/", "pltest");
    const XmpPropertyInfo* list = XmpProperties::propertyList("pltest");
    EXPECT_EQ(list, nullptr);
}

// Test nsInfo for a known prefix
TEST_F(XmpPropertiesTest_1268, NsInfoForKnownPrefix_1268) {
    const XmpNsInfo* info = XmpProperties::nsInfo("dc");
    EXPECT_NE(info, nullptr);
}

// Test printProperties doesn't crash for known prefix
TEST_F(XmpPropertiesTest_1268, PrintPropertiesDoesNotCrash_1268) {
    std::ostringstream oss;
    EXPECT_NO_THROW(XmpProperties::printProperties(oss, "dc"));
    EXPECT_FALSE(oss.str().empty());
}

// Test printProperty for a known key
TEST_F(XmpPropertiesTest_1268, PrintPropertyDoesNotCrash_1268) {
    std::ostringstream oss;
    XmpTextValue value("Test");
    EXPECT_NO_THROW(XmpProperties::printProperty(oss, "Xmp.dc.title", value));
}

// Test ns() for "xmp" prefix (XMP basic)
TEST_F(XmpPropertiesTest_1268, NsForXmpPrefix_1268) {
    std::string ns = XmpProperties::ns("xmp");
    EXPECT_FALSE(ns.empty());
}

// Test ns() for "exif" prefix
TEST_F(XmpPropertiesTest_1268, NsForExifPrefix_1268) {
    std::string ns = XmpProperties::ns("exif");
    EXPECT_FALSE(ns.empty());
}

// Test ns() for "tiff" prefix
TEST_F(XmpPropertiesTest_1268, NsForTiffPrefix_1268) {
    std::string ns = XmpProperties::ns("tiff");
    EXPECT_FALSE(ns.empty());
}

// Test re-registering same namespace with different prefix
TEST_F(XmpPropertiesTest_1268, ReRegisterNamespaceWithDifferentPrefix_1268) {
    XmpProperties::registerNs("http://example.com/reregtest/", "rereg1");
    std::string ns1 = XmpProperties::ns("rereg1");
    EXPECT_EQ(ns1, "http://example.com/reregtest/");
    
    // Re-register with different prefix
    XmpProperties::registerNs("http://example.com/reregtest/", "rereg2");
    std::string ns2 = XmpProperties::ns("rereg2");
    EXPECT_EQ(ns2, "http://example.com/reregtest/");
}

// Test lookupNsRegistry for a registered namespace
TEST_F(XmpPropertiesTest_1268, LookupNsRegistryForRegistered_1268) {
    XmpProperties::registerNs("http://example.com/lookup/", "lkup");
    XmpNsInfo::Prefix prefix("lkup");
    const XmpNsInfo* info = XmpProperties::lookupNsRegistry(prefix);
    EXPECT_NE(info, nullptr);
}

// Test lookupNsRegistry for unregistered returns null
TEST_F(XmpPropertiesTest_1268, LookupNsRegistryForUnregistered_1268) {
    XmpNsInfo::Prefix prefix("nonexistentprefix");
    const XmpNsInfo* info = XmpProperties::lookupNsRegistry(prefix);
    EXPECT_EQ(info, nullptr);
}

// Test XmpKey with different standard namespaces
TEST_F(XmpPropertiesTest_1268, XmpKeyWithXmpRightsNamespace_1268) {
    XmpKey key("Xmp.xmpRights.UsageTerms");
    EXPECT_EQ(key.key(), "Xmp.xmpRights.UsageTerms");
    EXPECT_EQ(key.groupName(), "xmpRights");
    EXPECT_EQ(key.tagName(), "UsageTerms");
    EXPECT_FALSE(key.ns().empty());
}

// Test XmpKey with photoshop namespace
TEST_F(XmpPropertiesTest_1268, XmpKeyWithPhotoshopNamespace_1268) {
    XmpKey key("Xmp.photoshop.City");
    EXPECT_EQ(key.groupName(), "photoshop");
    EXPECT_EQ(key.tagName(), "City");
}

// Test property type for dc:creator (should be a bag/seq type)
TEST_F(XmpPropertiesTest_1268, PropertyTypeForDcCreator_1268) {
    XmpKey key("Xmp.dc.creator");
    TypeId type = XmpProperties::propertyType(key);
    EXPECT_NE(type, invalidTypeId);
}

// Test self-assignment of XmpKey
TEST_F(XmpPropertiesTest_1268, SelfAssignment_1268) {
    XmpKey key("Xmp.dc.title");
    key = key;
    EXPECT_EQ(key.key(), "Xmp.dc.title");
}

} // namespace
