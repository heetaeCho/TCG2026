// =================================================================================================
// TEST_ID: 2029
// Unit tests for WXMPMeta_GetProperty_Date_1
// File: ./TestProjects/exiv2/xmpsdk/src/WXMPMeta.cpp
// =================================================================================================

#include <gtest/gtest.h>

#include <cstring>
#include <string>

#if __has_include("XMP_Const.h")
  #include "XMP_Const.h"
#elif __has_include("../include/XMP_Const.h")
  #include "../include/XMP_Const.h"
#endif

#if __has_include("XMPMeta.hpp")
  #include "XMPMeta.hpp"
#elif __has_include("xmpsdk/src/XMPMeta.hpp")
  #include "xmpsdk/src/XMPMeta.hpp"
#endif

#if __has_include("client-glue/WXMP_Common.hpp")
  #include "client-glue/WXMP_Common.hpp"
#elif __has_include("WXMP_Common.hpp")
  #include "WXMP_Common.hpp"
#endif

// Prefer an official wrapper header if present.
#if __has_include("client-glue/WXMPMeta.hpp")
  #include "client-glue/WXMPMeta.hpp"
#elif __has_include("WXMPMeta.hpp")
  #include "WXMPMeta.hpp"
#endif

// If the project headers did not provide these, define minimal stand-ins.
// (These are interface-level typedefs commonly used by the WXMP C glue.)
#ifndef XMPMetaRef
  typedef void* XMPMetaRef;
#endif

#ifndef XMP_StringPtr
  typedef const char* XMP_StringPtr;
#endif

#ifndef XMP_OptionBits
  typedef unsigned long XMP_OptionBits;
#endif

// Forward-declare the function under test if a header didn't declare it.
extern "C" {
  void WXMPMeta_GetProperty_Date_1(
      XMPMetaRef xmpRef,
      XMP_StringPtr schemaNS,
      XMP_StringPtr propName,
      XMP_DateTime* propValue,
      XMP_OptionBits* options,
      WXMP_Result* wResult);
}

// -------------------------------------------------------------------------------------------------

namespace {

static const char* kSchemaNS_XMP = "http://ns.adobe.com/xap/1.0/";
static const char* kPropName_CreateDate = "CreateDate";

XMP_DateTime MakeDateTime() {
  XMP_DateTime dt;
  std::memset(&dt, 0, sizeof(dt));
  dt.year = 2026;
  dt.month = 2;
  dt.day = 10;
  dt.hour = 12;
  dt.minute = 34;
  dt.second = 56;
  dt.nanoSecond = 123456789;
  dt.tzSign = 1;
  dt.tzHour = 9;
  dt.tzMinute = 0;
  return dt;
}

}  // namespace

class WXMPMetaGetPropertyDate1Test_2029 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Initialize the toolkit if available; ignore return value assumptions.
    // (These are part of the provided interface for XMPMeta.)
    (void)XMPMeta::Initialize();

    meta_ = new XMPMeta();
    xmpRef_ = reinterpret_cast<XMPMetaRef>(meta_);
  }

  void TearDown() override {
    delete meta_;
    meta_ = nullptr;
    xmpRef_ = nullptr;

    XMPMeta::Terminate();
  }

  XMPMeta* meta_{nullptr};
  XMPMetaRef xmpRef_{nullptr};
};

TEST_F(WXMPMetaGetPropertyDate1Test_2029, ReturnsTrueAndOutputsDateWhenPropertyExists_2029) {
  const XMP_DateTime inDT = MakeDateTime();
  meta_->SetProperty_Date(kSchemaNS_XMP, kPropName_CreateDate, inDT, 0);

  XMP_DateTime outDT;
  std::memset(&outDT, 0xA5, sizeof(outDT));  // sentinel
  XMP_OptionBits outOptions = 0;
  WXMP_Result wResult;

  WXMPMeta_GetProperty_Date_1(xmpRef_, kSchemaNS_XMP, kPropName_CreateDate, &outDT, &outOptions, &wResult);

  EXPECT_EQ(wResult.errMessage, nullptr);
  EXPECT_NE(wResult.int32Result, 0u);

  // Observable behavior via public struct contents: returned date-time equals the one set.
  EXPECT_EQ(outDT.year, inDT.year);
  EXPECT_EQ(outDT.month, inDT.month);
  EXPECT_EQ(outDT.day, inDT.day);
  EXPECT_EQ(outDT.hour, inDT.hour);
  EXPECT_EQ(outDT.minute, inDT.minute);
  EXPECT_EQ(outDT.second, inDT.second);
  EXPECT_EQ(outDT.nanoSecond, inDT.nanoSecond);
  EXPECT_EQ(outDT.tzSign, inDT.tzSign);
  EXPECT_EQ(outDT.tzHour, inDT.tzHour);
  EXPECT_EQ(outDT.tzMinute, inDT.tzMinute);
}

