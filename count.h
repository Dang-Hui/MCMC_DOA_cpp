#pragma once
#pragma once
#ifndef COUNT_H_ 
#define COUNT_H_
#include <vector.h>
using namespace splab;
class Count//求解最后100组数据中出现次数最多的一组数据
{
public:
    Vector<double> majorityElement(Vector<Vector<double>> nums)
    {

        Vector<double> res = nums[0];
        Vector<Vector<double>>::iterator it;
        int count = 1;
        for (it = nums.end() - 100;it != nums.end(); it++)
        {
            if (res == *it)
                count++;
            else
            {
                count--;
                if (count == 0)
                    res = *(it + 1);
            }
        }
        return res;
    }
};
#endif
