#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>
#include <cstdio>

#include "HtmlOutputDev.h"
#include "PDFDoc.h"
#include "GlobalParams.h"

class HtmlOutputDevTest_2706 : public ::testing::Test {
protected:
    void SetUp() override {
        // Ensure globalParams is initialized
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }

    // Helper to create a temporary file path
    std::string getTempFilePath() {
        char tmpName[] = "/tmp/htmloutputdev_test_XXXXXX";
        int fd = mkstemp(tmpName);
        if (fd != -1) {
            close(fd);
        }
        return std::string(tmpName);
    }
};

// Test that upsideDown() returns true as per the interface
TEST_F(HtmlOutputDevTest_2706, UpsideDownReturnsTrue_2706) {
    std::string tmpFile = getTempFilePath();

    HtmlOutputDev dev(nullptr, tmpFile.c_str(), "Test Title", "Author",
                      "keywords", "subject", "date", false, 1, false);

    EXPECT_TRUE(dev.upsideDown());

    // Cleanup
    std::remove(tmpFile.c_str());
    std::remove((tmpFile + ".html").c_str());
    std::remove((tmpFile + "s.html").c_str());
}

// Test useDrawChar override
TEST_F(HtmlOutputDevTest_2706, UseDrawCharReturnsTrue_2706) {
    std::string tmpFile = getTempFilePath();

    HtmlOutputDev dev(nullptr, tmpFile.c_str(), "Test Title", "Author",
                      "keywords", "subject", "date", false, 1, false);

    EXPECT_TRUE(dev.useDrawChar());

    std::remove(tmpFile.c_str());
    std::remove((tmpFile + ".html").c_str());
    std::remove((tmpFile + "s.html").c_str());
}

// Test interpretType3Chars override
TEST_F(HtmlOutputDevTest_2706, InterpretType3CharsReturnsFalse_2706) {
    std::string tmpFile = getTempFilePath();

    HtmlOutputDev dev(nullptr, tmpFile.c_str(), "Test Title", "Author",
                      "keywords", "subject", "date", false, 1, false);

    EXPECT_FALSE(dev.interpretType3Chars());

    std::remove(tmpFile.c_str());
    std::remove((tmpFile + ".html").c_str());
    std::remove((tmpFile + "s.html").c_str());
}

// Test needNonText override
TEST_F(HtmlOutputDevTest_2706, NeedNonTextReturnsTrue_2706) {
    std::string tmpFile = getTempFilePath();

    HtmlOutputDev dev(nullptr, tmpFile.c_str(), "Test Title", "Author",
                      "keywords", "subject", "date", false, 1, false);

    EXPECT_TRUE(dev.needNonText());

    std::remove(tmpFile.c_str());
    std::remove((tmpFile + ".html").c_str());
    std::remove((tmpFile + "s.html").c_str());
}

// Test addBackgroundImage adds images (no crash, basic operation)
TEST_F(HtmlOutputDevTest_2706, AddBackgroundImageNoThrow_2706) {
    std::string tmpFile = getTempFilePath();

    HtmlOutputDev dev(nullptr, tmpFile.c_str(), "Test Title", "Author",
                      "keywords", "subject", "date", false, 1, false);

    EXPECT_NO_THROW(dev.addBackgroundImage("test_image.png"));
    EXPECT_NO_THROW(dev.addBackgroundImage("another_image.jpg"));

    std::remove(tmpFile.c_str());
    std::remove((tmpFile + ".html").c_str());
    std::remove((tmpFile + "s.html").c_str());
}

// Test addBackgroundImage with empty string
TEST_F(HtmlOutputDevTest_2706, AddBackgroundImageEmptyString_2706) {
    std::string tmpFile = getTempFilePath();

    HtmlOutputDev dev(nullptr, tmpFile.c_str(), "Test Title", "Author",
                      "keywords", "subject", "date", false, 1, false);

    EXPECT_NO_THROW(dev.addBackgroundImage(""));

    std::remove(tmpFile.c_str());
    std::remove((tmpFile + ".html").c_str());
    std::remove((tmpFile + "s.html").c_str());
}

// Test getPageWidth and getPageHeight default values
TEST_F(HtmlOutputDevTest_2706, DefaultPageDimensions_2706) {
    std::string tmpFile = getTempFilePath();

    HtmlOutputDev dev(nullptr, tmpFile.c_str(), "Test Title", "Author",
                      "keywords", "subject", "date", false, 1, false);

    // Default dimensions should be non-negative
    EXPECT_GE(dev.getPageWidth(), 0);
    EXPECT_GE(dev.getPageHeight(), 0);

    std::remove(tmpFile.c_str());
    std::remove((tmpFile + ".html").c_str());
    std::remove((tmpFile + "s.html").c_str());
}

