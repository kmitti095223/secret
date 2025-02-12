#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMPARE_LEN 1000 // ��r�̍ő啶�������`

// ��r�֐��iqsort�p�A�A�h���X�̎w����������������Ŕ�r�j
int compare(const void *a, const void *b) {
    const char **pa = (const char **)a;
    const char **pb = (const char **)b;
    return strncmp(*pa, *pb, MAX_COMPARE_LEN); // �ő�1000�����܂Ŏ�������r
}

// �N�G���p�^�[���ƃT�t�B�b�N�X�z��̗v�f���r�ibsearch�p�j
int match_pattern(const void *pattern, const void *suffix) {
    const char *pa = (const char *)pattern;
    const char **pb = (const char **)suffix;
    return strncmp(pa, *pb, strlen(pa)); // �p�^�[�����܂Ŕ�r
}

int main() {
    static char T[1000001]; // ���͕����� T�i�ő咷 1000000, static �ɕύX�j
    static char P[MAX_COMPARE_LEN + 1]; // �N�G�������� P�istatic �ɕύX�j
    int Q;                             // �N�G���� Q

    // T �� Q �̓ǂݍ���
    scanf("%s", T);
    scanf("%d", &Q);

    int n = strlen(T);

    // �d�������������T�t�B�b�N�X�z����쐬
    char **unique_suffixes = (char **)malloc(n * sizeof(char *));
    int unique_count = 0;

    // �T�t�B�b�N�X��ǉ����Ȃ���i1000�����܂ł��r���āj�d��������
    for (int i = 0; i < n; i++) {
        if (unique_count == 0 || strncmp(&T[i], unique_suffixes[unique_count - 1], MAX_COMPARE_LEN) != 0) {
            unique_suffixes[unique_count++] = &T[i];
        }
    }

    // �������Ƀ\�[�g
    qsort(unique_suffixes, unique_count, sizeof(char *), compare);

    // �N�G��������
    for (int i = 0; i < Q; i++) {
        scanf("%s", P);

        // bsearch ���g�p���ăp�^�[����T��
        void *found = bsearch(P, unique_suffixes, unique_count, sizeof(char *), match_pattern);

        // ���ʂ��o��
        if (found != NULL) {
            printf("1\n"); // �p�^�[������������
        } else {
            printf("0\n"); // �p�^�[����������Ȃ�
        }
    }

    return 0; // �������̉���������폜
}
