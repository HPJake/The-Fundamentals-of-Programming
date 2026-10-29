#include <iostream>
#include <algorithm> //for next_permutation() 全排列
using namespace std;

int main(){
	int a[5] = {1, 2, 3, 4, 5};
	// a[0]~a[4] 分别表示 A、B、C、D、E 的名次
    // 初始排名为 1、2、3、4、5, 之后使用 next_permutation枚举
    
	do { //用 do...while 而不是普通 while （while 会先调用函数，再执行循环体 ） 
		bool A = (a[1] == 2) + (a[0] == 3) == 1;

        // B：B第二；E第四
        bool B = (a[1] == 2) + (a[4] == 4) == 1;

        // C：C第一；D第二
        bool C = (a[2] == 1) + (a[3] == 2) == 1;

        // D：C第五；D第三
        bool D = (a[2] == 5) + (a[3] == 3) == 1;

        // E：E第四；A第一
        bool E = (a[4] == 4) + (a[0] == 1) == 1;

        // 五个人的预测都满足条件，
        // 才说明当前排列是正确答案
        if (A && B && C && D && E) {

            // 按 A、B、C、D、E 的顺序输出
            for (int i = 0; i < 5; i++) {
                cout << a[i] << endl;
            }
            
            return 0; // 找到唯一答案，结束程序
    	}
	}while (next_permutation(a, a + 5)); //next_permutation(起始迭代器, 结束迭代器);
    return 0;
}

/*

#利用 bool 进行计数
两个都错：0; 一个对、一个错：1; 两个都对：2

#next_permutation();
将一个序列变成字典序中的下一个排列（Next Lexicographical Permutation）
***用 do...while 而不是 while : 需要先处理初始排列，再生成下一个排列。
***while 会先调用函数，再执行循环体 

*/
