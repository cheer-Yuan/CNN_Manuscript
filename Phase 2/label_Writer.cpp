//
// Created by cheerfulliu on 15/01/2020.
//

#include <iostream>
#include <fstream>
using namespace std;

int main(void){

    fstream file("label_0.txt", ofstream::app | ios::binary | ofstream::out);
    if (!file){
        cerr << "open fir.txt failure" << endl;
        return 0;
    }

    unsigned char label_1 = 0;
    for (int i = 0; i < 100; ++i) file.write((char*)&label_1 , sizeof(label_1));

    file.close();
    file.clear();

    file.open("label_0.txt", ifstream::in | ios::binary);
    if (!file){
        cerr << "open fir.txt for read failure!" << endl;
        return 0;
    }

    //read the binary number 1 y 1 and output
    unsigned char num = 0;
    for (int i = 0; i < 100; ++i)
    {
        file.read((char *)&num, sizeof(num));
        cout << (int)num << "\t";
    }


    cout << endl;
    file.close();
    file.clear();



    return 0;
}
