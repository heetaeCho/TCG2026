#include <gtest/gtest.h>

#include "TestProjects/poppler/goo/GooString.h"

#include "TestProjects/poppler/poppler/PDFDoc.cc"



TEST(get_id_1856, ValidInput_ReturnsTrueAndCorrectId_1856) {

    GooString encodedidstring("0123456789abcdef");

    GooString id;

    bool result = get_id(&encodedidstring, &id);

    EXPECT_TRUE(result);

    EXPECT_EQ(id.toStr(), "000102030405060708090a0b0c0d0e0f");

}



TEST(get_id_1856, InvalidLength_ReturnsFalse_1856) {

    GooString encodedidstring("0123456789abcde"); // Length is 15, expected 16

    GooString id;

    bool result = get_id(&encodedidstring, &id);

    EXPECT_FALSE(result);

}



TEST(get_id_1856, EmptyInput_ReturnsFalse_1856) {

    GooString encodedidstring("");

    GooString id;

    bool result = get_id(&encodedidstring, &id);

    EXPECT_FALSE(result);

}



TEST(get_id_1856, NullInput_ReturnsFalse_1856) {

    GooString *encodedidstring = nullptr;

    GooString id;

    bool result = get_id(encodedidstring, &id);

    EXPECT_FALSE(result);

}



TEST(get_id_1856, LargeInput_ReturnsFalse_1856) {

    GooString encodedidstring("0123456789abcdef0"); // Length is 17, expected 16

    GooString id;

    bool result = get_id(&encodedidstring, &id);

    EXPECT_FALSE(result);

}



TEST(get_id_1856, ValidInputWithNonHexCharacters_ReturnsFalse_1856) {

    GooString encodedidstring("0123456789abcdefg"); // 'g' is not a hex character

    GooString id;

    bool result = get_id(&encodedidstring, &id);

    EXPECT_FALSE(result);

}
