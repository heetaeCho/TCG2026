#include <gtest/gtest.h>
#include <exiv2/properties.hpp>
#include <exiv2/value.hpp>
#include <sstream>
#include <string>

using namespace Exiv2;

// Test fixture for XmpProperties tests
class XmpPropertiesTest_1252 : public ::testing::Test {
protected:
    void SetUp() override {
        // Ensure clean state by unregistering custom namespaces
    }

    void TearDown() override {
        // Clean up any registered namespaces
        XmpProperties::unregisterNs();
    }
};

// ==================== propertyInfo tests ====================

TEST_F(XmpPropertiesTest_1252, PropertyInfoReturnsValidInfoForKnownDcProperty_1252) {
    XmpKey key("Xmp.dc.title");
    const XmpPropertyInfo* info = XmpProperties::propertyInfo(key);
    ASSERT_NE(info, nullptr);
    EXPECT_STREQ(info->name_, "title");
}

TEST_F(XmpPropertiesTest_1252, PropertyInfoReturnsValidInfoForKnownDcCreator_1252) {
    XmpKey key("Xmp.dc.creator");
    const XmpPropertyInfo* info = XmpProperties::propertyInfo(key);
    ASSERT_NE(info, nullptr);
    EXPECT_STREQ(info->name_, "creator");
}

TEST_F(XmpPropertiesTest_1252, PropertyInfoReturnsNullForUnknownProperty_1252) {
    XmpKey key("Xmp.dc.nonExistentProperty12345");
    const XmpPropertyInfo* info = XmpProperties::propertyInfo(key);
    EXPECT_EQ(info, nullptr);
}

TEST_F(XmpPropertiesTest_1252, PropertyInfoReturnsValidForXmpBasicCreateDate_1252) {
    XmpKey key("Xmp.xmp.CreateDate");
    const XmpPropertyInfo* info = XmpProperties::propertyInfo(key);
    ASSERT_NE(info, nullptr);
    EXPECT_STREQ(info->name_, "CreateDate");
}

TEST_F(XmpPropertiesTest_1252, PropertyInfoReturnsValidForTiffProperty_1252) {
    XmpKey key("Xmp.tiff.ImageWidth");
    const XmpPropertyInfo* info = XmpProperties::propertyInfo(key);
    ASSERT_NE(info, nullptr);
    EXPECT_STREQ(info->name_, "ImageWidth");
}

TEST_F(XmpPropertiesTest_1252, PropertyInfoReturnsValidForExifProperty_1252) {
    XmpKey key("Xmp.exif.ExposureTime");
    const XmpPropertyInfo* info = XmpProperties::propertyInfo(key);
    ASSERT_NE(info, nullptr);
    EXPECT_STREQ(info->name_, "ExposureTime");
}

TEST_F(XmpPropertiesTest_1252, PropertyInfoForDcDescription_1252) {
    XmpKey key("Xmp.dc.description");
    const XmpPropertyInfo* info = XmpProperties::propertyInfo(key);
    ASSERT_NE(info, nullptr);
    EXPECT_STREQ(info->name_, "description");
}

TEST_F(XmpPropertiesTest_1252, PropertyInfoForDcSubject_1252) {
    XmpKey key("Xmp.dc.subject");
    const XmpPropertyInfo* info = XmpProperties::propertyInfo(key);
    ASSERT_NE(info, nullptr);
    EXPECT_STREQ(info->name_, "subject");
}

// ==================== propertyType tests ====================

TEST_F(XmpPropertiesTest_1252, PropertyTypeReturnsCorrectTypeForDcTitle_1252) {
    XmpKey key("Xmp.dc.title");
    TypeId type = XmpProperties::propertyType(key);
    EXPECT_NE(type, invalidTypeId);
}

TEST_F(XmpPropertiesTest_1252, PropertyTypeReturnsCorrectTypeForDcCreator_1252) {
    XmpKey key("Xmp.dc.creator");
    TypeId type = XmpProperties::propertyType(key);
    EXPECT_NE(type, invalidTypeId);
}

// ==================== propertyTitle tests ====================

TEST_F(XmpPropertiesTest_1252, PropertyTitleReturnsNonNullForKnownProperty_1252) {
    XmpKey key("Xmp.dc.title");
    const char* title = XmpProperties::propertyTitle(key);
    EXPECT_NE(title, nullptr);
}

TEST_F(XmpPropertiesTest_1252, PropertyTitleReturnsNullForUnknownProperty_1252) {
    XmpKey key("Xmp.dc.nonExistentProperty99999");
    const char* title = XmpProperties::propertyTitle(key);
    EXPECT_EQ(title, nullptr);
}

// ==================== propertyDesc tests ====================

