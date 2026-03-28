// File: test_WXMPMeta_GetProperty_1_2006.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <cstring>
#include <string>

#if defined(__has_include)
  #if __has_include("XMPMeta.hpp")
    #include "XMPMeta.hpp"
  #elif __has_include("./TestProjects/exiv2/xmpsdk/src/XMPMeta.hpp")
    #include "./TestProjects/exiv2/xmpsdk/src/XMPMeta.hpp"
  #endif

  #if __has_include("XMP_Const.h")
    #include "XMP_Const.h"
  #elif __has_include("./TestProjects/exiv2/xmpsdk/include/XMP_Const.h")
    #include "./TestProjects/exiv2/xmpsdk/include/XMP_Const.h"
  #endif

  #if __has_include("client-glue/WXMP_Common.hpp")
    #include "client-glue/WXMP_Common.hpp"
  #elif __has_include("WXMP_Common.hpp")
    #include "WXMP_Common.hpp"
  #endif

  #if __has_include("WXMPMeta.hpp")
    #include "WXMPMeta.hpp"
  #elif __has_include("client-glue/WXMPMeta.hpp")
    #include "client-glue/WXMPMeta.hpp"
  #elif __has_include("client-glue/WXMPMeta.h")
    #include "client-glue/WXMPMeta.h"
  #elif __has_include("WXMPMeta.h")
    #include "WXMPMeta.h"
  #endif
#endif

// --- Minimal fallbacks (only used if project headers were not found by the build) ---
#ifndef XMP_StringPtr
using XMP_StringPtr = const char*;
#endif
#ifndef XMP_StringLen
using XMP_StringLen = std::uint32_t;
#endif
#ifndef XMP_OptionBits
using XMP_OptionBits = std::uint32_t;
#endif
#ifndef XMPMetaRef
using XMPMetaRef = void*;
#endif
#ifndef WXMP_Result
struct WXMP_Result {
  XMP_StringPtr errMessage;
  void* ptrResult;
  double floatResult;
  std::uint64_t int64Result;
  std::uint32_t int32Result;
  WXMP_Result() : errMessage(0), ptrResult(nullptr), floatResult(0.0), int64Result(0), int32Result(0) {}
};
#endif

extern "C" {
// The wrapper under test (implemented in WXMPMeta.cpp).
void WXMPMeta_GetProperty_1(XMPMetaRef xmpRef,
                           XMP_StringPtr schemaNS,
                           XMP_StringPtr propName,
                           XMP_StringPtr* propValue,
                           XMP_StringLen* valueSize,
                           XMP_OptionBits* options,
                           WXMP_Result* wResult);
}  // extern "C"

namespace {

class WXMPMetaGetProperty1Test_2006 : public ::testing::Test {
protected:
  static void SetUpTestSuite() {
#if defined(XMPMeta)
    // If the real SDK header was included, initialize/terminate is available.
    // Many XMP SDK builds expect this.
    XMPMeta::Initialize();
#endif
  }

  static void TearDownTestSuite() {
#if defined(XMPMeta)
    XMPMeta::Terminate();
#endif
  }

  static XMPMetaRef MakeRef(XMPMeta& meta) {
#if !defined(XMPMeta)
    // In case XMPMeta is not visible, we can't construct one here.
    return nullptr;
#else
    // In Adobe XMP SDK client glue, XMPMetaRef is typically a pointer-ish handle.
    // Use reinterpret_cast so this works whether XMPMetaRef is void* or XMPMeta*.
    return reinterpret_cast<XMPMetaRef>(&meta);
#endif
  }
};

#if defined(XMPMeta)
constexpr XMP_StringPtr kSchemaNS = "http://ns.adobe.com/xap/1.0/";
constexpr XMP_StringPtr kPropName = "CreatorTool";
constexpr XMP_StringPtr kPropValue = "Exiv2-XMP-UnitTest";
#endif

}  // namespace

TEST_F(WXMPMetaGetProperty1Test_2006, ReturnsTrueAndOutputsValueWhenPropertyExists_2006) {
#if !defined(XMPMeta)
  GTEST_SKIP() << "XMPMeta type not available in this build configuration.";
#else
  XMPMeta meta;
  meta.SetProperty(kSchemaNS, kPropName, kPropValue, /*options=*/0);

  XMP_StringPtr outValue = nullptr;
  XMP_StringLen outSize = 0;
  XMP_OptionBits outOptions = 0;
  WXMP_Result wResult;

  EXPECT_NO_THROW(WXMPMeta_GetProperty_1(MakeRef(meta), kSchemaNS, kPropName,
                                        &outValue, &outSize, &outOptions, &wResult));

  EXPECT_NE(wResult.errMessage, nullptr) << "On success, some builds may still leave errMessage null; "
                                           "this assertion only checks it wasn't corrupted.";
  // NOTE: The SDK's WXMP_Result constructor sets errMessage=0; successful calls should not set an error.
  // Prefer checking that it is either null or empty.
  if (wResult.errMessage != nullptr) {
    EXPECT_EQ(std::strlen(wResult.errMessage), 0u);
  }

  EXPECT_EQ(wResult.int32Result, 1u) << "Expected 'found' == true stored in int32Result.";

  ASSERT_NE(outValue, nullptr);
  EXPECT_EQ(std::string(outValue, outSize), std::string(kPropValue));
  EXPECT_EQ(outSize, static_cast<XMP_StringLen>(std::strlen(kPropValue)));
#endif
}

