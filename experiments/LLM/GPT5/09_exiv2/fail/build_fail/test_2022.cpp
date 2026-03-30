// =================================================================================================
// TEST_ID: 2022
// Unit tests for WXMPMeta_DoesQualifierExist_1
// File: ./TestProjects/exiv2/xmpsdk/src/WXMPMeta.cpp
// =================================================================================================

#include <gtest/gtest.h>

#include <cstring>
#include <string>

#include "XMP_Const.h"
#include "WXMP_Common.hpp"
#include "XMPMeta.hpp"

// The wrapper under test (implemented in WXMPMeta.cpp).
extern "C" void WXMPMeta_DoesQualifierExist_1(XMPMetaRef xmpRef,
                                             XMP_StringPtr schemaNS,
                                             XMP_StringPtr propName,
                                             XMP_StringPtr qualNS,
                                             XMP_StringPtr qualName,
                                             WXMP_Result* wResult);

// Some builds expose XMP_Error::GetID inline; keep usage minimal and guarded by compilation.
static XMP_Int32 GetXmpErrorIdOrFallback(const XMP_Error& e) {
#if defined(__TXMPMeta_hpp__) || 1
  // In this codebase, XMP_Error has GetID() inline in XMP_Const.h (per prompt).
  return e.GetID();
#else
  (void)e;
  return kXMPErr_Unknown;
#endif
}

class WXMPMetaDoesQualifierExistTest_2022 : public ::testing::Test {
 protected:
  static void SetUpTestSuite() {
    // Many XMP SDK configurations require global init before using XMPMeta.
    // Treat as black box: call Initialize, but don't assert on its return value too strongly.
    (void)XMPMeta::Initialize();
  }

  static void TearDownTestSuite() {
    // Symmetric cleanup.
    XMPMeta::Terminate();
  }

  struct CallOutcome {
    bool threw = false;
    XMP_Int32 errId = kXMPErr_Unknown;
    std::string errMsg;
  };

  static CallOutcome CallWrapperExpectingError(XMPMetaRef xmpRef,
                                               XMP_StringPtr schemaNS,
                                               XMP_StringPtr propName,
                                               XMP_StringPtr qualNS,
                                               XMP_StringPtr qualName,
                                               WXMP_Result* result) {
    CallOutcome out;
    try {
      WXMPMeta_DoesQualifierExist_1(xmpRef, schemaNS, propName, qualNS, qualName, result);
    } catch (const XMP_Error& e) {
      out.threw = true;
      out.errId = GetXmpErrorIdOrFallback(e);
      const XMP_StringPtr msg = e.GetErrMsg();
      if (msg != nullptr) out.errMsg = msg;
    } catch (...) {
      out.threw = true;
      out.errId = kXMPErr_UnknownException;
    }

    if (!out.threw) {
      // If wrapper catches internally, it should communicate the error via WXMP_Result.
      if (result != nullptr && result->errMessage != nullptr) {
        out.errMsg = result->errMessage;
      }
    }
    return out;
  }

  static void ExpectReportedBadParam(const CallOutcome& outcome,
                                     const WXMP_Result& wResult,
                                     XMP_Int32 expectedId) {
    if (outcome.threw) {
      EXPECT_EQ(outcome.errId, expectedId);
    } else {
      // Black-box tolerant: we don't assume exact error plumbing,
      // but we require an observable error indication.
      EXPECT_NE(wResult.errMessage, nullptr);
      // If there is an error message, it should not be an empty string.
      if (wResult.errMessage != nullptr) {
        EXPECT_NE(*wResult.errMessage, '\0');
      }
    }
  }
};

TEST_F(WXMPMetaDoesQualifierExistTest_2022, ReturnsFalseWhenQualifierMissing_2022) {
  XMPMeta meta;

  // Use a schema/property without setting any qualifier; should report "not found".
  const char* schemaNS = "http://ns.adobe.com/xap/1.0/";
  const char* propName = "CreatorTool";
  const char* qualNS = "http://www.w3.org/XML/1998/namespace";
  const char* qualName = "lang";

  WXMP_Result wr;
  wr.int32Result = 0xA5A5A5A5;  // sentinel

  ASSERT_NO_THROW(WXMPMeta_DoesQualifierExist_1(reinterpret_cast<XMPMetaRef>(&meta),
                                               schemaNS,
                                               propName,
                                               qualNS,
                                               qualName,
                                               &wr));
  EXPECT_EQ(wr.int32Result, 0u);
}

TEST_F(WXMPMetaDoesQualifierExistTest_2022, ReturnsTrueWhenQualifierExists_2022) {
  XMPMeta meta;

  const char* schemaNS = "http://ns.adobe.com/xap/1.0/";
  const char* propName = "CreatorTool";
  const char* propValue = "UnitTestTool";
  const char* qualNS = "http://www.w3.org/XML/1998/namespace";
  const char* qualName = "lang";
  const char* qualValue = "en-US";

  // Arrange: create the property and then add a qualifier.
  ASSERT_NO_THROW(meta.SetProperty(schemaNS, propName, propValue, 0));
  ASSERT_NO_THROW(meta.SetQualifier(schemaNS, propName, qualNS, qualName, qualValue, 0));

  WXMP_Result wr;
  wr.int32Result = 0;  // baseline

  ASSERT_NO_THROW(WXMPMeta_DoesQualifierExist_1(reinterpret_cast<XMPMetaRef>(&meta),
                                               schemaNS,
                                               propName,
                                               qualNS,
                                               qualName,
                                               &wr));
  EXPECT_EQ(wr.int32Result, 1u);
}

