//=============================================================================
// �C���N���[�h
//=============================================================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#ifndef WINDOWS_DEBUG
#include <unistd.h>
#else
#include <io.h>
#endif

#ifdef WINDOWS_DEBUG
#include <windows.h>
LARGE_INTEGER m_Freq, m_Start, m_End;
int nCount1 = 0, nCount2 = 0;
#endif

//=============================================================================
// �萔
//=============================================================================
#define MAX_LEN_T			1000000					// ������ T�̍ő咷
#define MAX_LEN_T_PLUS_1	(MAX_LEN_T+1)			// ������ T�̍ő咷+1

#define MAX_LEN_P			1000					// ������ P�̍ő咷
#define MAX_LEN_P_PLUS_1	(MAX_LEN_P+1)			// ������ P�̍ő咷+1

#define MAX_COUNT_Q			10000					// ������ P�̐�(Q)�̍ő�l

#define MAX_COUNT_Q         10000
#define MAX_COUNT_PLUS_1    (MAX_COUNT_Q+1)

// �W�����͓ǂݍ��݂̍ő�T�C�Y
#define INPUT_SIZE			(MAX_LEN_T_PLUS_1 + ( MAX_LEN_P_PLUS_1 *MAX_COUNT_Q ))

// �����𐔒l�ɕϊ����邽�߂̃e�[�u��('0'��0�A'1'��1�A'A'��10 �Ȃ�)
const unsigned char CHAR_TO_NO[] = {
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18,
	0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x32,
	0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D
};
//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
int			g_nLenP;			// ������ P�̒���
char		*g_pT;				// ���͒l ������ T
int			g_nLenT;			// ���͒l ������ T �̒���
int			g_nQ;				// ���͒l ���� Q
char		*pP;				// ���͒l ������ P
int			g_nLenPMin;			// ���͒l ������ P �̍ŏ�
int			i;					// ���[�v�J�E���^
char		*p, *p1, *p2;		// �|�C���^(�ėp)
int			len;				// ������(�ėp)

char		*g_Table_Sentou;	// �擪X�����̃e�[�u��

void proc_char_3();	// ������� > 2 �p����
void proc_char_2(); // ������� = 2 �p����
void proc_char_1();	// ������� = 1 �p����

// �\�[�g�p��r�֐�
int compare(const void* a, const void* b)
{
	return memcmp(*((char**)a), *((char**)b), MAX_LEN_P);
}

// 2���T���p��r�֐�
int compare2(const void* a, const void* b)
{
	return memcmp((char*)a, *((char**)b), g_nLenP);
}

// vec���ǂ�
char** MyVec_data;
int MyVec_size; // ���ݎg�p���̗̈�T�C�Y
int MyVec_reserve_size; // �\��̈�T�C�Y

void vec_create(int size)
{
	MyVec_reserve_size = size;
	MyVec_data = (char**)malloc(sizeof(char*) * MyVec_reserve_size);
	MyVec_size = 0;
}

#define vec_push( pWk)													\
{																		\
	if (MyVec_size == MyVec_reserve_size)								\
			{															\
		MyVec_reserve_size = MyVec_reserve_size * 2;					\
		char** wk = (char**)malloc(sizeof(char*) * MyVec_reserve_size);	\
		memcpy(wk, MyVec_data, sizeof(int) * MyVec_size);				\
		free(MyVec_data);												\
		MyVec_data = wk;												\
			}															\
	MyVec_data[MyVec_size] = pWk;										\
	MyVec_size++;														\
}


//=============================================================================
// ���C���֐�
//=============================================================================
int main(void) {

#ifdef WINDOWS_DEBUG // �f�o�b�O�p�������Ԍv��
	QueryPerformanceFrequency(&m_Freq);
	QueryPerformanceCounter(&m_Start);
#endif

	//----------------------------------------------------------------------------
	// �W�����͓ǂݍ���
	//----------------------------------------------------------------------------
	// �W�����͂����ׂēǂݍ��ށB
	g_pT = (char*)malloc(sizeof(char*) * INPUT_SIZE);
	i = read(0, g_pT, INPUT_SIZE);
	g_pT[i] = 0x0A;
	
	// ������ T �̃A�h���X���擾����B
	// �����ɕ����̐����J�E���g����B
	char CharList['z' + 1] = { 0 };
	p1 = g_pT;
	while (*p1 != '\n')
	{
		CharList[*p1++] = 1;
	}
	*p1 = 0;
	g_nLenT = p1 - g_pT;
	p1++;

	int char_count = 0;
	for (i = '0'; i <= 'z'; i++)
	{
		char_count += CharList[i];
	}

	// ���� Q (������ P�̐�) ���擾����B
	p2 = strchr(p1, '\n');
	*p2 = 0;
	g_nQ = atoi(p1);
	p2++;

	// ������ P �̐擪�A�h���X��ێ�����B
	pP = p2;

	//----------------------------------------------------------------------------
	// ������ T �Ɋ܂܂�镶����ނŏ�������
	//----------------------------------------------------------------------------
	if (char_count  > 2)
	{
		// ������ T �Ɋ܂܂�镶����� > 2 �̏ꍇ
		proc_char_3();
	}
	else if (char_count == 2)
	{
		// �����̎�ނ����Ȃ�(��2)�̏ꍇ�̂��߂̓��ꏈ�� �� Case #11 �΍�
		proc_char_2();
	}
	else { // char_count == 1
		// ������ T �Ɋ܂܂�镶����� �� 1 �̏ꍇ
		proc_char_1();
	}

#ifdef WINDOWS_DEBUG // �f�o�b�O�p�������Ԍv��
	QueryPerformanceCounter(&m_End);
	printf("���s����:%dms\n", (int)((double)(m_End.QuadPart - m_Start.QuadPart) * 1000.0 / m_Freq.QuadPart));
	printf("nCount1=%d  nCount2=%d\n", nCount1, nCount2);
	while (1) getchar();
#endif
}


