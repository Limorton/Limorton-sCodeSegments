#ifndef LIMORTON_GRAPH_H_INCLUDED
#define LIMORTON_GRAPH_H_INCLUDED
#include <vector>
#include <limits.h>
using namespace std;

#define Lim_Debug 1
typedef unsigned int u_int;

//ͼ�Ĵ洢�ṹ
typedef int NodeType;        //���������

///�߽ṹ
struct EdgeNode{
    NodeType headID;    //�����ߵ�ͷ���
    NodeType tailID;    //�����ߵ�β���
    EdgeNode *vexOut;   //ָ��ͷ�ڵ���ͬ��������
    EdgeNode *vexIn;    //ָ��β�ڵ���ͬ��������
    // ����Ϊ�����ߵ���Ϣ
    double EdgeInfo;
};

///���ṹ
struct VertexNode{
    NodeType nodeID;        //�����
    EdgeNode* inEdgeTails;  //ǰ���������
    EdgeNode* outEdgeTails; //��̽������
    // �����Ϣ
    double NodeInfo;
};

/// ͼ�ṹ
class NetGraph{
private:
    int nodeNum;
    int edgeNum;
    vector<VertexNode> adjList;
public:
    NetGraph(int nodes = 0, int edges = 0): nodeNum(nodes), edgeNum(edges){};
//    NetGraph(int nodes): nodeNum(nodes){};
    int Reset_Nodes(int nodes);
    int Add_OneEdge(int head, int tail, double edgeInfo);
    int Delete_OneEdge(int head, int tail);
    int Clear_Graph();
    void Print_Graph();
    ~NetGraph(){ Clear_Graph();}
};
/** \brief
 *  �����ͷ�ԭ���Ŀռ䣬Ȼ������ nodeNum �� adjList
 * \param nodes: -> nodeNum
 * \return 1-success 0-failed
 */
int NetGraph::Reset_Nodes(int nodes){
    if(!Clear_Graph())
        return 0;
    nodeNum = nodes;
    adjList.resize(nodeNum);
}
/** \brief
 *
 * \param
 * \param
 * \return
 *
 */
int NetGraph::Add_OneEdge(int head, int tail, double edgeInfo){
    /// TODO here
}

///���һ����
void Add_OneEdge(int head, int tail, double edgeInfo ){
    EdgeNode* pEdge = new EdgeNode;
    pEdge ->headID = head;
    pEdge ->tailID = tail;
    pEdge ->bandWidth = band;
    pEdge ->rest_bandWidth = r_band;
    pEdge ->Rental = rent;

    pEdge -> vexOut = graph.adjList[head].outEdgeTails;
    if(pEdge -> vexOut){
        while(pEdge -> vexOut -> vexOut){   //�ҵ�����adjList[head].outEdgeTails��β��
           pEdge -> vexOut = pEdge -> vexOut -> vexOut;
        }
        pEdge -> vexOut -> vexOut = pEdge;  //����β��
        pEdge -> vexOut = nullptr;
    }
    else{   //����adjList[head].outEdgeTailsΪ��
         graph.adjList[head].outEdgeTails = pEdge;
         pEdge -> vexOut = nullptr;
    }

    pEdge -> vexIn = graph.adjList[tail].inEdgeTails;
    if(pEdge -> vexIn){
        while(pEdge -> vexIn -> vexIn){ //�ҵ�����adjList[head].inEdgeTails��β��
            pEdge -> vexIn = pEdge -> vexIn -> vexIn;
        }
        pEdge -> vexIn -> vexIn = pEdge;
        pEdge -> vexIn = nullptr;
    }
    else{
        graph.adjList[tail].inEdgeTails = pEdge;
        pEdge -> vexIn = nullptr;
    }
}

///ɾ��һ����
void Delete_OneEdge(int head, int tail){
    EdgeNode *p, *q;
    //�޸�head�ĳ�������
    if(graph.adjList[head].outEdgeTails ->tailID == tail){  //������ͷ
        q = graph.adjList[head].outEdgeTails;
        if(q ->vexOut){                                     //�ñߺ��б�
            graph.adjList[head].outEdgeTails = q ->vexOut;
        }
        else{                                               //�ñߺ��ޱ�
            graph.adjList[head].outEdgeTails = nullptr;
        }
    }
    else{                                                   //��������ͷ
        p = graph.adjList[head].outEdgeTails;
        while(p && (p ->vexOut) && (p ->vexOut ->tailID != tail)){
            p = p ->vexOut;
        }                                                   //��������Ѱ�Ҹñ�
        if(p && (p ->vexOut -> vexOut)){
            q = p ->vexOut;
            p -> vexOut = q -> vexOut;
        }
        else{   //�ñ��޳��ߣ���Ҫɾ���ı�������ĩβ
            p -> vexOut = nullptr;
        }
    }
    //�޸�tail���뻡����
    if(graph.adjList[tail].inEdgeTails ->headID == head){
        q = graph.adjList[tail].inEdgeTails;
        if(q ->vexIn){
            graph.adjList[tail].inEdgeTails = q ->vexIn;
        }
        else{
            graph.adjList[tail].inEdgeTails = nullptr;
        }
        delete q;   //ɾ���ñ�
    }
    else{
        p = graph.adjList[tail].inEdgeTails;
        while(p && (p ->vexIn) && (p ->vexIn ->headID != head)){
            p = p ->vexIn;
        }                                           //��������Ѱ�Ҹñ�
        if(p && (p -> vexIn -> vexIn)){ //ɾ���ñ�
            q = p ->vexIn;
            p -> vexIn = q -> vexIn;
            delete q;
        }
        else{
            q = p ->vexIn;
            delete q;
            p -> vexIn = nullptr;
        }
    }
}

