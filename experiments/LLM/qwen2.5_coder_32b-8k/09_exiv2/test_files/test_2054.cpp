#include <gtest/gtest.h>

#include <string>



// Assuming UTF8Unit and UTF16Unit are defined as char types for simplicity

typedef char UTF8Unit;

typedef char UTF16Unit;



extern void ToUTF16(const UTF8Unit* utf8In, size_t utf8Len, std::string* utf16Str, bool bigEndian);



TEST(ToUTF16Test_2054, NormalOperation_LittleEndian_2054) {

    const UTF8Unit utf8Input[] = "Hello";

    std::string utf16Output;

    ToUTF16(utf8Input, sizeof(utf8Input) - 1, &utf16Output, false);

    EXPECT_EQ(utf16Output.size(), 10); // Each character is 2 bytes in UTF-16

}



TEST(ToUTF16Test_2054, NormalOperation_BigEndian_2054) {

    const UTF8Unit utf8Input[] = "Hello";

    std::string utf16Output;

    ToUTF16(utf8Input, sizeof(utf8Input) - 1, &utf16Output, true);

    EXPECT_EQ(utf16Output.size(), 10); // Each character is 2 bytes in UTF-16

}



TEST(ToUTF16Test_2054, EmptyString_2054) {

    const UTF8Unit utf8Input[] = "";

    std::string utf16Output;

    ToUTF16(utf8Input, sizeof(utf8Input) - 1, &utf16Output, false);

    EXPECT_EQ(utf16Output.empty(), true);

}



TEST(ToUTF16Test_2054, SingleCharacter_2054) {

    const UTF8Unit utf8Input[] = "A";

    std::string utf16Output;

    ToUTF16(utf8Input, sizeof(utf8Input) - 1, &utf16Output, false);

    EXPECT_EQ(utf16Output.size(), 2); // Single character is 2 bytes in UTF-16

}



TEST(ToUTF16Test_2054, MultiByteCharacter_LittleEndian_2054) {

    const UTF8Unit utf8Input[] = "\xE2\x9C\x85"; // Check mark (✓)

    std::string utf16Output;

    ToUTF16(utf8Input, sizeof(utf8Input) - 1, &utf16Output, false);

    EXPECT_EQ(utf16Output.size(), 2); // Single multi-byte character is 2 bytes in UTF-16

}



TEST(ToUTF16Test_2054, MultiByteCharacter_BigEndian_2054) {

    const UTF8Unit utf8Input[] = "\xE2\x9C\x85"; // Check mark (✓)

    std::string utf16Output;

    ToUTF16(utf8Input, sizeof(utf8Input) - 1, &utf16Output, true);

    EXPECT_EQ(utf16Output.size(), 2); // Single multi-byte character is 2 bytes in UTF-16

}



TEST(ToUTF16Test_2054, IncompleteUnicode_LittleEndian_2054) {

    const UTF8Unit utf8Input[] = "\xC3"; // Incomplete UTF-8 sequence

    std::string utf16Output;

    EXPECT_THROW({

        ToUTF16(utf8Input, sizeof(utf8Input) - 1, &utf16Output, false);

    }, XMP_Error);

}



TEST(ToUTF16Test_2054, IncompleteUnicode_BigEndian_2054) {

    const UTF8Unit utf8Input[] = "\xC3"; // Incomplete UTF-8 sequence

    std::string utf16Output;

    EXPECT_THROW({

        ToUTF16(utf8Input, sizeof(utf8Input) - 1, &utf16Output, true);

    }, XMP_Error);

}



TEST(ToUTF16Test_2054, LargeInput_LittleEndian_2054) {

    std::string largeUtf8Input(10000, 'A'); // Large input

    std::string utf16Output;

    ToUTF16(reinterpret_cast<const UTF8Unit*>(largeUtf8Input.c_str()), largeUtf8Input.size(), &utf16Output, false);

    EXPECT_EQ(utf16Output.size(), 20000); // Each character is 2 bytes in UTF-16

}



TEST(ToUTF16Test_2054, LargeInput_BigEndian_2054) {

    std::string largeUtf8Input(10000, 'A'); // Large input

    std::string utf16Output;

    ToUTF16(reinterpret_cast<const UTF8Unit*>(largeUtf8Input.c_str()), largeUtf8Input.size(), &utf16Output, true);

    EXPECT_EQ(utf16Output.size(), 20000); // Each character is 2 bytes in UTF-16

}
