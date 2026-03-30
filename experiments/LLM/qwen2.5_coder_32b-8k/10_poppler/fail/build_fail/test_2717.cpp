#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <poppler/utils/pdftohtml.cc>

#include <poppler/poppler/Object.h>

#include <poppler/poppler/Dict.h>

#include <optional>



using namespace ::testing;



// Mock class for Dict to simulate lookup behavior

class MockDict : public Dict {

public:

    MOCK_METHOD(Object, lookup, (const char *key), (override));

};



TEST(getInfoDateTest_2717, NormalOperation_2717) {

    MockDict mockDict;

    Object mockObject(std::unique_ptr<GooString>(new GooString("2023-10-05T14:48:00+00:00")));

    EXPECT_CALL(mockDict, lookup(Eq("CreationDate"))).WillOnce(ReturnRef(mockObject));



    auto result = getInfoDate(&mockDict, "CreationDate");

    ASSERT_TRUE(result.has_value());

    EXPECT_EQ(*result, "2023-10-05T14:48:00+00:00");

}



TEST(getInfoDateTest_2717, BoundaryConditions_EmptyString_2717) {

    MockDict mockDict;

    Object mockObject(std::unique_ptr<GooString>(new GooString("")));

    EXPECT_CALL(mockDict, lookup(Eq("CreationDate"))).WillOnce(ReturnRef(mockObject));



    auto result = getInfoDate(&mockDict, "CreationDate");

    ASSERT_TRUE(result.has_value());

    EXPECT_EQ(*result, "");

}



TEST(getInfoDateTest_2717, BoundaryConditions_NullString_2717) {

    MockDict mockDict;

    Object mockObject(std::unique_ptr<GooString>(nullptr));

    EXPECT_CALL(mockDict, lookup(Eq("CreationDate"))).WillOnce(ReturnRef(mockObject));



    auto result = getInfoDate(&mockDict, "CreationDate");

    ASSERT_FALSE(result.has_value());

}



TEST(getInfoDateTest_2717, ExceptionalCase_NonDateString_2717) {

    MockDict mockDict;

    Object mockObject(std::unique_ptr<GooString>(new GooString("NotADate")));

    EXPECT_CALL(mockDict, lookup(Eq("CreationDate"))).WillOnce(ReturnRef(mockObject));



    auto result = getInfoDate(&mockDict, "CreationDate");

    ASSERT_TRUE(result.has_value());

    EXPECT_EQ(*result, "NotADate");

}



TEST(getInfoDateTest_2717, ExceptionalCase_NotAString_2717) {

    MockDict mockDict;

    Object mockObject(42); // Int object instead of string

    EXPECT_CALL(mockDict, lookup(Eq("CreationDate"))).WillOnce(ReturnRef(mockObject));



    auto result = getInfoDate(&mockDict, "CreationDate");

    ASSERT_FALSE(result.has_value());

}



TEST(getInfoDateTest_2717, ExceptionalCase_EmptyKey_2717) {

    MockDict mockDict;

    Object mockObject(std::unique_ptr<GooString>(new GooString("2023-10-05T14:48:00+00:00")));

    EXPECT_CALL(mockDict, lookup(Eq(""))).WillOnce(ReturnRef(mockObject));



    auto result = getInfoDate(&mockDict, "");

    ASSERT_TRUE(result.has_value());

    EXPECT_EQ(*result, "2023-10-05T14:48:00+00:00");

}



TEST(getInfoDateTest_2717, ExceptionalCase_KeyNotFound_2717) {

    MockDict mockDict;

    Object mockObject = Object::null();

    EXPECT_CALL(mockDict, lookup(Eq("CreationDate"))).WillOnce(ReturnRef(mockObject));



    auto result = getInfoDate(&mockDict, "CreationDate");

    ASSERT_FALSE(result.has_value());

}
