// =================================================================================================
// TEST_ID: 2021
// Unit tests for WXMPMeta_DoesStructFieldExist_1
// File: ./TestProjects/exiv2/xmpsdk/src/WXMPMeta.cpp
// =================================================================================================

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <cstring>   // std::strstr
#include <cstdint>

// XMP SDK headers (project-local)
#include "XMP_Const.h"
#include "WXMP_Common.hpp"
#include "XMPMeta.hpp"

// The wrapper function under test (implemented in WXMPMeta.cpp).
extern "C" {
void WXMPMeta_DoesStructFieldExist_1(XMPMetaRef xmpRef,
                                    XMP_StringPtr schemaNS,
                                    XMP_StringPtr structName,
                                    XMP_StringPtr fieldNS,
                                    XMP_StringPtr fieldName,
                                    WXMP_Result* wResult) /* const */;
}

namespace {

class WXMPMeta_DoesStructFieldExist_1_Test_2021 : public ::testing::Test {
protected:
  static void SetUpTestSuite() {
    // Most XMP SDK usage requires global init/term. Treat as black box.
    // If Initialize() returns false, tests that depend on it should fail early.
    const bool ok = XMPMeta::Initialize();
    ASSERT_TRUE(ok);

    // Register a test namespace/prefix pair. If already registered, the SDK may throw;
    // we avoid asserting on that behavior, but keep the call simple.
    // (If this throws internally, wrapper macro behavior isn't involved; it's fine to omit checks.)
    XMPMeta::RegisterNamespace(kTestSchemaNS, kTestPrefix);
  }

  static void TearDownTestSuite() {
    XMPMeta::Terminate();
  }

  void SetUp() override {
    // Fresh meta object each test.
    // NOTE: XMPMetaRef is an SDK type; in most builds it's an opaque pointer to an XMPMeta instance.
    xmpRef_ = reinterpret_cast<XMPMetaRef>(&meta_);
    result_ = WXMP_Result{};
    // Provide a recognizable sentinel so we can see if success path overwrote it.
    result_.int32Result = 0xA5A5A5A5u;
  }

  static constexpr XMP_StringPtr kTestSchemaNS = "http://ns.example.com/xmpmeta-test/1.0/";
  static constexpr XMP_StringPtr kTestPrefix   = "tst";
  static constexpr XMP_StringPtr kStructName   = "MyStruct";
  static constexpr XMP_StringPtr kFieldName    = "MyField";

  XMPMeta meta_;
  XMPMetaRef xmpRef_{};
  WXMP_Result result_{};

