#include "gtest/gtest.h"
#include "re2/prefilter.h"
#include "re2/re2.h"

namespace re2 {

// Test basic construction and destruction with different ops
TEST(PrefilterTest_536, ConstructWithNONE_536) {
  Prefilter* pf = new Prefilter(Prefilter::NONE);
  EXPECT_EQ(Prefilter::NONE, pf->op());
  delete pf;
}

TEST(PrefilterTest_536, ConstructWithALL_536) {
  Prefilter* pf = new Prefilter(Prefilter::ALL);
  EXPECT_EQ(Prefilter::ALL, pf->op());
  delete pf;
}

TEST(PrefilterTest_536, ConstructWithATOM_536) {
  Prefilter* pf = new Prefilter(Prefilter::ATOM);
  EXPECT_EQ(Prefilter::ATOM, pf->op());
  delete pf;
}

TEST(PrefilterTest_536, ConstructWithAND_536) {
  Prefilter* pf = new Prefilter(Prefilter::AND);
  EXPECT_EQ(Prefilter::AND, pf->op());
  delete pf;
}

TEST(PrefilterTest_536, ConstructWithOR_536) {
  Prefilter* pf = new Prefilter(Prefilter::OR);
  EXPECT_EQ(Prefilter::OR, pf->op());
  delete pf;
}

// Test unique_id getter and setter
TEST(PrefilterTest_536, UniqueIdDefaultValue_536) {
  Prefilter* pf = new Prefilter(Prefilter::NONE);
  // Default unique_id should be some initial value (typically -1 or 0)
  int id = pf->unique_id();
  // Just verify it's callable
  (void)id;
  delete pf;
}

TEST(PrefilterTest_536, SetAndGetUniqueId_536) {
  Prefilter* pf = new Prefilter(Prefilter::NONE);
  pf->set_unique_id(42);
  EXPECT_EQ(42, pf->unique_id());
  delete pf;
}

TEST(PrefilterTest_536, SetUniqueIdMultipleTimes_536) {
  Prefilter* pf = new Prefilter(Prefilter::NONE);
  pf->set_unique_id(1);
  EXPECT_EQ(1, pf->unique_id());
  pf->set_unique_id(100);
  EXPECT_EQ(100, pf->unique_id());
  pf->set_unique_id(-1);
  EXPECT_EQ(-1, pf->unique_id());
  delete pf;
}

// Test atom getter
TEST(PrefilterTest_536, AtomDefaultEmpty_536) {
  Prefilter* pf = new Prefilter(Prefilter::ATOM);
  // The atom should initially be empty or default
  const std::string& atom = pf->atom();
  (void)atom;
  delete pf;
}

// Test subs getter and setter
TEST(PrefilterTest_536, SubsInitiallyNull_536) {
  Prefilter* pf = new Prefilter(Prefilter::AND);
  // subs() may return nullptr initially or a valid pointer depending on construction
  // Just verify the method is callable
  std::vector<Prefilter*>* subs = pf->subs();
  (void)subs;
  delete pf;
}

TEST(PrefilterTest_536, SetSubs_536) {
  Prefilter* pf = new Prefilter(Prefilter::AND);
  std::vector<Prefilter*>* new_subs = new std::vector<Prefilter*>();
  pf->set_subs(new_subs);
  EXPECT_EQ(new_subs, pf->subs());
  // Destructor will clean up subs
  delete pf;
}

TEST(PrefilterTest_536, SetSubsWithChildren_536) {
  Prefilter* pf = new Prefilter(Prefilter::AND);
  std::vector<Prefilter*>* new_subs = new std::vector<Prefilter*>();
  new_subs->push_back(new Prefilter(Prefilter::ATOM));
  new_subs->push_back(new Prefilter(Prefilter::ALL));
  pf->set_subs(new_subs);
  EXPECT_EQ(new_subs, pf->subs());
  EXPECT_EQ(2u, pf->subs()->size());
  // Destructor should clean up children and the vector
  delete pf;
}

// Test DebugString
TEST(PrefilterTest_536, DebugStringNONE_536) {
  Prefilter* pf = new Prefilter(Prefilter::NONE);
  std::string debug = pf->DebugString();
  EXPECT_FALSE(debug.empty());
  delete pf;
}

TEST(PrefilterTest_536, DebugStringALL_536) {
  Prefilter* pf = new Prefilter(Prefilter::ALL);
  std::string debug = pf->DebugString();
  EXPECT_FALSE(debug.empty());
  delete pf;
}

// Test FromRE2 with simple patterns
TEST(PrefilterTest_536, FromRE2SimpleLiteral_536) {
  RE2 re("hello");
  Prefilter* pf = Prefilter::FromRE2(&re);
  // For a simple literal, we should get a non-null prefilter
  if (pf != nullptr) {
    std::string debug = pf->DebugString();
    EXPECT_FALSE(debug.empty());
    delete pf;
  }
}

TEST(PrefilterTest_536, FromRE2DotStar_536) {
  RE2 re(".*");
  Prefilter* pf = Prefilter::FromRE2(&re);
  // .* matches everything, prefilter might be ALL or null
  if (pf != nullptr) {
    // If returned, it should be valid
    std::string debug = pf->DebugString();
    (void)debug;
    delete pf;
  }
}

TEST(PrefilterTest_536, FromRE2Alternation_536) {
  RE2 re("hello|world");
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    std::string debug = pf->DebugString();
    EXPECT_FALSE(debug.empty());
    delete pf;
  }
}

