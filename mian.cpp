#include <iostream>
#include <vector>

using std::vector;

constexpr int layer = 4;

struct stick {
    vector<int> a = vector<int>(layer);
    vector<int> b = vector<int>(layer);
    vector<int> c = vector<int>(layer);
}sticks;

struct num {
    int a;
    vector<int>* b; //竟然用指针吗,不得不用二级指针
};

struct all_num {
    num a;
    num b;
    num c;
};

void stick_printf(stick* sticks);
void move(int n, vector<int> &a, vector<int> &b, vector<int> &c);
void stick_int();
void move_one(vector<int>& a, vector<int>& c);
int first_number(vector<int>& a);
int first_number(vector<int>& a, int b);
void while_move();

vector<num> read_num();
num ReadOneNum(vector<int>& a);
vector<num> list();
bool ifMove(num const& a);

int main() {
    stick_int();

    move(layer, sticks.a, sticks.b, sticks.c);

    return 0;
}


void stick_printf(stick* sticks) {
    for (int i = layer; i >= 1; --i) {
        std::cout << sticks->a[i-1] << " " << sticks->b[i-1] << " " << sticks->c[i-1] << std::endl;

    }
    std::cout << "- - -" << std::endl;

}

int first_number(vector<int>& a) {
    auto q = end(a) - 1;
    for (; q != begin(a) && *q == 0; --q) {}//找到柱子的第一个数或起始数（未知是0或数）
    if (q == begin(a) && *q == 0) {
        return -1;//没找到数
    }
    else {
        return *q;
    }
}

int first_number(vector<int>& a,int b){
    auto q = end(a) - 1;
    for (; q != begin(a) && *q == 0; --q) {}//找到柱子的第一个数或起始数（未知是0或数）
    if (q == begin(a) && *q == 0) {
        return -1;//没找到数
    }
    else {
        int num = *q;
        *q = b;
        return num;
    }
}

void move_one(vector<int>& a, vector<int>& c) {

    int tag = first_number(a,0);

    auto p = end(c) - 1;
    for (; p != begin(c) && *p == 0; --p) {}
    if (p == begin(c) && *p == 0) {
        *p = tag;
    }
    else {
        ++p;
        *p = tag;
    }
    stick_printf(&sticks);

}

void move(int n, vector<int> &a, vector<int> &b, vector<int> &c) {
    if (n == 1) {
        //
        move_one(a, c);
        return;
    }

    move(n - 1, a, c, b);
    move_one(a, c);
    move(n - 1, b, a, c);
}

void stick_int() {
    for (int i = 1; i <= layer; ++i) {
        sticks.a[layer-i] = i;
    }
    stick_printf(&sticks);
}



num ReadOneNum(vector<int>&a) {
    num x;
    x.a = first_number(sticks.a);
    x.b = &sticks.a;
    return x;
}


vector<num> read_num() {
    vector<num> a{ ReadOneNum(sticks.a),ReadOneNum(sticks.b),ReadOneNum(sticks.c) };

    return a;
}

vector<num> list() {

    vector<num> list = read_num();

    for (auto i = begin(list); i != end(list); ++i) {
        if (i->a < (i + 1)->a) {
            num n = *i;
            *i = *(i + 1);
            *(i + 1) = n;

        }
    }
    std::cout << list[0].a << " " << list[1].a << " " << list[2].a << std::endl;
    return list;
}

//对比函数
int beat(num const&a,num const&b,num const&c){

    if(b.a!=0 && a.a >= b.a){
        if (c.a!=0 && a.a >= c.a)
        {
           return 0;
        }
        else{
            move_one(*(a.b),*(c.b));
        }
        
    }
    move_one(*(a.b),*(b.b));

}
//判断是否能动

// bool ifMove(num const& a) {
//     int first_a = first_number(sticks.a);
//     int first_b = first_number(sticks.b);
//     int first_c = first_number(sticks.c);
    
//     if (*(a.b) == sticks.a) {
//             if(a.a >= first_b){
                
//             }
            
//         }
//     else if (*(a.b) == sticks.b) {

//         }
//     else {

//     }

//     return 0;
// }
//从左往右放
void putdown(num& i, int tag) {
    //判断上一次是否已动过
    
    if (i.a!=tag) {
        if (*(i.b) == sticks.a) {

        }
        else if (*(i.b) == sticks.b) {

        }
        else {

        }
  
        tag = i.a;
    }


}

//检测到c柱的位子满就退出
bool test() {
    auto i = end(sticks.c) - 1;
    if (*i!=0) {
        return 1;
    }

    return 0;
}

void while_move() {
    //从大到小排列，并找出最大数
    vector<num> list(list());
    int tag = 0;
    //往下遍历找出能动的数
    while(1) {
        auto i = begin(list);
        for (; !ifMove(*i) && i != end(list); ++i) {}
        //从左往右放
        putdown(*i,tag);
        //检测到c柱的位子满就退出
        if(test())
        break;
    }

}


//容纳不同类型的数组
//结构体能否先声明
//遍历除数组外的对象 注释快捷键
// 忌边敲边想，即便有思路
// 函数里不能break
// 无效的强制类型转换，指针转int等
//不要过度封装
//vector函数不能直接用来赋值？
