#include <gtest/gtest.h>
#include <string>
#include <utility>

// Include the header under test
#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"

using namespace Catch::Benchmark::Detail;

// A simple test type to use with ObjectStorage
struct SimpleType {
    int value;
    SimpleType() : value(0) {}
    SimpleType(int v) : value(v) {}
    SimpleType(const SimpleType& other) : value(other.value) {}
    SimpleType(SimpleType&& other) noexcept : value(other.value) { other.value = -1; }
    ~SimpleType() = default;
};

// A type that tracks construction/destruction
struct TrackingType {
    static int construction_count;
    static int destruction_count;
    static int copy_count;
    static int move_count;
    
    int value;
    
    TrackingType() : value(0) { ++construction_count; }
    TrackingType(int v) : value(v) { ++construction_count; }
    TrackingType(const TrackingType& other) : value(other.value) { ++copy_count; ++construction_count; }
    TrackingType(TrackingType&& other) noexcept : value(other.value) { ++move_count; ++construction_count; other.value = -1; }
    ~TrackingType() { ++destruction_count; }
    
    static void reset() {
        construction_count = 0;
        destruction_count = 0;
        copy_count = 0;
        move_count = 0;
    }
};

int TrackingType::construction_count = 0;
int TrackingType::destruction_count = 0;
int TrackingType::copy_count = 0;
int TrackingType::move_count = 0;

// Test fixture
class ObjectStorageTest_1105 : public ::testing::Test {
protected:
    void SetUp() override {
        TrackingType::reset();
    }
};

// Test default construction - ObjectStorage with Destruct=true
TEST_F(ObjectStorageTest_1105, DefaultConstruction_Destruct_True_1105) {
    ObjectStorage<SimpleType, true> storage;
    // Default construction should succeed without issues
    SUCCEED();
}

// Test default construction - ObjectStorage with Destruct=false
TEST_F(ObjectStorageTest_1105, DefaultConstruction_Destruct_False_1105) {
    ObjectStorage<SimpleType, false> storage;
    SUCCEED();
}

// Test construct with no arguments
TEST_F(ObjectStorageTest_1105, ConstructDefaultArgs_1105) {
    ObjectStorage<SimpleType, true> storage;
    storage.construct();
    // Object should be constructed with default constructor
    SUCCEED();
}

// Test construct with arguments
TEST_F(ObjectStorageTest_1105, ConstructWithArgs_1105) {
    ObjectStorage<SimpleType, true> storage;
    storage.construct(42);
    SUCCEED();
}

// Test copy constructor
TEST_F(ObjectStorageTest_1105, CopyConstruction_1105) {
    ObjectStorage<SimpleType, true> storage1;
    storage1.construct(42);
    
    ObjectStorage<SimpleType, true> storage2(storage1);
    // Copy should succeed
    SUCCEED();
}

// Test move constructor
TEST_F(ObjectStorageTest_1105, MoveConstruction_1105) {
    ObjectStorage<SimpleType, true> storage1;
    storage1.construct(42);
    
    ObjectStorage<SimpleType, true> storage2(std::move(storage1));
    SUCCEED();
}

// Test destruct with Destruct=false (manual destruction allowed)
TEST_F(ObjectStorageTest_1105, ManualDestruct_DestructFalse_1105) {
    ObjectStorage<TrackingType, false> storage;
    storage.construct(10);
    int constructedBefore = TrackingType::destruction_count;
    storage.destruct();
    EXPECT_EQ(TrackingType::destruction_count, constructedBefore + 1);
}

// Test that construct with tracking type increments construction count
TEST_F(ObjectStorageTest_1105, ConstructTracksConstruction_1105) {
    TrackingType::reset();
    ObjectStorage<TrackingType, true> storage;
    int before = TrackingType::construction_count;
    storage.construct(5);
    EXPECT_EQ(TrackingType::construction_count, before + 1);
}

// Test copy construction with tracking type
TEST_F(ObjectStorageTest_1105, CopyConstructionTracking_1105) {
    TrackingType::reset();
    ObjectStorage<TrackingType, true> storage1;
    storage1.construct(7);
    
    int copyBefore = TrackingType::copy_count;
    ObjectStorage<TrackingType, true> storage2(storage1);
    EXPECT_EQ(TrackingType::copy_count, copyBefore + 1);
}

// Test move construction with tracking type
TEST_F(ObjectStorageTest_1105, MoveConstructionTracking_1105) {
    TrackingType::reset();
    ObjectStorage<TrackingType, true> storage1;
    storage1.construct(9);
    
    int moveBefore = TrackingType::move_count;
    ObjectStorage<TrackingType, true> storage2(std::move(storage1));
    EXPECT_EQ(TrackingType::move_count, moveBefore + 1);
}

