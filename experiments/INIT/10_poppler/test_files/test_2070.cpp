#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Mocks and test dependencies
#include "poppler-private.h"

class AnnotMock {
public:
    MOCK_METHOD(int, getPageNum, (), ());
};

class PopplerAnnotTest_2070 : public ::testing::Test {
protected:
    std::shared_ptr<AnnotMock> annotMock;
    _PopplerAnnot popplerAnnot;

    void SetUp() override {
        annotMock = std::make_shared<AnnotMock>();
        popplerAnnot.annot = annotMock;
    }
};

// Normal operation test case
TEST_F(PopplerAnnotTest_2070, GetPageIndex_ValidPageNum) {
    EXPECT_CALL(*annotMock, getPageNum())
        .WillOnce(::testing::Return(2));  // Mocking the getPageNum method to return 2
    
    gint result = poppler_annot_get_page_index(&popplerAnnot);

    EXPECT_EQ(result, 1);  // The page number returned should be 1 (2 - 1)
}

// Boundary condition test case (page number is 1)
TEST_F(PopplerAnnotTest_2070, GetPageIndex_PageNumOne) {
    EXPECT_CALL(*annotMock, getPageNum())
        .WillOnce(::testing::Return(1));  // Mocking the getPageNum method to return 1
    
    gint result = poppler_annot_get_page_index(&popplerAnnot);

    EXPECT_EQ(result, 0);  // The page number returned should be 0 (1 - 1)
}

// Boundary condition test case (page number is 0)
TEST_F(PopplerAnnotTest_2070, GetPageIndex_PageNumZero) {
    EXPECT_CALL(*annotMock, getPageNum())
        .WillOnce(::testing::Return(0));  // Mocking the getPageNum method to return 0
    
    gint result = poppler_annot_get_page_index(&popplerAnnot);

    EXPECT_EQ(result, -1);  // Since page number is 0, the result should be -1
}

// Error case: Invalid PopplerAnnot (nullptr or invalid pointer)
TEST_F(PopplerAnnotTest_2070, GetPageIndex_InvalidAnnot) {
    EXPECT_CALL(*annotMock, getPageNum())
        .Times(0);  // The method should not be called when the annotation is invalid

    _PopplerAnnot invalidAnnot;
    gint result = poppler_annot_get_page_index(&invalidAnnot);

    EXPECT_EQ(result, -1);  // Invalid annotation should return -1 without calling getPageNum
}