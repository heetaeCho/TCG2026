#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/qt5/src/poppler-annotation.cc"  // Include the necessary header file for the function

namespace {

    // Test normal operation of the fromPdfFlags function
    TEST_F(PopplerAnnotationTest_1394, FromPdfFlags_NormalOperation_1394) {
        int inputFlags = Annot::flagHidden | Annot::flagNoZoom;
        int expectedQtFlags = Annotation::Hidden | Annotation::FixedSize;

        int result = Poppler::fromPdfFlags(inputFlags);

        EXPECT_EQ(result, expectedQtFlags);
    }

    // Test when the input flags are 0 (boundary condition)
    TEST_F(PopplerAnnotationTest_1394, FromPdfFlags_NoFlags_1394) {
        int inputFlags = 0;
        int expectedQtFlags = 0;  // No flags set should result in 0

        int result = Poppler::fromPdfFlags(inputFlags);

        EXPECT_EQ(result, expectedQtFlags);
    }

    // Test when only the flagReadOnly flag is set (boundary condition)
    TEST_F(PopplerAnnotationTest_1394, FromPdfFlags_ReadOnly_1394) {
        int inputFlags = Annot::flagReadOnly;
        int expectedQtFlags = Annotation::DenyWrite | Annotation::DenyDelete;

        int result = Poppler::fromPdfFlags(inputFlags);

        EXPECT_EQ(result, expectedQtFlags);
    }

    // Test when flags contain multiple values (complex boundary)
    TEST_F(PopplerAnnotationTest_1394, FromPdfFlags_MultipleFlags_1394) {
        int inputFlags = Annot::flagHidden | Annot::flagNoZoom | Annot::flagNoRotate | Annot::flagReadOnly;
        int expectedQtFlags = Annotation::Hidden | Annotation::FixedSize | Annotation::FixedRotation | Annotation::DenyWrite | Annotation::DenyDelete;

        int result = Poppler::fromPdfFlags(inputFlags);

        EXPECT_EQ(result, expectedQtFlags);
    }

    // Test when an invalid flag is passed (boundary condition)
    TEST_F(PopplerAnnotationTest_1394, FromPdfFlags_InvalidFlag_1394) {
        // Here, we will pass a flag not defined in AnnotFlag (e.g., flagUnknown)
        int inputFlags = Annot::flagUnknown;
        int expectedQtFlags = 0;  // Since it's an unknown flag, it should result in 0.

        int result = Poppler::fromPdfFlags(inputFlags);

        EXPECT_EQ(result, expectedQtFlags);
    }

    // Test when flagLockedContents is set (boundary condition)
    TEST_F(PopplerAnnotationTest_1394, FromPdfFlags_LockedContents_1394) {
        int inputFlags = Annot::flagLockedContents;
        int expectedQtFlags = 0;  // Since flagLockedContents does not correspond to any Poppler flag, it should result in 0.

        int result = Poppler::fromPdfFlags(inputFlags);

        EXPECT_EQ(result, expectedQtFlags);
    }

    // Test the behavior when flagPrint is not set (boundary condition)
    TEST_F(PopplerAnnotationTest_1394, FromPdfFlags_NoPrint_1394) {
        int inputFlags = Annot::flagHidden | Annot::flagNoZoom | Annot::flagReadOnly;
        int expectedQtFlags = Annotation::Hidden | Annotation::FixedSize | Annotation::DenyWrite | Annotation::DenyDelete;

        // flagPrint is missing in inputFlags, so DenyPrint should be added to result
        int result = Poppler::fromPdfFlags(inputFlags);

        EXPECT_EQ(result, expectedQtFlags);
    }
}