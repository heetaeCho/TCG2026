// =================================================================================================
// UNIT TESTS for WXMPMeta_GetQualifier_1
// File: ./TestProjects/exiv2/xmpsdk/src/WXMPMeta.cpp (wrapper)
// TEST_ID: 2009
// =================================================================================================

#include <gtest/gtest.h>

#include <cstring>
#include <string>

// These headers are referenced by the prompt and are expected to exist in the codebase.
#include "XMP_Const.h"
#include "client-glue/WXMP_Common.hpp"
#include "XMPMeta.hpp"

// If XMPMetaRef is not visible via included headers, provide a compatible fallback.
// In the XMP C-API glue, XMPMetaRef is typically an opaque pointer type.
#ifndef __XMPMetaRef_defined__
using XMPMetaRef = void*;
#endif

// The wrapper function under test (implemented in WXMPMeta.cpp).
extern "C" void WXMPMeta_GetQualifier_1(XMPMetaRef xmpRef,
                                       XMP_StringPtr schemaNS,
                                       XMP_StringPtr propName,
                                       XMP_StringPtr qualNS,
                                       XMP_StringPtr qualName,
                                       XMP_StringPtr* qualValue,
                                       XMP_StringLen* valueSize,
                                       XMP_OptionBits* options,
                                       WXMP_Result* wResult);

namespace {

// Common namespace URIs used for safe, non-empty inputs.
// (Exact URI values are not important for these tests as long as they are non-empty.)
constexpr XMP_StringPtr kSchemaNS = "http://ns.adobe.com/xap/1.0/";
constexpr XMP_StringPtr kQualNS   = "http://www.w3.org/XML/1998/namespace";

class WXMPMeta_GetQualifier_1_Test_2009 : public ::testing::Test {
protected:
  static void SetUpTestSuite() {
    // Many XMP operations require global init. If already initialized elsewhere, this should be safe.
    // We do not assert on the return value to avoid depending on global test ordering.
    (void)XMPMeta::Initialize();
  }

  static void TearDownTestSuite() {
    // Match initialization attempt.
    XMPMeta::Terminate();
  }

  static XMPMetaRef AsRef(XMPMeta& meta) {
    // Treat XMPMetaRef as an opaque handle to an XMPMeta instance, as used by the wrapper layer.
    return reinterpret_cast<XMPMetaRef>(&meta);
  }
};

}  // namespace

// ------------------------------ Normal operation ------------------------------

TEST_F(WXMPMeta_GetQualifier_1_Test_2009, ReturnsTrueAndOutputsValue_WhenQualifierExists_2009) {
  XMPMeta meta;

  // Arrange: create a property and attach a qualifier.
  // We do NOT assume anything about internal storage; we only use the public interface.
  meta.SetProperty(kSchemaNS, "TestProp", "PropValue", 0);
  meta.SetQualifier(kSchemaNS, "TestProp", kQualNS, "lang", "en-US", 0);

  XMP_StringPtr outValue = nullptr;
  XMP_StringLen outSize = 0;
  XMP_OptionBits outOptions = 0;
  WXMP_Result wResult;

  // Act
  WXMPMeta_GetQualifier_1(AsRef(meta),
                         kSchemaNS,
                         "TestProp",
                         kQualNS,
                         "lang",
                         &outValue,
                         &outSize,
                         &outOptions,
                         &wResult);

  // Assert: wrapper reports found via int32Result.
  EXPECT_EQ(wResult.int32Result, 1u);

  // And outputs are populated in some observable way.
  ASSERT_NE(outValue, nullptr);
  EXPECT_GT(outSize, 0u);
  EXPECT_EQ(std::string(outValue, outSize), "en-US");
}

TEST_F(WXMPMeta_GetQualifier_1_Test_2009, ReturnsFalse_WhenQualifierDoesNotExist_2009) {
  XMPMeta meta;

  // Arrange: property exists, but qualifier is not set.
  meta.SetProperty(kSchemaNS, "TestProp", "PropValue", 0);

  XMP_StringPtr outValue = nullptr;
  XMP_StringLen outSize = 0;
  XMP_OptionBits outOptions = 0;
  WXMP_Result wResult;

  // Act
  WXMPMeta_GetQualifier_1(AsRef(meta),
                         kSchemaNS,
                         "TestProp",
                         kQualNS,
                         "lang",
                         &outValue,
                         &outSize,
                         &outOptions,
                         &wResult);

  // Assert
  EXPECT_EQ(wResult.int32Result, 0u);
}

// ------------------------------ Boundary conditions ------------------------------

TEST_F(WXMPMeta_GetQualifier_1_Test_2009, DoesNotCrash_WhenOutputPointersAreNull_2009) {
  XMPMeta meta;

  // Arrange: qualifier exists.
  meta.SetProperty(kSchemaNS, "TestProp", "PropValue", 0);
  meta.SetQualifier(kSchemaNS, "TestProp", kQualNS, "lang", "en-US", 0);

  WXMP_Result wResult;

  // Act: pass null for qualValue/valueSize/options (wrapper substitutes internal void defaults).
  WXMPMeta_GetQualifier_1(AsRef(meta),
                         kSchemaNS,
                         "TestProp",
                         kQualNS,
                         "lang",
                         /*qualValue*/ nullptr,
                         /*valueSize*/ nullptr,
                         /*options*/ nullptr,
                         &wResult);

  // Assert: still reports found.
  EXPECT_EQ(wResult.int32Result, 1u);
}

