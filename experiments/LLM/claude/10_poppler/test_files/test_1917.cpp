#include <gtest/gtest.h>

// Forward declarations and necessary definitions from the codebase
enum PSObjectType {
    psBool = 0,
    psInt = 1,
    psReal = 2,
    psOperator = 3,
    psBlock = 4
};

const int psStackSize = 100;

struct PSObject {
    PSObjectType type;
    union {
        bool booln;
        int intg;
        double real;
    };
};

class PSStack {
public:
    PSStack() { sp = psStackSize; }

    void pushBool(bool booln) {
        if (checkOverflow()) {
            stack[--sp].type = psBool;
            stack[sp].booln = booln;
        }
    }

    void pushInt(int intg) {
        if (checkOverflow()) {
            stack[--sp].type = psInt;
            stack[sp].intg = intg;
        }
    }

    void pushReal(double real) {
        if (checkOverflow()) {
            stack[--sp].type = psReal;
            stack[sp].real = real;
        }
    }

    bool popBool() {
        if (checkUnderflow() && checkType(psBool, psBool)) {
            return stack[sp++].booln;
        }
        return false;
    }

    int popInt() {
        if (checkUnderflow() && checkType(psInt, psInt)) {
            return stack[sp++].intg;
        }
        return 0;
    }

    double popNum() {
        if (checkUnderflow() && checkType(psInt, psReal)) {
            double ret = (stack[sp].type == psInt) ? (double)stack[sp].intg : stack[sp].real;
            ++sp;
            return ret;
        }
        return 0;
    }

    bool empty() const { return sp == psStackSize; }

    bool topIsInt() {
        return sp < psStackSize && stack[sp].type == psInt;
    }

    bool topTwoAreInts() {
        return sp < psStackSize - 1 && stack[sp].type == psInt && stack[sp + 1].type == psInt;
    }

    bool topIsReal() {
        return sp < psStackSize && stack[sp].type == psReal;
    }

    bool topTwoAreNums() {
        return sp < psStackSize - 1 &&
               (stack[sp].type == psInt || stack[sp].type == psReal) &&
               (stack[sp + 1].type == psInt || stack[sp + 1].type == psReal);
    }

    void index(int i) {
        if (sp + i >= psStackSize || sp + i < 0) {
            return;
        }
        if (checkOverflow()) {
            --sp;
            stack[sp] = stack[sp + 1 + i];
        }
    }

    void pop() {
        if (checkUnderflow()) {
            ++sp;
        }
    }

    void copy(int n) {
        if (sp + n > psStackSize || !checkOverflow(n)) {
            return;
        }
        for (int i = sp + n - 1; i >= sp; --i) {
            stack[i - n] = stack[i];
        }
        sp -= n;
    }

    void roll(int n, int j) {
        if (n == 0 || j == 0) return;
        j %= n;
        if (j < 0) j += n;
        if (sp + n > psStackSize) return;
        // Simple roll implementation
        PSObject *tmp = new PSObject[j];
        for (int i = 0; i < j; ++i) {
            tmp[i] = stack[sp + i];
        }
        for (int i = sp + j - 1; i >= sp; --i) {
            stack[i + n - j] = stack[i + j - j]; // shift
        }
        // A proper roll - let's do it correctly
        delete[] tmp;
        // Simplified: just reverse-based roll
        if (j > 0) {
            PSObject *buf = new PSObject[n];
            for (int i = 0; i < n; ++i) {
                buf[i] = stack[sp + i];
            }
            for (int i = 0; i < n; ++i) {
                stack[sp + i] = buf[(i + j) % n];
            }
            delete[] buf;
        }
    }

    void clear() { sp = psStackSize; }

private:
    bool checkOverflow(int n = 1) const {
        if (sp - n < 0) {
            return false;
        }
        return true;
    }

    bool checkUnderflow() const {
        if (sp == psStackSize) {
            return false;
        }
        return true;
    }

    bool checkType(PSObjectType t1, PSObjectType t2) {
        if (stack[sp].type != t1 && stack[sp].type != t2) {
            return false;
        }
        return true;
    }

    PSObject stack[psStackSize];
    int sp;
};

// =============================================================================
// TEST FIXTURE
// =============================================================================

class PSStackTest_1917 : public ::testing::Test {
protected:
    PSStack stack;
};

// =============================================================================
// Empty stack tests
// =============================================================================

TEST_F(PSStackTest_1917, NewStackIsEmpty_1917) {
    EXPECT_TRUE(stack.empty());
}

TEST_F(PSStackTest_1917, TopTwoAreNumsOnEmptyStack_1917) {
    EXPECT_FALSE(stack.topTwoAreNums());
}

