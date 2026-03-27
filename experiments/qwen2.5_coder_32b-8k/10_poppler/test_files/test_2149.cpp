#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-document.cc"

#include "poppler-private.h"



// Mocking CairoOutputDev for any potential future interactions

class MockCairoOutputDev {

public:

    MOCK_METHOD(void, someMethod, (), ());

};



// Test Fixture for PopplerDocument tests

class PopplerDocumentTest_2149 : public ::testing::Test {

protected:

    void SetUp() override {

        document = new PopplerDocument();

        document->output_dev = new MockCairoOutputDev();

    }



    void TearDown() override {

        delete document;

    }



    PopplerDocument* document;

};



// Test case to verify that the finalize method correctly frees layers

TEST_F(PopplerDocumentTest_2149, FinalizeFreesLayers_2149) {

    // Assuming poppler_document_layers_free is a function that sets layers_rbgroups to nullptr or similar

    document->layers_rbgroups = new int[10];  // Simulate allocation of layers

    EXPECT_NE(document->layers_rbgroups, nullptr);



    G_OBJECT_CLASS(poppler_document_parent_class)->finalize(reinterpret_cast<GObject*>(document));



    EXPECT_EQ(document->layers_rbgroups, nullptr);

}



// Test case to verify that the finalize method correctly deletes output_dev

TEST_F(PopplerDocumentTest_2149, FinalizeDeletesOutputDev_2149) {

    MockCairoOutputDev* mock_output_dev = new MockCairoOutputDev();

    document->output_dev = mock_output_dev;



    EXPECT_CALL(*mock_output_dev, someMethod()).Times(0);  // Ensure no method is called on output_dev before deletion



    G_OBJECT_CLASS(poppler_document_parent_class)->finalize(reinterpret_cast<GObject*>(document));



    // Since output_dev is deleted in the finalize method, we cannot directly verify it.

    // We ensure that no further interactions occur with output_dev after deletion.

}



// Test case to verify that the finalize method correctly resets doc

TEST_F(PopplerDocumentTest_2149, FinalizeResetsDoc_2149) {

    document->doc = std::make_unique<int>(42);  // Simulate initialization of doc



    G_OBJECT_CLASS(poppler_document_parent_class)->finalize(reinterpret_cast<GObject*>(document));



    EXPECT_FALSE(document->doc);

}



// Test case to verify that the finalize method correctly resets initer

TEST_F(PopplerDocumentTest_2149, FinalizeResetsIniter_2149) {

    document->initer = std::make_unique<int>(42);  // Simulate initialization of initer



    G_OBJECT_CLASS(poppler_document_parent_class)->finalize(reinterpret_cast<GObject*>(document));



    EXPECT_FALSE(document->initer);

}



// Test case to verify that the finalize method correctly calls parent finalize

TEST_F(PopplerDocumentTest_2149, FinalizeCallsParentFinalize_2149) {

    bool parent_finalize_called = false;

    auto original_parent_finalize = poppler_document_parent_class->finalize;



    poppler_document_parent_class->finalize = [](GObject* object) {

        parent_finalize_called = true;

        if (original_parent_finalize)

            original_parent_finalize(object);

    };



    G_OBJECT_CLASS(poppler_document_parent_class)->finalize(reinterpret_cast<GObject*>(document));



    EXPECT_TRUE(parent_finalize_called);



    // Restore the original finalize method

    poppler_document_parent_class->finalize = original_parent_finalize;

}
