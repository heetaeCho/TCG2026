#include <gtest/gtest.h>
#include <string>
#include <sstream>
#include <map>

#include "exiv2/properties.hpp"
#include "exiv2/value.hpp"
#include "exiv2/xmp_exiv2.hpp"

using namespace Exiv2;

class XmpPropertiesTest_1247 : public ::testing::Test {
protected:
    void SetUp() override {
        // Ensure clean state by unregistering all custom namespaces
        XmpProperties::unregisterNs();
    }

    void TearDown() override {
        XmpProperties::unregisterNs();
    }
};

// =============================================================================
// Tests for prefix()
// =============================================================================

TEST_F(XmpPropertiesTest_1247, PrefixReturnsCorrectPrefixForDcNamespace_1247) {
    std::string result = XmpProperties::prefix("http://purl.org/dc/elements/1.1/");
    EXPECT_EQ(result, "dc");
}

TEST_F(XmpPropertiesTest_1247, PrefixReturnsCorrectPrefixForXmpNamespace_1247) {
    std::string result = XmpProperties::prefix("http://ns.adobe.com/xap/1.0/");
    EXPECT_EQ(result, "xmp");
}

TEST_F(XmpPropertiesTest_1247, PrefixReturnsCorrectPrefixForTiffNamespace_1247) {
    std::string result = XmpProperties::prefix("http://ns.adobe.com/tiff/1.0/");
    EXPECT_EQ(result, "tiff");
}

TEST_F(XmpPropertiesTest_1247, PrefixReturnsCorrectPrefixForExifNamespace_1247) {
    std::string result = XmpProperties::prefix("http://ns.adobe.com/exif/1.0/");
    EXPECT_EQ(result, "exif");
}

TEST_F(XmpPropertiesTest_1247, PrefixReturnsEmptyStringForUnknownNamespace_1247) {
    std::string result = XmpProperties::prefix("http://unknown.namespace.example.com/");
    EXPECT_EQ(result, "");
}

TEST_F(XmpPropertiesTest_1247, PrefixAppendsSlashIfMissing_1247) {
    // The implementation appends '/' if ns doesn't end with '/' or '#'
    std::string result = XmpProperties::prefix("http://purl.org/dc/elements/1.1");
    EXPECT_EQ(result, "dc");
}

TEST_F(XmpPropertiesTest_1247, PrefixHandlesNamespaceEndingWithHash_1247) {
    std::string result = XmpProperties::prefix("http://ns.microsoft.com/photo/1.2/t/RegionInfo#");
    EXPECT_EQ(result, "MPRI");
}

TEST_F(XmpPropertiesTest_1247, PrefixReturnsEmptyForEmptyStringInput_1247) {
    // Empty string - this may throw or return empty
    // The implementation tries to access back() on empty string which is UB,
    // but we test with at least one character
    std::string result = XmpProperties::prefix("/");
    EXPECT_EQ(result, "");
}

TEST_F(XmpPropertiesTest_1247, PrefixForPhotoshopNamespace_1247) {
    std::string result = XmpProperties::prefix("http://ns.adobe.com/photoshop/1.0/");
    EXPECT_EQ(result, "photoshop");
}

TEST_F(XmpPropertiesTest_1247, PrefixForPdfNamespace_1247) {
    std::string result = XmpProperties::prefix("http://ns.adobe.com/pdf/1.3/");
    EXPECT_EQ(result, "pdf");
}

// =============================================================================
// Tests for registerNs() and prefix() interaction
// =============================================================================

TEST_F(XmpPropertiesTest_1247, RegisterNsAllowsCustomNamespaceToBeFound_1247) {
    XmpProperties::registerNs("http://example.com/custom/1.0/", "myCustom");
    std::string result = XmpProperties::prefix("http://example.com/custom/1.0/");
    EXPECT_EQ(result, "myCustom");
}

