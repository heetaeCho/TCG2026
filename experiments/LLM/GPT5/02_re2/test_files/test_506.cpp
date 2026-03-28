// File: factor_alternation_round1_test_506.cc
#include <gtest/gtest.h>
#include <vector>
#include <string>
#include "re2/regexp.h"

// Minimal declarations to call the code under test & access observable results.
// Matches RE2's parse.cc definitions (public surface only).
namespace re2 {

// Splice as documented (needed so std::vector<Splice> is a complete type).
struct Splice {
  Regexp* prefix;
  Regexp** sub;
  int nsub;
  int nsuffix;
  inline Splice(Regexp* p, Regexp** s, int n)
      : prefix(p), sub(s), nsub(n), nsuffix(0) {}
};

// Round1 entry point we are testing.
class FactorAlternationImpl {
 public:
  static void Round1(Regexp** sub, int nsub, Regexp::ParseFlags flags,
                     std::vector<Splice>* splices);
};

}  // namespace re2

using re2::Regexp;
using re2::FactorAlternationImpl;
using re2::Splice;

namespace {

// Helper: parse a literal pattern into a Regexp*, asserting success.
static Regexp* ParseOrDie(const std::string& s) {
  re2::RegexpStatus status;
  Regexp* r = Regexp::Parse(s, Regexp::NoParseFlags, &status);
  EXPECT_NE(r, nullptr);
  return r;
}

// Helper: Decref all subs and splice prefixes to avoid leaks in tests.
static void Cleanup(std::vector<Regexp*>& subs, const std::vector<Splice>& splices) {
  for (const auto& sp : splices) {
    if (sp.prefix) sp.prefix->Decref();
  }
  for (auto* r : subs) {
    if (r) r->Decref();
  }
}

}  // namespace

// ------------------------------ Tests ------------------------------

TEST(FactorAlternationImplTest_506, Round1_FactorsContiguousCommonPrefix_506) {
  // Given: contiguous alternatives with a common "aba" prefix.
  std::vector<Regexp*> subs = {
      ParseOrDie("abacus"),
      ParseOrDie("abalone"),
      ParseOrDie("zebra"),
  };

  std::vector<Splice> splices;
  FactorAlternationImpl::Round1(subs.data(), static_cast<int>(subs.size()),
                                Regexp::NoParseFlags, &splices);

  // Then: one splice created for the first two entries.
  ASSERT_EQ(splices.size(), 1u);
  const Splice& sp = splices[0];

  // Splice describes the factored run.
  ASSERT_NE(sp.prefix, nullptr);
  EXPECT_EQ(sp.prefix->ToString(), "aba");
  EXPECT_EQ(sp.nsub, 2);
  EXPECT_EQ(sp.sub, &subs[0]) << "Splice should point at the start of the run";

  // Subs in the run have had the common prefix removed (observable via ToString()).
  EXPECT_EQ(subs[0]->ToString(), "cus");
  EXPECT_EQ(subs[1]->ToString(), "lone");

  // Non-participating alternative unchanged.
  EXPECT_EQ(subs[2]->ToString(), "zebra");

  Cleanup(subs, splices);
}

TEST(FactorAlternationImplTest_506, Round1_NoCommonPrefix_NoSplicesNoMutation_506) {
  std::vector<Regexp*> subs = {
      ParseOrDie("dog"),
      ParseOrDie("cat"),
  };
  const std::string before0 = subs[0]->ToString();
  const std::string before1 = subs[1]->ToString();

  std::vector<Splice> splices;
  FactorAlternationImpl::Round1(subs.data(), static_cast<int>(subs.size()),
                                Regexp::NoParseFlags, &splices);

  EXPECT_TRUE(splices.empty());
  EXPECT_EQ(subs[0]->ToString(), before0);
  EXPECT_EQ(subs[1]->ToString(), before1);

  Cleanup(subs, splices);
}

TEST(FactorAlternationImplTest_506, Round1_UTF8CommonPrefix_506) {
  // Unicode: "한글사" and "한글자" share the prefix "한글".
  std::vector<Regexp*> subs = {
      ParseOrDie("한글사"),
      ParseOrDie("한글자"),
  };

  std::vector<Splice> splices;
  FactorAlternationImpl::Round1(subs.data(), static_cast<int>(subs.size()),
                                Regexp::NoParseFlags, &splices);

  ASSERT_EQ(splices.size(), 1u);
  EXPECT_EQ(splices[0].prefix->ToString(), "한글");
  EXPECT_EQ(subs[0]->ToString(), "사");
  EXPECT_EQ(subs[1]->ToString(), "자");

  Cleanup(subs, splices);
}

TEST(FactorAlternationImplTest_506, Round1_OnlyContiguousRunsAreFactored_506) {
  // Only the contiguous "abacus|abalone" should be factored; "car" and "cat" remain separate.
  std::vector<Regexp*> subs = {
      ParseOrDie("car"),
      ParseOrDie("abacus"),
      ParseOrDie("abalone"),
      ParseOrDie("cat"),
  };
  const std::string before0 = subs[0]->ToString();
  const std::string before3 = subs[3]->ToString();

  std::vector<Splice> splices;
  FactorAlternationImpl::Round1(subs.data(), static_cast<int>(subs.size()),
                                Regexp::NoParseFlags, &splices);

  ASSERT_EQ(splices.size(), 1u);
  EXPECT_EQ(splices[0].prefix->ToString(), "aba");
  EXPECT_EQ(splices[0].nsub, 2);
  EXPECT_EQ(splices[0].sub, &subs[1]);

  // Only the run [1,2) is trimmed.
  EXPECT_EQ(subs[1]->ToString(), "cus");
  EXPECT_EQ(subs[2]->ToString(), "lone");

  // The non-contiguous entries are unchanged.
  EXPECT_EQ(subs[0]->ToString(), before0);
  EXPECT_EQ(subs[3]->ToString(), before3);

  Cleanup(subs, splices);
}

TEST(FactorAlternationImplTest_506, Round1_EmptyInput_NoCrashNoSplices_506) {
  std::vector<Regexp*> subs;
  std::vector<Splice> splices;

  // Should not crash and should not produce any splices.
  FactorAlternationImpl::Round1(nullptr, 0, Regexp::NoParseFlags, &splices);
  EXPECT_TRUE(splices.empty());

  Cleanup(subs, splices);
}

TEST(FactorAlternationImplTest_506, Round1_SingleRunePrefix_506) {
  std::vector<Regexp*> subs = {
      ParseOrDie("xa"),
      ParseOrDie("xb"),
  };

  std::vector<Splice> splices;
  FactorAlternationImpl::Round1(subs.data(), static_cast<int>(subs.size()),
                                Regexp::NoParseFlags, &splices);

  ASSERT_EQ(splices.size(), 1u);
  EXPECT_EQ(splices[0].prefix->ToString(), "x");
  EXPECT_EQ(subs[0]->ToString(), "a");
  EXPECT_EQ(subs[1]->ToString(), "b");

  Cleanup(subs, splices);
}
