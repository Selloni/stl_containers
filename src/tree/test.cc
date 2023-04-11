#include"tree.h"
//#include "../vector/s21_vector.h"
//#include<vector>


int main()
{
    using namespace std;
    pair <int, string> one {1, "fff"};
    pair <int, string> two {2, "alol"};
    pair < int, string> six {6, "lolll"};
    pair <int, string> ten {10, "alol"};
    pair <int, string> four {4, "llll"};
    pair <int, string> five{5, "kklklk"};
    pair <int, string> seven{7, "kklklk"};
    pair <int, string> eleven{11, "kklklk"};
    pair <int, string> ll{13, "kklklk"};
    pair <int, string> gg{12, "kklklk"};
    pair <int, string> three {3, "alol"};
    pair <int, string> eight {8, "alol"};
    pair <int, string> nine {9, "alol"};
    pair <int, string> zero {0, "alol"};
    pair <int, string> m_one {-1, "alol"};
    pair <int, string> ftof {4, "alol"};


    node<int, string> *slot = nullptr;
//    node<int, string> *slot = new node<int, string>({3, "fdfd"}, nullptr, nullptr, nullptr);
//    tree<int, string> hh();
//    push(&slot,two);

    push(slot, six);
////    print_tree(slot);
//    push(slot, five);
////    print_tree(slot);
//    push(slot, two);
////    print_tree(slot);
//    push(slot, nine);
////    print_tree(slot);
//////    print_tree(slot);
//    push(slot, seven);
//////    print_tree(slot);
//    push(slot, one);
////    print_tree(slot);
//    push(slot, three);
////    push(slot, four);
//    push(slot, ten);
////    print_tree(slot);
//    push(slot, ll);
////    print_tree(slot);
//    push(slot, gg);
////    print_tree(slot);
//    push(slot, gg);
////    print_tree(slot);
//    push(slot, gg);
////    print_tree(slot);
//    push(slot, gg);
////    print_tree(slot);
//    push(slot, eleven);
////    print_tree(slot);
//    push(slot, five);
////    print_tree(slot);
//    push(slot, eight);
////    print_tree(slot);
//    push(slot, six);
////    print_tree(slot);
//
//    push(slot, ten);
////    print_tree(slot);
//    push(slot, zero);
////    push(slot, m_one);
//    push(slot, four);

//   print_key(slot);
   std::cout << "height: " << height(slot) << endl;
//    turn_right(slot);
//    turn_left(slot);
//    height(slot);
//   set_balance(slot);
//    print_tree(slot);
////    std::pair<int, string>  tmp = get_max(slot);
////    std::cout << tmp.first;
//    remove(slot,  ten);
//    print_tree(slot);
//    remove(slot,  gg);
//    print_tree(slot);
//    remove(slot,  ll);

    print_tree(slot);

//
//    print_key(slot);
    return 0;
}