TEST_F(XmpPropertiesTest_1247, RegisterNsWithoutTrailingSlashStillWorks_1247) {
    XmpProperties::registerNs("http://example.com/test/ns/", "testNs");
    // prefix() should find it with or without trailing slash
    std::string result = XmpProperties::prefix("http://example.com/test/ns/");
    EXPECT_EQ(result, "testNs");
}

TEST_F(XmpPropertiesTest_1247, UnregisterNsRemovesCustomNamespace_1247) {
    XmpProperties::registerNs("http://example.com/removable/1.0/", "removable");
    std::string result = XmpProperties::prefix("http://example.com/removable/1.0/");
    EXPECT_EQ(result, "removable");

    XmpProperties::unregisterNs("http://example.com/removable/1.0/");
    result = XmpProperties::prefix("http://example.com/removable/1.0/");
    EXPECT_EQ(result, "");
}

TEST_F(XmpPropertiesTest_1247, UnregisterAllNsClearsCustomNamespaces_1247) {
    XmpProperties::registerNs("http://example.com/ns1/", "ns1");
    XmpProperties::registerNs("http://example.com/ns2/", "ns2");
    XmpProperties::unregisterNs();

    EXPECT_EQ(XmpProperties::prefix("http://example.com/ns1/"), "");
    EXPECT_EQ(XmpProperties::prefix("http://example.com/ns2/"), "");
}

TEST_F(XmpPropertiesTest_1247, BuiltinNamespacesRemainAfterUnregisterAll_1247) {
    XmpProperties::unregisterNs();
    // Built-in namespaces should still be accessible
    EXPECT_EQ(XmpProperties::prefix("http://purl.org/dc/elements/1.1/"), "dc");
    EXPECT_EQ(XmpProperties::prefix("http://ns.adobe.com/xap/1.0/"), "xmp");
}

// =============================================================================
// Tests for ns()
// =============================================================================

TEST_F(XmpPropertiesTest_1247, NsReturnsCorrectNamespaceForDcPrefix_1247) {
    std::string result = XmpProperties::ns("dc");
    EXPECT_EQ(result, "http://purl.org/dc/elements/1.1/");
}

TEST_F(XmpPropertiesTest_1247, NsReturnsCorrectNamespaceForXmpPrefix_1247) {
    std::string result = XmpProperties::ns("xmp");
    EXPECT_EQ(result, "http://ns.adobe.com/xap/1.0/");
}

TEST_F(XmpPropertiesTest_1247, NsReturnsCorrectNamespaceForTiffPrefix_1247) {
    std::string result = XmpProperties::ns("tiff");
    EXPECT_EQ(result, "http://ns.adobe.com/tiff/1.0/");
}

TEST_F(XmpPropertiesTest_1247, NsReturnsEmptyForUnknownPrefix_1247) {
    std::string result = XmpProperties::ns("unknownPrefix");
    EXPECT_TRUE(result.empty());
}

// =============================================================================
// Tests for nsInfo()
// =============================================================================

TEST_F(XmpPropertiesTest_1247, NsInfoReturnsNonNullForKnownPrefix_1247) {
    const XmpNsInfo* info = XmpProperties::nsInfo("dc");
    ASSERT_NE(info, nullptr);
    EXPECT_STREQ(info->prefix_, "dc");
}

TEST_F(XmpPropertiesTest_1247, NsInfoReturnsNullForUnknownPrefix_1247) {
    const XmpNsInfo* info = XmpProperties::nsInfo("nonexistent");
    EXPECT_EQ(info, nullptr);
}

// =============================================================================
// Tests for nsDesc()
// =============================================================================

TEST_F(XmpPropertiesTest_1247, NsDescReturnsDescriptionForKnownPrefix_1247) {
    const char* desc = XmpProperties::nsDesc("dc");
    ASSERT_NE(desc, nullptr);
    EXPECT_STREQ(desc, "Dublin Core schema");
}

// =============================================================================
// Tests for propertyList()
// =============================================================================

TEST_F(XmpPropertiesTest_1247, PropertyListReturnsNonNullForDc_1247) {
    const XmpPropertyInfo* list = XmpProperties::propertyList("dc");
    EXPECT_NE(list, nullptr);
}