//=============================================================================
// ������ T �Ɋ܂܂�镶����� > 2 �̏���
// ���擪4����(3�o�C�g)���e�[�u���Ɋi�[���Č���
//=============================================================================
void proc_char_3()
{
	//-----------------------------------------------------
	// ��������
	//-----------------------------------------------------
	// �ϐ������Ȃ�
	char* result = (char*)malloc((g_nQ + 1) * 2 + 1);
	char* p_result = result;
	memset(result, '\n', (g_nQ + 1) * 2 + 1);

	int x;
	p = p2;

	char** List_PtrP = (char**)malloc(sizeof(char*) * g_nQ);
	int* List_LenP = (int*)malloc(sizeof(int) * g_nQ);

	g_Table_Sentou = (char*)malloc(256 * 256 * 256);
	memset(g_Table_Sentou, 0, 256 * 256 * 256);

	// �z�񏉊���
	// �������l�傫�߂Ŋm�ہB�s��������ǉ��B
	vec_create(10000);

	//-----------------------------------------------------
	// ������Q������List_PtrP���쐬
	//-----------------------------------------------------
	for (i = 0; i < g_nQ; i++) {

		List_PtrP[i] = p;
		List_LenP[i] = strchr(p, '\n') - p;

		x = CHAR_TO_NO[*(p++)];
		if (List_LenP[i] > 1)
		{
			x += (CHAR_TO_NO[*(p++)] << 6);
			if (List_LenP[i] > 2)
			{
				x += (CHAR_TO_NO[*(p++)] << 12);
				if (List_LenP[i] > 3)
				{
					x += (CHAR_TO_NO[*(p++)] << 18);
					if (List_LenP[i] > 4)
					{
						g_Table_Sentou[x] = 10; 
						p = List_PtrP[i] + List_LenP[i] + 1;
						continue;
					}
				}
			}
		}

		g_Table_Sentou[x] = (char)List_LenP[i] << 1;
		p = List_PtrP[i] + List_LenP[i] + 1;
	}

	//-----------------------------------------------------
	// ������T��1�����ځA2�����ځE�E�E�����ɔz��Ɋi�[
	// ������g_Table_Sentou���X�V
	//-----------------------------------------------------
	p = g_pT;
	len = g_nLenT - 3;
	if (len>0)
	{
		do
		{
			x = CHAR_TO_NO[*p];
			if (g_Table_Sentou[x] == 2) // ����=1
				g_Table_Sentou[x] |= 1;	// �擪1�o�C�g����v���Ă���΃t���O�𗧂Ă�

			x += (CHAR_TO_NO[*(p + 1)] << 6);
			if (g_Table_Sentou[x] == 4) // ����=2
				g_Table_Sentou[x] |= 1;

			x += (CHAR_TO_NO[*(p + 2)] << 12);
			if (g_Table_Sentou[x] == 6) // ����=3
				g_Table_Sentou[x] |= 1;

			x += (CHAR_TO_NO[*(p + 3)] << 18);
			if (g_Table_Sentou[x] == 8) // ����=4
				g_Table_Sentou[x] |= 1;

			// ����5�ȏ�
			if (g_Table_Sentou[x] && (g_Table_Sentou[x] != 9)){
				g_Table_Sentou[x] |= 1;
				vec_push(p);
			}
		} while (*(++p + 3));

	}
	// ���[�v���̔�������炷���ߍŌ��3�����̓��[�v�̊O�ŏ���
	// (�{�֐���3�����ȏ�ł����Ă΂�Ȃ�)
	
	// ��납��3������
	x = CHAR_TO_NO[*p];
	if (g_Table_Sentou[x] == 2)
		g_Table_Sentou[x] |= 1;

	x += (CHAR_TO_NO[*(p + 1)] << 6);
	if (g_Table_Sentou[x] == 4)
		g_Table_Sentou[x] |= 1;

	x += (CHAR_TO_NO[*(p + 2)] << 12);
	if (g_Table_Sentou[x] == 6)
		g_Table_Sentou[x] |= 1;
	p++;

	//---------------------------
	// ��납��2������
	x = CHAR_TO_NO[*p];
	if (g_Table_Sentou[x] == 2)
		g_Table_Sentou[x] |= 1;

	x += (CHAR_TO_NO[*(p + 1)] << 6);
	if (g_Table_Sentou[x] == 4)
		g_Table_Sentou[x] |= 1;
	p++;

	//---------------------------
	// ��Ԍ��̕���
	x = CHAR_TO_NO[*p];
	if (g_Table_Sentou[x] == 2)
		g_Table_Sentou[x] |= 1;

	//-----------------------------------------------------
	// ������ T�̔z����\�[�g
	//-----------------------------------------------------
	qsort((void*)MyVec_data, MyVec_size, sizeof(const char*), compare);

	//-----------------------------------------------------
	// ������ T ����A������ P ������
	//-----------------------------------------------------
	for (i = 0; i < g_nQ; i++) {

		if (List_LenP[i] > 4)
		{
			// ������P��5�����ȏ�̏ꍇ
			if (!(g_Table_Sentou[CHAR_TO_NO[*List_PtrP[i]]
				+ (CHAR_TO_NO[*(List_PtrP[i] + 1)] << 6)
				+ (CHAR_TO_NO[*(List_PtrP[i] + 2)] << 12)
				+ (CHAR_TO_NO[*(List_PtrP[i] + 3)] << 18)] & 1))
			{
				// g_Table_Sentou�Ƀt���O�������ĂȂ��ꍇ�A
				// ��������܂ł��Ȃ��u�����v�B
				*p_result = '0';
			}
			else
			{
				// 2���T��
				g_nLenP = List_LenP[i];
				*p_result = '0' + (bsearch(List_PtrP[i], MyVec_data, MyVec_size, sizeof(const char*), compare2) > 0);
			}
		}
		else {

			if (List_LenP[i] == 1) {
				// ������P��1�����̏ꍇ
				*p_result = '0' + (g_Table_Sentou[CHAR_TO_NO[*List_PtrP[i]]] & 1);
			}
			else if (List_LenP[i] == 2) {
				// ������P��2�����̏ꍇ
				*p_result = '0' + (g_Table_Sentou[CHAR_TO_NO[*List_PtrP[i]]
					+ (CHAR_TO_NO[*(List_PtrP[i] + 1)] << 6)] & 1);
			}
			else if (List_LenP[i] == 3) {
				// ������P��3�����̏ꍇ
				*p_result = '0' + (g_Table_Sentou[CHAR_TO_NO[*List_PtrP[i]]
					+ (CHAR_TO_NO[*(List_PtrP[i] + 1)] << 6)
					+ (CHAR_TO_NO[*(List_PtrP[i] + 2)] << 12)] & 1);
			}
			else {
				// ������P��3�����̏ꍇ
				*p_result = '0' + (g_Table_Sentou[CHAR_TO_NO[*List_PtrP[i]]
					+ (CHAR_TO_NO[*(List_PtrP[i] + 1)] << 6)
					+ (CHAR_TO_NO[*(List_PtrP[i] + 2)] << 12)
					+ (CHAR_TO_NO[*(List_PtrP[i] + 3)] << 18)] & 1);
			}
		}

		p_result += 2;
	}

	// ���ʏo�͗p������̖�����NULL�����ďo�́B
	*(p_result - 1) = 0;
	puts(result);
}

