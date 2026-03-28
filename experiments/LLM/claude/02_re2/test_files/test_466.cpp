#include "gtest/gtest.h"
#include "re2/prefilter.h"
#include "re2/re2.h"

namespace re2 {

class PrefilterTest_466 : public ::testing::Test {
 protected:
  void TearDown() override {
    for (auto* p : allocated_) {
      delete p;
    }
    allocated_.clear();
  }

  Prefilter* MakePrefilter(Prefilter::Op op) {
    Prefilter* p = new Prefilter(op);
    allocated_.push_back(p);
    return p;
  }

  // Helper: create an ATOM prefilter but we need to go through FromRE2
  // since atom_ is private. We'll use the public interface.
  std::vector<Prefilter*> allocated_;
};

// Test basic construction with different ops
TEST_F(PrefilterTest_466, ConstructWithALL_466) {
  Prefilter* p = MakePrefilter(Prefilter::ALL);
  EXPECT_EQ(p->op(), Prefilter::ALL);
}

TEST_F(PrefilterTest_466, ConstructWithNONE_466) {
  Prefilter* p = MakePrefilter(Prefilter::NONE);
  EXPECT_EQ(p->op(), Prefilter::NONE);
}

TEST_F(PrefilterTest_466, ConstructWithATOM_466) {
  Prefilter* p = MakePrefilter(Prefilter::ATOM);
  EXPECT_EQ(p->op(), Prefilter::ATOM);
}

TEST_F(PrefilterTest_466, ConstructWithAND_466) {
  Prefilter* p = MakePrefilter(Prefilter::AND);
  EXPECT_EQ(p->op(), Prefilter::AND);
}

TEST_F(PrefilterTest_466, ConstructWithOR_466) {
  Prefilter* p = MakePrefilter(Prefilter::OR);
  EXPECT_EQ(p->op(), Prefilter::OR);
}

// Test unique_id get/set
TEST_F(PrefilterTest_466, SetAndGetUniqueId_466) {
  Prefilter* p = MakePrefilter(Prefilter::ALL);
  p->set_unique_id(42);
  EXPECT_EQ(p->unique_id(), 42);
}

TEST_F(PrefilterTest_466, SetUniqueIdZero_466) {
  Prefilter* p = MakePrefilter(Prefilter::ALL);
  p->set_unique_id(0);
  EXPECT_EQ(p->unique_id(), 0);
}

TEST_F(PrefilterTest_466, SetUniqueIdNegative_466) {
  Prefilter* p = MakePrefilter(Prefilter::ALL);
  p->set_unique_id(-1);
  EXPECT_EQ(p->unique_id(), -1);
}

// Test operator== for identity (same object)
TEST_F(PrefilterTest_466, EqualitySameObject_466) {
  Prefilter* p = MakePrefilter(Prefilter::ALL);
  EXPECT_TRUE(*p == *p);
}

// Test operator== for ALL vs ALL
TEST_F(PrefilterTest_466, EqualityBothALL_466) {
  Prefilter* a = MakePrefilter(Prefilter::ALL);
  Prefilter* b = MakePrefilter(Prefilter::ALL);
  EXPECT_TRUE(*a == *b);
}

// Test operator== for NONE vs NONE
TEST_F(PrefilterTest_466, EqualityBothNONE_466) {
  Prefilter* a = MakePrefilter(Prefilter::NONE);
  Prefilter* b = MakePrefilter(Prefilter::NONE);
  EXPECT_TRUE(*a == *b);
}

// Test operator== for different ops
TEST_F(PrefilterTest_466, InequalityDifferentOps_466) {
  Prefilter* a = MakePrefilter(Prefilter::ALL);
  Prefilter* b = MakePrefilter(Prefilter::NONE);
  EXPECT_FALSE(*a == *b);
}

TEST_F(PrefilterTest_466, InequalityALLvsATOM_466) {
  Prefilter* a = MakePrefilter(Prefilter::ALL);
  Prefilter* b = MakePrefilter(Prefilter::ATOM);
  EXPECT_FALSE(*a == *b);
}

// Test FromRE2 with a simple literal pattern
TEST_F(PrefilterTest_466, FromRE2SimpleLiteral_466) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  // FromRE2 may return nullptr or a valid prefilter
  if (pf != nullptr) {
    // For a simple literal, we expect an ATOM
    EXPECT_EQ(pf->op(), Prefilter::ATOM);
    EXPECT_EQ(pf->atom(), "hello");
    delete pf;
  }
}

