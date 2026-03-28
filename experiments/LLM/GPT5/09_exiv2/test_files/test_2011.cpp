// =================================================================================================
// UNIT TESTS
// File:        test_WXMPMeta_SetArrayItem_1_2011.cpp
// Description: GoogleTest unit tests for WXMPMeta_SetArrayItem_1 wrapper
// =================================================================================================

#include <gtest/gtest.h>

#include <cstdint>
#include <cstring>

// Pull in the SDK headers that define types and options.
#include "XMP_Const.h"
#include "client-glue/WXMP_Common.hpp"
#include "XMPMeta.hpp"

// The wrapper under test (implemented in xmpsdk/src/WXMPMeta.cpp).
extern "C" void WXMPMeta_SetArrayItem_1(XMPMetaRef xmpRef,
                                       XMP_StringPtr schemaNS,
                                       XMP_StringPtr arrayName,
                                       XMP_Index itemIndex,
                                       XMP_StringPtr itemValue,
                                       XMP_OptionBits options,
                                       WXMP_Result* wResult);

namespace {

class WXMPMetaSetArrayItem1Test_2011 : public ::testing::Test {
 protected:
  // Using a stack XMPMeta and passing its address as XMPMetaRef is the least invasive way
  // to get a valid object pointer for the wrapper (treated as a black box).
  XMPMeta meta_;
  XMPMetaRef metaRef_ = reinterpret_cast<XMPMetaRef>(&meta_);

  static constexpr XMP_StringPtr kSchemaNS = "http://ns.adobe.com/xap/1.0/";
  static constexpr XMP_StringPtr kArrayName = "TestArray";

  static void ExpectNoError(const WXMP_Result& r) { EXPECT_EQ(nullptr, r.errMessage); }
  static void ExpectHasError(const WXMP_Result& r) { EXPECT_NE(nullptr, r.errMessage); }
};

TEST_F(WXMPMetaSetArrayItem1Test_2011, RejectsNullSchemaNS_2011) {
  WXMP_Result r;
  WXMPMeta_SetArrayItem_1(metaRef_, /*schemaNS*/ nullptr, kArrayName, /*itemIndex*/ 1, "v",
                          /*options*/ 0, &r);
  ExpectHasError(r);
}

TEST_F(WXMPMetaSetArrayItem1Test_2011, RejectsEmptySchemaNS_2011) {
  WXMP_Result r;
  WXMPMeta_SetArrayItem_1(metaRef_, /*schemaNS*/ "", kArrayName, /*itemIndex*/ 1, "v",
                          /*options*/ 0, &r);
  ExpectHasError(r);
}

TEST_F(WXMPMetaSetArrayItem1Test_2011, RejectsNullArrayName_2011) {
  WXMP_Result r;
  WXMPMeta_SetArrayItem_1(metaRef_, kSchemaNS, /*arrayName*/ nullptr, /*itemIndex*/ 1, "v",
                          /*options*/ 0, &r);
  ExpectHasError(r);
}

TEST_F(WXMPMetaSetArrayItem1Test_2011, RejectsEmptyArrayName_2011) {
  WXMP_Result r;
  WXMPMeta_SetArrayItem_1(metaRef_, kSchemaNS, /*arrayName*/ "", /*itemIndex*/ 1, "v",
                          /*options*/ 0, &r);
  ExpectHasError(r);
}

TEST_F(WXMPMetaSetArrayItem1Test_2011, SetsExistingFirstArrayItem_2011) {
  // Arrange: create an ordered array with one item using the public interface.
  meta_.AppendArrayItem(kSchemaNS, kArrayName, kXMP_PropArrayIsOrdered, "old-value", /*options*/ 0);

  // Act: replace item 1 via the wrapper.
  WXMP_Result r;
  WXMPMeta_SetArrayItem_1(metaRef_, kSchemaNS, kArrayName, /*itemIndex*/ 1, "new-value",
                          /*options*/ 0, &r);

  // Assert: wrapper reported success and observable state changed.
  ExpectNoError(r);

  XMP_StringPtr got = nullptr;
  XMP_StringLen gotLen = 0;
  XMP_OptionBits gotOpts = 0;
  const bool ok = meta_.GetArrayItem(kSchemaNS, kArrayName, /*itemIndex*/ 1, &got, &gotLen, &gotOpts);
  EXPECT_TRUE(ok);
  ASSERT_NE(nullptr, got);
  EXPECT_EQ(std::string("new-value"), std::string(got, static_cast<size_t>(gotLen)));
}

TEST_F(WXMPMetaSetArrayItem1Test_2011, SetsLastArrayItemBoundary_2011) {
  // Arrange: create 2 items so we can target the last index boundary.
  meta_.AppendArrayItem(kSchemaNS, kArrayName, kXMP_PropArrayIsOrdered, "v1", /*options*/ 0);
  meta_.AppendArrayItem(kSchemaNS, kArrayName, kXMP_PropArrayIsOrdered, "v2", /*options*/ 0);

  const XMP_Index count = meta_.CountArrayItems(kSchemaNS, kArrayName);
  ASSERT_GE(count, 2);

  // Act: set the last item.
  WXMP_Result r;
  WXMPMeta_SetArrayItem_1(metaRef_, kSchemaNS, kArrayName, /*itemIndex*/ count, "last-new",
                          /*options*/ 0, &r);

  // Assert.
  ExpectNoError(r);

  XMP_StringPtr got = nullptr;
  XMP_StringLen gotLen = 0;
  XMP_OptionBits gotOpts = 0;
  const bool ok = meta_.GetArrayItem(kSchemaNS, kArrayName, /*itemIndex*/ count, &got, &gotLen,
                                     &gotOpts);
  EXPECT_TRUE(ok);
  ASSERT_NE(nullptr, got);
  EXPECT_EQ(std::string("last-new"), std::string(got, static_cast<size_t>(gotLen)));
}

TEST_F(WXMPMetaSetArrayItem1Test_2011, BadIndexZeroReportsError_2011) {
  // Arrange: create at least 1 item.
  meta_.AppendArrayItem(kSchemaNS, kArrayName, kXMP_PropArrayIsOrdered, "v1", /*options*/ 0);

  // Act: index 0 is commonly invalid for 1-based array item APIs; observable error should be reported.
  WXMP_Result r;
  WXMPMeta_SetArrayItem_1(metaRef_, kSchemaNS, kArrayName, /*itemIndex*/ 0, "should-fail",
                          /*options*/ 0, &r);

  // Assert: error is observable through WXMP_Result.
  ExpectHasError(r);
}

}  // namespace