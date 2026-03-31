#include "gtest/gtest.h"
#include "re2/prefilter.h"
#include "re2/re2.h"

namespace re2 {

// Test fixture for Prefilter tests
class PrefilterTest_462 : public ::testing::Test {
 protected:
  void TearDown() override {
    // Clean up any allocated prefilters
  }
};

// Test construction with NONE op
TEST_F(PrefilterTest_462, ConstructWithNoneOp_462) {
  Prefilter pf(Prefilter::NONE);
  EXPECT_EQ(pf.op(), Prefilter::NONE);
}

// Test construction with AND op
TEST_F(PrefilterTest_462, ConstructWithAndOp_462) {
  Prefilter pf(Prefilter::AND);
  EXPECT_EQ(pf.op(), Prefilter::AND);
}

// Test construction with OR op
TEST_F(PrefilterTest_462, ConstructWithOrOp_462) {
  Prefilter pf(Prefilter::OR);
  EXPECT_EQ(pf.op(), Prefilter::OR);
}

// Test construction with ATOM op
TEST_F(PrefilterTest_462, ConstructWithAtomOp_462) {
  Prefilter pf(Prefilter::ATOM);
  EXPECT_EQ(pf.op(), Prefilter::ATOM);
}

// Test construction with ALL op
TEST_F(PrefilterTest_462, ConstructWithAllOp_462) {
  Prefilter pf(Prefilter::ALL);
  EXPECT_EQ(pf.op(), Prefilter::ALL);
}

// Test unique_id default value
TEST_F(PrefilterTest_462, DefaultUniqueId_462) {
  Prefilter pf(Prefilter::NONE);
  // The default unique_id should be some initial value (likely -1 or 0)
  // We just verify it's retrievable
  int id = pf.unique_id();
  (void)id;  // Just ensure it doesn't crash
}

// Test set_unique_id and unique_id
TEST_F(PrefilterTest_462, SetAndGetUniqueId_462) {
  Prefilter pf(Prefilter::NONE);
  pf.set_unique_id(42);
  EXPECT_EQ(pf.unique_id(), 42);
}

// Test set_unique_id with zero
TEST_F(PrefilterTest_462, SetUniqueIdZero_462) {
  Prefilter pf(Prefilter::NONE);
  pf.set_unique_id(0);
  EXPECT_EQ(pf.unique_id(), 0);
}

// Test set_unique_id with negative value
TEST_F(PrefilterTest_462, SetUniqueIdNegative_462) {
  Prefilter pf(Prefilter::NONE);
  pf.set_unique_id(-1);
  EXPECT_EQ(pf.unique_id(), -1);
}

// Test set_unique_id with large value
TEST_F(PrefilterTest_462, SetUniqueIdLargeValue_462) {
  Prefilter pf(Prefilter::NONE);
  pf.set_unique_id(1000000);
  EXPECT_EQ(pf.unique_id(), 1000000);
}

// Test set_unique_id overwrite
TEST_F(PrefilterTest_462, SetUniqueIdOverwrite_462) {
  Prefilter pf(Prefilter::NONE);
  pf.set_unique_id(10);
  EXPECT_EQ(pf.unique_id(), 10);
  pf.set_unique_id(20);
  EXPECT_EQ(pf.unique_id(), 20);
}

// Test atom() on ATOM prefilter - default should be empty
TEST_F(PrefilterTest_462, AtomDefaultEmpty_462) {
  Prefilter pf(Prefilter::ATOM);
  // Default atom should be empty string
  EXPECT_TRUE(pf.atom().empty());
}

// Test subs() on non-AND/OR prefilter
TEST_F(PrefilterTest_462, SubsDefault_462) {
  Prefilter pf(Prefilter::NONE);
  // subs may be nullptr for a simple prefilter
  // Just verify it's accessible
  std::vector<Prefilter*>* s = pf.subs();
  (void)s;
}

// Test set_subs
TEST_F(PrefilterTest_462, SetSubs_462) {
  Prefilter pf(Prefilter::AND);
  auto* subs = new std::vector<Prefilter*>();
  pf.set_subs(subs);
  EXPECT_EQ(pf.subs(), subs);
  // Note: the Prefilter destructor should handle cleanup of subs
}

// Test set_subs with nullptr
TEST_F(PrefilterTest_462, SetSubsNull_462) {
  Prefilter pf(Prefilter::AND);
  pf.set_subs(nullptr);
  EXPECT_EQ(pf.subs(), nullptr);
}

// Test DebugString on NONE
TEST_F(PrefilterTest_462, DebugStringNone_462) {
  Prefilter pf(Prefilter::NONE);
  std::string debug = pf.DebugString();
  // Should return some non-crashing string
  EXPECT_FALSE(debug.empty());
}

// Test DebugString on ALL
TEST_F(PrefilterTest_462, DebugStringAll_462) {
  Prefilter pf(Prefilter::ALL);
  std::string debug = pf.DebugString();
  EXPECT_FALSE(debug.empty());
}

// Test FromRE2 with a simple literal pattern
TEST_F(PrefilterTest_462, FromRE2SimpleLiteral_462) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  // For a simple literal, we expect a non-null prefilter
  if (pf != nullptr) {
    EXPECT_EQ(pf->op(), Prefilter::ATOM);
    EXPECT_EQ(pf->atom(), "hello");
    delete pf;
  }
}

