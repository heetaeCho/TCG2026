// File: FilterStream_getNextStream_tests_144.cpp
#include <gtest/gtest.h>

#include "poppler/Stream.h"

// The implementation is treated as a black box.
// We only verify observable behavior via the public interface.

namespace {

class FilterStreamTest_144 : public ::testing::Test {
protected:
  // Create a FilterStream but intentionally never destroy it, to avoid making
  // assumptions about ownership/lifetime semantics of the wrapped Stream*.
  static FilterStream* MakeLeakyFilterStream(Stream* next) {
    return new FilterStream(next);
  }
};

TEST_F(FilterStreamTest_144, GetNextStreamReturnsWrappedPointer_144) {
  // Use an arbitrary non-null pointer value without dereferencing it.
  // This avoids depending on any concrete Stream subclass.
  auto* wrapped = reinterpret_cast<Stream*>(static_cast<uintptr_t>(0x1));

  FilterStream* fs = MakeLeakyFilterStream(wrapped);

  EXPECT_EQ(fs->getNextStream(), wrapped);
}

TEST_F(FilterStreamTest_144, GetNextStreamCallableOnConstObject_144) {
  auto* wrapped = reinterpret_cast<Stream*>(static_cast<uintptr_t>(0x2));

  FilterStream* fs = MakeLeakyFilterStream(wrapped);
  const FilterStream* cfs = fs;

  EXPECT_EQ(cfs->getNextStream(), wrapped);
}

TEST_F(FilterStreamTest_144, GetNextStreamStableAcrossMultipleCalls_144) {
  auto* wrapped = reinterpret_cast<Stream*>(static_cast<uintptr_t>(0x3));

  FilterStream* fs = MakeLeakyFilterStream(wrapped);

  Stream* first = fs->getNextStream();
  Stream* second = fs->getNextStream();
  Stream* third = fs->getNextStream();

  EXPECT_EQ(first, wrapped);
  EXPECT_EQ(second, wrapped);
  EXPECT_EQ(third, wrapped);
  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);
}

}  // namespace