// Test with std::string as a non-trivial type
TEST_F(ObjectStorageTest_1105, ConstructWithString_1105) {
    ObjectStorage<std::string, true> storage;
    storage.construct("Hello, World!");
    SUCCEED();
}

// Test copy construction with string
TEST_F(ObjectStorageTest_1105, CopyConstructionString_1105) {
    ObjectStorage<std::string, true> storage1;
    storage1.construct("Test string");
    
    ObjectStorage<std::string, true> storage2(storage1);
    SUCCEED();
}

// Test move construction with string
TEST_F(ObjectStorageTest_1105, MoveConstructionString_1105) {
    ObjectStorage<std::string, true> storage1;
    storage1.construct("Movable string");
    
    ObjectStorage<std::string, true> storage2(std::move(storage1));
    SUCCEED();
}

// Test construct with multiple arguments
TEST_F(ObjectStorageTest_1105, ConstructWithMultipleArgs_1105) {
    struct MultiArgType {
        int a;
        double b;
        MultiArgType(int x, double y) : a(x), b(y) {}
        MultiArgType(const MultiArgType&) = default;
        MultiArgType(MultiArgType&&) = default;
        ~MultiArgType() = default;
    };
    
    ObjectStorage<MultiArgType, true> storage;
    storage.construct(1, 2.5);
    SUCCEED();
}

// Test destruction behavior with Destruct=true
TEST_F(ObjectStorageTest_1105, DestructorCalledOnScopeExit_DestructTrue_1105) {
    TrackingType::reset();
    {
        ObjectStorage<TrackingType, true> storage;
        storage.construct(42);
    }
    // When Destruct=true, the destructor of the stored object should be called
    // when ObjectStorage goes out of scope
    EXPECT_GT(TrackingType::destruction_count, 0);
}

// Test destruction behavior with Destruct=false
TEST_F(ObjectStorageTest_1105, NoAutoDestructOnScopeExit_DestructFalse_1105) {
    TrackingType::reset();
    int destructionCountAfterConstruct;
    {
        ObjectStorage<TrackingType, false> storage;
        storage.construct(42);
        destructionCountAfterConstruct = TrackingType::destruction_count;
        storage.destruct(); // Manual destruct needed
    }
    // With Destruct=false, only our manual destruct should have been called
    EXPECT_GT(TrackingType::destruction_count, destructionCountAfterConstruct);
}

// Test with a type that has a non-trivial destructor
TEST_F(ObjectStorageTest_1105, NonTrivialDestructorType_1105) {
    struct NonTrivial {
        std::string data;
        NonTrivial() : data("non-trivial") {}
        NonTrivial(const NonTrivial&) = default;
        NonTrivial(NonTrivial&&) = default;
        ~NonTrivial() = default;
    };
    
    ObjectStorage<NonTrivial, true> storage;
    storage.construct();
    SUCCEED();
}

// Test construct overwriting previously constructed object
TEST_F(ObjectStorageTest_1105, ReconstructAfterDestruct_DestructFalse_1105) {
    ObjectStorage<TrackingType, false> storage;
    TrackingType::reset();
    
    storage.construct(1);
    EXPECT_EQ(TrackingType::construction_count, 1);
    
    storage.destruct();
    EXPECT_EQ(TrackingType::destruction_count, 1);
    
    storage.construct(2);
    EXPECT_EQ(TrackingType::construction_count, 2);
    
    storage.destruct();
    EXPECT_EQ(TrackingType::destruction_count, 2);
}

// Test ObjectStorage size matches the stored type
TEST_F(ObjectStorageTest_1105, StorageSizeMatchesType_1105) {
    // The internal data array should be sizeof(T), so ObjectStorage should be at least sizeof(T)
    EXPECT_GE(sizeof(ObjectStorage<int, true>), sizeof(int));
    EXPECT_GE(sizeof(ObjectStorage<double, true>), sizeof(double));
    EXPECT_GE(sizeof(ObjectStorage<SimpleType, true>), sizeof(SimpleType));
}

// Test with a POD type
TEST_F(ObjectStorageTest_1105, PODType_1105) {
    ObjectStorage<int, true> storage;
    storage.construct(42);
    SUCCEED();
}

// Test copy of ObjectStorage with POD type
TEST_F(ObjectStorageTest_1105, CopyPODType_1105) {
    ObjectStorage<int, true> storage1;
    storage1.construct(100);
    
    ObjectStorage<int, true> storage2(storage1);
    SUCCEED();
}

// Test move of ObjectStorage with POD type
TEST_F(ObjectStorageTest_1105, MovePODType_1105) {
    ObjectStorage<int, true> storage1;
    storage1.construct(200);
    
    ObjectStorage<int, true> storage2(std::move(storage1));
    SUCCEED();
}
