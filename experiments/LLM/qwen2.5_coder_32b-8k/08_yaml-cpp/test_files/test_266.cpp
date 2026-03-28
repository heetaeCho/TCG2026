#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "eventhandler.h"

#include "nodeevents.h"



using namespace YAML;

using ::testing::_;

using ::testing::InSequence;



class MockEventHandler : public EventHandler {

public:

    MOCK_METHOD(void, OnDocumentStart, (const Mark & mark), (override));

    MOCK_METHOD(void, OnDocumentEnd, (), (override));

    MOCK_METHOD(void, OnNull, (const Mark & mark, anchor_t anchor), (override));

    MOCK_METHOD(void, OnAlias, (const Mark & mark, anchor_t anchor), (override));

    MOCK_METHOD(void, OnScalar, (const Mark & mark, const std::string & tag, anchor_t anchor, const std::string & value), (override));

    MOCK_METHOD(void, OnSequenceStart, (const Mark & mark, const std::string & tag, anchor_t anchor, EmitterStyle::value style), (override));

    MOCK_METHOD(void, OnSequenceEnd, (), (override));

    MOCK_METHOD(void, OnMapStart, (const Mark & mark, const std::string & tag, anchor_t anchor, EmitterStyle::value style), (override));

    MOCK_METHOD(void, OnMapEnd, (), (override));

};



class NodeEventsTest_266 : public ::testing::Test {

protected:

    MockEventHandler mock_handler;

    Node dummy_node;  // Assuming there's a way to create a dummy node for testing

    NodeEvents node_events;



    NodeEventsTest_266() : node_events(dummy_node) {}

};



TEST_F(NodeEventsTest_266, EmitCallsDocumentStartAndEnd_266) {

    EXPECT_CALL(mock_handler, OnDocumentStart(_)).Times(1);

    EXPECT_CALL(mock_handler, OnDocumentEnd()).Times(1);



    node_events.Emit(mock_handler);

}



TEST_F(NodeEventsTest_266, EmitDoesNotCallOtherMethodsWhenRootIsNull_266) {

    NodeEvents empty_node_events(Node());  // Assuming Node() creates a null node



    EXPECT_CALL(mock_handler, OnDocumentStart(_)).Times(1);

    EXPECT_CALL(mock_handler, OnDocumentEnd()).Times(1);

    EXPECT_CALL(mock_handler, OnNull(_, _)).Times(0);

    EXPECT_CALL(mock_handler, OnAlias(_, _)).Times(0);

    EXPECT_CALL(mock_handler, OnScalar(_, _, _, _)).Times(0);

    EXPECT_CALL(mock_handler, OnSequenceStart(_, _, _, _)).Times(0);

    EXPECT_CALL(mock_handler, OnSequenceEnd()).Times(0);

    EXPECT_CALL(mock_handler, OnMapStart(_, _, _, _)).Times(0);

    EXPECT_CALL(mock_handler, OnMapEnd()).Times(0);



    empty_node_events.Emit(mock_handler);

}



TEST_F(NodeEventsTest_266, EmitHandlesNormalNode_266) {

    // Assuming dummy_node is a valid node that emits some events

    InSequence seq;



    EXPECT_CALL(mock_handler, OnDocumentStart(_)).Times(1);

    EXPECT_CALL(mock_handler, OnScalar(_, _, _, _)).Times(1);  // Example of expected calls based on the normal operation

    EXPECT_CALL(mock_handler, OnDocumentEnd()).Times(1);



    node_events.Emit(mock_handler);

}



// Additional tests could be added for more specific scenarios or edge cases if needed
