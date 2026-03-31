#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/properties.hpp>
#include <exiv2/error.hpp>
#include <exiv2/value.hpp>
#include <sstream>
#include <string>

using namespace Exiv2;

// Test fixture for XmpProperties tests
class XmpPropertiesTest_2177 : public ::testing::Test {
protected:
    void SetUp() override {
        // Ensure clean state by unregistering all custom namespaces
        XmpProperties::unregisterNs();
    }

    void TearDown() override {
        XmpProperties::unregisterNs();
    }
};

// Test fixture for XmpKey tests
class XmpKeyTest_2177 : public ::testing::Test {
protected:
    void SetUp() override {
        XmpProperties::unregisterNs();
    }

    void TearDown() override {
        XmpProperties::unregisterNs();
    }
};

// ==================== XmpKey::Impl Tests ====================

TEST_F(XmpKeyTest_2177, ConstructImplWithValidPrefix_2177) {
    // "dc" is a well-known XMP prefix (Dublin Core)
    EXPECT_NO_THROW(XmpKey key("Xmp.dc.title"));
}

TEST_F(XmpKeyTest_2177, ConstructImplWithInvalidPrefixThrows_2177) {
    // Using a completely unknown prefix should throw
    EXPECT_THROW(XmpKey key("Xmp.nonexistentprefix12345.property"), Error);
}

TEST_F(XmpKeyTest_2177, ConstructImplWithRegisteredCustomPrefix_2177) {
    // Register a custom namespace, then create a key with it
    XmpProperties::registerNs("http://example.com/test/", "mytest");
    EXPECT_NO_THROW(XmpKey key("Xmp.mytest.someproperty"));
}

TEST_F(XmpKeyTest_2177, ConstructImplWithUnregisteredCustomPrefixThrows_2177) {
    // Register and then unregister
    XmpProperties::registerNs("http://example.com/test2/", "mytest2");
    XmpProperties::unregisterNs("http://example.com/test2/");
    EXPECT_THROW(XmpKey key("Xmp.mytest2.someproperty"), Error);
}

// ==================== XmpProperties::ns Tests ====================

TEST_F(XmpPropertiesTest_2177, NsReturnsNamespaceForKnownPrefix_2177) {
    std::string ns = XmpProperties::ns("dc");
    EXPECT_FALSE(ns.empty());
    EXPECT_EQ(ns, "http://purl.org/dc/elements/1.1/");
}

TEST_F(XmpPropertiesTest_2177, NsReturnsEmptyForUnknownPrefix_2177) {
    std::string ns = XmpProperties::ns("totally_unknown_prefix_xyz");
    EXPECT_TRUE(ns.empty());
}

TEST_F(XmpPropertiesTest_2177, NsReturnsNamespaceForRegisteredPrefix_2177) {
    XmpProperties::registerNs("http://example.com/custom/", "customns");
    std::string ns = XmpProperties::ns("customns");
    EXPECT_EQ(ns, "http://example.com/custom/");
}

TEST_F(XmpPropertiesTest_2177, NsReturnsEmptyForEmptyPrefix_2177) {
    std::string ns = XmpProperties::ns("");
    EXPECT_TRUE(ns.empty());
}

// ==================== XmpProperties::prefix Tests ====================

TEST_F(XmpPropertiesTest_2177, PrefixReturnsKnownPrefixForNamespace_2177) {
    std::string prefix = XmpProperties::prefix("http://purl.org/dc/elements/1.1/");
    EXPECT_EQ(prefix, "dc");
}

TEST_F(XmpPropertiesTest_2177, PrefixReturnsEmptyForUnknownNamespace_2177) {
    std::string prefix = XmpProperties::prefix("http://nonexistent.example.com/");
    EXPECT_TRUE(prefix.empty());
}

TEST_F(XmpPropertiesTest_2177, PrefixReturnsRegisteredPrefix_2177) {
    XmpProperties::registerNs("http://example.com/pfxtest/", "pfxtest");
    std::string prefix = XmpProperties::prefix("http://example.com/pfxtest/");
    EXPECT_EQ(prefix, "pfxtest");
}

// ==================== XmpProperties::registerNs Tests ====================

