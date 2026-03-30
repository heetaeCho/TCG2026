// File: pcre_walker_shortvisit_test.cc

#include <gtest/gtest.h>

// Forward-declare re2::Regexp so the included .cc can reference it without needing full headers.
namespace re2 { class Regexp; }

// Include the implementation unit to access the PCREWalker definition for testing.
// (Acceptable in unit tests when there is no public header available.)
#include "TestProjects/re2/re2/mimics_pcre.cc"

namespace {

// Test suite for PCREWalker::ShortVisit behavior.
// We avoid any assumptions about logging or internal state.
// We only assert the observable return value and that a nullptr Regexp* is tolerated.

TEST(PCREWalkerTest_218, ShortVisit_ReturnsTrueWhenInputTrue_218) {
  re2::PCREWalker walker;
  // Passing nullptr for Regexp* since the method contract does not require dereferencing it.
  bool out = walker.ShortVisit(/*re=*/nullptr, /*a=*/true);
  EXPECT_TRUE(out);
}

TEST(PCREWalkerTest_218, ShortVisit_ReturnsFalseWhenInputFalse_218) {
  re2::PCREWalker walker;
  bool out = walker.ShortVisit(/*re=*/nullptr, /*a=*/false);
  EXPECT_FALSE(out);
}

TEST(PCREWalkerTest_218, ShortVisit_IgnoresRegexpPointerNullIsOkay_218) {
  re2::PCREWalker walker;
  // Verify both boolean paths while emphasizing that a null Regexp* is acceptable.
  EXPECT_TRUE(walker.ShortVisit(/*re=*/nullptr, /*a=*/true));
  EXPECT_FALSE(walker.ShortVisit(/*re=*/nullptr, /*a=*/false));
}

}  // namespace