// Test FromRE2 with alternation
TEST_F(PrefilterTest_466, FromRE2Alternation_466) {
  RE2 re("hello|world");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    // For alternation, expect OR
    EXPECT_EQ(pf->op(), Prefilter::OR);
    delete pf;
  }
}

// Test FromRE2 with concatenation containing alternation
TEST_F(PrefilterTest_466, FromRE2Concatenation_466) {
  RE2 re("(foo)(bar)");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    // Could be AND or ATOM depending on simplification
    EXPECT_TRUE(pf->op() == Prefilter::AND || pf->op() == Prefilter::ATOM ||
                pf->op() == Prefilter::ALL);
    delete pf;
  }
}

// Test FromRE2 with dot star (matches everything)
TEST_F(PrefilterTest_466, FromRE2DotStar_466) {
  RE2 re(".*");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    // .* matches everything, so prefilter should be ALL
    EXPECT_EQ(pf->op(), Prefilter::ALL);
    delete pf;
  }
}

// Test FromRE2 with empty pattern
TEST_F(PrefilterTest_466, FromRE2EmptyPattern_466) {
  RE2 re("");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    EXPECT_EQ(pf->op(), Prefilter::ALL);
    delete pf;
  }
}

// Test DebugString doesn't crash for ALL
TEST_F(PrefilterTest_466, DebugStringALL_466) {
  Prefilter* p = MakePrefilter(Prefilter::ALL);
  std::string s = p->DebugString();
  EXPECT_FALSE(s.empty());
}

// Test DebugString doesn't crash for NONE
TEST_F(PrefilterTest_466, DebugStringNONE_466) {
  Prefilter* p = MakePrefilter(Prefilter::NONE);
  std::string s = p->DebugString();
  EXPECT_FALSE(s.empty());
}

// Test subs() and set_subs()
TEST_F(PrefilterTest_466, SubsGetSet_466) {
  Prefilter* p = MakePrefilter(Prefilter::AND);
  auto* subs = new std::vector<Prefilter*>();
  Prefilter* child1 = new Prefilter(Prefilter::ALL);
  Prefilter* child2 = new Prefilter(Prefilter::NONE);
  subs->push_back(child1);
  subs->push_back(child2);
  p->set_subs(subs);
  ASSERT_NE(p->subs(), nullptr);
  EXPECT_EQ(p->subs()->size(), 2u);
  // The destructor of p should handle cleanup of subs
  // Remove from allocated_ since set_subs ownership is taken
  // Actually, we need to be careful about double-free. The Prefilter dtor
  // should delete subs and their contents. So remove p from allocated_ and
  // handle manually, or let the destructor handle it.
  // Remove p from allocated_ to avoid double management issues.
  allocated_.erase(std::remove(allocated_.begin(), allocated_.end(), p),
                   allocated_.end());
  delete p;  // Should clean up subs vector and children
}

// Test operator== for AND with same subs unique_ids
TEST_F(PrefilterTest_466, EqualityANDSameSubsIds_466) {
  Prefilter* a = new Prefilter(Prefilter::AND);
  Prefilter* b = new Prefilter(Prefilter::AND);

  auto* subs_a = new std::vector<Prefilter*>();
  Prefilter* child_a1 = new Prefilter(Prefilter::ALL);
  child_a1->set_unique_id(10);
  Prefilter* child_a2 = new Prefilter(Prefilter::NONE);
  child_a2->set_unique_id(20);
  subs_a->push_back(child_a1);
  subs_a->push_back(child_a2);
  a->set_subs(subs_a);

  auto* subs_b = new std::vector<Prefilter*>();
  Prefilter* child_b1 = new Prefilter(Prefilter::ALL);
  child_b1->set_unique_id(10);
  Prefilter* child_b2 = new Prefilter(Prefilter::NONE);
  child_b2->set_unique_id(20);
  subs_b->push_back(child_b1);
  subs_b->push_back(child_b2);
  b->set_subs(subs_b);

  EXPECT_TRUE(*a == *b);

  delete a;
  delete b;
}

// Test operator== for AND with different subs unique_ids
TEST_F(PrefilterTest_466, InequalityANDDifferentSubsIds_466) {
  Prefilter* a = new Prefilter(Prefilter::AND);
  Prefilter* b = new Prefilter(Prefilter::AND);

  auto* subs_a = new std::vector<Prefilter*>();
  Prefilter* child_a1 = new Prefilter(Prefilter::ALL);
  child_a1->set_unique_id(10);
  subs_a->push_back(child_a1);
  a->set_subs(subs_a);

  auto* subs_b = new std::vector<Prefilter*>();
  Prefilter* child_b1 = new Prefilter(Prefilter::ALL);
  child_b1->set_unique_id(99);
  subs_b->push_back(child_b1);
  b->set_subs(subs_b);

  EXPECT_FALSE(*a == *b);

  delete a;
  delete b;
}

