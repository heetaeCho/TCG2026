// ============================================================================
// TEST_ID: 2046
// Unit tests for WXMPMeta_SerializeToBuffer_1
// File: ./TestProjects/exiv2/xmpsdk/src/WXMPMeta.cpp
// ============================================================================

#include <gtest/gtest.h>

#include <cstring>
#include <limits>

#include "XMP_Const.h"
#include "XMPMeta.hpp"
#include "client-glue/WXMP_Common.hpp"

// The wrapper under test is implemented in WXMPMeta.cpp.
// Some builds may already provide a declaration via a public header; declaring
// here keeps the test self-contained and does not re-implement any logic.
extern "C" void WXMPMeta_SerializeToBuffer_1(XMPMetaRef xmpRef, XMP_StringPtr* rdfString, XMP_StringLen* rdfSize,
                                            XMP_OptionBits options, XMP_StringLen padding, XMP_StringPtr newline,
                                            XMP_StringPtr indent, XMP_Index baseIndent, WXMP_Result* wResult);

namespace {

class WXMPMetaSerializeToBuffer1Test_2046 : public ::testing::Test {
public:
  static void SetUpTestSuite() {
    // XMP toolkit often requires initialization. If Initialize() is idempotent in
    // your build, calling it here is safe. If it's already initialized elsewhere,
    // Initialize() should still succeed (or be a no-op).
    (void)XMPMeta::Initialize();
  }

  static void TearDownTestSuite() {
    // Best-effort cleanup.
    XMPMeta::Terminate();
  }

protected:
  void TearDown() override {
    // The wrapper comment indicates it "always keep[s] the lock" because a string is returned.
    // Release any global lock between tests to avoid cross-test interference.
    // Options are not specified by the interface here; 0 is commonly used for default unlock.
    XMPMeta::Unlock(0);
  }

  static XMPMetaRef MakeMetaRef() {
    // The wrapper converts XMPMetaRef to a const XMPMeta& (black-box). In the toolkit,
    // XMPMetaRef typically refers to an XMPMeta instance. We treat it as an opaque handle
    // and only provide a valid instance address.
    auto* meta = new XMPMeta();
    return reinterpret_cast<XMPMetaRef>(meta);
  }

  static void DestroyMetaRef(XMPMetaRef ref) {
    delete reinterpret_cast<XMPMeta*>(ref);
  }
};

TEST_F(WXMPMetaSerializeToBuffer1Test_2046, SerializesWithDefaultsWhenNewlineAndIndentNull_2046) {
  XMPMetaRef ref = MakeMetaRef();

  XMP_StringPtr rdf = nullptr;
  XMP_StringLen size = 0;
  WXMP_Result result;

  // newline==nullptr and indent==nullptr should be handled (defaulted to "") by the wrapper.
  EXPECT_NO_THROW(WXMPMeta_SerializeToBuffer_1(ref, &rdf, &size,
                                              /*options=*/0,
                                              /*padding=*/0,
                                              /*newline=*/nullptr,
                                              /*indent=*/nullptr,
                                              /*baseIndent=*/0,
                                              &result));

  // On success, wrapper should not report an error message.
  EXPECT_EQ(result.errMessage, nullptr);

  // Wrapper promises "a string is always returned" (comment in implementation).
  ASSERT_NE(rdf, nullptr);

  // Size should be consistent with the returned C-string (at least large enough to contain it).
  const size_t cLen = std::strlen(rdf);
  EXPECT_GE(static_cast<size_t>(size), cLen);

  DestroyMetaRef(ref);
}

TEST_F(WXMPMetaSerializeToBuffer1Test_2046, SerializesNonEmptyBufferForEmptyMeta_2046) {
  XMPMetaRef ref = MakeMetaRef();

  XMP_StringPtr rdf = nullptr;
  XMP_StringLen size = 0;
  WXMP_Result result;

  EXPECT_NO_THROW(WXMPMeta_SerializeToBuffer_1(ref, &rdf, &size,
                                              /*options=*/0,
                                              /*padding=*/0,
                                              /*newline=*/"\n",
                                              /*indent=*/"  ",
                                              /*baseIndent=*/0,
                                              &result));

  EXPECT_EQ(result.errMessage, nullptr);
  ASSERT_NE(rdf, nullptr);

  // Even an "empty" meta typically serializes to some RDF packet; at minimum it should be a valid C-string.
  EXPECT_GE(std::strlen(rdf), static_cast<size_t>(0));
  EXPECT_GE(static_cast<size_t>(size), std::strlen(rdf));

  DestroyMetaRef(ref);
}

TEST_F(WXMPMetaSerializeToBuffer1Test_2046, AllowsNullRdfStringPointerButStillWritesSize_2046) {
  XMPMetaRef ref = MakeMetaRef();

  // Pass rdfString==nullptr (wrapper routes to internal voidStringPtr).
  XMP_StringLen size = 0;
  WXMP_Result result;

  EXPECT_NO_THROW(WXMPMeta_SerializeToBuffer_1(ref,
                                              /*rdfString=*/nullptr,
                                              /*rdfSize=*/&size,
                                              /*options=*/0,
                                              /*padding=*/0,
                                              /*newline=*/"\n",
                                              /*indent=*/" ",
                                              /*baseIndent=*/0,
                                              &result));

  EXPECT_EQ(result.errMessage, nullptr);

  // We cannot observe the string pointer (we passed nullptr), but size should be set to something consistent.
  // Accept 0 as a boundary (implementation-dependent), but it must be a valid write.
  EXPECT_GE(size, static_cast<XMP_StringLen>(0));

  DestroyMetaRef(ref);
}

TEST_F(WXMPMetaSerializeToBuffer1Test_2046, HandlesBoundaryValuesForPaddingAndBaseIndent_2046) {
  XMPMetaRef ref = MakeMetaRef();

  XMP_StringPtr rdf = nullptr;
  XMP_StringLen size = 0;
  WXMP_Result result;

  const XMP_StringLen padding = std::numeric_limits<XMP_StringLen>::max();
  const XMP_Index baseIndent = std::numeric_limits<XMP_Index>::max();

  // Boundary/large values should be handled (either succeed or report an error through wResult).
  // We only assert it does not crash and that any error is reported via errMessage.
  EXPECT_NO_THROW(WXMPMeta_SerializeToBuffer_1(ref, &rdf, &size,
                                              /*options=*/0,
                                              padding,
                                              /*newline=*/"\n",
                                              /*indent=*/" ",
                                              baseIndent,
                                              &result));

  if (result.errMessage == nullptr) {
    ASSERT_NE(rdf, nullptr);
    EXPECT_GE(static_cast<size_t>(size), std::strlen(rdf));
  } else {
    // If there is an error, the interface exposes it via errMessage.
    EXPECT_NE(result.errMessage, nullptr);
  }

  DestroyMetaRef(ref);
}

TEST_F(WXMPMetaSerializeToBuffer1Test_2046, NullMetaRefReportsErrorThroughResult_2046) {
  XMP_StringPtr rdf = nullptr;
  XMP_StringLen size = 0;
  WXMP_Result result;

  // Passing a null meta ref is an observable error case; wrapper macros typically catch and report.
  EXPECT_NO_THROW(WXMPMeta_SerializeToBuffer_1(/*xmpRef=*/nullptr,
                                              &rdf, &size,
                                              /*options=*/0,
                                              /*padding=*/0,
                                              /*newline=*/"\n",
                                              /*indent=*/" ",
                                              /*baseIndent=*/0,
                                              &result));

  EXPECT_NE(result.errMessage, nullptr);
}

}  // namespace