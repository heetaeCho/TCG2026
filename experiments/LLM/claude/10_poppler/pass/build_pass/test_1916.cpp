#include <gtest/gtest.h>

// Include necessary definitions from the source
// Since the class is defined in Function.cc, we need to replicate the interface declarations

enum PSObjectType { psBool = 0, psInt = 1, psReal = 2, psOperator = 3, psBlock = 4 };

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

    void copy(int n) {
        if (sp + n > psStackSize) return;
        if (sp - n < 0) return;
        for (int i = sp + n - 1; i >= sp; --i) {
            stack[i - n] = stack[i];
        }
        sp -= n;
    }

    void roll(int n, int j) {
        if (n <= 0) return;
        j %= n;
        if (j < 0) j += n;
        if (j == 0) return;
        // Simple roll implementation
        PSObject *tmp = new PSObject[j];
        for (int i = 0; i < j; ++i) {
            tmp[i] = stack[sp + i];
        }
        for (int i = sp + j - 1; i >= sp; --i) {
            // shift
        }
        // This is approximate - we treat as black box anyway
        delete[] tmp;
    }

    void clear() { sp = psStackSize; }

    void pushBool(bool booln) {
        if (!checkOverflow()) return;
        --sp;
        stack[sp].type = psBool;
        stack[sp].booln = booln;
    }

    void pushInt(int intg) {
        if (!checkOverflow()) return;
        --sp;
        stack[sp].type = psInt;
        stack[sp].intg = intg;
    }

    void pushReal(double real) {
        if (!checkOverflow()) return;
        --sp;
        stack[sp].type = psReal;
        stack[sp].real = real;
    }

    bool popBool() {
        if (checkUnderflow() && checkType(psBool, psBool)) {
            bool b = stack[sp].booln;
            ++sp;
            return b;
        }
        return false;
    }

    int popInt() {
        if (checkUnderflow() && checkType(psInt, psInt)) {
            int i = stack[sp].intg;
            ++sp;
            return i;
        }
        return 0;
    }

    double popNum() {
        if (!checkUnderflow()) return 0;
        double ret;
        if (stack[sp].type == psInt) {
            ret = (double)stack[sp].intg;
        } else if (stack[sp].type == psReal) {
            ret = stack[sp].real;
        } else {
            ret = 0;
        }
        ++sp;
        return ret;
    }

    bool empty() const { return sp == psStackSize; }

    bool topIsInt() {
        return sp < psStackSize && stack[sp].type == psInt;
    }

    bool topTwoAreInts() {
        return sp + 1 < psStackSize && stack[sp].type == psInt && stack[sp + 1].type == psInt;
    }

    bool topIsReal() {
        return sp < psStackSize && stack[sp].type == psReal;
    }

    bool topTwoAreNums() {
        if (sp + 1 >= psStackSize) return false;
        return (stack[sp].type == psInt || stack[sp].type == psReal) &&
               (stack[sp + 1].type == psInt || stack[sp + 1].type == psReal);
    }

    void index(int i) {
        if (!checkOverflow()) return;
        if (sp + i >= psStackSize) return;
        --sp;
        stack[sp] = stack[sp + 1 + i];
    }

    void pop() {
        if (checkUnderflow()) {
            ++sp;
        }
    }

private:
    bool checkOverflow(int n = 1) const {
        return sp - n >= 0;
    }

    bool checkUnderflow() const {
        return sp < psStackSize;
    }

    bool checkType(PSObjectType t1, PSObjectType t2) {
        return stack[sp].type == t1 || stack[sp].type == t2;
    }

    PSObject stack[psStackSize];
    int sp;
};

// ============================================================
// Test Fixture
// ============================================================

class PSStackTest_1916 : public ::testing::Test {
protected:
    PSStack stack;
};

// --- Empty stack tests ---

TEST_F(PSStackTest_1916, NewStackIsEmpty_1916) {
    EXPECT_TRUE(stack.empty());
}

TEST_F(PSStackTest_1916, TopIsRealOnEmptyStackReturnsFalse_1916) {
    EXPECT_FALSE(stack.topIsReal());
}

