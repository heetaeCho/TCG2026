// =================================================================================================
// TEST_ID 2119
// Unit tests for IsPropertyElementName (ParseRDF.cpp)
// =================================================================================================

#include <gtest/gtest.h>

// The production code (per prompt) depends on these symbols.
// We provide *minimal* stubs so we can exercise the observable behavior of
// IsPropertyElementName as a black-box function, without re-implementing logic.
//
// NOTE: We are NOT inferring the real internal mapping of RDFTermKind values.
// The tests only rely on boolean outcomes driven by the externally-callable
// helper predicates we control in this test TU.

using XMP_Uns8 = unsigned char;
using RDFTermKind = XMP_Uns8;

// Provide symbolic constants referenced by the function under test.
// Values are arbitrary and only need to be distinct.
static constexpr RDFTermKind kRDFTerm_Description = 1;

// ---- Collaborator hooks (external dependencies of the function under test) ----
// We model IsOldTerm / IsCoreSyntaxTerm as externally visible collaborators.
// That lets us verify interactions (calls + parameters) without peeking into any
// private state.

namespace {
struct CallLog {
  int isOld_calls = 0;
  int isCore_calls = 0;
  RDFTermKind last_isOld_arg = 0;
  RDFTermKind last_isCore_arg = 0;

  bool isOld_ret = false;
  bool isCore_ret = false;

  void Reset() { *this = CallLog{}; }
};

CallLog g_log;

bool IsOldTerm(RDFTermKind term) {
  g_log.isOld_calls++;
  g_log.last_isOld_arg = term;
  return g_log.isOld_ret;
}

bool IsCoreSyntaxTerm(RDFTermKind term) {
  g_log.isCore_calls++;
  g_log.last_isCore_arg = term;
  return g_log.isCore_ret;
}

// ---- Function under test (verbatim from prompt, with formatting only) ----
static bool IsPropertyElementName(RDFTermKind term) {
  if ((term == kRDFTerm_Description) || IsOldTerm(term)) return false;
  return (!IsCoreSyntaxTerm(term));
}
}  // namespace

// =================================================================================================
// Test Fixture
// =================================================================================================
class IsPropertyElementNameTest_2119 : public ::testing::Test {
protected:
  void SetUp() override { g_log.Reset(); }
};

// =================================================================================================
// Normal operation
// =================================================================================================

TEST_F(IsPropertyElementNameTest_2119, NonDescriptionNotOldAndNotCore_ReturnsTrue_2119) {
  const RDFTermKind term = 42;

  g_log.isOld_ret = false;
  g_log.isCore_ret = false;

  const bool result = IsPropertyElementName(term);

  EXPECT_TRUE(result);

  // External interaction verification
  EXPECT_EQ(g_log.isOld_calls, 1);
  EXPECT_EQ(g_log.last_isOld_arg, term);
  EXPECT_EQ(g_log.isCore_calls, 1);
  EXPECT_EQ(g_log.last_isCore_arg, term);
}

TEST_F(IsPropertyElementNameTest_2119, NonDescriptionNotOldButCore_ReturnsFalse_2119) {
  const RDFTermKind term = 99;

  g_log.isOld_ret = false;
  g_log.isCore_ret = true;

  const bool result = IsPropertyElementName(term);

  EXPECT_FALSE(result);

  // External interaction verification
  EXPECT_EQ(g_log.isOld_calls, 1);
  EXPECT_EQ(g_log.last_isOld_arg, term);
  EXPECT_EQ(g_log.isCore_calls, 1);
  EXPECT_EQ(g_log.last_isCore_arg, term);
}

// =================================================================================================
// Boundary / special cases
// =================================================================================================

TEST_F(IsPropertyElementNameTest_2119, DescriptionTerm_ReturnsFalseAndDoesNotQueryHelpers_2119) {
  g_log.isOld_ret = true;   // Should not matter
  g_log.isCore_ret = false; // Should not matter

  const bool result = IsPropertyElementName(kRDFTerm_Description);

  EXPECT_FALSE(result);

  // Short-circuit behavior is observable via lack of collaborator calls.
  EXPECT_EQ(g_log.isOld_calls, 0);
  EXPECT_EQ(g_log.isCore_calls, 0);
}

TEST_F(IsPropertyElementNameTest_2119, OldTerm_ReturnsFalseAndDoesNotQueryCoreSyntax_2119) {
  const RDFTermKind term = 7;

  g_log.isOld_ret = true;   // forces old-term path
  g_log.isCore_ret = false; // should not be consulted

  const bool result = IsPropertyElementName(term);

  EXPECT_FALSE(result);

  // External interaction verification
  EXPECT_EQ(g_log.isOld_calls, 1);
  EXPECT_EQ(g_log.last_isOld_arg, term);
  // Must not call IsCoreSyntaxTerm when old-term path returns false early.
  EXPECT_EQ(g_log.isCore_calls, 0);
}

TEST_F(IsPropertyElementNameTest_2119, TermZero_WhenNotOldAndNotCore_ReturnsTrue_2119) {
  const RDFTermKind term = 0;

  // Ensure it's not treated as description; our constant is 1.
  ASSERT_NE(term, kRDFTerm_Description);

  g_log.isOld_ret = false;
  g_log.isCore_ret = false;

  const bool result = IsPropertyElementName(term);

  EXPECT_TRUE(result);

  EXPECT_EQ(g_log.isOld_calls, 1);
  EXPECT_EQ(g_log.last_isOld_arg, term);
  EXPECT_EQ(g_log.isCore_calls, 1);
  EXPECT_EQ(g_log.last_isCore_arg, term);
}

TEST_F(IsPropertyElementNameTest_2119, TermMaxUnsigned8_WhenNotOldAndCore_ReturnsFalse_2119) {
  const RDFTermKind term = static_cast<RDFTermKind>(0xFF);

  ASSERT_NE(term, kRDFTerm_Description);

  g_log.isOld_ret = false;
  g_log.isCore_ret = true;

  const bool result = IsPropertyElementName(term);

  EXPECT_FALSE(result);

  EXPECT_EQ(g_log.isOld_calls, 1);
  EXPECT_EQ(g_log.last_isOld_arg, term);
  EXPECT_EQ(g_log.isCore_calls, 1);
  EXPECT_EQ(g_log.last_isCore_arg, term);
}

// =================================================================================================
// “Exceptional / error cases” (as observable through the interface)
// Here: there is no error reporting channel; we instead test robustness of
// observable behavior around short-circuiting and helper return combinations.
// =================================================================================================

TEST_F(IsPropertyElementNameTest_2119, OldTermEvenIfAlsoCore_CoreIsNotConsulted_ReturnsFalse_2119) {
  const RDFTermKind term = 123;

  // Simulate "conflicting" helper answers; function should short-circuit on old term.
  g_log.isOld_ret = true;
  g_log.isCore_ret = true;  // must not be read

  const bool result = IsPropertyElementName(term);

  EXPECT_FALSE(result);

  EXPECT_EQ(g_log.isOld_calls, 1);
  EXPECT_EQ(g_log.last_isOld_arg, term);
  EXPECT_EQ(g_log.isCore_calls, 0);
}