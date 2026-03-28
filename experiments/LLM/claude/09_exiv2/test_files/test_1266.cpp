#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include "exiv2/properties.hpp"
#include "exiv2/value.hpp"

using namespace Exiv2;

// Test fixture for XmpProperties and XmpKey tests
class XmpPropertiesTest_1266 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Unregister all custom namespaces to start clean
    XmpProperties::unregisterNs();
  }

  void TearDown() override {
    // Clean up custom namespaces
    XmpProperties::unregisterNs();
  }
};

// ==================== XmpKey Construction Tests ====================

TEST_F(XmpPropertiesTest_1266, XmpKeyConstructFromString_1266) {
  XmpKey key("Xmp.dc.title");
  EXPECT_EQ(key.key(), "Xmp.dc.title");
  EXPECT_STREQ(key.familyName(), "Xmp");
  EXPECT_EQ(key.groupName(), "dc");
  EXPECT_EQ(key.tagName(), "title");
}

TEST_F(XmpPropertiesTest_1266, XmpKeyConstructFromPrefixAndProperty_1266) {
  XmpKey key("dc", "creator");
  EXPECT_EQ(key.key(), "Xmp.dc.creator");
  EXPECT_STREQ(key.familyName(), "Xmp");
  EXPECT_EQ(key.groupName(), "dc");
  EXPECT_EQ(key.tagName(), "creator");
}

TEST_F(XmpPropertiesTest_1266, XmpKeyCopyConstructor_1266) {
  XmpKey original("Xmp.dc.title");
  XmpKey copy(original);
  EXPECT_EQ(copy.key(), original.key());
  EXPECT_EQ(copy.groupName(), original.groupName());
  EXPECT_EQ(copy.tagName(), original.tagName());
}

TEST_F(XmpPropertiesTest_1266, XmpKeyAssignmentOperator_1266) {
  XmpKey key1("Xmp.dc.title");
  XmpKey key2("Xmp.dc.creator");
  key2 = key1;
  EXPECT_EQ(key2.key(), key1.key());
  EXPECT_EQ(key2.tagName(), key1.tagName());
}

TEST_F(XmpPropertiesTest_1266, XmpKeyClone_1266) {
  XmpKey original("Xmp.dc.title");
  auto cloned = original.clone();
  ASSERT_NE(cloned, nullptr);
  EXPECT_EQ(cloned->key(), original.key());
  EXPECT_EQ(cloned->tagName(), original.tagName());
}

TEST_F(XmpPropertiesTest_1266, XmpKeyFamilyNameIsXmp_1266) {
  XmpKey key("Xmp.dc.subject");
  EXPECT_STREQ(key.familyName(), "Xmp");
}

TEST_F(XmpPropertiesTest_1266, XmpKeyNs_1266) {
  XmpKey key("Xmp.dc.title");
  std::string nsValue = key.ns();
  EXPECT_FALSE(nsValue.empty());
}

// ==================== XmpKey tagLabel and tagDesc Tests ====================

TEST_F(XmpPropertiesTest_1266, XmpKeyTagLabelKnownProperty_1266) {
  XmpKey key("Xmp.dc.title");
  std::string label = key.tagLabel();
  // Known property should have a non-empty label
  EXPECT_FALSE(label.empty());
}

TEST_F(XmpPropertiesTest_1266, XmpKeyTagDescKnownProperty_1266) {
  XmpKey key("Xmp.dc.title");
  std::string desc = key.tagDesc();
  // Known dc.title should have a description
  // The tagDesc method returns "" if propertyDesc returns null
  // For a well-known property, we expect non-empty
  EXPECT_FALSE(desc.empty());
}

TEST_F(XmpPropertiesTest_1266, XmpKeyTagDescReturnsEmptyForUnknown_1266) {
  // Register a custom namespace with no property definitions
  XmpProperties::registerNs("http://example.com/test/", "testns");
  XmpKey key("Xmp.testns.unknownProp");
  std::string desc = key.tagDesc();
  // Unknown property should return empty string
  EXPECT_EQ(desc, "");
  XmpProperties::unregisterNs("http://example.com/test/");
}

