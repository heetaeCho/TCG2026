#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/qt5/src/poppler-annotation.cc"  // Include the header file for the function to be tested
#include "./TestProjects/poppler/poppler/Annot.h"  // Include the dependencies for Annot flags

namespace Poppler {
    // Mocking external dependencies if necessary
    // Since `toPdfFlags` is a standalone function, there's no need to mock anything here
}

class ToPdfFlagsTest_1395 : public ::testing::Test {
protected:
    // You can use this setup for any common initialization you need.
    // This function runs before each test case.
    void SetUp() override {}

    // This function runs after each test case.
    void TearDown() override {}
};

// Test normal operation: Check conversion of various Annotation flags to expected PdfFlags
TEST_F(ToPdfFlagsTest_1395, ConvertHiddenFlag_1395) {
    int qtflags = Annotation::Hidden;
    int expected_flags = Annot::flagHidden;

    int result = Poppler::toPdfFlags(qtflags);

    ASSERT_EQ(result, expected_flags);
}

TEST_F(ToPdfFlagsTest_1395, ConvertFixedSizeFlag_1395) {
    int qtflags = Annotation::FixedSize;
    int expected_flags = Annot::flagNoZoom;

    int result = Poppler::toPdfFlags(qtflags);

    ASSERT_EQ(result, expected_flags);
}

TEST_F(ToPdfFlagsTest_1395, ConvertFixedRotationFlag_1395) {
    int qtflags = Annotation::FixedRotation;
    int expected_flags = Annot::flagNoRotate;

    int result = Poppler::toPdfFlags(qtflags);

    ASSERT_EQ(result, expected_flags);
}

TEST_F(ToPdfFlagsTest_1395, ConvertDenyPrintFlag_1395) {
    int qtflags = Annotation::DenyPrint;
    int expected_flags = Annot::flagPrint;

    int result = Poppler::toPdfFlags(qtflags);

    ASSERT_EQ(result, expected_flags);
}

TEST_F(ToPdfFlagsTest_1395, ConvertDenyWriteFlag_1395) {
    int qtflags = Annotation::DenyWrite;
    int expected_flags = Annot::flagReadOnly;

    int result = Poppler::toPdfFlags(qtflags);

    ASSERT_EQ(result, expected_flags);
}

TEST_F(ToPdfFlagsTest_1395, ConvertDenyDeleteFlag_1395) {
    int qtflags = Annotation::DenyDelete;
    int expected_flags = Annot::flagLocked;

    int result = Poppler::toPdfFlags(qtflags);

    ASSERT_EQ(result, expected_flags);
}

TEST_F(ToPdfFlagsTest_1395, ConvertToggleHidingOnMouseFlag_1395) {
    int qtflags = Annotation::ToggleHidingOnMouse;
    int expected_flags = Annot::flagToggleNoView;

    int result = Poppler::toPdfFlags(qtflags);

    ASSERT_EQ(result, expected_flags);
}

// Test boundary condition: when no flags are set (i.e., 0)
TEST_F(ToPdfFlagsTest_1395, ConvertNoFlagsSet_1395) {
    int qtflags = 0;
    int expected_flags = 0;

    int result = Poppler::toPdfFlags(qtflags);

    ASSERT_EQ(result, expected_flags);
}

// Test exceptional case: Check behavior when an invalid flag is set
TEST_F(ToPdfFlagsTest_1395, ConvertInvalidFlag_1395) {
    int qtflags = 9999;  // Invalid flag that doesn't match any defined constants
    int expected_flags = 0;  // Since it's an invalid flag, the result should be 0

    int result = Poppler::toPdfFlags(qtflags);

    ASSERT_EQ(result, expected_flags);
}