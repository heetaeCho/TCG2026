// LinkJavaScript_tests_324.cpp
// Unit tests for poppler::LinkJavaScript (getScript / basic observable behavior)
//
// The TEST_ID is 324

#include <gtest/gtest.h>

#include <string>

#include "Link.h"   // LinkJavaScript, LinkActionKind
#include "Object.h" // Object
#include "XRef.h"   // XRef (may be forward-declared in your build; include if available)

namespace {

// Helper: construct a LinkJavaScript via the public factory (if available) and ctor(Object*).
// We keep Object alive for the lifetime of LinkJavaScript in each test.
struct JsActionBuilder {
  Object obj;
  LinkJavaScript *action = nullptr;

  explicit JsActionBuilder(const std::string &js, XRef *xref = nullptr) {
    obj = LinkJavaScript::createObject(xref, js);
    action = new LinkJavaScript(&obj);
  }

  ~JsActionBuilder() { delete action; }

  LinkJavaScript &get() { return *action; }
};

class LinkJavaScriptTest_324 : public ::testing::Test {};

} // namespace

TEST_F(LinkJavaScriptTest_324, GetScript_ReturnsStableReference_324) {
  JsActionBuilder b("var x = 1;");

  const std::string &s1 = b.get().getScript();
  const std::string &s2 = b.get().getScript();

  // Same reference across calls (observable via address).
  EXPECT_EQ(&s1, &s2);
}

TEST_F(LinkJavaScriptTest_324, CreateObjectAndCtor_PreservesScriptContent_Normal_324) {
  const std::string js = "app.alert('hello');";
  JsActionBuilder b(js);

  EXPECT_EQ(b.get().getScript(), js);
}

TEST_F(LinkJavaScriptTest_324, EmptyScript_IsHandled_Boundary_324) {
  JsActionBuilder b("");

  // Observable: getScript returns a string reference; content should match the input JS for factory-created object.
  EXPECT_TRUE(b.get().getScript().empty());
}

TEST_F(LinkJavaScriptTest_324, LargeScript_IsHandled_Boundary_324) {
  std::string js(64 * 1024, 'a'); // 64 KiB
  js.replace(0, 16, "function f(){");
  js.append("} f();");

  JsActionBuilder b(js);

  EXPECT_EQ(b.get().getScript().size(), js.size());
  EXPECT_EQ(b.get().getScript(), js);
}

TEST_F(LinkJavaScriptTest_324, NonAsciiScript_IsPreserved_Boundary_324) {
  // UTF-8 literal content
  const std::string js = u8"console.log('안녕하세요 🌍');";
  JsActionBuilder b(js);

  EXPECT_EQ(b.get().getScript(), js);
}

TEST_F(LinkJavaScriptTest_324, IsOkAndGetKind_AreCallable_Normal_324) {
  JsActionBuilder b("var ok = true;");

  // Observable behavior through interface: these calls should be valid.
  EXPECT_NO_THROW((void)b.get().isOk());
  EXPECT_NO_THROW((void)b.get().getKind());

  // When built through createObject, it should be a JavaScript action kind.
  // (If your enum name differs, adjust accordingly.)
  EXPECT_EQ(b.get().getKind(), actionJavaScript);
}

TEST_F(LinkJavaScriptTest_324, CtorWithNullObject_DoesNotCrash_ErrorCase_324) {
  // Error/exceptional case: construct with nullptr and ensure interface calls are safe.
  // We do NOT assert specific internal outcomes beyond being callable.
  LinkJavaScript a(nullptr);

  EXPECT_NO_THROW((void)a.isOk());
  EXPECT_NO_THROW((void)a.getKind());
  EXPECT_NO_THROW((void)a.getScript());

  // Also ensure getScript returns a valid reference (addressable).
  const std::string &s = a.getScript();
  EXPECT_NE(&s, nullptr);
}