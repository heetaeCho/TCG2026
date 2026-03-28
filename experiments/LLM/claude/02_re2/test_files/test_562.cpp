#include "gtest/gtest.h"
#include "re2/prefilter.h"
#include "re2/re2.h"

namespace re2 {

class PrefilterTest_562 : public ::testing::Test {
 protected:
  void TearDown() override {
    // Prefilters obtained from FromRE2 are owned by us and need cleanup
  }
};

// Test constructing a Prefilter with ALL op
TEST_F(PrefilterTest_562, ConstructALL_DebugString_562) {
  Prefilter pf(Prefilter::ALL);
  EXPECT_EQ(pf.op(), Prefilter::ALL);
  std::string debug = pf.DebugString();
  EXPECT_EQ(debug, "");
}

// Test constructing a Prefilter with NONE op
TEST_F(PrefilterTest_562, ConstructNONE_DebugString_562) {
  Prefilter pf(Prefilter::NONE);
  EXPECT_EQ(pf.op(), Prefilter::NONE);
  std::string debug = pf.DebugString();
  EXPECT_EQ(debug, "*no-matches*");
}

// Test op() accessor
TEST_F(PrefilterTest_562, OpAccessor_562) {
  Prefilter pf_all(Prefilter::ALL);
  EXPECT_EQ(pf_all.op(), Prefilter::ALL);

  Prefilter pf_none(Prefilter::NONE);
  EXPECT_EQ(pf_none.op(), Prefilter::NONE);

  Prefilter pf_atom(Prefilter::ATOM);
  EXPECT_EQ(pf_atom.op(), Prefilter::ATOM);

  Prefilter pf_and(Prefilter::AND);
  EXPECT_EQ(pf_and.op(), Prefilter::AND);

  Prefilter pf_or(Prefilter::OR);
  EXPECT_EQ(pf_or.op(), Prefilter::OR);
}

// Test unique_id set and get
TEST_F(PrefilterTest_562, UniqueIdSetGet_562) {
  Prefilter pf(Prefilter::ALL);
  pf.set_unique_id(42);
  EXPECT_EQ(pf.unique_id(), 42);
}

// Test unique_id with zero
TEST_F(PrefilterTest_562, UniqueIdZero_562) {
  Prefilter pf(Prefilter::ALL);
  pf.set_unique_id(0);
  EXPECT_EQ(pf.unique_id(), 0);
}

// Test unique_id with negative
TEST_F(PrefilterTest_562, UniqueIdNegative_562) {
  Prefilter pf(Prefilter::ALL);
  pf.set_unique_id(-1);
  EXPECT_EQ(pf.unique_id(), -1);
}

// Test FromRE2 with a simple literal pattern
TEST_F(PrefilterTest_562, FromRE2SimpleLiteral_562) {
  RE2 re("hello");
  Prefilter* pf = Prefilter::FromRE2(&re);
  // A simple literal should produce an ATOM prefilter
  if (pf != nullptr) {
    EXPECT_EQ(pf->op(), Prefilter::ATOM);
    std::string debug = pf->DebugString();
    EXPECT_FALSE(debug.empty());
    delete pf;
  }
}

// Test FromRE2 with alternation (should produce OR)
TEST_F(PrefilterTest_562, FromRE2Alternation_562) {
  RE2 re("hello|world");
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    // Alternation typically produces OR
    std::string debug = pf->DebugString();
    EXPECT_FALSE(debug.empty());
    delete pf;
  }
}

// Test FromRE2 with dot star (match anything - should produce ALL)
TEST_F(PrefilterTest_562, FromRE2MatchAll_562) {
  RE2 re(".*");
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    EXPECT_EQ(pf->op(), Prefilter::ALL);
    std::string debug = pf->DebugString();
    EXPECT_EQ(debug, "");
    delete pf;
  }
}

// Test FromRE2 with concatenation
TEST_F(PrefilterTest_562, FromRE2Concatenation_562) {
  RE2 re("abc.*def");
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    std::string debug = pf->DebugString();
    // Should contain some form of "abc" and "def"
    EXPECT_FALSE(debug.empty());
    delete pf;
  }
}

// Test DebugString for ATOM prefilter via FromRE2
TEST_F(PrefilterTest_562, DebugStringAtom_562) {
  RE2 re("hello");
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr && pf->op() == Prefilter::ATOM) {
    std::string debug = pf->DebugString();
    EXPECT_EQ(debug, "hello");
    delete pf;
  } else {
    delete pf;
  }
}

// Test DebugString for OR prefilter via FromRE2
TEST_F(PrefilterTest_562, DebugStringOR_562) {
  RE2 re("abc|def");
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr && pf->op() == Prefilter::OR) {
    std::string debug = pf->DebugString();
    // OR debug string starts with "(" and ends with ")"
    EXPECT_EQ(debug.front(), '(');
    EXPECT_EQ(debug.back(), ')');
    // Should contain "|"
    EXPECT_NE(debug.find('|'), std::string::npos);
    delete pf;
  } else {
    delete pf;
  }
}

// Test subs() accessor
TEST_F(PrefilterTest_562, SubsAccessor_562) {
  Prefilter pf(Prefilter::AND);
  // For a newly created AND, subs may or may not be initialized
  // but the accessor should be callable
  auto* subs = pf.subs();
  // Just verifying we can call subs()
  (void)subs;
}

