#include <glib.h>
#include <glib-object.h>
#include <gtest/gtest.h>

// Include poppler glib headers
#include "poppler-action.h"
#include "poppler-movie.h"
#include "poppler-media.h"
#include "poppler.h"

class PopplerActionCopyTest_2288 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}

    // Helper to create a basic PopplerAction with a given type
    PopplerAction *createAction(PopplerActionType type) {
        PopplerAction *action = g_slice_new0(PopplerAction);
        action->type = type;
        action->any.title = nullptr;
        return action;
    }

    // Helper to create a PopplerDest
    PopplerDest *createDest() {
        PopplerDest *dest = g_slice_new0(PopplerDest);
        dest->type = POPPLER_DEST_XYZ;
        dest->page_num = 5;
        dest->left = 100.0;
        dest->top = 200.0;
        dest->zoom = 1.5;
        dest->named_dest = g_strdup("test_named_dest");
        dest->change_left = 1;
        dest->change_top = 1;
        dest->change_zoom = 1;
        return dest;
    }

    void freeAction(PopplerAction *action) {
        if (action) {
            poppler_action_free(action);
        }
    }
};

// Test that copying a null action returns null
TEST_F(PopplerActionCopyTest_2288, CopyNullAction_2288) {
    PopplerAction *result = poppler_action_copy(nullptr);
    EXPECT_EQ(result, nullptr);
}

// Test copying POPPLER_ACTION_URI with title and uri
TEST_F(PopplerActionCopyTest_2288, CopyUriAction_2288) {
    PopplerAction *action = createAction(POPPLER_ACTION_URI);
    action->any.title = g_strdup("Test URI Action");
    action->uri.uri = g_strdup("https://example.com");

    PopplerAction *copy = poppler_action_copy(action);

    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->type, POPPLER_ACTION_URI);
    EXPECT_STREQ(copy->any.title, "Test URI Action");
    EXPECT_STREQ(copy->uri.uri, "https://example.com");

    // Verify deep copy - pointers should be different
    EXPECT_NE(copy->any.title, action->any.title);
    EXPECT_NE(copy->uri.uri, action->uri.uri);

    freeAction(action);
    freeAction(copy);
}

// Test copying POPPLER_ACTION_URI with null uri
TEST_F(PopplerActionCopyTest_2288, CopyUriActionNullUri_2288) {
    PopplerAction *action = createAction(POPPLER_ACTION_URI);
    action->any.title = g_strdup("URI No URI");
    action->uri.uri = nullptr;

    PopplerAction *copy = poppler_action_copy(action);

    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->type, POPPLER_ACTION_URI);
    EXPECT_STREQ(copy->any.title, "URI No URI");
    EXPECT_EQ(copy->uri.uri, nullptr);

    freeAction(action);
    freeAction(copy);
}

// Test copying POPPLER_ACTION_GOTO_DEST
TEST_F(PopplerActionCopyTest_2288, CopyGotoDestAction_2288) {
    PopplerAction *action = createAction(POPPLER_ACTION_GOTO_DEST);
    action->any.title = g_strdup("Goto Dest");
    action->goto_dest.dest = createDest();

    PopplerAction *copy = poppler_action_copy(action);

    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->type, POPPLER_ACTION_GOTO_DEST);
    EXPECT_STREQ(copy->any.title, "Goto Dest");
    ASSERT_NE(copy->goto_dest.dest, nullptr);
    EXPECT_NE(copy->goto_dest.dest, action->goto_dest.dest);
    EXPECT_EQ(copy->goto_dest.dest->page_num, 5);
    EXPECT_EQ(copy->goto_dest.dest->type, POPPLER_DEST_XYZ);

    freeAction(action);
    freeAction(copy);
}

// Test copying POPPLER_ACTION_GOTO_REMOTE
TEST_F(PopplerActionCopyTest_2288, CopyGotoRemoteAction_2288) {
    PopplerAction *action = createAction(POPPLER_ACTION_GOTO_REMOTE);
    action->any.title = g_strdup("Goto Remote");
    action->goto_remote.dest = createDest();
    action->goto_remote.file_name = g_strdup("remote_file.pdf");

    PopplerAction *copy = poppler_action_copy(action);

    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->type, POPPLER_ACTION_GOTO_REMOTE);
    EXPECT_STREQ(copy->any.title, "Goto Remote");
    ASSERT_NE(copy->goto_remote.dest, nullptr);
    EXPECT_NE(copy->goto_remote.dest, action->goto_remote.dest);
    EXPECT_STREQ(copy->goto_remote.file_name, "remote_file.pdf");
    EXPECT_NE(copy->goto_remote.file_name, action->goto_remote.file_name);

    freeAction(action);
    freeAction(copy);
}

