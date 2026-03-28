#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "exiv2/properties.hpp"
#include "exiv2/value.hpp"

using namespace Exiv2;

// Test fixture for XmpProperties and XmpKey tests
class XmpPropertiesTest_1265 : public ::testing::Test {
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

// ==================== XmpKey Construction Tests ====================

TEST_F(XmpPropertiesTest_1265, XmpKeyConstructFromString_1265) {
  ASSERT_NO_THROW(XmpKey key("Xmp.dc.title"));
  XmpKey key("Xmp.dc.title");
  EXPECT_EQ(key.key(), "Xmp.dc.title");
}

TEST_F(XmpPropertiesTest_1265, XmpKeyConstructFromPrefixAndProperty_1265) {
  ASSERT_NO_THROW(XmpKey key("dc", "title"));
  XmpKey key("dc", "title");
  EXPECT_EQ(key.key(), "Xmp.dc.title");
}

TEST_F(XmpPropertiesTest_1265, XmpKeyCopyConstructor_1265) {
  XmpKey key1("Xmp.dc.title");
  XmpKey key2(key1);
  EXPECT_EQ(key1.key(), key2.key());
  EXPECT_EQ(key1.tagName(), key2.tagName());
  EXPECT_EQ(key1.groupName(), key2.groupName());
}

TEST_F(XmpPropertiesTest_1265, XmpKeyAssignmentOperator_1265) {
  XmpKey key1("Xmp.dc.title");
  XmpKey key2("Xmp.dc.description");
  key2 = key1;
  EXPECT_EQ(key1.key(), key2.key());
  EXPECT_EQ(key1.tagName(), key2.tagName());
}

TEST_F(XmpPropertiesTest_1265, XmpKeyClone_1265) {
  XmpKey key("Xmp.dc.title");
  auto cloned = key.clone();
  ASSERT_NE(cloned, nullptr);
  EXPECT_EQ(key.key(), cloned->key());
  EXPECT_EQ(key.tagName(), cloned->tagName());
}

// ==================== XmpKey Accessors Tests ====================

TEST_F(XmpPropertiesTest_1265, XmpKeyFamilyName_1265) {
  XmpKey key("Xmp.dc.title");
  EXPECT_STREQ(key.familyName(), "Xmp");
}

TEST_F(XmpPropertiesTest_1265, XmpKeyGroupName_1265) {
  XmpKey key("Xmp.dc.title");
  EXPECT_EQ(key.groupName(), "dc");
}

TEST_F(XmpPropertiesTest_1265, XmpKeyTagName_1265) {
  XmpKey key("Xmp.dc.title");
  EXPECT_EQ(key.tagName(), "title");
}

TEST_F(XmpPropertiesTest_1265, XmpKeyTagLabel_1265) {
  XmpKey key("Xmp.dc.title");
  std::string label = key.tagLabel();
  // tagLabel should return either the property title or the tag name
  EXPECT_FALSE(label.empty());
}

TEST_F(XmpPropertiesTest_1265, XmpKeyTagDesc_1265) {
  XmpKey key("Xmp.dc.title");
  std::string desc = key.tagDesc();
  // Description can be empty or non-empty
  // Just verify it doesn't throw
}

TEST_F(XmpPropertiesTest_1265, XmpKeyTag_1265) {
  XmpKey key("Xmp.dc.title");
  // tag() returns a uint16_t; just verify it doesn't throw
  uint16_t tag = key.tag();
  (void)tag;
}

TEST_F(XmpPropertiesTest_1265, XmpKeyNs_1265) {
  XmpKey key("Xmp.dc.title");
  std::string ns = key.ns();
  EXPECT_FALSE(ns.empty());
  // dc namespace should be the Dublin Core namespace
  EXPECT_EQ(ns, "http://purl.org/dc/elements/1.1/");
}

// ==================== XmpKey with different standard prefixes ====================

TEST_F(XmpPropertiesTest_1265, XmpKeyXmpPrefix_1265) {
  XmpKey key("Xmp.xmp.CreateDate");
  EXPECT_EQ(key.groupName(), "xmp");
  EXPECT_EQ(key.tagName(), "CreateDate");
}

TEST_F(XmpPropertiesTest_1265, XmpKeyExifPrefix_1265) {
  XmpKey key("Xmp.exif.DateTimeOriginal");
  EXPECT_EQ(key.groupName(), "exif");
  EXPECT_EQ(key.tagName(), "DateTimeOriginal");
}

TEST_F(XmpPropertiesTest_1265, XmpKeyTiffPrefix_1265) {
  XmpKey key("Xmp.tiff.Orientation");
  EXPECT_EQ(key.groupName(), "tiff");
  EXPECT_EQ(key.tagName(), "Orientation");
}

// ==================== XmpProperties Static Methods Tests ====================

TEST_F(XmpPropertiesTest_1265, PropertyTitleKnownProperty_1265) {
  XmpKey key("Xmp.dc.title");
  const char* title = XmpProperties::propertyTitle(key);
  // Known property should have a title
  if (title) {
    EXPECT_GT(strlen(title), 0u);
  }
}

TEST_F(XmpPropertiesTest_1265, PropertyDescKnownProperty_1265) {
  XmpKey key("Xmp.dc.title");
  const char* desc = XmpProperties::propertyDesc(key);
  // May return nullptr or a valid string
  if (desc) {
    EXPECT_GT(strlen(desc), 0u);
  }
}

TEST_F(XmpPropertiesTest_1265, PropertyTypeKnownProperty_1265) {
  XmpKey key("Xmp.dc.title");
  TypeId type = XmpProperties::propertyType(key);
  // Should return a valid type
  EXPECT_NE(type, invalidTypeId);
}

TEST_F(XmpPropertiesTest_1265, PropertyInfoKnownProperty_1265) {
  XmpKey key("Xmp.dc.title");
  const XmpPropertyInfo* info = XmpProperties::propertyInfo(key);
  // Known property should have info
  EXPECT_NE(info, nullptr);
}

TEST_F(XmpPropertiesTest_1265, NsForKnownPrefix_1265) {
  std::string ns = XmpProperties::ns("dc");
  EXPECT_FALSE(ns.empty());
  EXPECT_EQ(ns, "http://purl.org/dc/elements/1.1/");
}

TEST_F(XmpPropertiesTest_1265, PrefixForKnownNs_1265) {
  std::string prefix = XmpProperties::prefix("http://purl.org/dc/elements/1.1/");
  EXPECT_EQ(prefix, "dc");
}

TEST_F(XmpPropertiesTest_1265, NsDescForKnownPrefix_1265) {
  const char* desc = XmpProperties::nsDesc("dc");
  EXPECT_NE(desc, nullptr);
  EXPECT_GT(strlen(desc), 0u);
}

TEST_F(XmpPropertiesTest_1265, PropertyListForKnownPrefix_1265) {
  const XmpPropertyInfo* list = XmpProperties::propertyList("dc");
  EXPECT_NE(list, nullptr);
}

TEST_F(XmpPropertiesTest_1265, NsInfoForKnownPrefix_1265) {
  const XmpNsInfo* info = XmpProperties::nsInfo("dc");
  EXPECT_NE(info, nullptr);
}

// ==================== Namespace Registration Tests ====================

TEST_F(XmpPropertiesTest_1265, RegisterAndLookupCustomNamespace_1265) {
  const std::string customNs = "http://example.com/custom/1.0/";
  const std::string customPrefix = "customtest";

  XmpProperties::registerNs(customNs, customPrefix);

  std::string resultPrefix = XmpProperties::prefix(customNs);
  EXPECT_EQ(resultPrefix, customPrefix);

  std::string resultNs = XmpProperties::ns(customPrefix);
  EXPECT_EQ(resultNs, customNs);

  // Clean up
  XmpProperties::unregisterNs(customNs);
}

TEST_F(XmpPropertiesTest_1265, UnregisterCustomNamespace_1265) {
  const std::string customNs = "http://example.com/unreg/1.0/";
  const std::string customPrefix = "unregtest";

  XmpProperties::registerNs(customNs, customPrefix);
  std::string resultPrefix = XmpProperties::prefix(customNs);
  EXPECT_EQ(resultPrefix, customPrefix);

  XmpProperties::unregisterNs(customNs);

  // After unregistering, prefix lookup should return empty or throw
  std::string afterPrefix = XmpProperties::prefix(customNs);
  EXPECT_TRUE(afterPrefix.empty());
}

TEST_F(XmpPropertiesTest_1265, UnregisterAllCustomNamespaces_1265) {
  const std::string customNs1 = "http://example.com/all1/1.0/";
  const std::string customPrefix1 = "alltest1";
  const std::string customNs2 = "http://example.com/all2/1.0/";
  const std::string customPrefix2 = "alltest2";

  XmpProperties::registerNs(customNs1, customPrefix1);
  XmpProperties::registerNs(customNs2, customPrefix2);

  XmpProperties::unregisterNs();

  // Custom namespaces should be gone
  EXPECT_TRUE(XmpProperties::prefix(customNs1).empty());
  EXPECT_TRUE(XmpProperties::prefix(customNs2).empty());

  // Built-in namespaces should still work
  EXPECT_EQ(XmpProperties::prefix("http://purl.org/dc/elements/1.1/"), "dc");
}

TEST_F(XmpPropertiesTest_1265, RegisteredNamespaces_1265) {
  Dictionary nsDict;
  XmpProperties::registeredNamespaces(nsDict);
  // Should contain at least the built-in namespaces
  EXPECT_FALSE(nsDict.empty());
}

TEST_F(XmpPropertiesTest_1265, RegisteredNamespacesIncludesCustom_1265) {
  const std::string customNs = "http://example.com/regdict/1.0/";
  const std::string customPrefix = "regdicttest";

  XmpProperties::registerNs(customNs, customPrefix);

  Dictionary nsDict;
  XmpProperties::registeredNamespaces(nsDict);

  // The custom namespace should be in the dictionary
  bool found = false;
  for (const auto& entry : nsDict) {
    if (entry.first == customPrefix || entry.second == customNs ||
        entry.first == customNs || entry.second == customPrefix) {
      found = true;
      break;
    }
  }
  EXPECT_TRUE(found);

  XmpProperties::unregisterNs(customNs);
}

// ==================== LookupNsRegistry Tests ====================

TEST_F(XmpPropertiesTest_1265, LookupNsRegistryForRegisteredPrefix_1265) {
  const std::string customNs = "http://example.com/lookup/1.0/";
  const std::string customPrefix = "lookuptest";

  XmpProperties::registerNs(customNs, customPrefix);

  XmpNsInfo::Prefix prefixStruct;
  prefixStruct.prefix_ = customPrefix.c_str();
  const XmpNsInfo* info = XmpProperties::lookupNsRegistry(prefixStruct);
  EXPECT_NE(info, nullptr);

  XmpProperties::unregisterNs(customNs);
}

TEST_F(XmpPropertiesTest_1265, LookupNsRegistryForUnregisteredPrefix_1265) {
  XmpNsInfo::Prefix prefixStruct;
  prefixStruct.prefix_ = "nonexistentprefix";
  const XmpNsInfo* info = XmpProperties::lookupNsRegistry(prefixStruct);
  EXPECT_EQ(info, nullptr);
}

// ==================== Print Tests ====================

TEST_F(XmpPropertiesTest_1265, PrintPropertiesKnownPrefix_1265) {
  std::ostringstream os;
  ASSERT_NO_THROW(XmpProperties::printProperties(os, "dc"));
  std::string output = os.str();
  // Should produce some output for known prefix
  EXPECT_FALSE(output.empty());
}

TEST_F(XmpPropertiesTest_1265, PrintPropertyKnownKey_1265) {
  std::ostringstream os;
  XmpTextValue value("Test Value");
  ASSERT_NO_THROW(XmpProperties::printProperty(os, "Xmp.dc.title", value));
  // printProperty returns ostream reference, verify it doesn't crash
}

// ==================== Error Cases ====================

TEST_F(XmpPropertiesTest_1265, XmpKeyInvalidKeyStringThrows_1265) {
  // Invalid key format should throw
  EXPECT_THROW(XmpKey key("invalid"), Error);
}

TEST_F(XmpPropertiesTest_1265, XmpKeyUnknownPrefixThrows_1265) {
  // Unknown prefix should throw
  EXPECT_THROW(XmpKey key("Xmp.unknownprefix12345.property"), Error);
}

TEST_F(XmpPropertiesTest_1265, NsForUnknownPrefix_1265) {
  // Unknown prefix should return empty or throw
  try {
    std::string ns = XmpProperties::ns("totallyunknownprefix");
    // If it doesn't throw, it should be empty
    EXPECT_TRUE(ns.empty());
  } catch (const Error&) {
    // Throwing is also acceptable behavior
    SUCCEED();
  }
}

// ==================== XmpKey with Custom Namespace ====================

TEST_F(XmpPropertiesTest_1265, XmpKeyWithCustomNamespace_1265) {
  const std::string customNs = "http://example.com/xmpkeytest/1.0/";
  const std::string customPrefix = "xmpkeytest";

  XmpProperties::registerNs(customNs, customPrefix);

  XmpKey key(customPrefix, "myProperty");
  EXPECT_EQ(key.key(), "Xmp." + customPrefix + ".myProperty");
  EXPECT_EQ(key.groupName(), customPrefix);
  EXPECT_EQ(key.tagName(), "myProperty");
  EXPECT_STREQ(key.familyName(), "Xmp");
  EXPECT_EQ(key.ns(), customNs);

  XmpProperties::unregisterNs(customNs);
}

TEST_F(XmpPropertiesTest_1265, XmpKeyTagLabelForUnknownPropertyReturnTagName_1265) {
  const std::string customNs = "http://example.com/labeltst/1.0/";
  const std::string customPrefix = "labeltst";

  XmpProperties::registerNs(customNs, customPrefix);

  XmpKey key(customPrefix, "unknownProp");
  std::string label = key.tagLabel();
  // For unknown properties, tagLabel should fall back to tagName
  EXPECT_EQ(label, "unknownProp");

  XmpProperties::unregisterNs(customNs);
}

TEST_F(XmpPropertiesTest_1265, PropertyInfoForUnknownProperty_1265) {
  const std::string customNs = "http://example.com/propinfo/1.0/";
  const std::string customPrefix = "propinfo";

  XmpProperties::registerNs(customNs, customPrefix);

  XmpKey key(customPrefix, "nonexistentProperty");
  const XmpPropertyInfo* info = XmpProperties::propertyInfo(key);
  EXPECT_EQ(info, nullptr);

  XmpProperties::unregisterNs(customNs);
}

TEST_F(XmpPropertiesTest_1265, PropertyTitleForUnknownProperty_1265) {
  const std::string customNs = "http://example.com/proptitle/1.0/";
  const std::string customPrefix = "proptitle";

  XmpProperties::registerNs(customNs, customPrefix);

  XmpKey key(customPrefix, "noSuchProp");
  const char* title = XmpProperties::propertyTitle(key);
  // For unknown properties, should return nullptr
  EXPECT_EQ(title, nullptr);

  XmpProperties::unregisterNs(customNs);
}

// ==================== Multiple Registrations ====================

TEST_F(XmpPropertiesTest_1265, ReRegisterSameNamespace_1265) {
  const std::string customNs = "http://example.com/rereg/1.0/";
  const std::string customPrefix = "rereg";

  XmpProperties::registerNs(customNs, customPrefix);
  // Re-registering with the same prefix should not cause issues
  ASSERT_NO_THROW(XmpProperties::registerNs(customNs, customPrefix));

  std::string resultPrefix = XmpProperties::prefix(customNs);
  EXPECT_EQ(resultPrefix, customPrefix);

  XmpProperties::unregisterNs(customNs);
}

// ==================== Standard namespace properties ====================

TEST_F(XmpPropertiesTest_1265, DcSubjectProperty_1265) {
  XmpKey key("Xmp.dc.subject");
  EXPECT_EQ(key.groupName(), "dc");
  EXPECT_EQ(key.tagName(), "subject");
  const XmpPropertyInfo* info = XmpProperties::propertyInfo(key);
  EXPECT_NE(info, nullptr);
}

TEST_F(XmpPropertiesTest_1265, DcDescriptionProperty_1265) {
  XmpKey key("Xmp.dc.description");
  EXPECT_EQ(key.tagName(), "description");
  const char* title = XmpProperties::propertyTitle(key);
  EXPECT_NE(title, nullptr);
}

TEST_F(XmpPropertiesTest_1265, PropertyListForUnknownPrefix_1265) {
  const XmpPropertyInfo* list = XmpProperties::propertyList("nonexistent_prefix_xyz");
  EXPECT_EQ(list, nullptr);
}

TEST_F(XmpPropertiesTest_1265, NsInfoForUnknownPrefix_1265) {
  try {
    const XmpNsInfo* info = XmpProperties::nsInfo("nonexistent_prefix_xyz");
    EXPECT_EQ(info, nullptr);
  } catch (const Error&) {
    // Throwing is also acceptable
    SUCCEED();
  }
}
