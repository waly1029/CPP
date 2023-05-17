#ifndef CDOCUMENT_H
#define CDOCUMENT_H

#include <iostream>

using namespace std;

class CDocuments {
public:
    void OnFileOpen() {
        // 这是一个算法，每个cout输出代表一个实际动作
        cout << "dialog..." << endl;
        cout << "check file status..." << endl;
        cout << "open file..." << endl;
        Serialize();
        cout << "close file..." << endl;
        cout << "update all views..." << endl;
    }

    virtual void Serialize() { }
};

//============================================================================
class CMyDoc: public CDocuments {
public:
    virtual void Serialize() override { 
        // 实际应用开发时的具体实现
        cout << "CMyDoc::Serialize()" << endl;
    }
};

#endif // _CDOCUMENT_H