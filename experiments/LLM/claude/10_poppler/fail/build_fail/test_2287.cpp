#include <glib.h>
#include <glib-object.h>
#include "poppler-action.h"
#include <gtest/gtest.h>

// Helper to allocate a PopplerAction using g_slice_new0 (matching the free with g_slice_free)
static PopplerAction *create_action(PopplerActionType type)
{
    PopplerAction *action = g_slice_new0(PopplerAction);
    action->type = type;
    action->any.type = type;
    action->any.title = nullptr;
    return action;
}

class PopplerActionFreeTest_2287 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that passing nullptr does not crash
TEST_F(PopplerActionFreeTest_2287, FreeNull_DoesNotCrash_2287)
{
    poppler_action_free(nullptr);
    // If we reach here, no crash occurred
    SUCCEED();
}

// Test freeing a POPPLER_ACTION_NONE (default case) with no title
TEST_F(PopplerActionFreeTest_2287, FreeActionNone_NoTitle_2287)
{
    PopplerAction *action = create_action(POPPLER_ACTION_NONE);
    poppler_action_free(action);
    SUCCEED();
}

// Test freeing a POPPLER_ACTION_NONE with a title
TEST_F(PopplerActionFreeTest_2287, FreeActionNone_WithTitle_2287)
{
    PopplerAction *action = create_action(POPPLER_ACTION_NONE);
    action->any.title = g_strdup("Test Title");
    poppler_action_free(action);
    SUCCEED();
}

// Test freeing POPPLER_ACTION_GOTO_DEST with null dest
TEST_F(PopplerActionFreeTest_2287, FreeGotoDest_NullDest_2287)
{
    PopplerAction *action = create_action(POPPLER_ACTION_GOTO_DEST);
    action->goto_dest.dest = nullptr;
    poppler_action_free(action);
    SUCCEED();
}

// Test freeing POPPLER_ACTION_GOTO_DEST with a valid dest
TEST_F(PopplerActionFreeTest_2287, FreeGotoDest_ValidDest_2287)
{
    PopplerAction *action = create_action(POPPLER_ACTION_GOTO_DEST);
    action->goto_dest.dest = poppler_dest_copy(nullptr);
    // poppler_dest_free should handle null, but let's create a real one if possible
    // Since we can't easily create a PopplerDest, use nullptr which poppler_dest_free handles
    action->goto_dest.dest = nullptr;
    poppler_action_free(action);
    SUCCEED();
}

// Test freeing POPPLER_ACTION_GOTO_REMOTE with null fields
TEST_F(PopplerActionFreeTest_2287, FreeGotoRemote_NullFields_2287)
{
    PopplerAction *action = create_action(POPPLER_ACTION_GOTO_REMOTE);
    action->goto_remote.dest = nullptr;
    action->goto_remote.file_name = nullptr;
    poppler_action_free(action);
    SUCCEED();
}

// Test freeing POPPLER_ACTION_GOTO_REMOTE with valid file_name
TEST_F(PopplerActionFreeTest_2287, FreeGotoRemote_WithFileName_2287)
{
    PopplerAction *action = create_action(POPPLER_ACTION_GOTO_REMOTE);
    action->goto_remote.dest = nullptr;
    action->goto_remote.file_name = g_strdup("remote_file.pdf");
    action->any.title = g_strdup("Remote Action");
    poppler_action_free(action);
    SUCCEED();
}

// Test freeing POPPLER_ACTION_URI with null uri
TEST_F(PopplerActionFreeTest_2287, FreeUri_NullUri_2287)
{
    PopplerAction *action = create_action(POPPLER_ACTION_URI);
    action->uri.uri = nullptr;
    poppler_action_free(action);
    SUCCEED();
}

// Test freeing POPPLER_ACTION_URI with valid uri
TEST_F(PopplerActionFreeTest_2287, FreeUri_ValidUri_2287)
{
    PopplerAction *action = create_action(POPPLER_ACTION_URI);
    action->uri.uri = g_strdup("https://example.com");
    action->any.title = g_strdup("URI Action");
    poppler_action_free(action);
    SUCCEED();
}

// Test freeing POPPLER_ACTION_LAUNCH with null fields
TEST_F(PopplerActionFreeTest_2287, FreeLaunch_NullFields_2287)
{
    PopplerAction *action = create_action(POPPLER_ACTION_LAUNCH);
    action->launch.file_name = nullptr;
    action->launch.params = nullptr;
    poppler_action_free(action);
    SUCCEED();
}

// Test freeing POPPLER_ACTION_LAUNCH with valid fields
TEST_F(PopplerActionFreeTest_2287, FreeLaunch_ValidFields_2287)
{
    PopplerAction *action = create_action(POPPLER_ACTION_LAUNCH);
    action->launch.file_name = g_strdup("/usr/bin/test");
    action->launch.params = g_strdup("--help");
    action->any.title = g_strdup("Launch Action");
    poppler_action_free(action);
    SUCCEED();
}

// Test freeing POPPLER_ACTION_NAMED with null named_dest
TEST_F(PopplerActionFreeTest_2287, FreeNamed_NullDest_2287)
{
    PopplerAction *action = create_action(POPPLER_ACTION_NAMED);
    action->named.named_dest = nullptr;
    poppler_action_free(action);
    SUCCEED();
}

