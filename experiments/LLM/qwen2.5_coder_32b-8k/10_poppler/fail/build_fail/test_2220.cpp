#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-document.h"

#include "FontInfo.h"



// Mocking FontInfo to control its behavior for testing purposes

class MockFontInfo : public FontInfo {

public:

    MOCK_METHOD(const std::optional<std::string>&, getName, (), (const, override));

};



// Test fixture for PopplerFontsIter

class PopplerFontsIterTest_2220 : public ::testing::Test {

protected:

    void SetUp() override {

        iter = new _PopplerFontsIter();

        iter->items = new FontInfo*[3]; // Assuming a simple array of pointers for testing



        // Create mock objects for each item

        iter->items[0] = new MockFontInfo();

        iter->items[1] = new MockFontInfo();

        iter->items[2] = new MockFontInfo();



        iter->index = 0; // Start at the first item

    }



    void TearDown() override {

        for (int i = 0; i < 3; ++i) {

            delete static_cast<MockFontInfo*>(iter->items[i]);

        }

        delete[] iter->items;

        delete iter;

    }



protected:

    _PopplerFontsIter* iter;

};



// Test case: Normal operation - Full name available

TEST_F(PopplerFontsIterTest_2220, GetFullName_Normal_2220) {

    std::optional<std::string> expectedName = "Arial";

    EXPECT_CALL(*static_cast<MockFontInfo*>(iter->items[0]), getName())

        .WillOnce(::testing::Return(expectedName));



    char* result = poppler_fonts_iter_get_full_name(iter);

    ASSERT_NE(result, nullptr);

    EXPECT_STREQ(result, expectedName->c_str());

}



// Test case: Normal operation - Full name not available

TEST_F(PopplerFontsIterTest_2220, GetFullName_NotAvailable_2220) {

    std::optional<std::string> expectedName;

    EXPECT_CALL(*static_cast<MockFontInfo*>(iter->items[1]), getName())

        .WillOnce(::testing::Return(expectedName));



    iter->index = 1; // Move to the second item

    char* result = poppler_fonts_iter_get_full_name(iter);

    ASSERT_EQ(result, nullptr);

}



// Test case: Boundary condition - Index out of bounds

TEST_F(PopplerFontsIterTest_2220, GetFullName_OutOfBounds_2220) {

    iter->index = 3; // Out of bounds

    char* result = poppler_fonts_iter_get_full_name(iter);

    ASSERT_EQ(result, nullptr);

}



// Test case: Exceptional or error cases - Index out of bounds (negative)

TEST_F(PopplerFontsIterTest_2220, GetFullName_NegativeIndex_2220) {

    iter->index = -1; // Negative index

    char* result = poppler_fonts_iter_get_full_name(iter);

    ASSERT_EQ(result, nullptr);

}



// Test case: Verification of external interactions - getName() is called

TEST_F(PopplerFontsIterTest_2220, GetFullName_VerifyGetNameCall_2220) {

    std::optional<std::string> expectedName = "Times New Roman";

    EXPECT_CALL(*static_cast<MockFontInfo*>(iter->items[2]), getName())

        .WillOnce(::testing::Return(expectedName));



    iter->index = 2; // Move to the third item

    char* result = poppler_fonts_iter_get_full_name(iter);

    ASSERT_NE(result, nullptr);

    EXPECT_STREQ(result, expectedName->c_str());

}
