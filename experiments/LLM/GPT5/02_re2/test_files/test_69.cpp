// File: pod_array_deleter_test_69.cc
#include <gtest/gtest.h>
#include <memory>
#include <allocator>
#include "./TestProjects/re2/re2/pod_array.h"

// We treat PODArray/PODArray::Deleter as a black box, relying only on
// observable/public interface: public len_, constructors, and operator().

namespace {

using namespace re2;

class PODArrayDeleterTest_69 : public ::testing::Test {};

// [Normal] Default constructor initializes len_ to 0.
TEST_F(PODArrayDeleterTest_69, DefaultCtor_SetsLenZero_69) {
  // The interface exposes len_ as public; checking its value is allowed.
  PODArray::Deleter d;
  EXPECT_EQ(d.len_, 0);
}

// [Normal] Explicit constructor stores provided length.
TEST_F(PODArrayDeleterTest_69, ExplicitCtor_SetsProvidedLength_69) {
  PODArray::Deleter d(5);
  EXPECT_EQ(d.len_, 5);
}

// [Normal] operator() deallocates memory (for int) without throwing when length matches.
// We purposefully avoid UB by allocating exactly len_ elements and passing the same len_.
TEST_F(PODArrayDeleterTest_69, Call_DeallocatesIntPointer_NoThrow_69) {
  constexpr int kN = 3;
  std::allocator<int> alloc;
  int* ptr = alloc.allocate(kN);

  PODArray::Deleter d(kN);
  EXPECT_NO_THROW(d(ptr));
}

// [Boundary] Minimal positive length (1) is supported, and operator() is const-callable.
TEST_F(PODArrayDeleterTest_69, Call_WithLenOne_AndConstCallable_69) {
  constexpr int kN = 1;
  std::allocator<double> alloc;
  double* ptr = alloc.allocate(kN);

  const PODArray::Deleter d(kN);  // const object to verify const-callability
  EXPECT_NO_THROW(d(ptr));
}

// [Normal] Using a larger length works when we allocate the same number of elements.
// This also lightly exercises a different element type to avoid coupling to a single T.
TEST_F(PODArrayDeleterTest_69, Call_DeallocatesCharPointer_NoThrow_69) {
  constexpr int kN = 8;
  std::allocator<char> alloc;
  char* ptr = alloc.allocate(kN);

  PODArray::Deleter d(kN);
  EXPECT_NO_THROW(d(ptr));
}

}  // namespace
