#include <gtest/gtest.h>

#include "poppler-action.h"



class PopplerActionTest_2288 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize any necessary resources here

    }



    void TearDown() override {

        // Clean up any resources used by the tests

    }

};



TEST_F(PopplerActionTest_2288, CopyNullPointer_2288) {

    PopplerAction* action = nullptr;

    PopplerAction* new_action = poppler_action_copy(action);

    EXPECT_EQ(new_action, nullptr);

}



TEST_F(PopplerActionTest_2288, CopyAnyTitle_2288) {

    PopplerAction action;

    action.any.title = g_strdup("Sample Title");

    PopplerAction* new_action = poppler_action_copy(&action);

    EXPECT_NE(new_action->any.title, nullptr);

    EXPECT_STREQ(new_action->any.title, "Sample Title");

    g_free(action.any.title);

    g_free(new_action->any.title);

    g_slice_free(PopplerAction, new_action);

}



TEST_F(PopplerActionTest_2288, CopyGotoDest_2288) {

    PopplerAction action;

    action.type = POPPLER_ACTION_GOTO_DEST;

    action.goto_dest.dest = reinterpret_cast<PopplerDest*>(0x1); // Mocking a valid dest pointer

    PopplerAction* new_action = poppler_action_copy(&action);

    EXPECT_EQ(new_action->goto_dest.dest, action.goto_dest.dest);

    g_slice_free(PopplerAction, new_action);

}



TEST_F(PopplerActionTest_2288, CopyGotoRemoteFileName_2288) {

    PopplerAction action;

    action.type = POPPLER_ACTION_GOTO_REMOTE;

    action.goto_remote.file_name = g_strdup("remote_file.pdf");

    PopplerAction* new_action = poppler_action_copy(&action);

    EXPECT_NE(new_action->goto_remote.file_name, nullptr);

    EXPECT_STREQ(new_action->goto_remote.file_name, "remote_file.pdf");

    g_free(action.goto_remote.file_name);

    g_free(new_action->goto_remote.file_name);

    g_slice_free(PopplerAction, new_action);

}



TEST_F(PopplerActionTest_2288, CopyUri_2288) {

    PopplerAction action;

    action.type = POPPLER_ACTION_URI;

    action.uri.uri = g_strdup("http://example.com");

    PopplerAction* new_action = poppler_action_copy(&action);

    EXPECT_NE(new_action->uri.uri, nullptr);

    EXPECT_STREQ(new_action->uri.uri, "http://example.com");

    g_free(action.uri.uri);

    g_free(new_action->uri.uri);

    g_slice_free(PopplerAction, new_action);

}



TEST_F(PopplerActionTest_2288, CopyLaunchFileNameParams_2288) {

    PopplerAction action;

    action.type = POPPLER_ACTION_LAUNCH;

    action.launch.file_name = g_strdup("app.exe");

    action.launch.params = g_strdup("/param1 /param2");

    PopplerAction* new_action = poppler_action_copy(&action);

    EXPECT_NE(new_action->launch.file_name, nullptr);

    EXPECT_STREQ(new_action->launch.file_name, "app.exe");

    EXPECT_NE(new_action->launch.params, nullptr);

    EXPECT_STREQ(new_action->launch.params, "/param1 /param2");

    g_free(action.launch.file_name);

    g_free(action.launch.params);

    g_free(new_action->launch.file_name);

    g_free(new_action->launch.params);

    g_slice_free(PopplerAction, new_action);

}



TEST_F(PopplerActionTest_2288, CopyNamedDest_2288) {

    PopplerAction action;

    action.type = POPPLER_ACTION_NAMED;

    action.named.named_dest = g_strdup("destination_name");

    PopplerAction* new_action = poppler_action_copy(&action);

    EXPECT_NE(new_action->named.named_dest, nullptr);

    EXPECT_STREQ(new_action->named.named_dest, "destination_name");

    g_free(action.named.named_dest);

    g_free(new_action->named.named_dest);

    g_slice_free(PopplerAction, new_action);

}



TEST_F(PopplerActionTest_2288, CopyMovieMedia_2288) {

    PopplerAction action;

    action.type = POPPLER_ACTION_MOVIE;

    action.movie.movie = reinterpret_cast<PopplerMovie*>(0x1); // Mocking a valid movie pointer

    PopplerAction* new_action = poppler_action_copy(&action);

    EXPECT_EQ(new_action->movie.movie, action.movie.movie);

    g_slice_free(PopplerAction, new_action);

}



TEST_F(PopplerActionTest_2288, CopyRenditionMedia_2288) {

    PopplerAction action;

    action.type = POPPLER_ACTION_RENDITION;

    action.rendition.media = reinterpret_cast<PopplerMedia*>(0x1); // Mocking a valid media pointer

    PopplerAction* new_action = poppler_action_copy(&action);

    EXPECT_EQ(new_action->rendition.media, action.rendition.media);

    g_slice_free(PopplerAction, new_action);

}



TEST_F(PopplerActionTest_2288, CopyOcgState_2288) {

    PopplerAction action;

    action.type = POPPLER_ACTION_OCG_STATE;

    GList* state_list = nullptr;

    PopplerActionLayer layer;

    state_list = g_list_prepend(state_list, &layer);

    action.ocg_state.state_list = state_list;



    PopplerAction* new_action = poppler_action_copy(&action);



    EXPECT_NE(new_action->ocg_state.state_list, nullptr);

    GList* l1 = action.ocg_state.state_list;

    GList* l2 = new_action->ocg_state.state_list;



    while (l1 && l2) {

        EXPECT_EQ(l1->data, l2->data);

        l1 = g_list_next(l1);

        l2 = g_list_next(l2);

    }



    g_list_free_full(action.ocg_state.state_list, nullptr);

    g_list_free_full(new_action->ocg_state.state_list, nullptr);



    g_slice_free(PopplerAction, new_action);

}



TEST_F(PopplerActionTest_2288, CopyJavascriptScript_2288) {

    PopplerAction action;

    action.type = POPPLER_ACTION_JAVASCRIPT;

    action.javascript.script = g_strdup("alert('hello');");

    PopplerAction* new_action = poppler_action_copy(&action);

    EXPECT_NE(new_action->javascript.script, nullptr);

    EXPECT_STREQ(new_action->javascript.script, "alert('hello');");

    g_free(action.javascript.script);

    g_free(new_action->javascript.script);

    g_slice_free(PopplerAction, new_action);

}



TEST_F(PopplerActionTest_2288, CopyResetFormFields_2288) {

    PopplerAction action;

    action.type = POPPLER_ACTION_RESET_FORM;

    GList* fields = nullptr;

    char* field1 = g_strdup("field1");

    char* field2 = g_strdup("field2");

    fields = g_list_append(fields, field1);

    fields = g_list_append(fields, field2);

    action.reset_form.fields = fields;



    PopplerAction* new_action = poppler_action_copy(&action);



    EXPECT_NE(new_action->reset_form.fields, nullptr);

    GList* iter1 = action.reset_form.fields;

    GList* iter2 = new_action->reset_form.fields;



    while (iter1 && iter2) {

        EXPECT_STREQ((char*)iter1->data, (char*)iter2->data);

        g_free(iter1->data);

        iter1 = g_list_next(iter1);

        g_free(iter2->data);

        iter2 = g_list_next(iter2);

    }



    g_list_free(action.reset_form.fields);

    g_list_free(new_action->reset_form.fields);



    g_slice_free(PopplerAction, new_action);

}
