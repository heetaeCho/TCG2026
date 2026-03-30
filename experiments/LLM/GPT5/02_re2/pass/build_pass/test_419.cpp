// File: ./TestProjects/re2/tests/prog_prefixaccel_shiftdfa_test.cc
#include <gtest/gtest.h>
#include <cstdint>
#include <vector>
#include <cstring>

#include "re2/prog.h"  // Provides re2::Prog and PrefixAccel_ShiftDFA

using namespace re2;

namespace {

// A tiny accessor shim to set up the byte->uint64_t transition table used by
// PrefixAccel_ShiftDFA. We only touch the table pointer that the public code
// consults for transitions; tests continue to treat the implementation as a
// black box and verify behavior strictly via inputs/outputs.
struct PrefixDFAAccessor {
  uint64_t* prefix_dfa_;
};

inline void SetPrefixDFATable(Prog* prog, uint64_t* table256) {
  // Write the transition table pointer that PrefixAccel_ShiftDFA reads.
  // This does not re-implement any internal logic; it only supplies the
  // external collaborator (table) the function consults.
  reinterpret_cast<PrefixDFAAccessor*>(prog)->prefix_dfa_ = table256;
}

// Helper: build a 256-entry table initialized to a value.
std::vector<uint64_t> MakeTable(uint64_t init) {
  std::vector<uint64_t> t(256, init);
  return t;
}

// kShiftDFAFinal is defined in the TU as 9; the routine checks (curr & 63) == 9*6 = 54.
// Using table entries == 54 ensures the very first step reaches the observable "final".
constexpr uint64_t kFinalLow6 = 54;

}  // namespace

// ----------------------------- TESTS ---------------------------------

// Size == 0 should have no match and return nullptr.
TEST(ProgPrefixAccelShiftDFATest_419, ReturnsNullWhenSizeZero_419) {
  Prog prog;
  auto table = MakeTable(0);
  SetPrefixDFATable(&prog, table.data());

  const uint8_t* base = nullptr;
  const void* out = prog.PrefixAccel_ShiftDFA(base, /*size=*/0);
  EXPECT_EQ(out, nullptr);
}

// When the table never yields a final state (low 6 bits != 54), result is nullptr.
TEST(ProgPrefixAccelShiftDFATest_419, ReturnsNullWhenNoFinalState_419) {
  Prog prog;
  auto table = MakeTable(/*init=*/0);  // keeps curr&63 != 54
  SetPrefixDFATable(&prog, table.data());

  const uint8_t data[] = {1, 2, 3, 4, 5, 6, 7};
  const void* out = prog.PrefixAccel_ShiftDFA(data, sizeof(data));
  EXPECT_EQ(out, nullptr);
}

// If the very first byte reaches final, the returned pointer should be base + 1.
TEST(ProgPrefixAccelShiftDFATest_419, DetectsOnFirstByte_419) {
  Prog prog;
  auto table = MakeTable(/*init=*/0);
  // Choose a specific byte value to trigger final on the first step.
  const uint8_t trigger = 7;
  table[trigger] = kFinalLow6;
  SetPrefixDFATable(&prog, table.data());

  const uint8_t data[] = {trigger, 9, 9, 9};
  const uint8_t* base = data;
  const void* out = prog.PrefixAccel_ShiftDFA(base, sizeof(data));
  ASSERT_NE(out, nullptr);
  EXPECT_EQ(static_cast<const uint8_t*>(out), base + 1);  // prefix_size_ defaults to 0
}

// When the final is reached after several bytes, the pointer should be base + index_of_match + 1.
TEST(ProgPrefixAccelShiftDFATest_419, DetectsAfterSeveralBytes_419) {
  Prog prog;
  auto table = MakeTable(/*init=*/0);
  const uint8_t trigger = 42;
  table[trigger] = kFinalLow6;
  SetPrefixDFATable(&prog, table.data());

  const uint8_t data[] = {1, 2, 3, trigger, 5, 6};
  const uint8_t* base = data;

  const void* out = prog.PrefixAccel_ShiftDFA(base, sizeof(data));
  ASSERT_NE(out, nullptr);
  // Match occurs at index 3 -> base + (3 + 1) = base + 4
  EXPECT_EQ(static_cast<const uint8_t*>(out), base + 4);
}

// For size >= 8 with no final states anywhere, the function should still return nullptr.
TEST(ProgPrefixAccelShiftDFATest_419, SizeGE8_NoFinal_ReturnsNull_419) {
  Prog prog;
  auto table = MakeTable(/*init=*/0);  // never reaches final
  SetPrefixDFATable(&prog, table.data());

  uint8_t data[16];
  for (int i = 0; i < 16; ++i) data[i] = static_cast<uint8_t>(i);
  const void* out = prog.PrefixAccel_ShiftDFA(data, sizeof(data));
  EXPECT_EQ(out, nullptr);
}

// Using a high byte value (255) still indexes correctly and returns base + 1 on first-byte match.
TEST(ProgPrefixAccelShiftDFATest_419, HighByteValueTriggers_419) {
  Prog prog;
  auto table = MakeTable(/*init=*/0);
  table[255] = kFinalLow6;  // trigger on 0xFF
  SetPrefixDFATable(&prog, table.data());

  const uint8_t data[] = {255, 1, 2, 3};
  const uint8_t* base = data;

  const void* out = prog.PrefixAccel_ShiftDFA(base, sizeof(data));
  ASSERT_NE(out, nullptr);
  EXPECT_EQ(static_cast<const uint8_t*>(out), base + 1);
}
