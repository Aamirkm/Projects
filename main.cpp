/**************************
 *
 * Program 6: Linked Lists
 * Course: CS 141, Fall 2022, UIC
 * System: CLion on MacOS
 * Author: Aamir Merchant, starter code provided by Dr. Sara Riazi
 *
 * ************************/

#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <string>

using namespace std;

//************************** Node *************************

class Node{
    public:

        int data;
        Node *pNext;

};

//************************** Graph ****************************
void displayList(Node *pHead){

    while(pHead != NULL){
        cout << pHead->data << " ";
        pHead = pHead->pNext;
    }
    cout << endl;
}

void displayList(vector<Node*> vertices){
    for(int i = 0; i < vertices.size(); i++) {
        if(vertices.at(i) != NULL){
            cout << i << ": ";
            displayList(vertices.at(i));
        }
    }
}


class Graph {
	public:
		//add the node with neighborId as the neighbor of nodeId
		void addNeighbor(int nodeId, int neighborId);

		//reads the edge list from file and creates the adjacency list data structure
		void loadGraph(string edgeListFileName);

		//writes the adjacency list into the file
		void dumpGraph(string adjListFileName);

		//Prints number of nodes, number of edges, and maximum degree on terminal
		void printGraphInfo();

		//returns the number of neighbor (degree) of a node
		int getNumNeighbors(int nodeId);

		//returns the number of nodes in the graph
		int getNumVertices();

        int getMaxDegree();



	private:
        Node *pHead = NULL;
        Node *pTemp;
        vector<Node*> vertices;


};

void Graph::dumpGraph(std::string adjListFileName) {
    ofstream myOutStream;
    myOutStream.open(adjListFileName);
    assert(myOutStream.fail() == false);
    pTemp = NULL;
    for(int i = 0; i < vertices.size(); i++) {
        if(vertices.at(i) != NULL){
            pTemp = vertices.at(i);
            myOutStream << i << ": ";
            while(pTemp != NULL){
                myOutStream << pTemp->data;
                if(pTemp->pNext != NULL){
                    myOutStream << " ";
                }
                pTemp = pTemp->pNext;
            }
            myOutStream << endl;
        }
    }

    //myOutStream << displayList(vertices);

    myOutStream.close();
}

int Graph::getNumNeighbors(int nodeId) {
    int counter = 0;
    pTemp = vertices.at(nodeId);
    while(pTemp != NULL){
        counter++;
        pTemp = pTemp->pNext;
    }
    return counter;
}

int Graph::getNumVertices() {
    int count = 0;
    for(int i = 0; i < vertices.size(); i++) {
        if(vertices.at(i) != NULL){
            count++;
        }
    }
    return count;
}

int Graph::getMaxDegree() {
    int max = 0;
    for(int i = 0; i < vertices.size(); i++){
        if(vertices.at(i) != NULL){
            int x = getNumNeighbors(i);
            if(x > max){
                max = x;
            }
        }
    }
return max;
}

void Graph::printGraphInfo() {
    int counts = 0;
    for(int i = 0; i < vertices.size(); i++) {
        if(vertices.at(i) != NULL){
            counts += getNumNeighbors(i);
        }
    }
    cout << "Number of nodes: " << getNumVertices() << endl;
    cout << "Number of edges: " << counts/2 << endl;
    cout << "Maximum degree: " << getMaxDegree() << endl;
}



void Graph::addNeighbor(int nodeId, int neighborId) {

    while(vertices.size() <= nodeId){
        vertices.push_back(NULL);
    }

    pTemp = new Node;
    Node *pCurrent;
    pTemp->data = neighborId;
    pTemp->pNext = NULL;
    if(vertices.at(nodeId) == NULL) {

        vertices.at(nodeId) = pTemp;

    }else if(vertices.at(nodeId)->pNext == NULL){

        if(neighborId < vertices.at(nodeId)->data){

            pTemp->pNext = vertices.at(nodeId);
            vertices.at(nodeId) = pTemp;

        } else if(neighborId == vertices.at(nodeId)->data){

            return;

        }else{

            vertices.at(nodeId)->pNext = pTemp;

        }
    } else {

        pCurrent = vertices.at(nodeId);
        while(pCurrent->pNext != NULL && neighborId > pCurrent->data){
            pCurrent = pCurrent->pNext;

        }
        if(neighborId > pCurrent->data){
            pCurrent->pNext = pTemp;
        } else if(neighborId == pCurrent->data){
            return;
        } else {
            pTemp->pNext = pCurrent->pNext;
            pCurrent->pNext = pTemp;
            int tempValue = pCurrent->data;
            pCurrent->data = pTemp->data;
            pTemp->data = tempValue;
        }
    }


    //vertices.at(nodeId) = pHead;
    //delete pHead;

    //delete pCurrent;

    //addNeighbor(neighborId, nodeId);
    //addNeighbor(neighborId, nodeId);
    //cout << nodeId << ": ";
    //displayList(vertices.at(nodeId));

    //cout << vertices.at(nodeId)->data << endl;

   //vertices.at(nodeId)->pNext = pTemp;
    //cout << vertices.at(nodeId)->pNext->data << endl;
    //cout << nodeId << ": ";


}


void run(string edgeListFileName, string adjListFileName) {

    fstream edgeListFile(edgeListFileName, ios::in);
    fstream adjListFile(adjListFileName, ios::in);
    Graph graph;
    string line;
    int node, neighbor;
    while(!edgeListFile.eof()){
        getline(edgeListFile, line);
        if(line.empty()){break;}
        node = stoi(line.substr(0,line.find(' ')));
        if(line.find(' ') != string::npos) {
            neighbor = stoi(line.substr(line.find(' ')));
        }else{
            neighbor = stoi(line.substr(line.find('\t')));
        }
        graph.addNeighbor(node, neighbor);
        graph.addNeighbor(neighbor, node);
    }
   // displayList(graph.vertices);

    graph.dumpGraph(adjListFileName);

    //displayList(graph.vertices);

    graph.printGraphInfo();






}//END RUn

//*****************************************************************************


// The main will be removed for testing, do not add any code in the main function
int main() {
	//Change the filenames according to your local path.
    string edgeListFileName("karate.txt");
    string adjListFileName("karate_adj.txt");
	run(edgeListFileName, adjListFileName);
    return 0;
}
