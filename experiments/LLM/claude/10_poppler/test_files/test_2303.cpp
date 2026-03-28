#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <glib.h>

// Include necessary headers
#include "poppler-action.h"
#include "poppler-private.h"
#include "Link.h"

// We need to create mock/stub LinkAction subclasses for testing
// Since we treat the implementation as a black box, we create minimal
// concrete subclasses that return specific LinkActionKind values.

class MockLinkAction : public LinkAction {
public:
    MockLinkAction(LinkActionKind kind) : kind_(kind) {}
    ~MockLinkAction() override = default;
    LinkActionKind getKind() const override { return kind_; }
    bool isOk() const override { return true; }

private:
    LinkActionKind kind_;
};

// Minimal subclasses for specific action types
class MockLinkGoTo : public LinkGoTo {
public:
    MockLinkGoTo() : LinkGoTo() {}
    ~MockLinkGoTo() override = default;
    LinkActionKind getKind() const override { return actionGoTo; }
    bool isOk() const override { return true; }
};

class MockLinkURI : public LinkURI {
public:
    MockLinkURI(const std::string &uri) : LinkURI(uri) {}
    ~MockLinkURI() override = default;
    LinkActionKind getKind() const override { return actionURI; }
    bool isOk() const override { return true; }
};

class MockLinkNamed : public LinkNamed {
public:
    MockLinkNamed(const std::string &name) : LinkNamed(name) {}
    ~MockLinkNamed() override = default;
    LinkActionKind getKind() const override { return actionNamed; }
    bool isOk() const override { return true; }
};

class MockLinkJavaScript : public LinkJavaScript {
public:
    MockLinkJavaScript(const std::string &js) : LinkJavaScript(js) {}
    ~MockLinkJavaScript() override = default;
    LinkActionKind getKind() const override { return actionJavaScript; }
    bool isOk() const override { return true; }
};

class MockLinkLaunch : public LinkLaunch {
public:
    MockLinkLaunch() : LinkLaunch() {}
    ~MockLinkLaunch() override = default;
    LinkActionKind getKind() const override { return actionLaunch; }
    bool isOk() const override { return true; }
};

class PopplerActionTest_2303 : public ::testing::Test {
protected:
    void SetUp() override {
        // We don't need a real PopplerDocument for most tests,
        // but some build_ functions may dereference it.
        // We'll use nullptr where possible.
        document_ = nullptr;
    }

    void TearDown() override {
    }

    PopplerDocument *document_;
};

// Test: When link is nullptr and title is nullptr, action type should be POPPLER_ACTION_NONE
TEST_F(PopplerActionTest_2303, NullLinkNullTitle_ReturnsActionNone_2303) {
    PopplerAction *action = _poppler_action_new(nullptr, nullptr, nullptr);
    ASSERT_NE(action, nullptr);
    EXPECT_EQ(action->type, POPPLER_ACTION_NONE);
    EXPECT_EQ(action->any.title, nullptr);
    poppler_action_free(action);
}

// Test: When link is nullptr but title is provided, action type should be POPPLER_ACTION_NONE with title set
TEST_F(PopplerActionTest_2303, NullLinkWithTitle_ReturnsActionNoneWithTitle_2303) {
    const gchar *title = "Test Title";
    PopplerAction *action = _poppler_action_new(nullptr, nullptr, title);
    ASSERT_NE(action, nullptr);
    EXPECT_EQ(action->type, POPPLER_ACTION_NONE);
    ASSERT_NE(action->any.title, nullptr);
    EXPECT_STREQ(action->any.title, "Test Title");
    poppler_action_free(action);
}

// Test: When link is nullptr and title is empty string
TEST_F(PopplerActionTest_2303, NullLinkEmptyTitle_ReturnsActionNoneWithEmptyTitle_2303) {
    const gchar *title = "";
    PopplerAction *action = _poppler_action_new(nullptr, nullptr, title);
    ASSERT_NE(action, nullptr);
    EXPECT_EQ(action->type, POPPLER_ACTION_NONE);
    ASSERT_NE(action->any.title, nullptr);
    EXPECT_STREQ(action->any.title, "");
    poppler_action_free(action);
}

