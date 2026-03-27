#include <gtest/gtest.h>

#include "poppler-page.cc"

#include "poppler/Link.h"

#include "poppler/DocumentData.h"



using namespace Poppler;



class PageDataTest_1440 : public ::testing::Test {

protected:

    DocumentData* mockDoc;

    QRectF linkArea;



    void SetUp() override {

        mockDoc = new DocumentData("dummy.pdf", std::nullopt, std::nullopt);

        linkArea = QRectF(0, 0, 100, 100);

    }



    void TearDown() override {

        delete mockDoc;

    }

};



TEST_F(PageDataTest_1440, ConvertLinkActionToLink_ReturnsNullptrForNullAction_1440) {

    PageData pageData;

    EXPECT_EQ(pageData.convertLinkActionToLink(nullptr, mockDoc, linkArea), nullptr);

}



TEST_F(PageDataTest_1440, ConvertLinkActionToLink_ReturnsValidLinkGoto_ForGoToAction_1440) {

    auto* action = new LinkGoTo(new Object());

    PageData pageData;

    Link* result = pageData.convertLinkActionToLink(action, mockDoc, linkArea);

    EXPECT_NE(result, nullptr);

    EXPECT_EQ(result->getKind(), actionGoTo);

}



TEST_F(PageDataTest_1440, ConvertLinkActionToLink_ReturnsValidLinkGotoR_ForGoToRAction_1440) {

    auto* action = new LinkGoToR(new Object(), new Object());

    PageData pageData;

    Link* result = pageData.convertLinkActionToLink(action, mockDoc, linkArea);

    EXPECT_NE(result, nullptr);

    EXPECT_EQ(result->getKind(), actionGoToR);

}



TEST_F(PageDataTest_1440, ConvertLinkActionToLink_ReturnsValidLinkLaunch_ForLaunchAction_1440) {

    auto* action = new LinkLaunch(new Object());

    PageData pageData;

    Link* result = pageData.convertLinkActionToLink(action, mockDoc, linkArea);

    EXPECT_NE(result, nullptr);

    EXPECT_EQ(result->getKind(), actionLaunch);

}



TEST_F(PageDataTest_1440, ConvertLinkActionToLink_ReturnsValidLinkNamed_ForNextPageNamedAction_1440) {

    auto* action = new LinkNamed(new Object());

    dynamic_cast<LinkNamed*>(action)->getName() = "NextPage";

    PageData pageData;

    Link* result = pageData.convertLinkActionToLink(action, mockDoc, linkArea);

    EXPECT_NE(result, nullptr);

    EXPECT_EQ(result->getKind(), actionNamed);

}



TEST_F(PageDataTest_1440, ConvertLinkActionToLink_ReturnsValidLinkNamed_ForPrevPageNamedAction_1440) {

    auto* action = new LinkNamed(new Object());

    dynamic_cast<LinkNamed*>(action)->getName() = "PrevPage";

    PageData pageData;

    Link* result = pageData.convertLinkActionToLink(action, mockDoc, linkArea);

    EXPECT_NE(result, nullptr);

    EXPECT_EQ(result->getKind(), actionNamed);

}



TEST_F(PageDataTest_1440, ConvertLinkActionToLink_ReturnsValidLinkMovie_ForPlayMovieOperation_1440) {

    auto* action = new LinkMovie(new Object());

    dynamic_cast<LinkMovie*>(action)->setOperation(LinkMovie::operationTypePlay);

    PageData pageData;

    Link* result = pageData.convertLinkActionToLink(action, mockDoc, linkArea);

    EXPECT_NE(result, nullptr);

    EXPECT_EQ(result->getKind(), actionMovie);

}



TEST_F(PageDataTest_1440, ConvertLinkActionToLink_ReturnsValidLinkJavaScript_ForJavaScriptAction_1440) {

    auto* action = new LinkJavaScript(new Object());

    PageData pageData;

    Link* result = pageData.convertLinkActionToLink(action, mockDoc, linkArea);

    EXPECT_NE(result, nullptr);

    EXPECT_EQ(result->getKind(), actionJavaScript);

}



TEST_F(PageDataTest_1440, ConvertLinkActionToLink_ReturnsValidLinkOCGState_ForOCGStateAction_1440) {

    auto* action = new LinkOCGState(new Object());

    PageData pageData;

    Link* result = pageData.convertLinkActionToLink(action, mockDoc, linkArea);

    EXPECT_NE(result, nullptr);

    EXPECT_EQ(result->getKind(), actionOCGState);

}



TEST_F(PageDataTest_1440, ConvertLinkActionToLink_ReturnsValidLinkResetForm_ForResetFormAction_1440) {

    auto* action = new LinkResetForm(new Object());

    PageData pageData;

    Link* result = pageData.convertLinkActionToLink(action, mockDoc, linkArea);

    EXPECT_NE(result, nullptr);

    EXPECT_EQ(result->getKind(), actionResetForm);

}



TEST_F(PageDataTest_1440, ConvertLinkActionToLink_ReturnsValidLinkSubmitForm_ForSubmitFormAction_1440) {

    auto* action = new LinkSubmitForm(new Object());

    PageData pageData;

    Link* result = pageData.convertLinkActionToLink(action, mockDoc, linkArea);

    EXPECT_NE(result, nullptr);

    EXPECT_EQ(result->getKind(), actionSubmitForm);

}



TEST_F(PageDataTest_1440, ConvertLinkActionToLink_ReturnsNullptr_ForUnknownAction_1440) {

    auto* action = new LinkAction();

    PageData pageData;

    Link* result = pageData.convertLinkActionToLink(action, mockDoc, linkArea);

    EXPECT_EQ(result, nullptr);

}



TEST_F(PageDataTest_1440, ConvertLinkActionToLink_HandlesMultipleNextActions_1440) {

    auto* action = new LinkGoTo(new Object());

    action->nextActions().push_back(std::unique_ptr<LinkAction>(new LinkNamed(new Object())));

    PageData pageData;

    Link* result = pageData.convertLinkActionToLink(action, mockDoc, linkArea);

    EXPECT_NE(result, nullptr);

    EXPECT_EQ(result->getKind(), actionGoTo);

    EXPECT_EQ(LinkPrivate::get(result)->nextLinks.size(), 1);

}



TEST_F(PageDataTest_1440, ConvertLinkActionToLink_WarningLoggedForUnhandledNamedActions_1440) {

    testing::internal::CaptureStderr();

    auto* action = new LinkNamed(new Object());

    dynamic_cast<LinkNamed*>(action)->getName() = "UnhandledAction";

    PageData pageData;

    Link* result = pageData.convertLinkActionToLink(action, mockDoc, linkArea);

    std::string output = testing::internal::GetCapturedStderr();

    EXPECT_TRUE(output.find("Unhandled action name") != std::string::npos);

}
