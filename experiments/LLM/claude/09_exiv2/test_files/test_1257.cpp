#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <map>

#include <exiv2/properties.hpp>
#include <exiv2/xmp_exiv2.hpp>
#include <exiv2/value.hpp>

using namespace Exiv2;

class XmpPropertiesTest_1257 : public ::testing::Test {
protected:
    void SetUp() override {
        // Ensure clean state by unregistering any custom namespaces
    }

    void TearDown() override {
        // Clean up any registered namespaces
        XmpProperties::unregisterNs();
    }
};

// ============================================================
// Tests for ns() - get namespace from prefix
// ============================================================

TEST_F(XmpPropertiesTest_1257, NsReturnsNamespaceForKnownPrefix_dc_1257) {
    std::string result = XmpProperties::ns("dc");
    EXPECT_FALSE(result.empty());
    EXPECT_EQ(result, "http://purl.org/dc/elements/1.1/");
}

TEST_F(XmpPropertiesTest_1257, NsReturnsNamespaceForKnownPrefix_xmp_1257) {
    std::string result = XmpProperties::ns("xmp");
    EXPECT_FALSE(result.empty());
}

TEST_F(XmpPropertiesTest_1257, NsReturnsNamespaceForKnownPrefix_exif_1257) {
    std::string result = XmpProperties::ns("exif");
    EXPECT_FALSE(result.empty());
}

TEST_F(XmpPropertiesTest_1257, NsThrowsForUnknownPrefix_1257) {
    EXPECT_THROW(XmpProperties::ns("nonexistent_prefix_xyz"), Error);
}

TEST_F(XmpPropertiesTest_1257, NsThrowsForEmptyPrefix_1257) {
    EXPECT_THROW(XmpProperties::ns(""), Error);
}

// ============================================================
// Tests for prefix() - get prefix from namespace
// ============================================================

TEST_F(XmpPropertiesTest_1257, PrefixReturnsPrefixForKnownNamespace_1257) {
    std::string result = XmpProperties::prefix("http://purl.org/dc/elements/1.1/");
    EXPECT_EQ(result, "dc");
}

TEST_F(XmpPropertiesTest_1257, PrefixReturnsEmptyForUnknownNamespace_1257) {
    std::string result = XmpProperties::prefix("http://nonexistent.example.com/ns/");
    EXPECT_TRUE(result.empty());
}

TEST_F(XmpPropertiesTest_1257, PrefixReturnsEmptyForEmptyNamespace_1257) {
    std::string result = XmpProperties::prefix("");
    EXPECT_TRUE(result.empty());
}

// ============================================================
// Tests for registerNs() and unregisterNs()
// ============================================================

TEST_F(XmpPropertiesTest_1257, RegisterNsAndRetrievePrefix_1257) {
    XmpProperties::registerNs("http://test.example.com/ns/", "testprefix");
    std::string result = XmpProperties::prefix("http://test.example.com/ns/");
    EXPECT_EQ(result, "testprefix");
    XmpProperties::unregisterNs("http://test.example.com/ns/");
}

TEST_F(XmpPropertiesTest_1257, RegisterNsAndRetrieveNs_1257) {
    XmpProperties::registerNs("http://test2.example.com/ns/", "testpfx2");
    std::string result = XmpProperties::ns("testpfx2");
    EXPECT_EQ(result, "http://test2.example.com/ns/");
    XmpProperties::unregisterNs("http://test2.example.com/ns/");
}

TEST_F(XmpPropertiesTest_1257, UnregisterNsRemovesRegisteredNamespace_1257) {
    XmpProperties::registerNs("http://unreg.example.com/ns/", "unregpfx");
    XmpProperties::unregisterNs("http://unreg.example.com/ns/");
    std::string result = XmpProperties::prefix("http://unreg.example.com/ns/");
    EXPECT_TRUE(result.empty());
}

TEST_F(XmpPropertiesTest_1257, UnregisterAllCustomNamespaces_1257) {
    XmpProperties::registerNs("http://all1.example.com/ns/", "allpfx1");
    XmpProperties::registerNs("http://all2.example.com/ns/", "allpfx2");
    XmpProperties::unregisterNs();
    std::string result1 = XmpProperties::prefix("http://all1.example.com/ns/");
    std::string result2 = XmpProperties::prefix("http://all2.example.com/ns/");
    EXPECT_TRUE(result1.empty());
    EXPECT_TRUE(result2.empty());
}

TEST_F(XmpPropertiesTest_1257, UnregisterNsDoesNotAffectBuiltinNamespaces_1257) {
    XmpProperties::unregisterNs();
    // Built-in namespaces should still work
    std::string result = XmpProperties::prefix("http://purl.org/dc/elements/1.1/");
    EXPECT_EQ(result, "dc");
}

