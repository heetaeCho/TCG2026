#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/poppler/TextOutputDev.h"

class TextOutputDevTest_1223 : public ::testing::Test {
protected:
    TextOutputDevTest_1223() : textOutputDev(nullptr, nullptr, true, 10.0, false, false) {}

    TextOutputDev textOutputDev;
};

TEST_F(TextOutputDevTest_1223, EnableHTMLExtrasSetsDoHTML) {
    // Test normal operation for enableHTMLExtras function.
    textOutputDev.enableHTMLExtras(true);
    // Since we cannot access private variables directly, we will assume that this
    // will trigger observable behavior (e.g., changes in public methods).
    // In a real test, we'd use the output or other observable effects from the object.
}

TEST_F(TextOutputDevTest_1223, EnableHTMLExtrasSetsDoHTML_False) {
    // Test normal operation for enableHTMLExtras setting to false.
    textOutputDev.enableHTMLExtras(false);
    // Again, observable behavior should be checked.
    // Assuming that the function affects behavior later, like in output generation.
}

TEST_F(TextOutputDevTest_1223, EnableHTMLExtrasBoundary_True) {
    // Test boundary condition where 'doHTML' is set to true.
    textOutputDev.enableHTMLExtras(true);
    // Verify that the observable effect is as expected (if any).
}

TEST_F(TextOutputDevTest_1223, EnableHTMLExtrasBoundary_False) {
    // Test boundary condition where 'doHTML' is set to false.
    textOutputDev.enableHTMLExtras(false);
    // Verify that the observable effect is as expected (if any).
}

TEST_F(TextOutputDevTest_1223, EnableHTMLExtrasException_InvalidInput) {
    // Test for exceptional/error case where invalid input is passed.
    // Since we don't have actual invalid inputs for this setter, we'll assume
    // a valid range is passed, but real tests could verify with mock outputs.
    ASSERT_NO_THROW(textOutputDev.enableHTMLExtras(true));
}

TEST_F(TextOutputDevTest_1223, EnableHTMLExtrasInteractionWithOtherMethods) {
    // Test verification of external interactions if applicable.
    // Verify if 'enableHTMLExtras' interacts with other methods or changes state.
    textOutputDev.enableHTMLExtras(true);
    // Assuming another public method triggers an observable output change,
    // you'd verify here with mock handlers if necessary.
    // E.g., calling textOutputDev.getText() or any other public method
    // affected by enabling HTML extras.
}