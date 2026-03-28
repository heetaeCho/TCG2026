// File: pcre_constructor_test_588.cc
#include <gtest/gtest.h>
#include <string>
#include <type_traits>

#include "TestProjects/re2/util/pcre.h"

namespace {

using re2::PCRE;

// A tiny fixture is kept for naming consistency & future extension.
class PCREConstructorTest_588 : public ::testing::Test {};

// ---------------------------------------------------------------
// Compile-time interface contracts (from header) — no internals.
// ---------------------------------------------------------------

TEST_F(PCREConstructorTest_588, NotCopyConstructible_588) {
  static_assert(!std::is_copy_constructible<PCRE>::value,
                "PCRE should not be copy-constructible per header (deleted copy ctor).");
}

TEST_F(PCREConstructorTest_588, NotCopyAssignable_588) {
  static_assert(!std::is_copy_assignable<PCRE>::value,
                "PCRE should not be copy-assignable per header (deleted operator=).");
}

TEST_F(PCREConstructorTest_588, ConstructibleFromStdString_588) {
  static_assert(std::is_constructible<PCRE, const std::string&>::value,
                "PCRE should be constructible from const std::string& per header.");
}

// ---------------------------------------------
// Runtime smoke tests for the visible ctor.
// ---------------------------------------------

TEST_F(PCREConstructorTest_588, ConstructWithNormalPattern_NoThrow_588) {
  std::string pattern = "abc.*(def)?";
  EXPECT_NO_THROW({
    PCRE re(pattern);
    (void)re;  // silence unused warning
  });
}

TEST_F(PCREConstructorTest_588, ConstructWithEmptyPattern_NoThrow_588) {
  std::string pattern = "";
  EXPECT_NO_THROW({
    PCRE re(pattern);
    (void)re;
  });
}

TEST_F(PCREConstructorTest_588, ConstructWithLongPattern_NoThrow_588) {
  std::string pattern(10000, 'x');  // very long but valid string input
  EXPECT_NO_THROW({
    PCRE re(pattern);
    (void)re;
  });
}

TEST_F(PCREConstructorTest_588, ConstructWithUTF8Pattern_NoThrow_588) {
  // Simple UTF-8 content; we don't assume UTF-8 mode behavior, only that construction succeeds.
  std::string pattern = u8"한글과🙂이 섞인 패턴.*";
  EXPECT_NO_THROW({
    PCRE re(pattern);
    (void)re;
  });
}

}  // namespace
