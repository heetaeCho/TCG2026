#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "OptionalContent.h"

// Since we need to test OptionalContentGroup but the constructor requires a Dict*,
// and we need to work with the public interface, we'll set up tests accordingly.

// We need to include necessary headers for Dict and other Poppler types
#include "Dict.h"
#include "Object.h"
#include "PDFDoc.h"
#include "GlobalParams.h"

#include <memory>

class OptionalContentGroupTest_943 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }

    // Helper to create a minimal OCG Dict
    std::unique_ptr<Dict> createOCGDict(XRef *xref, const char *name) {
        auto dict = std::make_unique<Dict>(xref);
        dict->add("Type", Object(objName, "OCG"));
        dict->add("Name", Object(new GooString(name)));
        return dict;
    }
};

// Test that setState changes the state and getState reflects it
TEST_F(OptionalContentGroupTest_943, SetStateOn_943) {
    Dict dict(nullptr);
    dict.add("Type", Object(objName, "OCG"));
    dict.add("Name", Object(new GooString("TestGroup")));
    
    OptionalContentGroup ocg(&dict);
    
    ocg.setState(OptionalContentGroup::On);
    EXPECT_EQ(ocg.getState(), OptionalContentGroup::On);
}

TEST_F(OptionalContentGroupTest_943, SetStateOff_943) {
    Dict dict(nullptr);
    dict.add("Type", Object(objName, "OCG"));
    dict.add("Name", Object(new GooString("TestGroup")));
    
    OptionalContentGroup ocg(&dict);
    
    ocg.setState(OptionalContentGroup::Off);
    EXPECT_EQ(ocg.getState(), OptionalContentGroup::Off);
}

TEST_F(OptionalContentGroupTest_943, SetStateToggle_943) {
    Dict dict(nullptr);
    dict.add("Type", Object(objName, "OCG"));
    dict.add("Name", Object(new GooString("TestGroup")));
    
    OptionalContentGroup ocg(&dict);
    
    ocg.setState(OptionalContentGroup::On);
    EXPECT_EQ(ocg.getState(), OptionalContentGroup::On);
    
    ocg.setState(OptionalContentGroup::Off);
    EXPECT_EQ(ocg.getState(), OptionalContentGroup::Off);
    
    ocg.setState(OptionalContentGroup::On);
    EXPECT_EQ(ocg.getState(), OptionalContentGroup::On);
}

TEST_F(OptionalContentGroupTest_943, GetNameReturnsCorrectName_943) {
    Dict dict(nullptr);
    dict.add("Type", Object(objName, "OCG"));
    dict.add("Name", Object(new GooString("MyLayerName")));
    
    OptionalContentGroup ocg(&dict);
    
    const GooString *name = ocg.getName();
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name->c_str(), "MyLayerName");
}

TEST_F(OptionalContentGroupTest_943, SetRefAndGetRef_943) {
    Dict dict(nullptr);
    dict.add("Type", Object(objName, "OCG"));
    dict.add("Name", Object(new GooString("RefTest")));
    
    OptionalContentGroup ocg(&dict);
    
    Ref testRef = {10, 0};
    ocg.setRef(testRef);
    
    Ref retrieved = ocg.getRef();
    EXPECT_EQ(retrieved.num, 10);
    EXPECT_EQ(retrieved.gen, 0);
}

TEST_F(OptionalContentGroupTest_943, SetRefDifferentValues_943) {
    Dict dict(nullptr);
    dict.add("Type", Object(objName, "OCG"));
    dict.add("Name", Object(new GooString("RefTest2")));
    
    OptionalContentGroup ocg(&dict);
    
    Ref testRef = {42, 3};
    ocg.setRef(testRef);
    
    Ref retrieved = ocg.getRef();
    EXPECT_EQ(retrieved.num, 42);
    EXPECT_EQ(retrieved.gen, 3);
}

TEST_F(OptionalContentGroupTest_943, MultipleSetStateCalls_943) {
    Dict dict(nullptr);
    dict.add("Type", Object(objName, "OCG"));
    dict.add("Name", Object(new GooString("MultiState")));
    
    OptionalContentGroup ocg(&dict);
    
    for (int i = 0; i < 100; ++i) {
        if (i % 2 == 0) {
            ocg.setState(OptionalContentGroup::On);
            EXPECT_EQ(ocg.getState(), OptionalContentGroup::On);
        } else {
            ocg.setState(OptionalContentGroup::Off);
            EXPECT_EQ(ocg.getState(), OptionalContentGroup::Off);
        }
    }
}

TEST_F(OptionalContentGroupTest_943, GetViewStateDefault_943) {
    Dict dict(nullptr);
    dict.add("Type", Object(objName, "OCG"));
    dict.add("Name", Object(new GooString("ViewStateTest")));
    
    OptionalContentGroup ocg(&dict);
    
    // Without usage dict, view state should have a default value
    OptionalContentGroup::UsageState vs = ocg.getViewState();
    // Just verify it returns without crashing - the exact default depends on implementation
    (void)vs;
}

TEST_F(OptionalContentGroupTest_943, GetPrintStateDefault_943) {
    Dict dict(nullptr);
    dict.add("Type", Object(objName, "OCG"));
    dict.add("Name", Object(new GooString("PrintStateTest")));
    
    OptionalContentGroup ocg(&dict);
    
    // Without usage dict, print state should have a default value
    OptionalContentGroup::UsageState ps = ocg.getPrintState();
    // Just verify it returns without crashing
    (void)ps;
}

TEST_F(OptionalContentGroupTest_943, EmptyName_943) {
    Dict dict(nullptr);
    dict.add("Type", Object(objName, "OCG"));
    dict.add("Name", Object(new GooString("")));
    
    OptionalContentGroup ocg(&dict);
    
    const GooString *name = ocg.getName();
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name->c_str(), "");
}

TEST_F(OptionalContentGroupTest_943, SetStateSameValueRepeatedly_943) {
    Dict dict(nullptr);
    dict.add("Type", Object(objName, "OCG"));
    dict.add("Name", Object(new GooString("SameState")));
    
    OptionalContentGroup ocg(&dict);
    
    ocg.setState(OptionalContentGroup::On);
    ocg.setState(OptionalContentGroup::On);
    ocg.setState(OptionalContentGroup::On);
    EXPECT_EQ(ocg.getState(), OptionalContentGroup::On);
    
    ocg.setState(OptionalContentGroup::Off);
    ocg.setState(OptionalContentGroup::Off);
    ocg.setState(OptionalContentGroup::Off);
    EXPECT_EQ(ocg.getState(), OptionalContentGroup::Off);
}

TEST_F(OptionalContentGroupTest_943, SetRefOverwrite_943) {
    Dict dict(nullptr);
    dict.add("Type", Object(objName, "OCG"));
    dict.add("Name", Object(new GooString("RefOverwrite")));
    
    OptionalContentGroup ocg(&dict);
    
    Ref ref1 = {1, 0};
    ocg.setRef(ref1);
    EXPECT_EQ(ocg.getRef().num, 1);
    
    Ref ref2 = {99, 5};
    ocg.setRef(ref2);
    EXPECT_EQ(ocg.getRef().num, 99);
    EXPECT_EQ(ocg.getRef().gen, 5);
}
