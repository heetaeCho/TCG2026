#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <map>

#include <exiv2/properties.hpp>
#include <exiv2/value.hpp>
#include <exiv2/error.hpp>

namespace {

using namespace Exiv2;

// Test fixture for XmpProperties tests
class XmpPropertiesTest_1253 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Unregister all custom namespaces to start clean
    XmpProperties::unregisterNs();
  }

  void TearDown() override {
    // Clean up any registered namespaces
    XmpProperties::unregisterNs();
  }
};

// ============================================================
// Tests for ns() - get namespace URI from prefix
// ============================================================

TEST_F(XmpPropertiesTest_1253, NsReturnsNamespaceForKnownPrefix_dc_1253) {
  std::string nsUri = XmpProperties::ns("dc");
  EXPECT_FALSE(nsUri.empty());
  EXPECT_EQ("http://purl.org/dc/elements/1.1/", nsUri);
}

TEST_F(XmpPropertiesTest_1253, NsReturnsNamespaceForKnownPrefix_xmp_1253) {
  std::string nsUri = XmpProperties::ns("xmp");
  EXPECT_FALSE(nsUri.empty());
  EXPECT_EQ("http://ns.adobe.com/xap/1.0/", nsUri);
}

TEST_F(XmpPropertiesTest_1253, NsReturnsNamespaceForKnownPrefix_exif_1253) {
  std::string nsUri = XmpProperties::ns("exif");
  EXPECT_FALSE(nsUri.empty());
}

TEST_F(XmpPropertiesTest_1253, NsThrowsForUnknownPrefix_1253) {
  EXPECT_THROW(XmpProperties::ns("nonexistent_prefix_xyz"), Error);
}

// ============================================================
// Tests for prefix() - get prefix from namespace URI
// ============================================================

TEST_F(XmpPropertiesTest_1253, PrefixReturnsPrefixForKnownNamespace_1253) {
  std::string pfx = XmpProperties::prefix("http://purl.org/dc/elements/1.1/");
  EXPECT_EQ("dc", pfx);
}

TEST_F(XmpPropertiesTest_1253, PrefixReturnsEmptyForUnknownNamespace_1253) {
  std::string pfx = XmpProperties::prefix("http://nonexistent.example.com/ns/");
  EXPECT_TRUE(pfx.empty());
}

// ============================================================
// Tests for nsDesc() - get namespace description
// ============================================================

TEST_F(XmpPropertiesTest_1253, NsDescReturnsDescriptionForKnownPrefix_1253) {
  const char* desc = XmpProperties::nsDesc("dc");
  ASSERT_NE(nullptr, desc);
  EXPECT_GT(strlen(desc), 0u);
}

TEST_F(XmpPropertiesTest_1253, NsDescThrowsForUnknownPrefix_1253) {
  EXPECT_THROW(XmpProperties::nsDesc("totally_unknown_prefix"), Error);
}

// ============================================================
// Tests for nsInfo() - get namespace info struct
// ============================================================

TEST_F(XmpPropertiesTest_1253, NsInfoReturnsNonNullForKnownPrefix_1253) {
  const XmpNsInfo* info = XmpProperties::nsInfo("dc");
  ASSERT_NE(nullptr, info);
  EXPECT_NE(nullptr, info->ns_);
  EXPECT_NE(nullptr, info->prefix_);
}

TEST_F(XmpPropertiesTest_1253, NsInfoThrowsForUnknownPrefix_1253) {
  EXPECT_THROW(XmpProperties::nsInfo("unknown_prefix_abc"), Error);
}

// ============================================================
// Tests for propertyList() - get property list for a prefix
// ============================================================

TEST_F(XmpPropertiesTest_1253, PropertyListReturnsNonNullForKnownPrefix_1253) {
  const XmpPropertyInfo* propList = XmpProperties::propertyList("dc");
  EXPECT_NE(nullptr, propList);
}

TEST_F(XmpPropertiesTest_1253, PropertyListThrowsForUnknownPrefix_1253) {
  EXPECT_THROW(XmpProperties::propertyList("nonexistent_pfx"), Error);
}

// ============================================================
// Tests for registerNs() and unregisterNs()
// ============================================================

TEST_F(XmpPropertiesTest_1253, RegisterNsAndRetrieve_1253) {
  const std::string testNs = "http://example.com/test/ns/";
  const std::string testPrefix = "testprefix";

  XmpProperties::registerNs(testNs, testPrefix);

  // Now we should be able to get the prefix from the namespace
  std::string pfx = XmpProperties::prefix(testNs);
  EXPECT_EQ(testPrefix, pfx);

  // And get the namespace from the prefix
  std::string ns = XmpProperties::ns(testPrefix);
  EXPECT_EQ(testNs, ns);

  // Clean up
  XmpProperties::unregisterNs(testNs);
}

