#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <optional>
#include <string>
#include <vector>

// Forward declarations and minimal type stubs needed for testing
// We need to recreate enough structure to test the function

// Minimal FontInfo mock/stub for testing purposes
class FontInfo {
public:
    FontInfo() = default;
    
    void setSubstituteName(const std::optional<std::string>& name) {
        substituteName_ = name;
    }
    
    const std::optional<std::string>& getSubstituteName() const {
        return substituteName_;
    }
    
    const std::optional<std::string>& getName() const {
        return name_;
    }
    
    const std::optional<std::string>& getFile() const {
        return file_;
    }
    
private:
    std::optional<std::string> name_;
    std::optional<std::string> substituteName_;
    std::optional<std::string> file_;
};

// Recreate the PopplerFontsIter structure
struct _PopplerFontsIter {
    std::vector<FontInfo*> items;
    int index;
};

typedef struct _PopplerFontsIter PopplerFontsIter;

// The function under test - reimplemented based on the provided code
const char *poppler_fonts_iter_get_substitute_name(PopplerFontsIter *iter) {
    FontInfo *info;
    info = iter->items[iter->index];
    const std::optional<std::string> &name = info->getSubstituteName();
    if (name) {
        return name->c_str();
    }
    return nullptr;
}

class PopplerFontsIterGetSubstituteNameTest_2222 : public ::testing::Test {
protected:
    void SetUp() override {
        iter_ = new PopplerFontsIter();
    }
    
    void TearDown() override {
        for (auto* item : iter_->items) {
            delete item;
        }
        delete iter_;
    }
    
    PopplerFontsIter* iter_;
};

// Test: When substitute name is set, function returns the correct C string
TEST_F(PopplerFontsIterGetSubstituteNameTest_2222, ReturnsSubstituteNameWhenSet_2222) {
    FontInfo* fontInfo = new FontInfo();
    fontInfo->setSubstituteName("Arial");
    iter_->items.push_back(fontInfo);
    iter_->index = 0;
    
    const char* result = poppler_fonts_iter_get_substitute_name(iter_);
    
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "Arial");
}

// Test: When substitute name is not set (nullopt), function returns nullptr
TEST_F(PopplerFontsIterGetSubstituteNameTest_2222, ReturnsNullptrWhenSubstituteNameNotSet_2222) {
    FontInfo* fontInfo = new FontInfo();
    fontInfo->setSubstituteName(std::nullopt);
    iter_->items.push_back(fontInfo);
    iter_->index = 0;
    
    const char* result = poppler_fonts_iter_get_substitute_name(iter_);
    
    EXPECT_EQ(result, nullptr);
}

// Test: When substitute name is an empty string, function returns empty string (not nullptr)
TEST_F(PopplerFontsIterGetSubstituteNameTest_2222, ReturnsEmptyStringWhenSubstituteNameIsEmpty_2222) {
    FontInfo* fontInfo = new FontInfo();
    fontInfo->setSubstituteName(std::string(""));
    iter_->items.push_back(fontInfo);
    iter_->index = 0;
    
    const char* result = poppler_fonts_iter_get_substitute_name(iter_);
    
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "");
}

// Test: Function correctly accesses item at the current index
TEST_F(PopplerFontsIterGetSubstituteNameTest_2222, AccessesCorrectItemByIndex_2222) {
    FontInfo* fontInfo0 = new FontInfo();
    fontInfo0->setSubstituteName("Font0");
    
    FontInfo* fontInfo1 = new FontInfo();
    fontInfo1->setSubstituteName("Font1");
    
    FontInfo* fontInfo2 = new FontInfo();
    fontInfo2->setSubstituteName("Font2");
    
    iter_->items.push_back(fontInfo0);
    iter_->items.push_back(fontInfo1);
    iter_->items.push_back(fontInfo2);
    
    iter_->index = 1;
    const char* result = poppler_fonts_iter_get_substitute_name(iter_);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "Font1");
    
    iter_->index = 2;
    result = poppler_fonts_iter_get_substitute_name(iter_);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "Font2");
    
    iter_->index = 0;
    result = poppler_fonts_iter_get_substitute_name(iter_);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "Font0");
}