TEST(PrefilterTest_536, FromRE2Concatenation_536) {
  RE2 re("abc.*def");
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    std::string debug = pf->DebugString();
    EXPECT_FALSE(debug.empty());
    delete pf;
  }
}

TEST(PrefilterTest_536, FromRE2CharacterClass_536) {
  RE2 re("[a-z]+hello");
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    std::string debug = pf->DebugString();
    EXPECT_FALSE(debug.empty());
    delete pf;
  }
}

TEST(PrefilterTest_536, FromRE2EmptyPattern_536) {
  RE2 re("");
  Prefilter* pf = Prefilter::FromRE2(&re);
  // Empty pattern - could be null or ALL
  if (pf != nullptr) {
    delete pf;
  }
}

TEST(PrefilterTest_536, FromRE2ComplexPattern_536) {
  RE2 re("(foo|bar)baz[0-9]+");
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    std::string debug = pf->DebugString();
    EXPECT_FALSE(debug.empty());
    delete pf;
  }
}

// Test destruction with null subs (no crash)
TEST(PrefilterTest_536, DestructionWithNoSubs_536) {
  Prefilter* pf = new Prefilter(Prefilter::ATOM);
  // Should not crash on destruction even without subs
  delete pf;
}

// Test destruction with empty subs vector
TEST(PrefilterTest_536, DestructionWithEmptySubs_536) {
  Prefilter* pf = new Prefilter(Prefilter::AND);
  std::vector<Prefilter*>* subs = new std::vector<Prefilter*>();
  pf->set_subs(subs);
  // Should not crash
  delete pf;
}

// Test deeply nested structure destruction
TEST(PrefilterTest_536, DestructionWithNestedSubs_536) {
  Prefilter* root = new Prefilter(Prefilter::AND);
  std::vector<Prefilter*>* root_subs = new std::vector<Prefilter*>();

  Prefilter* child = new Prefilter(Prefilter::OR);
  std::vector<Prefilter*>* child_subs = new std::vector<Prefilter*>();
  child_subs->push_back(new Prefilter(Prefilter::ATOM));
  child_subs->push_back(new Prefilter(Prefilter::ATOM));
  child->set_subs(child_subs);

  root_subs->push_back(child);
  root_subs->push_back(new Prefilter(Prefilter::ALL));
  root->set_subs(root_subs);

  // Should properly free all nested structures
  delete root;
}

// Test DebugString with sub-filters
TEST(PrefilterTest_536, DebugStringWithSubs_536) {
  Prefilter* pf = new Prefilter(Prefilter::AND);
  std::vector<Prefilter*>* subs = new std::vector<Prefilter*>();
  subs->push_back(new Prefilter(Prefilter::ALL));
  subs->push_back(new Prefilter(Prefilter::NONE));
  pf->set_subs(subs);
  std::string debug = pf->DebugString();
  EXPECT_FALSE(debug.empty());
  delete pf;
}

// Test FromRE2 with case-insensitive regex
TEST(PrefilterTest_536, FromRE2CaseInsensitive_536) {
  RE2 re("(?i)hello");
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    std::string debug = pf->DebugString();
    EXPECT_FALSE(debug.empty());
    delete pf;
  }
}

// Test FromRE2 with single character
TEST(PrefilterTest_536, FromRE2SingleChar_536) {
  RE2 re("a");
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    delete pf;
  }
}

// Test unique_id boundary values
TEST(PrefilterTest_536, UniqueIdZero_536) {
  Prefilter* pf = new Prefilter(Prefilter::NONE);
  pf->set_unique_id(0);
  EXPECT_EQ(0, pf->unique_id());
  delete pf;
}

TEST(PrefilterTest_536, UniqueIdLargeValue_536) {
  Prefilter* pf = new Prefilter(Prefilter::NONE);
  pf->set_unique_id(INT_MAX);
  EXPECT_EQ(INT_MAX, pf->unique_id());
  delete pf;
}

TEST(PrefilterTest_536, UniqueIdNegativeValue_536) {
  Prefilter* pf = new Prefilter(Prefilter::NONE);
  pf->set_unique_id(INT_MIN);
  EXPECT_EQ(INT_MIN, pf->unique_id());
  delete pf;
}

}  // namespace re2
