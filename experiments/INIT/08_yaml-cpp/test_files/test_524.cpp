// File: emitter_set_indent_test_524.cpp
#include <gtest/gtest.h>

#include <cstddef>
#include <limits>
#include <sstream>
#include <string>

#include "yaml-cpp/emitter.h"

namespace {

using YAML::Emitter;

// Keep assertions conservative: only rely on observable public API.
static void ExpectConsistentStateAfterSetIndent(Emitter& out, bool ok) {
  // SetIndent should not throw; if it reports success, the emitter should still
  // appear usable via the public "good"/error surface. If it reports failure,
  // we only require that some observable "not ok" signal may exist.
  if (ok) {
    EXPECT_TRUE(out.good());
    // Some implementations may keep last error sticky; don't require empty.
    (void)out.GetLastError();
  } else {
    const bool not_good = !out.good();
    const bool has_error = !out.GetLastError().empty();
    EXPECT_TRUE(not_good || has_error);
  }
}

class EmitterSetIndentTest_524 : public ::testing::Test {
 protected:
  std::stringstream ss_;
};

TEST_F(EmitterSetIndentTest_524, DefaultConstruct_NoThrowAndDoesNotChangeEmptyBuffer_524) {
  Emitter out;

  const char* before_cstr = out.c_str();
  const std::size_t before_size = out.size();
  const bool before_good = out.good();
  const std::string before_err = out.GetLastError();

  bool ok = false;
  EXPECT_NO_THROW(ok = out.SetIndent(2));

  // Pure formatting change should not mutate output buffer by itself.
  EXPECT_EQ(out.size(), before_size);
  EXPECT_STREQ(out.c_str(), before_cstr);

  // "good" / "last error" behavior is implementation-defined; keep it consistent.
  (void)before_good;
  (void)before_err;
  ExpectConsistentStateAfterSetIndent(out, ok);
}

TEST_F(EmitterSetIndentTest_524, StreamConstruct_NoThrowAndDoesNotChangeEmptyBuffer_524) {
  Emitter out(ss_);

  const std::size_t before_size = out.size();
  const std::string before_err = out.GetLastError();

  bool ok = false;
  EXPECT_NO_THROW(ok = out.SetIndent(4));

  EXPECT_EQ(out.size(), before_size);

  // If it failed, we allow any observable error signal.
  // If it succeeded, we at least expect it to remain usable.
  (void)before_err;
  ExpectConsistentStateAfterSetIndent(out, ok);
}

TEST_F(EmitterSetIndentTest_524, Boundary_ZeroIndent_IsHandledWithoutThrow_524) {
  Emitter out;

  bool ok = false;
  EXPECT_NO_THROW(ok = out.SetIndent(0));

  ExpectConsistentStateAfterSetIndent(out, ok);
}

TEST_F(EmitterSetIndentTest_524, Boundary_OneIndent_IsHandledWithoutThrow_524) {
  Emitter out;

  bool ok = false;
  EXPECT_NO_THROW(ok = out.SetIndent(1));

  ExpectConsistentStateAfterSetIndent(out, ok);
}

TEST_F(EmitterSetIndentTest_524, TypicalValues_AreHandledWithoutThrow_524) {
  Emitter out;

  for (std::size_t n : {2u, 3u, 4u, 8u}) {
    bool ok = false;
    EXPECT_NO_THROW(ok = out.SetIndent(n)) << "n=" << n;
    ExpectConsistentStateAfterSetIndent(out, ok);
  }
}

TEST_F(EmitterSetIndentTest_524, RepeatedCalls_SameValue_IsConsistentAndNoThrow_524) {
  Emitter out;

  bool ok1 = false;
  bool ok2 = false;
  EXPECT_NO_THROW(ok1 = out.SetIndent(2));
  EXPECT_NO_THROW(ok2 = out.SetIndent(2));

  // We don't assume what "ok" means, but the same call on the same object should
  // behave consistently.
  EXPECT_EQ(ok1, ok2);

  ExpectConsistentStateAfterSetIndent(out, ok2);
}

TEST_F(EmitterSetIndentTest_524, ExtremeValue_MaxSizeT_IsHandledWithoutThrow_524) {
  Emitter out;

  const std::size_t n = (std::numeric_limits<std::size_t>::max)();
  bool ok = false;
  EXPECT_NO_THROW(ok = out.SetIndent(n));

  // If this is rejected, it should manifest via public-facing state in some way.
  ExpectConsistentStateAfterSetIndent(out, ok);
}

TEST_F(EmitterSetIndentTest_524, DoesNotMutateOutputBuffer_WhenNoWritesHaveOccurred_524) {
  Emitter out;

  // Capture a stable view of the buffer.
  const std::string before = out.c_str();
  const std::size_t before_size = out.size();

  bool ok = false;
  EXPECT_NO_THROW(ok = out.SetIndent(6));

  EXPECT_EQ(out.size(), before_size);
  EXPECT_EQ(std::string(out.c_str()), before);

  ExpectConsistentStateAfterSetIndent(out, ok);
}

}  // namespace