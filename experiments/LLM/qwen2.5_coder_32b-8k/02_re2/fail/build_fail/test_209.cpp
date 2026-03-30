#include <gtest/gtest.h>

#include "TestProjects/re2/util/rune.h"



namespace re2 {



class UtfruneTest_209 : public ::testing::Test {

protected:

    // No additional setup required for this function.

};



TEST_F(UtfruneTest_209, NormalOperationSingleByte_209) {

    const char* str = "hello";

    Rune c = 'l';

    EXPECT_EQ(utfrune(str, c), str + 2);

}



TEST_F(UtfruneTest_209, NormalOperationMultiByte_209) {

    const char* str = "\xC3\xA1\xC3\xB1o"; // "áño" in UTF-8

    Rune c = 0xF1; // 'ñ'

    EXPECT_EQ(utfrune(str, c), str + 2);

}



TEST_F(UtfruneTest_209, NotFoundSingleByte_209) {

    const char* str = "hello";

    Rune c = 'z';

    EXPECT_EQ(utfrune(str, c), nullptr);

}



TEST_F(UtfruneTest_209, NotFoundMultiByte_209) {

    const char* str = "\xC3\xA1\xC3\xB1o"; // "áño" in UTF-8

    Rune c = 0xF1; // 'ñ'

    str += 3;

    EXPECT_EQ(utfrune(str, c), nullptr);

}



TEST_F(UtfruneTest_209, EmptyString_209) {

    const char* str = "";

    Rune c = 'a';

    EXPECT_EQ(utfrune(str, c), nullptr);

}



TEST_F(UtfruneTest_209, NullString_209) {

    const char* str = nullptr;

    Rune c = 'a';

    EXPECT_EQ(utfrune(str, c), nullptr);

}



TEST_F(UtfruneTest_209, BoundaryConditionSingleByteStart_209) {

    const char* str = "hello";

    Rune c = 'h';

    EXPECT_EQ(utfrune(str, c), str);

}



TEST_F(UtfruneTest_209, BoundaryConditionSingleByteEnd_209) {

    const char* str = "hello";

    Rune c = 'o';

    EXPECT_EQ(utfrune(str, c), str + 4);

}



TEST_F(UtfruneTest_209, BoundaryConditionMultiByteStart_209) {

    const char* str = "\xC3\xA1\xC3\xB1o"; // "áño" in UTF-8

    Rune c = 0xE1; // 'á'

    EXPECT_EQ(utfrune(str, c), str);

}



TEST_F(UtfruneTest_209, BoundaryConditionMultiByteEnd_209) {

    const char* str = "\xC3\xA1\xC3\xB1o"; // "áño" in UTF-8

    Rune c = 0xF1; // 'ñ'

    EXPECT_EQ(utfrune(str, c), str + 2);

}



} // namespace re2
