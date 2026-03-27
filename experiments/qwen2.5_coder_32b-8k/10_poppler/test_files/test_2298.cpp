#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/glib/poppler-action.cc"

#include "TestProjects/poppler/poppler/Link.h"



using namespace testing;



class PopplerActionTest_2298 : public ::testing::Test {

protected:

    PopplerAction action;

    std::unique_ptr<LinkJavaScript> linkJavaScript;



    void SetUp() override {

        action = {};

    }



    LinkJavaScript* createLinkJavaScript(const char* script, bool isValid) {

        auto mockJsObj = std::make_unique<Object>(); // Assuming Object is a placeholder and not used in isOk or getScript

        linkJavaScript = std::make_unique<LinkJavaScript>(mockJsObj.release());

        ON_CALL(*linkJavaScript, isOk()).WillByDefault(Return(isValid));

        ON_CALL(*linkJavaScript, getScript()).WillByDefault(ReturnRef(script ? std::string(script) : std::string()));

        return linkJavaScript.get();

    }

};



TEST_F(PopplerActionTest_2298, BuildJavascript_ValidScript_2298) {

    auto* link = createLinkJavaScript("alert('Hello');", true);

    build_javascript(&action, link);

    EXPECT_STREQ(action.javascript.script, "alert('Hello');");

}



TEST_F(PopplerActionTest_2298, BuildJavascript_EmptyScript_2298) {

    auto* link = createLinkJavaScript("", true);

    build_javascript(&action, link);

    EXPECT_STREQ(action.javascript.script, "");

}



TEST_F(PopplerActionTest_2298, BuildJavascript_NullptrScript_2298) {

    auto* link = createLinkJavaScript(nullptr, true);

    build_javascript(&action, link);

    EXPECT_STREQ(action.javascript.script, "");

}



TEST_F(PopplerActionTest_2298, BuildJavascript_InvalidLink_2298) {

    auto* link = createLinkJavaScript("alert('Hello');", false);

    build_javascript(&action, link);

    EXPECT_STREQ(action.javascript.script, "");

}
