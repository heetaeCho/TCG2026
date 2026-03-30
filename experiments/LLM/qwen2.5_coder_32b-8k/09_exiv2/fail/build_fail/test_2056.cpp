#include <gtest/gtest.h>

#include <string>



// Assuming UTF8Unit and UTF32Unit are defined somewhere in UnicodeConversions.hpp

typedef unsigned char UTF8Unit;

typedef unsigned int UTF32Unit;



extern void ToUTF32(const UTF8Unit* utf8In, size_t utf8Len, std::string* utf32Str, bool bigEndian);



TEST(ToUTF32Test_2056, NormalOperationASCII_2056) {

    const UTF8Unit utf8In[] = "HelloWorld";

    size_t utf8Len = sizeof(utf8In) - 1;

    std::string utf32Str;

    ToUTF32(utf8In, utf8Len, &utf32Str, false);

    EXPECT_EQ(utf32Str.size(), utf8Len * 4); // Each ASCII character is represented by 4 bytes in UTF-32

}



TEST(ToUTF32Test_2056, NormalOperationUnicode_2056) {

    const UTF8Unit utf8In[] = "\xE2\x9C\x93"; // Check mark character (U+2713)

    size_t utf8Len = sizeof(utf8In) - 1;

    std::string utf32Str;

    ToUTF32(utf8In, utf8Len, &utf32Str, false);

    EXPECT_EQ(utf32Str.size(), 4); // One Unicode character is represented by 4 bytes in UTF-32

}



TEST(ToUTF32Test_2056, BoundaryConditionEmptyString_2056) {

    const UTF8Unit utf8In[] = "";

    size_t utf8Len = sizeof(utf8In) - 1;

    std::string utf32Str;

    ToUTF32(utf8In, utf8Len, &utf32Str, false);

    EXPECT_EQ(utf32Str.size(), 0); // Empty input should result in an empty output

}



TEST(ToUTF32Test_2056, BoundaryConditionSingleByteASCII_2056) {

    const UTF8Unit utf8In[] = "A";

    size_t utf8Len = sizeof(utf8In) - 1;

    std::string utf32Str;

    ToUTF32(utf8In, utf8Len, &utf32Str, false);

    EXPECT_EQ(utf32Str.size(), 4); // Single ASCII character is represented by 4 bytes in UTF-32

}



TEST(ToUTF32Test_2056, BoundaryConditionSingleByteUnicode_2056) {

    const UTF8Unit utf8In[] = "\xC2\xA9"; // Copyright symbol (U+00A9)

    size_t utf8Len = sizeof(utf8In) - 1;

    std::string utf32Str;

    ToUTF32(utf8In, utf8Len, &utf32Str, false);

    EXPECT_EQ(utf32Str.size(), 4); // Single Unicode character is represented by 4 bytes in UTF-32

}



TEST(ToUTF32Test_2056, ExceptionalConditionIncompleteUnicode_2056) {

    const UTF8Unit utf8In[] = "\xE2\x9C"; // Incomplete check mark character (U+2713)

    size_t utf8Len = sizeof(utf8In) - 1;

    std::string utf32Str;

    EXPECT_THROW(ToUTF32(utf8In, utf8Len, &utf32Str, false), XMP_Error);

}



TEST(ToUTF32Test_2056, BigEndianConversion_2056) {

    const UTF8Unit utf8In[] = "HelloWorld";

    size_t utf8Len = sizeof(utf8In) - 1;

    std::string utf32StrBE;

    ToUTF32(utf8In, utf8Len, &utf32StrBE, true);

    EXPECT_EQ(utf32StrBE.size(), utf8Len * 4); // Each ASCII character is represented by 4 bytes in UTF-32



    std::string utf32StrLE;

    ToUTF32(utf8In, utf8Len, &utf32StrLE, false);

    EXPECT_EQ(utf32StrBE, utf32StrLE); // The content should be the same for comparison, but byte order is different

}



TEST(ToUTF32Test_2056, LargeInput_2056) {

    const std::string largeInput(1024 * 1024, 'A'); // 1MB of ASCII characters

    std::string utf32Str;

    ToUTF32(reinterpret_cast<const UTF8Unit*>(largeInput.c_str()), largeInput.size(), &utf32Str, false);

    EXPECT_EQ(utf32Str.size(), largeInput.size() * 4); // Each ASCII character is represented by 4 bytes in UTF-32

}
