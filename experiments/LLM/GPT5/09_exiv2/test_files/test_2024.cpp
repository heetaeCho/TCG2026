// =================================================================================================
// Copyright
// Unit tests for WXMPMeta_SetLocalizedText_1
// TEST_ID: 2024
// =================================================================================================

#include <gtest/gtest.h>

#include <cstring>
#include <string>

#include "XMP_Const.h"
#include "WXMP_Common.hpp"
#include "XMPMeta.hpp"

// Wrapper under test (from WXMPMeta.cpp)
extern "C" void WXMPMeta_SetLocalizedText_1(
    XMPMetaRef xmpRef,
    XMP_StringPtr schemaNS,
    XMP_StringPtr arrayName,
    XMP_StringPtr genericLang,
    XMP_StringPtr specificLang,
    XMP_StringPtr itemValue,
    XMP_OptionBits options,
    WXMP_Result* wResult);

namespace {

class WXMPMeta_SetLocalizedText_1_Test_2024 : public ::testing::Test {
 protected:
  void SetUp() override {
    meta_ = new XMPMeta();
    xmpRef_ = reinterpret_cast<XMPMetaRef>(meta_);
  }

  void TearDown() override {
    delete meta_;
    meta_ = nullptr;
    xmpRef_ = nullptr;
  }

  static constexpr XMP_StringPtr kSchemaNS = "http://purl.org/dc/elements/1.1/";
  static constexpr XMP_StringPtr kArrayName = "dc:title";

