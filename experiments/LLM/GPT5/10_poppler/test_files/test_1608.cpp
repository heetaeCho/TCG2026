// Decrypt_Mul0eTable_test_1608.cc

#include <gtest/gtest.h>

#include <cstdint>
#include <type_traits>
#include <array>

// Mul0eTable is defined in Decrypt.cc (no public header in the prompt).
// We include the implementation file to access the type without re-implementing it.
#if __has_include("Decrypt.cc")
#include "Decrypt.cc"
#elif __has_include("poppler/Decrypt.cc")
#include "poppler/Decrypt.cc"
#elif __has_include("../poppler/Decrypt.cc")
#include "../poppler/Decrypt.cc"
#elif __has_include("./TestProjects/poppler/poppler/Decrypt.cc")
#include "./TestProjects/poppler/poppler/Decrypt.cc"
#else
#error "Cannot find Decrypt.cc to access Mul0eTable for tests."
#endif

namespace {

class Mul0eTableTest_1608 : public ::testing::Test {};

TEST_F(Mul0eTableTest_1608, OperatorReturnTypeIsUnsignedChar_1608) {
  using RetT = decltype(std::declval<const Mul0eTable&>()(std::declval<uint8_t>()));
  static_assert(std::is_same_v<RetT, unsigned char>,
                "Mul0eTable::operator()(uint8_t) must return unsigned char");
  SUCCEED();
}

TEST_F(Mul0eTableTest_1608, DefaultConstructionAndBasicCallsDoNotCrash_1608) {
  const Mul0eTable table;

  // Basic sanity calls across a few points, including boundaries.
  (void)table(static_cast<uint8_t>(0));
  (void)table(static_cast<uint8_t>(1));
  (void)table(static_cast<uint8_t>(254));
  (void)table(static_cast<uint8_t>(255));

  SUCCEED();
}

TEST_F(Mul0eTableTest_1608, RepeatedCallsWithSameIndexAreDeterministic_1608) {
  const Mul0eTable table;

  const uint8_t indices[] = {0u, 1u, 2u, 127u, 128u, 254u, 255u};
  for (uint8_t i : indices) {
    const unsigned char v1 = table(i);
    const unsigned char v2 = table(i);
    const unsigned char v3 = table(i);
    EXPECT_EQ(v1, v2) << "Index=" << static_cast<unsigned int>(i);
    EXPECT_EQ(v2, v3) << "Index=" << static_cast<unsigned int>(i);
  }
}

TEST_F(Mul0eTableTest_1608, TwoIndependentlyConstructedTablesAgreeForAllInputs_1608) {
  const Mul0eTable a;
  const Mul0eTable b;

  for (unsigned int u = 0; u < 256u; ++u) {
    const auto i = static_cast<uint8_t>(u);
    EXPECT_EQ(a(i), b(i)) << "Index=" << u;
  }
}

TEST_F(Mul0eTableTest_1608, ValuesAreStableAcrossCopiesForAllInputs_1608) {
  const Mul0eTable original;
  const Mul0eTable copied = original;

  for (unsigned int u = 0; u < 256u; ++u) {
    const auto i = static_cast<uint8_t>(u);
    EXPECT_EQ(original(i), copied(i)) << "Index=" << u;
  }
}

TEST_F(Mul0eTableTest_1608, BoundaryIndicesAreConsistentAcrossInstances_1608) {
  const Mul0eTable t1;
  const Mul0eTable t2;

  const unsigned char t1_0 = t1(static_cast<uint8_t>(0));
  const unsigned char t2_0 = t2(static_cast<uint8_t>(0));
  EXPECT_EQ(t1_0, t2_0);

  const unsigned char t1_255 = t1(static_cast<uint8_t>(255));
  const unsigned char t2_255 = t2(static_cast<uint8_t>(255));
  EXPECT_EQ(t1_255, t2_255);
}

TEST_F(Mul0eTableTest_1608, ExhaustiveDeterminismWithinOneInstance_1608) {
  const Mul0eTable table;

  std::array<unsigned char, 256> first{};
  for (unsigned int u = 0; u < 256u; ++u) {
    first[u] = table(static_cast<uint8_t>(u));
  }

  // Verify repeating the full sweep produces identical outputs.
  for (unsigned int u = 0; u < 256u; ++u) {
    const unsigned char again = table(static_cast<uint8_t>(u));
    EXPECT_EQ(first[u], again) << "Index=" << u;
  }
}

}  // namespace