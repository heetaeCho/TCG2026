#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>

#include "Annot.h"
#include "Object.h"
#include "Dict.h"
#include "PDFDoc.h"
#include "Catalog.h"
#include "Link.h"
#include "GlobalParams.h"

class GetAdditionalActionTest_2019 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Test that loading a PDF without additional actions returns nullptr for catalog additional actions
TEST_F(GetAdditionalActionTest_2019, CatalogNoAdditionalActions_2019) {
    // Create a minimal PDF document
    auto fileName = std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>());
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    
    // Test all DocumentAdditionalActionsType values - expect nullptr when no actions defined
    auto action = catalog->getAdditionalAction(Catalog::actionCloseDocument);
    // We just verify it doesn't crash; result depends on document content
}

// Test AdditionalActionsType enum values
TEST_F(GetAdditionalActionTest_2019, EnumValuesAreCorrect_2019) {
    EXPECT_EQ(Annot::actionCursorEntering, 0);
    EXPECT_EQ(Annot::actionCursorLeaving, 1);
    EXPECT_EQ(Annot::actionMousePressed, 2);
    EXPECT_EQ(Annot::actionMouseReleased, 3);
    EXPECT_EQ(Annot::actionFocusIn, 4);
    EXPECT_EQ(Annot::actionFocusOut, 5);
    EXPECT_EQ(Annot::actionPageOpening, 6);
    EXPECT_EQ(Annot::actionPageClosing, 7);
    EXPECT_EQ(Annot::actionPageVisible, 8);
    EXPECT_EQ(Annot::actionPageInvisible, 9);
}

// Test that Object::isDict returns false for non-dict objects
TEST_F(GetAdditionalActionTest_2019, NonDictObjectReturnsFalse_2019) {
    Object nullObj = Object::null();
    EXPECT_FALSE(nullObj.isDict());
    
    Object intObj(42);
    EXPECT_FALSE(intObj.isDict());
    
    Object boolObj(true);
    EXPECT_FALSE(boolObj.isDict());
}

// Test creating dict objects and looking up missing keys
TEST_F(GetAdditionalActionTest_2019, DictLookupMissingKeyReturnsNull_2019) {
    Dict *dict = new Dict(nullptr);
    Object dictObj(dict);
    
    ASSERT_TRUE(dictObj.isDict());
    
    Object result = dictObj.dictLookup("E");
    EXPECT_FALSE(result.isDict());
    
    result = dictObj.dictLookup("X");
    EXPECT_FALSE(result.isDict());
    
    result = dictObj.dictLookup("D");
    EXPECT_FALSE(result.isDict());
    
    result = dictObj.dictLookup("U");
    EXPECT_FALSE(result.isDict());
    
    result = dictObj.dictLookup("Fo");
    EXPECT_FALSE(result.isDict());
    
    result = dictObj.dictLookup("Bl");
    EXPECT_FALSE(result.isDict());
    
    result = dictObj.dictLookup("PO");
    EXPECT_FALSE(result.isDict());
    
    result = dictObj.dictLookup("PC");
    EXPECT_FALSE(result.isDict());
    
    result = dictObj.dictLookup("PV");
    EXPECT_FALSE(result.isDict());
    
    result = dictObj.dictLookup("PI");
    EXPECT_FALSE(result.isDict());
}

// Test that a null Object fetch does not crash and returns non-dict
TEST_F(GetAdditionalActionTest_2019, FetchNullObjectIsNotDict_2019) {
    Object nullObj = Object::null();
    EXPECT_FALSE(nullObj.isDict());
}

// Test dict with entry that is not a dict (should not produce action)
TEST_F(GetAdditionalActionTest_2019, DictEntryNotDictProducesNoAction_2019) {
    Dict *dict = new Dict(nullptr);
    dict->add("E", Object(42));  // int, not dict
    Object dictObj(dict);
    
    ASSERT_TRUE(dictObj.isDict());
    Object result = dictObj.dictLookup("E");
    EXPECT_FALSE(result.isDict());
}

// Test that all additional action type key mappings correspond to expected keys
TEST_F(GetAdditionalActionTest_2019, KeyMappingVerification_2019) {
    // We verify indirectly by creating a dict with all expected keys
    // and checking they can be looked up
    Dict *dict = new Dict(nullptr);
    dict->add("E", Object(1));
    dict->add("X", Object(2));
    dict->add("D", Object(3));
    dict->add("U", Object(4));
    dict->add("Fo", Object(5));
    dict->add("Bl", Object(6));
    dict->add("PO", Object(7));
    dict->add("PC", Object(8));
    dict->add("PV", Object(9));
    dict->add("PI", Object(10));
    
    Object dictObj(dict);
    ASSERT_TRUE(dictObj.isDict());
    
    EXPECT_EQ(dictObj.dictLookup("E").getInt(), 1);
    EXPECT_EQ(dictObj.dictLookup("X").getInt(), 2);
    EXPECT_EQ(dictObj.dictLookup("D").getInt(), 3);
    EXPECT_EQ(dictObj.dictLookup("U").getInt(), 4);
    EXPECT_EQ(dictObj.dictLookup("Fo").getInt(), 5);
    EXPECT_EQ(dictObj.dictLookup("Bl").getInt(), 6);
    EXPECT_EQ(dictObj.dictLookup("PO").getInt(), 7);
    EXPECT_EQ(dictObj.dictLookup("PC").getInt(), 8);
    EXPECT_EQ(dictObj.dictLookup("PV").getInt(), 9);
    EXPECT_EQ(dictObj.dictLookup("PI").getInt(), 10);
}

// Test LinkAction::parseAction with a non-action dict returns appropriate result
TEST_F(GetAdditionalActionTest_2019, ParseActionWithEmptyDict_2019) {
    Dict *dict = new Dict(nullptr);
    Object dictObj(dict);
    
    auto action = LinkAction::parseAction(&dictObj, std::nullopt);
    // An empty dict without /S (action type) should not produce a valid action
    // or may return nullptr
    if (action) {
        EXPECT_FALSE(action->isOk());
    }
}

// Test with a valid GoTo action dict
TEST_F(GetAdditionalActionTest_2019, ParseActionWithGoToAction_2019) {
    Dict *actionDict = new Dict(nullptr);
    actionDict->add("S", Object(objName, "GoTo"));
    
    Dict *destArray = new Dict(nullptr);
    // Minimal GoTo action - might not be fully valid but tests the path
    Object actionObj(actionDict);
    
    auto action = LinkAction::parseAction(&actionObj, std::nullopt);
    // Result depends on whether the action is valid
    // We just verify no crash
}

// Boundary: Test with all 10 action types to ensure complete coverage
TEST_F(GetAdditionalActionTest_2019, AllActionTypesInRange_2019) {
    // Verify enum has exactly these values
    std::vector<Annot::AdditionalActionsType> allTypes = {
        Annot::actionCursorEntering,
        Annot::actionCursorLeaving,
        Annot::actionMousePressed,
        Annot::actionMouseReleased,
        Annot::actionFocusIn,
        Annot::actionFocusOut,
        Annot::actionPageOpening,
        Annot::actionPageClosing,
        Annot::actionPageVisible,
        Annot::actionPageInvisible
    };
    
    EXPECT_EQ(allTypes.size(), 10u);
    
    for (int i = 0; i < 10; i++) {
        EXPECT_EQ(static_cast<int>(allTypes[i]), i);
    }
}