//=============================================================================
// ������ T �Ɋ܂܂�镶����� �� 2 �̏���
// ���擪10����(10�r�b�g)���e�[�u���Ɋi�[���Č���
//=============================================================================
void proc_char_2()
{
	int x;
	g_nLenPMin = MAX_LEN_P;

	vec_create(50000);

	g_Table_Sentou = (char*)malloc(sizeof(char) * 2048);
	memset(g_Table_Sentou, 0, 1024 * sizeof(char));

	// ���݂��镶����1�����ڂ��擾
	// �� �Ⴆ�� "a" �� "b"�̏ꍇ "a" �̕����R�[�h���擾����B
	char c = g_pT[0];

	for (i = 0; i < g_nQ; i++) {
		p1 = strchr(p2, '\n');

		len = p1 - p2;

		if (len < g_nLenPMin)
		{
			g_nLenPMin = len;
		}

		x = (*(p2) == c);
		if (len > 1) x += (((*(p2 + 1)) == c) << 1);
		if (len > 2) x += (((*(p2 + 2)) == c) << 2);
		if (len > 3) x += (((*(p2 + 3)) == c) << 3);
		if (len > 4) x += (((*(p2 + 4)) == c) << 4);
		if (len > 5) x += (((*(p2 + 5)) == c) << 5);
		if (len > 6) x += (((*(p2 + 6)) == c) << 6);
		if (len > 7) x += (((*(p2 + 7)) == c) << 7);
		if (len > 8) x += (((*(p2 + 8)) == c) << 8);
		if (len > 9) x += (((*(p2 + 9)) == c) << 9);
		if (len > 10) x += (((*(p2 + 10)) == c) << 10);

		g_Table_Sentou[x] = 1;

		p1++;
		p2 = p1;
	}

	//  ������ T �̏d��������������������B
	char* pNewT = (char*)malloc(MAX_LEN_T_PLUS_1);
	memcpy(pNewT, g_pT, g_nLenT);
	pNewT[g_nLenT] = 0;

	// p2 = pNewT;
	char SameChar = '?';
	int SameCount = 0;
	int k = 0;
	int nSitchCount = 0;

	p2 = g_pT;
	for (i = 0; i < g_nLenT; i++)
	{
		if (*p2 == SameChar)
		{
			if (SameCount <= MAX_LEN_P)
			{
				pNewT[k++] = *p2;
				SameCount++;
			}
		}
		else
		{
			pNewT[k++] = *p2;
			SameChar = *p2;
			SameCount = 0;
			nSitchCount++;
			if (nSitchCount > 2)
			{
				nSitchCount = -1;
				break;
			}
		}
		p2++;
	}

	if (nSitchCount >= 0)
	{
		pNewT[k++] = 0;
		g_nLenT = k;
		memcpy(g_pT, pNewT, g_nLenT);
	}

	//  ������ T �� 0 or 1 �ɒu������B
	char* pZeroOne = (char*)malloc(MAX_LEN_T_PLUS_1);
	memcpy(pZeroOne, g_pT, g_nLenT);
	pZeroOne[g_nLenT] = 0;

	p2 = pZeroOne;
	for (i = 0; i < g_nLenT; i++)
	{
		*p2 = *p2 == c;
		p2++;
	}

	p = g_pT;
	p2 = pZeroOne;
	len = g_nLenT - 10;
	for (i = 0; i < len; i++)
	{
		x = 0;

		while (1)
		{
			// 1�O�Ɠ����ꍇ�͒ǉ����Ȃ��B
			if (strcmp(p, p - 1) == 0)
			{
				break;
			}

			x = *(p2);
			x += *(p2 + 1) << 1;
			x += (*(p2 + 2) << 2);
			x += (*(p2 + 3) << 3);
			x += (*(p2 + 4) << 4);
			x += (*(p2 + 5) << 5);
			x += (*(p2 + 6) << 6);
			x += (*(p2 + 7) << 7);
			x += (*(p2 + 8) << 8);
			x += (*(p2 + 9) << 9);
			x += (*(p2 + 10) << 10);

			if (g_nLenPMin <= 10)	if (g_Table_Sentou[x]) { vec_push(p); break; }

			break;
		}

		p++;
		p2++;
	}

	for (i; i < g_nLenT; i++)
	{
		// i�����ڈȍ~�̕�����̃|�C���^
		vec_push(p);
		p++;
		p2++;
	}

	// ������ T ���\�[�g
	qsort((void*)MyVec_data, MyVec_size, sizeof(const char*), compare);

	// ������ T ����A������ P ������
	p = pP;

	for (i = 0; i < g_nQ; i++) {
		p1 = strchr(p, '\n');
		g_nLenP = p1 - p;

		if (bsearch(p, MyVec_data, MyVec_size, sizeof(const char*), compare2))
			printf("1\n");
		else
			printf("0\n");

		p = p1 + 1;
	}
}

//=============================================================================
// ������ T �Ɋ܂܂�镶����� �� 1 �̏���
// ��������1��z��Ɋi�[���Č���
//=============================================================================
void proc_char_1()
{
	// �z��ɒǉ� ���S�ē����Ȃ̂�1����
	vec_create(1);
	vec_push(g_pT);

	// ������ T ���\�[�g
	qsort((void*)MyVec_data, MyVec_size, sizeof(const char*), compare);

	// ����
	p = pP;
	for (i = 0; i < g_nQ; i++) {

		p1 = strchr(p, '\n');
		g_nLenP = p1 - p;

		if (bsearch(p, MyVec_data, MyVec_size, sizeof(const char*), compare2))
			printf("1\n");
		else
			printf("0\n");

		p = p1 + 1;
	}
}