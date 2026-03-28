import os
import re
import subprocess

def parse(file):
  read_flag = False
  new_lines = []
  with open(file, 'r', encoding='utf-8') as f:
    for line in f.readlines():
      if line.startswith('```') and read_flag == False:
        read_flag = True
        continue
      if line.startswith('```') and read_flag:
        read_flag = False
      if read_flag:
        new_lines.append(line)
  return new_lines

def write_to(ix, dir_name, lines: list):
  with open(f"claude/{dir_name}/test_files/test_{ix}.cpp", 'w', encoding='utf-8') as f:
    f.write(''.join(lines))

for dir_name in os.listdir("temp"):
  for txt_file in os.listdir("temp/"+dir_name):
    ix = txt_file.split("_")[-1].replace(".txt", "")
    lines = parse(f"temp/{dir_name}/{txt_file}")
    write_to(ix, dir_name, lines)