TEST_F(XmpPropertiesTest_1253, UnregisterNsRemovesRegistration_1253) {
  const std::string testNs = "http://example.com/test/unregister/";
  const std::string testPrefix = "unreg";

  XmpProperties::registerNs(testNs, testPrefix);

  // Verify registration
  std::string pfx = XmpProperties::prefix(testNs);
  EXPECT_EQ(testPrefix, pfx);

  // Unregister
  XmpProperties::unregisterNs(testNs);

  // After unregistering, prefix should return empty
  pfx = XmpProperties::prefix(testNs);
  EXPECT_TRUE(pfx.empty());
}

TEST_F(XmpPropertiesTest_1253, UnregisterAllCustomNamespaces_1253) {
  const std::string testNs1 = "http://example.com/test/ns1/";
  const std::string testPrefix1 = "testns1";
  const std::string testNs2 = "http://example.com/test/ns2/";
  const std::string testPrefix2 = "testns2";

  XmpProperties::registerNs(testNs1, testPrefix1);
  XmpProperties::registerNs(testNs2, testPrefix2);

  // Unregister all
  XmpProperties::unregisterNs();

  // Custom namespaces should be gone
  EXPECT_TRUE(XmpProperties::prefix(testNs1).empty());
  EXPECT_TRUE(XmpProperties::prefix(testNs2).empty());

  // Built-in namespaces should still work
  EXPECT_EQ("dc", XmpProperties::prefix("http://purl.org/dc/elements/1.1/"));
}

// ============================================================
// Tests for registeredNamespaces()
// ============================================================

TEST_F(XmpPropertiesTest_1253, RegisteredNamespacesContainsBuiltIns_1253) {
  Dictionary nsDict;
  XmpProperties::registeredNamespaces(nsDict);

  // Should contain at least the built-in namespaces
  EXPECT_FALSE(nsDict.empty());

  // Check for dc namespace
  bool foundDc = false;
  for (const auto& entry : nsDict) {
    if (entry.second == "dc") {
      foundDc = true;
      EXPECT_EQ("http://purl.org/dc/elements/1.1/", entry.first);
      break;
    }
  }
  EXPECT_TRUE(foundDc);
}

TEST_F(XmpPropertiesTest_1253, RegisteredNamespacesIncludesCustom_1253) {
  const std::string testNs = "http://example.com/test/registered/";
  const std::string testPrefix = "regtest";

  XmpProperties::registerNs(testNs, testPrefix);

  Dictionary nsDict;
  XmpProperties::registeredNamespaces(nsDict);

  // Should contain our custom namespace
  auto it = nsDict.find(testNs);
  EXPECT_NE(nsDict.end(), it);
  if (it != nsDict.end()) {
    EXPECT_EQ(testPrefix, it->second);
  }

  XmpProperties::unregisterNs(testNs);
}

// ============================================================
// Tests for lookupNsRegistry()
// ============================================================

TEST_F(XmpPropertiesTest_1253, LookupNsRegistryReturnsNullForBuiltIn_1253) {
  // Built-in namespaces are not in the registry (only custom ones)
  XmpNsInfo::Prefix dcPrefix("dc");
  const XmpNsInfo* info = XmpProperties::lookupNsRegistry(dcPrefix);
  // dc is a built-in, so it should not be in the custom registry
  EXPECT_EQ(nullptr, info);
}

TEST_F(XmpPropertiesTest_1253, LookupNsRegistryFindsCustomNamespace_1253) {
  const std::string testNs = "http://example.com/test/lookup/";
  const std::string testPrefix = "lookuptest";

  XmpProperties::registerNs(testNs, testPrefix);

  XmpNsInfo::Prefix pfx(testPrefix);
  const XmpNsInfo* info = XmpProperties::lookupNsRegistry(pfx);
  ASSERT_NE(nullptr, info);

  XmpProperties::unregisterNs(testNs);
}

// ============================================================
// Tests for propertyTitle(), propertyDesc(), propertyType(), propertyInfo()
// ============================================================

TEST_F(XmpPropertiesTest_1253, PropertyTitleReturnsValidTitleForKnownKey_1253) {
  XmpKey key("Xmp.dc.title");
  const char* title = XmpProperties::propertyTitle(key);
  // title may or may not be null depending on property definition
  // but for dc.title it should have a title
  ASSERT_NE(nullptr, title);
  EXPECT_GT(strlen(title), 0u);
}

TEST_F(XmpPropertiesTest_1253, PropertyDescReturnsValidDescForKnownKey_1253) {
  XmpKey key("Xmp.dc.title");
  const char* desc = XmpProperties::propertyDesc(key);
  ASSERT_NE(nullptr, desc);
  EXPECT_GT(strlen(desc), 0u);
}

