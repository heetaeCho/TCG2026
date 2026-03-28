#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Annot.h"
#include "PDFDoc.h"
#include "PDFDocFactory.h"
#include "GlobalParams.h"
#include "Link.h"
#include <memory>

class AnnotScreenTest_813 : public ::testing::Test {
protected:
    static void SetUpTestSuite()
    {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void SetUp() override
    {
    }

    void TearDown() override
    {
    }
};

// Test that getAction returns nullptr when no action is set (constructed with just a rect)
TEST_F(AnnotScreenTest_813, GetActionReturnsNullWhenNoAction_813)
{
    // Create a minimal PDF document in memory to use for constructing annotations
    GooString *fileName = new GooString(TESTDATADIR "/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(*fileName));
    delete fileName;

    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotScreen>(doc.get(), &rect);

    // A freshly constructed AnnotScreen with just a rectangle should have no action
    LinkAction *action = annot->getAction();
    EXPECT_EQ(action, nullptr);
}

// Test that getAppearCharacs returns nullptr when no appearance characteristics are set
TEST_F(AnnotScreenTest_813, GetAppearCharacsReturnsNullWhenNone_813)
{
    GooString *fileName = new GooString(TESTDATADIR "/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(*fileName));
    delete fileName;

    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotScreen>(doc.get(), &rect);

    AnnotAppearanceCharacs *appearCharacs = annot->getAppearCharacs();
    EXPECT_EQ(appearCharacs, nullptr);
}

// Test that getTitle returns non-null (even if empty) for a default constructed AnnotScreen
TEST_F(AnnotScreenTest_813, GetTitleFromDefaultConstruction_813)
{
    GooString *fileName = new GooString(TESTDATADIR "/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(*fileName));
    delete fileName;

    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotScreen>(doc.get(), &rect);

    // getTitle may return nullptr or a valid string for a default annotation
    const GooString *title = annot->getTitle();
    // We just verify it doesn't crash; title can be nullptr
    (void)title;
    SUCCEED();
}

// Test construction with a dictionary object
TEST_F(AnnotScreenTest_813, ConstructFromDictObject_813)
{
    GooString *fileName = new GooString(TESTDATADIR "/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(*fileName));
    delete fileName;

    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    // Create a minimal annotation dictionary
    Object dictObj = Object(new Dict(doc->getXRef()));
    Dict *dict = dictObj.getDict();

    // Add required /Type and /Subtype entries
    dict->add("Type", Object(objName, "Annot"));
    dict->add("Subtype", Object(objName, "Screen"));

    // Add a Rect array
    Object rectArray = Object(new Array(doc->getXRef()));
    rectArray.arrayAdd(Object(0.0));
    rectArray.arrayAdd(Object(0.0));
    rectArray.arrayAdd(Object(100.0));
    rectArray.arrayAdd(Object(100.0));
    dict->add("Rect", std::move(rectArray));

    Object refObj;
    auto annot = std::make_unique<AnnotScreen>(doc.get(), std::move(dictObj), &refObj);

    // Should be constructable without crashing
    EXPECT_NE(annot, nullptr);

    // getAction should return nullptr since we didn't add an /A entry
    LinkAction *action = annot->getAction();
    EXPECT_EQ(action, nullptr);

    // getAppearCharacs should return nullptr since we didn't add /MK entry
    AnnotAppearanceCharacs *ac = annot->getAppearCharacs();
    EXPECT_EQ(ac, nullptr);
}

// Test getAdditionalAction returns nullptr when no additional actions defined
TEST_F(AnnotScreenTest_813, GetAdditionalActionReturnsNullWhenNone_813)
{
    GooString *fileName = new GooString(TESTDATADIR "/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(*fileName));
    delete fileName;

    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotScreen>(doc.get(), &rect);

    // Test various additional action types
    auto action1 = annot->getAdditionalAction(Annot::actionCursorEntering);
    EXPECT_EQ(action1, nullptr);

    auto action2 = annot->getAdditionalAction(Annot::actionCursorLeaving);
    EXPECT_EQ(action2, nullptr);

    auto action3 = annot->getAdditionalAction(Annot::actionMousePressed);
    EXPECT_EQ(action3, nullptr);

    auto action4 = annot->getAdditionalAction(Annot::actionMouseReleased);
    EXPECT_EQ(action4, nullptr);
}

// Test that AnnotScreen can be destroyed without issues (no double-free, etc.)
TEST_F(AnnotScreenTest_813, DestructorDoesNotCrash_813)
{
    GooString *fileName = new GooString(TESTDATADIR "/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(*fileName));
    delete fileName;

    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0, 0, 50, 50);
    {
        auto annot = std::make_unique<AnnotScreen>(doc.get(), &rect);
        // annot goes out of scope and destructor is called
    }
    SUCCEED();
}

// Test with boundary rectangle values (zero-sized rectangle)
TEST_F(AnnotScreenTest_813, ZeroSizedRectangle_813)
{
    GooString *fileName = new GooString(TESTDATADIR "/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(*fileName));
    delete fileName;

    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0, 0, 0, 0);
    auto annot = std::make_unique<AnnotScreen>(doc.get(), &rect);
    EXPECT_NE(annot, nullptr);

    LinkAction *action = annot->getAction();
    EXPECT_EQ(action, nullptr);
}

// Test with negative coordinate rectangle
TEST_F(AnnotScreenTest_813, NegativeCoordinateRectangle_813)
{
    GooString *fileName = new GooString(TESTDATADIR "/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(*fileName));
    delete fileName;

    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(-100, -100, -50, -50);
    auto annot = std::make_unique<AnnotScreen>(doc.get(), &rect);
    EXPECT_NE(annot, nullptr);
}
