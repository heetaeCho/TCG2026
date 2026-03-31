#include <gtest/gtest.h>
#include <utility>
#include <string>
#include <type_traits>

// Include the header under test
#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"

using namespace Catch::Benchmark::Detail;

// A simple test type to use with ObjectStorage
struct SimpleType {
    int value;
    static int construct_count;
    static int destruct_count;
    static int copy_count;
    static int move_count;

    static void reset_counts() {
        construct_count = 0;
        destruct_count = 0;
        copy_count = 0;
        move_count = 0;
    }

    SimpleType() : value(0) { ++construct_count; }
    explicit SimpleType(int v) : value(v) { ++construct_count; }
    SimpleType(int a, int b) : value(a + b) { ++construct_count; }

    SimpleType(const SimpleType& other) : value(other.value) {
        ++construct_count;
        ++copy_count;
    }

    SimpleType(SimpleType&& other) noexcept : value(other.value) {
        other.value = -1;
        ++construct_count;
        ++move_count;
    }

    ~SimpleType() { ++destruct_count; }

    SimpleType& operator=(const SimpleType&) = default;
    SimpleType& operator=(SimpleType&&) noexcept = default;
};

int SimpleType::construct_count = 0;
int SimpleType::destruct_count = 0;
int SimpleType::copy_count = 0;
int SimpleType::move_count = 0;

// Test fixture
class ObjectStorageTest_1106 : public ::testing::Test {
protected:
    void SetUp() override {
        SimpleType::reset_counts();
    }
};

// Test default construction - should not construct stored object
TEST_F(ObjectStorageTest_1106, DefaultConstruction_1106) {
    SimpleType::reset_counts();
    {
        ObjectStorage<SimpleType, false> storage;
        // Default construction should NOT construct the stored object
        EXPECT_EQ(SimpleType::construct_count, 0);
    }
}

// Test construct with no arguments
TEST_F(ObjectStorageTest_1106, ConstructDefaultObject_1106) {
    SimpleType::reset_counts();
    ObjectStorage<SimpleType, false> storage;
    storage.construct();
    EXPECT_EQ(SimpleType::construct_count, 1);
    // Manual destruct since Destruct=false
    storage.destruct();
}

// Test construct with single argument
TEST_F(ObjectStorageTest_1106, ConstructWithSingleArg_1106) {
    SimpleType::reset_counts();
    ObjectStorage<SimpleType, false> storage;
    storage.construct(42);
    EXPECT_EQ(SimpleType::construct_count, 1);
    storage.destruct();
}

// Test construct with multiple arguments
TEST_F(ObjectStorageTest_1106, ConstructWithMultipleArgs_1106) {
    SimpleType::reset_counts();
    ObjectStorage<SimpleType, false> storage;
    storage.construct(10, 20);
    EXPECT_EQ(SimpleType::construct_count, 1);
    storage.destruct();
}

// Test copy construction
TEST_F(ObjectStorageTest_1106, CopyConstruction_1106) {
    SimpleType::reset_counts();
    ObjectStorage<SimpleType, false> original;
    original.construct(42);

    int count_before = SimpleType::construct_count;
    ObjectStorage<SimpleType, false> copy(original);
    // Copy construction should have constructed a new SimpleType via copy
    EXPECT_GT(SimpleType::construct_count, count_before);
    EXPECT_GE(SimpleType::copy_count, 1);

    copy.destruct();
    original.destruct();
}

// Test move construction
TEST_F(ObjectStorageTest_1106, MoveConstruction_1106) {
    SimpleType::reset_counts();
    ObjectStorage<SimpleType, false> original;
    original.construct(42);

    int count_before = SimpleType::construct_count;
    int move_before = SimpleType::move_count;
    ObjectStorage<SimpleType, false> moved(std::move(original));
    // Move construction should have constructed a new SimpleType via move
    EXPECT_GT(SimpleType::construct_count, count_before);
    EXPECT_GT(SimpleType::move_count, move_before);

    moved.destruct();
}

// Test manual destruct when Destruct=false
TEST_F(ObjectStorageTest_1106, ManualDestruct_1106) {
    SimpleType::reset_counts();
    ObjectStorage<SimpleType, false> storage;
    storage.construct(100);

    int destruct_before = SimpleType::destruct_count;
    storage.destruct();
    EXPECT_GT(SimpleType::destruct_count, destruct_before);
}

