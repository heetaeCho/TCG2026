// test_emitter_operator_cstr_47.cpp
#include <gtest/gtest.h>

#include <cstring>      // std::strlen
#include <sstream>      // std::stringstream
#include <string>

#include "yaml-cpp/emitter.h"

namespace {

class EmitterOperatorCStrTest_47 : public ::testing::Test {
 protected:
  static std::string Str(const YAML::Emitter& e) {
    const char* s = e.c_str();
    return s ? std::string(s) : std::string();
  }
};

TEST_F(EmitterOperatorCStrTest_47, ReturnsSameEmitterReference_47) {
  YAML::Emitter emitter;
  YAML::Emitter& ref = (emitter << "abc");
  EXPECT_EQ(&ref, &emitter);
}

TEST_F(EmitterOperatorCStrTest_47, MatchesWriteWithStrlenForNormalString_47) {
  const char* input = "hello world";

  YAML::Emitter via_op;
  YAML::Emitter via_write;

  via_op << input;
  via_write.Write(input, std::strlen(input));

  EXPECT_EQ(via_op.good(), via_write.good());
  EXPECT_EQ(via_op.GetLastError(), via_write.GetLastError());
  EXPECT_EQ(via_op.size(), via_write.size());
  EXPECT_EQ(Str(via_op), Str(via_write));
}

TEST_F(EmitterOperatorCStrTest_47, MatchesWriteWithZeroLengthForEmptyString_47) {
  const char* input = "";

  YAML::Emitter via_op;
  YAML::Emitter via_write;

  via_op << input;
  via_write.Write(input, std::strlen(input));  // 0

  EXPECT_EQ(via_op.good(), via_write.good());
  EXPECT_EQ(via_op.GetLastError(), via_write.GetLastError());
  EXPECT_EQ(via_op.size(), via_write.size());
  EXPECT_EQ(Str(via_op), Str(via_write));
}

TEST_F(EmitterOperatorCStrTest_47, UsesStrlenSoEmbeddedNullStopsEarly_47) {
  // "ab\0cd" has strlen == 2
  const char input[] = {'a', 'b', '\0', 'c', 'd', '\0'};

  YAML::Emitter via_op;
  YAML::Emitter via_write_len2;
  YAML::Emitter via_write_full;

  via_op << input;
  via_write_len2.Write(input, std::strlen(input));  // 2
  via_write_full.Write(input, 5);                   // includes embedded '\0'

  // Operator<< must match Write(input, strlen(input))
  EXPECT_EQ(via_op.good(), via_write_len2.good());
  EXPECT_EQ(via_op.GetLastError(), via_write_len2.GetLastError());
  EXPECT_EQ(via_op.size(), via_write_len2.size());
  EXPECT_EQ(Str(via_op), Str(via_write_len2));

  // And it should generally differ from writing the full buffer (size-based write).
  // We don't assume *how* it differs—only that it is not required to match.
  EXPECT_TRUE(Str(via_op) != Str(via_write_full) || via_op.size() != via_write_full.size());
}

TEST_F(EmitterOperatorCStrTest_47, CanBeChainedAndMatchesEquivalentWrites_47) {
  YAML::Emitter via_op;
  YAML::Emitter via_write;

  via_op << "a" << "b" << "c";

  via_write.Write("a", std::strlen("a"));
  via_write.Write("b", std::strlen("b"));
  via_write.Write("c", std::strlen("c"));

  EXPECT_EQ(via_op.good(), via_write.good());
  EXPECT_EQ(via_op.GetLastError(), via_write.GetLastError());
  EXPECT_EQ(via_op.size(), via_write.size());
  EXPECT_EQ(Str(via_op), Str(via_write));
}

#if GTEST_HAS_DEATH_TEST
TEST_F(EmitterOperatorCStrTest_47, DeathOnNullPointerInput_47) {
  // The operator implementation calls std::strlen(v), so nullptr is invalid/UB.
  // This test documents that passing nullptr is not supported and should crash
  // in typical builds.
  YAML::Emitter emitter;
  const char* null_str = nullptr;

  ASSERT_DEATH(
      {
        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast)
        emitter << null_str;
      },
      ".*");
}
#endif

}  // namespace
