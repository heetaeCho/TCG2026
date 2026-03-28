#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <glib.h>
#include "GooString.h"

// We need to test get_font_name_from_word which is a static function.
// We'll mock TextWord to control getFontName behavior.

// Forward declare what we need
class TextFontInfo;
class AnnotLink;
class Matrix;
class GfxState;

// Minimal mock of TextWord that provides getFontName
class TextWord {
public:
    TextWord() = default;
    virtual ~TextWord() = default;
    
    virtual const GooString *getFontName(int idx) const {
        return font_name_.get();
    }
    
    void setFontName(const char *name) {
        if (name) {
            font_name_ = std::make_unique<GooString>(name);
        } else {
            font_name_.reset();
        }
    }
    
    void clearFontName() {
        font_name_.reset();
    }

private:
    std::unique_ptr<GooString> font_name_;
};

// Now include the static function - we replicate it here since it's static
// and we can't link to it. We replicate it exactly as given.
static gchar *get_font_name_from_word(const TextWord *word, gint word_i)
{
    const GooString *font_name = word->getFontName(word_i);
    const gchar *name;
    gboolean subset;
    size_t i;

    if (!font_name || font_name->empty()) {
        return g_strdup("Default");
    }

    for (i = 0; i < font_name->size(); ++i) {
        if (font_name->getChar(i) < 'A' || font_name->getChar(i) > 'Z') {
            break;
        }
    }

    subset = i > 0 && i < font_name->size() && font_name->getChar(i) == '+';

    name = font_name->c_str();
    if (subset) {
        name += i + 1;
    }

    return g_strdup(name);
}

class GetFontNameFromWordTest_2476 : public ::testing::Test {
protected:
    TextWord word_;
    
    void TearDown() override {
    }
    
    // Helper to call the function and manage memory
    std::string callGetFontName(const char* fontName, int idx = 0) {
        if (fontName) {
            word_.setFontName(fontName);
        } else {
            word_.clearFontName();
        }
        gchar *result = get_font_name_from_word(&word_, idx);
        std::string ret(result);
        g_free(result);
        return ret;
    }
};

// Test: null font name returns "Default"
TEST_F(GetFontNameFromWordTest_2476, NullFontNameReturnsDefault_2476) {
    word_.clearFontName();
    gchar *result = get_font_name_from_word(&word_, 0);
    EXPECT_STREQ(result, "Default");
    g_free(result);
}

// Test: empty font name returns "Default"
TEST_F(GetFontNameFromWordTest_2476, EmptyFontNameReturnsDefault_2476) {
    EXPECT_EQ(callGetFontName(""), "Default");
}

// Test: font name without subset prefix returns full name
TEST_F(GetFontNameFromWordTest_2476, NoSubsetPrefixReturnsFullName_2476) {
    EXPECT_EQ(callGetFontName("TimesNewRoman"), "TimesNewRoman");
}

// Test: font name with valid subset prefix (e.g., "ABCDEF+TimesNewRoman")
TEST_F(GetFontNameFromWordTest_2476, SubsetPrefixStripped_2476) {
    EXPECT_EQ(callGetFontName("ABCDEF+TimesNewRoman"), "TimesNewRoman");
}

// Test: single uppercase letter followed by '+' and name
TEST_F(GetFontNameFromWordTest_2476, SingleUppercaseSubsetPrefix_2476) {
    EXPECT_EQ(callGetFontName("A+Arial"), "Arial");
}

// Test: all uppercase letters followed by '+' 
TEST_F(GetFontNameFromWordTest_2476, AllUppercaseWithPlus_2476) {
    EXPECT_EQ(callGetFontName("ZZZZZZ+Helvetica"), "Helvetica");
}

// Test: uppercase letters but no '+' sign - not a subset, return full name
TEST_F(GetFontNameFromWordTest_2476, UppercaseWithoutPlusReturnsFullName_2476) {
    EXPECT_EQ(callGetFontName("ABCDEFHelvetica"), "ABCDEFHelvetica");
}