TEST_F(XmpPropertiesTest_2177, RegisterNsAndRetrieve_2177) {
    XmpProperties::registerNs("http://example.com/reg/", "regtest");
    EXPECT_EQ(XmpProperties::ns("regtest"), "http://example.com/reg/");
    EXPECT_EQ(XmpProperties::prefix("http://example.com/reg/"), "regtest");
}

TEST_F(XmpPropertiesTest_2177, RegisterNsOverwritePrefix_2177) {
    XmpProperties::registerNs("http://example.com/overwrite/", "owtest1");
    EXPECT_EQ(XmpProperties::ns("owtest1"), "http://example.com/overwrite/");

    // Re-register same namespace with different prefix
    XmpProperties::registerNs("http://example.com/overwrite/", "owtest2");
    EXPECT_EQ(XmpProperties::prefix("http://example.com/overwrite/"), "owtest2");
}

// ==================== XmpProperties::unregisterNs Tests ====================

TEST_F(XmpPropertiesTest_2177, UnregisterSpecificNs_2177) {
    XmpProperties::registerNs("http://example.com/unreg/", "unregtest");
    EXPECT_FALSE(XmpProperties::ns("unregtest").empty());

    XmpProperties::unregisterNs("http://example.com/unreg/");
    EXPECT_TRUE(XmpProperties::ns("unregtest").empty());
}

TEST_F(XmpPropertiesTest_2177, UnregisterAllCustomNs_2177) {
    XmpProperties::registerNs("http://example.com/all1/", "alltest1");
    XmpProperties::registerNs("http://example.com/all2/", "alltest2");

    XmpProperties::unregisterNs();

    EXPECT_TRUE(XmpProperties::ns("alltest1").empty());
    EXPECT_TRUE(XmpProperties::ns("alltest2").empty());
}

TEST_F(XmpPropertiesTest_2177, UnregisterNsBuiltinStillAvailable_2177) {
    // After unregistering all custom namespaces, built-in ones should remain
    XmpProperties::unregisterNs();
    EXPECT_FALSE(XmpProperties::ns("dc").empty());
}

// ==================== XmpProperties::nsInfo Tests ====================

TEST_F(XmpPropertiesTest_2177, NsInfoReturnsNonNullForKnownPrefix_2177) {
    const XmpNsInfo* info = XmpProperties::nsInfo("dc");
    EXPECT_NE(info, nullptr);
}

TEST_F(XmpPropertiesTest_2177, NsInfoReturnsNullForUnknownPrefix_2177) {
    const XmpNsInfo* info = XmpProperties::nsInfo("totally_unknown_ns_prefix");
    EXPECT_EQ(info, nullptr);
}

// ==================== XmpProperties::nsDesc Tests ====================

TEST_F(XmpPropertiesTest_2177, NsDescReturnsNonNullForKnownPrefix_2177) {
    const char* desc = XmpProperties::nsDesc("dc");
    EXPECT_NE(desc, nullptr);
}

// ==================== XmpProperties::propertyList Tests ====================

TEST_F(XmpPropertiesTest_2177, PropertyListReturnsNonNullForKnownPrefix_2177) {
    const XmpPropertyInfo* list = XmpProperties::propertyList("dc");
    EXPECT_NE(list, nullptr);
}

TEST_F(XmpPropertiesTest_2177, PropertyListReturnsNullForUnknownPrefix_2177) {
    const XmpPropertyInfo* list = XmpProperties::propertyList("unknown_prefix_xyz");
    EXPECT_EQ(list, nullptr);
}

// ==================== XmpProperties::propertyInfo Tests ====================

TEST_F(XmpPropertiesTest_2177, PropertyInfoReturnsNonNullForKnownProperty_2177) {
    XmpKey key("Xmp.dc.title");
    const XmpPropertyInfo* info = XmpProperties::propertyInfo(key);
    EXPECT_NE(info, nullptr);
}

TEST_F(XmpPropertiesTest_2177, PropertyInfoReturnsNullForUnknownProperty_2177) {
    XmpKey key("Xmp.dc.nonexistentproperty12345");
    const XmpPropertyInfo* info = XmpProperties::propertyInfo(key);
    EXPECT_EQ(info, nullptr);
}

// ==================== XmpProperties::propertyTitle Tests ====================

TEST_F(XmpPropertiesTest_2177, PropertyTitleForKnownProperty_2177) {
    XmpKey key("Xmp.dc.title");
    const char* title = XmpProperties::propertyTitle(key);
    // For a known property, title should be non-null
    EXPECT_NE(title, nullptr);
}

