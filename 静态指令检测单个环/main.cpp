#include <iostream>
#include <fstream>
#include "Seq.h"
#include<vector>
#include <string>
using namespace std;


const char* INPUT_FILE = "matrix.txt";
const char* INPUT_NODE = "GraphNode.txt";
const char * FELENODENAME="string.txt";
struct Graph {
	int NodeCount;                  // �ڵ����Ŀ
	//int AdjMatrix[MAX_N][MAX_N];    // �ڽӾ���,���ͼ��i,j������G[i][j]>0������G[i][j]=0
	int **AdjMatrix;
};

const int MAX_POINT = 10000;
const int MAX_NODE = 100000;
typedef int Path[MAX_POINT];            // �����洢·��
int paths;						// ��¼���ɵ�·������Ŀ

int src;
int des[MAX_POINT];//��Ƕ�Ӧ�ڵ��Ƿ�Ϊ��ʼ�㣬�����㣬 ��ʼ��Ϊ0 ��������Ϊ1


struct treeNode{
	int nodeNumber;//�ڵ�ͼ���
	int fatherNode;//���ڵ�ͼ���
	int fatherTreeNode;//���ڵ� tree���
};

struct  treeNode *TreeNode;
 vector<string> nodeNameV;

void getNodeName(const char * filename, vector<string> &nodeNameV1)
{
    ifstream ife(filename);
    cout<< "read file "<<endl;
      string temp;
    while(ife >> temp)
    {
         if(temp != "" && temp != " ")
         {
             nodeNameV1.push_back(temp);
             cout<< " read  "<< temp;
         }
         else cout<< " read  null  ";
    }

}

// ��ӡ·��
void PrintPathTest(struct  treeNode *TreeNode , int length) {
	//cout << "\n\n\n\n";
	bool* temp = (bool *)malloc(sizeof(bool)*length);
	for (int i = 0; i < length; i++)
	{
		temp[i] = true;
	}
	for (int j = length-1; j >=0; j--)
	{
		if (temp[j]  )
		{
			temp[j] = false;
            cout << (nodeNameV[TreeNode[j].nodeNumber] ) << "->";
			int tempNF = TreeNode[j].fatherTreeNode;
			while (tempNF != -1)
			{
                cout <<  (nodeNameV [TreeNode[tempNF].nodeNumber]) << "->";
				temp[tempNF] = false;
				tempNF = TreeNode[tempNF].fatherTreeNode;
			}
			cout << "\n";
		}	
	}
}


void PrintIntInStack(vector<string> printIntStack)
{
    vector<string> ::iterator iter;
	for (iter = printIntStack.end(); iter != printIntStack.begin(); 	)
	{
		iter--;
		if (iter == printIntStack.begin())
		{
            cout <<  *iter ;
		}
		else
		{
            cout << *iter;
            cout<< "->";
		}
	}
	cout << endl;
}
// ��ӡ·��
void PrintPath(struct  treeNode *TreeNode, int length) {
	///cout << "\n\n\n\n";
	int numberOfPath=0;
	bool* temp = (bool *)malloc(sizeof(bool)*length);
	for (int i = 0; i < length; i++)
	{
		temp[i] = true;
	}

    vector <string > printIntStack;

	for (int j = length - 1; j >= 0; j--)
	{
		if (temp[j] && des[TreeNode[j].nodeNumber] == 1)
		{//û��������� ���һ������ F
			numberOfPath++;			
			
			temp[j] = false;
			printIntStack.clear();

        printIntStack.push_back( nodeNameV [TreeNode[j].nodeNumber] );

		  ///////////////////////  	printIntStack.push_back(TreeNode[j].nodeNumber);
		//	cout << (char)(TreeNode[j].nodeNumber + 'A') << "->";

			int tempNF = TreeNode[j].fatherTreeNode;
			while (tempNF != -1)
			{
         printIntStack.push_back( nodeNameV[TreeNode[tempNF].nodeNumber]);
				      ////////////////////////// printIntStack.push_back(TreeNode[tempNF].nodeNumber );
			//	cout << (char)(TreeNode[tempNF].nodeNumber + 'A') << "->";
				temp[tempNF] = false;
				tempNF = TreeNode[tempNF].fatherTreeNode;
			}
			PrintIntInStack(printIntStack);

			//cout << "\n";
		}
	}
	cout << "--------------------" << endl;
	cout << "The generated path number is:" << numberOfPath << endl;

	free(temp);
}

 