TEST_F(XmpPropertiesTest_1253, PropertyTypeReturnsValidTypeForKnownKey_1253) {
  XmpKey key("Xmp.dc.title");
  TypeId typeId = XmpProperties::propertyType(key);
  // Should return a valid type, not invalidTypeId for a known property
  EXPECT_NE(invalidTypeId, typeId);
}

TEST_F(XmpPropertiesTest_1253, PropertyInfoReturnsNonNullForKnownKey_1253) {
  XmpKey key("Xmp.dc.title");
  const XmpPropertyInfo* info = XmpProperties::propertyInfo(key);
  EXPECT_NE(nullptr, info);
}

TEST_F(XmpPropertiesTest_1253, PropertyInfoReturnsNullForUnknownProperty_1253) {
  XmpKey key("Xmp.dc.nonExistentProperty12345");
  const XmpPropertyInfo* info = XmpProperties::propertyInfo(key);
  EXPECT_EQ(nullptr, info);
}

TEST_F(XmpPropertiesTest_1253, PropertyTitleReturnsNullForUnknownProperty_1253) {
  XmpKey key("Xmp.dc.nonExistentProperty12345");
  const char* title = XmpProperties::propertyTitle(key);
  EXPECT_EQ(nullptr, title);
}

TEST_F(XmpPropertiesTest_1253, PropertyDescReturnsNullForUnknownProperty_1253) {
  XmpKey key("Xmp.dc.nonExistentProperty12345");
  const char* desc = XmpProperties::propertyDesc(key);
  EXPECT_EQ(nullptr, desc);
}

// ============================================================
// Tests for printProperties()
// ============================================================

TEST_F(XmpPropertiesTest_1253, PrintPropertiesOutputsDataForKnownPrefix_1253) {
  std::ostringstream os;
  XmpProperties::printProperties(os, "dc");
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

// ============================================================
// Tests for printProperty()
// ============================================================

TEST_F(XmpPropertiesTest_1253, PrintPropertyOutputsSomething_1253) {
  std::ostringstream os;
  XmpTextValue value("Test value");
  XmpProperties::printProperty(os, "Xmp.dc.title", value);
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

// ============================================================
// Tests for multiple known prefixes
// ============================================================

TEST_F(XmpPropertiesTest_1253, NsWorksForTiffPrefix_1253) {
  std::string nsUri = XmpProperties::ns("tiff");
  EXPECT_FALSE(nsUri.empty());
}

TEST_F(XmpPropertiesTest_1253, NsWorksForXmpRightsPrefix_1253) {
  std::string nsUri = XmpProperties::ns("xmpRights");
  EXPECT_FALSE(nsUri.empty());
}

TEST_F(XmpPropertiesTest_1253, PrefixForXmpNamespace_1253) {
  std::string pfx = XmpProperties::prefix("http://ns.adobe.com/xap/1.0/");
  EXPECT_EQ("xmp", pfx);
}

// ============================================================
// Tests for re-registering namespaces
// ============================================================

TEST_F(XmpPropertiesTest_1253, ReRegisterNamespaceUpdatesPrefix_1253) {
  const std::string testNs = "http://example.com/test/reregister/";
  const std::string testPrefix1 = "rereg1";
  const std::string testPrefix2 = "rereg2";

  XmpProperties::registerNs(testNs, testPrefix1);
  std::string pfx = XmpProperties::prefix(testNs);
  EXPECT_EQ(testPrefix1, pfx);

  // Re-register with different prefix
  XmpProperties::registerNs(testNs, testPrefix2);
  pfx = XmpProperties::prefix(testNs);
  EXPECT_EQ(testPrefix2, pfx);

  XmpProperties::unregisterNs(testNs);
}

// ============================================================
// Edge case: empty prefix/namespace
// ============================================================

TEST_F(XmpPropertiesTest_1253, NsThrowsForEmptyPrefix_1253) {
  EXPECT_THROW(XmpProperties::ns(""), Error);
}

TEST_F(XmpPropertiesTest_1253, PrefixReturnsEmptyForEmptyNamespace_1253) {
  std::string pfx = XmpProperties::prefix("");
  EXPECT_TRUE(pfx.empty());
}

// ============================================================
// Tests for XmpKey with custom registered namespace
// ============================================================

TEST_F(XmpPropertiesTest_1253, PropertyTypeForCustomNamespaceReturnsXmpText_1253) {
  const std::string testNs = "http://example.com/test/custom/";
  const std::string testPrefix = "customns";

  XmpProperties::registerNs(testNs, testPrefix);

  XmpKey key("Xmp.customns.someProperty");
  TypeId typeId = XmpProperties::propertyType(key);
  // For unknown properties in custom namespace, should return xmpText
  EXPECT_EQ(xmpText, typeId);

  XmpProperties::unregisterNs(testNs);
}

}  // namespace
