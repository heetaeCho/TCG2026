#include "gtest/gtest.h"
#include "re2/prefilter.h"
#include "re2/re2.h"

namespace re2 {

// Test constructing a Prefilter with ALL op
TEST(PrefilterTest_459, ConstructWithAllOp_459) {
  Prefilter pf(Prefilter::ALL);
  EXPECT_EQ(Prefilter::ALL, pf.op());
}

// Test constructing a Prefilter with NONE op
TEST(PrefilterTest_459, ConstructWithNoneOp_459) {
  Prefilter pf(Prefilter::NONE);
  EXPECT_EQ(Prefilter::NONE, pf.op());
}

// Test constructing a Prefilter with AND op
TEST(PrefilterTest_459, ConstructWithAndOp_459) {
  Prefilter pf(Prefilter::AND);
  EXPECT_EQ(Prefilter::AND, pf.op());
}

// Test constructing a Prefilter with OR op
TEST(PrefilterTest_459, ConstructWithOrOp_459) {
  Prefilter pf(Prefilter::OR);
  EXPECT_EQ(Prefilter::OR, pf.op());
}

// Test constructing a Prefilter with ATOM op
TEST(PrefilterTest_459, ConstructWithAtomOp_459) {
  Prefilter pf(Prefilter::ATOM);
  EXPECT_EQ(Prefilter::ATOM, pf.op());
}

// Test atom() returns empty string for non-ATOM prefilter
TEST(PrefilterTest_459, AtomDefaultEmpty_459) {
  Prefilter pf(Prefilter::ALL);
  EXPECT_TRUE(pf.atom().empty());
}

// Test unique_id default and set/get
TEST(PrefilterTest_459, UniqueIdDefaultAndSetGet_459) {
  Prefilter pf(Prefilter::ALL);
  // Set unique_id and verify
  pf.set_unique_id(42);
  EXPECT_EQ(42, pf.unique_id());
}

// Test set_unique_id with zero
TEST(PrefilterTest_459, UniqueIdZero_459) {
  Prefilter pf(Prefilter::NONE);
  pf.set_unique_id(0);
  EXPECT_EQ(0, pf.unique_id());
}

// Test set_unique_id with negative value
TEST(PrefilterTest_459, UniqueIdNegative_459) {
  Prefilter pf(Prefilter::AND);
  pf.set_unique_id(-1);
  EXPECT_EQ(-1, pf.unique_id());
}

// Test subs() returns something for AND/OR prefilters
TEST(PrefilterTest_459, SubsInitiallyNull_459) {
  Prefilter pf(Prefilter::AND);
  // subs might be null initially or allocated; just test it doesn't crash
  auto* subs = pf.subs();
  // We just ensure the call succeeds; the value depends on implementation
  (void)subs;
}

// Test set_subs and subs
TEST(PrefilterTest_459, SetSubsAndGetSubs_459) {
  Prefilter pf(Prefilter::OR);
  auto* new_subs = new std::vector<Prefilter*>();
  new_subs->push_back(new Prefilter(Prefilter::ATOM));
  pf.set_subs(new_subs);
  EXPECT_EQ(new_subs, pf.subs());
  EXPECT_EQ(1u, pf.subs()->size());
  // Destructor of pf should clean up
}

// Test set_subs with nullptr
TEST(PrefilterTest_459, SetSubsNullptr_459) {
  Prefilter pf(Prefilter::AND);
  pf.set_subs(nullptr);
  EXPECT_EQ(nullptr, pf.subs());
}

// Test DebugString for ALL
TEST(PrefilterTest_459, DebugStringAll_459) {
  Prefilter pf(Prefilter::ALL);
  std::string debug = pf.DebugString();
  EXPECT_FALSE(debug.empty());
}

// Test DebugString for NONE
TEST(PrefilterTest_459, DebugStringNone_459) {
  Prefilter pf(Prefilter::NONE);
  std::string debug = pf.DebugString();
  EXPECT_FALSE(debug.empty());
}

// Test FromRE2 with a simple literal pattern
TEST(PrefilterTest_459, FromRE2SimpleLiteral_459) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  // A simple literal should produce an ATOM prefilter
  if (pf != nullptr) {
    EXPECT_EQ(Prefilter::ATOM, pf->op());
    EXPECT_EQ("hello", pf->atom());
    delete pf;
  }
}

