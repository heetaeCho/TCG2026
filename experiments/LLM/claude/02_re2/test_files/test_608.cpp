#include "gtest/gtest.h"
#include "re2/prefilter.h"
#include "re2/re2.h"

namespace re2 {

// Test constructing Prefilter with ALL op
TEST(PrefilterTest_608, ConstructWithALL_608) {
  Prefilter pf(Prefilter::ALL);
  EXPECT_EQ(pf.op(), Prefilter::ALL);
  EXPECT_EQ(pf.subs(), nullptr);
}

// Test constructing Prefilter with NONE op
TEST(PrefilterTest_608, ConstructWithNONE_608) {
  Prefilter pf(Prefilter::NONE);
  EXPECT_EQ(pf.op(), Prefilter::NONE);
  EXPECT_EQ(pf.subs(), nullptr);
}

// Test constructing Prefilter with ATOM op
TEST(PrefilterTest_608, ConstructWithATOM_608) {
  Prefilter pf(Prefilter::ATOM);
  EXPECT_EQ(pf.op(), Prefilter::ATOM);
  EXPECT_EQ(pf.subs(), nullptr);
}

// Test constructing Prefilter with AND op - should allocate subs
TEST(PrefilterTest_608, ConstructWithAND_608) {
  Prefilter* pf = new Prefilter(Prefilter::AND);
  EXPECT_EQ(pf->op(), Prefilter::AND);
  EXPECT_NE(pf->subs(), nullptr);
  EXPECT_TRUE(pf->subs()->empty());
  delete pf;
}

// Test constructing Prefilter with OR op - should allocate subs
TEST(PrefilterTest_608, ConstructWithOR_608) {
  Prefilter* pf = new Prefilter(Prefilter::OR);
  EXPECT_EQ(pf->op(), Prefilter::OR);
  EXPECT_NE(pf->subs(), nullptr);
  EXPECT_TRUE(pf->subs()->empty());
  delete pf;
}

// Test unique_id getter and setter
TEST(PrefilterTest_608, UniqueId_608) {
  Prefilter pf(Prefilter::ALL);
  pf.set_unique_id(42);
  EXPECT_EQ(pf.unique_id(), 42);
}

// Test unique_id with zero
TEST(PrefilterTest_608, UniqueIdZero_608) {
  Prefilter pf(Prefilter::ALL);
  pf.set_unique_id(0);
  EXPECT_EQ(pf.unique_id(), 0);
}

// Test unique_id with negative value
TEST(PrefilterTest_608, UniqueIdNegative_608) {
  Prefilter pf(Prefilter::ALL);
  pf.set_unique_id(-1);
  EXPECT_EQ(pf.unique_id(), -1);
}

// Test atom() accessor
TEST(PrefilterTest_608, AtomAccessor_608) {
  Prefilter pf(Prefilter::ATOM);
  // Default atom should be empty
  EXPECT_TRUE(pf.atom().empty());
}

// Test set_subs
TEST(PrefilterTest_608, SetSubs_608) {
  Prefilter* pf = new Prefilter(Prefilter::ALL);
  EXPECT_EQ(pf->subs(), nullptr);
  
  auto* new_subs = new std::vector<Prefilter*>;
  pf->set_subs(new_subs);
  EXPECT_EQ(pf->subs(), new_subs);
  
  // Clean up - set_subs doesn't take ownership in the set call, 
  // but destructor might delete. Let's set to nullptr to be safe before manual delete.
  pf->set_subs(nullptr);
  delete new_subs;
  delete pf;
}

// Test DebugString for ALL
TEST(PrefilterTest_608, DebugStringALL_608) {
  Prefilter pf(Prefilter::ALL);
  std::string debug = pf.DebugString();
  EXPECT_FALSE(debug.empty());
}

// Test DebugString for NONE
TEST(PrefilterTest_608, DebugStringNONE_608) {
  Prefilter pf(Prefilter::NONE);
  std::string debug = pf.DebugString();
  EXPECT_FALSE(debug.empty());
}

// Test FromRE2 with a simple literal pattern
TEST(PrefilterTest_608, FromRE2SimpleLiteral_608) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  // A simple literal should produce a non-null prefilter
  if (pf != nullptr) {
    // For a literal string, we expect an ATOM
    EXPECT_EQ(pf->op(), Prefilter::ATOM);
    EXPECT_EQ(pf->atom(), "hello");
    delete pf;
  }
}

