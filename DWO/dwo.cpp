#include <map>
#include <cstdio>
#include <algorithm>
using namespace std;

typedef unsigned long long llu;

#define MAGIC_X 36
#define MAGIC_Y 64

llu size[MAGIC_X] = {1LLU,2LLU,4LLU,8LLU,16LLU,32LLU,64LLU,128LLU,256LLU,512LLU,1024LLU,2048LLU,4096LLU,8192LLU,16384LLU,32768LLU,65536LLU,131072LLU,262144LLU,524288LLU,1048576LLU,2097152LLU,4194304LLU,8388608LLU,16777216LLU,33554432LLU,67108864LLU,134217728LLU,268435456LLU,536870912LLU,1073741824LLU,2147483648LLU,4294967296LLU,8589934592LLU,17179869184LLU,34359738368LLU};

llu xorki[MAGIC_X] = {0LLU,1LLU,3LLU,1LLU,7LLU,1LLU,3LLU,1LLU,15LLU,1LLU,3LLU,1LLU,7LLU,1LLU,3LLU,1LLU,31LLU,1LLU,3LLU,1LLU,7LLU,1LLU,3LLU,1LLU,15LLU,1LLU,3LLU,1LLU,7LLU,1LLU,3LLU,1LLU,63LLU,1LLU,3LLU,1LLU};

