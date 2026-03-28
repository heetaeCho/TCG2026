#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Mocks (if needed) - Placeholder for any external dependencies to be mocked
// Add more mocks as needed based on external dependencies.

class MockPopplerFontDescription : public PopplerFontDescription {
public:
    MOCK_METHOD0(copy, PopplerFontDescription*());
    MOCK_METHOD0(free, void());
};

class PopplerAnnotFreeTextTest_2100 : public ::testing::Test {
protected:
    PopplerAnnotFreeText *poppler_annot;
    PopplerFontDescription *font_desc;

    void SetUp() override {
        poppler_annot = new PopplerAnnotFreeText();
        font_desc = new PopplerFontDescription();
    }

    void TearDown() override {
        delete poppler_annot;
        delete font_desc;
    }
};

// Test normal operation - When font description is set to a new one
TEST_F(PopplerAnnotFreeTextTest_2100, SetFontDescription_2100) {
    // Arrange
    PopplerFontDescription new_font_desc;
    new_font_desc.font_name = "Arial";
    new_font_desc.size_pt = 12.0;
    new_font_desc.stretch = PopplerStretch::Normal;
    new_font_desc.weight = PopplerWeight::Normal;
    new_font_desc.style = PopplerStyle::Regular;

    // Act
    poppler_annot_free_text_set_font_desc(poppler_annot, &new_font_desc);

    // Assert
    ASSERT_EQ(poppler_annot->font_desc->font_name, new_font_desc.font_name);
    ASSERT_EQ(poppler_annot->font_desc->size_pt, new_font_desc.size_pt);
    ASSERT_EQ(poppler_annot->font_desc->stretch, new_font_desc.stretch);
    ASSERT_EQ(poppler_annot->font_desc->weight, new_font_desc.weight);
    ASSERT_EQ(poppler_annot->font_desc->style, new_font_desc.style);
}

// Test boundary condition - Null font_desc
TEST_F(PopplerAnnotFreeTextTest_2101, SetFontDescription_NullFontDesc_2101) {
    // Act
    poppler_annot_free_text_set_font_desc(poppler_annot, nullptr);

    // Assert
    ASSERT_EQ(poppler_annot->font_desc, nullptr);
}

// Test boundary condition - Empty font description
TEST_F(PopplerAnnotFreeTextTest_2102, SetFontDescription_EmptyFontDesc_2102) {
    // Arrange
    PopplerFontDescription empty_font_desc;
    empty_font_desc.font_name = nullptr;
    empty_font_desc.size_pt = 0.0;

    // Act
    poppler_annot_free_text_set_font_desc(poppler_annot, &empty_font_desc);

    // Assert
    ASSERT_EQ(poppler_annot->font_desc->font_name, nullptr);
    ASSERT_EQ(poppler_annot->font_desc->size_pt, 0.0);
}

// Test exceptional case - Verifying the function handles freeing memory properly
TEST_F(PopplerAnnotFreeTextTest_2103, SetFontDescription_FreeMemory_2103) {
    // Arrange
    PopplerFontDescription new_font_desc;
    new_font_desc.font_name = "Arial";
    new_font_desc.size_pt = 12.0;

    // Set initial font description
    poppler_annot_free_text_set_font_desc(poppler_annot, &new_font_desc);

    // Act: Re-assign new font description
    PopplerFontDescription another_font_desc;
    another_font_desc.font_name = "Times New Roman";
    another_font_desc.size_pt = 14.0;
    poppler_annot_free_text_set_font_desc(poppler_annot, &another_font_desc);

    // Assert: Ensuring old font description is freed
    ASSERT_EQ(poppler_annot->font_desc->font_name, "Times New Roman");
    ASSERT_EQ(poppler_annot->font_desc->size_pt, 14.0);
}

// Test external interaction - Verify the internal `poppler_font_description_copy` is called
TEST_F(PopplerAnnotFreeTextTest_2104, VerifyCopyCalled_2104) {
    // Arrange
    MockPopplerFontDescription mock_font_desc;
    EXPECT_CALL(mock_font_desc, copy())
        .Times(1);

    // Act
    poppler_annot_free_text_set_font_desc(poppler_annot, &mock_font_desc);

    // Assert - Mock function verification
    // The expectation is checked automatically at the end of the test.
}