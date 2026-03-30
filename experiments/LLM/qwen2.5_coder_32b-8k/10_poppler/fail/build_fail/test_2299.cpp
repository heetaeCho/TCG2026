#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-action.h"

#include "Link.h"



class PopplerActionTest_2299 : public ::testing::Test {

protected:

    PopplerAction action;

};



TEST_F(PopplerActionTest_2299, BuildResetFormWithFields_2299) {

    std::vector<std::string> fields = {"field1", "field2"};

    LinkResetForm link(fields.data(), true);

    build_reset_form(&action, &link);



    GList* current = action.reset_form.fields;

    EXPECT_STREQ(static_cast<char*>(current->data), "field1");

    current = current->next;

    EXPECT_STREQ(static_cast<char*>(current->data), "field2");

    EXPECT_EQ(current->next, nullptr);

}



TEST_F(PopplerActionTest_2299, BuildResetFormExcludeTrue_2299) {

    std::vector<std::string> fields = {"field1"};

    LinkResetForm link(fields.data(), true);

    build_reset_form(&action, &link);



    EXPECT_TRUE(action.reset_form.exclude);

}



TEST_F(PopplerActionTest_2299, BuildResetFormExcludeFalse_2299) {

    std::vector<std::string> fields = {"field1"};

    LinkResetForm link(fields.data(), false);

    build_reset_form(&action, &link);



    EXPECT_FALSE(action.reset_form.exclude);

}



TEST_F(PopplerActionTest_2299, BuildResetFormNoFields_2299) {

    std::vector<std::string> fields = {};

    LinkResetForm link(fields.data(), true);

    build_reset_form(&action, &link);



    EXPECT_EQ(action.reset_form.fields, nullptr);

}



TEST_F(PopplerActionTest_2299, BuildResetFormExistingFields_2299) {

    std::vector<std::string> initial_fields = {"initial_field"};

    action.reset_form.fields = g_list_append(nullptr, g_strdup(initial_fields[0].c_str()));



    std::vector<std::string> new_fields = {"field1", "field2"};

    LinkResetForm link(new_fields.data(), true);

    build_reset_form(&action, &link);



    GList* current = action.reset_form.fields;

    EXPECT_STREQ(static_cast<char*>(current->data), "field1");

    current = current->next;

    EXPECT_STREQ(static_cast<char*>(current->data), "field2");

    EXPECT_EQ(current->next, nullptr);

}
