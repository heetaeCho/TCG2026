// File: greallocn_checkoverflow_test_16.cpp
//
// Unit tests for:
//   inline void *greallocn_checkoverflow(void *p, int count, int size)
//     { return greallocn(p, count, size, true); }
//
// These tests treat greallocn_checkoverflow as a black box and verify only
// observable behavior through its interface: that it forwards parameters to
// greallocn, forces the overflow-check flag to true, and returns whatever
// greallocn returns.

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <mutex>

namespace {

// Simple capture of the external collaborator call (greallocn).
struct GreallocnCapture {
  std::mutex mu;
  int calls = 0;

  void* p = nullptr;
  int count = 0;
  int size = 0;
  bool checkOverflow = false;

  void* returnValue = nullptr;

  void Reset() {
    std::lock_guard<std::mutex> lock(mu);
    calls = 0;
    p = nullptr;
    count = 0;
    size = 0;
    checkOverflow = false;
    returnValue = nullptr;
  }

  void SetReturn(void* rv) {
    std::lock_guard<std::mutex> lock(mu);
    returnValue = rv;
  }

  void Record(void* in_p, int in_count, int in_size, bool in_checkOverflow) {
    std::lock_guard<std::mutex> lock(mu);
    ++calls;
    p = in_p;
    count = in_count;
    size = in_size;
    checkOverflow = in_checkOverflow;
  }
};

GreallocnCapture g_capture;

// Provide a test double for greallocn by macro-renaming it at include time.
// This avoids relying on any internal implementation details.
void* test_greallocn(void* p, int count, int size, bool checkOverflow) {
  g_capture.Record(p, count, size, checkOverflow);

  std::lock_guard<std::mutex> lock(g_capture.mu);
  return g_capture.returnValue;
}

}  // namespace

// Redirect calls inside gmem.h from greallocn(...) to test_greallocn(...).
#define greallocn test_greallocn
#include "goo/gmem.h"
#undef greallocn

namespace {

class GreallocnCheckOverflowTest_16 : public ::testing::Test {
 protected:
  void SetUp() override { g_capture.Reset(); }
};

TEST_F(GreallocnCheckOverflowTest_16, ForwardsArgumentsAndForcesCheckOverflowTrue_16) {
  int dummy = 0;
  void* inputPtr = &dummy;

  void* expectedReturn = reinterpret_cast<void*>(static_cast<uintptr_t>(0x1234));
  g_capture.SetReturn(expectedReturn);

  void* out = greallocn_checkoverflow(inputPtr, /*count=*/7, /*size=*/9);

  EXPECT_EQ(out, expectedReturn);

  std::lock_guard<std::mutex> lock(g_capture.mu);
  EXPECT_EQ(g_capture.calls, 1);
  EXPECT_EQ(g_capture.p, inputPtr);
  EXPECT_EQ(g_capture.count, 7);
  EXPECT_EQ(g_capture.size, 9);
  EXPECT_TRUE(g_capture.checkOverflow);
}

TEST_F(GreallocnCheckOverflowTest_16, AcceptsNullPointerAndStillForcesCheckOverflowTrue_16) {
  void* expectedReturn = reinterpret_cast<void*>(static_cast<uintptr_t>(0xBEEF));
  g_capture.SetReturn(expectedReturn);

  void* out = greallocn_checkoverflow(nullptr, /*count=*/1, /*size=*/1);

  EXPECT_EQ(out, expectedReturn);

  std::lock_guard<std::mutex> lock(g_capture.mu);
  EXPECT_EQ(g_capture.calls, 1);
  EXPECT_EQ(g_capture.p, nullptr);
  EXPECT_EQ(g_capture.count, 1);
  EXPECT_EQ(g_capture.size, 1);
  EXPECT_TRUE(g_capture.checkOverflow);
}

TEST_F(GreallocnCheckOverflowTest_16, BoundaryValuesZeroCountAndZeroSizeAreForwarded_16) {
  int dummy = 0;
  void* inputPtr = &dummy;

  void* expectedReturn = nullptr;  // Simulate an observable error/exceptional outcome via return.
  g_capture.SetReturn(expectedReturn);

  void* out = greallocn_checkoverflow(inputPtr, /*count=*/0, /*size=*/0);

  EXPECT_EQ(out, expectedReturn);

  std::lock_guard<std::mutex> lock(g_capture.mu);
  EXPECT_EQ(g_capture.calls, 1);
  EXPECT_EQ(g_capture.p, inputPtr);
  EXPECT_EQ(g_capture.count, 0);
  EXPECT_EQ(g_capture.size, 0);
  EXPECT_TRUE(g_capture.checkOverflow);
}

TEST_F(GreallocnCheckOverflowTest_16, NegativeValuesAreForwardedUnmodified_16) {
  int dummy = 0;
  void* inputPtr = &dummy;

  void* expectedReturn = reinterpret_cast<void*>(static_cast<uintptr_t>(0xCAFE));
  g_capture.SetReturn(expectedReturn);

  void* out = greallocn_checkoverflow(inputPtr, /*count=*/-3, /*size=*/-11);

  EXPECT_EQ(out, expectedReturn);

  std::lock_guard<std::mutex> lock(g_capture.mu);
  EXPECT_EQ(g_capture.calls, 1);
  EXPECT_EQ(g_capture.p, inputPtr);
  EXPECT_EQ(g_capture.count, -3);
  EXPECT_EQ(g_capture.size, -11);
  EXPECT_TRUE(g_capture.checkOverflow);
}

}  // namespace