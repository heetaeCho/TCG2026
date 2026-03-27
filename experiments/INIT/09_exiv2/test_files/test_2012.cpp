// =================================================================================================
// TEST_ID: 2012
// Unit tests for WXMPMeta_AppendArrayItem_1 wrapper
// File: ./TestProjects/exiv2/xmpsdk/src/WXMPMeta.cpp
// =================================================================================================

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <string>

// These headers are part of the XMP SDK as vendored in this repository.
#include "XMP_Const.h"
#include "XMPMeta.hpp"
#include "client-glue/WXMP_Common.hpp"

// If the C typedefs are not visible here, provide minimal compatible typedefs.
// (These are only for compilation glue; they do not re-implement any logic.)
#ifndef __XMPMETAREF_TYPEDEF_GUARD_2012
#define __XMPMETAREF_TYPEDEF_GUARD_2012
using XMPMetaRef = void*;
#endif

extern "C" {
// Wrapper under test (implemented in WXMPMeta.cpp)
void WXMPMeta_AppendArrayItem_1(XMPMetaRef xmpRef, XMP_StringPtr schemaNS, XMP_StringPtr arrayName,
                               XMP_OptionBits arrayOptions, XMP_StringPtr itemValue, XMP_OptionBits options,
                               WXMP_Result* wResult);
}  // extern "C"

namespace {

// Some builds might not expose these option bits in the visible headers. If they are not defined,
// just use 0 and rely on other observable behavior (error reporting / no-crash).
#ifndef kXMP_PropValueIsArray
static constexpr XMP_OptionBits kXMP_PropValueIsArray = 0;
#endif
#ifndef kXMP_PropArrayIsOrdered
static constexpr XMP_OptionBits kXMP_PropArrayIsOrdered = 0;
#endif

class WXMPMeta_AppendArrayItem_1_Test_2012 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Safe to call; treat as black box.
    (void)XMPMeta::Initialize();
    meta_ = new XMPMeta();
    xmpRef_ = reinterpret_cast<XMPMetaRef>(meta_);
  }

  void TearDown() override {
    delete meta_;
    meta_ = nullptr;
    xmpRef_ = nullptr;
    // Safe to call; treat as black box.
    XMPMeta::Terminate();
  }

  static bool HasError(const WXMP_Result& r) { return (r.errMessage != nullptr) && (r.errMessage[0] != '\0'); }

  // Helper: try both "ex:Array" and "Array" naming variants, since the exact expectations
  // (prefixed vs. local name) are not part of the wrapper interface and can vary by SDK build.
  XMP_Index CountItemsBestEffort(XMP_StringPtr schemaNS, XMP_StringPtr propMaybePrefixed,
                                XMP_StringPtr propMaybeLocal) const {
    XMP_Index c1 = 0;
    XMP_Index c2 = 0;
    try {
      c1 = meta_->CountArrayItems(schemaNS, propMaybePrefixed);
    } catch (...) {
      c1 = 0;
    }
    try {
      c2 = meta_->CountArrayItems(schemaNS, propMaybeLocal);
    } catch (...) {
      c2 = 0;
    }
    return (c1 > 0) ? c1 : c2;
  }

  // Helper: best-effort fetch the first array item and return it (empty if not retrievable).
  std::string GetFirstItemBestEffort(XMP_StringPtr schemaNS, XMP_StringPtr propMaybePrefixed,
                                     XMP_StringPtr propMaybeLocal) const {
    XMP_StringPtr itemValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits opts = 0;

    try {
      if (meta_->GetArrayItem(schemaNS, propMaybePrefixed, 1, &itemValue, &valueSize, &opts)) {
        return std::string(itemValue ? itemValue : "", static_cast<size_t>(valueSize));
      }
    } catch (...) {
      // ignore
    }

    itemValue = nullptr;
    valueSize = 0;
    opts = 0;

    try {
      if (meta_->GetArrayItem(schemaNS, propMaybeLocal, 1, &itemValue, &valueSize, &opts)) {
        return std::string(itemValue ? itemValue : "", static_cast<size_t>(valueSize));
      }
    } catch (...) {
      // ignore
    }

    return std::string();
  }

  XMPMeta* meta_ = nullptr;
  XMPMetaRef xmpRef_ = nullptr;
};

}  // namespace

// -------------------------------------------------------------------------------------------------
// Normal operation
// -------------------------------------------------------------------------------------------------

