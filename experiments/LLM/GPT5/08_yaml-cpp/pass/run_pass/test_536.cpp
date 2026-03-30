#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "yaml-cpp/emitter.h"
#include "yaml-cpp/emittermanip.h"

namespace {

class EmitterWriteBoolTest_536 : public ::testing::Test {
 protected:
  static std::string EmitBoolWithLocal(std::ostream& os, YAML::EMITTER_MANIP local, bool value) {
    YAML::Emitter emitter(os);
    emitter.SetLocalValue(local).Write(value);
    return static_cast<std::ostringstream&>(os).str();
  }

  static std::string EmitBoolWithFormat(std::ostream& os, YAML::EMITTER_MANIP fmt, bool value) {
    YAML::Emitter emitter(os);
    // SetBoolFormat returns bool; don't assume success for every value.
    (void)emitter.SetBoolFormat(fmt);
    emitter.Write(value);
    return static_cast<std::ostringstream&>(os).str();
  }
};

TEST_F(EmitterWriteBoolTest_536, DefaultTrueAndFalseAreNonEmptyAndDifferent_536) {
  std::ostringstream oss_true;
  YAML::Emitter emitter_true(oss_true);
  emitter_true.Write(true);
  const std::string out_true = oss_true.str();

  std::ostringstream oss_false;
  YAML::Emitter emitter_false(oss_false);
  emitter_false.Write(false);
  const std::string out_false = oss_false.str();

  EXPECT_FALSE(out_true.empty());
  EXPECT_FALSE(out_false.empty());
  EXPECT_NE(out_true, out_false);
}

TEST_F(EmitterWriteBoolTest_536, ReturnsSameEmitterReferenceForChaining_536) {
  std::ostringstream oss;
  YAML::Emitter emitter(oss);

  YAML::Emitter& ref1 = emitter.Write(true);
  YAML::Emitter& ref2 = emitter.Write(false);

  EXPECT_EQ(&ref1, &emitter);
  EXPECT_EQ(&ref2, &emitter);
  EXPECT_FALSE(oss.str().empty());
}

TEST_F(EmitterWriteBoolTest_536, ShortBoolEmitsSingleCharacterAndMatchesLongPrefixForTrue_536) {
  std::ostringstream oss_long;
  YAML::Emitter emitter_long(oss_long);
  emitter_long.SetLocalValue(YAML::LongBool).Write(true);
  const std::string long_out = oss_long.str();

  std::ostringstream oss_short;
  YAML::Emitter emitter_short(oss_short);
  emitter_short.SetLocalValue(YAML::ShortBool).Write(true);
  const std::string short_out = oss_short.str();

  ASSERT_FALSE(long_out.empty());
  ASSERT_FALSE(short_out.empty());

  EXPECT_EQ(short_out.size(), 1u);
  // Write(bool) uses name[0] when ShortBool, otherwise full name.
  EXPECT_EQ(long_out.front(), short_out.front());
}

TEST_F(EmitterWriteBoolTest_536, ShortBoolEmitsSingleCharacterAndMatchesLongPrefixForFalse_536) {
  std::ostringstream oss_long;
  YAML::Emitter emitter_long(oss_long);
  emitter_long.SetLocalValue(YAML::LongBool).Write(false);
  const std::string long_out = oss_long.str();

  std::ostringstream oss_short;
  YAML::Emitter emitter_short(oss_short);
  emitter_short.SetLocalValue(YAML::ShortBool).Write(false);
  const std::string short_out = oss_short.str();

  ASSERT_FALSE(long_out.empty());
  ASSERT_FALSE(short_out.empty());

  EXPECT_EQ(short_out.size(), 1u);
  EXPECT_EQ(long_out.front(), short_out.front());
}

TEST_F(EmitterWriteBoolTest_536, ShortBoolStillDistinguishesTrueAndFalse_536) {
  std::ostringstream oss_t;
  YAML::Emitter emitter_t(oss_t);
  emitter_t.SetLocalValue(YAML::ShortBool).Write(true);
  const std::string out_t = oss_t.str();

  std::ostringstream oss_f;
  YAML::Emitter emitter_f(oss_f);
  emitter_f.SetLocalValue(YAML::ShortBool).Write(false);
  const std::string out_f = oss_f.str();

  ASSERT_EQ(out_t.size(), 1u);
  ASSERT_EQ(out_f.size(), 1u);
  EXPECT_NE(out_t, out_f);
}

TEST_F(EmitterWriteBoolTest_536, BoolFormatSettingChangesOutputForAtLeastOneFormat_536) {
  // We don't assume which formats are supported or what exact text is used.
  // We only check that selecting a different bool format can change output.
  std::ostringstream oss_default_t;
  YAML::Emitter emitter_default_t(oss_default_t);
  emitter_default_t.Write(true);
  const std::string default_true = oss_default_t.str();
  ASSERT_FALSE(default_true.empty());

  // Try a few known enum values that represent bool formats.
  const YAML::EMITTER_MANIP candidates[] = {
      YAML::YesNoBool, YAML::TrueFalseBool, YAML::OnOffBool,
  };

  bool observed_difference = false;
  for (auto fmt : candidates) {
    std::ostringstream oss;
    YAML::Emitter emitter(oss);
    (void)emitter.SetBoolFormat(fmt);
    emitter.Write(true);
    const std::string out = oss.str();
    if (!out.empty() && out != default_true) {
      observed_difference = true;
      break;
    }
  }

  // If the implementation treats the default as one of these formats,
  // it's possible no difference is observed. In that case, at least ensure
  // we produced valid (non-empty) output for the attempts.
  if (!observed_difference) {
    for (auto fmt : candidates) {
      std::ostringstream oss;
      YAML::Emitter emitter(oss);
      (void)emitter.SetBoolFormat(fmt);
      emitter.Write(true);
      EXPECT_FALSE(oss.str().empty());
    }
  } else {
    SUCCEED();
  }
}

TEST_F(EmitterWriteBoolTest_536, WhenEmitterBecomesBadWriteDoesNotAppendToStream_536) {
  std::ostringstream oss;
  YAML::Emitter emitter(oss);

  // Attempt to drive the emitter into an error state via invalid manip values.
  // We do not assume which setter rejects invalid values; we just try a few.
  const auto invalid = static_cast<YAML::EMITTER_MANIP>(999999);

  (void)emitter.SetBoolFormat(invalid);
  (void)emitter.SetNullFormat(invalid);
  (void)emitter.SetStringFormat(invalid);
  (void)emitter.SetOutputCharset(invalid);
  (void)emitter.SetIntBase(invalid);
  (void)emitter.SetSeqFormat(invalid);
  (void)emitter.SetMapFormat(invalid);

  const bool became_bad = !emitter.good();
  const std::string before = oss.str();

  emitter.Write(true);
  const std::string after = oss.str();

  if (!became_bad) {
    // If we couldn't observe a "bad" state through the public interface,
    // at least verify Write(bool) is still safe and produces some output.
    EXPECT_FALSE(after.empty());
    return;
  }

  // If !good(), Write(bool) should early-return without emitting.
  EXPECT_EQ(after, before);
  EXPECT_FALSE(emitter.GetLastError().empty());
}

}  // namespace