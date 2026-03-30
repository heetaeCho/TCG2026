// TEST_ID: 266
#include <stdexcept>
#include <string>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "yaml-cpp/yaml.h"          // YAML::Node
#include "yaml-cpp/eventhandler.h"  // YAML::EventHandler
#include "nodeevents.h"             // YAML::NodeEvents (project-local)

using ::testing::_;
using ::testing::InSequence;
using ::testing::NiceMock;
using ::testing::Sequence;
using ::testing::StrictMock;

namespace YAML {

class MockEventHandler_266 : public EventHandler {
 public:
  MOCK_METHOD(void, OnDocumentStart, (const Mark& mark), (override));
  MOCK_METHOD(void, OnDocumentEnd, (), (override));

  MOCK_METHOD(void, OnNull, (const Mark& mark, anchor_t anchor), (override));
  MOCK_METHOD(void, OnAlias, (const Mark& mark, anchor_t anchor), (override));
  MOCK_METHOD(void,
              OnScalar,
              (const Mark& mark, const std::string& tag, anchor_t anchor,
               const std::string& value),
              (override));
  MOCK_METHOD(void,
              OnSequenceStart,
              (const Mark& mark, const std::string& tag, anchor_t anchor,
               EmitterStyle::value style),
              (override));
  MOCK_METHOD(void, OnSequenceEnd, (), (override));
  MOCK_METHOD(void,
              OnMapStart,
              (const Mark& mark, const std::string& tag, anchor_t anchor,
               EmitterStyle::value style),
              (override));
  MOCK_METHOD(void, OnMapEnd, (), (override));

  MOCK_METHOD(void, OnAnchor, (const Mark& mark, const std::string& anchor_name), (override));
};

class NodeEventsTest_266 : public ::testing::Test {};

TEST_F(NodeEventsTest_266, EmitCallsDocumentStartThenDocumentEnd_266) {
  YAML::Node node("hello");
  YAML::NodeEvents events(node);

  StrictMock<MockEventHandler_266> handler;

  Sequence s;
  EXPECT_CALL(handler, OnDocumentStart(_)).InSequence(s);
  EXPECT_CALL(handler, OnDocumentEnd()).InSequence(s);

  // Allow other event callbacks (content emission) without pinning their exact shape here.
  EXPECT_CALL(handler, OnNull(_, _)).Times(::testing::AnyNumber());
  EXPECT_CALL(handler, OnAlias(_, _)).Times(::testing::AnyNumber());
  EXPECT_CALL(handler, OnScalar(_, _, _, _)).Times(::testing::AnyNumber());
  EXPECT_CALL(handler, OnSequenceStart(_, _, _, _)).Times(::testing::AnyNumber());
  EXPECT_CALL(handler, OnSequenceEnd()).Times(::testing::AnyNumber());
  EXPECT_CALL(handler, OnMapStart(_, _, _, _)).Times(::testing::AnyNumber());
  EXPECT_CALL(handler, OnMapEnd()).Times(::testing::AnyNumber());
  EXPECT_CALL(handler, OnAnchor(_, _)).Times(::testing::AnyNumber());

  events.Emit(handler);
}

TEST_F(NodeEventsTest_266, EmitOnDefaultConstructedNodeCallsDocumentMarkers_266) {
  // Boundary-ish: a default-constructed node may have no underlying root pointer.
  YAML::Node node;
  YAML::NodeEvents events(node);

  StrictMock<MockEventHandler_266> handler;

  EXPECT_CALL(handler, OnDocumentStart(_)).Times(1);
  EXPECT_CALL(handler, OnDocumentEnd()).Times(1);

  // If there is no root, no other callbacks should be observable.
  EXPECT_CALL(handler, OnNull(_, _)).Times(0);
  EXPECT_CALL(handler, OnAlias(_, _)).Times(0);
  EXPECT_CALL(handler, OnScalar(_, _, _, _)).Times(0);
  EXPECT_CALL(handler, OnSequenceStart(_, _, _, _)).Times(0);
  EXPECT_CALL(handler, OnSequenceEnd()).Times(0);
  EXPECT_CALL(handler, OnMapStart(_, _, _, _)).Times(0);
  EXPECT_CALL(handler, OnMapEnd()).Times(0);
  EXPECT_CALL(handler, OnAnchor(_, _)).Times(0);

  events.Emit(handler);
}

TEST_F(NodeEventsTest_266, EmitForScalarNodeEmitsScalarValue_266) {
  YAML::Node node("hello");
  YAML::NodeEvents events(node);

  StrictMock<MockEventHandler_266> handler;

  Sequence s;
  EXPECT_CALL(handler, OnDocumentStart(_)).InSequence(s);
  EXPECT_CALL(handler, OnScalar(_, _, _, "hello")).Times(1).InSequence(s);
  EXPECT_CALL(handler, OnDocumentEnd()).InSequence(s);

  // No requirement to emit other event types for a scalar.
  EXPECT_CALL(handler, OnNull(_, _)).Times(0);
  EXPECT_CALL(handler, OnAlias(_, _)).Times(0);
  EXPECT_CALL(handler, OnSequenceStart(_, _, _, _)).Times(0);
  EXPECT_CALL(handler, OnSequenceEnd()).Times(0);
  EXPECT_CALL(handler, OnMapStart(_, _, _, _)).Times(0);
  EXPECT_CALL(handler, OnMapEnd()).Times(0);
  EXPECT_CALL(handler, OnAnchor(_, _)).Times(::testing::AnyNumber());

  events.Emit(handler);
}

TEST_F(NodeEventsTest_266, EmitForSequenceNodeEmitsSequenceStartItemsAndEnd_266) {
  YAML::Node node(YAML::NodeType::Sequence);
  node.push_back("a");
  node.push_back("b");
  YAML::NodeEvents events(node);

  StrictMock<MockEventHandler_266> handler;

  Sequence s;
  EXPECT_CALL(handler, OnDocumentStart(_)).InSequence(s);
  EXPECT_CALL(handler, OnSequenceStart(_, _, _, _)).Times(1).InSequence(s);
  EXPECT_CALL(handler, OnScalar(_, _, _, "a")).Times(1).InSequence(s);
  EXPECT_CALL(handler, OnScalar(_, _, _, "b")).Times(1).InSequence(s);
  EXPECT_CALL(handler, OnSequenceEnd()).Times(1).InSequence(s);
  EXPECT_CALL(handler, OnDocumentEnd()).InSequence(s);

  EXPECT_CALL(handler, OnNull(_, _)).Times(0);
  EXPECT_CALL(handler, OnAlias(_, _)).Times(0);
  EXPECT_CALL(handler, OnMapStart(_, _, _, _)).Times(0);
  EXPECT_CALL(handler, OnMapEnd()).Times(0);
  EXPECT_CALL(handler, OnAnchor(_, _)).Times(::testing::AnyNumber());

  events.Emit(handler);
}

TEST_F(NodeEventsTest_266, EmitPropagatesExceptionFromHandler_266) {
  class ThrowingHandler : public YAML::EventHandler {
   public:
    void OnDocumentStart(const YAML::Mark&) override { throw std::runtime_error("boom"); }
  };

  YAML::Node node("x");
  YAML::NodeEvents events(node);

  ThrowingHandler handler;
  EXPECT_THROW(events.Emit(handler), std::runtime_error);
}

}  // namespace YAML