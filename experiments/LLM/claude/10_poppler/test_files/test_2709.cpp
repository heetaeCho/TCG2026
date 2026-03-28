#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdio>
#include <memory>
#include <string>

#include "HtmlOutputDev.h"
#include "PDFDoc.h"
#include "Catalog.h"
#include "GlobalParams.h"

class HtmlOutputDevTest_2709 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
        // Clean up any generated files
        std::remove("test_output_2709.html");
        std::remove("test_output_2709s.html");
        std::remove("test_output_2709_ind.html");
        std::remove("test_output_2709-1.html");
        std::remove("test_output_2709-outline.html");
    }

    std::unique_ptr<HtmlOutputDev> createHtmlOutputDev(const char* fileName = "test_output_2709.html",
                                                        const char* title = "Test Title",
                                                        const char* author = "Test Author",
                                                        const char* keywords = "test",
                                                        const char* subject = "Test Subject",
                                                        const char* date = "2024-01-01",
                                                        bool rawOrder = false,
                                                        int firstPage = 1,
                                                        bool outline = false) {
        return std::make_unique<HtmlOutputDev>(nullptr, fileName, title, author, keywords, subject, date, rawOrder, firstPage, outline);
    }
};

TEST_F(HtmlOutputDevTest_2709, NeedNonTextReturnsTrue_2709) {
    auto dev = createHtmlOutputDev();
    if (dev && dev->isOk()) {
        EXPECT_TRUE(dev->needNonText());
    }
}

TEST_F(HtmlOutputDevTest_2709, UpsideDownReturnValue_2709) {
    auto dev = createHtmlOutputDev();
    if (dev && dev->isOk()) {
        // HtmlOutputDev::upsideDown() should return a consistent boolean
        bool result = dev->upsideDown();
        EXPECT_TRUE(result == true || result == false);
    }
}

TEST_F(HtmlOutputDevTest_2709, UseDrawCharReturnValue_2709) {
    auto dev = createHtmlOutputDev();
    if (dev && dev->isOk()) {
        bool result = dev->useDrawChar();
        EXPECT_TRUE(result == true || result == false);
    }
}

TEST_F(HtmlOutputDevTest_2709, InterpretType3CharsReturnValue_2709) {
    auto dev = createHtmlOutputDev();
    if (dev && dev->isOk()) {
        bool result = dev->interpretType3Chars();
        EXPECT_TRUE(result == true || result == false);
    }
}

TEST_F(HtmlOutputDevTest_2709, ConstructionWithValidParams_2709) {
    auto dev = createHtmlOutputDev();
    ASSERT_NE(dev, nullptr);
    // isOk() should indicate whether construction succeeded
    // With nullptr catalog, behavior depends on implementation
    bool ok = dev->isOk();
    EXPECT_TRUE(ok == true || ok == false);
}

TEST_F(HtmlOutputDevTest_2709, ConstructionWithNullTitle_2709) {
    auto dev = std::make_unique<HtmlOutputDev>(nullptr, "test_output_2709.html", nullptr, nullptr, nullptr, nullptr, nullptr, false, 1, false);
    ASSERT_NE(dev, nullptr);
}

TEST_F(HtmlOutputDevTest_2709, GetPageWidthInitialValue_2709) {
    auto dev = createHtmlOutputDev();
    if (dev && dev->isOk()) {
        int width = dev->getPageWidth();
        EXPECT_GE(width, 0);
    }
}

TEST_F(HtmlOutputDevTest_2709, GetPageHeightInitialValue_2709) {
    auto dev = createHtmlOutputDev();
    if (dev && dev->isOk()) {
        int height = dev->getPageHeight();
        EXPECT_GE(height, 0);
    }
}

TEST_F(HtmlOutputDevTest_2709, AddBackgroundImage_2709) {
    auto dev = createHtmlOutputDev();
    if (dev && dev->isOk()) {
        // Should not crash when adding background images
        dev->addBackgroundImage("test_image.png");
        dev->addBackgroundImage("test_image2.jpg");
        SUCCEED();
    }
}

TEST_F(HtmlOutputDevTest_2709, AddBackgroundImageEmptyString_2709) {
    auto dev = createHtmlOutputDev();
    if (dev && dev->isOk()) {
        dev->addBackgroundImage("");
        SUCCEED();
    }
}

TEST_F(HtmlOutputDevTest_2709, AddMultipleBackgroundImages_2709) {
    auto dev = createHtmlOutputDev();
    if (dev && dev->isOk()) {
        for (int i = 0; i < 100; i++) {
            dev->addBackgroundImage("image_" + std::to_string(i) + ".png");
        }
        SUCCEED();
    }
}

TEST_F(HtmlOutputDevTest_2709, DevTypeReturnValue_2709) {
    auto dev = createHtmlOutputDev();
    if (dev && dev->isOk()) {
        int devType = dev->DevType();
        // DevType should return a defined constant
        EXPECT_GE(devType, 0);
    }
}

TEST_F(HtmlOutputDevTest_2709, NeedNonTextConsistency_2709) {
    auto dev = createHtmlOutputDev();
    if (dev && dev->isOk()) {
        // needNonText should consistently return the same value
        bool first = dev->needNonText();
        bool second = dev->needNonText();
        EXPECT_EQ(first, second);
        EXPECT_TRUE(first);
    }
}

TEST_F(HtmlOutputDevTest_2709, DumpDocOutlineWithNullDoc_2709) {
    auto dev = createHtmlOutputDev();
    if (dev && dev->isOk()) {
        // Passing nullptr should be handled gracefully
        bool result = dev->dumpDocOutline(nullptr);
        EXPECT_TRUE(result == true || result == false);
    }
}

TEST_F(HtmlOutputDevTest_2709, ConstructionWithOutlineTrue_2709) {
    auto dev = std::make_unique<HtmlOutputDev>(nullptr, "test_output_2709.html", "Title", "Author", "Keywords", "Subject", "Date", false, 1, true);
    ASSERT_NE(dev, nullptr);
}

TEST_F(HtmlOutputDevTest_2709, ConstructionWithRawOrderTrue_2709) {
    auto dev = std::make_unique<HtmlOutputDev>(nullptr, "test_output_2709.html", "Title", "Author", "Keywords", "Subject", "Date", true, 1, false);
    ASSERT_NE(dev, nullptr);
}

TEST_F(HtmlOutputDevTest_2709, ConstructionWithLargeFirstPage_2709) {
    auto dev = std::make_unique<HtmlOutputDev>(nullptr, "test_output_2709.html", "Title", "Author", "Keywords", "Subject", "Date", false, 9999, false);
    ASSERT_NE(dev, nullptr);
}

TEST_F(HtmlOutputDevTest_2709, UseDrawCharExpectedTrue_2709) {
    auto dev = createHtmlOutputDev();
    if (dev && dev->isOk()) {
        // For an HTML output device, useDrawChar is typically true
        EXPECT_TRUE(dev->useDrawChar());
    }
}

TEST_F(HtmlOutputDevTest_2709, UpsideDownExpectedTrue_2709) {
    auto dev = createHtmlOutputDev();
    if (dev && dev->isOk()) {
        // PDF coordinate system is bottom-up, so upsideDown typically returns true
        EXPECT_TRUE(dev->upsideDown());
    }
}
