#include "vigenere.h"

using namespace std;

void increment(char& c, char ch, int flip)
{  
    //Since the alphabet is between 97 and 122 in ASCII, we need to reduce ch to 0 through 25. 
    ch -= 97;
    //If a nonzero value for flip is entered (such as 1), we decrement instead of incrementing.
    if(flip != 0)
    {
        ch = 26 - ch;
    }
    //Since the alphabet is between 97 and 122, we need to reduce it to 0 through 25
    c -= 97;

    //Then, we increment it by i letters
    c += ch;
    //We reduce it again to between 0 and 25
    c = c % 26;
    //Finally, we reincrement it by 97 again
    c += 97;
}

VigenereEncrypt::VigenereEncrypt( const string& filename, const string& code)
    :   EncryptedFileWriter(filename)
{
    this->code = code;
    codeIndex = 0;
    maxCodeIndex = code.size() - 1;
}

string VigenereEncrypt::encrypt(const string& str)
{
    int maxCodeIndex = code.size() - 1;
    string result;

    //not technically needed but it helps readability
    char c = 'a';

    //will go through the input string
    for(int i = 0; i < str.size(); i++)
    {  
        //checks to make sure the current char is in the alphabet
        if(isalpha(str.at(i)))
        {
            //my increment function depends on the char being lower case.
            c = tolower(str.at(i));

            //increments c
            increment(c, tolower(code.at(codeIndex)));

            //adds c to the string that will be returned.
            result.push_back(c);

            //increments the codeindex
            if(maxCodeIndex > 0)
            {
                codeIndex++;
                if(codeIndex > maxCodeIndex)
                    codeIndex = 0;                        
            }
        }
        //I don't think this is needed but I'm scared to remove it
        else if(str.at(i) == '\n')
        {
            result.push_back('\n');
        }
        else
        {
            result.push_back(str.at(i));
        }
    }
    result = EncryptedFileWriter::encrypt(result);
    return result;
}

VigenereDecrypt::VigenereDecrypt( const string& filename, const string& code)
    :   EncryptedFileReader(filename)
{
    this->code = code;
    codeIndex = 0;
    maxCodeIndex = code.size() - 1;
}

string VigenereDecrypt::decrypt(const string& str)
{
    int maxCodeIndex = code.size() - 1;
    string result;

    //not technically needed but it helps readability
    char c = 'a';

    //will go through the input string
    for(int i = 0; i < str.size(); i++)
    {  
        //checks to make sure the current char is in the alphabet
        if(isalpha(str.at(i)))
        {
            //my increment function depends on the char being lower case.
            c = tolower(str.at(i));

            //Decrements c, since there's a third value passed
            increment(c, tolower(code.at(codeIndex)), 1);

            //adds c to the string that will be returned.
            result.push_back(c);

            //increments the codeindex
            //If it's just one character don't bother
            if(maxCodeIndex > 0)
            {
                codeIndex++;
                //Don't go too far though
                if(codeIndex > maxCodeIndex)
                    codeIndex = 0;                        
            }
        }
        else if(str.at(i) == '\n')
        {
            result.push_back('\n');
        }
        else
        {
            result.push_back(str.at(i));
        }
    }
    result = EncryptedFileReader::decrypt(result);
    return result;
}