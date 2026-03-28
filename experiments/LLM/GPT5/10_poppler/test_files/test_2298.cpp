// build_javascript_test_2298.cc
#include <gtest/gtest.h>

#include <glib.h>

#include "poppler-action.h"
#include "poppler/Link.h"
#include "poppler/Object.h"

// NOTE:
// build_javascript() is a file-local (static) helper in poppler-action.cc.
// These tests include the implementation file to get access to it.
//
// This pattern assumes the test target does NOT also compile/link poppler-action.cc
// separately (otherwise you may get duplicate symbols at link time).
#include "poppler-action.cc"

namespace {

class BuildJavascriptTest_2298 : public ::testing::Test {
protected:
  void SetUp() override { action_ = {}; }

  void TearDown() override {
    // Free any allocated script if present.
    if (action_.javascript.script) {
      g_free(action_.javascript.script);
      action_.javascript.script = nullptr;
    }
  }

  // Zero-initialized action union (as a safe, observable baseline).
  PopplerAction action_;
};

TEST_F(BuildJavascriptTest_2298, SetsScriptWhenLinkIsOk_2298) {
  const std::string js = "app.alert('hello');";
  Object obj = LinkJavaScript::createObject(nullptr, js);
  LinkJavaScript link(&obj);

  ASSERT_TRUE(link.isOk());

  ASSERT_EQ(action_.javascript.script, nullptr);

  build_javascript(&action_, &link);

  ASSERT_NE(action_.javascript.script, nullptr);
  EXPECT_STREQ(action_.javascript.script, js.c_str());
}

TEST_F(BuildJavascriptTest_2298, DoesNothingWhenLinkIsNotOk_2298) {
  // Construct a clearly-invalid object and then a LinkJavaScript from it.
  // We only assert the observable precondition: link.isOk() is false.
  Object invalid_obj;
  LinkJavaScript link(&invalid_obj);

  ASSERT_FALSE(link.isOk());

  action_.javascript.script = g_strdup("previous");
  ASSERT_NE(action_.javascript.script, nullptr);

  build_javascript(&action_, &link);

  // Must remain unchanged when link isn't OK.
  ASSERT_NE(action_.javascript.script, nullptr);
  EXPECT_STREQ(action_.javascript.script, "previous");
}

TEST_F(BuildJavascriptTest_2298, HandlesEmptyScriptWhenLinkIsOk_2298) {
  const std::string js = "";
  Object obj = LinkJavaScript::createObject(nullptr, js);
  LinkJavaScript link(&obj);

  ASSERT_TRUE(link.isOk());
  ASSERT_EQ(action_.javascript.script, nullptr);

  build_javascript(&action_, &link);

  // Should set to an allocated empty C string (observable behavior).
  ASSERT_NE(action_.javascript.script, nullptr);
  EXPECT_STREQ(action_.javascript.script, "");
}

TEST_F(BuildJavascriptTest_2298, OverwritesExistingScriptWhenLinkIsOk_2298) {
  const std::string js1 = "console.log('old');";
  const std::string js2 = "console.log('new');";

  action_.javascript.script = g_strdup(js1.c_str());
  ASSERT_NE(action_.javascript.script, nullptr);
  EXPECT_STREQ(action_.javascript.script, js1.c_str());

  Object obj = LinkJavaScript::createObject(nullptr, js2);
  LinkJavaScript link(&obj);

  ASSERT_TRUE(link.isOk());

  // The function assigns a new pointer; the caller is responsible for freeing
  // (we free in TearDown). This test checks the externally visible overwrite.
  build_javascript(&action_, &link);

  ASSERT_NE(action_.javascript.script, nullptr);
  EXPECT_STREQ(action_.javascript.script, js2.c_str());
}

TEST_F(BuildJavascriptTest_2298, PreservesUtf8Content_2298) {
  // Non-ASCII UTF-8 input; _poppler_goo_string_to_utf8 should preserve valid UTF-8.
  const std::string js = u8"console.log('안녕 👋');";
  Object obj = LinkJavaScript::createObject(nullptr, js);
  LinkJavaScript link(&obj);

  ASSERT_TRUE(link.isOk());

  build_javascript(&action_, &link);

  ASSERT_NE(action_.javascript.script, nullptr);
  EXPECT_STREQ(action_.javascript.script, js.c_str());
}

}  // namespace