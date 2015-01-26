#include "MessageBoard.h"

MessageBoard::MessageBoard()
{
}

MessageBoard::~MessageBoard()
{
}

void MessageBoard::sendMessage(string content, GameObject::GAMEOBJECT_TYPE sender, GameObject::GAMEOBJECT_TYPE receiver, int piority )
{
	Message newMessage(content, sender, receiver, piority);

	DebugMessage.NewMessage(newMessage);
	themessages.push_back(newMessage);
}

string MessageBoard::getMessage(GameObject::GAMEOBJECT_TYPE recv)
{
	string theReturn = "";
	std::vector<Message> theListofMessage;

	//Put everything relevent into the ListofMessages
	for(int i = 0; i < themessages.size(); i++)
	{
		if(themessages[i].receiver == recv)
		{
			theListofMessage.push_back(themessages[i]);
		}
	}

	if(!theListofMessage.empty())
	{
		//Sort according to priority
		std::sort(theListofMessage.begin(),theListofMessage.end());
		theReturn = theListofMessage[0].message;
	}
	return theReturn;

}