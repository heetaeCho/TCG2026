// TEST_ID: 637
#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "yaml-cpp/ostream_wrapper.h"

// The function under test lives in emitterutils.cpp in namespace YAML::Utils.
namespace YAML {
namespace Utils {
bool WriteTagWithPrefix(ostream_wrapper& out, const std::string& prefix,
                        const std::string& tag);
}  // namespace Utils
}  // namespace YAML

namespace {

class WriteTagWithPrefixTest_637 : public ::testing::Test {
 protected:
  std::stringstream ss_;
  YAML::ostream_wrapper out_{ss_};
};

TEST_F(WriteTagWithPrefixTest_637, WritesBangPrefixBangTagOnSuccess_637) {
  const std::string prefix = "tag:example.com,2026:";
  const std::string tag = "myTag";

  const bool ok = YAML::Utils::WriteTagWithPrefix(out_, prefix, tag);

  EXPECT_TRUE(ok);
  EXPECT_EQ(ss_.str(), "!" + prefix + "!" + tag);
}

TEST_F(WriteTagWithPrefixTest_637, EmptyPrefixStillWritesLeadingBangBangTag_637) {
  const std::string prefix = "";
  const std::string tag = "local";

  const bool ok = YAML::Utils::WriteTagWithPrefix(out_, prefix, tag);

  EXPECT_TRUE(ok);
  EXPECT_EQ(ss_.str(), "!!" + tag);
}

TEST_F(WriteTagWithPrefixTest_637, EmptyTagStillWritesBangPrefixBang_637) {
  const std::string prefix = "tag:example.com,2026:";
  const std::string tag = "";

  const bool ok = YAML::Utils::WriteTagWithPrefix(out_, prefix, tag);

  EXPECT_TRUE(ok);
  EXPECT_EQ(ss_.str(), "!" + prefix + "!");
}

TEST_F(WriteTagWithPrefixTest_637, EmptyPrefixAndEmptyTagWritesDoubleBang_637) {
  const std::string prefix = "";
  const std::string tag = "";

  const bool ok = YAML::Utils::WriteTagWithPrefix(out_, prefix, tag);

  EXPECT_TRUE(ok);
  EXPECT_EQ(ss_.str(), "!!");
}

TEST_F(WriteTagWithPrefixTest_637, InvalidPrefixReturnsFalse_637) {
  // Space is commonly not valid in URI-style productions; this should exercise
  // an observable error path without relying on internal regex details.
  const std::string prefix = "tag:bad prefix:";
  const std::string tag = "ok";

  const bool ok = YAML::Utils::WriteTagWithPrefix(out_, prefix, tag);

  EXPECT_FALSE(ok);
  // Observable side effect: the function writes the initial '!' before validation.
  ASSERT_FALSE(ss_.str().empty());
  EXPECT_EQ(ss_.str().front(), '!');
}

TEST_F(WriteTagWithPrefixTest_637, InvalidTagReturnsFalse_637) {
  // Space is commonly not valid in tag suffix productions; this should exercise
  // an observable error path without relying on internal regex details.
  const std::string prefix = "tag:example.com,2026:";
  const std::string tag = "bad tag";

  const bool ok = YAML::Utils::WriteTagWithPrefix(out_, prefix, tag);

  EXPECT_FALSE(ok);
  // On any attempt, the function writes at least the initial '!' and, if the
  // prefix was acceptable, the separator '!' before validating the tag.
  ASSERT_FALSE(ss_.str().empty());
  EXPECT_EQ(ss_.str().front(), '!');
}

TEST_F(WriteTagWithPrefixTest_637, PrefixAndTagContainingOnlyPunctuationMayFailButIsObservable_637) {
  // Boundary-ish case: unusual but printable characters. We only assert that
  // the function returns a boolean and does not crash; output is observable.
  const std::string prefix = "tag:example.com,2026:";
  const std::string tag = "-_.:/";

  const bool ok = YAML::Utils::WriteTagWithPrefix(out_, prefix, tag);

  // If it succeeds, output format must match the documented concatenation.
  // If it fails, we only assert the failure is observable via return value.
  if (ok) {
    EXPECT_EQ(ss_.str(), "!" + prefix + "!" + tag);
  } else {
    EXPECT_FALSE(ok);
    ASSERT_FALSE(ss_.str().empty());
    EXPECT_EQ(ss_.str().front(), '!');
  }
}

}  // namespace