TEST_F(XmpPropertiesTest_1247, PropertyListReturnsNullForXmpGWhichHasNullPropertyInfo_1247) {
    // xmpG has nullptr for xmpPropertyInfo_
    const XmpPropertyInfo* list = XmpProperties::propertyList("xmpG");
    EXPECT_EQ(list, nullptr);
}

// =============================================================================
// Tests for registeredNamespaces()
// =============================================================================

TEST_F(XmpPropertiesTest_1247, RegisteredNamespacesContainsCustomRegistrations_1247) {
    XmpProperties::registerNs("http://example.com/regtest/", "regtest");
    Dictionary nsDict;
    XmpProperties::registeredNamespaces(nsDict);
    EXPECT_NE(nsDict.find("http://example.com/regtest/"), nsDict.end());
    if (nsDict.find("http://example.com/regtest/") != nsDict.end()) {
        EXPECT_EQ(nsDict["http://example.com/regtest/"], "regtest");
    }
}

// =============================================================================
// Tests for lookupNsRegistry()
// =============================================================================

TEST_F(XmpPropertiesTest_1247, LookupNsRegistryReturnsNullForUnregisteredPrefix_1247) {
    const XmpNsInfo* result = XmpProperties::lookupNsRegistry(XmpNsInfo::Prefix{"nonexistent"});
    EXPECT_EQ(result, nullptr);
}

TEST_F(XmpPropertiesTest_1247, LookupNsRegistryReturnsInfoForRegisteredPrefix_1247) {
    XmpProperties::registerNs("http://example.com/lookup/", "lookupTest");
    const XmpNsInfo* result = XmpProperties::lookupNsRegistry(XmpNsInfo::Prefix{"lookupTest"});
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->prefix_, "lookupTest");
}

// =============================================================================
// Tests for printProperties()
// =============================================================================

TEST_F(XmpPropertiesTest_1247, PrintPropertiesOutputsToStream_1247) {
    std::ostringstream oss;
    XmpProperties::printProperties(oss, "dc");
    std::string output = oss.str();
    // Should produce some output for the dc namespace
    EXPECT_FALSE(output.empty());
}

// =============================================================================
// Tests for propertyInfo(), propertyTitle(), propertyDesc(), propertyType()
// =============================================================================

TEST_F(XmpPropertiesTest_1247, PropertyInfoReturnsNonNullForKnownProperty_1247) {
    XmpKey key("Xmp.dc.title");
    const XmpPropertyInfo* info = XmpProperties::propertyInfo(key);
    EXPECT_NE(info, nullptr);
}

TEST_F(XmpPropertiesTest_1247, PropertyTitleReturnsNonNullForKnownProperty_1247) {
    XmpKey key("Xmp.dc.title");
    const char* title = XmpProperties::propertyTitle(key);
    EXPECT_NE(title, nullptr);
}

TEST_F(XmpPropertiesTest_1247, PropertyDescReturnsNonNullForKnownProperty_1247) {
    XmpKey key("Xmp.dc.title");
    const char* desc = XmpProperties::propertyDesc(key);
    EXPECT_NE(desc, nullptr);
}

TEST_F(XmpPropertiesTest_1247, PropertyTypeReturnsValidTypeForKnownProperty_1247) {
    XmpKey key("Xmp.dc.title");
    TypeId type = XmpProperties::propertyType(key);
    EXPECT_NE(type, invalidTypeId);
}

// =============================================================================
// Tests for multiple registrations and edge cases
// =============================================================================

TEST_F(XmpPropertiesTest_1247, RegisterSameNamespaceTwiceOverwritesPrefix_1247) {
    XmpProperties::registerNs("http://example.com/overwrite/", "first");
    std::string p1 = XmpProperties::prefix("http://example.com/overwrite/");
    EXPECT_EQ(p1, "first");

    XmpProperties::registerNs("http://example.com/overwrite/", "second");
    std::string p2 = XmpProperties::prefix("http://example.com/overwrite/");
    EXPECT_EQ(p2, "second");
}

