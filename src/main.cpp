#include <QCoreApplication>
#include <QDebug>
#include <cmath>
#include <fstream>

#include "study.h"
#include "refconnector.h"
#include "objects.h"
#include "algorithms.h"

//int main(int argc, char *argv[])
//{
//    std::string a{"12kujk4"};
////    std::cout << a << std::endl;
//    Entities ents;
//    double qq[3][3];
//    std::cout << qq << std::endl;
////    ents.add("aaaaa", std::unordered_map<std::string, int>{{std::string{"qwer"}, 1}}, 11);
//    ents.add(a, std::unordered_map<std::string, int>{{std::string{"qwer"}, 1}}, 11);
//    ents.add("bbbbb", std::unordered_map<std::string, int>{{std::string{"qwer"}, 2}}, 12);
//    ents.add("ccccc", std::unordered_map<std::string, int>{{std::string{"qwer"}, 3}}, 13);
//    ents.add("ddddd", std::unordered_map<std::string, int>{{std::string{"qwer"}, 4}}, 14);
//    ents.add("eeeee", std::unordered_map<std::string, int>{{std::string{"qwer"}, 5}}, 15);

//    for (const auto& p: ents.the_map){
//        std::cout << p.second.str  << " " << p.second.map.at("qwer")
//                  << p.second.number
//                  << std::endl;
//        auto& a = p.second;
//        auto& t = p.second.str;
//        for(const auto& i: p.second.map)
//            std::cout << i.first << i.second << std::endl;
//    }

//}

int main()
{
//    int x = 0, y = 0;
//    int* matrix;
//    std::fstream myfile("input.txt");
//    if (myfile.is_open()) {
//        myfile >> y >> x;
//        int size = x * y;
//        matrix = new int[size];

//        for (int i = 0; i < size; ++i) {
//            myfile >> matrix[i];
//        }

//        myfile.close();
//    }

    Node node3("node3", nullptr, nullptr);
    Node node2("node2", nullptr, nullptr);
    Node node1("node1", nullptr, nullptr);
    Node node0("node0", nullptr, nullptr);
    node0.next = &node1;

    node1.next = &node2;
    node1.prev = &node0;

    node2.next = &node3;
    node2.prev = &node1;

    node3.prev = &node2;


    Algorithms::printLinkedList(Algorithms::inverseOrder(&node0));
    /*
    Output is:
    node0
    node1
    node2
    node3
    */


//    auto res = Algorithms::transpose(x, y, matrix);
//    for (int i = 0; i < x; ++i) {
//        for (int j = 0; j < y; ++j) {
//            std::cout << res[i*y + j] << " ";
//        }
//        std::cout << std::endl;
//    }
//    std::cout << res;
    return 0;
}