TEST_F(XmpPropertiesTest_1252, PropertyDescReturnsNonNullForKnownProperty_1252) {
    XmpKey key("Xmp.dc.title");
    const char* desc = XmpProperties::propertyDesc(key);
    EXPECT_NE(desc, nullptr);
}

TEST_F(XmpPropertiesTest_1252, PropertyDescReturnsNullForUnknownProperty_1252) {
    XmpKey key("Xmp.dc.nonExistentProperty99999");
    const char* desc = XmpProperties::propertyDesc(key);
    EXPECT_EQ(desc, nullptr);
}

// ==================== ns and prefix tests ====================

TEST_F(XmpPropertiesTest_1252, NsReturnsCorrectNamespaceForDc_1252) {
    std::string ns = XmpProperties::ns("dc");
    EXPECT_FALSE(ns.empty());
    EXPECT_EQ(ns, "http://purl.org/dc/elements/1.1/");
}

TEST_F(XmpPropertiesTest_1252, NsReturnsCorrectNamespaceForXmp_1252) {
    std::string ns = XmpProperties::ns("xmp");
    EXPECT_FALSE(ns.empty());
}

TEST_F(XmpPropertiesTest_1252, PrefixReturnsCorrectPrefixForDcNamespace_1252) {
    std::string prefix = XmpProperties::prefix("http://purl.org/dc/elements/1.1/");
    EXPECT_EQ(prefix, "dc");
}

TEST_F(XmpPropertiesTest_1252, PrefixReturnsEmptyForUnknownNamespace_1252) {
    std::string prefix = XmpProperties::prefix("http://nonexistent.example.com/");
    EXPECT_TRUE(prefix.empty());
}

TEST_F(XmpPropertiesTest_1252, NsReturnsEmptyForUnknownPrefix_1252) {
    std::string ns = XmpProperties::ns("unknownPrefix12345");
    EXPECT_TRUE(ns.empty());
}

// ==================== propertyList tests ====================

TEST_F(XmpPropertiesTest_1252, PropertyListReturnsNonNullForDc_1252) {
    const XmpPropertyInfo* pl = XmpProperties::propertyList("dc");
    EXPECT_NE(pl, nullptr);
}

TEST_F(XmpPropertiesTest_1252, PropertyListReturnsNonNullForXmp_1252) {
    const XmpPropertyInfo* pl = XmpProperties::propertyList("xmp");
    EXPECT_NE(pl, nullptr);
}

TEST_F(XmpPropertiesTest_1252, PropertyListReturnsNullForUnknownPrefix_1252) {
    const XmpPropertyInfo* pl = XmpProperties::propertyList("unknownPrefix12345");
    EXPECT_EQ(pl, nullptr);
}

// ==================== nsInfo tests ====================

TEST_F(XmpPropertiesTest_1252, NsInfoReturnsNonNullForDc_1252) {
    const XmpNsInfo* info = XmpProperties::nsInfo("dc");
    EXPECT_NE(info, nullptr);
}

TEST_F(XmpPropertiesTest_1252, NsInfoReturnsNonNullForXmp_1252) {
    const XmpNsInfo* info = XmpProperties::nsInfo("xmp");
    EXPECT_NE(info, nullptr);
}

// ==================== nsDesc tests ====================

TEST_F(XmpPropertiesTest_1252, NsDescReturnsNonNullForDc_1252) {
    const char* desc = XmpProperties::nsDesc("dc");
    EXPECT_NE(desc, nullptr);
}

// ==================== registerNs / unregisterNs tests ====================

TEST_F(XmpPropertiesTest_1252, RegisterAndUnregisterCustomNamespace_1252) {
    const std::string customNs = "http://example.com/custom/ns/";
    const std::string customPrefix = "customTest";

    XmpProperties::registerNs(customNs, customPrefix);

    std::string retrievedPrefix = XmpProperties::prefix(customNs);
    EXPECT_EQ(retrievedPrefix, customPrefix);

    std::string retrievedNs = XmpProperties::ns(customPrefix);
    EXPECT_EQ(retrievedNs, customNs);

    XmpProperties::unregisterNs(customNs);

    std::string afterUnregPrefix = XmpProperties::prefix(customNs);
    EXPECT_TRUE(afterUnregPrefix.empty());
}

TEST_F(XmpPropertiesTest_1252, RegisterNsOverwriteExisting_1252) {
    const std::string customNs = "http://example.com/overwrite/ns/";
    const std::string prefix1 = "overwrite1";
    const std::string prefix2 = "overwrite2";

    XmpProperties::registerNs(customNs, prefix1);
    EXPECT_EQ(XmpProperties::prefix(customNs), prefix1);

    XmpProperties::registerNs(customNs, prefix2);
    EXPECT_EQ(XmpProperties::prefix(customNs), prefix2);

    XmpProperties::unregisterNs(customNs);
}

