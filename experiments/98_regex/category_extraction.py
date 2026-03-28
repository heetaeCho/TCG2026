import os

def parse_td_file(lines):
    result = {}
    current_comment = None
    
    i = 0
    while i < len(lines):
        line = lines[i].strip()

        # 주석 (카테고리)
        if line.startswith('//') and not line.startswith('//==='):
            current_comment = line[2:].strip()
            i += 1
            continue

        # def err_ 로 시작하는 경우만
        if line.startswith('def err_'):
            # };  나올 때까지 블록 수집
            block = []
            while i < len(lines):
                block.append(lines[i].strip())
                if lines[i].strip().endswith('};'):
                    break
                i += 1

            block_text = ' '.join(block)

            # Error< 가 있는 경우만
            if 'Error<' in block_text:
                # err_id 추출
                err_id = block_text.split()[1].split(':')[0]

                # 문자열 추출: \" 임시 치환 후 " 로 split
                block_text = block_text.replace('\\"', '<<Q>>')
                parts = block_text.split('"')
                err_msg = ''.join(parts[j] for j in range(1, len(parts), 2))
                err_msg = err_msg.replace('<<Q>>', '"')

                if current_comment:
                    result.setdefault(current_comment, []).append((err_id, err_msg))

        i += 1
    
    return result

if __name__ == "__main__":
    td_files = ["DiagnosticLexKinds.td", "DiagnosticParseKinds.td", "DiagnosticSemaKinds.td"]
    td_file = os.path.join("experiments/98_temp", td_files[0])
    with open(td_file, 'r', encoding='utf-8') as f:
        result = parse_td_file(f.readlines())
        cnt = 0
        for key in result.keys():
            print(key)
            print(len(result[key]))
            cnt += len(result[key])
        print(cnt)