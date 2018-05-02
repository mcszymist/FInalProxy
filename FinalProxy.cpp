#include <string>
using std::string;
#include <mutex>
#include <iostream>
using std::cout;
using std::endl;

//cout should be fileio but didnt have time to change it to that.

class FileAccessBase {
public:
    virtual void Write() = 0;
};

class FileAccess : public FileAccessBase {
    void Write() override {
        cout << "Hello" << endl;
    }
};

class FileAccessProxy : public FileAccessBase {
private:
    FileAccessBase* fileAccesser; 
    const string infoForFile;
    std::mutex cout_mutex;
public:
    FileAccessProxy(const string &info) : fileAccesser(new FileAccess()), infoForFile(info) {}
    ~FileAccessProxy () {
        delete fileAccesser;
    }

    void Write() override{
        std::lock_guard<std::mutex> guard(cout_mutex);
        cout << infoForFile << endl;
    }
    
};

// How to use above Proxy class?
int main()
{
    FileAccessBase* file = new FileAccessProxy("Hello World!");
    file->Write();
    delete file;

}
