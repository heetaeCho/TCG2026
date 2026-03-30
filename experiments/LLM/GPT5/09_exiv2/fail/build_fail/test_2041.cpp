// =================================================================================================
// TEST_ID: 2041
// Unit tests for: WXMPMeta_GetObjectName_1
// File: ./TestProjects/exiv2/xmpsdk/src/WXMPMeta.cpp
// =================================================================================================

#include <gtest/gtest.h>

#include <string>
#include <vector>

// XMP SDK headers (project-local)
#include "XMP_Const.h"
#include "XMPMeta.hpp"
#include "client-glue/WXMP_Common.hpp"

// Some builds expose XMPMetaRef via WXMPMeta.hpp; if not available, it is typically a void*.
#if __has_include("client-glue/WXMPMeta.hpp")
#include "client-glue/WXMPMeta.hpp"
#endif

#ifndef XMPMetaRef
using XMPMetaRef = void*;
#endif

// Wrapper under test (C-callable wrapper).
extern "C" {
void WXMPMeta_GetObjectName_1(XMPMetaRef xmpRef, XMP_StringPtr* namePtr, XMP_StringLen* nameLen, WXMP_Result* wResult);
}

namespace {

class WXMPMeta_GetObjectName_1_Test_2041 : public ::testing::Test {
public:
  static void SetUpTestSuite() {
    // The SDK typically requires initialization. We do not assume side effects beyond returning bool.
    (void)XMPMeta::Initialize();
  }

  static void TearDownTestSuite() { XMPMeta::Terminate(); }

protected:
  static XMPMetaRef ToRef(XMPMeta& meta) {
    // Treat as black-box: wrapper converts ref to XMPMeta reference internally.
    // In this SDK, XMPMetaRef is commonly a void* pointing to an XMPMeta instance.
    return reinterpret_cast<XMPMetaRef>(&meta);
  }

  static std::string CopyOutString(XMP_StringPtr ptr, XMP_StringLen len) {
    if (ptr == nullptr) return std::string();
    return std::string(ptr, ptr + static_cast<size_t>(len));
  }
};

}  // namespace

TEST_F(WXMPMeta_GetObjectName_1_Test_2041, ReturnsObjectNameAndLength_2041) {
  XMPMeta meta;
  const std::string expected = "TestObjectName";

  meta.SetObjectName(expected.c_str());

  XMP_StringPtr outPtr = nullptr;
  XMP_StringLen outLen = 0;
  WXMP_Result wResult;

  WXMPMeta_GetObjectName_1(WXMPMeta_GetObjectName_1_Test_2041::ToRef(meta), &outPtr, &outLen, &wResult);

  ASSERT_EQ(wResult.errMessage, nullptr);
  ASSERT_NE(outPtr, nullptr);

  const std::string actual = WXMPMeta_GetObjectName_1_Test_2041::CopyOutString(outPtr, outLen);
  EXPECT_EQ(actual, expected);
  EXPECT_EQ(outLen, static_cast<XMP_StringLen>(expected.size()));
}

TEST_F(WXMPMeta_GetObjectName_1_Test_2041, EmptyObjectNameReturnsEmptyString_2041) {
  XMPMeta meta;
  const std::string expected = "";

  meta.SetObjectName(expected.c_str());

  XMP_StringPtr outPtr = nullptr;
  XMP_StringLen outLen = 999;  // sentinel
  WXMP_Result wResult;

  WXMPMeta_GetObjectName_1(WXMPMeta_GetObjectName_1_Test_2041::ToRef(meta), &outPtr, &outLen, &wResult);

  ASSERT_EQ(wResult.errMessage, nullptr);
  ASSERT_NE(outPtr, nullptr);

  const std::string actual = WXMPMeta_GetObjectName_1_Test_2041::CopyOutString(outPtr, outLen);
  EXPECT_EQ(actual, expected);
  EXPECT_EQ(outLen, static_cast<XMP_StringLen>(expected.size()));
}

TEST_F(WXMPMeta_GetObjectName_1_Test_2041, LongObjectNameReturnsMatchingLength_2041) {
  XMPMeta meta;

  std::string expected;
  expected.reserve(4096);
  for (int i = 0; i < 4096; ++i) expected.push_back(static_cast<char>('a' + (i % 26)));

  meta.SetObjectName(expected.c_str());

  XMP_StringPtr outPtr = nullptr;
  XMP_StringLen outLen = 0;
  WXMP_Result wResult;

  WXMPMeta_GetObjectName_1(WXMPMeta_GetObjectName_1_Test_2041::ToRef(meta), &outPtr, &outLen, &wResult);

  ASSERT_EQ(wResult.errMessage, nullptr);
  ASSERT_NE(outPtr, nullptr);

  const std::string actual = WXMPMeta_GetObjectName_1_Test_2041::CopyOutString(outPtr, outLen);
  EXPECT_EQ(actual.size(), expected.size());
  EXPECT_EQ(actual, expected);
  EXPECT_EQ(outLen, static_cast<XMP_StringLen>(expected.size()));
}

TEST_F(WXMPMeta_GetObjectName_1_Test_2041, NullNamePtrStillUpdatesNameLen_2041) {
  XMPMeta meta;
  const std::string expected = "NameLenOnly";

  meta.SetObjectName(expected.c_str());

  XMP_StringLen outLen = 0;
  WXMP_Result wResult;

  // namePtr is null -> wrapper should internally use a default pointer location.
  WXMPMeta_GetObjectName_1(WXMPMeta_GetObjectName_1_Test_2041::ToRef(meta), nullptr, &outLen, &wResult);

  ASSERT_EQ(wResult.errMessage, nullptr);
  EXPECT_EQ(outLen, static_cast<XMP_StringLen>(expected.size()));
}

TEST_F(WXMPMeta_GetObjectName_1_Test_2041, NullNameLenStillUpdatesNamePtr_2041) {
  XMPMeta meta;
  const std::string expected = "NamePtrOnly";

  meta.SetObjectName(expected.c_str());

  XMP_StringPtr outPtr = nullptr;
  WXMP_Result wResult;

  // nameLen is null -> wrapper should internally use a default length location.
  WXMPMeta_GetObjectName_1(WXMPMeta_GetObjectName_1_Test_2041::ToRef(meta), &outPtr, nullptr, &wResult);

  ASSERT_EQ(wResult.errMessage, nullptr);
  ASSERT_NE(outPtr, nullptr);

  // We don't have a returned length; compare prefix via std::string(expected) length.
  const std::string actual(outPtr, outPtr + expected.size());
  EXPECT_EQ(actual, expected);
}

TEST_F(WXMPMeta_GetObjectName_1_Test_2041, NullNamePtrAndNameLenDoesNotCrash_2041) {
  XMPMeta meta;
  meta.SetObjectName("Anything");

  WXMP_Result wResult;

  // Both outputs null: observable behavior is simply "no crash" and no error if the ref is valid.
  WXMPMeta_GetObjectName_1(WXMPMeta_GetObjectName_1_Test_2041::ToRef(meta), nullptr, nullptr, &wResult);

  EXPECT_EQ(wResult.errMessage, nullptr);
}

TEST_F(WXMPMeta_GetObjectName_1_Test_2041, NullXmpRefReportsError_2041) {
  XMP_StringPtr outPtr = nullptr;
  XMP_StringLen outLen = 0;
  WXMP_Result wResult;

  // Invalid ref: wrapper should report an error through WXMP_Result (observable via errMessage).
  WXMPMeta_GetObjectName_1(nullptr, &outPtr, &outLen, &wResult);

  EXPECT_NE(wResult.errMessage, nullptr);
}