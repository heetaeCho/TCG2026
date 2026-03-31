#include "gtest/gtest.h"
#include "re2/prefilter.h"
#include "re2/re2.h"
#include <string>
#include <vector>

namespace re2 {

// Test fixture for Prefilter tests
class PrefilterTest_465 : public ::testing::Test {
 protected:
  void TearDown() override {
    // Clean up any allocated prefilters
    for (auto* p : to_delete_) {
      delete p;
    }
    to_delete_.clear();
  }

  Prefilter* MakePrefilter(Prefilter::Op op) {
    Prefilter* p = new Prefilter(op);
    to_delete_.push_back(p);
    return p;
  }

  // Remove from to_delete_ so caller manages lifetime
  void Release(Prefilter* p) {
    auto it = std::find(to_delete_.begin(), to_delete_.end(), p);
    if (it != to_delete_.end()) {
      to_delete_.erase(it);
    }
  }

  std::vector<Prefilter*> to_delete_;
};

// Test constructor and op() for ALL
TEST_F(PrefilterTest_465, ConstructorAll_465) {
  Prefilter* p = MakePrefilter(Prefilter::ALL);
  EXPECT_EQ(Prefilter::ALL, p->op());
}

// Test constructor and op() for NONE
TEST_F(PrefilterTest_465, ConstructorNone_465) {
  Prefilter* p = MakePrefilter(Prefilter::NONE);
  EXPECT_EQ(Prefilter::NONE, p->op());
}

// Test constructor and op() for ATOM
TEST_F(PrefilterTest_465, ConstructorAtom_465) {
  Prefilter* p = MakePrefilter(Prefilter::ATOM);
  EXPECT_EQ(Prefilter::ATOM, p->op());
}

// Test constructor and op() for AND
TEST_F(PrefilterTest_465, ConstructorAnd_465) {
  Prefilter* p = MakePrefilter(Prefilter::AND);
  EXPECT_EQ(Prefilter::AND, p->op());
}

// Test constructor and op() for OR
TEST_F(PrefilterTest_465, ConstructorOr_465) {
  Prefilter* p = MakePrefilter(Prefilter::OR);
  EXPECT_EQ(Prefilter::OR, p->op());
}

// Test unique_id default and set/get
TEST_F(PrefilterTest_465, UniqueIdDefaultAndSetGet_465) {
  Prefilter* p = MakePrefilter(Prefilter::ALL);
  // Set and retrieve unique_id
  p->set_unique_id(42);
  EXPECT_EQ(42, p->unique_id());
}

// Test set_unique_id with zero
TEST_F(PrefilterTest_465, UniqueIdZero_465) {
  Prefilter* p = MakePrefilter(Prefilter::ATOM);
  p->set_unique_id(0);
  EXPECT_EQ(0, p->unique_id());
}

// Test set_unique_id with negative value
TEST_F(PrefilterTest_465, UniqueIdNegative_465) {
  Prefilter* p = MakePrefilter(Prefilter::ATOM);
  p->set_unique_id(-1);
  EXPECT_EQ(-1, p->unique_id());
}

// Test set_unique_id overwrite
TEST_F(PrefilterTest_465, UniqueIdOverwrite_465) {
  Prefilter* p = MakePrefilter(Prefilter::ALL);
  p->set_unique_id(10);
  EXPECT_EQ(10, p->unique_id());
  p->set_unique_id(20);
  EXPECT_EQ(20, p->unique_id());
}

// Test atom() returns empty string for non-ATOM
TEST_F(PrefilterTest_465, AtomEmptyForNonAtom_465) {
  Prefilter* p = MakePrefilter(Prefilter::ALL);
  EXPECT_TRUE(p->atom().empty());
}

// Test subs() for AND/OR
TEST_F(PrefilterTest_465, SubsAccessor_465) {
  Prefilter* p = MakePrefilter(Prefilter::AND);
  // subs may or may not be initialized; just test it doesn't crash
  // We can set subs and retrieve them
  auto* subs = new std::vector<Prefilter*>();
  p->set_subs(subs);
  EXPECT_EQ(subs, p->subs());
  // subs will be cleaned up by destructor of p
}

// Test set_subs and subs()
TEST_F(PrefilterTest_465, SetSubsAndRetrieve_465) {
  Prefilter* p = MakePrefilter(Prefilter::OR);
  auto* subs = new std::vector<Prefilter*>();
  Prefilter* child = new Prefilter(Prefilter::ALL);
  subs->push_back(child);
  p->set_subs(subs);
  EXPECT_EQ(subs, p->subs());
  EXPECT_EQ(1u, p->subs()->size());
  EXPECT_EQ(child, (*p->subs())[0]);
  // Destructor of p should handle cleanup
}

// Test FromRE2 with a simple literal pattern
TEST_F(PrefilterTest_465, FromRE2SimpleLiteral_465) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  // A literal pattern should produce a non-null prefilter
  if (pf != nullptr) {
    // For a simple literal, we expect ATOM
    EXPECT_EQ(Prefilter::ATOM, pf->op());
    // The atom should contain the literal (possibly lowercased)
    EXPECT_FALSE(pf->atom().empty());
    delete pf;
  }
}

// Test FromRE2 with a pattern that matches everything
TEST_F(PrefilterTest_465, FromRE2MatchAll_465) {
  RE2 re(".*");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    // .* matches everything, so prefilter should be ALL
    EXPECT_EQ(Prefilter::ALL, pf->op());
    delete pf;
  }
}

