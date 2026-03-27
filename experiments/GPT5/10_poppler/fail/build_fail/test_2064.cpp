#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "poppler-annot.h"  // Assuming this is the header for poppler_annot_set_contents
#include "poppler-private.h" // Assuming this includes the struct _PopplerAnnot and relevant classes

// Mock class for testing PopplerAnnot's interactions
class MockAnnot {
public:
    MOCK_METHOD(void, setContents, (std::unique_ptr<GooString> contents), ());
};

// Unit tests for the poppler_annot_set_contents function
TEST_F(PopplerAnnotTest_2064, SetContentsWithValidInput_2064) {
    // Arrange
    PopplerAnnot poppler_annot;
    MockAnnot mock_annot;
    poppler_annot.annot = std::make_shared<MockAnnot>();

    const gchar* contents = "Test content";

    // Expect setContents to be called with a GooString created from "Test content"
    EXPECT_CALL(*poppler_annot.annot, setContents(::testing::Pointee(::testing::Eq("Test content"))))
        .Times(1);

    // Act
    poppler_annot_set_contents(&poppler_annot, contents);

    // Assert: The expectation is automatically checked by Google Mock
}

TEST_F(PopplerAnnotTest_2064, SetContentsWithNullInput_2065) {
    // Arrange
    PopplerAnnot poppler_annot;
    MockAnnot mock_annot;
    poppler_annot.annot = std::make_shared<MockAnnot>();

    const gchar* contents = nullptr;

    // Expect setContents to be called with a nullptr
    EXPECT_CALL(*poppler_annot.annot, setContents(::testing::Pointee(::testing::Eq(""))))
        .Times(1);

    // Act
    poppler_annot_set_contents(&poppler_annot, contents);

    // Assert: The expectation is automatically checked by Google Mock
}

TEST_F(PopplerAnnotTest_2064, SetContentsWithEmptyInput_2066) {
    // Arrange
    PopplerAnnot poppler_annot;
    MockAnnot mock_annot;
    poppler_annot.annot = std::make_shared<MockAnnot>();

    const gchar* contents = "";

    // Expect setContents to be called with an empty string
    EXPECT_CALL(*poppler_annot.annot, setContents(::testing::Pointee(::testing::Eq(""))))
        .Times(1);

    // Act
    poppler_annot_set_contents(&poppler_annot, contents);

    // Assert: The expectation is automatically checked by Google Mock
}

TEST_F(PopplerAnnotTest_2064, NullAnnot_2067) {
    // Arrange
    PopplerAnnot poppler_annot;
    const gchar* contents = "Test content";

    // Expect g_return_if_fail to prevent further processing if the annotation is null
    EXPECT_DEATH({
        poppler_annot_set_contents(&poppler_annot, contents);
    }, ".*g_return_if_fail.*");
}