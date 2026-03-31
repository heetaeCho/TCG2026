#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <map>
#include <sstream>

#include "exiv2/properties.hpp"
#include "exiv2/error.hpp"
#include "exiv2/xmp_exiv2.hpp"

namespace {

class XmpPropertiesTest_1244 : public ::testing::Test {
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

// Test registering a new namespace with a trailing slash
TEST_F(XmpPropertiesTest_1244, RegisterNsWithTrailingSlash_1244) {
    const std::string ns = "http://example.com/test/";
    const std::string prefix = "testprefix";

    Exiv2::XmpProperties::registerNs(ns, prefix);

    auto result = Exiv2::XmpProperties::lookupNsRegistry(Exiv2::XmpNsInfo::Prefix{prefix.c_str()});
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->ns_, ns.c_str());
    EXPECT_STREQ(result->prefix_, prefix.c_str());
}

// Test registering a new namespace without trailing slash (should auto-append '/')
TEST_F(XmpPropertiesTest_1244, RegisterNsWithoutTrailingSlash_1244) {
    const std::string ns = "http://example.com/test";
    const std::string prefix = "testns";

    Exiv2::XmpProperties::registerNs(ns, prefix);

    auto result = Exiv2::XmpProperties::lookupNsRegistry(Exiv2::XmpNsInfo::Prefix{prefix.c_str()});
    ASSERT_NE(result, nullptr);
    // Should have appended '/'
    EXPECT_STREQ(result->ns_, "http://example.com/test/");
    EXPECT_STREQ(result->prefix_, prefix.c_str());
}

// Test registering a namespace with trailing '#' (should not append '/')
TEST_F(XmpPropertiesTest_1244, RegisterNsWithTrailingHash_1244) {
    const std::string ns = "http://example.com/test#";
    const std::string prefix = "testhash";

    Exiv2::XmpProperties::registerNs(ns, prefix);

    auto result = Exiv2::XmpProperties::lookupNsRegistry(Exiv2::XmpNsInfo::Prefix{prefix.c_str()});
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->ns_, "http://example.com/test#");
    EXPECT_STREQ(result->prefix_, prefix.c_str());
}

// Test looking up a non-registered prefix returns nullptr
TEST_F(XmpPropertiesTest_1244, LookupNsRegistryNotFound_1244) {
    auto result = Exiv2::XmpProperties::lookupNsRegistry(Exiv2::XmpNsInfo::Prefix{"nonexistent"});
    EXPECT_EQ(result, nullptr);
}

// Test re-registering the same prefix with the same namespace
TEST_F(XmpPropertiesTest_1244, ReRegisterSameNsSamePrefix_1244) {
    const std::string ns = "http://example.com/same/";
    const std::string prefix = "sameprefix";

    Exiv2::XmpProperties::registerNs(ns, prefix);
    Exiv2::XmpProperties::registerNs(ns, prefix);

    auto result = Exiv2::XmpProperties::lookupNsRegistry(Exiv2::XmpNsInfo::Prefix{prefix.c_str()});
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->ns_, ns.c_str());
    EXPECT_STREQ(result->prefix_, prefix.c_str());
}

// Test updating namespace URI for an existing prefix
TEST_F(XmpPropertiesTest_1244, UpdateNsForExistingPrefix_1244) {
    const std::string ns1 = "http://example.com/old/";
    const std::string ns2 = "http://example.com/new/";
    const std::string prefix = "updateprefix";

    Exiv2::XmpProperties::registerNs(ns1, prefix);
    Exiv2::XmpProperties::registerNs(ns2, prefix);

    auto result = Exiv2::XmpProperties::lookupNsRegistry(Exiv2::XmpNsInfo::Prefix{prefix.c_str()});
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->ns_, ns2.c_str());
    EXPECT_STREQ(result->prefix_, prefix.c_str());
}

// Test unregistering a specific namespace
TEST_F(XmpPropertiesTest_1244, UnregisterSpecificNs_1244) {
    const std::string ns = "http://example.com/unregister/";
    const std::string prefix = "unreg";

    Exiv2::XmpProperties::registerNs(ns, prefix);
    auto result = Exiv2::XmpProperties::lookupNsRegistry(Exiv2::XmpNsInfo::Prefix{prefix.c_str()});
    ASSERT_NE(result, nullptr);

    Exiv2::XmpProperties::unregisterNs(ns);
    result = Exiv2::XmpProperties::lookupNsRegistry(Exiv2::XmpNsInfo::Prefix{prefix.c_str()});
    EXPECT_EQ(result, nullptr);
}

// Test unregisterNs() (all) clears custom registrations
TEST_F(XmpPropertiesTest_1244, UnregisterAllNs_1244) {
    Exiv2::XmpProperties::registerNs("http://example.com/a/", "nsa");
    Exiv2::XmpProperties::registerNs("http://example.com/b/", "nsb");

    Exiv2::XmpProperties::unregisterNs();

    EXPECT_EQ(Exiv2::XmpProperties::lookupNsRegistry(Exiv2::XmpNsInfo::Prefix{"nsa"}), nullptr);
    EXPECT_EQ(Exiv2::XmpProperties::lookupNsRegistry(Exiv2::XmpNsInfo::Prefix{"nsb"}), nullptr);
}

// Test registeredNamespaces includes registered custom ns
TEST_F(XmpPropertiesTest_1244, RegisteredNamespacesContainsCustom_1244) {
    const std::string ns = "http://example.com/regdict/";
    const std::string prefix = "regdict";

    Exiv2::XmpProperties::registerNs(ns, prefix);

    Exiv2::Dictionary nsDict;
    Exiv2::XmpProperties::registeredNamespaces(nsDict);

    auto it = nsDict.find(ns);
    ASSERT_NE(it, nsDict.end());
    EXPECT_EQ(it->second, prefix);
}

