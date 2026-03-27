// File: bytemapbuilder_mark_test.cc

#include <cstdint>
#include "gtest/gtest.h"

// Include the header that declares re2::ByteMapBuilder.
// Adjust the include path to match your project layout.
#include "re2/prog.h"   // or the correct header that contains ByteMapBuilder

using re2::ByteMapBuilder;

// Test fixture left minimal — no internal state is accessed.
class ByteMapBuilderTest_408 : public ::testing::Test {};

// ---- Normal operation & boundary acceptance ----

TEST_F(ByteMapBuilderTest_408, Mark_AllBytesNoOp_408) {
  ByteMapBuilder b;
  // Should not crash or terminate: valid full range [0, 255].
  b.Mark(0, 255);
  SUCCEED();
}

TEST_F(ByteMapBuilderTest_408, Mark_SingleByteAtLowerBoundary_408) {
  ByteMapBuilder b;
  // Lowest single-byte range is accepted.
  b.Mark(0, 0);
  SUCCEED();
}

TEST_F(ByteMapBuilderTest_408, Mark_SingleByteAtUpperBoundary_408) {
  ByteMapBuilder b;
  // Highest single-byte range is accepted.
  b.Mark(255, 255);
  SUCCEED();
}

TEST_F(ByteMapBuilderTest_408, Mark_ProperRangeWithinBounds_408) {
  ByteMapBuilder b;
  // Typical in-bounds non-empty range is accepted.
  b.Mark(10, 20);
  SUCCEED();
}

TEST_F(ByteMapBuilderTest_408, Mark_MultipleValidCalls_408) {
  ByteMapBuilder b;
  // Multiple valid ranges should be accepted without termination.
  b.Mark(0, 0);
  b.Mark(1, 2);
  b.Mark(100, 150);
  b.Mark(255, 255);
  SUCCEED();
}

// ---- Argument validation via ABSL_DCHECK (observable as death in debug) ----

TEST_F(ByteMapBuilderTest_408, Mark_LoGreaterThanHi_TriggersDeathInDebug_408) {
#ifndef NDEBUG
  ByteMapBuilder b;
  EXPECT_DEATH({ b.Mark(10, 9); }, "");  // message is implementation-defined
#else
  GTEST_SKIP() << "ABSL_DCHECKs are disabled in release builds.";
#endif
}

TEST_F(ByteMapBuilderTest_408, Mark_NegativeLo_TriggersDeathInDebug_408) {
#ifndef NDEBUG
  ByteMapBuilder b;
  EXPECT_DEATH({ b.Mark(-1, 10); }, "");
#else
  GTEST_SKIP() << "ABSL_DCHECKs are disabled in release builds.";
#endif
}

TEST_F(ByteMapBuilderTest_408, Mark_NegativeHi_TriggersDeathInDebug_408) {
#ifndef NDEBUG
  ByteMapBuilder b;
  EXPECT_DEATH({ b.Mark(0, -1); }, "");
#else
  GTEST_SKIP() << "ABSL_DCHECKs are disabled in release builds.";
#endif
}

TEST_F(ByteMapBuilderTest_408, Mark_LoAbove255_TriggersDeathInDebug_408) {
#ifndef NDEBUG
  ByteMapBuilder b;
  EXPECT_DEATH({ b.Mark(256, 256); }, "");
#else
  GTEST_SKIP() << "ABSL_DCHECKs are disabled in release builds.";
#endif
}

TEST_F(ByteMapBuilderTest_408, Mark_HiAbove255_TriggersDeathInDebug_408) {
#ifndef NDEBUG
  ByteMapBuilder b;
  EXPECT_DEATH({ b.Mark(0, 256); }, "");
#else
  GTEST_SKIP() << "ABSL_DCHECKs are disabled in release builds.";
#endif
}

TEST_F(ByteMapBuilderTest_408, Mark_BothOutOfRange_TriggersDeathInDebug_408) {
#ifndef NDEBUG
  ByteMapBuilder b;
  EXPECT_DEATH({ b.Mark(-5, 300); }, "");
#else
  GTEST_SKIP() << "ABSL_DCHECKs are disabled in release builds.";
#endif
}
