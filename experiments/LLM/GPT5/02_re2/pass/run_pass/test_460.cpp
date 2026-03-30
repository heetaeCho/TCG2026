// File: prefilter_atom_test_460.cc
#include <type_traits>
#include <string>
#include "gtest/gtest.h"
#include "re2/prefilter.h"

namespace {

using re2::Prefilter;

class PrefilterAtomTest_460 : public ::testing::Test {};

TEST_F(PrefilterAtomTest_460, AtomReturnsConstReferenceType_460) {
  // Compile-time check: the function returns const std::string&.
  static_assert(std::is_same<decltype(std::declval<const Prefilter&>().atom()),
                             const std::string&>::value,
                "Prefilter::atom() must return const std::string&");
  SUCCEED();
}

TEST_F(PrefilterAtomTest_460, DefaultConstructedAtomIsEmpty_460) {
  // Construct with a dummy Op value without assuming its semantics.
  Prefilter pf(static_cast<Prefilter::Op>(0));
  EXPECT_TRUE(pf.atom().empty());
}

TEST_F(PrefilterAtomTest_460, RepeatedCallsReturnSameUnderlyingObject_460) {
  Prefilter pf(static_cast<Prefilter::Op>(0));
  const std::string* p1 = &pf.atom();
  const std::string* p2 = &pf.atom();
  EXPECT_EQ(p1, p2) << "atom() should return a stable reference to the same string";
}

TEST_F(PrefilterAtomTest_460, ReferenceStableThroughConstQualification_460) {
  Prefilter pf(static_cast<Prefilter::Op>(0));
  const Prefilter& cpf = pf;
  const std::string* p_from_nonconst = &pf.atom();
  const std::string* p_from_const = &cpf.atom();
  EXPECT_EQ(p_from_nonconst, p_from_const)
      << "atom() reference should be identical whether object is const or not";
}

}  // namespace
