#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Form.h"

#include <memory>



using namespace std;



class FormFieldTextTest_903 : public ::testing::Test {

protected:

    PDFDoc* docA = nullptr;

    Object dictObj;

    Ref ref;

    FormField* parent = nullptr;

    set<int>* usedParents = nullptr;



    void SetUp() override {

        // Initialize necessary objects for the tests

        docA = new PDFDoc();

        usedParents = new set<int>();

    }



    void TearDown() override {

        delete docA;

        delete usedParents;

    }

};



TEST_F(FormFieldTextTest_903, GetAppearanceContent_NormalOperation_903) {

    FormFieldText field(docA, move(dictObj), ref, parent, *usedParents);

    const GooString* content = field.getAppearanceContent();

    EXPECT_TRUE(content != nullptr);  // Assuming default constructed object has some non-null content

}



TEST_F(FormFieldTextTest_903, GetAppearanceContent_InternalContentSet_903) {

    FormFieldText field(docA, move(dictObj), ref, parent, *usedParents);

    auto internal_content = make_unique<GooString>("internal");

    field.setAppearanceContent(move(internal_content));

    const GooString* content = field.getAppearanceContent();

    EXPECT_STREQ(content->getCString(), "internal");

}



TEST_F(FormFieldTextTest_903, GetAppearanceContent_DefaultContentUsed_903) {

    FormFieldText field(docA, move(dictObj), ref, parent, *usedParents);

    auto default_content = make_unique<GooString>("default");

    field.setContent(move(default_content));

    const GooString* content = field.getAppearanceContent();

    EXPECT_STREQ(content->getCString(), "default");

}



TEST_F(FormFieldTextTest_903, GetAppearanceContent_NoContentSet_903) {

    FormFieldText field(docA, move(dictObj), ref, parent, *usedParents);

    const GooString* content = field.getAppearanceContent();

    EXPECT_TRUE(content != nullptr);  // Assuming default constructed object has some non-null content

}



TEST_F(FormFieldTextTest_903, SetAndGetAppearanceContent_BoundaryCondition_903) {

    FormFieldText field(docA, move(dictObj), ref, parent, *usedParents);

    auto empty_content = make_unique<GooString>("");

    field.setAppearanceContent(move(empty_content));

    const GooString* content = field.getAppearanceContent();

    EXPECT_STREQ(content->getCString(), "");

}



TEST_F(FormFieldTextTest_903, SetAndGetAppearanceContent_ExceptionalCase_903) {

    FormFieldText field(docA, move(dictObj), ref, parent, *usedParents);

    auto long_content = make_unique<GooString>("a".append(10000, 'b')); // Large content

    field.setAppearanceContent(move(long_content));

    const GooString* content = field.getAppearanceContent();

    EXPECT_STREQ(content->getCString(), "a".append(10000, 'b').c_str());

}
