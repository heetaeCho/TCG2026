#include <gtest/gtest.h>
#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"
#include <string>
#include <utility>

using namespace Catch::Benchmark::Detail;

// A simple test type to use with ObjectStorage
struct SimpleType {
    int value;
    static int constructor_count;
    static int destructor_count;
    static int copy_count;
    static int move_count;

    static void reset_counts() {
        constructor_count = 0;
        destructor_count = 0;
        copy_count = 0;
        move_count = 0;
    }

    SimpleType() : value(0) { ++constructor_count; }
    explicit SimpleType(int v) : value(v) { ++constructor_count; }
    SimpleType(const SimpleType& other) : value(other.value) { ++copy_count; }
    SimpleType(SimpleType&& other) noexcept : value(other.value) { other.value = 0; ++move_count; }
    ~SimpleType() { ++destructor_count; }
};

int SimpleType::constructor_count = 0;
int SimpleType::destructor_count = 0;
int SimpleType::copy_count = 0;
int SimpleType::move_count = 0;

// A type with multiple constructor arguments
struct MultiArgType {
    int a;
    double b;
    std::string c;

    MultiArgType(int a_, double b_, std::string c_) : a(a_), b(b_), c(std::move(c_)) {}
};

// Test fixture for ObjectStorage with Destruct = true (auto destruct)
class ObjectStorageAutoDestruct_918 : public ::testing::Test {
protected:
    void SetUp() override {
        SimpleType::reset_counts();
    }
};

// Test fixture for ObjectStorage with Destruct = false (manual destruct)
class ObjectStorageManualDestruct_918 : public ::testing::Test {
protected:
    void SetUp() override {
        SimpleType::reset_counts();
    }
};

// Test default construction of ObjectStorage with Destruct=true
TEST_F(ObjectStorageAutoDestruct_918, DefaultConstruction_918) {
    ObjectStorage<SimpleType, true> storage;
    // Default construction should not construct the stored object
    EXPECT_EQ(SimpleType::constructor_count, 0);
}

// Test default construction of ObjectStorage with Destruct=false
TEST_F(ObjectStorageManualDestruct_918, DefaultConstruction_918) {
    ObjectStorage<SimpleType, false> storage;
    EXPECT_EQ(SimpleType::constructor_count, 0);
}

// Test construct with no arguments (Destruct=true)
TEST_F(ObjectStorageAutoDestruct_918, ConstructDefaultArgs_918) {
    {
        ObjectStorage<SimpleType, true> storage;
        storage.construct();
        EXPECT_EQ(SimpleType::constructor_count, 1);
    }
    // Destruct=true means destructor should be called automatically
    EXPECT_GE(SimpleType::destructor_count, 1);
}

// Test construct with arguments (Destruct=true)
TEST_F(ObjectStorageAutoDestruct_918, ConstructWithArgs_918) {
    {
        ObjectStorage<SimpleType, true> storage;
        storage.construct(42);
        EXPECT_EQ(SimpleType::constructor_count, 1);
    }
    EXPECT_GE(SimpleType::destructor_count, 1);
}

// Test construct with no arguments (Destruct=false)
TEST_F(ObjectStorageManualDestruct_918, ConstructDefaultArgs_918) {
    ObjectStorage<SimpleType, false> storage;
    storage.construct();
    EXPECT_EQ(SimpleType::constructor_count, 1);
    storage.destruct();
    EXPECT_GE(SimpleType::destructor_count, 1);
}

// Test construct with arguments (Destruct=false)
TEST_F(ObjectStorageManualDestruct_918, ConstructWithArgs_918) {
    ObjectStorage<SimpleType, false> storage;
    storage.construct(99);
    EXPECT_EQ(SimpleType::constructor_count, 1);
    storage.destruct();
    EXPECT_GE(SimpleType::destructor_count, 1);
}

// Test manual destruct is available when Destruct=false
TEST_F(ObjectStorageManualDestruct_918, ManualDestructCallsDestructor_918) {
    ObjectStorage<SimpleType, false> storage;
    storage.construct(10);
    int before = SimpleType::destructor_count;
    storage.destruct();
    EXPECT_EQ(SimpleType::destructor_count, before + 1);
}

// Test copy construction of ObjectStorage (Destruct=true)
TEST_F(ObjectStorageAutoDestruct_918, CopyConstruction_918) {
    ObjectStorage<SimpleType, true> storage1;
    storage1.construct(5);
    ObjectStorage<SimpleType, true> storage2(storage1);
    // Copy construction of ObjectStorage should copy the underlying data
    // The exact behavior depends on implementation but should not crash
}

// Test move construction of ObjectStorage (Destruct=true)
TEST_F(ObjectStorageAutoDestruct_918, MoveConstruction_918) {
    ObjectStorage<SimpleType, true> storage1;
    storage1.construct(7);
    ObjectStorage<SimpleType, true> storage2(std::move(storage1));
    // Move construction should transfer the data
}

// Test copy construction of ObjectStorage (Destruct=false)
TEST_F(ObjectStorageManualDestruct_918, CopyConstruction_918) {
    ObjectStorage<SimpleType, false> storage1;
    storage1.construct(15);
    ObjectStorage<SimpleType, false> storage2(storage1);
    storage1.destruct();
    storage2.destruct();
}