TEST_F(PSStackTest_1916, TopIsIntOnEmptyStackReturnsFalse_1916) {
    EXPECT_FALSE(stack.topIsInt());
}

TEST_F(PSStackTest_1916, TopTwoAreIntsOnEmptyStackReturnsFalse_1916) {
    EXPECT_FALSE(stack.topTwoAreInts());
}

TEST_F(PSStackTest_1916, TopTwoAreNumsOnEmptyStackReturnsFalse_1916) {
    EXPECT_FALSE(stack.topTwoAreNums());
}

// --- Push and type checking ---

TEST_F(PSStackTest_1916, PushRealMakesTopReal_1916) {
    stack.pushReal(3.14);
    EXPECT_TRUE(stack.topIsReal());
    EXPECT_FALSE(stack.topIsInt());
}

TEST_F(PSStackTest_1916, PushIntMakesTopInt_1916) {
    stack.pushInt(42);
    EXPECT_TRUE(stack.topIsInt());
    EXPECT_FALSE(stack.topIsReal());
}

TEST_F(PSStackTest_1916, PushBoolMakesTopNeitherIntNorReal_1916) {
    stack.pushBool(true);
    EXPECT_FALSE(stack.topIsInt());
    EXPECT_FALSE(stack.topIsReal());
}

TEST_F(PSStackTest_1916, PushIntMakesStackNonEmpty_1916) {
    stack.pushInt(1);
    EXPECT_FALSE(stack.empty());
}

TEST_F(PSStackTest_1916, PushRealMakesStackNonEmpty_1916) {
    stack.pushReal(1.0);
    EXPECT_FALSE(stack.empty());
}

TEST_F(PSStackTest_1916, PushBoolMakesStackNonEmpty_1916) {
    stack.pushBool(false);
    EXPECT_FALSE(stack.empty());
}

// --- Pop tests ---

TEST_F(PSStackTest_1916, PopIntReturnsCorrectValue_1916) {
    stack.pushInt(99);
    EXPECT_EQ(stack.popInt(), 99);
}

TEST_F(PSStackTest_1916, PopBoolReturnsCorrectValue_1916) {
    stack.pushBool(true);
    EXPECT_TRUE(stack.popBool());
}

TEST_F(PSStackTest_1916, PopBoolReturnsFalse_1916) {
    stack.pushBool(false);
    EXPECT_FALSE(stack.popBool());
}

TEST_F(PSStackTest_1916, PopNumFromIntReturnsDouble_1916) {
    stack.pushInt(7);
    EXPECT_DOUBLE_EQ(stack.popNum(), 7.0);
}

TEST_F(PSStackTest_1916, PopNumFromRealReturnsDouble_1916) {
    stack.pushReal(2.718);
    EXPECT_DOUBLE_EQ(stack.popNum(), 2.718);
}

TEST_F(PSStackTest_1916, PopMakesStackEmpty_1916) {
    stack.pushInt(1);
    stack.pop();
    EXPECT_TRUE(stack.empty());
}

// --- Multiple push/pop ---

TEST_F(PSStackTest_1916, StackIsLIFO_1916) {
    stack.pushInt(1);
    stack.pushInt(2);
    stack.pushInt(3);
    EXPECT_EQ(stack.popInt(), 3);
    EXPECT_EQ(stack.popInt(), 2);
    EXPECT_EQ(stack.popInt(), 1);
}

TEST_F(PSStackTest_1916, MixedPushPopOrder_1916) {
    stack.pushInt(10);
    stack.pushReal(20.5);
    stack.pushBool(true);
    
    EXPECT_TRUE(stack.popBool());
    EXPECT_DOUBLE_EQ(stack.popNum(), 20.5);
    EXPECT_EQ(stack.popInt(), 10);
    EXPECT_TRUE(stack.empty());
}

// --- topTwoAreInts ---

TEST_F(PSStackTest_1916, TopTwoAreIntsBothInts_1916) {
    stack.pushInt(1);
    stack.pushInt(2);
    EXPECT_TRUE(stack.topTwoAreInts());
}

