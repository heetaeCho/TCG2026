#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/emitfromevents.h"
#include "yaml-cpp/emitter.h"

namespace YAML {
namespace {

class EmitFromEventsTest_61 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test basic document start and end
TEST_F(EmitFromEventsTest_61, DocumentStartAndEnd_61) {
  Emitter emitter;
  EmitFromEvents handler(emitter);
  Mark mark;
  handler.OnDocumentStart(mark);
  handler.OnNull(mark, 0);
  handler.OnDocumentEnd();
  EXPECT_TRUE(emitter.good());
}

// Test emitting a scalar value
TEST_F(EmitFromEventsTest_61, ScalarValue_61) {
  Emitter emitter;
  EmitFromEvents handler(emitter);
  Mark mark;
  handler.OnDocumentStart(mark);
  handler.OnScalar(mark, "", 0, "hello");
  handler.OnDocumentEnd();
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("hello"), std::string::npos);
}

// Test emitting a null value
TEST_F(EmitFromEventsTest_61, NullValue_61) {
  Emitter emitter;
  EmitFromEvents handler(emitter);
  Mark mark;
  handler.OnDocumentStart(mark);
  handler.OnNull(mark, 0);
  handler.OnDocumentEnd();
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("~"), std::string::npos);
}

// Test emitting a simple sequence
TEST_F(EmitFromEventsTest_61, SimpleSequence_61) {
  Emitter emitter;
  EmitFromEvents handler(emitter);
  Mark mark;
  handler.OnDocumentStart(mark);
  handler.OnSequenceStart(mark, "", 0, EmitterStyle::Block);
  handler.OnScalar(mark, "", 0, "item1");
  handler.OnScalar(mark, "", 0, "item2");
  handler.OnSequenceEnd();
  handler.OnDocumentEnd();
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("item1"), std::string::npos);
  EXPECT_NE(output.find("item2"), std::string::npos);
}

// Test emitting a flow sequence
TEST_F(EmitFromEventsTest_61, FlowSequence_61) {
  Emitter emitter;
  EmitFromEvents handler(emitter);
  Mark mark;
  handler.OnDocumentStart(mark);
  handler.OnSequenceStart(mark, "", 0, EmitterStyle::Flow);
  handler.OnScalar(mark, "", 0, "a");
  handler.OnScalar(mark, "", 0, "b");
  handler.OnSequenceEnd();
  handler.OnDocumentEnd();
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("a"), std::string::npos);
  EXPECT_NE(output.find("b"), std::string::npos);
}

// Test emitting a simple map
TEST_F(EmitFromEventsTest_61, SimpleMap_61) {
  Emitter emitter;
  EmitFromEvents handler(emitter);
  Mark mark;
  handler.OnDocumentStart(mark);
  handler.OnMapStart(mark, "", 0, EmitterStyle::Block);
  handler.OnScalar(mark, "", 0, "key");
  handler.OnScalar(mark, "", 0, "value");
  handler.OnMapEnd();
  handler.OnDocumentEnd();
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("key"), std::string::npos);
  EXPECT_NE(output.find("value"), std::string::npos);
}

// Test emitting a flow map
TEST_F(EmitFromEventsTest_61, FlowMap_61) {
  Emitter emitter;
  EmitFromEvents handler(emitter);
  Mark mark;
  handler.OnDocumentStart(mark);
  handler.OnMapStart(mark, "", 0, EmitterStyle::Flow);
  handler.OnScalar(mark, "", 0, "key");
  handler.OnScalar(mark, "", 0, "value");
  handler.OnMapEnd();
  handler.OnDocumentEnd();
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("key"), std::string::npos);
  EXPECT_NE(output.find("value"), std::string::npos);
}

// Test nested sequence in map
TEST_F(EmitFromEventsTest_61, NestedSequenceInMap_61) {
  Emitter emitter;
  EmitFromEvents handler(emitter);
  Mark mark;
  handler.OnDocumentStart(mark);
  handler.OnMapStart(mark, "", 0, EmitterStyle::Block);
  handler.OnScalar(mark, "", 0, "list");
  handler.OnSequenceStart(mark, "", 0, EmitterStyle::Block);
  handler.OnScalar(mark, "", 0, "item1");
  handler.OnScalar(mark, "", 0, "item2");
  handler.OnSequenceEnd();
  handler.OnMapEnd();
  handler.OnDocumentEnd();
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("list"), std::string::npos);
  EXPECT_NE(output.find("item1"), std::string::npos);
}

// Test nested map in map
TEST_F(EmitFromEventsTest_61, NestedMapInMap_61) {
  Emitter emitter;
  EmitFromEvents handler(emitter);
  Mark mark;
  handler.OnDocumentStart(mark);
  handler.OnMapStart(mark, "", 0, EmitterStyle::Block);
  handler.OnScalar(mark, "", 0, "outer");
  handler.OnMapStart(mark, "", 0, EmitterStyle::Block);
  handler.OnScalar(mark, "", 0, "inner_key");
  handler.OnScalar(mark, "", 0, "inner_value");
  handler.OnMapEnd();
  handler.OnMapEnd();
  handler.OnDocumentEnd();
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("outer"), std::string::npos);
  EXPECT_NE(output.find("inner_key"), std::string::npos);
  EXPECT_NE(output.find("inner_value"), std::string::npos);
}

