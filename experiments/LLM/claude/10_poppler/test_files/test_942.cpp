#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "OptionalContent.h"
#include "Dict.h"
#include "PDFDoc.h"
#include "GlobalParams.h"

class OptionalContentGroupTest_942 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Test that getState returns the current state of the OptionalContentGroup
TEST_F(OptionalContentGroupTest_942, GetStateReturnsCurrentState_942) {
    // We need a Dict to construct an OptionalContentGroup
    // Create a minimal dict that has the required /Type and /Name entries
    XRef xref;
    Dict *dict = new Dict(&xref);
    
    // Add required entries for an OCG dict
    dict->add("Type", Object(objName, "OCG"));
    GooString nameStr("TestOCG");
    dict->add("Name", Object(&nameStr));
    
    OptionalContentGroup ocg(dict);
    
    // By default, OCGs should be in ON state
    OptionalContentGroup::State state = ocg.getState();
    EXPECT_TRUE(state == OptionalContentGroup::On || state == OptionalContentGroup::Off);
}

// Test setState and getState round-trip
TEST_F(OptionalContentGroupTest_942, SetStateThenGetState_942) {
    XRef xref;
    Dict *dict = new Dict(&xref);
    dict->add("Type", Object(objName, "OCG"));
    GooString nameStr("TestOCG2");
    dict->add("Name", Object(&nameStr));
    
    OptionalContentGroup ocg(dict);
    
    ocg.setState(OptionalContentGroup::On);
    EXPECT_EQ(ocg.getState(), OptionalContentGroup::On);
    
    ocg.setState(OptionalContentGroup::Off);
    EXPECT_EQ(ocg.getState(), OptionalContentGroup::Off);
}

// Test toggling state
TEST_F(OptionalContentGroupTest_942, ToggleState_942) {
    XRef xref;
    Dict *dict = new Dict(&xref);
    dict->add("Type", Object(objName, "OCG"));
    GooString nameStr("TestOCG3");
    dict->add("Name", Object(&nameStr));
    
    OptionalContentGroup ocg(dict);
    
    ocg.setState(OptionalContentGroup::On);
    EXPECT_EQ(ocg.getState(), OptionalContentGroup::On);
    
    ocg.setState(OptionalContentGroup::Off);
    EXPECT_EQ(ocg.getState(), OptionalContentGroup::Off);
    
    ocg.setState(OptionalContentGroup::On);
    EXPECT_EQ(ocg.getState(), OptionalContentGroup::On);
}

// Test getName returns a valid name
TEST_F(OptionalContentGroupTest_942, GetNameReturnsName_942) {
    XRef xref;
    Dict *dict = new Dict(&xref);
    dict->add("Type", Object(objName, "OCG"));
    GooString nameStr("MyLayer");
    dict->add("Name", Object(&nameStr));
    
    OptionalContentGroup ocg(dict);
    
    const GooString *name = ocg.getName();
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name->c_str(), "MyLayer");
}

// Test setRef and getRef round-trip
TEST_F(OptionalContentGroupTest_942, SetRefAndGetRef_942) {
    XRef xref;
    Dict *dict = new Dict(&xref);
    dict->add("Type", Object(objName, "OCG"));
    GooString nameStr("RefTestOCG");
    dict->add("Name", Object(&nameStr));
    
    OptionalContentGroup ocg(dict);
    
    Ref testRef = {42, 0};
    ocg.setRef(testRef);
    
    Ref retrievedRef = ocg.getRef();
    EXPECT_EQ(retrievedRef.num, 42);
    EXPECT_EQ(retrievedRef.gen, 0);
}

// Test getViewState and getPrintState
TEST_F(OptionalContentGroupTest_942, GetViewAndPrintState_942) {
    XRef xref;
    Dict *dict = new Dict(&xref);
    dict->add("Type", Object(objName, "OCG"));
    GooString nameStr("UsageTestOCG");
    dict->add("Name", Object(&nameStr));
    
    OptionalContentGroup ocg(dict);
    
    // Without usage dict, these should return a default value
    OptionalContentGroup::UsageState viewState = ocg.getViewState();
    OptionalContentGroup::UsageState printState = ocg.getPrintState();
    
    // Just verify they return valid enum values (no crash)
    EXPECT_TRUE(viewState == OptionalContentGroup::ocUsageOn || 
                viewState == OptionalContentGroup::ocUsageOff || 
                viewState == OptionalContentGroup::ocUsageUnset);
    EXPECT_TRUE(printState == OptionalContentGroup::ocUsageOn || 
                printState == OptionalContentGroup::ocUsageOff || 
                printState == OptionalContentGroup::ocUsageUnset);
}

// Test setting state to Off explicitly
TEST_F(OptionalContentGroupTest_942, SetStateOff_942) {
    XRef xref;
    Dict *dict = new Dict(&xref);
    dict->add("Type", Object(objName, "OCG"));
    GooString nameStr("OffTestOCG");
    dict->add("Name", Object(&nameStr));
    
    OptionalContentGroup ocg(dict);
    
    ocg.setState(OptionalContentGroup::Off);
    EXPECT_EQ(ocg.getState(), OptionalContentGroup::Off);
}

// Test setting state to On explicitly
TEST_F(OptionalContentGroupTest_942, SetStateOn_942) {
    XRef xref;
    Dict *dict = new Dict(&xref);
    dict->add("Type", Object(objName, "OCG"));
    GooString nameStr("OnTestOCG");
    dict->add("Name", Object(&nameStr));
    
    OptionalContentGroup ocg(dict);
    
    ocg.setState(OptionalContentGroup::On);
    EXPECT_EQ(ocg.getState(), OptionalContentGroup::On);
}

// Test multiple state changes
TEST_F(OptionalContentGroupTest_942, MultipleStateChanges_942) {
    XRef xref;
    Dict *dict = new Dict(&xref);
    dict->add("Type", Object(objName, "OCG"));
    GooString nameStr("MultiChangeOCG");
    dict->add("Name", Object(&nameStr));
    
    OptionalContentGroup ocg(dict);
    
    for (int i = 0; i < 10; ++i) {
        ocg.setState(OptionalContentGroup::On);
        EXPECT_EQ(ocg.getState(), OptionalContentGroup::On);
        ocg.setState(OptionalContentGroup::Off);
        EXPECT_EQ(ocg.getState(), OptionalContentGroup::Off);
    }
}

// Test setRef with different values
TEST_F(OptionalContentGroupTest_942, SetRefMultipleTimes_942) {
    XRef xref;
    Dict *dict = new Dict(&xref);
    dict->add("Type", Object(objName, "OCG"));
    GooString nameStr("MultiRefOCG");
    dict->add("Name", Object(&nameStr));
    
    OptionalContentGroup ocg(dict);
    
    Ref ref1 = {10, 0};
    ocg.setRef(ref1);
    EXPECT_EQ(ocg.getRef().num, 10);
    
    Ref ref2 = {20, 1};
    ocg.setRef(ref2);
    EXPECT_EQ(ocg.getRef().num, 20);
    EXPECT_EQ(ocg.getRef().gen, 1);
}
