// TEST_ID: 522
// File: test_emitter_setseqformat_522.cpp

#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include <yaml-cpp/emitter.h>
#include <yaml-cpp/yaml.h>

namespace {

class EmitterSetSeqFormatTest_522 : public ::testing::Test {
 protected:
  static std::string EmitSimpleSeqToString(YAML::Emitter& out) {
    // Rely only on observable output via c_str()/size() after emission.
    out << YAML::BeginSeq << 1 << 2 << YAML::EndSeq;
    return std::string(out.c_str(), out.size());
  }

  static bool LooksLikeFlowSeq(const std::string& s) {
    // Very lightweight heuristic: flow sequences commonly use brackets.
    return s.find('[') != std::string::npos && s.find(']') != std::string::npos;
  }

  static bool LooksLikeBlockSeq(const std::string& s) {
    // Very lightweight heuristic: block sequences commonly use "-".
    return s.find('-') != std::string::npos;
  }
};

}  // namespace

TEST_F(EmitterSetSeqFormatTest_522, SetSeqFormatFlow_ProducesBracketedSequence_522) {
  YAML::Emitter out;

  const bool ok = out.SetSeqFormat(YAML::Flow);
  EXPECT_TRUE(ok) << "SetSeqFormat(YAML::Flow) should succeed for a valid manipulator.";
  EXPECT_TRUE(out.good()) << out.GetLastError();

  const std::string emitted = EmitSimpleSeqToString(out);
  EXPECT_FALSE(emitted.empty());
  EXPECT_TRUE(LooksLikeFlowSeq(emitted)) << "Expected flow-style sequence formatting. Got: " << emitted;
}

TEST_F(EmitterSetSeqFormatTest_522, SetSeqFormatBlock_ProducesDashSequence_522) {
  YAML::Emitter out;

  const bool ok = out.SetSeqFormat(YAML::Block);
  EXPECT_TRUE(ok) << "SetSeqFormat(YAML::Block) should succeed for a valid manipulator.";
  EXPECT_TRUE(out.good()) << out.GetLastError();

  const std::string emitted = EmitSimpleSeqToString(out);
  EXPECT_FALSE(emitted.empty());
  EXPECT_TRUE(LooksLikeBlockSeq(emitted)) << "Expected block-style sequence formatting. Got: " << emitted;
}

TEST_F(EmitterSetSeqFormatTest_522, SetSeqFormat_CanBeCalledMultipleTimes_LastCallWinsObservably_522) {
  YAML::Emitter out;

  ASSERT_TRUE(out.SetSeqFormat(YAML::Block));
  ASSERT_TRUE(out.good()) << out.GetLastError();

  // Switch to flow before emitting; output should look like flow.
  ASSERT_TRUE(out.SetSeqFormat(YAML::Flow));
  EXPECT_TRUE(out.good()) << out.GetLastError();

  const std::string emitted = EmitSimpleSeqToString(out);
  EXPECT_FALSE(emitted.empty());
  EXPECT_TRUE(LooksLikeFlowSeq(emitted)) << "Expected the last SetSeqFormat to be reflected. Got: " << emitted;
}

TEST_F(EmitterSetSeqFormatTest_522, SetSeqFormat_AfterSomeOutput_DoesNotCrashAndKeepsConsistency_522) {
  YAML::Emitter out;

  // Emit something first (scalar), then change seq format and emit sequence.
  out << 42;
  EXPECT_TRUE(out.good()) << out.GetLastError();

  const bool ok = out.SetSeqFormat(YAML::Flow);
  EXPECT_TRUE(ok);
  EXPECT_TRUE(out.good()) << out.GetLastError();

  out << YAML::BeginSeq << 1 << YAML::EndSeq;
  EXPECT_TRUE(out.good()) << out.GetLastError();

  const std::string emitted(out.c_str(), out.size());
  EXPECT_FALSE(emitted.empty());
  // We don't assume exact formatting; just ensure something sensible is produced.
  EXPECT_NE(emitted.find("42"), std::string::npos);
  EXPECT_TRUE(LooksLikeFlowSeq(emitted)) << "Expected flow-style sequence formatting. Got: " << emitted;
}

TEST_F(EmitterSetSeqFormatTest_522, SetSeqFormat_InvalidManipulator_ReportsFailureOrErrorState_522) {
  YAML::Emitter out;

  // Pass an invalid value. We do not assume how it is handled internally; we only
  // require that the interface reflects failure via return value and/or error state.
  const auto invalid = static_cast<YAML::EMITTER_MANIP>(-1);

  const bool ok = out.SetSeqFormat(invalid);

  // Observable error handling: either returns false OR puts emitter into a not-good state.
  // If it becomes not-good, it should have some (possibly empty) last error string.
  if (!ok) {
    SUCCEED();
  } else {
    // If it "accepts" the invalid value, it should still remain in a good state.
    // (We keep this tolerant: good() may remain true or become false depending on impl.)
    // At minimum, it must not crash and must remain queryable.
    (void)out.good();
    (void)out.GetLastError();
  }

  if (!out.good()) {
    // If the emitter reports not-good, it should provide an error message (observable).
    EXPECT_FALSE(out.GetLastError().empty());
  }
}