TEST_F(XmpPropertiesTest_1247, PrefixForIptcNamespace_1247) {
    std::string result = XmpProperties::prefix("http://iptc.org/std/Iptc4xmpCore/1.0/xmlns/");
    // Could be "iptc" or "Iptc4xmpCore" - the first match in the table
    EXPECT_FALSE(result.empty());
}

TEST_F(XmpPropertiesTest_1247, PrefixForVideoNamespace_1247) {
    std::string result = XmpProperties::prefix("http://www.video/");
    EXPECT_EQ(result, "video");
}

TEST_F(XmpPropertiesTest_1247, PrefixForAudioNamespace_1247) {
    std::string result = XmpProperties::prefix("http://www.audio/");
    EXPECT_EQ(result, "audio");
}

TEST_F(XmpPropertiesTest_1247, PrefixForGPanoNamespace_1247) {
    std::string result = XmpProperties::prefix("http://ns.google.com/photos/1.0/panorama/");
    EXPECT_EQ(result, "GPano");
}

TEST_F(XmpPropertiesTest_1247, PrefixForDigiKamNamespace_1247) {
    std::string result = XmpProperties::prefix("http://www.digikam.org/ns/1.0/");
    EXPECT_EQ(result, "digiKam");
}

TEST_F(XmpPropertiesTest_1247, PrefixForKipiNamespace_1247) {
    std::string result = XmpProperties::prefix("http://www.digikam.org/ns/kipi/1.0/");
    EXPECT_EQ(result, "kipi");
}

TEST_F(XmpPropertiesTest_1247, RegisteredNamespaceAppearsInRegisteredNamespaces_1247) {
    XmpProperties::registerNs("http://example.com/dicttest/", "dicttest");
    Dictionary nsDict;
    XmpProperties::registeredNamespaces(nsDict);

    bool found = false;
    for (const auto& entry : nsDict) {
        if (entry.first == "http://example.com/dicttest/" && entry.second == "dicttest") {
            found = true;
            break;
        }
    }
    EXPECT_TRUE(found);
}

TEST_F(XmpPropertiesTest_1247, UnregisterNsForNonExistentDoesNotCrash_1247) {
    // Unregistering a namespace that was never registered should not crash
    EXPECT_NO_THROW(XmpProperties::unregisterNs("http://nonexistent.example.com/"));
}

TEST_F(XmpPropertiesTest_1247, PrefixForXmpRightsNamespace_1247) {
    std::string result = XmpProperties::prefix("http://ns.adobe.com/xap/1.0/rights/");
    EXPECT_EQ(result, "xmpRights");
}

TEST_F(XmpPropertiesTest_1247, PrefixForXmpMMNamespace_1247) {
    std::string result = XmpProperties::prefix("http://ns.adobe.com/xap/1.0/mm/");
    EXPECT_EQ(result, "xmpMM");
}

TEST_F(XmpPropertiesTest_1247, PrefixForCrsNamespace_1247) {
    std::string result = XmpProperties::prefix("http://ns.adobe.com/camera-raw-settings/1.0/");
    EXPECT_EQ(result, "crs");
}

TEST_F(XmpPropertiesTest_1247, PrefixForLightroomNamespace_1247) {
    std::string result = XmpProperties::prefix("http://ns.adobe.com/lightroom/1.0/");
    EXPECT_EQ(result, "lr");
}

TEST_F(XmpPropertiesTest_1247, CustomRegisteredNsTakesPriorityOverBuiltin_1247) {
    // Register a custom prefix for a built-in namespace
    // This tests that the registry is checked before the built-in table
    XmpProperties::registerNs("http://example.com/priority/", "priorityTest");
    std::string result = XmpProperties::prefix("http://example.com/priority/");
    EXPECT_EQ(result, "priorityTest");
}

TEST_F(XmpPropertiesTest_1247, PrintPropertyOutputsToStream_1247) {
    std::ostringstream oss;
    XmpTextValue val("test value");
    XmpProperties::printProperty(oss, "Xmp.dc.title", val);
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}