// Test copying POPPLER_ACTION_GOTO_REMOTE with null file_name
TEST_F(PopplerActionCopyTest_2288, CopyGotoRemoteNullFileName_2288) {
    PopplerAction *action = createAction(POPPLER_ACTION_GOTO_REMOTE);
    action->any.title = g_strdup("Goto Remote No File");
    action->goto_remote.dest = createDest();
    action->goto_remote.file_name = nullptr;

    PopplerAction *copy = poppler_action_copy(action);

    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->goto_remote.file_name, nullptr);

    freeAction(action);
    freeAction(copy);
}

// Test copying POPPLER_ACTION_LAUNCH
TEST_F(PopplerActionCopyTest_2288, CopyLaunchAction_2288) {
    PopplerAction *action = createAction(POPPLER_ACTION_LAUNCH);
    action->any.title = g_strdup("Launch Action");
    action->launch.file_name = g_strdup("program.exe");
    action->launch.params = g_strdup("--verbose --output=test");

    PopplerAction *copy = poppler_action_copy(action);

    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->type, POPPLER_ACTION_LAUNCH);
    EXPECT_STREQ(copy->any.title, "Launch Action");
    EXPECT_STREQ(copy->launch.file_name, "program.exe");
    EXPECT_NE(copy->launch.file_name, action->launch.file_name);
    EXPECT_STREQ(copy->launch.params, "--verbose --output=test");
    EXPECT_NE(copy->launch.params, action->launch.params);

    freeAction(action);
    freeAction(copy);
}

// Test copying POPPLER_ACTION_LAUNCH with null file_name and params
TEST_F(PopplerActionCopyTest_2288, CopyLaunchActionNullFields_2288) {
    PopplerAction *action = createAction(POPPLER_ACTION_LAUNCH);
    action->any.title = nullptr;
    action->launch.file_name = nullptr;
    action->launch.params = nullptr;

    PopplerAction *copy = poppler_action_copy(action);

    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->type, POPPLER_ACTION_LAUNCH);
    EXPECT_EQ(copy->any.title, nullptr);
    EXPECT_EQ(copy->launch.file_name, nullptr);
    EXPECT_EQ(copy->launch.params, nullptr);

    freeAction(action);
    freeAction(copy);
}

// Test copying POPPLER_ACTION_NAMED
TEST_F(PopplerActionCopyTest_2288, CopyNamedAction_2288) {
    PopplerAction *action = createAction(POPPLER_ACTION_NAMED);
    action->any.title = g_strdup("Named Action");
    action->named.named_dest = g_strdup("Chapter1");

    PopplerAction *copy = poppler_action_copy(action);

    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->type, POPPLER_ACTION_NAMED);
    EXPECT_STREQ(copy->any.title, "Named Action");
    EXPECT_STREQ(copy->named.named_dest, "Chapter1");
    EXPECT_NE(copy->named.named_dest, action->named.named_dest);

    freeAction(action);
    freeAction(copy);
}

// Test copying POPPLER_ACTION_NAMED with null named_dest
TEST_F(PopplerActionCopyTest_2288, CopyNamedActionNullDest_2288) {
    PopplerAction *action = createAction(POPPLER_ACTION_NAMED);
    action->any.title = g_strdup("Named No Dest");
    action->named.named_dest = nullptr;

    PopplerAction *copy = poppler_action_copy(action);

    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->named.named_dest, nullptr);

    freeAction(action);
    freeAction(copy);
}

// Test copying POPPLER_ACTION_JAVASCRIPT
TEST_F(PopplerActionCopyTest_2288, CopyJavascriptAction_2288) {
    PopplerAction *action = createAction(POPPLER_ACTION_JAVASCRIPT);
    action->any.title = g_strdup("JS Action");
    action->javascript.script = g_strdup("alert('hello');");

    PopplerAction *copy = poppler_action_copy(action);

    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->type, POPPLER_ACTION_JAVASCRIPT);
    EXPECT_STREQ(copy->any.title, "JS Action");
    EXPECT_STREQ(copy->javascript.script, "alert('hello');");
    EXPECT_NE(copy->javascript.script, action->javascript.script);

    freeAction(action);
    freeAction(copy);
}