// Test auto destruct when Destruct=true
TEST_F(ObjectStorageTest_1106, AutoDestructOnExit_1106) {
    SimpleType::reset_counts();
    {
        ObjectStorage<SimpleType, true> storage;
        storage.construct(55);
        EXPECT_EQ(SimpleType::construct_count, 1);
    }
    // Destructor of ObjectStorage should have destructed the SimpleType
    EXPECT_GE(SimpleType::destruct_count, 1);
}

// Test that Destruct=true triggers automatic destruction in destructor
TEST_F(ObjectStorageTest_1106, DestructTrueCallsDestructor_1106) {
    SimpleType::reset_counts();
    int destruct_after;
    {
        ObjectStorage<SimpleType, true> storage;
        storage.construct(77);
    }
    destruct_after = SimpleType::destruct_count;
    EXPECT_GE(destruct_after, 1);
}

// Test with string type to verify complex types work
TEST_F(ObjectStorageTest_1106, WorksWithStringType_1106) {
    ObjectStorage<std::string, false> storage;
    storage.construct("hello world");
    storage.destruct();
}

// Test construct and then copy of storage with string
TEST_F(ObjectStorageTest_1106, CopyWithStringType_1106) {
    ObjectStorage<std::string, false> storage;
    storage.construct("test string");

    ObjectStorage<std::string, false> copy(storage);

    copy.destruct();
    storage.destruct();
}

// Test move with string type
TEST_F(ObjectStorageTest_1106, MoveWithStringType_1106) {
    ObjectStorage<std::string, false> storage;
    storage.construct("moveable string");

    ObjectStorage<std::string, false> moved(std::move(storage));

    moved.destruct();
}

// Test that destruct is only available when Destruct=false (compile-time check is implicit)
// We test that it compiles and works correctly
TEST_F(ObjectStorageTest_1106, DestructAvailableWhenDestructFalse_1106) {
    ObjectStorage<SimpleType, false> storage;
    storage.construct(1);
    // This should compile and work fine
    storage.destruct();
    EXPECT_GE(SimpleType::destruct_count, 1);
}

// Test with int type (trivial type)
TEST_F(ObjectStorageTest_1106, WorksWithIntType_1106) {
    ObjectStorage<int, false> storage;
    storage.construct(42);
    storage.destruct();
}

// Test with int type and auto destruct
TEST_F(ObjectStorageTest_1106, WorksWithIntTypeAutoDestruct_1106) {
    {
        ObjectStorage<int, true> storage;
        storage.construct(42);
    }
    // Should not crash - int destructor is trivial
}

// Test multiple construct/destruct cycles on same storage (Destruct=false)
TEST_F(ObjectStorageTest_1106, MultipleConstructDestructCycles_1106) {
    SimpleType::reset_counts();
    ObjectStorage<SimpleType, false> storage;

    storage.construct(1);
    EXPECT_EQ(SimpleType::construct_count, 1);
    storage.destruct();
    EXPECT_EQ(SimpleType::destruct_count, 1);

    storage.construct(2);
    EXPECT_EQ(SimpleType::construct_count, 2);
    storage.destruct();
    EXPECT_EQ(SimpleType::destruct_count, 2);
}

// Test construct with zero value
TEST_F(ObjectStorageTest_1106, ConstructWithZeroValue_1106) {
    SimpleType::reset_counts();
    ObjectStorage<SimpleType, false> storage;
    storage.construct(0);
    EXPECT_EQ(SimpleType::construct_count, 1);
    storage.destruct();
}

// Test empty string construct
TEST_F(ObjectStorageTest_1106, ConstructWithEmptyString_1106) {
    ObjectStorage<std::string, false> storage;
    storage.construct("");
    storage.destruct();
}

// Test default constructed object of Destruct=true without constructing stored object
TEST_F(ObjectStorageTest_1106, DefaultConstructDestructTrue_1106) {
    // This tests that creating and destroying ObjectStorage<T, true> without
    // calling construct doesn't crash (though behavior might be undefined,
    // we test the observable interface)
    SimpleType::reset_counts();
    {
        ObjectStorage<SimpleType, true> storage;
        // Not calling construct - just let it go out of scope
        // This may or may not be valid, but we test it doesn't crash in the
        // zero-initialized case
    }
}
