#include <cstdio>
#include <cstring>
#include <string_view>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_BUF = 1 << 24; // 16MB
char input_buffer[MAX_BUF];
int buf_index = 0;
char output_buffer[MAX_BUF];
int output_index = 0;

// �������́F����
inline int read_int() {
    int x = 0, neg = 1;
    while (input_buffer[buf_index] < '0' || input_buffer[buf_index] > '9') {
        if (input_buffer[buf_index] == '-') neg = -1;
        ++buf_index;
    }
    while (input_buffer[buf_index] >= '0' && input_buffer[buf_index] <= '9') {
        x = x * 10 + (input_buffer[buf_index] - '0');
        ++buf_index;
    }
    return x * neg;
}

// �������́Fstring_view�i���I�m�ۂ������j
inline std::string_view read_sv() {
    while (input_buffer[buf_index] == ' ' || input_buffer[buf_index] == '\n')
        ++buf_index;
    int start = buf_index;
    while (input_buffer[buf_index] > ' ')
        ++buf_index;
    return { input_buffer + start, size_t(buf_index - start) };
}

// �����o�́Fstring_view
inline void write_string(std::string_view sv) {
    int len = int(sv.size());
    if (output_index + len + 1 > MAX_BUF) {
        fwrite(output_buffer, 1, output_index, stdout);
        output_index = 0;
    }
    memcpy(output_buffer + output_index, sv.data(), len);
    output_index += len;
    output_buffer[output_index++] = ' ';
}

// �����o�́F����
inline void write_int(int x) {
    char buf[12];
    int index = 0;
    if (x == 0) {
        output_buffer[output_index++] = '0';
        output_buffer[output_index++] = '\n';
        return;
    }
    if (x < 0) {
        output_buffer[output_index++] = '-';
        x = -x;
    }
    while (x) {
        buf[index++] = '0' + (x % 10);
        x /= 10;
    }
    while (index)
        output_buffer[output_index++] = buf[--index];
    output_buffer[output_index++] = '\n';
}

// FlatMap : �L�[�� string_view�A�l�� int �Ƃ���
class FlatMap {
public:
    using value_type = std::pair<std::string_view, int>;

    // �}���^�X�V�F���łɃL�[�����݂���΍X�V�A�Ȃ���Α}��
    void emplace(std::string_view key, int value) {
        auto it = std::lower_bound(data.begin(), data.end(), key,
            [](const value_type& a, std::string_view b) { return a.first < b; });
        if (it != data.end() && it->first == key) {
            it->second = value;
        }
        else {
            data.insert(it, { key, value });
        }
    }

    // �����F������Βl�ւ̃|�C���^�A�Ȃ���� nullptr
    int* find(std::string_view key) {
        auto it = std::lower_bound(data.begin(), data.end(), key,
            [](const value_type& a, std::string_view b) { return a.first < b; });
        return (it != data.end() && it->first == key) ? &it->second : nullptr;
    }

    // �폜
    void erase(std::string_view key) {
        auto it = std::lower_bound(data.begin(), data.end(), key,
            [](const value_type& a, std::string_view b) { return a.first < b; });
        if (it != data.end() && it->first == key) {
            data.erase(it);
        }
    }

    auto begin() { return data.begin(); }
    auto end() { return data.end(); }

private:
    std::vector<value_type> data;
};

// FlatMap : 1�����z��ɕύX
FlatMap M_flat[26 * 26 * 26];  // 26�~26�~26��1�����z���

int main() {
    int input_size = (int)fread(input_buffer, 1, MAX_BUF - 1, stdin);
    if (input_size <= 0)
        return 1;
    input_buffer[input_size] = '\0';

    int q = read_int();
    while (q--) {
        int op = read_int();
        std::string_view key = read_sv();

        // �L�[�̐擪3�������C���f�b�N�X��
        int i1 = key[0] - 'a';
        int i2 = key.size() > 1 ? key[1] - 'a' : 0;
        int i3 = key.size() > 2 ? key[2] - 'a' : 0;

        int index = (i1 * 26 * 26) + (i2 * 26) + i3;

        if (op == 0) { // insert ����
            int value = read_int();
            M_flat[index].emplace(key, value);
        }
        else if (op == 1) { // get ����
            int* val = M_flat[index].find(key);
            write_int(val ? *val : 0);
        }
        else if (op == 2) { // delete ����
            M_flat[index].erase(key);
        }
        else if (op == 3) { // dump ����
            std::string_view R = read_sv(); // �͈͂̏��
            int j1 = R[0] - 'a';
            int j2 = R.size() > 1 ? R[1] - 'a' : 0;
            int j3 = R.size() > 2 ? R[2] - 'a' : 0;

            int j_index = (j1 * 26 * 26) + (j2 * 26) + j3;

            // �擪3�����͈̔͂Ŋe�o�P�b�g��T��
            for (int i = index; i <= j_index; ++i) {

                auto& mp = M_flat[i];

                if ((i == index) || (i == j_index))
                {
                    // lower_bound �� dump �͈͂̊J�n�ʒu���擾
                    auto it = std::lower_bound(mp.begin(), mp.end(), key,
                        [](const FlatMap::value_type& p, std::string_view key) { return p.first < key; });
                    while (it != mp.end() && it->first <= R) {
                        write_string(it->first);
                        write_int(it->second);
                        ++it;
                    }
                }
                else
                {
                    auto it = mp.begin();
                    while (it != mp.end() ) {
                        write_string(it->first);
                        write_int(it->second);
                        ++it;
                    }
                }
            }
        }
    }

    if (output_index > 0)
        fwrite(output_buffer, 1, output_index, stdout);

    return 0;
}