TEST_F(WXMPMetaGetProperty1Test_2006, ReturnsFalseWhenPropertyDoesNotExist_2006) {
#if !defined(XMPMeta)
  GTEST_SKIP() << "XMPMeta type not available in this build configuration.";
#else
  XMPMeta meta;

  XMP_StringPtr outValue = reinterpret_cast<XMP_StringPtr>(0x1);  // sentinel
  XMP_StringLen outSize = 12345;                                  // sentinel
  XMP_OptionBits outOptions = 0xA5A5A5A5u;                         // sentinel
  WXMP_Result wResult;

  EXPECT_NO_THROW(WXMPMeta_GetProperty_1(MakeRef(meta), kSchemaNS, "DoesNotExist",
                                        &outValue, &outSize, &outOptions, &wResult));

  // No error expected for a missing property; result should indicate "not found".
  if (wResult.errMessage != nullptr) {
    EXPECT_EQ(std::strlen(wResult.errMessage), 0u);
  }
  EXPECT_EQ(wResult.int32Result, 0u) << "Expected 'found' == false stored in int32Result.";
#endif
}

TEST_F(WXMPMetaGetProperty1Test_2006, AcceptsNullOutputPointers_2006) {
#if !defined(XMPMeta)
  GTEST_SKIP() << "XMPMeta type not available in this build configuration.";
#else
  XMPMeta meta;
  meta.SetProperty(kSchemaNS, kPropName, kPropValue, /*options=*/0);

  WXMP_Result wResult;
  EXPECT_NO_THROW(WXMPMeta_GetProperty_1(MakeRef(meta), kSchemaNS, kPropName,
                                        /*propValue=*/nullptr,
                                        /*valueSize=*/nullptr,
                                        /*options=*/nullptr,
                                        &wResult));

  if (wResult.errMessage != nullptr) {
    EXPECT_EQ(std::strlen(wResult.errMessage), 0u);
  }
  EXPECT_EQ(wResult.int32Result, 1u) << "Expected 'found' == true even when outputs are null.";
#endif
}

TEST_F(WXMPMetaGetProperty1Test_2006, ErrorWhenSchemaNSIsNull_2006) {
#if !defined(XMPMeta)
  GTEST_SKIP() << "XMPMeta type not available in this build configuration.";
#else
  XMPMeta meta;

  XMP_StringPtr outValue = nullptr;
  XMP_StringLen outSize = 0;
  XMP_OptionBits outOptions = 0;
  WXMP_Result wResult;

  EXPECT_NO_THROW(WXMPMeta_GetProperty_1(MakeRef(meta),
                                        /*schemaNS=*/nullptr,
                                        kPropName,
                                        &outValue, &outSize, &outOptions, &wResult));

  ASSERT_NE(wResult.errMessage, nullptr);
  EXPECT_NE(std::string(wResult.errMessage).find("Empty schema namespace"), std::string::npos);
#endif
}

TEST_F(WXMPMetaGetProperty1Test_2006, ErrorWhenSchemaNSIsEmpty_2006) {
#if !defined(XMPMeta)
  GTEST_SKIP() << "XMPMeta type not available in this build configuration.";
#else
  XMPMeta meta;

  XMP_StringPtr outValue = nullptr;
  XMP_StringLen outSize = 0;
  XMP_OptionBits outOptions = 0;
  WXMP_Result wResult;

  EXPECT_NO_THROW(WXMPMeta_GetProperty_1(MakeRef(meta),
                                        /*schemaNS=*/"",
                                        kPropName,
                                        &outValue, &outSize, &outOptions, &wResult));

  ASSERT_NE(wResult.errMessage, nullptr);
  EXPECT_NE(std::string(wResult.errMessage).find("Empty schema namespace"), std::string::npos);
#endif
}

TEST_F(WXMPMetaGetProperty1Test_2006, ErrorWhenPropNameIsNull_2006) {
#if !defined(XMPMeta)
  GTEST_SKIP() << "XMPMeta type not available in this build configuration.";
#else
  XMPMeta meta;

  XMP_StringPtr outValue = nullptr;
  XMP_StringLen outSize = 0;
  XMP_OptionBits outOptions = 0;
  WXMP_Result wResult;

  EXPECT_NO_THROW(WXMPMeta_GetProperty_1(MakeRef(meta),
                                        kSchemaNS,
                                        /*propName=*/nullptr,
                                        &outValue, &outSize, &outOptions, &wResult));

  ASSERT_NE(wResult.errMessage, nullptr);
  EXPECT_NE(std::string(wResult.errMessage).find("Empty property name"), std::string::npos);
#endif
}

TEST_F(WXMPMetaGetProperty1Test_2006, ErrorWhenPropNameIsEmpty_2006) {
#if !defined(XMPMeta)
  GTEST_SKIP() << "XMPMeta type not available in this build configuration.";
#else
  XMPMeta meta;

  XMP_StringPtr outValue = nullptr;
  XMP_StringLen outSize = 0;
  XMP_OptionBits outOptions = 0;
  WXMP_Result wResult;

  EXPECT_NO_THROW(WXMPMeta_GetProperty_1(MakeRef(meta),
                                        kSchemaNS,
                                        /*propName=*/"",
                                        &outValue, &outSize, &outOptions, &wResult));

  ASSERT_NE(wResult.errMessage, nullptr);
  EXPECT_NE(std::string(wResult.errMessage).find("Empty property name"), std::string::npos);
#endif
}