// Test set_subs
TEST_F(PrefilterTest_562, SetSubs_562) {
  Prefilter pf(Prefilter::AND);
  auto* new_subs = new std::vector<Prefilter*>();
  new_subs->push_back(new Prefilter(Prefilter::ALL));
  new_subs->push_back(new Prefilter(Prefilter::NONE));
  pf.set_subs(new_subs);
  EXPECT_EQ(pf.subs(), new_subs);
  EXPECT_EQ(pf.subs()->size(), 2u);
  // The debug string for AND with ALL and NONE subs
  std::string debug = pf.DebugString();
  EXPECT_FALSE(debug.empty());
}

// Test atom() accessor
TEST_F(PrefilterTest_562, AtomAccessor_562) {
  RE2 re("hello");
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr && pf->op() == Prefilter::ATOM) {
    EXPECT_EQ(pf->atom(), "hello");
    delete pf;
  } else {
    delete pf;
  }
}

// Test FromRE2 with empty pattern
TEST_F(PrefilterTest_562, FromRE2EmptyPattern_562) {
  RE2 re("");
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    // Empty pattern matches everything, should be ALL
    EXPECT_EQ(pf->op(), Prefilter::ALL);
    delete pf;
  }
}

// Test FromRE2 with character class
TEST_F(PrefilterTest_562, FromRE2CharacterClass_562) {
  RE2 re("[abc]def");
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    std::string debug = pf->DebugString();
    // Should have some meaningful prefilter
    delete pf;
  }
}

// Test FromRE2 with complex pattern
TEST_F(PrefilterTest_562, FromRE2Complex_562) {
  RE2 re("(foo|bar).*baz");
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    std::string debug = pf->DebugString();
    EXPECT_FALSE(debug.empty());
    delete pf;
  }
}

// Test AND DebugString with multiple subs
TEST_F(PrefilterTest_562, DebugStringANDMultipleSubs_562) {
  Prefilter* pf = new Prefilter(Prefilter::AND);
  auto* subs = new std::vector<Prefilter*>();
  
  Prefilter* sub1 = new Prefilter(Prefilter::ALL);
  Prefilter* sub2 = new Prefilter(Prefilter::NONE);
  Prefilter* sub3 = new Prefilter(Prefilter::ALL);
  
  subs->push_back(sub1);
  subs->push_back(sub2);
  subs->push_back(sub3);
  pf->set_subs(subs);
  
  std::string debug = pf->DebugString();
  // AND separates subs with spaces
  EXPECT_NE(debug.find(' '), std::string::npos);
  EXPECT_NE(debug.find("*no-matches*"), std::string::npos);
  
  delete pf;
}

// Test OR DebugString with multiple subs
TEST_F(PrefilterTest_562, DebugStringORMultipleSubs_562) {
  Prefilter* pf = new Prefilter(Prefilter::OR);
  auto* subs = new std::vector<Prefilter*>();
  
  Prefilter* sub1 = new Prefilter(Prefilter::ALL);
  Prefilter* sub2 = new Prefilter(Prefilter::NONE);
  
  subs->push_back(sub1);
  subs->push_back(sub2);
  pf->set_subs(subs);
  
  std::string debug = pf->DebugString();
  // OR wraps in parens and separates with |
  EXPECT_EQ(debug.front(), '(');
  EXPECT_EQ(debug.back(), ')');
  EXPECT_NE(debug.find('|'), std::string::npos);
  
  delete pf;
}

// Test FromRE2 with single character
TEST_F(PrefilterTest_562, FromRE2SingleChar_562) {
  RE2 re("a");
  Prefilter* pf = Prefilter::FromRE2(&re);
  // Single character might be ALL since it's too short for meaningful prefilter
  if (pf != nullptr) {
    delete pf;
  }
}

// Test FromRE2 with repeated pattern
TEST_F(PrefilterTest_562, FromRE2Repeated_562) {
  RE2 re("aaa+");
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    std::string debug = pf->DebugString();
    delete pf;
  }
}

// Test unique_id with large value
TEST_F(PrefilterTest_562, UniqueIdLargeValue_562) {
  Prefilter pf(Prefilter::ALL);
  pf.set_unique_id(999999);
  EXPECT_EQ(pf.unique_id(), 999999);
}

// Test DebugString for nested OR inside AND
TEST_F(PrefilterTest_562, DebugStringNestedORInsideAND_562) {
  Prefilter* pf_and = new Prefilter(Prefilter::AND);
  Prefilter* pf_or = new Prefilter(Prefilter::OR);
  
  auto* or_subs = new std::vector<Prefilter*>();
  or_subs->push_back(new Prefilter(Prefilter::NONE));
  or_subs->push_back(new Prefilter(Prefilter::ALL));
  pf_or->set_subs(or_subs);
  
  auto* and_subs = new std::vector<Prefilter*>();
  and_subs->push_back(pf_or);
  and_subs->push_back(new Prefilter(Prefilter::NONE));
  pf_and->set_subs(and_subs);
  
  std::string debug = pf_and->DebugString();
  // Should contain nested OR representation with parens
  EXPECT_NE(debug.find('('), std::string::npos);
  EXPECT_NE(debug.find(')'), std::string::npos);
  EXPECT_NE(debug.find('|'), std::string::npos);
  
  delete pf_and;
}

// Test FromRE2 case insensitive
TEST_F(PrefilterTest_562, FromRE2CaseInsensitive_562) {
  RE2 re("(?i)hello");
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    std::string debug = pf->DebugString();
    // Case insensitive might produce OR of different cases
    delete pf;
  }
}

}  // namespace re2
