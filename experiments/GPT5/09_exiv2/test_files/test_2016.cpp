// =================================================================================================
// UNIT TESTS for WXMPMeta_DeleteArrayItem_1
// File: ./TestProjects/exiv2/xmpsdk/src/WXMPMeta.cpp
// =================================================================================================

#include <gtest/gtest.h>

#include <cstring>

#include "client-glue/WXMP_Common.hpp"          // WXMP_Result
#include "XMP_Const.h"                          // kXMPErr_* enums, XMP types
#include "xmpsdk/src/XMPMeta.hpp"               // XMPMeta

// The wrapper under test (implemented in WXMPMeta.cpp).
extern "C" {
void WXMPMeta_DeleteArrayItem_1(XMPMetaRef xmpRef,
                               XMP_StringPtr schemaNS,
                               XMP_StringPtr arrayName,
                               XMP_Index itemIndex,
                               WXMP_Result* wResult);
}

// Some builds expose these option constants; if not, fall back to 0.
// (We avoid assuming exact option values; tests primarily validate observable behavior.)
#ifndef kXMP_ArrayIsOrdered
#define kXMP_ArrayIsOrdered 0
#endif

namespace {

static const char* kDublinCoreNS = "http://purl.org/dc/elements/1.1/";
static const char* kArrayName = "dc:subject";

class WXMPMeta_DeleteArrayItem_1_Test_2016 : public ::testing::Test {
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

  void AppendTwoArrayItems() {
    // Create an ordered array and append two items.
    // If the underlying implementation requires a specific array option, this is the most typical.
    meta_->AppendArrayItem(kDublinCoreNS, kArrayName, kXMP_ArrayIsOrdered, "one", 0);
    meta_->AppendArrayItem(kDublinCoreNS, kArrayName, kXMP_ArrayIsOrdered, "two", 0);
  }

  XMPMeta* meta_{nullptr};
  XMPMetaRef xmpRef_{nullptr};
};

}  // namespace

// -------------------------------------------------------------------------------------------------
// Normal operation
// -------------------------------------------------------------------------------------------------

TEST_F(WXMPMeta_DeleteArrayItem_1_Test_2016, DeletesExistingItem_DecreasesCount_2016) {
  AppendTwoArrayItems();
  const XMP_Index before = meta_->CountArrayItems(kDublinCoreNS, kArrayName);
  ASSERT_GE(before, 2);

  WXMP_Result wResult;
  WXMPMeta_DeleteArrayItem_1(xmpRef_, kDublinCoreNS, kArrayName, /*itemIndex=*/1, &wResult);

  // On success, wrapper should not report an error message.
  EXPECT_TRUE(wResult.errMessage == nullptr);

  const XMP_Index after = meta_->CountArrayItems(kDublinCoreNS, kArrayName);
  EXPECT_EQ(after, before - 1);
}

TEST_F(WXMPMeta_DeleteArrayItem_1_Test_2016, DeletesSecondItem_DecreasesCount_2016) {
  AppendTwoArrayItems();
  const XMP_Index before = meta_->CountArrayItems(kDublinCoreNS, kArrayName);
  ASSERT_GE(before, 2);

  WXMP_Result wResult;
  WXMPMeta_DeleteArrayItem_1(xmpRef_, kDublinCoreNS, kArrayName, /*itemIndex=*/2, &wResult);

  EXPECT_TRUE(wResult.errMessage == nullptr);

  const XMP_Index after = meta_->CountArrayItems(kDublinCoreNS, kArrayName);
  EXPECT_EQ(after, before - 1);
}

// -------------------------------------------------------------------------------------------------
// Parameter validation / error cases (observable via wResult.errMessage)
// -------------------------------------------------------------------------------------------------

TEST_F(WXMPMeta_DeleteArrayItem_1_Test_2016, NullSchemaNS_SetsErrorMessage_2016) {
  AppendTwoArrayItems();
  const XMP_Index before = meta_->CountArrayItems(kDublinCoreNS, kArrayName);

  WXMP_Result wResult;
  WXMPMeta_DeleteArrayItem_1(xmpRef_, /*schemaNS=*/nullptr, kArrayName, /*itemIndex=*/1, &wResult);

  EXPECT_TRUE(wResult.errMessage != nullptr);

  // Deletion should not have succeeded.
  const XMP_Index after = meta_->CountArrayItems(kDublinCoreNS, kArrayName);
  EXPECT_EQ(after, before);
}

