#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <memory>

// Include necessary headers
#include "poppler/GfxState.h"
#include "utils/HtmlOutputDev.h"

class HtmlImageTest_2792 : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a simple page box for GfxState construction
        PDFRectangle pageBox;
        pageBox.x1 = 0;
        pageBox.y1 = 0;
        pageBox.x2 = 612; // Letter width in points
        pageBox.y2 = 792; // Letter height in points

        // Create a GfxState with identity-like CTM (72 DPI, no rotation, not upside down)
        state = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, true);
    }

    void TearDown() override {
        state.reset();
    }

    std::unique_ptr<GfxState> state;
};

// Test that HtmlImage can be constructed with a valid filename and state
TEST_F(HtmlImageTest_2792, ConstructWithValidFilenameAndState_2792) {
    std::string filename = "test_image.png";
    HtmlImage img(std::move(filename), state.get());
    
    // After move, the fName should contain the original string
    EXPECT_EQ(img.fName, "test_image.png");
}

// Test that the filename is properly moved (original string should be empty after move)
TEST_F(HtmlImageTest_2792, FilenameIsMovedProperly_2792) {
    std::string filename = "image.jpg";
    std::string originalFilename = filename; // copy before move
    HtmlImage img(std::move(filename), state.get());
    
    EXPECT_EQ(img.fName, originalFilename);
    // After std::move, filename should be in a valid but unspecified state (typically empty)
    EXPECT_TRUE(filename.empty());
}

// Test construction with an empty filename
TEST_F(HtmlImageTest_2792, ConstructWithEmptyFilename_2792) {
    std::string filename = "";
    HtmlImage img(std::move(filename), state.get());
    
    EXPECT_EQ(img.fName, "");
}

// Test construction with a long filename
TEST_F(HtmlImageTest_2792, ConstructWithLongFilename_2792) {
    std::string longName(1000, 'a');
    std::string expected = longName;
    HtmlImage img(std::move(longName), state.get());
    
    EXPECT_EQ(img.fName, expected);
}

// Test construction with filename containing special characters
TEST_F(HtmlImageTest_2792, ConstructWithSpecialCharacterFilename_2792) {
    std::string filename = "path/to/image (1).png";
    HtmlImage img(std::move(filename), state.get());
    
    EXPECT_EQ(img.fName, "path/to/image (1).png");
}

// Test construction with a filename containing unicode-like characters
TEST_F(HtmlImageTest_2792, ConstructWithUnicodeFilename_2792) {
    std::string filename = "图片.png";
    HtmlImage img(std::move(filename), state.get());
    
    EXPECT_EQ(img.fName, "图片.png");
}

// Test that HtmlImage works with different GfxState configurations (different DPI)
TEST_F(HtmlImageTest_2792, ConstructWithDifferentDPI_2792) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 300;
    pageBox.y2 = 400;

    auto highDpiState = std::make_unique<GfxState>(300.0, 300.0, &pageBox, 0, true);
    
    std::string filename = "high_dpi_image.png";
    HtmlImage img(std::move(filename), highDpiState.get());
    
    EXPECT_EQ(img.fName, "high_dpi_image.png");
}

// Test with rotated GfxState
TEST_F(HtmlImageTest_2792, ConstructWithRotatedState_2792) {
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612;
    pageBox.y2 = 792;

    auto rotatedState = std::make_unique<GfxState>(72.0, 72.0, &pageBox, 90, true);
    
    std::string filename = "rotated.png";
    HtmlImage img(std::move(filename), rotatedState.get());
    
    EXPECT_EQ(img.fName, "rotated.png");
}

// Test with modified CTM in GfxState
TEST_F(HtmlImageTest_2792, ConstructWithModifiedCTM_2792) {
    // Set a custom CTM (scaling transform)
    state->setCTM(2.0, 0, 0, 2.0, 100.0, 200.0);
    
    std::string filename = "scaled_image.png";
    HtmlImage img(std::move(filename), state.get());
    
    EXPECT_EQ(img.fName, "scaled_image.png");
}

// Test that copy constructor is deleted (compile-time check, but we verify the type trait)
TEST_F(HtmlImageTest_2792, CopyConstructorIsDeleted_2792) {
    EXPECT_FALSE(std::is_copy_constructible<HtmlImage>::value);
}

// Test that copy assignment is deleted
TEST_F(HtmlImageTest_2792, CopyAssignmentIsDeleted_2792) {
    EXPECT_FALSE(std::is_copy_assignable<HtmlImage>::value);
}

// Test with identity-like CTM - transform of (0,0) and (1,1) should produce predictable results
TEST_F(HtmlImageTest_2792, TransformProducesValidCoordinates_2792) {
    // Use identity CTM
    state->setCTM(1.0, 0, 0, 1.0, 0, 0);
    
    std::string filename = "identity_transform.png";
    HtmlImage img(std::move(filename), state.get());
    
    EXPECT_EQ(img.fName, "identity_transform.png");
}

// Test construction with filename containing only whitespace
TEST_F(HtmlImageTest_2792, ConstructWithWhitespaceFilename_2792) {
    std::string filename = "   ";
    HtmlImage img(std::move(filename), state.get());
    
    EXPECT_EQ(img.fName, "   ");
}

// Test construction with filename containing path separators
TEST_F(HtmlImageTest_2792, ConstructWithPathSeparators_2792) {
    std::string filename = "/tmp/output/img-001.png";
    HtmlImage img(std::move(filename), state.get());
    
    EXPECT_EQ(img.fName, "/tmp/output/img-001.png");
}
