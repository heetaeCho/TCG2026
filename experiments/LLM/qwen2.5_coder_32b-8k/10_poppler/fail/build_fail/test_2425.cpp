#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-page.h"

#include "poppler-private.h"



class PopplerPageTest_2425 : public ::testing::Test {

protected:

    GType page_type;

    GObject* obj;



    void SetUp() override {

        // Initialize the type system

        g_type_init();

        page_type = g_type_register_static_simple(

            G_TYPE_OBJECT,

            "PopplerPage",

            sizeof(PopplerPage),

            nullptr, // class init function

            sizeof(PopplerPagePrivate), // instance size

            nullptr, // instance init function

            0);



        obj = g_object_new(page_type, nullptr);

    }



    void TearDown() override {

        g_object_unref(obj);

    }

};



TEST_F(PopplerPageTest_2425, FinalizeResetsDocumentPointer_2425) {

    PopplerPage* page = POPPLER_PAGE(obj);

    page->document = reinterpret_cast<PopplerDocument*>(g_object_new(G_TYPE_OBJECT, nullptr));



    g_object_unref(obj);



    EXPECT_EQ(page->document, nullptr);

}



TEST_F(PopplerPageTest_2425, FinalizeResetsTextPointer_2425) {

    PopplerPage* page = POPPLER_PAGE(obj);

    page->text = std::make_shared<TextPage>();



    g_object_unref(obj);



    EXPECT_EQ(page->text.get(), nullptr);

}



// Since the implementation does not indicate any external collaborators or callbacks,

// we do not need to use Google Mock for this class.

```


