// =================================================================================================
// TestProject: Exiv2 XMP SDK
// Unit tests for WXMPMeta_DeleteStructField_1
// TEST_ID: 2017
// =================================================================================================

#include <gtest/gtest.h>

#include "XMP_Const.h"
#include "XMPMeta.hpp"
#include "client-glue/WXMP_Common.hpp"

// The wrapper under test is implemented in xmpsdk/src/WXMPMeta.cpp.
// In most Exiv2/XMP SDK layouts, its declaration is available via a public wrapper header.
// If your tree uses a different header name/path, adjust the include accordingly.
#include "client-glue/WXMPMeta.hpp"

namespace {

class WXMPMeta_DeleteStructField_1_Test_2017 : public ::testing::Test {
protected:
  static void SetUpTestSuite() {
    // Required by many XMP SDK builds before using XMPMeta APIs.
    (void)XMPMeta::Initialize();
  }

  static void TearDownTestSuite() {
    XMPMeta::Terminate();
  }

  // Helper: create a usable XMPMetaRef for wrapper calls.
  // In the XMP SDK, XMPMetaRef is typically an opaque pointer to XMPMeta.
  static XMPMetaRef AsRef(XMPMeta* meta) { return reinterpret_cast<XMPMetaRef>(meta); }

  static constexpr XMP_StringPtr kSchemaNS = "http://ns.adobe.com/xap/1.0/";
  static constexpr XMP_StringPtr kStructName = "TestStruct";
  static constexpr XMP_StringPtr kFieldNS = "http://ns.adobe.com/xap/1.0/";
  static constexpr XMP_StringPtr kFieldName = "Field";
};

TEST_F(WXMPMeta_DeleteStructField_1_Test_2017, NullSchemaNS_SetsError_2017) {
  XMPMeta meta;
  WXMP_Result wr;

  WXMPMeta_DeleteStructField_1(AsRef(&meta), /*schemaNS*/ nullptr, kStructName, kFieldNS, kFieldName, &wr);

  EXPECT_NE(wr.errMessage, nullptr);
}

TEST_F(WXMPMeta_DeleteStructField_1_Test_2017, EmptySchemaNS_SetsError_2017) {
  XMPMeta meta;
  WXMP_Result wr;

  WXMPMeta_DeleteStructField_1(AsRef(&meta), /*schemaNS*/ "", kStructName, kFieldNS, kFieldName, &wr);

  EXPECT_NE(wr.errMessage, nullptr);
}

TEST_F(WXMPMeta_DeleteStructField_1_Test_2017, NullStructName_SetsError_2017) {
  XMPMeta meta;
  WXMP_Result wr;

  WXMPMeta_DeleteStructField_1(AsRef(&meta), kSchemaNS, /*structName*/ nullptr, kFieldNS, kFieldName, &wr);

  EXPECT_NE(wr.errMessage, nullptr);
}

TEST_F(WXMPMeta_DeleteStructField_1_Test_2017, EmptyStructName_SetsError_2017) {
  XMPMeta meta;
  WXMP_Result wr;

  WXMPMeta_DeleteStructField_1(AsRef(&meta), kSchemaNS, /*structName*/ "", kFieldNS, kFieldName, &wr);

  EXPECT_NE(wr.errMessage, nullptr);
}

TEST_F(WXMPMeta_DeleteStructField_1_Test_2017, NullFieldNS_SetsError_2017) {
  XMPMeta meta;
  WXMP_Result wr;

  WXMPMeta_DeleteStructField_1(AsRef(&meta), kSchemaNS, kStructName, /*fieldNS*/ nullptr, kFieldName, &wr);

  EXPECT_NE(wr.errMessage, nullptr);
}

TEST_F(WXMPMeta_DeleteStructField_1_Test_2017, EmptyFieldNS_SetsError_2017) {
  XMPMeta meta;
  WXMP_Result wr;

  WXMPMeta_DeleteStructField_1(AsRef(&meta), kSchemaNS, kStructName, /*fieldNS*/ "", kFieldName, &wr);

  EXPECT_NE(wr.errMessage, nullptr);
}

TEST_F(WXMPMeta_DeleteStructField_1_Test_2017, NullFieldName_SetsError_2017) {
  XMPMeta meta;
  WXMP_Result wr;

  WXMPMeta_DeleteStructField_1(AsRef(&meta), kSchemaNS, kStructName, kFieldNS, /*fieldName*/ nullptr, &wr);

  EXPECT_NE(wr.errMessage, nullptr);
}

TEST_F(WXMPMeta_DeleteStructField_1_Test_2017, EmptyFieldName_SetsError_2017) {
  XMPMeta meta;
  WXMP_Result wr;

  WXMPMeta_DeleteStructField_1(AsRef(&meta), kSchemaNS, kStructName, kFieldNS, /*fieldName*/ "", &wr);

  EXPECT_NE(wr.errMessage, nullptr);
}

TEST_F(WXMPMeta_DeleteStructField_1_Test_2017, DeletesExistingStructField_2017) {
  XMPMeta meta;

  // Arrange: create a struct field via the public XMPMeta interface.
  meta.SetStructField(kSchemaNS, kStructName, kFieldNS, kFieldName, "value", /*options*/ 0);
  EXPECT_TRUE(meta.DoesStructFieldExist(kSchemaNS, kStructName, kFieldNS, kFieldName));

  WXMP_Result wr;

  // Act: delete via the wrapper.
  WXMPMeta_DeleteStructField_1(AsRef(&meta), kSchemaNS, kStructName, kFieldNS, kFieldName, &wr);

  // Assert: wrapper reported no error and field is gone (observable via public API).
  EXPECT_EQ(wr.errMessage, nullptr);
  EXPECT_FALSE(meta.DoesStructFieldExist(kSchemaNS, kStructName, kFieldNS, kFieldName));
}

TEST_F(WXMPMeta_DeleteStructField_1_Test_2017, DeleteNonexistentStructField_DoesNotCreateField_2017) {
  XMPMeta meta;

  EXPECT_FALSE(meta.DoesStructFieldExist(kSchemaNS, kStructName, kFieldNS, kFieldName));

  WXMP_Result wr;
  WXMPMeta_DeleteStructField_1(AsRef(&meta), kSchemaNS, kStructName, kFieldNS, kFieldName, &wr);

  // Observable expectations:
  // - The field should still not exist.
  // - If the underlying implementation treats deletion of a missing field as a no-op,
  //   errMessage should remain null; if it throws, errMessage would become non-null.
  // We assert the field is still absent (always valid), and accept either error/no-error
  // behavior by not over-specifying the exception policy.
  EXPECT_FALSE(meta.DoesStructFieldExist(kSchemaNS, kStructName, kFieldNS, kFieldName));
}

}  // namespace