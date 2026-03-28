// =================================================================================================
// TEST_ID 2037
// Unit tests for WXMPMeta_Erase_1
// =================================================================================================

#include <gtest/gtest.h>

#include <cstring>

// The wrapper under test lives in xmpsdk/src/WXMPMeta.cpp, and its public declarations/types
// are expected to be available via the SDK headers.
#include "WXMPMeta.hpp"   // for XMPMetaRef and wrapper function declarations (expected)
#include "XMPMeta.hpp"    // for class XMPMeta
#include "WXMP_Common.hpp" // for WXMP_Result (errMessage field, etc.)

namespace {

class WXMPMeta_Erase_1_Test_2037 : public ::testing::Test {
protected:
  static void SetUpTestSuite() {
    // Many XMP SDK builds require explicit initialization before using XMPMeta.
    // Treat as black-box: if Initialize returns false, tests cannot proceed meaningfully.
    ASSERT_TRUE(XMPMeta::Initialize());
  }

  static void TearDownTestSuite() {
    XMPMeta::Terminate();
  }

  static XMPMetaRef AsRef(XMPMeta* meta) {
    // XMPMetaRef is an SDK handle type. In typical XMP SDKs it is a pointer/opaque handle.
    // We avoid assuming more than "it can represent an XMPMeta*".
    return reinterpret_cast<XMPMetaRef>(meta);
  }

  static constexpr const char* kSchemaNS = "http://ns.adobe.com/xap/1.0/";
  static constexpr const char* kPropName = "CreatorTool";
};

TEST_F(WXMPMeta_Erase_1_Test_2037, EraseClearsPreviouslySetProperty_2037) {
  XMPMeta meta;

  // Arrange: set a property and verify it exists via the public interface.
  meta.SetProperty(kSchemaNS, kPropName, "unit-test", 0 /* options */);
  EXPECT_TRUE(meta.DoesPropertyExist(kSchemaNS, kPropName));

  WXMP_Result wResult;
  EXPECT_EQ(wResult.errMessage, nullptr);

  // Act
  WXMPMeta_Erase_1(AsRef(&meta), &wResult);

  // Assert: observable behavior through public methods
  EXPECT_EQ(wResult.errMessage, nullptr);
  EXPECT_FALSE(meta.DoesPropertyExist(kSchemaNS, kPropName));
}

TEST_F(WXMPMeta_Erase_1_Test_2037, EraseOnEmptyObjectIsNoopAndNoError_2037) {
  XMPMeta meta;

  // Precondition: property does not exist
  EXPECT_FALSE(meta.DoesPropertyExist(kSchemaNS, kPropName));

  WXMP_Result wResult;
  EXPECT_EQ(wResult.errMessage, nullptr);

  // Act: erasing an already-empty object should not create an error observable via WXMP_Result.
  WXMPMeta_Erase_1(AsRef(&meta), &wResult);

  // Assert
  EXPECT_EQ(wResult.errMessage, nullptr);
  EXPECT_FALSE(meta.DoesPropertyExist(kSchemaNS, kPropName));
}

TEST_F(WXMPMeta_Erase_1_Test_2037, NullRefProducesObservableError_2037) {
  WXMP_Result wResult;
  EXPECT_EQ(wResult.errMessage, nullptr);

  // Act: Passing a null handle is an error/boundary case. The wrapper macros typically
  // convert exceptions into WXMP_Result::errMessage. We only assert observable outcomes.
  WXMPMeta_Erase_1(reinterpret_cast<XMPMetaRef>(nullptr), &wResult);

  // Assert: an error should be observable (message set). We do NOT assume specific text.
  EXPECT_NE(wResult.errMessage, nullptr);
}

}  // namespace