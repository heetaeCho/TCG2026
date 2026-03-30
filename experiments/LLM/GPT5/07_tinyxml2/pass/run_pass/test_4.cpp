// File: dynarray_test_4.cpp

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdlib>
#include <new>
#include <unordered_set>
#include <mutex>
#include <utility>
#include <vector>
#include <algorithm>

#include "./TestProjects/tinyxml2/tinyxml2.h"

namespace {

// --- Global new[]/delete[] interception (test-only) ---
// We keep this as quiet and scoped as possible, so we only "listen" during a narrow window.
struct NewDeleteArrayTracker {
    bool enabled = false;
    std::mutex mu;
    std::unordered_set<void*> allocated;
    std::unordered_set<void*> freed;

    void Reset() {
        std::lock_guard<std::mutex> lk(mu);
        allocated.clear();
        freed.clear();
    }
    void Enable() { enabled = true; }
    void Disable() { enabled = false; }

    void OnAlloc(void* p) {
        if (!enabled || !p) return;
        std::lock_guard<std::mutex> lk(mu);
        allocated.insert(p);
    }
    void OnFree(void* p) {
        if (!enabled || !p) return;
        std::lock_guard<std::mutex> lk(mu);
        freed.insert(p);
    }

    bool WasAllocated(void* p) {
        std::lock_guard<std::mutex> lk(mu);
        return allocated.count(p) != 0;
    }
    bool WasFreed(void* p) {
        std::lock_guard<std::mutex> lk(mu);
        return freed.count(p) != 0;
    }
    size_t AllocCount() {
        std::lock_guard<std::mutex> lk(mu);
        return allocated.size();
    }
    size_t FreeCount() {
        std::lock_guard<std::mutex> lk(mu);
        return freed.size();
    }
};

NewDeleteArrayTracker& Tracker() {
    static NewDeleteArrayTracker t;
    return t;
}

struct ScopedArrayNewDeleteTracking {
    ScopedArrayNewDeleteTracking() {
        Tracker().Reset();
        Tracker().Enable();
    }
    ~ScopedArrayNewDeleteTracking() {
        Tracker().Disable();
    }
};

// Use malloc/free to avoid recursion into operator new/new[].
void* MallocOrThrow(std::size_t n) {
    if (n == 0) n = 1;
    if (void* p = std::malloc(n)) return p;
    throw std::bad_alloc();
}

}  // namespace

// Override global array new/delete.
// (This is test-TU global; it will observe any array allocations during the enabled scope.)
void* operator new[](std::size_t n) {
    void* p = MallocOrThrow(n);
    Tracker().OnAlloc(p);
    return p;
}
void operator delete[](void* p) noexcept {
    Tracker().OnFree(p);
    std::free(p);
}
void operator delete[](void* p, std::size_t) noexcept {
    Tracker().OnFree(p);
    std::free(p);
}

