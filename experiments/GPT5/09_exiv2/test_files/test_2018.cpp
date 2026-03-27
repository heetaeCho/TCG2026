// =================================================================================================
// Unit tests for WXMPMeta_DeleteQualifier_1
// File: ./TestProjects/exiv2/xmpsdk/src/WXMPMeta.cpp
// =================================================================================================

#include <gtest/gtest.h>

#include "XMP_Const.h"
#include "WXMP_Common.hpp"

// The wrapper under test (declared elsewhere in the codebase).
extern "C" {
void WXMPMeta_DeleteQualifier_1(XMPMetaRef xmpRef,
                               XMP_StringPtr schemaNS,
                               XMP_StringPtr propName,
                               XMP_StringPtr qualNS,
                               XMP_StringPtr qualName,
                               WXMP_Result* wResult);
}

#include "XMPMeta.hpp"  // XMPMeta class API (used to set up/verify observable behavior)

namespace {

class WXMPMeta_DeleteQualifier_1_Test_2018 : public ::testing::Test {
protected:
  static void SetUpTestSuite() {
    // Many XMP SDK builds require explicit initialization; calling is safe even if it is a no-op.
    (void)XMPMeta::Initialize();
  }

  static void TearDownTestSuite() { XMPMeta::Terminate(); }

  static constexpr XMP_StringPtr kSchemaNS = "http://ns.adobe.com/xap/1.0/";
  static constexpr XMP_StringPtr kPropName = "TestProp";

  // Common qualifier: xml:lang
  static constexpr XMP_StringPtr kQualNS = "http://www.w3.org/XML/1998/namespace";
  static constexpr XMP_StringPtr kQualName = "lang";

  static XMPMetaRef AsRef(XMPMeta& meta) {
    // XMPMetaRef is an SDK handle type; in typical builds it is a pointer/opaque handle.
    return reinterpret_cast<XMPMetaRef>(&meta);
  }

