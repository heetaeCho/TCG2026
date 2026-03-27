#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/poppler/TextOutputDev.cc"

#include "TestProjects/poppler/goo/GooString.h"

#include "TestProjects/poppler/poppler/UnicodeMap.h"



using namespace testing;



class UnicodeMapMock : public UnicodeMap {

public:

    MOCK_METHOD3(mapUnicode, int(Unicode u, char *buf, int bufSize));

};



TEST(reorderTextTest_1903, NormalOperation_LTR_1903) {

    Unicode text[] = {0x0041, 0x05D0, 0x0042}; // A, א, B

    GooString s;

    Unicode u[3];

    UnicodeMapMock uMap;



    EXPECT_CALL(uMap, mapUnicode(0x202a, _, _)).WillOnce(Return(1));

    EXPECT_CALL(uMap, mapUnicode(0x202b, _, _)).WillOnce(Return(1));

    EXPECT_CALL(uMap, mapUnicode(0x202c, _, _)).Times(2).WillRepeatedly(Return(1));



    int result = reorderText(text, 3, &uMap, true, &s, u);



    ASSERT_EQ(result, 3);

    ASSERT_STREQ(s.toStr().c_str(), "\x01\x41\x01\x05\xd0\x01\x42");

    EXPECT_EQ(u[0], 0x0041);

    EXPECT_EQ(u[1], 0x05D0);

    EXPECT_EQ(u[2], 0x0042);

}



TEST(reorderTextTest_1903, NormalOperation_RTL_1903) {

    Unicode text[] = {0x0041, 0x05D0, 0x0042}; // A, א, B

    GooString s;

    Unicode u[3];

    UnicodeMapMock uMap;



    EXPECT_CALL(uMap, mapUnicode(0x202a, _, _)).WillOnce(Return(1));

    EXPECT_CALL(uMap, mapUnicode(0x202b, _, _)).WillOnce(Return(1));

    EXPECT_CALL(uMap, mapUnicode(0x202c, _, _)).Times(2).WillRepeatedly(Return(1));



    int result = reorderText(text, 3, &uMap, false, &s, u);



    ASSERT_EQ(result, 3);

    ASSERT_STREQ(s.toStr().c_str(), "\x01\x42\x01\x05\xd0\x01\x41");

    EXPECT_EQ(u[0], 0x0042);

    EXPECT_EQ(u[1], 0x05D0);

    EXPECT_EQ(u[2], 0x0041);

}



TEST(reorderTextTest_1903, BoundaryCondition_EmptyInput_1903) {

    Unicode text[] = {};

    GooString s;

    Unicode u[0];

    UnicodeMapMock uMap;



    int result = reorderText(text, 0, &uMap, true, &s, nullptr);



    ASSERT_EQ(result, 0);

    ASSERT_STREQ(s.toStr().c_str(), "");

}



TEST(reorderTextTest_1903, BoundaryCondition_SingleLTR_1903) {

    Unicode text[] = {0x0041}; // A

    GooString s;

    Unicode u[1];

    UnicodeMapMock uMap;



    EXPECT_CALL(uMap, mapUnicode(0x202a, _, _)).WillOnce(Return(1));

    EXPECT_CALL(uMap, mapUnicode(0x202b, _, _)).Times(0);

    EXPECT_CALL(uMap, mapUnicode(0x202c, _, _)).Times(0);



    int result = reorderText(text, 1, &uMap, true, &s, u);



    ASSERT_EQ(result, 1);

    ASSERT_STREQ(s.toStr().c_str(), "\x01\x41");

    EXPECT_EQ(u[0], 0x0041);

}



TEST(reorderTextTest_1903, BoundaryCondition_SingleRTL_1903) {

    Unicode text[] = {0x05D0}; // א

    GooString s;

    Unicode u[1];

    UnicodeMapMock uMap;



    EXPECT_CALL(uMap, mapUnicode(0x202a, _, _)).WillOnce(Return(1));

    EXPECT_CALL(uMap, mapUnicode(0x202b, _, _)).WillOnce(Return(1));

    EXPECT_CALL(uMap, mapUnicode(0x202c, _, _)).Times(1).WillRepeatedly(Return(1));



    int result = reorderText(text, 1, &uMap, true, &s, u);



    ASSERT_EQ(result, 1);

    ASSERT_STREQ(s.toStr().c_str(), "\x01\x05\xd0");

    EXPECT_EQ(u[0], 0x05D0);

}



TEST(reorderTextTest_1903, ExceptionalCase_MapUnicodeFailure_1903) {

    Unicode text[] = {0x0041, 0x05D0}; // A, א

    GooString s;

    Unicode u[2];

    UnicodeMapMock uMap;



    EXPECT_CALL(uMap, mapUnicode(0x202a, _, _)).WillOnce(Return(-1));



    int result = reorderText(text, 2, &uMap, true, &s, u);



    ASSERT_EQ(result, 0);

    ASSERT_STREQ(s.toStr().c_str(), "");

}



TEST(reorderTextTest_1903, ExternalInteraction_MapUnicodeCalls_1903) {

    Unicode text[] = {0x0041, 0x05D0}; // A, א

    GooString s;

    Unicode u[2];

    UnicodeMapMock uMap;



    EXPECT_CALL(uMap, mapUnicode(0x202a, _, _)).WillOnce(Return(1));

    EXPECT_CALL(uMap, mapUnicode(0x202b, _, _)).WillOnce(Return(1));

    EXPECT_CALL(uMap, mapUnicode(0x202c, _, _)).Times(2).WillRepeatedly(Return(1));



    int result = reorderText(text, 2, &uMap, true, &s, u);



    ASSERT_EQ(result, 2);

}
