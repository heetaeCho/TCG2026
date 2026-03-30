#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/poppler/glib/poppler-structure-element.cc"

#include "./TestProjects/poppler/poppler/Object.h"



using ::testing::Return;



class MockObject : public Object {

public:

    MOCK_METHOD(int, arrayGetLength, (), (const, override));

    MOCK_METHOD(Object, arrayGet, (int i, int recursion), (const, override));

};



TEST_F(ConvertDoublesArrayTest_2555, NormalOperation_2555) {

    MockObject mock_object;

    EXPECT_CALL(mock_object, arrayGetLength()).WillOnce(Return(3));



    std::vector<double> expected_values = {1.0, 2.0, 3.0};

    EXPECT_CALL(mock_object, arrayGet(0, 0)).WillOnce(Return(Object(expected_values[0])));

    EXPECT_CALL(mock_object, arrayGet(1, 0)).WillOnce(Return(Object(expected_values[1])));

    EXPECT_CALL(mock_object, arrayGet(2, 0)).WillOnce(Return(Object(expected_values[2])));



    gdouble *values = nullptr;

    guint n_values = 0;

    convert_doubles_array(&mock_object, &values, &n_values);



    ASSERT_EQ(n_values, expected_values.size());

    for (guint i = 0; i < n_values; ++i) {

        EXPECT_DOUBLE_EQ(values[i], expected_values[i]);

    }

    g_free(values);

}



TEST_F(ConvertDoublesArrayTest_2555, BoundaryCondition_ZeroLength_2555) {

    MockObject mock_object;

    EXPECT_CALL(mock_object, arrayGetLength()).WillOnce(Return(0));



    gdouble *values = nullptr;

    guint n_values = 0;

    convert_doubles_array(&mock_object, &values, &n_values);



    ASSERT_EQ(n_values, 0);

    EXPECT_EQ(values, nullptr);

}



TEST_F(ConvertDoublesArrayTest_2555, BoundaryCondition_OneElement_2555) {

    MockObject mock_object;

    EXPECT_CALL(mock_object, arrayGetLength()).WillOnce(Return(1));



    std::vector<double> expected_values = {42.0};

    EXPECT_CALL(mock_object, arrayGet(0, 0)).WillOnce(Return(Object(expected_values[0])));



    gdouble *values = nullptr;

    guint n_values = 0;

    convert_doubles_array(&mock_object, &values, &n_values);



    ASSERT_EQ(n_values, expected_values.size());

    for (guint i = 0; i < n_values; ++i) {

        EXPECT_DOUBLE_EQ(values[i], expected_values[i]);

    }

    g_free(values);

}



TEST_F(ConvertDoublesArrayTest_2555, ExceptionalCase_ArrayLengthNegative_2555) {

    MockObject mock_object;

    EXPECT_CALL(mock_object, arrayGetLength()).WillOnce(Return(-1));



    gdouble *values = nullptr;

    guint n_values = 0;



    // Assuming the function will handle negative length gracefully

    convert_doubles_array(&mock_object, &values, &n_values);



    ASSERT_EQ(n_values, 0);

    EXPECT_EQ(values, nullptr);

}



TEST_F(ConvertDoublesArrayTest_2555, ExternalInteraction_CallbackInvocation_2555) {

    MockObject mock_object;

    EXPECT_CALL(mock_object, arrayGetLength()).WillOnce(Return(3));



    std::vector<double> expected_values = {1.0, 2.0, 3.0};

    for (guint i = 0; i < expected_values.size(); ++i) {

        EXPECT_CALL(mock_object, arrayGet(i, 0)).WillRepeatedly(Return(Object(expected_values[i])));

    }



    gdouble *values = nullptr;

    guint n_values = 0;

    convert_doubles_array(&mock_object, &values, &n_values);



    ASSERT_EQ(n_values, expected_values.size());

    for (guint i = 0; i < n_values; ++i) {

        EXPECT_DOUBLE_EQ(values[i], expected_values[i]);

    }

    g_free(values);

}