// Test: starts with lowercase letter - no subset stripping
TEST_F(GetFontNameFromWordTest_2476, StartsWithLowercaseNoStripping_2476) {
    EXPECT_EQ(callGetFontName("arial"), "arial");
}

// Test: starts with '+' - i==0 so subset is false, return full name
TEST_F(GetFontNameFromWordTest_2476, StartsWithPlusReturnsFullName_2476) {
    EXPECT_EQ(callGetFontName("+Arial"), "+Arial");
}

// Test: all uppercase letters with no '+' at end - not a subset
TEST_F(GetFontNameFromWordTest_2476, AllUppercaseNoPlusReturnsFullName_2476) {
    EXPECT_EQ(callGetFontName("ABCDEF"), "ABCDEF");
}

// Test: uppercase letters followed by '+' only (nothing after)
TEST_F(GetFontNameFromWordTest_2476, SubsetPrefixWithEmptyNameAfterPlus_2476) {
    EXPECT_EQ(callGetFontName("ABC+"), "");
}

// Test: font name is just a single non-uppercase character
TEST_F(GetFontNameFromWordTest_2476, SingleNonUppercaseChar_2476) {
    EXPECT_EQ(callGetFontName("a"), "a");
}

// Test: font name is a single uppercase character (no '+' after)
TEST_F(GetFontNameFromWordTest_2476, SingleUppercaseCharNoPlusAfter_2476) {
    EXPECT_EQ(callGetFontName("A"), "A");
}

// Test: digit after uppercase letters (not '+')
TEST_F(GetFontNameFromWordTest_2476, DigitAfterUppercaseNoStripping_2476) {
    EXPECT_EQ(callGetFontName("ABC123"), "ABC123");
}

// Test: mixed case before '+' - only leading uppercase matters
TEST_F(GetFontNameFromWordTest_2476, MixedCaseBeforePlusNoStripping_2476) {
    EXPECT_EQ(callGetFontName("ABc+Font"), "ABc+Font");
}

// Test: '+' appears later but preceded by non-uppercase
TEST_F(GetFontNameFromWordTest_2476, PlusAfterNonUppercaseNoStripping_2476) {
    EXPECT_EQ(callGetFontName("Ab+Font"), "Ab+Font");
}

// Test: typical 6-letter subset prefix
TEST_F(GetFontNameFromWordTest_2476, TypicalSixLetterSubset_2476) {
    EXPECT_EQ(callGetFontName("BCDEFG+CourierNew"), "CourierNew");
}

// Test: long uppercase prefix followed by '+'
TEST_F(GetFontNameFromWordTest_2476, LongUppercasePrefixWithPlus_2476) {
    EXPECT_EQ(callGetFontName("ABCDEFGHIJKLMNOP+MyFont"), "MyFont");
}

// Test: font name with spaces after subset prefix
TEST_F(GetFontNameFromWordTest_2476, SubsetWithSpacesInFontName_2476) {
    EXPECT_EQ(callGetFontName("ABC+Times New Roman"), "Times New Roman");
}

// Test: font name that is just "Default"
TEST_F(GetFontNameFromWordTest_2476, FontNameIsDefaultString_2476) {
    EXPECT_EQ(callGetFontName("Default"), "Default");
}

// Test: font name with numbers and special chars (no subset)
TEST_F(GetFontNameFromWordTest_2476, SpecialCharsNoSubset_2476) {
    EXPECT_EQ(callGetFontName("123-Font!@#"), "123-Font!@#");
}

// Test: multiple '+' signs - only first matters after uppercase prefix
TEST_F(GetFontNameFromWordTest_2476, MultiplePlusSigns_2476) {
    EXPECT_EQ(callGetFontName("AB+Font+Extra"), "Font+Extra");
}
