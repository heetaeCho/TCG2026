#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/poppler/Link.h"



using namespace testing;



class LinkMovieTest_306 : public Test {

protected:

    std::unique_ptr<LinkMovie> linkMovie;



    void SetUp() override {

        // Assuming a mock or stub implementation is not needed for Object as it's not part of the interface

        // and we treat the constructor as a black box.

        linkMovie = std::make_unique<LinkMovie>(nullptr);

    }

};



TEST_F(LinkMovieTest_306, IsOk_ReturnsExpectedValue_306) {

    bool isOk = linkMovie->isOk();

    EXPECT_TRUE(isOk); // Assuming isOk() returns true by default based on interface usage.

}



TEST_F(LinkMovieTest_306, GetKind_ReturnsExpectedValue_306) {

    LinkActionKind kind = linkMovie->getKind();

    EXPECT_EQ(kind, LinkActionKind::movie); // Assuming getKind() should return movie for LinkMovie

}



TEST_F(LinkMovieTest_306, HasAnnotRef_ReturnsFalseWhenNoReference_306) {

    bool hasRef = linkMovie->hasAnnotRef();

    EXPECT_FALSE(hasRef);

}



TEST_F(LinkMovieTest_306, GetAnnotRef_ReturnsNullptrWhenNoReference_306) {

    const Ref* ref = linkMovie->getAnnotRef();

    EXPECT_EQ(ref, nullptr);

}



TEST_F(LinkMovieTest_306, HasAnnotTitle_ReturnsFalseWhenNoTitle_306) {

    bool hasTitle = linkMovie->hasAnnotTitle();

    EXPECT_FALSE(hasTitle);

}



TEST_F(LinkMovieTest_306, GetAnnotTitle_ReturnsEmptyStringWhenNoTitle_306) {

    const std::string& title = linkMovie->getAnnotTitle();

    EXPECT_TRUE(title.empty());

}



TEST_F(LinkMovieTest_306, GetOperation_ReturnsExpectedValue_306) {

    OperationType operation = linkMovie->getOperation();

    // Assuming default value for operation if not set

    EXPECT_EQ(operation, OperationType::none); // Placeholder assuming a valid default operation type

}
