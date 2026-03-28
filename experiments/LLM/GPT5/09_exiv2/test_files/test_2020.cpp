// =================================================================================================
// Unit tests for WXMPMeta_DoesArrayItemExist_1
// File: ./TestProjects/exiv2/xmpsdk/src/WXMPMeta.cpp
// TEST_ID: 2020
// =================================================================================================

#include <gtest/gtest.h>

#include <cstring>
#include <string>

// XMP Toolkit headers (paths may vary in your tree; these are typical for xmpsdk in Exiv2 vendor layout).
#include "XMP_Const.h"
#include "XMPMeta.hpp"
#include "client-glue/WXMP_Common.hpp"

// The wrapper under test (C wrapper symbol).
extern "C" {
void WXMPMeta_DoesArrayItemExist_1(XMPMetaRef xmpRef,
                                  XMP_StringPtr schemaNS,
                                  XMP_StringPtr arrayName,
                                  XMP_Index itemIndex,
                                  WXMP_Result* wResult);
}

namespace {

class XMPToolkitGuard_2020 {
public:
  XMPToolkitGuard_2020() { (void)XMPMeta::Initialize(); }
  ~XMPToolkitGuard_2020() { XMPMeta::Terminate(); }
  XMPToolkitGuard_2020(const XMPToolkitGuard_2020&) = delete;
  XMPToolkitGuard_2020& operator=(const XMPToolkitGuard_2020&) = delete;
};

class WXMPMetaDoesArrayItemExist1Test_2020 : public ::testing::Test {
protected:
  static void SetUpTestSuite() { guard_ = new XMPToolkitGuard_2020(); }
  static void TearDownTestSuite() {
    delete guard_;
    guard_ = nullptr;
  }

  static XMPToolkitGuard_2020* guard_;

  static XMPMetaRef AsRef(XMPMeta& meta) {
    // In the XMP toolkit C API glue, XMPMetaRef is typically an opaque pointer to an XMPMeta instance.
    // Tests treat it as opaque and only pass it back to the wrapper.
    return reinterpret_cast<XMPMetaRef>(&meta);
  }

  static std::string MinimalXmpWithDcSubjectBag() {
    // A minimal XMP packet that includes dc:subject as an rdf:Bag with two items.
    return std::string(
        "<x:xmpmeta xmlns:x='adobe:ns:meta/'>"
        "<rdf:RDF xmlns:rdf='http://www.w3.org/1999/02/22-rdf-syntax-ns#'>"
        "<rdf:Description xmlns:dc='http://purl.org/dc/elements/1.1/'>"
        "<dc:subject>"
        "<rdf:Bag>"
        "<rdf:li>one</rdf:li>"
        "<rdf:li>two</rdf:li>"
        "</rdf:Bag>"
        "</dc:subject>"
        "</rdf:Description>"
        "</rdf:RDF>"
        "</x:xmpmeta>");
  }
};

XMPToolkitGuard_2020* WXMPMetaDoesArrayItemExist1Test_2020::guard_ = nullptr;

}  // namespace

// ------------------------- Normal operation -------------------------

TEST_F(WXMPMetaDoesArrayItemExist1Test_2020, ReturnsTrueForExistingItem_2020) {
  XMPMeta meta;
  const std::string xmp = MinimalXmpWithDcSubjectBag();
  meta.ParseFromBuffer(xmp.c_str(), static_cast<XMP_StringLen>(xmp.size()), 0);

  WXMP_Result result;
  WXMPMeta_DoesArrayItemExist_1(AsRef(meta),
                               "http://purl.org/dc/elements/1.1/",  // schemaNS
                               "subject",                           // arrayName
                               1,                                   // itemIndex (1-based in XMP)
                               &result);

  EXPECT_EQ(result.errMessage, nullptr);
  EXPECT_NE(result.int32Result, 0u);  // true
}

TEST_F(WXMPMetaDoesArrayItemExist1Test_2020, ReturnsFalseForNonExistingItem_2020) {
  XMPMeta meta;
  const std::string xmp = MinimalXmpWithDcSubjectBag();
  meta.ParseFromBuffer(xmp.c_str(), static_cast<XMP_StringLen>(xmp.size()), 0);

  WXMP_Result result;
  WXMPMeta_DoesArrayItemExist_1(AsRef(meta),
                               "http://purl.org/dc/elements/1.1/",
                               "subject",
                               3,  // beyond the 2 items in the rdf:Bag
                               &result);

  EXPECT_EQ(result.errMessage, nullptr);
  EXPECT_EQ(result.int32Result, 0u);  // false
}