///��ӳ���Դ��
void Add_SuperSourceNodeEdge(const vector<int>& ServerNode){
    int servNum = ServerNode.size();
    for(int i = 0; i < servNum; ++i){
        if(ServerNode[i] == 1 || ServerNode[i] == 2){
            Add_OneEdge(graph.nodeNum, i, BAND_MAX, BAND_MAX, 0);
            Add_OneEdge(i, graph.nodeNum, BAND_MAX, BAND_MAX, 0);
        }
    }
}

///ɾ������Դ��
void Destory_SuperSourceNodeEdge(const vector<int>& ServerNode){
    int servNum = ServerNode.size();
    for(int i = 0; i < servNum; ++i){
        if(ServerNode[i] == 1 || ServerNode[i] == 2){
            Delete_OneEdge(graph.nodeNum, i);
            Delete_OneEdge(i, graph.nodeNum);
        }
    }
}

///��ӳ������
void Add_SuperEndNodeEdge(){
    for(int i = 0; i < graph.custNum; ++i){
        Add_OneEdge(graph.nodeNum + 1, graph.customerInfo[i].toNodeID, graph.customerInfo[i].bandNeed, graph.customerInfo[i].bandNeed, 0);
        Add_OneEdge(graph.customerInfo[i].toNodeID, graph.nodeNum + 1, graph.customerInfo[i].bandNeed, graph.customerInfo[i].bandNeed, 0);
    }
}

///ɾ���������
void Destory_SuperEndNodeEdge(){
    for(int i = 0; i < graph.custNum; ++i){
        Delete_OneEdge(graph.nodeNum + 1, graph.customerInfo[i].toNodeID);
        Delete_OneEdge(graph.customerInfo[i].toNodeID, graph.nodeNum + 1);
    }
}

///��������ͼ
void Create_Graph(char** topo){
    //��ʼ������ڵ��ͷ
    for(int i = 0; i < graph.nodeNum; ++i){
        graph.adjList[i].nodeID = i;
        graph.adjList[i].outEdgeTails = nullptr;
        graph.adjList[i].inEdgeTails = nullptr;
        graph.adjList[i].edgeAttached = 0;
        graph.adjList[i].maxFlux = 0;
        graph.adjList[i].minSA = MY_INT_MAX;
    }
    //��ʼ�����������Ϣ
    graph.adjList[graph.nodeNum].nodeID = graph.nodeNum;    //Դ��
    graph.adjList[graph.nodeNum].outEdgeTails = nullptr;
    graph.adjList[graph.nodeNum].inEdgeTails = nullptr;
    graph.adjList[graph.nodeNum].edgeAttached = graph.custNum;
    graph.adjList[graph.nodeNum].maxFlux = BAND_MAX;

    graph.adjList[graph.nodeNum + 1].nodeID = graph.nodeNum + 1;    //���
    graph.adjList[graph.nodeNum + 1].outEdgeTails = nullptr;
    graph.adjList[graph.nodeNum + 1].inEdgeTails = nullptr;
    graph.adjList[graph.nodeNum + 1].edgeAttached = graph.custNum;
    graph.adjList[graph.nodeNum + 1].maxFlux = BAND_MAX;

    int ptrData = 4;    //���ѽ�����ݿ�ʼ��λ��
    int a, b, c, d;     //����������Ϣ��ͷ�ڵ㣬β��� ���� ����
    stringstream charStream;
    //��ȡ������
    int RentSum = 0;
    int BandSum = 0;
    for(int i = 0; i < graph.edgeNum; ++i){
        charStream << topo[ptrData];
        //cout << "read Once..." << endl;
        //����ÿ���ߵ���Ϣ
        charStream >> a >> b >> c >> d;
        charStream.clear();
        ++ptrData;
        BandSum += c;
        RentSum += d;
        //���½�������Ϣ
        graph.adjList[a].edgeAttached += 1;
        graph.adjList[b].edgeAttached += 1;
        graph.adjList[a].maxFlux += c;
        graph.adjList[b].maxFlux += c;

        Add_OneEdge(a, b, c, c, d);
        Add_OneEdge(b, a, c, c, d);
        //��������
//        EdgeNode* pEdge = new EdgeNode;
//        pEdge -> headID = a;
//        pEdge -> tailID = b;
//        pEdge -> bandWidth = c;
//        pEdge -> rest_bandWidth = c;
//        pEdge -> Rental = d;
//        pEdge -> vexOut = graph.adjList[a].outEdgeTails;
//
//        if(pEdge -> vexOut){
//            while(pEdge -> vexOut -> vexOut){
//               pEdge -> vexOut = pEdge -> vexOut -> vexOut;
//            }
//            pEdge -> vexOut -> vexOut = pEdge;
//            pEdge -> vexOut = nullptr;
//        }
//        else{
//             graph.adjList[a].outEdgeTails = pEdge;
//             pEdge -> vexOut = nullptr;
//        }
//        //��������
//        EdgeNode* pEdgeBack = new EdgeNode;
//        pEdgeBack -> headID = b;
//        pEdgeBack -> tailID = a;
//        pEdgeBack -> bandWidth = c;
//        pEdgeBack -> rest_bandWidth = c;
//        pEdgeBack -> Rental = d;
//        pEdgeBack -> vexOut = graph.adjList[b].outEdgeTails;
//
//        if(pEdgeBack -> vexOut){
//            while(pEdgeBack -> vexOut -> vexOut){
//                pEdgeBack -> vexOut = pEdgeBack -> vexOut -> vexOut;
//            }
//            pEdgeBack -> vexOut -> vexOut = pEdgeBack;
//            pEdgeBack -> vexOut = nullptr;
//        }
//        else{
//            graph.adjList[b].outEdgeTails = pEdgeBack;
//            pEdgeBack -> vexOut = nullptr;
//        }
    }
//    for(int i = 0;  i < graph.nodeNum; ++i){
//            EdgeNode **pInLink = &graph.adjList[i].inEdgeTails;
//            for(int j = 0; j < graph.nodeNum; ++j){
//                if(i == j){
//                    continue;
//                }
//                EdgeNode *p = graph.adjList[j].outEdgeTails;
//                while(p){
//                    if(p ->tailID != graph.adjList[i].nodeID){
//                        p = p ->vexOut;
//                        continue;
//                    }
//                    *pInLink = p;
//                    pInLink = &p ->vexIn;
//                    p = p ->vexOut;
//                }
//            }
//            *pInLink = nullptr;
//    }

    charStream.clear();
    ++ptrData;   //������ȫ�������ˣ�ptrDataָ�����ѽ��Ŀ�ͷ
    graph.avgBand = BandSum / graph.edgeNum;
    graph.avgRent = RentSum / graph.edgeNum;
    //��ȡ���ѽ��
    int sumNeed = 0;
    for(int j = 0; j < graph.custNum; ++j){
        charStream << topo[ptrData];
        charStream >> graph.customerInfo[j].customerID >> graph.customerInfo[j].toNodeID >> graph.customerInfo[j].bandNeed;
        charStream.clear();
        ++ptrData;
        sumNeed += graph.customerInfo[j].bandNeed;
    }
    graph.avgNeed = sumNeed / graph.custNum;
}

