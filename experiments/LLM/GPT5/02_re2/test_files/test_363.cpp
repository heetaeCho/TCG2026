// File: capture_names_walker_take_map_test_363.cc

#include <gtest/gtest.h>
#include <map>
#include <string>

// Rely on the public interface; no peeking at internals.
#include "re2/regexp.h"

using re2::CaptureNamesWalker;

// Test fixture for clarity and reuse.
class CaptureNamesWalkerTest_363 : public ::testing::Test {
protected:
  CaptureNamesWalker walker_;
};

// [Normal] Constructing the object and calling TakeMap once should return nullptr
// when no work has been done to populate any internal map.
TEST_F(CaptureNamesWalkerTest_363, InitialTakeMapIsNull_363) {
  std::map<int, std::string>* m = walker_.TakeMap();
  EXPECT_EQ(m, nullptr);
}

// [Boundary] Calling TakeMap multiple times should be safe and idempotent,
// i.e., once the (possibly null) pointer is taken, subsequent calls return nullptr.
TEST_F(CaptureNamesWalkerTest_363, TakeMapIsIdempotentOnRepeatedCalls_363) {
  std::map<int, std::string>* first = walker_.TakeMap();
  std::map<int, std::string>* second = walker_.TakeMap();
  EXPECT_EQ(first, nullptr);
  EXPECT_EQ(second, nullptr);
  EXPECT_EQ(first, second);  // both should be nullptr
}

// [Robustness] Ensure repeated calls to TakeMap (even many times) do not throw or crash.
// We don't assert internal state—only that observable behavior remains safe.
TEST_F(CaptureNamesWalkerTest_363, MultipleTakeMapCallsDoNotCrash_363) {
  for (int i = 0; i < 10; ++i) {
    std::map<int, std::string>* m = walker_.TakeMap();
    EXPECT_EQ(m, nullptr);
  }
}