llu magic[MAGIC_X][MAGIC_Y] = {
    {1LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU},
    {1LLU,1LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU},
    {1LLU,2LLU,0LLU,1LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU},
    {1LLU,3LLU,2LLU,2LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU},
    {3LLU,4LLU,4LLU,4LLU,0LLU,0LLU,0LLU,1LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU},
    {3LLU,5LLU,4LLU,4LLU,4LLU,4LLU,4LLU,4LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU},
    {7LLU,8LLU,8LLU,9LLU,8LLU,8LLU,8LLU,8LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU},
    {15LLU,17LLU,16LLU,16LLU,16LLU,16LLU,16LLU,16LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU},
    {31LLU,32LLU,32LLU,32LLU,32LLU,32LLU,32LLU,32LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,1LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU},
    {31LLU,33LLU,32LLU,32LLU,32LLU,32LLU,32LLU,32LLU,32LLU,32LLU,32LLU,32LLU,32LLU,32LLU,32LLU,32LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU},
    {63LLU,64LLU,64LLU,65LLU,64LLU,64LLU,64LLU,64LLU,64LLU,64LLU,64LLU,64LLU,64LLU,64LLU,64LLU,64LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU},
    {127LLU,129LLU,128LLU,128LLU,128LLU,128LLU,128LLU,128LLU,128LLU,128LLU,128LLU,128LLU,128LLU,128LLU,128LLU,128LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU},
    {255LLU,256LLU,256LLU,256LLU,256LLU,256LLU,256LLU,257LLU,256LLU,256LLU,256LLU,256LLU,256LLU,256LLU,256LLU,256LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU},
    {511LLU,513LLU,512LLU,512LLU,512LLU,512LLU,512LLU,512LLU,512LLU,512LLU,512LLU,512LLU,512LLU,512LLU,512LLU,512LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU},
    {1023LLU,1024LLU,1024LLU,1025LLU,1024LLU,1024LLU,1024LLU,1024LLU,1024LLU,1024LLU,1024LLU,1024LLU,1024LLU,1024LLU,1024LLU,1024LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU},
    {2047LLU,2049LLU,2048LLU,2048LLU,2048LLU,2048LLU,2048LLU,2048LLU,2048LLU,2048LLU,2048LLU,2048LLU,2048LLU,2048LLU,2048LLU,2048LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU},
    {4095LLU,4096LLU,4096LLU,4096LLU,4096LLU,4096LLU,4096LLU,4096LLU,4096LLU,4096LLU,4096LLU,4096LLU,4096LLU,4096LLU,4096LLU,4096LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,1LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU},
    {4095LLU,4097LLU,4096LLU,4096LLU,4096LLU,4096LLU,4096LLU,4096LLU,4096LLU,4096LLU,4096LLU,4096LLU,4096LLU,4096LLU,4096LLU,4096LLU,4096LLU,4096LLU,4096LLU,4096LLU,4096LLU,4096LLU,4096LLU,4096LLU,4096LLU,4096LLU,4096LLU,4096LLU,4096LLU,4096LLU,4096LLU,4096LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU},
    {8191LLU,8192LLU,8192LLU,8193LLU,8192LLU,8192LLU,8192LLU,8192LLU,8192LLU,8192LLU,8192LLU,8192LLU,8192LLU,8192LLU,8192LLU,8192LLU,8192LLU,8192LLU,8192LLU,8192LLU,8192LLU,8192LLU,8192LLU,8192LLU,8192LLU,8192LLU,8192LLU,8192LLU,8192LLU,8192LLU,8192LLU,8192LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU},
    {16383LLU,16385LLU,16384LLU,16384LLU,16384LLU,16384LLU,16384LLU,16384LLU,16384LLU,16384LLU,16384LLU,16384LLU,16384LLU,16384LLU,16384LLU,16384LLU,16384LLU,16384LLU,16384LLU,16384LLU,16384LLU,16384LLU,16384LLU,16384LLU,16384LLU,16384LLU,16384LLU,16384LLU,16384LLU,16384LLU,16384LLU,16384LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU},
    {32767LLU,32768LLU,32768LLU,32768LLU,32768LLU,32768LLU,32768LLU,32769LLU,32768LLU,32768LLU,32768LLU,32768LLU,32768LLU,32768LLU,32768LLU,32768LLU,32768LLU,32768LLU,32768LLU,32768LLU,32768LLU,32768LLU,32768LLU,32768LLU,32768LLU,32768LLU,32768LLU,32768LLU,32768LLU,32768LLU,32768LLU,32768LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU},
    {65535LLU,65537LLU,65536LLU,65536LLU,65536LLU,65536LLU,65536LLU,65536LLU,65536LLU,65536LLU,65536LLU,65536LLU,65536LLU,65536LLU,65536LLU,65536LLU,65536LLU,65536LLU,65536LLU,65536LLU,65536LLU,65536LLU,65536LLU,65536LLU,65536LLU,65536LLU,65536LLU,65536LLU,65536LLU,65536LLU,65536LLU,65536LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU},
    {131071LLU,131072LLU,131072LLU,131073LLU,131072LLU,131072LLU,131072LLU,131072LLU,131072LLU,131072LLU,131072LLU,131072LLU,131072LLU,131072LLU,131072LLU,131072LLU,131072LLU,131072LLU,131072LLU,131072LLU,131072LLU,131072LLU,131072LLU,131072LLU,131072LLU,131072LLU,131072LLU,131072LLU,131072LLU,131072LLU,131072LLU,131072LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU},
    {262143LLU,262145LLU,262144LLU,262144LLU,262144LLU,262144LLU,262144LLU,262144LLU,262144LLU,262144LLU,262144LLU,262144LLU,262144LLU,262144LLU,262144LLU,262144LLU,262144LLU,262144LLU,262144LLU,262144LLU,262144LLU,262144LLU,262144LLU,262144LLU,262144LLU,262144LLU,262144LLU,262144LLU,262144LLU,262144LLU,262144LLU,262144LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU},
    {524287LLU,524288LLU,524288LLU,524288LLU,524288LLU,524288LLU,524288LLU,524288LLU,524288LLU,524288LLU,524288LLU,524288LLU,524288LLU,524288LLU,524288LLU,524289LLU,524288LLU,524288LLU,524288LLU,524288LLU,524288LLU,524288LLU,524288LLU,524288LLU,524288LLU,524288LLU,524288LLU,524288LLU,524288LLU,524288LLU,524288LLU,524288LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU},
    {1048575LLU,1048577LLU,1048576LLU,1048576LLU,1048576LLU,1048576LLU,1048576LLU,1048576LLU,1048576LLU,1048576LLU,1048576LLU,1048576LLU,1048576LLU,1048576LLU,1048576LLU,1048576LLU,1048576LLU,1048576LLU,1048576LLU,1048576LLU,1048576LLU,1048576LLU,1048576LLU,1048576LLU,1048576LLU,1048576LLU,1048576LLU,1048576LLU,1048576LLU,1048576LLU,1048576LLU,1048576LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU},
    {2097151LLU,2097152LLU,2097152LLU,2097153LLU,2097152LLU,2097152LLU,2097152LLU,2097152LLU,2097152LLU,2097152LLU,2097152LLU,2097152LLU,2097152LLU,2097152LLU,2097152LLU,2097152LLU,2097152LLU,2097152LLU,2097152LLU,2097152LLU,2097152LLU,2097152LLU,2097152LLU,2097152LLU,2097152LLU,2097152LLU,2097152LLU,2097152LLU,2097152LLU,2097152LLU,2097152LLU,2097152LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU},
    {4194303LLU,4194305LLU,4194304LLU,4194304LLU,4194304LLU,4194304LLU,4194304LLU,4194304LLU,4194304LLU,4194304LLU,4194304LLU,4194304LLU,4194304LLU,4194304LLU,4194304LLU,4194304LLU,4194304LLU,4194304LLU,4194304LLU,4194304LLU,4194304LLU,4194304LLU,4194304LLU,4194304LLU,4194304LLU,4194304LLU,4194304LLU,4194304LLU,4194304LLU,4194304LLU,4194304LLU,4194304LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU},
    {8388607LLU,8388608LLU,8388608LLU,8388608LLU,8388608LLU,8388608LLU,8388608LLU,8388609LLU,8388608LLU,8388608LLU,8388608LLU,8388608LLU,8388608LLU,8388608LLU,8388608LLU,8388608LLU,8388608LLU,8388608LLU,8388608LLU,8388608LLU,8388608LLU,8388608LLU,8388608LLU,8388608LLU,8388608LLU,8388608LLU,8388608LLU,8388608LLU,8388608LLU,8388608LLU,8388608LLU,8388608LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU},
    {16777215LLU,16777217LLU,16777216LLU,16777216LLU,16777216LLU,16777216LLU,16777216LLU,16777216LLU,16777216LLU,16777216LLU,16777216LLU,16777216LLU,16777216LLU,16777216LLU,16777216LLU,16777216LLU,16777216LLU,16777216LLU,16777216LLU,16777216LLU,16777216LLU,16777216LLU,16777216LLU,16777216LLU,16777216LLU,16777216LLU,16777216LLU,16777216LLU,16777216LLU,16777216LLU,16777216LLU,16777216LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU},
    {33554431LLU,33554432LLU,33554432LLU,33554433LLU,33554432LLU,33554432LLU,33554432LLU,33554432LLU,33554432LLU,33554432LLU,33554432LLU,33554432LLU,33554432LLU,33554432LLU,33554432LLU,33554432LLU,33554432LLU,33554432LLU,33554432LLU,33554432LLU,33554432LLU,33554432LLU,33554432LLU,33554432LLU,33554432LLU,33554432LLU,33554432LLU,33554432LLU,33554432LLU,33554432LLU,33554432LLU,33554432LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU},
    {67108863LLU,67108865LLU,67108864LLU,67108864LLU,67108864LLU,67108864LLU,67108864LLU,67108864LLU,67108864LLU,67108864LLU,67108864LLU,67108864LLU,67108864LLU,67108864LLU,67108864LLU,67108864LLU,67108864LLU,67108864LLU,67108864LLU,67108864LLU,67108864LLU,67108864LLU,67108864LLU,67108864LLU,67108864LLU,67108864LLU,67108864LLU,67108864LLU,67108864LLU,67108864LLU,67108864LLU,67108864LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU},
    {134217727LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,0LLU,1LLU},
    {134217727LLU,134217729LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU,134217728LLU},
    {268435455LLU,268435456LLU,268435456LLU,268435457LLU,268435456LLU,268435456LLU,268435456LLU,268435456LLU,268435456LLU,268435456LLU,268435456LLU,268435456LLU,268435456LLU,268435456LLU,268435456LLU,268435456LLU,268435456LLU,268435456LLU,268435456LLU,268435456LLU,268435456LLU,268435456LLU,268435456LLU,268435456LLU,268435456LLU,268435456LLU,268435456LLU,268435456LLU,268435456LLU,268435456LLU,268435456LLU,268435456LLU,268435456LLU,268435456LLU,268435456LLU,268435456LLU,268435456LLU,268435456LLU,268435456LLU,268435456LLU,268435456LLU,268435456LLU,268435456LLU,268435456LLU,268435456LLU,268435456LLU,268435456LLU,268435456LLU,268435456LLU,268435456LLU,268435456LLU,268435456LLU,268435456LLU,268435456LLU,268435456LLU,268435456LLU,268435456LLU,268435456LLU,268435456LLU,268435456LLU,268435456LLU,268435456LLU,268435456LLU,268435456LLU},
    {536870911LLU,536870913LLU,536870912LLU,536870912LLU,536870912LLU,536870912LLU,536870912LLU,536870912LLU,536870912LLU,536870912LLU,536870912LLU,536870912LLU,536870912LLU,536870912LLU,536870912LLU,536870912LLU,536870912LLU,536870912LLU,536870912LLU,536870912LLU,536870912LLU,536870912LLU,536870912LLU,536870912LLU,536870912LLU,536870912LLU,536870912LLU,536870912LLU,536870912LLU,536870912LLU,536870912LLU,536870912LLU,536870912LLU,536870912LLU,536870912LLU,536870912LLU,536870912LLU,536870912LLU,536870912LLU,536870912LLU,536870912LLU,536870912LLU,536870912LLU,536870912LLU,536870912LLU,536870912LLU,536870912LLU,536870912LLU,536870912LLU,536870912LLU,536870912LLU,536870912LLU,536870912LLU,536870912LLU,536870912LLU,536870912LLU,536870912LLU,536870912LLU,536870912LLU,536870912LLU,536870912LLU,536870912LLU,536870912LLU,536870912LLU},
};

