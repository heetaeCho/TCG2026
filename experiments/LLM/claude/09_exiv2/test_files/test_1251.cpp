#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include "exiv2/properties.hpp"
#include "exiv2/types.hpp"
#include "exiv2/value.hpp"

namespace {

using namespace Exiv2;

class XmpPropertiesTest_1251 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Ensure clean state by unregistering any custom namespaces
    XmpProperties::unregisterNs();
  }

  void TearDown() override {
    XmpProperties::unregisterNs();
  }
};

// ============================================================
// Tests for propertyType
// ============================================================

TEST_F(XmpPropertiesTest_1251, PropertyType_KnownDcSubject_ReturnsBagType_1251) {
  XmpKey key("Xmp.dc.subject");
  TypeId type = XmpProperties::propertyType(key);
  EXPECT_EQ(xmpBag, type);
}

TEST_F(XmpPropertiesTest_1251, PropertyType_KnownDcTitle_ReturnsLangAlt_1251) {
  XmpKey key("Xmp.dc.title");
  TypeId type = XmpProperties::propertyType(key);
  EXPECT_EQ(langAlt, type);
}

TEST_F(XmpPropertiesTest_1251, PropertyType_KnownDcDescription_ReturnsLangAlt_1251) {
  XmpKey key("Xmp.dc.description");
  TypeId type = XmpProperties::propertyType(key);
  EXPECT_EQ(langAlt, type);
}

TEST_F(XmpPropertiesTest_1251, PropertyType_KnownDcCreator_ReturnsSeqType_1251) {
  XmpKey key("Xmp.dc.creator");
  TypeId type = XmpProperties::propertyType(key);
  EXPECT_EQ(xmpSeq, type);
}

TEST_F(XmpPropertiesTest_1251, PropertyType_UnknownProperty_ReturnsXmpText_1251) {
  XmpKey key("Xmp.dc.nonExistentProperty12345");
  TypeId type = XmpProperties::propertyType(key);
  EXPECT_EQ(xmpText, type);
}

TEST_F(XmpPropertiesTest_1251, PropertyType_KnownXmpRating_ReturnsExpectedType_1251) {
  XmpKey key("Xmp.xmp.Rating");
  TypeId type = XmpProperties::propertyType(key);
  // Rating is typically xmpText (a simple value)
  EXPECT_NE(invalidTypeId, type);
}

// ============================================================
// Tests for propertyInfo
// ============================================================

TEST_F(XmpPropertiesTest_1251, PropertyInfo_KnownProperty_ReturnsNonNull_1251) {
  XmpKey key("Xmp.dc.subject");
  const XmpPropertyInfo* info = XmpProperties::propertyInfo(key);
  EXPECT_NE(nullptr, info);
}

TEST_F(XmpPropertiesTest_1251, PropertyInfo_UnknownProperty_ReturnsNull_1251) {
  XmpKey key("Xmp.dc.totallyUnknownProp999");
  const XmpPropertyInfo* info = XmpProperties::propertyInfo(key);
  EXPECT_EQ(nullptr, info);
}

// ============================================================
// Tests for propertyTitle
// ============================================================

TEST_F(XmpPropertiesTest_1251, PropertyTitle_KnownProperty_ReturnsNonNull_1251) {
  XmpKey key("Xmp.dc.subject");
  const char* title = XmpProperties::propertyTitle(key);
  EXPECT_NE(nullptr, title);
  EXPECT_GT(std::string(title).length(), 0u);
}

TEST_F(XmpPropertiesTest_1251, PropertyTitle_UnknownProperty_ReturnsEmptyOrNull_1251) {
  XmpKey key("Xmp.dc.nonExistentPropABC");
  const char* title = XmpProperties::propertyTitle(key);
  // For unknown properties, title should be empty string or null
  if (title != nullptr) {
    EXPECT_EQ(std::string(""), std::string(title));
  }
}

// ============================================================
// Tests for propertyDesc
// ============================================================

TEST_F(XmpPropertiesTest_1251, PropertyDesc_KnownProperty_ReturnsNonNull_1251) {
  XmpKey key("Xmp.dc.subject");
  const char* desc = XmpProperties::propertyDesc(key);
  EXPECT_NE(nullptr, desc);
  EXPECT_GT(std::string(desc).length(), 0u);
}