  XMPMeta* meta_{nullptr};
  XMPMetaRef xmpRef_{nullptr};
};

TEST_F(WXMPMeta_SetLocalizedText_1_Test_2024, RejectsNullSchemaNS_2024) {
  WXMP_Result wr;
  WXMPMeta_SetLocalizedText_1(xmpRef_, /*schemaNS*/ nullptr, kArrayName,
                             /*genericLang*/ "en", /*specificLang*/ "en-US",
                             /*itemValue*/ "Hello", /*options*/ 0, &wr);

  EXPECT_NE(wr.errMessage, nullptr);
}

TEST_F(WXMPMeta_SetLocalizedText_1_Test_2024, RejectsEmptySchemaNS_2024) {
  WXMP_Result wr;
  WXMPMeta_SetLocalizedText_1(xmpRef_, /*schemaNS*/ "", kArrayName,
                             /*genericLang*/ "en", /*specificLang*/ "en-US",
                             /*itemValue*/ "Hello", /*options*/ 0, &wr);

  EXPECT_NE(wr.errMessage, nullptr);
}

TEST_F(WXMPMeta_SetLocalizedText_1_Test_2024, RejectsNullArrayName_2024) {
  WXMP_Result wr;
  WXMPMeta_SetLocalizedText_1(xmpRef_, kSchemaNS, /*arrayName*/ nullptr,
                             /*genericLang*/ "en", /*specificLang*/ "en-US",
                             /*itemValue*/ "Hello", /*options*/ 0, &wr);

  EXPECT_NE(wr.errMessage, nullptr);
}

TEST_F(WXMPMeta_SetLocalizedText_1_Test_2024, RejectsEmptyArrayName_2024) {
  WXMP_Result wr;
  WXMPMeta_SetLocalizedText_1(xmpRef_, kSchemaNS, /*arrayName*/ "",
                             /*genericLang*/ "en", /*specificLang*/ "en-US",
                             /*itemValue*/ "Hello", /*options*/ 0, &wr);

  EXPECT_NE(wr.errMessage, nullptr);
}

TEST_F(WXMPMeta_SetLocalizedText_1_Test_2024, RejectsNullSpecificLang_2024) {
  WXMP_Result wr;
  WXMPMeta_SetLocalizedText_1(xmpRef_, kSchemaNS, kArrayName,
                             /*genericLang*/ "en", /*specificLang*/ nullptr,
                             /*itemValue*/ "Hello", /*options*/ 0, &wr);

  EXPECT_NE(wr.errMessage, nullptr);
}

TEST_F(WXMPMeta_SetLocalizedText_1_Test_2024, RejectsEmptySpecificLang_2024) {
  WXMP_Result wr;
  WXMPMeta_SetLocalizedText_1(xmpRef_, kSchemaNS, kArrayName,
                             /*genericLang*/ "en", /*specificLang*/ "",
                             /*itemValue*/ "Hello", /*options*/ 0, &wr);

  EXPECT_NE(wr.errMessage, nullptr);
}

TEST_F(WXMPMeta_SetLocalizedText_1_Test_2024, SetsLocalizedTextAndCanReadBack_2024) {
  WXMP_Result wr;

  const char* genericLang = "en";
  const char* specificLang = "en-US";
  const char* value = "Hello";

  WXMPMeta_SetLocalizedText_1(xmpRef_, kSchemaNS, kArrayName, genericLang, specificLang, value,
                             /*options*/ 0, &wr);

  EXPECT_EQ(wr.errMessage, nullptr);

  XMP_StringPtr actualLang = nullptr;
  XMP_StringLen actualLangSize = 0;
  XMP_StringPtr itemValue = nullptr;
  XMP_StringLen valueSize = 0;
  XMP_OptionBits opts = 0;

  const bool ok = meta_->GetLocalizedText(kSchemaNS, kArrayName, genericLang, specificLang,
                                         &actualLang, &actualLangSize, &itemValue, &valueSize, &opts);
  EXPECT_TRUE(ok);
  ASSERT_NE(itemValue, nullptr);
  EXPECT_EQ(std::string(itemValue, valueSize), std::string(value));
}

TEST_F(WXMPMeta_SetLocalizedText_1_Test_2024, NullGenericLangIsAccepted_2024) {
  WXMP_Result wr;

  const char* specificLang = "en-US";
  const char* value = "Hello";

  WXMPMeta_SetLocalizedText_1(xmpRef_, kSchemaNS, kArrayName,
                             /*genericLang*/ nullptr, /*specificLang*/ specificLang,
                             /*itemValue*/ value, /*options*/ 0, &wr);

  EXPECT_EQ(wr.errMessage, nullptr);

  // Read back using the same specificLang; pass nullptr genericLang to mirror wrapper boundary.
  XMP_StringPtr actualLang = nullptr;
  XMP_StringLen actualLangSize = 0;
  XMP_StringPtr itemValue = nullptr;
  XMP_StringLen valueSize = 0;
  XMP_OptionBits opts = 0;

  const bool ok = meta_->GetLocalizedText(kSchemaNS, kArrayName, /*genericLang*/ nullptr, specificLang,
                                         &actualLang, &actualLangSize, &itemValue, &valueSize, &opts);
  EXPECT_TRUE(ok);
  ASSERT_NE(itemValue, nullptr);
  EXPECT_EQ(std::string(itemValue, valueSize), std::string(value));
}

TEST_F(WXMPMeta_SetLocalizedText_1_Test_2024, NullItemValueIsTreatedAsEmptyString_2024) {
  WXMP_Result wr;

  const char* genericLang = "en";
  const char* specificLang = "en-US";

  WXMPMeta_SetLocalizedText_1(xmpRef_, kSchemaNS, kArrayName, genericLang, specificLang,
                             /*itemValue*/ nullptr, /*options*/ 0, &wr);

  EXPECT_EQ(wr.errMessage, nullptr);

  XMP_StringPtr actualLang = nullptr;
  XMP_StringLen actualLangSize = 0;
  XMP_StringPtr itemValue = nullptr;
  XMP_StringLen valueSize = 0;
  XMP_OptionBits opts = 0;

  const bool ok = meta_->GetLocalizedText(kSchemaNS, kArrayName, genericLang, specificLang,
                                         &actualLang, &actualLangSize, &itemValue, &valueSize, &opts);
  EXPECT_TRUE(ok);
  ASSERT_NE(itemValue, nullptr);
  EXPECT_EQ(std::string(itemValue, valueSize), std::string(""));  // empty
}

}  // namespace