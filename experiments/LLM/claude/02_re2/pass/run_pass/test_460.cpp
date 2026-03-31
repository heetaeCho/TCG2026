#include "gtest/gtest.h"
#include "re2/prefilter.h"
#include "re2/re2.h"

namespace re2 {

// Test basic construction with different Op values
TEST(PrefilterTest_460, ConstructWithNONE_460) {
  Prefilter pf(Prefilter::NONE);
  EXPECT_EQ(pf.op(), Prefilter::NONE);
}

TEST(PrefilterTest_460, ConstructWithAND_460) {
  Prefilter pf(Prefilter::AND);
  EXPECT_EQ(pf.op(), Prefilter::AND);
}

TEST(PrefilterTest_460, ConstructWithOR_460) {
  Prefilter pf(Prefilter::OR);
  EXPECT_EQ(pf.op(), Prefilter::OR);
}

TEST(PrefilterTest_460, ConstructWithATOM_460) {
  Prefilter pf(Prefilter::ATOM);
  EXPECT_EQ(pf.op(), Prefilter::ATOM);
}

TEST(PrefilterTest_460, ConstructWithALL_460) {
  Prefilter pf(Prefilter::ALL);
  EXPECT_EQ(pf.op(), Prefilter::ALL);
}

// Test atom() on a freshly constructed Prefilter
TEST(PrefilterTest_460, AtomDefaultEmpty_460) {
  Prefilter pf(Prefilter::ATOM);
  EXPECT_TRUE(pf.atom().empty());
}

// Test unique_id set and get
TEST(PrefilterTest_460, SetAndGetUniqueId_460) {
  Prefilter pf(Prefilter::NONE);
  pf.set_unique_id(42);
  EXPECT_EQ(pf.unique_id(), 42);
}

TEST(PrefilterTest_460, SetUniqueIdZero_460) {
  Prefilter pf(Prefilter::NONE);
  pf.set_unique_id(0);
  EXPECT_EQ(pf.unique_id(), 0);
}

TEST(PrefilterTest_460, SetUniqueIdNegative_460) {
  Prefilter pf(Prefilter::NONE);
  pf.set_unique_id(-1);
  EXPECT_EQ(pf.unique_id(), -1);
}

TEST(PrefilterTest_460, SetUniqueIdMultipleTimes_460) {
  Prefilter pf(Prefilter::NONE);
  pf.set_unique_id(10);
  EXPECT_EQ(pf.unique_id(), 10);
  pf.set_unique_id(20);
  EXPECT_EQ(pf.unique_id(), 20);
}

// Test subs() default value
TEST(PrefilterTest_460, SubsDefaultNull_460) {
  Prefilter pf(Prefilter::AND);
  // After construction, subs might be null or might be allocated.
  // We just test that calling subs() doesn't crash.
  // The result depends on implementation.
  (void)pf.subs();
}

// Test set_subs
TEST(PrefilterTest_460, SetSubsAndRetrieve_460) {
  Prefilter pf(Prefilter::AND);
  auto* subs = new std::vector<Prefilter*>();
  subs->push_back(new Prefilter(Prefilter::ATOM));
  pf.set_subs(subs);
  EXPECT_EQ(pf.subs(), subs);
  EXPECT_EQ(pf.subs()->size(), 1u);
}

// Test set_subs with nullptr
TEST(PrefilterTest_460, SetSubsNull_460) {
  Prefilter pf(Prefilter::AND);
  pf.set_subs(nullptr);
  EXPECT_EQ(pf.subs(), nullptr);
}

// Test FromRE2 with a simple literal pattern
TEST(PrefilterTest_460, FromRE2SimpleLiteral_460) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  // For a simple literal, we expect an ATOM
  EXPECT_EQ(pf->op(), Prefilter::ATOM);
  EXPECT_EQ(pf->atom(), "hello");
  delete pf;
}

// Test FromRE2 with alternation
TEST(PrefilterTest_460, FromRE2Alternation_460) {
  RE2 re("hello|world");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  // For alternation, we expect an OR of atoms
  // Just verify it doesn't crash and returns something valid
  std::string debug = pf->DebugString();
  EXPECT_FALSE(debug.empty());
  delete pf;
}

// Test FromRE2 with a pattern that matches everything
TEST(PrefilterTest_460, FromRE2MatchAll_460) {
  RE2 re(".*");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  // For .* there might be no useful prefilter, could be ALL or nullptr
  if (pf != nullptr) {
    EXPECT_EQ(pf->op(), Prefilter::ALL);
    delete pf;
  }
}

