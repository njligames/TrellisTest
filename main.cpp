#include "PolicyParser.h"
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

static bool readPolicyFile(const string &policyFile, vector<Policy> &policies) {
    FILE *file = fopen(policyFile.c_str(), "rb");
    size_t size;
    void *buffer;

    if(file) {
        fseek(file, 0, SEEK_END);
        size = ftell(file);
        fseek(file, 0, SEEK_SET);
        buffer = malloc(size + 1);
        fread(buffer, 1, size, file);
        char *t = (char*)buffer;
        t[size] = 0;

        PolicyParser::get()->parse(string(t), policies);

        free(buffer);
        fclose(file);

        return true;
    }
    return false;

}

int main(int nArg, char *cArg[]) {
    string policyFile = string(TEST_ASSET_PATH);
    vector<Policy> policies;

    if(readPolicyFile(policyFile, policies)) {
        PolicyParser::get()->printRuleErrors(policies, Colonel);
    }
    PolicyParser::destroy();
    
    return 0;
}

