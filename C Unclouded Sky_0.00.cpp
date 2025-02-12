#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define min(a, b) ((a) < (b) ? (a) : (b))

typedef struct {
    int dx, dy;
} Direction;

// �����ɉ������ړ��x�N�g����Ԃ��֐�
Direction getDirection(const char* D) {
    if (D[0] == 'N' && D[1] == 'E') return (Direction) { 1, -1 };
    if (D[0] == 'N' && D[1] == 'W') return (Direction) { 1, 1 };
    if (D[0] == 'N')  return (Direction) { 1, 0 };
    if (D[0] == 'S' && D[1] == 'E') return (Direction) { -1, -1 };
    if (D[0] == 'S' && D[1] == 'W') return (Direction) { -1, 1 };
    if (D[0] == 'E')  return (Direction) { 0, -1 };
    if (D[0] == 'S')  return (Direction) { -1, 0 };
    if (D[0] == 'W')  return (Direction) { 0, 1 };
    return (Direction) { 0, 0 }; // default (invalid)
}

int calculateExitTime(int x, int y, int H, int W, const Direction dir) {
    int time = INT_MAX;

    // �s�����ɃO���b�h�O�֏o�鎞��
    if (dir.dx > 0) { // ����� (����)
        time = min(time, (H - x) / dir.dx);
    }
    else if (dir.dx < 0) { // �k���� (����)
        time = min(time, (x + 1) / -dir.dx);
    }

    // ������ɃO���b�h�O�֏o�鎞��
    if (dir.dy > 0) { // ������ (����)
        time = min(time, (W - y) / dir.dy);
    }
    else if (dir.dy < 0) { // ������ (����)
        time = min(time, (y + 1) / -dir.dy);
    }

    return time;
}

int main() {
    int H, W;
    scanf("%d %d", &H, &W);

    char grid[1000][1000 + 1];
    for (int i = 0; i < H; i++) {
        scanf("%s", grid[i]);
    }

    char D[3];
    scanf("%s", D);

    // ��������ړ��x�N�g�����擾
    Direction dir = getDirection(D);

    int maxTime = 0;

    // �_�̈ʒu�𒲂ׁA�ł����Ԃ���������̂�������
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (grid[i][j] == '#') {
                // �_�����݂̃}�X (i, j) �ɑ���
                int time = calculateExitTime(i, j, H, W, dir);
                if (time > maxTime) {
                    maxTime = time;
                }
            }
        }
    }

    // �������o��
    printf("%d\n", maxTime);

    return 0;
}
