//
// Created by cheerfulliu on 15/01/2020.
//

#include <iostream>
#include <fstream>
using namespace std;

int main(void){

    fstream file("label.txt", ofstream::app | ios::binary | ofstream::out);
    if (!file){
        cerr << "open fir.txt failure" << endl;
        return 0;
    }

    unsigned char label_1 = 0;
    file.write((char*)&label_1 , sizeof(label_1));
    label_1 = 1;
    file.write((char*)&label_1 , sizeof(label_1));

    file.close();
    file.clear();

    file.open("label.txt", ifstream::in | ios::binary);
    if (!file){
        cerr << "open fir.txt for read failure!" << endl;
        return 0;
    }

    unsigned char tt;
    //依次读取二进制文件中的unsigned char值读入到变量i,并输出
    file.read((char *)&tt, sizeof(tt));
    cout << (int)tt << "\t";
    file.read((char *)&tt, sizeof(tt));
    cout << (int)tt << "\t";

    cout << endl;
    file.close();
    file.clear();



    return 0;
}