TEST_F(XmpPropertiesTest_1251, PropertyDesc_UnknownProperty_ReturnsEmptyOrNull_1251) {
  XmpKey key("Xmp.dc.unknownDescProp");
  const char* desc = XmpProperties::propertyDesc(key);
  if (desc != nullptr) {
    EXPECT_EQ(std::string(""), std::string(desc));
  }
}

// ============================================================
// Tests for ns / prefix
// ============================================================

TEST_F(XmpPropertiesTest_1251, Ns_KnownPrefix_ReturnsNonEmptyNamespace_1251) {
  std::string nsStr = XmpProperties::ns("dc");
  EXPECT_FALSE(nsStr.empty());
  EXPECT_NE(std::string::npos, nsStr.find("dc"));
}

TEST_F(XmpPropertiesTest_1251, Prefix_KnownNamespace_ReturnsExpectedPrefix_1251) {
  std::string nsStr = XmpProperties::ns("dc");
  ASSERT_FALSE(nsStr.empty());
  std::string prefixStr = XmpProperties::prefix(nsStr);
  EXPECT_EQ("dc", prefixStr);
}

TEST_F(XmpPropertiesTest_1251, Ns_XmpPrefix_ReturnsNonEmpty_1251) {
  std::string nsStr = XmpProperties::ns("xmp");
  EXPECT_FALSE(nsStr.empty());
}

// ============================================================
// Tests for nsDesc
// ============================================================

TEST_F(XmpPropertiesTest_1251, NsDesc_KnownPrefix_ReturnsNonNull_1251) {
  const char* desc = XmpProperties::nsDesc("dc");
  EXPECT_NE(nullptr, desc);
  EXPECT_GT(std::string(desc).length(), 0u);
}

// ============================================================
// Tests for nsInfo
// ============================================================

TEST_F(XmpPropertiesTest_1251, NsInfo_KnownPrefix_ReturnsNonNull_1251) {
  const XmpNsInfo* info = XmpProperties::nsInfo("dc");
  EXPECT_NE(nullptr, info);
}

// ============================================================
// Tests for propertyList
// ============================================================

TEST_F(XmpPropertiesTest_1251, PropertyList_KnownPrefix_ReturnsNonNull_1251) {
  const XmpPropertyInfo* list = XmpProperties::propertyList("dc");
  EXPECT_NE(nullptr, list);
}

TEST_F(XmpPropertiesTest_1251, PropertyList_UnknownPrefix_ReturnsNull_1251) {
  const XmpPropertyInfo* list = XmpProperties::propertyList("nonexistentprefix999");
  EXPECT_EQ(nullptr, list);
}

// ============================================================
// Tests for registerNs / unregisterNs
// ============================================================

TEST_F(XmpPropertiesTest_1251, RegisterNs_NewNamespace_CanBeRetrieved_1251) {
  const std::string testNs = "http://example.com/test/1251/";
  const std::string testPrefix = "test1251";

  XmpProperties::registerNs(testNs, testPrefix);

  std::string retrievedNs = XmpProperties::ns(testPrefix);
  EXPECT_EQ(testNs, retrievedNs);

  std::string retrievedPrefix = XmpProperties::prefix(testNs);
  EXPECT_EQ(testPrefix, retrievedPrefix);

  XmpProperties::unregisterNs(testNs);
}

TEST_F(XmpPropertiesTest_1251, UnregisterNs_RegisteredNamespace_RemovesIt_1251) {
  const std::string testNs = "http://example.com/test/unregister1251/";
  const std::string testPrefix = "unreg1251";

  XmpProperties::registerNs(testNs, testPrefix);
  std::string retrievedNs = XmpProperties::ns(testPrefix);
  EXPECT_EQ(testNs, retrievedNs);

  XmpProperties::unregisterNs(testNs);

  // After unregistering, the prefix should no longer resolve to the namespace
  // (it may throw or return empty)
  std::string prefixAfter = XmpProperties::prefix(testNs);
  EXPECT_TRUE(prefixAfter.empty());
}

