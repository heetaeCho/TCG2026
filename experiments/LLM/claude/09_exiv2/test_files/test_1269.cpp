#include <gtest/gtest.h>
#include <exiv2/properties.hpp>
#include <exiv2/error.hpp>
#include <exiv2/xmp_exiv2.hpp>
#include <sstream>

namespace {

class XmpKeyTest_1269 : public ::testing::Test {
protected:
    void SetUp() override {
        // Ensure we have a clean state for namespace registrations
    }

    void TearDown() override {
        // Clean up any registered namespaces
        Exiv2::XmpProperties::unregisterNs();
    }
};

class XmpPropertiesTest_1269 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
        Exiv2::XmpProperties::unregisterNs();
    }
};

// ============================================================
// XmpKey construction and decomposition tests
// ============================================================

TEST_F(XmpKeyTest_1269, ValidKeyConstruction_1269) {
    // "dc" is a well-known XMP prefix (Dublin Core)
    ASSERT_NO_THROW(Exiv2::XmpKey key("Xmp.dc.title"));
}

TEST_F(XmpKeyTest_1269, ValidKeyReturnsCorrectFamilyName_1269) {
    Exiv2::XmpKey key("Xmp.dc.title");
    EXPECT_STREQ(key.familyName(), "Xmp");
}

TEST_F(XmpKeyTest_1269, ValidKeyReturnsCorrectGroupName_1269) {
    Exiv2::XmpKey key("Xmp.dc.title");
    EXPECT_EQ(key.groupName(), "dc");
}

TEST_F(XmpKeyTest_1269, ValidKeyReturnsCorrectTagName_1269) {
    Exiv2::XmpKey key("Xmp.dc.title");
    EXPECT_EQ(key.tagName(), "title");
}

TEST_F(XmpKeyTest_1269, ValidKeyReturnsCorrectKey_1269) {
    Exiv2::XmpKey key("Xmp.dc.title");
    EXPECT_EQ(key.key(), "Xmp.dc.title");
}

TEST_F(XmpKeyTest_1269, KeyNotStartingWithXmpThrows_1269) {
    EXPECT_THROW(Exiv2::XmpKey key("Iptc.dc.title"), Exiv2::Error);
}

TEST_F(XmpKeyTest_1269, KeyNotStartingWithXmpThrows2_1269) {
    EXPECT_THROW(Exiv2::XmpKey key("Exif.dc.title"), Exiv2::Error);
}

TEST_F(XmpKeyTest_1269, KeyWithNoSecondDotThrows_1269) {
    EXPECT_THROW(Exiv2::XmpKey key("Xmp.dconly"), Exiv2::Error);
}

TEST_F(XmpKeyTest_1269, KeyWithEmptyPrefixThrows_1269) {
    EXPECT_THROW(Exiv2::XmpKey key("Xmp..property"), Exiv2::Error);
}

TEST_F(XmpKeyTest_1269, KeyWithEmptyPropertyThrows_1269) {
    EXPECT_THROW(Exiv2::XmpKey key("Xmp.dc."), Exiv2::Error);
}

TEST_F(XmpKeyTest_1269, KeyWithUnknownPrefixThrows_1269) {
    EXPECT_THROW(Exiv2::XmpKey key("Xmp.unknownprefix12345.property"), Exiv2::Error);
}

TEST_F(XmpKeyTest_1269, EmptyKeyThrows_1269) {
    EXPECT_THROW(Exiv2::XmpKey key(""), Exiv2::Error);
}

TEST_F(XmpKeyTest_1269, KeyWithOnlyFamilyNameThrows_1269) {
    EXPECT_THROW(Exiv2::XmpKey key("Xmp"), Exiv2::Error);
}

TEST_F(XmpKeyTest_1269, KeyWithOnlyFamilyAndDotThrows_1269) {
    EXPECT_THROW(Exiv2::XmpKey key("Xmp."), Exiv2::Error);
}

TEST_F(XmpKeyTest_1269, CopyConstructor_1269) {
    Exiv2::XmpKey key1("Xmp.dc.title");
    Exiv2::XmpKey key2(key1);
    EXPECT_EQ(key1.key(), key2.key());
    EXPECT_EQ(key1.groupName(), key2.groupName());
    EXPECT_EQ(key1.tagName(), key2.tagName());
}

TEST_F(XmpKeyTest_1269, CloneReturnsValidKey_1269) {
    Exiv2::XmpKey key("Xmp.dc.title");
    auto cloned = key.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->key(), key.key());
}

TEST_F(XmpKeyTest_1269, ConstructFromPrefixAndProperty_1269) {
    ASSERT_NO_THROW(Exiv2::XmpKey key("dc", "title"));
    Exiv2::XmpKey key("dc", "title");
    EXPECT_EQ(key.key(), "Xmp.dc.title");
    EXPECT_EQ(key.groupName(), "dc");
    EXPECT_EQ(key.tagName(), "title");
}

