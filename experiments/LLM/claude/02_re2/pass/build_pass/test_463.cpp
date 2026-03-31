#include "gtest/gtest.h"
#include "re2/prefilter.h"
#include "re2/re2.h"

namespace re2 {

// Test basic construction with different Op types
TEST(PrefilterTest_463, ConstructWithALL_463) {
  Prefilter pf(Prefilter::ALL);
  EXPECT_EQ(pf.op(), Prefilter::ALL);
}

TEST(PrefilterTest_463, ConstructWithNONE_463) {
  Prefilter pf(Prefilter::NONE);
  EXPECT_EQ(pf.op(), Prefilter::NONE);
}

TEST(PrefilterTest_463, ConstructWithATOM_463) {
  Prefilter pf(Prefilter::ATOM);
  EXPECT_EQ(pf.op(), Prefilter::ATOM);
}

TEST(PrefilterTest_463, ConstructWithAND_463) {
  Prefilter pf(Prefilter::AND);
  EXPECT_EQ(pf.op(), Prefilter::AND);
}

TEST(PrefilterTest_463, ConstructWithOR_463) {
  Prefilter pf(Prefilter::OR);
  EXPECT_EQ(pf.op(), Prefilter::OR);
}

// Test unique_id getter and setter
TEST(PrefilterTest_463, DefaultUniqueId_463) {
  Prefilter pf(Prefilter::ALL);
  // Check default unique_id (typically -1 or 0, but we just verify set/get roundtrip)
  int default_id = pf.unique_id();
  // Just ensure it doesn't crash; actual default depends on implementation
  (void)default_id;
}

TEST(PrefilterTest_463, SetAndGetUniqueId_463) {
  Prefilter pf(Prefilter::ALL);
  pf.set_unique_id(42);
  EXPECT_EQ(pf.unique_id(), 42);
}

TEST(PrefilterTest_463, SetUniqueIdZero_463) {
  Prefilter pf(Prefilter::ATOM);
  pf.set_unique_id(0);
  EXPECT_EQ(pf.unique_id(), 0);
}

TEST(PrefilterTest_463, SetUniqueIdNegative_463) {
  Prefilter pf(Prefilter::NONE);
  pf.set_unique_id(-1);
  EXPECT_EQ(pf.unique_id(), -1);
}

TEST(PrefilterTest_463, SetUniqueIdMultipleTimes_463) {
  Prefilter pf(Prefilter::ALL);
  pf.set_unique_id(10);
  EXPECT_EQ(pf.unique_id(), 10);
  pf.set_unique_id(20);
  EXPECT_EQ(pf.unique_id(), 20);
}

// Test atom() accessor
TEST(PrefilterTest_463, AtomDefaultEmpty_463) {
  Prefilter pf(Prefilter::ATOM);
  // Atom should be accessible; default likely empty
  const std::string& atom = pf.atom();
  (void)atom;  // Just ensure no crash
}

// Test subs() accessor for AND op
TEST(PrefilterTest_463, SubsAccessibleForAND_463) {
  Prefilter pf(Prefilter::AND);
  std::vector<Prefilter*>* s = pf.subs();
  // subs pointer should be accessible for AND
  (void)s;
}

// Test subs() accessor for OR op
TEST(PrefilterTest_463, SubsAccessibleForOR_463) {
  Prefilter pf(Prefilter::OR);
  std::vector<Prefilter*>* s = pf.subs();
  (void)s;
}

// Test set_subs
TEST(PrefilterTest_463, SetSubsForAND_463) {
  Prefilter pf(Prefilter::AND);
  auto* new_subs = new std::vector<Prefilter*>();
  pf.set_subs(new_subs);
  EXPECT_EQ(pf.subs(), new_subs);
  // Note: pf destructor should handle cleanup or we rely on implementation
}

TEST(PrefilterTest_463, SetSubsForOR_463) {
  Prefilter pf(Prefilter::OR);
  auto* new_subs = new std::vector<Prefilter*>();
  pf.set_subs(new_subs);
  EXPECT_EQ(pf.subs(), new_subs);
}

// Test DebugString
TEST(PrefilterTest_463, DebugStringALL_463) {
  Prefilter pf(Prefilter::ALL);
  std::string dbg = pf.DebugString();
  EXPECT_FALSE(dbg.empty());
}

TEST(PrefilterTest_463, DebugStringNONE_463) {
  Prefilter pf(Prefilter::NONE);
  std::string dbg = pf.DebugString();
  EXPECT_FALSE(dbg.empty());
}

TEST(PrefilterTest_463, DebugStringATOM_463) {
  Prefilter pf(Prefilter::ATOM);
  std::string dbg = pf.DebugString();
  // Should return some string representation
  (void)dbg;
}

TEST(PrefilterTest_463, DebugStringAND_463) {
  Prefilter pf(Prefilter::AND);
  std::string dbg = pf.DebugString();
  (void)dbg;
}

TEST(PrefilterTest_463, DebugStringOR_463) {
  Prefilter pf(Prefilter::OR);
  std::string dbg = pf.DebugString();
  (void)dbg;
}

// Test FromRE2 with a simple pattern
TEST(PrefilterTest_463, FromRE2SimpleLiteral_463) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  // For a simple literal, we expect a non-null prefilter
  if (pf != nullptr) {
    // The prefilter for a literal string should be ATOM or contain atoms
    EXPECT_TRUE(pf->op() == Prefilter::ATOM || 
                pf->op() == Prefilter::AND ||
                pf->op() == Prefilter::ALL);
    delete pf;
  }
}

