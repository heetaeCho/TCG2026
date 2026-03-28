#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include "exiv2/properties.hpp"
#include "exiv2/value.hpp"

using namespace Exiv2;

class XmpPropertiesTest_1250 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Ensure clean state by unregistering custom namespaces
    XmpProperties::unregisterNs();
  }

  void TearDown() override {
    XmpProperties::unregisterNs();
  }
};

// Test propertyDesc with a known XMP key (dc:description)
TEST_F(XmpPropertiesTest_1250, PropertyDescKnownKey_1250) {
  XmpKey key("Xmp.dc.description");
  const char* desc = XmpProperties::propertyDesc(key);
  EXPECT_NE(desc, nullptr);
  EXPECT_GT(strlen(desc), 0u);
}

// Test propertyDesc with an unknown property returns nullptr
TEST_F(XmpPropertiesTest_1250, PropertyDescUnknownProperty_1250) {
  XmpKey key("Xmp.dc.nonExistentProperty12345");
  const char* desc = XmpProperties::propertyDesc(key);
  // Unknown properties should return nullptr
  EXPECT_EQ(desc, nullptr);
}

// Test propertyTitle with a known key
TEST_F(XmpPropertiesTest_1250, PropertyTitleKnownKey_1250) {
  XmpKey key("Xmp.dc.title");
  const char* title = XmpProperties::propertyTitle(key);
  EXPECT_NE(title, nullptr);
  EXPECT_GT(strlen(title), 0u);
}

// Test propertyTitle with an unknown property
TEST_F(XmpPropertiesTest_1250, PropertyTitleUnknownProperty_1250) {
  XmpKey key("Xmp.dc.unknownPropertyXYZ");
  const char* title = XmpProperties::propertyTitle(key);
  EXPECT_EQ(title, nullptr);
}

// Test propertyType with a known key
TEST_F(XmpPropertiesTest_1250, PropertyTypeKnownKey_1250) {
  XmpKey key("Xmp.dc.creator");
  TypeId type = XmpProperties::propertyType(key);
  EXPECT_NE(type, invalidTypeId);
}

// Test propertyInfo with a known key
TEST_F(XmpPropertiesTest_1250, PropertyInfoKnownKey_1250) {
  XmpKey key("Xmp.dc.subject");
  const XmpPropertyInfo* info = XmpProperties::propertyInfo(key);
  EXPECT_NE(info, nullptr);
}

// Test propertyInfo with an unknown key
TEST_F(XmpPropertiesTest_1250, PropertyInfoUnknownKey_1250) {
  XmpKey key("Xmp.dc.totallyFakeProperty");
  const XmpPropertyInfo* info = XmpProperties::propertyInfo(key);
  EXPECT_EQ(info, nullptr);
}

// Test ns for a known prefix
TEST_F(XmpPropertiesTest_1250, NsForKnownPrefix_1250) {
  std::string nsValue = XmpProperties::ns("dc");
  EXPECT_FALSE(nsValue.empty());
  EXPECT_NE(nsValue.find("dc"), std::string::npos);
}

// Test prefix for a known namespace
TEST_F(XmpPropertiesTest_1250, PrefixForKnownNs_1250) {
  std::string nsValue = XmpProperties::ns("dc");
  ASSERT_FALSE(nsValue.empty());
  std::string prefixValue = XmpProperties::prefix(nsValue);
  EXPECT_EQ(prefixValue, "dc");
}

// Test nsDesc for a known prefix
TEST_F(XmpPropertiesTest_1250, NsDescKnownPrefix_1250) {
  const char* desc = XmpProperties::nsDesc("dc");
  EXPECT_NE(desc, nullptr);
  EXPECT_GT(strlen(desc), 0u);
}

// Test propertyList for a known prefix
TEST_F(XmpPropertiesTest_1250, PropertyListKnownPrefix_1250) {
  const XmpPropertyInfo* list = XmpProperties::propertyList("dc");
  EXPECT_NE(list, nullptr);
}

// Test nsInfo for a known prefix
TEST_F(XmpPropertiesTest_1250, NsInfoKnownPrefix_1250) {
  const XmpNsInfo* info = XmpProperties::nsInfo("dc");
  EXPECT_NE(info, nullptr);
}

// Test registerNs and prefix lookup
TEST_F(XmpPropertiesTest_1250, RegisterNsAndLookup_1250) {
  const std::string testNs = "http://example.com/test/ns/1250/";
  const std::string testPrefix = "testns1250";

  XmpProperties::registerNs(testNs, testPrefix);

  std::string resolvedPrefix = XmpProperties::prefix(testNs);
  EXPECT_EQ(resolvedPrefix, testPrefix);

  std::string resolvedNs = XmpProperties::ns(testPrefix);
  EXPECT_EQ(resolvedNs, testNs);

  // Clean up
  XmpProperties::unregisterNs(testNs);
}

