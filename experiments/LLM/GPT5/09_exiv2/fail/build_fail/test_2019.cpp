// File: test_WXMPMeta_DoesPropertyExist_1_2019.cpp
// Unit tests for WXMPMeta_DoesPropertyExist_1
//
// The TEST_ID is 2019

#include <gtest/gtest.h>

#include "XMP_Const.h"
#include "client-glue/WXMP_Common.hpp"
#include "XMPMeta.hpp"

// Wrapper under test (implemented in WXMPMeta.cpp).
extern "C" void WXMPMeta_DoesPropertyExist_1(XMPMetaRef xmpRef,
                                            XMP_StringPtr schemaNS,
                                            XMP_StringPtr propName,
                                            WXMP_Result* wResult);

namespace {

class WXMPMeta_DoesPropertyExist_1_Test_2019 : public ::testing::Test {
protected:
  static XMPMetaRef AsRef(XMPMeta& meta) {
    // Treat as opaque handle; wrapper converts back via WtoXMPMeta_Ref.
    return reinterpret_cast<XMPMetaRef>(&meta);
  }
};

TEST_F(WXMPMeta_DoesPropertyExist_1_Test_2019, ReturnsFalseWhenPropertyDoesNotExist_2019) {
  XMPMeta meta;
  WXMP_Result r;
  r.int32Result = 123456u;  // sentinel

  const char* kSchema = "http://ns.adobe.com/xap/1.0/";
  const char* kProp = "CreatorTool";

  WXMPMeta_DoesPropertyExist_1(AsRef(meta), kSchema, kProp, &r);

  // On success, wrapper should not report an error message.
  EXPECT_EQ(r.errMessage, nullptr);
  EXPECT_EQ(r.int32Result, 0u);  // "found" stored as 0/1.
}

TEST_F(WXMPMeta_DoesPropertyExist_1_Test_2019, ReturnsTrueAfterSetProperty_2019) {
  XMPMeta meta;

  const char* kSchema = "http://ns.adobe.com/xap/1.0/";
  const char* kProp = "CreatorTool";

  // Observable setup through public interface only.
  meta.SetProperty(kSchema, kProp, "unit-test", 0 /* options */);

  WXMP_Result r;
  r.int32Result = 0u;

  WXMPMeta_DoesPropertyExist_1(AsRef(meta), kSchema, kProp, &r);

  EXPECT_EQ(r.errMessage, nullptr);
  EXPECT_EQ(r.int32Result, 1u);
}

TEST_F(WXMPMeta_DoesPropertyExist_1_Test_2019, EmptySchemaNamespaceReportsError_2019) {
  XMPMeta meta;
  WXMP_Result r;
  r.int32Result = 42u;  // sentinel

  WXMPMeta_DoesPropertyExist_1(AsRef(meta), "" /* empty schemaNS */, "AnyProp", &r);

  // Error should be observable via errMessage being set (wrapper-level behavior).
  EXPECT_NE(r.errMessage, nullptr);
}

TEST_F(WXMPMeta_DoesPropertyExist_1_Test_2019, NullSchemaNamespaceReportsError_2019) {
  XMPMeta meta;
  WXMP_Result r;
  r.int32Result = 42u;  // sentinel

  WXMPMeta_DoesPropertyExist_1(AsRef(meta), nullptr /* schemaNS */, "AnyProp", &r);

  EXPECT_NE(r.errMessage, nullptr);
}

TEST_F(WXMPMeta_DoesPropertyExist_1_Test_2019, EmptyPropertyNameReportsError_2019) {
  XMPMeta meta;
  WXMP_Result r;
  r.int32Result = 42u;  // sentinel

  const char* kSchema = "http://ns.adobe.com/xap/1.0/";

  WXMPMeta_DoesPropertyExist_1(AsRef(meta), kSchema, "" /* empty propName */, &r);

  EXPECT_NE(r.errMessage, nullptr);
}

TEST_F(WXMPMeta_DoesPropertyExist_1_Test_2019, NullPropertyNameReportsError_2019) {
  XMPMeta meta;
  WXMP_Result r;
  r.int32Result = 42u;  // sentinel

  const char* kSchema = "http://ns.adobe.com/xap/1.0/";

  WXMPMeta_DoesPropertyExist_1(AsRef(meta), kSchema, nullptr /* propName */, &r);

  EXPECT_NE(r.errMessage, nullptr);
}

}  // namespace