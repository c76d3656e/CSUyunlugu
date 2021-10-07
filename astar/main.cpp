#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
struct Node{
    int x,y;
    int f,g,h;
    Node *father;
    Node(int inx,int iny):x(inx),y(iny),f(0),g(0),h(0),father(nullptr){};
    Node(int inx,int iny,Node* father):x(inx),y(iny),f(0),g(0),h(0),father(father){};
};
//待检查节点列表
vector<Node*> OpenList;
//不可行节点列表
vector<Node*> CloseList;
//起始点与终点，在main函数内初始化
Node *startPos;
Node *endPos;

int map[12][12]={
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0},
        {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0},
        {0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0},
        {0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0},
        {0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0},
        {0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0},
        {0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0},
        {0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0},
        {0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};//0为墙壁1为路
void printfPath(Node *current){
    //使用递归回溯到起点进行输出
    if(current->father!= nullptr)
        printfPath(current->father);
    //改变地图中的路径数字
    map[current->x][current->y]=4;
    printf("(%d,%d) ",current->x,current->y);
}
void printfMap(){
    for(int i=0;i<=11;i++){
        for(int j=0;j<=11;j++){
            printf("%d ",map[i][j]);
        }
        printf("\n");
    }
}
bool unWalk(const int x,const int y){
    if(map[x][y]==0)
        return true;
    return false;
}//判断能否经过
int isContains(vector<Node*>* nodeList,const int x,const int y){
    for(int i=0;i<nodeList->size();i++){
        if(nodeList->at(i)->x==x&&nodeList->at(i)->y==y){
            return i;
        }
    }//返回int用以判断第几个点
    return -1;
}//判断是否在List中

void countGHF(Node *sNode,Node *eNode,const int g){
    int h= abs(sNode->x - eNode->x)*10+abs(sNode->y-eNode->y);
    int currentG=sNode->father->g+g;
    int F=currentG+h;
    sNode->f=F;//估计值
    sNode->h=h;//估计路程代价
    sNode->g=currentG;//实际代价
}

void checkPoint(const int x,const int y,Node* father,const int g){
    //判断是否越界
    if(x<=0||x>=11||y<=0||y>=11){
        return;
    }
    //以下两项判断是否经过不可行地点
    if(unWalk(x,y)){
        return;
    }
    if(isContains(&CloseList,x,y)!=-1){
        return;
    }
    //判断是否在开放表中
    int index= isContains(&OpenList,x,y);
    //在开放表中则将其与当前节点比较
    if(index!=-1) {
        Node *point = OpenList[index];
        if (point->g > father->g + g) {
            point->father = father;
            point->g = father->g + g;
            point->f = point->g + point->h;
        }
    }else{
        Node *point =new Node(x,y,father);
        //计算新节点的G,H,F值
        countGHF(point,endPos,g);
        //将该新建节点放入可行节点中
        OpenList.push_back(point);
    }//如果是新节点则将其计算后重新放入开放表中
}


void NextStep(Node *current){
    //左
    checkPoint(current->x-1,current->y,current,10);
    //右
    checkPoint(current->x+1,current->y,current,10);
    //上
    checkPoint(current->x,current->y-1,current,10);
    //下
    checkPoint(current->x,current->y+1,current,10);
}

void searchPath(Node *startPos, Node *endPos){
    Node *current;
    OpenList.push_back(startPos);
    while ((!OpenList.empty())){
        current=OpenList[0];
        if(current->x==endPos->x&&current->y==endPos->y){
            printf("Find the path\n");
//            //打印迷宫
//            printfMap();
            //打印路径坐标点
            printfPath(current);
            OpenList.clear();
            CloseList.clear();
            break;
        }
        //下一步搜索
        NextStep(current);
        //将现节点放进Close不在考虑
        CloseList.push_back(current);
        //移出开放表
        OpenList.erase(OpenList.begin());
        //排序获得最低F值的节点
        sort(OpenList.begin(),OpenList.end(),[](Node *a,Node *b){return a->f<b->f;});
    }
}
bool inputIsFalse(const int x,const int y){
    if(x<=0||x>=11||y<=0||y>=11|| unWalk(x,y)){
        printf("Wrong Input\n");
        system("pause");
        system("cls");
        return true;
    }
    return false;
}
int main() {
    int startx,starty,endx,endy;
    while (true){
        printfMap();
        printf("vertical is x,crosswise is y\n");
        printf("Input example:\n1 1\n2 1\n");
        printf("Input Start Point\n");
        scanf_s("%d%d",&startx,&starty);
        if(inputIsFalse(startx,starty))
            continue;
        printf("\n");
        printf("Input End Point\n");
        scanf_s("%d%d",&endx,&endy);
        if(inputIsFalse(endx,endy))
            continue;
        break;
    }//用于判断非法输入
    //创建节点
    startPos=new Node(startx,starty);
    endPos= new Node(endx,endy);
    //进行搜索
    searchPath(startPos,endPos);
    printf("\n");
    printfMap();
    system("pause");
    return 0;
}
