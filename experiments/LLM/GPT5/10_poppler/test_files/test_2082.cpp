#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Mock classes for dependencies
class MockPopup {
public:
    MOCK_METHOD(void, setRect, (int x1, int y1, int x2, int y2), ());
};

class MockAnnot {
public:
    MOCK_METHOD(std::shared_ptr<MockPopup>, getPopup, (), ());
};

class MockPopplerAnnot {
public:
    MOCK_METHOD(MockAnnot*, annot, (), ());
};

class MockPopplerRectangle {
public:
    int x1, y1, x2, y2;
};

// Function being tested
void poppler_annot_markup_set_popup_rectangle(PopplerAnnotMarkup *poppler_annot, PopplerRectangle *poppler_rect) {
    AnnotMarkup *annot;
    Annot *annot_popup;
    g_return_if_fail(POPPLER_IS_ANNOT_MARKUP(poppler_annot));
    g_return_if_fail(poppler_rect != nullptr);
    annot = static_cast<AnnotMarkup *>(POPPLER_ANNOT(poppler_annot)->annot.get());
    annot_popup = annot->getPopup().get();
    if (!annot_popup) {
        return;
    }
    annot_popup->setRect(poppler_rect->x1, poppler_rect->y1, poppler_rect->x2, poppler_rect->y2);
}

// Test fixture
class PopplerAnnotMarkupTest_2082 : public ::testing::Test {
protected:
    MockPopplerAnnotMarkup poppler_annot;
    MockPopplerRectangle poppler_rect;
    MockAnnot mock_annot;
    MockPopup mock_popup;

    void SetUp() override {
        // Mock setup if needed
    }

    void TearDown() override {
        // Clean up if needed
    }
};

// Test for normal operation
TEST_F(PopplerAnnotMarkupTest_2082, SetPopupRectangle_NormalOperation_2082) {
    // Arrange
    poppler_annot.annot = &mock_annot;
    poppler_rect.x1 = 10;
    poppler_rect.y1 = 20;
    poppler_rect.x2 = 30;
    poppler_rect.y2 = 40;

    // Set expectations
    EXPECT_CALL(mock_annot, getPopup())
        .WillOnce(testing::Return(std::make_shared<MockPopup>()));

    EXPECT_CALL(mock_popup, setRect(10, 20, 30, 40));

    // Act
    poppler_annot_markup_set_popup_rectangle(&poppler_annot, &poppler_rect);

    // Assert (handled by mock assertions)
}

// Test for null rectangle (boundary condition)
TEST_F(PopplerAnnotMarkupTest_2082, SetPopupRectangle_NullRectangle_2082) {
    // Arrange
    poppler_annot.annot = &mock_annot;

    // Set expectations
    EXPECT_CALL(mock_annot, getPopup())
        .WillOnce(testing::Return(std::make_shared<MockPopup>()));

    // Act
    poppler_annot_markup_set_popup_rectangle(&poppler_annot, nullptr);

    // Assert (no setRect should be called)
    // No additional assertions needed; mocked functions should not be called
}

// Test for annot without popup (boundary condition)
TEST_F(PopplerAnnotMarkupTest_2082, SetPopupRectangle_NoPopup_2082) {
    // Arrange
    poppler_annot.annot = &mock_annot;
    poppler_rect.x1 = 10;
    poppler_rect.y1 = 20;
    poppler_rect.x2 = 30;
    poppler_rect.y2 = 40;

    // Set expectations
    EXPECT_CALL(mock_annot, getPopup())
        .WillOnce(testing::Return(nullptr));

    // Act
    poppler_annot_markup_set_popup_rectangle(&poppler_annot, &poppler_rect);

    // Assert (setRect should not be called since popup is nullptr)
    // No assertions needed as no interaction will happen with popup
}