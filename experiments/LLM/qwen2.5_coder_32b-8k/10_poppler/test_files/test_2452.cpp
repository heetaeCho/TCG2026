#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-page.h"



// Mocking external dependencies if necessary

class MockPopplerPage : public PopplerPage {

public:

    MOCK_METHOD(void, finalize, (), (override));

    MOCK_METHOD(void, get_property, (GObject* object, guint property_id, GValue* value, GParamSpec* pspec), (override));

};



// Test fixture for PopplerPage

class PopplerPageTest_2452 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize any necessary objects or mocks here

    }



    void TearDown() override {

        // Clean up if necessary

    }

};



TEST_F(PopplerPageTest_2452, FinalizeIsCalled_2452) {

    MockPopplerPage mockPage;

    EXPECT_CALL(mockPage, finalize()).Times(1);

    mockPage.finalize();

}



TEST_F(PopplerPageTest_2452, GetPropertyLabel_ReturnsNullByDefault_2452) {

    PopplerPage page;

    GValue value = G_VALUE_INIT;

    g_value_init(&value, G_TYPE_STRING);

    g_object_get_property(G_OBJECT(&page), "label", &value);



    EXPECT_EQ(g_value_get_string(&value), nullptr);

    g_value_unset(&value);

}



// No observable exceptional or error cases for the provided interface



TEST_F(PopplerPageTest_2452, BoundaryConditionLabelProperty_2452) {

    PopplerPage page;

    GValue value = G_VALUE_INIT;

    g_value_init(&value, G_TYPE_STRING);



    // Test with an invalid property id

    EXPECT_NO_THROW(g_object_get_property(G_OBJECT(&page), 0, &value));

    EXPECT_EQ(g_value_get_string(&value), nullptr);

    g_value_unset(&value);

}



TEST_F(PopplerPageTest_2452, LabelProperty_IsReadable_2452) {

    PopplerPage page;

    GValue value = G_VALUE_INIT;

    g_value_init(&value, G_TYPE_STRING);



    // Test if the property is readable

    EXPECT_NO_THROW(g_object_get_property(G_OBJECT(&page), PROP_LABEL, &value));

    EXPECT_EQ(g_value_get_string(&value), nullptr);

    g_value_unset(&value);

}