llu rozw(llu k) {
    int xorek = 0;
    llu res = 0;
    for (int i = MAGIC_X - 1; i >= 0 && k > 0; i--) {
        if (magic[i][xorek] < k || (i == 0)) {
//            printf("Bedziemy dodawac %llu bo xorek = %d oraz pow2 = %d\n", magic[i][xorek], xorek, i);
            k -= magic[i][xorek];
            xorek ^= xorki[i];
            res += size[i];
//            printf("Res %llu xorek %d k %llu\n", res, xorek, k);
        }
    }
    while (k > 0) {
//        printf("Bujam %llu xorek %d\n", res, xorek);
        int md = 0;
        llu nr = res + 1;
        while (nr%2==0) {nr/=2; md++;}
//        printf("NR dla %llu -> %d\n", res + 1, md);
        xorek ^= md;
        if (xorek == 0) k--;
        res++;
    }
    return res;
}

int main() {
    llu k;
    scanf("%llu", &k);
    printf("%llu\n", rozw(k));
//    for (llu i=1;i<k;i++) printf("%llu\n", rozw(i));
    return 0;
}

int mainU() {
    llu n;
    scanf("%llu", &n);
    int xorek = 0;
    llu odp = 0;
    for (llu idx = 1; idx < n; idx++) {
        int zc = 0;
        llu cp = idx;
        while (cp % 2 == 0) { cp/=2; zc++; };
        xorek ^= zc;
        if (xorek == 0) {
            odp++;
            llu o2 = rozw(odp);
            if (o2 != idx) {
                printf("BUBA @ %llu -> %llu vs %llu\n", odp, idx, o2);
                return 0;
            }
        }
    }
    return 0;
}