// Test operator== for AND with different number of subs
TEST_F(PrefilterTest_466, InequalityANDDifferentSubsCount_466) {
  Prefilter* a = new Prefilter(Prefilter::AND);
  Prefilter* b = new Prefilter(Prefilter::AND);

  auto* subs_a = new std::vector<Prefilter*>();
  Prefilter* child_a1 = new Prefilter(Prefilter::ALL);
  child_a1->set_unique_id(10);
  subs_a->push_back(child_a1);
  a->set_subs(subs_a);

  auto* subs_b = new std::vector<Prefilter*>();
  Prefilter* child_b1 = new Prefilter(Prefilter::ALL);
  child_b1->set_unique_id(10);
  Prefilter* child_b2 = new Prefilter(Prefilter::NONE);
  child_b2->set_unique_id(20);
  subs_b->push_back(child_b1);
  subs_b->push_back(child_b2);
  b->set_subs(subs_b);

  EXPECT_FALSE(*a == *b);

  delete a;
  delete b;
}

// Test operator== for OR with same subs
TEST_F(PrefilterTest_466, EqualityORSameSubsIds_466) {
  Prefilter* a = new Prefilter(Prefilter::OR);
  Prefilter* b = new Prefilter(Prefilter::OR);

  auto* subs_a = new std::vector<Prefilter*>();
  Prefilter* child_a1 = new Prefilter(Prefilter::ALL);
  child_a1->set_unique_id(5);
  subs_a->push_back(child_a1);
  a->set_subs(subs_a);

  auto* subs_b = new std::vector<Prefilter*>();
  Prefilter* child_b1 = new Prefilter(Prefilter::ALL);
  child_b1->set_unique_id(5);
  subs_b->push_back(child_b1);
  b->set_subs(subs_b);

  EXPECT_TRUE(*a == *b);

  delete a;
  delete b;
}

// Test FromRE2 with a more complex pattern
TEST_F(PrefilterTest_466, FromRE2ComplexPattern_466) {
  RE2 re("(abc|def).*ghi");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    // Should produce some meaningful prefilter
    std::string debug = pf->DebugString();
    EXPECT_FALSE(debug.empty());
    delete pf;
  }
}

// Test FromRE2 with character class
TEST_F(PrefilterTest_466, FromRE2CharClass_466) {
  RE2 re("[a-z]+");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    // Broad character class likely produces ALL
    EXPECT_EQ(pf->op(), Prefilter::ALL);
    delete pf;
  }
}

// Test atom() accessor
TEST_F(PrefilterTest_466, AtomAccessor_466) {
  RE2 re("specificword");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr && pf->op() == Prefilter::ATOM) {
    EXPECT_EQ(pf->atom(), "specificword");
    delete pf;
  } else if (pf != nullptr) {
    delete pf;
  }
}

// Test DebugString for a FromRE2-created prefilter
TEST_F(PrefilterTest_466, DebugStringFromRE2_466) {
  RE2 re("test");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    std::string debug = pf->DebugString();
    EXPECT_FALSE(debug.empty());
    delete pf;
  }
}

// Test AND with empty subs
TEST_F(PrefilterTest_466, EqualityANDEmptySubs_466) {
  Prefilter* a = new Prefilter(Prefilter::AND);
  Prefilter* b = new Prefilter(Prefilter::AND);

  auto* subs_a = new std::vector<Prefilter*>();
  auto* subs_b = new std::vector<Prefilter*>();
  a->set_subs(subs_a);
  b->set_subs(subs_b);

  EXPECT_TRUE(*a == *b);

  delete a;
  delete b;
}

// Test operator== with AND vs OR (same subs, different op)
TEST_F(PrefilterTest_466, InequalityANDvsOR_466) {
  Prefilter* a = new Prefilter(Prefilter::AND);
  Prefilter* b = new Prefilter(Prefilter::OR);

  auto* subs_a = new std::vector<Prefilter*>();
  Prefilter* child_a = new Prefilter(Prefilter::ALL);
  child_a->set_unique_id(1);
  subs_a->push_back(child_a);
  a->set_subs(subs_a);

  auto* subs_b = new std::vector<Prefilter*>();
  Prefilter* child_b = new Prefilter(Prefilter::ALL);
  child_b->set_unique_id(1);
  subs_b->push_back(child_b);
  b->set_subs(subs_b);

  EXPECT_FALSE(*a == *b);

  delete a;
  delete b;
}

}  // namespace re2
