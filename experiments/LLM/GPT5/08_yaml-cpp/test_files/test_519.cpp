// File: emitter_setboolformat_test.cpp
#include <gtest/gtest.h>

#include <string>
#include <yaml-cpp/yaml.h>

namespace {

class EmitterSetBoolFormatTest_519 : public ::testing::Test {
 protected:
  static std::string EmitTrueWithManip(YAML::EMITTER_MANIP manip1) {
    YAML::Emitter out;
    (void)out.SetBoolFormat(manip1);
    out.Write(true);
    return std::string(out.c_str(), out.size());
  }

  static std::string EmitTrueWithTwoManips(YAML::EMITTER_MANIP manip1,
                                          YAML::EMITTER_MANIP manip2) {
    YAML::Emitter out;
    (void)out.SetBoolFormat(manip1);
    (void)out.SetBoolFormat(manip2);
    out.Write(true);
    return std::string(out.c_str(), out.size());
  }

  static std::string EmitTrueFalseWithManip(YAML::EMITTER_MANIP manip1) {
    YAML::Emitter out;
    (void)out.SetBoolFormat(manip1);
    out.Write(true);
    out.Write(false);
    return std::string(out.c_str(), out.size());
  }
};

TEST_F(EmitterSetBoolFormatTest_519, TrueFalseStyleIsAcceptedAndProducesOutput_519) {
  YAML::Emitter out;

  EXPECT_TRUE(out.SetBoolFormat(YAML::TrueFalse));
  EXPECT_TRUE(out.good());

  out.Write(true);
  out.Write(false);

  EXPECT_TRUE(out.good());
  EXPECT_GT(out.size(), 0u);

  const std::string s(out.c_str(), out.size());
  EXPECT_FALSE(s.empty());
}

TEST_F(EmitterSetBoolFormatTest_519, DifferentBoolStylesProduceDifferentOutput_519) {
  const std::string true_false = EmitTrueWithManip(YAML::TrueFalse);
  const std::string yes_no = EmitTrueWithManip(YAML::YesNo);

  // Observable behavior: different accepted bool styles should typically change output.
  // We only assert inequality (not specific spellings) to keep the test black-box.
  EXPECT_FALSE(true_false.empty());
  EXPECT_FALSE(yes_no.empty());
  EXPECT_NE(true_false, yes_no);
}

TEST_F(EmitterSetBoolFormatTest_519, BoolCaseFormatsAffectOutput_519) {
  // Apply the same style, then vary case settings.
  const std::string lower = EmitTrueWithTwoManips(YAML::TrueFalse, YAML::LowerCase);
  const std::string upper = EmitTrueWithTwoManips(YAML::TrueFalse, YAML::UpperCase);

  EXPECT_FALSE(lower.empty());
  EXPECT_FALSE(upper.empty());
  EXPECT_NE(lower, upper);
}

TEST_F(EmitterSetBoolFormatTest_519, BoolLengthFormatsAffectOutput_519) {
  const std::string short_bool = EmitTrueWithTwoManips(YAML::TrueFalse, YAML::ShortBool);
  const std::string long_bool = EmitTrueWithTwoManips(YAML::TrueFalse, YAML::LongBool);

  EXPECT_FALSE(short_bool.empty());
  EXPECT_FALSE(long_bool.empty());
  EXPECT_NE(short_bool, long_bool);
}

TEST_F(EmitterSetBoolFormatTest_519, ReturnsFalseForNonBoolManipulatorAndDoesNotChangeBoolOutput_519) {
  // Establish a baseline output for a known bool format.
  const std::string baseline = EmitTrueWithManip(YAML::TrueFalse);
  ASSERT_FALSE(baseline.empty());

  YAML::Emitter out;
  ASSERT_TRUE(out.SetBoolFormat(YAML::TrueFalse));

  // Use a manipulator that is not a bool-related setting.
  // Observable behavior of SetBoolFormat: it should return whether *any* bool-related setter accepted it.
  EXPECT_FALSE(out.SetBoolFormat(YAML::Flow));

  out.Write(true);
  const std::string after(out.c_str(), out.size());

  EXPECT_FALSE(after.empty());
  EXPECT_EQ(after, baseline);
}

TEST_F(EmitterSetBoolFormatTest_519, MultipleCallsRemainUsableAndGood_519) {
  YAML::Emitter out;

  // Repeated calls should not break basic usage.
  EXPECT_TRUE(out.SetBoolFormat(YAML::TrueFalse));
  EXPECT_TRUE(out.SetBoolFormat(YAML::UpperCase));
  EXPECT_TRUE(out.SetBoolFormat(YAML::LongBool));

  out.Write(true);
  out.Write(false);

  EXPECT_TRUE(out.good());
  EXPECT_GT(out.size(), 0u);
}

}  // namespace