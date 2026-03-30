#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Mocking external dependencies if needed

class MockAnnot {

public:

    MOCK_CONST_METHOD0(getName, const GooString*());

};



TEST_F(PopplerAnnotTest_2065, GetValidName_2065) {

    MockAnnot mock_annot;

    GooString expected_name("valid_name");

    EXPECT_CALL(mock_annot, getName()).WillOnce(::testing::Return(&expected_name));



    PopplerAnnot poppler_annot;

    poppler_annot.annot = std::make_shared<MockAnnot>(mock_annot);



    gchar* result = poppler_annot_get_name(&poppler_annot);

    ASSERT_STREQ(result, "valid_name");

    g_free(result);

}



TEST_F(PopplerAnnotTest_2065, GetNullName_2065) {

    MockAnnot mock_annot;

    EXPECT_CALL(mock_annot, getName()).WillOnce(::testing::Return(nullptr));



    PopplerAnnot poppler_annot;

    poppler_annot.annot = std::make_shared<MockAnnot>(mock_annot);



    gchar* result = poppler_annot_get_name(&poppler_annot);

    ASSERT_EQ(result, nullptr);

}



TEST_F(PopplerAnnotTest_2065, InvalidPopplerAnnot_2065) {

    PopplerAnnot* invalid_poppler_annot = nullptr;

    gchar* result = poppler_annot_get_name(invalid_poppler_annot);

    ASSERT_EQ(result, nullptr);

}
