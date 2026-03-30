#include <gtest/gtest.h>

#include <gmock/gmock.h>



extern "C" {

    #include "./TestProjects/poppler/glib/poppler-action.h"

}



#include "./TestProjects/poppler/poppler/Link.h"



using ::testing::_;

using ::testing::Return;



class PopplerActionFixture_2294 : public ::testing::Test {

protected:

    void SetUp() override {

        action = new PopplerAction();

    }



    void TearDown() override {

        g_free(action->uri.uri);

        delete action;

    }



    PopplerAction* action;

};



TEST_F(PopplerActionFixture_2294, BuildUriWithValidUri_2294) {

    LinkURI link(nullptr, std::optional<std::string>("http://example.com"));

    build_uri(action, &link);

    EXPECT_STREQ(action->uri.uri, "http://example.com");

}



TEST_F(PopplerActionFixture_2294, BuildUriWithEmptyUri_2294) {

    LinkURI link(nullptr, std::optional<std::string>(""));

    build_uri(action, &link);

    EXPECT_EQ(action->uri.uri, nullptr);

}



TEST_F(PopplerActionFixture_2294, BuildUriWithNullUri_2294) {

    LinkURI link(nullptr, std::nullopt);

    build_uri(action, &link);

    EXPECT_EQ(action->uri.uri, nullptr);

}