// Test FromRE2 with concatenation
TEST(PrefilterTest_460, FromRE2Concatenation_460) {
  RE2 re("abc.*def");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  std::string debug = pf->DebugString();
  EXPECT_FALSE(debug.empty());
  delete pf;
}

// Test DebugString on ATOM
TEST(PrefilterTest_460, DebugStringAtom_460) {
  RE2 re("test");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  std::string debug = pf->DebugString();
  EXPECT_FALSE(debug.empty());
  // The debug string for an atom should contain the atom text
  EXPECT_NE(debug.find("test"), std::string::npos);
  delete pf;
}

// Test DebugString on ALL
TEST(PrefilterTest_460, DebugStringAll_460) {
  Prefilter pf(Prefilter::ALL);
  std::string debug = pf.DebugString();
  EXPECT_FALSE(debug.empty());
}

// Test DebugString on NONE
TEST(PrefilterTest_460, DebugStringNone_460) {
  Prefilter pf(Prefilter::NONE);
  std::string debug = pf.DebugString();
  EXPECT_FALSE(debug.empty());
}

// Test FromRE2 with character class
TEST(PrefilterTest_460, FromRE2CharClass_460) {
  RE2 re("[abc]def");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  std::string debug = pf->DebugString();
  EXPECT_FALSE(debug.empty());
  delete pf;
}

// Test FromRE2 with repetition
TEST(PrefilterTest_460, FromRE2Repetition_460) {
  RE2 re("ab+c");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  std::string debug = pf->DebugString();
  EXPECT_FALSE(debug.empty());
  delete pf;
}

// Test FromRE2 with complex pattern
TEST(PrefilterTest_460, FromRE2Complex_460) {
  RE2 re("(foo|bar)baz(qux|quux)");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  std::string debug = pf->DebugString();
  EXPECT_FALSE(debug.empty());
  delete pf;
}

// Test FromRE2 with case-insensitive pattern
TEST(PrefilterTest_460, FromRE2CaseInsensitive_460) {
  RE2 re("(?i)hello");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    std::string debug = pf->DebugString();
    EXPECT_FALSE(debug.empty());
    delete pf;
  }
}

// Test FromRE2 with single character
TEST(PrefilterTest_460, FromRE2SingleChar_460) {
  RE2 re("a");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  // Single char might not produce a useful prefilter
  if (pf != nullptr) {
    delete pf;
  }
}

// Test op() returns correct value after construction
TEST(PrefilterTest_460, OpReturnsConstructedValue_460) {
  Prefilter pf1(Prefilter::AND);
  Prefilter pf2(Prefilter::OR);
  Prefilter pf3(Prefilter::ATOM);
  Prefilter pf4(Prefilter::ALL);
  Prefilter pf5(Prefilter::NONE);

  EXPECT_EQ(pf1.op(), Prefilter::AND);
  EXPECT_EQ(pf2.op(), Prefilter::OR);
  EXPECT_EQ(pf3.op(), Prefilter::ATOM);
  EXPECT_EQ(pf4.op(), Prefilter::ALL);
  EXPECT_EQ(pf5.op(), Prefilter::NONE);
}

// Test destruction doesn't crash
TEST(PrefilterTest_460, DestructionDoesNotCrash_460) {
  Prefilter* pf = new Prefilter(Prefilter::ALL);
  pf->set_unique_id(100);
  delete pf;
  // If we get here without crashing, the test passes
}

// Test FromRE2 with empty pattern
TEST(PrefilterTest_460, FromRE2EmptyPattern_460) {
  RE2 re("");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    delete pf;
  }
}

// Test FromRE2 with dot
TEST(PrefilterTest_460, FromRE2Dot_460) {
  RE2 re(".");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    EXPECT_EQ(pf->op(), Prefilter::ALL);
    delete pf;
  }
}

// Test FromRE2 with long literal string
TEST(PrefilterTest_460, FromRE2LongLiteral_460) {
  RE2 re("abcdefghijklmnopqrstuvwxyz");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  EXPECT_EQ(pf->op(), Prefilter::ATOM);
  EXPECT_EQ(pf->atom(), "abcdefghijklmnopqrstuvwxyz");
  delete pf;
}

}  // namespace re2
