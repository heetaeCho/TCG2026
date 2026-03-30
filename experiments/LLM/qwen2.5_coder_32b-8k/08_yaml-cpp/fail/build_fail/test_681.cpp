#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "nodeevents.h"

#include "node.h"



namespace YAML {

    class MockEventHandler : public EventHandler {

    public:

        MOCK_METHOD(void, OnNull, (), (override));

        MOCK_METHOD(void, OnScalar, (const std::string&), (override));

        MOCK_METHOD(void, OnSequenceStart, (const Mark&, const std::string&, EmitterStyle::value), (override));

        MOCK_METHOD(void, OnSequenceEnd, (), (override));

        MOCK_METHOD(void, OnMapStart, (const Mark&, const std::string&, EmitterStyle::value), (override));

        MOCK_METHOD(void, OnMapEnd, (), (override));

    };

}



using ::testing::_;



class NodeEventsTest_681 : public ::testing::Test {

protected:

    YAML::Node emptyNode;

    YAML::Node scalarNode;

    YAML::Node sequenceNode;

    YAML::MockEventHandler mockHandler;



    void SetUp() override {

        emptyNode = YAML::Node();

        scalarNode = YAML::Node("scalar_value");

        sequenceNode.push_back("item1");

        sequenceNode.push_back("item2");

    }

};



TEST_F(NodeEventsTest_681, EmitEmptyNode_681) {

    YAML::NodeEvents nodeEvents(emptyNode);

    EXPECT_CALL(mockHandler, OnNull()).Times(1);

    nodeEvents.Emit(mockHandler);

}



TEST_F(NodeEventsTest_681, EmitScalarNode_681) {

    YAML::NodeEvents nodeEvents(scalarNode);

    EXPECT_CALL(mockHandler, OnScalar("scalar_value")).Times(1);

    nodeEvents.Emit(mockHandler);

}



TEST_F(NodeEventsTest_681, EmitSequenceNode_681) {

    YAML::NodeEvents nodeEvents(sequenceNode);

    EXPECT_CALL(mockHandler, OnSequenceStart(_, "", EmitterStyle::Any)).Times(1);

    EXPECT_CALL(mockHandler, OnScalar("item1")).Times(1);

    EXPECT_CALL(mockHandler, OnScalar("item2")).Times(1);

    EXPECT_CALL(mockHandler, OnSequenceEnd()).Times(1);

    nodeEvents.Emit(mockHandler);

}



TEST_F(NodeEventsTest_681, EmitInvalidNode_681) {

    YAML::Node invalidNode(YAML::Zombie());

    YAML::NodeEvents nodeEvents(invalidNode);

    // Assuming an invalid node should not produce any output

    EXPECT_CALL(mockHandler, _).Times(0);

    nodeEvents.Emit(mockHandler);

}