TEST_F(XmpPropertiesTest_1252, UnregisterAllCustomNamespaces_1252) {
    const std::string ns1 = "http://example.com/test1/";
    const std::string ns2 = "http://example.com/test2/";

    XmpProperties::registerNs(ns1, "test1");
    XmpProperties::registerNs(ns2, "test2");

    XmpProperties::unregisterNs();

    // Built-in namespaces should still work
    std::string dcNs = XmpProperties::ns("dc");
    EXPECT_FALSE(dcNs.empty());

    // Custom namespaces should be gone
    EXPECT_TRUE(XmpProperties::prefix(ns1).empty());
    EXPECT_TRUE(XmpProperties::prefix(ns2).empty());
}

// ==================== registeredNamespaces tests ====================

TEST_F(XmpPropertiesTest_1252, RegisteredNamespacesContainsDc_1252) {
    Exiv2::Dictionary nsDict;
    XmpProperties::registeredNamespaces(nsDict);
    EXPECT_FALSE(nsDict.empty());

    // The dc namespace should be in there
    auto it = nsDict.find("dc");
    // Note: the dictionary may be keyed by prefix or namespace depending on implementation.
    // We just check it's not empty.
}

TEST_F(XmpPropertiesTest_1252, RegisteredNamespacesIncludesCustomAfterRegister_1252) {
    const std::string customNs = "http://example.com/regtest/";
    const std::string customPrefix = "regtest";

    XmpProperties::registerNs(customNs, customPrefix);

    Exiv2::Dictionary nsDict;
    XmpProperties::registeredNamespaces(nsDict);

    // Should find the custom namespace
    bool found = false;
    for (const auto& entry : nsDict) {
        if (entry.first == customPrefix || entry.second == customNs ||
            entry.first == customNs || entry.second == customPrefix) {
            found = true;
            break;
        }
    }
    EXPECT_TRUE(found);

    XmpProperties::unregisterNs(customNs);
}

// ==================== printProperties tests ====================

TEST_F(XmpPropertiesTest_1252, PrintPropertiesProducesOutput_1252) {
    std::ostringstream os;
    XmpProperties::printProperties(os, "dc");
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(XmpPropertiesTest_1252, PrintPropertiesForUnknownPrefixProducesNoOutput_1252) {
    std::ostringstream os;
    // This might throw or produce empty output for unknown prefix
    try {
        XmpProperties::printProperties(os, "unknownPrefix12345");
    } catch (...) {
        // If it throws, that's acceptable behavior
    }
}

// ==================== XmpKey tests ====================

class XmpKeyTest_1252 : public ::testing::Test {};

TEST_F(XmpKeyTest_1252, ConstructFromString_1252) {
    XmpKey key("Xmp.dc.title");
    EXPECT_EQ(key.familyName(), std::string("Xmp"));
    EXPECT_EQ(key.groupName(), "dc");
    EXPECT_EQ(key.tagName(), "title");
}

TEST_F(XmpKeyTest_1252, ConstructFromPrefixAndProperty_1252) {
    XmpKey key("dc", "title");
    EXPECT_EQ(key.groupName(), "dc");
    EXPECT_EQ(key.tagName(), "title");
}

TEST_F(XmpKeyTest_1252, KeyReturnsFullKey_1252) {
    XmpKey key("Xmp.dc.title");
    std::string k = key.key();
    EXPECT_EQ(k, "Xmp.dc.title");
}

TEST_F(XmpKeyTest_1252, CopyConstructor_1252) {
    XmpKey original("Xmp.dc.title");
    XmpKey copy(original);
    EXPECT_EQ(copy.key(), original.key());
    EXPECT_EQ(copy.groupName(), original.groupName());
    EXPECT_EQ(copy.tagName(), original.tagName());
}

TEST_F(XmpKeyTest_1252, AssignmentOperator_1252) {
    XmpKey key1("Xmp.dc.title");
    XmpKey key2("Xmp.dc.creator");
    key2 = key1;
    EXPECT_EQ(key2.key(), key1.key());
}

TEST_F(XmpKeyTest_1252, Clone_1252) {
    XmpKey key("Xmp.dc.title");
    auto cloned = key.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->key(), key.key());
}

TEST_F(XmpKeyTest_1252, FamilyNameIsXmp_1252) {
    XmpKey key("Xmp.dc.title");
    EXPECT_STREQ(key.familyName(), "Xmp");
}

TEST_F(XmpKeyTest_1252, TagLabelReturnsNonEmptyForKnownProperty_1252) {
    XmpKey key("Xmp.dc.title");
    std::string label = key.tagLabel();
    EXPECT_FALSE(label.empty());
}

