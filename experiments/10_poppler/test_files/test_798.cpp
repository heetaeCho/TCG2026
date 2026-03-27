#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/poppler/Annot.h"



using namespace testing;



class AnnotMarkupTest_798 : public ::testing::Test {

protected:

    std::shared_ptr<AnnotPopup> mock_popup;

    AnnotMarkup* annot_markup;



    void SetUp() override {

        mock_popup = std::make_shared<NiceMock<AnnotPopup>>();

        PDFDoc doc(nullptr);

        PDFRectangle rect(0, 0, 10, 10);

        annot_markup = new AnnotMarkup(&doc, &rect);

        annot_markup->setPopup(mock_popup);

    }



    void TearDown() override {

        delete annot_markup;

    }

};



TEST_F(AnnotMarkupTest_798, GetPopup_ReturnsSetPopup_798) {

    EXPECT_EQ(annot_markup->getPopup(), mock_popup);

}



TEST_F(AnnotMarkupTest_798, GetPopup_ReturnsNullptrIfNotSet_798) {

    AnnotMarkup no_popup_markup(nullptr, nullptr);

    EXPECT_EQ(no_popup_markup.getPopup(), nullptr);

}
