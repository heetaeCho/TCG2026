#include <gtest/gtest.h>

#include "poppler-action.h"



// Test fixture for poppler_action_free

class PopplerActionFreeTest_2287 : public ::testing::Test {

protected:

    void SetUp() override {

        // No setup required as the function is a free-standing function

    }



    void TearDown() override {

        // No teardown required

    }

};



// Test normal operation for different action types

TEST_F(PopplerActionFreeTest_2287, FreeGotoDestAction_2287) {

    PopplerAction *action = g_slice_new0(PopplerAction);

    action->type = POPPLER_ACTION_GOTO_DEST;

    action->goto_dest.dest = nullptr; // Assuming dest is already freed or not allocated

    poppler_action_free(action);

}



TEST_F(PopplerActionFreeTest_2287, FreeGotoRemoteAction_2287) {

    PopplerAction *action = g_slice_new0(PopplerAction);

    action->type = POPPLER_ACTION_GOTO_REMOTE;

    action->goto_remote.dest = nullptr; // Assuming dest is already freed or not allocated

    action->goto_remote.file_name = g_strdup("example.pdf");

    poppler_action_free(action);

}



TEST_F(PopplerActionFreeTest_2287, FreeUriAction_2287) {

    PopplerAction *action = g_slice_new0(PopplerAction);

    action->type = POPPLER_ACTION_URI;

    action->uri.uri = g_strdup("http://example.com");

    poppler_action_free(action);

}



TEST_F(PopplerActionFreeTest_2287, FreeLaunchAction_2287) {

    PopplerAction *action = g_slice_new0(PopplerAction);

    action->type = POPPLER_ACTION_LAUNCH;

    action->launch.file_name = g_strdup("example.exe");

    action->launch.params = g_strdup("--param");

    poppler_action_free(action);

}



TEST_F(PopplerActionFreeTest_2287, FreeNamedAction_2287) {

    PopplerAction *action = g_slice_new0(PopplerAction);

    action->type = POPPLER_ACTION_NAMED;

    action->named.named_dest = g_strdup("example");

    poppler_action_free(action);

}



TEST_F(PopplerActionFreeTest_2287, FreeMovieAction_2287) {

    PopplerAction *action = g_slice_new0(PopplerAction);

    action->type = POPPLER_ACTION_MOVIE;

    action->movie.movie = nullptr; // Assuming movie is already freed or not allocated

    poppler_action_free(action);

}



TEST_F(PopplerActionFreeTest_2287, FreeRenditionAction_2287) {

    PopplerAction *action = g_slice_new0(PopplerAction);

    action->type = POPPLER_ACTION_RENDITION;

    action->rendition.media = nullptr; // Assuming media is already freed or not allocated

    poppler_action_free(action);

}



TEST_F(PopplerActionFreeTest_2287, FreeOcgStateAction_2287) {

    PopplerAction *action = g_slice_new0(PopplerAction);

    action->type = POPPLER_ACTION_OCG_STATE;

    action->ocg_state.state_list = nullptr; // Assuming state_list is already freed or not allocated

    poppler_action_free(action);

}



TEST_F(PopplerActionFreeTest_2287, FreeJavascriptAction_2287) {

    PopplerAction *action = g_slice_new0(PopplerAction);

    action->type = POPPLER_ACTION_JAVASCRIPT;

    action->javascript.script = g_strdup("alert('test');");

    poppler_action_free(action);

}



TEST_F(PopplerActionFreeTest_2287, FreeResetFormAction_2287) {

    PopplerAction *action = g_slice_new0(PopplerAction);

    action->type = POPPLER_ACTION_RESET_FORM;

    action->reset_form.fields = nullptr; // Assuming fields is already freed or not allocated

    poppler_action_free(action);

}



// Test boundary condition for null action

TEST_F(PopplerActionFreeTest_2287, FreeNullAction_2287) {

    PopplerAction *action = nullptr;

    poppler_action_free(action); // Should handle nullptr gracefully

}



// Test boundary condition for unknown action type

TEST_F(PopplerActionFreeTest_2287, FreeUnknownTypeAction_2287) {

    PopplerAction *action = g_slice_new0(PopplerAction);

    action->type = static_cast<PopplerActionType>(-1); // Assuming an invalid type

    poppler_action_free(action); // Should handle unknown types gracefully

}
