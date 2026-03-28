#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <optional>

#include "./poppler/Annot.h"
#include "./poppler/Annot.cc"
#include "./poppler/Form.h"
#include "./poppler/GfxFont.h"
#include "./poppler/GooString.h"

// Mocking dependencies (Form, GfxFont, etc.)
class MockForm : public Form {
public:
    MockForm(PDFDoc* doc) : Form(doc) {}
    MOCK_METHOD(const std::string&, findFontInDefaultResources, (const std::string&, const std::string&), (const, override));
};

class MockGfxFont : public GfxFont {
public:
    MockGfxFont(const char* tagA, Ref idA, std::optional<std::string> &&nameA, GfxFontType typeA, Ref embFontIDA)
        : GfxFont(tagA, idA, std::move(nameA), typeA, embFontIDA) {}
    MOCK_METHOD(bool, isOk, (), (const, override));
};

// Helper function to create common objects
std::unique_ptr<GfxFont> createMockGfxFont() {
    return std::make_unique<MockGfxFont>("TestTag", Ref(), std::optional<std::string>("TestFont"), GfxFontType::type1, Ref());
}

// Test the normal operation of drawMultiLineText
TEST_F(AnnotTest, drawMultiLineText_NormalOperation_2025) {
    const std::string text = "This is a test";
    const double availableWidth = 500.0;
    const Form* form = nullptr;
    const GfxFont& font = *createMockGfxFont();
    const std::string fontName = "Arial";
    const double fontSize = 12.0;
    const VariableTextQuadding quadding = VariableTextQuadding::leftJustified;
    const double borderWidth = 5.0;

    // Call the function under test
    DrawMultiLineTextResult result = drawMultiLineText(text, availableWidth, form, font, fontName, fontSize, quadding, borderWidth);

    // Verify the results
    EXPECT_EQ(result.nLines, 1); // Expecting 1 line of text
}

// Test boundary condition with empty text
TEST_F(AnnotTest, drawMultiLineText_EmptyText_2025) {
    const std::string text = "";
    const double availableWidth = 500.0;
    const Form* form = nullptr;
    const GfxFont& font = *createMockGfxFont();
    const std::string fontName = "Arial";
    const double fontSize = 12.0;
    const VariableTextQuadding quadding = VariableTextQuadding::leftJustified;
    const double borderWidth = 5.0;

    // Call the function under test
    DrawMultiLineTextResult result = drawMultiLineText(text, availableWidth, form, font, fontName, fontSize, quadding, borderWidth);

    // Verify the results
    EXPECT_EQ(result.nLines, 0); // No lines of text
}

// Test boundary condition with very long text
TEST_F(AnnotTest, drawMultiLineText_LongText_2025) {
    const std::string text(1000, 'A');  // Text of length 1000
    const double availableWidth = 500.0;
    const Form* form = nullptr;
    const GfxFont& font = *createMockGfxFont();
    const std::string fontName = "Arial";
    const double fontSize = 12.0;
    const VariableTextQuadding quadding = VariableTextQuadding::leftJustified;
    const double borderWidth = 5.0;

    // Call the function under test
    DrawMultiLineTextResult result = drawMultiLineText(text, availableWidth, form, font, fontName, fontSize, quadding, borderWidth);

    // Verify the results
    EXPECT_GT(result.nLines, 1); // Expecting multiple lines of text
}

// Test error condition where font is invalid
TEST_F(AnnotTest, drawMultiLineText_InvalidFont_2025) {
    const std::string text = "Test text";
    const double availableWidth = 500.0;
    const Form* form = nullptr;
    MockGfxFont invalidFont("InvalidTag", Ref(), std::optional<std::string>("InvalidFont"), GfxFontType::type1, Ref());
    const std::string fontName = "Arial";
    const double fontSize = 12.0;
    const VariableTextQuadding quadding = VariableTextQuadding::leftJustified;
    const double borderWidth = 5.0;

    // Expect the font to be invalid
    EXPECT_CALL(invalidFont, isOk()).WillOnce(testing::Return(false));

    // Call the function under test
    DrawMultiLineTextResult result = drawMultiLineText(text, availableWidth, form, invalidFont, fontName, fontSize, quadding, borderWidth);

    // Verify the result (likely it should not produce any lines of text if font is invalid)
    EXPECT_EQ(result.nLines, 0); // No lines if the font is invalid
}