// Test unregisterNs removes a registered namespace
TEST_F(XmpPropertiesTest_1250, UnregisterNsRemovesRegistration_1250) {
  const std::string testNs = "http://example.com/test/unregister/1250/";
  const std::string testPrefix = "unreg1250";

  XmpProperties::registerNs(testNs, testPrefix);
  std::string resolvedPrefix = XmpProperties::prefix(testNs);
  EXPECT_EQ(resolvedPrefix, testPrefix);

  XmpProperties::unregisterNs(testNs);

  // After unregistering, the prefix should be empty
  std::string resolvedAfter = XmpProperties::prefix(testNs);
  EXPECT_TRUE(resolvedAfter.empty());
}

// Test unregisterNs (no args) clears all custom registrations
TEST_F(XmpPropertiesTest_1250, UnregisterAllNs_1250) {
  const std::string testNs1 = "http://example.com/test/all1/1250/";
  const std::string testPrefix1 = "all1x1250";
  const std::string testNs2 = "http://example.com/test/all2/1250/";
  const std::string testPrefix2 = "all2x1250";

  XmpProperties::registerNs(testNs1, testPrefix1);
  XmpProperties::registerNs(testNs2, testPrefix2);

  XmpProperties::unregisterNs();

  EXPECT_TRUE(XmpProperties::prefix(testNs1).empty());
  EXPECT_TRUE(XmpProperties::prefix(testNs2).empty());
}

// Test registeredNamespaces returns a dictionary
TEST_F(XmpPropertiesTest_1250, RegisteredNamespacesNotEmpty_1250) {
  Exiv2::Dictionary nsDict;
  XmpProperties::registeredNamespaces(nsDict);
  // There should be at least some built-in namespaces
  EXPECT_FALSE(nsDict.empty());
}

