// File: ./TestProjects/re2/util/pcre_partialmatchfunctor_test.cc

#include "gtest/gtest.h"
#include "TestProjects/re2/util/pcre.h"

using re2::PCRE;

class PartialMatchFunctorTest_190 : public ::testing::Test {
protected:
  // Helper to call the functor with up to 16 Args.
  template <typename... Args>
  bool Invoke(PCRE::PartialMatchFunctor& f,
              absl::string_view text,
              const PCRE& re,
              const Args&... args) {
    return f(text, re, args...);
  }
};

// [Normal] Basic success: two captures mapped into two outputs.
TEST_F(PartialMatchFunctorTest_190, SimpleMatch_FillsTwoCaptures_190) {
  PCRE re("(\\w+):(\\w+)");
  PCRE::PartialMatchFunctor f;

  std::string lhs, rhs;

  // Provide two destination Args, the rest default-constructed (ignored).
  bool ok = f(
      "user:alice",
      re,
      PCRE::Arg(&lhs),
      PCRE::Arg(&rhs),
      PCRE::Arg(), PCRE::Arg(), PCRE::Arg(), PCRE::Arg(),
      PCRE::Arg(), PCRE::Arg(), PCRE::Arg(), PCRE::Arg(),
      PCRE::Arg(), PCRE::Arg(), PCRE::Arg(), PCRE::Arg(),
      PCRE::Arg(), PCRE::Arg()
  );

  EXPECT_TRUE(ok);
  EXPECT_EQ(lhs, "user");
  EXPECT_EQ(rhs, "alice");
}

// [Exceptional/Observable] No match: returns false and leaves outputs unchanged.
TEST_F(PartialMatchFunctorTest_190, NoMatch_ReturnsFalse_190) {
  PCRE re("(\\w+):(\\w+)");
  PCRE::PartialMatchFunctor f;

  std::string lhs = "init", rhs = "init";

  bool ok = f(
      "user-alice",  // does not match "word:word"
      re,
      PCRE::Arg(&lhs),
      PCRE::Arg(&rhs),
      PCRE::Arg(), PCRE::Arg(), PCRE::Arg(), PCRE::Arg(),
      PCRE::Arg(), PCRE::Arg(), PCRE::Arg(), PCRE::Arg(),
      PCRE::Arg(), PCRE::Arg(), PCRE::Arg(), PCRE::Arg(),
      PCRE::Arg(), PCRE::Arg()
  );

  EXPECT_FALSE(ok);
  // We only assert there is no successful parse; we do not rely on internal
  // behavior to clear or modify outputs on failure.
  EXPECT_EQ(lhs, "init");
  EXPECT_EQ(rhs, "init");
}

// [Boundary] More Args than captures: extra Args should be safely ignored.
TEST_F(PartialMatchFunctorTest_190, IgnoresExtraArgsBeyondCaptures_190) {
  PCRE re("(\\w+):(\\w+)");
  PCRE::PartialMatchFunctor f;

  std::string a1, a2;
  // Prepare a bunch of extras that should not be written.
  std::string extra[14];
  for (auto& s : extra) s = "unset";

  bool ok = f(
      "k1:v2",
      re,
      PCRE::Arg(&a1),
      PCRE::Arg(&a2),
      // Supply 14 additional string pointers (total 16 Args)
      PCRE::Arg(&extra[0]),  PCRE::Arg(&extra[1]),
      PCRE::Arg(&extra[2]),  PCRE::Arg(&extra[3]),
      PCRE::Arg(&extra[4]),  PCRE::Arg(&extra[5]),
      PCRE::Arg(&extra[6]),  PCRE::Arg(&extra[7]),
      PCRE::Arg(&extra[8]),  PCRE::Arg(&extra[9]),
      PCRE::Arg(&extra[10]), PCRE::Arg(&extra[11]),
      PCRE::Arg(&extra[12]), PCRE::Arg(&extra[13])
  );

  EXPECT_TRUE(ok);
  EXPECT_EQ(a1, "k1");
  EXPECT_EQ(a2, "v2");

  // We don’t assert that the “extra” outputs change; we only verify
  // observable success on the requested captures.
  for (const auto& s : extra) {
    EXPECT_EQ(s, "unset");
  }
}

// [Boundary] Handles many (≤16) captures: first 10 captures extracted.
TEST_F(PartialMatchFunctorTest_190, HandlesUpToTenCaptures_190) {
  // Ten single-character capture groups.
  PCRE re("(.)(.)(.)(.)(.)(.)(.)(.)(.)(.)");
  PCRE::PartialMatchFunctor f;

  std::string c1, c2, c3, c4, c5, c6, c7, c8, c9, c10;

  bool ok = f(
      "abcdefghij",
      re,
      PCRE::Arg(&c1), PCRE::Arg(&c2), PCRE::Arg(&c3), PCRE::Arg(&c4),
      PCRE::Arg(&c5), PCRE::Arg(&c6), PCRE::Arg(&c7), PCRE::Arg(&c8),
      PCRE::Arg(&c9), PCRE::Arg(&c10),
      // Fill the remaining up to 16 with defaults (ignored)
      PCRE::Arg(), PCRE::Arg(), PCRE::Arg(), PCRE::Arg(), PCRE::Arg(), PCRE::Arg()
  );

  EXPECT_TRUE(ok);
  EXPECT_EQ(c1,  "a");
  EXPECT_EQ(c2,  "b");
  EXPECT_EQ(c3,  "c");
  EXPECT_EQ(c4,  "d");
  EXPECT_EQ(c5,  "e");
  EXPECT_EQ(c6,  "f");
  EXPECT_EQ(c7,  "g");
  EXPECT_EQ(c8,  "h");
  EXPECT_EQ(c9,  "i");
  EXPECT_EQ(c10, "j");
}
