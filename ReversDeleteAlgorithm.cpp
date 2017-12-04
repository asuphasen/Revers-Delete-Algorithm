#include <iostream>
#include <map>
#include <vector>
#include <queue>
using namespace std;

struct Edges{
    int u;
    int v;
    int w;
};

class graph{
    public:
        int getSize();
        void showGraph();
        bool haveNodeInGraph(int x);
        void addNode(int n);
        void addEdge(int u,int v,int w);
        int getNumEdeges();
        vector<Edges> getEdge();
        int getNumEOfNode(int n);
        void deleteEdge(int u,int v);
        graph ReverseDelete(graph g);
        bool isConect();
    private:
        vector<int> numOfNode; //ชื่อโนด
        map<int,map<int ,int> > gr; // กราฟ แบบเมทริก
};

//จำนวนโนด
int graph::getSize(){
    return numOfNode.size();
}

//แสดงกราฟ
void graph::showGraph(){
    cout<<"_|";
    for(int i=0;i<numOfNode.size();i++){
        cout<<numOfNode[i]<<" ";
    }
    cout<<endl;
    for(int i=0;i<numOfNode.size();i++){
        cout<<numOfNode[i]<<"|";
        for(int j=0;j<numOfNode.size();j++){
            cout<<gr[numOfNode[i]][numOfNode[j]]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}

//ตรวจสอบว่า มีโนด x อยู่ในกราฟหรือไม่
bool graph::haveNodeInGraph(int x){
    for(int i=0;i<numOfNode.size();i++){
        if(numOfNode[i]==x){
            return true;
        }
    }
    return false;
}

//เพิ่มโนด
void graph::addNode(int n){
    if(!haveNodeInGraph(n)){
        numOfNode.push_back(n);
        cout<<"add node <"<<n<<">"<<endl;
    }
    else{
        cout<<"have node <"<<n<<">"<<endl;
    }

}

//เพิ่มเส้นเชื่อม
void graph::addEdge(int u,int v,int w){
    if(haveNodeInGraph(v)&&haveNodeInGraph(u)){
        gr[v][u] = w;
        gr[u][v] = w;
        cout<<"add edge <"<<u<<"> and <"<<v<<"> have weight : <"<<w<<">"<<endl;
    }else{
        cout<<"don't have node <"<<u<<"> or <"<<v<<">"<<endl;
    }
}

//จำนวนเส้นเชื่อม
int graph::getNumEdeges(){
    int count=0;
    int start=0;
    int last = numOfNode.size();
    for(int i=0; i<numOfNode.size();i++){
        for(int j=start;j<numOfNode.size();j++){
            if(gr[numOfNode[i]][numOfNode[j]]!=0){
                count++;
            }
        }
        start++;
    }
    return count;
}

//ลบเส้นเชื่อม
void graph::deleteEdge(int u,int v){
    gr[u][v] =0;
    gr[v][u] =0;
}
//get เส้นเชื่อม จากมากไปน้อย
vector<Edges> graph::getEdge(){
    vector<Edges> edges;
    int start=0;
    int last = numOfNode.size();
    int numE = getNumEdeges();//จำนวนโนด
    bool haveInQ;

    while(edges.size()!=numE){
        Edges MaxE={0,0,0};
        start = 0;
        for(int i=0; i<numOfNode.size();i++){
            for(int j=start;j<numOfNode.size();j++){
                //check ว่ามีใน list หรือยัง
                haveInQ = false;
                for(int k=0;k<edges.size();k++){
                    if((edges[k].u == numOfNode[i] && edges[k].v == numOfNode[j]) || (edges[k].u == numOfNode[j] && edges[k].v == numOfNode[i]) ){
                        haveInQ = true;
                    }
                }
                //ถ้าไม่มีเส้นเชื่อม และ น้ำหนังไม่เป็น 0
                if(!haveInQ && gr[numOfNode[i]][numOfNode[j]]!=0){
                    //ถ้าน้ำหนักมากกว่า ค่า เก่า ให้เปลี่ยนค่า
                    if(gr[numOfNode[i]][numOfNode[j]]>MaxE.w){
                        MaxE.v = numOfNode[i];
                        MaxE.u = numOfNode[j];
                        MaxE.w = gr[numOfNode[i]][numOfNode[j]];
                    }
                }
            }
            start++;
        }
        if(MaxE.w!=0){
            edges.push_back(MaxE);
            cout<<"max : "<<"("<<MaxE.u<<","<<MaxE.v<<") = "<<MaxE.w<<endl;
        }
    }
    cout<<endl;
    return edges;
 }

int graph::getNumEOfNode(int n){
    int count = 0;
    for(int i=0;i<numOfNode.size();i++){
        if(gr[n][numOfNode[i]]!=0){
            count++;
        }
    }
    return count;
}

bool graph::isConect(){
    queue<int> q;
    int used[100]={0};
    int v = numOfNode[0];
    used[v] = 1;
    q.push(v);
    int count = 1;
    while(!q.empty()){
        for(int i=0;i<numOfNode.size();i++){
            if(gr[numOfNode[i]][q.front()]!=0 && !used[numOfNode[i]]){
                q.push(numOfNode[i]);
                used[numOfNode[i]] = 1;
                count++;
            }
        }
        q.pop();
    }
    if(count==numOfNode.size()) return true;

    return false;
}
graph graph::ReverseDelete(graph g){
    vector<Edges> edges = g.getEdge();
    for(int i=0;i<edges.size();i++){
        g.deleteEdge(edges[i].u,edges[i].v);
        cout<<"delete : ("<<edges[i].u<<","<<edges[i].v<<")"<<endl;
        if(g.isConect()){
            cout<<"is connected"<<endl;
        }else{
            cout<<"don't connected"<<endl;
            g.addEdge(edges[i].u,edges[i].v,edges[i].w);
        }
        cout<<endl;
    }
    return g;
}

int main(){
    graph g;
    g.addNode(1);
    g.addNode(2);
    g.addNode(3);
    g.addNode(4);
    g.addNode(5);
    g.addNode(6);
    g.addNode(7);

    g.addEdge(1,2,7);
    g.addEdge(1,4,5);
    g.addEdge(2,3,8);
    g.addEdge(2,4,9);
    g.addEdge(2,5,7);
    g.addEdge(3,5,5);
    g.addEdge(4,5,15);
    g.addEdge(4,6,6);
    g.addEdge(5,6,8);
    g.addEdge(5,7,9);
    g.addEdge(6,7,11);
    cout<<endl;
    g.showGraph();
    g = g.ReverseDelete(g);
    g.showGraph();
    return 0;
}