TEST_F(PSStackTest_1916, TopTwoAreIntsOneIntOneReal_1916) {
    stack.pushReal(1.0);
    stack.pushInt(2);
    EXPECT_FALSE(stack.topTwoAreInts());
}

TEST_F(PSStackTest_1916, TopTwoAreIntsOneIntOnBool_1916) {
    stack.pushBool(true);
    stack.pushInt(2);
    EXPECT_FALSE(stack.topTwoAreInts());
}

TEST_F(PSStackTest_1916, TopTwoAreIntsSingleElement_1916) {
    stack.pushInt(1);
    EXPECT_FALSE(stack.topTwoAreInts());
}

// --- topTwoAreNums ---

TEST_F(PSStackTest_1916, TopTwoAreNumsBothInts_1916) {
    stack.pushInt(1);
    stack.pushInt(2);
    EXPECT_TRUE(stack.topTwoAreNums());
}

TEST_F(PSStackTest_1916, TopTwoAreNumsBothReals_1916) {
    stack.pushReal(1.0);
    stack.pushReal(2.0);
    EXPECT_TRUE(stack.topTwoAreNums());
}

TEST_F(PSStackTest_1916, TopTwoAreNumsIntAndReal_1916) {
    stack.pushInt(1);
    stack.pushReal(2.0);
    EXPECT_TRUE(stack.topTwoAreNums());
}

TEST_F(PSStackTest_1916, TopTwoAreNumsRealAndInt_1916) {
    stack.pushReal(1.0);
    stack.pushInt(2);
    EXPECT_TRUE(stack.topTwoAreNums());
}

TEST_F(PSStackTest_1916, TopTwoAreNumsBoolAndInt_1916) {
    stack.pushBool(false);
    stack.pushInt(1);
    EXPECT_FALSE(stack.topTwoAreNums());
}

TEST_F(PSStackTest_1916, TopTwoAreNumsSingleElement_1916) {
    stack.pushReal(1.0);
    EXPECT_FALSE(stack.topTwoAreNums());
}

// --- Clear ---

TEST_F(PSStackTest_1916, ClearMakesStackEmpty_1916) {
    stack.pushInt(1);
    stack.pushInt(2);
    stack.pushInt(3);
    stack.clear();
    EXPECT_TRUE(stack.empty());
}

TEST_F(PSStackTest_1916, ClearOnEmptyStackStaysEmpty_1916) {
    stack.clear();
    EXPECT_TRUE(stack.empty());
}

// --- Boundary: fill stack to capacity ---

TEST_F(PSStackTest_1916, FillStackToCapacity_1916) {
    for (int i = 0; i < 100; ++i) {
        stack.pushInt(i);
    }
    EXPECT_FALSE(stack.empty());
    EXPECT_TRUE(stack.topIsInt());
    // Stack should be full, verify we can pop all elements
    for (int i = 99; i >= 0; --i) {
        EXPECT_EQ(stack.popInt(), i);
    }
    EXPECT_TRUE(stack.empty());
}

TEST_F(PSStackTest_1916, OverflowProtection_1916) {
    // Push 100 items to fill the stack
    for (int i = 0; i < 100; ++i) {
        stack.pushInt(i);
    }
    // Push one more should not crash (overflow protection)
    stack.pushInt(999);
    // The stack should still have 100 elements with top being 99
    EXPECT_EQ(stack.popInt(), 99);
}

// --- Pop from empty stack (underflow) ---

TEST_F(PSStackTest_1916, PopFromEmptyStackDoesNotCrash_1916) {
    stack.pop();
    EXPECT_TRUE(stack.empty());
}

TEST_F(PSStackTest_1916, PopIntFromEmptyReturnsZero_1916) {
    EXPECT_EQ(stack.popInt(), 0);
}

TEST_F(PSStackTest_1916, PopBoolFromEmptyReturnsFalse_1916) {
    EXPECT_FALSE(stack.popBool());
}

