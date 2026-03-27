#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/poppler/glib/poppler-action.h"

#include "./TestProjects/poppler/poppler/Link.h"



using namespace testing;



class PopplerActionTest_2303 : public ::testing::Test {

protected:

    PopplerDocument* document;

    const gchar* title = "Sample Title";



    void SetUp() override {

        document = g_slice_new0(PopplerDocument);

    }



    void TearDown() override {

        g_slice_free(PopplerDocument, document);

    }

};



TEST_F(PopplerActionTest_2303, CreateWithNullLink_2303) {

    PopplerAction* action = _poppler_action_new(document, nullptr, title);

    ASSERT_NE(action, nullptr);

    EXPECT_EQ(action->type, POPPLER_ACTION_NONE);

    EXPECT_STREQ(action->any.title, title);

    g_slice_free(PopplerAction, action);

}



TEST_F(PopplerActionTest_2303, CreateWithGoToLink_2303) {

    Mock<LinkAction> mock_link;

    ON_CALL(mock_link, getKind()).WillByDefault(Return(actionGoTo));



    PopplerAction* action = _poppler_action_new(document, &mock_link, title);

    ASSERT_NE(action, nullptr);

    EXPECT_EQ(action->type, POPPLER_ACTION_GOTO_DEST);

    g_slice_free(PopplerAction, action);

}



TEST_F(PopplerActionTest_2303, CreateWithGoToRLink_2303) {

    Mock<LinkAction> mock_link;

    ON_CALL(mock_link, getKind()).WillByDefault(Return(actionGoToR));



    PopplerAction* action = _poppler_action_new(document, &mock_link, title);

    ASSERT_NE(action, nullptr);

    EXPECT_EQ(action->type, POPPLER_ACTION_GOTO_REMOTE);

    g_slice_free(PopplerAction, action);

}



TEST_F(PopplerActionTest_2303, CreateWithLaunchLink_2303) {

    Mock<LinkAction> mock_link;

    ON_CALL(mock_link, getKind()).WillByDefault(Return(actionLaunch));



    PopplerAction* action = _poppler_action_new(document, &mock_link, title);

    ASSERT_NE(action, nullptr);

    EXPECT_EQ(action->type, POPPLER_ACTION_LAUNCH);

    g_slice_free(PopplerAction, action);

}



TEST_F(PopplerActionTest_2303, CreateWithURILink_2303) {

    Mock<LinkAction> mock_link;

    ON_CALL(mock_link, getKind()).WillByDefault(Return(actionURI));



    PopplerAction* action = _poppler_action_new(document, &mock_link, title);

    ASSERT_NE(action, nullptr);

    EXPECT_EQ(action->type, POPPLER_ACTION_URI);

    g_slice_free(PopplerAction, action);

}



TEST_F(PopplerActionTest_2303, CreateWithNamedLink_2303) {

    Mock<LinkAction> mock_link;

    ON_CALL(mock_link, getKind()).WillByDefault(Return(actionNamed));



    PopplerAction* action = _poppler_action_new(document, &mock_link, title);

    ASSERT_NE(action, nullptr);

    EXPECT_EQ(action->type, POPPLER_ACTION_NAMED);

    g_slice_free(PopplerAction, action);

}



TEST_F(PopplerActionTest_2303, CreateWithMovieLink_2303) {

    Mock<LinkAction> mock_link;

    ON_CALL(mock_link, getKind()).WillByDefault(Return(actionMovie));



    PopplerAction* action = _poppler_action_new(document, &mock_link, title);

    ASSERT_NE(action, nullptr);

    EXPECT_EQ(action->type, POPPLER_ACTION_MOVIE);

    g_slice_free(PopplerAction, action);

}



TEST_F(PopplerActionTest_2303, CreateWithRenditionLink_2303) {

    Mock<LinkAction> mock_link;

    ON_CALL(mock_link, getKind()).WillByDefault(Return(actionRendition));



    PopplerAction* action = _poppler_action_new(document, &mock_link, title);

    ASSERT_NE(action, nullptr);

    EXPECT_EQ(action->type, POPPLER_ACTION_RENDITION);

    g_slice_free(PopplerAction, action);

}



TEST_F(PopplerActionTest_2303, CreateWithOCGStateLink_2303) {

    Mock<LinkAction> mock_link;

    ON_CALL(mock_link, getKind()).WillByDefault(Return(actionOCGState));



    PopplerAction* action = _poppler_action_new(document, &mock_link, title);

    ASSERT_NE(action, nullptr);

    EXPECT_EQ(action->type, POPPLER_ACTION_OCG_STATE);

    g_slice_free(PopplerAction, action);

}



TEST_F(PopplerActionTest_2303, CreateWithJavaScriptLink_2303) {

    Mock<LinkAction> mock_link;

    ON_CALL(mock_link, getKind()).WillByDefault(Return(actionJavaScript));



    PopplerAction* action = _poppler_action_new(document, &mock_link, title);

    ASSERT_NE(action, nullptr);

    EXPECT_EQ(action->type, POPPLER_ACTION_JAVASCRIPT);

    g_slice_free(PopplerAction, action);

}



TEST_F(PopplerActionTest_2303, CreateWithResetFormLink_2303) {

    Mock<LinkAction> mock_link;

    ON_CALL(mock_link, getKind()).WillByDefault(Return(actionResetForm));



    PopplerAction* action = _poppler_action_new(document, &mock_link, title);

    ASSERT_NE(action, nullptr);

    EXPECT_EQ(action->type, POPPLER_ACTION_RESET_FORM);

    g_slice_free(PopplerAction, action);

}



TEST_F(PopplerActionTest_2303, CreateWithUnknownLink_2303) {

    Mock<LinkAction> mock_link;

    ON_CALL(mock_link, getKind()).WillByDefault(Return(actionUnknown));



    PopplerAction* action = _poppler_action_new(document, &mock_link, title);

    ASSERT_NE(action, nullptr);

    EXPECT_EQ(action->type, POPPLER_ACTION_UNKNOWN);

    g_slice_free(PopplerAction, action);

}



TEST_F(PopplerActionTest_2303, CreateWithEmptyTitle_2303) {

    PopplerAction* action = _poppler_action_new(document, nullptr, nullptr);

    ASSERT_NE(action, nullptr);

    EXPECT_EQ(action->type, POPPLER_ACTION_NONE);

    EXPECT_EQ(action->any.title, nullptr);

    g_slice_free(PopplerAction, action);

}
