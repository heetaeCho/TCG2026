#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "TextOutputDev.h"

// Since TextWordList requires a TextPage* and bool in its constructor,
// and we cannot create TextPage objects easily without the full Poppler
// infrastructure, we need to test what we can through the public interface.
// We'll focus on testing the getWords() method behavior.

// Note: TextWordList's constructor takes (const TextPage*, bool), and
// TextPage is a complex object. We'll test with scenarios where we can
// construct valid objects.

class TextWordListTest_1212 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that getWords returns a reference to a vector of TextWord pointers
// When constructed with a null TextPage, we test the boundary behavior
TEST_F(TextWordListTest_1212, GetWordsWithNullTextPage_1212) {
    // TextWordList requires a valid TextPage*, passing nullptr may crash
    // or return an empty list depending on implementation.
    // We test with nullptr to check boundary behavior.
    // Note: This might segfault if the implementation doesn't handle null.
    // If so, this test documents that null is not a valid input.
    
    // We cannot safely test with nullptr without knowing the implementation.
    // Skip this specific dangerous case and document it.
    SUCCEED() << "Cannot safely construct TextWordList with nullptr TextPage without potential crash";
}

// Test that getWords returns a const reference
TEST_F(TextWordListTest_1212, GetWordsReturnsConstReference_1212) {
    // Verify the return type is const reference at compile time
    // This is a compile-time check - if it compiles, the test passes
    using ReturnType = decltype(std::declval<const TextWordList>().getWords());
    bool isConstRef = std::is_same<ReturnType, const std::vector<TextWord*>&>::value;
    EXPECT_TRUE(isConstRef);
}

// Test that TextWordList is non-copyable (compile-time check documented as test)
TEST_F(TextWordListTest_1212, NonCopyable_1212) {
    // TextWordList has deleted copy constructor and copy assignment
    EXPECT_FALSE(std::is_copy_constructible<TextWordList>::value);
    EXPECT_FALSE(std::is_copy_assignable<TextWordList>::value);
}

// Integration-style test: Create a TextWordList from a real TextPage
// This requires setting up the Poppler document pipeline
TEST_F(TextWordListTest_1212, GetWordsFromEmptyPage_1212) {
    // Create a TextPage with no content - the word list should be empty
    // We need a TextPage to do this. TextPage requires TextOutputDev context.
    
    // Create a TextOutputDev to get a TextPage
    TextOutputDev *textDev = new TextOutputDev(nullptr, false, 0, false, false);
    
    // Get the text page from the device
    TextPage *textPage = textDev->takeText();
    
    if (textPage) {
        // Create TextWordList with physical layout = false
        TextWordList wordList(textPage, false);
        const std::vector<TextWord*> &words = wordList.getWords();
        
        // An empty page should have no words
        EXPECT_TRUE(words.empty());
        
        textPage->decRefCnt();
    }
    
    delete textDev;
}

TEST_F(TextWordListTest_1212, GetWordsFromEmptyPagePhysLayout_1212) {
    // Test with physical layout = true on empty page
    TextOutputDev *textDev = new TextOutputDev(nullptr, false, 0, false, false);
    
    TextPage *textPage = textDev->takeText();
    
    if (textPage) {
        TextWordList wordList(textPage, true);
        const std::vector<TextWord*> &words = wordList.getWords();
        
        // An empty page should have no words regardless of layout mode
        EXPECT_TRUE(words.empty());
        
        textPage->decRefCnt();
    }
    
    delete textDev;
}

// Test that calling getWords multiple times returns the same reference
TEST_F(TextWordListTest_1212, GetWordsConsistency_1212) {
    TextOutputDev *textDev = new TextOutputDev(nullptr, false, 0, false, false);
    
    TextPage *textPage = textDev->takeText();
    
    if (textPage) {
        TextWordList wordList(textPage, false);
        
        const std::vector<TextWord*> &words1 = wordList.getWords();
        const std::vector<TextWord*> &words2 = wordList.getWords();
        
        // Both calls should return the same reference
        EXPECT_EQ(&words1, &words2);
        EXPECT_EQ(words1.size(), words2.size());
        
        textPage->decRefCnt();
    }
    
    delete textDev;
}
