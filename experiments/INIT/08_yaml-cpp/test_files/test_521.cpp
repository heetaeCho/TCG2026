// File: ./TestProjects/yaml-cpp/test/emitter_setintbase_test_521.cpp

#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "yaml-cpp/emitter.h"

namespace {

class EmitterSetIntBaseTest_521 : public ::testing::Test {
 protected:
  static std::string EmitIntWithOptionalBase(YAML::EMITTER_MANIP base, bool setBase) {
    std::stringstream ss;
    YAML::Emitter out(ss);

    if (setBase) {
      const bool ok = out.SetIntBase(base);
      EXPECT_TRUE(ok);
      EXPECT_TRUE(out.good());
    }

    // Use the public template API (do not assume operator<< exists).
    out.WriteIntegralType<int>(31);

    EXPECT_TRUE(out.good());
    return std::string(out.c_str(), out.size());
  }
};

TEST_F(EmitterSetIntBaseTest_521, SetIntBaseAcceptsCommonBasesAndKeepsGood_521) {
  std::stringstream ss;
  YAML::Emitter out(ss);

  // These are the standard yaml-cpp integer base manipulators.
  EXPECT_TRUE(out.SetIntBase(YAML::Dec));
  EXPECT_TRUE(out.good());
  EXPECT_TRUE(out.GetLastError().empty());

  EXPECT_TRUE(out.SetIntBase(YAML::Hex));
  EXPECT_TRUE(out.good());
  EXPECT_TRUE(out.GetLastError().empty());

  EXPECT_TRUE(out.SetIntBase(YAML::Oct));
  EXPECT_TRUE(out.good());
  EXPECT_TRUE(out.GetLastError().empty());
}

TEST_F(EmitterSetIntBaseTest_521, SetIntBaseAffectsIntegralEmissionAcrossEmitters_521) {
  const std::string decOut = EmitIntWithOptionalBase(YAML::Dec, /*setBase=*/true);
  const std::string hexOut = EmitIntWithOptionalBase(YAML::Hex, /*setBase=*/true);
  const std::string octOut = EmitIntWithOptionalBase(YAML::Oct, /*setBase=*/true);

  // Black-box check: different bases should produce different text for the same value.
  EXPECT_NE(decOut, hexOut);
  EXPECT_NE(decOut, octOut);
  EXPECT_NE(hexOut, octOut);
}

TEST_F(EmitterSetIntBaseTest_521, SetIntBaseSameBaseIsStableForIntegralEmission_521) {
  const std::string hexOut1 = EmitIntWithOptionalBase(YAML::Hex, /*setBase=*/true);
  const std::string hexOut2 = EmitIntWithOptionalBase(YAML::Hex, /*setBase=*/true);

  EXPECT_EQ(hexOut1, hexOut2);

  const std::string decOut1 = EmitIntWithOptionalBase(YAML::Dec, /*setBase=*/true);
  const std::string decOut2 = EmitIntWithOptionalBase(YAML::Dec, /*setBase=*/true);

  EXPECT_EQ(decOut1, decOut2);
}

TEST_F(EmitterSetIntBaseTest_521, SetIntBaseRejectsInvalidManipulatorAndReportsError_521) {
  std::stringstream ss;
  YAML::Emitter out(ss);

  const auto invalid = static_cast<YAML::EMITTER_MANIP>(999999);

  const bool ok = out.SetIntBase(invalid);
  EXPECT_FALSE(ok);

  // Observable error reporting via public API (good()/GetLastError()).
  EXPECT_FALSE(out.good());
  EXPECT_FALSE(out.GetLastError().empty());
}

}  // namespace