TEST_F(WXMPMetaDoesQualifierExistTest_2022, EmptySchemaNamespaceReportsBadSchema_2022) {
  XMPMeta meta;

  const char* empty = "";
  const char* propName = "CreatorTool";
  const char* qualNS = "http://www.w3.org/XML/1998/namespace";
  const char* qualName = "lang";

  WXMP_Result wr;
  wr.int32Result = 123;
  wr.errMessage = nullptr;

  const auto outcome =
      CallWrapperExpectingError(reinterpret_cast<XMPMetaRef>(&meta), empty, propName, qualNS, qualName, &wr);

  ExpectReportedBadParam(outcome, wr, kXMPErr_BadSchema);
}

TEST_F(WXMPMetaDoesQualifierExistTest_2022, NullSchemaNamespaceReportsBadSchema_2022) {
  XMPMeta meta;

  const char* propName = "CreatorTool";
  const char* qualNS = "http://www.w3.org/XML/1998/namespace";
  const char* qualName = "lang";

  WXMP_Result wr;
  wr.int32Result = 123;
  wr.errMessage = nullptr;

  const auto outcome =
      CallWrapperExpectingError(reinterpret_cast<XMPMetaRef>(&meta), nullptr, propName, qualNS, qualName, &wr);

  ExpectReportedBadParam(outcome, wr, kXMPErr_BadSchema);
}

TEST_F(WXMPMetaDoesQualifierExistTest_2022, EmptyPropertyNameReportsBadXPath_2022) {
  XMPMeta meta;

  const char* schemaNS = "http://ns.adobe.com/xap/1.0/";
  const char* empty = "";
  const char* qualNS = "http://www.w3.org/XML/1998/namespace";
  const char* qualName = "lang";

  WXMP_Result wr;
  wr.int32Result = 123;
  wr.errMessage = nullptr;

  const auto outcome =
      CallWrapperExpectingError(reinterpret_cast<XMPMetaRef>(&meta), schemaNS, empty, qualNS, qualName, &wr);

  ExpectReportedBadParam(outcome, wr, kXMPErr_BadXPath);
}

TEST_F(WXMPMetaDoesQualifierExistTest_2022, NullPropertyNameReportsBadXPath_2022) {
  XMPMeta meta;

  const char* schemaNS = "http://ns.adobe.com/xap/1.0/";
  const char* qualNS = "http://www.w3.org/XML/1998/namespace";
  const char* qualName = "lang";

  WXMP_Result wr;
  wr.int32Result = 123;
  wr.errMessage = nullptr;

  const auto outcome =
      CallWrapperExpectingError(reinterpret_cast<XMPMetaRef>(&meta), schemaNS, nullptr, qualNS, qualName, &wr);

  ExpectReportedBadParam(outcome, wr, kXMPErr_BadXPath);
}

TEST_F(WXMPMetaDoesQualifierExistTest_2022, EmptyQualifierNamespaceReportsBadSchema_2022) {
  XMPMeta meta;

  const char* schemaNS = "http://ns.adobe.com/xap/1.0/";
  const char* propName = "CreatorTool";
  const char* empty = "";
  const char* qualName = "lang";

  WXMP_Result wr;
  wr.int32Result = 123;
  wr.errMessage = nullptr;

  const auto outcome =
      CallWrapperExpectingError(reinterpret_cast<XMPMetaRef>(&meta), schemaNS, propName, empty, qualName, &wr);

  ExpectReportedBadParam(outcome, wr, kXMPErr_BadSchema);
}

TEST_F(WXMPMetaDoesQualifierExistTest_2022, NullQualifierNamespaceReportsBadSchema_2022) {
  XMPMeta meta;

  const char* schemaNS = "http://ns.adobe.com/xap/1.0/";
  const char* propName = "CreatorTool";
  const char* qualName = "lang";

  WXMP_Result wr;
  wr.int32Result = 123;
  wr.errMessage = nullptr;

  const auto outcome =
      CallWrapperExpectingError(reinterpret_cast<XMPMetaRef>(&meta), schemaNS, propName, nullptr, qualName, &wr);

  ExpectReportedBadParam(outcome, wr, kXMPErr_BadSchema);
}

TEST_F(WXMPMetaDoesQualifierExistTest_2022, EmptyQualifierNameReportsBadXPath_2022) {
  XMPMeta meta;

  const char* schemaNS = "http://ns.adobe.com/xap/1.0/";
  const char* propName = "CreatorTool";
  const char* qualNS = "http://www.w3.org/XML/1998/namespace";
  const char* empty = "";

  WXMP_Result wr;
  wr.int32Result = 123;
  wr.errMessage = nullptr;

  const auto outcome =
      CallWrapperExpectingError(reinterpret_cast<XMPMetaRef>(&meta), schemaNS, propName, qualNS, empty, &wr);

  ExpectReportedBadParam(outcome, wr, kXMPErr_BadXPath);
}

TEST_F(WXMPMetaDoesQualifierExistTest_2022, NullQualifierNameReportsBadXPath_2022) {
  XMPMeta meta;

  const char* schemaNS = "http://ns.adobe.com/xap/1.0/";
  const char* propName = "CreatorTool";
  const char* qualNS = "http://www.w3.org/XML/1998/namespace";

  WXMP_Result wr;
  wr.int32Result = 123;
  wr.errMessage = nullptr;

  const auto outcome =
      CallWrapperExpectingError(reinterpret_cast<XMPMetaRef>(&meta), schemaNS, propName, qualNS, nullptr, &wr);

  ExpectReportedBadParam(outcome, wr, kXMPErr_BadXPath);
}