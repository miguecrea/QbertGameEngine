#include "AIComponent.h"
#include "GameObject.h"
#include"SceneManager.h"
#include "Renderer.h"
#include"DebugRenderComponent.h"
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include<set>
#include <stack>
#include <array>
#include"staticHeader.h"





//
#define X_MAX 720
#define X_STEP 48
#define Y_MAX 816
#define Y_STEP 48
#define COLUMNS 1
#define ROWS 1

// Use std::enable_shared_from_this<T> when your class needs to return shared_ptr<T> to itself.

//Always create the object via std::make_shared<T>().

//Prevents ownership bugs and double - deletion.




dae::AIComponent::AIComponent(std::shared_ptr<GameObject> Map, std::shared_ptr<GameObject> pTargetGameObejct):
	m_Map{Map},m_Target{ pTargetGameObejct},m_pSceneManager{&SceneManager::GetInstance()}
{
}

void dae::AIComponent::BeginPlay()
{

	m_Self = this->GetOwner();

	m_mapComponent = m_Map->GetComponent<dae::MapComponent>();


	if (!m_Self)
	{
		std::cout << "Owner is null\n";
	}
}




inline bool operator < (const Node & lhs, const Node & rhs)
{//We need to overload "<" to put our struct into a set
	return lhs.fCost < rhs.fCost;
}

bool isDestination(int x, int y, Node dest)
{

	//row and columns of the tow are the same 
	if (x == dest.x && y == dest.y) {
		return true;
	}
	return false;
}


double calculateH(int x, int y, Node dest) {
	double H = (sqrt((x - dest.x) * (x - dest.x)
		+ (y - dest.y) * (y - dest.y)));
	return H;
}

bool dae::AIComponent::isValid(int x, int y)
{

	// y column and x is the row 
	

	//this y is row and y is column in grid positions
	

	//if check is
	                           // 15 columns             //rows 17 
	if (x < 0 || y < 0 || x >= (X_MAX / X_STEP) || y >= (Y_MAX / Y_STEP))
	{
		return false;
	}

	if (m_mapComponent->MapArray[y][x] == 9 || m_mapComponent->MapArray[y][x] == 8)
	{
		return false;
	}
	return true;
}
std::vector<Node> dae::AIComponent::aStar(Node agent, Node dest) 

{
	std::vector<Node> empty;

	if (!isValid(dest.x, dest.y)) 
	{
		//std::cout << "Destination is an obstacle" << std::endl;
		return empty;
	}

	if (isDestination(agent.x, agent.y,dest)) {
		//std::cout << "You are the destination" << std::endl;
		return empty;
	}

	// Dynamically allocate memory for the closedList


	  //2d array of bools   //15 columns
	bool ** closedList = new bool * [X_MAX / X_STEP];

	                    // rows 
	for (int i = 0; i < X_MAX / X_STEP; ++i) 
	{
		//for each  of column ,fill them with 17 rows 
		closedList[i] = new bool[Y_MAX / Y_STEP];
		std::fill_n(closedList[i], Y_MAX / Y_STEP, false);
	}




//2d array as well    // 15 vectores ,each of the has size of 17
	std::vector<std::vector<Node>> allMap(X_MAX / X_STEP,std::vector<Node>(Y_MAX / Y_STEP));

	// Initialize whole map   //columns 
	for (int x = 0; x < X_MAX / X_STEP; x++)
	{
		for (int y = 0; y < Y_MAX / Y_STEP; y++) {
			allMap[x][y].fCost = FLT_MAX;
			allMap[x][y].gCost = FLT_MAX;
			allMap[x][y].hCost = FLT_MAX;
			allMap[x][y].parentX = -1;
			allMap[x][y].parentY = -1;
			allMap[x][y].x = x;
			allMap[x][y].y = y;

			closedList[x][y] = false;
		}
	}

	// Initialize starting point
	int x = agent.x;  //column
	int y = agent.y;  //row 
	allMap[x][y].fCost = 0.0;
	allMap[x][y].gCost = 0.0;
	allMap[x][y].hCost = 0.0;
	allMap[x][y].parentX = x;
	allMap[x][y].parentY = y;

	std::vector<Node> openList;
	openList.emplace_back(allMap[x][y]);

	bool destinationFound = false;

	while (!openList.empty() && openList.size() < (X_MAX / X_STEP) * (Y_MAX / Y_STEP))
	{
		Node node;
		//it = next(it)
		do {
			float temp = FLT_MAX;
			std::vector<Node>::iterator itNode;
			for (std::vector<Node>::iterator it = openList.begin();
				it != openList.end(); ++it) {
				Node n = *it;
				if (n.fCost < temp)
				{
					temp = n.fCost;
					itNode = it;
				}
			}
			node = *itNode;
			openList.erase(itNode);
		} while (!isValid(node.x, node.y) && !openList.empty());

		x = node.x;
		y = node.y;
		closedList[x][y] = true;

		for (int newX = -1; newX <= 1; newX++)
		{
			for (int newY = -1; newY <= 1; newY++) {
				double gNew, hNew, fNew;
				if (isValid(x + newX, y + newY)) {
					if (isDestination(x + newX, y + newY, dest))
					{
						//Lines block diagonals //before checking if it is destinantion
						if (newX != 0 && newY != 0) {
							continue;
						}


						allMap[x + newX][y + newY].parentX = x;
						allMap[x + newX][y + newY].parentY = y;
						destinationFound = true;

						// Clean up dynamically allocated memory
						for (int i = 0; i < X_MAX / X_STEP; ++i) {
							delete[] closedList[i];
						}
						delete[] closedList;

						return makePath(allMap, dest);
					}
					else if (!closedList[x + newX][y + newY]) {
						gNew = node.gCost + 1.0;
						hNew = calculateH(x + newX, y + newY, dest);
						fNew = gNew + hNew;
						if (allMap[x + newX][y + newY].fCost == FLT_MAX ||
							allMap[x + newX][y + newY].fCost > fNew)
						{

							//lines blocks diagonals too 
							if (newX != 0 && newY != 0) {
								fNew = FLT_MAX;
								gNew = FLT_MAX;
								hNew = FLT_MAX;
							}

						
							allMap[x + newX][y + newY].fCost = float(fNew);
							allMap[x + newX][y + newY].gCost = float(gNew);
							allMap[x + newX][y + newY].hCost = float(hNew);
							allMap[x + newX][y + newY].parentX = x;
							allMap[x + newX][y + newY].parentY = y;
							openList.emplace_back(allMap[x + newX][y + newY]);
						}
					}
				}
			}
		}
	}


	if (!destinationFound)
	{
		//std::cout << "Destination not found" << std::endl;
		for (int i = 0; i < X_MAX / X_STEP; ++i) {
			delete[] closedList[i];
		}
		delete[] closedList;
		return empty;
	}
	return empty;
}


