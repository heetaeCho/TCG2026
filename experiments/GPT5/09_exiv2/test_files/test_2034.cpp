// SPDX-License-Identifier: GPL-2.0-or-later
// TEST_ID 2034
//
// Unit tests for WXMPMeta_SetProperty_Date_1 wrapper.
//
// Constraints reminder (applied):
// - Treat implementation as a black box.
// - Assert only observable behavior via public interface (GetProperty_Date / errMessage).

#include <gtest/gtest.h>

#include <cstring>

#include "XMP_Const.h"
#include "XMPMeta.hpp"
#include "client-glue/WXMP_Common.hpp"

// The wrapper under test is implemented in WXMPMeta.cpp (already built in the codebase).
// We include the declaration here to avoid relying on any particular wrapper header layout.
extern "C" {
void WXMPMeta_SetProperty_Date_1(XMPMetaRef xmpRef, XMP_StringPtr schemaNS, XMP_StringPtr propName,
                                const XMP_DateTime& propValue, XMP_OptionBits options, WXMP_Result* wResult);
}

namespace {

class WXMPMeta_SetProperty_Date_1_Test_2034 : public ::testing::Test {
 protected:
  void SetUp() override {
    meta_ = new XMPMeta();
    // In the XMP SDK wrappers, XMPMetaRef is an opaque handle; in practice it is compatible with passing
    // the XMPMeta* through the wrapper and then converting back internally.
    xmpRef_ = reinterpret_cast<XMPMetaRef>(meta_);
  }

  void TearDown() override {
    delete meta_;
    meta_ = nullptr;
    xmpRef_ = nullptr;
  }

  static XMP_DateTime MakeDate(int year, int month, int day, int hour, int minute, int second) {
    XMP_DateTime dt{};
    dt.year = year;
    dt.month = month;
    dt.day = day;
    dt.hour = hour;
    dt.minute = minute;
    dt.second = second;
    dt.tzSign = 0;
    dt.tzHour = 0;
    dt.tzMinute = 0;
    dt.nanoSecond = 0;
    return dt;
  }

  static bool StrNonEmpty(XMP_StringPtr s) { return (s != nullptr) && (*s != 0); }