TEST_F(WXMPMetaDoesArrayItemExist1Test_2020, ReturnsFalseForMissingArrayProperty_2020) {
  XMPMeta meta;  // empty metadata, no dc:subject
  WXMP_Result result;

  WXMPMeta_DoesArrayItemExist_1(AsRef(meta),
                               "http://purl.org/dc/elements/1.1/",
                               "subject",
                               1,
                               &result);

  // Observable behavior: should not crash; either false or an error is acceptable depending on toolkit behavior.
  // Prefer checking that a "missing array" does not necessarily produce an error.
  if (result.errMessage == nullptr) {
    EXPECT_EQ(result.int32Result, 0u);
  } else {
    // If the implementation treats missing array as an error, at least it should report it.
    EXPECT_NE(result.errMessage, nullptr);
  }
}

// ------------------------- Boundary / error cases -------------------------

TEST_F(WXMPMetaDoesArrayItemExist1Test_2020, NullSchemaNamespaceReportsError_2020) {
  XMPMeta meta;
  WXMP_Result result;

  WXMPMeta_DoesArrayItemExist_1(AsRef(meta),
                               nullptr,     // schemaNS
                               "subject",   // arrayName
                               1,           // itemIndex
                               &result);

  EXPECT_NE(result.errMessage, nullptr);
}

TEST_F(WXMPMetaDoesArrayItemExist1Test_2020, EmptySchemaNamespaceReportsError_2020) {
  XMPMeta meta;
  WXMP_Result result;

  WXMPMeta_DoesArrayItemExist_1(AsRef(meta),
                               "",          // schemaNS empty
                               "subject",   // arrayName
                               1,           // itemIndex
                               &result);

  EXPECT_NE(result.errMessage, nullptr);
}

TEST_F(WXMPMetaDoesArrayItemExist1Test_2020, NullArrayNameReportsError_2020) {
  XMPMeta meta;
  WXMP_Result result;

  WXMPMeta_DoesArrayItemExist_1(AsRef(meta),
                               "http://purl.org/dc/elements/1.1/",
                               nullptr,  // arrayName
                               1,
                               &result);

  EXPECT_NE(result.errMessage, nullptr);
}

TEST_F(WXMPMetaDoesArrayItemExist1Test_2020, EmptyArrayNameReportsError_2020) {
  XMPMeta meta;
  WXMP_Result result;

  WXMPMeta_DoesArrayItemExist_1(AsRef(meta),
                               "http://purl.org/dc/elements/1.1/",
                               "",  // arrayName empty
                               1,
                               &result);

  EXPECT_NE(result.errMessage, nullptr);
}

TEST_F(WXMPMetaDoesArrayItemExist1Test_2020, ZeroIndexHandledWithoutCrash_2020) {
  XMPMeta meta;
  const std::string xmp = MinimalXmpWithDcSubjectBag();
  meta.ParseFromBuffer(xmp.c_str(), static_cast<XMP_StringLen>(xmp.size()), 0);

  WXMP_Result result;
  WXMPMeta_DoesArrayItemExist_1(AsRef(meta),
                               "http://purl.org/dc/elements/1.1/",
                               "subject",
                               0,  // boundary/invalid in many XMP APIs
                               &result);

  // Black-box friendly: accept either explicit error or a false result, but must be observable and safe.
  if (result.errMessage == nullptr) {
    EXPECT_EQ(result.int32Result, 0u);
  } else {
    EXPECT_NE(result.errMessage, nullptr);
  }
}

TEST_F(WXMPMetaDoesArrayItemExist1Test_2020, NegativeIndexHandledWithoutCrash_2020) {
  XMPMeta meta;
  const std::string xmp = MinimalXmpWithDcSubjectBag();
  meta.ParseFromBuffer(xmp.c_str(), static_cast<XMP_StringLen>(xmp.size()), 0);

  WXMP_Result result;
  WXMPMeta_DoesArrayItemExist_1(AsRef(meta),
                               "http://purl.org/dc/elements/1.1/",
                               "subject",
                               static_cast<XMP_Index>(-1),
                               &result);

  // Black-box friendly: accept either explicit error or a false result.
  if (result.errMessage == nullptr) {
    EXPECT_EQ(result.int32Result, 0u);
  } else {
    EXPECT_NE(result.errMessage, nullptr);
  }
}