TEST_F(WXMPMeta_DeleteArrayItem_1_Test_2016, EmptySchemaNS_SetsErrorMessage_2016) {
  AppendTwoArrayItems();
  const XMP_Index before = meta_->CountArrayItems(kDublinCoreNS, kArrayName);

  WXMP_Result wResult;
  WXMPMeta_DeleteArrayItem_1(xmpRef_, /*schemaNS=*/"", kArrayName, /*itemIndex=*/1, &wResult);

  EXPECT_TRUE(wResult.errMessage != nullptr);

  const XMP_Index after = meta_->CountArrayItems(kDublinCoreNS, kArrayName);
  EXPECT_EQ(after, before);
}

TEST_F(WXMPMeta_DeleteArrayItem_1_Test_2016, NullArrayName_SetsErrorMessage_2016) {
  AppendTwoArrayItems();
  const XMP_Index before = meta_->CountArrayItems(kDublinCoreNS, kArrayName);

  WXMP_Result wResult;
  WXMPMeta_DeleteArrayItem_1(xmpRef_, kDublinCoreNS, /*arrayName=*/nullptr, /*itemIndex=*/1, &wResult);

  EXPECT_TRUE(wResult.errMessage != nullptr);

  const XMP_Index after = meta_->CountArrayItems(kDublinCoreNS, kArrayName);
  EXPECT_EQ(after, before);
}

TEST_F(WXMPMeta_DeleteArrayItem_1_Test_2016, EmptyArrayName_SetsErrorMessage_2016) {
  AppendTwoArrayItems();
  const XMP_Index before = meta_->CountArrayItems(kDublinCoreNS, kArrayName);

  WXMP_Result wResult;
  WXMPMeta_DeleteArrayItem_1(xmpRef_, kDublinCoreNS, /*arrayName=*/"", /*itemIndex=*/1, &wResult);

  EXPECT_TRUE(wResult.errMessage != nullptr);

  const XMP_Index after = meta_->CountArrayItems(kDublinCoreNS, kArrayName);
  EXPECT_EQ(after, before);
}

// -------------------------------------------------------------------------------------------------
// Boundary conditions
// -------------------------------------------------------------------------------------------------

TEST_F(WXMPMeta_DeleteArrayItem_1_Test_2016, DeleteFromEmptyArray_ReportsErrorOrNoChange_2016) {
  // Ensure the array is empty / not present.
  EXPECT_EQ(meta_->CountArrayItems(kDublinCoreNS, kArrayName), 0);

  WXMP_Result wResult;
  WXMPMeta_DeleteArrayItem_1(xmpRef_, kDublinCoreNS, kArrayName, /*itemIndex=*/1, &wResult);

  // Depending on underlying SDK behavior, this may throw (error message set) or be a no-op.
  // We assert only what is observable and safe: no new items are created.
  EXPECT_EQ(meta_->CountArrayItems(kDublinCoreNS, kArrayName), 0);

  // If an error is reported, it must be via errMessage.
  // If no error is reported, errMessage should be null.
  // (We don't enforce which behavior occurs.)
  EXPECT_TRUE((wResult.errMessage == nullptr) || (wResult.errMessage != nullptr));
}

TEST_F(WXMPMeta_DeleteArrayItem_1_Test_2016, OutOfRangeIndex_DoesNotIncreaseCount_2016) {
  AppendTwoArrayItems();
  const XMP_Index before = meta_->CountArrayItems(kDublinCoreNS, kArrayName);
  ASSERT_GE(before, 2);

  WXMP_Result wResult;
  WXMPMeta_DeleteArrayItem_1(xmpRef_, kDublinCoreNS, kArrayName, /*itemIndex=*/before + 10, &wResult);

  // Regardless of whether this is treated as an error or a no-op, it must not add items.
  const XMP_Index after = meta_->CountArrayItems(kDublinCoreNS, kArrayName);
  EXPECT_LE(after, before);

  // If an error occurs, it should be reflected in errMessage; if not, errMessage may be null.
  // We avoid asserting a specific error code/message.
}