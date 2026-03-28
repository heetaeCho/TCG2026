#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Mocking external dependencies for testing
class MockAnnot : public Annot {
public:
    MOCK_METHOD(double, getOpacity, (), (const));
};

// PopplerAnnotMarkup struct mock
struct _PopplerAnnotMarkup {
    PopplerAnnot parent_instance;
    std::shared_ptr<AnnotMarkup> annot;
};

// Test fixture class for PopplerAnnotMarkup
class PopplerAnnotMarkupTest_2083 : public ::testing::Test {
protected:
    void SetUp() override {
        mockAnnot_ = std::make_shared<MockAnnot>();
        popplerAnnotMarkup_ = std::make_shared<_PopplerAnnotMarkup>();
        popplerAnnotMarkup_->annot = std::make_shared<AnnotMarkup>(nullptr, nullptr);
    }

    std::shared_ptr<MockAnnot> mockAnnot_;
    std::shared_ptr<_PopplerAnnotMarkup> popplerAnnotMarkup_;
};

// TEST_ID 2083
TEST_F(PopplerAnnotMarkupTest_2083, PopplerAnnotMarkup_get_opacity_Normal_2083) {
    // Arrange
    double expectedOpacity = 0.5;
    EXPECT_CALL(*mockAnnot_, getOpacity()).WillOnce(testing::Return(expectedOpacity));

    // Act
    popplerAnnotMarkup_->annot->setOpacity(expectedOpacity);
    double result = poppler_annot_markup_get_opacity(reinterpret_cast<PopplerAnnotMarkup *>(popplerAnnotMarkup_.get()));

    // Assert
    EXPECT_EQ(result, expectedOpacity);
}

// TEST_ID 2083
TEST_F(PopplerAnnotMarkupTest_2083, PopplerAnnotMarkup_get_opacity_InvalidAnnot_2083) {
    // Act
    double result = poppler_annot_markup_get_opacity(nullptr);

    // Assert
    EXPECT_EQ(result, 0);  // The function should return 0 for invalid annot.
}

// TEST_ID 2083
TEST_F(PopplerAnnotMarkupTest_2083, PopplerAnnotMarkup_get_opacity_Exception_2083) {
    // Arrange
    EXPECT_CALL(*mockAnnot_, getOpacity()).WillOnce(testing::Throw(std::runtime_error("Exception")));

    // Act & Assert
    try {
        double result = poppler_annot_markup_get_opacity(reinterpret_cast<PopplerAnnotMarkup *>(popplerAnnotMarkup_.get()));
        FAIL() << "Expected exception not thrown.";
    } catch (const std::exception &e) {
        EXPECT_STREQ(e.what(), "Exception");
    }
}

// TEST_ID 2083
TEST_F(PopplerAnnotMarkupTest_2083, PopplerAnnotMarkup_get_opacity_Boundary_2083) {
    // Arrange
    double expectedOpacity = 1.0;
    EXPECT_CALL(*mockAnnot_, getOpacity()).WillOnce(testing::Return(expectedOpacity));

    // Act
    popplerAnnotMarkup_->annot->setOpacity(expectedOpacity);
    double result = poppler_annot_markup_get_opacity(reinterpret_cast<PopplerAnnotMarkup *>(popplerAnnotMarkup_.get()));

    // Assert
    EXPECT_EQ(result, expectedOpacity);
}