#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Mocking external dependencies if necessary



// Assuming PopplerDocument and LinkOCGState are already defined as per provided headers



class PopplerActionTest : public ::testing::Test {

protected:

    // Setup code here, if needed

    PopplerDocument* document;

    PopplerAction action;



    void SetUp() override {

        document = new PopplerDocument();

        // Additional setup can be done here if required

    }



    void TearDown() override {

        delete document;

        // Cleanup code can be added here if necessary

    }

};



TEST_F(PopplerActionTest_2302, NormalOperationWithValidStateList_2302) {

    // Arrange

    std::vector<LinkOCGState::StateList> stateLists = {{

        LinkOCGState::On, {Ref(), Ref()}

    }, {

        LinkOCGState::Off, {Ref()}

    }};

    bool preserveRB = true;

    auto* mockLinkOCGState = new LinkOCGState(nullptr);

    ON_CALL(*mockLinkOCGState, getStateList()).WillByDefault(::testing::ReturnRef(stateLists));

    ON_CALL(*mockLinkOCGState, getPreserveRB()).WillByDefault(::testing::Return(preserveRB));



    // Act

    build_ocg_state(document, &action, mockLinkOCGState);



    // Assert

    EXPECT_NE(action.ocg_state.state_list, nullptr);

    GList* current = action.ocg_state.state_list;

    int count = 0;

    while (current != nullptr) {

        PopplerActionLayer* layer_action = static_cast<PopplerActionLayer*>(current->data);

        if (count == 0) {

            EXPECT_EQ(layer_action->action, POPPLER_ACTION_LAYER_ON);

            EXPECT_EQ(g_list_length(layer_action->layers), 2);

        } else if (count == 1) {

            EXPECT_EQ(layer_action->action, POPPLER_ACTION_LAYER_OFF);

            EXPECT_EQ(g_list_length(layer_action->layers), 1);

        }

        current = g_list_next(current);

        count++;

    }

    EXPECT_EQ(count, 2);



    // Cleanup

    g_list_free_full(action.ocg_state.state_list, [](gpointer data) {

        PopplerActionLayer* layer_action = static_cast<PopplerActionLayer*>(data);

        g_list_free(layer_action->layers);

        g_slice_free(PopplerActionLayer, layer_action);

    });

}



TEST_F(PopplerActionTest_2302, EmptyStateList_2302) {

    // Arrange

    std::vector<LinkOCGState::StateList> stateLists = {};

    bool preserveRB = false;

    auto* mockLinkOCGState = new LinkOCGState(nullptr);

    ON_CALL(*mockLinkOCGState, getStateList()).WillByDefault(::testing::ReturnRef(stateLists));

    ON_CALL(*mockLinkOCGState, getPreserveRB()).WillByDefault(::testing::Return(preserveRB));



    // Act

    build_ocg_state(document, &action, mockLinkOCGState);



    // Assert

    EXPECT_EQ(action.ocg_state.state_list, nullptr);

}



TEST_F(PopplerActionTest_2302, DocumentWithoutLayers_2302) {

    // Arrange

    std::vector<LinkOCGState::StateList> stateLists = {{

        LinkOCGState::Toggle, {Ref()}

    }};

    bool preserveRB = true;

    auto* mockLinkOCGState = new LinkOCGState(nullptr);

    ON_CALL(*mockLinkOCGState, getStateList()).WillByDefault(::testing::ReturnRef(stateLists));

    ON_CALL(*mockLinkOCGState, getPreserveRB()).WillByDefault(::testing::Return(preserveRB));



    // Act

    document->layers = nullptr;

    build_ocg_state(document, &action, mockLinkOCGState);



    // Assert

    EXPECT_EQ(action.ocg_state.state_list, nullptr);

}



TEST_F(PopplerActionTest_2302, DocumentWithLayers_2302) {

    // Arrange

    std::vector<LinkOCGState::StateList> stateLists = {{

        LinkOCGState::On, {Ref()}

    }};

    bool preserveRB = false;

    auto* mockLinkOCGState = new LinkOCGState(nullptr);

    ON_CALL(*mockLinkOCGState, getStateList()).WillByDefault(::testing::ReturnRef(stateLists));

    ON_CALL(*mockLinkOCGState, getPreserveRB()).WillByDefault(::testing::Return(preserveRB));



    // Act

    document->layers = new GList();

    build_ocg_state(document, &action, mockLinkOCGState);



    // Assert

    EXPECT_NE(action.ocg_state.state_list, nullptr);

    GList* current = action.ocg_state.state_list;

    while (current != nullptr) {

        PopplerActionLayer* layer_action = static_cast<PopplerActionLayer*>(current->data);

        EXPECT_EQ(layer_action->action, POPPLER_ACTION_LAYER_ON);

        EXPECT_EQ(g_list_length(layer_action->layers), 1);

        current = g_list_next(current);

    }



    // Cleanup

    g_list_free_full(action.ocg_state.state_list, [](gpointer data) {

        PopplerActionLayer* layer_action = static_cast<PopplerActionLayer*>(data);

        g_list_free(layer_action->layers);

        g_slice_free(PopplerActionLayer, layer_action);

    });

}
