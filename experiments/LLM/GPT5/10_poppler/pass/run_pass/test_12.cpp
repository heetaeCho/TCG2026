// gmallocn_gtest_12.cpp
// Unit tests for gmallocn (./TestProjects/poppler/goo/gmem.h)
//
// These tests treat gmallocn as a black box and verify only observable behavior:
// - return values
// - stderr output
// - process termination (death tests) when observable
// - interactions with external collaborators: checkedMultiply(...) and gmalloc(...)

#include <gtest/gtest.h>

#include <atomic>
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <limits>

#if GTEST_HAS_DEATH_TEST
#include <gtest/gtest-death-test.h>
#endif

// Include the real header under test.
#include "goo/gmem.h"

// ---- Test doubles for external collaborators used by gmallocn ----
// gmallocn depends on:
//   - checkedMultiply(int, int, int*)
//   - gmalloc(int, bool)
//
// We provide definitions here so the inline function in the header links against them,
// and so we can verify observable external interactions.

namespace {

struct CheckedMultiplyBehavior {
  // If true, checkedMultiply reports overflow/error.
  bool should_report_overflow = false;

  // If false, checkedMultiply writes product to out (as int).
  // For safety in tests, product_value will be used.
  int product_value = 0;

  // Call recording
  int call_count = 0;
  int last_count = 0;
  int last_size = 0;
  int* last_out_ptr = nullptr;
};

struct GmallocBehavior {
  // Returned pointer from gmalloc.
  void* return_ptr = nullptr;

  // Call recording
  int call_count = 0;
  int last_bytes = 0;
  bool last_checkoverflow = false;
};

CheckedMultiplyBehavior& CM() {
  static CheckedMultiplyBehavior s;
  return s;
}

GmallocBehavior& GM() {
  static GmallocBehavior s;
  return s;
}

void ResetFakes() {
  CM() = CheckedMultiplyBehavior{};
  GM() = GmallocBehavior{};
}

// Helper: a stable non-null pointer value for tests.
void* FakePtr() {
  static int dummy = 123;
  return &dummy;
}

}  // namespace

// Free function collaborators (must be in global namespace to match calls from header).
extern "C" bool checkedMultiply(int count, int size, int* bytes) {
  auto& cm = CM();
  cm.call_count++;
  cm.last_count = count;
  cm.last_size = size;
  cm.last_out_ptr = bytes;

  if (cm.should_report_overflow) {
    return true;
  }
  if (bytes) {
    *bytes = cm.product_value;
  }
  return false;
}

// NOTE: Signature matches the call site: gmalloc(bytes, checkoverflow).
extern "C" void* gmalloc(int bytes, bool checkoverflow) {
  auto& gm = GM();
  gm.call_count++;
  gm.last_bytes = bytes;
  gm.last_checkoverflow = checkoverflow;
  return gm.return_ptr;
}

// -------------------- Tests --------------------

class GmallocnTest_12 : public ::testing::Test {
protected:
  void SetUp() override { ResetFakes(); }
};

TEST_F(GmallocnTest_12, CountZeroReturnsNullptrAndNoExternalCalls_12) {
  GM().return_ptr = FakePtr();
  CM().product_value = 999;

  void* p = gmallocn(/*count=*/0, /*size=*/4);

  EXPECT_EQ(p, nullptr);
  EXPECT_EQ(CM().call_count, 0);
  EXPECT_EQ(GM().call_count, 0);
}

TEST_F(GmallocnTest_12, NormalAllocationCallsCheckedMultiplyAndGmallocAndReturnsPointer_12) {
  // Arrange: checkedMultiply returns false and writes product bytes.
  CM().should_report_overflow = false;
  CM().product_value = 12;  // bytes
  GM().return_ptr = FakePtr();

  // Act
  void* p = gmallocn(/*count=*/3, /*size=*/4, /*checkoverflow=*/false);

  // Assert observable behavior
  EXPECT_EQ(p, FakePtr());

  // External interactions
  EXPECT_EQ(CM().call_count, 1);
  EXPECT_EQ(CM().last_count, 3);
  EXPECT_EQ(CM().last_size, 4);
  EXPECT_NE(CM().last_out_ptr, nullptr);

  EXPECT_EQ(GM().call_count, 1);
  EXPECT_EQ(GM().last_bytes, 12);
  EXPECT_FALSE(GM().last_checkoverflow);
}

