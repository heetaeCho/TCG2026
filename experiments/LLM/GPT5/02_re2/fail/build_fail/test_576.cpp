// File: nfa_interface_test_576.cc
#include <gtest/gtest.h>
#include <type_traits>
#include <utility>

#include "re2/nfa.cc"  // Using the provided partial implementation as the interface source.

// Forward declarations or lightweight includes used in signatures.
#include "absl/strings/string_view.h"

namespace {

using re2::NFA;

// Helper alias for SFINAE checks without instantiation or linking.
template <typename T>
using identity_t = T;

// ------------------------------------------------------------------
// Interface: Search signature
// ------------------------------------------------------------------

TEST(NFAInterfaceTest_576, HasSearchMethodSignature_576) {
  // Verify the Search method exists with the expected signature (returning bool).
  using SearchSig = bool (NFA::*)(absl::string_view, absl::string_view,
                                  bool, bool, absl::string_view*, int);
  // &NFA::Search is not ODR-used here; we only check it's a member with this type.
  SearchSig ptr = &NFA::Search;
  (void)ptr;  // silence unused warning
  SUCCEED();
}

TEST(NFAInterfaceTest_576, SearchIsInvocableInUnevaluatedContext_576) {
  // Check the expression type in an unevaluated context matches bool.
  using std::declval;
  using Ret = decltype(
      declval<NFA&>().Search(
          declval<absl::string_view>(),
          declval<absl::string_view>(),
          declval<bool>(),
          declval<bool>(),
          declval<absl::string_view*>(),
          declval<int>()));
  static_assert(std::is_same<Ret, bool>::value, "Search must return bool");
  SUCCEED();
}

// ------------------------------------------------------------------
// Interface: Object semantics (copy/assign/delete)
// ------------------------------------------------------------------

TEST(NFAInterfaceTest_576, IsDestructible_576) {
  static_assert(std::is_destructible<NFA>::value, "NFA must be destructible");
  SUCCEED();
}

TEST(NFAInterfaceTest_576, NotCopyConstructible_576) {
  static_assert(!std::is_copy_constructible<NFA>::value,
                "NFA copy constructor should be deleted");
  SUCCEED();
}

TEST(NFAInterfaceTest_576, NotCopyAssignable_576) {
  static_assert(!std::is_copy_assignable<NFA>::value,
                "NFA copy assignment should be deleted");
  SUCCEED();
}

// ------------------------------------------------------------------
// Interface: Nested types and observable members
// ------------------------------------------------------------------

TEST(NFAInterfaceTest_576, ThreadHasCapturePointer_576) {
  // Validate presence and type of NFA::Thread::capture.
  using CaptureT = decltype(std::declval<NFA::Thread>().capture);
  static_assert(std::is_same<CaptureT, const char**>::value,
                "NFA::Thread::capture must be a const char**");
  SUCCEED();
}

}  // namespace