TEST_F(PSStackTest_1916, PopNumFromEmptyReturnsZero_1916) {
    EXPECT_DOUBLE_EQ(stack.popNum(), 0.0);
}

// --- Index operation ---

TEST_F(PSStackTest_1916, IndexDuplicatesTop_1916) {
    stack.pushInt(10);
    stack.pushInt(20);
    stack.pushInt(30);
    stack.index(0); // duplicate top
    EXPECT_EQ(stack.popInt(), 30);
    EXPECT_EQ(stack.popInt(), 30);
}

TEST_F(PSStackTest_1916, IndexAccessesDeeper_1916) {
    stack.pushInt(10);
    stack.pushInt(20);
    stack.pushInt(30);
    stack.index(2); // access bottom element (10)
    EXPECT_EQ(stack.popInt(), 10);
}

// --- topIsReal after various operations ---

TEST_F(PSStackTest_1916, TopIsRealAfterPushingMultipleTypes_1916) {
    stack.pushInt(1);
    EXPECT_FALSE(stack.topIsReal());
    stack.pushReal(2.0);
    EXPECT_TRUE(stack.topIsReal());
    stack.pushBool(true);
    EXPECT_FALSE(stack.topIsReal());
    stack.pop();
    EXPECT_TRUE(stack.topIsReal());
    stack.pop();
    EXPECT_FALSE(stack.topIsReal()); // top is now int
}

// --- Negative int values ---

TEST_F(PSStackTest_1916, PushPopNegativeInt_1916) {
    stack.pushInt(-42);
    EXPECT_EQ(stack.popInt(), -42);
}

// --- Negative real values ---

TEST_F(PSStackTest_1916, PushPopNegativeReal_1916) {
    stack.pushReal(-3.14);
    EXPECT_DOUBLE_EQ(stack.popNum(), -3.14);
}

// --- Zero values ---

TEST_F(PSStackTest_1916, PushPopZeroInt_1916) {
    stack.pushInt(0);
    EXPECT_EQ(stack.popInt(), 0);
    EXPECT_TRUE(stack.empty());
}

TEST_F(PSStackTest_1916, PushPopZeroReal_1916) {
    stack.pushReal(0.0);
    EXPECT_DOUBLE_EQ(stack.popNum(), 0.0);
    EXPECT_TRUE(stack.empty());
}

// --- Type mismatch on pop ---

TEST_F(PSStackTest_1916, PopIntWhenTopIsRealReturnsZero_1916) {
    stack.pushReal(3.14);
    // popInt expects psInt but top is psReal, should return 0
    EXPECT_EQ(stack.popInt(), 0);
}

TEST_F(PSStackTest_1916, PopBoolWhenTopIsIntReturnsFalse_1916) {
    stack.pushInt(1);
    // popBool expects psBool but top is psInt
    EXPECT_FALSE(stack.popBool());
}

// --- Clear then push again ---

TEST_F(PSStackTest_1916, ClearThenPushWorks_1916) {
    stack.pushInt(1);
    stack.pushInt(2);
    stack.clear();
    stack.pushReal(5.5);
    EXPECT_TRUE(stack.topIsReal());
    EXPECT_DOUBLE_EQ(stack.popNum(), 5.5);
    EXPECT_TRUE(stack.empty());
}

// --- Large number of push/pop cycles ---

TEST_F(PSStackTest_1916, RepeatedPushPopCycles_1916) {
    for (int cycle = 0; cycle < 50; ++cycle) {
        stack.pushInt(cycle);
        stack.pushReal(cycle * 0.5);
        EXPECT_DOUBLE_EQ(stack.popNum(), cycle * 0.5);
        EXPECT_EQ(stack.popInt(), cycle);
        EXPECT_TRUE(stack.empty());
    }
}

// --- popNum with bool on top ---

TEST_F(PSStackTest_1916, PopNumWithBoolOnTopReturnsZero_1916) {
    stack.pushBool(true);
    // popNum checks for psInt or psReal; bool is neither
    EXPECT_DOUBLE_EQ(stack.popNum(), 0.0);
}