TEST_F(XmpPropertiesTest_1251, UnregisterNsAll_ClearsCustomNamespaces_1251) {
  const std::string testNs1 = "http://example.com/test/all1/";
  const std::string testPrefix1 = "all1test";
  const std::string testNs2 = "http://example.com/test/all2/";
  const std::string testPrefix2 = "all2test";

  XmpProperties::registerNs(testNs1, testPrefix1);
  XmpProperties::registerNs(testNs2, testPrefix2);

  XmpProperties::unregisterNs();

  // Custom namespaces should be gone
  std::string prefix1 = XmpProperties::prefix(testNs1);
  std::string prefix2 = XmpProperties::prefix(testNs2);
  EXPECT_TRUE(prefix1.empty());
  EXPECT_TRUE(prefix2.empty());

  // Built-in namespaces should still work
  std::string dcNs = XmpProperties::ns("dc");
  EXPECT_FALSE(dcNs.empty());
}

// ============================================================
// Tests for registeredNamespaces
// ============================================================

TEST_F(XmpPropertiesTest_1251, RegisteredNamespaces_ContainsBuiltInNamespaces_1251) {
  Exiv2::Dictionary nsDict;
  XmpProperties::registeredNamespaces(nsDict);

  // Should contain at least some built-in namespaces
  EXPECT_FALSE(nsDict.empty());
}

TEST_F(XmpPropertiesTest_1251, RegisteredNamespaces_AfterRegister_ContainsNew_1251) {
  const std::string testNs = "http://example.com/test/regdict1251/";
  const std::string testPrefix = "regdict1251";

  XmpProperties::registerNs(testNs, testPrefix);

  Exiv2::Dictionary nsDict;
  XmpProperties::registeredNamespaces(nsDict);

  // The custom namespace should appear in the dictionary
  bool found = false;
  for (const auto& entry : nsDict) {
    if (entry.first == testPrefix || entry.second == testNs) {
      found = true;
      break;
    }
  }
  EXPECT_TRUE(found);

  XmpProperties::unregisterNs(testNs);
}

// ============================================================
// Tests for lookupNsRegistry
// ============================================================

TEST_F(XmpPropertiesTest_1251, LookupNsRegistry_RegisteredPrefix_ReturnsNonNull_1251) {
  const std::string testNs = "http://example.com/test/lookup1251/";
  const std::string testPrefix = "lookup1251";

  XmpProperties::registerNs(testNs, testPrefix);

  XmpNsInfo::Prefix prefix(testPrefix);
  const XmpNsInfo* info = XmpProperties::lookupNsRegistry(prefix);
  EXPECT_NE(nullptr, info);

  XmpProperties::unregisterNs(testNs);
}

TEST_F(XmpPropertiesTest_1251, LookupNsRegistry_UnregisteredPrefix_ReturnsNull_1251) {
  XmpNsInfo::Prefix prefix("nonExistentCustomPrefix999");
  const XmpNsInfo* info = XmpProperties::lookupNsRegistry(prefix);
  EXPECT_EQ(nullptr, info);
}

// ============================================================
// Tests for printProperties
// ============================================================

TEST_F(XmpPropertiesTest_1251, PrintProperties_KnownPrefix_OutputsContent_1251) {
  std::ostringstream oss;
  XmpProperties::printProperties(oss, "dc");
  std::string output = oss.str();
  EXPECT_FALSE(output.empty());
}

// ============================================================
// Tests for printProperty
// ============================================================

TEST_F(XmpPropertiesTest_1251, PrintProperty_ValidKeyValue_OutputsContent_1251) {
  std::ostringstream oss;
  XmpTextValue value;
  value.read("Test value");
  XmpProperties::printProperty(oss, "Xmp.dc.subject", value);
  std::string output = oss.str();
  EXPECT_FALSE(output.empty());
}

// ============================================================
// Tests for XmpKey
// ============================================================

class XmpKeyTest_1251 : public ::testing::Test {};

TEST_F(XmpKeyTest_1251, ConstructFromString_ValidKey_ParsesCorrectly_1251) {
  XmpKey key("Xmp.dc.subject");
  EXPECT_EQ("Xmp.dc.subject", key.key());
  EXPECT_STREQ("Xmp", key.familyName());
  EXPECT_EQ("dc", key.groupName());
  EXPECT_EQ("subject", key.tagName());
}

TEST_F(XmpKeyTest_1251, ConstructFromPrefixAndProperty_ValidArgs_ParsesCorrectly_1251) {
  XmpKey key("dc", "title");
  EXPECT_EQ("Xmp.dc.title", key.key());
  EXPECT_STREQ("Xmp", key.familyName());
  EXPECT_EQ("dc", key.groupName());
  EXPECT_EQ("title", key.tagName());
}

