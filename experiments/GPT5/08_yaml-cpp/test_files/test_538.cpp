// TEST_ID: 538
#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include <yaml-cpp/emitter.h>
#include <yaml-cpp/emittermanip.h>
#include <yaml-cpp/exceptions.h>

namespace {

class WriteAliasTest_538 : public ::testing::Test {
 protected:
  std::stringstream out;
  YAML::Emitter emitter{out};
};

TEST_F(WriteAliasTest_538, WriteReturnsSameEmitterReference_538) {
  YAML::_Alias alias("myAlias");
  YAML::Emitter& ret = emitter.Write(alias);
  EXPECT_EQ(&ret, &emitter);
}

TEST_F(WriteAliasTest_538, WriteValidAliasKeepsEmitterGoodAndProducesOutput_538) {
  YAML::_Alias alias("myAlias");

  emitter.Write(alias);

  EXPECT_TRUE(emitter.good());
  EXPECT_EQ(emitter.GetLastError(), std::string());

  // Observable output should exist for a successfully written alias.
  const std::string s = out.str();
  EXPECT_FALSE(s.empty());

  // Public API consistency checks.
  EXPECT_EQ(emitter.size(), s.size());
  ASSERT_NE(emitter.c_str(), nullptr);
  EXPECT_EQ(std::string(emitter.c_str()), s);
}

TEST_F(WriteAliasTest_538, WriteValidAliasWithLongContentStillGood_538) {
  const std::string longName(1024, 'a');
  YAML::_Alias alias(longName);

  emitter.Write(alias);

  EXPECT_TRUE(emitter.good());
  EXPECT_EQ(emitter.GetLastError(), std::string());
  EXPECT_FALSE(out.str().empty());
}

TEST_F(WriteAliasTest_538, AliasAfterAnchorSetsInvalidAliasError_538) {
  // Anchor and Tag are public manipulators; writing an alias when either is already set
  // should produce INVALID_ALIAS per the implementation.
  YAML::_Anchor anchor("anc");
  YAML::_Alias alias("myAlias");

  emitter.Write(anchor);
  const std::string before = out.str();

  emitter.Write(alias);

  EXPECT_FALSE(emitter.good());
  EXPECT_EQ(emitter.GetLastError(), std::string(YAML::ErrorMsg::INVALID_ALIAS));

  // Once in an error state, further writes should be a no-op for output.
  emitter.Write(YAML::_Alias("another"));
  EXPECT_EQ(out.str(), before);
}

TEST_F(WriteAliasTest_538, AliasAfterTagSetsInvalidAliasError_538) {
  YAML::_Tag tag("!t");
  YAML::_Alias alias("myAlias");

  emitter.Write(tag);
  const std::string before = out.str();

  emitter.Write(alias);

  EXPECT_FALSE(emitter.good());
  EXPECT_EQ(emitter.GetLastError(), std::string(YAML::ErrorMsg::INVALID_ALIAS));

  // Verify subsequent calls short-circuit when !good().
  emitter.Write(YAML::_Alias("another"));
  EXPECT_EQ(out.str(), before);
}

}  // namespace