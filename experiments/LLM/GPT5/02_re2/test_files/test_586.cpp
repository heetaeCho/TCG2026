// File: pcre_constructor_tests_586.cc
#include <gtest/gtest.h>
#include <type_traits>
#include <string>

#include "util/pcre.h"  // adjust include path if needed

using re2::PCRE;

//
// Compile-time interface tests (do not touch runtime behavior or internals)
//

TEST(PCRE_Interface_586, IsNotCopyConstructible_586) {
  static_assert(!std::is_copy_constructible<PCRE>::value,
                "PCRE should not be copy-constructible per deleted copy ctor");
  SUCCEED(); // keeps the test visible to the framework
}

TEST(PCRE_Interface_586, IsNotCopyAssignable_586) {
  static_assert(!std::is_copy_assignable<PCRE>::value,
                "PCRE should not be copy-assignable per deleted copy assignment");
  SUCCEED();
}

TEST(PCRE_Interface_586, IsMoveConstructible_586) {
  // Move is not explicitly deleted; ensure it is available.
  static_assert(std::is_move_constructible<PCRE>::value,
                "PCRE should be move-constructible by default");
  SUCCEED();
}

TEST(PCRE_Interface_586, IsMoveAssignable_586) {
  static_assert(std::is_move_assignable<PCRE>::value,
                "PCRE should be move-assignable by default");
  SUCCEED();
}

//
// Runtime constructor tests (only exercise the defined ctor: PCRE(const char*))
//

TEST(PCRE_Constructor_586, ConstructWithSimplePattern_NoThrow_586) {
  EXPECT_NO_THROW({
    PCRE re("abc");
    (void)re;
  });
}

TEST(PCRE_Constructor_586, ConstructWithEmptyPattern_NoThrow_586) {
  EXPECT_NO_THROW({
    PCRE re("");
    (void)re;
  });
}

TEST(PCRE_Constructor_586, ConstructWithLongPattern_NoThrow_586) {
  // A longer but still ordinary literal; exact semantics are not asserted.
  std::string long_pat(1024, 'x');  // 1KB of 'x'
  EXPECT_NO_THROW({
    PCRE re(long_pat.c_str());
    (void)re;
  });
}

// Note: We intentionally do NOT test other constructors or methods declared
// in the header because their definitions are not provided in the partial
// implementation and would cause link-time failures. We also avoid testing
// any internal state or behavior beyond successful construction.
