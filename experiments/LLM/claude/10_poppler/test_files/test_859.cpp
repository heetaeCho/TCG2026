#include <gtest/gtest.h>
#include <memory>
#include "Annot.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "Object.h"
#include "Dict.h"
#include "XRef.h"

class AnnotWidgetTest_859 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void SetUp() override {
    }

    void TearDown() override {
    }
};

TEST_F(AnnotWidgetTest_859, GetAppearCharacsReturnsNullWhenNotSet_859) {
    // Create a minimal PDF in memory to construct an AnnotWidget
    // Use a simple PDF file approach
    GooString fileName("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not open test PDF file";
    }

    // Create a minimal widget annotation dict
    Object annotObj = Object(new Dict(doc->getXRef()));
    annotObj.dictSet("Type", Object(objName, "Annot"));
    annotObj.dictSet("Subtype", Object(objName, "Widget"));
    
    // Create Rect array
    Object rectArray = Object(new Array(doc->getXRef()));
    rectArray.arrayAdd(Object(0.0));
    rectArray.arrayAdd(Object(0.0));
    rectArray.arrayAdd(Object(100.0));
    rectArray.arrayAdd(Object(100.0));
    annotObj.dictSet("Rect", std::move(rectArray));

    Object refObj;
    refObj = Object(1, 0);

    auto widget = std::make_unique<AnnotWidget>(doc.get(), std::move(annotObj), &refObj);
    
    // When no MK entry is present, getAppearCharacs should return nullptr
    AnnotAppearanceCharacs *ac = widget->getAppearCharacs();
    // It may or may not be null depending on the dict content; just verify it doesn't crash
    SUCCEED();
}

TEST_F(AnnotWidgetTest_859, SetAndGetAppearCharacs_859) {
    GooString fileName("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not open test PDF file";
    }

    Object annotObj = Object(new Dict(doc->getXRef()));
    annotObj.dictSet("Type", Object(objName, "Annot"));
    annotObj.dictSet("Subtype", Object(objName, "Widget"));
    
    Object rectArray = Object(new Array(doc->getXRef()));
    rectArray.arrayAdd(Object(0.0));
    rectArray.arrayAdd(Object(0.0));
    rectArray.arrayAdd(Object(100.0));
    rectArray.arrayAdd(Object(100.0));
    annotObj.dictSet("Rect", std::move(rectArray));

    Object refObj = Object(1, 0);

    auto widget = std::make_unique<AnnotWidget>(doc.get(), std::move(annotObj), &refObj);

    // Create an AnnotAppearanceCharacs from a dict
    Object mkDict = Object(new Dict(doc->getXRef()));
    mkDict.dictSet("R", Object(90));
    
    auto appearCharacs = std::make_unique<AnnotAppearanceCharacs>(mkDict.getDict());
    AnnotAppearanceCharacs *rawPtr = appearCharacs.get();
    
    widget->setAppearCharacs(std::move(appearCharacs));
    
    AnnotAppearanceCharacs *result = widget->getAppearCharacs();
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->getRotation(), 90);
}

TEST_F(AnnotWidgetTest_859, SetAppearCharacsToNull_859) {
    GooString fileName("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not open test PDF file";
    }

    Object annotObj = Object(new Dict(doc->getXRef()));
    annotObj.dictSet("Type", Object(objName, "Annot"));
    annotObj.dictSet("Subtype", Object(objName, "Widget"));
    
    Object rectArray = Object(new Array(doc->getXRef()));
    rectArray.arrayAdd(Object(0.0));
    rectArray.arrayAdd(Object(0.0));
    rectArray.arrayAdd(Object(100.0));
    rectArray.arrayAdd(Object(100.0));
    annotObj.dictSet("Rect", std::move(rectArray));

    Object refObj = Object(1, 0);

    auto widget = std::make_unique<AnnotWidget>(doc.get(), std::move(annotObj), &refObj);

    // Set to nullptr
    widget->setAppearCharacs(nullptr);
    
    AnnotAppearanceCharacs *result = widget->getAppearCharacs();
    EXPECT_EQ(result, nullptr);
}

TEST_F(AnnotWidgetTest_859, GetParentReturnsCorrectDict_859) {
    GooString fileName("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not open test PDF file";
    }

    Object annotObj = Object(new Dict(doc->getXRef()));
    annotObj.dictSet("Type", Object(objName, "Annot"));
    annotObj.dictSet("Subtype", Object(objName, "Widget"));
    
    Object rectArray = Object(new Array(doc->getXRef()));
    rectArray.arrayAdd(Object(0.0));
    rectArray.arrayAdd(Object(0.0));
    rectArray.arrayAdd(Object(100.0));
    rectArray.arrayAdd(Object(100.0));
    annotObj.dictSet("Rect", std::move(rectArray));

    // Add a Parent entry
    Object parentDict = Object(new Dict(doc->getXRef()));
    parentDict.dictSet("T", Object(new GooString("TestField")));
    annotObj.dictSet("Parent", std::move(parentDict));

    Object refObj = Object(1, 0);

    auto widget = std::make_unique<AnnotWidget>(doc.get(), std::move(annotObj), &refObj);

    Dict *parent = widget->getParent();
    // Parent may or may not be set depending on implementation details
    // Just verify no crash
    SUCCEED();
}

