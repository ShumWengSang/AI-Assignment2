#include <iostream>
#include <string>
#include <vector>
#include "GameObject.h"
using namespace std;

#define HELP "Help";
#define SHOOT "Shoot";
#define TAKECOVER "Take Cover";

class MessageBoard {
public:
	MessageBoard(); // Initialise to no message
	~MessageBoard();

	//int priority;
	string message;

	std::vector<string *> messages;

	void sendMessage(string content, GameObject::GAMEOBJECT_TYPE type);
	void getMessage();
};
