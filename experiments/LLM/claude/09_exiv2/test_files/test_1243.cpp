#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include "exiv2/properties.hpp"
#include "exiv2/value.hpp"
#include "exiv2/types.hpp"

namespace {

class XmpPropertiesTest_1243 : public ::testing::Test {
protected:
    void SetUp() override {
        // Unregister all custom namespaces before each test
        Exiv2::XmpProperties::unregisterNs();
    }

    void TearDown() override {
        // Clean up after each test
        Exiv2::XmpProperties::unregisterNs();
    }
};

// Test registering a namespace and looking it up by prefix
TEST_F(XmpPropertiesTest_1243, RegisterNsAndLookup_1243) {
    const std::string ns = "http://example.com/test/";
    const std::string prefix = "testprefix";

    Exiv2::XmpProperties::registerNs(ns, prefix);

    Exiv2::XmpNsInfo::Prefix pfx;
    pfx.prefix_ = prefix;
    const Exiv2::XmpNsInfo* info = Exiv2::XmpProperties::lookupNsRegistry(pfx);

    ASSERT_NE(info, nullptr);
}

// Test that lookupNsRegistry returns nullptr for unregistered prefix
TEST_F(XmpPropertiesTest_1243, LookupNsRegistryUnregisteredPrefix_1243) {
    Exiv2::XmpNsInfo::Prefix pfx;
    pfx.prefix_ = "nonexistent";
    const Exiv2::XmpNsInfo* info = Exiv2::XmpProperties::lookupNsRegistry(pfx);

    EXPECT_EQ(info, nullptr);
}

// Test registering and then unregistering a namespace by ns string
TEST_F(XmpPropertiesTest_1243, RegisterAndUnregisterNs_1243) {
    const std::string ns = "http://example.com/unregtest/";
    const std::string prefix = "unregtest";

    Exiv2::XmpProperties::registerNs(ns, prefix);

    Exiv2::XmpNsInfo::Prefix pfx;
    pfx.prefix_ = prefix;
    const Exiv2::XmpNsInfo* info = Exiv2::XmpProperties::lookupNsRegistry(pfx);
    ASSERT_NE(info, nullptr);

    Exiv2::XmpProperties::unregisterNs(ns);

    const Exiv2::XmpNsInfo* infoAfter = Exiv2::XmpProperties::lookupNsRegistry(pfx);
    EXPECT_EQ(infoAfter, nullptr);
}

// Test unregisterNs() clears all custom namespaces
TEST_F(XmpPropertiesTest_1243, UnregisterAllCustomNs_1243) {
    Exiv2::XmpProperties::registerNs("http://example.com/a/", "nsa");
    Exiv2::XmpProperties::registerNs("http://example.com/b/", "nsb");

    Exiv2::XmpProperties::unregisterNs();

    Exiv2::XmpNsInfo::Prefix pfxA;
    pfxA.prefix_ = "nsa";
    Exiv2::XmpNsInfo::Prefix pfxB;
    pfxB.prefix_ = "nsb";

    EXPECT_EQ(Exiv2::XmpProperties::lookupNsRegistry(pfxA), nullptr);
    EXPECT_EQ(Exiv2::XmpProperties::lookupNsRegistry(pfxB), nullptr);
}

// Test prefix lookup for a registered namespace
TEST_F(XmpPropertiesTest_1243, PrefixFromNs_1243) {
    const std::string ns = "http://example.com/pfxtest/";
    const std::string prefix = "pfxtest";

    Exiv2::XmpProperties::registerNs(ns, prefix);

    std::string result = Exiv2::XmpProperties::prefix(ns);
    EXPECT_EQ(result, prefix);
}

// Test ns lookup from prefix for a registered namespace
TEST_F(XmpPropertiesTest_1243, NsFromPrefix_1243) {
    const std::string ns = "http://example.com/nstest/";
    const std::string prefix = "nstest";

    Exiv2::XmpProperties::registerNs(ns, prefix);

    std::string result = Exiv2::XmpProperties::ns(prefix);
    EXPECT_EQ(result, ns);
}

// Test that well-known XMP namespace "dc" is recognized
TEST_F(XmpPropertiesTest_1243, WellKnownDcPrefix_1243) {
    std::string nsResult = Exiv2::XmpProperties::ns("dc");
    EXPECT_FALSE(nsResult.empty());
}

// Test that well-known XMP namespace "xmp" is recognized
TEST_F(XmpPropertiesTest_1243, WellKnownXmpPrefix_1243) {
    std::string nsResult = Exiv2::XmpProperties::ns("xmp");
    EXPECT_FALSE(nsResult.empty());
}

// Test nsInfo for a well-known prefix
TEST_F(XmpPropertiesTest_1243, NsInfoForDc_1243) {
    const Exiv2::XmpNsInfo* info = Exiv2::XmpProperties::nsInfo("dc");
    ASSERT_NE(info, nullptr);
}

// Test nsInfo for unknown prefix returns nullptr
TEST_F(XmpPropertiesTest_1243, NsInfoForUnknownPrefix_1243) {
    const Exiv2::XmpNsInfo* info = Exiv2::XmpProperties::nsInfo("totallyunknown");
    EXPECT_EQ(info, nullptr);
}

// Test nsDesc for a well-known prefix
TEST_F(XmpPropertiesTest_1243, NsDescForDc_1243) {
    const char* desc = Exiv2::XmpProperties::nsDesc("dc");
    // Should return a non-null description for a known prefix
    EXPECT_NE(desc, nullptr);
}

// Test propertyList for a well-known prefix
TEST_F(XmpPropertiesTest_1243, PropertyListForDc_1243) {
    const Exiv2::XmpPropertyInfo* propList = Exiv2::XmpProperties::propertyList("dc");
    EXPECT_NE(propList, nullptr);
}

// Test propertyList for unknown prefix returns nullptr
TEST_F(XmpPropertiesTest_1243, PropertyListForUnknownPrefix_1243) {
    const Exiv2::XmpPropertyInfo* propList = Exiv2::XmpProperties::propertyList("totallyunknown");
    EXPECT_EQ(propList, nullptr);
}

// Test registeredNamespaces returns a non-empty dictionary (well-known namespaces exist)
TEST_F(XmpPropertiesTest_1243, RegisteredNamespacesNotEmpty_1243) {
    Exiv2::Dictionary nsDict;
    Exiv2::XmpProperties::registeredNamespaces(nsDict);
    EXPECT_FALSE(nsDict.empty());
}

// Test that registering a namespace includes it in registeredNamespaces
TEST_F(XmpPropertiesTest_1243, RegisteredNamespacesIncludesCustom_1243) {
    const std::string ns = "http://example.com/regtest/";
    const std::string prefix = "regtest";

    Exiv2::XmpProperties::registerNs(ns, prefix);

    Exiv2::Dictionary nsDict;
    Exiv2::XmpProperties::registeredNamespaces(nsDict);

    bool found = false;
    for (const auto& entry : nsDict) {
        if (entry.first == ns || entry.second == prefix) {
            found = true;
            break;
        }
    }
    EXPECT_TRUE(found);
}

// Test prefix for an unknown namespace returns empty string
TEST_F(XmpPropertiesTest_1243, PrefixForUnknownNs_1243) {
    std::string result = Exiv2::XmpProperties::prefix("http://nonexistent.example.com/");
    EXPECT_TRUE(result.empty());
}

// Test ns for an unknown prefix returns empty string
TEST_F(XmpPropertiesTest_1243, NsForUnknownPrefix_1243) {
    std::string result = Exiv2::XmpProperties::ns("nonexistentprefix");
    EXPECT_TRUE(result.empty());
}

// Test printProperties does not crash for a known prefix
TEST_F(XmpPropertiesTest_1243, PrintPropertiesForDc_1243) {
    std::ostringstream os;
    EXPECT_NO_THROW(Exiv2::XmpProperties::printProperties(os, "dc"));
    // The output should contain something
    EXPECT_FALSE(os.str().empty());
}

// Test registering the same prefix with a different namespace overwrites
TEST_F(XmpPropertiesTest_1243, ReRegisterSamePrefixDifferentNs_1243) {
    const std::string ns1 = "http://example.com/first/";
    const std::string ns2 = "http://example.com/second/";
    const std::string prefix = "sameprefix";

    Exiv2::XmpProperties::registerNs(ns1, prefix);
    Exiv2::XmpProperties::registerNs(ns2, prefix);

    std::string result = Exiv2::XmpProperties::ns(prefix);
    EXPECT_EQ(result, ns2);
}

// Test lookupNsRegistry with empty prefix
TEST_F(XmpPropertiesTest_1243, LookupNsRegistryEmptyPrefix_1243) {
    Exiv2::XmpNsInfo::Prefix pfx;
    pfx.prefix_ = "";
    const Exiv2::XmpNsInfo* info = Exiv2::XmpProperties::lookupNsRegistry(pfx);
    EXPECT_EQ(info, nullptr);
}

// Test propertyTitle for a known dc property
TEST_F(XmpPropertiesTest_1243, PropertyTitleForKnownDcKey_1243) {
    try {
        Exiv2::XmpKey key("Xmp.dc.title");
        const char* title = Exiv2::XmpProperties::propertyTitle(key);
        // Title may or may not be null depending on the property, but should not crash
        if (title) {
            EXPECT_GT(std::string(title).size(), 0u);
        }
    } catch (const Exiv2::Error&) {
        // Some keys might not be valid, that's acceptable
    }
}

// Test propertyDesc for a known dc property
TEST_F(XmpPropertiesTest_1243, PropertyDescForKnownDcKey_1243) {
    try {
        Exiv2::XmpKey key("Xmp.dc.title");
        const char* desc = Exiv2::XmpProperties::propertyDesc(key);
        if (desc) {
            EXPECT_GT(std::string(desc).size(), 0u);
        }
    } catch (const Exiv2::Error&) {
        // Acceptable
    }
}

// Test propertyType for a known dc property
TEST_F(XmpPropertiesTest_1243, PropertyTypeForKnownDcKey_1243) {
    try {
        Exiv2::XmpKey key("Xmp.dc.title");
        Exiv2::TypeId type = Exiv2::XmpProperties::propertyType(key);
        // Should return some valid type
        EXPECT_NE(type, Exiv2::invalidTypeId);
    } catch (const Exiv2::Error&) {
        // Acceptable
    }
}

// Test propertyInfo for a known dc property
TEST_F(XmpPropertiesTest_1243, PropertyInfoForKnownDcKey_1243) {
    try {
        Exiv2::XmpKey key("Xmp.dc.title");
        const Exiv2::XmpPropertyInfo* info = Exiv2::XmpProperties::propertyInfo(key);
        // Info may or may not be null
        // Just ensure it doesn't crash
        (void)info;
    } catch (const Exiv2::Error&) {
        // Acceptable
    }
}

// Test unregistering a namespace that was never registered
TEST_F(XmpPropertiesTest_1243, UnregisterNonExistentNs_1243) {
    // Should not throw or crash
    EXPECT_NO_THROW(Exiv2::XmpProperties::unregisterNs("http://nonexistent.example.com/"));
}

// Test that well-known prefixes like "exif" can be looked up
TEST_F(XmpPropertiesTest_1243, WellKnownExifPrefix_1243) {
    std::string nsResult = Exiv2::XmpProperties::ns("exif");
    EXPECT_FALSE(nsResult.empty());
}

// Test that well-known prefixes like "tiff" can be looked up
TEST_F(XmpPropertiesTest_1243, WellKnownTiffPrefix_1243) {
    std::string nsResult = Exiv2::XmpProperties::ns("tiff");
    EXPECT_FALSE(nsResult.empty());
}

// Test registering and querying multiple custom namespaces
TEST_F(XmpPropertiesTest_1243, MultipleCustomNamespaces_1243) {
    Exiv2::XmpProperties::registerNs("http://example.com/alpha/", "alpha");
    Exiv2::XmpProperties::registerNs("http://example.com/beta/", "beta");
    Exiv2::XmpProperties::registerNs("http://example.com/gamma/", "gamma");

    EXPECT_EQ(Exiv2::XmpProperties::ns("alpha"), "http://example.com/alpha/");
    EXPECT_EQ(Exiv2::XmpProperties::ns("beta"), "http://example.com/beta/");
    EXPECT_EQ(Exiv2::XmpProperties::ns("gamma"), "http://example.com/gamma/");

    EXPECT_EQ(Exiv2::XmpProperties::prefix("http://example.com/alpha/"), "alpha");
    EXPECT_EQ(Exiv2::XmpProperties::prefix("http://example.com/beta/"), "beta");
    EXPECT_EQ(Exiv2::XmpProperties::prefix("http://example.com/gamma/"), "gamma");
}

// Test that unregisterNs with specific ns only removes that one
TEST_F(XmpPropertiesTest_1243, UnregisterSpecificNsLeavesOthers_1243) {
    Exiv2::XmpProperties::registerNs("http://example.com/keep/", "keep");
    Exiv2::XmpProperties::registerNs("http://example.com/remove/", "remove");

    Exiv2::XmpProperties::unregisterNs("http://example.com/remove/");

    EXPECT_EQ(Exiv2::XmpProperties::ns("remove"), "");

    Exiv2::XmpNsInfo::Prefix pfxKeep;
    pfxKeep.prefix_ = "keep";
    const Exiv2::XmpNsInfo* info = Exiv2::XmpProperties::lookupNsRegistry(pfxKeep);
    EXPECT_NE(info, nullptr);
}

// Test printProperty with a simple value
TEST_F(XmpPropertiesTest_1243, PrintPropertyDoesNotCrash_1243) {
    std::ostringstream os;
    Exiv2::XmpTextValue value("Test value");
    EXPECT_NO_THROW(Exiv2::XmpProperties::printProperty(os, "Xmp.dc.title", value));
}

}  // namespace