TEST_F(XmpPropertiesTest_1266, XmpKeyTag_1266) {
  XmpKey key("Xmp.dc.title");
  // tag() returns a uint16_t; for XMP it is typically 0
  uint16_t t = key.tag();
  // We just verify it doesn't throw and returns some value
  (void)t;
}

// ==================== XmpProperties::propertyTitle Tests ====================

TEST_F(XmpPropertiesTest_1266, PropertyTitleKnownProperty_1266) {
  XmpKey key("Xmp.dc.title");
  const char* title = XmpProperties::propertyTitle(key);
  EXPECT_NE(title, nullptr);
}

TEST_F(XmpPropertiesTest_1266, PropertyTitleUnknownProperty_1266) {
  XmpProperties::registerNs("http://example.com/unknown/", "unkn");
  XmpKey key("Xmp.unkn.nonexistent");
  const char* title = XmpProperties::propertyTitle(key);
  EXPECT_EQ(title, nullptr);
  XmpProperties::unregisterNs("http://example.com/unknown/");
}

// ==================== XmpProperties::propertyDesc Tests ====================

TEST_F(XmpPropertiesTest_1266, PropertyDescKnownProperty_1266) {
  XmpKey key("Xmp.dc.creator");
  const char* desc = XmpProperties::propertyDesc(key);
  EXPECT_NE(desc, nullptr);
}

TEST_F(XmpPropertiesTest_1266, PropertyDescUnknownProperty_1266) {
  XmpProperties::registerNs("http://example.com/test2/", "test2");
  XmpKey key("Xmp.test2.missing");
  const char* desc = XmpProperties::propertyDesc(key);
  EXPECT_EQ(desc, nullptr);
  XmpProperties::unregisterNs("http://example.com/test2/");
}

// ==================== XmpProperties::propertyType Tests ====================

TEST_F(XmpPropertiesTest_1266, PropertyTypeKnownProperty_1266) {
  XmpKey key("Xmp.dc.title");
  TypeId type = XmpProperties::propertyType(key);
  EXPECT_NE(type, invalidTypeId);
}

// ==================== XmpProperties::propertyInfo Tests ====================

TEST_F(XmpPropertiesTest_1266, PropertyInfoKnownProperty_1266) {
  XmpKey key("Xmp.dc.title");
  const XmpPropertyInfo* info = XmpProperties::propertyInfo(key);
  EXPECT_NE(info, nullptr);
}

TEST_F(XmpPropertiesTest_1266, PropertyInfoUnknownProperty_1266) {
  XmpProperties::registerNs("http://example.com/test3/", "test3");
  XmpKey key("Xmp.test3.noSuchProp");
  const XmpPropertyInfo* info = XmpProperties::propertyInfo(key);
  EXPECT_EQ(info, nullptr);
  XmpProperties::unregisterNs("http://example.com/test3/");
}

// ==================== Namespace Registration/Lookup Tests ====================

TEST_F(XmpPropertiesTest_1266, RegisterAndLookupNs_1266) {
  const std::string testNs = "http://example.com/myreg/";
  const std::string testPrefix = "myreg";
  XmpProperties::registerNs(testNs, testPrefix);

  std::string resultPrefix = XmpProperties::prefix(testNs);
  EXPECT_EQ(resultPrefix, testPrefix);

  std::string resultNs = XmpProperties::ns(testPrefix);
  EXPECT_EQ(resultNs, testNs);

  XmpProperties::unregisterNs(testNs);
}

