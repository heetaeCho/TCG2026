#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <glib.h>

// Poppler glib headers
extern "C" {
#include <poppler.h>
}

#include <cstdio>
#include <cstdlib>
#include <string>
#include <memory>

class PopplerActionOCGStateTest_2302 : public ::testing::Test {
protected:
    void SetUp() override {
        doc_ = nullptr;
    }

    void TearDown() override {
        if (doc_) {
            g_object_unref(doc_);
            doc_ = nullptr;
        }
    }

    PopplerDocument *loadDocument(const char *path) {
        GError *error = nullptr;
        gchar *uri = g_filename_to_uri(path, nullptr, &error);
        if (!uri) {
            if (error) {
                g_error_free(error);
            }
            return nullptr;
        }
        PopplerDocument *doc = poppler_document_new_from_file(uri, nullptr, &error);
        g_free(uri);
        if (error) {
            g_error_free(error);
        }
        return doc;
    }

    PopplerDocument *doc_;
};

// Test that PopplerAction type enum includes OCG state
TEST_F(PopplerActionOCGStateTest_2302, ActionTypeOCGStateExists_2302) {
    // Verify the OCG state action type constant exists and has expected value
    PopplerActionType type = POPPLER_ACTION_OCG_STATE;
    EXPECT_EQ(type, POPPLER_ACTION_OCG_STATE);
}

// Test that layer action enum values exist
TEST_F(PopplerActionOCGStateTest_2302, LayerActionEnumValues_2302) {
    EXPECT_EQ(POPPLER_ACTION_LAYER_ON, 0);
    EXPECT_EQ(POPPLER_ACTION_LAYER_OFF, 1);
    EXPECT_EQ(POPPLER_ACTION_LAYER_TOGGLE, 2);
}

// Test that PopplerAction union has ocg_state member accessible
TEST_F(PopplerActionOCGStateTest_2302, ActionUnionHasOCGStateMember_2302) {
    PopplerAction action;
    memset(&action, 0, sizeof(action));
    // Verify we can access the ocg_state member of the union
    action.ocg_state.type = POPPLER_ACTION_OCG_STATE;
    EXPECT_EQ(action.ocg_state.type, POPPLER_ACTION_OCG_STATE);
}

// Test that a null state_list is handled (empty initialization)
TEST_F(PopplerActionOCGStateTest_2302, EmptyOCGStateList_2302) {
    PopplerAction action;
    memset(&action, 0, sizeof(action));
    action.ocg_state.type = POPPLER_ACTION_OCG_STATE;
    // state_list should be null when not populated
    EXPECT_EQ(action.ocg_state.state_list, nullptr);
}

// Test poppler_action_copy and poppler_action_free with OCG state action
TEST_F(PopplerActionOCGStateTest_2302, ActionCopyFreeNullStateList_2302) {
    PopplerAction *action = static_cast<PopplerAction *>(g_malloc0(sizeof(PopplerAction)));
    action->type = POPPLER_ACTION_OCG_STATE;
    action->ocg_state.type = POPPLER_ACTION_OCG_STATE;
    action->ocg_state.title = g_strdup("Test OCG Action");
    action->ocg_state.state_list = nullptr;

    PopplerAction *copy = poppler_action_copy(action);
    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->type, POPPLER_ACTION_OCG_STATE);
    EXPECT_STREQ(copy->ocg_state.title, "Test OCG Action");
    EXPECT_EQ(copy->ocg_state.state_list, nullptr);

    poppler_action_free(copy);
    poppler_action_free(action);
}

// Test that poppler_action_get_type returns valid GType
TEST_F(PopplerActionOCGStateTest_2302, ActionGetTypeValid_2302) {
    GType type = poppler_action_get_type();
    EXPECT_NE(type, G_TYPE_INVALID);
}

// Test poppler_action_free with nullptr doesn't crash
TEST_F(PopplerActionOCGStateTest_2302, ActionFreeNull_2302) {
    // poppler_action_free should handle NULL gracefully
    poppler_action_free(nullptr);
    SUCCEED();
}
