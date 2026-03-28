// File: prefilter_set_subs_test_464.cc

#include "re2/prefilter.h"
#include <gtest/gtest.h>
#include <vector>

namespace re2 {

class PrefilterTest_464 : public ::testing::Test {
protected:
  // We don't assume anything about valid Op values beyond type existence.
  // Using 0 via static_cast keeps us from inferring any internal meaning.
  static Prefilter MakeDefaultPrefilter() {
    return Prefilter(static_cast<Op>(0));
  }
};

// [Normal] Setting a valid (non-null) vector pointer is reflected by subs().
TEST(PrefilterTest_464, SetSubsStoresPointer_464) {
  Prefilter pf = PrefilterTest_464::MakeDefaultPrefilter();
  std::vector<Prefilter*> vec;  // contents don't matter; we won't dereference elements
  vec.push_back(nullptr);       // ensure non-empty to cover a typical case

  pf.set_subs(&vec);

  ASSERT_NE(nullptr, pf.subs());
  EXPECT_EQ(&vec, pf.subs());
  EXPECT_EQ(vec.size(), pf.subs()->size());  // observable aliasing of the same vector
}

// [Boundary] Setting nullptr clears/sets the pointer; subs() returns nullptr.
TEST(PrefilterTest_464, SetSubsToNullptr_464) {
  Prefilter pf = PrefilterTest_464::MakeDefaultPrefilter();

  pf.set_subs(nullptr);

  EXPECT_EQ(nullptr, pf.subs());
}

// [Boundary] Setting to an empty vector pointer is accepted and observable.
TEST(PrefilterTest_464, SetSubsEmptyVector_464) {
  Prefilter pf = PrefilterTest_464::MakeDefaultPrefilter();
  std::vector<Prefilter*> empty;

  pf.set_subs(&empty);

  ASSERT_NE(nullptr, pf.subs());
  EXPECT_EQ(&empty, pf.subs());
  EXPECT_TRUE(pf.subs()->empty());
}

// [Normal] Re-assigning with a different pointer updates the observable pointer.
TEST(PrefilterTest_464, ReassignsToDifferentPointer_464) {
  Prefilter pf = PrefilterTest_464::MakeDefaultPrefilter();
  std::vector<Prefilter*> first, second;
  first.push_back(nullptr);

  pf.set_subs(&first);
  ASSERT_EQ(&first, pf.subs());

  pf.set_subs(&second);
  EXPECT_EQ(&second, pf.subs());
  EXPECT_NE(&first, pf.subs());
}

// [Boundary/Stress-lite] Large vector aliasing remains observable via size().
TEST(PrefilterTest_464, LargeVectorAliasingObservable_464) {
  Prefilter pf = PrefilterTest_464::MakeDefaultPrefilter();
  std::vector<Prefilter*> large;
  // Populate with many nullptrs; elements are not dereferenced.
  const size_t kN = 1000;
  large.reserve(kN);
  for (size_t i = 0; i < kN; ++i) large.push_back(nullptr);

  pf.set_subs(&large);

  ASSERT_NE(nullptr, pf.subs());
  EXPECT_EQ(&large, pf.subs());
  EXPECT_EQ(kN, pf.subs()->size());

  // Mutate the aliased vector and observe the change through subs()
  large.push_back(nullptr);
  EXPECT_EQ(kN + 1, pf.subs()->size());
}

}  // namespace re2