  XMPMeta* meta_{nullptr};
  XMPMetaRef xmpRef_{nullptr};
};

TEST_F(WXMPMeta_SetProperty_Date_1_Test_2034, SetsDatePropertyAndCanReadBack_2034) {
  WXMP_Result wResult;

  const char* kSchema = "http://ns.adobe.com/xap/1.0/";
  const char* kProp = "CreateDate";

  const XMP_DateTime in = MakeDate(2024, 2, 29, 12, 34, 56);

  EXPECT_NO_THROW(WXMPMeta_SetProperty_Date_1(xmpRef_, kSchema, kProp, in, 0 /* options */, &wResult));
  EXPECT_FALSE(StrNonEmpty(wResult.errMessage)) << "Wrapper reported an unexpected error message";

  XMP_DateTime out{};
  XMP_OptionBits gotOptions = 0;
  const bool ok = meta_->GetProperty_Date(kSchema, kProp, &out, &gotOptions);
  EXPECT_TRUE(ok);

  EXPECT_EQ(out.year, in.year);
  EXPECT_EQ(out.month, in.month);
  EXPECT_EQ(out.day, in.day);
  EXPECT_EQ(out.hour, in.hour);
  EXPECT_EQ(out.minute, in.minute);
  EXPECT_EQ(out.second, in.second);
}

TEST_F(WXMPMeta_SetProperty_Date_1_Test_2034, OverwritesExistingDateProperty_2034) {
  WXMP_Result wResult;

  const char* kSchema = "http://ns.adobe.com/xap/1.0/";
  const char* kProp = "ModifyDate";

  const XMP_DateTime first = MakeDate(2020, 1, 2, 3, 4, 5);
  const XMP_DateTime second = MakeDate(2025, 12, 31, 23, 59, 58);

  ASSERT_NO_THROW(WXMPMeta_SetProperty_Date_1(xmpRef_, kSchema, kProp, first, 0 /* options */, &wResult));
  ASSERT_FALSE(StrNonEmpty(wResult.errMessage));

  ASSERT_NO_THROW(WXMPMeta_SetProperty_Date_1(xmpRef_, kSchema, kProp, second, 0 /* options */, &wResult));
  EXPECT_FALSE(StrNonEmpty(wResult.errMessage));

  XMP_DateTime out{};
  XMP_OptionBits gotOptions = 0;
  const bool ok = meta_->GetProperty_Date(kSchema, kProp, &out, &gotOptions);
  EXPECT_TRUE(ok);

  EXPECT_EQ(out.year, second.year);
  EXPECT_EQ(out.month, second.month);
  EXPECT_EQ(out.day, second.day);
  EXPECT_EQ(out.hour, second.hour);
  EXPECT_EQ(out.minute, second.minute);
  EXPECT_EQ(out.second, second.second);
}

TEST_F(WXMPMeta_SetProperty_Date_1_Test_2034, AcceptsTimezoneFieldsAsPartOfDateTime_2034) {
  WXMP_Result wResult;

  const char* kSchema = "http://ns.adobe.com/xap/1.0/";
  const char* kProp = "MetadataDate";

  XMP_DateTime in{};
  in.year = 2023;
  in.month = 7;
  in.day = 8;
  in.hour = 9;
  in.minute = 10;
  in.second = 11;
  in.tzSign = -1;
  in.tzHour = 9;
  in.tzMinute = 0;
  in.nanoSecond = 123456789;

  EXPECT_NO_THROW(WXMPMeta_SetProperty_Date_1(xmpRef_, kSchema, kProp, in, 0 /* options */, &wResult));
  EXPECT_FALSE(StrNonEmpty(wResult.errMessage));

  XMP_DateTime out{};
  XMP_OptionBits gotOptions = 0;
  const bool ok = meta_->GetProperty_Date(kSchema, kProp, &out, &gotOptions);
  EXPECT_TRUE(ok);

  // Observable behavior: the public getter returns a date/time; compare fields.
  EXPECT_EQ(out.year, in.year);
  EXPECT_EQ(out.month, in.month);
  EXPECT_EQ(out.day, in.day);
  EXPECT_EQ(out.hour, in.hour);
  EXPECT_EQ(out.minute, in.minute);
  EXPECT_EQ(out.second, in.second);
  EXPECT_EQ(out.tzSign, in.tzSign);
  EXPECT_EQ(out.tzHour, in.tzHour);
  EXPECT_EQ(out.tzMinute, in.tzMinute);
  EXPECT_EQ(out.nanoSecond, in.nanoSecond);
}

TEST_F(WXMPMeta_SetProperty_Date_1_Test_2034, EmptySchemaNamespaceReportsError_2034) {
  WXMP_Result wResult;

  const char* kSchema = "";  // boundary: empty string
  const char* kProp = "CreateDate";
  const XMP_DateTime in = MakeDate(2024, 1, 1, 0, 0, 0);

  EXPECT_NO_THROW(WXMPMeta_SetProperty_Date_1(xmpRef_, kSchema, kProp, in, 0 /* options */, &wResult));
  EXPECT_TRUE(StrNonEmpty(wResult.errMessage));

  // Observable behavior: property should not become readable if the call failed.
  XMP_DateTime out{};
  XMP_OptionBits gotOptions = 0;
  const bool ok = meta_->GetProperty_Date(kSchema, kProp, &out, &gotOptions);
  EXPECT_FALSE(ok);
}

TEST_F(WXMPMeta_SetProperty_Date_1_Test_2034, NullSchemaNamespaceReportsError_2034) {
  WXMP_Result wResult;

  const char* kProp = "CreateDate";
  const XMP_DateTime in = MakeDate(2024, 1, 1, 0, 0, 0);

  EXPECT_NO_THROW(WXMPMeta_SetProperty_Date_1(xmpRef_, nullptr, kProp, in, 0 /* options */, &wResult));
  EXPECT_TRUE(StrNonEmpty(wResult.errMessage));
}

TEST_F(WXMPMeta_SetProperty_Date_1_Test_2034, EmptyPropertyNameReportsError_2034) {
  WXMP_Result wResult;

  const char* kSchema = "http://ns.adobe.com/xap/1.0/";
  const char* kProp = "";  // boundary: empty string
  const XMP_DateTime in = MakeDate(2024, 1, 1, 0, 0, 0);

  EXPECT_NO_THROW(WXMPMeta_SetProperty_Date_1(xmpRef_, kSchema, kProp, in, 0 /* options */, &wResult));
  EXPECT_TRUE(StrNonEmpty(wResult.errMessage));
}

TEST_F(WXMPMeta_SetProperty_Date_1_Test_2034, NullPropertyNameReportsError_2034) {
  WXMP_Result wResult;

  const char* kSchema = "http://ns.adobe.com/xap/1.0/";
  const XMP_DateTime in = MakeDate(2024, 1, 1, 0, 0, 0);

  EXPECT_NO_THROW(WXMPMeta_SetProperty_Date_1(xmpRef_, kSchema, nullptr, in, 0 /* options */, &wResult));
  EXPECT_TRUE(StrNonEmpty(wResult.errMessage));
}

}  // namespace