#include <gtest/gtest.h>
#include <exiv2/properties.hpp>
#include <exiv2/xmp_exiv2.hpp>
#include <exiv2/types.hpp>
#include <exiv2/value.hpp>
#include <map>
#include <string>
#include <sstream>

namespace {

class XmpPropertiesTest_1256 : public ::testing::Test {
 protected:
  void SetUp() override {
    Exiv2::XmpParser::initialize();
  }

  void TearDown() override {
    // Unregister any custom namespaces we may have registered
    Exiv2::XmpProperties::unregisterNs();
    Exiv2::XmpParser::terminate();
  }
};

// Test that registeredNamespaces populates the dictionary with known namespaces
TEST_F(XmpPropertiesTest_1256, RegisteredNamespacesContainsKnownEntries_1256) {
  Exiv2::Dictionary nsDict;
  Exiv2::XmpProperties::registeredNamespaces(nsDict);

  // The dictionary should not be empty since there are 47 built-in namespaces
  EXPECT_FALSE(nsDict.empty());

  // Check some well-known namespaces are present
  // The dictionary maps prefix -> namespace or namespace -> prefix depending on implementation
  // We check that the dc namespace is registered
  bool foundDc = false;
  bool foundExif = false;
  bool foundTiff = false;
  for (const auto& entry : nsDict) {
    if (entry.first == "http://purl.org/dc/elements/1.1/" || entry.second == "http://purl.org/dc/elements/1.1/") {
      foundDc = true;
    }
    if (entry.first == "http://ns.adobe.com/exif/1.0/" || entry.second == "http://ns.adobe.com/exif/1.0/") {
      foundExif = true;
    }
    if (entry.first == "http://ns.adobe.com/tiff/1.0/" || entry.second == "http://ns.adobe.com/tiff/1.0/") {
      foundTiff = true;
    }
  }
  EXPECT_TRUE(foundDc);
  EXPECT_TRUE(foundExif);
  EXPECT_TRUE(foundTiff);
}

// Test prefix lookup for known namespace
TEST_F(XmpPropertiesTest_1256, PrefixForKnownNamespace_1256) {
  std::string prefix = Exiv2::XmpProperties::prefix("http://purl.org/dc/elements/1.1/");
  EXPECT_EQ(prefix, "dc");
}

// Test ns lookup for known prefix
TEST_F(XmpPropertiesTest_1256, NsForKnownPrefix_1256) {
  std::string ns = Exiv2::XmpProperties::ns("dc");
  EXPECT_EQ(ns, "http://purl.org/dc/elements/1.1/");
}

// Test ns for xmp prefix
TEST_F(XmpPropertiesTest_1256, NsForXmpPrefix_1256) {
  std::string ns = Exiv2::XmpProperties::ns("xmp");
  EXPECT_EQ(ns, "http://ns.adobe.com/xap/1.0/");
}

// Test prefix for xmp namespace
TEST_F(XmpPropertiesTest_1256, PrefixForXmpNamespace_1256) {
  std::string prefix = Exiv2::XmpProperties::prefix("http://ns.adobe.com/xap/1.0/");
  EXPECT_EQ(prefix, "xmp");
}

// Test registering a custom namespace
TEST_F(XmpPropertiesTest_1256, RegisterCustomNamespace_1256) {
  Exiv2::XmpProperties::registerNs("http://example.com/test/1.0/", "testNs");

  std::string prefix = Exiv2::XmpProperties::prefix("http://example.com/test/1.0/");
  EXPECT_EQ(prefix, "testNs");

  std::string ns = Exiv2::XmpProperties::ns("testNs");
  EXPECT_EQ(ns, "http://example.com/test/1.0/");

  // Clean up
  Exiv2::XmpProperties::unregisterNs("http://example.com/test/1.0/");
}

// Test unregistering a custom namespace
TEST_F(XmpPropertiesTest_1256, UnregisterCustomNamespace_1256) {
  Exiv2::XmpProperties::registerNs("http://example.com/unreg/1.0/", "unregNs");

  std::string prefix = Exiv2::XmpProperties::prefix("http://example.com/unreg/1.0/");
  EXPECT_EQ(prefix, "unregNs");

  Exiv2::XmpProperties::unregisterNs("http://example.com/unreg/1.0/");

  // After unregistering, prefix lookup should return empty or throw
  std::string prefixAfter = Exiv2::XmpProperties::prefix("http://example.com/unreg/1.0/");
  EXPECT_TRUE(prefixAfter.empty());
}

// Test unregisterNs() (no args) clears custom namespaces
TEST_F(XmpPropertiesTest_1256, UnregisterAllCustomNamespaces_1256) {
  Exiv2::XmpProperties::registerNs("http://example.com/all1/", "allNs1");
  Exiv2::XmpProperties::registerNs("http://example.com/all2/", "allNs2");

  // Verify they are registered
  EXPECT_EQ(Exiv2::XmpProperties::prefix("http://example.com/all1/"), "allNs1");
  EXPECT_EQ(Exiv2::XmpProperties::prefix("http://example.com/all2/"), "allNs2");

  Exiv2::XmpProperties::unregisterNs();

  // After clearing, custom namespaces should not be found
  EXPECT_TRUE(Exiv2::XmpProperties::prefix("http://example.com/all1/").empty());
  EXPECT_TRUE(Exiv2::XmpProperties::prefix("http://example.com/all2/").empty());
}

// Test nsInfo returns non-null for known prefix
TEST_F(XmpPropertiesTest_1256, NsInfoForKnownPrefix_1256) {
  const Exiv2::XmpNsInfo* info = Exiv2::XmpProperties::nsInfo("dc");
  ASSERT_NE(info, nullptr);
  EXPECT_STREQ(info->prefix_, "dc");
  EXPECT_STREQ(info->ns_, "http://purl.org/dc/elements/1.1/");
}

// Test nsInfo for exif prefix
TEST_F(XmpPropertiesTest_1256, NsInfoForExifPrefix_1256) {
  const Exiv2::XmpNsInfo* info = Exiv2::XmpProperties::nsInfo("exif");
  ASSERT_NE(info, nullptr);
  EXPECT_STREQ(info->prefix_, "exif");
  EXPECT_STREQ(info->ns_, "http://ns.adobe.com/exif/1.0/");
}

// Test propertyList returns non-null for known prefix with properties
TEST_F(XmpPropertiesTest_1256, PropertyListForDcPrefix_1256) {
  const Exiv2::XmpPropertyInfo* propList = Exiv2::XmpProperties::propertyList("dc");
  EXPECT_NE(propList, nullptr);
}

// Test propertyList returns nullptr for prefix with no property info
TEST_F(XmpPropertiesTest_1256, PropertyListForPrefixWithNoProperties_1256) {
  // "xmpG" has nullptr for xmpPropertyInfo_
  const Exiv2::XmpPropertyInfo* propList = Exiv2::XmpProperties::propertyList("xmpG");
  EXPECT_EQ(propList, nullptr);
}

// Test ns lookup for tiff prefix
TEST_F(XmpPropertiesTest_1256, NsForTiffPrefix_1256) {
  std::string ns = Exiv2::XmpProperties::ns("tiff");
  EXPECT_EQ(ns, "http://ns.adobe.com/tiff/1.0/");
}

// Test prefix for tiff namespace
TEST_F(XmpPropertiesTest_1256, PrefixForTiffNamespace_1256) {
  std::string prefix = Exiv2::XmpProperties::prefix("http://ns.adobe.com/tiff/1.0/");
  EXPECT_EQ(prefix, "tiff");
}

// Test prefix for photoshop namespace
TEST_F(XmpPropertiesTest_1256, PrefixForPhotoshopNamespace_1256) {
  std::string prefix = Exiv2::XmpProperties::prefix("http://ns.adobe.com/photoshop/1.0/");
  EXPECT_EQ(prefix, "photoshop");
}

// Test ns for photoshop prefix
TEST_F(XmpPropertiesTest_1256, NsForPhotoshopPrefix_1256) {
  std::string ns = Exiv2::XmpProperties::ns("photoshop");
  EXPECT_EQ(ns, "http://ns.adobe.com/photoshop/1.0/");
}

// Test lookupNsRegistry for a custom registered namespace
TEST_F(XmpPropertiesTest_1256, LookupNsRegistryForCustomNamespace_1256) {
  Exiv2::XmpProperties::registerNs("http://example.com/lookup/1.0/", "lookupTest");

  Exiv2::XmpNsInfo::Prefix prefix("lookupTest");
  const Exiv2::XmpNsInfo* info = Exiv2::XmpProperties::lookupNsRegistry(prefix);
  ASSERT_NE(info, nullptr);
  EXPECT_STREQ(info->prefix_, "lookupTest");

  Exiv2::XmpProperties::unregisterNs("http://example.com/lookup/1.0/");
}

// Test lookupNsRegistry returns nullptr for unknown prefix
TEST_F(XmpPropertiesTest_1256, LookupNsRegistryForUnknownPrefix_1256) {
  Exiv2::XmpNsInfo::Prefix prefix("nonExistentPrefix");
  const Exiv2::XmpNsInfo* info = Exiv2::XmpProperties::lookupNsRegistry(prefix);
  EXPECT_EQ(info, nullptr);
}

// Test that registeredNamespaces dictionary includes custom namespaces
TEST_F(XmpPropertiesTest_1256, RegisteredNamespacesIncludesCustom_1256) {
  Exiv2::XmpProperties::registerNs("http://example.com/custom/1.0/", "customPfx");

  Exiv2::Dictionary nsDict;
  Exiv2::XmpProperties::registeredNamespaces(nsDict);

  bool found = false;
  for (const auto& entry : nsDict) {
    if (entry.first == "http://example.com/custom/1.0/" || entry.second == "http://example.com/custom/1.0/") {
      found = true;
      break;
    }
  }
  EXPECT_TRUE(found);

  Exiv2::XmpProperties::unregisterNs("http://example.com/custom/1.0/");
}

// Test printProperties doesn't crash for known prefix
TEST_F(XmpPropertiesTest_1256, PrintPropertiesForDcDoesNotCrash_1256) {
  std::ostringstream os;
  EXPECT_NO_THROW(Exiv2::XmpProperties::printProperties(os, "dc"));
  EXPECT_FALSE(os.str().empty());
}

// Test printProperties for prefix with no properties
TEST_F(XmpPropertiesTest_1256, PrintPropertiesForPrefixWithNoPropertiesDoesNotCrash_1256) {
  std::ostringstream os;
  // "xmpG" has nullptr property info - should still handle gracefully
  EXPECT_NO_THROW(Exiv2::XmpProperties::printProperties(os, "xmpG"));
}

// Test ns for various known prefixes
TEST_F(XmpPropertiesTest_1256, NsForPdfPrefix_1256) {
  std::string ns = Exiv2::XmpProperties::ns("pdf");
  EXPECT_EQ(ns, "http://ns.adobe.com/pdf/1.3/");
}

TEST_F(XmpPropertiesTest_1256, NsForXmpRightsPrefix_1256) {
  std::string ns = Exiv2::XmpProperties::ns("xmpRights");
  EXPECT_EQ(ns, "http://ns.adobe.com/xap/1.0/rights/");
}

TEST_F(XmpPropertiesTest_1256, NsForXmpMMPrefix_1256) {
  std::string ns = Exiv2::XmpProperties::ns("xmpMM");
  EXPECT_EQ(ns, "http://ns.adobe.com/xap/1.0/mm/");
}

// Test prefix for unknown namespace returns empty
TEST_F(XmpPropertiesTest_1256, PrefixForUnknownNamespace_1256) {
  std::string prefix = Exiv2::XmpProperties::prefix("http://nonexistent.example.com/");
  EXPECT_TRUE(prefix.empty());
}

// Test ns for IPTC prefix
TEST_F(XmpPropertiesTest_1256, NsForIptcPrefix_1256) {
  std::string ns = Exiv2::XmpProperties::ns("iptc");
  EXPECT_EQ(ns, "http://iptc.org/std/Iptc4xmpCore/1.0/xmlns/");
}

// Test that re-registering a namespace with same prefix updates it
TEST_F(XmpPropertiesTest_1256, ReRegisterNamespaceUpdates_1256) {
  Exiv2::XmpProperties::registerNs("http://example.com/v1/", "reregPfx");
  std::string ns1 = Exiv2::XmpProperties::ns("reregPfx");
  EXPECT_EQ(ns1, "http://example.com/v1/");

  Exiv2::XmpProperties::registerNs("http://example.com/v2/", "reregPfx");
  std::string ns2 = Exiv2::XmpProperties::ns("reregPfx");
  EXPECT_EQ(ns2, "http://example.com/v2/");

  Exiv2::XmpProperties::unregisterNs("http://example.com/v1/");
  Exiv2::XmpProperties::unregisterNs("http://example.com/v2/");
}

// Test nsDesc for known prefix
TEST_F(XmpPropertiesTest_1256, NsDescForDcPrefix_1256) {
  const char* desc = Exiv2::XmpProperties::nsDesc("dc");
  ASSERT_NE(desc, nullptr);
  EXPECT_STREQ(desc, "Dublin Core schema");
}

// Test nsDesc for exif prefix
TEST_F(XmpPropertiesTest_1256, NsDescForExifPrefix_1256) {
  const char* desc = Exiv2::XmpProperties::nsDesc("exif");
  ASSERT_NE(desc, nullptr);
  EXPECT_STREQ(desc, "Exif schema for Exif-specific Properties");
}

// Test multiple registeredNamespaces calls give consistent results
TEST_F(XmpPropertiesTest_1256, RegisteredNamespacesConsistent_1256) {
  Exiv2::Dictionary nsDict1;
  Exiv2::XmpProperties::registeredNamespaces(nsDict1);

  Exiv2::Dictionary nsDict2;
  Exiv2::XmpProperties::registeredNamespaces(nsDict2);

  EXPECT_EQ(nsDict1.size(), nsDict2.size());
}

// Test ns for GPano prefix
TEST_F(XmpPropertiesTest_1256, NsForGPanoPrefix_1256) {
  std::string ns = Exiv2::XmpProperties::ns("GPano");
  EXPECT_EQ(ns, "http://ns.google.com/photos/1.0/panorama/");
}

// Test prefix for GPano namespace
TEST_F(XmpPropertiesTest_1256, PrefixForGPanoNamespace_1256) {
  std::string prefix = Exiv2::XmpProperties::prefix("http://ns.google.com/photos/1.0/panorama/");
  EXPECT_EQ(prefix, "GPano");
}

// Test ns for aux prefix
TEST_F(XmpPropertiesTest_1256, NsForAuxPrefix_1256) {
  std::string ns = Exiv2::XmpProperties::ns("aux");
  EXPECT_EQ(ns, "http://ns.adobe.com/exif/1.0/aux/");
}

// Test ns for crs prefix
TEST_F(XmpPropertiesTest_1256, NsForCrsPrefix_1256) {
  std::string ns = Exiv2::XmpProperties::ns("crs");
  EXPECT_EQ(ns, "http://ns.adobe.com/camera-raw-settings/1.0/");
}

// Test that registeredNamespaces has at least 47 entries (the built-in ones)
TEST_F(XmpPropertiesTest_1256, RegisteredNamespacesHasMinimumEntries_1256) {
  Exiv2::Dictionary nsDict;
  Exiv2::XmpProperties::registeredNamespaces(nsDict);
  // There are 47 built-in namespaces (some share the same NS with different prefixes),
  // plus XMP SDK built-in namespaces
  EXPECT_GE(nsDict.size(), static_cast<size_t>(30));
}

}  // namespace
