// ============================================================================
// TEST_ID 2042
// Unit tests for WXMPMeta_SetObjectName_1
// File: ./TestProjects/exiv2/xmpsdk/src/WXMPMeta.cpp
// ============================================================================

#include <gtest/gtest.h>

#include <string>
#include <vector>

// These headers are part of the XMP SDK / Exiv2 vendored xmpsdk tree.
#include "XMP_Const.h"
#include "WXMP_Common.hpp"
#include "XMPMeta.hpp"

// The wrapper under test is implemented in WXMPMeta.cpp. If there is a proper
// public header declaring it in your tree, prefer including that header instead.
// (We declare it here to keep the test single-file and focused.)
extern "C" void WXMPMeta_SetObjectName_1(XMPMetaRef xmpRef, XMP_StringPtr name, WXMP_Result* wResult);

namespace {

class WXMPMeta_SetObjectName_1_Test_2042 : public ::testing::Test {
protected:
  static void SetUpTestSuite() {
    // Many XMP SDK builds require initialization. If Initialize() is a no-op
    // in your build, it should still be safe to call.
    (void)XMPMeta::Initialize();
  }

  static void TearDownTestSuite() {
    // Balance Initialize() if the implementation expects it.
    XMPMeta::Terminate();
  }

  static std::string GetObjectNameString(const XMPMeta& meta) {
    XMP_StringPtr namePtr = nullptr;
    XMP_StringLen nameLen = 0;
    meta.GetObjectName(&namePtr, &nameLen);

    if (namePtr == nullptr || nameLen == 0) return std::string();
    return std::string(namePtr, static_cast<size_t>(nameLen));
  }
};

TEST_F(WXMPMeta_SetObjectName_1_Test_2042, SetsObjectName_NormalString_2042) {
  WXMP_Result wResult;
  XMPMeta meta;

  WXMPMeta_SetObjectName_1(reinterpret_cast<XMPMetaRef>(&meta), "hello", &wResult);

  EXPECT_EQ(GetObjectNameString(meta), "hello");
}

TEST_F(WXMPMeta_SetObjectName_1_Test_2042, SetsObjectName_EmptyString_2042) {
  WXMP_Result wResult;
  XMPMeta meta;

  WXMPMeta_SetObjectName_1(reinterpret_cast<XMPMetaRef>(&meta), "", &wResult);

  EXPECT_EQ(GetObjectNameString(meta), "");
}

TEST_F(WXMPMeta_SetObjectName_1_Test_2042, NullNameTreatedAsEmptyString_2042) {
  WXMP_Result wResult;
  XMPMeta meta;

  // The wrapper explicitly maps null to "".
  WXMPMeta_SetObjectName_1(reinterpret_cast<XMPMetaRef>(&meta), nullptr, &wResult);

  EXPECT_EQ(GetObjectNameString(meta), "");
}

TEST_F(WXMPMeta_SetObjectName_1_Test_2042, OverwritesPreviouslySetName_2042) {
  WXMP_Result wResult;
  XMPMeta meta;

  WXMPMeta_SetObjectName_1(reinterpret_cast<XMPMetaRef>(&meta), "first", &wResult);
  EXPECT_EQ(GetObjectNameString(meta), "first");

  WXMPMeta_SetObjectName_1(reinterpret_cast<XMPMetaRef>(&meta), "second", &wResult);
  EXPECT_EQ(GetObjectNameString(meta), "second");
}

TEST_F(WXMPMeta_SetObjectName_1_Test_2042, AcceptsLongName_Boundary_2042) {
  WXMP_Result wResult;
  XMPMeta meta;

  // Boundary-ish: large but reasonable C-string payload.
  std::string longName(4096, 'A');

  WXMPMeta_SetObjectName_1(reinterpret_cast<XMPMetaRef>(&meta), longName.c_str(), &wResult);

  EXPECT_EQ(GetObjectNameString(meta), longName);
}

TEST_F(WXMPMeta_SetObjectName_1_Test_2042, InvalidXmpRef_ReportsErrorOrThrows_2042) {
  WXMP_Result wResult;

  // Behavior depends on XMP_ENTER_WRAPPER / WtoXMPMeta_Ptr implementation:
  // - may capture errors into wResult.errMessage
  // - may throw an exception
  // This test validates the call is "error-observable" via either mechanism.
  bool threw = false;
  try {
    WXMPMeta_SetObjectName_1(reinterpret_cast<XMPMetaRef>(nullptr), "name", &wResult);
  } catch (...) {
    threw = true;
  }

  // If it didn't throw, we expect some observable error indication.
  if (!threw) {
    EXPECT_TRUE(wResult.errMessage != nullptr);
  } else {
    SUCCEED();
  }
}

}  // namespace