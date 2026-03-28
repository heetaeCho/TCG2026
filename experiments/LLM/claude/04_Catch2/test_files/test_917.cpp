#include <gtest/gtest.h>
#include <string>
#include <utility>

// Include the header under test
#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"

using namespace Catch::Benchmark::Detail;

// ============================================================
// Test with Destruct = false (manual destruction required)
// ============================================================

// Simple struct to track construction and destruction
struct Tracker {
    static int construct_count;
    static int destruct_count;
    static int copy_count;
    static int move_count;
    int value;

    static void reset() {
        construct_count = 0;
        destruct_count = 0;
        copy_count = 0;
        move_count = 0;
    }

    Tracker() : value(0) { ++construct_count; }
    explicit Tracker(int v) : value(v) { ++construct_count; }
    Tracker(int a, int b) : value(a + b) { ++construct_count; }
    Tracker(const Tracker& other) : value(other.value) { ++construct_count; ++copy_count; }
    Tracker(Tracker&& other) noexcept : value(other.value) { ++construct_count; ++move_count; other.value = -1; }
    ~Tracker() { ++destruct_count; }
};

int Tracker::construct_count = 0;
int Tracker::destruct_count = 0;
int Tracker::copy_count = 0;
int Tracker::move_count = 0;

// ============================================================
// Tests for ObjectStorage with Destruct = false
// ============================================================

class ObjectStorageNoDestructTest_917 : public ::testing::Test {
protected:
    void SetUp() override {
        Tracker::reset();
    }
};

TEST_F(ObjectStorageNoDestructTest_917, DefaultConstruction_917) {
    // Default construction of ObjectStorage should not construct the stored object
    Tracker::reset();
    ObjectStorage<Tracker, false> storage;
    EXPECT_EQ(Tracker::construct_count, 0);
}

TEST_F(ObjectStorageNoDestructTest_917, ConstructDefaultArgs_917) {
    ObjectStorage<Tracker, false> storage;
    storage.construct();
    EXPECT_EQ(Tracker::construct_count, 1);
    EXPECT_EQ(Tracker::destruct_count, 0);
    // Manual cleanup
    storage.destruct();
}

TEST_F(ObjectStorageNoDestructTest_917, ConstructWithSingleArg_917) {
    ObjectStorage<Tracker, false> storage;
    storage.construct(42);
    EXPECT_EQ(Tracker::construct_count, 1);
    // Manual cleanup
    storage.destruct();
}

TEST_F(ObjectStorageNoDestructTest_917, ConstructWithMultipleArgs_917) {
    ObjectStorage<Tracker, false> storage;
    storage.construct(10, 20);
    EXPECT_EQ(Tracker::construct_count, 1);
    // Manual cleanup
    storage.destruct();
}

TEST_F(ObjectStorageNoDestructTest_917, ManualDestruct_917) {
    ObjectStorage<Tracker, false> storage;
    storage.construct(5);
    EXPECT_EQ(Tracker::destruct_count, 0);
    storage.destruct();
    EXPECT_EQ(Tracker::destruct_count, 1);
}

TEST_F(ObjectStorageNoDestructTest_917, CopyConstruction_917) {
    ObjectStorage<Tracker, false> storage1;
    storage1.construct(99);
    
    Tracker::reset();
    ObjectStorage<Tracker, false> storage2(storage1);
    
    // Copy constructor of ObjectStorage should copy the underlying data
    // The exact behavior depends on implementation, but it should be safe
    storage1.destruct();
    storage2.destruct();
}

TEST_F(ObjectStorageNoDestructTest_917, MoveConstruction_917) {
    ObjectStorage<Tracker, false> storage1;
    storage1.construct(77);
    
    Tracker::reset();
    ObjectStorage<Tracker, false> storage2(std::move(storage1));
    
    // Move constructor of ObjectStorage
    storage2.destruct();
}

// ============================================================
// Tests for ObjectStorage with Destruct = true
// ============================================================

class ObjectStorageAutoDestructTest_917 : public ::testing::Test {
protected:
    void SetUp() override {
        Tracker::reset();
    }
};

TEST_F(ObjectStorageAutoDestructTest_917, DefaultConstruction_917) {
    Tracker::reset();
    ObjectStorage<Tracker, true> storage;
    EXPECT_EQ(Tracker::construct_count, 0);
}

TEST_F(ObjectStorageAutoDestructTest_917, ConstructAndAutoDestruct_917) {
    Tracker::reset();
    {
        ObjectStorage<Tracker, true> storage;
        storage.construct(42);
        EXPECT_EQ(Tracker::construct_count, 1);
        EXPECT_EQ(Tracker::destruct_count, 0);
    }
    // After storage goes out of scope, the object should be auto-destructed
    EXPECT_GE(Tracker::destruct_count, 1);
}

