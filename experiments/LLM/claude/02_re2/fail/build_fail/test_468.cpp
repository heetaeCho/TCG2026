#include "gtest/gtest.h"
#include "re2/prefilter_tree.h"
#include "re2/prefilter.h"
#include "re2/re2.h"

namespace re2 {

// Test fixture for PrefilterTree::PrefilterHash
class PrefilterHashTest_468 : public ::testing::Test {
 protected:
  PrefilterTree::PrefilterHash hasher_;
};

// Test that hashing a valid Prefilter with NONE op produces a consistent result
TEST_F(PrefilterHashTest_468, HashConsistentForSamePrefilter_468) {
  Prefilter pf(Prefilter::ALL);
  size_t hash1 = hasher_(&pf);
  size_t hash2 = hasher_(&pf);
  EXPECT_EQ(hash1, hash2);
}

// Test that two Prefilters with the same op produce the same hash
TEST_F(PrefilterHashTest_468, SameOpProducesSameHash_468) {
  Prefilter pf1(Prefilter::ALL);
  Prefilter pf2(Prefilter::ALL);
  EXPECT_EQ(hasher_(&pf1), hasher_(&pf2));
}

// Test that two Prefilters with different ops may produce different hashes
TEST_F(PrefilterHashTest_468, DifferentOpMayProduceDifferentHash_468) {
  Prefilter pf_all(Prefilter::ALL);
  Prefilter pf_none(Prefilter::NONE);
  // While hash collisions are possible, for distinct types we expect
  // different hashes in practice. This is a best-effort test.
  size_t hash_all = hasher_(&pf_all);
  size_t hash_none = hasher_(&pf_none);
  // We just verify they return without error; equality is not guaranteed
  // but we note them for coverage
  (void)hash_all;
  (void)hash_none;
}

// Test hashing Prefilters created from RE2 patterns
TEST_F(PrefilterHashTest_468, HashFromRE2Prefilter_468) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    size_t h1 = hasher_(pf);
    size_t h2 = hasher_(pf);
    EXPECT_EQ(h1, h2);
    delete pf;
  }
}

// Test that two Prefilters from the same pattern produce the same hash
TEST_F(PrefilterHashTest_468, SamePatternProducesSameHash_468) {
  RE2 re1("world");
  RE2 re2("world");
  ASSERT_TRUE(re1.ok());
  ASSERT_TRUE(re2.ok());
  Prefilter* pf1 = Prefilter::FromRE2(&re1);
  Prefilter* pf2 = Prefilter::FromRE2(&re2);
  if (pf1 != nullptr && pf2 != nullptr) {
    EXPECT_EQ(hasher_(pf1), hasher_(pf2));
  }
  delete pf1;
  delete pf2;
}

// Test that Prefilters from different patterns may produce different hashes
TEST_F(PrefilterHashTest_468, DifferentPatternsHash_468) {
  RE2 re1("foo");
  RE2 re2("bar");
  ASSERT_TRUE(re1.ok());
  ASSERT_TRUE(re2.ok());
  Prefilter* pf1 = Prefilter::FromRE2(&re1);
  Prefilter* pf2 = Prefilter::FromRE2(&re2);
  if (pf1 != nullptr && pf2 != nullptr) {
    // Different atoms should generally produce different hashes
    // but collisions are technically possible
    size_t h1 = hasher_(pf1);
    size_t h2 = hasher_(pf2);
    // Just ensure they don't crash; we note them
    (void)h1;
    (void)h2;
  }
  delete pf1;
  delete pf2;
}

// Test that hashing with ATOM op and setting unique_id doesn't affect hash consistency
TEST_F(PrefilterHashTest_468, HashWithUniqueIdDoesNotCrash_468) {
  Prefilter pf(Prefilter::ALL);
  pf.set_unique_id(42);
  size_t h1 = hasher_(&pf);
  pf.set_unique_id(99);
  size_t h2 = hasher_(&pf);
  // unique_id may or may not affect hash; just verify no crash
  (void)h1;
  (void)h2;
}

// Test hashing NONE type prefilter
TEST_F(PrefilterHashTest_468, HashNonePrefilter_468) {
  Prefilter pf(Prefilter::NONE);
  size_t h = hasher_(&pf);
  // Just verify it returns a value without crashing
  (void)h;
}

// Test hashing AND type prefilter
TEST_F(PrefilterHashTest_468, HashAndPrefilter_468) {
  Prefilter pf(Prefilter::AND);
  auto* subs = new std::vector<Prefilter*>();
  subs->push_back(new Prefilter(Prefilter::ALL));
  pf.set_subs(subs);
  size_t h = hasher_(&pf);
  (void)h;
}

// Test hashing OR type prefilter
TEST_F(PrefilterHashTest_468, HashOrPrefilter_468) {
  Prefilter pf(Prefilter::OR);
  auto* subs = new std::vector<Prefilter*>();
  subs->push_back(new Prefilter(Prefilter::ALL));
  pf.set_subs(subs);
  size_t h = hasher_(&pf);
  (void)h;
}

}  // namespace re2