// ============================================================
// Tests for propertyList()
// ============================================================

TEST_F(XmpPropertiesTest_1257, PropertyListReturnsNonNullForKnownPrefix_1257) {
    const XmpPropertyInfo* list = XmpProperties::propertyList("dc");
    EXPECT_NE(list, nullptr);
}

TEST_F(XmpPropertiesTest_1257, PropertyListReturnsNullForUnknownPrefix_1257) {
    const XmpPropertyInfo* list = XmpProperties::propertyList("nonexistent_xyz");
    EXPECT_EQ(list, nullptr);
}

// ============================================================
// Tests for nsInfo()
// ============================================================

TEST_F(XmpPropertiesTest_1257, NsInfoReturnsNonNullForKnownPrefix_1257) {
    const XmpNsInfo* info = XmpProperties::nsInfo("dc");
    EXPECT_NE(info, nullptr);
}

TEST_F(XmpPropertiesTest_1257, NsInfoThrowsForUnknownPrefix_1257) {
    EXPECT_THROW(XmpProperties::nsInfo("nonexistent_xyz"), Error);
}

// ============================================================
// Tests for nsDesc()
// ============================================================

TEST_F(XmpPropertiesTest_1257, NsDescReturnsNonNullForKnownPrefix_1257) {
    const char* desc = XmpProperties::nsDesc("dc");
    EXPECT_NE(desc, nullptr);
    EXPECT_GT(strlen(desc), 0u);
}

TEST_F(XmpPropertiesTest_1257, NsDescThrowsForUnknownPrefix_1257) {
    EXPECT_THROW(XmpProperties::nsDesc("nonexistent_xyz"), Error);
}

// ============================================================
// Tests for propertyInfo(), propertyTitle(), propertyDesc(), propertyType()
// ============================================================

TEST_F(XmpPropertiesTest_1257, PropertyInfoReturnsNonNullForKnownKey_1257) {
    XmpKey key("Xmp.dc.title");
    const XmpPropertyInfo* info = XmpProperties::propertyInfo(key);
    EXPECT_NE(info, nullptr);
}

TEST_F(XmpPropertiesTest_1257, PropertyTitleReturnsNonNullForKnownKey_1257) {
    XmpKey key("Xmp.dc.title");
    const char* title = XmpProperties::propertyTitle(key);
    EXPECT_NE(title, nullptr);
}

TEST_F(XmpPropertiesTest_1257, PropertyDescReturnsNonNullForKnownKey_1257) {
    XmpKey key("Xmp.dc.title");
    const char* desc = XmpProperties::propertyDesc(key);
    EXPECT_NE(desc, nullptr);
}

TEST_F(XmpPropertiesTest_1257, PropertyTypeReturnsValidTypeForKnownKey_1257) {
    XmpKey key("Xmp.dc.title");
    TypeId type = XmpProperties::propertyType(key);
    EXPECT_NE(type, invalidTypeId);
}

TEST_F(XmpPropertiesTest_1257, PropertyInfoReturnsNullForUnknownProperty_1257) {
    XmpKey key("Xmp.dc.nonExistentPropertyXyz");
    const XmpPropertyInfo* info = XmpProperties::propertyInfo(key);
    EXPECT_EQ(info, nullptr);
}

TEST_F(XmpPropertiesTest_1257, PropertyTitleReturnsEmptyStringForUnknownProperty_1257) {
    XmpKey key("Xmp.dc.nonExistentPropertyXyz");
    const char* title = XmpProperties::propertyTitle(key);
    // Should return empty string or nullptr for unknown property
    if (title) {
        EXPECT_STREQ(title, "");
    }
}

// ============================================================
// Tests for printProperties()
// ============================================================

