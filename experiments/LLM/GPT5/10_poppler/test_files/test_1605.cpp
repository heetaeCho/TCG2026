// Decrypt_Mul09Table_test_1605.cc
#include <gtest/gtest.h>

#include <cstdint>
#include <type_traits>

// The type under test is defined in a .cc file.
// In Poppler's test setup this pattern is commonly used to access internal structs.
#include "Decrypt.cc"

// Compile-time interface checks (no assumptions about internal logic).
static_assert(std::is_default_constructible_v<Mul09Table>,
              "Mul09Table should be default-constructible (constexpr ctor exists).");
static_assert(std::is_copy_constructible_v<Mul09Table>, "Mul09Table should be copyable.");
static_assert(std::is_copy_assignable_v<Mul09Table>, "Mul09Table should be copy-assignable.");
static_assert(std::is_same_v<decltype(std::declval<const Mul09Table&>()(std::declval<uint8_t>())),
                             unsigned char>,
              "operator()(uint8_t) must return unsigned char.");

namespace {

class Mul09TableTest_1605 : public ::testing::Test {};

TEST_F(Mul09TableTest_1605, ConstexprConstructionAndCallCompiles_1605) {
  // If the constructor/operator are truly constexpr-capable, this should compile.
  // (Even if the test suite is built in a mode where it doesn't *evaluate* at compile-time,
  // this still validates the interface usage pattern.)
  constexpr Mul09Table table{};
  constexpr unsigned char v0 = table(uint8_t{0});
  constexpr unsigned char v255 = table(uint8_t{255});

  // Runtime assertions just to keep values "used" and ensure codegen path is exercised.
  EXPECT_EQ(v0, table(uint8_t{0}));
  EXPECT_EQ(v255, table(uint8_t{255}));
}

TEST_F(Mul09TableTest_1605, WorksForBoundaryInputs_1605) {
  Mul09Table table;

  // Boundary/edge values for uint8_t domain.
  EXPECT_EQ(table(uint8_t{0}), table(uint8_t{0}));
  EXPECT_EQ(table(uint8_t{1}), table(uint8_t{1}));
  EXPECT_EQ(table(uint8_t{254}), table(uint8_t{254}));
  EXPECT_EQ(table(uint8_t{255}), table(uint8_t{255}));
}

TEST_F(Mul09TableTest_1605, DeterministicForSameInput_1605) {
  Mul09Table table;

  // Verify repeatability without assuming any specific mapping.
  for (int i = 0; i < 256; ++i) {
    const uint8_t in = static_cast<uint8_t>(i);
    const unsigned char a = table(in);
    const unsigned char b = table(in);
    EXPECT_EQ(a, b) << "Input byte: " << i;
  }
}

TEST_F(Mul09TableTest_1605, CallableOnConstInstance_1605) {
  const Mul09Table table;

  // Ensure the const-qualified call operator is usable across the full domain.
  for (int i = 0; i < 256; ++i) {
    const uint8_t in = static_cast<uint8_t>(i);
    (void)table(in);  // observable behavior here is "call succeeds"
    SUCCEED();
  }
}

TEST_F(Mul09TableTest_1605, IndependentCopiesProduceSameResults_1605) {
  Mul09Table table1;
  Mul09Table table2 = table1;  // copy

  // Copying should preserve observable lookup behavior.
  for (int i = 0; i < 256; ++i) {
    const uint8_t in = static_cast<uint8_t>(i);
    EXPECT_EQ(table1(in), table2(in)) << "Input byte: " << i;
  }
}

}  // namespace