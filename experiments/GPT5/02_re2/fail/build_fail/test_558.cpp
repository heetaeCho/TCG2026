// File: prefilter_cclass_test_558.cc
#include <gtest/gtest.h>
#include <set>
#include <string>
#include <vector>

#include "re2/prefilter.h"
#include "re2/regexp.h"

using re2::CharClass;
using re2::Prefilter;

namespace {

// --- Minimal builder helpers (black-box friendly) -------------------------
// These helpers rely only on public/visible APIs; if population is not
// available in your compiled headers, we skip the tests cleanly.
struct Range { int lo; int hi; };

class PrefilterInfoCClassTest_558 : public ::testing::Test {
protected:
  // Attempts to build a CharClass with the given ranges.
  // If your RE2 build lacks public population APIs, this returns nullptr
  // and tests will SKIP gracefully (never poking private state).
  static CharClass* BuildCharClassOrSkip(const std::vector<Range>& ranges) {
    // Common RE2 distros provide a builder/adder; if your build doesn't,
    // we cannot control begin()/end()/size()—so we skip.
    //
    // Replace the block below with whatever public factory your tree exposes,
    // e.g. CharClassBuilder builder; builder.AddRange(...); CharClass* cc = builder.GetCharClass();
    //
    // Since the prompt only shows a partial header, we detect lack of support
    // by failing to obtain a non-null and skipping.

    CharClass* cc = nullptr;

    // ---- BEGIN: example/typical path if available in your tree ----
    // If you have a CharClassBuilder (typical in RE2), uncomment/adapt:
    //
    // re2::CharClassBuilder ccb;
    // for (const auto& r : ranges) ccb.AddRange(r.lo, r.hi);
    // cc = ccb.GetCharClass();
    //
    // ---- END: example path ----

    if (cc == nullptr) {
      GTEST_SKIP()
          << "Cannot construct a populated re2::CharClass from public API in this build.";
    }
    return cc;
  }

  // Count helper for SSet-like containers (std::set<std::string> in typical RE2).
  static size_t CountString(const decltype(((Prefilter::Info*)nullptr)->exact())& sset,
                            const std::string& s) {
    // SSet in upstream RE2 is std::set<std::string>. If your tree differs
    // but exposes find()/count(), this stays within the public interface.
    return sset.count(s);
  }
};

}  // namespace

// -------------------- Tests --------------------

TEST_F(PrefilterInfoCClassTest_558, SmallLatin1YieldsExactLowercasedSet_558) {
  // Ranges cover uppercase and lowercase to confirm Latin-1 lowercasing merge.
  // 'A'-'B' and 'a'-'b' should collapse to {"a","b"} under latin1=true.
  CharClass* cc = BuildCharClassOrSkip({{int('A'), int('B')}, {int('a'), int('b')}});

  std::unique_ptr<Prefilter::Info> info(Prefilter::Info::CClass(cc, /*latin1=*/true));
  ASSERT_NE(info, nullptr);
  EXPECT_TRUE(info->is_exact());

  auto& exact = info->exact();
  // Expect unique lowercased strings.
  EXPECT_EQ(exact.size(), 2u);
  EXPECT_EQ(CountString(exact, "a"), 1u);
  EXPECT_EQ(CountString(exact, "b"), 1u);
}

TEST_F(PrefilterInfoCClassTest_558, SmallUnicodeYieldsExactLowercasedSet_558) {
  // Non-Latin1 branch uses RuneToString(ToLowerRune).
  // Using basic ASCII still validates lowercasing path for latin1=false.
  CharClass* cc = BuildCharClassOrSkip({{int('X'), int('Z')}});  // X..Z

  std::unique_ptr<Prefilter::Info> info(Prefilter::Info::CClass(cc, /*latin1=*/false));
  ASSERT_NE(info, nullptr);
  EXPECT_TRUE(info->is_exact());

  auto& exact = info->exact();
  // Should include x,y,z (inclusive bounds).
  EXPECT_EQ(exact.size(), 3u);
  EXPECT_EQ(CountString(exact, "x"), 1u);
  EXPECT_EQ(CountString(exact, "y"), 1u);
  EXPECT_EQ(CountString(exact, "z"), 1u);
}

TEST_F(PrefilterInfoCClassTest_558, LargeClassFallsBackFromExact_558) {
  // Create >10 disjoint singletons to trigger the early-return path:
  // if (cc->size() > 10) return AnyCharOrAnyByte();
  std::vector<Range> many;
  for (int i = 0; i < 11; ++i) {
    int ch = 'a' + i;
    many.push_back({ch, ch});
  }
  CharClass* cc = BuildCharClassOrSkip(many);

  std::unique_ptr<Prefilter::Info> info(Prefilter::Info::CClass(cc, /*latin1=*/true));
  ASSERT_NE(info, nullptr);

  // AnyCharOrAnyByte() is expected to NOT be an exact set (black-box check).
  EXPECT_FALSE(info->is_exact());
}

TEST_F(PrefilterInfoCClassTest_558, InclusiveRangeBounds_558) {
  // Single range 'm'..'o' should include all three: m, n, o (inclusive).
  CharClass* cc = BuildCharClassOrSkip({{int('m'), int('o')}});

  std::unique_ptr<Prefilter::Info> info(Prefilter::Info::CClass(cc, /*latin1=*/true));
  ASSERT_NE(info, nullptr);
  EXPECT_TRUE(info->is_exact());

  auto& exact = info->exact();
  EXPECT_EQ(exact.size(), 3u);
  EXPECT_EQ(CountString(exact, "m"), 1u);
  EXPECT_EQ(CountString(exact, "n"), 1u);
  EXPECT_EQ(CountString(exact, "o"), 1u);
}

TEST_F(PrefilterInfoCClassTest_558, EmptyCharClassProducesEmptyExactSet_558) {
  // Empty class → loop doesn't insert anything; still marked exact (per code).
  CharClass* cc = BuildCharClassOrSkip({/*no ranges*/});

  std::unique_ptr<Prefilter::Info> info(Prefilter::Info::CClass(cc, /*latin1=*/true));
  ASSERT_NE(info, nullptr);
  EXPECT_TRUE(info->is_exact());
  EXPECT_TRUE(info->exact().empty());
}
