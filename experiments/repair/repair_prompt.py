CONDITION_1=\
'''### 1. Original Goal & Context
{init_prompt}

### 2. Current Error Message
Current Build Error:
{errors}

### 3. Progress History
{attempt}

Important:
Do not reintroduce previously resolved errors.

### 4. Previous Code
{test_code}

### 5. Instruction
Please minimally revise the previous code to fix the current error while preserving all previously successful test logic and coverage intent.'''

CONDITION_2=\
'''### 1. Original Goal & Context
{init_prompt}

### 2. Repair Information (Variable)
Current Build Error:
{errors}

Current Error Type:
{errors_categories}

Description:
{category_descriptions}

### 3. Progress History
{attempt}

Important:
Do not reintroduce previously resolved errors.

### 4. Previous Code
{test_code}

### 5. Instruction
Please minimally revise the previous code to fix the current error while preserving all previously successful test logic and coverage intent.'''

CONDITION_3=\
'''### 1. Original Goal & Context
{init_prompt}

### 2. Repair Information (Variable)
Current Build Error:
{errors}

Current Error Type:
{errors_categories}

Description:
{category_descriptions}

Solution Guide
{solutions}

### 3. Progress History
{attempt}

Important:
Do not reintroduce previously resolved errors.

### 4. Previous Code
{test_code}

### 5. Instruction
Please minimally revise the previous code to fix the current error while preserving all previously successful test logic and coverage intent.'''