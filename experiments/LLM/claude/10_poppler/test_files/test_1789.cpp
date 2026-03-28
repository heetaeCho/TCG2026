#include <gtest/gtest.h>
#include <nss.h>
#include <pk11pub.h>
#include <cms.h>
#include <secerr.h>
#include <seccomon.h>
#include <plarena.h>

// Include the .cc file to access the static function
// This is a standard technique for testing static (file-scope) functions
#include "poppler/NSSCryptoSignBackend.cc"

class NSSCMSArrayAddTest_1789 : public ::testing::Test {
protected:
    PLArenaPool *arena = nullptr;

    void SetUp() override {
        // Initialize NSS if not already initialized
        if (NSS_NoDB_Init(nullptr) != SECSuccess) {
            // It might already be initialized, that's okay
        }
        arena = PORT_NewArena(1024);
        ASSERT_NE(arena, nullptr);
    }

    void TearDown() override {
        if (arena) {
            PORT_FreeArena(arena, PR_FALSE);
            arena = nullptr;
        }
    }
};

// Test that passing a null array pointer returns SECFailure
TEST_F(NSSCMSArrayAddTest_1789, NullArrayReturnsFailure_1789) {
    int obj = 42;
    SECStatus status = my_NSS_CMSArray_Add(arena, nullptr, &obj);
    EXPECT_EQ(status, SECFailure);
}

// Test adding an object to a null (empty) array
TEST_F(NSSCMSArrayAddTest_1789, AddToNullArray_1789) {
    void **array = nullptr;
    int obj = 42;
    SECStatus status = my_NSS_CMSArray_Add(arena, &array, &obj);
    EXPECT_EQ(status, SECSuccess);
    ASSERT_NE(array, nullptr);
    EXPECT_EQ(array[0], &obj);
    EXPECT_EQ(array[1], nullptr);
}

// Test adding a single object and verifying it's stored correctly
TEST_F(NSSCMSArrayAddTest_1789, AddSingleElement_1789) {
    void **array = nullptr;
    int value = 100;
    SECStatus status = my_NSS_CMSArray_Add(arena, &array, &value);
    EXPECT_EQ(status, SECSuccess);
    ASSERT_NE(array, nullptr);
    EXPECT_EQ(array[0], static_cast<void *>(&value));
    EXPECT_EQ(array[1], nullptr);
}

// Test adding multiple objects to the array
TEST_F(NSSCMSArrayAddTest_1789, AddMultipleElements_1789) {
    void **array = nullptr;
    int v1 = 1, v2 = 2, v3 = 3;

    EXPECT_EQ(my_NSS_CMSArray_Add(arena, &array, &v1), SECSuccess);
    EXPECT_EQ(my_NSS_CMSArray_Add(arena, &array, &v2), SECSuccess);
    EXPECT_EQ(my_NSS_CMSArray_Add(arena, &array, &v3), SECSuccess);

    ASSERT_NE(array, nullptr);
    EXPECT_EQ(array[0], static_cast<void *>(&v1));
    EXPECT_EQ(array[1], static_cast<void *>(&v2));
    EXPECT_EQ(array[2], static_cast<void *>(&v3));
    EXPECT_EQ(array[3], nullptr);
}

// Test adding a nullptr object (should still succeed as the function doesn't validate obj)
TEST_F(NSSCMSArrayAddTest_1789, AddNullObject_1789) {
    void **array = nullptr;
    SECStatus status = my_NSS_CMSArray_Add(arena, &array, nullptr);
    EXPECT_EQ(status, SECSuccess);
    ASSERT_NE(array, nullptr);
    // The first element should be nullptr (the object we added)
    EXPECT_EQ(array[0], nullptr);
    // Note: array[1] is the sentinel nullptr
}

// Test that the array is null-terminated after each addition
TEST_F(NSSCMSArrayAddTest_1789, ArrayIsNullTerminated_1789) {
    void **array = nullptr;
    int v1 = 10, v2 = 20;

    my_NSS_CMSArray_Add(arena, &array, &v1);
    ASSERT_NE(array, nullptr);
    EXPECT_EQ(array[1], nullptr);

    my_NSS_CMSArray_Add(arena, &array, &v2);
    EXPECT_EQ(array[2], nullptr);
}

// Test adding many elements to verify growth works
TEST_F(NSSCMSArrayAddTest_1789, AddManyElements_1789) {
    void **array = nullptr;
    const int count = 50;
    int values[count];

    for (int i = 0; i < count; i++) {
        values[i] = i;
        SECStatus status = my_NSS_CMSArray_Add(arena, &array, &values[i]);
        EXPECT_EQ(status, SECSuccess);
    }

    ASSERT_NE(array, nullptr);
    for (int i = 0; i < count; i++) {
        EXPECT_EQ(array[i], static_cast<void *>(&values[i]));
    }
    EXPECT_EQ(array[count], nullptr);
}
