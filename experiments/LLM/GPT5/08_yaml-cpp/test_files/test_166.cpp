// File: ./TestProjects/yaml-cpp/test/exp_str_test.cpp

#include <gtest/gtest.h>

#include <string>
#include <vector>

namespace YAML {
namespace Exp {
// Forward declaration (implementation lives in src/exp.cpp).
std::string Str(unsigned ch);
}  // namespace Exp
}  // namespace YAML

namespace {

class ExpStrTest_166 : public ::testing::Test {};

TEST_F(ExpStrTest_166, ReturnsSingleCharacterStringForTypicalAscii_166) {
  const std::string out = YAML::Exp::Str(static_cast<unsigned>('A'));
  ASSERT_EQ(out.size(), 1u);
  EXPECT_EQ(out[0], 'A');
}

TEST_F(ExpStrTest_166, HandlesNullByteAsSingleCharacterString_166) {
  const std::string out = YAML::Exp::Str(0u);
  ASSERT_EQ(out.size(), 1u);
  EXPECT_EQ(out[0], '\0');
}

TEST_F(ExpStrTest_166, HandlesByteValue255AsSingleCharacterString_166) {
  const unsigned input = 255u;
  const std::string out = YAML::Exp::Str(input);

  ASSERT_EQ(out.size(), 1u);

  // Compare as unsigned bytes to avoid signed-char pitfalls.
  const unsigned char got = static_cast<unsigned char>(out[0]);
  EXPECT_EQ(got, static_cast<unsigned char>(input));
}

TEST_F(ExpStrTest_166, DoesNotThrowForRepresentativeInputs_166) {
  const std::vector<unsigned> inputs = {
      0u, 1u, static_cast<unsigned>(' '), static_cast<unsigned>('z'), 127u, 128u, 255u};

  for (unsigned v : inputs) {
    EXPECT_NO_THROW({
      const std::string out = YAML::Exp::Str(v);
      EXPECT_EQ(out.size(), 1u);
    }) << "input=" << v;
  }
}

}  // namespace