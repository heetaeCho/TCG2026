#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Form.h"

#include <memory>



class FormFieldChoiceMock : public FormFieldChoice {

public:

    using FormFieldChoice::FormFieldChoice;

    MOCK_METHOD(const GooString*, getSelectedChoice, (), (const));

    MOCK_METHOD(void, setAppearanceChoiceContent, (std::unique_ptr<GooString> new_content), ());

    MOCK_METHOD(void, select, (int i), ());

    MOCK_METHOD(void, toggle, (int i), ());

    MOCK_METHOD(void, deselectAll, (), ());

    MOCK_METHOD(void, setEditChoice, (std::unique_ptr<GooString> new_content), ());

    MOCK_METHOD(const GooString*, getEditChoice, (), (const));

    MOCK_METHOD(int, getNumSelected, (), (const));

    MOCK_METHOD(void, print, (int indent), (override));

    MOCK_METHOD(void, reset, (const std::vector<std::string>& excludedFields), (override));

    MOCK_METHOD(const GooString*, getAppearanceSelectedChoice, (), (const));

    MOCK_METHOD(bool, isSelected, (int i), (const));

    MOCK_METHOD(bool, isCombo, (), (const));

    MOCK_METHOD(bool, hasEdit, (), (const));

    MOCK_METHOD(bool, isMultiSelect, (), (const));

    MOCK_METHOD(bool, noSpellCheck, (), (const));

    MOCK_METHOD(bool, commitOnSelChange, (), (const));

    MOCK_METHOD(int, getTopIndex, (), (const));

    MOCK_METHOD(int, getNumChoices, (), (const));

    MOCK_METHOD(const GooString*, getChoice, (int i), (const));

    MOCK_METHOD(const GooString*, getExportVal, (int i), (const));

};



class FormFieldChoiceTest_922 : public ::testing::Test {

protected:

    std::unique_ptr<FormFieldChoiceMock> formFieldChoice;



    void SetUp() override {

        // Assuming a mock constructor is available or use a real object if possible

        formFieldChoice = std::make_unique<FormFieldChoiceMock>(nullptr, Object(), Ref(), nullptr, static_cast<std::set<int>* >(nullptr));

    }

};



TEST_F(FormFieldChoiceTest_922, IsListBoxWhenComboFalse_922) {

    EXPECT_CALL(*formFieldChoice, isCombo()).WillOnce(::testing::Return(false));

    EXPECT_TRUE(formFieldChoice->isListBox());

}



TEST_F(FormFieldChoiceTest_922, IsNotListBoxWhenComboTrue_922) {

    EXPECT_CALL(*formFieldChoice, isCombo()).WillOnce(::testing::Return(true));

    EXPECT_FALSE(formFieldChoice->isListBox());

}
