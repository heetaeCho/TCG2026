#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "poppler-annot.h"
#include "Annot.h"

// Mock classes for testing purposes
class MockAnnotPopup : public AnnotPopup {
public:
    MOCK_METHOD(bool, getOpen, (), (const, override));
    MOCK_METHOD(void, setOpen, (bool), (override));
};

class MockPopplerAnnotMarkup : public PopplerAnnotMarkup {
public:
    MockPopplerAnnotMarkup() {
        annot = std::make_shared<MockAnnot>();
        annot_popup = std::make_shared<MockAnnotPopup>();
    }

    std::shared_ptr<MockAnnot> annot;
    std::shared_ptr<MockAnnotPopup> annot_popup;

    void setPopup(MockAnnotPopup* popup) {
        annot_popup = std::shared_ptr<MockAnnotPopup>(popup);
    }
};

// Test Fixture
class PopplerAnnotMarkupTest_2080 : public ::testing::Test {
protected:
    void SetUp() override {
        mock_poppler_annot = std::make_shared<MockPopplerAnnotMarkup>();
    }

    std::shared_ptr<MockPopplerAnnotMarkup> mock_poppler_annot;
};

// Test case for normal operation when popup state changes
TEST_F(PopplerAnnotMarkupTest_2080, PopupStateChangesSuccessfully_2080) {
    EXPECT_CALL(*mock_poppler_annot->annot_popup, getOpen())
        .WillOnce(testing::Return(false))
        .WillOnce(testing::Return(true));

    EXPECT_CALL(*mock_poppler_annot->annot_popup, setOpen(true));

    poppler_annot_markup_set_popup_is_open(reinterpret_cast<PopplerAnnotMarkup*>(mock_poppler_annot.get()), true);
}

// Test case for when the popup is already in the desired state
TEST_F(PopplerAnnotMarkupTest_2081, PopupStateRemainsUnchangedWhenAlreadyOpen_2081) {
    EXPECT_CALL(*mock_poppler_annot->annot_popup, getOpen())
        .WillOnce(testing::Return(true));  // Popup already open

    EXPECT_CALL(*mock_poppler_annot->annot_popup, setOpen(testing::_)).Times(0);  // No change in state

    poppler_annot_markup_set_popup_is_open(reinterpret_cast<PopplerAnnotMarkup*>(mock_poppler_annot.get()), true);
}

TEST_F(PopplerAnnotMarkupTest_2082, PopupStateRemainsUnchangedWhenAlreadyClosed_2082) {
    EXPECT_CALL(*mock_poppler_annot->annot_popup, getOpen())
        .WillOnce(testing::Return(false));  // Popup already closed

    EXPECT_CALL(*mock_poppler_annot->annot_popup, setOpen(testing::_)).Times(0);  // No change in state

    poppler_annot_markup_set_popup_is_open(reinterpret_cast<PopplerAnnotMarkup*>(mock_poppler_annot.get()), false);
}

// Test case for when no popup exists
TEST_F(PopplerAnnotMarkupTest_2083, NoPopupExists_2083) {
    EXPECT_CALL(*mock_poppler_annot->annot_popup, getOpen()).Times(0);  // No call to getOpen

    // Set the popup to null
    mock_poppler_annot->setPopup(nullptr);

    // No setOpen should be called
    EXPECT_CALL(*mock_poppler_annot->annot_popup, setOpen(testing::_)).Times(0);

    poppler_annot_markup_set_popup_is_open(reinterpret_cast<PopplerAnnotMarkup*>(mock_poppler_annot.get()), true);
}

// Test case for invalid PopplerAnnotMarkup instance
TEST_F(PopplerAnnotMarkupTest_2084, InvalidPopplerAnnotMarkupInstance_2084) {
    // Simulate failure of g_return_if_fail
    poppler_annot_markup_set_popup_is_open(nullptr, true);  // Should return immediately without any effect
}