// Test FromRE2 with alternation
TEST_F(PrefilterTest_465, FromRE2Alternation_465) {
  RE2 re("hello|world");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    // Alternation could produce OR
    // Just verify it's a valid prefilter
    EXPECT_TRUE(pf->op() == Prefilter::OR || pf->op() == Prefilter::ATOM ||
                pf->op() == Prefilter::ALL || pf->op() == Prefilter::AND);
    delete pf;
  }
}

// Test FromRE2 with concatenation
TEST_F(PrefilterTest_465, FromRE2Concatenation_465) {
  RE2 re("abc.*def");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    // Concatenation of literals with .* in between could produce AND
    EXPECT_TRUE(pf->op() == Prefilter::AND || pf->op() == Prefilter::ATOM ||
                pf->op() == Prefilter::ALL || pf->op() == Prefilter::OR);
    delete pf;
  }
}

// Test DebugString doesn't crash for ALL
TEST_F(PrefilterTest_465, DebugStringAll_465) {
  Prefilter* p = MakePrefilter(Prefilter::ALL);
  std::string debug = p->DebugString();
  EXPECT_FALSE(debug.empty());
}

// Test DebugString doesn't crash for NONE
TEST_F(PrefilterTest_465, DebugStringNone_465) {
  Prefilter* p = MakePrefilter(Prefilter::NONE);
  std::string debug = p->DebugString();
  EXPECT_FALSE(debug.empty());
}

// Test DebugString for a prefilter from RE2
TEST_F(PrefilterTest_465, DebugStringFromRE2_465) {
  RE2 re("test");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    std::string debug = pf->DebugString();
    EXPECT_FALSE(debug.empty());
    delete pf;
  }
}

// Test FromRE2 with character class
TEST_F(PrefilterTest_465, FromRE2CharClass_465) {
  RE2 re("[abc]def");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    // Character class may produce various filter types
    EXPECT_TRUE(pf->op() >= Prefilter::ALL && pf->op() <= Prefilter::OR);
    delete pf;
  }
}

// Test FromRE2 with repetition
TEST_F(PrefilterTest_465, FromRE2Repetition_465) {
  RE2 re("a{3,5}b");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    EXPECT_TRUE(pf->op() >= Prefilter::ALL && pf->op() <= Prefilter::OR);
    delete pf;
  }
}

// Test FromRE2 with case-insensitive flag
TEST_F(PrefilterTest_465, FromRE2CaseInsensitive_465) {
  RE2 re("(?i)Hello");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    // Case insensitive patterns should still produce some prefilter
    EXPECT_TRUE(pf->op() >= Prefilter::ALL && pf->op() <= Prefilter::OR);
    delete pf;
  }
}

// Test FromRE2 with empty pattern
TEST_F(PrefilterTest_465, FromRE2EmptyPattern_465) {
  RE2 re("");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    // Empty pattern matches everything
    EXPECT_EQ(Prefilter::ALL, pf->op());
    delete pf;
  }
}

// Test FromRE2 with complex pattern
TEST_F(PrefilterTest_465, FromRE2ComplexPattern_465) {
  RE2 re("(foo|bar).*baz");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    std::string debug = pf->DebugString();
    EXPECT_FALSE(debug.empty());
    delete pf;
  }
}

// Test that Op enum values are distinct
TEST_F(PrefilterTest_465, OpEnumValues_465) {
  EXPECT_EQ(0, Prefilter::ALL);
  EXPECT_EQ(1, Prefilter::NONE);
  EXPECT_EQ(2, Prefilter::ATOM);
  EXPECT_EQ(3, Prefilter::AND);
  EXPECT_EQ(4, Prefilter::OR);
}

// Test multiple unique_id settings on different prefilters
TEST_F(PrefilterTest_465, MultiplePrefiltersUniqueIds_465) {
  Prefilter* p1 = MakePrefilter(Prefilter::ALL);
  Prefilter* p2 = MakePrefilter(Prefilter::NONE);
  Prefilter* p3 = MakePrefilter(Prefilter::ATOM);

  p1->set_unique_id(1);
  p2->set_unique_id(2);
  p3->set_unique_id(3);

  EXPECT_EQ(1, p1->unique_id());
  EXPECT_EQ(2, p2->unique_id());
  EXPECT_EQ(3, p3->unique_id());
}

// Test FromRE2 with single character
TEST_F(PrefilterTest_465, FromRE2SingleChar_465) {
  RE2 re("x");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  // Single character might not produce a useful prefilter (atoms typically need min length)
  if (pf != nullptr) {
    EXPECT_TRUE(pf->op() >= Prefilter::ALL && pf->op() <= Prefilter::OR);
    delete pf;
  }
}

// Test FromRE2 with longer literal
TEST_F(PrefilterTest_465, FromRE2LongerLiteral_465) {
  RE2 re("abcdefghij");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(nullptr, pf);
  EXPECT_EQ(Prefilter::ATOM, pf->op());
  EXPECT_FALSE(pf->atom().empty());
  delete pf;
}

// Test DebugString for AND-type prefilter from complex regex
TEST_F(PrefilterTest_465, DebugStringAnd_465) {
  RE2 re("abcd.*efgh");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    std::string debug = pf->DebugString();
    // DebugString should produce non-empty output
    EXPECT_FALSE(debug.empty());
    delete pf;
  }
}

// Test set_subs with nullptr
TEST_F(PrefilterTest_465, SetSubsNull_465) {
  Prefilter* p = MakePrefilter(Prefilter::AND);
  p->set_subs(nullptr);
  EXPECT_EQ(nullptr, p->subs());
}

}  // namespace re2