TEST_F(XmpPropertiesTest_1266, UnregisterNsRemovesNamespace_1266) {
  const std::string testNs = "http://example.com/unreg/";
  const std::string testPrefix = "unreg";
  XmpProperties::registerNs(testNs, testPrefix);

  // Verify it's registered
  EXPECT_EQ(XmpProperties::prefix(testNs), testPrefix);

  // Unregister
  XmpProperties::unregisterNs(testNs);

  // After unregistering, prefix lookup should return empty
  std::string resultPrefix = XmpProperties::prefix(testNs);
  EXPECT_TRUE(resultPrefix.empty());
}

TEST_F(XmpPropertiesTest_1266, UnregisterAllCustomNs_1266) {
  XmpProperties::registerNs("http://example.com/a/", "aaa");
  XmpProperties::registerNs("http://example.com/b/", "bbb");

  XmpProperties::unregisterNs();

  EXPECT_TRUE(XmpProperties::prefix("http://example.com/a/").empty());
  EXPECT_TRUE(XmpProperties::prefix("http://example.com/b/").empty());
}

// ==================== XmpProperties::ns and prefix Tests ====================

TEST_F(XmpPropertiesTest_1266, NsForBuiltInPrefix_1266) {
  std::string dcNs = XmpProperties::ns("dc");
  EXPECT_FALSE(dcNs.empty());
}

TEST_F(XmpPropertiesTest_1266, PrefixForBuiltInNs_1266) {
  std::string dcNs = XmpProperties::ns("dc");
  ASSERT_FALSE(dcNs.empty());
  std::string prefix = XmpProperties::prefix(dcNs);
  EXPECT_EQ(prefix, "dc");
}

TEST_F(XmpPropertiesTest_1266, NsForUnknownPrefixThrowsOrEmpty_1266) {
  // An unknown prefix should throw or return empty
  try {
    std::string result = XmpProperties::ns("totallyunknownprefix");
    // If it doesn't throw, it should be empty
    EXPECT_TRUE(result.empty());
  } catch (const Error&) {
    // Throwing is also acceptable behavior
    SUCCEED();
  }
}

// ==================== XmpProperties::nsDesc Tests ====================

TEST_F(XmpPropertiesTest_1266, NsDescBuiltInPrefix_1266) {
  const char* desc = XmpProperties::nsDesc("dc");
  EXPECT_NE(desc, nullptr);
}

// ==================== XmpProperties::propertyList Tests ====================

TEST_F(XmpPropertiesTest_1266, PropertyListBuiltInPrefix_1266) {
  const XmpPropertyInfo* list = XmpProperties::propertyList("dc");
  EXPECT_NE(list, nullptr);
}

TEST_F(XmpPropertiesTest_1266, PropertyListCustomPrefixReturnsNull_1266) {
  XmpProperties::registerNs("http://example.com/pl/", "plns");
  const XmpPropertyInfo* list = XmpProperties::propertyList("plns");
  EXPECT_EQ(list, nullptr);
  XmpProperties::unregisterNs("http://example.com/pl/");
}

// ==================== XmpProperties::nsInfo Tests ====================

TEST_F(XmpPropertiesTest_1266, NsInfoBuiltInPrefix_1266) {
  const XmpNsInfo* info = XmpProperties::nsInfo("dc");
  EXPECT_NE(info, nullptr);
}

// ==================== XmpProperties::registeredNamespaces Tests ====================

TEST_F(XmpPropertiesTest_1266, RegisteredNamespacesIncludesCustom_1266) {
  XmpProperties::registerNs("http://example.com/regns/", "regns");

  Exiv2::Dictionary nsDict;
  XmpProperties::registeredNamespaces(nsDict);

  // The custom namespace should appear in the dictionary
  auto it = nsDict.find("http://example.com/regns/");
  EXPECT_NE(it, nsDict.end());
  if (it != nsDict.end()) {
    EXPECT_EQ(it->second, "regns");
  }

  XmpProperties::unregisterNs("http://example.com/regns/");
}

TEST_F(XmpPropertiesTest_1266, RegisteredNamespacesNotEmpty_1266) {
  Exiv2::Dictionary nsDict;
  XmpProperties::registeredNamespaces(nsDict);
  // Should contain at least the built-in namespaces
  EXPECT_FALSE(nsDict.empty());
}

