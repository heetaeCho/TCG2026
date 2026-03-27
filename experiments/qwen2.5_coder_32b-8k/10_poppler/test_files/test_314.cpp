#include <gtest/gtest.h>

#include "Link.h"



using namespace poppler;



class LinkRenditionTest_314 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize any necessary objects or mocks here if needed.

        // Since we are treating the class as a black box, no internal setup is required.

    }



    void TearDown() override {

        // Clean up if necessary.

    }

};



TEST_F(LinkRenditionTest_314, GetScript_ReturnsEmptyString_314) {

    // Arrange

    LinkRendition link(nullptr);



    // Act

    const std::string &script = link.getScript();



    // Assert

    EXPECT_EQ(script, "");

}



TEST_F(LinkRenditionTest_314, IsOk_ReturnsFalseForNullptr_314) {

    // Arrange

    LinkRendition link(nullptr);



    // Act

    bool isOk = link.isOk();



    // Assert

    EXPECT_FALSE(isOk);

}



TEST_F(LinkRenditionTest_314, HasScreenAnnot_ReturnsFalseForNullptr_314) {

    // Arrange

    LinkRendition link(nullptr);



    // Act

    bool hasScreenAnnot = link.hasScreenAnnot();



    // Assert

    EXPECT_FALSE(hasScreenAnnot);

}



TEST_F(LinkRenditionTest_314, GetKind_ReturnsExpectedValue_314) {

    // Arrange

    LinkRendition link(nullptr);



    // Act

    LinkActionKind kind = link.getKind();



    // Assert

    EXPECT_EQ(kind, action_rendition);

}



TEST_F(LinkRenditionTest_314, GetScreenAnnot_ReturnsNullRefForNullptr_314) {

    // Arrange

    LinkRendition link(nullptr);



    // Act

    Ref screenAnnot = link.getScreenAnnot();



    // Assert

    EXPECT_TRUE(screenAnnum.is_null());

}



TEST_F(LinkRenditionTest_314, GetOperation_ReturnsExpectedValueForNullptr_314) {

    // Arrange

    LinkRendition link(nullptr);



    // Act

    RenditionOperation operation = link.getOperation();



    // Assert

    EXPECT_EQ(operation, op_play);

}



TEST_F(LinkRenditionTest_314, GetMedia_ReturnsNullptrForNullptr_314) {

    // Arrange

    LinkRendition link(nullptr);



    // Act

    const MediaRendition *media = link.getMedia();



    // Assert

    EXPECT_EQ(media, nullptr);

}