// Test nested map in sequence
TEST_F(EmitFromEventsTest_61, NestedMapInSequence_61) {
  Emitter emitter;
  EmitFromEvents handler(emitter);
  Mark mark;
  handler.OnDocumentStart(mark);
  handler.OnSequenceStart(mark, "", 0, EmitterStyle::Block);
  handler.OnMapStart(mark, "", 0, EmitterStyle::Block);
  handler.OnScalar(mark, "", 0, "key");
  handler.OnScalar(mark, "", 0, "value");
  handler.OnMapEnd();
  handler.OnSequenceEnd();
  handler.OnDocumentEnd();
  EXPECT_TRUE(emitter.good());
}

// Test empty sequence
TEST_F(EmitFromEventsTest_61, EmptySequence_61) {
  Emitter emitter;
  EmitFromEvents handler(emitter);
  Mark mark;
  handler.OnDocumentStart(mark);
  handler.OnSequenceStart(mark, "", 0, EmitterStyle::Flow);
  handler.OnSequenceEnd();
  handler.OnDocumentEnd();
  EXPECT_TRUE(emitter.good());
}

// Test empty map
TEST_F(EmitFromEventsTest_61, EmptyMap_61) {
  Emitter emitter;
  EmitFromEvents handler(emitter);
  Mark mark;
  handler.OnDocumentStart(mark);
  handler.OnMapStart(mark, "", 0, EmitterStyle::Flow);
  handler.OnMapEnd();
  handler.OnDocumentEnd();
  EXPECT_TRUE(emitter.good());
}

// Test scalar with tag
TEST_F(EmitFromEventsTest_61, ScalarWithTag_61) {
  Emitter emitter;
  EmitFromEvents handler(emitter);
  Mark mark;
  handler.OnDocumentStart(mark);
  handler.OnScalar(mark, "!mytag", 0, "tagged_value");
  handler.OnDocumentEnd();
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("tagged_value"), std::string::npos);
  EXPECT_NE(output.find("!mytag"), std::string::npos);
}

// Test scalar with anchor
TEST_F(EmitFromEventsTest_61, ScalarWithAnchor_61) {
  Emitter emitter;
  EmitFromEvents handler(emitter);
  Mark mark;
  handler.OnDocumentStart(mark);
  handler.OnScalar(mark, "", 1, "anchored_value");
  handler.OnDocumentEnd();
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("anchored_value"), std::string::npos);
}

// Test alias
TEST_F(EmitFromEventsTest_61, Alias_61) {
  Emitter emitter;
  EmitFromEvents handler(emitter);
  Mark mark;
  handler.OnDocumentStart(mark);
  handler.OnSequenceStart(mark, "", 0, EmitterStyle::Block);
  handler.OnScalar(mark, "", 1, "value");
  handler.OnAlias(mark, 1);
  handler.OnSequenceEnd();
  handler.OnDocumentEnd();
  EXPECT_TRUE(emitter.good());
}

// Test emitting empty string scalar
TEST_F(EmitFromEventsTest_61, EmptyStringScalar_61) {
  Emitter emitter;
  EmitFromEvents handler(emitter);
  Mark mark;
  handler.OnDocumentStart(mark);
  handler.OnScalar(mark, "", 0, "");
  handler.OnDocumentEnd();
  EXPECT_TRUE(emitter.good());
}

// Test multiple scalar entries in a sequence
TEST_F(EmitFromEventsTest_61, MultipleScalarsInSequence_61) {
  Emitter emitter;
  EmitFromEvents handler(emitter);
  Mark mark;
  handler.OnDocumentStart(mark);
  handler.OnSequenceStart(mark, "", 0, EmitterStyle::Block);
  for (int i = 0; i < 10; i++) {
    handler.OnScalar(mark, "", 0, "item" + std::to_string(i));
  }
  handler.OnSequenceEnd();
  handler.OnDocumentEnd();
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  for (int i = 0; i < 10; i++) {
    EXPECT_NE(output.find("item" + std::to_string(i)), std::string::npos);
  }
}

// Test sequence with tag
TEST_F(EmitFromEventsTest_61, SequenceWithTag_61) {
  Emitter emitter;
  EmitFromEvents handler(emitter);
  Mark mark;
  handler.OnDocumentStart(mark);
  handler.OnSequenceStart(mark, "!myseq", 0, EmitterStyle::Block);
  handler.OnScalar(mark, "", 0, "item");
  handler.OnSequenceEnd();
  handler.OnDocumentEnd();
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("!myseq"), std::string::npos);
}

// Test map with tag
TEST_F(EmitFromEventsTest_61, MapWithTag_61) {
  Emitter emitter;
  EmitFromEvents handler(emitter);
  Mark mark;
  handler.OnDocumentStart(mark);
  handler.OnMapStart(mark, "!mymap", 0, EmitterStyle::Block);
  handler.OnScalar(mark, "", 0, "key");
  handler.OnScalar(mark, "", 0, "value");
  handler.OnMapEnd();
  handler.OnDocumentEnd();
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("!mymap"), std::string::npos);
}

