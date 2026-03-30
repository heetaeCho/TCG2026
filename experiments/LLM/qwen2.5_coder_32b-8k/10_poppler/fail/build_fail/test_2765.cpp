#include <gtest/gtest.h>

#include "poppler-link-private.h"

#include "Link.h"

#include <QRectF>

#include <QString>

#include <memory>



using namespace Poppler;



class LinkRenditionPrivateTest : public ::testing::Test {

protected:

    QRectF area;

    std::unique_ptr<MediaRendition> mediaRendition;

    QString javaScript;

    Ref ref;



    void SetUp() override {

        area = QRectF(10, 20, 30, 40);

        mediaRendition = std::make_unique<MediaRendition>();

        javaScript = "exampleScript";

        ref = {1, 0};

    }

};



TEST_F(LinkRenditionPrivateTest_2765, ConstructorValidRendition_2765) {

    LinkRendition::RenditionOperation operation = LinkRendition::PlayRendition;

    LinkRenditionPrivate linkRendition(area, std::move(mediaRendition), operation, javaScript, ref);

    EXPECT_EQ(linkRendition.action, LinkRendition::PlayRendition);

}



TEST_F(LinkRenditionPrivateTest_2765, ConstructorNoRendition_2765) {

    LinkRendition::RenditionOperation operation = LinkRendition::NoRendition;

    std::unique_ptr<MediaRendition> nullMediaRendition = nullptr;

    LinkRenditionPrivate linkRendition(area, std::move(nullMediaRendition), operation, javaScript, ref);

    EXPECT_EQ(linkRendition.action, LinkRendition::NoRendition);

}



TEST_F(LinkRenditionPrivateTest_2765, ConstructorStopRendition_2765) {

    LinkRendition::RenditionOperation operation = LinkRendition::StopRendition;

    LinkRenditionPrivate linkRendition(area, std::move(mediaRendition), operation, javaScript, ref);

    EXPECT_EQ(linkRendition.action, LinkRendition::StopRendition);

}



TEST_F(LinkRenditionPrivateTest_2765, ConstructorPauseRendition_2765) {

    LinkRendition::RenditionOperation operation = LinkRendition::PauseRendition;

    LinkRenditionPrivate linkRendition(area, std::move(mediaRendition), operation, javaScript, ref);

    EXPECT_EQ(linkRendition.action, LinkRendition::PauseRendition);

}



TEST_F(LinkRenditionPrivateTest_2765, ConstructorResumeRendition_2765) {

    LinkRendition::RenditionOperation operation = LinkRendition::ResumeRendition;

    LinkRenditionPrivate linkRendition(area, std::move(mediaRendition), operation, javaScript, ref);

    EXPECT_EQ(linkRendition.action, LinkRendition::ResumeRendition);

}



TEST_F(LinkRenditionPrivateTest_2765, ConstructorInvalidRef_2765) {

    Ref invalidRef = Ref::INVALID();

    LinkRendition::RenditionOperation operation = LinkRendition::NoRendition;

    std::unique_ptr<MediaRendition> nullMediaRendition = nullptr;

    LinkRenditionPrivate linkRendition(area, std::move(nullMediaRendition), operation, javaScript, invalidRef);

    EXPECT_EQ(linkRendition.annotationReference.num, -1);

    EXPECT_EQ(linkRendition.annotationReference.gen, -1);

}
