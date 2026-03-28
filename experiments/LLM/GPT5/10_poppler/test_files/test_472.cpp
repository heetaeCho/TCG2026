// GfxIndexedColorSpace_getLookup_472_test.cpp
#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

#include "GfxState.h"

// NOTE:
// The provided visible interface is only:
//   unsigned char *GfxIndexedColorSpace::getLookup()
// No public constructors / setters are provided in the prompt snippet, so we cannot
// (and must not) reach into private state or fabricate instances.
// These tests therefore verify *observable interface properties* (signature / constness).

class GfxIndexedColorSpaceTest_472 : public ::testing::Test {};

namespace {

// SFINAE helper: can we call T::getLookup() on an lvalue of type U?
template <typename U, typename = void>
struct HasGetLookupOnLvalue : std::false_type {};
template <typename U>
struct HasGetLookupOnLvalue<U, std::void_t<decltype(std::declval<U &>().getLookup())>>
    : std::true_type {};

// SFINAE helper: can we call T::getLookup() on a const lvalue of type U?
template <typename U, typename = void>
struct HasGetLookupOnConstLvalue : std::false_type {};
template <typename U>
struct HasGetLookupOnConstLvalue<
    U, std::void_t<decltype(std::declval<const U &>().getLookup())>> : std::true_type {};

}  // namespace

TEST_F(GfxIndexedColorSpaceTest_472, GetLookup_ReturnTypeIsUnsignedCharPtr_472) {
  // Compile-time contract: return type is exactly unsigned char*.
  static_assert(
      std::is_same_v<decltype(std::declval<GfxIndexedColorSpace &>().getLookup()),
                     unsigned char *>,
      "GfxIndexedColorSpace::getLookup() must return unsigned char*");
  SUCCEED();
}

TEST_F(GfxIndexedColorSpaceTest_472, GetLookup_IsCallableOnNonConstLvalue_472) {
  // Compile-time contract: callable on non-const lvalue.
  static_assert(HasGetLookupOnLvalue<GfxIndexedColorSpace>::value,
                "getLookup() should be callable on non-const lvalues");
  SUCCEED();
}

TEST_F(GfxIndexedColorSpaceTest_472, GetLookup_IsNotCallableOnConstLvalue_472) {
  // With the provided partial code, getLookup is non-const:
  //   unsigned char *getLookup() { ... }
  // Verify (at compile time) that it cannot be invoked on a const object.
  static_assert(!HasGetLookupOnConstLvalue<GfxIndexedColorSpace>::value,
                "getLookup() is expected to be non-const and not callable on const objects");
  SUCCEED();
}