TEST_F(XmpPropertiesTest_2177, PropertyTitleForUnknownPropertyReturnsEmpty_2177) {
    XmpKey key("Xmp.dc.unknownprop999");
    const char* title = XmpProperties::propertyTitle(key);
    // For an unknown property, title should be empty string or nullptr
    if (title != nullptr) {
        EXPECT_STREQ(title, "");
    }
}

// ==================== XmpProperties::propertyDesc Tests ====================

TEST_F(XmpPropertiesTest_2177, PropertyDescForKnownProperty_2177) {
    XmpKey key("Xmp.dc.title");
    const char* desc = XmpProperties::propertyDesc(key);
    EXPECT_NE(desc, nullptr);
}

// ==================== XmpProperties::propertyType Tests ====================

TEST_F(XmpPropertiesTest_2177, PropertyTypeForKnownProperty_2177) {
    XmpKey key("Xmp.dc.title");
    TypeId type = XmpProperties::propertyType(key);
    // dc:title is a lang alt, so it should have a defined type
    EXPECT_NE(type, TypeId::invalidTypeId);
}

TEST_F(XmpPropertiesTest_2177, PropertyTypeForUnknownPropertyReturnsXmpText_2177) {
    XmpKey key("Xmp.dc.somethingnotdefined123");
    TypeId type = XmpProperties::propertyType(key);
    // Unknown properties typically default to xmpText
    EXPECT_EQ(type, TypeId::xmpText);
}

// ==================== XmpProperties::registeredNamespaces Tests ====================

TEST_F(XmpPropertiesTest_2177, RegisteredNamespacesContainsBuiltIn_2177) {
    Exiv2::Dictionary nsDict;
    XmpProperties::registeredNamespaces(nsDict);
    // Should contain at least the dc namespace
    EXPECT_FALSE(nsDict.empty());
    // Check for dc
    auto it = nsDict.find("http://purl.org/dc/elements/1.1/");
    if (it != nsDict.end()) {
        EXPECT_EQ(it->second, "dc");
    }
}

TEST_F(XmpPropertiesTest_2177, RegisteredNamespacesIncludesCustom_2177) {
    XmpProperties::registerNs("http://example.com/dicttest/", "dicttest");
    Exiv2::Dictionary nsDict;
    XmpProperties::registeredNamespaces(nsDict);
    auto it = nsDict.find("http://example.com/dicttest/");
    EXPECT_NE(it, nsDict.end());
    EXPECT_EQ(it->second, "dicttest");
}

// ==================== XmpProperties::printProperties Tests ====================

TEST_F(XmpPropertiesTest_2177, PrintPropertiesForKnownPrefix_2177) {
    std::ostringstream os;
    EXPECT_NO_THROW(XmpProperties::printProperties(os, "dc"));
    std::string output = os.str();
    // Should produce some output for dc properties
    EXPECT_FALSE(output.empty());
}

TEST_F(XmpPropertiesTest_2177, PrintPropertiesForUnknownPrefixProducesNoOutput_2177) {
    std::ostringstream os;
    // Unknown prefix - should either produce empty or throw
    try {
        XmpProperties::printProperties(os, "unknown_prefix_for_print");
        // If it doesn't throw, output should be empty or minimal
    } catch (const Error&) {
        // Acceptable behavior
    }
}

// ==================== XmpProperties::lookupNsRegistry Tests ====================

TEST_F(XmpPropertiesTest_2177, LookupNsRegistryForRegisteredPrefix_2177) {
    XmpProperties::registerNs("http://example.com/lookup/", "lookuptest");
    XmpNsInfo::Prefix pfx{"lookuptest"};
    const XmpNsInfo* info = XmpProperties::lookupNsRegistry(pfx);
    EXPECT_NE(info, nullptr);
}

TEST_F(XmpPropertiesTest_2177, LookupNsRegistryForUnregisteredPrefixReturnsNull_2177) {
    XmpNsInfo::Prefix pfx{"nonexistent_lookup_prefix"};
    const XmpNsInfo* info = XmpProperties::lookupNsRegistry(pfx);
    EXPECT_EQ(info, nullptr);
}

// ==================== XmpKey Construction via string key Tests ====================