// ��̬�����ά����洢�ڽӾ���
int ** NewMatrix(int nodeCount)
{
	int **Matrix;
	Matrix = new int *[nodeCount];
	for (int i = 0; i < nodeCount; i++)
	{
		Matrix[i] = new int[nodeCount];
		//	Matrix[i][2] = i;
	}
	return Matrix;
}

// �ͷŶ�̬�����ά������ڴ�
void DeleteMatrix(int **Matrix, int nodeCount)
{
	for (int i = 0; i < nodeCount; i++)
	{
		delete[] Matrix[i];
	}
	delete Matrix;
}

void ReadData(Graph& G)  // ��������
{
	int k = 0, l = 0;
	int src = 0;
	ifstream fin(INPUT_FILE);
	ofstream infile;
	infile.open(INPUT_NODE);
	fin >> G.NodeCount;       // ����ڵ���Ŀ���ڵ��0��ʼ���
	G.AdjMatrix = NewMatrix(G.NodeCount);
	for (int i = 0; i < G.NodeCount; i++)
	{

		for (int j = 0; j < G.NodeCount; j++) {
			fin >> G.AdjMatrix[i][j];
			//cout << G.AdjMatrix[i][j];
		}
		cout << "\n";
	}
	for (k = 0; k < G.NodeCount; k++) {
		for (l = 0; l < G.NodeCount; l++) {
			if (G.AdjMatrix[k][l] == 0) {
				continue;
			}
			else
				break;
		}
		if (l == G.NodeCount) {
			infile << src << " " <<k << endl;
			//infile.close();
			//cout << k << endl;
			//infile >> k;
		}
	}
	//fin.close();
	//infile.close();

}


void ReadStartAndEndFromFile()
{//û�м����ʼ�� ������ĳ�ͻ
	ifstream finode(INPUT_NODE);
	int i = 0;
	for (i = 0; i < MAX_POINT; i++)
	{
		des[i] = -1;
	}
	int temp;
	while (!finode.eof()) {// ѭ��������ʼ�ڵ�Ͷ�Ӧ��Ŀ�Ľڵ�
		finode >> src >> temp;
		des[temp] = 1;
		des[src] = 0;
		// ����������ȱ���
	}
}
bool intequality(int * a, int * b)
{//�ж����
	do 
	{
			if (*a != *b)
			{
				return false;
			}	
			a++; b++;
	} while (*a != -1 && *b != -1);
	if (*a == -1 && *b == -1)
		return true;
	else
	{
		return false;
	}
}
bool IsCircleSt(int * path, int length)
{/* ��¼�߹��� ���� ������Ȼ���»��Ƚ�*/
	vector < int * >  circle;
	int lastNumber = path[length - 1];
	int currentTag=length;//��¼������ ���µ�һ��ѭ����

	bool tagresult=false,tagrun=true;

	for (int i = length - 2; tagrun && i >= 0; i--)
	{
		if ( path[i] == lastNumber)
		{//��
			//���ƻ�
			int * tempCircle = (int *)malloc(sizeof (int)* (length - i+1));
			int k;
			for (k = i; k < currentTag; k++)
			{
				tempCircle[k - i] = path[k];
			}
			tempCircle[k - i] = -1;

			/*t
			cout << "��ǰ��";
			for (int ti = 0; ti <= k - i; ti++)
			{
				cout << tempCircle[ti]<<" ";
			}
			cout << endl;
			est*/

			currentTag = i+ 1;

			//�ж��Ƿ�����ͬ�Ļ���
			vector <int *> ::iterator iter;
			for (iter = circle.begin(); iter != circle.end(); iter ++)
			{
				if (intequality(*iter,tempCircle))
				{
					tagresult= true;
					tagrun = false;
				}
			}
			//û���ظ��� ��Ҫ���
			circle.push_back(tempCircle);			
		}
	}

	vector <int *> ::iterator iter;
	for (iter = circle.begin(); iter != circle.end(); iter++)
	{
		free(*iter);
	}

	return tagresult;
}

