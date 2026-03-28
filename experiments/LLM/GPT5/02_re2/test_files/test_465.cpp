// File: prefilter_hash_test_465.cc

#include "re2/prefilter.h"
#include "gtest/gtest.h"
#include "absl/hash/hash.h"

using ::re2::Prefilter;

namespace {

// Helper to compute hash via Abseil's hashing API.
static size_t HashOf(const Prefilter& p) {
  return absl::Hash<Prefilter>{}(p);
}

// Fixture to centralize cleanup of heap-allocated helpers when needed.
class PrefilterHashTest_465 : public ::testing::Test {
 protected:
  // Utility to create a heap std::vector<Prefilter*> and hand ownership to the caller.
  static std::vector<Prefilter*>* MakeSubs(std::initializer_list<Prefilter*> init) {
    auto* v = new std::vector<Prefilter*>();
    v->insert(v->end(), init.begin(), init.end());
    return v;
  }
};

}  // namespace

// Normal case: same op (no subs) => same hash.
TEST_F(PrefilterHashTest_465, SameOpNoSubs_ProducesSameHash_465) {
  Prefilter a(Prefilter::ALL);
  Prefilter b(Prefilter::ALL);

  EXPECT_EQ(HashOf(a), HashOf(b));
}

// Normal case: different ops => (very likely) different hashes.
// We assert inequality to verify op participates in hashing.
TEST_F(PrefilterHashTest_465, DifferentOps_ProduceDifferentHashes_465) {
  Prefilter a(Prefilter::ALL);
  Prefilter b(Prefilter::NONE);

  EXPECT_NE(HashOf(a), HashOf(b));
}

// ATOM path: without touching internal state, two default-constructed ATOMs
// should hash the same (atom string not set via public API).
TEST_F(PrefilterHashTest_465, Atom_DefaultAtomsHashEqual_465) {
  Prefilter a(Prefilter::ATOM);
  Prefilter b(Prefilter::ATOM);

  EXPECT_EQ(HashOf(a), HashOf(b));
}

// AND path: size of subs and each child's unique_id participate in the hash.
// Changing a child's unique_id should change the parent's hash.
TEST_F(PrefilterHashTest_465, And_ChildIdAffectsHash_465) {
  Prefilter c1(Prefilter::ALL);
  Prefilter c2(Prefilter::NONE);
  c1.set_unique_id(1);
  c2.set_unique_id(2);

  Prefilter and_node(Prefilter::AND);
  auto* subs = PrefilterHashTest_465::MakeSubs({&c1, &c2});
  and_node.set_subs(subs);

  const size_t h1 = HashOf(and_node);

  // Change an observable field (unique_id) of a child referenced via subs.
  c1.set_unique_id(42);
  const size_t h2 = HashOf(and_node);

  EXPECT_NE(h1, h2);

  delete subs;
}

// AND path: order of subs is observable through the public set_subs API,
// and hashing iterates in order; different order => different hash.
TEST_F(PrefilterHashTest_465, And_OrderOfSubsMatters_465) {
  Prefilter c1(Prefilter::ALL);
  Prefilter c2(Prefilter::NONE);
  c1.set_unique_id(7);
  c2.set_unique_id(8);

  Prefilter a1(Prefilter::AND);
  Prefilter a2(Prefilter::AND);

  auto* subs12 = PrefilterHashTest_465::MakeSubs({&c1, &c2});
  auto* subs21 = PrefilterHashTest_465::MakeSubs({&c2, &c1});

  a1.set_subs(subs12);
  a2.set_subs(subs21);

  EXPECT_NE(HashOf(a1), HashOf(a2));

  delete subs12;
  delete subs21;
}

// Boundary: empty subs vector is allowed and should produce a stable hash
// that matches another AND node with empty subs.
TEST_F(PrefilterHashTest_465, And_EmptySubsStableAndEqual_465) {
  Prefilter a(Prefilter::AND);
  Prefilter b(Prefilter::AND);

  auto* empty1 = PrefilterHashTest_465::MakeSubs({});
  auto* empty2 = PrefilterHashTest_465::MakeSubs({});

  a.set_subs(empty1);
  b.set_subs(empty2);

  EXPECT_EQ(HashOf(a), HashOf(b));

  delete empty1;
  delete empty2;
}

// OR path mirrors AND semantics: size and child unique_ids affect the hash.
TEST_F(PrefilterHashTest_465, Or_ChildSetAffectsHash_465) {
  Prefilter c1(Prefilter::ALL);
  Prefilter c2(Prefilter::NONE);
  c1.set_unique_id(100);
  c2.set_unique_id(200);

  Prefilter or_node(Prefilter::OR);
  auto* subs = PrefilterHashTest_465::MakeSubs({&c1, &c2});
  or_node.set_subs(subs);

  const size_t h1 = HashOf(or_node);

  // Change subs size (observable via set_subs) -> hash should change.
  auto* subs_single = PrefilterHashTest_465::MakeSubs({&c1});
  or_node.set_subs(subs_single);
  const size_t h2 = HashOf(or_node);

  EXPECT_NE(h1, h2);

  delete subs;
  delete subs_single;
}
