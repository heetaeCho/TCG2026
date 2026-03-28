#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"



using namespace Catch::Benchmark::Detail;



// Test Fixture for ObjectStorage

template<typename T, bool Destruct>

class ObjectStorageTest : public ::testing::Test {

protected:

    ObjectStorage<T, Destruct> objectStorage;

};



// Define test types and destruct settings

typedef ::testing::Types<

    std::pair<int, true>,

    std::pair<double, false>,

    std::pair<std::string, true>

> ObjectStorageTestTypes;



TYPED_TEST_SUITE(ObjectStorageTest, ObjectStorageTestTypes);



// Test normal construction and destruction with manual destruction allowed

TYPED_TEST(ObjectStorageTest, ConstructAndDestruct_918) {

    using T = typename TypeParam::first_type;

    constexpr bool Destruct = TypeParam::second;



    if (Destruct) {

        this->objectStorage.construct(T{});

        EXPECT_NO_THROW(this->objectStorage.destruct());

    } else {

        // No manual destruction allowed, should throw

        EXPECT_ANY_THROW(this->objectStorage.destruct());

    }

}



// Test construction with variadic arguments

TYPED_TEST(ObjectStorageTest, ConstructWithVariadicArgs_918) {

    using T = typename TypeParam::first_type;

    if constexpr (std::is_constructible_v<T, int, double>) {

        this->objectStorage.construct(42, 3.14);

    } else if constexpr (std::is_constructible_v<T, const char*>) {

        this->objectStorage.construct("test");

    }

}



// Test boundary condition with default construction

TYPED_TEST(ObjectStorageTest, DefaultConstruct_918) {

    using T = typename TypeParam::first_type;

    ObjectStorage<T, TypeParam::second> objectStorageDefault;

    EXPECT_NO_THROW(objectStorageDefault.destruct());

}



// Test exceptional case when trying to destruct without constructing first

TYPED_TEST(ObjectStorageTest, DestructWithoutConstruct_918) {

    using T = typename TypeParam::first_type;

    constexpr bool Destruct = TypeParam::second;



    if (Destruct) {

        EXPECT_ANY_THROW(this->objectStorage.destruct());

    } else {

        // No manual destruction allowed, should throw

        EXPECT_ANY_THROW(this->objectStorage.destruct());

    }

}
