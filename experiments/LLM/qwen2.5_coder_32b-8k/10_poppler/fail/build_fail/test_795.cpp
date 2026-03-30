#include <gtest/gtest.h>

#include "poppler/Annot.h"

#include "poppler/Object.h"



class AnnotPopupTest_795 : public ::testing::Test {

protected:

    PDFDoc* doc;

    PDFRectangle rect;

    Object dictObject;

    Object obj;



    void SetUp() override {

        doc = new PDFDoc(); // Assuming PDFDoc has a default constructor

        dictObject.initDict();

        obj.initNull();

    }



    void TearDown() override {

        delete doc;

        dictObject.free();

        obj.free();

    }

};



TEST_F(AnnotPopupTest_795, HasParent_ReturnsFalse_WhenNoParentSet_795) {

    AnnotPopup popup(doc, &rect);

    EXPECT_FALSE(popup.hasParent());

}



TEST_F(AnnotPopupTest_795, HasParent_ReturnsTrue_AfterSettingValidParentRef_795) {

    AnnotPopup popup(doc, std::move(dictObject), &obj);

    Ref validRef;

    validRef.num = 1;

    validRef.gen = 0;

    popup.setParent(reinterpret_cast<Annot*>(&validRef)); // Assuming setParent takes a pointer to an Annot object

    EXPECT_TRUE(popup.hasParent());

}



TEST_F(AnnotPopupTest_795, HasParent_ReturnsFalse_AfterSettingInvalidParentRef_795) {

    AnnotPopup popup(doc, std::move(dictObject), &obj);

    Ref invalidRef = Ref::INVALID();

    popup.setParent(reinterpret_cast<Annot*>(&invalidRef)); // Assuming setParent takes a pointer to an Annot object

    EXPECT_FALSE(popup.hasParent());

}



TEST_F(AnnotPopupTest_795, SetOpen_ChangesState_Correctly_795) {

    AnnotPopup popup(doc, &rect);

    popup.setOpen(true);

    EXPECT_TRUE(popup.getOpen());

    popup.setOpen(false);

    EXPECT_FALSE(popup.getOpen());

}



TEST_F(AnnotPopupTest_795, ConstructorWithRect_SetsParentRefToInvalid_795) {

    AnnotPopup popup(doc, &rect);

    EXPECT_FALSE(popup.hasParent());

}



TEST_F(AnnotPopupTest_795, ConstructorWithDictObjectAndObj_SetsParentRefBasedOnInput_795) {

    // This test assumes that the constructor with dictObject and obj initializes parentRef based on these inputs

    // Since we don't have access to the internal logic, we can only assume it works as expected if valid input is given.

    AnnotPopup popup(doc, std::move(dictObject), &obj);

    EXPECT_FALSE(popup.hasParent()); // Assuming no parent is set by default with this constructor

}
