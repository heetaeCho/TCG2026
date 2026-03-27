#include <gtest/gtest.h>

#include "XMP_Const.h"

#include "UnicodeConversions.cpp" // Assuming the function is defined in this file for testing



class UnicodeConversionsTest : public ::testing::Test {

protected:

    std::string result;

};



TEST_F(UnicodeConversionsTest, PutIncreasesCount_2055) {

    const UTF8Unit utf8In[] = {'H', 'e', 'l', 'l', 'o'};

    size_t utf8Len = sizeof(utf8In) / sizeof(utf8In[0]);

    ToUTF16Native(utf8In, utf8Len, &result);

    EXPECT_EQ(result.size(), 10); // 5 characters * 2 bytes per UTF-16 character

}



TEST_F(UnicodeConversionsTest, EmptyString_2055) {

    const UTF8Unit utf8In[] = {};

    size_t utf8Len = sizeof(utf8In) / sizeof(utf8In[0]);

    ToUTF16Native(utf8In, utf8Len, &result);

    EXPECT_EQ(result.size(), 0); // Empty input should result in empty output

}



TEST_F(UnicodeConversionsTest, SingleCharacter_2055) {

    const UTF8Unit utf8In[] = {'A'};

    size_t utf8Len = sizeof(utf8In) / sizeof(utf8In[0]);

    ToUTF16Native(utf8In, utf8Len, &result);

    EXPECT_EQ(result.size(), 2); // Single character * 2 bytes per UTF-16 character

}



TEST_F(UnicodeConversionsTest, MultibyteCharacter_2055) {

    const UTF8Unit utf8In[] = {0xE2, 0x9C, 0x85}; // Check mark (✓)

    size_t utf8Len = sizeof(utf8In) / sizeof(utf8In[0]);

    ToUTF16Native(utf8In, utf8Len, &result);

    EXPECT_EQ(result.size(), 2); // Multibyte UTF-8 character should be converted to a single UTF-16 character

}



TEST_F(UnicodeConversionsTest, IncompleteUnicodeAtEnd_2055) {

    const UTF8Unit utf8In[] = {0xE2, 0x9C}; // Incomplete check mark (✓)

    size_t utf8Len = sizeof(utf8In) / sizeof(utf8In[0]);

    EXPECT_THROW(ToUTF16Native(utf8In, utf8Len, &result), XMP_Error);

}



TEST_F(UnicodeConversionsTest, LargeInput_2055) {

    const size_t largeSize = 4096; // Larger than the internal buffer to test loop behavior

    std::vector<UTF8Unit> utf8In(largeSize, 'A');

    size_t utf8Len = utf8In.size();

    ToUTF16Native(utf8In.data(), utf8Len, &result);

    EXPECT_EQ(result.size(), 2 * largeSize); // Each character should be converted to 2 bytes

}
