// File: prefilter_eq_test.cc
#include <gtest/gtest.h>
#include "re2/prefilter.h"

using re2::Prefilter;

// Small helper to build a sub-prefilter with a specific unique_id.
static Prefilter* MakeNode(Prefilter::Op op, int id) {
  Prefilter* n = new Prefilter(op);
  n->set_unique_id(id);
  return n;
}

// Ensures vectors allocated via new are cleaned up.
static void DeleteVec(std::vector<Prefilter*>* v) {
  if (!v) return;
  for (auto* p : *v) delete p;
  delete v;
}

// ---------- Tests ----------

TEST(PrefilterEqualityTest_466, PointerEquality_466) {
  Prefilter a(Prefilter::ALL);
  // Same object (address) must be equal.
  EXPECT_TRUE(a == a);
}

TEST(PrefilterEqualityTest_466, DifferentOpNotEqual_466) {
  Prefilter all_node(Prefilter::ALL);
  Prefilter none_node(Prefilter::NONE);
  EXPECT_FALSE(all_node == none_node);
}

TEST(PrefilterEqualityTest_466, SameSimpleOpEqual_466) {
  // For ops other than ATOM/AND/OR, equality depends only on op.
  Prefilter a1(Prefilter::ALL);
  Prefilter a2(Prefilter::ALL);
  EXPECT_TRUE(a1 == a2);

  Prefilter n1(Prefilter::NONE);
  Prefilter n2(Prefilter::NONE);
  EXPECT_TRUE(n1 == n2);
}

TEST(PrefilterEqualityTest_466, AtomWithDefaultAtomStringEqual_466) {
  // We cannot set the atom value via the public interface.
  // Two ATOM nodes constructed the same way should compare equal.
  Prefilter x(Prefilter::ATOM);
  Prefilter y(Prefilter::ATOM);
  EXPECT_TRUE(x == y);
}

TEST(PrefilterEqualityTest_466, AndEqualWhenSameSubIdsAndOrder_466) {
  Prefilter a(Prefilter::AND);
  Prefilter b(Prefilter::AND);

  auto* subs1 = new std::vector<Prefilter*>();
  auto* subs2 = new std::vector<Prefilter*>();

  subs1->push_back(MakeNode(Prefilter::ALL,  10));
  subs1->push_back(MakeNode(Prefilter::NONE, 20));
  subs1->push_back(MakeNode(Prefilter::ATOM, 30));

  // Same unique_ids in the same order.
  subs2->push_back(MakeNode(Prefilter::ALL,  10));
  subs2->push_back(MakeNode(Prefilter::NONE, 20));
  subs2->push_back(MakeNode(Prefilter::ATOM, 30));

  a.set_subs(subs1);
  b.set_subs(subs2);

  EXPECT_TRUE(a == b);

  // Clean up
  DeleteVec(a.subs());
  DeleteVec(b.subs());
}

TEST(PrefilterEqualityTest_466, AndNotEqualWhenDifferentSizes_466) {
  Prefilter a(Prefilter::AND);
  Prefilter b(Prefilter::AND);

  auto* subs1 = new std::vector<Prefilter*>();
  auto* subs2 = new std::vector<Prefilter*>();

  subs1->push_back(MakeNode(Prefilter::ALL, 10));
  subs1->push_back(MakeNode(Prefilter::NONE, 20));

  // Same ids but fewer elements.
  subs2->push_back(MakeNode(Prefilter::ALL, 10));

  a.set_subs(subs1);
  b.set_subs(subs2);

  EXPECT_FALSE(a == b);

  DeleteVec(a.subs());
  DeleteVec(b.subs());
}

TEST(PrefilterEqualityTest_466, AndNotEqualWhenSubIdMismatch_466) {
  Prefilter a(Prefilter::AND);
  Prefilter b(Prefilter::AND);

  auto* subs1 = new std::vector<Prefilter*>();
  auto* subs2 = new std::vector<Prefilter*>();

  subs1->push_back(MakeNode(Prefilter::ALL, 10));
  subs1->push_back(MakeNode(Prefilter::NONE, 20));

  // Second element has a different unique_id.
  subs2->push_back(MakeNode(Prefilter::ALL, 10));
  subs2->push_back(MakeNode(Prefilter::NONE, 99));

  a.set_subs(subs1);
  b.set_subs(subs2);

  EXPECT_FALSE(a == b);

  DeleteVec(a.subs());
  DeleteVec(b.subs());
}

TEST(PrefilterEqualityTest_466, OrOrderMatters_466) {
  Prefilter a(Prefilter::OR);
  Prefilter b(Prefilter::OR);

  auto* subs1 = new std::vector<Prefilter*>();
  auto* subs2 = new std::vector<Prefilter*>();

  // Same ids, different order.
  subs1->push_back(MakeNode(Prefilter::ATOM, 1));
  subs1->push_back(MakeNode(Prefilter::ATOM, 2));

  subs2->push_back(MakeNode(Prefilter::ATOM, 2));
  subs2->push_back(MakeNode(Prefilter::ATOM, 1));

  a.set_subs(subs1);
  b.set_subs(subs2);

  EXPECT_FALSE(a == b);

  DeleteVec(a.subs());
  DeleteVec(b.subs());
}

TEST(PrefilterEqualityTest_466, AndEmptySubsVectorsEqual_466) {
  Prefilter a(Prefilter::AND);
  Prefilter b(Prefilter::AND);

  auto* empty1 = new std::vector<Prefilter*>();
  auto* empty2 = new std::vector<Prefilter*>();
  a.set_subs(empty1);
  b.set_subs(empty2);

  EXPECT_TRUE(a == b);

  DeleteVec(a.subs());
  DeleteVec(b.subs());
}