std::vector<Node> dae::AIComponent::makePath(std::vector<std::vector<Node>> map, Node dest) {
	try {
		//std::cout << "Found a path" << std::endl;
		int x = dest.x;
		int y = dest.y;
		std::stack<Node> path;
		std::vector<Node> usablePath;

		while (!(map[x][y].parentX == x && map[x][y].parentY == y)
			&& map[x][y].x != -1 && map[x][y].y != -1)
		{
			path.push(map[x][y]);
			int tempX = map[x][y].parentX;
			int tempY = map[x][y].parentY;
			x = tempX;
			y = tempY;

		}
		path.push(map[x][y]);

		while (!path.empty()) {
			Node top = path.top();
			path.pop();
			usablePath.emplace_back(top);
		}
		//std::cout << "Path full, " << usablePath.size() << std::endl;
		return usablePath;
	}
	catch (const std::exception& e)
	{
		std::cout << "Path empty, error " << e.what() << std::endl;
		return std::vector<Node>();
	}
}




void dae::AIComponent::Render()
{




	for (size_t i = 0; i < m_usablePath.size(); i++)
	{
		SDL_Color color{};
		if (i == 1)
		{
			color = SDL_Color{ 0,0,255,250 };
		}
		else
		{
			color = SDL_Color{ 255,0,0,250 };
		}

	
	 Renderer::GetInstance().FillSquare(m_usablePath[i].x * m_TileSize, m_usablePath[i].y * m_TileSize, m_TileSize,color);
	}

	for (const auto & path : m_usablePath)
	{


	}




}

void dae::AIComponent::Update()
{


	Node currentPos;
	//  //column 1
	currentPos.x = int(m_Self->GetLocalPosition().x ) / X_STEP;
	currentPos.y = int(m_Self->GetLocalPosition().y) / Y_STEP;

	//row 


	Node targetPos;

	//column
	targetPos.x = int(m_Target->GetLocalPosition().x) / X_STEP;
	targetPos.y = int(m_Target->GetLocalPosition().y) / Y_STEP;
	//row

	/*UpdatePathTimer += m_pSceneManager->GetDeltaTime();
	if (UpdatePathTimer >= 0.2f)
	{
	}*/

	
	m_usablePath = aStar(currentPos, targetPos);
	UpdatePathTimer = 0;
	std::cout << m_usablePath.size() << "\n";


	if (m_usablePath.size() > 1)
	{
		
		glm::vec2 targetNode =
		{
			float(m_usablePath[1].x * X_STEP),
			float(m_usablePath[1].y * Y_STEP)
		};


		glm::vec2 currentPos = m_Self->GetLocalPosition();

		glm::vec2 toTarget = targetNode - currentPos;
		float distance = glm::length(toTarget);


		const float snapThreshold = 0.05f;

		if (distance < snapThreshold)
		{
			m_Self->SetPosition(targetNode.x, targetNode.y);
		}
		else
		{
			// Move toward the target node
			glm::vec2 moveDir = toTarget / distance;
			float speed = m_Speed * m_pSceneManager->GetDeltaTime();
			glm::vec2 moveVec = moveDir * speed;

			m_Self->SetPosition(
				currentPos.x + moveVec.x,
				currentPos.y + moveVec.y
			);
		}

	}


}







