#include <iostream>
#include <cstring>

class RLECoder
{
public:
    static void ncode(char * input, char * output){
        int inpPosition = 0;
        int outPosition = 0;
        int len = strlen(input);
        while(inpPosition < len){
            char current = input[inpPosition];
            int cnt = 1;

            while(inpPosition + cnt < len && input[inpPosition + cnt] == current){
                cnt++;
            }
            output[outPosition++] = '0' + cnt;
            output[outPosition++] = current;
            inpPosition++;
        
        }
    }
    static void dcode(char * input, char * output){

    }
};