// File: ./TestProjects/yaml-cpp/test/directives_test.cpp

#include <gtest/gtest.h>

#include <string>

#include "directives.h"

namespace {

class DirectivesTest_1 : public ::testing::Test {};

TEST_F(DirectivesTest_1, ReturnsMappedValueWhenHandleExistsInTags_1) {
  YAML::Directives dirs;
  dirs.tags["!foo!"] = "tag:example.com,2026:foo/";

  const YAML::Directives& cdirs = dirs;
  EXPECT_EQ(cdirs.TranslateTagHandle("!foo!"), "tag:example.com,2026:foo/");
}

TEST_F(DirectivesTest_1, ReturnsYamlCorePrefixForDoubleExclamationWhenNotMapped_1) {
  YAML::Directives dirs;

  const YAML::Directives& cdirs = dirs;
  EXPECT_EQ(cdirs.TranslateTagHandle("!!"), "tag:yaml.org,2002:");
}

TEST_F(DirectivesTest_1, ReturnsHandleItselfWhenNotMappedAndNotDoubleExclamation_1) {
  YAML::Directives dirs;

  const YAML::Directives& cdirs = dirs;
  EXPECT_EQ(cdirs.TranslateTagHandle("!bar!"), "!bar!");
}

TEST_F(DirectivesTest_1, EmptyHandleReturnsEmptyWhenNotMapped_1) {
  YAML::Directives dirs;

  const YAML::Directives& cdirs = dirs;
  EXPECT_EQ(cdirs.TranslateTagHandle(""), "");
}

TEST_F(DirectivesTest_1, TagMappingTakesPrecedenceOverDefaultDoubleExclamationBehavior_1) {
  YAML::Directives dirs;
  dirs.tags["!!"] = "tag:custom.example,2026:";

  const YAML::Directives& cdirs = dirs;
  EXPECT_EQ(cdirs.TranslateTagHandle("!!"), "tag:custom.example,2026:");
}

TEST_F(DirectivesTest_1, HandlesNonAsciiOrUnusualCharactersByReturningMappedOrOriginal_1) {
  YAML::Directives dirs;
  const std::string handle = u8"!태그!";
  const std::string mapped = u8"tag:example.com,2026:태그/";

  // Not mapped -> returns original handle
  {
    const YAML::Directives& cdirs = dirs;
    EXPECT_EQ(cdirs.TranslateTagHandle(handle), handle);
  }

  // Mapped -> returns mapped value
  dirs.tags[handle] = mapped;
  {
    const YAML::Directives& cdirs = dirs;
    EXPECT_EQ(cdirs.TranslateTagHandle(handle), mapped);
  }
}

TEST_F(DirectivesTest_1, LargeHandleNotMappedReturnsOriginal_1) {
  YAML::Directives dirs;
  std::string big(10'000, 'a');
  big.insert(big.begin(), '!');  // make it look like a handle-ish token

  const YAML::Directives& cdirs = dirs;
  EXPECT_EQ(cdirs.TranslateTagHandle(big), big);
}

}  // namespace