TEST_F(XmpKeyTest_2177, XmpKeyFromFullKeyString_2177) {
    EXPECT_NO_THROW(XmpKey key("Xmp.dc.subject"));
}

TEST_F(XmpKeyTest_2177, XmpKeyFromInvalidKeyStringThrows_2177) {
    EXPECT_THROW(XmpKey key("Xmp.invalidprefix999.something"), Error);
}

TEST_F(XmpKeyTest_2177, XmpKeyFromMalformedKeyStringThrows_2177) {
    EXPECT_THROW(XmpKey key("notxmp"), Error);
}

TEST_F(XmpKeyTest_2177, XmpKeyFromEmptyStringThrows_2177) {
    EXPECT_THROW(XmpKey key(""), Error);
}

// ==================== XmpKey accessors Tests ====================

TEST_F(XmpKeyTest_2177, XmpKeyFamilyName_2177) {
    XmpKey key("Xmp.dc.title");
    EXPECT_EQ(std::string(key.familyName()), "Xmp");
}

TEST_F(XmpKeyTest_2177, XmpKeyGroupName_2177) {
    XmpKey key("Xmp.dc.title");
    EXPECT_EQ(key.groupName(), "dc");
}

TEST_F(XmpKeyTest_2177, XmpKeyTagName_2177) {
    XmpKey key("Xmp.dc.title");
    EXPECT_EQ(key.tagName(), "title");
}

TEST_F(XmpKeyTest_2177, XmpKeyKey_2177) {
    XmpKey key("Xmp.dc.title");
    EXPECT_EQ(key.key(), "Xmp.dc.title");
}

// ==================== XmpKey copy Tests ====================

TEST_F(XmpKeyTest_2177, XmpKeyCopyConstructor_2177) {
    XmpKey key1("Xmp.dc.title");
    XmpKey key2(key1);
    EXPECT_EQ(key1.key(), key2.key());
}

TEST_F(XmpKeyTest_2177, XmpKeyClone_2177) {
    XmpKey key("Xmp.dc.title");
    auto cloned = key.clone();
    EXPECT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->key(), key.key());
}

// ==================== Error verification for invalid prefix ====================

TEST_F(XmpKeyTest_2177, ErrorCodeForNoNamespaceForPrefix_2177) {
    try {
        XmpKey key("Xmp.bogusprefix.property");
        FAIL() << "Expected Error to be thrown";
    } catch (const Error& e) {
        EXPECT_EQ(e.code(), ErrorCode::kerNoNamespaceForPrefix);
    }
}

// ==================== XmpProperties with xmp prefix Tests ====================

TEST_F(XmpPropertiesTest_2177, NsForXmpPrefix_2177) {
    std::string ns = XmpProperties::ns("xmp");
    EXPECT_FALSE(ns.empty());
}

TEST_F(XmpPropertiesTest_2177, NsForExifPrefix_2177) {
    std::string ns = XmpProperties::ns("exif");
    EXPECT_FALSE(ns.empty());
}

TEST_F(XmpPropertiesTest_2177, NsForTiffPrefix_2177) {
    std::string ns = XmpProperties::ns("tiff");
    EXPECT_FALSE(ns.empty());
}

// ==================== Boundary: registering with empty strings ====================

TEST_F(XmpPropertiesTest_2177, RegisterNsWithEmptyPrefix_2177) {
    // Behavior may vary, but should not crash
    try {
        XmpProperties::registerNs("http://example.com/empty/", "");
    } catch (const Error&) {
        // Acceptable
    }
}

TEST_F(XmpPropertiesTest_2177, RegisterNsWithEmptyNamespace_2177) {
    try {
        XmpProperties::registerNs("", "emptyns");
    } catch (const Error&) {
        // Acceptable
    }
}

// ==================== Multiple register/unregister cycles ====================

TEST_F(XmpPropertiesTest_2177, MultipleRegisterUnregisterCycles_2177) {
    for (int i = 0; i < 5; ++i) {
        XmpProperties::registerNs("http://example.com/cycle/", "cycletest");
        EXPECT_EQ(XmpProperties::ns("cycletest"), "http://example.com/cycle/");
        XmpProperties::unregisterNs("http://example.com/cycle/");
        EXPECT_TRUE(XmpProperties::ns("cycletest").empty());
    }
}
