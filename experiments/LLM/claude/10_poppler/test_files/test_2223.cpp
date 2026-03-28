#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <optional>
#include <string>
#include <vector>

// Forward declarations and minimal reproductions needed for testing
// We need to match the actual memory layout used by the function

// Minimal FontInfo stub matching the interface
class FontInfo {
public:
    std::optional<std::string> file_;

    const std::optional<std::string> &getFile() const { return file_; }
};

// Match the actual PopplerFontsIter struct layout
struct _PopplerFontsIter {
    std::vector<FontInfo*> items;
    int index;
};

typedef struct _PopplerFontsIter PopplerFontsIter;

// Function under test - we reproduce the implementation as given
const char *poppler_fonts_iter_get_file_name(PopplerFontsIter *iter) {
    FontInfo *info;
    info = iter->items[iter->index];
    const std::optional<std::string> &file = info->getFile();
    if (file) {
        return file->c_str();
    }
    return nullptr;
}

class PopplerFontsIterGetFileNameTest_2223 : public ::testing::Test {
protected:
    void TearDown() override {
        for (auto* fi : fontInfos_) {
            delete fi;
        }
        fontInfos_.clear();
    }

    FontInfo* createFontInfo(const std::optional<std::string>& file) {
        FontInfo* fi = new FontInfo();
        fi->file_ = file;
        fontInfos_.push_back(fi);
        return fi;
    }

    std::vector<FontInfo*> fontInfos_;
};

TEST_F(PopplerFontsIterGetFileNameTest_2223, ReturnsFileName_WhenFileIsPresent_2223) {
    FontInfo* fi = createFontInfo(std::string("/usr/share/fonts/test.ttf"));

    PopplerFontsIter iter;
    iter.items.push_back(fi);
    iter.index = 0;

    const char* result = poppler_fonts_iter_get_file_name(&iter);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "/usr/share/fonts/test.ttf");
}

TEST_F(PopplerFontsIterGetFileNameTest_2223, ReturnsNullptr_WhenFileIsNullopt_2223) {
    FontInfo* fi = createFontInfo(std::nullopt);

    PopplerFontsIter iter;
    iter.items.push_back(fi);
    iter.index = 0;

    const char* result = poppler_fonts_iter_get_file_name(&iter);
    EXPECT_EQ(result, nullptr);
}

TEST_F(PopplerFontsIterGetFileNameTest_2223, ReturnsEmptyString_WhenFileIsEmptyString_2223) {
    FontInfo* fi = createFontInfo(std::string(""));

    PopplerFontsIter iter;
    iter.items.push_back(fi);
    iter.index = 0;

    const char* result = poppler_fonts_iter_get_file_name(&iter);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "");
}

TEST_F(PopplerFontsIterGetFileNameTest_2223, ReturnsCorrectFile_ForDifferentIndex_2223) {
    FontInfo* fi0 = createFontInfo(std::string("file0.ttf"));
    FontInfo* fi1 = createFontInfo(std::string("file1.ttf"));
    FontInfo* fi2 = createFontInfo(std::string("file2.ttf"));

    PopplerFontsIter iter;
    iter.items.push_back(fi0);
    iter.items.push_back(fi1);
    iter.items.push_back(fi2);
    iter.index = 2;

    const char* result = poppler_fonts_iter_get_file_name(&iter);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "file2.ttf");
}

TEST_F(PopplerFontsIterGetFileNameTest_2223, ReturnsCorrectFile_ForMiddleIndex_2223) {
    FontInfo* fi0 = createFontInfo(std::string("first.ttf"));
    FontInfo* fi1 = createFontInfo(std::string("second.ttf"));
    FontInfo* fi2 = createFontInfo(std::nullopt);

    PopplerFontsIter iter;
    iter.items.push_back(fi0);
    iter.items.push_back(fi1);
    iter.items.push_back(fi2);
    iter.index = 1;

    const char* result = poppler_fonts_iter_get_file_name(&iter);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "second.ttf");
}

TEST_F(PopplerFontsIterGetFileNameTest_2223, ReturnsNullptr_ForMiddleIndexWithNullopt_2223) {
    FontInfo* fi0 = createFontInfo(std::string("first.ttf"));
    FontInfo* fi1 = createFontInfo(std::nullopt);
    FontInfo* fi2 = createFontInfo(std::string("third.ttf"));

    PopplerFontsIter iter;
    iter.items.push_back(fi0);
    iter.items.push_back(fi1);
    iter.items.push_back(fi2);
    iter.index = 1;

    const char* result = poppler_fonts_iter_get_file_name(&iter);
    EXPECT_EQ(result, nullptr);
}

TEST_F(PopplerFontsIterGetFileNameTest_2223, HandlesLongFilePath_2223) {
    std::string longPath(1024, 'a');
    longPath = "/very/long/path/" + longPath + ".ttf";
    FontInfo* fi = createFontInfo(longPath);

    PopplerFontsIter iter;
    iter.items.push_back(fi);
    iter.index = 0;

    const char* result = poppler_fonts_iter_get_file_name(&iter);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, longPath.c_str());
}

TEST_F(PopplerFontsIterGetFileNameTest_2223, HandlesSpecialCharactersInFileName_2223) {
    FontInfo* fi = createFontInfo(std::string("/path/to/font with spaces & (special).ttf"));

    PopplerFontsIter iter;
    iter.items.push_back(fi);
    iter.index = 0;

    const char* result = poppler_fonts_iter_get_file_name(&iter);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "/path/to/font with spaces & (special).ttf");
}

TEST_F(PopplerFontsIterGetFileNameTest_2223, HandlesUnicodeInFileName_2223) {
    FontInfo* fi = createFontInfo(std::string("/path/to/フォント.ttf"));

    PopplerFontsIter iter;
    iter.items.push_back(fi);
    iter.index = 0;

    const char* result = poppler_fonts_iter_get_file_name(&iter);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "/path/to/フォント.ttf");
}

TEST_F(PopplerFontsIterGetFileNameTest_2223, FirstIndexReturnsCorrectly_2223) {
    FontInfo* fi = createFontInfo(std::string("only.ttf"));

    PopplerFontsIter iter;
    iter.items.push_back(fi);
    iter.index = 0;

    const char* result = poppler_fonts_iter_get_file_name(&iter);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "only.ttf");
}