// Test: Action with unknown link kind returns POPPLER_ACTION_UNKNOWN
TEST_F(PopplerActionTest_2303, UnknownLinkKind_ReturnsActionUnknown_2303) {
    MockLinkAction unknownLink(actionUnknown);
    PopplerAction *action = _poppler_action_new(nullptr, &unknownLink, "Unknown Action");
    ASSERT_NE(action, nullptr);
    EXPECT_EQ(action->type, POPPLER_ACTION_UNKNOWN);
    ASSERT_NE(action->any.title, nullptr);
    EXPECT_STREQ(action->any.title, "Unknown Action");
    poppler_action_free(action);
}

// Test: Title is properly duplicated (not just pointer copy)
TEST_F(PopplerActionTest_2303, TitleIsDuplicated_2303) {
    gchar *title = g_strdup("Duplicated Title");
    PopplerAction *action = _poppler_action_new(nullptr, nullptr, title);
    ASSERT_NE(action, nullptr);
    ASSERT_NE(action->any.title, nullptr);
    // The title pointer should be different from the original
    EXPECT_NE(action->any.title, title);
    EXPECT_STREQ(action->any.title, "Duplicated Title");
    g_free(title);
    poppler_action_free(action);
}

// Test: poppler_action_copy creates a proper copy
TEST_F(PopplerActionTest_2303, ActionCopy_CopiesCorrectly_2303) {
    PopplerAction *action = _poppler_action_new(nullptr, nullptr, "Copy Test");
    ASSERT_NE(action, nullptr);
    
    PopplerAction *copy = poppler_action_copy(action);
    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->type, action->type);
    ASSERT_NE(copy->any.title, nullptr);
    EXPECT_STREQ(copy->any.title, "Copy Test");
    // Should be different pointers
    EXPECT_NE(copy->any.title, action->any.title);
    
    poppler_action_free(action);
    poppler_action_free(copy);
}

// Test: poppler_action_free handles nullptr gracefully (if applicable)
TEST_F(PopplerActionTest_2303, ActionFree_NullAction_2303) {
    // This should not crash
    poppler_action_free(nullptr);
}

// Test: Action with URI link type
TEST_F(PopplerActionTest_2303, URILinkAction_ReturnsActionURI_2303) {
    MockLinkURI uriLink("https://example.com");
    PopplerAction *action = _poppler_action_new(nullptr, &uriLink, "URI Action");
    ASSERT_NE(action, nullptr);
    EXPECT_EQ(action->type, POPPLER_ACTION_URI);
    ASSERT_NE(action->any.title, nullptr);
    EXPECT_STREQ(action->any.title, "URI Action");
    if (action->uri.uri) {
        EXPECT_STREQ(action->uri.uri, "https://example.com");
    }
    poppler_action_free(action);
}

// Test: Action with Named link type
TEST_F(PopplerActionTest_2303, NamedLinkAction_ReturnsActionNamed_2303) {
    MockLinkNamed namedLink("NextPage");
    PopplerAction *action = _poppler_action_new(nullptr, &namedLink, "Named Action");
    ASSERT_NE(action, nullptr);
    EXPECT_EQ(action->type, POPPLER_ACTION_NAMED);
    ASSERT_NE(action->any.title, nullptr);
    EXPECT_STREQ(action->any.title, "Named Action");
    if (action->named.named_dest) {
        EXPECT_STREQ(action->named.named_dest, "NextPage");
    }
    poppler_action_free(action);
}

// Test: Action with JavaScript link type
TEST_F(PopplerActionTest_2303, JavaScriptLinkAction_ReturnsActionJavaScript_2303) {
    MockLinkJavaScript jsLink("alert('hello');");
    PopplerAction *action = _poppler_action_new(nullptr, &jsLink, "JS Action");
    ASSERT_NE(action, nullptr);
    EXPECT_EQ(action->type, POPPLER_ACTION_JAVASCRIPT);
    ASSERT_NE(action->any.title, nullptr);
    EXPECT_STREQ(action->any.title, "JS Action");
    if (action->javascript.script) {
        EXPECT_STREQ(action->javascript.script, "alert('hello');");
    }
    poppler_action_free(action);
}

