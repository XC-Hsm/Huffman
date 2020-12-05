#include "BM.h"
#define SIZE 256    //�ַ����ַ���

void suffixes(char* x, int m, int* suff)
{
    suff[m - 1] = m;
    for (int i = m - 2; i >= 0; --i) {
        int q = i;
        while (q >= 0 && x[q] == x[m - 1 - i + q])
            --q;
        suff[i] = i - q;
    }
}
void preBmGs(char* x, int m, int bmGs[]) {
    int i, j;
    int* suff = (int*)malloc(sizeof(int) * m);
    suffixes(x, m, suff);
    for (i = 0; i < m; ++i)
        bmGs[i] = m;
    j = 0;
    for (i = m - 1; i >= 0; --i)
        if (suff[i] == i + 1)
            for (; j < m - 1 - i; ++j)
                if (bmGs[j] == m)
                    bmGs[j] = m - 1 - i;
    for (i = 0; i <= m - 2; ++i)
        bmGs[m - 1 - suff[i]] = m - 1 - i;
}
void preBmBc(char* b, int m, int* badchar)//(ģʽ���ַ�b��ģʽ������m��ģʽ���Ĺ�ϣ��)
{
    for (int i = 0; i < SIZE; ++i)
    {
        badchar[i] = m;//��ϣ���ʼ��Ϊ-1
    }
    for (int i = 0; i < m; i++)
    {
        badchar[b[i]] = m - i - 1;//�ظ��ַ������ǣ���¼���������ֵĸ��ַ���λ��
    }
}

void BM(char* x, int m, char* y, int n) {
    int i, j, bmBc[SIZE];
    int* bmGs = (int*)malloc(sizeof(int) * m);
    /* Preprocessing */
    preBmGs(x, m, bmGs);
    preBmBc(x, m, bmBc);

    /* Searching */
    j = 0;
    while (j <= n - m) {
        for (i = m - 1; i >= 0 && x[i] == y[i + j]; --i);
        if (i < 0) {
            printf("%d\t", j);
            j += bmGs[0];
        }
        else
            j += bmGs[i] > bmBc[y[i + j]] - m + 1 + i ? bmGs[i] : bmBc[y[i + j]] - m + 1 + i;
    }
}