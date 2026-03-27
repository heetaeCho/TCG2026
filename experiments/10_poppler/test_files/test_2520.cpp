#include <gtest/gtest.h>

#include "TestProjects/poppler/glib/poppler-structure-element.cc"

#include "TestProjects/poppler/poppler/Object.h"



using namespace std;



// Mock EnumType for testing purposes

enum class TestEnum {

    Value1,

    Value2,

    Invalid

};



// Mock EnumNameValue struct for testing purposes

template<>

struct EnumNameValue<TestEnum> {

    const char* name;

    TestEnum value;

};



const EnumNameValue<TestEnum> EnumNameValue<TestEnum>::values[] = {

    {"Value1", TestEnum::Value1},

    {"Value2", TestEnum::Value2},

    {nullptr, TestEnum::Invalid} // Sentinel value

};



class NameToEnumTest : public ::testing::Test {

protected:

    Object validObjectName;

    Object invalidObjectName;



    NameToEnumTest() 

        : validObjectName(Object("Value1")),

          invalidObjectName(Object("InvalidValue")) {}

};



TEST_F(NameToEnumTest, ValidNameReturnsCorrectEnum_2520) {

    EXPECT_EQ(name_to_enum<TestEnum>(&validObjectName), TestEnum::Value1);

}



TEST_F(NameToEnumTest, InvalidNameAssertsNotReached_2520) {

    EXPECT_DEATH(name_to_enum<TestEnum>(&invalidObjectName), ".*");

}



TEST_F(NameToEnumTest, NullObjectPointerThrowsAssertion_2520) {

    Object* nullObject = nullptr;

    EXPECT_DEATH(name_to_enum<TestEnum>(nullObject), ".*");

}