// Test copying POPPLER_ACTION_JAVASCRIPT with null script
TEST_F(PopplerActionCopyTest_2288, CopyJavascriptActionNullScript_2288) {
    PopplerAction *action = createAction(POPPLER_ACTION_JAVASCRIPT);
    action->any.title = g_strdup("JS No Script");
    action->javascript.script = nullptr;

    PopplerAction *copy = poppler_action_copy(action);

    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->javascript.script, nullptr);

    freeAction(action);
    freeAction(copy);
}

// Test copying action with null title
TEST_F(PopplerActionCopyTest_2288, CopyActionNullTitle_2288) {
    PopplerAction *action = createAction(POPPLER_ACTION_URI);
    action->any.title = nullptr;
    action->uri.uri = g_strdup("https://notitle.com");

    PopplerAction *copy = poppler_action_copy(action);

    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->any.title, nullptr);
    EXPECT_STREQ(copy->uri.uri, "https://notitle.com");

    freeAction(action);
    freeAction(copy);
}

// Test copying POPPLER_ACTION_RESET_FORM with fields
TEST_F(PopplerActionCopyTest_2288, CopyResetFormAction_2288) {
    PopplerAction *action = createAction(POPPLER_ACTION_RESET_FORM);
    action->any.title = g_strdup("Reset Form");
    action->reset_form.fields = nullptr;
    action->reset_form.fields = g_list_append(action->reset_form.fields, g_strdup("field1"));
    action->reset_form.fields = g_list_append(action->reset_form.fields, g_strdup("field2"));
    action->reset_form.fields = g_list_append(action->reset_form.fields, g_strdup("field3"));

    PopplerAction *copy = poppler_action_copy(action);

    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->type, POPPLER_ACTION_RESET_FORM);
    EXPECT_STREQ(copy->any.title, "Reset Form");

    // Verify the fields list was deep copied
    ASSERT_NE(copy->reset_form.fields, nullptr);
    GList *orig_iter = action->reset_form.fields;
    GList *copy_iter = copy->reset_form.fields;

    int count = 0;
    while (orig_iter && copy_iter) {
        EXPECT_STREQ((char *)copy_iter->data, (char *)orig_iter->data);
        EXPECT_NE(copy_iter->data, orig_iter->data); // deep copy
        orig_iter = g_list_next(orig_iter);
        copy_iter = g_list_next(copy_iter);
        count++;
    }
    EXPECT_EQ(count, 3);
    EXPECT_EQ(orig_iter, nullptr);
    EXPECT_EQ(copy_iter, nullptr);

    freeAction(action);
    freeAction(copy);
}

// Test copying POPPLER_ACTION_RESET_FORM with null fields
TEST_F(PopplerActionCopyTest_2288, CopyResetFormActionNullFields_2288) {
    PopplerAction *action = createAction(POPPLER_ACTION_RESET_FORM);
    action->any.title = g_strdup("Reset Form Empty");
    action->reset_form.fields = nullptr;

    PopplerAction *copy = poppler_action_copy(action);

    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->reset_form.fields, nullptr);

    freeAction(action);
    freeAction(copy);
}

// Test that the copied action is a distinct object
TEST_F(PopplerActionCopyTest_2288, CopyReturnsDifferentPointer_2288) {
    PopplerAction *action = createAction(POPPLER_ACTION_URI);
    action->any.title = g_strdup("Distinct");
    action->uri.uri = g_strdup("https://distinct.com");

    PopplerAction *copy = poppler_action_copy(action);

    ASSERT_NE(copy, nullptr);
    EXPECT_NE(copy, action);

    freeAction(action);
    freeAction(copy);
}

// Test copying POPPLER_ACTION_NONE (default case)
TEST_F(PopplerActionCopyTest_2288, CopyNoneAction_2288) {
    PopplerAction *action = createAction(POPPLER_ACTION_NONE);
    action->any.title = g_strdup("None Action");

    PopplerAction *copy = poppler_action_copy(action);

    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->type, POPPLER_ACTION_NONE);
    EXPECT_STREQ(copy->any.title, "None Action");
    EXPECT_NE(copy->any.title, action->any.title);

    freeAction(action);
    freeAction(copy);
}

