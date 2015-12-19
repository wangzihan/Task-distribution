#include "iostream"
#include "fstream"
#include "string"

class log
{

private:
    char * lfile;
    std::ofstream ofile;

public:
    log():lfile("./server.log")
    {
        ofile.open(lfile);
    }
    
    ~log()
    {
        ofile.close();
    }

    void common(char * c, std::string s)
    {
        ofile<<c<<s<<std::endl;
    }
};
