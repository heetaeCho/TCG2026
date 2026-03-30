// TEST_ID: 127
#include <gtest/gtest.h>

#include "exp.h"
#include "regex_yaml.h"

namespace {

class Utf8ByteOrderMarkTest_127 : public ::testing::Test {};

TEST_F(Utf8ByteOrderMarkTest_127, ReturnsSameStaticInstance_127) {
  const YAML::RegEx* p1 = &YAML::Exp::Utf8_ByteOrderMark();
  const YAML::RegEx* p2 = &YAML::Exp::Utf8_ByteOrderMark();
  EXPECT_EQ(p1, p2);
}

TEST_F(Utf8ByteOrderMarkTest_127, MatchesExactUtf8BomSequence_127) {
  const auto& bom = YAML::Exp::Utf8_ByteOrderMark();

  const std::string kBom("\xEF\xBB\xBF", 3);
  EXPECT_TRUE(bom.Matches(kBom));
}

TEST_F(Utf8ByteOrderMarkTest_127, DoesNotMatchEmptyString_127) {
  const auto& bom = YAML::Exp::Utf8_ByteOrderMark();
  EXPECT_FALSE(bom.Matches(std::string()));
}

TEST_F(Utf8ByteOrderMarkTest_127, DoesNotMatchDifferentBytesSameLength_127) {
  const auto& bom = YAML::Exp::Utf8_ByteOrderMark();

  // Same length (3) but different content than UTF-8 BOM.
  const std::string not_bom("\xEF\xBB\xBE", 3);
  EXPECT_FALSE(bom.Matches(not_bom));
}

TEST_F(Utf8ByteOrderMarkTest_127, DoesNotMatchPartialPrefix_127) {
  const auto& bom = YAML::Exp::Utf8_ByteOrderMark();

  const std::string partial1("\xEF", 1);
  const std::string partial2("\xEF\xBB", 2);

  EXPECT_FALSE(bom.Matches(partial1));
  EXPECT_FALSE(bom.Matches(partial2));
}

}  // namespace