TEST_F(XmpKeyTest_1269, MultipleKnownPrefixes_1269) {
    // Test several well-known XMP prefixes
    ASSERT_NO_THROW(Exiv2::XmpKey("Xmp.dc.creator"));
    ASSERT_NO_THROW(Exiv2::XmpKey("Xmp.xmp.CreateDate"));
    ASSERT_NO_THROW(Exiv2::XmpKey("Xmp.tiff.ImageWidth"));
    ASSERT_NO_THROW(Exiv2::XmpKey("Xmp.exif.ExposureTime"));
}

TEST_F(XmpKeyTest_1269, PropertyWithDotsInName_1269) {
    // The property part can contain dots (everything after prefix.)
    // This depends on the implementation behavior
    ASSERT_NO_THROW(Exiv2::XmpKey("Xmp.dc.subject.item"));
}

// ============================================================
// XmpProperties static method tests
// ============================================================

TEST_F(XmpPropertiesTest_1269, NsForKnownPrefix_1269) {
    std::string ns = Exiv2::XmpProperties::ns("dc");
    EXPECT_FALSE(ns.empty());
    EXPECT_EQ(ns, "http://purl.org/dc/elements/1.1/");
}

TEST_F(XmpPropertiesTest_1269, NsForUnknownPrefixReturnsEmpty_1269) {
    std::string ns = Exiv2::XmpProperties::ns("completelyunknownprefix");
    EXPECT_TRUE(ns.empty());
}

TEST_F(XmpPropertiesTest_1269, PrefixForKnownNs_1269) {
    std::string prefix = Exiv2::XmpProperties::prefix("http://purl.org/dc/elements/1.1/");
    EXPECT_EQ(prefix, "dc");
}

TEST_F(XmpPropertiesTest_1269, PrefixForUnknownNsReturnsEmpty_1269) {
    std::string prefix = Exiv2::XmpProperties::prefix("http://unknown.example.com/ns/");
    EXPECT_TRUE(prefix.empty());
}

TEST_F(XmpPropertiesTest_1269, RegisterAndLookupCustomNs_1269) {
    Exiv2::XmpProperties::registerNs("http://example.com/test/", "mytest");
    std::string ns = Exiv2::XmpProperties::ns("mytest");
    EXPECT_EQ(ns, "http://example.com/test/");
    std::string prefix = Exiv2::XmpProperties::prefix("http://example.com/test/");
    EXPECT_EQ(prefix, "mytest");
}

TEST_F(XmpPropertiesTest_1269, UnregisterCustomNs_1269) {
    Exiv2::XmpProperties::registerNs("http://example.com/unreg/", "unreg");
    EXPECT_FALSE(Exiv2::XmpProperties::ns("unreg").empty());
    Exiv2::XmpProperties::unregisterNs("http://example.com/unreg/");
    // After unregistering, the namespace should no longer resolve
    // (unless it's a built-in one)
    std::string ns = Exiv2::XmpProperties::ns("unreg");
    EXPECT_TRUE(ns.empty());
}

TEST_F(XmpPropertiesTest_1269, UnregisterAllCustomNs_1269) {
    Exiv2::XmpProperties::registerNs("http://example.com/a/", "nsa");
    Exiv2::XmpProperties::registerNs("http://example.com/b/", "nsb");
    Exiv2::XmpProperties::unregisterNs();
    EXPECT_TRUE(Exiv2::XmpProperties::ns("nsa").empty());
    EXPECT_TRUE(Exiv2::XmpProperties::ns("nsb").empty());
}

TEST_F(XmpPropertiesTest_1269, BuiltInNsStillAvailableAfterUnregisterAll_1269) {
    Exiv2::XmpProperties::unregisterNs();
    // dc is a built-in namespace
    EXPECT_FALSE(Exiv2::XmpProperties::ns("dc").empty());
}

TEST_F(XmpPropertiesTest_1269, PropertyInfoForKnownKey_1269) {
    Exiv2::XmpKey key("Xmp.dc.title");
    const Exiv2::XmpPropertyInfo* info = Exiv2::XmpProperties::propertyInfo(key);
    // title is a well-known property of dc, so info should not be null
    EXPECT_NE(info, nullptr);
}

TEST_F(XmpPropertiesTest_1269, PropertyInfoForUnknownPropertyReturnsNull_1269) {
    Exiv2::XmpKey key("Xmp.dc.completelyUnknownProperty12345");
    const Exiv2::XmpPropertyInfo* info = Exiv2::XmpProperties::propertyInfo(key);
    EXPECT_EQ(info, nullptr);
}

TEST_F(XmpPropertiesTest_1269, PropertyTypeForKnownKey_1269) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::TypeId type = Exiv2::XmpProperties::propertyType(key);
    // title is xmpText type (langAlt), should return a valid type
    EXPECT_NE(type, Exiv2::invalidTypeId);
}

TEST_F(XmpPropertiesTest_1269, PropertyTitleForKnownKey_1269) {
    Exiv2::XmpKey key("Xmp.dc.title");
    const char* title = Exiv2::XmpProperties::propertyTitle(key);
    // title property should have a title
    if (title) {
        EXPECT_GT(strlen(title), 0u);
    }
}