TEST_F(XmpKeyTest_1251, CopyConstructor_ProducesEqualKey_1251) {
  XmpKey original("Xmp.dc.subject");
  XmpKey copy(original);
  EXPECT_EQ(original.key(), copy.key());
  EXPECT_EQ(original.groupName(), copy.groupName());
  EXPECT_EQ(original.tagName(), copy.tagName());
}

TEST_F(XmpKeyTest_1251, AssignmentOperator_ProducesEqualKey_1251) {
  XmpKey key1("Xmp.dc.subject");
  XmpKey key2("Xmp.dc.title");
  key2 = key1;
  EXPECT_EQ(key1.key(), key2.key());
}

TEST_F(XmpKeyTest_1251, Clone_ProducesEqualKey_1251) {
  XmpKey original("Xmp.dc.subject");
  auto cloned = original.clone();
  ASSERT_NE(nullptr, cloned);
  EXPECT_EQ(original.key(), cloned->key());
}

TEST_F(XmpKeyTest_1251, TagLabel_KnownProperty_ReturnsNonEmpty_1251) {
  XmpKey key("Xmp.dc.subject");
  std::string label = key.tagLabel();
  EXPECT_FALSE(label.empty());
}

TEST_F(XmpKeyTest_1251, TagDesc_KnownProperty_ReturnsNonEmpty_1251) {
  XmpKey key("Xmp.dc.subject");
  std::string desc = key.tagDesc();
  EXPECT_FALSE(desc.empty());
}

TEST_F(XmpKeyTest_1251, Ns_KnownProperty_ReturnsNonEmpty_1251) {
  XmpKey key("Xmp.dc.subject");
  std::string ns = key.ns();
  EXPECT_FALSE(ns.empty());
}

TEST_F(XmpKeyTest_1251, FamilyName_AlwaysReturnsXmp_1251) {
  XmpKey key("Xmp.xmp.Rating");
  EXPECT_STREQ("Xmp", key.familyName());
}

TEST_F(XmpKeyTest_1251, Tag_ReturnsValue_1251) {
  XmpKey key("Xmp.dc.subject");
  // tag() should return some value without crashing
  uint16_t tag = key.tag();
  (void)tag;  // Just verify it doesn't crash
  SUCCEED();
}

// ============================================================
// Tests for propertyType with different known schemas
// ============================================================

TEST_F(XmpPropertiesTest_1251, PropertyType_TiffImageWidth_ReturnsExpectedType_1251) {
  XmpKey key("Xmp.tiff.ImageWidth");
  TypeId type = XmpProperties::propertyType(key);
  // Should return a valid type
  EXPECT_NE(invalidTypeId, type);
}

TEST_F(XmpPropertiesTest_1251, PropertyType_ExifDateTimeOriginal_ReturnsExpectedType_1251) {
  XmpKey key("Xmp.exif.DateTimeOriginal");
  TypeId type = XmpProperties::propertyType(key);
  EXPECT_NE(invalidTypeId, type);
}

TEST_F(XmpPropertiesTest_1251, PropertyType_DcFormat_ReturnsXmpText_1251) {
  XmpKey key("Xmp.dc.format");
  TypeId type = XmpProperties::propertyType(key);
  // dc:format is a simple text property
  EXPECT_EQ(xmpText, type);
}

TEST_F(XmpPropertiesTest_1251, PropertyType_DcRights_ReturnsLangAlt_1251) {
  XmpKey key("Xmp.dc.rights");
  TypeId type = XmpProperties::propertyType(key);
  EXPECT_EQ(langAlt, type);
}

// ============================================================
// Edge case: register namespace then use XmpKey with it
// ============================================================

TEST_F(XmpPropertiesTest_1251, RegisterNs_ThenCreateKey_PropertyTypeIsXmpText_1251) {
  const std::string testNs = "http://example.com/test/custom1251/";
  const std::string testPrefix = "custom1251";

  XmpProperties::registerNs(testNs, testPrefix);

  XmpKey key("Xmp.custom1251.someProperty");
  TypeId type = XmpProperties::propertyType(key);
  // Unknown property in custom namespace should default to xmpText
  EXPECT_EQ(xmpText, type);

  XmpProperties::unregisterNs(testNs);
}

}  // namespace
