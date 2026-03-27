#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-document.h"



// Mock class for PopplerDocument to verify reference counting behavior if needed.

class MockPopplerDocument {

public:

    MOCK_METHOD(void, ref, (), (const));

};



TEST(PopplerLayersIterCopyTest_2246, CopyNonNullIterator_2246) {

    // Arrange

    PopplerLayersIter iter;

    iter.document = reinterpret_cast<PopplerDocument*>(new MockPopplerDocument());



    // Act

    PopplerLayersIter* new_iter = poppler_layers_iter_copy(&iter);



    // Assert

    EXPECT_NE(new_iter, nullptr);

    EXPECT_EQ(new_iter->document, iter.document);



    // Cleanup

    g_object_unref(new_iter->document);

    delete reinterpret_cast<MockPopplerDocument*>(iter.document);

    g_slice_free(PopplerLayersIter, new_iter);

}



TEST(PopplerLayersIterCopyTest_2246, CopyNullIteratorReturnsNull_2246) {

    // Arrange

    PopplerLayersIter* iter = nullptr;



    // Act

    PopplerLayersIter* new_iter = poppler_layers_iter_copy(iter);



    // Assert

    EXPECT_EQ(new_iter, nullptr);

}



// Assuming g_object_ref increments a reference count and we can mock that behavior.

TEST(PopplerLayersIterCopyTest_2246, DocumentRefCalledOnce_2246) {

    // Arrange

    MockPopplerDocument* mock_doc = new MockPopplerDocument();

    EXPECT_CALL(*mock_doc, ref()).Times(1);



    PopplerLayersIter iter;

    iter.document = reinterpret_cast<PopplerDocument*>(mock_doc);



    // Act

    poppler_layers_iter_copy(&iter);



    // Cleanup

    g_object_unref(iter.document);

    delete mock_doc;

}