TEST_F(GmallocnTest_12, NormalAllocationForwardsCheckoverflowFlagToGmalloc_12) {
  CM().should_report_overflow = false;
  CM().product_value = 20;
  GM().return_ptr = FakePtr();

  void* p = gmallocn(/*count=*/4, /*size=*/5, /*checkoverflow=*/true);

  EXPECT_EQ(p, FakePtr());
  EXPECT_EQ(CM().call_count, 1);
  EXPECT_EQ(GM().call_count, 1);
  EXPECT_EQ(GM().last_bytes, 20);
  EXPECT_TRUE(GM().last_checkoverflow);
}

TEST_F(GmallocnTest_12, OverflowWhenCheckoverflowTrueReturnsNullptrPrintsErrorAndDoesNotCallGmalloc_12) {
  CM().should_report_overflow = true;
  GM().return_ptr = FakePtr();

  testing::internal::CaptureStderr();
  void* p = gmallocn(/*count=*/1000000, /*size=*/1000000, /*checkoverflow=*/true);
  std::string err = testing::internal::GetCapturedStderr();

  EXPECT_EQ(p, nullptr);
  EXPECT_NE(err.find("Bogus memory allocation size"), std::string::npos);

  // It should still consult checkedMultiply.
  EXPECT_EQ(CM().call_count, 1);
  // And must not call gmalloc if it returns nullptr early.
  EXPECT_EQ(GM().call_count, 0);
}

#if GTEST_HAS_DEATH_TEST
TEST_F(GmallocnTest_12, OverflowWhenCheckoverflowFalseAbortsAndPrintsError_12) {
  CM().should_report_overflow = true;

  // Death test: observable behavior is termination. Regex should match the error text.
  ASSERT_DEATH(
      {
        (void)gmallocn(/*count=*/1000000, /*size=*/1000000, /*checkoverflow=*/false);
      },
      "Bogus memory allocation size");
}

TEST_F(GmallocnTest_12, NegativeCountAbortsAndPrintsError_12) {
  // checkedMultiply should not be required for this path, but we only assert death + message.
  ASSERT_DEATH(
      {
        (void)gmallocn(/*count=*/-1, /*size=*/1, /*checkoverflow=*/false);
      },
      "Bogus memory allocation size");
}

TEST_F(GmallocnTest_12, NonPositiveSizeAbortsAndPrintsError_12) {
  ASSERT_DEATH(
      {
        (void)gmallocn(/*count=*/1, /*size=*/0, /*checkoverflow=*/false);
      },
      "Bogus memory allocation size");
}
#endif  // GTEST_HAS_DEATH_TEST

TEST_F(GmallocnTest_12, NegativeCountWithCheckoverflowTrueReturnsNullptrAndDoesNotCallGmalloc_12) {
  GM().return_ptr = FakePtr();

  testing::internal::CaptureStderr();
  void* p = gmallocn(/*count=*/-5, /*size=*/1, /*checkoverflow=*/true);
  std::string err = testing::internal::GetCapturedStderr();

  EXPECT_EQ(p, nullptr);
  EXPECT_NE(err.find("Bogus memory allocation size"), std::string::npos);

  EXPECT_EQ(GM().call_count, 0);
}

TEST_F(GmallocnTest_12, NonPositiveSizeWithCheckoverflowTrueReturnsNullptrAndDoesNotCallGmalloc_12) {
  GM().return_ptr = FakePtr();

  testing::internal::CaptureStderr();
  void* p = gmallocn(/*count=*/5, /*size=*/-1, /*checkoverflow=*/true);
  std::string err = testing::internal::GetCapturedStderr();

  EXPECT_EQ(p, nullptr);
  EXPECT_NE(err.find("Bogus memory allocation size"), std::string::npos);

  EXPECT_EQ(GM().call_count, 0);
}

TEST_F(GmallocnTest_12, WhenCheckedMultiplySucceedsBytesPassedToGmallocAreExactlyWhatCheckedMultiplyWrote_12) {
  // Boundary-ish: verify byte value plumbing is observable.
  CM().should_report_overflow = false;
  CM().product_value = 1;  // minimal positive bytes
  GM().return_ptr = FakePtr();

  void* p = gmallocn(/*count=*/1, /*size=*/1, /*checkoverflow=*/false);

  EXPECT_EQ(p, FakePtr());
  EXPECT_EQ(CM().call_count, 1);
  EXPECT_EQ(GM().call_count, 1);
  EXPECT_EQ(GM().last_bytes, 1);
}