namespace {

TEST(DynArrayTest_4, DefaultConstructedIsEmpty_4) {
    tinyxml2::DynArray<int, 4> a;
    EXPECT_TRUE(a.Empty());
    EXPECT_EQ(a.Size(), 0u);
    EXPECT_EQ(a.Capacity(), 4u);
    EXPECT_NE(a.Mem(), nullptr);
}

TEST(DynArrayTest_4, PushThenPopBehavesLikeStack_4) {
    tinyxml2::DynArray<int, 4> a;

    a.Push(123);
    EXPECT_FALSE(a.Empty());
    EXPECT_EQ(a.Size(), 1u);
    EXPECT_EQ(a.PeekTop(), 123);
    EXPECT_EQ(a[0], 123);

    int v = a.Pop();
    EXPECT_EQ(v, 123);
    EXPECT_TRUE(a.Empty());
    EXPECT_EQ(a.Size(), 0u);
}

TEST(DynArrayTest_4, ClearEmptiesArray_4) {
    tinyxml2::DynArray<int, 4> a;
    a.Push(1);
    a.Push(2);
    ASSERT_EQ(a.Size(), 2u);

    a.Clear();
    EXPECT_TRUE(a.Empty());
    EXPECT_EQ(a.Size(), 0u);
}

TEST(DynArrayTest_4, PushArrIncreasesSizeAndProvidesWritableBlock_4) {
    tinyxml2::DynArray<int, 8> a;

    int* block = a.PushArr(3);
    ASSERT_NE(block, nullptr);

    block[0] = 10;
    block[1] = 20;
    block[2] = 30;

    EXPECT_EQ(a.Size(), 3u);
    EXPECT_EQ(a[0], 10);
    EXPECT_EQ(a[1], 20);
    EXPECT_EQ(a[2], 30);
    EXPECT_EQ(a.PeekTop(), 30);
}

TEST(DynArrayTest_4, PopArrReducesSize_4) {
    tinyxml2::DynArray<int, 8> a;

    int* block = a.PushArr(5);
    ASSERT_NE(block, nullptr);
    for (int i = 0; i < 5; ++i) block[i] = i;

    ASSERT_EQ(a.Size(), 5u);

    a.PopArr(2);
    EXPECT_EQ(a.Size(), 3u);
    EXPECT_EQ(a.PeekTop(), 2);
}

TEST(DynArrayTest_4, SwapRemoveReducesSizeAndPreservesOtherElements_4) {
    tinyxml2::DynArray<int, 8> a;
    a.Push(10);
    a.Push(20);
    a.Push(30);
    a.Push(40);

    ASSERT_EQ(a.Size(), 4u);

    // Remove index 1 (value 20). SwapRemove implies order may change.
    a.SwapRemove(1);
    ASSERT_EQ(a.Size(), 3u);

    std::vector<int> got;
    got.reserve(a.Size());
    for (size_t i = 0; i < a.Size(); ++i) got.push_back(a[i]);
    std::sort(got.begin(), got.end());

    std::vector<int> expected = {10, 30, 40};
    std::sort(expected.begin(), expected.end());

    EXPECT_EQ(got, expected);
}

TEST(DynArrayTest_4, DestructorDoesNotDeleteWhenUsingInternalPool_4) {
    // Track only within a tight scope and avoid making assertions inside it.
    const size_t initial_allocs = Tracker().AllocCount();
    const size_t initial_frees = Tracker().FreeCount();

    {
        ScopedArrayNewDeleteTracking scope;
        {
            tinyxml2::DynArray<int, 4> a;
            // Stay within INITIAL_SIZE so we should not require heap growth.
            a.Push(1);
            a.Push(2);
            a.Push(3);
            a.Push(4);
        }
        // At end of inner block, destructor has run while tracking is enabled.
        // If DynArray stayed on the pool, it shouldn't have used new[] at all.
        // (If some other array new[] happened, it'll show up; we verify none were observed.)
        EXPECT_EQ(Tracker().AllocCount(), 0u);
        EXPECT_EQ(Tracker().FreeCount(), 0u);
    }

    (void)initial_allocs;
    (void)initial_frees;
}

TEST(DynArrayTest_4, DestructorDeletesHeapBufferWhenGrownBeyondInitialSize_4) {
    void* grown_mem = nullptr;

    {
        ScopedArrayNewDeleteTracking scope;

        {
            tinyxml2::DynArray<int, 4> a;

            const void* pool_mem = static_cast<const void*>(a.Mem());

            // Force growth by exceeding INITIAL_SIZE.
            a.Push(1);
            a.Push(2);
            a.Push(3);
            a.Push(4);
            a.Push(5);

            const void* after_mem = static_cast<const void*>(a.Mem());
            // If growth happened, Mem() should no longer point to the initial pool buffer.
            ASSERT_NE(after_mem, pool_mem);

            grown_mem = const_cast<void*>(after_mem);
            // The grown buffer should come from new[] (observed during tracking).
            ASSERT_TRUE(Tracker().WasAllocated(grown_mem));
        }

        // Destructor runs here (end of inner block). It should delete[] the grown buffer.
        ASSERT_NE(grown_mem, nullptr);
        EXPECT_TRUE(Tracker().WasFreed(grown_mem));
    }
}

}  // namespace
