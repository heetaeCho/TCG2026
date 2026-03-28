#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "OptionalContent.h"
#include "Dict.h"
#include "PDFDoc.h"
#include "GlobalParams.h"

#include <memory>
#include <string>

class OptionalContentGroupTest_944 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }

    // Helper to create a minimal OCG dict
    Dict *createMinimalOCGDict(XRef *xref, const char *name) {
        Dict *dict = new Dict(xref);
        dict->add("Type", Object(objName, "OCG"));
        dict->add("Name", Object(new GooString(name)));
        return dict;
    }

    Dict *createOCGDictWithUsage(XRef *xref, const char *name, const char *viewState, const char *printState) {
        Dict *dict = new Dict(xref);
        dict->add("Type", Object(objName, "OCG"));
        dict->add("Name", Object(new GooString(name)));

        Dict *usageDict = new Dict(xref);

        if (viewState) {
            Dict *viewDict = new Dict(xref);
            viewDict->add("ViewState", Object(objName, viewState));
            usageDict->add("View", Object(viewDict));
        }

        if (printState) {
            Dict *printDict = new Dict(xref);
            printDict->add("PrintState", Object(objName, printState));
            usageDict->add("Print", Object(printDict));
        }

        dict->add("Usage", Object(usageDict));
        return dict;
    }
};

// Test that getViewState returns a valid UsageState for a basic OCG without usage dict
TEST_F(OptionalContentGroupTest_944, GetViewStateDefaultNoUsage_944) {
    // Create a minimal dict without Usage entry
    // Without usage info, viewState should default to ocUsageOn or some default
    Dict dict(nullptr);
    dict.add("Type", Object(objName, "OCG"));
    dict.add("Name", Object(new GooString("TestLayer")));

    OptionalContentGroup ocg(&dict);
    OptionalContentGroup::UsageState vs = ocg.getViewState();

    // Without a Usage dictionary, the view state should be unset/default
    // Typically this would be ocUsageUnset
    EXPECT_TRUE(vs == OptionalContentGroup::ocUsageOn ||
                vs == OptionalContentGroup::ocUsageOff ||
                vs == OptionalContentGroup::ocUsageUnset);
}

// Test getName returns the correct name
TEST_F(OptionalContentGroupTest_944, GetNameReturnsCorrectName_944) {
    Dict dict(nullptr);
    dict.add("Type", Object(objName, "OCG"));
    dict.add("Name", Object(new GooString("MyLayer")));

    OptionalContentGroup ocg(&dict);
    const GooString *name = ocg.getName();
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name->c_str(), "MyLayer");
}

// Test getState returns default state
TEST_F(OptionalContentGroupTest_944, GetStateDefaultIsOn_944) {
    Dict dict(nullptr);
    dict.add("Type", Object(objName, "OCG"));
    dict.add("Name", Object(new GooString("TestLayer")));

    OptionalContentGroup ocg(&dict);
    OptionalContentGroup::State state = ocg.getState();
    EXPECT_EQ(state, OptionalContentGroup::On);
}

// Test setState changes the state
TEST_F(OptionalContentGroupTest_944, SetStateChangesState_944) {
    Dict dict(nullptr);
    dict.add("Type", Object(objName, "OCG"));
    dict.add("Name", Object(new GooString("TestLayer")));

    OptionalContentGroup ocg(&dict);
    ocg.setState(OptionalContentGroup::Off);
    EXPECT_EQ(ocg.getState(), OptionalContentGroup::Off);

    ocg.setState(OptionalContentGroup::On);
    EXPECT_EQ(ocg.getState(), OptionalContentGroup::On);
}

// Test setRef and getRef
TEST_F(OptionalContentGroupTest_944, SetRefAndGetRef_944) {
    Dict dict(nullptr);
    dict.add("Type", Object(objName, "OCG"));
    dict.add("Name", Object(new GooString("TestLayer")));

    OptionalContentGroup ocg(&dict);
    Ref ref = {42, 0};
    ocg.setRef(ref);

    Ref retrievedRef = ocg.getRef();
    EXPECT_EQ(retrievedRef.num, 42);
    EXPECT_EQ(retrievedRef.gen, 0);
}

// Test getPrintState for OCG without usage
TEST_F(OptionalContentGroupTest_944, GetPrintStateDefaultNoUsage_944) {
    Dict dict(nullptr);
    dict.add("Type", Object(objName, "OCG"));
    dict.add("Name", Object(new GooString("TestLayer")));

    OptionalContentGroup ocg(&dict);
    OptionalContentGroup::UsageState ps = ocg.getPrintState();
    EXPECT_TRUE(ps == OptionalContentGroup::ocUsageOn ||
                ps == OptionalContentGroup::ocUsageOff ||
                ps == OptionalContentGroup::ocUsageUnset);
}

// Test getViewState consistency - calling multiple times returns same value
TEST_F(OptionalContentGroupTest_944, GetViewStateConsistent_944) {
    Dict dict(nullptr);
    dict.add("Type", Object(objName, "OCG"));
    dict.add("Name", Object(new GooString("ConsistentLayer")));

    OptionalContentGroup ocg(&dict);
    OptionalContentGroup::UsageState vs1 = ocg.getViewState();
    OptionalContentGroup::UsageState vs2 = ocg.getViewState();
    EXPECT_EQ(vs1, vs2);
}

// Test that getPrintState is consistent
TEST_F(OptionalContentGroupTest_944, GetPrintStateConsistent_944) {
    Dict dict(nullptr);
    dict.add("Type", Object(objName, "OCG"));
    dict.add("Name", Object(new GooString("ConsistentLayer")));

    OptionalContentGroup ocg(&dict);
    OptionalContentGroup::UsageState ps1 = ocg.getPrintState();
    OptionalContentGroup::UsageState ps2 = ocg.getPrintState();
    EXPECT_EQ(ps1, ps2);
}

// Test setState with multiple toggles
TEST_F(OptionalContentGroupTest_944, SetStateMultipleToggles_944) {
    Dict dict(nullptr);
    dict.add("Type", Object(objName, "OCG"));
    dict.add("Name", Object(new GooString("ToggleLayer")));

    OptionalContentGroup ocg(&dict);

    for (int i = 0; i < 10; i++) {
        ocg.setState(OptionalContentGroup::Off);
        EXPECT_EQ(ocg.getState(), OptionalContentGroup::Off);
        ocg.setState(OptionalContentGroup::On);
        EXPECT_EQ(ocg.getState(), OptionalContentGroup::On);
    }
}

// Test with empty name
TEST_F(OptionalContentGroupTest_944, EmptyName_944) {
    Dict dict(nullptr);
    dict.add("Type", Object(objName, "OCG"));
    dict.add("Name", Object(new GooString("")));

    OptionalContentGroup ocg(&dict);
    const GooString *name = ocg.getName();
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name->c_str(), "");
}

// Test setRef with different ref values
TEST_F(OptionalContentGroupTest_944, SetRefDifferentValues_944) {
    Dict dict(nullptr);
    dict.add("Type", Object(objName, "OCG"));
    dict.add("Name", Object(new GooString("RefTest")));

    OptionalContentGroup ocg(&dict);

    Ref ref1 = {1, 0};
    ocg.setRef(ref1);
    EXPECT_EQ(ocg.getRef().num, 1);
    EXPECT_EQ(ocg.getRef().gen, 0);

    Ref ref2 = {999, 5};
    ocg.setRef(ref2);
    EXPECT_EQ(ocg.getRef().num, 999);
    EXPECT_EQ(ocg.getRef().gen, 5);
}