//
//bool dae::AIComponent::HasArrived(Node& ghosts, Node& TargetNode)
//{
//
//	return ghosts.x == TargetNode.x && ghosts.y == ghosts.y;
//
//}

float dae::AIComponent::distanceBetweenPoints()
{
	float targetX = m_Target->GetWorldPosition().x;
	float targetY = m_Target->GetWorldPosition().y;
	float selfX = m_Self->GetWorldPosition().x;
	float selfY = m_Self->GetWorldPosition().y;

	float dx = targetX  - selfX ;
	float dy = targetY - selfY;

	// Calculate the sum of squares
	float sumOfSquares = dx * dx + dy * dy;

	float distance = std::sqrt(sumOfSquares);

	return distance;
}























//m_OldPosition = m_Self->GetLocalPosition();
//glm::vec3 newPosition = m_OldPosition + glm::vec3{10,0,0} * m_pSceneManager->GetDeltaTime();
//m_Self->SetPosition(newPosition.x, newPosition.y);



/////////////////////////////////////////////////////////////////////////////////////////////////


//const float targetX = 20.0f;
//const float targetY = 200.0f;

//m_OldPosition = m_Self->GetLocalPosition();

//// Calculate direction vector towards the target position (200, 200)
//glm::vec3 targetPosition(targetX, targetY, 0.0f); // Assuming z-coordinate is 0
//glm::vec3 direction = glm::normalize(targetPosition - m_OldPosition);

//// Define movement speed
//float moveSpeed = 10.f; // Adjust as needed

//// Calculate movement for this frame
//glm::vec3 movement = direction * moveSpeed * m_pSceneManager->GetDeltaTime();

//// Calculate new position by adding movement to the old position
//glm::vec3 newPosition = m_OldPosition + movement;

//// Check if the character is close enough to the target position
//float distanceToTarget = glm::distance(newPosition, targetPosition);
//if (distanceToTarget <= moveSpeed * m_pSceneManager->GetDeltaTime()) {
//    // If close enough, directly set the position to the target position
//    m_Self->SetPosition(targetX, targetY);
//}
//else {
//    // Otherwise, set the position to the new calculated position
//    m_Self->SetPosition(newPosition.x, newPosition.y);
//}

//


/////////////////////
//Go to target 

// m_OldPosition = m_Self->GetLocalPosition();

// // Assuming playerPosition represents the position of the player object
// glm::vec3 playerPosition = m_Target->GetLocalPosition(); // Assuming m_Player is a pointer to the player object

// // Calculate direction vector towards the player's position
// glm::vec3 direction = glm::normalize(playerPosition - m_OldPosition);

// // Define movement speed
// float moveSpeed = 10.0f; // Adjust as needed

// // Calculate movement for this frame
// glm::vec3 movement = direction * moveSpeed * m_pSceneManager->GetDeltaTime();

// // Calculate new position by adding movement to the old position
// glm::vec3 newPositions = m_OldPosition + movement;

// // Set the position to the new calculated position
//m_Self->SetPosition(newPositions.x, newPositions.y);


 ///////////////




	//char mapVisualized[X_MAX / X_STEP][Y_MAX / Y_STEP];

	// for (int y{ 0 }; y < Y_MAX / Y_STEP; y++) {
	// 	for (int x{ 0 }; x < X_MAX / X_STEP; x++) {
	// 		mapVisualized[x][y] = '.';

	// 		for (const auto& node : path) {
	// 			if (node.x == x && node.y == y) {
	// 				mapVisualized[x][y] = 'x';
	// 				break;
	// 			}
	// 		}
	// 		if (currentPos.x == x && currentPos.y == y) {
	// 			mapVisualized[x][y] = 'C';
	// 		}
	// 		if (targetPos.x == x && targetPos.y == y) {
	// 			mapVisualized[x][y] = 'T';
	// 		}
	// 		std::cout << mapVisualized[x][y];
	// 	}
	// 	std::cout << "\n";
	// }