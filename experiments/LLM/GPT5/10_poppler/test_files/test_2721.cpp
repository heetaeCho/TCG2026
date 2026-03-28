// myxmltokenreplace_test_2721.cc
#include <gtest/gtest.h>

#include <string>

// We need to test a file-local (static) function from pdftotext.cc.
// The common pattern is to include the .cc into this test TU so the
// static symbol is visible here.
//
// pdftotext.cc is a utility program and likely defines its own `main`.
// Rename it to avoid conflicting with gtest_main (or other test mains).
#define main pdftotext_tool_main_2721
#include "TestProjects/poppler/utils/pdftotext.cc"
#undef main

class MyXmlTokenReplaceTest_2721 : public ::testing::Test {};

TEST_F(MyXmlTokenReplaceTest_2721, ReplacesAllXmlSensitiveTokens_2721) {
  const std::string out = myXmlTokenReplace("&'\"<>");
  EXPECT_EQ(out, "&amp;&apos;&quot;&lt;&gt;");
}

TEST_F(MyXmlTokenReplaceTest_2721, LeavesStringWithoutTokensUnchanged_2721) {
  const char *in = "Hello World 123";
  const std::string out = myXmlTokenReplace(in);
  EXPECT_EQ(out, in);
}

TEST_F(MyXmlTokenReplaceTest_2721, HandlesEmptyString_2721) {
  const std::string out = myXmlTokenReplace("");
  EXPECT_TRUE(out.empty());
}

TEST_F(MyXmlTokenReplaceTest_2721, ReplacesMultipleAmpersands_2721) {
  const std::string out = myXmlTokenReplace("a && b & c");
  EXPECT_EQ(out, "a &amp;&amp; b &amp; c");
}

TEST_F(MyXmlTokenReplaceTest_2721, ReplacesMixedTokensInsideText_2721) {
  const std::string out = myXmlTokenReplace("Tom & Jerry's <tag> \"q\"");
  EXPECT_EQ(out, "Tom &amp; Jerry&apos;s &lt;tag&gt; &quot;q&quot;");
}

TEST_F(MyXmlTokenReplaceTest_2721, EscapesAmpersandBeforeOtherReplacements_2721) {
  // Observable behavior: '&' is replaced first, so pre-escaped entities
  // get their '&' re-escaped.
  const std::string out = myXmlTokenReplace("1 &lt; 2 &amp; 3 &gt; 0");
  EXPECT_EQ(out, "1 &amp;lt; 2 &amp;amp; 3 &amp;gt; 0");
}

#if GTEST_HAS_DEATH_TEST
TEST_F(MyXmlTokenReplaceTest_2721, NullptrInputDies_2721) {
  // std::string(inString) is undefined behavior for nullptr; a crash is observable.
  // Death tests are the safest way to assert this behavior without relying on internals.
  EXPECT_DEATH(
      {
        (void)myXmlTokenReplace(nullptr);
      },
      "");
}
#endif