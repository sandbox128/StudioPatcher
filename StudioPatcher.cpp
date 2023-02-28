#include <fstream>
#include <sstream>

using std::string;
using std::ifstream;
using std::ofstream;
using std::stringstream;
using std::ios;

string fromHex(const string& hex) {
    string ret;
    for (int i = 0; i < hex.length(); i += 2)
    {
        string byte = hex.substr(i, 2);
        char chr = (char)(int)strtol(byte.c_str(), NULL, 16);
        ret.push_back(chr);
    }
    return ret;
}

int main(int argc, char* argv[])
{
    if (argc < 2) return 0;

    ifstream infile(argv[1], ios::binary);
    if (!infile.good()) return 0;

    stringstream buffer;
    buffer << infile.rdbuf();
    infile.close();

    string str = buffer.str();
    string searchFor = fromHex("83CB04895E64");
    string replaceWith = fromHex("83CB05895E64");

    str.replace(str.find(searchFor), searchFor.length(), replaceWith);
    
    ofstream outfile(argv[1], ios::trunc | ios::binary);
    outfile.write(str.c_str(), str.size());
    outfile.close();

    return 1;
}