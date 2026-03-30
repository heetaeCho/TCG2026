#include <gtest/gtest.h>

#include "exiv2/value.hpp"



using namespace Exiv2;



class StringValueBaseTest_810 : public ::testing::Test {

protected:

    TypeId typeId = 0; // Assuming a valid TypeId for StringValueBase, replace with actual if needed.

    std::string testString = "testString";

    StringValueBase* stringValueBase;



    void SetUp() override {

        stringValueBase = new StringValueBase(typeId, testString);

    }



    void TearDown() override {

        delete stringValueBase;

    }

};



TEST_F(StringValueBaseTest_810, toUint32_NormalOperation_810) {

    uint32_t result = stringValueBase->toUint32(0);

    EXPECT_TRUE(stringValueBase->ok());

    // Assuming the first character's ASCII value is returned

    EXPECT_EQ(result, static_cast<uint32_t>(testString[0]));

}



TEST_F(StringValueBaseTest_810, toUint32_BoundaryCondition_810) {

    if (testString.empty()) return; // Skip if testString is empty



    uint32_t result = stringValueBase->toUint32(testString.size() - 1);

    EXPECT_TRUE(stringValueBase->ok());

    EXPECT_EQ(result, static_cast<uint32_t>(testString[testString.size() - 1]));



    // Out of bounds should not crash but behavior is undefined as per interface

    result = stringValueBase->toUint32(testString.size());

    EXPECT_FALSE(stringValueBase->ok()); // Assuming ok_ is set to false on error

}



TEST_F(StringValueBaseTest_810, toUint32_ExceptionalCase_810) {

    if (testString.empty()) return; // Skip if testString is empty



    stringValueBase->toUint32(testString.size());

    EXPECT_FALSE(stringValueBase->ok()); // Assuming ok_ is set to false on error

}



TEST_F(StringValueBaseTest_810, read_NormalOperation_810) {

    std::string newString = "newString";

    int result = stringValueBase->read(newString);

    EXPECT_EQ(result, 0); // Assuming success return value is 0

    // Verify internal state change through observable behavior

    uint32_t firstChar = stringValueBase->toUint32(0);

    EXPECT_EQ(firstChar, static_cast<uint32_t>(newString[0]));

}



TEST_F(StringValueBaseTest_810, read_EmptyString_810) {

    std::string emptyString = "";

    int result = stringValueBase->read(emptyString);

    EXPECT_EQ(result, 0); // Assuming success return value is 0

    // Verify internal state change through observable behavior

    uint32_t firstChar = stringValueBase->toUint32(0);

    EXPECT_EQ(firstChar, static_cast<uint32_t>(emptyString[0]));

}



TEST_F(StringValueBaseTest_810, count_NormalOperation_810) {

    size_t result = stringValueBase->count();

    EXPECT_TRUE(stringValueBase->ok());

    EXPECT_EQ(result, testString.size());

}
