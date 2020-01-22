#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include "DataStruct_Array.h"
#define F 2.2E3
#define Time 1E6
// #define PRINT_RESULT

using namespace std;
using namespace FYSPACE;

// 数据量规模
const int ni = 500;
const int nj = 400;
const int nk = 300;

// 正确性检查的取样规模
const int checkNi = ni / 200 + 1;

typedef double RDouble;
typedef FYArray<RDouble, 3> RDouble3D;
typedef FYArray<RDouble, 4> RDouble4D;

int preccheck(RDouble4D result, const std::string &filename);
void resultprint(RDouble4D result, const std::string &filename);

inline unsigned long long rdtsc(void)
{
    unsigned long hi = 0, lo = 0;

    __asm__ __volatile__("lfence;rdtsc" : "=a"(lo), "=d"(hi));

    return (((unsigned long long)lo)) | (((unsigned long long)hi) << 32);
}

int main()
{
    double start, end, elapsed;
    int mst = 0;
    int med = 3;

    Range I(-1, ni + 1);
    Range J(-1, nj + 1);
    Range K(-1, nk + 1);
    RDouble3D x(I, J, K, fortranArray);
    for (int k = -1; k <= nk + 1; ++k)
    {
        for (int j = -1; j <= nj + 1; ++j)
        {
            for (int i = -1; i <= ni + 1; ++i)
            {
                x(i, j, k) = i * 0.1 + j * 0.2 + k * 0.3;
            }
        }
    }

    Range M(mst, med);
    RDouble4D result(I, J, K, M, fortranArray);
    result(I, J, K, M) = 2.0;

    start = rdtsc();
    // 此处开始统计计算部分代码运行时间

    for (int cnt = 1; cnt < 5; cnt++)
    {
        Range IW(-1, ni + 1);
        Range JW(-1, nj + 1);
        Range KW(-1, nk + 1);

        RDouble3D worksx(IW, JW, KW, fortranArray);

        // Magical Number
        worksx(I, J, K) = cnt * x(I, J, K) * x(I, J, K) + 1.7 * x(I, J, K);

        for (int m = mst; m <= med; ++m)
        {
            result(I, J, K, m) *= -worksx(I, J, K) * x(I, J, K);
        }

        Range I0(1, ni);
        Range J0(1, nj);
        Range K0(1, nk);

        for (int m = mst; m <= med; ++m)
        {
            result(I0, J0, K0, m) /= worksx(I0, J0, K0);
        }
    }
    //----------------------------------------------------
    //以下为正确性对比部分！
    //----------------------------------------------------
    end = rdtsc();
    elapsed = (end - start) / (F * Time);
    cout << "The programe elapsed " << elapsed << setprecision(8) << " s" << endl;

#ifdef PRINT_RESULT
    resultprint(result, "check.txt");
    cout << "Result printed!" << std::endl;
#else
    if (!preccheck(result, "check.txt"))
        cout << "Result check passed!" << endl;
#endif // PRINT_RESULT

    return 0;
}

void resultprint(RDouble4D result, const std::string &filename)
{
    ofstream file(filename, std::ofstream::binary);
    for (int i = 0; i < checkNi; ++i)
    {
        for (int j = 0; j < nj; ++j)
        {
            for (int k = 0; k < nk; ++k)
            {
                for (int m = 0; m < 3; ++m)
                {
                    double num = result(i, j, k, m);
                    file.write(reinterpret_cast<char *>(&num), sizeof(num));
                }
            }
        }
    }
}

int preccheck(RDouble4D result, const std::string &filename)
{
    double tmp, real;
    ifstream file(filename, std::ofstream::binary);
    if (!file)
    {
        cout << "Error opening check file! ";
        exit(1);
    }
    for (int i = 0; i < checkNi; ++i)
    {
        for (int j = 0; j < nj; ++j)
        {
            for (int k = 0; k < nk; ++k)
            {
                for (int m = 0; m < 3; ++m)
                {
                    file.read(reinterpret_cast<char *>(&tmp), sizeof(double));
                    if (fabs(result(i, j, k, m) - tmp) > 1e-6)
                    {
                        real = result(i, j, k, m);
                        cout << "Precision check failed !" << endl;
                        cout << "Your result is " << setprecision(15) << real << endl;
                        cout << "The Standard result is " << setprecision(15) << tmp << endl;
                        cout << "The wrong position is " << endl;
                        cout << "i=" << i << ",j=" << j << ",k=" << k << ",m=" << m << endl;
                        exit(1);
                    }
                }
            }
        }
    }
    file.close();
    return 0;
}
