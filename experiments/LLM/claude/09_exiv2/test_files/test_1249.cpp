#include <gtest/gtest.h>
#include <string>
#include <sstream>
#include <map>

#include "exiv2/properties.hpp"
#include "exiv2/value.hpp"

using namespace Exiv2;

class XmpPropertiesTest_1249 : public ::testing::Test {
protected:
    void SetUp() override {
        // Unregister any custom namespaces to start clean
        XmpProperties::unregisterNs();
    }

    void TearDown() override {
        XmpProperties::unregisterNs();
    }
};

// Test propertyTitle with a known standard XMP key
TEST_F(XmpPropertiesTest_1249, PropertyTitleKnownKey_1249) {
    XmpKey key("Xmp.dc.title");
    const char* title = XmpProperties::propertyTitle(key);
    // dc.title is a well-known Dublin Core property; should have a title
    ASSERT_NE(title, nullptr);
    EXPECT_TRUE(std::string(title).length() > 0);
}

// Test propertyTitle with a known dc.description key
TEST_F(XmpPropertiesTest_1249, PropertyTitleDcDescription_1249) {
    XmpKey key("Xmp.dc.description");
    const char* title = XmpProperties::propertyTitle(key);
    ASSERT_NE(title, nullptr);
    EXPECT_TRUE(std::string(title).length() > 0);
}

// Test propertyTitle with an unknown property in a known namespace
TEST_F(XmpPropertiesTest_1249, PropertyTitleUnknownProperty_1249) {
    XmpKey key("Xmp.dc.nonExistentProperty12345");
    const char* title = XmpProperties::propertyTitle(key);
    // Unknown property should return nullptr
    EXPECT_EQ(title, nullptr);
}

// Test propertyDesc with a known key
TEST_F(XmpPropertiesTest_1249, PropertyDescKnownKey_1249) {
    XmpKey key("Xmp.dc.title");
    const char* desc = XmpProperties::propertyDesc(key);
    ASSERT_NE(desc, nullptr);
    EXPECT_TRUE(std::string(desc).length() > 0);
}

// Test propertyDesc with an unknown property
TEST_F(XmpPropertiesTest_1249, PropertyDescUnknownProperty_1249) {
    XmpKey key("Xmp.dc.nonExistentProp999");
    const char* desc = XmpProperties::propertyDesc(key);
    EXPECT_EQ(desc, nullptr);
}

// Test propertyType with a known key
TEST_F(XmpPropertiesTest_1249, PropertyTypeKnownKey_1249) {
    XmpKey key("Xmp.dc.title");
    TypeId type = XmpProperties::propertyType(key);
    // dc.title should have a valid type
    EXPECT_NE(type, invalidTypeId);
}

// Test propertyInfo with a known key returns non-null
TEST_F(XmpPropertiesTest_1249, PropertyInfoKnownKey_1249) {
    XmpKey key("Xmp.dc.creator");
    const XmpPropertyInfo* info = XmpProperties::propertyInfo(key);
    ASSERT_NE(info, nullptr);
}

// Test propertyInfo with unknown property returns null
TEST_F(XmpPropertiesTest_1249, PropertyInfoUnknownProperty_1249) {
    XmpKey key("Xmp.dc.totallyFakeProperty");
    const XmpPropertyInfo* info = XmpProperties::propertyInfo(key);
    EXPECT_EQ(info, nullptr);
}

// Test ns() with known prefix "dc"
TEST_F(XmpPropertiesTest_1249, NsKnownPrefix_1249) {
    std::string ns = XmpProperties::ns("dc");
    EXPECT_FALSE(ns.empty());
    EXPECT_NE(ns.find("dc"), std::string::npos);
}

// Test prefix() with known dc namespace
TEST_F(XmpPropertiesTest_1249, PrefixKnownNs_1249) {
    std::string ns = XmpProperties::ns("dc");
    ASSERT_FALSE(ns.empty());
    std::string prefix = XmpProperties::prefix(ns);
    EXPECT_EQ(prefix, "dc");
}

// Test nsDesc with known prefix
TEST_F(XmpPropertiesTest_1249, NsDescKnownPrefix_1249) {
    const char* desc = XmpProperties::nsDesc("dc");
    ASSERT_NE(desc, nullptr);
    EXPECT_TRUE(std::string(desc).length() > 0);
}

// Test propertyList with known prefix
TEST_F(XmpPropertiesTest_1249, PropertyListKnownPrefix_1249) {
    const XmpPropertyInfo* list = XmpProperties::propertyList("dc");
    ASSERT_NE(list, nullptr);
}

// Test nsInfo with known prefix
TEST_F(XmpPropertiesTest_1249, NsInfoKnownPrefix_1249) {
    const XmpNsInfo* info = XmpProperties::nsInfo("dc");
    ASSERT_NE(info, nullptr);
}

