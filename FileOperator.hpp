#ifndef FileOperatorr
#define FileOperatorr
#include <cstdio>
#include <iostream>
#include <fstream>

class Fileoperator {
    public:
    void NewFile(char *FileName) {
        std::ofstream who(FileName);
        who.close();
    }

    template <typename T>
    void get(std::fstream &curFile, int pos, int num, T *where) const {
		curFile.seekg(pos);
		curFile.read( reinterpret_cast<char*>(where), int(num * sizeof(T)) );
    }

    int getend(std::fstream &curFile) const {
		curFile.seekg(0, std::ios::end);
		curFile.clear();
		return (int)curFile.tellg();
    }

    template <typename T>
    void write(std::fstream &curFile, int pos, int num, T *where) const {
        if(pos == -1) pos = getend( curFile );
        curFile.seekg( pos );
        curFile.write( reinterpret_cast<char*>(where),  int(num * sizeof(T)) );
    }
}FileOperator;
#endif
