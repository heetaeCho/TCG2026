#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "OptionalContent.h"
#include "Dict.h"
#include "PDFDoc.h"
#include "GlobalParams.h"

#include <memory>

class OptionalContentGroupTest_945 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Test that getPrintState returns a valid UsageState value
TEST_F(OptionalContentGroupTest_945, GetPrintStateReturnsUsageState_945) {
    // We need a Dict to construct an OptionalContentGroup
    // Create a minimal OCG dictionary
    XRef xref;
    Dict *dict = new Dict(&xref);
    
    // Add required "Name" entry for OCG
    GooString nameStr("TestOCG");
    dict->add("Name", Object(nameStr.copy()));
    dict->add("Type", Object(objName, "OCG"));
    
    OptionalContentGroup ocg(dict);
    
    // getPrintState should return a valid UsageState
    // Without usage dictionary, it should return ocUsageOn or some default
    OptionalContentGroup::UsageState state = ocg.getPrintState();
    
    // The state should be one of the valid enum values
    EXPECT_TRUE(state == OptionalContentGroup::ocUsageOn ||
                state == OptionalContentGroup::ocUsageOff ||
                state == OptionalContentGroup::ocUsageUnset);
    
    delete dict;
}

// Test that getPrintState returns default value when no usage dict is present
TEST_F(OptionalContentGroupTest_945, GetPrintStateDefaultWhenNoUsageDict_945) {
    XRef xref;
    Dict *dict = new Dict(&xref);
    
    GooString nameStr("TestOCGNoUsage");
    dict->add("Name", Object(nameStr.copy()));
    dict->add("Type", Object(objName, "OCG"));
    
    OptionalContentGroup ocg(dict);
    
    // Without a Usage dictionary, printState should be unset
    OptionalContentGroup::UsageState printState = ocg.getPrintState();
    EXPECT_EQ(printState, OptionalContentGroup::ocUsageUnset);
    
    delete dict;
}

// Test that getPrintState reflects print usage when Usage dict with Print is present
TEST_F(OptionalContentGroupTest_945, GetPrintStateWithPrintUsageOn_945) {
    XRef xref;
    Dict *usagePrintDict = new Dict(&xref);
    usagePrintDict->add("PrintState", Object(objName, "ON"));
    
    Dict *usageDict = new Dict(&xref);
    usageDict->add("Print", Object(usagePrintDict));
    
    Dict *dict = new Dict(&xref);
    GooString nameStr("TestOCGPrintOn");
    dict->add("Name", Object(nameStr.copy()));
    dict->add("Type", Object(objName, "OCG"));
    dict->add("Usage", Object(usageDict));
    
    OptionalContentGroup ocg(dict);
    
    OptionalContentGroup::UsageState printState = ocg.getPrintState();
    EXPECT_EQ(printState, OptionalContentGroup::ocUsageOn);
    
    delete dict;
}

// Test that getPrintState reflects OFF when Usage Print is OFF
TEST_F(OptionalContentGroupTest_945, GetPrintStateWithPrintUsageOff_945) {
    XRef xref;
    Dict *usagePrintDict = new Dict(&xref);
    usagePrintDict->add("PrintState", Object(objName, "OFF"));
    
    Dict *usageDict = new Dict(&xref);
    usageDict->add("Print", Object(usagePrintDict));
    
    Dict *dict = new Dict(&xref);
    GooString nameStr("TestOCGPrintOff");
    dict->add("Name", Object(nameStr.copy()));
    dict->add("Type", Object(objName, "OCG"));
    dict->add("Usage", Object(usageDict));
    
    OptionalContentGroup ocg(dict);
    
    OptionalContentGroup::UsageState printState = ocg.getPrintState();
    EXPECT_EQ(printState, OptionalContentGroup::ocUsageOff);
    
    delete dict;
}

// Test getViewState alongside getPrintState for consistency
TEST_F(OptionalContentGroupTest_945, GetPrintStateIndependentOfViewState_945) {
    XRef xref;
    Dict *usagePrintDict = new Dict(&xref);
    usagePrintDict->add("PrintState", Object(objName, "ON"));
    
    Dict *usageViewDict = new Dict(&xref);
    usageViewDict->add("ViewState", Object(objName, "OFF"));
    
    Dict *usageDict = new Dict(&xref);
    usageDict->add("Print", Object(usagePrintDict));
    usageDict->add("View", Object(usageViewDict));
    
    Dict *dict = new Dict(&xref);
    GooString nameStr("TestOCGBothUsage");
    dict->add("Name", Object(nameStr.copy()));
    dict->add("Type", Object(objName, "OCG"));
    dict->add("Usage", Object(usageDict));
    
    OptionalContentGroup ocg(dict);
    
    // Print should be ON regardless of view being OFF
    EXPECT_EQ(ocg.getPrintState(), OptionalContentGroup::ocUsageOn);
    EXPECT_EQ(ocg.getViewState(), OptionalContentGroup::ocUsageOff);
    
    delete dict;
}

// Test getPrintState is const-correct (can be called on const reference)
TEST_F(OptionalContentGroupTest_945, GetPrintStateConstCorrectness_945) {
    XRef xref;
    Dict *dict = new Dict(&xref);
    GooString nameStr("TestConst");
    dict->add("Name", Object(nameStr.copy()));
    dict->add("Type", Object(objName, "OCG"));
    
    OptionalContentGroup ocg(dict);
    const OptionalContentGroup &constRef = ocg;
    
    // Should compile and work on const reference
    OptionalContentGroup::UsageState state = constRef.getPrintState();
    EXPECT_TRUE(state == OptionalContentGroup::ocUsageOn ||
                state == OptionalContentGroup::ocUsageOff ||
                state == OptionalContentGroup::ocUsageUnset);
    
    delete dict;
}

// Test that getPrintState returns consistent results on multiple calls
TEST_F(OptionalContentGroupTest_945, GetPrintStateConsistentMultipleCalls_945) {
    XRef xref;
    Dict *dict = new Dict(&xref);
    GooString nameStr("TestConsistent");
    dict->add("Name", Object(nameStr.copy()));
    dict->add("Type", Object(objName, "OCG"));
    
    OptionalContentGroup ocg(dict);
    
    OptionalContentGroup::UsageState firstCall = ocg.getPrintState();
    OptionalContentGroup::UsageState secondCall = ocg.getPrintState();
    OptionalContentGroup::UsageState thirdCall = ocg.getPrintState();
    
    EXPECT_EQ(firstCall, secondCall);
    EXPECT_EQ(secondCall, thirdCall);
    
    delete dict;
}

// Test that setState does not affect getPrintState
TEST_F(OptionalContentGroupTest_945, SetStateDoesNotAffectPrintState_945) {
    XRef xref;
    Dict *dict = new Dict(&xref);
    GooString nameStr("TestSetState");
    dict->add("Name", Object(nameStr.copy()));
    dict->add("Type", Object(objName, "OCG"));
    
    OptionalContentGroup ocg(dict);
    
    OptionalContentGroup::UsageState printBefore = ocg.getPrintState();
    
    // Change the OCG state
    ocg.setState(OptionalContentGroup::On);
    OptionalContentGroup::UsageState printAfterOn = ocg.getPrintState();
    
    ocg.setState(OptionalContentGroup::Off);
    OptionalContentGroup::UsageState printAfterOff = ocg.getPrintState();
    
    // Print state should remain unchanged regardless of state changes
    EXPECT_EQ(printBefore, printAfterOn);
    EXPECT_EQ(printBefore, printAfterOff);
    
    delete dict;
}