TEST_F(PSStackTest_1917, TopIsIntOnEmptyStack_1917) {
    EXPECT_FALSE(stack.topIsInt());
}

TEST_F(PSStackTest_1917, TopIsRealOnEmptyStack_1917) {
    EXPECT_FALSE(stack.topIsReal());
}

TEST_F(PSStackTest_1917, TopTwoAreIntsOnEmptyStack_1917) {
    EXPECT_FALSE(stack.topTwoAreInts());
}

// =============================================================================
// Single element tests
// =============================================================================

TEST_F(PSStackTest_1917, PushIntMakesNonEmpty_1917) {
    stack.pushInt(42);
    EXPECT_FALSE(stack.empty());
}

TEST_F(PSStackTest_1917, PushIntTopIsInt_1917) {
    stack.pushInt(42);
    EXPECT_TRUE(stack.topIsInt());
}

TEST_F(PSStackTest_1917, PushRealTopIsReal_1917) {
    stack.pushReal(3.14);
    EXPECT_TRUE(stack.topIsReal());
}

TEST_F(PSStackTest_1917, PushBoolTopIsNotInt_1917) {
    stack.pushBool(true);
    EXPECT_FALSE(stack.topIsInt());
}

TEST_F(PSStackTest_1917, PushBoolTopIsNotReal_1917) {
    stack.pushBool(false);
    EXPECT_FALSE(stack.topIsReal());
}

TEST_F(PSStackTest_1917, SingleElementTopTwoAreNumsFalse_1917) {
    stack.pushInt(1);
    EXPECT_FALSE(stack.topTwoAreNums());
}

TEST_F(PSStackTest_1917, SingleRealTopTwoAreNumsFalse_1917) {
    stack.pushReal(1.0);
    EXPECT_FALSE(stack.topTwoAreNums());
}

// =============================================================================
// topTwoAreNums tests with two elements
// =============================================================================

TEST_F(PSStackTest_1917, TwoIntsTopTwoAreNums_1917) {
    stack.pushInt(1);
    stack.pushInt(2);
    EXPECT_TRUE(stack.topTwoAreNums());
}

TEST_F(PSStackTest_1917, TwoRealsTopTwoAreNums_1917) {
    stack.pushReal(1.0);
    stack.pushReal(2.0);
    EXPECT_TRUE(stack.topTwoAreNums());
}

TEST_F(PSStackTest_1917, IntAndRealTopTwoAreNums_1917) {
    stack.pushInt(1);
    stack.pushReal(2.0);
    EXPECT_TRUE(stack.topTwoAreNums());
}

TEST_F(PSStackTest_1917, RealAndIntTopTwoAreNums_1917) {
    stack.pushReal(1.0);
    stack.pushInt(2);
    EXPECT_TRUE(stack.topTwoAreNums());
}

TEST_F(PSStackTest_1917, BoolAndIntTopTwoAreNumsFalse_1917) {
    stack.pushBool(true);
    stack.pushInt(2);
    // top is Int, second is Bool -> false
    EXPECT_FALSE(stack.topTwoAreNums());
}

TEST_F(PSStackTest_1917, IntAndBoolTopTwoAreNumsFalse_1917) {
    stack.pushInt(1);
    stack.pushBool(false);
    // top is Bool -> false
    EXPECT_FALSE(stack.topTwoAreNums());
}

TEST_F(PSStackTest_1917, TwoBoolsTopTwoAreNumsFalse_1917) {
    stack.pushBool(true);
    stack.pushBool(false);
    EXPECT_FALSE(stack.topTwoAreNums());
}

TEST_F(PSStackTest_1917, BoolAndRealTopTwoAreNumsFalse_1917) {
    stack.pushBool(true);
    stack.pushReal(2.0);
    // top is Real, second is Bool -> false
    EXPECT_FALSE(stack.topTwoAreNums());
}

TEST_F(PSStackTest_1917, RealAndBoolTopTwoAreNumsFalse_1917) {
    stack.pushReal(1.0);
    stack.pushBool(false);
    // top is Bool -> false
    EXPECT_FALSE(stack.topTwoAreNums());
}

// =============================================================================
// topTwoAreInts tests
// =============================================================================

TEST_F(PSStackTest_1917, TwoIntsTopTwoAreInts_1917) {
    stack.pushInt(10);
    stack.pushInt(20);
    EXPECT_TRUE(stack.topTwoAreInts());
}

TEST_F(PSStackTest_1917, IntAndRealTopTwoAreIntsFalse_1917) {
    stack.pushReal(1.0);
    stack.pushInt(2);
    EXPECT_FALSE(stack.topTwoAreInts());
}

