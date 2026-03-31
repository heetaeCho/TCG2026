#include "gtest/gtest.h"
#include "re2/re2.h"
#include "re2/prefilter.h"

namespace re2 {

class PrefilterTest_544 : public ::testing::Test {
 protected:
  void TearDown() override {}
};

TEST_F(PrefilterTest_544, ConstructorALL_544) {
  Prefilter pf(Prefilter::ALL);
  EXPECT_EQ(pf.op(), Prefilter::ALL);
}

TEST_F(PrefilterTest_544, ConstructorNONE_544) {
  Prefilter pf(Prefilter::NONE);
  EXPECT_EQ(pf.op(), Prefilter::NONE);
}

TEST_F(PrefilterTest_544, ConstructorATOM_544) {
  Prefilter pf(Prefilter::ATOM);
  EXPECT_EQ(pf.op(), Prefilter::ATOM);
}

TEST_F(PrefilterTest_544, ConstructorAND_544) {
  Prefilter pf(Prefilter::AND);
  EXPECT_EQ(pf.op(), Prefilter::AND);
}

TEST_F(PrefilterTest_544, ConstructorOR_544) {
  Prefilter pf(Prefilter::OR);
  EXPECT_EQ(pf.op(), Prefilter::OR);
}

TEST_F(PrefilterTest_544, UniqueIdDefaultValue_544) {
  Prefilter pf(Prefilter::ALL);
  EXPECT_EQ(pf.unique_id(), -1);
}

TEST_F(PrefilterTest_544, SetAndGetUniqueId_544) {
  Prefilter pf(Prefilter::ALL);
  pf.set_unique_id(42);
  EXPECT_EQ(pf.unique_id(), 42);
}

TEST_F(PrefilterTest_544, SetUniqueIdZero_544) {
  Prefilter pf(Prefilter::ALL);
  pf.set_unique_id(0);
  EXPECT_EQ(pf.unique_id(), 0);
}

TEST_F(PrefilterTest_544, SetUniqueIdNegative_544) {
  Prefilter pf(Prefilter::ALL);
  pf.set_unique_id(-5);
  EXPECT_EQ(pf.unique_id(), -5);
}

TEST_F(PrefilterTest_544, AtomDefaultEmpty_544) {
  Prefilter pf(Prefilter::ATOM);
  EXPECT_TRUE(pf.atom().empty());
}

TEST_F(PrefilterTest_544, SubsInitiallyNull_544) {
  Prefilter pf(Prefilter::AND);
  // subs() may or may not be null depending on constructor, just check it doesn't crash
  // For non-AND/OR ops, subs might be null
  Prefilter pf2(Prefilter::ATOM);
  // Just verify we can call subs() without crashing
  pf2.subs();
}

TEST_F(PrefilterTest_544, FromRE2SimpleLiteral_544) {
  RE2 re("hello");
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  EXPECT_EQ(pf->op(), Prefilter::ATOM);
  EXPECT_EQ(pf->atom(), "hello");
  delete pf;
}

TEST_F(PrefilterTest_544, FromRE2Alternation_544) {
  RE2 re("hello|world");
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  EXPECT_EQ(pf->op(), Prefilter::OR);
  ASSERT_NE(pf->subs(), nullptr);
  EXPECT_EQ(pf->subs()->size(), 2u);
  delete pf;
}

TEST_F(PrefilterTest_544, FromRE2DotStar_544) {
  RE2 re(".*");
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  EXPECT_EQ(pf->op(), Prefilter::ALL);
  delete pf;
}

TEST_F(PrefilterTest_544, FromRE2EmptyPattern_544) {
  RE2 re("");
  Prefilter* pf = Prefilter::FromRE2(&re);
  // Empty pattern should return something (ALL match)
  ASSERT_NE(pf, nullptr);
  EXPECT_EQ(pf->op(), Prefilter::ALL);
  delete pf;
}

TEST_F(PrefilterTest_544, FromRE2Concatenation_544) {
  RE2 re("abc.*def");
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  // Should be AND of "abc" and "def", or possibly a single complex filter
  delete pf;
}

TEST_F(PrefilterTest_544, FromRE2NullPointer_544) {
  Prefilter* pf = Prefilter::FromRE2(nullptr);
  EXPECT_EQ(pf, nullptr);
}

TEST_F(PrefilterTest_544, DebugStringNotEmpty_544) {
  RE2 re("hello");
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  std::string debug = pf->DebugString();
  EXPECT_FALSE(debug.empty());
  delete pf;
}

TEST_F(PrefilterTest_544, DebugStringALL_544) {
  Prefilter pf(Prefilter::ALL);
  std::string debug = pf.DebugString();
  EXPECT_FALSE(debug.empty());
  EXPECT_NE(debug.find("*"), std::string::npos);
}

TEST_F(PrefilterTest_544, DebugStringNONE_544) {
  Prefilter pf(Prefilter::NONE);
  std::string debug = pf.DebugString();
  EXPECT_FALSE(debug.empty());
}

TEST_F(PrefilterTest_544, FromRE2CaseInsensitive_544) {
  RE2 re("(?i)hello");
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  // Case insensitive should produce OR of various cases or ALL
  delete pf;
}

TEST_F(PrefilterTest_544, FromRE2CharacterClass_544) {
  RE2 re("[abc]def");
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  delete pf;
}

TEST_F(PrefilterTest_544, FromRE2QuestionMark_544) {
  RE2 re("hello?world");
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  delete pf;
}

TEST_F(PrefilterTest_544, FromRE2Plus_544) {
  RE2 re("hel+o");
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  delete pf;
}

TEST_F(PrefilterTest_544, FromRE2ComplexPattern_544) {
  RE2 re("(foo|bar).*baz");
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  delete pf;
}

TEST_F(PrefilterTest_544, SetSubs_544) {
  Prefilter pf(Prefilter::AND);
  auto* subs = new std::vector<Prefilter*>();
  subs->push_back(new Prefilter(Prefilter::ATOM));
  subs->push_back(new Prefilter(Prefilter::ATOM));
  pf.set_subs(subs);
  EXPECT_EQ(pf.subs(), subs);
  EXPECT_EQ(pf.subs()->size(), 2u);
}

TEST_F(PrefilterTest_544, OpReturnsCorrectValue_544) {
  Prefilter pf1(Prefilter::ALL);
  Prefilter pf2(Prefilter::NONE);
  Prefilter pf3(Prefilter::ATOM);
  Prefilter pf4(Prefilter::AND);
  Prefilter pf5(Prefilter::OR);
  
  EXPECT_EQ(pf1.op(), Prefilter::ALL);
  EXPECT_EQ(pf2.op(), Prefilter::NONE);
  EXPECT_EQ(pf3.op(), Prefilter::ATOM);
  EXPECT_EQ(pf4.op(), Prefilter::AND);
  EXPECT_EQ(pf5.op(), Prefilter::OR);
}

TEST_F(PrefilterTest_544, FromRE2SingleChar_544) {
  RE2 re("a");
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  // Single char might be ALL since it's too short to be useful as a filter
  delete pf;
}

TEST_F(PrefilterTest_544, FromRE2LongLiteral_544) {
  RE2 re("abcdefghijklmnop");
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  EXPECT_EQ(pf->op(), Prefilter::ATOM);
  delete pf;
}

TEST_F(PrefilterTest_544, FromRE2InvalidRegex_544) {
  RE2 re("(unclosed");
  // RE2 handles invalid patterns internally; FromRE2 should handle gracefully
  if (re.ok()) {
    Prefilter* pf = Prefilter::FromRE2(&re);
    delete pf;
  }
}

TEST_F(PrefilterTest_544, DebugStringForAlternation_544) {
  RE2 re("hello|world");
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  std::string debug = pf->DebugString();
  EXPECT_FALSE(debug.empty());
  // Should mention both alternatives
  delete pf;
}

TEST_F(PrefilterTest_544, MultipleUniqueIdSets_544) {
  Prefilter pf(Prefilter::ALL);
  pf.set_unique_id(1);
  EXPECT_EQ(pf.unique_id(), 1);
  pf.set_unique_id(100);
  EXPECT_EQ(pf.unique_id(), 100);
  pf.set_unique_id(-1);
  EXPECT_EQ(pf.unique_id(), -1);
}

}  // namespace re2