// Test copying action with empty string title
TEST_F(PopplerActionCopyTest_2288, CopyActionEmptyTitle_2288) {
    PopplerAction *action = createAction(POPPLER_ACTION_URI);
    action->any.title = g_strdup("");
    action->uri.uri = g_strdup("https://emptytitle.com");

    PopplerAction *copy = poppler_action_copy(action);

    ASSERT_NE(copy, nullptr);
    EXPECT_STREQ(copy->any.title, "");
    EXPECT_NE(copy->any.title, action->any.title);

    freeAction(action);
    freeAction(copy);
}

// Test copying URI action with empty uri string
TEST_F(PopplerActionCopyTest_2288, CopyUriActionEmptyUri_2288) {
    PopplerAction *action = createAction(POPPLER_ACTION_URI);
    action->any.title = g_strdup("Empty URI");
    action->uri.uri = g_strdup("");

    PopplerAction *copy = poppler_action_copy(action);

    ASSERT_NE(copy, nullptr);
    EXPECT_STREQ(copy->uri.uri, "");
    EXPECT_NE(copy->uri.uri, action->uri.uri);

    freeAction(action);
    freeAction(copy);
}

// Test type is preserved correctly for all basic types
TEST_F(PopplerActionCopyTest_2288, CopyPreservesType_2288) {
    PopplerActionType types[] = {
        POPPLER_ACTION_NONE,
        POPPLER_ACTION_URI,
        POPPLER_ACTION_NAMED,
        POPPLER_ACTION_JAVASCRIPT
    };

    for (auto type : types) {
        PopplerAction *action = createAction(type);
        action->any.title = g_strdup("Type Test");

        // Initialize type-specific fields to null to avoid issues
        switch (type) {
            case POPPLER_ACTION_URI:
                action->uri.uri = nullptr;
                break;
            case POPPLER_ACTION_NAMED:
                action->named.named_dest = nullptr;
                break;
            case POPPLER_ACTION_JAVASCRIPT:
                action->javascript.script = nullptr;
                break;
            default:
                break;
        }

        PopplerAction *copy = poppler_action_copy(action);
        ASSERT_NE(copy, nullptr);
        EXPECT_EQ(copy->type, type) << "Type mismatch for type: " << type;

        freeAction(action);
        freeAction(copy);
    }
}

// Test copying POPPLER_ACTION_RESET_FORM with single field
TEST_F(PopplerActionCopyTest_2288, CopyResetFormSingleField_2288) {
    PopplerAction *action = createAction(POPPLER_ACTION_RESET_FORM);
    action->any.title = g_strdup("Single Field");
    action->reset_form.fields = nullptr;
    action->reset_form.fields = g_list_append(action->reset_form.fields, g_strdup("only_field"));

    PopplerAction *copy = poppler_action_copy(action);

    ASSERT_NE(copy, nullptr);
    ASSERT_NE(copy->reset_form.fields, nullptr);
    EXPECT_EQ(g_list_length(copy->reset_form.fields), 1u);
    EXPECT_STREQ((char *)copy->reset_form.fields->data, "only_field");

    freeAction(action);
    freeAction(copy);
}

// Test copying Launch action with only file_name set (params null)
TEST_F(PopplerActionCopyTest_2288, CopyLaunchFileNameOnly_2288) {
    PopplerAction *action = createAction(POPPLER_ACTION_LAUNCH);
    action->any.title = g_strdup("Launch File Only");
    action->launch.file_name = g_strdup("app.exe");
    action->launch.params = nullptr;

    PopplerAction *copy = poppler_action_copy(action);

    ASSERT_NE(copy, nullptr);
    EXPECT_STREQ(copy->launch.file_name, "app.exe");
    EXPECT_EQ(copy->launch.params, nullptr);

    freeAction(action);
    freeAction(copy);
}

// Test copying Launch action with only params set (file_name null)
TEST_F(PopplerActionCopyTest_2288, CopyLaunchParamsOnly_2288) {
    PopplerAction *action = createAction(POPPLER_ACTION_LAUNCH);
    action->any.title = g_strdup("Launch Params Only");
    action->launch.file_name = nullptr;
    action->launch.params = g_strdup("--help");

    PopplerAction *copy = poppler_action_copy(action);

    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->launch.file_name, nullptr);
    EXPECT_STREQ(copy->launch.params, "--help");

    freeAction(action);
    freeAction(copy);
}
