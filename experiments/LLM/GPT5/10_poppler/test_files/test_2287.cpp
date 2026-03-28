// poppler-action-free-test_2287.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <glib-object.h>

extern "C" {
#include "poppler-action.h"
}

// NOTE: These tests treat poppler_action_free() as a black box.
// We validate only observable behavior: it should not crash for various inputs,
// and it should unref embedded GObjects when applicable.

namespace {

class PopplerActionFreeTest_2287 : public ::testing::Test {
protected:
  static PopplerAction* NewAction(PopplerActionType type, const char* title = nullptr) {
    // poppler_action_free() uses g_slice_free(PopplerAction, action),
    // so allocate with g_slice_new0 for correct pairing.
    PopplerAction* action = g_slice_new0(PopplerAction);
    action->type = type;
    action->any.title = title ? g_strdup(title) : nullptr;
    return action;
  }

  static void FreeAction(PopplerAction* action) { poppler_action_free(action); }

  static void WeakNotify(gpointer data, GObject* /*where_the_object_was*/) {
    auto* flag = static_cast<gboolean*>(data);
    *flag = TRUE;
  }
};

TEST_F(PopplerActionFreeTest_2287, NullActionDoesNothing_2287) {
  // Should be safe / no-crash.
  ASSERT_NO_FATAL_FAILURE(poppler_action_free(nullptr));
}

TEST_F(PopplerActionFreeTest_2287, FreesGotoDestWithNullDest_2287) {
  PopplerAction* action = NewAction(POPPLER_ACTION_GOTO_DEST, "t");
  action->goto_dest.dest = nullptr; // boundary: null sub-object
  ASSERT_NO_FATAL_FAILURE(FreeAction(action));
}

TEST_F(PopplerActionFreeTest_2287, FreesGotoRemoteWithNullDestAndNullFilename_2287) {
  PopplerAction* action = NewAction(POPPLER_ACTION_GOTO_REMOTE, "remote");
  action->goto_remote.dest = nullptr;
  action->goto_remote.file_name = nullptr;
  ASSERT_NO_FATAL_FAILURE(FreeAction(action));
}

TEST_F(PopplerActionFreeTest_2287, FreesGotoRemoteWithFilename_2287) {
  PopplerAction* action = NewAction(POPPLER_ACTION_GOTO_REMOTE, "");
  action->goto_remote.dest = nullptr;
  action->goto_remote.file_name = g_strdup("file.pdf");
  ASSERT_NO_FATAL_FAILURE(FreeAction(action));
}

TEST_F(PopplerActionFreeTest_2287, FreesUriWithNullUri_2287) {
  PopplerAction* action = NewAction(POPPLER_ACTION_URI, "u");
  action->uri.uri = nullptr;
  ASSERT_NO_FATAL_FAILURE(FreeAction(action));
}

TEST_F(PopplerActionFreeTest_2287, FreesUriWithUriString_2287) {
  PopplerAction* action = NewAction(POPPLER_ACTION_URI, "u2");
  action->uri.uri = g_strdup("https://example.com/");
  ASSERT_NO_FATAL_FAILURE(FreeAction(action));
}

TEST_F(PopplerActionFreeTest_2287, FreesLaunchWithNullStrings_2287) {
  PopplerAction* action = NewAction(POPPLER_ACTION_LAUNCH, "l");
  action->launch.file_name = nullptr;
  action->launch.params = nullptr;
  ASSERT_NO_FATAL_FAILURE(FreeAction(action));
}

TEST_F(PopplerActionFreeTest_2287, FreesLaunchWithStrings_2287) {
  PopplerAction* action = NewAction(POPPLER_ACTION_LAUNCH, "launch");
  action->launch.file_name = g_strdup("prog");
  action->launch.params = g_strdup("--help");
  ASSERT_NO_FATAL_FAILURE(FreeAction(action));
}

TEST_F(PopplerActionFreeTest_2287, FreesNamedWithNullNamedDest_2287) {
  PopplerAction* action = NewAction(POPPLER_ACTION_NAMED, "n");
  action->named.named_dest = nullptr;
  ASSERT_NO_FATAL_FAILURE(FreeAction(action));
}

TEST_F(PopplerActionFreeTest_2287, FreesNamedWithNamedDest_2287) {
  PopplerAction* action = NewAction(POPPLER_ACTION_NAMED, "n2");
  action->named.named_dest = g_strdup("SomeNamedDestination");
  ASSERT_NO_FATAL_FAILURE(FreeAction(action));
}

TEST_F(PopplerActionFreeTest_2287, FreesJavascriptWithNullScript_2287) {
  PopplerAction* action = NewAction(POPPLER_ACTION_JAVASCRIPT, "js");
  action->javascript.script = nullptr;
  ASSERT_NO_FATAL_FAILURE(FreeAction(action));
}

TEST_F(PopplerActionFreeTest_2287, FreesJavascriptWithScript_2287) {
  PopplerAction* action = NewAction(POPPLER_ACTION_JAVASCRIPT, "js2");
  action->javascript.script = g_strdup("app.alert('hi');");
  ASSERT_NO_FATAL_FAILURE(FreeAction(action));
}

TEST_F(PopplerActionFreeTest_2287, FreesResetFormWithNullFields_2287) {
  PopplerAction* action = NewAction(POPPLER_ACTION_RESET_FORM, "rf");
  action->reset_form.fields = nullptr;
  ASSERT_NO_FATAL_FAILURE(FreeAction(action));
}

TEST_F(PopplerActionFreeTest_2287, FreesResetFormWithFieldsList_2287) {
  PopplerAction* action = NewAction(POPPLER_ACTION_RESET_FORM, "rf2");

  // reset_form.fields is freed with g_list_free_full(..., g_free).
  // Use g_strdup strings so g_free is appropriate.
  GList* fields = nullptr;
  fields = g_list_append(fields, g_strdup("field1"));
  fields = g_list_append(fields, g_strdup("field2"));
  action->reset_form.fields = fields;

  ASSERT_NO_FATAL_FAILURE(FreeAction(action));
}

TEST_F(PopplerActionFreeTest_2287, FreesMovieWithNullMovieObject_2287) {
  PopplerAction* action = NewAction(POPPLER_ACTION_MOVIE, "m");
  action->movie.movie = nullptr;
  ASSERT_NO_FATAL_FAILURE(FreeAction(action));
}

TEST_F(PopplerActionFreeTest_2287, UnrefsMovieGObjectWhenPresent_2287) {
  PopplerAction* action = NewAction(POPPLER_ACTION_MOVIE, "m2");

  // Provide a real GObject instance. PopplerMovie is expected to be a GObject-derived type;
  // poppler_action_free() calls g_object_unref() on this pointer.
  GObject* obj = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
  gboolean finalized = FALSE;
  g_object_weak_ref(obj, &WeakNotify, &finalized);

  action->movie.movie = reinterpret_cast<PopplerMovie*>(obj);

  ASSERT_NO_FATAL_FAILURE(FreeAction(action));
  EXPECT_TRUE(finalized);
}

TEST_F(PopplerActionFreeTest_2287, FreesRenditionWithNullMedia_2287) {
  PopplerAction* action = NewAction(POPPLER_ACTION_RENDITION, "r");
  action->rendition.media = nullptr;
  ASSERT_NO_FATAL_FAILURE(FreeAction(action));
}

TEST_F(PopplerActionFreeTest_2287, UnrefsRenditionMediaGObjectWhenPresent_2287) {
  PopplerAction* action = NewAction(POPPLER_ACTION_RENDITION, "r2");

  // Provide a real GObject instance. PopplerMedia is expected to be a GObject-derived type;
  // poppler_action_free() calls g_object_unref() on this pointer.
  GObject* obj = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
  gboolean finalized = FALSE;
  g_object_weak_ref(obj, &WeakNotify, &finalized);

  action->rendition.media = reinterpret_cast<PopplerMedia*>(obj);

  ASSERT_NO_FATAL_FAILURE(FreeAction(action));
  EXPECT_TRUE(finalized);
}

TEST_F(PopplerActionFreeTest_2287, FreesOcgStateWithNullList_2287) {
  PopplerAction* action = NewAction(POPPLER_ACTION_OCG_STATE, "ocg");
  action->ocg_state.state_list = nullptr; // boundary: nullptr list
  ASSERT_NO_FATAL_FAILURE(FreeAction(action));
}

TEST_F(PopplerActionFreeTest_2287, FreesAnyTitleNull_2287) {
  // Boundary: title is nullptr.
  PopplerAction* action = NewAction(POPPLER_ACTION_URI, nullptr);
  action->uri.uri = g_strdup("https://example.com/");
  ASSERT_NO_FATAL_FAILURE(FreeAction(action));
}

TEST_F(PopplerActionFreeTest_2287, FreesUnknownOrDefaultTypeDoesNotCrash_2287) {
  // Exercise default: branch. Use a value outside the known enum range.
  PopplerAction* action = NewAction(static_cast<PopplerActionType>(-123), "weird");
  ASSERT_NO_FATAL_FAILURE(FreeAction(action));
}

} // namespace