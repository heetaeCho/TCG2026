// =================================================================================================
// TEST_ID 2038
// Unit tests for WXMPMeta_Clone_1
// File: ./TestProjects/exiv2/xmpsdk/src/WXMPMeta.cpp
// =================================================================================================

#include <gtest/gtest.h>

#include <cstdint>
#include <cstring>
#include <string>

#include "XMPMeta.hpp"
#include "client-glue/WXMP_Common.hpp"

// The wrapper under test (implemented in WXMPMeta.cpp).
extern "C" void WXMPMeta_Clone_1(XMPMetaRef xmpRef, XMP_OptionBits options, WXMP_Result* wResult);

namespace {

static std::string GetPropString(
    const XMPMeta& xmp, XMP_StringPtr schemaNS, XMP_StringPtr propName, bool* existsOut = nullptr) {
  XMP_StringPtr value = nullptr;
  XMP_StringLen valueSize = 0;
  XMP_OptionBits options = 0;

  const bool exists = xmp.GetProperty(schemaNS, propName, &value, &valueSize, &options);
  if (existsOut) *existsOut = exists;
  if (!exists) return std::string();
  if (value == nullptr) return std::string();  // Defensive.
  return std::string(value, static_cast<size_t>(valueSize));
}

class WXMPMetaClone1Test_2038 : public ::testing::Test {
 public:
  static void SetUpTestSuite() {
    // Many XMP SDK builds require global init/terminate.
    (void)XMPMeta::Initialize();
  }

  static void TearDownTestSuite() { XMPMeta::Terminate(); }
};

}  // namespace

TEST_F(WXMPMetaClone1Test_2038, CloneReturnsDistinctObject_2038) {
  XMPMeta original;
  const XMP_StringPtr kSchema = "http://ns.adobe.com/xap/1.0/";
  original.SetProperty(kSchema, "CreatorTool", "exiv2-test", 0);

  WXMP_Result result;
  result.ptrResult = nullptr;
  result.errMessage = nullptr;

  WXMPMeta_Clone_1(reinterpret_cast<XMPMetaRef>(&original), 0, &result);

  ASSERT_EQ(result.errMessage, nullptr) << "Unexpected error from wrapper";
  ASSERT_NE(result.ptrResult, nullptr) << "Expected a clone object";
  EXPECT_NE(result.ptrResult, reinterpret_cast<void*>(&original)) << "Clone must be distinct";

  // Cleanup: wrapper allocates with new.
  delete reinterpret_cast<XMPMeta*>(result.ptrResult);
}

TEST_F(WXMPMetaClone1Test_2038, CloneCopiesObservableProperties_2038) {
  XMPMeta original;
  const XMP_StringPtr kSchema = "http://ns.adobe.com/xap/1.0/";
  original.SetProperty(kSchema, "CreatorTool", "exiv2-test", 0);
  original.SetProperty(kSchema, "Label", "unit", 0);

  WXMP_Result result;
  result.ptrResult = nullptr;
  result.errMessage = nullptr;

  WXMPMeta_Clone_1(reinterpret_cast<XMPMetaRef>(&original), 0, &result);

  ASSERT_EQ(result.errMessage, nullptr) << "Unexpected error from wrapper";
  ASSERT_NE(result.ptrResult, nullptr);

  XMPMeta* clone = reinterpret_cast<XMPMeta*>(result.ptrResult);

  EXPECT_EQ(GetPropString(*clone, kSchema, "CreatorTool"), "exiv2-test");
  EXPECT_EQ(GetPropString(*clone, kSchema, "Label"), "unit");

  delete clone;
}

TEST_F(WXMPMetaClone1Test_2038, CloneIsIndependentAfterModification_2038) {
  XMPMeta original;
  const XMP_StringPtr kSchema = "http://ns.adobe.com/xap/1.0/";
  original.SetProperty(kSchema, "CreatorTool", "exiv2-test", 0);

  WXMP_Result result;
  result.ptrResult = nullptr;
  result.errMessage = nullptr;

  WXMPMeta_Clone_1(reinterpret_cast<XMPMetaRef>(&original), 0, &result);

  ASSERT_EQ(result.errMessage, nullptr) << "Unexpected error from wrapper";
  ASSERT_NE(result.ptrResult, nullptr);

  XMPMeta* clone = reinterpret_cast<XMPMeta*>(result.ptrResult);

  // Mutate clone, ensure original remains unchanged (observable via public API).
  clone->SetProperty(kSchema, "CreatorTool", "changed-in-clone", 0);

  EXPECT_EQ(GetPropString(original, kSchema, "CreatorTool"), "exiv2-test");
  EXPECT_EQ(GetPropString(*clone, kSchema, "CreatorTool"), "changed-in-clone");

  delete clone;
}

TEST_F(WXMPMetaClone1Test_2038, CloneWithNullRefReportsErrorOrNullResult_2038) {
  WXMP_Result result;
  result.ptrResult = reinterpret_cast<void*>(static_cast<uintptr_t>(0x1));  // sentinel
  result.errMessage = nullptr;

  WXMPMeta_Clone_1(reinterpret_cast<XMPMetaRef>(nullptr), 0, &result);

  // We don't assume the exact error mechanism, only observable outcomes:
  // - On failure, ptrResult should not become a valid allocated object.
  // - Many wrappers populate errMessage; if present, it should be non-empty.
  EXPECT_TRUE(result.ptrResult == nullptr || result.ptrResult == reinterpret_cast<void*>(static_cast<uintptr_t>(0x1)))
      << "Unexpected ptrResult mutation on null input";

  if (result.errMessage != nullptr) {
    EXPECT_NE(std::strlen(result.errMessage), 0u);
  }

  // If ptrResult was somehow set, avoid leaking but only delete if it's not sentinel.
  if (result.ptrResult != nullptr && result.ptrResult != reinterpret_cast<void*>(static_cast<uintptr_t>(0x1))) {
    delete reinterpret_cast<XMPMeta*>(result.ptrResult);
  }
}