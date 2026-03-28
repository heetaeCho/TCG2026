// TEST_ID: 532
// File: test_emitter_setlocalprecision_532.cpp

#include <gtest/gtest.h>

#include <string>

#include "yaml-cpp/emitter.h"
#include "yaml-cpp/emittermanip.h"

namespace {

class EmitterSetLocalPrecisionTest_532 : public ::testing::Test {
protected:
  static std::string EmitFloatWithOptionalLocalPrecision(int localFloatPrec, int localDoublePrec) {
    YAML::Emitter out;

    // Establish a known baseline (we don't assert on exact digits, only observable differences).
    (void)out.SetFloatPrecision(8);
    (void)out.SetDoublePrecision(16);

    if (localFloatPrec != kNoLocal || localDoublePrec != kNoLocal) {
      YAML::_Precision p(localFloatPrec, localDoublePrec);
      out.SetLocalPrecision(p);
    }

    out.WriteStreamable(1.2345678f);
    return std::string(out.c_str(), out.size());
  }

  static std::string EmitDoubleWithOptionalLocalPrecision(int localFloatPrec, int localDoublePrec) {
    YAML::Emitter out;

    // Establish a known baseline (we don't assert on exact digits, only observable differences).
    (void)out.SetFloatPrecision(8);
    (void)out.SetDoublePrecision(16);

    if (localFloatPrec != kNoLocal || localDoublePrec != kNoLocal) {
      YAML::_Precision p(localFloatPrec, localDoublePrec);
      out.SetLocalPrecision(p);
    }

    out.WriteStreamable(1.234567890123456);  // needs many digits to observe precision differences
    return std::string(out.c_str(), out.size());
  }

  static std::string EmitFloatThenDoubleWithLocalPrecision(int localFloatPrec, int localDoublePrec) {
    YAML::Emitter out;

    (void)out.SetFloatPrecision(8);
    (void)out.SetDoublePrecision(16);

    YAML::_Precision p(localFloatPrec, localDoublePrec);
    out.SetLocalPrecision(p);

    out.WriteStreamable(1.2345678f);
    out.WriteStreamable(1.234567890123456);

    return std::string(out.c_str(), out.size());
  }

  static constexpr int kNoLocal = -999999;  // sentinel for "don't call SetLocalPrecision"
};

TEST_F(EmitterSetLocalPrecisionTest_532, ReturnsSelfReference_532) {
  YAML::Emitter out;
  YAML::_Precision p(3, 7);

  YAML::Emitter& ret = out.SetLocalPrecision(p);

  EXPECT_EQ(&ret, &out);
}

TEST_F(EmitterSetLocalPrecisionTest_532, ChangesFloatOutputWhenFloatPrecisionProvided_532) {
  const std::string baseline = EmitFloatWithOptionalLocalPrecision(kNoLocal, kNoLocal);
  const std::string withLocal = EmitFloatWithOptionalLocalPrecision(/*localFloatPrec=*/2, /*localDoublePrec=*/kNoLocal);

  // Observable behavior: output should change when local float precision is applied.
  EXPECT_NE(withLocal, baseline);
  EXPECT_FALSE(withLocal.empty());
}

TEST_F(EmitterSetLocalPrecisionTest_532, DoesNotChangeFloatOutputWhenFloatPrecisionIsNegative_532) {
  const std::string baseline = EmitFloatWithOptionalLocalPrecision(kNoLocal, kNoLocal);

  // Per interface behavior: negative precision value is a boundary/error-like input;
  // we only check observable behavior (no change vs baseline).
  const std::string withNegativeLocal = EmitFloatWithOptionalLocalPrecision(/*localFloatPrec=*/-1, /*localDoublePrec=*/kNoLocal);

  EXPECT_EQ(withNegativeLocal, baseline);
}

TEST_F(EmitterSetLocalPrecisionTest_532, ChangesDoubleOutputWhenDoublePrecisionProvided_532) {
  const std::string baseline = EmitDoubleWithOptionalLocalPrecision(kNoLocal, kNoLocal);
  const std::string withLocal = EmitDoubleWithOptionalLocalPrecision(/*localFloatPrec=*/kNoLocal, /*localDoublePrec=*/6);

  // Observable behavior: output should change when local double precision is applied.
  EXPECT_NE(withLocal, baseline);
  EXPECT_FALSE(withLocal.empty());
}

TEST_F(EmitterSetLocalPrecisionTest_532, DoesNotChangeDoubleOutputWhenDoublePrecisionIsNegative_532) {
  const std::string baseline = EmitDoubleWithOptionalLocalPrecision(kNoLocal, kNoLocal);
  const std::string withNegativeLocal = EmitDoubleWithOptionalLocalPrecision(/*localFloatPrec=*/kNoLocal, /*localDoublePrec=*/-1);

  EXPECT_EQ(withNegativeLocal, baseline);
}

TEST_F(EmitterSetLocalPrecisionTest_532, MixedLocalPrecisionAffectsCombinedOutput_532) {
  // Apply local precision to both and compare against applying it to only one.
  const std::string both = EmitFloatThenDoubleWithLocalPrecision(/*localFloatPrec=*/2, /*localDoublePrec=*/6);
  const std::string onlyFloat = EmitFloatThenDoubleWithLocalPrecision(/*localFloatPrec=*/2, /*localDoublePrec=*/16);
  const std::string onlyDouble = EmitFloatThenDoubleWithLocalPrecision(/*localFloatPrec=*/8, /*localDoublePrec=*/6);

  // We don't assume exact formatting, only that these configurations are observably different.
  EXPECT_NE(both, onlyFloat);
  EXPECT_NE(both, onlyDouble);
  EXPECT_FALSE(both.empty());
}

TEST_F(EmitterSetLocalPrecisionTest_532, AcceptsLargePrecisionValuesWithoutBreakingGoodState_532) {
  YAML::Emitter out;
  EXPECT_TRUE(out.good());

  YAML::_Precision p(/*floatPrecision=*/50, /*doublePrecision=*/100);
  out.SetLocalPrecision(p);

  // Write values to exercise the settings through public API.
  out.WriteStreamable(1.2345678f);
  out.WriteStreamable(1.234567890123456);

  EXPECT_TRUE(out.good());
  EXPECT_GE(out.size(), 1u);
}

}  // namespace