TEST_F(WXMPMetaGetPropertyDate1Test_2029, ReturnsFalseWhenPropertyDoesNotExist_2029) {
  XMP_DateTime outDT;
  std::memset(&outDT, 0, sizeof(outDT));
  XMP_OptionBits outOptions = 0;
  WXMP_Result wResult;

  WXMPMeta_GetProperty_Date_1(xmpRef_, kSchemaNS_XMP, "NonExistentDate", &outDT, &outOptions, &wResult);

  EXPECT_EQ(wResult.errMessage, nullptr);
  EXPECT_EQ(wResult.int32Result, 0u);
}

TEST_F(WXMPMetaGetPropertyDate1Test_2029, AcceptsNullPropValuePointerWhenPropertyExists_2029) {
  const XMP_DateTime inDT = MakeDateTime();
  meta_->SetProperty_Date(kSchemaNS_XMP, kPropName_CreateDate, inDT, 0);

  XMP_OptionBits outOptions = 0;
  WXMP_Result wResult;

  // propValue is null; wrapper should not crash and should still report found/not found via int32Result.
  WXMPMeta_GetProperty_Date_1(xmpRef_, kSchemaNS_XMP, kPropName_CreateDate, nullptr, &outOptions, &wResult);

  EXPECT_EQ(wResult.errMessage, nullptr);
  EXPECT_NE(wResult.int32Result, 0u);
}

TEST_F(WXMPMetaGetPropertyDate1Test_2029, AcceptsNullOptionsPointerWhenPropertyExists_2029) {
  const XMP_DateTime inDT = MakeDateTime();
  meta_->SetProperty_Date(kSchemaNS_XMP, kPropName_CreateDate, inDT, 0);

  XMP_DateTime outDT;
  std::memset(&outDT, 0, sizeof(outDT));
  WXMP_Result wResult;

  // options is null; wrapper should not crash and should still return found.
  WXMPMeta_GetProperty_Date_1(xmpRef_, kSchemaNS_XMP, kPropName_CreateDate, &outDT, nullptr, &wResult);

  EXPECT_EQ(wResult.errMessage, nullptr);
  EXPECT_NE(wResult.int32Result, 0u);
}

TEST_F(WXMPMetaGetPropertyDate1Test_2029, ReportsErrorForNullSchemaNamespace_2029) {
  XMP_DateTime outDT;
  std::memset(&outDT, 0, sizeof(outDT));
  XMP_OptionBits outOptions = 0;
  WXMP_Result wResult;

  WXMPMeta_GetProperty_Date_1(xmpRef_, nullptr, kPropName_CreateDate, &outDT, &outOptions, &wResult);

  // Observable error reporting through WXMP_Result (wrapper macros typically catch and store error text).
  EXPECT_NE(wResult.errMessage, nullptr);
  if (wResult.errMessage != nullptr) {
    EXPECT_NE(std::string(wResult.errMessage).size(), 0u);
  }
}

TEST_F(WXMPMetaGetPropertyDate1Test_2029, ReportsErrorForEmptySchemaNamespace_2029) {
  XMP_DateTime outDT;
  std::memset(&outDT, 0, sizeof(outDT));
  XMP_OptionBits outOptions = 0;
  WXMP_Result wResult;

  WXMPMeta_GetProperty_Date_1(xmpRef_, "", kPropName_CreateDate, &outDT, &outOptions, &wResult);

  EXPECT_NE(wResult.errMessage, nullptr);
  if (wResult.errMessage != nullptr) {
    EXPECT_NE(std::string(wResult.errMessage).size(), 0u);
  }
}

TEST_F(WXMPMetaGetPropertyDate1Test_2029, ReportsErrorForNullPropertyName_2029) {
  XMP_DateTime outDT;
  std::memset(&outDT, 0, sizeof(outDT));
  XMP_OptionBits outOptions = 0;
  WXMP_Result wResult;

  WXMPMeta_GetProperty_Date_1(xmpRef_, kSchemaNS_XMP, nullptr, &outDT, &outOptions, &wResult);

  EXPECT_NE(wResult.errMessage, nullptr);
  if (wResult.errMessage != nullptr) {
    EXPECT_NE(std::string(wResult.errMessage).size(), 0u);
  }
}

TEST_F(WXMPMetaGetPropertyDate1Test_2029, ReportsErrorForEmptyPropertyName_2029) {
  XMP_DateTime outDT;
  std::memset(&outDT, 0, sizeof(outDT));
  XMP_OptionBits outOptions = 0;
  WXMP_Result wResult;

  WXMPMeta_GetProperty_Date_1(xmpRef_, kSchemaNS_XMP, "", &outDT, &outOptions, &wResult);

  EXPECT_NE(wResult.errMessage, nullptr);
  if (wResult.errMessage != nullptr) {
    EXPECT_NE(std::string(wResult.errMessage).size(), 0u);
  }
}