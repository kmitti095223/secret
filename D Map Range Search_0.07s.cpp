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