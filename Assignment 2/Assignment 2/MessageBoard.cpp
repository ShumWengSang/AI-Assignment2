#include "MessageBoard.h"
#include "AI.h"

MessageBoard::MessageBoard()
{
}

MessageBoard::MessageBoard(AI*theHandler):
	DebugMessage(theHandler)
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

void ShowMessages::DrawLineCube(int x, int y, int width, int height)
{


	glLineWidth(5);
	glBegin(GL_LINE_STRIP);
	{
		glColor3f(1, 1, 1);
		glVertex2f(x, y);
		glVertex2f(x, y + height);
		glVertex2f(x + width, y + height);
		glVertex2f(x + width, y);
		glVertex2f(x, y);
		//glLineWidth(1);
	}
	glEnd();
	glBegin(GL_LINES);
	{
		glColor3f(1, 1, 1);
		glVertex2f(x + width / 4, y + height);
		glVertex2f(x + width / 4, y + height - height/ 3);

		glVertex2f(x + width / 2, y + height);
		glVertex2f(x + width / 2, y + height - height/ 3);

		glVertex2f(x + width * 3 / 4, y + height);
		glVertex2f(x + width * 3 / 4, y + height - height/ 3);

		glVertex2f(x , y + height - height/ 3);
		glVertex2f(x + width, y + height - height/ 3);

	}
	glEnd();

	glBegin(GL_QUADS);
	{
		glEnable (GL_BLEND);
		glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(0.5, 0.5, 0.0, 0.4);

		glVertex2f(x , y + height);
		glVertex2f(x + width , y + height);	
		glVertex2f(x + width , y );
		glVertex2f(x , y);

		glDisable(GL_BLEND);
	}
	glEnd();


	aiHandler->RenderStringOnScreen(x + width -  width * 3 / 4 - 10 , y + height - height  / 3 + 2, "Text");
	aiHandler->RenderStringOnScreen(x + width -  width * 2 / 4 - 10 , y + height - height  / 3 + 2, "To");
	aiHandler->RenderStringOnScreen(x + width -  width * 1 / 4 - 10 , y + height - height  / 3 + 2, "From");

	if(Messages.size() >= 1)
	{
		if(Messages.back().message.size() > 10)
		{
			static bool done = true;
			static std::string theString = Messages.back().message;

			Messages.back().message.insert(10,"\n");
		}
		aiHandler->RenderStringOnScreen(x + width -  width * 3 / 4 - 10 , y + height - height * 2 / 3 + 2, Messages.back().message.c_str());
		aiHandler->RenderStringOnScreen(x + width -  width * 2 / 4 - 10 , y + height - height * 2 / 3 + 2, Messages.back().StringRecv.c_str());
		aiHandler->RenderStringOnScreen(x + width -  width * 1 / 4 - 10 , y + height - height * 2 / 3 + 2, Messages.back().StringSender.c_str());
	}

	//aiHandler->RenderStringOnScreen(x + width - (x + width * 3 / 4), y + height - height  / 3 , "Text");
	//aiHandler->RenderStringOnScreen(x + width - (x + width * 2 / 4) , y + height - height  / 3 , "To");
	//aiHandler->RenderStringOnScreen(x + width - (x + width * 1 / 4)  , y + height - height  / 3 , "From");


	glLineWidth(1);
}