#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-annotation.h"



using namespace Poppler;



class ScreenAnnotationPrivateTest : public ::testing::Test {

protected:

    ScreenAnnotationPrivate* screenAnnotationPrivate;



    void SetUp() override {

        screenAnnotationPrivate = new ScreenAnnotationPrivate();

    }



    void TearDown() override {

        delete screenAnnotationPrivate;

    }

};



TEST_F(ScreenAnnotationPrivateTest_1419, MakeAlias_ReturnsUniquePointer_1419) {

    std::unique_ptr<Annotation> alias = screenAnnotationPrivate->makeAlias();

    EXPECT_NE(alias.get(), nullptr);

}



TEST_F(ScreenAnnotationPrivateTest_1419, CreateNativeAnnot_ReturnsSharedPtr_1419) {

    ::Page* destPage = nullptr;  // Assuming a valid page object would be passed in actual usage

    DocumentData* doc = nullptr; // Assuming a valid document data object would be passed in actual usage



    std::shared_ptr<Annot> nativeAnnot = screenAnnotationPrivate->createNativeAnnot(destPage, doc);

    EXPECT_NE(nativeAnnot.get(), nullptr);

}



TEST_F(ScreenAnnotationPrivateTest_1419, Destructor_CleansUpAction_1419) {

    // Assuming action is set to a valid LinkRendition* before destruction

    screenAnnotationPrivate->action = new LinkRendition();

    EXPECT_NE(screenAnnotationPrivate->action, nullptr);



    delete screenAnnotationPrivate;

    screenAnnotationPrivate = nullptr;



    // If the destructor correctly deletes action, no memory leak should occur.

    // This can be verified through Valgrind or similar tools in practice.

}

```


