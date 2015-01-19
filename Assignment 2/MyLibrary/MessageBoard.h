#include <iostream>
#include <string>
#include <vector>
#include "GameObject.h"
#include <algorithm>
using namespace std;

#define HELP "Help";
#define SHOOT "Shoot";
#define TAKECOVER "Take Cover";

struct Message
{
	Message(string Message, GameObject::GAMEOBJECT_TYPE sender, GameObject::GAMEOBJECT_TYPE receiver, int priority)
	{
		this->message = Message;
		this->sender = sender;
		this->receiver = receiver;
		this->priority = priority;
	}
	unsigned int priority;
	string message;
	GameObject::GAMEOBJECT_TYPE sender;
	GameObject::GAMEOBJECT_TYPE receiver;

	bool operator< (const Message& rhs)
	{
		return this->priority < rhs.priority;
	}

	bool operator> (const Message& rhs)
	{
		return this->priority > rhs.priority;
	}
};

class ShowMessages{
public:
	std::vector<Message> Messages;
	void NewMessage(Message theMessage)
	{
		if(Messages.size() >= 10)
		{
			Messages.erase(Messages.begin());
		}
		Messages.push_back(theMessage);
	}



	void RenderMessageBoard()
	{
	}

};

class MessageBoard {
public:
	MessageBoard(); // Initialise to no message
	~MessageBoard();

	std::vector<Message> themessages;

	void sendMessage(string content, GameObject::GAMEOBJECT_TYPE sender, GameObject::GAMEOBJECT_TYPE receiver, int priority);
	string getMessage(GameObject::GAMEOBJECT_TYPE recv);
	
	ShowMessages DebugMessage;
};