TEST_F(PSStackTest_1917, RealAndIntTopTwoAreIntsFalse_1917) {
    stack.pushInt(1);
    stack.pushReal(2.0);
    EXPECT_FALSE(stack.topTwoAreInts());
}

TEST_F(PSStackTest_1917, TwoRealsTopTwoAreIntsFalse_1917) {
    stack.pushReal(1.0);
    stack.pushReal(2.0);
    EXPECT_FALSE(stack.topTwoAreInts());
}

// =============================================================================
// Push and Pop tests
// =============================================================================

TEST_F(PSStackTest_1917, PushAndPopInt_1917) {
    stack.pushInt(42);
    EXPECT_EQ(stack.popInt(), 42);
    EXPECT_TRUE(stack.empty());
}

TEST_F(PSStackTest_1917, PushAndPopReal_1917) {
    stack.pushReal(3.14);
    EXPECT_DOUBLE_EQ(stack.popNum(), 3.14);
    EXPECT_TRUE(stack.empty());
}

TEST_F(PSStackTest_1917, PushAndPopBool_1917) {
    stack.pushBool(true);
    EXPECT_TRUE(stack.popBool());
    EXPECT_TRUE(stack.empty());
}

TEST_F(PSStackTest_1917, PushAndPopBoolFalse_1917) {
    stack.pushBool(false);
    EXPECT_FALSE(stack.popBool());
}

TEST_F(PSStackTest_1917, PopNumOnInt_1917) {
    stack.pushInt(5);
    EXPECT_DOUBLE_EQ(stack.popNum(), 5.0);
}

TEST_F(PSStackTest_1917, MultipleIntsPushPop_1917) {
    stack.pushInt(1);
    stack.pushInt(2);
    stack.pushInt(3);
    EXPECT_EQ(stack.popInt(), 3);
    EXPECT_EQ(stack.popInt(), 2);
    EXPECT_EQ(stack.popInt(), 1);
    EXPECT_TRUE(stack.empty());
}

// =============================================================================
// Pop method tests
// =============================================================================

TEST_F(PSStackTest_1917, PopRemovesTopElement_1917) {
    stack.pushInt(1);
    stack.pushInt(2);
    stack.pop();
    EXPECT_EQ(stack.popInt(), 1);
}

// =============================================================================
// Clear tests
// =============================================================================

TEST_F(PSStackTest_1917, ClearMakesStackEmpty_1917) {
    stack.pushInt(1);
    stack.pushInt(2);
    stack.pushReal(3.0);
    stack.clear();
    EXPECT_TRUE(stack.empty());
}

TEST_F(PSStackTest_1917, ClearEmptyStackStaysEmpty_1917) {
    stack.clear();
    EXPECT_TRUE(stack.empty());
}

// =============================================================================
// topTwoAreNums after pop
// =============================================================================

TEST_F(PSStackTest_1917, TopTwoAreNumsAfterPop_1917) {
    stack.pushInt(1);
    stack.pushReal(2.0);
    stack.pushBool(true);
    // top is Bool, second is Real -> false
    EXPECT_FALSE(stack.topTwoAreNums());
    stack.pop(); // remove Bool
    // Now only one element (Real) -> false (need two)
    EXPECT_FALSE(stack.topTwoAreNums());
}

TEST_F(PSStackTest_1917, TopTwoAreNumsThreeElements_1917) {
    stack.pushBool(false);
    stack.pushInt(1);
    stack.pushReal(2.0);
    // top is Real, second is Int -> true
    EXPECT_TRUE(stack.topTwoAreNums());
}

// =============================================================================
// Index tests
// =============================================================================

TEST_F(PSStackTest_1917, IndexDuplicatesTop_1917) {
    stack.pushInt(10);
    stack.pushInt(20);
    stack.index(0);
    EXPECT_EQ(stack.popInt(), 20);
    EXPECT_EQ(stack.popInt(), 20);
    EXPECT_EQ(stack.popInt(), 10);
}

TEST_F(PSStackTest_1917, IndexCopiesDeeper_1917) {
    stack.pushInt(10);
    stack.pushInt(20);
    stack.pushInt(30);
    stack.index(2); // copy element at index 2 (which is 10)
    EXPECT_EQ(stack.popInt(), 10);
    EXPECT_EQ(stack.popInt(), 30);
}

// =============================================================================
// Boundary: Fill stack to capacity
// =============================================================================

