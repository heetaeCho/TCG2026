// =================================================================================================
// TEST_ID 2026
// Unit tests for WXMPMeta_GetProperty_Int_1
// File: ./TestProjects/exiv2/xmpsdk/src/WXMPMeta.cpp
// =================================================================================================

#include <gtest/gtest.h>

#include <cstdint>
#include <cstring>

// XMP SDK headers (project-local)
#include "XMP_Const.h"
#include "XMPCore_Impl.hpp"          // for XMPMeta (implementation header used in this codebase)
#include "XMPMeta.hpp"               // XMPMeta public interface
#include "client-glue/WXMP_Common.hpp"  // WXMP_Result

// Some builds define XMPMetaRef elsewhere; keep this benign if already defined.
#ifndef XMPMetaRef
typedef void* XMPMetaRef;
#endif

// Under test (implemented in WXMPMeta.cpp)
extern "C" void WXMPMeta_GetProperty_Int_1(XMPMetaRef xmpRef, XMP_StringPtr schemaNS, XMP_StringPtr propName,
                                          XMP_Int32* propValue, XMP_OptionBits* options, WXMP_Result* wResult);

// -------------------------------------------------------------------------------------------------

namespace {

struct WrapperCallOutcome {
  bool threw = false;
  XMP_Int32 errId = 0;
};

WrapperCallOutcome CallGetPropertyInt1Catching(XMPMetaRef ref, XMP_StringPtr schemaNS, XMP_StringPtr propName,
                                              XMP_Int32* propValue, XMP_OptionBits* options, WXMP_Result* wResult) {
  WrapperCallOutcome out{};
  try {
    WXMPMeta_GetProperty_Int_1(ref, schemaNS, propName, propValue, options, wResult);
  } catch (const XMP_Error& e) {
    out.threw = true;
    out.errId = e.GetID();
  } catch (...) {
    out.threw = true;
    out.errId = -1;
  }
  return out;
}

class WXMPMetaGetPropertyInt1Test_2026 : public ::testing::Test {
protected:
  static void SetUpTestSuite() {
    // Most XMP SDK builds require explicit init/term to set up global state.
    // If already initialized internally, Initialize() typically returns true or is idempotent.
    (void)XMPMeta::Initialize();
  }

  static void TearDownTestSuite() { XMPMeta::Terminate(); }

  // Common schema used in tests
  static constexpr const char* kXmpSchema = "http://ns.adobe.com/xap/1.0/";
};

}  // namespace

// -------------------------------------------------------------------------------------------------
// Normal operation

TEST_F(WXMPMetaGetPropertyInt1Test_2026, ReturnsTrueAndOutputsValueWhenPropertyExists_2026) {
  XMPMeta meta;
  meta.SetProperty_Int(kXmpSchema, "Rating", 5, 0);

  WXMP_Result wResult;
  wResult.errMessage = nullptr;
  wResult.int32Result = 0;

  XMP_Int32 outValue = 0;
  XMP_OptionBits outOptions = 0;

  ASSERT_NO_THROW(WXMPMeta_GetProperty_Int_1(reinterpret_cast<XMPMetaRef>(&meta), kXmpSchema, "Rating", &outValue,
                                            &outOptions, &wResult));

  EXPECT_EQ(wResult.int32Result, 1u);  // found == true
  EXPECT_EQ(outValue, 5);
}

TEST_F(WXMPMetaGetPropertyInt1Test_2026, ReturnsFalseWhenPropertyDoesNotExist_2026) {
  XMPMeta meta;  // no properties set

  WXMP_Result wResult;
  wResult.errMessage = nullptr;
  wResult.int32Result = 123456u;  // sentinel

  XMP_Int32 outValue = 777;       // sentinel
  XMP_OptionBits outOptions = 42; // sentinel

  ASSERT_NO_THROW(WXMPMeta_GetProperty_Int_1(reinterpret_cast<XMPMetaRef>(&meta), kXmpSchema, "Rating", &outValue,
                                            &outOptions, &wResult));

  EXPECT_EQ(wResult.int32Result, 0u);  // found == false
}

// -------------------------------------------------------------------------------------------------
// Boundary conditions (null output pointers are allowed by wrapper)

TEST_F(WXMPMetaGetPropertyInt1Test_2026, AcceptsNullPropValuePointer_2026) {
  XMPMeta meta;
  meta.SetProperty_Int(kXmpSchema, "Rating", 10, 0);

  WXMP_Result wResult;
  wResult.errMessage = nullptr;
  wResult.int32Result = 0;

  XMP_OptionBits outOptions = 0;

  ASSERT_NO_THROW(WXMPMeta_GetProperty_Int_1(reinterpret_cast<XMPMetaRef>(&meta), kXmpSchema, "Rating",
                                            /*propValue*/ nullptr, &outOptions, &wResult));

  EXPECT_EQ(wResult.int32Result, 1u);
}