bool IsCircle(int Last, struct treeNode * TreeNode)
{
	int LastNodeNumber =  TreeNode[Last].nodeNumber;//·�������ͼ���
	int n = 0;//��¼��ͬ�����


	int path[MAX_NODE];
	int tempFNode = TreeNode[Last].fatherTreeNode;
	int kPath =1;
	path[0] = LastNodeNumber;
	
	while (tempFNode != -1){
		path[kPath] = TreeNode[tempFNode].nodeNumber;//·��
		kPath++;

		if (TreeNode[tempFNode].nodeNumber == LastNodeNumber)
		{//��ͬ��
			n++;
			if (n >= 2)
			{//�Զ����ֱ���˳�
				return true;
			}
			//if (n % 2 == 0)
			{
				//�ַ����ж�
				bool b= IsCircleSt(path, kPath);
				if ( b)
				{
					return true;
				}
			}
		}
		tempFNode = TreeNode[tempFNode].fatherTreeNode;
	} ;

	return false;
}

void Caculate(Graph G)
{
	TreeNode = (struct treeNode *) malloc(sizeof(struct treeNode) *MAX_NODE);
	TreeNode[0].fatherNode = -1;
	TreeNode[0].fatherTreeNode = -1;
	TreeNode[0].nodeNumber = 0;
	int currentNumberOfTreeNode=1;//��ǰTree�ڵ�����

	//Ӧ���ǹ�����ȱ���
	MySeq myseq = MySeq(MAX_POINT);//������п��ܺܳ�
	myseq.ToolSeqInsert(0);
	
	 do 
	 {
		 int tempN = myseq.ToolSeqOut();//���е�ǰ������
		 for (int i = 0; i < G.NodeCount; i++)
		 {
			 int tempGrapthN = TreeNode[tempN].nodeNumber;
			 if (G.AdjMatrix[tempGrapthN][i] != 0)
			 {//�ڵ���Ե���� �ӽڵ�
			
			//	 cout << "  " << (char)(tempGrapthN + 'A') << "-->" << (char)(i + 'A') << "  ";
				 TreeNode[currentNumberOfTreeNode].fatherNode = tempGrapthN;//���ڵ� ��ͼ�����  չʾ
				 TreeNode[currentNumberOfTreeNode].fatherTreeNode = tempN;//���ڵ� ��TreeNode�����
				 TreeNode[currentNumberOfTreeNode].nodeNumber = i;//�ڵ�ֵ �����			 

				 //���б�
				 bool b = IsCircle(currentNumberOfTreeNode, TreeNode);
				 if (b)
				{
					 TreeNode[currentNumberOfTreeNode].fatherNode = -1;//���ڵ� ��ͼ�����  չʾ
					 TreeNode[currentNumberOfTreeNode].fatherTreeNode = -1;//���ڵ� ��TreeNode�����
					 TreeNode[currentNumberOfTreeNode].nodeNumber = -1;//�ڵ�ֵ �����	
					 continue;
				}
				// IsCircle(currentNumberOfTreeNode, TreeNode);
			//test  PrintPathTest(TreeNode, currentNumberOfTreeNode);
		
				 //�����
				 myseq.ToolSeqInsert(currentNumberOfTreeNode);
				 currentNumberOfTreeNode++;
			 }
		 }
		

	 } while ( ! myseq.IsSeqEmpty());

	 PrintPath(TreeNode, currentNumberOfTreeNode);

	 myseq.freeSeq();
	 free(TreeNode);



}

int main()
{
	Graph G;


	int src=0, des=0;           // �����յ�    

 
	ReadData(G);  // ����洢ͼ�Ľڵ������ڽӾ���
	ReadStartAndEndFromFile();
   // getNodeName( FELENODENAME,  nodeNameV);
	string temp[91] = {"1","2","3","4","5","6","7","8","9","10",
		"11", "12", "13", "14", "15", "16", "17", "18", "19", "20" ,
		 "21", "22", "23", "24", "25", "26", "27", "28", "29", "30" ,
		"31", "32", "33", "34", "35", "36", "37", "38", "39", "40" ,
		"41", "42", "43", "44", "45", "46", "47", "48", "49", "50" ,
		"51", "52", "53", "54", "55", "56", "57", "58", "59", "60" };
	 for (int k = 0; k < 50;k++)
	 {
		 nodeNameV.push_back(temp[k]);
	}
	Caculate(G);

	DeleteMatrix(G.AdjMatrix, G.NodeCount);			// �ͷŶ�̬������ڴ�

	
	return 0;
}