TEST_F(XmpPropertiesTest_1257, PrintPropertiesOutputsForKnownPrefix_1257) {
    std::ostringstream oss;
    XmpProperties::printProperties(oss, "dc");
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(XmpPropertiesTest_1257, PrintPropertiesOutputsNothingForUnknownPrefix_1257) {
    std::ostringstream oss;
    XmpProperties::printProperties(oss, "nonexistent_xyz");
    std::string output = oss.str();
    EXPECT_TRUE(output.empty());
}

TEST_F(XmpPropertiesTest_1257, PrintPropertiesContainsKnownPropertyName_1257) {
    std::ostringstream oss;
    XmpProperties::printProperties(oss, "dc");
    std::string output = oss.str();
    // "title" is a well-known Dublin Core property
    EXPECT_NE(output.find("title"), std::string::npos);
}

// ============================================================
// Tests for registeredNamespaces()
// ============================================================

TEST_F(XmpPropertiesTest_1257, RegisteredNamespacesContainsBuiltins_1257) {
    Dictionary nsDict;
    XmpProperties::registeredNamespaces(nsDict);
    // Should contain at least dc
    bool found_dc = false;
    for (auto& kv : nsDict) {
        if (kv.second == "dc" || kv.first == "http://purl.org/dc/elements/1.1/") {
            found_dc = true;
            break;
        }
    }
    EXPECT_TRUE(found_dc);
}

TEST_F(XmpPropertiesTest_1257, RegisteredNamespacesIncludesCustomRegistered_1257) {
    XmpProperties::registerNs("http://customreg.example.com/ns/", "custreg");
    Dictionary nsDict;
    XmpProperties::registeredNamespaces(nsDict);
    bool found = false;
    for (auto& kv : nsDict) {
        if (kv.first == "http://customreg.example.com/ns/" && kv.second == "custreg") {
            found = true;
            break;
        }
    }
    EXPECT_TRUE(found);
    XmpProperties::unregisterNs("http://customreg.example.com/ns/");
}

// ============================================================
// Tests for lookupNsRegistry()
// ============================================================

TEST_F(XmpPropertiesTest_1257, LookupNsRegistryReturnsNullForUnregisteredPrefix_1257) {
    XmpNsInfo::Prefix prefix("nonexistent_reg_prefix");
    const XmpNsInfo* info = XmpProperties::lookupNsRegistry(prefix);
    EXPECT_EQ(info, nullptr);
}

TEST_F(XmpPropertiesTest_1257, LookupNsRegistryReturnsInfoForRegisteredPrefix_1257) {
    XmpProperties::registerNs("http://lookup.example.com/ns/", "lookuppfx");
    XmpNsInfo::Prefix prefix("lookuppfx");
    const XmpNsInfo* info = XmpProperties::lookupNsRegistry(prefix);
    EXPECT_NE(info, nullptr);
    XmpProperties::unregisterNs("http://lookup.example.com/ns/");
}

// ============================================================
// Tests for printProperty()
// ============================================================

TEST_F(XmpPropertiesTest_1257, PrintPropertyOutputsKeyAndValue_1257) {
    std::ostringstream oss;
    XmpTextValue val("TestValue");
    XmpProperties::printProperty(oss, "Xmp.dc.title", val);
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

// ============================================================
// Edge case: re-register same namespace
// ============================================================

TEST_F(XmpPropertiesTest_1257, ReregisterSameNamespaceUpdatesPrefix_1257) {
    XmpProperties::registerNs("http://reregister.example.com/ns/", "rerpfx1");
    std::string prefix1 = XmpProperties::prefix("http://reregister.example.com/ns/");
    EXPECT_EQ(prefix1, "rerpfx1");
    
    // Re-register with a different prefix
    XmpProperties::registerNs("http://reregister.example.com/ns/", "rerpfx2");
    std::string prefix2 = XmpProperties::prefix("http://reregister.example.com/ns/");
    EXPECT_EQ(prefix2, "rerpfx2");
    
    XmpProperties::unregisterNs("http://reregister.example.com/ns/");
}

// ============================================================
// Tests for multiple known prefixes
// ============================================================

TEST_F(XmpPropertiesTest_1257, NsWorksForTiffPrefix_1257) {
    std::string result = XmpProperties::ns("tiff");
    EXPECT_FALSE(result.empty());
}

TEST_F(XmpPropertiesTest_1257, PropertyListWorksForExifPrefix_1257) {
    const XmpPropertyInfo* list = XmpProperties::propertyList("exif");
    EXPECT_NE(list, nullptr);
}

TEST_F(XmpPropertiesTest_1257, PropertyListWorksForXmpPrefix_1257) {
    const XmpPropertyInfo* list = XmpProperties::propertyList("xmp");
    EXPECT_NE(list, nullptr);
}

// ============================================================
// Tests for XmpKey-based property queries on exif prefix
// ============================================================

TEST_F(XmpPropertiesTest_1257, PropertyInfoForExifDateTimeOriginal_1257) {
    XmpKey key("Xmp.exif.DateTimeOriginal");
    const XmpPropertyInfo* info = XmpProperties::propertyInfo(key);
    EXPECT_NE(info, nullptr);
}

TEST_F(XmpPropertiesTest_1257, PropertyTypeForExifDateTimeOriginal_1257) {
    XmpKey key("Xmp.exif.DateTimeOriginal");
    TypeId type = XmpProperties::propertyType(key);
    EXPECT_NE(type, invalidTypeId);
}