// Test: Action with unknown kind and no title
TEST_F(PopplerActionTest_2303, UnknownLinkNoTitle_2303) {
    MockLinkAction unknownLink(actionUnknown);
    PopplerAction *action = _poppler_action_new(nullptr, &unknownLink, nullptr);
    ASSERT_NE(action, nullptr);
    EXPECT_EQ(action->type, POPPLER_ACTION_UNKNOWN);
    EXPECT_EQ(action->any.title, nullptr);
    poppler_action_free(action);
}

// Test: poppler_action_get_type returns a valid GType
TEST_F(PopplerActionTest_2303, GetType_ReturnsValidGType_2303) {
    GType type = poppler_action_get_type();
    EXPECT_NE(type, G_TYPE_INVALID);
}

// Test: poppler_dest_get_type returns a valid GType
TEST_F(PopplerActionTest_2303, DestGetType_ReturnsValidGType_2303) {
    GType type = poppler_dest_get_type();
    EXPECT_NE(type, G_TYPE_INVALID);
}

// Test: Multiple actions can be created and freed independently
TEST_F(PopplerActionTest_2303, MultipleActions_IndependentLifecycles_2303) {
    PopplerAction *action1 = _poppler_action_new(nullptr, nullptr, "Action 1");
    PopplerAction *action2 = _poppler_action_new(nullptr, nullptr, "Action 2");
    PopplerAction *action3 = _poppler_action_new(nullptr, nullptr, "Action 3");

    ASSERT_NE(action1, nullptr);
    ASSERT_NE(action2, nullptr);
    ASSERT_NE(action3, nullptr);

    EXPECT_STREQ(action1->any.title, "Action 1");
    EXPECT_STREQ(action2->any.title, "Action 2");
    EXPECT_STREQ(action3->any.title, "Action 3");

    poppler_action_free(action2);
    // action1 and action3 should still be valid
    EXPECT_STREQ(action1->any.title, "Action 1");
    EXPECT_STREQ(action3->any.title, "Action 3");

    poppler_action_free(action1);
    poppler_action_free(action3);
}

// Test: Title with special characters
TEST_F(PopplerActionTest_2303, TitleWithSpecialChars_2303) {
    const gchar *title = "Título con ñ y ü — «special» chars™";
    PopplerAction *action = _poppler_action_new(nullptr, nullptr, title);
    ASSERT_NE(action, nullptr);
    ASSERT_NE(action->any.title, nullptr);
    EXPECT_STREQ(action->any.title, title);
    poppler_action_free(action);
}

// Test: Very long title
TEST_F(PopplerActionTest_2303, VeryLongTitle_2303) {
    std::string longTitle(10000, 'A');
    PopplerAction *action = _poppler_action_new(nullptr, nullptr, longTitle.c_str());
    ASSERT_NE(action, nullptr);
    ASSERT_NE(action->any.title, nullptr);
    EXPECT_STREQ(action->any.title, longTitle.c_str());
    poppler_action_free(action);
}

// Test: Action with Launch link type
TEST_F(PopplerActionTest_2303, LaunchLinkAction_ReturnsActionLaunch_2303) {
    MockLinkLaunch launchLink;
    PopplerAction *action = _poppler_action_new(nullptr, &launchLink, "Launch Action");
    ASSERT_NE(action, nullptr);
    EXPECT_EQ(action->type, POPPLER_ACTION_LAUNCH);
    poppler_action_free(action);
}

// Test: Copy of NONE action
TEST_F(PopplerActionTest_2303, CopyNoneAction_2303) {
    PopplerAction *action = _poppler_action_new(nullptr, nullptr, "None");
    ASSERT_NE(action, nullptr);
    EXPECT_EQ(action->type, POPPLER_ACTION_NONE);

    PopplerAction *copy = poppler_action_copy(action);
    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->type, POPPLER_ACTION_NONE);
    EXPECT_STREQ(copy->any.title, "None");

    poppler_action_free(action);
    poppler_action_free(copy);
}
