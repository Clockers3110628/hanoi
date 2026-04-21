#include <iostream>
#include <vector>

using std::vector;

int layer = 10;

struct num {
    int a;
    vector<int>* b; //竟然用指针吗,不得不用二级指针
};

struct all_num {
    num a;
    num b;
    num c;
};

struct api {
    void move_one(vector<int>& a, vector<int>& c);
    int first_number(vector<int>& a);
    int first_number(vector<int>& a, int b);
    vector<num> read_num();
    num ReadOneNum(vector<int>& a);
    bool beat_and_put(num& a, int* i);
    bool test();
};
struct stick {
    vector<int> a = vector<int>(layer);
    vector<int> b = vector<int>(layer);
    vector<int> c = vector<int>(layer);

    void stick_printf(stick* sticks);
    void move(int n, vector<int>& a, vector<int>& b, vector<int>& c);
    void stick_int();
    void while_move();

    struct api api;
}sticks;

int main() {
    int b;
    do {
        char a;

        std::cout << "选1迭代，选2循环" << std::endl;
        std::cin >> a;
        std::cout << "选择层数（10以下）" << std::endl;
        std::cin >> layer;
        sticks.stick_int();
        if (a)
        {
            sticks.move(layer, sticks.a, sticks.b, sticks.c);
        }
        else {
            sticks.while_move();
        }

        std::cout << "选1继续，选0退出" << std::endl;
        std::cin >> b;
    } while (b);

    return 0;
}


void stick::stick_printf(stick* sticks) {
    for (int i = layer; i >= 1; --i) {
        std::cout << sticks->a[i - 1] << " " << sticks->b[i - 1] << " " << sticks->c[i - 1] << std::endl;

    }
    std::cout << "- - -" << std::endl;

}

int api::first_number(vector<int>& a) {
    auto q = end(a) - 1;
    for (; q != begin(a) && *q == 0; --q) {}//找到柱子的第一个数或起始数（未知是0或数）
    if (q == begin(a) && *q == 0) {
        return 0;//没找到数
    }
    else {
        return *q;
    }
}

int api::first_number(vector<int>& a, int b) {
    auto q = end(a) - 1;
    for (; q != begin(a) && *q == 0; --q) {}//找到柱子的第一个数或起始数（未知是0或数）
    if (q == begin(a) && *q == 0) {
        return 0;//没找到数
    }
    else {
        int num = *q;
        *q = b;
        return num;
    }
}

void api::move_one(vector<int>& a, vector<int>& c) {

    int tag = first_number(a, 0);

    auto p = end(c) - 1;
    for (; p != begin(c) && *p == 0; --p) {}
    if (p == begin(c) && *p == 0) {
        *p = tag;
    }
    else {
        ++p;
        *p = tag;
    }

    sticks.stick_printf(&sticks);

}

void stick::move(int n, vector<int>& a, vector<int>& b, vector<int>& c) {
    if (n == 1) {
        //
        sticks.api.move_one(a, c);
        return;
    }

    move(n - 1, a, c, b);
    sticks.api.move_one(a, c);
    move(n - 1, b, a, c);
}

void stick::stick_int() {
    //先全清零
    for (int i = 1; i <= 10; ++i) {
        sticks.c[10 - i] = 0;
    }
    for (int i = 1; i <= layer; ++i) {
        sticks.a[layer - i] = i;
    }
    sticks.stick_printf(&sticks);
}

num api::ReadOneNum(vector<int>& a) {
    num x;
    x.a = first_number(a);
    x.b = &a;
    return x;
}


vector<num> api::read_num() {
    vector<num> a{ ReadOneNum(sticks.a),ReadOneNum(sticks.b),ReadOneNum(sticks.c) };

    return a;
}

// vector<num> list() {

//     vector<num> list = read_num();

//     for (auto i = begin(list); i != end(list); ++i) {
//         if (i->a < (i + 1)->a) {
//             num n = *i;
//             *i = *(i + 1);
//             *(i + 1) = n;

//         }
//     }
//     std::cout << list[0].a << " " << list[1].a << " " << list[2].a << std::endl;
//     return list;
// }


//对比函数
bool api::beat_and_put(num& a, int* i) {
    num b;
    num c;

    if (*(a.b) == sticks.a) {
        b = { first_number(sticks.b),&sticks.b };
        c = { first_number(sticks.c),&sticks.c };
    }
    else if (*(a.b) == sticks.b)
    {
        b = { first_number(sticks.c),&sticks.c };
        c = { first_number(sticks.a),&sticks.a };
    }
    else {
        b = { first_number(sticks.a),&sticks.a };
        c = { first_number(sticks.b),&sticks.b };
    }

    if (a.a == *i || (b.a != 0 && a.a > b.a)) {
        if (a.a == *i || (c.a != 0 && a.a > c.a))
        {
            return 1;
        }
        else {
            *i = a.a;
            move_one(*(a.b), *(c.b));
            return 0;
        }

    }
    *i = a.a;
    move_one(*(a.b), *(b.b));
    return 0;

}

//检测到c柱的位子满就退出
bool api::test() {
    auto i = end(sticks.c) - 1;
    if (*i != 0) {
        return 1;
    }

    return 0;
}

void stick::while_move() {
    int tag = 0;
    while (1)
    {
        vector<num> list = sticks.api.read_num();
        for (auto I = begin(list); I != end(list)-1; ++I)
        {
            for (auto i = begin(list); i != end(list)-1; ++i) {
                if (i->a < (i + 1)->a) {
                    num n = *i;
                    *i = *(i + 1);
                    *(i + 1) = n;

                }
            }
        }

        std::cout << list[0].a << " " << list[1].a << " " << list[2].a << std::endl;
        std::cout << "- - -" << std::endl;
        
        if (sticks.api.beat_and_put(list[0], &tag)) {
            if (sticks.api.beat_and_put(list[1],&tag)) {
                if (sticks.api.beat_and_put(list[2],&tag));
            }
                             
        }
           
        //检测到c柱的位子满就退出
        if (sticks.api.test())
            return;
    }

}

// 忌边敲边想，即便有思路
// 函数里不能break
// 无效的强制类型转换，指针转int等
//不要过度封装
//vector函数不能直接用来赋值？
