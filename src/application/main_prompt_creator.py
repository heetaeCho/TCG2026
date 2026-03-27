# application/main.py
from infrastructure.PyDBImpl.SQLiteAdapter import SQLiteAdapter
from domain.prompt_creator.plugins.prompt_creator import PromptCreator

import json
import os

# Load config.json
with open("config.json", "r") as f:
    config = json.load(f)

# Construct database path
db_path = os.path.join(config["database_path"], config["project_name"] + "_info.db")

db = SQLiteAdapter(db_path)
creator = PromptCreator(db, config["project_name"])

input_data = {
    "type": "function",
    "data": db.select("SELECT * FROM FunctionDefinition")
}
test_function_prompts = creator.run(input_data) # list

input_data = {
    "type": "constructor",
    "data": db.select("SELECT * FROM ConstructorDefinition")
}
test_constructor_prompts = creator.run(input_data) # list

print(len(test_function_prompts))
print(len(test_constructor_prompts))
print(len(test_function_prompts) + len(test_constructor_prompts))

test_id = 1
prompt_save_path = config['prompt_save_path']
for prompt in test_function_prompts:
    with open(prompt_save_path+f'/prompt_{test_id}.txt', 'w', encoding='utf-8') as f:
        prompt = f"The TEST_ID is {test_id}\n" + prompt
        f.write(prompt)
        test_id += 1

for prompt in test_constructor_prompts:
    with open(prompt_save_path+f'/prompt_{test_id}.txt', 'w', encoding='utf-8') as f:
        prompt = f"The TEST_ID is {test_id}\n" + prompt
        f.write(prompt)
        test_id += 1

# for prompt in test_function_prompts:
#     print(prompt)

# for prompt in test_constructor_prompts:
#     print(prompt)

# print(len(test_function_prompts))
# print(len(test_constructor_prompts))