// ------------------------------ Exceptional / error cases (observable via wrapper) ------------------------------

TEST_F(WXMPMeta_GetQualifier_1_Test_2009, SetsError_WhenSchemaNSIsNull_2009) {
  XMPMeta meta;

  XMP_StringPtr outValue = nullptr;
  XMP_StringLen outSize = 0;
  XMP_OptionBits outOptions = 0;
  WXMP_Result wResult;

  WXMPMeta_GetQualifier_1(AsRef(meta),
                         /*schemaNS*/ nullptr,
                         "TestProp",
                         kQualNS,
                         "lang",
                         &outValue,
                         &outSize,
                         &outOptions,
                         &wResult);

  // Observable error: wrapper is expected to report an error message on failure.
  EXPECT_NE(wResult.errMessage, nullptr);
}

TEST_F(WXMPMeta_GetQualifier_1_Test_2009, SetsError_WhenSchemaNSIsEmpty_2009) {
  XMPMeta meta;

  XMP_StringPtr outValue = nullptr;
  XMP_StringLen outSize = 0;
  XMP_OptionBits outOptions = 0;
  WXMP_Result wResult;

  WXMPMeta_GetQualifier_1(AsRef(meta),
                         /*schemaNS*/ "",
                         "TestProp",
                         kQualNS,
                         "lang",
                         &outValue,
                         &outSize,
                         &outOptions,
                         &wResult);

  EXPECT_NE(wResult.errMessage, nullptr);
}

TEST_F(WXMPMeta_GetQualifier_1_Test_2009, SetsError_WhenPropNameIsNull_2009) {
  XMPMeta meta;

  XMP_StringPtr outValue = nullptr;
  XMP_StringLen outSize = 0;
  XMP_OptionBits outOptions = 0;
  WXMP_Result wResult;

  WXMPMeta_GetQualifier_1(AsRef(meta),
                         kSchemaNS,
                         /*propName*/ nullptr,
                         kQualNS,
                         "lang",
                         &outValue,
                         &outSize,
                         &outOptions,
                         &wResult);

  EXPECT_NE(wResult.errMessage, nullptr);
}

TEST_F(WXMPMeta_GetQualifier_1_Test_2009, SetsError_WhenPropNameIsEmpty_2009) {
  XMPMeta meta;

  XMP_StringPtr outValue = nullptr;
  XMP_StringLen outSize = 0;
  XMP_OptionBits outOptions = 0;
  WXMP_Result wResult;

  WXMPMeta_GetQualifier_1(AsRef(meta),
                         kSchemaNS,
                         /*propName*/ "",
                         kQualNS,
                         "lang",
                         &outValue,
                         &outSize,
                         &outOptions,
                         &wResult);

  EXPECT_NE(wResult.errMessage, nullptr);
}

TEST_F(WXMPMeta_GetQualifier_1_Test_2009, SetsError_WhenQualNSIsNull_2009) {
  XMPMeta meta;

  XMP_StringPtr outValue = nullptr;
  XMP_StringLen outSize = 0;
  XMP_OptionBits outOptions = 0;
  WXMP_Result wResult;

  WXMPMeta_GetQualifier_1(AsRef(meta),
                         kSchemaNS,
                         "TestProp",
                         /*qualNS*/ nullptr,
                         "lang",
                         &outValue,
                         &outSize,
                         &outOptions,
                         &wResult);

  EXPECT_NE(wResult.errMessage, nullptr);
}

TEST_F(WXMPMeta_GetQualifier_1_Test_2009, SetsError_WhenQualNSIsEmpty_2009) {
  XMPMeta meta;

  XMP_StringPtr outValue = nullptr;
  XMP_StringLen outSize = 0;
  XMP_OptionBits outOptions = 0;
  WXMP_Result wResult;

  WXMPMeta_GetQualifier_1(AsRef(meta),
                         kSchemaNS,
                         "TestProp",
                         /*qualNS*/ "",
                         "lang",
                         &outValue,
                         &outSize,
                         &outOptions,
                         &wResult);

  EXPECT_NE(wResult.errMessage, nullptr);
}

TEST_F(WXMPMeta_GetQualifier_1_Test_2009, SetsError_WhenQualNameIsNull_2009) {
  XMPMeta meta;

  XMP_StringPtr outValue = nullptr;
  XMP_StringLen outSize = 0;
  XMP_OptionBits outOptions = 0;
  WXMP_Result wResult;

  WXMPMeta_GetQualifier_1(AsRef(meta),
                         kSchemaNS,
                         "TestProp",
                         kQualNS,
                         /*qualName*/ nullptr,
                         &outValue,
                         &outSize,
                         &outOptions,
                         &wResult);

  EXPECT_NE(wResult.errMessage, nullptr);
}

TEST_F(WXMPMeta_GetQualifier_1_Test_2009, SetsError_WhenQualNameIsEmpty_2009) {
  XMPMeta meta;

  XMP_StringPtr outValue = nullptr;
  XMP_StringLen outSize = 0;
  XMP_OptionBits outOptions = 0;
  WXMP_Result wResult;

  WXMPMeta_GetQualifier_1(AsRef(meta),
                         kSchemaNS,
                         "TestProp",
                         kQualNS,
                         /*qualName*/ "",
                         &outValue,
                         &outSize,
                         &outOptions,
                         &wResult);

  EXPECT_NE(wResult.errMessage, nullptr);
}