// Test registerNs and then retrieve it
TEST_F(XmpPropertiesTest_1249, RegisterAndRetrieveNs_1249) {
    const std::string testNs = "http://test.example.com/test1249/";
    const std::string testPrefix = "test1249";

    XmpProperties::registerNs(testNs, testPrefix);

    std::string retrievedNs = XmpProperties::ns(testPrefix);
    EXPECT_EQ(retrievedNs, testNs);

    std::string retrievedPrefix = XmpProperties::prefix(testNs);
    EXPECT_EQ(retrievedPrefix, testPrefix);

    // Clean up
    XmpProperties::unregisterNs(testNs);
}

// Test unregisterNs for a specific namespace
TEST_F(XmpPropertiesTest_1249, UnregisterSpecificNs_1249) {
    const std::string testNs = "http://test.example.com/unregister1249/";
    const std::string testPrefix = "unreg1249";

    XmpProperties::registerNs(testNs, testPrefix);
    std::string retrievedNs = XmpProperties::ns(testPrefix);
    EXPECT_EQ(retrievedNs, testNs);

    XmpProperties::unregisterNs(testNs);

    // After unregistering, the custom namespace should no longer be found
    // (the prefix lookup may throw or return empty)
    std::string afterUnregister = XmpProperties::prefix(testNs);
    EXPECT_TRUE(afterUnregister.empty());
}

// Test unregisterNs (all custom namespaces)
TEST_F(XmpPropertiesTest_1249, UnregisterAllCustomNs_1249) {
    const std::string testNs1 = "http://test.example.com/all1_1249/";
    const std::string testPrefix1 = "all1x1249";
    const std::string testNs2 = "http://test.example.com/all2_1249/";
    const std::string testPrefix2 = "all2x1249";

    XmpProperties::registerNs(testNs1, testPrefix1);
    XmpProperties::registerNs(testNs2, testPrefix2);

    XmpProperties::unregisterNs();

    // After unregistering all, custom namespaces should be gone
    std::string p1 = XmpProperties::prefix(testNs1);
    std::string p2 = XmpProperties::prefix(testNs2);
    EXPECT_TRUE(p1.empty());
    EXPECT_TRUE(p2.empty());

    // But standard namespaces like dc should still work
    std::string dcNs = XmpProperties::ns("dc");
    EXPECT_FALSE(dcNs.empty());
}

// Test registeredNamespaces returns a non-empty dictionary
TEST_F(XmpPropertiesTest_1249, RegisteredNamespacesNotEmpty_1249) {
    Exiv2::Dictionary nsDict;
    XmpProperties::registeredNamespaces(nsDict);
    // There should be at least the standard namespaces
    EXPECT_FALSE(nsDict.empty());
}

// Test registeredNamespaces includes custom registered namespace
TEST_F(XmpPropertiesTest_1249, RegisteredNamespacesIncludesCustom_1249) {
    const std::string testNs = "http://test.example.com/regns1249/";
    const std::string testPrefix = "regns1249";

    XmpProperties::registerNs(testNs, testPrefix);

    Exiv2::Dictionary nsDict;
    XmpProperties::registeredNamespaces(nsDict);

    // Check that our custom namespace is present
    bool found = false;
    for (const auto& entry : nsDict) {
        if (entry.first == testNs || entry.second == testPrefix) {
            found = true;
            break;
        }
    }
    EXPECT_TRUE(found);

    XmpProperties::unregisterNs(testNs);
}

// Test printProperties doesn't crash for known prefix
TEST_F(XmpPropertiesTest_1249, PrintPropertiesKnownPrefix_1249) {
    std::ostringstream os;
    EXPECT_NO_THROW(XmpProperties::printProperties(os, "dc"));
    EXPECT_FALSE(os.str().empty());
}

// Test XmpKey construction from string
TEST_F(XmpPropertiesTest_1249, XmpKeyFromString_1249) {
    XmpKey key("Xmp.dc.title");
    EXPECT_EQ(key.familyName(), std::string("Xmp"));
    EXPECT_EQ(key.groupName(), std::string("dc"));
    EXPECT_EQ(key.tagName(), std::string("title"));
    EXPECT_EQ(key.key(), std::string("Xmp.dc.title"));
}

// Test XmpKey construction from prefix and property
TEST_F(XmpPropertiesTest_1249, XmpKeyFromPrefixAndProperty_1249) {
    XmpKey key("dc", "creator");
    EXPECT_EQ(key.familyName(), std::string("Xmp"));
    EXPECT_EQ(key.groupName(), std::string("dc"));
    EXPECT_EQ(key.tagName(), std::string("creator"));
}

// Test XmpKey copy constructor
TEST_F(XmpPropertiesTest_1249, XmpKeyCopyConstructor_1249) {
    XmpKey original("Xmp.dc.title");
    XmpKey copy(original);
    EXPECT_EQ(copy.key(), original.key());
    EXPECT_EQ(copy.groupName(), original.groupName());
    EXPECT_EQ(copy.tagName(), original.tagName());
}

