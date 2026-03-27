#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Link.h"

#include <string>



using namespace std;



class LinkJavaScriptTest_323 : public ::testing::Test {

protected:

    Object jsObj;

    XRef xref;

    string script = "app.alert('Hello, World!');";

    unique_ptr<LinkJavaScript> linkJs;



    void SetUp() override {

        linkJs = make_unique<LinkJavaScript>(LinkJavaScript::createObject(&xref, script));

    }

};



TEST_F(LinkJavaScriptTest_323, IsOkReturnsTrueForValidScript_323) {

    EXPECT_TRUE(linkJs->isOk());

}



TEST_F(LinkJavaScriptTest_323, GetKindReturnsActionJavaScript_323) {

    EXPECT_EQ(linkJs->getKind(), actionJavaScript);

}



TEST_F(LinkJavaScriptTest_323, GetScriptReturnsCorrectScript_323) {

    EXPECT_EQ(linkJs->getScript(), script);

}
