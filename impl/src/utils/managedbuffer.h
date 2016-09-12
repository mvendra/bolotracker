
#ifndef __MANAGEDBUFFER_H__
#define __MANAGEDBUFFER_H__

class ManagedBuffer final {

public:

    ManagedBuffer(unsigned const int len):buffer{new char[len]}, length{len}{}
    ~ManagedBuffer(){ delete [] buffer; }

    ManagedBuffer(const ManagedBuffer&) = delete;
    ManagedBuffer(ManagedBuffer&&) = delete;
    ManagedBuffer& operator=(const ManagedBuffer&) = delete;
    ManagedBuffer& operator=(ManagedBuffer&&) = delete;

    char *buffer;
    unsigned int length;

private:

};

#endif // __MANAGEDBUFFER_H__

