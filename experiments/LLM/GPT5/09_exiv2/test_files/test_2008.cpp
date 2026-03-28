// =================================================================================================
// Unit tests for WXMPMeta_GetStructField_1
// File: ./TestProjects/exiv2/xmpsdk/src/WXMPMeta.cpp
// TEST_ID: 2008
// =================================================================================================

#include <gtest/gtest.h>

#include <cstring>
#include <string>

#include "XMP_Const.h"
#include "./TestProjects/exiv2/xmpsdk/src/XMPMeta.hpp"
#include "client-glue/WXMP_Common.hpp"

// The wrapper uses XMPMetaRef and C-style ABI in the glue layer.
// In Adobe XMP C++ SDK, XMPMetaRef is typically an opaque pointer (often void*).
// We only rely on observable behavior through the public wrapper interface.
typedef void* XMPMetaRef;

extern "C" {
void WXMPMeta_GetStructField_1(XMPMetaRef xmpRef,
                              XMP_StringPtr schemaNS,
                              XMP_StringPtr structName,
                              XMP_StringPtr fieldNS,
                              XMP_StringPtr fieldName,
                              XMP_StringPtr* fieldValue,
                              XMP_StringLen* valueSize,
                              XMP_OptionBits* options,
                              WXMP_Result* wResult);
} // extern "C"

namespace {

class WXMPMeta_GetStructField_1_Test_2008 : public ::testing::Test {
protected:
  static void SetUpTestSuite() {
    // If Initialize is already handled globally by the test runner in your codebase,
    // calling it again should be harmless; if not, these calls make the tests self-contained.
    (void)XMPMeta::Initialize();
  }

  static void TearDownTestSuite() { XMPMeta::Terminate(); }

  static XMPMetaRef ToRef(XMPMeta& meta) {
    // Treat as opaque ref; the wrapper converts internally.
    return reinterpret_cast<XMPMetaRef>(&meta);
  }
};

TEST_F(WXMPMeta_GetStructField_1_Test_2008, ReturnsTrueAndOutputsValueForExistingField_2008) {
  XMPMeta meta;

  // Create a struct field via public API, then retrieve via wrapper.
  const char* schemaNS = "http://ns.adobe.com/xap/1.0/";
  const char* structName = "TestStruct";
  const char* fieldNS = "http://ns.adobe.com/xap/1.0/";
  const char* fieldName = "TestField";
  const char* expectedValue = "HelloStructField";

  meta.SetStructField(schemaNS, structName, fieldNS, fieldName, expectedValue, /*options*/ 0);

  XMP_StringPtr outValue = nullptr;
  XMP_StringLen outSize = 0;
  XMP_OptionBits outOptions = 0;
  WXMP_Result wr; // errMessage initialized to 0 by ctor

  WXMPMeta_GetStructField_1(ToRef(meta), schemaNS, structName, fieldNS, fieldName, &outValue, &outSize,
                           &outOptions, &wr);

  EXPECT_EQ(wr.errMessage, nullptr);
  EXPECT_NE(wr.int32Result, 0u); // found == true

  ASSERT_NE(outValue, nullptr);
  std::string got(outValue, static_cast<size_t>(outSize));
  EXPECT_EQ(got, expectedValue);
}

TEST_F(WXMPMeta_GetStructField_1_Test_2008, ReturnsFalseForMissingField_2008) {
  XMPMeta meta;

  const char* schemaNS = "http://ns.adobe.com/xap/1.0/";
  const char* structName = "StructDoesNotExist";
  const char* fieldNS = "http://ns.adobe.com/xap/1.0/";
  const char* fieldName = "FieldDoesNotExist";

  XMP_StringPtr outValue = reinterpret_cast<XMP_StringPtr>(0x1); // sentinel; should not crash if unchanged
  XMP_StringLen outSize = 123;
  XMP_OptionBits outOptions = 0xFFFFFFFFu;
  WXMP_Result wr;

  WXMPMeta_GetStructField_1(ToRef(meta), schemaNS, structName, fieldNS, fieldName, &outValue, &outSize,
                           &outOptions, &wr);

  EXPECT_EQ(wr.errMessage, nullptr);
  EXPECT_EQ(wr.int32Result, 0u); // found == false
}

TEST_F(WXMPMeta_GetStructField_1_Test_2008, SucceedsWhenOutputPointersAreNull_2008) {
  XMPMeta meta;

  const char* schemaNS = "http://ns.adobe.com/xap/1.0/";
  const char* structName = "TestStruct2";
  const char* fieldNS = "http://ns.adobe.com/xap/1.0/";
  const char* fieldName = "Field2";
  const char* expectedValue = "Value2";

  meta.SetStructField(schemaNS, structName, fieldNS, fieldName, expectedValue, /*options*/ 0);

  WXMP_Result wr;

  // Per wrapper code: if any of these are null, it substitutes internal "void" placeholders.
  WXMPMeta_GetStructField_1(ToRef(meta), schemaNS, structName, fieldNS, fieldName,
                           /*fieldValue*/ nullptr, /*valueSize*/ nullptr, /*options*/ nullptr, &wr);

  EXPECT_EQ(wr.errMessage, nullptr);
  EXPECT_NE(wr.int32Result, 0u); // still should report "found"
}

TEST_F(WXMPMeta_GetStructField_1_Test_2008, ErrorWhenSchemaNSIsNull_2008) {
  XMPMeta meta;

  const char* structName = "AnyStruct";
  const char* fieldNS = "http://ns.adobe.com/xap/1.0/";
  const char* fieldName = "AnyField";

  XMP_StringPtr outValue = nullptr;
  XMP_StringLen outSize = 0;
  XMP_OptionBits outOptions = 0;
  WXMP_Result wr;

  WXMPMeta_GetStructField_1(ToRef(meta), /*schemaNS*/ nullptr, structName, fieldNS, fieldName, &outValue,
                           &outSize, &outOptions, &wr);

  EXPECT_NE(wr.errMessage, nullptr);
}

TEST_F(WXMPMeta_GetStructField_1_Test_2008, ErrorWhenStructNameIsEmpty_2008) {
  XMPMeta meta;

  const char* schemaNS = "http://ns.adobe.com/xap/1.0/";
  const char* structName = ""; // empty triggers bad xpath per wrapper code
  const char* fieldNS = "http://ns.adobe.com/xap/1.0/";
  const char* fieldName = "AnyField";

  XMP_StringPtr outValue = nullptr;
  XMP_StringLen outSize = 0;
  XMP_OptionBits outOptions = 0;
  WXMP_Result wr;

  WXMPMeta_GetStructField_1(ToRef(meta), schemaNS, structName, fieldNS, fieldName, &outValue, &outSize,
                           &outOptions, &wr);

  EXPECT_NE(wr.errMessage, nullptr);
}

TEST_F(WXMPMeta_GetStructField_1_Test_2008, ErrorWhenFieldNameIsNull_2008) {
  XMPMeta meta;

  const char* schemaNS = "http://ns.adobe.com/xap/1.0/";
  const char* structName = "AnyStruct";
  const char* fieldNS = "http://ns.adobe.com/xap/1.0/";

  XMP_StringPtr outValue = nullptr;
  XMP_StringLen outSize = 0;
  XMP_OptionBits outOptions = 0;
  WXMP_Result wr;

  WXMPMeta_GetStructField_1(ToRef(meta), schemaNS, structName, fieldNS, /*fieldName*/ nullptr, &outValue,
                           &outSize, &outOptions, &wr);

  EXPECT_NE(wr.errMessage, nullptr);
}

} // namespace