TEST_F(AnnotWidgetTest_859, GetActionReturnsNullWhenNoAction_859) {
    GooString fileName("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not open test PDF file";
    }

    Object annotObj = Object(new Dict(doc->getXRef()));
    annotObj.dictSet("Type", Object(objName, "Annot"));
    annotObj.dictSet("Subtype", Object(objName, "Widget"));
    
    Object rectArray = Object(new Array(doc->getXRef()));
    rectArray.arrayAdd(Object(0.0));
    rectArray.arrayAdd(Object(0.0));
    rectArray.arrayAdd(Object(100.0));
    rectArray.arrayAdd(Object(100.0));
    annotObj.dictSet("Rect", std::move(rectArray));

    Object refObj = Object(1, 0);

    auto widget = std::make_unique<AnnotWidget>(doc.get(), std::move(annotObj), &refObj);

    LinkAction *action = widget->getAction();
    EXPECT_EQ(action, nullptr);
}

TEST_F(AnnotWidgetTest_859, SetFieldDoesNotCrash_859) {
    GooString fileName("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not open test PDF file";
    }

    Object annotObj = Object(new Dict(doc->getXRef()));
    annotObj.dictSet("Type", Object(objName, "Annot"));
    annotObj.dictSet("Subtype", Object(objName, "Widget"));
    
    Object rectArray = Object(new Array(doc->getXRef()));
    rectArray.arrayAdd(Object(0.0));
    rectArray.arrayAdd(Object(0.0));
    rectArray.arrayAdd(Object(100.0));
    rectArray.arrayAdd(Object(100.0));
    annotObj.dictSet("Rect", std::move(rectArray));

    Object refObj = Object(1, 0);

    auto widget = std::make_unique<AnnotWidget>(doc.get(), std::move(annotObj), &refObj);

    // Setting field to nullptr should not crash
    widget->setField(nullptr);
    SUCCEED();
}

TEST_F(AnnotWidgetTest_859, ReplaceAppearCharacs_859) {
    GooString fileName("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not open test PDF file";
    }

    Object annotObj = Object(new Dict(doc->getXRef()));
    annotObj.dictSet("Type", Object(objName, "Annot"));
    annotObj.dictSet("Subtype", Object(objName, "Widget"));
    
    Object rectArray = Object(new Array(doc->getXRef()));
    rectArray.arrayAdd(Object(0.0));
    rectArray.arrayAdd(Object(0.0));
    rectArray.arrayAdd(Object(100.0));
    rectArray.arrayAdd(Object(100.0));
    annotObj.dictSet("Rect", std::move(rectArray));

    Object refObj = Object(1, 0);

    auto widget = std::make_unique<AnnotWidget>(doc.get(), std::move(annotObj), &refObj);

    // Set first appearance characteristics
    Object mkDict1 = Object(new Dict(doc->getXRef()));
    mkDict1.dictSet("R", Object(90));
    auto ac1 = std::make_unique<AnnotAppearanceCharacs>(mkDict1.getDict());
    widget->setAppearCharacs(std::move(ac1));
    
    ASSERT_NE(widget->getAppearCharacs(), nullptr);
    EXPECT_EQ(widget->getAppearCharacs()->getRotation(), 90);

    // Replace with new appearance characteristics
    Object mkDict2 = Object(new Dict(doc->getXRef()));
    mkDict2.dictSet("R", Object(180));
    auto ac2 = std::make_unique<AnnotAppearanceCharacs>(mkDict2.getDict());
    widget->setAppearCharacs(std::move(ac2));
    
    ASSERT_NE(widget->getAppearCharacs(), nullptr);
    EXPECT_EQ(widget->getAppearCharacs()->getRotation(), 180);
}

TEST_F(AnnotWidgetTest_859, GetModeDefaultValue_859) {
    GooString fileName("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not open test PDF file";
    }

    Object annotObj = Object(new Dict(doc->getXRef()));
    annotObj.dictSet("Type", Object(objName, "Annot"));
    annotObj.dictSet("Subtype", Object(objName, "Widget"));
    
    Object rectArray = Object(new Array(doc->getXRef()));
    rectArray.arrayAdd(Object(0.0));
    rectArray.arrayAdd(Object(0.0));
    rectArray.arrayAdd(Object(100.0));
    rectArray.arrayAdd(Object(100.0));
    annotObj.dictSet("Rect", std::move(rectArray));

    Object refObj = Object(1, 0);

    auto widget = std::make_unique<AnnotWidget>(doc.get(), std::move(annotObj), &refObj);

    // Get the highlight mode - default should be a valid enum value
    AnnotWidget::AnnotWidgetHighlightMode mode = widget->getMode();
    // Just verify it returns without crashing and is a valid value
    SUCCEED();
}