TEST_F(WXMPMetaGetPropertyInt1Test_2026, AcceptsNullOptionsPointer_2026) {
  XMPMeta meta;
  meta.SetProperty_Int(kXmpSchema, "Rating", 3, 0);

  WXMP_Result wResult;
  wResult.errMessage = nullptr;
  wResult.int32Result = 0;

  XMP_Int32 outValue = 0;

  ASSERT_NO_THROW(WXMPMeta_GetProperty_Int_1(reinterpret_cast<XMPMetaRef>(&meta), kXmpSchema, "Rating", &outValue,
                                            /*options*/ nullptr, &wResult));

  EXPECT_EQ(wResult.int32Result, 1u);
  EXPECT_EQ(outValue, 3);
}

TEST_F(WXMPMetaGetPropertyInt1Test_2026, AcceptsNullPropValueAndOptionsPointers_2026) {
  XMPMeta meta;
  meta.SetProperty_Int(kXmpSchema, "Rating", 1, 0);

  WXMP_Result wResult;
  wResult.errMessage = nullptr;
  wResult.int32Result = 0;

  ASSERT_NO_THROW(WXMPMeta_GetProperty_Int_1(reinterpret_cast<XMPMetaRef>(&meta), kXmpSchema, "Rating",
                                            /*propValue*/ nullptr, /*options*/ nullptr, &wResult));

  EXPECT_EQ(wResult.int32Result, 1u);
}

// -------------------------------------------------------------------------------------------------
// Exceptional / error cases (observable either via thrown XMP_Error OR via wResult.errMessage)

TEST_F(WXMPMetaGetPropertyInt1Test_2026, EmptySchemaNamespaceIsRejected_2026) {
  XMPMeta meta;
  WXMP_Result wResult;
  wResult.errMessage = nullptr;
  wResult.int32Result = 0;

  XMP_Int32 outValue = 0;
  XMP_OptionBits outOptions = 0;

  const WrapperCallOutcome outcome = CallGetPropertyInt1Catching(reinterpret_cast<XMPMetaRef>(&meta),
                                                                 /*schemaNS*/ "", /*propName*/ "Rating", &outValue,
                                                                 &outOptions, &wResult);

  // Wrapper behavior differs by build: either it throws XMP_Error, or it captures it into wResult.
  if (outcome.threw) {
    EXPECT_EQ(outcome.errId, kXMPErr_BadSchema);
  } else {
    EXPECT_NE(wResult.errMessage, nullptr);
  }
}

TEST_F(WXMPMetaGetPropertyInt1Test_2026, NullSchemaNamespaceIsRejected_2026) {
  XMPMeta meta;
  WXMP_Result wResult;
  wResult.errMessage = nullptr;
  wResult.int32Result = 0;

  XMP_Int32 outValue = 0;
  XMP_OptionBits outOptions = 0;

  const WrapperCallOutcome outcome = CallGetPropertyInt1Catching(reinterpret_cast<XMPMetaRef>(&meta),
                                                                 /*schemaNS*/ nullptr, /*propName*/ "Rating",
                                                                 &outValue, &outOptions, &wResult);

  if (outcome.threw) {
    EXPECT_EQ(outcome.errId, kXMPErr_BadSchema);
  } else {
    EXPECT_NE(wResult.errMessage, nullptr);
  }
}

TEST_F(WXMPMetaGetPropertyInt1Test_2026, EmptyPropertyNameIsRejected_2026) {
  XMPMeta meta;
  WXMP_Result wResult;
  wResult.errMessage = nullptr;
  wResult.int32Result = 0;

  XMP_Int32 outValue = 0;
  XMP_OptionBits outOptions = 0;

  const WrapperCallOutcome outcome = CallGetPropertyInt1Catching(reinterpret_cast<XMPMetaRef>(&meta), kXmpSchema,
                                                                 /*propName*/ "", &outValue, &outOptions, &wResult);

  if (outcome.threw) {
    EXPECT_EQ(outcome.errId, kXMPErr_BadXPath);
  } else {
    EXPECT_NE(wResult.errMessage, nullptr);
  }
}

TEST_F(WXMPMetaGetPropertyInt1Test_2026, NullPropertyNameIsRejected_2026) {
  XMPMeta meta;
  WXMP_Result wResult;
  wResult.errMessage = nullptr;
  wResult.int32Result = 0;

  XMP_Int32 outValue = 0;
  XMP_OptionBits outOptions = 0;

  const WrapperCallOutcome outcome = CallGetPropertyInt1Catching(reinterpret_cast<XMPMetaRef>(&meta), kXmpSchema,
                                                                 /*propName*/ nullptr, &outValue, &outOptions,
                                                                 &wResult);

  if (outcome.threw) {
    EXPECT_EQ(outcome.errId, kXMPErr_BadXPath);
  } else {
    EXPECT_NE(wResult.errMessage, nullptr);
  }
}