// Test registeredNamespaces includes custom registration
TEST_F(XmpPropertiesTest_1250, RegisteredNamespacesIncludesCustom_1250) {
  const std::string testNs = "http://example.com/test/regdict/1250/";
  const std::string testPrefix = "regdict1250";

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

// Test printProperties does not crash for a known prefix
TEST_F(XmpPropertiesTest_1250, PrintPropertiesKnownPrefix_1250) {
  std::ostringstream os;
  EXPECT_NO_THROW(XmpProperties::printProperties(os, "dc"));
  EXPECT_FALSE(os.str().empty());
}

// Test XmpKey construction from full key string
TEST_F(XmpPropertiesTest_1250, XmpKeyFromString_1250) {
  XmpKey key("Xmp.dc.title");
  EXPECT_EQ(key.key(), "Xmp.dc.title");
  EXPECT_STREQ(key.familyName(), "Xmp");
  EXPECT_EQ(key.groupName(), "dc");
  EXPECT_EQ(key.tagName(), "title");
}

// Test XmpKey construction from prefix and property
TEST_F(XmpPropertiesTest_1250, XmpKeyFromPrefixAndProperty_1250) {
  XmpKey key("dc", "subject");
  EXPECT_EQ(key.key(), "Xmp.dc.subject");
  EXPECT_STREQ(key.familyName(), "Xmp");
  EXPECT_EQ(key.groupName(), "dc");
  EXPECT_EQ(key.tagName(), "subject");
}

// Test XmpKey copy constructor
TEST_F(XmpPropertiesTest_1250, XmpKeyCopyConstructor_1250) {
  XmpKey original("Xmp.dc.creator");
  XmpKey copy(original);
  EXPECT_EQ(copy.key(), original.key());
  EXPECT_EQ(copy.groupName(), original.groupName());
  EXPECT_EQ(copy.tagName(), original.tagName());
}

// Test XmpKey assignment operator
TEST_F(XmpPropertiesTest_1250, XmpKeyAssignment_1250) {
  XmpKey key1("Xmp.dc.title");
  XmpKey key2("Xmp.dc.subject");
  key2 = key1;
  EXPECT_EQ(key2.key(), key1.key());
  EXPECT_EQ(key2.tagName(), key1.tagName());
}

// Test XmpKey clone
TEST_F(XmpPropertiesTest_1250, XmpKeyClone_1250) {
  XmpKey original("Xmp.dc.description");
  auto cloned = original.clone();
  EXPECT_NE(cloned, nullptr);
  EXPECT_EQ(cloned->key(), original.key());
}

// Test XmpKey ns returns a non-empty namespace for a known prefix
TEST_F(XmpPropertiesTest_1250, XmpKeyNs_1250) {
  XmpKey key("Xmp.dc.title");
  std::string ns = key.ns();
  EXPECT_FALSE(ns.empty());
}

// Test XmpKey tagLabel for a known property
TEST_F(XmpPropertiesTest_1250, XmpKeyTagLabel_1250) {
  XmpKey key("Xmp.dc.title");
  std::string label = key.tagLabel();
  EXPECT_FALSE(label.empty());
}

// Test XmpKey tagDesc for a known property
TEST_F(XmpPropertiesTest_1250, XmpKeyTagDesc_1250) {
  XmpKey key("Xmp.dc.title");
  std::string desc = key.tagDesc();
  // desc may or may not be empty depending on the property
}

// Test that re-registering a namespace with a different prefix updates correctly
TEST_F(XmpPropertiesTest_1250, ReRegisterNsUpdatesPrefix_1250) {
  const std::string testNs = "http://example.com/test/rereg/1250/";
  const std::string testPrefix1 = "rereg1a";
  const std::string testPrefix2 = "rereg1b";

  XmpProperties::registerNs(testNs, testPrefix1);
  EXPECT_EQ(XmpProperties::prefix(testNs), testPrefix1);

  XmpProperties::registerNs(testNs, testPrefix2);
  EXPECT_EQ(XmpProperties::prefix(testNs), testPrefix2);

  XmpProperties::unregisterNs(testNs);
}

// Test that ns("dc") returns the Dublin Core namespace
TEST_F(XmpPropertiesTest_1250, NsForDc_1250) {
  std::string nsValue = XmpProperties::ns("dc");
  EXPECT_FALSE(nsValue.empty());
  // Dublin Core namespace typically contains "purl.org/dc"
  EXPECT_NE(nsValue.find("dc"), std::string::npos);
}

// Test prefix for an unknown namespace returns empty
TEST_F(XmpPropertiesTest_1250, PrefixForUnknownNs_1250) {
  std::string result = XmpProperties::prefix("http://totally.nonexistent.ns/1250/");
  EXPECT_TRUE(result.empty());
}

// Test multiple known XMP prefixes
TEST_F(XmpPropertiesTest_1250, NsInfoForXmpPrefix_1250) {
  const XmpNsInfo* info = XmpProperties::nsInfo("xmp");
  EXPECT_NE(info, nullptr);
}

// Test propertyDesc for xmp:CreateDate
TEST_F(XmpPropertiesTest_1250, PropertyDescXmpCreateDate_1250) {
  XmpKey key("Xmp.xmp.CreateDate");
  const char* desc = XmpProperties::propertyDesc(key);
  EXPECT_NE(desc, nullptr);
}

// Test propertyInfo for tiff prefix properties
TEST_F(XmpPropertiesTest_1250, PropertyInfoTiffImageWidth_1250) {
  XmpKey key("Xmp.tiff.ImageWidth");
  const XmpPropertyInfo* info = XmpProperties::propertyInfo(key);
  EXPECT_NE(info, nullptr);
}

// Test printProperty with a string value
TEST_F(XmpPropertiesTest_1250, PrintPropertyWithStringValue_1250) {
  std::ostringstream os;
  XmpTextValue value("test value");
  EXPECT_NO_THROW(XmpProperties::printProperty(os, "Xmp.dc.title", value));
}

// Test that XmpKey throws on invalid key format
TEST_F(XmpPropertiesTest_1250, XmpKeyInvalidFormat_1250) {
  EXPECT_THROW(XmpKey("invalidkey"), Error);
}

// Test lookupNsRegistry for unregistered prefix
TEST_F(XmpPropertiesTest_1250, LookupNsRegistryUnknown_1250) {
  XmpNsInfo::Prefix prefix("nonexistent1250");
  const XmpNsInfo* result = XmpProperties::lookupNsRegistry(prefix);
  EXPECT_EQ(result, nullptr);
}

// Test lookupNsRegistry for a registered custom namespace
TEST_F(XmpPropertiesTest_1250, LookupNsRegistryAfterRegister_1250) {
  const std::string testNs = "http://example.com/test/lookup/1250/";
  const std::string testPrefix = "lookup1250";

  XmpProperties::registerNs(testNs, testPrefix);

  XmpNsInfo::Prefix prefix(testPrefix);
  const XmpNsInfo* result = XmpProperties::lookupNsRegistry(prefix);
  EXPECT_NE(result, nullptr);

  XmpProperties::unregisterNs(testNs);
}
