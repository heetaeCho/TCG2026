#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Mocks for dependencies
class MockPopplerDocument {
 public:
  MOCK_METHOD(void, doSomething, (), ());
};

class MockPopplerRectangle {
 public:
  MOCK_METHOD(double, getX1, (), ());
  MOCK_METHOD(double, getY1, (), ());
  MOCK_METHOD(double, getX2, (), ());
  MOCK_METHOD(double, getY2, (), ());
};

class MockAnnotGeometry {
 public:
  MOCK_METHOD(void, initialize, (), ());
};

class PopplerAnnotTest_2058 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Create mock objects
    mock_doc = std::make_unique<MockPopplerDocument>();
    mock_rect = std::make_unique<MockPopplerRectangle>();
  }

  std::unique_ptr<MockPopplerDocument> mock_doc;
  std::unique_ptr<MockPopplerRectangle> mock_rect;
};

TEST_F(PopplerAnnotTest_2058, poppler_annot_square_new_creates_annot_geometry_2058) {
  // Arrange
  EXPECT_CALL(*mock_rect, getX1()).WillOnce(testing::Return(1.0));
  EXPECT_CALL(*mock_rect, getY1()).WillOnce(testing::Return(1.0));
  EXPECT_CALL(*mock_rect, getX2()).WillOnce(testing::Return(5.0));
  EXPECT_CALL(*mock_rect, getY2()).WillOnce(testing::Return(5.0));

  // Act
  PopplerAnnot* annot = poppler_annot_square_new(mock_doc.get(), mock_rect.get());

  // Assert
  ASSERT_NE(annot, nullptr);
}

TEST_F(PopplerAnnotTest_2058, poppler_annot_square_new_with_invalid_rect_returns_null_2058) {
  // Arrange
  EXPECT_CALL(*mock_rect, getX1()).WillOnce(testing::Return(5.0));
  EXPECT_CALL(*mock_rect, getY1()).WillOnce(testing::Return(5.0));
  EXPECT_CALL(*mock_rect, getX2()).WillOnce(testing::Return(1.0)); // Invalid rectangle
  EXPECT_CALL(*mock_rect, getY2()).WillOnce(testing::Return(1.0));

  // Act
  PopplerAnnot* annot = poppler_annot_square_new(mock_doc.get(), mock_rect.get());

  // Assert
  ASSERT_EQ(annot, nullptr);
}

TEST_F(PopplerAnnotTest_2058, poppler_annot_square_new_with_valid_rect_creates_annot_geometry_2058) {
  // Arrange
  EXPECT_CALL(*mock_rect, getX1()).WillOnce(testing::Return(0.0));
  EXPECT_CALL(*mock_rect, getY1()).WillOnce(testing::Return(0.0));
  EXPECT_CALL(*mock_rect, getX2()).WillOnce(testing::Return(3.0));
  EXPECT_CALL(*mock_rect, getY2()).WillOnce(testing::Return(3.0));

  // Act
  PopplerAnnot* annot = poppler_annot_square_new(mock_doc.get(), mock_rect.get());

  // Assert
  ASSERT_NE(annot, nullptr);
}

TEST_F(PopplerAnnotTest_2058, poppler_annot_square_new_handles_null_doc_2058) {
  // Arrange
  EXPECT_CALL(*mock_rect, getX1()).WillOnce(testing::Return(0.0));
  EXPECT_CALL(*mock_rect, getY1()).WillOnce(testing::Return(0.0));
  EXPECT_CALL(*mock_rect, getX2()).WillOnce(testing::Return(3.0));
  EXPECT_CALL(*mock_rect, getY2()).WillOnce(testing::Return(3.0));

  // Act
  PopplerAnnot* annot = poppler_annot_square_new(nullptr, mock_rect.get());

  // Assert
  ASSERT_EQ(annot, nullptr);
}