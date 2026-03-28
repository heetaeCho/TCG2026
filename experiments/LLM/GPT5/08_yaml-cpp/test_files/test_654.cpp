// TEST_ID: 654
//
// Unit tests for YAML::EmitSeq (yaml-cpp/stlemitter.h)
//
// Constraints note:
// - Treat EmitSeq / Emitter as a black box.
// - Verify only observable behavior via Emitter output and return reference identity.

#include <gtest/gtest.h>

#include <algorithm>
#include <cctype>
#include <list>
#include <sstream>
#include <string>
#include <vector>

#include "yaml-cpp/emitter.h"
#include "yaml-cpp/emittermanip.h"
#include "yaml-cpp/stlemitter.h"

namespace {

static std::string TrimCopy(const std::string& s) {
  auto is_space = [](unsigned char c) { return std::isspace(c) != 0; };

  auto b = std::find_if_not(s.begin(), s.end(), is_space);
  auto e = std::find_if_not(s.rbegin(), s.rend(), is_space).base();
  if (b >= e) return std::string();
  return std::string(b, e);
}

static bool ContainsInOrder(const std::string& haystack,
                            const std::vector<std::string>& needles) {
  std::size_t pos = 0;
  for (const auto& n : needles) {
    auto found = haystack.find(n, pos);
    if (found == std::string::npos) return false;
    pos = found + n.size();
  }
  return true;
}

class EmitSeqTest_654 : public ::testing::Test {
 protected:
  std::ostringstream out;
  YAML::Emitter emitter{out};

  void ForceFlowSeqOrSkip() {
    // If the library doesn't support forcing Flow sequences via SetSeqFormat,
    // we skip tests that rely on bracketed flow formatting.
    if (!emitter.SetSeqFormat(YAML::Flow)) {
      GTEST_SKIP() << "Emitter::SetSeqFormat(YAML::Flow) returned false; "
                      "cannot assert flow-seq formatting.";
    }
  }
};

}  // namespace

TEST_F(EmitSeqTest_654, ReturnsSameEmitterReference_654) {
  ForceFlowSeqOrSkip();

  const std::vector<int> seq{1, 2, 3};
  YAML::Emitter* before = &emitter;

  YAML::Emitter& returned = YAML::EmitSeq(emitter, seq);

  EXPECT_EQ(&returned, before);
}

TEST_F(EmitSeqTest_654, EmitsFlowSequenceWithOrderedElements_Ints_654) {
  ForceFlowSeqOrSkip();

  const std::vector<int> seq{1, 2, 3, 10};
  YAML::EmitSeq(emitter, seq);

  const std::string emitted = TrimCopy(out.str());
  ASSERT_FALSE(emitted.empty());

  // In flow format, YAML sequences are typically bracketed; verify observable
  // outer structure without over-specifying whitespace.
  EXPECT_EQ(emitted.front(), '[') << emitted;
  EXPECT_EQ(emitted.back(), ']') << emitted;

  // Verify elements appear in order.
  EXPECT_TRUE(ContainsInOrder(emitted, {"1", "2", "3", "10"})) << emitted;
}

TEST_F(EmitSeqTest_654, EmitsFlowSequenceWithOrderedElements_Strings_654) {
  ForceFlowSeqOrSkip();

  // Use simple unambiguous scalars to avoid quoting/escaping differences.
  const std::vector<std::string> seq{"alpha", "beta", "gamma"};
  YAML::EmitSeq(emitter, seq);

  const std::string emitted = TrimCopy(out.str());
  ASSERT_FALSE(emitted.empty());

  EXPECT_EQ(emitted.front(), '[') << emitted;
  EXPECT_EQ(emitted.back(), ']') << emitted;

  EXPECT_TRUE(ContainsInOrder(emitted, {"alpha", "beta", "gamma"})) << emitted;
}

TEST_F(EmitSeqTest_654, EmitsEmptySequence_654) {
  ForceFlowSeqOrSkip();

  const std::vector<int> empty;
  YAML::EmitSeq(emitter, empty);

  const std::string emitted = TrimCopy(out.str());
  // For an empty flow sequence, the standard representation is [].
  // We allow whitespace differences but not extra content.
  EXPECT_EQ(emitted, "[]") << emitted;
}

TEST_F(EmitSeqTest_654, EmitsSingleElementSequence_654) {
  ForceFlowSeqOrSkip();

  const std::vector<int> seq{42};
  YAML::EmitSeq(emitter, seq);

  const std::string emitted = TrimCopy(out.str());
  ASSERT_FALSE(emitted.empty());

  EXPECT_EQ(emitted.front(), '[') << emitted;
  EXPECT_EQ(emitted.back(), ']') << emitted;
  EXPECT_NE(emitted.find("42"), std::string::npos) << emitted;
}

TEST_F(EmitSeqTest_654, WorksWithDifferentSTLSequenceContainer_List_654) {
  ForceFlowSeqOrSkip();

  const std::list<int> seq{5, 6, 7};
  YAML::EmitSeq(emitter, seq);

  const std::string emitted = TrimCopy(out.str());
  ASSERT_FALSE(emitted.empty());

  EXPECT_EQ(emitted.front(), '[') << emitted;
  EXPECT_EQ(emitted.back(), ']') << emitted;
  EXPECT_TRUE(ContainsInOrder(emitted, {"5", "6", "7"})) << emitted;
}

TEST_F(EmitSeqTest_654, AppendsToExistingEmitterContent_654) {
  ForceFlowSeqOrSkip();

  // Write something first, then EmitSeq; verify output contains both in order.
  emitter << "prefix";
  const std::vector<int> seq{1, 2};
  YAML::EmitSeq(emitter, seq);

  const std::string emitted = TrimCopy(out.str());
  ASSERT_FALSE(emitted.empty());

  EXPECT_TRUE(ContainsInOrder(emitted, {"prefix", "[", "1", "2", "]"}))
      << emitted;
}

TEST_F(EmitSeqTest_654, EmitsLargerSequenceMaintainingOrder_654) {
  ForceFlowSeqOrSkip();

  std::vector<int> seq;
  for (int i = 0; i < 50; ++i) seq.push_back(i);

  YAML::EmitSeq(emitter, seq);

  const std::string emitted = TrimCopy(out.str());
  ASSERT_FALSE(emitted.empty());

  EXPECT_EQ(emitted.front(), '[') << emitted;
  EXPECT_EQ(emitted.back(), ']') << emitted;

  // Spot-check a few ordered elements to avoid over-constraining formatting.
  EXPECT_TRUE(ContainsInOrder(emitted, {"0", "1", "2", "10", "25", "49"}))
      << emitted;
}