TEST(PrefilterTest_463, FromRE2DotStar_463) {
  RE2 re(".*");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  // .* matches everything, so prefilter could be ALL or null
  if (pf != nullptr) {
    EXPECT_EQ(pf->op(), Prefilter::ALL);
    delete pf;
  }
}

TEST(PrefilterTest_463, FromRE2Alternation_463) {
  RE2 re("hello|world");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    // For alternation, we might get OR of atoms
    std::string dbg = pf->DebugString();
    EXPECT_FALSE(dbg.empty());
    delete pf;
  }
}

TEST(PrefilterTest_463, FromRE2Concatenation_463) {
  RE2 re("abc.*def");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    std::string dbg = pf->DebugString();
    EXPECT_FALSE(dbg.empty());
    delete pf;
  }
}

TEST(PrefilterTest_463, FromRE2EmptyPattern_463) {
  RE2 re("");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    delete pf;
  }
}

TEST(PrefilterTest_463, FromRE2ComplexPattern_463) {
  RE2 re("(foo|bar)baz[0-9]+");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    std::string dbg = pf->DebugString();
    EXPECT_FALSE(dbg.empty());
    delete pf;
  }
}

TEST(PrefilterTest_463, FromRE2CharacterClass_463) {
  RE2 re("[abc]+");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    delete pf;
  }
}

// Test that op enum values are distinct
TEST(PrefilterTest_463, OpEnumValues_463) {
  EXPECT_EQ(Prefilter::ALL, 0);
  EXPECT_EQ(Prefilter::NONE, 1);
  EXPECT_EQ(Prefilter::ATOM, 2);
  EXPECT_EQ(Prefilter::AND, 3);
  EXPECT_EQ(Prefilter::OR, 4);
}

// Test destruction doesn't crash
TEST(PrefilterTest_463, DestructorNoSubs_463) {
  Prefilter* pf = new Prefilter(Prefilter::ALL);
  delete pf;  // Should not crash
}

TEST(PrefilterTest_463, DestructorWithEmptySubs_463) {
  Prefilter* pf = new Prefilter(Prefilter::AND);
  // Default construction for AND should be safe to destroy
  delete pf;
}

// Test FromRE2 with case insensitive pattern
TEST(PrefilterTest_463, FromRE2CaseInsensitive_463) {
  RE2 re("(?i)hello");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    std::string dbg = pf->DebugString();
    (void)dbg;
    delete pf;
  }
}

// Test FromRE2 with single character
TEST(PrefilterTest_463, FromRE2SingleChar_463) {
  RE2 re("a");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    delete pf;
  }
}

// Test FromRE2 with long literal
TEST(PrefilterTest_463, FromRE2LongLiteral_463) {
  RE2 re("abcdefghijklmnopqrstuvwxyz");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  EXPECT_TRUE(pf->op() == Prefilter::ATOM || 
              pf->op() == Prefilter::AND ||
              pf->op() == Prefilter::ALL);
  delete pf;
}

}  // namespace re2