// Test deeply nested structure
TEST_F(EmitFromEventsTest_61, DeeplyNestedStructure_61) {
  Emitter emitter;
  EmitFromEvents handler(emitter);
  Mark mark;
  handler.OnDocumentStart(mark);
  handler.OnSequenceStart(mark, "", 0, EmitterStyle::Block);
  handler.OnSequenceStart(mark, "", 0, EmitterStyle::Block);
  handler.OnSequenceStart(mark, "", 0, EmitterStyle::Block);
  handler.OnScalar(mark, "", 0, "deep");
  handler.OnSequenceEnd();
  handler.OnSequenceEnd();
  handler.OnSequenceEnd();
  handler.OnDocumentEnd();
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("deep"), std::string::npos);
}

// Test null in a map value
TEST_F(EmitFromEventsTest_61, NullInMapValue_61) {
  Emitter emitter;
  EmitFromEvents handler(emitter);
  Mark mark;
  handler.OnDocumentStart(mark);
  handler.OnMapStart(mark, "", 0, EmitterStyle::Block);
  handler.OnScalar(mark, "", 0, "key");
  handler.OnNull(mark, 0);
  handler.OnMapEnd();
  handler.OnDocumentEnd();
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("key"), std::string::npos);
}

// Test multiple key-value pairs in a map
TEST_F(EmitFromEventsTest_61, MultipleKeyValuePairsInMap_61) {
  Emitter emitter;
  EmitFromEvents handler(emitter);
  Mark mark;
  handler.OnDocumentStart(mark);
  handler.OnMapStart(mark, "", 0, EmitterStyle::Block);
  handler.OnScalar(mark, "", 0, "key1");
  handler.OnScalar(mark, "", 0, "value1");
  handler.OnScalar(mark, "", 0, "key2");
  handler.OnScalar(mark, "", 0, "value2");
  handler.OnScalar(mark, "", 0, "key3");
  handler.OnScalar(mark, "", 0, "value3");
  handler.OnMapEnd();
  handler.OnDocumentEnd();
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("key1"), std::string::npos);
  EXPECT_NE(output.find("value1"), std::string::npos);
  EXPECT_NE(output.find("key2"), std::string::npos);
  EXPECT_NE(output.find("value2"), std::string::npos);
  EXPECT_NE(output.find("key3"), std::string::npos);
  EXPECT_NE(output.find("value3"), std::string::npos);
}

// Test round-trip: parse then emit using EmitFromEvents
TEST_F(EmitFromEventsTest_61, RoundTripSimpleYAML_61) {
  std::string input = "key: value";
  Node node = Load(input);
  
  Emitter emitter;
  EmitFromEvents handler(emitter);
  Mark mark;
  handler.OnDocumentStart(mark);
  handler.OnMapStart(mark, "", 0, EmitterStyle::Block);
  handler.OnScalar(mark, "", 0, "key");
  handler.OnScalar(mark, "", 0, "value");
  handler.OnMapEnd();
  handler.OnDocumentEnd();
  
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  
  Node reparsed = Load(output);
  EXPECT_EQ(reparsed["key"].as<std::string>(), "value");
}

// Test sequence with anchor
TEST_F(EmitFromEventsTest_61, SequenceWithAnchor_61) {
  Emitter emitter;
  EmitFromEvents handler(emitter);
  Mark mark;
  handler.OnDocumentStart(mark);
  handler.OnSequenceStart(mark, "", 1, EmitterStyle::Block);
  handler.OnScalar(mark, "", 0, "item");
  handler.OnSequenceEnd();
  handler.OnDocumentEnd();
  EXPECT_TRUE(emitter.good());
}

// Test map with anchor
TEST_F(EmitFromEventsTest_61, MapWithAnchor_61) {
  Emitter emitter;
  EmitFromEvents handler(emitter);
  Mark mark;
  handler.OnDocumentStart(mark);
  handler.OnMapStart(mark, "", 1, EmitterStyle::Block);
  handler.OnScalar(mark, "", 0, "key");
  handler.OnScalar(mark, "", 0, "value");
  handler.OnMapEnd();
  handler.OnDocumentEnd();
  EXPECT_TRUE(emitter.good());
}

// Test special characters in scalar
TEST_F(EmitFromEventsTest_61, SpecialCharactersInScalar_61) {
  Emitter emitter;
  EmitFromEvents handler(emitter);
  Mark mark;
  handler.OnDocumentStart(mark);
  handler.OnScalar(mark, "", 0, "hello: world\nnewline");
  handler.OnDocumentEnd();
  EXPECT_TRUE(emitter.good());
}

// Test null with anchor
TEST_F(EmitFromEventsTest_61, NullWithAnchor_61) {
  Emitter emitter;
  EmitFromEvents handler(emitter);
  Mark mark;
  handler.OnDocumentStart(mark);
  handler.OnNull(mark, 1);
  handler.OnDocumentEnd();
  EXPECT_TRUE(emitter.good());
}

}  // namespace
}  // namespace YAML
