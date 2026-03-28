#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-annot.h"

#include "poppler-private.h"



// Mock class for Annot

class MockAnnot : public Annot {

public:

    MOCK_METHOD(const GooString*, getModified, (), (const, override));

};



// Test fixture for PopplerAnnot tests

class PopplerAnnotTest_2066 : public ::testing::Test {

protected:

    std::shared_ptr<MockAnnot> mock_annot;

    _PopplerAnnot poppler_annot;



    void SetUp() override {

        mock_annot = std::make_shared<MockAnnot>();

        poppler_annot.annot = mock_annot;

    }

};



// Test case to verify normal operation with a valid modified date

TEST_F(PopplerAnnotTest_2066, GetModified_ReturnsValidString_2066) {

    const char* expected_modified_date = "2023-10-05T14:48:00Z";

    GooString goo_string(expected_modified_date);

    EXPECT_CALL(*mock_annot, getModified()).WillOnce(::testing::Return(&goo_string));



    gchar* result = poppler_annot_get_modified(reinterpret_cast<PopplerAnnot*>(&poppler_annot));

    ASSERT_STREQ(result, expected_modified_date);

    g_free(result);

}



// Test case to verify behavior when the modified date is not set

TEST_F(PopplerAnnotTest_2066, GetModified_ReturnsNullWhenNotSet_2066) {

    EXPECT_CALL(*mock_annot, getModified()).WillOnce(::testing::Return(nullptr));



    gchar* result = poppler_annot_get_modified(reinterpret_cast<PopplerAnnot*>(&poppler_annot));

    ASSERT_EQ(result, nullptr);

}



// Test case to verify behavior with an empty modified date

TEST_F(PopplerAnnotTest_2066, GetModified_ReturnsNullWhenEmptyString_2066) {

    GooString goo_string("");

    EXPECT_CALL(*mock_annot, getModified()).WillOnce(::testing::Return(&goo_string));



    gchar* result = poppler_annot_get_modified(reinterpret_cast<PopplerAnnot*>(&poppler_annot));

    ASSERT_EQ(result, nullptr);

}



// Test case to verify behavior with a null PopplerAnnot pointer

TEST(PopplerAnnotTest_2066, GetModified_ReturnsNullWhenNullPointer_2066) {

    gchar* result = poppler_annot_get_modified(nullptr);

    ASSERT_EQ(result, nullptr);

}
