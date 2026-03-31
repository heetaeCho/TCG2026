#include <gtest/gtest.h>
#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"
#include <string>
#include <utility>

using namespace Catch::Benchmark::Detail;

// A simple test type to use with ObjectStorage
struct SimpleType {
    int value;
    static int construct_count;
    static int destruct_count;

    SimpleType() : value(0) {
        construct_count++;
    }
    SimpleType(int v) : value(v) {
        construct_count++;
    }
    SimpleType(const SimpleType& other) : value(other.value) {
        construct_count++;
    }
    SimpleType(SimpleType&& other) : value(other.value) {
        other.value = 0;
        construct_count++;
    }
    ~SimpleType() {
        destruct_count++;
    }

    static void reset_counts() {
        construct_count = 0;
        destruct_count = 0;
    }
};

int SimpleType::construct_count = 0;
int SimpleType::destruct_count = 0;

// A type with multiple constructor arguments
struct MultiArgType {
    int a;
    double b;
    std::string c;

    MultiArgType(int a_, double b_, std::string c_) : a(a_), b(b_), c(std::move(c_)) {}
};

// Test fixture for ObjectStorage with Destruct = true
class ObjectStorageDestructTrue_916 : public ::testing::Test {
protected:
    void SetUp() override {
        SimpleType::reset_counts();
    }
};

// Test fixture for ObjectStorage with Destruct = false
class ObjectStorageDestructFalse_916 : public ::testing::Test {
protected:
    void SetUp() override {
        SimpleType::reset_counts();
    }
};

// Test: Default construction does not construct the stored object
TEST_F(ObjectStorageDestructTrue_916, DefaultConstruction_916) {
    SimpleType::reset_counts();
    {
        ObjectStorage<SimpleType, true> storage;
        // Default construction should not construct SimpleType
        EXPECT_EQ(SimpleType::construct_count, 0);
    }
}

// Test: Construct method creates the object in storage (Destruct=true)
TEST_F(ObjectStorageDestructTrue_916, ConstructCreatesObject_916) {
    SimpleType::reset_counts();
    {
        ObjectStorage<SimpleType, true> storage;
        storage.construct(42);
        EXPECT_EQ(SimpleType::construct_count, 1);
    }
    // Destruct=true means destructor should be called on exit
    EXPECT_EQ(SimpleType::destruct_count, 1);
}

// Test: Construct with default arguments (Destruct=true)
TEST_F(ObjectStorageDestructTrue_916, ConstructDefaultArgs_916) {
    SimpleType::reset_counts();
    {
        ObjectStorage<SimpleType, true> storage;
        storage.construct();
        EXPECT_EQ(SimpleType::construct_count, 1);
    }
    EXPECT_EQ(SimpleType::destruct_count, 1);
}

// Test: ObjectStorage with Destruct=false does NOT auto-destruct
TEST_F(ObjectStorageDestructFalse_916, NoAutoDestruct_916) {
    SimpleType::reset_counts();
    {
        ObjectStorage<SimpleType, false> storage;
        storage.construct(10);
        EXPECT_EQ(SimpleType::construct_count, 1);
        // Manually destruct since Destruct=false allows it
        storage.destruct();
        EXPECT_EQ(SimpleType::destruct_count, 1);
    }
    // Should not have an additional destruct call on exit
    EXPECT_EQ(SimpleType::destruct_count, 1);
}

// Test: Manual destruct is available when Destruct=false
TEST_F(ObjectStorageDestructFalse_916, ManualDestructAvailable_916) {
    SimpleType::reset_counts();
    ObjectStorage<SimpleType, false> storage;
    storage.construct(99);
    EXPECT_EQ(SimpleType::construct_count, 1);
    storage.destruct();
    EXPECT_EQ(SimpleType::destruct_count, 1);
}

// Test: Copy construction of ObjectStorage
TEST_F(ObjectStorageDestructTrue_916, CopyConstruction_916) {
    SimpleType::reset_counts();
    {
        ObjectStorage<SimpleType, true> storage1;
        storage1.construct(5);

        ObjectStorage<SimpleType, true> storage2(storage1);
        // Copy should have occurred - at least the raw bytes are copied
    }
    // Both should destruct
}

// Test: Move construction of ObjectStorage
TEST_F(ObjectStorageDestructTrue_916, MoveConstruction_916) {
    SimpleType::reset_counts();
    {
        ObjectStorage<SimpleType, true> storage1;
        storage1.construct(7);

        ObjectStorage<SimpleType, true> storage2(std::move(storage1));
    }
}

// Test: Multi-argument construct
TEST_F(ObjectStorageDestructTrue_916, MultiArgConstruct_916) {
    {
        ObjectStorage<MultiArgType, true> storage;
        storage.construct(1, 2.5, std::string("hello"));
    }
    // Should not crash - destructor runs automatically
}

// Test: Construct with string type
TEST_F(ObjectStorageDestructTrue_916, StringTypeConstruct_916) {
    {
        ObjectStorage<std::string, true> storage;
        storage.construct("test string");
    }
    // String destructor should be called automatically
}

// Test: Multiple construct/destruct cycles with Destruct=false
TEST_F(ObjectStorageDestructFalse_916, MultipleConstructDestruct_916) {
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

// Test: ObjectStorage with POD type (int)
TEST_F(ObjectStorageDestructTrue_916, PODTypeInt_916) {
    {
        ObjectStorage<int, true> storage;
        storage.construct(42);
    }
    // Should not crash
}

// Test: ObjectStorage with Destruct=false and POD type
TEST_F(ObjectStorageDestructFalse_916, PODTypeIntManualDestruct_916) {
    ObjectStorage<int, false> storage;
    storage.construct(100);
    storage.destruct();
    // Should not crash
}

// Test: ObjectStorage default constructed state with Destruct=true (no construct called)
TEST_F(ObjectStorageDestructTrue_916, DefaultStateNoConstruct_916) {
    SimpleType::reset_counts();
    {
        ObjectStorage<SimpleType, true> storage;
        // Don't call construct - object was never constructed
        // On destruction, destruct_on_exit with Destruct=true should still be called
        // but behavior depends on implementation
    }
}

// Test: Large object in ObjectStorage
struct LargeObject {
    char data[1024];
    int marker;
    LargeObject() : marker(0xDEAD) { std::memset(data, 0, sizeof(data)); }
    LargeObject(int m) : marker(m) { std::memset(data, 0, sizeof(data)); }
};

TEST_F(ObjectStorageDestructTrue_916, LargeObjectStorage_916) {
    {
        ObjectStorage<LargeObject, true> storage;
        storage.construct(0xBEEF);
    }
    // Should handle large objects without issues
}

// Test: ObjectStorage with a type that has no default constructor
struct NoDefaultCtor {
    int val;
    explicit NoDefaultCtor(int v) : val(v) {}
};

TEST_F(ObjectStorageDestructTrue_916, NoDefaultCtorType_916) {
    {
        ObjectStorage<NoDefaultCtor, true> storage;
        storage.construct(123);
    }
}

// Test: Forwarding of rvalue arguments through construct
TEST_F(ObjectStorageDestructTrue_916, RvalueForwarding_916) {
    {
        ObjectStorage<std::string, true> storage;
        std::string temp = "hello world";
        storage.construct(std::move(temp));
        // temp should have been moved from
    }
}
