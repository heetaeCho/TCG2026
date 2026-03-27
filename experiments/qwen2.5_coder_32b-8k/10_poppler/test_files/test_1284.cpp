#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <QString>

#include <memory>

#include "poppler-private.cc"



using namespace Poppler;



class QStringToUnicodeGooStringTest : public ::testing::Test {

protected:

    std::unique_ptr<GooString> result;

};



TEST_F(QStringToUnicodeGooStringTest, EmptyString_ReturnsEmptyGooString_1284) {

    QString input = "";

    result = QStringToUnicodeGooString(input);

    EXPECT_EQ(result->getLength(), 0);

}



TEST_F(QStringToUnicodeGooStringTest, SingleCharacter_ReturnsCorrectGooString_1284) {

    QString input = "A";

    result = QStringToUnicodeGooString(input);

    const char expected[] = {0xfe, 0xff, 0x00, 0x41};

    EXPECT_EQ(memcmp(result->getCString(), expected, sizeof(expected)), 0);

}



TEST_F(QStringToUnicodeGooStringTest, MultipleCharacters_ReturnsCorrectGooString_1284) {

    QString input = "Hello";

    result = QStringToUnicodeGooString(input);

    const char expected[] = {0xfe, 0xff, 0x00, 0x48, 0x00, 0x65, 0x00, 0x6c, 0x00, 0x6c, 0x00, 0x6f};

    EXPECT_EQ(memcmp(result->getCString(), expected, sizeof(expected)), 0);

}



TEST_F(QStringToUnicodeGooStringTest, NonAsciiCharacters_ReturnsCorrectGooString_1284) {

    QString input = "Привет";

    result = QStringToUnicodeGooString(input);

    const char expected[] = {0xfe, 0xff, 0x04, 0x1f, 0x04, 0x38, 0x04, 0x32, 0x04, 0x32, 0x04, 0x35, 0x04, 0x42};

    EXPECT_EQ(memcmp(result->getCString(), expected, sizeof(expected)), 0);

}



TEST_F(QStringToUnicodeGooStringTest, LargeString_ReturnsCorrectGooString_1284) {

    QString input = "A very large string that should be properly converted to GooString";

    result = QStringToUnicodeGooString(input);

    EXPECT_EQ(result->getLength(), (input.length() * 2 + 2));

}
