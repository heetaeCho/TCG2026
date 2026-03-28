#include <gtest/gtest.h>
#include <glib.h>
#include <cstring>

// Include the necessary headers
extern "C" {
#include "poppler-annot.h"
}

// Forward declare the struct and function if not fully available from headers
typedef struct _PopplerFontDescription PopplerFontDescription;

struct _PopplerFontDescription {
    char *font_name;
    double size_pt;
    PopplerStretch stretch;
    PopplerStyle style;
    PopplerWeight weight;
};

extern "C" PopplerFontDescription *poppler_font_description_new(const char *font_name);

class PopplerFontDescriptionTest_2124 : public ::testing::Test {
protected:
    void TearDown() override {
        // Clean up any allocated font descriptions
        for (auto *fd : allocated_) {
            if (fd) {
                g_free(fd->font_name);
                g_free(fd);
            }
        }
    }

    PopplerFontDescription *CreateAndTrack(const char *font_name) {
        auto *fd = poppler_font_description_new(font_name);
        if (fd) {
            allocated_.push_back(fd);
        }
        return fd;
    }

    std::vector<PopplerFontDescription *> allocated_;
};

TEST_F(PopplerFontDescriptionTest_2124, ReturnsNonNull_2124) {
    PopplerFontDescription *fd = CreateAndTrack("Arial");
    ASSERT_NE(fd, nullptr);
}

TEST_F(PopplerFontDescriptionTest_2124, FontNameIsCopied_2124) {
    const char *name = "Helvetica";
    PopplerFontDescription *fd = CreateAndTrack(name);
    ASSERT_NE(fd, nullptr);
    EXPECT_STREQ(fd->font_name, "Helvetica");
    // Ensure it's a copy, not the same pointer
    EXPECT_NE(fd->font_name, name);
}

TEST_F(PopplerFontDescriptionTest_2124, DefaultSizeIs11_2124) {
    PopplerFontDescription *fd = CreateAndTrack("Times");
    ASSERT_NE(fd, nullptr);
    EXPECT_DOUBLE_EQ(fd->size_pt, 11.0);
}

TEST_F(PopplerFontDescriptionTest_2124, DefaultStretchIsNormal_2124) {
    PopplerFontDescription *fd = CreateAndTrack("Courier");
    ASSERT_NE(fd, nullptr);
    EXPECT_EQ(fd->stretch, POPPLER_STRETCH_NORMAL);
}

TEST_F(PopplerFontDescriptionTest_2124, DefaultStyleIsNormal_2124) {
    PopplerFontDescription *fd = CreateAndTrack("Courier");
    ASSERT_NE(fd, nullptr);
    EXPECT_EQ(fd->style, POPPLER_STYLE_NORMAL);
}

TEST_F(PopplerFontDescriptionTest_2124, DefaultWeightIsNormal_2124) {
    PopplerFontDescription *fd = CreateAndTrack("Courier");
    ASSERT_NE(fd, nullptr);
    EXPECT_EQ(fd->weight, POPPLER_WEIGHT_NORMAL);
}

TEST_F(PopplerFontDescriptionTest_2124, EmptyFontName_2124) {
    PopplerFontDescription *fd = CreateAndTrack("");
    ASSERT_NE(fd, nullptr);
    EXPECT_STREQ(fd->font_name, "");
}

TEST_F(PopplerFontDescriptionTest_2124, LongFontName_2124) {
    std::string longName(1024, 'A');
    PopplerFontDescription *fd = CreateAndTrack(longName.c_str());
    ASSERT_NE(fd, nullptr);
    EXPECT_STREQ(fd->font_name, longName.c_str());
}

TEST_F(PopplerFontDescriptionTest_2124, FontNameWithSpaces_2124) {
    PopplerFontDescription *fd = CreateAndTrack("Times New Roman");
    ASSERT_NE(fd, nullptr);
    EXPECT_STREQ(fd->font_name, "Times New Roman");
}

TEST_F(PopplerFontDescriptionTest_2124, FontNameWithSpecialCharacters_2124) {
    PopplerFontDescription *fd = CreateAndTrack("Font-Name_v2.0");
    ASSERT_NE(fd, nullptr);
    EXPECT_STREQ(fd->font_name, "Font-Name_v2.0");
}

TEST_F(PopplerFontDescriptionTest_2124, MultipleAllocationsAreIndependent_2124) {
    PopplerFontDescription *fd1 = CreateAndTrack("Arial");
    PopplerFontDescription *fd2 = CreateAndTrack("Helvetica");
    ASSERT_NE(fd1, nullptr);
    ASSERT_NE(fd2, nullptr);
    EXPECT_NE(fd1, fd2);
    EXPECT_STREQ(fd1->font_name, "Arial");
    EXPECT_STREQ(fd2->font_name, "Helvetica");
}

TEST_F(PopplerFontDescriptionTest_2124, StretchNormalValue_2124) {
    PopplerFontDescription *fd = CreateAndTrack("Test");
    ASSERT_NE(fd, nullptr);
    EXPECT_EQ(fd->stretch, 4); // POPPLER_STRETCH_NORMAL == 4
}

TEST_F(PopplerFontDescriptionTest_2124, StyleNormalValue_2124) {
    PopplerFontDescription *fd = CreateAndTrack("Test");
    ASSERT_NE(fd, nullptr);
    EXPECT_EQ(fd->style, 0); // POPPLER_STYLE_NORMAL == 0
}

TEST_F(PopplerFontDescriptionTest_2124, WeightNormalValue_2124) {
    PopplerFontDescription *fd = CreateAndTrack("Test");
    ASSERT_NE(fd, nullptr);
    EXPECT_EQ(fd->weight, 400); // POPPLER_WEIGHT_NORMAL == 400
}

TEST_F(PopplerFontDescriptionTest_2124, FontNameWithUTF8Characters_2124) {
    PopplerFontDescription *fd = CreateAndTrack("日本語フォント");
    ASSERT_NE(fd, nullptr);
    EXPECT_STREQ(fd->font_name, "日本語フォント");
}

TEST_F(PopplerFontDescriptionTest_2124, SingleCharacterFontName_2124) {
    PopplerFontDescription *fd = CreateAndTrack("X");
    ASSERT_NE(fd, nullptr);
    EXPECT_STREQ(fd->font_name, "X");
    EXPECT_DOUBLE_EQ(fd->size_pt, 11.0);
    EXPECT_EQ(fd->stretch, POPPLER_STRETCH_NORMAL);
    EXPECT_EQ(fd->style, POPPLER_STYLE_NORMAL);
    EXPECT_EQ(fd->weight, POPPLER_WEIGHT_NORMAL);
}
