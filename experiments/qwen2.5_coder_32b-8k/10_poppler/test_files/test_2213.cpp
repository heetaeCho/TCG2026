#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-document.h"

#include "poppler-private.h"



class PopplerIndexIterTest_2213 : public ::testing::Test {

protected:

    void SetUp() override {

        document = reinterpret_cast<PopplerDocument*>(g_slice_new(PopplerDocument));

        document->doc = new Outline(); // Assuming Outline is a class that provides getOutline and getItems methods

        document->initer = 0;

        document->layers_rbgroups = nullptr;

        document->output_dev = nullptr;



        outline = document->doc; // Direct access to outline for test setup

    }



    void TearDown() override {

        g_object_unref(document);

        delete document->doc;

        g_slice_free(PopplerDocument, document);

    }



    PopplerDocument* document;

    Outline* outline;

};



TEST_F(PopplerIndexIterTest_2213, NewIteratorWithNonEmptyOutline_2213) {

    // Arrange

    std::vector<OutlineItem*> items = { new OutlineItem(), new OutlineItem() };

    EXPECT_CALL(*outline, getItems()).WillOnce(testing::Return(&items));



    // Act

    PopplerIndexIter* iter = poppler_index_iter_new(document);



    // Assert

    ASSERT_NE(iter, nullptr);

    EXPECT_EQ(iter->index, 0u);

    EXPECT_EQ(iter->items, &items);

    g_slice_free(PopplerIndexIter, iter);

}



TEST_F(PopplerIndexIterTest_2213, NewIteratorWithEmptyOutline_2213) {

    // Arrange

    std::vector<OutlineItem*> items;

    EXPECT_CALL(*outline, getItems()).WillOnce(testing::Return(&items));



    // Act

    PopplerIndexIter* iter = poppler_index_iter_new(document);



    // Assert

    ASSERT_EQ(iter, nullptr);

}



TEST_F(PopplerIndexIterTest_2213, NewIteratorWithNullOutline_2213) {

    // Arrange

    document->doc = nullptr;



    // Act

    PopplerIndexIter* iter = poppler_index_iter_new(document);



    // Assert

    ASSERT_EQ(iter, nullptr);

}



TEST_F(PopplerIndexIterTest_2213, NewIteratorWithNullItems_2213) {

    // Arrange

    EXPECT_CALL(*outline, getItems()).WillOnce(testing::Return(nullptr));



    // Act

    PopplerIndexIter* iter = poppler_index_iter_new(document);



    // Assert

    ASSERT_EQ(iter, nullptr);

}