// Test move construction of ObjectStorage (Destruct=false)
TEST_F(ObjectStorageManualDestruct_918, MoveConstruction_918) {
    ObjectStorage<SimpleType, false> storage1;
    storage1.construct(20);
    ObjectStorage<SimpleType, false> storage2(std::move(storage1));
    storage2.destruct();
}

// Test with multi-argument type
TEST_F(ObjectStorageAutoDestruct_918, MultiArgConstruct_918) {
    {
        ObjectStorage<MultiArgType, true> storage;
        storage.construct(1, 2.5, std::string("hello"));
    }
    // Should not leak or crash
}

// Test with multi-argument type (manual destruct)
TEST_F(ObjectStorageManualDestruct_918, MultiArgConstruct_918) {
    ObjectStorage<MultiArgType, false> storage;
    storage.construct(10, 3.14, std::string("world"));
    storage.destruct();
}

// Test construct and destruct cycle multiple times (Destruct=false)
TEST_F(ObjectStorageManualDestruct_918, MultipleConstructDestructCycles_918) {
    ObjectStorage<SimpleType, false> storage;
    
    for (int i = 0; i < 5; ++i) {
        storage.construct(i);
        storage.destruct();
    }
    
    EXPECT_EQ(SimpleType::constructor_count, 5);
    EXPECT_EQ(SimpleType::destructor_count, 5);
}

// Test with a type that has no default constructor
struct NoDefaultCtor {
    int val;
    explicit NoDefaultCtor(int v) : val(v) {}
};

TEST_F(ObjectStorageAutoDestruct_918, NoDefaultCtorType_918) {
    {
        ObjectStorage<NoDefaultCtor, true> storage;
        storage.construct(42);
    }
}

TEST_F(ObjectStorageManualDestruct_918, NoDefaultCtorType_918) {
    ObjectStorage<NoDefaultCtor, false> storage;
    storage.construct(42);
    storage.destruct();
}

// Test with std::string type (non-trivial)
TEST(ObjectStorageStringTest_918, ConstructString_918) {
    {
        ObjectStorage<std::string, true> storage;
        storage.construct("test string with some content");
    }
    // auto-destruct should clean up
}

TEST(ObjectStorageStringTest_918, ManualDestructString_918) {
    ObjectStorage<std::string, false> storage;
    storage.construct("another test string");
    storage.destruct();
}

// Test with primitive type
TEST(ObjectStoragePrimitiveTest_918, IntType_918) {
    {
        ObjectStorage<int, true> storage;
        storage.construct(123);
    }
}

TEST(ObjectStoragePrimitiveTest_918, IntTypeManual_918) {
    ObjectStorage<int, false> storage;
    storage.construct(456);
    storage.destruct();
}

// Compile-time check: destruct() should only be available when Destruct=false
// This is a SFINAE check - we verify the template constraint exists
// by testing that Destruct=false allows manual destruct
TEST(ObjectStorageSFINAETest_918, ManualDestructAvailableWhenDestructFalse_918) {
    ObjectStorage<int, false> storage;
    storage.construct(1);
    // This should compile fine because Destruct=false means AllowManualDestruction=true
    storage.destruct();
}

// Test with a large object
struct LargeObject {
    char data[1024];
    int id;
    LargeObject() : data{}, id(0) {}
    explicit LargeObject(int i) : data{}, id(i) {}
};

TEST(ObjectStorageLargeObjectTest_918, AutoDestruct_918) {
    {
        ObjectStorage<LargeObject, true> storage;
        storage.construct(42);
    }
}

TEST(ObjectStorageLargeObjectTest_918, ManualDestruct_918) {
    ObjectStorage<LargeObject, false> storage;
    storage.construct(99);
    storage.destruct();
}

// Test with move-only type
struct MoveOnlyType {
    std::unique_ptr<int> ptr;
    MoveOnlyType() : ptr(nullptr) {}
    explicit MoveOnlyType(int v) : ptr(std::make_unique<int>(v)) {}
    MoveOnlyType(MoveOnlyType&&) = default;
    MoveOnlyType& operator=(MoveOnlyType&&) = default;
    MoveOnlyType(const MoveOnlyType&) = delete;
    MoveOnlyType& operator=(const MoveOnlyType&) = delete;
};

TEST(ObjectStorageMoveOnlyTest_918, ConstructMoveOnly_918) {
    {
        ObjectStorage<MoveOnlyType, true> storage;
        storage.construct(77);
    }
}

TEST(ObjectStorageMoveOnlyTest_918, ManualDestructMoveOnly_918) {
    ObjectStorage<MoveOnlyType, false> storage;
    storage.construct(88);
    storage.destruct();
}

// Test construct with forwarding (rvalue reference argument)
TEST(ObjectStorageForwardingTest_918, ConstructWithRvalue_918) {
    ObjectStorage<std::string, false> storage;
    std::string s = "forward me";
    storage.construct(std::move(s));
    storage.destruct();
}

// Test construct with const lvalue reference argument
TEST(ObjectStorageForwardingTest_918, ConstructWithLvalue_918) {
    ObjectStorage<std::string, false> storage;
    const std::string s = "copy me";
    storage.construct(s);
    storage.destruct();
}
