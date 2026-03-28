#include <gtest/gtest.h>



// Assuming Unicode is defined as an appropriate type, e.g., uint16_t or uint32_t

typedef uint32_t Unicode;



extern "C" {

    int mapUTF16(Unicode u, char *buf, int bufSize);

}



class MapUTF16Test : public ::testing::Test {

protected:

    char buffer[4];

};



TEST_F(MapUTF16Test_1648, BasicASCII_1648) {

    Unicode u = 0x0020; // Space character

    int result = mapUTF16(u, buffer, sizeof(buffer));

    EXPECT_EQ(result, 2);

    EXPECT_EQ(buffer[0], 0x00);

    EXPECT_EQ(buffer[1], 0x20);

}



TEST_F(MapUTF16Test_1648, BasicLatin_1648) {

    Unicode u = 0x00A9; // Copyright symbol

    int result = mapUTF16(u, buffer, sizeof(buffer));

    EXPECT_EQ(result, 2);

    EXPECT_EQ(buffer[0], 0x00);

    EXPECT_EQ(buffer[1], 0xA9);

}



TEST_F(MapUTF16Test_1648, BasicMultilingualPlane_1648) {

    Unicode u = 0x20AC; // Euro sign

    int result = mapUTF16(u, buffer, sizeof(buffer));

    EXPECT_EQ(result, 2);

    EXPECT_EQ(buffer[0], 0x20);

    EXPECT_EQ(buffer[1], 0xAC);

}



TEST_F(MapUTF16Test_1648, SupplementaryPlane_1648) {

    Unicode u = 0x1F600; // Grinning Face emoji

    int result = mapUTF16(u, buffer, sizeof(buffer));

    EXPECT_EQ(result, 4);

    EXPECT_EQ(buffer[0], 0xD8);

    EXPECT_EQ(buffer[1], 0x3D);

    EXPECT_EQ(buffer[2], 0xDE);

    EXPECT_EQ(buffer[3], 0x00);

}



TEST_F(MapUTF16Test_1648, BufferSizeTwo_SupplementaryPlane_1648) {

    Unicode u = 0x1F600; // Grinning Face emoji

    int result = mapUTF16(u, buffer, 2);

    EXPECT_EQ(result, 0);

}



TEST_F(MapUTF16Test_1648, BufferSizeFour_Normal_1648) {

    Unicode u = 0x00A9; // Copyright symbol

    int result = mapUTF16(u, buffer, 4);

    EXPECT_EQ(result, 2);

    EXPECT_EQ(buffer[0], 0x00);

    EXPECT_EQ(buffer[1], 0xA9);

}



TEST_F(MapUTF16Test_1648, BufferSizeOne_Normal_1648) {

    Unicode u = 0x00A9; // Copyright symbol

    int result = mapUTF16(u, buffer, 1);

    EXPECT_EQ(result, 0);

}



TEST_F(MapUTF16Test_1648, InvalidUnicode_1648) {

    Unicode u = 0x110000; // Out of range

    int result = mapUTF16(u, buffer, sizeof(buffer));

    EXPECT_EQ(result, 0);

}
