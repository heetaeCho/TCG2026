#include <gtest/gtest.h>

#include "Annot.h"

#include <memory>



class AnnotMarkupTest_803 : public ::testing::Test {

protected:

    std::unique_ptr<AnnotMarkup> annotMarkup;



    void SetUp() override {

        PDFDoc* docA = nullptr;

        PDFRectangle rect(0, 0, 100, 100);

        annotMarkup = std::make_unique<AnnotMarkup>(docA, &rect);

    }

};



TEST_F(AnnotMarkupTest_803, GetSubject_Default_ReturnsNullptr_803) {

    EXPECT_EQ(annotMarkup->getSubject(), nullptr);

}



TEST_F(AnnotMarkupTest_803, SetAndGetString_Subject_ReturnsSetValue_803) {

    auto subject = std::make_unique<GooString>("Test Subject");

    annotMarkup->setSubject(std::move(subject));

    EXPECT_STREQ(annotMarkup->getSubject()->getCString(), "Test Subject");

}



TEST_F(AnnotMarkupTest_803, GetLabel_Default_ReturnsNullptr_803) {

    EXPECT_EQ(annotMarkup->getLabel(), nullptr);

}



TEST_F(AnnotMarkupTest_803, SetAndGetString_Label_ReturnsSetValue_803) {

    auto label = std::make_unique<GooString>("Test Label");

    annotMarkup->setLabel(std::move(label));

    EXPECT_STREQ(annotMarkup->getLabel()->getCString(), "Test Label");

}



TEST_F(AnnotMarkupTest_803, GetOpacity_Default_Returns1_0_803) {

    EXPECT_DOUBLE_EQ(annotMarkup->getOpacity(), 1.0);

}



TEST_F(AnnotMarkupTest_803, SetAndGetDouble_Opacity_ReturnsSetValue_803) {

    annotMarkup->setOpacity(0.5);

    EXPECT_DOUBLE_EQ(annotMarkup->getOpacity(), 0.5);

}



TEST_F(AnnotMarkupTest_803, GetDate_Default_ReturnsNullptr_803) {

    EXPECT_EQ(annotMarkup->getDate(), nullptr);

}



TEST_F(AnnotMarkupTest_803, SetAndGetString_Date_ReturnsSetValue_803) {

    auto date = std::make_unique<GooString>("2023-10-05");

    annotMarkup->setDate(std::move(date));

    EXPECT_STREQ(annotMarkup->getDate()->getCString(), "2023-10-05");

}



TEST_F(AnnotMarkupTest_803, IsInReplyTo_Default_ReturnsFalse_803) {

    EXPECT_FALSE(annotMarkup->isInReplyTo());

}



TEST_F(AnnotMarkupTest_803, SetAndGetRef_InReplyTo_ReturnsSetValue_803) {

    Ref inReplyTo(1, 0);

    annotMarkup->setInReplyTo(inReplyTo);

    EXPECT_TRUE(annotMarkup->isInReplyTo());

    EXPECT_EQ(annotMarkup->getInReplyToID(), 1);

}



TEST_F(AnnotMarkupTest_803, GetPopup_Default_ReturnsNullptr_803) {

    EXPECT_EQ(annotMarkup->getPopup(), nullptr);

}



TEST_F(AnnotMarkupTest_803, SetAndGetPopup_Popup_ReturnsSetValue_803) {

    auto popup = std::make_shared<AnnotPopup>();

    annotMarkup->setPopup(popup);

    EXPECT_EQ(annotMarkup->getPopup(), popup);

}
