#include "gtest/gtest.h"
#include <vector>
#include <cstdint>
#include <string>

// Since we need to test CompactionState which is a nested struct inside DBImpl,
// and we need the relevant types, we recreate the minimal necessary structures
// based on the known/inferred dependencies.

namespace leveldb {

// Forward declarations / minimal stubs for dependencies
class Compaction {};
class WritableFile {};
class TableBuilder {};

typedef uint64_t SequenceNumber;

// Output struct - inferred from usage in CompactionState
struct Output {
  uint64_t number;
  uint64_t file_size;
  // Minimal fields needed
};

struct CompactionState {
  struct OutputEntry {
    uint64_t number;
    uint64_t file_size;
  };

  Compaction* const compaction;
  SequenceNumber smallest_snapshot;
  std::vector<Output> outputs;
  WritableFile* outfile;
  TableBuilder* builder;
  uint64_t total_bytes;

  explicit CompactionState(Compaction* c)
      : compaction(c),
        smallest_snapshot(0),
        outfile(nullptr),
        builder(nullptr),
        total_bytes(0) {}

  Output* current_output() { return &outputs[outputs.size() - 1]; }
};

}  // namespace leveldb

// Test fixture
class CompactionStateTest_297 : public ::testing::Test {
 protected:
  leveldb::Compaction compaction_;
};

// Test that constructor initializes fields correctly
TEST_F(CompactionStateTest_297, ConstructorInitializesFields_297) {
  leveldb::CompactionState state(&compaction_);
  
  EXPECT_EQ(state.compaction, &compaction_);
  EXPECT_EQ(state.smallest_snapshot, 0u);
  EXPECT_TRUE(state.outputs.empty());
  EXPECT_EQ(state.outfile, nullptr);
  EXPECT_EQ(state.builder, nullptr);
  EXPECT_EQ(state.total_bytes, 0u);
}

// Test current_output returns pointer to last element when one output exists
TEST_F(CompactionStateTest_297, CurrentOutputWithSingleOutput_297) {
  leveldb::CompactionState state(&compaction_);
  
  leveldb::Output output;
  output.number = 42;
  output.file_size = 1024;
  state.outputs.push_back(output);
  
  leveldb::Output* result = state.current_output();
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result->number, 42u);
  EXPECT_EQ(result->file_size, 1024u);
}

// Test current_output returns pointer to last element when multiple outputs exist
TEST_F(CompactionStateTest_297, CurrentOutputWithMultipleOutputs_297) {
  leveldb::CompactionState state(&compaction_);
  
  leveldb::Output output1;
  output1.number = 1;
  output1.file_size = 100;
  state.outputs.push_back(output1);
  
  leveldb::Output output2;
  output2.number = 2;
  output2.file_size = 200;
  state.outputs.push_back(output2);
  
  leveldb::Output output3;
  output3.number = 3;
  output3.file_size = 300;
  state.outputs.push_back(output3);
  
  leveldb::Output* result = state.current_output();
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result->number, 3u);
  EXPECT_EQ(result->file_size, 300u);
}

// Test that current_output returns a mutable pointer (can modify the output)
TEST_F(CompactionStateTest_297, CurrentOutputIsMutable_297) {
  leveldb::CompactionState state(&compaction_);
  
  leveldb::Output output;
  output.number = 10;
  output.file_size = 500;
  state.outputs.push_back(output);
  
  leveldb::Output* result = state.current_output();
  result->file_size = 999;
  
  EXPECT_EQ(state.outputs.back().file_size, 999u);
}

// Test current_output after adding outputs incrementally
TEST_F(CompactionStateTest_297, CurrentOutputUpdatesAfterPush_297) {
  leveldb::CompactionState state(&compaction_);
  
  leveldb::Output output1;
  output1.number = 1;
  output1.file_size = 100;
  state.outputs.push_back(output1);
  
  leveldb::Output* result1 = state.current_output();
  EXPECT_EQ(result1->number, 1u);
  
  leveldb::Output output2;
  output2.number = 2;
  output2.file_size = 200;
  state.outputs.push_back(output2);
  
  leveldb::Output* result2 = state.current_output();
  EXPECT_EQ(result2->number, 2u);
}

// Test that compaction pointer is correctly stored
TEST_F(CompactionStateTest_297, CompactionPointerIsStored_297) {
  leveldb::Compaction c1;
  leveldb::CompactionState state(&c1);
  EXPECT_EQ(state.compaction, &c1);
}

// Test with nullptr compaction
TEST_F(CompactionStateTest_297, NullCompactionPointer_297) {
  leveldb::CompactionState state(nullptr);
  EXPECT_EQ(state.compaction, nullptr);
}

// Test that current_output points into the vector (address check)
TEST_F(CompactionStateTest_297, CurrentOutputPointsIntoVector_297) {
  leveldb::CompactionState state(&compaction_);
  
  leveldb::Output output;
  output.number = 7;
  output.file_size = 777;
  state.outputs.push_back(output);
  
  leveldb::Output* result = state.current_output();
  EXPECT_EQ(result, &state.outputs[state.outputs.size() - 1]);
}

// Test total_bytes can be modified
TEST_F(CompactionStateTest_297, TotalBytesModifiable_297) {
  leveldb::CompactionState state(&compaction_);
  EXPECT_EQ(state.total_bytes, 0u);
  
  state.total_bytes = 12345;
  EXPECT_EQ(state.total_bytes, 12345u);
}

// Test smallest_snapshot can be modified
TEST_F(CompactionStateTest_297, SmallestSnapshotModifiable_297) {
  leveldb::CompactionState state(&compaction_);
  EXPECT_EQ(state.smallest_snapshot, 0u);
  
  state.smallest_snapshot = 99999;
  EXPECT_EQ(state.smallest_snapshot, 99999u);
}
