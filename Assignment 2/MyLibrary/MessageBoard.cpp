#include "MessageBoard.h"

MessageBoard::MessageBoard()
{
}

MessageBoard::~MessageBoard()
{
}

void MessageBoard::sendMessage(string content, GameObject::GAMEOBJECT_TYPE type ) {
	message = content;
	if (type == GameObject::GO_CHIEF) {
		//priority = 10;
	}

}

void MessageBoard::getMessage()
{
	//string * read = messages.back();



}