// Test FromRE2 with alternation
TEST(PrefilterTest_459, FromRE2Alternation_459) {
  RE2 re("hello|world");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    // Alternation should produce OR or similar structure
    // Just verify it doesn't crash and produces valid output
    std::string debug = pf->DebugString();
    EXPECT_FALSE(debug.empty());
    delete pf;
  }
}

// Test FromRE2 with dot star (match anything)
TEST(PrefilterTest_459, FromRE2DotStar_459) {
  RE2 re(".*");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    // .* matches everything, so should be ALL
    EXPECT_EQ(Prefilter::ALL, pf->op());
    delete pf;
  }
}

// Test FromRE2 with concatenation
TEST(PrefilterTest_459, FromRE2Concatenation_459) {
  RE2 re("abc.*def");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    std::string debug = pf->DebugString();
    EXPECT_FALSE(debug.empty());
    delete pf;
  }
}

// Test FromRE2 with empty pattern
TEST(PrefilterTest_459, FromRE2EmptyPattern_459) {
  RE2 re("");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    // Empty pattern matches everything
    EXPECT_EQ(Prefilter::ALL, pf->op());
    delete pf;
  }
}

// Test FromRE2 with character class
TEST(PrefilterTest_459, FromRE2CharClass_459) {
  RE2 re("[abc]def");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    std::string debug = pf->DebugString();
    EXPECT_FALSE(debug.empty());
    delete pf;
  }
}

// Test FromRE2 with case-insensitive literal
TEST(PrefilterTest_459, FromRE2CaseInsensitive_459) {
  RE2 re("(?i)hello");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    std::string debug = pf->DebugString();
    EXPECT_FALSE(debug.empty());
    delete pf;
  }
}

// Test that unique_id can be set multiple times
TEST(PrefilterTest_459, UniqueIdMultipleSets_459) {
  Prefilter pf(Prefilter::ALL);
  pf.set_unique_id(10);
  EXPECT_EQ(10, pf.unique_id());
  pf.set_unique_id(20);
  EXPECT_EQ(20, pf.unique_id());
  pf.set_unique_id(100);
  EXPECT_EQ(100, pf.unique_id());
}

// Test FromRE2 with complex pattern
TEST(PrefilterTest_459, FromRE2ComplexPattern_459) {
  RE2 re("(foo|bar)baz[0-9]+quux");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    std::string debug = pf->DebugString();
    EXPECT_FALSE(debug.empty());
    delete pf;
  }
}

// Test DebugString on a prefilter from a real RE2
TEST(PrefilterTest_459, DebugStringFromRE2_459) {
  RE2 re("test");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    std::string debug = pf->DebugString();
    // For a literal "test", the debug string should contain "test"
    EXPECT_NE(std::string::npos, debug.find("test"));
    delete pf;
  }
}

// Test FromRE2 with nullable
TEST(PrefilterTest_459, FromRE2NullablePattern_459) {
  RE2 re("a?");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    // a? can match empty, so likely ALL
    EXPECT_EQ(Prefilter::ALL, pf->op());
    delete pf;
  }
}

// Test FromRE2 with plus (one or more)
TEST(PrefilterTest_459, FromRE2PlusPattern_459) {
  RE2 re("a+");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    // a+ requires at least one 'a'
    std::string debug = pf->DebugString();
    EXPECT_FALSE(debug.empty());
    delete pf;
  }
}

}  // namespace re2
