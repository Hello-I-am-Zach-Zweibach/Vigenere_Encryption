#ifndef __VIGENERE_H
#define __VIGENERE_H

#include "encryption.h"

using namespace std;

//My increment function
//flip is explained in vig.cpp
void increment(char& c, char ch, int flip = 0);

//nothing exciting here
class VigenereEncrypt : public EncryptedFileWriter
{
    protected:
        string code;
        int codeIndex;
        int maxCodeIndex;
    public:
        //Constructor
        VigenereEncrypt( const string& filename, const string& code);
        //Encrypt
        string encrypt(const string& str) override;
};

class VigenereDecrypt : public EncryptedFileReader
{
    protected:
        string code;
        int codeIndex;
        int maxCodeIndex;
    public:
        //constructor
        VigenereDecrypt( const string& filename, const string& code);
        //Decrypt
        string decrypt(const string& str) override;
};

#endif