///ɾ������ͼ�ռ�
void Clear_Graph(){

    for(int i = 0; i < graph.nodeNum + 2; ++i){
        EdgeNode *p = graph.adjList[i].outEdgeTails;
        EdgeNode *q;
        while(p){
            q = p;
            p = p -> vexOut;
            delete q;
        }
        graph.adjList[i].outEdgeTails = nullptr;
        graph.adjList[i].inEdgeTails = nullptr;
    }
    graph.adjList.clear();
    //Destory_SuperEndNodeEdge();
    //print_time("Destory Finish:");
}

///��ʾ����ͼ
void Print_Graph(){
    cout << "----Print Nodes and Edges--------------------------" << endl;
    for(int i = 0; i < graph.nodeNum + 2; ++i){
        cout << graph.adjList[i].nodeID << "--out--(" << graph.adjList[i].edgeAttached << "," << graph.adjList[i].maxFlux << ")" << "-->";
        EdgeNode *p = graph.adjList[i].outEdgeTails;
        while(p){
            cout << "(" << p ->headID << ", " << p -> tailID << ", " << p -> bandWidth << ", " << p -> rest_bandWidth<< ", " << p -> Rental << ")";
            p = p -> vexOut;
        }
        cout << endl;
        p = graph.adjList[i].inEdgeTails;
        cout << graph.adjList[i].nodeID << "--in---(" << graph.adjList[i].edgeAttached << "," << graph.adjList[i].maxFlux << ")" << "-->";
        while(p){
            cout << "(" << p ->headID << ", " << p -> tailID << ", " << p -> bandWidth << ", " << p -> rest_bandWidth << ", " << p -> Rental << ")";
            p = p -> vexIn;
        }
        cout << endl << endl;
    }
    cout << "--Print customer message:" << endl;
    for(int i = 0; i < graph.custNum; ++i){
        cout << graph.customerInfo[i].customerID << "-->" << graph.customerInfo[i].toNodeID << ", Need:" << graph.customerInfo[i].bandNeed << endl;
    }
    cout << "--Other info:" << endl;
    cout << "--avgBand is " << graph.avgBand << endl;
    cout << "--avgRent is " << graph.avgRent << endl;
    cout << "--avgNeed is " << graph.avgNeed << endl;
    cout << "--serverCost is " << graph.serverCost << endl;
    cout << "----End Print N&E----" << endl << endl;
}


#endif // LIMORTON_GRAPH_H_INCLUDED
