// ============================================================================
// Unit tests for WXMPMeta_DumpObject_1 (TEST_ID: 2035)
// File: WXMPMeta_DumpObject_1_test_2035.cpp
// ============================================================================

#include <gtest/gtest.h>
#include <string>

// XMP SDK / Exiv2 XMP glue headers (available in the codebase under test).
#include "XMP_Const.h"
#include "WXMP_Common.hpp"
#include "XMPMeta.hpp"

// The wrapper under test is implemented in ./TestProjects/exiv2/xmpsdk/src/WXMPMeta.cpp.
// Its declaration is typically available via the public/client glue headers in the project.
// If your build exposes a different header for these wrapper entry points, adjust include(s).
extern "C" {
void WXMPMeta_DumpObject_1(XMPMetaRef xmpRef, XMP_TextOutputProc outProc, void* refCon, WXMP_Result* wResult);
}

// ------------------------------------------------------------
// Test fixture
// ------------------------------------------------------------
class WXMPMeta_DumpObject_1_Test_2035 : public ::testing::Test {
protected:
  static void SetUpTestSuite() {
    // Initialize the toolkit once for this suite. If Initialize is idempotent,
    // this remains safe; if required, it ensures API calls are valid.
    (void)XMPMeta::Initialize();
  }

  static void TearDownTestSuite() {
    // Best-effort cleanup.
    XMPMeta::Terminate();
  }

  struct OutputCapture {
    std::string data;
    int calls = 0;

    static void Proc(void* refCon, XMP_StringPtr buffer, XMP_StringLen bufferLen) {
      auto* self = static_cast<OutputCapture*>(refCon);
      if (self == nullptr) return;

      self->calls++;

      if (buffer != nullptr && bufferLen > 0) {
        self->data.append(buffer, static_cast<size_t>(bufferLen));
      }
    }
  };

  static XMPMetaRef MakeMetaRef() {
    // Treat the implementation as a black box: we only rely on the commonly-used
    // public convention that XMPMetaRef refers to an XMPMeta instance.
    return reinterpret_cast<XMPMetaRef>(new XMPMeta());
  }

  static void FreeMetaRef(XMPMetaRef ref) {
    delete reinterpret_cast<XMPMeta*>(ref);
  }
};

// ------------------------------------------------------------
// Normal operation
// ------------------------------------------------------------
TEST_F(WXMPMeta_DumpObject_1_Test_2035, DumpObject_WritesToCallbackAndReportsStatus_2035) {
  WXMP_Result result;
  OutputCapture cap;

  XMPMetaRef ref = MakeMetaRef();

  ASSERT_NO_FATAL_FAILURE(
      WXMPMeta_DumpObject_1(ref, &OutputCapture::Proc, &cap, &result));

  // Observable behavior: on success, errMessage should remain null.
  EXPECT_EQ(result.errMessage, nullptr);

  // The wrapper forwards the underlying status into int32Result.
  // For "normal operation", we expect a "success" style status.
  // (Most XMP APIs use 0 for OK.)
  EXPECT_EQ(result.int32Result, 0u);

  // Observable external interaction: callback should have been invoked (at least once).
  EXPECT_GE(cap.calls, 1);

  // Data may vary depending on implementation; ensure we got *some* output.
  EXPECT_FALSE(cap.data.empty());

  FreeMetaRef(ref);
}

TEST_F(WXMPMeta_DumpObject_1_Test_2035, DumpObject_AllowsNullRefCon_2035) {
  WXMP_Result result;

  XMPMetaRef ref = MakeMetaRef();

  // refCon is passed through; null should be acceptable for many output procs.
  // Here we provide a proc that tolerates null refCon.
  auto proc = +[](void* /*refCon*/, XMP_StringPtr /*buffer*/, XMP_StringLen /*len*/) {};

  WXMPMeta_DumpObject_1(ref, proc, nullptr, &result);

  EXPECT_EQ(result.errMessage, nullptr);
  EXPECT_EQ(result.int32Result, 0u);

  FreeMetaRef(ref);
}

// ------------------------------------------------------------
// Boundary / error cases (observable through wrapper result)
// ------------------------------------------------------------
TEST_F(WXMPMeta_DumpObject_1_Test_2035, DumpObject_NullOutputProcReportsBadParam_2035) {
  WXMP_Result result;
  XMPMetaRef ref = MakeMetaRef();

  // Contract visible in implementation: outProc == 0 => XMP_Throw(..., kXMPErr_BadParam).
  // Wrapper macros are expected to translate that into WXMP_Result fields.
  WXMPMeta_DumpObject_1(ref, nullptr, nullptr, &result);

  EXPECT_NE(result.errMessage, nullptr);
  EXPECT_EQ(result.int32Result, static_cast<XMP_Uns32>(kXMPErr_BadParam));

  FreeMetaRef(ref);
}

TEST_F(WXMPMeta_DumpObject_1_Test_2035, DumpObject_NullMetaRefReportsBadObjectOrError_2035) {
  WXMP_Result result;
  WXMPMeta_DumpObject_1(nullptr, &WXMPMeta_DumpObject_1_Test_2035::OutputCapture::Proc, nullptr, &result);

  // We avoid assuming internal mapping details beyond "error is observable".
  EXPECT_NE(result.errMessage, nullptr);

  // Many XMP wrappers report kXMPErr_BadObject for null/invalid object refs.
  // If the codebase uses a different error code, this expectation may be updated
  // by aligning with the public wrapper contract.
  EXPECT_EQ(result.int32Result, static_cast<XMP_Uns32>(kXMPErr_BadObject));
}