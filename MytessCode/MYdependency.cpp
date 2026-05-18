/*** 
 * @Author: shengli.liu
 * @Date: 2024-07-08 15:44:17
 * @Description: 
 * @
 * @LastEditors: shengli.liu shengli.liu@hongjingdrive.com
 * @LastEditTime: 2024-07-08 17:42:20
 */


#include "MyDependency.h"
void Assert(bool val, std::string s) {
    if (!val){ // Assertion failed -- close the program
        std::cout << "Assertion Failed: " << s << std::endl;
        exit(-1);
    }
}