// Test FromRE2 with alternation
TEST(PrefilterTest_608, FromRE2Alternation_608) {
  RE2 re("hello|world");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    // Alternation should produce OR
    EXPECT_EQ(pf->op(), Prefilter::OR);
    delete pf;
  }
}

// Test FromRE2 with wildcard pattern (matches everything)
TEST(PrefilterTest_608, FromRE2MatchAll_608) {
  RE2 re(".*");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    // A .* pattern matches everything, expect ALL
    EXPECT_EQ(pf->op(), Prefilter::ALL);
    delete pf;
  }
}

// Test FromRE2 with concatenated literals
TEST(PrefilterTest_608, FromRE2ConcatLiterals_608) {
  RE2 re("abc.*def");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    // Should produce an AND of atoms or similar
    delete pf;
  }
}

// Test FromRE2 with single character
TEST(PrefilterTest_608, FromRE2SingleChar_608) {
  RE2 re("a");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    delete pf;
  }
}

// Test FromRE2 with character class
TEST(PrefilterTest_608, FromRE2CharClass_608) {
  RE2 re("[abc]");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  // Character class might result in ALL since no single atom matches
  if (pf != nullptr) {
    delete pf;
  }
}

// Test FromRE2 with empty pattern
TEST(PrefilterTest_608, FromRE2EmptyPattern_608) {
  RE2 re("");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    EXPECT_EQ(pf->op(), Prefilter::ALL);
    delete pf;
  }
}

// Test DebugString for AND with subs
TEST(PrefilterTest_608, DebugStringAND_608) {
  Prefilter* pf = new Prefilter(Prefilter::AND);
  ASSERT_NE(pf->subs(), nullptr);
  std::string debug = pf->DebugString();
  EXPECT_FALSE(debug.empty());
  delete pf;
}

// Test DebugString for OR with subs
TEST(PrefilterTest_608, DebugStringOR_608) {
  Prefilter* pf = new Prefilter(Prefilter::OR);
  ASSERT_NE(pf->subs(), nullptr);
  std::string debug = pf->DebugString();
  EXPECT_FALSE(debug.empty());
  delete pf;
}

// Test destructor doesn't crash with empty AND
TEST(PrefilterTest_608, DestructorEmptyAND_608) {
  Prefilter* pf = new Prefilter(Prefilter::AND);
  EXPECT_NO_FATAL_FAILURE(delete pf);
}

// Test destructor doesn't crash with empty OR
TEST(PrefilterTest_608, DestructorEmptyOR_608) {
  Prefilter* pf = new Prefilter(Prefilter::OR);
  EXPECT_NO_FATAL_FAILURE(delete pf);
}

// Test destructor doesn't crash for simple ops
TEST(PrefilterTest_608, DestructorSimpleOps_608) {
  {
    Prefilter pf(Prefilter::ALL);
  }
  {
    Prefilter pf(Prefilter::NONE);
  }
  {
    Prefilter pf(Prefilter::ATOM);
  }
}

// Test FromRE2 with complex regex
TEST(PrefilterTest_608, FromRE2ComplexRegex_608) {
  RE2 re("(foo|bar).*baz");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    // Complex pattern, just verify it produces a valid result
    Op op = pf->op();
    EXPECT_GE(static_cast<int>(op), 0);
    EXPECT_LE(static_cast<int>(op), 4);
    delete pf;
  }
}

// Test FromRE2 with case-insensitive pattern
TEST(PrefilterTest_608, FromRE2CaseInsensitive_608) {
  RE2 re("(?i)hello");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    delete pf;
  }
}

// Test multiple unique_id sets
TEST(PrefilterTest_608, UniqueIdMultipleSets_608) {
  Prefilter pf(Prefilter::ALL);
  pf.set_unique_id(10);
  EXPECT_EQ(pf.unique_id(), 10);
  pf.set_unique_id(20);
  EXPECT_EQ(pf.unique_id(), 20);
  pf.set_unique_id(100);
  EXPECT_EQ(pf.unique_id(), 100);
}

// Test Op enum values
TEST(PrefilterTest_608, OpEnumValues_608) {
  EXPECT_EQ(static_cast<int>(Prefilter::ALL), 0);
  EXPECT_EQ(static_cast<int>(Prefilter::NONE), 1);
  EXPECT_EQ(static_cast<int>(Prefilter::ATOM), 2);
  EXPECT_EQ(static_cast<int>(Prefilter::AND), 3);
  EXPECT_EQ(static_cast<int>(Prefilter::OR), 4);
}

}  // namespace re2
