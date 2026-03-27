#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/poppler/qt5/src/poppler-private.cc"

#include "./TestProjects/poppler/goo/GooString.h"

#include "./TestProjects/poppler/poppler/UnicodeMap.h"



using namespace Poppler;

using ::testing::_;

using ::testing::Return;



// Mock UnicodeMap class

class MockUnicodeMap : public UnicodeMap {

public:

    MOCK_METHOD(int, mapUnicode, (Unicode u, char *buf, int bufSize), (override));

};



TEST(UnicodeToQStringTest_1282, NormalOperation_1282) {

    Unicode u[] = {0x41, 0x65, 0x9A}; // "Aež" in UTF-8

    char buf[8];

    MockUnicodeMap mockUtf8Map;

    EXPECT_CALL(mockUtf8Map, mapUnicode(u[0], _, sizeof(buf))).WillOnce(Return(1));

    EXPECT_CALL(mockUtf8Map, mapUnicode(u[1], _, sizeof(buf))).WillOnce(Return(1));

    EXPECT_CALL(mockUtf8Map, mapUnicode(u[2], _, sizeof(buf))).WillOnce(Return(2));



    globalParams->getUtf8Map = [&mockUtf8Map]() { return &mockUtf8Map; };



    QString result = unicodeToQString(u, 3);

    EXPECT_EQ(result.toStdString(), "Aež");

}



TEST(UnicodeToQStringTest_1282, EmptyString_1282) {

    Unicode u[] = {};

    MockUnicodeMap mockUtf8Map;

    globalParams->getUtf8Map = [&mockUtf8Map]() { return &mockUtf8Map; };



    QString result = unicodeToQString(u, 0);

    EXPECT_EQ(result.toStdString(), "");

}



TEST(UnicodeToQStringTest_1282, TrailingNulls_1282) {

    Unicode u[] = {0x41, 0x65, 0x9A, 0x00}; // "Aež" with a trailing null

    char buf[8];

    MockUnicodeMap mockUtf8Map;

    EXPECT_CALL(mockUtf8Map, mapUnicode(u[0], _, sizeof(buf))).WillOnce(Return(1));

    EXPECT_CALL(mockUtf8Map, mapUnicode(u[1], _, sizeof(buf))).WillOnce(Return(1));

    EXPECT_CALL(mockUtf8Map, mapUnicode(u[2], _, sizeof(buf))).WillOnce(Return(2));



    globalParams->getUtf8Map = [&mockUtf8Map]() { return &mockUtf8Map; };



    QString result = unicodeToQString(u, 4);

    EXPECT_EQ(result.toStdString(), "Aež");

}



TEST(UnicodeToQStringTest_1282, AllNulls_1282) {

    Unicode u[] = {0x00, 0x00, 0x00};

    MockUnicodeMap mockUtf8Map;

    globalParams->getUtf8Map = [&mockUtf8Map]() { return &mockUtf8Map; };



    QString result = unicodeToQString(u, 3);

    EXPECT_EQ(result.toStdString(), "");

}
