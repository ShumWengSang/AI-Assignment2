#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "GameObject.h"
#include "freeglut.h"
#include <algorithm>

extern class AI;


using namespace std;

#define HELP "Help";
#define SHOOT "Shoot";
#define TAKECOVER "Take Cover";
#define REPLACE "Replace"; //For when the chief dies and another takes over


struct Message
{
	Message(string Message, GameObject::GAMEOBJECT_TYPE sender, GameObject::GAMEOBJECT_TYPE receiver, int priority)
	{
		this->message = Message;
		this->sender = sender;
		this->receiver = receiver;
		this->priority = priority;

		if(sender == GameObject::GO_POLICE)
		{
			StringSender = "POLICE";
		}
		else if(sender == GameObject::GO_CHIEF)
		{
			StringSender = "CHIEF";
		}
		else if(sender == GameObject::GO_LOOKOUT)
		{
			StringSender = "LOOKOUT";
		}
		else if(sender == GameObject::GO_ROBBER)
		{
			StringSender = "Robber";
		}

		if(receiver == GameObject::GO_POLICE)
		{
			StringRecv = "POLICE";
		}
		if(receiver == GameObject::GO_CHIEF)
		{
			StringRecv = "CHIEF";
		}
		if(receiver == GameObject::GO_ROBBER)
		{
			StringRecv = "ROBBER";
		}
		if(receiver == GameObject::GO_LOOKOUT)
		{
			StringRecv = "LOOKOUT";
		}
	}
	unsigned int priority;
	string message;
	GameObject::GAMEOBJECT_TYPE sender;
	GameObject::GAMEOBJECT_TYPE receiver;
	std::string StringSender;
	std::string StringRecv;
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
	ShowMessages()
	{};
	ShowMessages(AI* theHandler)
	{
		this->aiHandler = theHandler;
	}
	std::vector<Message> Messages;

	void NewMessage(Message theMessage)
	{
		if(Messages.size() >= 10)
		{
			Messages.erase(Messages.begin());
		}
		Messages.push_back(theMessage);
	}

	void DrawLineCube(int x, int y, int width, int height);

	void RenderMessageBoard(int x, int y, int width, int height)
	{
		DrawLineCube(x,y,width,height);

	}

	AI*aiHandler;
};

class MessageBoard {
public:
	MessageBoard(); // Initialise to no message
	MessageBoard(AI*theHandler);
	~MessageBoard();

	std::vector<Message> themessages;

	void sendMessage(string content, GameObject::GAMEOBJECT_TYPE sender, GameObject::GAMEOBJECT_TYPE receiver, int priority);
	string getMessage(GameObject::GAMEOBJECT_TYPE recv);
	
	ShowMessages DebugMessage;
};