TEST_F(XmpPropertiesTest_1269, PropertyDescForKnownKey_1269) {
    Exiv2::XmpKey key("Xmp.dc.title");
    const char* desc = Exiv2::XmpProperties::propertyDesc(key);
    // dc.title should have a description
    if (desc) {
        EXPECT_GT(strlen(desc), 0u);
    }
}

TEST_F(XmpPropertiesTest_1269, NsDescForKnownPrefix_1269) {
    const char* desc = Exiv2::XmpProperties::nsDesc("dc");
    ASSERT_NE(desc, nullptr);
    EXPECT_GT(strlen(desc), 0u);
}

TEST_F(XmpPropertiesTest_1269, PropertyListForKnownPrefix_1269) {
    const Exiv2::XmpPropertyInfo* list = Exiv2::XmpProperties::propertyList("dc");
    EXPECT_NE(list, nullptr);
}

TEST_F(XmpPropertiesTest_1269, NsInfoForKnownPrefix_1269) {
    const Exiv2::XmpNsInfo* info = Exiv2::XmpProperties::nsInfo("dc");
    EXPECT_NE(info, nullptr);
}

TEST_F(XmpPropertiesTest_1269, PrintPropertiesDoesNotThrow_1269) {
    std::ostringstream os;
    EXPECT_NO_THROW(Exiv2::XmpProperties::printProperties(os, "dc"));
    EXPECT_FALSE(os.str().empty());
}

TEST_F(XmpPropertiesTest_1269, RegisteredNamespacesContainsBuiltIn_1269) {
    Exiv2::Dictionary nsDict;
    Exiv2::XmpProperties::registeredNamespaces(nsDict);
    // Should contain at least the dc namespace
    bool foundDc = false;
    for (auto& [key, value] : nsDict) {
        if (value == "dc" || key == "http://purl.org/dc/elements/1.1/") {
            foundDc = true;
            break;
        }
    }
    EXPECT_TRUE(foundDc);
}

TEST_F(XmpPropertiesTest_1269, RegisteredNamespacesContainsCustom_1269) {
    Exiv2::XmpProperties::registerNs("http://example.com/custom/", "custom");
    Exiv2::Dictionary nsDict;
    Exiv2::XmpProperties::registeredNamespaces(nsDict);
    bool found = false;
    for (auto& [key, value] : nsDict) {
        if (key == "http://example.com/custom/" && value == "custom") {
            found = true;
            break;
        }
    }
    EXPECT_TRUE(found);
}

TEST_F(XmpPropertiesTest_1269, RegisterNsThenConstructKey_1269) {
    Exiv2::XmpProperties::registerNs("http://example.com/keytest/", "keytest");
    ASSERT_NO_THROW(Exiv2::XmpKey key("Xmp.keytest.something"));
    Exiv2::XmpKey key("Xmp.keytest.something");
    EXPECT_EQ(key.groupName(), "keytest");
    EXPECT_EQ(key.tagName(), "something");
}

TEST_F(XmpPropertiesTest_1269, LookupNsRegistryForRegisteredPrefix_1269) {
    Exiv2::XmpProperties::registerNs("http://example.com/lookup/", "lookup");
    Exiv2::XmpNsInfo::Prefix prefix("lookup");
    const Exiv2::XmpNsInfo* info = Exiv2::XmpProperties::lookupNsRegistry(prefix);
    EXPECT_NE(info, nullptr);
}

TEST_F(XmpPropertiesTest_1269, LookupNsRegistryForUnknownPrefixReturnsNull_1269) {
    Exiv2::XmpNsInfo::Prefix prefix("totallyunknownpfx");
    const Exiv2::XmpNsInfo* info = Exiv2::XmpProperties::lookupNsRegistry(prefix);
    EXPECT_EQ(info, nullptr);
}

// ============================================================
// XmpKey with various well-known prefixes
// ============================================================

TEST_F(XmpKeyTest_1269, XmpPrefixKey_1269) {
    Exiv2::XmpKey key("Xmp.xmp.CreateDate");
    EXPECT_EQ(key.groupName(), "xmp");
    EXPECT_EQ(key.tagName(), "CreateDate");
}

TEST_F(XmpKeyTest_1269, TiffPrefixKey_1269) {
    Exiv2::XmpKey key("Xmp.tiff.ImageWidth");
    EXPECT_EQ(key.groupName(), "tiff");
    EXPECT_EQ(key.tagName(), "ImageWidth");
}

TEST_F(XmpKeyTest_1269, ExifPrefixKey_1269) {
    Exiv2::XmpKey key("Xmp.exif.ExposureTime");
    EXPECT_EQ(key.groupName(), "exif");
    EXPECT_EQ(key.tagName(), "ExposureTime");
}

TEST_F(XmpKeyTest_1269, TagReturnsNonNegative_1269) {
    Exiv2::XmpKey key("Xmp.dc.title");
    // tag() should return a valid tag number
    EXPECT_GE(key.tag(), 0u);
}

} // anonymous namespace
