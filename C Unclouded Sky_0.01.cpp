#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <climits>

using namespace std;

struct Direction {
    int dx, dy;
};

// �����ɉ������ړ��x�N�g����Ԃ��֐�
Direction getDirection(const string& D) {
    if (D == "N")  return {1,  0};
    if (D == "NE") return {1, -1};
    if (D == "E")  return {0, -1};
    if (D == "SE") return {-1, -1};
    if (D == "S")  return {-1,  0};
    if (D == "SW") return {-1,  1};
    if (D == "W")  return {0,  1};
    if (D == "NW") return {1,  1};
    throw invalid_argument("Invalid direction");
}

int calculateExitTime(int x, int y, int H, int W, const Direction& dir) {
    int time = INT_MAX;

    // �s�����ɃO���b�h�O�֏o�鎞��
    if (dir.dx > 0) { // ����� (����)
        time = min(time, (H - x) / dir.dx);
    } else if (dir.dx < 0) { // �k���� (����)
        time = min(time, (x + 1) / -dir.dx);
    }

    // ������ɃO���b�h�O�֏o�鎞��
    if (dir.dy > 0) { // ������ (����)
        time = min(time, (W - y) / dir.dy);
    } else if (dir.dy < 0) { // ������ (����)
        time = min(time, (y + 1) / -dir.dy);
    }

    return time;
}

int main() {
    int H, W;
    cin >> H >> W;

    vector<string> grid(H);
    for (int i = 0; i < H; i++) {
        cin >> grid[i];
    }

    string D;
    cin >> D;

    // ��������ړ��x�N�g�����擾
    Direction dir = getDirection(D);

    int maxTime = 0;

    // �_�̈ʒu�𒲂ׁA�ł����Ԃ���������̂�������
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (grid[i][j] == '#') {
                // �_�����݂̃}�X (i, j) �ɑ���
                int time = calculateExitTime(i, j, H, W, dir);
                maxTime = max(maxTime, time);
            }
        }
    }

    // �������o��
    cout << maxTime << endl;

    return 0;
}