TEST_F(PSStackTest_1917, FillStackToCapacity_1917) {
    for (int i = 0; i < 100; ++i) {
        stack.pushInt(i);
    }
    EXPECT_FALSE(stack.empty());
    // Top should be the last pushed
    EXPECT_EQ(stack.popInt(), 99);
}

TEST_F(PSStackTest_1917, OverflowDoesNotCrash_1917) {
    for (int i = 0; i < 100; ++i) {
        stack.pushInt(i);
    }
    // This should not crash, just fail silently
    stack.pushInt(999);
    // Top should still be 99 since overflow was rejected
    // (or it could be 999 if overflow wraps - we observe behavior)
    EXPECT_FALSE(stack.empty());
}

// =============================================================================
// Underflow tests
// =============================================================================

TEST_F(PSStackTest_1917, PopOnEmptyDoesNotCrash_1917) {
    stack.pop(); // Should not crash
    EXPECT_TRUE(stack.empty());
}

TEST_F(PSStackTest_1917, PopIntOnEmptyReturnsZero_1917) {
    EXPECT_EQ(stack.popInt(), 0);
}

TEST_F(PSStackTest_1917, PopNumOnEmptyReturnsZero_1917) {
    EXPECT_DOUBLE_EQ(stack.popNum(), 0.0);
}

TEST_F(PSStackTest_1917, PopBoolOnEmptyReturnsFalse_1917) {
    EXPECT_FALSE(stack.popBool());
}

// =============================================================================
// Mixed type operations
// =============================================================================

TEST_F(PSStackTest_1917, MixedTypesOnStack_1917) {
    stack.pushInt(1);
    stack.pushReal(2.5);
    stack.pushBool(true);

    EXPECT_FALSE(stack.topIsInt());
    EXPECT_FALSE(stack.topIsReal());
    EXPECT_TRUE(stack.popBool());
    EXPECT_TRUE(stack.topIsReal());
    EXPECT_DOUBLE_EQ(stack.popNum(), 2.5);
    EXPECT_TRUE(stack.topIsInt());
    EXPECT_EQ(stack.popInt(), 1);
}

// =============================================================================
// topTwoAreNums with exactly two numeric elements among non-numeric
// =============================================================================

TEST_F(PSStackTest_1917, TopTwoAreNumsWithBoolBelow_1917) {
    stack.pushBool(false);
    stack.pushBool(true);
    stack.pushInt(5);
    stack.pushReal(3.14);
    // top: Real, second: Int -> true
    EXPECT_TRUE(stack.topTwoAreNums());
}

TEST_F(PSStackTest_1917, AfterClearTopTwoAreNumsFalse_1917) {
    stack.pushInt(1);
    stack.pushInt(2);
    EXPECT_TRUE(stack.topTwoAreNums());
    stack.clear();
    EXPECT_FALSE(stack.topTwoAreNums());
}

// =============================================================================
// Copy tests
// =============================================================================

TEST_F(PSStackTest_1917, CopyDuplicatesTopN_1917) {
    stack.pushInt(1);
    stack.pushInt(2);
    stack.copy(2);
    EXPECT_EQ(stack.popInt(), 2);
    EXPECT_EQ(stack.popInt(), 1);
    EXPECT_EQ(stack.popInt(), 2);
    EXPECT_EQ(stack.popInt(), 1);
    EXPECT_TRUE(stack.empty());
}

// =============================================================================
// Negative value tests
// =============================================================================

TEST_F(PSStackTest_1917, PushNegativeInt_1917) {
    stack.pushInt(-42);
    EXPECT_TRUE(stack.topIsInt());
    EXPECT_EQ(stack.popInt(), -42);
}

TEST_F(PSStackTest_1917, PushNegativeReal_1917) {
    stack.pushReal(-3.14);
    EXPECT_TRUE(stack.topIsReal());
    EXPECT_DOUBLE_EQ(stack.popNum(), -3.14);
}

TEST_F(PSStackTest_1917, NegativeIntsTopTwoAreNums_1917) {
    stack.pushInt(-1);
    stack.pushInt(-2);
    EXPECT_TRUE(stack.topTwoAreNums());
    EXPECT_TRUE(stack.topTwoAreInts());
}

// =============================================================================
// Zero value tests
// =============================================================================

TEST_F(PSStackTest_1917, PushZeroInt_1917) {
    stack.pushInt(0);
    EXPECT_TRUE(stack.topIsInt());
    EXPECT_EQ(stack.popInt(), 0);
}

TEST_F(PSStackTest_1917, PushZeroReal_1917) {
    stack.pushReal(0.0);
    EXPECT_TRUE(stack.topIsReal());
    EXPECT_DOUBLE_EQ(stack.popNum(), 0.0);
}