// Test FromRE2 with alternation
TEST_F(PrefilterTest_462, FromRE2Alternation_462) {
  RE2 re("hello|world");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    // Alternation should produce OR
    EXPECT_EQ(pf->op(), Prefilter::OR);
    delete pf;
  }
}

// Test FromRE2 with concatenation
TEST_F(PrefilterTest_462, FromRE2Concatenation_462) {
  RE2 re("abc.*def");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    // Concatenation with .* should produce AND of atoms
    delete pf;
  }
}

// Test FromRE2 with dot star (matches everything)
TEST_F(PrefilterTest_462, FromRE2DotStar_462) {
  RE2 re(".*");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  // .* matches everything, so prefilter could be ALL or null
  if (pf != nullptr) {
    EXPECT_EQ(pf->op(), Prefilter::ALL);
    delete pf;
  }
}

// Test FromRE2 with single character
TEST_F(PrefilterTest_462, FromRE2SingleChar_462) {
  RE2 re("a");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  // Single character may not produce a useful prefilter
  if (pf != nullptr) {
    delete pf;
  }
}

// Test FromRE2 with character class
TEST_F(PrefilterTest_462, FromRE2CharClass_462) {
  RE2 re("[abc]");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    delete pf;
  }
}

// Test FromRE2 with complex pattern
TEST_F(PrefilterTest_462, FromRE2ComplexPattern_462) {
  RE2 re("(foo|bar)baz(qux|quux)");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    // Should produce some combination of AND/OR
    delete pf;
  }
}

// Test FromRE2 with optional element
TEST_F(PrefilterTest_462, FromRE2Optional_462) {
  RE2 re("hello(world)?");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    delete pf;
  }
}

// Test DebugString on ATOM
TEST_F(PrefilterTest_462, DebugStringAtom_462) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    std::string debug = pf->DebugString();
    EXPECT_FALSE(debug.empty());
    delete pf;
  }
}

// Test FromRE2 with plus quantifier
TEST_F(PrefilterTest_462, FromRE2Plus_462) {
  RE2 re("hello+");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    delete pf;
  }
}

// Test FromRE2 with case insensitive
TEST_F(PrefilterTest_462, FromRE2CaseInsensitive_462) {
  RE2 re("(?i)hello");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    delete pf;
  }
}

// Test subs on OR prefilter from FromRE2
TEST_F(PrefilterTest_462, SubsOnOrPrefilter_462) {
  RE2 re("hello|world");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr && pf->op() == Prefilter::OR) {
    std::vector<Prefilter*>* s = pf->subs();
    EXPECT_NE(s, nullptr);
    if (s != nullptr) {
      EXPECT_GE(s->size(), 2u);
    }
    delete pf;
  } else {
    delete pf;
  }
}

// Test destructor doesn't crash on simple prefilter
TEST_F(PrefilterTest_462, DestructorSimple_462) {
  Prefilter* pf = new Prefilter(Prefilter::NONE);
  delete pf;  // Should not crash
}

// Test destructor on ALL prefilter
TEST_F(PrefilterTest_462, DestructorAll_462) {
  Prefilter* pf = new Prefilter(Prefilter::ALL);
  delete pf;  // Should not crash
}

// Test multiple set_unique_id calls
TEST_F(PrefilterTest_462, MultipleSetUniqueId_462) {
  Prefilter pf(Prefilter::ATOM);
  for (int i = 0; i < 100; i++) {
    pf.set_unique_id(i);
    EXPECT_EQ(pf.unique_id(), i);
  }
}

// Test FromRE2 with empty string pattern
TEST_F(PrefilterTest_462, FromRE2EmptyPattern_462) {
  RE2 re("");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  // Empty pattern matches everything
  if (pf != nullptr) {
    delete pf;
  }
}

// Test FromRE2 with long literal
TEST_F(PrefilterTest_462, FromRE2LongLiteral_462) {
  RE2 re("abcdefghijklmnopqrstuvwxyz");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    EXPECT_EQ(pf->op(), Prefilter::ATOM);
    delete pf;
  }
}

}  // namespace re2
