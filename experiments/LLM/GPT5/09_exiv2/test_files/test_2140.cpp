// =================================================================================================
// UNIT TESTS for DumpNodeOptions (TEST_ID = 2140)
// File-under-test: ./TestProjects/exiv2/xmpsdk/src/XMPMeta.cpp
//
// Notes:
// - DumpNodeOptions has internal linkage (static). To test it without re-implementing logic,
//   this test directly includes the implementation TU.
// - Tests validate only observable behavior: emitted text via the provided output proc and
//   returned status propagation.
// =================================================================================================

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <cstddef>
#include <cstdint>
#include <string>

// Include the implementation so the test can call the TU-local static function.
#include "TestProjects/exiv2/xmpsdk/src/XMPMeta.cpp"

namespace {

// A tiny capture sink for XMP_TextOutputProc.
struct CaptureOut {
  std::string text;
  int call_count = 0;
  int fail_on_call = -1;  // 1-based; -1 means never fail
  XMP_Status fail_status = 0;
};

extern "C" XMP_Status CapturingOutProc(void* refCon, const char* buffer, XMP_StringLen count) {
  auto* cap = reinterpret_cast<CaptureOut*>(refCon);
  cap->call_count += 1;

  if ((cap->fail_on_call > 0) && (cap->call_count == cap->fail_on_call)) {
    return cap->fail_status;
  }

  if ((buffer != nullptr) && (count > 0)) {
    cap->text.append(buffer, static_cast<std::size_t>(count));
  }
  return 0;
}

static std::string DumpWithOptions(XMP_OptionBits options, XMP_Status* outStatus = nullptr,
                                  int failOnCall = -1,
                                  XMP_Status failStatus = static_cast<XMP_Status>(123)) {
  CaptureOut cap;
  cap.fail_on_call = failOnCall;
  cap.fail_status = failStatus;

  const XMP_Status st = DumpNodeOptions(options, &CapturingOutProc, &cap);
  if (outStatus) *outStatus = st;
  return cap.text;
}

}  // namespace

TEST(DumpNodeOptionsTest_2140, OptionsZeroEmitsExactToken_2140) {
  XMP_Status st = 0;
  const std::string out = DumpWithOptions(static_cast<XMP_OptionBits>(0), &st);

  EXPECT_EQ(out, "(0x0)");
  EXPECT_EQ(st, 0);
}

TEST(DumpNodeOptionsTest_2140, NonZeroOptionsEmitsFramingAndHexPrefix_2140) {
  XMP_Status st = 0;
  const std::string out = DumpWithOptions(static_cast<XMP_OptionBits>(0x80000000u), &st);

  // Observable framing (don’t assume exact hex formatting details).
  EXPECT_THAT(out, ::testing::StartsWith("(0x"));
  EXPECT_THAT(out, ::testing::HasSubstr(" :"));
  EXPECT_THAT(out, ::testing::EndsWith(")"));
  EXPECT_EQ(st, 0);
}

TEST(DumpNodeOptionsTest_2140, SingleHighBitIncludesSchemaName_2140) {
  const std::string out = DumpWithOptions(static_cast<XMP_OptionBits>(0x80000000u));
  EXPECT_THAT(out, ::testing::HasSubstr(" schema"));
}

TEST(DumpNodeOptionsTest_2140, SingleLowBitIncludesURIName_2140) {
  // Based on the optNames table in the provided snippet, the second-lowest bit maps to " URI".
  const std::string out = DumpWithOptions(static_cast<XMP_OptionBits>(0x00000002u));
  EXPECT_THAT(out, ::testing::HasSubstr(" URI"));
}

TEST(DumpNodeOptionsTest_2140, MultipleBitsEmitNamesInDescendingBitOrder_2140) {
  // Highest bit (" schema") and the 0x2 bit (" URI") should appear in that order.
  const std::string out = DumpWithOptions(static_cast<XMP_OptionBits>(0x80000002u));

  const std::size_t posSchema = out.find(" schema");
  const std::size_t posUri = out.find(" URI");

  ASSERT_NE(posSchema, std::string::npos);
  ASSERT_NE(posUri, std::string::npos);
  EXPECT_LT(posSchema, posUri);
}

TEST(DumpNodeOptionsTest_2140, AllBitsSetIncludesKnownSentinelNames_2140) {
  // Boundary: exercise iteration across all 32 bits.
  const std::string out = DumpWithOptions(static_cast<XMP_OptionBits>(0xFFFFFFFFu));

  // These strings are explicitly present in the provided optNames list.
  EXPECT_THAT(out, ::testing::HasSubstr(" -COMMAS-"));
  EXPECT_THAT(out, ::testing::HasSubstr(" -AFTER-"));
  EXPECT_THAT(out, ::testing::HasSubstr(" -BEFORE-"));
}

TEST(DumpNodeOptionsTest_2140, OutputProcErrorPropagatesAsReturnStatus_2140) {
  // Error case: force the output proc to fail on its first invocation.
  const XMP_Status kErr = static_cast<XMP_Status>(777);

  XMP_Status st = 0;
  const std::string out =
      DumpWithOptions(static_cast<XMP_OptionBits>(0x80000000u), &st, /*failOnCall=*/1, kErr);

  EXPECT_EQ(st, kErr);
  // Some implementations may have emitted nothing or partial output before noticing the error.
  // We only assert it didn’t magically become the full successful output.
  const std::string okOut = DumpWithOptions(static_cast<XMP_OptionBits>(0x80000000u));
  EXPECT_LE(out.size(), okOut.size());
}

TEST(DumpNodeOptionsTest_2140, OutputProcErrorMidStreamProducesShorterOutputThanSuccess_2140) {
  // Error case: fail after a couple of calls; output should typically be truncated vs success.
  const XMP_Status kErr = static_cast<XMP_Status>(999);

  XMP_Status st = 0;
  const std::string partial =
      DumpWithOptions(static_cast<XMP_OptionBits>(0xFFFFFFFFu), &st, /*failOnCall=*/2, kErr);

  EXPECT_EQ(st, kErr);

  const std::string full = DumpWithOptions(static_cast<XMP_OptionBits>(0xFFFFFFFFu));
  EXPECT_LT(partial.size(), full.size());
}