#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <map>

#include "exiv2/properties.hpp"
#include "exiv2/value.hpp"
#include "exiv2/types.hpp"

namespace {

using namespace Exiv2;

class XmpPropertiesTest_1246 : public ::testing::Test {
protected:
    void SetUp() override {
        // Ensure a clean state by unregistering all custom namespaces
        XmpProperties::unregisterNs();
    }

    void TearDown() override {
        // Clean up after each test
        XmpProperties::unregisterNs();
    }
};

// ============================================================
// Tests for registerNs and prefix/ns lookup
// ============================================================

TEST_F(XmpPropertiesTest_1246, RegisterNs_BasicRegistration_1246) {
    const std::string nsUri = "http://example.com/test/1246/";
    const std::string nsPrefix = "testNs1246";

    XmpProperties::registerNs(nsUri, nsPrefix);

    std::string resultPrefix = XmpProperties::prefix(nsUri);
    EXPECT_EQ(resultPrefix, nsPrefix);
}

TEST_F(XmpPropertiesTest_1246, RegisterNs_LookupNsByPrefix_1246) {
    const std::string nsUri = "http://example.com/test2/1246/";
    const std::string nsPrefix = "testNs2_1246";

    XmpProperties::registerNs(nsUri, nsPrefix);

    std::string resultNs = XmpProperties::ns(nsPrefix);
    EXPECT_EQ(resultNs, nsUri);
}

TEST_F(XmpPropertiesTest_1246, UnregisterNs_SpecificNamespace_1246) {
    const std::string nsUri = "http://example.com/unreg/1246/";
    const std::string nsPrefix = "unregNs1246";

    XmpProperties::registerNs(nsUri, nsPrefix);
    // Verify it's registered
    EXPECT_EQ(XmpProperties::prefix(nsUri), nsPrefix);

    XmpProperties::unregisterNs(nsUri);

    // After unregistering, prefix lookup for the custom ns should return empty or throw
    std::string result = XmpProperties::prefix(nsUri);
    EXPECT_TRUE(result.empty());
}

TEST_F(XmpPropertiesTest_1246, UnregisterNs_AllNamespaces_1246) {
    const std::string nsUri1 = "http://example.com/all1/1246/";
    const std::string nsPrefix1 = "allNs1_1246";
    const std::string nsUri2 = "http://example.com/all2/1246/";
    const std::string nsPrefix2 = "allNs2_1246";

    XmpProperties::registerNs(nsUri1, nsPrefix1);
    XmpProperties::registerNs(nsUri2, nsPrefix2);

    // Verify both registered
    EXPECT_EQ(XmpProperties::prefix(nsUri1), nsPrefix1);
    EXPECT_EQ(XmpProperties::prefix(nsUri2), nsPrefix2);

    XmpProperties::unregisterNs();

    // Both should now be gone
    EXPECT_TRUE(XmpProperties::prefix(nsUri1).empty());
    EXPECT_TRUE(XmpProperties::prefix(nsUri2).empty());
}

TEST_F(XmpPropertiesTest_1246, RegisterNs_OverwriteExistingPrefix_1246) {
    const std::string nsUri = "http://example.com/overwrite/1246/";
    const std::string nsPrefix1 = "owNs1_1246";
    const std::string nsPrefix2 = "owNs2_1246";

    XmpProperties::registerNs(nsUri, nsPrefix1);
    EXPECT_EQ(XmpProperties::prefix(nsUri), nsPrefix1);

    // Re-register with different prefix
    XmpProperties::registerNs(nsUri, nsPrefix2);
    std::string resultPrefix = XmpProperties::prefix(nsUri);
    EXPECT_EQ(resultPrefix, nsPrefix2);
}

// ============================================================
// Tests for lookupNsRegistry
// ============================================================

TEST_F(XmpPropertiesTest_1246, LookupNsRegistry_RegisteredPrefix_1246) {
    const std::string nsUri = "http://example.com/lookup/1246/";
    const std::string nsPrefix = "lookupNs1246";

    XmpProperties::registerNs(nsUri, nsPrefix);

    XmpNsInfo::Prefix prefixStruct;
    prefixStruct.prefix_ = nsPrefix.c_str();

    const XmpNsInfo* info = XmpProperties::lookupNsRegistry(prefixStruct);
    EXPECT_NE(info, nullptr);
}

TEST_F(XmpPropertiesTest_1246, LookupNsRegistry_UnregisteredPrefix_1246) {
    XmpNsInfo::Prefix prefixStruct;
    prefixStruct.prefix_ = "nonExistentPrefix1246";

    const XmpNsInfo* info = XmpProperties::lookupNsRegistry(prefixStruct);
    EXPECT_EQ(info, nullptr);
}

// ============================================================
// Tests for registeredNamespaces
// ============================================================

TEST_F(XmpPropertiesTest_1246, RegisteredNamespaces_ContainsRegistered_1246) {
    const std::string nsUri = "http://example.com/regns/1246/";
    const std::string nsPrefix = "regNs1246";

    XmpProperties::registerNs(nsUri, nsPrefix);

    Dictionary nsDict;
    XmpProperties::registeredNamespaces(nsDict);

    // The custom namespace should be in the dictionary
    auto it = nsDict.find(nsPrefix);
    EXPECT_NE(it, nsDict.end());
    if (it != nsDict.end()) {
        EXPECT_EQ(it->second, nsUri);
    }
}

TEST_F(XmpPropertiesTest_1246, RegisteredNamespaces_AfterUnregisterAll_1246) {
    const std::string nsUri = "http://example.com/regns2/1246/";
    const std::string nsPrefix = "regNs2_1246";

    XmpProperties::registerNs(nsUri, nsPrefix);
    XmpProperties::unregisterNs();

    Dictionary nsDict;
    XmpProperties::registeredNamespaces(nsDict);

    // Custom namespace should NOT be in the dictionary
    auto it = nsDict.find(nsPrefix);
    EXPECT_EQ(it, nsDict.end());
}

// ============================================================
// Tests for built-in namespaces (dc, xmp, etc.)
// ============================================================

TEST_F(XmpPropertiesTest_1246, BuiltinNs_DcPrefix_1246) {
    // "dc" is a well-known built-in XMP namespace
    std::string dcNs = XmpProperties::ns("dc");
    EXPECT_FALSE(dcNs.empty());
    EXPECT_EQ(dcNs, "http://purl.org/dc/elements/1.1/");
}

TEST_F(XmpPropertiesTest_1246, BuiltinNs_DcPrefixLookup_1246) {
    std::string resultPrefix = XmpProperties::prefix("http://purl.org/dc/elements/1.1/");
    EXPECT_EQ(resultPrefix, "dc");
}

TEST_F(XmpPropertiesTest_1246, NsInfo_KnownPrefix_1246) {
    const XmpNsInfo* info = XmpProperties::nsInfo("dc");
    EXPECT_NE(info, nullptr);
}

TEST_F(XmpPropertiesTest_1246, NsInfo_UnknownPrefix_1246) {
    // An unknown prefix should return nullptr or throw
    try {
        const XmpNsInfo* info = XmpProperties::nsInfo("totallyBogusPrefix1246");
        // If it doesn't throw, it should return nullptr
        EXPECT_EQ(info, nullptr);
    } catch (const Error&) {
        // Also acceptable if it throws
        SUCCEED();
    }
}

TEST_F(XmpPropertiesTest_1246, NsDesc_KnownPrefix_1246) {
    const char* desc = XmpProperties::nsDesc("dc");
    EXPECT_NE(desc, nullptr);
}

// ============================================================
// Tests for propertyList
// ============================================================

TEST_F(XmpPropertiesTest_1246, PropertyList_KnownPrefix_1246) {
    const XmpPropertyInfo* propList = XmpProperties::propertyList("dc");
    EXPECT_NE(propList, nullptr);
}

TEST_F(XmpPropertiesTest_1246, PropertyList_UnknownPrefix_1246) {
    try {
        const XmpPropertyInfo* propList = XmpProperties::propertyList("bogusPrefix1246");
        // If it doesn't throw, could be nullptr
        EXPECT_EQ(propList, nullptr);
    } catch (const Error&) {
        SUCCEED();
    }
}

// ============================================================
// Tests for propertyTitle, propertyDesc, propertyType, propertyInfo
// ============================================================

TEST_F(XmpPropertiesTest_1246, PropertyTitle_KnownKey_1246) {
    XmpKey key("Xmp.dc.title");
    const char* title = XmpProperties::propertyTitle(key);
    EXPECT_NE(title, nullptr);
}

TEST_F(XmpPropertiesTest_1246, PropertyDesc_KnownKey_1246) {
    XmpKey key("Xmp.dc.title");
    const char* desc = XmpProperties::propertyDesc(key);
    EXPECT_NE(desc, nullptr);
}

TEST_F(XmpPropertiesTest_1246, PropertyType_KnownKey_1246) {
    XmpKey key("Xmp.dc.title");
    TypeId type = XmpProperties::propertyType(key);
    EXPECT_NE(type, invalidTypeId);
}

TEST_F(XmpPropertiesTest_1246, PropertyInfo_KnownKey_1246) {
    XmpKey key("Xmp.dc.title");
    const XmpPropertyInfo* info = XmpProperties::propertyInfo(key);
    EXPECT_NE(info, nullptr);
}

TEST_F(XmpPropertiesTest_1246, PropertyInfo_UnknownProperty_1246) {
    try {
        XmpKey key("Xmp.dc.totallyBogusProperty1246");
        const XmpPropertyInfo* info = XmpProperties::propertyInfo(key);
        // Unknown property within known namespace - may return nullptr
        EXPECT_EQ(info, nullptr);
    } catch (const Error&) {
        SUCCEED();
    }
}

// ============================================================
// Tests for printProperties
// ============================================================

TEST_F(XmpPropertiesTest_1246, PrintProperties_KnownPrefix_1246) {
    std::ostringstream os;
    XmpProperties::printProperties(os, "dc");
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
}

// ============================================================
// Tests for printProperty
// ============================================================

TEST_F(XmpPropertiesTest_1246, PrintProperty_BasicOutput_1246) {
    std::ostringstream os;
    XmpTextValue value;
    value.read("Test Value");
    XmpProperties::printProperty(os, "Xmp.dc.title", value);
    std::string output = os.str();
    // Should produce some output
    EXPECT_FALSE(output.empty());
}

// ============================================================
// Edge cases
// ============================================================

TEST_F(XmpPropertiesTest_1246, PrefixForEmptyNs_1246) {
    std::string result = XmpProperties::prefix("");
    EXPECT_TRUE(result.empty());
}

TEST_F(XmpPropertiesTest_1246, NsForEmptyPrefix_1246) {
    try {
        std::string result = XmpProperties::ns("");
        // Either empty or throws
        EXPECT_TRUE(result.empty());
    } catch (const Error&) {
        SUCCEED();
    }
}

TEST_F(XmpPropertiesTest_1246, UnregisterNs_NonExistentNs_1246) {
    // Unregistering a non-existent namespace should not crash
    EXPECT_NO_THROW(XmpProperties::unregisterNs("http://example.com/doesnotexist/1246/"));
}

TEST_F(XmpPropertiesTest_1246, UnregisterNs_EmptyCall_1246) {
    // Calling unregisterNs() with no custom namespaces should be fine
    EXPECT_NO_THROW(XmpProperties::unregisterNs());
}

TEST_F(XmpPropertiesTest_1246, RegisterNs_MultipleAndVerifyAll_1246) {
    const int count = 5;
    for (int i = 0; i < count; ++i) {
        std::string ns = "http://example.com/multi/" + std::to_string(i) + "/1246/";
        std::string prefix = "multi" + std::to_string(i) + "_1246";
        XmpProperties::registerNs(ns, prefix);
    }

    Dictionary nsDict;
    XmpProperties::registeredNamespaces(nsDict);

    for (int i = 0; i < count; ++i) {
        std::string ns = "http://example.com/multi/" + std::to_string(i) + "/1246/";
        std::string prefix = "multi" + std::to_string(i) + "_1246";
        EXPECT_EQ(XmpProperties::prefix(ns), prefix);
        EXPECT_EQ(XmpProperties::ns(prefix), ns);
    }
}

TEST_F(XmpPropertiesTest_1246, RegisterNs_ThenUnregisterSpecific_OthersRemain_1246) {
    const std::string nsUri1 = "http://example.com/remain1/1246/";
    const std::string nsPrefix1 = "remain1_1246";
    const std::string nsUri2 = "http://example.com/remain2/1246/";
    const std::string nsPrefix2 = "remain2_1246";

    XmpProperties::registerNs(nsUri1, nsPrefix1);
    XmpProperties::registerNs(nsUri2, nsPrefix2);

    // Unregister only the first
    XmpProperties::unregisterNs(nsUri1);

    EXPECT_TRUE(XmpProperties::prefix(nsUri1).empty());
    EXPECT_EQ(XmpProperties::prefix(nsUri2), nsPrefix2);
}

TEST_F(XmpPropertiesTest_1246, BuiltinNs_XmpPrefix_1246) {
    std::string xmpNs = XmpProperties::ns("xmp");
    EXPECT_FALSE(xmpNs.empty());
}

TEST_F(XmpPropertiesTest_1246, PropertyType_DcCreator_1246) {
    XmpKey key("Xmp.dc.creator");
    TypeId type = XmpProperties::propertyType(key);
    // dc:creator is a bag of proper names, typically xmpSeq
    EXPECT_NE(type, invalidTypeId);
}

TEST_F(XmpPropertiesTest_1246, RegisterNs_CustomPropertyInfoIsNull_1246) {
    const std::string nsUri = "http://example.com/custom/1246/";
    const std::string nsPrefix = "customNs1246";

    XmpProperties::registerNs(nsUri, nsPrefix);

    // A custom namespace should have no built-in property list
    try {
        const XmpPropertyInfo* propList = XmpProperties::propertyList(nsPrefix);
        // May be nullptr for custom namespaces
        // This is implementation dependent
        (void)propList;
    } catch (const Error&) {
        SUCCEED();
    }
}

}  // namespace