// Test construction with null title and author
TEST_F(HtmlOutputDevTest_2706, ConstructionWithNullParams_2706) {
    std::string tmpFile = getTempFilePath();

    EXPECT_NO_THROW({
        HtmlOutputDev dev(nullptr, tmpFile.c_str(), nullptr, nullptr,
                          nullptr, nullptr, nullptr, false, 1, false);
    });

    std::remove(tmpFile.c_str());
    std::remove((tmpFile + ".html").c_str());
    std::remove((tmpFile + "s.html").c_str());
}

// Test construction with rawOrder = true
TEST_F(HtmlOutputDevTest_2706, ConstructionWithRawOrder_2706) {
    std::string tmpFile = getTempFilePath();

    HtmlOutputDev dev(nullptr, tmpFile.c_str(), "Title", "Author",
                      "keys", "subj", "date", true, 1, false);

    EXPECT_TRUE(dev.upsideDown());

    std::remove(tmpFile.c_str());
    std::remove((tmpFile + ".html").c_str());
    std::remove((tmpFile + "s.html").c_str());
}

// Test construction with outline = true
TEST_F(HtmlOutputDevTest_2706, ConstructionWithOutline_2706) {
    std::string tmpFile = getTempFilePath();

    HtmlOutputDev dev(nullptr, tmpFile.c_str(), "Title", "Author",
                      "keys", "subj", "date", false, 1, true);

    EXPECT_TRUE(dev.upsideDown());

    std::remove(tmpFile.c_str());
    std::remove((tmpFile + ".html").c_str());
    std::remove((tmpFile + "s.html").c_str());
}

// Test dumpDocOutline with nullptr doc
TEST_F(HtmlOutputDevTest_2706, DumpDocOutlineWithNullDoc_2706) {
    std::string tmpFile = getTempFilePath();

    HtmlOutputDev dev(nullptr, tmpFile.c_str(), "Title", "Author",
                      "keys", "subj", "date", false, 1, false);

    // Passing null doc - should handle gracefully
    bool result = dev.dumpDocOutline(nullptr);
    // We just verify it doesn't crash; result depends on implementation
    (void)result;

    std::remove(tmpFile.c_str());
    std::remove((tmpFile + ".html").c_str());
    std::remove((tmpFile + "s.html").c_str());
}

// Test checkPageSlice with nullptr page
TEST_F(HtmlOutputDevTest_2706, CheckPageSliceWithNullPage_2706) {
    std::string tmpFile = getTempFilePath();

    HtmlOutputDev dev(nullptr, tmpFile.c_str(), "Title", "Author",
                      "keys", "subj", "date", false, 1, false);

    bool result = dev.checkPageSlice(nullptr, 72.0, 72.0, 0, false, false,
                                      0, 0, 100, 100, false);
    EXPECT_TRUE(result);

    std::remove(tmpFile.c_str());
    std::remove((tmpFile + ".html").c_str());
    std::remove((tmpFile + "s.html").c_str());
}

// Test construction with different firstPage values
TEST_F(HtmlOutputDevTest_2706, ConstructionWithDifferentFirstPage_2706) {
    std::string tmpFile = getTempFilePath();

    HtmlOutputDev dev(nullptr, tmpFile.c_str(), "Title", "Author",
                      "keys", "subj", "date", false, 5, false);

    EXPECT_TRUE(dev.upsideDown());
    EXPECT_TRUE(dev.useDrawChar());

    std::remove(tmpFile.c_str());
    std::remove((tmpFile + ".html").c_str());
    std::remove((tmpFile + "s.html").c_str());
}

// Test multiple addBackgroundImage calls
TEST_F(HtmlOutputDevTest_2706, MultipleAddBackgroundImages_2706) {
    std::string tmpFile = getTempFilePath();

    HtmlOutputDev dev(nullptr, tmpFile.c_str(), "Title", "Author",
                      "keys", "subj", "date", false, 1, false);

    for (int i = 0; i < 100; ++i) {
        EXPECT_NO_THROW(dev.addBackgroundImage("image_" + std::to_string(i) + ".png"));
    }

    std::remove(tmpFile.c_str());
    std::remove((tmpFile + ".html").c_str());
    std::remove((tmpFile + "s.html").c_str());
}
