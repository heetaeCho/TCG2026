// TEST_ID: 518
#include <gtest/gtest.h>

#include <string>

#include "yaml-cpp/emitter.h"

namespace {

class EmitterSetStringFormatTest_518 : public ::testing::Test {
 protected:
  YAML::Emitter out;
};

TEST_F(EmitterSetStringFormatTest_518, DoubleQuotedForcesQuotesOnSimpleString_518) {
  const bool ok = out.SetStringFormat(YAML::DoubleQuoted);
  EXPECT_TRUE(ok);
  EXPECT_TRUE(out.good()) << out.GetLastError();

  out.Write(std::string("abc"));

  ASSERT_NE(out.c_str(), nullptr);
  EXPECT_STREQ(out.c_str(), "\"abc\"");
  EXPECT_EQ(out.size(), std::string("\"abc\"").size());
}

TEST_F(EmitterSetStringFormatTest_518, SingleQuotedForcesQuotesOnSimpleString_518) {
  const bool ok = out.SetStringFormat(YAML::SingleQuoted);
  EXPECT_TRUE(ok);
  EXPECT_TRUE(out.good()) << out.GetLastError();

  out.Write(std::string("abc"));

  ASSERT_NE(out.c_str(), nullptr);
  EXPECT_STREQ(out.c_str(), "'abc'");
  EXPECT_EQ(out.size(), std::string("'abc'").size());
}

TEST_F(EmitterSetStringFormatTest_518, ReapplyingSameFormatIsNonDestructive_518) {
  EXPECT_TRUE(out.SetStringFormat(YAML::DoubleQuoted));
  EXPECT_TRUE(out.good()) << out.GetLastError();

  // Apply the same setting again; should still succeed and remain good.
  EXPECT_TRUE(out.SetStringFormat(YAML::DoubleQuoted));
  EXPECT_TRUE(out.good()) << out.GetLastError();

  out.Write(std::string("abc"));
  ASSERT_NE(out.c_str(), nullptr);
  EXPECT_STREQ(out.c_str(), "\"abc\"");
}

TEST_F(EmitterSetStringFormatTest_518, InvalidManipulatorReturnsFalseOrReportsError_518) {
  // Use a value that is very unlikely to be a valid EMITTER_MANIP.
  const auto invalid = static_cast<YAML::EMITTER_MANIP>(0x7fffffff);

  const bool ok = out.SetStringFormat(invalid);
  EXPECT_FALSE(ok);

  // Observable error reporting is allowed via the public interface, but we avoid
  // over-assuming the exact mechanism: either good() flips false OR an error is set.
  const std::string err = out.GetLastError();
  EXPECT_TRUE(!out.good() || !err.empty());
}

TEST_F(EmitterSetStringFormatTest_518, SettingFormatDoesNotEmitOutputByItself_518) {
  ASSERT_NE(out.c_str(), nullptr);
  const std::string before(out.c_str());
  const std::size_t size_before = out.size();

  EXPECT_TRUE(out.SetStringFormat(YAML::DoubleQuoted));

  ASSERT_NE(out.c_str(), nullptr);
  EXPECT_EQ(std::string(out.c_str()), before);
  EXPECT_EQ(out.size(), size_before);
}

}  // namespace