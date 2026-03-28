#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Mocking external dependencies if necessary

class MockAnnotPopup : public AnnotPopup {

public:

    MOCK_METHOD(void, setOpen, (bool openA), (override));

    MOCK_CONST_METHOD0(getOpen, bool());

};



class MockPopplerAnnotMarkup : public PopplerAnnotMarkup {

public:

    std::shared_ptr<MockAnnotPopup> mock_annot_popup;



    MockPopplerAnnotMarkup() {

        mock_annot_popup = std::make_shared<MockAnnotPopup>();

    }



    std::shared_ptr<AnnotPopup> getPopup() const override {

        return mock_annot_popup;

    }

};



class PopplerAnnotMarkupTest : public ::testing::Test {

protected:

    void SetUp() override {

        poppler_annot = new MockPopplerAnnotMarkup();

    }



    void TearDown() override {

        delete poppler_annot;

    }



    MockPopplerAnnotMarkup* poppler_annot;

};



TEST_F(PopplerAnnotMarkupTest, SetPopupIsOpenToTrue_2080) {

    EXPECT_CALL(*poppler_annot->mock_annot_popup, getOpen()).WillOnce(::testing::Return(false));

    EXPECT_CALL(*poppler_annot->mock_annot_popup, setOpen(true));



    poppler_annot_markup_set_popup_is_open(reinterpret_cast<PopplerAnnotMarkup*>(poppler_annot), TRUE);

}



TEST_F(PopplerAnnotMarkupTest, SetPopupIsOpenToFalse_2080) {

    EXPECT_CALL(*poppler_annot->mock_annot_popup, getOpen()).WillOnce(::testing::Return(true));

    EXPECT_CALL(*poppler_annot->mock_annot_popup, setOpen(false));



    poppler_annot_markup_set_popup_is_open(reinterpret_cast<PopplerAnnotMarkup*>(poppler_annot), FALSE);

}



TEST_F(PopplerAnnotMarkupTest, SetPopupIsOpenNoChange_2080) {

    EXPECT_CALL(*poppler_annot->mock_annot_popup, getOpen()).WillOnce(::testing::Return(true));

    EXPECT_CALL(*poppler_annot->mock_annot_popup, setOpen(::testing::_)).Times(0);



    poppler_annot_markup_set_popup_is_open(reinterpret_cast<PopplerAnnotMarkup*>(poppler_annot), TRUE);

}



TEST_F(PopplerAnnotMarkupTest, SetPopupIsOpenNullPopup_2080) {

    poppler_annot->mock_annot_popup.reset();



    EXPECT_CALL(*poppler_annot->mock_annot_popup, getOpen()).Times(0);

    EXPECT_CALL(*poppler_annot->mock_annot_popup, setOpen(::testing::_)).Times(0);



    poppler_annot_markup_set_popup_is_open(reinterpret_cast<PopplerAnnotMarkup*>(poppler_annot), TRUE);

}
