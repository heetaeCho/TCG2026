#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <string>

#include "Catalog.h"  // Assuming Catalog.h contains the declaration of EntryGooStringComparer and GooString



using ::testing::_;

using ::testing::Return;



// Mock class for GooString if needed, but in this case, we assume GooString is a simple wrapper around std::string

class MockGooString {

public:

    MOCK_CONST_METHOD0(toStr, const std::string&());

};



TEST(EntryGooStringComparerTest_1898, CompareDifferentStrings_1898) {

    MockGooString mockString1;

    MockGooString mockString2;



    EXPECT_CALL(mockString1, toStr()).WillRepeatedly(Return("apple"));

    EXPECT_CALL(mockString2, toStr()).WillRepeatedly(Return("banana"));



    EntryGooStringComparer comparer;

    EXPECT_TRUE(comparer(&mockString1, &mockString2));

}



TEST(EntryGooStringComparerTest_1898, CompareEqualStrings_1898) {

    MockGooString mockString1;

    MockGooString mockString2;



    EXPECT_CALL(mockString1, toStr()).WillRepeatedly(Return("apple"));

    EXPECT_CALL(mockString2, toStr()).WillRepeatedly(Return("apple"));



    EntryGooStringComparer comparer;

    EXPECT_FALSE(comparer(&mockString1, &mockString2));

}



TEST(EntryGooStringComparerTest_1898, CompareWithEmptyString_1898) {

    MockGooString mockString1;

    MockGooString mockString2;



    EXPECT_CALL(mockString1, toStr()).WillRepeatedly(Return(""));

    EXPECT_CALL(mockString2, toStr()).WillRepeatedly(Return("banana"));



    EntryGooStringComparer comparer;

    EXPECT_TRUE(comparer(&mockString1, &mockString2));

}



TEST(EntryGooStringComparerTest_1898, CompareLongStrings_1898) {

    MockGooString mockString1;

    MockGooString mockString2;



    std::string longStr1 = "a" + std::string(1000, 'b');

    std::string longStr2 = "c" + std::string(1000, 'd');



    EXPECT_CALL(mockString1, toStr()).WillRepeatedly(Return(longStr1));

    EXPECT_CALL(mockString2, toStr()).WillRepeatedly(Return(longStr2));



    EntryGooStringComparer comparer;

    EXPECT_TRUE(comparer(&mockString1, &mockString2));

}



TEST(EntryGooStringComparerTest_1898, CompareNullStrings_1898) {

    GooString* nullString1 = nullptr;

    GooString* nullString2 = nullptr;



    EntryGooStringComparer comparer;

    EXPECT_FALSE(comparer(nullString1, nullString2));

}
