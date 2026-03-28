// poppler-action-copy-test_2288.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <glib-object.h>

// Prefer the public Poppler headers if available in your build.
// poppler-action.h usually comes from poppler-glib.
#include "poppler-action.h"

// Some builds expose poppler_action_free() via poppler.h.
// If your build does not, you may need to include the correct header that declares it.
#if __has_include("poppler.h")
#include "poppler.h"
#endif

namespace {

class PopplerActionCopyTest_2288 : public ::testing::Test {
protected:
  static void FreeAction(PopplerAction* action) {
    if (!action)
      return;

#if defined(POPPLER_TYPE_ACTION) || __has_include("poppler.h")
    // poppler_action_free() is part of the poppler-glib API in typical builds.
    poppler_action_free(action);
#else
    // Fallback (best-effort) if poppler_action_free() is not available in your build.
    // This intentionally does NOT attempt to deep-free fields (to avoid re-implementing logic).
    // If this path is taken, consider wiring poppler_action_free() into your test build.
    g_slice_free(PopplerAction, action);
#endif
  }

  static PopplerAction* NewZeroedAction() {
    return static_cast<PopplerAction*>(g_slice_new0(PopplerAction));
  }
};

TEST_F(PopplerActionCopyTest_2288, NullActionReturnsNull_2288) {
  // g_return_val_if_fail(action != nullptr, NULL)
  EXPECT_EQ(poppler_action_copy(nullptr), nullptr);
}

TEST_F(PopplerActionCopyTest_2288, UriActionCopiesTypeTitleAndUri_2288) {
  PopplerAction* action = NewZeroedAction();
  ASSERT_NE(action, nullptr);

  action->uri.type = POPPLER_ACTION_URI;
  action->any.title = g_strdup("My Title");
  action->uri.uri = g_strdup("https://example.com/");

  PopplerAction* copied = poppler_action_copy(action);
  ASSERT_NE(copied, nullptr);
  EXPECT_NE(copied, action);

  EXPECT_EQ(copied->uri.type, POPPLER_ACTION_URI);
  ASSERT_NE(copied->any.title, nullptr);
  ASSERT_NE(copied->uri.uri, nullptr);

  EXPECT_STREQ(copied->any.title, "My Title");
  EXPECT_STREQ(copied->uri.uri, "https://example.com/");

  // Strings should be duplicated (different pointers).
  EXPECT_NE(copied->any.title, action->any.title);
  EXPECT_NE(copied->uri.uri, action->uri.uri);

  FreeAction(action);
  FreeAction(copied);
}

TEST_F(PopplerActionCopyTest_2288, UriActionHandlesNullTitleAndNullUri_2288) {
  PopplerAction* action = NewZeroedAction();
  ASSERT_NE(action, nullptr);

  action->uri.type = POPPLER_ACTION_URI;
  action->any.title = nullptr;
  action->uri.uri = nullptr;

  PopplerAction* copied = poppler_action_copy(action);
  ASSERT_NE(copied, nullptr);

  EXPECT_EQ(copied->uri.type, POPPLER_ACTION_URI);
  EXPECT_EQ(copied->any.title, nullptr);
  EXPECT_EQ(copied->uri.uri, nullptr);

  FreeAction(action);
  FreeAction(copied);
}

TEST_F(PopplerActionCopyTest_2288, LaunchActionCopiesOptionalStrings_2288) {
  PopplerAction* action = NewZeroedAction();
  ASSERT_NE(action, nullptr);

  action->launch.type = POPPLER_ACTION_LAUNCH;
  action->any.title = g_strdup("Launch");
  action->launch.file_name = g_strdup("/tmp/test.bin");
  action->launch.params = g_strdup("--flag=1");

  PopplerAction* copied = poppler_action_copy(action);
  ASSERT_NE(copied, nullptr);

  EXPECT_EQ(copied->launch.type, POPPLER_ACTION_LAUNCH);

  ASSERT_NE(copied->any.title, nullptr);
  EXPECT_STREQ(copied->any.title, "Launch");
  EXPECT_NE(copied->any.title, action->any.title);

  ASSERT_NE(copied->launch.file_name, nullptr);
  EXPECT_STREQ(copied->launch.file_name, "/tmp/test.bin");
  EXPECT_NE(copied->launch.file_name, action->launch.file_name);

  ASSERT_NE(copied->launch.params, nullptr);
  EXPECT_STREQ(copied->launch.params, "--flag=1");
  EXPECT_NE(copied->launch.params, action->launch.params);

  FreeAction(action);
  FreeAction(copied);
}

TEST_F(PopplerActionCopyTest_2288, LaunchActionHandlesNullOptionalStrings_2288) {
  PopplerAction* action = NewZeroedAction();
  ASSERT_NE(action, nullptr);

  action->launch.type = POPPLER_ACTION_LAUNCH;
  action->any.title = nullptr;
  action->launch.file_name = nullptr;
  action->launch.params = nullptr;

  PopplerAction* copied = poppler_action_copy(action);
  ASSERT_NE(copied, nullptr);

  EXPECT_EQ(copied->launch.type, POPPLER_ACTION_LAUNCH);
  EXPECT_EQ(copied->any.title, nullptr);
  EXPECT_EQ(copied->launch.file_name, nullptr);
  EXPECT_EQ(copied->launch.params, nullptr);

  FreeAction(action);
  FreeAction(copied);
}

TEST_F(PopplerActionCopyTest_2288, NamedActionCopiesNamedDestination_2288) {
  PopplerAction* action = NewZeroedAction();
  ASSERT_NE(action, nullptr);

  action->named.type = POPPLER_ACTION_NAMED;
  action->any.title = g_strdup("Named");
  action->named.named_dest = g_strdup("SomeNamedDest");

  PopplerAction* copied = poppler_action_copy(action);
  ASSERT_NE(copied, nullptr);

  EXPECT_EQ(copied->named.type, POPPLER_ACTION_NAMED);

  ASSERT_NE(copied->any.title, nullptr);
  EXPECT_STREQ(copied->any.title, "Named");
  EXPECT_NE(copied->any.title, action->any.title);

  ASSERT_NE(copied->named.named_dest, nullptr);
  EXPECT_STREQ(copied->named.named_dest, "SomeNamedDest");
  EXPECT_NE(copied->named.named_dest, action->named.named_dest);

  FreeAction(action);
  FreeAction(copied);
}

TEST_F(PopplerActionCopyTest_2288, JavascriptActionCopiesScript_2288) {
  PopplerAction* action = NewZeroedAction();
  ASSERT_NE(action, nullptr);

  action->javascript.type = POPPLER_ACTION_JAVASCRIPT;
  action->any.title = g_strdup("JS");
  action->javascript.script = g_strdup("app.alert('hi');");

  PopplerAction* copied = poppler_action_copy(action);
  ASSERT_NE(copied, nullptr);

  EXPECT_EQ(copied->javascript.type, POPPLER_ACTION_JAVASCRIPT);

  ASSERT_NE(copied->any.title, nullptr);
  EXPECT_STREQ(copied->any.title, "JS");
  EXPECT_NE(copied->any.title, action->any.title);

  ASSERT_NE(copied->javascript.script, nullptr);
  EXPECT_STREQ(copied->javascript.script, "app.alert('hi');");
  EXPECT_NE(copied->javascript.script, action->javascript.script);

  FreeAction(action);
  FreeAction(copied);
}

TEST_F(PopplerActionCopyTest_2288, ResetFormActionCopiesFieldsList_2288) {
  PopplerAction* action = NewZeroedAction();
  ASSERT_NE(action, nullptr);

  action->reset_form.type = POPPLER_ACTION_RESET_FORM;
  action->any.title = g_strdup("Reset");

  // Create a list of field names.
  action->reset_form.fields = nullptr;
  action->reset_form.fields = g_list_append(action->reset_form.fields, g_strdup("fieldA"));
  action->reset_form.fields = g_list_append(action->reset_form.fields, g_strdup("fieldB"));
  action->reset_form.fields = g_list_append(action->reset_form.fields, g_strdup("fieldC"));

  PopplerAction* copied = poppler_action_copy(action);
  ASSERT_NE(copied, nullptr);

  EXPECT_EQ(copied->reset_form.type, POPPLER_ACTION_RESET_FORM);
  ASSERT_NE(copied->reset_form.fields, nullptr);

  // Boundary/observable behavior: list length and string contents preserved.
  EXPECT_EQ(g_list_length(copied->reset_form.fields), 3u);

  const char* s0 = static_cast<const char*>(g_list_nth_data(copied->reset_form.fields, 0));
  const char* s1 = static_cast<const char*>(g_list_nth_data(copied->reset_form.fields, 1));
  const char* s2 = static_cast<const char*>(g_list_nth_data(copied->reset_form.fields, 2));

  ASSERT_NE(s0, nullptr);
  ASSERT_NE(s1, nullptr);
  ASSERT_NE(s2, nullptr);

  EXPECT_STREQ(s0, "fieldA");
  EXPECT_STREQ(s1, "fieldB");
  EXPECT_STREQ(s2, "fieldC");

  // Ensure copied list nodes are independent (pointer inequality at head is a minimal observable check).
  EXPECT_NE(copied->reset_form.fields, action->reset_form.fields);

  // And copied strings should be duplicated (at least compare first element pointer).
  const char* orig0 = static_cast<const char*>(g_list_nth_data(action->reset_form.fields, 0));
  ASSERT_NE(orig0, nullptr);
  EXPECT_NE(s0, orig0);

  FreeAction(action);
  FreeAction(copied);
}

TEST_F(PopplerActionCopyTest_2288, ResetFormActionHandlesNullFieldsList_2288) {
  PopplerAction* action = NewZeroedAction();
  ASSERT_NE(action, nullptr);

  action->reset_form.type = POPPLER_ACTION_RESET_FORM;
  action->any.title = g_strdup("Reset");
  action->reset_form.fields = nullptr;

  PopplerAction* copied = poppler_action_copy(action);
  ASSERT_NE(copied, nullptr);

  EXPECT_EQ(copied->reset_form.type, POPPLER_ACTION_RESET_FORM);
  EXPECT_EQ(copied->reset_form.fields, nullptr);

  FreeAction(action);
  FreeAction(copied);
}

struct FinalizeFlag_2288 {
  bool finalized = false;
};

static void WeakNotifySetFlag_2288(gpointer data, GObject* /*where_the_object_was*/) {
  auto* flag = static_cast<FinalizeFlag_2288*>(data);
  flag->finalized = true;
}

TEST_F(PopplerActionCopyTest_2288, MovieActionRefsGObjectSoLifetimeExtends_2288) {
  // poppler_action_copy() does: new_action->movie.movie = (PopplerMovie*) g_object_ref(action->movie.movie)
  PopplerAction* action = NewZeroedAction();
  ASSERT_NE(action, nullptr);

  action->movie.type = POPPLER_ACTION_MOVIE;
  action->any.title = g_strdup("Movie");

  // Use a plain GObject instance; implementation uses g_object_ref without type checking.
  GObject* obj = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
  ASSERT_NE(obj, nullptr);

  FinalizeFlag_2288 flag;
  g_object_weak_ref(obj, WeakNotifySetFlag_2288, &flag);

  action->movie.movie = reinterpret_cast<PopplerMovie*>(obj);

  PopplerAction* copied = poppler_action_copy(action);
  ASSERT_NE(copied, nullptr);
  ASSERT_NE(copied->movie.movie, nullptr);

  // Observable behavior: the pointer should be the same instance (ref'd), not duplicated.
  EXPECT_EQ(reinterpret_cast<GObject*>(copied->movie.movie), obj);

  // Drop our original reference. The copy should still hold a ref, so it should not finalize yet.
  g_object_unref(obj);
  EXPECT_FALSE(flag.finalized);

  // Now free the actions; at least the copied action should drop its ref, allowing finalize.
  FreeAction(action);
  FreeAction(copied);

  // After both actions are freed, object should be finalized.
  EXPECT_TRUE(flag.finalized);
}

TEST_F(PopplerActionCopyTest_2288, RenditionActionRefsGObjectSoLifetimeExtends_2288) {
  // poppler_action_copy() does: new_action->rendition.media = (PopplerMedia*) g_object_ref(action->rendition.media)
  PopplerAction* action = NewZeroedAction();
  ASSERT_NE(action, nullptr);

  action->rendition.type = POPPLER_ACTION_RENDITION;
  action->any.title = g_strdup("Rendition");

  GObject* obj = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
  ASSERT_NE(obj, nullptr);

  FinalizeFlag_2288 flag;
  g_object_weak_ref(obj, WeakNotifySetFlag_2288, &flag);

  action->rendition.media = reinterpret_cast<PopplerMedia*>(obj);

  PopplerAction* copied = poppler_action_copy(action);
  ASSERT_NE(copied, nullptr);
  ASSERT_NE(copied->rendition.media, nullptr);

  EXPECT_EQ(reinterpret_cast<GObject*>(copied->rendition.media), obj);

  g_object_unref(obj);
  EXPECT_FALSE(flag.finalized);

  FreeAction(action);
  FreeAction(copied);

  EXPECT_TRUE(flag.finalized);
}

}  // namespace