TEST_F(WXMPMeta_AppendArrayItem_1_Test_2012, AppendsItemAndIsObservableViaPublicAPI_2012) {
  // Register a custom namespace to avoid depending on pre-registered standard schemas.
  const char* kSchema = "http://example.com/ns/2012/";
  const char* kPrefix = "ex";

  // These are public APIs; treat as black box.
  XMPMeta::RegisterNamespace(kSchema, kPrefix);

  // Try both possible property name forms (prefixed vs local).
  const char* kArrayNamePrefixed = "ex:Array";
  const char* kArrayNameLocal = "Array";

  const char* kItem = "hello";

  WXMP_Result r;
  WXMPMeta_AppendArrayItem_1(
      xmpRef_, kSchema, kArrayNamePrefixed,
      static_cast<XMP_OptionBits>(kXMP_PropValueIsArray | kXMP_PropArrayIsOrdered), kItem, 0, &r);

  ASSERT_FALSE(HasError(r)) << "Unexpected error: " << (r.errMessage ? r.errMessage : "(null)");

  // Observable effect: array item count should be >= 1 (for either naming convention).
  const XMP_Index count = CountItemsBestEffort(kSchema, kArrayNamePrefixed, kArrayNameLocal);
  EXPECT_GE(count, 1);

  // Observable effect: first item should equal what we appended (best-effort retrieval).
  const std::string got = GetFirstItemBestEffort(kSchema, kArrayNamePrefixed, kArrayNameLocal);
  EXPECT_FALSE(got.empty());
  EXPECT_EQ(got, std::string(kItem));
}

// -------------------------------------------------------------------------------------------------
// Boundary conditions / error cases (observable via WXMP_Result)
// -------------------------------------------------------------------------------------------------

TEST_F(WXMPMeta_AppendArrayItem_1_Test_2012, NullSchemaNamespaceReportsError_2012) {
  const char* kArrayName = "ex:Array";

  WXMP_Result r;
  WXMPMeta_AppendArrayItem_1(xmpRef_, nullptr, kArrayName, 0, "v", 0, &r);

  EXPECT_TRUE(HasError(r));
}

TEST_F(WXMPMeta_AppendArrayItem_1_Test_2012, EmptySchemaNamespaceReportsError_2012) {
  const char* kArrayName = "ex:Array";

  WXMP_Result r;
  WXMPMeta_AppendArrayItem_1(xmpRef_, "", kArrayName, 0, "v", 0, &r);

  EXPECT_TRUE(HasError(r));
}

TEST_F(WXMPMeta_AppendArrayItem_1_Test_2012, NullArrayNameReportsError_2012) {
  const char* kSchema = "http://example.com/ns/2012/";
  XMPMeta::RegisterNamespace(kSchema, "ex");

  WXMP_Result r;
  WXMPMeta_AppendArrayItem_1(xmpRef_, kSchema, nullptr, 0, "v", 0, &r);

  EXPECT_TRUE(HasError(r));
}

TEST_F(WXMPMeta_AppendArrayItem_1_Test_2012, EmptyArrayNameReportsError_2012) {
  const char* kSchema = "http://example.com/ns/2012/";
  XMPMeta::RegisterNamespace(kSchema, "ex");

  WXMP_Result r;
  WXMPMeta_AppendArrayItem_1(xmpRef_, kSchema, "", 0, "v", 0, &r);

  EXPECT_TRUE(HasError(r));
}

TEST_F(WXMPMeta_AppendArrayItem_1_Test_2012, NullXmpRefReportsError_2012) {
  const char* kSchema = "http://example.com/ns/2012/";
  XMPMeta::RegisterNamespace(kSchema, "ex");

  WXMP_Result r;
  WXMPMeta_AppendArrayItem_1(nullptr, kSchema, "ex:Array", 0, "v", 0, &r);

  EXPECT_TRUE(HasError(r));
}

// Boundary-ish: ensure wrapper tolerates a null WXMP_Result pointer without crashing is NOT
// observable/guaranteed by the interface, so we do not test it.

// -------------------------------------------------------------------------------------------------
// Boundary conditions that should not corrupt existing data
// -------------------------------------------------------------------------------------------------

TEST_F(WXMPMeta_AppendArrayItem_1_Test_2012, AppendingMultipleItemsIncreasesCount_2012) {
  const char* kSchema = "http://example.com/ns/2012/";
  XMPMeta::RegisterNamespace(kSchema, "ex");

  const char* kArrayNamePrefixed = "ex:Array";
  const char* kArrayNameLocal = "Array";

  WXMP_Result r1;
  WXMPMeta_AppendArrayItem_1(
      xmpRef_, kSchema, kArrayNamePrefixed,
      static_cast<XMP_OptionBits>(kXMP_PropValueIsArray | kXMP_PropArrayIsOrdered), "one", 0, &r1);
  ASSERT_FALSE(HasError(r1));

  const XMP_Index count1 = CountItemsBestEffort(kSchema, kArrayNamePrefixed, kArrayNameLocal);
  ASSERT_GE(count1, 1);

  WXMP_Result r2;
  WXMPMeta_AppendArrayItem_1(
      xmpRef_, kSchema, kArrayNamePrefixed,
      static_cast<XMP_OptionBits>(kXMP_PropValueIsArray | kXMP_PropArrayIsOrdered), "two", 0, &r2);
  ASSERT_FALSE(HasError(r2));

  const XMP_Index count2 = CountItemsBestEffort(kSchema, kArrayNamePrefixed, kArrayNameLocal);
  EXPECT_GE(count2, count1);
  EXPECT_GE(count2, 2);
}