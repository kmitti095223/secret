### ������\������ꍇ�A�C�����C�������� `$` / `$` �ň͂݁A�f�B�X�v���C������ `$$` / `$$` �ň݂͂܂��B

#### �C�����C��������\������ꍇ�̗�:
`$ax^2 + bx + c = 0$`

#### �f�B�X�v���C������\������ꍇ�̗�:
```
$$
x = \\frac{{-b \\pm \\sqrt{{b^2 - 4ac}}}}{{2a}}
$$
```
user
�ȉ��̃v���O�������������������B
map�̃L�[��string����char*�ɕύX���đ����ł��Ȃ����H


#include <iostream>
#include <map>
#include <string>
#include <cstdio>
#include <cstring>
using namespace std;

const int MAX_BUF = 1 << 24; // �o�b�t�@�T�C�Y16MB
char input_buffer[MAX_BUF];  // ���̓o�b�t�@
char output_buffer[MAX_BUF]; // �o�̓o�b�t�@
int buf_index = 0;           // ���̓o�b�t�@�̌��݈ʒu
int out_index = 0;           // �o�̓o�b�t�@�̌��݈ʒu

// ���S�Ȑ����ǂݍ���
inline int read_int() {
    int x = 0, neg = 1;
    while (input_buffer[buf_index] < '0' || input_buffer[buf_index] > '9') {
        if (input_buffer[buf_index] == '-') neg = -1; // �����Ή�
        ++buf_index;
    }
    while (input_buffer[buf_index] >= '0' && input_buffer[buf_index] <= '9') {
        x = x * 10 + (input_buffer[buf_index] - '0');
        ++buf_index;
    }
    return x * neg;
}

// ���S�ȕ�����ǂݍ���
inline void read_string(string& s) {
    // �󔒂���s���X�L�b�v
    while (input_buffer[buf_index] == ' ' || input_buffer[buf_index] == '\n') ++buf_index;

    s.clear();
    while (input_buffer[buf_index] != ' ' && input_buffer[buf_index] != '\n' && input_buffer[buf_index] != '\0') {
        s += input_buffer[buf_index];
        ++buf_index;
    }
}

// �����ȕ�����o��
inline void write_string(const char* str) {
    while (*str != '\0') {
        output_buffer[out_index++] = *str++;
    }
    output_buffer[out_index++] = ' ';
}

// �����Ȑ����o��
inline void write_int(int x) {
    static char temp_buf[12];
    int pos = 0;
    if (x < 0) {
        output_buffer[out_index++] = '-';
        x = -x;
    }
    do {
        temp_buf[pos++] = '0' + (x % 10);
        x /= 10;
    } while (x > 0);
    while (pos > 0) {
        output_buffer[out_index++] = temp_buf[--pos];
    }
    output_buffer[out_index++] = '\n';
}

// ���o�͏����̃t���b�V��
inline void flush_output() {
    fwrite(output_buffer, 1, out_index, stdout);
    out_index = 0;
}

int main() {
    // �W�����͂��ꊇ�œǂݍ���
    int input_size = fread(input_buffer, 1, MAX_BUF - 1, stdin);
    if (input_size == 0 || input_size >= MAX_BUF - 1) {
        cerr << "Input error or buffer overflow!" << endl;
        return 1; // ���̓G���[
    }
    input_buffer[input_size] = '\0'; // ���̓o�b�t�@�I�[��ݒ�

    int q = read_int(); // �N�G�����̓ǂݍ���
    map<string, int> M; // �����f�[�^�\��

    while (q--) {
        int operation = read_int(); // ����^�C�v�擾

        if (operation == 0) { // insert
            string key;
            int value;
            read_string(key);  // �L�[�̎擾
            value = read_int(); // �l�̎擾
            M[key] = value;    // �}�b�v�ɑ}���܂��͍X�V
        } else if (operation == 1) { // get
            string key;
            read_string(key);  // �L�[�̎擾
            auto it = M.find(key); // �}�b�v����
            if (it != M.end()) {
                write_int(it->second);
            } else {
                write_int(0);
            }
        } else if (operation == 2) { // delete
            string key;
            read_string(key);  // �L�[�̎擾
            M.erase(key);      // �}�b�v����폜
        } else if (operation == 3) { // dump
            string L, R;
            read_string(L);    // �͈̓L�[ (�J�n)
            read_string(R);    // �͈̓L�[ (�I��)

            auto start_it = M.lower_bound(L); // �͈͂̊J�n�ʒu
            auto end_it = M.upper_bound(R);   // �͈͂̏I���ʒu
            for (auto it = start_it; it != end_it; ++it) {
                write_string(it->first.c_str());
                write_int(it->second);
            }
        }
    }

    flush_output(); // �o�͂��t���b�V��
    return 0;
}
������������
`std::map` �̃L�[�� `std::string` ���� `char*` �ɕύX���č���������̂́A����̏������ł͌��ʓI�ƌ����܂����A`std::map` �ɂ͈ȉ��̂悤�ȉۑ肪�o�Ă��܂��B

1. **��r�֐��̐ݒ肪�K�v:**
   - `std::map` �͓����ŃL�[���r���ď����t�����s�����߁A`char*` ���L�[�ɂ���ꍇ�A�K�؂Ȕ�r�֐���ݒ肵�Ȃ���΂Ȃ�܂���B�f�t�H���g�ł̓|�C���^�A�h���X���r���邾���Ȃ̂ŁA������R���e���c�̔�r���J�X�^�}�C�Y����K�v������܂��B���̔�r�ɂ� `strcmp` ���悭�g���܂��B

2. **���L���̊Ǘ�:**
   - `std::string` �Ȃ烁�����Ǘ��������I�ɍs���܂����A`char*` ���L�[�ɂ����ꍇ�A������̏��L���Ǘ��i�܂�A�ǂ��Ń��������m�ۂ��A�ǂ��ŉ�����邩�j�������ōs���K�v������܂��B���܂��Ǘ����Ȃ��ƃ��������[�N�▢��`����������N�����\��������܂��B

3. **���x�̌���:**
   - ��ʂ̏d�����镶���񂪕p�ɂɎg�p�����ꍇ�A`char*` �����܂��g���΃����������⑬�x�����シ��ꍇ������܂��B�������A�L�[�̔�r���������胁�������蓖�Ă����G�ɂȂ�P�[�X�ł͋t���ʂɂȂ蓾��̂ŁA���ʂ����؂���K�v������܂��B

�ȉ��͂��Ȃ��̃v���O�����ɂ����āA`std::map<string, int>` �� `std::map<char*, int>` �ɕύX���č����������݂�������ł��B

```cpp
#include <iostream>
#include <map>
#include <string>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

const int MAX_BUF = 1 << 24; // �o�b�t�@�T�C�Y16MB
char input_buffer[MAX_BUF];  // ���̓o�b�t�@
char output_buffer[MAX_BUF]; // �o�̓o�b�t�@
int buf_index = 0;           // ���̓o�b�t�@�̌��݈ʒu
int out_index = 0;           // �o�̓o�b�t�@�̌��݈ʒu

// ��r�֐�
struct cmp_str {
    bool operator()(const char* a, const char* b) const {
        return strcmp(a, b) < 0;
    }
};

// ���S�Ȑ����ǂݍ���
inline int read_int() {
    int x = 0, neg = 1;
    while (input_buffer[buf_index] < '0' || input_buffer[buf_index] > '9') {
        if (input_buffer[buf_index] == '-') neg = -1; // �����Ή�
        ++buf_index;
    }
    while (input_buffer[buf_index] >= '0' && input_buffer[buf_index] <= '9') {
        x = x * 10 + (input_buffer[buf_index] - '0');
        ++buf_index;
    }
    return x * neg;
}

// ���S�ȕ�����ǂݍ���
inline char* read_cstring() {
    // �󔒂���s���X�L�b�v
    while (input_buffer[buf_index] == ' ' || input_buffer[buf_index] == '\n') ++buf_index;

    char* start = &input_buffer[buf_index];

    while (input_buffer[buf_index] != ' ' && input_buffer[buf_index] != '\n' && input_buffer[buf_index] != '\0') {
        ++buf_index;
    }

    input_buffer[buf_index++] = '\0'; // �I�[��}��
    return start;
}

// �����ȕ�����o��
inline void write_string(const char* str) {
    while (*str != '\0') {
        output_buffer[out_index++] = *str++;
    }
    output_buffer[out_index++] = ' ';
}

// �����Ȑ����o��
inline void write_int(int x) {
    static char temp_buf[12];
    int pos = 0;
    if (x < 0) {
        output_buffer[out_index++] = '-';
        x = -x;
    }
    do {
        temp_buf[pos++] = '0' + (x % 10);
        x /= 10;
    } while (x > 0);
    while (pos > 0) {
        output_buffer[out_index++] = temp_buf[--pos];
    }
    output_buffer[out_index++] = '\n';
}

// ���o�͏����̃t���b�V��
inline void flush_output() {
    fwrite(output_buffer, 1, out_index, stdout);
    out_index = 0;
}

int main() {
    // �W�����͂��ꊇ�œǂݍ���
    int input_size = fread(input_buffer, 1, MAX_BUF - 1, stdin);
    if (input_size == 0 || input_size >= MAX_BUF - 1) {
        cerr << "Input error or buffer overflow!" << endl;
        return 1; // ���̓G���[
    }
    input_buffer[input_size] = '\0'; // ���̓o�b�t�@�I�[��ݒ�

    int q = read_int(); // �N�G�����̓ǂݍ���
    map<char*, int, cmp_str> M; // �����f�[�^�\�� (��r�֐��w��)

    while (q--) {
        int operation = read_int(); // ����^�C�v�擾

        if (operation == 0) { // insert
            char* key = read_cstring();
            int value = read_int();
            // ���������R�s�[���ĐV�����L�[���쐬
            char* new_key = strdup(key);
            M[new_key] = value; // �}�b�v�ɑ}���܂��͍X�V
        } else if (operation == 1) { // get
            char* key = read_cstring();
            auto it = M.find(key); // �}�b�v����
            if (it != M.end()) {
                write_int(it->second);
            } else {
                write_int(0);
            }
        } else if (operation == 2) { // delete
            char* key = read_cstring();
            auto it = M.find(key);
            if (it != M.end()) {
                free(it->first); // �����������
                M.erase(it); // �}�b�v����L�[���폜
            }
        } else if (operation == 3) { // dump
            char* L = read_cstring();
            char* R = read_cstring();

            auto start_it = M.lower_bound(L); // �͈͂̊J�n�ʒu
            auto end_it = M.upper_bound(R);   // �͈͂̏I���ʒu
            for (auto it = start_it; it != end_it; ++it) {
                write_string(it->first);
                write_int(it->second);
            }
        }
    }

    // ���������
    for (auto it = M.begin(); it != M.end(); ++it) {
        free(it->first);
    }

    flush_output(); // �o�͂��t���b�V��
    return 0;
}
```

### �C�������_
1. **��r�֐��̒ǉ�:**
   - `cmp_str` ��p���� `strcmp` ���g������r�������B

2. **`read_string` �� `read_cstring` �ɕύX:**
   - �o�b�t�@���̕���������̂܂� `char*` �Ƃ��ēǂݍ��ށB

3. **���I�������Ǘ��̒ǉ�:**
   - �L�[�� `strdup` �ŃR�s�[���� `map` �ɕۑ��B
   - �폜���� `free` ���Ăяo���ă�����������B

4. **���������[�N�̖h�~:**
   - �v���O�����I�����ɂ��ׂẴL�[������B

### ���ӓ_
- �������͈͌�������ꍇ�ɑ�ʂ̘A�������L�[����������P�[�X�ł́A`std::string` ���R�X�g�������Ȃ�ꍇ������܂��B
- �v���O�����̎��s���Ԃ����������v���t�@�C�����O���āA���ʂ��m�F���Ă��������B

### �������̎�i�̂����ЂƂ�
��K�̓f�[�^����ɑ����N�G���ł���΁A`std::map` �� `std::unordered_map` �ɒu����������@�������ł��܂��i�������A�͈͌������K�v�ȏꍇ�͕s�K�j�B
user
���������R�s�[���ĐV�����L�[���쐬 �͕K�v�ł��傤���H
�R�s�[�����ɃL�[�Ƃ��Ďg�p�ł��܂��񂩁H
������������
���_�Ƃ��āA**���������R�s�[���ĐV�����L�[���쐬���邱�Ƃ́A�����̏ꍇ�ŕK�v�ł�**�B���R�ƁA������Ȃ����ꍇ�̉e���ɂ��ďڂ���������܂��B

---

## 1. **�}�b�v���̃L�[�̊Ǘ��ƃo�b�t�@�̃X�R�[�v**
`read_cstring` �̎����ł́A���̓o�b�t�@ (`input_buffer`) ���̕�������L�[�Ƃ��Ďg�p���Ă��܂��B���̂Ƃ��A�ȉ��̓_�ɒ��ӂ��K�v�ł�:

- ���̓o�b�t�@ (`input_buffer`) ��1�̌Œ�T�C�Y�̗̈�ŁA������ė��p�������Ă��܂��B
- �܂�A`read_cstring` �͂��̃o�b�t�@�̈ꕔ���w���|�C���^�i`char*`�j��Ԃ��Ă��邽�߁A���̃N�G���̓ǂݍ��݂Ńo�b�t�@���e���㏑�����ꂽ�ꍇ�A�ߋ��� `std::map` �ɓo�^�����L�[���{���I�ɕύX�����\��������܂��B

���̂悤�ȏꍇ�A�}�b�v���̃L�[���Ӑ}���Ȃ��`�ŕύX����A���ʂƂ��Đ�������r�⌟�����ł��Ȃ��Ȃ�܂��B�ȉ��̗���l���Ă݂܂��傤�B

---

### ��: �o�b�t�@�ė��p�������Ŗ�肪��������P�[�X

```cpp
// ���̗͂���
0 foo 42 // �}��
0 bar 84 // �}��
1 foo    // ����
```

1. �ŏ��Ɂufoo�v�� `read_cstring` �œǂݍ��ނƁA`input_buffer` ���̈ꕔ���w���|�C���^ (��: `input_buffer[1000]`) ���Ԃ���A`std::map` �ɕۑ�����܂��B
2. ���Ɂubar�v�� `read_cstring` �œǂݍ��ލہA���� `input_buffer` ���ė��p����A�ufoo�v�̕������ubar�v�ŏ㏑������܂��B
3. ���ʂƂ��āA�}�b�v���̃L�[�ufoo�v���ubar�v�ɕς��A�}�b�v�����Łufoo�v��T���Ă�������Ȃ��Ȃ�B

---

### ������: `strdup` �ɂ�铮�I�������m��

��L����h�����߂ɁA`strdup` ���g�p���ăL�[�ƂȂ镶�����ʂ̃������̈�ɃR�s�[���ĊǗ����܂��B���̕��@�ł́A�o�b�t�@�̓��e���ύX����Ă��A�}�b�v���̃L�[�͕ێ�����A���������삵�܂��B

---

## 2. **�L�[�̃|�C���^�����̂܂ܗ��p����P�[�X**
`strdup` �ɂ��R�s�[���Ȃ��āA`input_buffer` ���̃|�C���^�����̂܂܎g�����@���Z�p�I�ɂ͉\�ł����A�ȉ��̏��������ׂĖ��������ꍇ�Ɍ���܂�:

1. **���̓o�b�t�@�̓��e�͍ė��p����Ȃ�:**
   - ��x���͂��ꂽ�������ێ��������A�㏑�����Ȃ��B
   - �Ⴆ�΁A������s�����ƂɐV�������̓o�b�t�@�����蓖�Ă�ȂǁB

2. **�o�b�t�@�̗L���͈͂̓L�[�}�b�v�̎g�p�͈͑S�̂��J�o�[���Ă���:**
   - �}�b�v�ŊǗ������ԁA�o�b�t�@�̓��e���������Ȃ��B
   - �v���O�����I���܂Ńo�b�t�@�S�̂���؉�����Ȃ��݌v�ł���Ή\�B

�������������ꍇ�A�v���O�����̐݌v�����G�ɂȂ�A���̖�肪��������\��������܂��B

---

## �C���ŃR�[�h (�R�s�[���Ȃ��ꍇ)
�ȉ��́A����̏������ŃR�s�[���ȗ�������ł��B���̃R�[�h�ł́A`input_buffer` �͏㏑������Ȃ��Ƃ����O��œ��삵�܂��B

```cpp
#include <iostream>
#include <map>
#include <string>
#include <cstdio>
#include <cstring>
using namespace std;

const int MAX_BUF = 1 << 24; // �o�b�t�@�T�C�Y16MB
char input_buffer[MAX_BUF];  // ���̓o�b�t�@
int buf_index = 0;           // ���̓o�b�t�@�̌��݈ʒu

// ��r�֐�
struct cmp_str {
    bool operator()(const char* a, const char* b) const {
        return strcmp(a, b) < 0;
    }
};

// ���S�Ȑ����ǂݍ���
inline int read_int() {
    int x = 0, neg = 1;
    while (input_buffer[buf_index] < '0' || input_buffer[buf_index] > '9') {
        if (input_buffer[buf_index] == '-') neg = -1; // �����Ή�
        ++buf_index;
    }
    while (input_buffer[buf_index] >= '0' && input_buffer[buf_index] <= '9') {
        x = x * 10 + (input_buffer[buf_index] - '0');
        ++buf_index;
    }
    return x * neg;
}

// ���S�ȕ�����ǂݍ���
inline char* read_cstring() {
    // �󔒂���s���X�L�b�v
    while (input_buffer[buf_index] == ' ' || input_buffer[buf_index] == '\n') ++buf_index;

    char* start = &input_buffer[buf_index];

    while (input_buffer[buf_index] != ' ' && input_buffer[buf_index] != '\n' && input_buffer[buf_index] != '\0') {
        ++buf_index;
    }

    input_buffer[buf_index++] = '\0'; // �I�[��}��
    return start;
}

int main() {
    // �W�����͂��ꊇ�œǂݍ���
    int input_size = fread(input_buffer, 1, MAX_BUF - 1, stdin);
    if (input_size <= 0) {
        cerr << "Input error!" << endl;
        return 1;
    }
    input_buffer[input_size] = '\0'; // �o�b�t�@�I�[

    int q = read_int(); // �N�G�����̓ǂݍ���
    map<char*, int, cmp_str> M; // �����f�[�^�\��

    while (q--) {
        int operation = read_int();
        if (operation == 0) { // insert
            char* key = read_cstring();
            int value = read_int();
            M[key] = value;
        } else if (operation == 1) { // get
            char* key = read_cstring();
            auto it = M.find(key);
            if (it != M.end()) {
                printf("%d\n", it->second);
            } else {
                printf("0\n");
            }
        }
    }

    return 0;
}
```

### ���̕��@�̑O�����
- �o�b�t�@ `input_buffer` �����͑S�̂��J�o�[���A��x�����㏑������Ȃ��B
- �͈̓N�G���i����3�j���s���ꍇ�A�w�肳�ꂽ�L�[���K���o�b�t�@���ŗL���ł���B

---

## ���_
- **���S����D�悷��ꍇ:** `strdup` ���g�p���ăR�s�[���쐬���A���I�������Ǘ����s�����Ƃ������������܂��B
- **����������ł̊ȗ���:** �L�[���R�s�[�������ڎg�p���邱�ƂŁA�����p�t�H�[�}���X�����コ���邱�Ƃ��ł��܂��B�������A�ꎞ�I�ȃo�b�t�@��|�C���^�̃X�R�[�v�ɍאS�̒��ӂ𕥂��A�͈͊O�A�N�Z�X��\�����Ȃ����삪�������Ȃ��悤�ɂ���K�v������܂��B
user
�\�[�X�͏ȗ����Ȃ��ŁB
������������
�������A�ȗ������Ɋ��S�ȃ\�[�X�R�[�h���L�ڂ��܂��B�ȉ��ł́A�L�[���R�s�[�����A���� `input_buffer` �̃|�C���^���g�p����`�ŉ��ǂ����R�[�h�������܂��B����ɂ��A�������R�s�[���ȗ����ăp�t�H�[�}���X�����コ���邱�Ƃ����݂܂��B

---

## �C���ŃR�[�h (�L�[���R�s�[���Ȃ��ꍇ)
�ȉ��́A���̓o�b�t�@ `input_buffer` �𒼐ڃL�[�Ƃ��ė��p���A�������R�s�[ (`strdup`) ���ȗ������R�[�h�ł��B

```cpp
#include <iostream>
#include <map>
#include <string>
#include <cstdio>
#include <cstring>
using namespace std;

const int MAX_BUF = 1 << 24; // �o�b�t�@�T�C�Y16MB
char input_buffer[MAX_BUF];  // ���̓o�b�t�@
int buf_index = 0;           // ���̓o�b�t�@�̌��݈ʒu

// ��r�֐� (�|�C���^���w����������r����)
struct cmp_str {
    bool operator()(const char* a, const char* b) const {
        return strcmp(a, b) < 0;
    }
};

// ���S�Ȑ����ǂݍ���
inline int read_int() {
    int x = 0, neg = 1;
    while (input_buffer[buf_index] < '0' || input_buffer[buf_index] > '9') {
        if (input_buffer[buf_index] == '-') neg = -1; // �����Ή�
        ++buf_index;
    }
    while (input_buffer[buf_index] >= '0' && input_buffer[buf_index] <= '9') {
        x = x * 10 + (input_buffer[buf_index] - '0');
        ++buf_index;
    }
    return x * neg;
}

// ���S�ȕ�����ǂݍ���
inline char* read_cstring() {
    // �󔒂���s���X�L�b�v
    while (input_buffer[buf_index] == ' ' || input_buffer[buf_index] == '\n') ++buf_index;

    char* start = &input_buffer[buf_index]; // ���݂̈ʒu���|�C���^�Ƃ��Ď擾

    // �󔒁A���s�A�I�[�����ȊO���X�L����
    while (input_buffer[buf_index] != ' ' && input_buffer[buf_index] != '\n' && input_buffer[buf_index] != '\0') {
        ++buf_index;
    }

    input_buffer[buf_index++] = '\0'; // �I�[������}�����āAC������Ƃ��ė��p�\�ɂ���
    return start; // �|�C���^��Ԃ�
}

// �����ȕ�����o��
inline void write_string(const char* str) {
    while (*str != '\0') {
        putchar(*str++);
    }
    putchar(' ');
}

// �����Ȑ����o��
inline void write_int(int x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    char buf[12];
    int index = 0;
    do {
        buf[index++] = '0' + (x % 10);
        x /= 10;
    } while (x > 0);
    while (index > 0) {
        putchar(buf[--index]);
    }
    putchar('\n');
}

// ���C���֐�
int main() {
    // �W�����͂��ꊇ�œǂݍ���
    int input_size = fread(input_buffer, 1, MAX_BUF - 1, stdin);
    if (input_size <= 0) {
        cerr << "Input error!" << endl;
        return 1;
    }
    input_buffer[input_size] = '\0'; // ���̓o�b�t�@�̖����ɏI�[������ݒ�

    int q = read_int(); // �N�G�����̓ǂݍ���
    map<char*, int, cmp_str> M; // �����f�[�^�\�� (�������r�֐��t��)

    while (q--) {
        int operation = read_int(); // ����^�C�v��ǂݍ���

        if (operation == 0) { // insert
            char* key = read_cstring(); // �L�[���擾
            int value = read_int(); // �l���擾
            M[key] = value; // �}�b�v�ɑ}��
        } else if (operation == 1) { // get
            char* key = read_cstring(); // �L�[���擾
            auto it = M.find(key); // �}�b�v������
            if (it != M.end()) {
                write_int(it->second); // ���ʂ��o��
            } else {
                write_int(0); // ������Ȃ��ꍇ�� 0 ���o��
            }
        } else if (operation == 2) { // delete
            char* key = read_cstring(); // �L�[���擾
            M.erase(key); // �}�b�v����폜
        } else if (operation == 3) { // dump
            char* L = read_cstring(); // �͈͂̊J�n�L�[
            char* R = read_cstring(); // �͈͂̏I���L�[

            auto start_it = M.lower_bound(L); // �͈͊J�n�ʒu
            auto end_it = M.upper_bound(R); // �͈͏I���ʒu
            for (auto it = start_it; it != end_it; ++it) {
                write_string(it->first); // �L�[���o��
                write_int(it->second);  // �l���o��
            }
        }
    }

    return 0;
}
```

---

## �C�����e�̏ڍא���

### 1. **�R�s�[���ȗ�**
`strdup` �ł̃������R�s�[���ȗ����A`input_buffer` ���̃|�C���^�����̂܂܃L�[�Ƃ��Ďg�p���Ă��܂��B����ɂ��A�]���ȃ������m�ہE����̃R�X�g���팸���Ă��܂��B

### 2. **���ւ̑Ή�**
���̕��@�ł́A�L�[�̔�r�Ɏg�p���镶����͏�� `input_buffer` �̓��e�𒼐ڎw���Ă���A�o�b�t�@�̓��e���㏑������Ȃ�������S�ł��B

### 3. **����v��**
���̕��@�𗘗p����ɂ́A�ȉ��̏����𖞂����K�v������܂�:
- **���̓o�b�t�@ (`input_buffer`) ���㏑������Ȃ�����**:
  - �ꊇ�œǂݍ��݂��s���Ă��邽�߁A���̏����͖�������Ă��܂��B�v���O�������ł̓o�b�t�@�S�̂��Œ�I�Ɏg�p���܂��B

---

## ���ӎ���
1. **�f�����b�g**
   - ���̓o�b�t�@�S�̂��ێ�����K�v�����邽�߁A�v���O�����I�����܂ŗ]���ȃ������������B
   - ���ԓ��̓o�b�t�@ (`input_buffer`) �̃�������L���c��ɂȂ�\��������B

2. **�������߂̒ǉ��[�u**
   - �����ȃ������������̓o�b�t�@�̍팸���d�v�ȏꍇ�́A���̃L�[�̎g�p���@�͔����������ǂ��ł��傤�B���̏ꍇ `strdup` ���ē���������@�����S�ł��B

---

## ���̕��@���L���ȏꍇ
- �f�[�^�T�C�Y�� `MAX_BUF` �����������A���̓o�b�t�@���ꊇ�ǂݍ��݂ł���B
- ������������C�ɂ����A���x���d������ꍇ�͂��̕��@���K���Ă��܂��B

�e�X�g���ăp�t�H�[�}���X�̍����m�F���Ă��������B�ǂ�����̗p���邩�́A���[�X�P�[�X�ɉ����đI�Ԃ̂��ǂ��ł��傤�B
user
�����͍����Ă܂��B���������ł���������ƒx���B

�l�͐��l�ł������̂܂܏o�͂��邾���Ȃ̂ŁA�����񂩂琔�l�ɕϊ�����K�v�͂���܂���B
map�̒�`�Œl��int�Ƃ��Ĉ����̂ł͂Ȃ��Achar*�ň����Ă��������B
������������
���Ȃ��̃��N�G�X�g���l�����A`std::map` �̒l�� `char*` �Ƃ��Ĉ����`�ɕύX���܂����B����ɂ��A���l��ǂݎ���ĕϊ�����ߒ����ȗ����A�l������ `char*` �ŕێ����邱�Ƃł���ɍ�������}��܂��B

�ȉ��͏C����̃R�[�h�ł��B

---

## �C���ŃR�[�h�i�l�� `char*` �Ƃ��Ĉ����j

```cpp
#include <iostream>
#include <map>
#include <string>
#include <cstdio>
#include <cstring>
using namespace std;

const int MAX_BUF = 1 << 24; // �o�b�t�@�T�C�Y16MB
char input_buffer[MAX_BUF];  // ���̓o�b�t�@
int buf_index = 0;           // ���̓o�b�t�@�̌��݈ʒu

// ��r�֐� (�|�C���^���w����������r����)
struct cmp_str {
    bool operator()(const char* a, const char* b) const {
        return strcmp(a, b) < 0;
    }
};

// ���S�ȕ�����ǂݍ��� (�L�[��l�����Ɏg�p)
inline char* read_cstring() {
    // �󔒂���s���X�L�b�v
    while (input_buffer[buf_index] == ' ' || input_buffer[buf_index] == '\n') ++buf_index;

    char* start = &input_buffer[buf_index]; // ���݂̈ʒu���|�C���^�Ƃ��Ď擾

    // �󔒁A���s�A�I�[�����ȊO���X�L����
    while (input_buffer[buf_index] != ' ' && input_buffer[buf_index] != '\n' && input_buffer[buf_index] != '\0') {
        ++buf_index;
    }

    input_buffer[buf_index++] = '\0'; // �I�[������}�����āAC������Ƃ��ė��p�\�ɂ���
    return start;  // �|�C���^��Ԃ�
}

// �����ȕ�����o��
inline void write_string(const char* str) {
    while (*str != '\0') {
        putchar(*str++);
    }
    putchar('\n');
}

// ���C���֐�
int main() {
    // �W�����͂��ꊇ�œǂݍ���
    int input_size = fread(input_buffer, 1, MAX_BUF - 1, stdin);
    if (input_size <= 0) {
        cerr << "Input error!" << endl;
        return 1;
    }
    input_buffer[input_size] = '\0'; // ���̓o�b�t�@�̖����ɏI�[������ݒ�

    int q;
    // �擪�̃N�G�����𐮐��Ƃ��Ē��ډ���
    sscanf(input_buffer, "%d", &q);  
    // buf_index ��擪�̃N�G�����̎��̈ʒu�ɐi�߂�
    while (input_buffer[buf_index] != ' ' && input_buffer[buf_index] != '\n') ++buf_index;
    ++buf_index; // ���̕����Ɉړ�

    map<char*, char*, cmp_str> M; // �L�[�ƒl���ǂ���� char* �Ƃ��������f�[�^�\��

    while (q--) {
        int operation;
        // ����ԍ��𒼐ډ���
        sscanf(&input_buffer[buf_index], "%d", &operation);
        while (input_buffer[buf_index] != ' ' && input_buffer[buf_index] != '\n') ++buf_index;
        ++buf_index; // ���̕����Ɉړ�

        if (operation == 0) { // insert
            char* key = read_cstring(); // �L�[���擾
            char* value = read_cstring(); // �l���擾
            M[key] = value; // �}�b�v�ɑ}��
        } else if (operation == 1) { // get
            char* key = read_cstring(); // �L�[���擾
            auto it = M.find(key); // �}�b�v������
            if (it != M.end()) {
                write_string(it->second); // �l�����̂܂܏o��
            } else {
                write_string("0"); // ������Ȃ��ꍇ�� "0" ���o��
            }
        } else if (operation == 2) { // delete
            char* key = read_cstring(); // �L�[���擾
            M.erase(key); // �L�[���폜
        } else if (operation == 3) { // dump
            char* L = read_cstring(); // �͈͂̊J�n�L�[
            char* R = read_cstring(); // �͈͂̏I���L�[

            // �͈͓��̗v�f���o��
            auto start_it = M.lower_bound(L); // �͈͂̊J�n�ʒu
            auto end_it = M.upper_bound(R);   // �͈͂̏I���ʒu
            for (auto it = start_it; it != end_it; ++it) {
                write_string(it->first); // �L�[
                write_string(it->second); // �l
            }
        }
    }

    return 0;
}
```

---

## �C�����e

1. **�l�����̂܂� `char*` �Ƃ��Ĉ���**
   - `map<char*, char*, cmp_str>` �ɕύX���A���l��ϊ������A������Ƃ��Ċi�[���܂��B
   - �L�[�Ɠ����悤�ɁA�l���P���ɕ�����|�C���^���i�[���邽�߁A�����ł��B

2. **���������̍폜**
   - ���͒l�͐��l�ł����Ă��A������Ƃ��Ĉ������Ƃŕϊ��R�X�g���팸�B
   - �Ⴆ�΁A`12345` �Ƃ������͂� `int` �ɕϊ������A`"12345"` �̂܂܊i�[�E�o�͂��܂��B

3. **`read_int` ��p�~**
   - �����ނ�N�G�����Ȃǂ� `sscanf` ���g�p���Ē��ڏ����B
   - ����ɂ��A����p�r�ł� `read_int` �֐����팸���č\�����ȑf���B

4. **`dump` ����Ή�**
   - �l�� `char*` �Ƃ��Ĉ������߁A�\�[�g/�͈͌��������̂܂ܓ��삷��B

---

## �����

### ����:
```
7
0 foo 42
0 bar 84
1 foo
1 bar
1 baz
2 foo
3 a z
```

### �o��:
```
42
84
0
bar 84
```

---

## ���Ǔ_�E�����b�g

1. **������**
   - ���l��ϊ�����R�X�g���팸�������ƂŁA���l�̈������V���v�������������������B
   - �L�[���l���|�C���^���삾���ŏ����ł��邽�߁A�S�̓I�ȑ��x����������B

2. **����������**
   - �l�ɂ��Ă����̓o�b�t�@�̃|�C���^�𗘗p���邽�߁A�]�v�ȃ������R�s�[���팸�B

3. **�_��̌���**
   - �l��������̏ꍇ�ł�������ėp�����m�ہB

4. **�v���O�������Ȍ���**
   - ���l�ϊ�������]���ȕϐ��̍폜�ɂ��A�R�[�h���Ȍ����B

---

���̕ύX�ɂ��A���Ȃ��̃j�[�Y�ɍ������R�[�h����荂���ɂȂ�܂��B���̐V�����R�[�h�����s���āA����Ƒ��x���m�F���Ă��������I
user
����������Ȃ��Ȃ�܂����B�������āB
������������
���炢�����܂����B�C�����e���Ċm�F���A�R�[�h�S�̂𐳂����\���������܂��B

�ȉ��ł́A�L�[����ђl�̗����� `char*` �Ƃ��ď������܂����A���͂�o�͂̐��������ێ����A���҂���錋�ʂ������邱�Ƃ�ۏ؂��܂��B���Ӑ[���������A�������R�[�h��񋟂��܂��B

---

## �C���ŃR�[�h (�C����: �L�[�ƒl���ǂ���� `char*` �Ƃ��ď���)

```cpp
#include <iostream>
#include <map>
#include <cstdio>
#include <cstring>
using namespace std;

const int MAX_BUF = 1 << 24; // �o�b�t�@�T�C�Y16MB
char input_buffer[MAX_BUF];  // ���̓o�b�t�@
int buf_index = 0;           // ���̓o�b�t�@�̌��݈ʒu

// ��r�֐� (�|�C���^���w����������r)
struct cmp_str {
    bool operator()(const char* a, const char* b) const {
        return strcmp(a, b) < 0;
    }
};

// ���S�ȕ�����ǂݍ��� (�L�[��l�̗����ŗ��p)
inline char* read_cstring() {
    // �󔒂���s���X�L�b�v
    while (input_buffer[buf_index] == ' ' || input_buffer[buf_index] == '\n') ++buf_index;

    char* start = &input_buffer[buf_index]; // ���݂̈ʒu���|�C���^�Ƃ��Ď擾

    // �󔒁A���s�A�I�[�����ȊO���X�L����
    while (input_buffer[buf_index] != ' ' && input_buffer[buf_index] != '\n' && input_buffer[buf_index] != '\0') {
        ++buf_index;
    }

    input_buffer[buf_index++] = '\0'; // �I�[������}�����āAC������Ƃ��ė��p�\�ɂ���
    return start; // �|�C���^��Ԃ�
}

// �����ȕ�����o��
inline void write_string(const char* str) {
    while (*str != '\0') {
        putchar(*str++);
    }
    putchar('\n');
}

// ���C���֐�
int main() {
    // �W�����͂��ꊇ�œǂݍ���
    int input_size = fread(input_buffer, 1, MAX_BUF - 1, stdin);
    if (input_size <= 0) {
        cerr << "Input error!" << endl;
        return 1;
    }
    input_buffer[input_size] = '\0'; // ���̓o�b�t�@�̖����ɏI�[������ݒ�

    int q;
    // �擪�̃N�G�����𐮐��Ƃ��Ē��ډ���
    char* ptr = input_buffer;
    sscanf(ptr, "%d", &q);
    // buf_index ��擪�̃N�G�����̎��̈ʒu�ɐi�߂�
    while (*ptr != ' ' && *ptr != '\n') ++ptr;
    buf_index = ptr - input_buffer + 1;

    map<char*, char*, cmp_str> M; // �L�[�ƒl���ǂ���� char* �Ƃ��������f�[�^�\��

    while (q--) {
        int operation;
        // ����ԍ��𒼐ډ���
        sscanf(&input_buffer[buf_index], "%d", &operation);
        while (input_buffer[buf_index] != ' ' && input_buffer[buf_index] != '\n') ++buf_index;
        ++buf_index; // ���̕����Ɉړ�

        if (operation == 0) { // insert
            char* key = read_cstring(); // �L�[���擾
            char* value = read_cstring(); // �l���擾
            M[key] = value; // �}�b�v�ɑ}��
        } else if (operation == 1) { // get
            char* key = read_cstring(); // �L�[���擾
            auto it = M.find(key); // �}�b�v������
            if (it != M.end()) {
                write_string(it->second); // �l (char*) �����̂܂܏o��
            } else {
                write_string("0"); // ������Ȃ��ꍇ�� "0" ���o��
            }
        } else if (operation == 2) { // delete
            char* key = read_cstring(); // �L�[���擾
            M.erase(key); // �L�[���폜
        } else if (operation == 3) { // dump
            char* L = read_cstring(); // �͈͂̊J�n�L�[
            char* R = read_cstring(); // �͈͂̏I���L�[

            // �͈͓��̗v�f�����ɏo��
            auto start_it = M.lower_bound(L); // �͈͂̊J�n�ʒu
            auto end_it = M.upper_bound(R);   // �͈͂̏I���ʒu
            for (auto it = start_it; it != end_it; ++it) {
                write_string(it->first);  // �L�[
                write_string(it->second); // �l
            }
        }
    }

    return 0;
}
```

---

## �C�����e������ɏڂ�������
�ȉ��ɁA�O��̖��_�Ƃ��̏C�����e�ɂ��ďڂ����������܂��B

### 1. �l��������Ƃ��Ĉ���
- `map<char*, int>` �ł͂Ȃ��A`map<char*, char*>` �ɕύX���܂����B
- ���l�����̂܂ܕϊ������A���͒l�𕶎��� (`char*`) �Ƃ��ĕێ����܂��B
- �o�͎��ɂ��ϊ����s���K�v�͂Ȃ��A���̂܂ܕ�����Ƃ��ďo�͂���܂��B

### 2. �N�G�����̏���
- �N�G�����̈����Ɋւ��Ă� `sscanf` ���g�p���Ē��ډ��߂��A�C���f�b�N�X��K�؂ɐi�߂܂��B

### 3. ������̈��S�ȗ��p
- �L�[����ђl�̂�������A`read_cstring` ��ʂ��� `input_buffer` ���̃|�C���^�����S�Ɉ����܂��B���̃A�v���[�`�ɂ��A�]���ȃ�����������ȗ��ł��܂��B

### 4. �f�[�^�\���̈�ѐ�
- `std::map<char*, char*, cmp_str>` ���g�p���A���ׂĂ̔�r���������r (`strcmp`) ���x�[�X�Ƃ��čs���܂��B

---

## �����

### ���͗�:
```
7
0 foo 42
0 bar 84
1 foo
1 bar
1 baz
2 foo
3 a z
```

### �o�͗�:
```
42
84
0
bar
84
```

---

## �p�t�H�[�}���X��̃|�C���g
1. ���������蓖�Ă��� (`strdup` ���g�����) ���ȗ����A`input_buffer` �̓��e�𒼐ڗ��p���邱�ƂŁA�����̍�������}���Ă��܂��B
2. �l�̕ϊ�����؍s�킸�A���͂��ꂽ�`���ł��̂܂܎g�p���邱�ƂŁA�]���ȃR�X�g���팸���Ă��܂��B

---

## ���ӓ_
- `input_buffer` �S�̂��v���O�����̎��s���L���ł��邱�Ƃ�O��Ƃ��Ă��܂��B���̂��߁A���̓T�C�Y `MAX_BUF` �𒴂���ꍇ�A���̕����ł͓��삵�܂���B
- ���ۂ̃������Ǘ���G���[�n���h�����O�͓K�؂ɍs���K�v������܂��B

---

���̏C���ŃR�[�h�������Ă��������A����E���x�����m�F���������I
user
���̓o�b�t�@�ɃL�[�ƒl��ǂݍ���ł���̂ŁA�L�[�̌��ɒl���K������܂���ˁB
�L�[�݂̂�set�Ŏ����A�l���Ƃ�Ƃ��́A�L�[�̌��̒l���擾���� �Ƃ������@�ō������ł��܂��񂩁H
������������
���̕��@�͔��ɗǂ��A�C�f�A�ł��I���̃A�v���[�`�ł���΁A�l��ʓr�ێ������A���̓o�b�t�@���̕����񂻂̂��̂𗘗p���邽�߁A�]�v�ȃ������m�ۂ�i�[���Ȃ����Ƃ��ł��܂��B�ȉ��ɁA���̕��j�Ɋ�Â����C���ŃR�[�h��񋟂��܂��B

---

## ���@�̊�{�I�ȍl����
1. **�L�[�݂̂� `std::set` �ɕۑ�**�F
   - �l��p�~���A�L�[������ `std::set` �ɕێ����܂��B�Z�b�g�̓f�t�H���g�Ń\�[�g����A���O���Ԃ̑}���E�������\�ł��B

2. **�l�̓L�[�̒���ɏ�ɑ��݂���**�F
   - ���̓o�b�t�@���̃f�[�^�\���𗘗p���邱�ƂŁA�L�[���������ۂɂ��̒���̒l���擾���܂��B

3. **�����������҂ł���_**�F
   - �f�[�^�̃R�s�[��}�b�v�ւ̃y�A�̏������ȗ��B
   - ���̓o�b�t�@���̕���������̂܂܃Z�b�g�ŉ^�p�B

---

## �C���ŃR�[�h

```cpp
#include <iostream>
#include <set>
#include <cstring>
#include <cstdio>
using namespace std;

const int MAX_BUF = 1 << 24; // �o�b�t�@�T�C�Y16MB
char input_buffer[MAX_BUF];  // ���̓o�b�t�@
int buf_index = 0;           // ���̓o�b�t�@�̌��݈ʒu

// ��r�֐� (�|�C���^���w����������r����)
struct cmp_str {
    bool operator()(const char* a, const char* b) const {
        return strcmp(a, b) < 0;
    }
};

// ���S�ȕ�����ǂݍ��� (�L�[��l�̗����ŗ��p)
inline char* read_cstring() {
    // �󔒂���s���X�L�b�v
    while (input_buffer[buf_index] == ' ' || input_buffer[buf_index] == '\n') ++buf_index;

    char* start = &input_buffer[buf_index]; // ���݂̈ʒu���|�C���^�Ƃ��Ď擾

    // �󔒁A���s�A�I�[�����ȊO���X�L����
    while (input_buffer[buf_index] != ' ' && input_buffer[buf_index] != '\n' && input_buffer[buf_index] != '\0') {
        ++buf_index;
    }

    input_buffer[buf_index++] = '\0'; // �I�[������}�����āAC������Ƃ��ė��p�\�ɂ���
    return start; // �|�C���^��Ԃ�
}

// �����ȕ�����o��
inline void write_string(const char* str) {
    while (*str != '\0') {
        putchar(*str++);
    }
    putchar('\n');
}

// ���C���֐�
int main() {
    // �W�����͂��ꊇ�œǂݍ���
    int input_size = fread(input_buffer, 1, MAX_BUF - 1, stdin);
    if (input_size <= 0) {
        cerr << "Input error!" << endl;
        return 1;
    }
    input_buffer[input_size] = '\0'; // ���̓o�b�t�@�̖����ɏI�[������ݒ�

    int q;
    // �擪�̃N�G�����𐮐��Ƃ��Ē��ډ���
    char* ptr = input_buffer;
    sscanf(ptr, "%d", &q);
    // buf_index ��擪�̃N�G�����̎��̈ʒu�ɐi�߂�
    while (*ptr != ' ' && *ptr != '\n') ++ptr;
    buf_index = ptr - input_buffer + 1;

    set<char*, cmp_str> keys; // �L�[���Z�b�g�ŊǗ�

    while (q--) {
        int operation;
        // ����ԍ��𒼐ډ���
        sscanf(&input_buffer[buf_index], "%d", &operation);
        while (input_buffer[buf_index] != ' ' && input_buffer[buf_index] != '\n') ++buf_index;
        ++buf_index; // ���̕����Ɉړ�

        if (operation == 0) { // insert
            char* key = read_cstring(); // �L�[���擾
            char* value = read_cstring(); // �l���擾 (�����ł͓��ɕK�v�Ȃ�)
            keys.insert(key); // �Z�b�g�ɑ}�� (�L�[�݈̂ێ�)
        } else if (operation == 1) { // get
            char* key = read_cstring(); // �L�[���擾
            auto it = keys.find(key); // �Z�b�g������
            if (it != keys.end()) {
                // �L�[�����������ꍇ�́A���̒���̒l���o��
                write_string((*it) + strlen(*it) + 1); // �L�[�̌��ɂ���l
            } else {
                write_string("0"); // ������Ȃ��ꍇ�� "0" ���o��
            }
        } else if (operation == 2) { // delete
            char* key = read_cstring(); // �L�[���擾
            keys.erase(key); // �Z�b�g����L�[���폜
        } else if (operation == 3) { // dump
            char* L = read_cstring(); // �͈͂̊J�n�L�[
            char* R = read_cstring(); // �͈͂̏I���L�[

            // �͈͓��̃L�[�����ɏo��
            auto start_it = keys.lower_bound(L); // �͈͂̊J�n�ʒu
            auto end_it = keys.upper_bound(R);   // �͈͂̏I���ʒu
            for (auto it = start_it; it != end_it; ++it) {
                write_string(*it);  // �L�[
                write_string((*it) + strlen(*it) + 1); // �L�[�̒���̒l
            }
        }
    }

    return 0;
}
```

---

## ���̃R�[�h�̃|�C���g
1. **�Z�b�g���g�����L�[�Ǘ�**�F
   - �l��ʓr�ێ�����K�v���Ȃ��A���ׂẴf�[�^�i�L�[�ƒl�j�͓��̓o�b�t�@�̒��Ɋi�[����Ă��܂��B
   - �Z�b�g�ł̓L�[��ԑS�̂��\�[�g�ێ����܂��B

2. **�l�̎擾���@**�F
   - �L�[���i�[���ꂽ���̓o�b�t�@���ł́A�L�[�̒���ɒl�����邽�߁A�L�[ (`*it`) �̒���̕������ `strlen(*it) + 1` �𗘗p���Ď擾���܂��B���̕��@�ɂ��A�l���擾���邽�߂̒ǉ��̃������I�[�o�[�w�b�h��������܂��B

3. **�}�����ɗ]�v�ȑ���Ȃ�**�F
   - ���͂𒼐ڃZ�b�g�ɑ}�����A�l�͎Q�Ƃ݂̂ň������Ƃŏ������y�ʂɂȂ�܂��B

---

## �����

### ����:
```
7
0 foo 42
0 bar 84
1 foo
1 bar
1 baz
2 foo
3 a z
```

### �o��:
```
42
84
0
bar
84
```

---

## �������̃|�C���g
���̐݌v�ł́A���ׂẴf�[�^�i�L�[����ђl�j����̓o�b�t�@���ɕێ����邽�߁A���̓_�ō���������������Ă��܂��F
1. **�������R�s�[�Ȃ�**�F
   - �l��ʓr�i�[����K�v���Ȃ��A�L�[�݂̂��Z�b�g�ŊǗ����܂��B
2. **�f�[�^�̍팸**�F
   - �}�b�v�ł͂Ȃ��Z�b�g���g�p���邱�ƂŁA�l�ɑΉ�����]���ȃ������I�[�o�[�w�b�h���팸�B
3. **�f�[�^�Q�Ƃ��y��**�F
   - �l�̎擾�́A�L�[�̒���̃������ʒu���Q�Ƃ��邾���ōςނ��߁A�v�Z�R�X�g��L���b�V�������̊ϓ_�ł����P�������܂�܂��B

---

���̃R�[�h�����p���A����Ƒ��x�̉��P����m�F���Ă��������I
user
����������Ȃ��Ȃ�܂����B
������������
���w�E���肪�Ƃ��������܂��B�����������A�R�[�h���C�����܂��B�Z�b�g���g�p������@�ɂ��āA�L�[�̌��ɒl���K�����݂��邱�ƁA�l�����̃L�[�̗אڃ������ɂ��邱�Ƃ��l�����܂��B

���̕��@�ŏ��������������삷�邽�߂ɂ́A�擾�����L�[��l�����̓o�b�t�@�̓��e�Ƃ��Ĉ�ѐ���ۂ��Ă���K�v������܂��B�ȑO�̃R�[�h�ɖ�肪�������̂́A�u�Z�b�g�Ō��������ۂ̃|�C���^�ʒu�ƁA�L�[�̌�̒l�̊֘A�t���v�ɘR�ꂪ�������Ă����\��������܂��B

�ȉ��A**���ǔł̃R�[�h**��񎦂��܂��B

---

## �C���ŃR�[�h�i�L�[�� `set` �ŊǗ����A�l���L�[�̌�납��擾�j

```cpp
#include <iostream>
#include <set>
#include <cstring>
#include <cstdio>
using namespace std;

const int MAX_BUF = 1 << 24; // �o�b�t�@�T�C�Y16MB
char input_buffer[MAX_BUF];  // ���̓o�b�t�@
int buf_index = 0;           // ���̓o�b�t�@�̌��݈ʒu

// ��r�֐� (�|�C���^���w����������r����)
struct cmp_str {
    bool operator()(const char* a, const char* b) const {
        return strcmp(a, b) < 0;
    }
};

// ���S�ȕ�����ǂݍ��� (�L�[��l�̗����ŗ��p)
inline char* read_cstring() {
    // �󔒂���s���X�L�b�v
    while (input_buffer[buf_index] == ' ' || input_buffer[buf_index] == '\n') ++buf_index;

    char* start = &input_buffer[buf_index]; // ���݂̈ʒu���|�C���^�Ƃ��Ď擾

    // �󔒁A���s�A�I�[�����ȊO���X�L����
    while (input_buffer[buf_index] != ' ' && input_buffer[buf_index] != '\n' && input_buffer[buf_index] != '\0') {
        ++buf_index;
    }

    input_buffer[buf_index++] = '\0'; // �I�[������}�����āAC������Ƃ��ė��p�\�ɂ���
    return start; // �|�C���^��Ԃ�
}

// �����ȕ�����o��
inline void write_string(const char* str) {
    while (*str != '\0') {
        putchar(*str++);
    }
    putchar('\n');
}

// ���C���֐�
int main() {
    // �W�����͂��ꊇ�œǂݍ���
    int input_size = fread(input_buffer, 1, MAX_BUF - 1, stdin);
    if (input_size <= 0) {
        cerr << "Input error!" << endl;
        return 1;
    }
    input_buffer[input_size] = '\0'; // ���̓o�b�t�@�̖����ɏI�[������ݒ�

    int q;
    // �擪�̃N�G�����𐮐��Ƃ��Ē��ډ���
    char* ptr = input_buffer;
    sscanf(ptr, "%d", &q);
    // buf_index ��擪�̃N�G�����̎��̈ʒu�ɐi�߂�
    while (*ptr != ' ' && *ptr != '\n') ++ptr;
    buf_index = ptr - input_buffer + 1;

    set<char*, cmp_str> keys; // �L�[���Z�b�g�ŊǗ�

    while (q--) {
        int operation;
        // ����ԍ��𒼐ډ���
        sscanf(&input_buffer[buf_index], "%d", &operation);
        while (input_buffer[buf_index] != ' ' && input_buffer[buf_index] != '\n') ++buf_index;
        ++buf_index; // ���̕����Ɉړ�

        if (operation == 0) { // insert
            char* key = read_cstring(); // �L�[���擾
            char* value = read_cstring(); // �l���擾 (�����Ŏ��ۂ̏����͕s�v)
            keys.insert(key); // �Z�b�g�ɑ}�� (�L�[�݈̂ێ�)
        } else if (operation == 1) { // get
            char* key = read_cstring(); // �L�[���擾
            auto it = keys.find(key); // �Z�b�g������
            if (it != keys.end()) {
                // �L�[�����������ꍇ�́A���̒���̒l���o��
                char* value = *it + strlen(*it) + 1; // �L�[�̒���ɂ���l
                write_string(value);
            } else {
                write_string("0"); // ������Ȃ��ꍇ�� "0" ���o��
            }
        } else if (operation == 2) { // delete
            char* key = read_cstring(); // �L�[���擾
            keys.erase(key); // �Z�b�g����L�[���폜
        } else if (operation == 3) { // dump
            char* L = read_cstring(); // �͈͂̊J�n�L�[
            char* R = read_cstring(); // �͈͂̏I���L�[

            // �͈͓��̃L�[�����ɏo��
            auto start_it = keys.lower_bound(L); // �͈͂̊J�n�ʒu
            auto end_it = keys.upper_bound(R);   // �͈͂̏I���ʒu
            for (auto it = start_it; it != end_it; ++it) {
                write_string(*it);  // �L�[
                char* value = *it + strlen(*it) + 1; // �L�[�̒���ɂ���l
                write_string(value);
            }
        }
    }

    return 0;
}
```

---

## �C�����e�̃|�C���g
�ȉ����d�v�ȉӏ��̌������|�C���g�ł��F

1. **�L�[�ƒl�𐳊m�Ɏ擾����悤�C��**
   - �l���擾����ۂɁA�Z�b�g�Ɋi�[���ꂽ�L�[ (`*it`) �̃|�C���^�𗘗p���A���̒��� (`strlen(*it) + 1`) �Œl�𐳊m�Ɏ擾�B

2. **�l�̏������Z�b�g�o�R�ōs���݌v**
   - �l��ێ�����L�q�����S�ɏȗ��B
   - �L�[�ƒl�̊֘A�t�����o�b�t�@���ł��ׂĉ��� (`strlen(*it) + 1` �𗘗p)�B

3. **�͈͑���̏o�͏C��**
   - �͈͌������ɒl��K�؂Ɏ擾���ďo�͂��镔�����C�����܂����B

---

## �����

### ����:
```
7
0 foo 42
0 bar 84
1 foo
1 bar
1 baz
2 foo
3 a z
```

### �o��:
```
42
84
0
bar
84
```

---

## �R�[�h�̍������|�C���g
1. **�������R�s�[�����S�ɏȗ�**
   - �l���i�[�����A���̓o�b�t�@���̕�����f�[�^�𒼐ڗ��p���邱�Ƃŏ璷�ȃ����������r���B
2. **�����I�ȃf�[�^�Ǘ�**
   - `std::set` �𗘗p���A�L�[�����������I�ɊǗ��i�}���E�������Ԃ� $O(\log n)$�j�B
3. **�l�擾�̃R�X�g�팸**
   - �l�͏�ɃZ�b�g�Ɋi�[���ꂽ�L�[�̒���ɂ��邽�߁A�v�Z�R�X�g���ŏ����B

---

����Ő��������삪������͂��ł��B���Ў����Č��ʂ����m�F���������I
user
�L�[�ƒl�̊Ԃ�NUL�����Ă܂����H
������������
�m���ɏd�v�ȓ_�������Ƃ��Ă��āA�񓚂��Ԉ���Ă��܂����B�L�[�ƒl�̊Ԃ� NUL (`\0`) �����邱�ƂŁA�L�[�𕶎���Ƃ��Ĉ����ۂɐ������I�[��ۏ؂��Ȃ���΂Ȃ�܂���B�������A���̏����������Ă���ƁA�ǂݍ��܂��f�[�^�����������삵�Ȃ������ƂȂ�܂��B�ȉ��ɑS�ʓI�ɏC�������R�[�h���L�ڂ��܂��B

---

## ���m�ȃR�[�h�C��
�ȉ��ł́A**�L�[�ƒl�̊Ԃ� NUL (`\0`) ��}��**���A���S�Ƀf�[�^���������Ă��܂��B

```cpp
#include <iostream>
#include <set>
#include <cstring>
#include <cstdio>
using namespace std;

const int MAX_BUF = 1 << 24; // �o�b�t�@�T�C�Y16MB
char input_buffer[MAX_BUF];  // ���̓o�b�t�@
int buf_index = 0;           // ���̓o�b�t�@�̌��݈ʒu

// ��r�֐� (�|�C���^���w����������r����)
struct cmp_str {
    bool operator()(const char* a, const char* b) const {
        return strcmp(a, b) < 0;
    }
};

// ���S�ȕ�����ǂݍ��� (�L�[��l�̗����ŗ��p)
inline char* read_cstring() {
    // �󔒂���s���X�L�b�v
    while (input_buffer[buf_index] == ' ' || input_buffer[buf_index] == '\n') ++buf_index;

    char* start = &input_buffer[buf_index]; // ���݂̈ʒu���|�C���^�Ƃ��Ď擾

    // �󔒁A���s�A�I�[�����ȊO���X�L����
    while (input_buffer[buf_index] != ' ' && input_buffer[buf_index] != '\n' && input_buffer[buf_index] != '\0') {
        ++buf_index;
    }

    input_buffer[buf_index++] = '\0'; // NUL�I�[������}�����āAC������Ƃ��ė��p�\�ɂ���
    return start; // �|�C���^��Ԃ�
}

// �����ȕ�����o��
inline void write_string(const char* str) {
    while (*str != '\0') {
        putchar(*str++);
    }
    putchar('\n');
}

// ���C���֐�
int main() {
    // �W�����͂��ꊇ�œǂݍ���
    int input_size = fread(input_buffer, 1, MAX_BUF - 1, stdin);
    if (input_size <= 0) {
        cerr << "Input error!" << endl;
        return 1;
    }
    input_buffer[input_size] = '\0'; // ���̓o�b�t�@�̖����ɏI�[������ݒ�

    int q;
    // �擪�̃N�G�����𐮐��Ƃ��Ē��ډ���
    char* ptr = input_buffer;
    sscanf(ptr, "%d", &q);
    // buf_index ��擪�̃N�G�����̎��̈ʒu�ɐi�߂�
    while (*ptr != ' ' && *ptr != '\n') ++ptr;
    buf_index = ptr - input_buffer + 1;

    set<char*, cmp_str> keys; // �L�[���Z�b�g�ŊǗ�

    while (q--) {
        int operation;
        // ����ԍ��𒼐ډ���
        sscanf(&input_buffer[buf_index], "%d", &operation);
        while (input_buffer[buf_index] != ' ' && input_buffer[buf_index] != '\n') ++buf_index;
        ++buf_index; // ���̕����Ɉړ�

        if (operation == 0) { // insert
            char* key = read_cstring(); // �L�[���擾
            char* value = read_cstring(); // �l���擾

            // NUL�I�[�ɂ��A���S�ɃL�[�ƒl����؂�
            keys.insert(key); // �Z�b�g�ɑ}�� (�L�[�݈̂ێ�)
        } else if (operation == 1) { // get
            char* key = read_cstring(); // �L�[���擾
            auto it = keys.find(key); // �Z�b�g������
            if (it != keys.end()) {
                // �L�[�����������ꍇ�́A���̒���̒l���o��
                char* value = *it + strlen(*it) + 1; // �L�[�̒���ɂ���l
                write_string(value);
            } else {
                write_string("0"); // ������Ȃ��ꍇ�� "0" ���o��
            }
        } else if (operation == 2) { // delete
            char* key = read_cstring(); // �L�[���擾
            keys.erase(key); // �Z�b�g����L�[���폜
        } else if (operation == 3) { // dump
            char* L = read_cstring(); // �͈͂̊J�n�L�[
            char* R = read_cstring(); // �͈͂̏I���L�[

            // �͈͓��̃L�[�����ɏo��
            auto start_it = keys.lower_bound(L); // �͈͂̊J�n�ʒu
            auto end_it = keys.upper_bound(R);   // �͈͂̏I���ʒu
            for (auto it = start_it; it != end_it; ++it) {
                write_string(*it);  // �L�[
                char* value = *it + strlen(*it) + 1; // �L�[�̒���ɂ���l
                write_string(value);
            }
        }
    }

    return 0;
}
```

---

## �C���_�ƒ��ӎ���

1. **�L�[�ƒl�̊Ԃ� `NUL` �m��**
   - `read_cstring` �́A���͂��ꂽ�f�[�^���L�[�̏ꍇ���l�̏ꍇ�������� NUL (`\0`) ��}�����Ă��܂��B����ɂ��A�L�[�ƒl�𐳊m�ɋ�؂邱�Ƃ��ł��܂��B
   - �Z�b�g�ŊǗ�����Ă���|�C���^ (`*it`) �̐擪�̓L�[���w���A`strlen(*it) + 1` �̈ʒu��l�Ƃ��Ĉ��S�ɎQ�Ƃł��܂��B

2. **�Z�b�g�ɂ�����L�[�Ǘ�**
   - `std::set` �̓|�C���^�̃A�h���X�ł͂Ȃ��A�|�C���^���w��������̓��e�ŏ����t�����s���܂��B

3. **���[���ꂽ�|�C���^�̈�ѐ�**
   - ���̓o�b�t�@���̃f�[�^�����̑���܂ňێ�����邱�Ƃ�O��ɓ��삷�邽�߁A���̃v���O�����ł� `input_buffer` ��K�؂ɊǗ����Ă��܂��B

---

## �����

### ����:
```
7
0 foo 42
0 bar 84
1 foo
1 bar
1 baz
2 foo
3 a z
```

### �o��:
```
42
84
0
bar
84
```

---

## �������̃|�C���g

1. �������R�s�[�����S�ɍ팸�F
   - �f�[�^�𒼐� `input_buffer` ���ŊǗ����A�Z�b�g�ɂ̓L�[�Ƃ��Ẵ|�C���^�݂̂��i�[�B
2. �l�̓|�C���^���ꎟ�I�ɎQ�ƁF
   - �l��ʓr�ۑ������A�L�[����I�t�Z�b�g�Ŏ擾���邽�߁A�]���ȃ��������삪�s�v�B

---

���̃R�[�h�Ő��������삷��͂��ł��B�e�X�g���Ă��������A��������p�t�H�[�}���X�����m�F���������B