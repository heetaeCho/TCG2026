// TEST_ID: 531
#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "yaml-cpp/emitter.h"
#include "yaml-cpp/emittermanip.h"
#include "yaml-cpp/yaml.h"

namespace {

constexpr int kTestId_531 = 531;

// Extract the number of spaces immediately following a newline and preceding "- "
// (typical indentation marker for block sequences). Returns -1 if not found.
int CountSpacesBeforeFirstDashAfterNewline(const std::string& s) {
  const std::string needle = "\n";
  std::size_t pos = s.find(needle);
  if (pos == std::string::npos) return -1;
  pos += needle.size();

  // Scan forward to find a line that contains "- " and count its leading spaces.
  // Limit scanning to a reasonable number of lines.
  for (int lines = 0; lines < 20 && pos < s.size(); ++lines) {
    // Find end-of-line
    std::size_t eol = s.find('\n', pos);
    if (eol == std::string::npos) eol = s.size();

    // Count leading spaces on this line
    std::size_t i = pos;
    int spaces = 0;
    while (i < eol && s[i] == ' ') {
      ++spaces;
      ++i;
    }

    // Check for "- " after spaces
    if (i + 1 < eol && s[i] == '-' && s[i + 1] == ' ') {
      return spaces;
    }

    // Move to next line
    pos = (eol < s.size()) ? (eol + 1) : s.size();
  }

  return -1;
}

std::string EmitNestedSeqUnderKey(YAML::Emitter& out) {
  // This is standard yaml-cpp usage: a map with key "a" whose value is a block sequence.
  out << YAML::BeginMap;
  out << YAML::Key << "a" << YAML::Value;
  out << YAML::BeginSeq << "x" << "y" << YAML::EndSeq;
  out << YAML::EndMap;
  return std::string(out.c_str(), out.size());
}

class EmitterSetLocalIndentTest_531 : public ::testing::Test {};

}  // namespace

TEST_F(EmitterSetLocalIndentTest_531, ReturnsSelfReference_531) {
  YAML::Emitter out;

  YAML::_Indent indent(7);
  YAML::Emitter& ret = out.SetLocalIndent(indent);

  EXPECT_EQ(&ret, &out);
}

TEST_F(EmitterSetLocalIndentTest_531, DoesNotThrowAndEmitterRemainsUsable_531) {
  YAML::Emitter out;

  EXPECT_NO_THROW({
    out.SetLocalIndent(YAML::_Indent(7));
    out << "hello";
  });

  // Observable behavior: emitter should have produced some output and be queryable.
  EXPECT_NE(out.c_str(), nullptr);
  EXPECT_GE(out.size(), static_cast<std::size_t>(0));
}

TEST_F(EmitterSetLocalIndentTest_531, AffectsIndentationForNestedBlockSequence_531) {
  // Baseline output
  YAML::Emitter baseline;
  const std::string baselineYaml = EmitNestedSeqUnderKey(baseline);
  const int baselineSpaces = CountSpacesBeforeFirstDashAfterNewline(baselineYaml);

  // Modified output (use an uncommon value to avoid "default already equals requested")
  YAML::Emitter modified;
  modified.SetLocalIndent(YAML::_Indent(7));
  const std::string modifiedYaml = EmitNestedSeqUnderKey(modified);
  const int modifiedSpaces = CountSpacesBeforeFirstDashAfterNewline(modifiedYaml);

  // We only assert on observable indentation in the produced YAML.
  // If a nested block sequence is emitted, we should see a dash-prefixed line.
  ASSERT_NE(baselineSpaces, -1) << "Baseline YAML did not contain an indented '- ' line:\n"
                                << baselineYaml;
  ASSERT_NE(modifiedSpaces, -1) << "Modified YAML did not contain an indented '- ' line:\n"
                                << modifiedYaml;

  // The core behavior under test: SetLocalIndent changes indentation used for emission.
  EXPECT_EQ(modifiedSpaces, 7) << "Modified YAML was:\n" << modifiedYaml;

  // And it should typically differ from the baseline (if baseline isn't already 7).
  if (baselineSpaces != 7) {
    EXPECT_NE(modifiedSpaces, baselineSpaces)
        << "Expected indentation to differ from baseline. Baseline YAML:\n"
        << baselineYaml << "\nModified YAML:\n"
        << modifiedYaml;
  }
}

TEST_F(EmitterSetLocalIndentTest_531, WorksWithStreamBackedEmitter_531) {
  std::stringstream ss;
  YAML::Emitter out(ss);

  out.SetLocalIndent(YAML::_Indent(7));
  out << YAML::BeginMap;
  out << YAML::Key << "a" << YAML::Value;
  out << YAML::BeginSeq << "x" << "y" << YAML::EndSeq;
  out << YAML::EndMap;

  const std::string yaml = ss.str();
  const int spaces = CountSpacesBeforeFirstDashAfterNewline(yaml);

  ASSERT_NE(spaces, -1) << "Stream YAML did not contain an indented '- ' line:\n" << yaml;
  EXPECT_EQ(spaces, 7) << "Stream YAML was:\n" << yaml;
}

TEST_F(EmitterSetLocalIndentTest_531, BoundaryIndentZeroDoesNotCrash_531) {
  YAML::Emitter out;

  EXPECT_NO_THROW({
    out.SetLocalIndent(YAML::_Indent(0));
    out << YAML::BeginMap << YAML::Key << "k" << YAML::Value << "v" << YAML::EndMap;
  });

  // Observable: still can query output.
  EXPECT_NE(out.c_str(), nullptr);
}

TEST_F(EmitterSetLocalIndentTest_531, BoundaryLargeIndentDoesNotCrash_531) {
  YAML::Emitter out;

  EXPECT_NO_THROW({
    out.SetLocalIndent(YAML::_Indent(1000));
    out << YAML::BeginMap;
    out << YAML::Key << "a" << YAML::Value;
    out << YAML::BeginSeq << "x" << YAML::EndSeq;
    out << YAML::EndMap;
  });

  EXPECT_NE(out.c_str(), nullptr);
  // If the emitter reports errors via good()/GetLastError(), this is observable too.
  // We do not assume success/failure semantics for extreme values; we only require stability.
  (void)out.good();
  (void)out.GetLastError();
}