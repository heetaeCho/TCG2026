#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "poppler-annotation-private.h"
#include "poppler/Page.h"
#include "poppler/DocumentData.h"
#include "poppler/Annot.h"

namespace Poppler {

class AnnotationPrivateTest_1385 : public ::testing::Test {
protected:
    // Set up necessary mock objects or test resources here
    std::shared_ptr<Annot> mockAnnot;
    ::Page* mockPage;
    DocumentData* mockDoc;

    void SetUp() override {
        // Initialize mock objects here
        mockAnnot = std::make_shared<Annot>();
        mockPage = nullptr; // Set up a valid Page object as needed
        mockDoc = nullptr;  // Set up a valid DocumentData object as needed
    }

    void TearDown() override {
        // Clean up if needed
    }
};

// Test for normal operation: fillTransformationMTX with a regular transformation matrix
TEST_F(AnnotationPrivateTest_1385, FillTransformationMTX_NormalOperation_1385) {
    AnnotationPrivate annotationPrivate;

    // Create a test transformation matrix (6 elements)
    double MTX[6];
    annotationPrivate.fillTransformationMTX(MTX);

    // Check that the MTX array is filled with correct values
    EXPECT_NE(MTX[0], 0);
    EXPECT_NE(MTX[1], 0);
    EXPECT_NE(MTX[2], 0);
    EXPECT_NE(MTX[3], 0);
    EXPECT_NE(MTX[4], 0);
    EXPECT_NE(MTX[5], 0);
}

// Test for boundary conditions: when rotation is 0 or annotation has flagNoRotate
TEST_F(AnnotationPrivateTest_1385, FillTransformationMTX_ZeroRotation_1385) {
    AnnotationPrivate annotationPrivate;

    // Test with a 0 rotation scenario
    // Assuming that the internal state can be simulated for the rotation value
    // Here, we mock the values or set page rotation to 0 directly
    EXPECT_CALL(*mockPage, getRotate())
        .WillOnce(testing::Return(0));

    double MTX[6];
    annotationPrivate.fillTransformationMTX(MTX);

    // Verify that the MTX array is filled with expected values when rotation is 0
    EXPECT_NE(MTX[0], 0);
    EXPECT_NE(MTX[1], 0);
}

// Test for boundary conditions: when annotation has flagNoRotate set
TEST_F(AnnotationPrivateTest_1385, FillTransformationMTX_FlagNoRotate_1385) {
    AnnotationPrivate annotationPrivate;

    // Assuming we can mock flags to include the Annot::flagNoRotate flag
    EXPECT_CALL(*mockAnnot, getFlags())
        .WillOnce(testing::Return(Annot::flagNoRotate));

    double MTX[6];
    annotationPrivate.fillTransformationMTX(MTX);

    // Verify that the MTX array is filled correctly when flagNoRotate is set
    EXPECT_NE(MTX[0], 0);
    EXPECT_NE(MTX[1], 0);
}

// Test for exceptional cases: if pdfPage or pdfAnnot is null
TEST_F(AnnotationPrivateTest_1385, FillTransformationMTX_NullPointer_1385) {
    AnnotationPrivate annotationPrivate;

    // Simulate a scenario where pdfPage or pdfAnnot is null
    EXPECT_EQ(annotationPrivate.fillTransformationMTX(nullptr), void());
    // Assuming a return type of void for error handling in this case
}

// Verify external interaction: mock the interaction of addAnnotationToPage
TEST_F(AnnotationPrivateTest_1385, AddAnnotationToPage_1385) {
    EXPECT_CALL(*mockPage, addAnnot(testing::_))
        .Times(1);  // Expect that the addAnnot function is called once

    AnnotationPrivate::addAnnotationToPage(mockPage, mockDoc, mockAnnot.get());
}

// Verify external interaction: mock the interaction of removeAnnotationFromPage
TEST_F(AnnotationPrivateTest_1385, RemoveAnnotationFromPage_1385) {
    EXPECT_CALL(*mockPage, removeAnnot(testing::_))
        .Times(1);  // Expect that the removeAnnot function is called once

    AnnotationPrivate::removeAnnotationFromPage(mockPage, mockAnnot.get());
}

}  // namespace Poppler