  static void SetUpPropAndQualifier(XMPMeta& meta) {
    meta.SetProperty(kSchemaNS, kPropName, "value", 0);
    meta.SetQualifier(kSchemaNS, kPropName, kQualNS, kQualName, "en-US", 0);
  }
};

TEST_F(WXMPMeta_DeleteQualifier_1_Test_2018, DeletesExistingQualifier_2018) {
  XMPMeta meta;
  SetUpPropAndQualifier(meta);

  ASSERT_TRUE(meta.DoesQualifierExist(kSchemaNS, kPropName, kQualNS, kQualName));

  WXMP_Result res;
  WXMPMeta_DeleteQualifier_1(AsRef(meta), kSchemaNS, kPropName, kQualNS, kQualName, &res);

  EXPECT_EQ(res.errMessage, nullptr);
  EXPECT_FALSE(meta.DoesQualifierExist(kSchemaNS, kPropName, kQualNS, kQualName));
}

TEST_F(WXMPMeta_DeleteQualifier_1_Test_2018, DeleteIsIdempotentWhenQualifierMissing_2018) {
  XMPMeta meta;
  SetUpPropAndQualifier(meta);

  WXMP_Result res1;
  WXMPMeta_DeleteQualifier_1(AsRef(meta), kSchemaNS, kPropName, kQualNS, kQualName, &res1);
  ASSERT_EQ(res1.errMessage, nullptr);
  ASSERT_FALSE(meta.DoesQualifierExist(kSchemaNS, kPropName, kQualNS, kQualName));

  // Boundary: deleting again should not crash; observable behavior should be "no error" in normal SDK usage.
  WXMP_Result res2;
  WXMPMeta_DeleteQualifier_1(AsRef(meta), kSchemaNS, kPropName, kQualNS, kQualName, &res2);

  EXPECT_EQ(res2.errMessage, nullptr);
  EXPECT_FALSE(meta.DoesQualifierExist(kSchemaNS, kPropName, kQualNS, kQualName));
}

TEST_F(WXMPMeta_DeleteQualifier_1_Test_2018, NullSchemaNSReportsErrorAndDoesNotDelete_2018) {
  XMPMeta meta;
  SetUpPropAndQualifier(meta);

  WXMP_Result res;
  WXMPMeta_DeleteQualifier_1(AsRef(meta), nullptr, kPropName, kQualNS, kQualName, &res);

  EXPECT_NE(res.errMessage, nullptr);
  EXPECT_TRUE(meta.DoesQualifierExist(kSchemaNS, kPropName, kQualNS, kQualName));
}

TEST_F(WXMPMeta_DeleteQualifier_1_Test_2018, EmptySchemaNSReportsErrorAndDoesNotDelete_2018) {
  XMPMeta meta;
  SetUpPropAndQualifier(meta);

  WXMP_Result res;
  WXMPMeta_DeleteQualifier_1(AsRef(meta), "", kPropName, kQualNS, kQualName, &res);

  EXPECT_NE(res.errMessage, nullptr);
  EXPECT_TRUE(meta.DoesQualifierExist(kSchemaNS, kPropName, kQualNS, kQualName));
}

TEST_F(WXMPMeta_DeleteQualifier_1_Test_2018, NullPropNameReportsErrorAndDoesNotDelete_2018) {
  XMPMeta meta;
  SetUpPropAndQualifier(meta);

  WXMP_Result res;
  WXMPMeta_DeleteQualifier_1(AsRef(meta), kSchemaNS, nullptr, kQualNS, kQualName, &res);

  EXPECT_NE(res.errMessage, nullptr);
  EXPECT_TRUE(meta.DoesQualifierExist(kSchemaNS, kPropName, kQualNS, kQualName));
}

TEST_F(WXMPMeta_DeleteQualifier_1_Test_2018, EmptyPropNameReportsErrorAndDoesNotDelete_2018) {
  XMPMeta meta;
  SetUpPropAndQualifier(meta);

  WXMP_Result res;
  WXMPMeta_DeleteQualifier_1(AsRef(meta), kSchemaNS, "", kQualNS, kQualName, &res);

  EXPECT_NE(res.errMessage, nullptr);
  EXPECT_TRUE(meta.DoesQualifierExist(kSchemaNS, kPropName, kQualNS, kQualName));
}

TEST_F(WXMPMeta_DeleteQualifier_1_Test_2018, NullQualNSReportsErrorAndDoesNotDelete_2018) {
  XMPMeta meta;
  SetUpPropAndQualifier(meta);

  WXMP_Result res;
  WXMPMeta_DeleteQualifier_1(AsRef(meta), kSchemaNS, kPropName, nullptr, kQualName, &res);

  EXPECT_NE(res.errMessage, nullptr);
  EXPECT_TRUE(meta.DoesQualifierExist(kSchemaNS, kPropName, kQualNS, kQualName));
}

TEST_F(WXMPMeta_DeleteQualifier_1_Test_2018, EmptyQualNSReportsErrorAndDoesNotDelete_2018) {
  XMPMeta meta;
  SetUpPropAndQualifier(meta);

  WXMP_Result res;
  WXMPMeta_DeleteQualifier_1(AsRef(meta), kSchemaNS, kPropName, "", kQualName, &res);

  EXPECT_NE(res.errMessage, nullptr);
  EXPECT_TRUE(meta.DoesQualifierExist(kSchemaNS, kPropName, kQualNS, kQualName));
}

TEST_F(WXMPMeta_DeleteQualifier_1_Test_2018, NullQualNameReportsErrorAndDoesNotDelete_2018) {
  XMPMeta meta;
  SetUpPropAndQualifier(meta);

  WXMP_Result res;
  WXMPMeta_DeleteQualifier_1(AsRef(meta), kSchemaNS, kPropName, kQualNS, nullptr, &res);

  EXPECT_NE(res.errMessage, nullptr);
  EXPECT_TRUE(meta.DoesQualifierExist(kSchemaNS, kPropName, kQualNS, kQualName));
}

TEST_F(WXMPMeta_DeleteQualifier_1_Test_2018, EmptyQualNameReportsErrorAndDoesNotDelete_2018) {
  XMPMeta meta;
  SetUpPropAndQualifier(meta);

  WXMP_Result res;
  WXMPMeta_DeleteQualifier_1(AsRef(meta), kSchemaNS, kPropName, kQualNS, "", &res);

  EXPECT_NE(res.errMessage, nullptr);
  EXPECT_TRUE(meta.DoesQualifierExist(kSchemaNS, kPropName, kQualNS, kQualName));
}

}  // namespace