// Test prefix() returns the prefix for a registered namespace
TEST_F(XmpPropertiesTest_1244, PrefixForRegisteredNs_1244) {
    const std::string ns = "http://example.com/pfx/";
    const std::string prefix = "pfxtest";

    Exiv2::XmpProperties::registerNs(ns, prefix);

    std::string result = Exiv2::XmpProperties::prefix(ns);
    EXPECT_EQ(result, prefix);
}

// Test ns() returns the namespace for a registered prefix
TEST_F(XmpPropertiesTest_1244, NsForRegisteredPrefix_1244) {
    const std::string ns = "http://example.com/nstest/";
    const std::string prefix = "nstest";

    Exiv2::XmpProperties::registerNs(ns, prefix);

    std::string result = Exiv2::XmpProperties::ns(prefix);
    EXPECT_EQ(result, ns);
}

// Test registering multiple distinct namespaces with different prefixes
TEST_F(XmpPropertiesTest_1244, RegisterMultipleDistinctNamespaces_1244) {
    Exiv2::XmpProperties::registerNs("http://example.com/one/", "one");
    Exiv2::XmpProperties::registerNs("http://example.com/two/", "two");
    Exiv2::XmpProperties::registerNs("http://example.com/three/", "three");

    auto r1 = Exiv2::XmpProperties::lookupNsRegistry(Exiv2::XmpNsInfo::Prefix{"one"});
    auto r2 = Exiv2::XmpProperties::lookupNsRegistry(Exiv2::XmpNsInfo::Prefix{"two"});
    auto r3 = Exiv2::XmpProperties::lookupNsRegistry(Exiv2::XmpNsInfo::Prefix{"three"});

    ASSERT_NE(r1, nullptr);
    ASSERT_NE(r2, nullptr);
    ASSERT_NE(r3, nullptr);

    EXPECT_STREQ(r1->ns_, "http://example.com/one/");
    EXPECT_STREQ(r2->ns_, "http://example.com/two/");
    EXPECT_STREQ(r3->ns_, "http://example.com/three/");
}

// Test that xmpPropertyInfo_ is nullptr for custom registered namespace
TEST_F(XmpPropertiesTest_1244, RegisteredNsHasNullPropertyInfo_1244) {
    const std::string ns = "http://example.com/nullprop/";
    const std::string prefix = "nullprop";

    Exiv2::XmpProperties::registerNs(ns, prefix);

    auto result = Exiv2::XmpProperties::lookupNsRegistry(Exiv2::XmpNsInfo::Prefix{prefix.c_str()});
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->xmpPropertyInfo_, nullptr);
}

// Test that unregistering a non-existent namespace doesn't crash
TEST_F(XmpPropertiesTest_1244, UnregisterNonExistentNs_1244) {
    EXPECT_NO_THROW(Exiv2::XmpProperties::unregisterNs("http://nonexistent.example.com/"));
}

// Test that prefix for known built-in namespaces works (e.g., dc for Dublin Core)
TEST_F(XmpPropertiesTest_1244, BuiltInNamespacePrefix_1244) {
    std::string dcNs = Exiv2::XmpProperties::ns("dc");
    EXPECT_FALSE(dcNs.empty());
}

// Test that nsInfo for known built-in prefix works
TEST_F(XmpPropertiesTest_1244, NsInfoForBuiltInPrefix_1244) {
    const Exiv2::XmpNsInfo* info = Exiv2::XmpProperties::nsInfo("dc");
    ASSERT_NE(info, nullptr);
    EXPECT_NE(info->ns_, nullptr);
    EXPECT_NE(info->prefix_, nullptr);
}

// Test that registering with an empty-ish namespace still gets trailing slash
TEST_F(XmpPropertiesTest_1244, RegisterMinimalNs_1244) {
    const std::string ns = "x";
    const std::string prefix = "minns";

    Exiv2::XmpProperties::registerNs(ns, prefix);

    auto result = Exiv2::XmpProperties::lookupNsRegistry(Exiv2::XmpNsInfo::Prefix{prefix.c_str()});
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->ns_, "x/");
}

// Test registering and then looking up via registeredNamespaces after unregistering one
TEST_F(XmpPropertiesTest_1244, RegisteredNamespacesAfterPartialUnregister_1244) {
    Exiv2::XmpProperties::registerNs("http://example.com/keep/", "keep");
    Exiv2::XmpProperties::registerNs("http://example.com/remove/", "remove");

    Exiv2::XmpProperties::unregisterNs("http://example.com/remove/");

    Exiv2::Dictionary nsDict;
    Exiv2::XmpProperties::registeredNamespaces(nsDict);

    EXPECT_NE(nsDict.find("http://example.com/keep/"), nsDict.end());
    EXPECT_EQ(nsDict.find("http://example.com/remove/"), nsDict.end());
}

// Test that the prefix string is correctly stored (not a dangling reference)
TEST_F(XmpPropertiesTest_1244, PrefixStringIntegrity_1244) {
    {
        std::string ns = "http://example.com/integrity/";
        std::string prefix = "integrity";
        Exiv2::XmpProperties::registerNs(ns, prefix);
    }
    // ns and prefix strings are out of scope, but the registry should still be valid
    auto result = Exiv2::XmpProperties::lookupNsRegistry(Exiv2::XmpNsInfo::Prefix{"integrity"});
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->ns_, "http://example.com/integrity/");
    EXPECT_STREQ(result->prefix_, "integrity");
}

}  // namespace