// Test XmpKey assignment operator
TEST_F(XmpPropertiesTest_1249, XmpKeyAssignment_1249) {
    XmpKey key1("Xmp.dc.title");
    XmpKey key2("Xmp.dc.creator");
    key2 = key1;
    EXPECT_EQ(key2.key(), key1.key());
}

// Test XmpKey clone
TEST_F(XmpPropertiesTest_1249, XmpKeyClone_1249) {
    XmpKey key("Xmp.dc.title");
    auto cloned = key.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->key(), key.key());
}

// Test XmpKey ns() method
TEST_F(XmpPropertiesTest_1249, XmpKeyNs_1249) {
    XmpKey key("Xmp.dc.title");
    std::string ns = key.ns();
    EXPECT_FALSE(ns.empty());
}

// Test XmpKey tagLabel for known property
TEST_F(XmpPropertiesTest_1249, XmpKeyTagLabel_1249) {
    XmpKey key("Xmp.dc.title");
    std::string label = key.tagLabel();
    EXPECT_FALSE(label.empty());
}

// Test XmpKey tagDesc for known property
TEST_F(XmpPropertiesTest_1249, XmpKeyTagDesc_1249) {
    XmpKey key("Xmp.dc.title");
    std::string desc = key.tagDesc();
    EXPECT_FALSE(desc.empty());
}

// Test propertyTitle with xmp namespace
TEST_F(XmpPropertiesTest_1249, PropertyTitleXmpNamespace_1249) {
    XmpKey key("Xmp.xmp.CreateDate");
    const char* title = XmpProperties::propertyTitle(key);
    ASSERT_NE(title, nullptr);
    EXPECT_TRUE(std::string(title).length() > 0);
}

// Test propertyType with xmp namespace
TEST_F(XmpPropertiesTest_1249, PropertyTypeXmpCreateDate_1249) {
    XmpKey key("Xmp.xmp.CreateDate");
    TypeId type = XmpProperties::propertyType(key);
    EXPECT_NE(type, invalidTypeId);
}

// Test ns with unknown prefix throws or returns empty
TEST_F(XmpPropertiesTest_1249, NsUnknownPrefix_1249) {
    try {
        std::string ns = XmpProperties::ns("completelyUnknownPrefix12345");
        // If it doesn't throw, we expect empty
        EXPECT_TRUE(ns.empty());
    } catch (const std::exception&) {
        // Throwing is also acceptable behavior for unknown prefix
        SUCCEED();
    }
}

// Test prefix with unknown namespace
TEST_F(XmpPropertiesTest_1249, PrefixUnknownNs_1249) {
    std::string prefix = XmpProperties::prefix("http://completely.unknown.namespace/");
    EXPECT_TRUE(prefix.empty());
}

// Test lookupNsRegistry with a registered custom namespace
TEST_F(XmpPropertiesTest_1249, LookupNsRegistryCustom_1249) {
    const std::string testNs = "http://test.example.com/lookup1249/";
    const std::string testPrefix = "lookup1249";

    XmpProperties::registerNs(testNs, testPrefix);

    XmpNsInfo::Prefix pfx;
    pfx.i_ = testPrefix.c_str();
    const XmpNsInfo* info = XmpProperties::lookupNsRegistry(pfx);
    EXPECT_NE(info, nullptr);

    XmpProperties::unregisterNs(testNs);
}

// Test re-registering the same namespace with a different prefix
TEST_F(XmpPropertiesTest_1249, ReRegisterSameNs_1249) {
    const std::string testNs = "http://test.example.com/rereg1249/";
    const std::string testPrefix1 = "rereg1249a";
    const std::string testPrefix2 = "rereg1249b";

    XmpProperties::registerNs(testNs, testPrefix1);
    std::string p1 = XmpProperties::prefix(testNs);

    XmpProperties::registerNs(testNs, testPrefix2);
    std::string p2 = XmpProperties::prefix(testNs);

    // The latest registration should take effect
    EXPECT_EQ(p2, testPrefix2);

    XmpProperties::unregisterNs(testNs);
}

// Test multiple different XMP namespaces
TEST_F(XmpPropertiesTest_1249, MultipleNamespaces_1249) {
    // Test tiff namespace
    XmpKey tiffKey("Xmp.tiff.ImageWidth");
    const XmpPropertyInfo* tiffInfo = XmpProperties::propertyInfo(tiffKey);
    EXPECT_NE(tiffInfo, nullptr);

    // Test exif namespace
    XmpKey exifKey("Xmp.exif.ExposureTime");
    const XmpPropertyInfo* exifInfo = XmpProperties::propertyInfo(exifKey);
    EXPECT_NE(exifInfo, nullptr);
}

// Test printProperty doesn't crash
TEST_F(XmpPropertiesTest_1249, PrintPropertyDoesNotCrash_1249) {
    std::ostringstream os;
    XmpTextValue value("Test value");
    EXPECT_NO_THROW(XmpProperties::printProperty(os, "Xmp.dc.title", value));
}