  // Helper: some wrapper error paths populate errMessage. We only assert presence / light content.
  static void ExpectErrorMessageSet(const WXMP_Result& r) {
    ASSERT_NE(r.errMessage, nullptr);
    // Be tolerant: just ensure it's non-empty.
    ASSERT_NE(*r.errMessage, '\0');
  }
};

TEST_F(WXMPMeta_DoesStructFieldExist_1_Test_2021, ReturnsFalseWhenStructFieldNotPresent_2021) {
  // No struct field set -> should report not found.
  WXMPMeta_DoesStructFieldExist_1(xmpRef_, kTestSchemaNS, kStructName, kTestSchemaNS, kFieldName, &result_);

  // Success path should not set errMessage.
  EXPECT_EQ(result_.errMessage, nullptr);
  EXPECT_EQ(result_.int32Result, 0u);
}

TEST_F(WXMPMeta_DoesStructFieldExist_1_Test_2021, ReturnsTrueAfterSettingStructField_2021) {
  // Arrange: create the struct field using the public interface.
  meta_.SetStructField(kTestSchemaNS, kStructName, kTestSchemaNS, kFieldName, "value", 0 /* options */);

  WXMPMeta_DoesStructFieldExist_1(xmpRef_, kTestSchemaNS, kStructName, kTestSchemaNS, kFieldName, &result_);

  EXPECT_EQ(result_.errMessage, nullptr);
  EXPECT_EQ(result_.int32Result, 1u);
}

TEST_F(WXMPMeta_DoesStructFieldExist_1_Test_2021, EmptyFieldValueStillCountsAsExisting_2021) {
  // Boundary-ish case: empty value but explicit field creation.
  meta_.SetStructField(kTestSchemaNS, kStructName, kTestSchemaNS, kFieldName, "" /* empty */, 0);

  WXMPMeta_DoesStructFieldExist_1(xmpRef_, kTestSchemaNS, kStructName, kTestSchemaNS, kFieldName, &result_);

  EXPECT_EQ(result_.errMessage, nullptr);
  EXPECT_EQ(result_.int32Result, 1u);
}

TEST_F(WXMPMeta_DoesStructFieldExist_1_Test_2021, ErrorWhenSchemaNSIsNull_2021) {
  WXMPMeta_DoesStructFieldExist_1(xmpRef_, nullptr, kStructName, kTestSchemaNS, kFieldName, &result_);
  ExpectErrorMessageSet(result_);
}

TEST_F(WXMPMeta_DoesStructFieldExist_1_Test_2021, ErrorWhenSchemaNSIsEmpty_2021) {
  WXMPMeta_DoesStructFieldExist_1(xmpRef_, "" /* empty */, kStructName, kTestSchemaNS, kFieldName, &result_);
  ExpectErrorMessageSet(result_);

  // If the wrapper propagates the thrown message text, it should mention "Empty".
  // Keep it soft: don't require exact wording.
  EXPECT_NE(std::strstr(result_.errMessage, "Empty"), nullptr);
}

TEST_F(WXMPMeta_DoesStructFieldExist_1_Test_2021, ErrorWhenStructNameIsNull_2021) {
  WXMPMeta_DoesStructFieldExist_1(xmpRef_, kTestSchemaNS, nullptr, kTestSchemaNS, kFieldName, &result_);
  ExpectErrorMessageSet(result_);
}

TEST_F(WXMPMeta_DoesStructFieldExist_1_Test_2021, ErrorWhenStructNameIsEmpty_2021) {
  WXMPMeta_DoesStructFieldExist_1(xmpRef_, kTestSchemaNS, "" /* empty */, kTestSchemaNS, kFieldName, &result_);
  ExpectErrorMessageSet(result_);
  EXPECT_NE(std::strstr(result_.errMessage, "Empty"), nullptr);
}

TEST_F(WXMPMeta_DoesStructFieldExist_1_Test_2021, ErrorWhenFieldNSIsNull_2021) {
  WXMPMeta_DoesStructFieldExist_1(xmpRef_, kTestSchemaNS, kStructName, nullptr, kFieldName, &result_);
  ExpectErrorMessageSet(result_);
}

TEST_F(WXMPMeta_DoesStructFieldExist_1_Test_2021, ErrorWhenFieldNSIsEmpty_2021) {
  WXMPMeta_DoesStructFieldExist_1(xmpRef_, kTestSchemaNS, kStructName, "" /* empty */, kFieldName, &result_);
  ExpectErrorMessageSet(result_);
  EXPECT_NE(std::strstr(result_.errMessage, "Empty"), nullptr);
}

TEST_F(WXMPMeta_DoesStructFieldExist_1_Test_2021, ErrorWhenFieldNameIsNull_2021) {
  WXMPMeta_DoesStructFieldExist_1(xmpRef_, kTestSchemaNS, kStructName, kTestSchemaNS, nullptr, &result_);
  ExpectErrorMessageSet(result_);
}

TEST_F(WXMPMeta_DoesStructFieldExist_1_Test_2021, ErrorWhenFieldNameIsEmpty_2021) {
  WXMPMeta_DoesStructFieldExist_1(xmpRef_, kTestSchemaNS, kStructName, kTestSchemaNS, "" /* empty */, &result_);
  ExpectErrorMessageSet(result_);
  EXPECT_NE(std::strstr(result_.errMessage, "Empty"), nullptr);
}

}  // namespace