TEST_F(ObjectStorageAutoDestructTest_917, ConstructWithNoArgs_917) {
    Tracker::reset();
    {
        ObjectStorage<Tracker, true> storage;
        storage.construct();
        EXPECT_EQ(Tracker::construct_count, 1);
    }
    EXPECT_GE(Tracker::destruct_count, 1);
}

TEST_F(ObjectStorageAutoDestructTest_917, ConstructWithMultipleArgs_917) {
    Tracker::reset();
    {
        ObjectStorage<Tracker, true> storage;
        storage.construct(3, 7);
        EXPECT_EQ(Tracker::construct_count, 1);
    }
    EXPECT_GE(Tracker::destruct_count, 1);
}

// ============================================================
// Tests with primitive types
// ============================================================

TEST(ObjectStoragePrimitiveTest_917, ConstructInt_917) {
    ObjectStorage<int, false> storage;
    storage.construct(42);
    storage.destruct();
}

TEST(ObjectStoragePrimitiveTest_917, ConstructDouble_917) {
    ObjectStorage<double, false> storage;
    storage.construct(3.14);
    storage.destruct();
}

TEST(ObjectStoragePrimitiveTest_917, ConstructIntAutoDestruct_917) {
    ObjectStorage<int, true> storage;
    storage.construct(100);
    // Should auto-destruct when going out of scope
}

// ============================================================
// Tests with std::string (complex type)
// ============================================================

TEST(ObjectStorageStringTest_917, ConstructString_917) {
    ObjectStorage<std::string, false> storage;
    storage.construct("hello world");
    storage.destruct();
}

TEST(ObjectStorageStringTest_917, ConstructEmptyString_917) {
    ObjectStorage<std::string, false> storage;
    storage.construct();
    storage.destruct();
}

TEST(ObjectStorageStringTest_917, ConstructStringAutoDestruct_917) {
    {
        ObjectStorage<std::string, true> storage;
        storage.construct("auto destruct test");
    }
    // Should not leak
}

TEST(ObjectStorageStringTest_917, ConstructStringFromSizeAndChar_917) {
    ObjectStorage<std::string, false> storage;
    storage.construct(5, 'a');
    storage.destruct();
}

// ============================================================
// Tests with move-only types
// ============================================================

struct MoveOnly {
    int value;
    MoveOnly(int v) : value(v) {}
    MoveOnly(const MoveOnly&) = delete;
    MoveOnly& operator=(const MoveOnly&) = delete;
    MoveOnly(MoveOnly&& other) noexcept : value(other.value) { other.value = -1; }
    MoveOnly& operator=(MoveOnly&&) noexcept = default;
};

TEST(ObjectStorageMoveOnlyTest_917, ConstructMoveOnly_917) {
    ObjectStorage<MoveOnly, false> storage;
    storage.construct(42);
    storage.destruct();
}

TEST(ObjectStorageMoveOnlyTest_917, ConstructMoveOnlyAutoDestruct_917) {
    {
        ObjectStorage<MoveOnly, true> storage;
        storage.construct(99);
    }
}

// ============================================================
// Boundary: Large object
// ============================================================

struct LargeObject {
    char data[1024];
    int marker;
    LargeObject() : marker(0) { std::memset(data, 0, sizeof(data)); }
    explicit LargeObject(int m) : marker(m) { std::memset(data, 0, sizeof(data)); }
};

TEST(ObjectStorageLargeObjectTest_917, ConstructLargeObject_917) {
    ObjectStorage<LargeObject, false> storage;
    storage.construct(123);
    storage.destruct();
}

TEST(ObjectStorageLargeObjectTest_917, ConstructLargeObjectAutoDestruct_917) {
    {
        ObjectStorage<LargeObject, true> storage;
        storage.construct(456);
    }
}

// ============================================================
// Test: Multiple construct/destruct cycles (manual)
// ============================================================

TEST(ObjectStorageCycleTest_917, MultipleConstructDestructCycles_917) {
    Tracker::reset();
    ObjectStorage<Tracker, false> storage;
    
    for (int i = 0; i < 5; ++i) {
        storage.construct(i);
        storage.destruct();
    }
    
    EXPECT_EQ(Tracker::construct_count, 5);
    EXPECT_EQ(Tracker::destruct_count, 5);
}

// ============================================================
// Test: Construct with forwarding (rvalue reference)
// ============================================================

TEST(ObjectStorageForwardingTest_917, ConstructWithRvalue_917) {
    Tracker::reset();
    ObjectStorage<Tracker, false> storage;
    Tracker t(55);
    Tracker::reset();
    
    storage.construct(std::move(t));
    EXPECT_EQ(Tracker::move_count, 1);
    storage.destruct();
}

TEST(ObjectStorageForwardingTest_917, ConstructWithLvalue_917) {
    Tracker::reset();
    ObjectStorage<Tracker, false> storage;
    Tracker t(66);
    Tracker::reset();
    
    storage.construct(t);
    EXPECT_EQ(Tracker::copy_count, 1);
    storage.destruct();
}