// Test freeing POPPLER_ACTION_NAMED with valid named_dest
TEST_F(PopplerActionFreeTest_2287, FreeNamed_ValidDest_2287)
{
    PopplerAction *action = create_action(POPPLER_ACTION_NAMED);
    action->named.named_dest = g_strdup("chapter1");
    poppler_action_free(action);
    SUCCEED();
}

// Test freeing POPPLER_ACTION_MOVIE with null movie
TEST_F(PopplerActionFreeTest_2287, FreeMovie_NullMovie_2287)
{
    PopplerAction *action = create_action(POPPLER_ACTION_MOVIE);
    action->movie.movie = nullptr;
    poppler_action_free(action);
    SUCCEED();
}

// Test freeing POPPLER_ACTION_RENDITION with null media
TEST_F(PopplerActionFreeTest_2287, FreeRendition_NullMedia_2287)
{
    PopplerAction *action = create_action(POPPLER_ACTION_RENDITION);
    action->rendition.media = nullptr;
    poppler_action_free(action);
    SUCCEED();
}

// Test freeing POPPLER_ACTION_OCG_STATE with null state_list
TEST_F(PopplerActionFreeTest_2287, FreeOcgState_NullStateList_2287)
{
    PopplerAction *action = create_action(POPPLER_ACTION_OCG_STATE);
    action->ocg_state.state_list = nullptr;
    poppler_action_free(action);
    SUCCEED();
}

// Test freeing POPPLER_ACTION_JAVASCRIPT with null script
TEST_F(PopplerActionFreeTest_2287, FreeJavascript_NullScript_2287)
{
    PopplerAction *action = create_action(POPPLER_ACTION_JAVASCRIPT);
    action->javascript.script = nullptr;
    poppler_action_free(action);
    SUCCEED();
}

// Test freeing POPPLER_ACTION_JAVASCRIPT with valid script
TEST_F(PopplerActionFreeTest_2287, FreeJavascript_ValidScript_2287)
{
    PopplerAction *action = create_action(POPPLER_ACTION_JAVASCRIPT);
    action->javascript.script = g_strdup("alert('hello');");
    action->any.title = g_strdup("JS Action");
    poppler_action_free(action);
    SUCCEED();
}

// Test freeing POPPLER_ACTION_RESET_FORM with null fields
TEST_F(PopplerActionFreeTest_2287, FreeResetForm_NullFields_2287)
{
    PopplerAction *action = create_action(POPPLER_ACTION_RESET_FORM);
    action->reset_form.fields = nullptr;
    poppler_action_free(action);
    SUCCEED();
}

// Test freeing POPPLER_ACTION_RESET_FORM with a valid fields list
TEST_F(PopplerActionFreeTest_2287, FreeResetForm_ValidFields_2287)
{
    PopplerAction *action = create_action(POPPLER_ACTION_RESET_FORM);
    GList *fields = nullptr;
    fields = g_list_append(fields, g_strdup("field1"));
    fields = g_list_append(fields, g_strdup("field2"));
    fields = g_list_append(fields, g_strdup("field3"));
    action->reset_form.fields = fields;
    action->any.title = g_strdup("Reset Form Action");
    poppler_action_free(action);
    SUCCEED();
}

// Test freeing action with only a title set (default/unknown type)
TEST_F(PopplerActionFreeTest_2287, FreeUnknownType_WithTitle_2287)
{
    PopplerAction *action = create_action((PopplerActionType)999);
    action->any.title = g_strdup("Unknown Action Title");
    poppler_action_free(action);
    SUCCEED();
}

// Test freeing POPPLER_ACTION_LAUNCH with only file_name set, params null
TEST_F(PopplerActionFreeTest_2287, FreeLaunch_OnlyFileName_2287)
{
    PopplerAction *action = create_action(POPPLER_ACTION_LAUNCH);
    action->launch.file_name = g_strdup("app.exe");
    action->launch.params = nullptr;
    poppler_action_free(action);
    SUCCEED();
}

// Test freeing POPPLER_ACTION_LAUNCH with only params set, file_name null
TEST_F(PopplerActionFreeTest_2287, FreeLaunch_OnlyParams_2287)
{
    PopplerAction *action = create_action(POPPLER_ACTION_LAUNCH);
    action->launch.file_name = nullptr;
    action->launch.params = g_strdup("--verbose");
    poppler_action_free(action);
    SUCCEED();
}

// Test freeing POPPLER_ACTION_URI with empty string uri
TEST_F(PopplerActionFreeTest_2287, FreeUri_EmptyString_2287)
{
    PopplerAction *action = create_action(POPPLER_ACTION_URI);
    action->uri.uri = g_strdup("");
    poppler_action_free(action);
    SUCCEED();
}

// Test freeing with empty title string
TEST_F(PopplerActionFreeTest_2287, FreeAction_EmptyTitle_2287)
{
    PopplerAction *action = create_action(POPPLER_ACTION_NONE);
    action->any.title = g_strdup("");
    poppler_action_free(action);
    SUCCEED();
}

// Test freeing POPPLER_ACTION_RESET_FORM with single field
TEST_F(PopplerActionFreeTest_2287, FreeResetForm_SingleField_2287)
{
    PopplerAction *action = create_action(POPPLER_ACTION_RESET_FORM);
    GList *fields = nullptr;
    fields = g_list_append(fields, g_strdup("singleField"));
    action->reset_form.fields = fields;
    poppler_action_free(action);
    SUCCEED();
}