// ==================== XmpProperties::printProperties Tests ====================

TEST_F(XmpPropertiesTest_1266, PrintPropertiesDc_1266) {
  std::ostringstream os;
  XmpProperties::printProperties(os, "dc");
  std::string output = os.str();
  // Should produce some output for the dc namespace
  EXPECT_FALSE(output.empty());
}

// ==================== XmpProperties::printProperty Tests ====================

TEST_F(XmpPropertiesTest_1266, PrintPropertyProducesOutput_1266) {
  std::ostringstream os;
  XmpTextValue value("Test Value");
  XmpProperties::printProperty(os, "Xmp.dc.title", value);
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

// ==================== Boundary / Error Tests ====================

TEST_F(XmpPropertiesTest_1266, InvalidKeyFormatThrows_1266) {
  // A key without proper Xmp. prefix should throw
  EXPECT_THROW(XmpKey("invalid"), Error);
}

TEST_F(XmpPropertiesTest_1266, InvalidKeyMissingProperty_1266) {
  // A key with only family and group but no property
  EXPECT_THROW(XmpKey("Xmp.dc"), Error);
}

TEST_F(XmpPropertiesTest_1266, EmptyKeyThrows_1266) {
  EXPECT_THROW(XmpKey(""), Error);
}

TEST_F(XmpPropertiesTest_1266, RegisterNsOverwritePrefix_1266) {
  // Registering the same namespace with a different prefix
  XmpProperties::registerNs("http://example.com/overwrite/", "over1");
  std::string p1 = XmpProperties::prefix("http://example.com/overwrite/");
  EXPECT_EQ(p1, "over1");

  XmpProperties::registerNs("http://example.com/overwrite/", "over2");
  std::string p2 = XmpProperties::prefix("http://example.com/overwrite/");
  EXPECT_EQ(p2, "over2");

  XmpProperties::unregisterNs("http://example.com/overwrite/");
}

TEST_F(XmpPropertiesTest_1266, LookupNsRegistryCustomNs_1266) {
  XmpProperties::registerNs("http://example.com/lookup/", "lkup");
  XmpNsInfo::Prefix prefix("lkup");
  const XmpNsInfo* info = XmpProperties::lookupNsRegistry(prefix);
  EXPECT_NE(info, nullptr);
  XmpProperties::unregisterNs("http://example.com/lookup/");
}

TEST_F(XmpPropertiesTest_1266, LookupNsRegistryUnknown_1266) {
  XmpNsInfo::Prefix prefix("nonexistent_prefix_xyz");
  const XmpNsInfo* info = XmpProperties::lookupNsRegistry(prefix);
  EXPECT_EQ(info, nullptr);
}

// ==================== Multiple Properties in dc Namespace ====================

TEST_F(XmpPropertiesTest_1266, DcSubjectPropertyInfo_1266) {
  XmpKey key("Xmp.dc.subject");
  const XmpPropertyInfo* info = XmpProperties::propertyInfo(key);
  EXPECT_NE(info, nullptr);
}

TEST_F(XmpPropertiesTest_1266, DcDescriptionPropertyInfo_1266) {
  XmpKey key("Xmp.dc.description");
  const XmpPropertyInfo* info = XmpProperties::propertyInfo(key);
  EXPECT_NE(info, nullptr);
}

TEST_F(XmpPropertiesTest_1266, XmpRightsPropertyInfo_1266) {
  XmpKey key("Xmp.xmpRights.UsageTerms");
  const XmpPropertyInfo* info = XmpProperties::propertyInfo(key);
  EXPECT_NE(info, nullptr);
}

// ==================== Self-assignment Test ====================

TEST_F(XmpPropertiesTest_1266, XmpKeySelfAssignment_1266) {
  XmpKey key("Xmp.dc.title");
  key = key;
  EXPECT_EQ(key.key(), "Xmp.dc.title");
}
