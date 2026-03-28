// =================================================================================================
// Unit tests for WXMPMeta_GetLocalizedText_1
// File: ./TestProjects/exiv2/xmpsdk/src/WXMPMeta.cpp
// TEST_ID: 2023
// =================================================================================================

#include <gtest/gtest.h>

#include <cstring>
#include <string>

// These headers are expected to exist in the xmpsdk tree used by Exiv2.
#include "WXMP_Common.hpp"   // WXMP_Result
#include "XMP_Const.h"       // kXMPErr_* (for context; tests avoid depending on internal error plumbing)
#include "XMPMeta.hpp"       // XMPMeta

// The wrapper function under test (implemented in WXMPMeta.cpp).
extern "C" {
void WXMPMeta_GetLocalizedText_1(XMPMetaRef xmpRef,
                                 XMP_StringPtr schemaNS,
                                 XMP_StringPtr arrayName,
                                 XMP_StringPtr genericLang,
                                 XMP_StringPtr specificLang,
                                 XMP_StringPtr* actualLang,
                                 XMP_StringLen* langSize,
                                 XMP_StringPtr* itemValue,
                                 XMP_StringLen* valueSize,
                                 XMP_OptionBits* options,
                                 WXMP_Result* wResult);
}

namespace {

static XMPMetaRef AsMetaRef(XMPMeta& meta) {
  // Treat as black box: only adapt the object pointer into the expected opaque handle type.
  return reinterpret_cast<XMPMetaRef>(&meta);
}

static std::string SafeStr(XMP_StringPtr p, XMP_StringLen n) {
  if (p == nullptr) return std::string();
  return std::string(p, p + n);
}

class WXMPMeta_GetLocalizedText_1_Test_2023 : public ::testing::Test {
 protected:
  XMPMeta meta_;
};

TEST_F(WXMPMeta_GetLocalizedText_1_Test_2023, ReturnsFalseWhenNoSuchAltTextArray_2023) {
  WXMP_Result wResult;
  XMP_StringPtr actualLang = nullptr;
  XMP_StringLen langSize = 0;
  XMP_StringPtr itemValue = nullptr;
  XMP_StringLen valueSize = 0;
  XMP_OptionBits opts = 0;

  WXMPMeta_GetLocalizedText_1(AsMetaRef(meta_),
                             "http://purl.org/dc/elements/1.1/",
                             "dc:title",
                             "en",
                             "en-US",
                             &actualLang,
                             &langSize,
                             &itemValue,
                             &valueSize,
                             &opts,
                             &wResult);

  EXPECT_EQ(wResult.errMessage, nullptr);
  EXPECT_EQ(wResult.int32Result, 0u);  // found == false (observable via wrapper's int32Result)
}

TEST_F(WXMPMeta_GetLocalizedText_1_Test_2023, GetsPreviouslySetLocalizedText_2023) {
  // Arrange: create an alt-text value using the public XMPMeta interface.
  // (No assumptions about internal structure; only observable behavior through API.)
  meta_.SetLocalizedText("http://purl.org/dc/elements/1.1/", "dc:title",
                         "en", "en-US", "Hello", 0);

  WXMP_Result wResult;
  XMP_StringPtr actualLang = nullptr;
  XMP_StringLen langSize = 0;
  XMP_StringPtr itemValue = nullptr;
  XMP_StringLen valueSize = 0;
  XMP_OptionBits opts = 0;

  WXMPMeta_GetLocalizedText_1(AsMetaRef(meta_),
                             "http://purl.org/dc/elements/1.1/",
                             "dc:title",
                             "en",
                             "en-US",
                             &actualLang,
                             &langSize,
                             &itemValue,
                             &valueSize,
                             &opts,
                             &wResult);

  EXPECT_EQ(wResult.errMessage, nullptr);
  EXPECT_EQ(wResult.int32Result, 1u);  // found == true

  ASSERT_NE(actualLang, nullptr);
  ASSERT_NE(itemValue, nullptr);

  // Value should match what was set.
  EXPECT_EQ(SafeStr(itemValue, valueSize), "Hello");

  // The returned language should be a non-empty string (exact fallback rules are not assumed).
  EXPECT_GT(langSize, 0u);
  EXPECT_FALSE(SafeStr(actualLang, langSize).empty());
}

TEST_F(WXMPMeta_GetLocalizedText_1_Test_2023, AcceptsNullGenericLangTreatsAsEmpty_2023) {
  meta_.SetLocalizedText("http://purl.org/dc/elements/1.1/", "dc:title",
                         "", "en-US", "Hello2", 0);

  WXMP_Result wResult;
  XMP_StringPtr actualLang = nullptr;
  XMP_StringLen langSize = 0;
  XMP_StringPtr itemValue = nullptr;
  XMP_StringLen valueSize = 0;
  XMP_OptionBits opts = 0;

  // genericLang is allowed to be null by the wrapper (it replaces with "").
  WXMPMeta_GetLocalizedText_1(AsMetaRef(meta_),
                             "http://purl.org/dc/elements/1.1/",
                             "dc:title",
                             nullptr,
                             "en-US",
                             &actualLang,
                             &langSize,
                             &itemValue,
                             &valueSize,
                             &opts,
                             &wResult);

  EXPECT_EQ(wResult.errMessage, nullptr);
  EXPECT_EQ(wResult.int32Result, 1u);
  EXPECT_EQ(SafeStr(itemValue, valueSize), "Hello2");
}

TEST_F(WXMPMeta_GetLocalizedText_1_Test_2023, NullOutputPointersAreAllowedAndDoNotCrash_2023) {
  meta_.SetLocalizedText("http://purl.org/dc/elements/1.1/", "dc:title",
                         "en", "en-US", "Hello3", 0);

  WXMP_Result wResult;

  // All output pointers except wResult are intentionally nullptr to exercise wrapper defaults.
  WXMPMeta_GetLocalizedText_1(AsMetaRef(meta_),
                             "http://purl.org/dc/elements/1.1/",
                             "dc:title",
                             "en",
                             "en-US",
                             nullptr,
                             nullptr,
                             nullptr,
                             nullptr,
                             nullptr,
                             &wResult);

  EXPECT_EQ(wResult.errMessage, nullptr);
  EXPECT_EQ(wResult.int32Result, 1u);
}

TEST_F(WXMPMeta_GetLocalizedText_1_Test_2023, ErrorWhenSchemaNSIsNull_2023) {
  WXMP_Result wResult;
  XMP_StringPtr actualLang = nullptr;
  XMP_StringLen langSize = 0;
  XMP_StringPtr itemValue = nullptr;
  XMP_StringLen valueSize = 0;
  XMP_OptionBits opts = 0;

  WXMPMeta_GetLocalizedText_1(AsMetaRef(meta_),
                             nullptr,         // schemaNS
                             "dc:title",
                             "en",
                             "en-US",
                             &actualLang,
                             &langSize,
                             &itemValue,
                             &valueSize,
                             &opts,
                             &wResult);

  ASSERT_NE(wResult.errMessage, nullptr);
  EXPECT_NE(std::string(wResult.errMessage).find("Empty schema namespace URI"), std::string::npos);
}

TEST_F(WXMPMeta_GetLocalizedText_1_Test_2023, ErrorWhenSchemaNSIsEmpty_2023) {
  WXMP_Result wResult;
  XMP_StringPtr actualLang = nullptr;
  XMP_StringLen langSize = 0;
  XMP_StringPtr itemValue = nullptr;
  XMP_StringLen valueSize = 0;
  XMP_OptionBits opts = 0;

  WXMPMeta_GetLocalizedText_1(AsMetaRef(meta_),
                             "",              // empty schemaNS
                             "dc:title",
                             "en",
                             "en-US",
                             &actualLang,
                             &langSize,
                             &itemValue,
                             &valueSize,
                             &opts,
                             &wResult);

  ASSERT_NE(wResult.errMessage, nullptr);
  EXPECT_NE(std::string(wResult.errMessage).find("Empty schema namespace URI"), std::string::npos);
}

TEST_F(WXMPMeta_GetLocalizedText_1_Test_2023, ErrorWhenArrayNameIsNull_2023) {
  WXMP_Result wResult;
  XMP_StringPtr actualLang = nullptr;
  XMP_StringLen langSize = 0;
  XMP_StringPtr itemValue = nullptr;
  XMP_StringLen valueSize = 0;
  XMP_OptionBits opts = 0;

  WXMPMeta_GetLocalizedText_1(AsMetaRef(meta_),
                             "http://purl.org/dc/elements/1.1/",
                             nullptr,         // arrayName
                             "en",
                             "en-US",
                             &actualLang,
                             &langSize,
                             &itemValue,
                             &valueSize,
                             &opts,
                             &wResult);

  ASSERT_NE(wResult.errMessage, nullptr);
  EXPECT_NE(std::string(wResult.errMessage).find("Empty array name"), std::string::npos);
}

TEST_F(WXMPMeta_GetLocalizedText_1_Test_2023, ErrorWhenArrayNameIsEmpty_2023) {
  WXMP_Result wResult;
  XMP_StringPtr actualLang = nullptr;
  XMP_StringLen langSize = 0;
  XMP_StringPtr itemValue = nullptr;
  XMP_StringLen valueSize = 0;
  XMP_OptionBits opts = 0;

  WXMPMeta_GetLocalizedText_1(AsMetaRef(meta_),
                             "http://purl.org/dc/elements/1.1/",
                             "",              // empty arrayName
                             "en",
                             "en-US",
                             &actualLang,
                             &langSize,
                             &itemValue,
                             &valueSize,
                             &opts,
                             &wResult);

  ASSERT_NE(wResult.errMessage, nullptr);
  EXPECT_NE(std::string(wResult.errMessage).find("Empty array name"), std::string::npos);
}

TEST_F(WXMPMeta_GetLocalizedText_1_Test_2023, ErrorWhenSpecificLangIsNull_2023) {
  WXMP_Result wResult;
  XMP_StringPtr actualLang = nullptr;
  XMP_StringLen langSize = 0;
  XMP_StringPtr itemValue = nullptr;
  XMP_StringLen valueSize = 0;
  XMP_OptionBits opts = 0;

  WXMPMeta_GetLocalizedText_1(AsMetaRef(meta_),
                             "http://purl.org/dc/elements/1.1/",
                             "dc:title",
                             "en",
                             nullptr,         // specificLang
                             &actualLang,
                             &langSize,
                             &itemValue,
                             &valueSize,
                             &opts,
                             &wResult);

  ASSERT_NE(wResult.errMessage, nullptr);
  EXPECT_NE(std::string(wResult.errMessage).find("Empty specific language"), std::string::npos);
}

TEST_F(WXMPMeta_GetLocalizedText_1_Test_2023, ErrorWhenSpecificLangIsEmpty_2023) {
  WXMP_Result wResult;
  XMP_StringPtr actualLang = nullptr;
  XMP_StringLen langSize = 0;
  XMP_StringPtr itemValue = nullptr;
  XMP_StringLen valueSize = 0;
  XMP_OptionBits opts = 0;

  WXMPMeta_GetLocalizedText_1(AsMetaRef(meta_),
                             "http://purl.org/dc/elements/1.1/",
                             "dc:title",
                             "en",
                             "",              // empty specificLang
                             &actualLang,
                             &langSize,
                             &itemValue,
                             &valueSize,
                             &opts,
                             &wResult);

  ASSERT_NE(wResult.errMessage, nullptr);
  EXPECT_NE(std::string(wResult.errMessage).find("Empty specific language"), std::string::npos);
}

}  // namespace