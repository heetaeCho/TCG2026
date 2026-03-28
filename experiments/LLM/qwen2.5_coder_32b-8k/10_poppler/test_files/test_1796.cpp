#include <gtest/gtest.h>

#include "GooString.h"

#include <secitem.h>



// Mocking SECItem for testing purposes

class MockSECItem {

public:

    unsigned char* data;

    unsigned int len;



    MockSECItem(const unsigned char* d, unsigned int l) : len(l) {

        data = new unsigned char[l];

        memcpy(data, d, l);

    }



    ~MockSECItem() {

        delete[] data;

    }

};



// Test fixture for SECItemToGooString

class SECItemToGooStringTest_1796 : public ::testing::Test {

protected:

    void SetUp() override {}

    void TearDown() override {}

};



// Normal operation test

TEST_F(SECItemToGooStringTest_1796, ConvertsNormalData_1796) {

    const unsigned char testData[] = "Hello, World!";

    MockSECItem secItem(testData, sizeof(testData) - 1); // Exclude null terminator



    GooString result = SECItemToGooString(secItem);

    EXPECT_STREQ("Hello, World!", result.getCString());

}



// Boundary condition: Empty data

TEST_F(SECItemToGooStringTest_1796, HandlesEmptyData_1796) {

    const unsigned char testData[] = "";

    MockSECItem secItem(testData, sizeof(testData) - 1); // Empty data



    GooString result = SECItemToGooString(secItem);

    EXPECT_STREQ("", result.getCString());

}



// Boundary condition: Single character

TEST_F(SECItemToGooStringTest_1796, HandlesSingleCharacter_1796) {

    const unsigned char testData[] = "A";

    MockSECItem secItem(testData, sizeof(testData) - 1); // Exclude null terminator



    GooString result = SECItemToGooString(secItem);

    EXPECT_STREQ("A", result.getCString());

}



// Exceptional case: Null data pointer

TEST_F(SECItemToGooStringTest_1796, HandlesNullDataPointer_1796) {

    MockSECItem secItem(nullptr, 0);



    GooString result = SECItemToGooString(secItem);

    EXPECT_STREQ("", result.getCString());

}
