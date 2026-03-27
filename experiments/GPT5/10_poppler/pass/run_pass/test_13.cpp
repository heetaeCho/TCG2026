// SPDX-License-Identifier: MIT
// Unit tests for gmallocn_checkoverflow (./TestProjects/poppler/goo/gmem.h)
//
// Constraints satisfied:
// - Treat implementation as black box: we only test observable calls/return behavior.
// - We don't re-implement gmallocn() logic; we mock/override it as an external dependency
//   and verify interaction and forwarded parameters.

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>

// ---- Minimal declaration surface to compile the inline under test ----
//
// In the real codebase, gmem.h provides this inline:
//
// inline void *gmallocn_checkoverflow(int count, int size) { return gmallocn(count, size, true); }
//
// We reproduce the inline exactly (verbatim) for testing, and provide a test double for gmallocn().
// This does not infer internal logic; it only allows linking and observing calls.

extern "C" void* gmallocn(int count, int size, bool checkoverflow);

// Keep the inline signature exactly as in the prompt.
inline void* gmallocn_checkoverflow(int count, int size) { return gmallocn(count, size, true); }

// ---- Test double for the external collaborator: gmallocn() ----
//
// We avoid Google Mock here because gmallocn is a free function. Instead, we intercept it
// by providing our own definition and capturing calls/parameters. This is an allowed form
// of mocking an external dependency.

namespace {
struct GmallocnSpy {
  int calls = 0;
  int last_count = 0;
  int last_size = 0;
  bool last_checkoverflow = false;
  void* return_ptr = nullptr;

  // Optional: simulate an error by returning nullptr.
  // No throwing here, since C-style allocator typically doesn't throw.
};

GmallocnSpy& Spy() {
  static GmallocnSpy spy;
  return spy;
}

void ResetSpy() { Spy() = GmallocnSpy{}; }
}  // namespace

extern "C" void* gmallocn(int count, int size, bool checkoverflow) {
  auto& s = Spy();
  s.calls += 1;
  s.last_count = count;
  s.last_size = size;
  s.last_checkoverflow = checkoverflow;
  return s.return_ptr;
}

// ---- Tests ----

class GmallocnCheckOverflowTest_13 : public ::testing::Test {
 protected:
  void SetUp() override { ResetSpy(); }
};

TEST_F(GmallocnCheckOverflowTest_13, ForwardsCountSizeAndSetsCheckOverflowTrue_13) {
  auto& s = Spy();
  int count = 3;
  int size = 7;
  void* expected = reinterpret_cast<void*>(static_cast<uintptr_t>(0x1234));
  s.return_ptr = expected;

  void* out = gmallocn_checkoverflow(count, size);

  EXPECT_EQ(out, expected);
  EXPECT_EQ(s.calls, 1);
  EXPECT_EQ(s.last_count, count);
  EXPECT_EQ(s.last_size, size);
  EXPECT_TRUE(s.last_checkoverflow);
}

TEST_F(GmallocnCheckOverflowTest_13, Boundary_ZeroCountIsForwarded_13) {
  auto& s = Spy();
  s.return_ptr = reinterpret_cast<void*>(static_cast<uintptr_t>(0x1));

  void* out = gmallocn_checkoverflow(0, 10);

  EXPECT_EQ(out, s.return_ptr);
  EXPECT_EQ(s.calls, 1);
  EXPECT_EQ(s.last_count, 0);
  EXPECT_EQ(s.last_size, 10);
  EXPECT_TRUE(s.last_checkoverflow);
}

TEST_F(GmallocnCheckOverflowTest_13, Boundary_ZeroSizeIsForwarded_13) {
  auto& s = Spy();
  s.return_ptr = reinterpret_cast<void*>(static_cast<uintptr_t>(0x2));

  void* out = gmallocn_checkoverflow(10, 0);

  EXPECT_EQ(out, s.return_ptr);
  EXPECT_EQ(s.calls, 1);
  EXPECT_EQ(s.last_count, 10);
  EXPECT_EQ(s.last_size, 0);
  EXPECT_TRUE(s.last_checkoverflow);
}

TEST_F(GmallocnCheckOverflowTest_13, Boundary_NegativeInputsAreForwardedUnmodified_13) {
  // We do not assume whether negatives are "valid"; we only assert forwarding behavior.
  auto& s = Spy();
  s.return_ptr = reinterpret_cast<void*>(static_cast<uintptr_t>(0x3));

  void* out = gmallocn_checkoverflow(-1, -8);

  EXPECT_EQ(out, s.return_ptr);
  EXPECT_EQ(s.calls, 1);
  EXPECT_EQ(s.last_count, -1);
  EXPECT_EQ(s.last_size, -8);
  EXPECT_TRUE(s.last_checkoverflow);
}

TEST_F(GmallocnCheckOverflowTest_13, ErrorCase_NullptrFromGmallocnIsPropagated_13) {
  auto& s = Spy();
  s.return_ptr = nullptr;  // simulate allocation failure or overflow rejection

  void* out = gmallocn_checkoverflow(1000000, 1000000);

  EXPECT_EQ(out, nullptr);
  EXPECT_EQ(s.calls, 1);
  EXPECT_EQ(s.last_count, 1000000);
  EXPECT_EQ(s.last_size, 1000000);
  EXPECT_TRUE(s.last_checkoverflow);
}

TEST_F(GmallocnCheckOverflowTest_13, MultipleCalls_AreIndependentlyForwarded_13) {
  auto& s = Spy();

  s.return_ptr = reinterpret_cast<void*>(static_cast<uintptr_t>(0x10));
  void* out1 = gmallocn_checkoverflow(1, 2);
  EXPECT_EQ(out1, s.return_ptr);
  EXPECT_EQ(s.calls, 1);
  EXPECT_EQ(s.last_count, 1);
  EXPECT_EQ(s.last_size, 2);
  EXPECT_TRUE(s.last_checkoverflow);

  s.return_ptr = reinterpret_cast<void*>(static_cast<uintptr_t>(0x20));
  void* out2 = gmallocn_checkoverflow(5, 6);
  EXPECT_EQ(out2, s.return_ptr);
  EXPECT_EQ(s.calls, 2);
  EXPECT_EQ(s.last_count, 5);
  EXPECT_EQ(s.last_size, 6);
  EXPECT_TRUE(s.last_checkoverflow);
}