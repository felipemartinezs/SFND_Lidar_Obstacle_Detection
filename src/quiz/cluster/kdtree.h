/* \author Aaron Brown */
// Quiz on implementing kd tree

#include "../../render/render.h"


// Structure to represent node of kd tree
struct Node
{
	std::vector<float> point;
	int id;
	Node* left;
	Node* right;

	Node(std::vector<float> arr, int setId)
	:	point(arr), id(setId), left(NULL), right(NULL)
	{}
};

struct KdTree
{
	Node* root;

	KdTree()
	: root(NULL)
	{}

	//void insert(std::vector<float> point, int id)
	
		// TODO: Fill in this function to insert a new point into the tree
		// the function should create a new node and place correctly with in the root 
	//====================================================
      
    // Node** node -- double pointer, memory address
	void insertHelper(Node** node, uint treeDepth, std::vector<float> point, int id)
	{
		// dereference *node to see its actual value
		if(*node == NULL)
			// if you encouter the NULL node (root, or child), 
			// you assign this point in that place
			// dereference *node to set the actual value
			*node = new Node(point, id);
		else
		{
			// For 2D pointers,
			// Depending on the treeDepth (every second, even|odd, 0|1 using mod 2)
			uint cd = treeDepth % 2; // results in 0 or 1
			if(point[cd] <= ((*node)->point[cd])) // it is possible that it is LESS OR EQUAL
				insertHelper(&((*node)->left), treeDepth+1, point, id);
			else
				insertHelper(&((*node)->right), treeDepth+1, point, id);
		}
		
	}

	void insert(std::vector<float> point, int id)
	{
		uint treeDepth = 0;
		// insertHelper is a recursive function
		// passing in memory address of root node - which is a global pointer in struct KdTree
		insertHelper(&root, treeDepth, point, id);
	}  
      
    //====================================================
      
      
	void searchHelper(
		std::vector<float> targetPoint, 
		Node* currentNode, 
		int treeDepth, 
		float distanceTreshhold, 
		std::vector<int>& resultIds) // address reference so we can keep changes
	{
		std::cout 
			<< std::endl 
			<< treeDepth
			<< " searchHelper: "
			<< " distanceTreshhold = " 
			<< distanceTreshhold 
			<< " meters, "
			<< "targetPoint = ";
		for (auto i: targetPoint)
  			std::cout << i << " "; 
		
		if(currentNode != NULL)
		{
			std::cout
				<< " current point = ";
			for (auto i: currentNode->point)
  				std::cout << i << " ";

			if( (  currentNode->point[0] >= (targetPoint[0] - distanceTreshhold) 
				&& currentNode->point[0] <= (targetPoint[0] + distanceTreshhold)) // Aaron has && here ?!?
				&& 
				(  currentNode->point[1] >= (targetPoint[1] - distanceTreshhold)
				&& currentNode->point[1] <= (targetPoint[1] + distanceTreshhold)))
			{
				float distance = sqrt(
					( currentNode->point[0] - targetPoint[0]) * (currentNode->point[0] - targetPoint[0])
					+(currentNode->point[1] - targetPoint[1]) * (currentNode->point[1] - targetPoint[1]));
				std::cout << " distance = " << distance;
				if( distance <= distanceTreshhold)
				{
					std::cout << " adding current node ID to results <<<<<<<<<<<<<<<<< " << currentNode->id ;
					resultIds.push_back(currentNode->id); // add this id to search results
				} 
			}

			// Mod % 2 to check if we are comparing X or Y coordinate
			// flow LEFT on the tree
			if( (targetPoint[treeDepth % 2] - distanceTreshhold) <= currentNode->point[treeDepth % 2] )
			{
				std::cout << " choosing LEFT branch " << std::endl;
				searchHelper(targetPoint, currentNode->left, treeDepth+1, distanceTreshhold, resultIds);
			}
			// else?
			// flow RIGHT on the tree
			if( (targetPoint[treeDepth % 2] + distanceTreshhold) > currentNode->point[treeDepth % 2] )			
			{
				std::cout << " choosing RIGHT branch " << std::endl;
				searchHelper(targetPoint, currentNode->right, treeDepth+1, distanceTreshhold, resultIds);
			}
		}
	}

	// return a list of point ids in the tree that are within distance of targetPoint
	std::vector<int> search(std::vector<float> targetPoint, float distanceTreshhold)
	{
		std::vector<int> resultIds;
		int treeDepth = 0;
		searchHelper(targetPoint, root, treeDepth, distanceTreshhold, resultIds);
		
		std::cout << "search results: " << resultIds.size() << " ";
		
		for (auto i: resultIds)
  			std::cout << i << " ";
		std::cout << std::endl;

		return resultIds;
	}
};