// Test: Substitute name with special characters
TEST_F(PopplerFontsIterGetSubstituteNameTest_2222, ReturnsSubstituteNameWithSpecialCharacters_2222) {
    FontInfo* fontInfo = new FontInfo();
    fontInfo->setSubstituteName("Times-New Roman (Bold+Italic)");
    iter_->items.push_back(fontInfo);
    iter_->index = 0;
    
    const char* result = poppler_fonts_iter_get_substitute_name(iter_);
    
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "Times-New Roman (Bold+Italic)");
}

// Test: Substitute name with very long string
TEST_F(PopplerFontsIterGetSubstituteNameTest_2222, ReturnsLongSubstituteName_2222) {
    std::string longName(1000, 'A');
    FontInfo* fontInfo = new FontInfo();
    fontInfo->setSubstituteName(longName);
    iter_->items.push_back(fontInfo);
    iter_->index = 0;
    
    const char* result = poppler_fonts_iter_get_substitute_name(iter_);
    
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, longName.c_str());
}

// Test: Multiple items where some have substitute names and some don't
TEST_F(PopplerFontsIterGetSubstituteNameTest_2222, MixedSubstituteNames_2222) {
    FontInfo* fontInfo0 = new FontInfo();
    fontInfo0->setSubstituteName("SubFont");
    
    FontInfo* fontInfo1 = new FontInfo();
    fontInfo1->setSubstituteName(std::nullopt);
    
    iter_->items.push_back(fontInfo0);
    iter_->items.push_back(fontInfo1);
    
    iter_->index = 0;
    const char* result0 = poppler_fonts_iter_get_substitute_name(iter_);
    ASSERT_NE(result0, nullptr);
    EXPECT_STREQ(result0, "SubFont");
    
    iter_->index = 1;
    const char* result1 = poppler_fonts_iter_get_substitute_name(iter_);
    EXPECT_EQ(result1, nullptr);
}

// Test: Substitute name with Unicode characters
TEST_F(PopplerFontsIterGetSubstituteNameTest_2222, ReturnsSubstituteNameWithUnicode_2222) {
    FontInfo* fontInfo = new FontInfo();
    fontInfo->setSubstituteName("フォント名");
    iter_->items.push_back(fontInfo);
    iter_->index = 0;
    
    const char* result = poppler_fonts_iter_get_substitute_name(iter_);
    
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "フォント名");
}

// Test: First index (boundary - index 0)
TEST_F(PopplerFontsIterGetSubstituteNameTest_2222, FirstIndexBoundary_2222) {
    FontInfo* fontInfo = new FontInfo();
    fontInfo->setSubstituteName("FirstFont");
    iter_->items.push_back(fontInfo);
    iter_->index = 0;
    
    const char* result = poppler_fonts_iter_get_substitute_name(iter_);
    
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "FirstFont");
}

// Test: Last index in a list (boundary)
TEST_F(PopplerFontsIterGetSubstituteNameTest_2222, LastIndexBoundary_2222) {
    for (int i = 0; i < 5; i++) {
        FontInfo* fi = new FontInfo();
        fi->setSubstituteName("Font" + std::to_string(i));
        iter_->items.push_back(fi);
    }
    
    iter_->index = 4;
    const char* result = poppler_fonts_iter_get_substitute_name(iter_);
    
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "Font4");
}

// Test: Substitute name with whitespace only
TEST_F(PopplerFontsIterGetSubstituteNameTest_2222, ReturnsWhitespaceOnlySubstituteName_2222) {
    FontInfo* fontInfo = new FontInfo();
    fontInfo->setSubstituteName("   ");
    iter_->items.push_back(fontInfo);
    iter_->index = 0;
    
    const char* result = poppler_fonts_iter_get_substitute_name(iter_);
    
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "   ");
}
