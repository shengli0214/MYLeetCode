/*
 * @Author: shengli0214 shengli_liu14@126.com
 * @Date: 2025-02-17 22:49:14
 * @LastEditors: shengli0214 shengli_liu14@126.com
 * @LastEditTime: 2025-12-15 15:01:08
 * @FilePath: \MytessCode\UnionFind.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
/*** 
 * @Author: shengli.liu
 * @Date: 2024-10-01 16:21:57
 * @Description: 
 * @
 * @LastEditors: shengli.liu shengli.liu@hongjingdrive.com
 * @LastEditTime: 2024-10-01 16:22:10
 */



#ifndef UNIONFIND_H
#define UNIONFIND_H
namespace unionfind{
class UnionFind{
private:
    int *id;    //父链接数组,由触点索引
    int *sz;    //由触点索引的各个根节点所对应的分量的大小
    int count;  //连通分量的数量
public:
    UnionFind(int N);
    ~UnionFind();
    int Find(int p);                //找p所在连通分量的根
    bool Connected(int p, int q);   //p和q是否在同一个连通分量里
    int GetCount();                 //返回连通分量
    void Union(int p, int q);       //将p和q连接起来
};

}


#endif // UNIONFIND_H