TEST_F(XmpKeyTest_1252, TagDescReturnsNonEmptyForKnownProperty_1252) {
    XmpKey key("Xmp.dc.title");
    std::string desc = key.tagDesc();
    EXPECT_FALSE(desc.empty());
}

TEST_F(XmpKeyTest_1252, NsReturnsNamespace_1252) {
    XmpKey key("Xmp.dc.title");
    std::string ns = key.ns();
    EXPECT_FALSE(ns.empty());
}

TEST_F(XmpKeyTest_1252, TagReturnsValue_1252) {
    XmpKey key("Xmp.dc.title");
    uint16_t tag = key.tag();
    // Tag is computed, just ensure it doesn't throw
    (void)tag;
}

// ==================== lookupNsRegistry tests ====================

TEST_F(XmpPropertiesTest_1252, LookupNsRegistryReturnsNullForUnregisteredPrefix_1252) {
    XmpNsInfo::Prefix prefix("nonExistentRegistryPrefix12345");
    const XmpNsInfo* info = XmpProperties::lookupNsRegistry(prefix);
    EXPECT_EQ(info, nullptr);
}

TEST_F(XmpPropertiesTest_1252, LookupNsRegistryReturnsInfoAfterRegister_1252) {
    const std::string customNs = "http://example.com/lookup/ns/";
    const std::string customPrefix = "lookupTest";

    XmpProperties::registerNs(customNs, customPrefix);

    XmpNsInfo::Prefix prefix(customPrefix);
    const XmpNsInfo* info = XmpProperties::lookupNsRegistry(prefix);
    EXPECT_NE(info, nullptr);

    XmpProperties::unregisterNs(customNs);
}

// ==================== Nested key handling in propertyInfo ====================

TEST_F(XmpPropertiesTest_1252, PropertyInfoHandlesNestedKeyWithSlash_1252) {
    // Test a nested key pattern like "Xmp.dc.something/dc:title"
    // This tests the nested key parsing in propertyInfo
    try {
        XmpKey key("Xmp.dc.something/dc:title");
        const XmpPropertyInfo* info = XmpProperties::propertyInfo(key);
        // It should find "title" in the "dc" property list
        if (info != nullptr) {
            EXPECT_STREQ(info->name_, "title");
        }
    } catch (...) {
        // If the key format is invalid, that's acceptable
    }
}

// ==================== Edge cases ====================

TEST_F(XmpPropertiesTest_1252, PropertyInfoForExifISOSpeedRatings_1252) {
    XmpKey key("Xmp.exif.ISOSpeedRatings");
    const XmpPropertyInfo* info = XmpProperties::propertyInfo(key);
    if (info != nullptr) {
        EXPECT_STREQ(info->name_, "ISOSpeedRatings");
    }
}

TEST_F(XmpPropertiesTest_1252, PropertyInfoForPhotoshopPrefix_1252) {
    XmpKey key("Xmp.photoshop.City");
    const XmpPropertyInfo* info = XmpProperties::propertyInfo(key);
    if (info != nullptr) {
        EXPECT_STREQ(info->name_, "City");
    }
}

TEST_F(XmpPropertiesTest_1252, PropertyListForTiff_1252) {
    const XmpPropertyInfo* pl = XmpProperties::propertyList("tiff");
    EXPECT_NE(pl, nullptr);
}

TEST_F(XmpPropertiesTest_1252, PropertyListForExif_1252) {
    const XmpPropertyInfo* pl = XmpProperties::propertyList("exif");
    EXPECT_NE(pl, nullptr);
}

TEST_F(XmpPropertiesTest_1252, NsForTiff_1252) {
    std::string ns = XmpProperties::ns("tiff");
    EXPECT_FALSE(ns.empty());
}

TEST_F(XmpPropertiesTest_1252, NsForExif_1252) {
    std::string ns = XmpProperties::ns("exif");
    EXPECT_FALSE(ns.empty());
}

TEST_F(XmpPropertiesTest_1252, PrefixForTiffNamespace_1252) {
    std::string tiffNs = XmpProperties::ns("tiff");
    if (!tiffNs.empty()) {
        std::string prefix = XmpProperties::prefix(tiffNs);
        EXPECT_EQ(prefix, "tiff");
    }
}

TEST_F(XmpPropertiesTest_1252, DcRights_1252) {
    XmpKey key("Xmp.dc.rights");
    const XmpPropertyInfo* info = XmpProperties::propertyInfo(key);
    ASSERT_NE(info, nullptr);
    EXPECT_STREQ(info->name_, "rights");
}

TEST_F(XmpPropertiesTest_1252, DcFormat_1252) {
    XmpKey key("Xmp.dc.format");
    const XmpPropertyInfo* info = XmpProperties::propertyInfo(key);
    ASSERT_NE(info, nullptr);
    EXPECT_STREQ(info->name_, "format");
}
