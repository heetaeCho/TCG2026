// TEST_ID: 48
#include <gtest/gtest.h>

#include <limits>
#include <string>

#include "yaml-cpp/emitter.h"

namespace {

class OperatorLeftShiftIntTest_48 : public ::testing::Test {
 protected:
  static std::string Str(YAML::Emitter& e) {
    const char* s = e.c_str();
    return s ? std::string(s) : std::string();
  }
};

TEST_F(OperatorLeftShiftIntTest_48, ReturnsSameEmitterReference_48) {
  YAML::Emitter emitter;

  YAML::Emitter& ret = (emitter << 1);
  EXPECT_EQ(&ret, &emitter);
}

TEST_F(OperatorLeftShiftIntTest_48, EmitsZeroInOutput_48) {
  YAML::Emitter emitter;

  const std::size_t before = emitter.size();
  emitter << 0;

  EXPECT_TRUE(emitter.good());
  EXPECT_GE(emitter.size(), before);
  EXPECT_NE(Str(emitter).find("0"), std::string::npos);
}

TEST_F(OperatorLeftShiftIntTest_48, EmitsPositiveIntegerDigits_48) {
  YAML::Emitter emitter;

  emitter << 42;

  EXPECT_TRUE(emitter.good());
  EXPECT_NE(Str(emitter).find("42"), std::string::npos);
}

TEST_F(OperatorLeftShiftIntTest_48, EmitsNegativeIntegerWithMinusSign_48) {
  YAML::Emitter emitter;

  emitter << -7;

  EXPECT_TRUE(emitter.good());
  const std::string out = Str(emitter);
  EXPECT_NE(out.find("-7"), std::string::npos);
  EXPECT_NE(out.find('-'), std::string::npos);
}

TEST_F(OperatorLeftShiftIntTest_48, SupportsChaining_48) {
  YAML::Emitter emitter;

  YAML::Emitter& ret = (emitter << 1 << 2 << 3);
  EXPECT_EQ(&ret, &emitter);

  const std::string out = Str(emitter);
  EXPECT_NE(out.find("1"), std::string::npos);
  EXPECT_NE(out.find("2"), std::string::npos);
  EXPECT_NE(out.find("3"), std::string::npos);
}

TEST_F(OperatorLeftShiftIntTest_48, HandlesIntMax_48) {
  YAML::Emitter emitter;

  const int v = (std::numeric_limits<int>::max)();
  EXPECT_NO_THROW(emitter << v);

  EXPECT_TRUE(emitter.good());
  EXPECT_NE(Str(emitter).find(std::to_string(v)), std::string::npos);
}

TEST_F(OperatorLeftShiftIntTest_48, HandlesIntMin_48) {
  YAML::Emitter emitter;

  const int v = (std::numeric_limits<int>::min)();
  EXPECT_NO_THROW(emitter << v);

  EXPECT_TRUE(emitter.good());
  EXPECT_NE(Str(emitter).find(std::to_string(v)), std::string::npos);
}

}  // namespace
