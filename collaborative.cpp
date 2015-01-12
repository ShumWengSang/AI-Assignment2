/**************************************************************************/
// FSM Variant : Collaborative - Parallel & Synchronized 
// Description : FSM-FSM Collaborate Based On Various Win-Lose Situations
/**************************************************************************/
#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int PATROL  = 1; // Searching For Enemy
const int FIGHT   = 2; // Fighting enemy
const int COVER   = 3; // Cover Fire For Front Line 
const int WIPEOUT = 4; // All troop soldiers killed
const int REPLACE = 5; // Cover troop replacing front line

const int NIL     = 6; // No win/lose situation yet
const int WIN     = 7; // Front line wins fight
const int LOSE    = 8; // Front line loses fight

int outcome;        // win or lose fight
int state1;         // First troop
int state2;         // Second troop
bool seenEnemy;     // Flag enemy sighted
bool begin = true;  // Flag start of application

// Central Location Where Troops Communicate Thru'
class MessageBoard {
public:
string message;
MessageBoard():message("Nil"){} // Initialise to no message
};

// For military Troop Object
class Troop {
public:
	string label; // Name For Troop
	int soldiers; // Number of Soldiers
	string role;  // Front line or Cover 
	// Constructor
	Troop(string mlabel,string mrole, int msoldiers){
	  if (begin){ // Start of Application
		 cout << "Running Collaborative FSMs - Parallel & Synchronized ...\n" << endl;
	     begin = false;
      }
	  // Set Troop Data
	  label = mlabel; role = mrole; soldiers = msoldiers;
	  cout << " Troop " << label << " created ! , Role = " << role << ", Soldier = "<< soldiers << endl;
	}
	// Pass Message To Message Board
	void SetMessage(MessageBoard *mb,string mmessage){mb->message=mmessage;}
	// Troop Get Message From Message Board
	string GetMessage(MessageBoard *mb){return mb->message;}
	// Token Function Showing Current Activity
	void Patrol(){cout << " Troop " << label << " patrolling...." << endl;}
	void Fight() { cout << " Troop " << label << " in front line fighting enemy ....\n" << endl;}
	void Cover() { cout << " Troop " << label << " covering fire for front line ....\n" << endl;}
};
// Create Troops With Specification
Troop troop1("#1","Front",3); // label, role, number of soldiers
Troop troop2("#2","Cover",20);
// Create Message Board
MessageBoard mb;

// FSM Process
void Process(){
	// For First FSM or Troop
	switch(state1){
		case PATROL  :  if (seenEnemy) {
							troop1.SetMessage(&mb,"Enemy Sighted");
							cout << "\n ENEMY SIGHTED ! \n" << endl;
							state1 = FIGHT;
						}
					    break;
		case FIGHT   :  if (outcome==WIN) {
							troop1.SetMessage(&mb,"Win");
							cout << " Enemy wiped out ! \n" << endl;
							state1 = PATROL;
							outcome=NIL;
							seenEnemy = false;
						}
						if (outcome==LOSE) {
							troop1.SetMessage(&mb,"Lose");
							state1 = WIPEOUT;
							troop1.soldiers = 0;
						    troop1.role="Dead";	
						 	outcome=NIL;
							cout << " Troop "<< troop1.label << " in front line WIPED OUT ! \n" << endl;
						}
						break;
	}
	// For Second FSM  or Troop
	switch(state2){
		case PATROL  :  if (troop2.GetMessage(&mb)=="Enemy Sighted") 
							state2 = COVER;
						break;
		case FIGHT	 :  if (outcome==WIN) {
							troop2.SetMessage(&mb,"Nil");
							state2 = PATROL;
							cout << " Enemy wiped out ! \n" << endl;	
							outcome=NIL;
						}
						if (outcome==LOSE) {
							troop2.SetMessage(&mb,"Nil");
							outcome=NIL;
							state2 = WIPEOUT;
							troop2.role="Dead";
							troop2.soldiers=0;
							cout << " Troop "<< troop2.label << " in front line WIPED OUT ! \n" << endl;							
						}
						break;
		case COVER   :  if (troop2.GetMessage(&mb)=="Win") {
							state2 = PATROL;
							troop2.SetMessage(&mb,"Nil");
						}
						if (troop2.GetMessage(&mb)=="Lose") {
							state2 = FIGHT;
							troop2.role="Front";
							cout << " Troop " << troop2.label << " covering fire, replaces front line ....\n" << endl;
							troop2.SetMessage(&mb,"Nil");
						}
						break;

	}
	// React To FSM States
	if (state1==PATROL) troop1.Patrol();
	if (state1==FIGHT)  troop1.Fight();
	if (state2==PATROL) troop2.Patrol();
	if (state2==FIGHT)  troop2.Fight();
	if (state2==COVER)  troop2.Cover();
}

// Initializes Application
void Init(){
  seenEnemy = false; // Enemy Hasn't Appear
  state1 = PATROL;   // Default Troop activity
  state2 = PATROL;
  outcome = NIL;	    // No Win-Lose Situation At Hand
  cout << endl;	
  
  // React To FSM States - Initial response
  if (state1==PATROL) troop1.Patrol();
  if (state1==FIGHT)  troop1.Fight();
  if (state2==PATROL) troop2.Patrol();
  if (state2==FIGHT)  troop2.Fight();
  if (state2==COVER)  troop2.Cover();

}
// Print Status Of Troops
void ListDetail(){
  cout << " STATUS : " <<endl;
  cout << " Troop " << troop1.label << "  , Role = " << troop1.role << ", Soldier = "<< troop1.soldiers << endl;
  cout << " Troop " << troop2.label << "  , Role = " << troop2.role << ", Soldier = "<< troop2.soldiers << endl;
}
// Various Scenarios Of Battle
void SimulateEnemySighted(){ seenEnemy = true;}
void SimulateWin() { outcome = WIN;}
void SimulateLose(){ outcome = LOSE;}

// Various Simulation Of Win-Lose Scenarios
void SimulationLoseWin(){
  cout << " ** Simulate LOSE-WIN situation **\n" << endl;          
  SimulateLose();
  Process();
  SimulateWin();
  Process();
  cout << "\n YOU WIN THE WAR !\n"<< endl;
  ListDetail();
}
void SimulationWin(){
  cout << " ** Simulate WIN situation **\n" << endl;  
  SimulateWin();
  Process();
  cout << "\n YOU WIN THE WAR !\n"<< endl;
  ListDetail();
}
void SimulationLoseLose(){
  cout << " ** Simulate LOSE-LOSE situation **\n" << endl;      
  SimulateLose();
  Process();
  SimulateLose();
  Process();
  cout << " YOU LOSE THE WAR !\n"<< endl;
  ListDetail();
}

// Entry Point Of Application
int main(){
  Init(); // Initialises Application
  SimulateEnemySighted(); // Simulate Enemy Appearing
  Process(); 
  // Various Simulations Scenarios
//  SimulationWin();
  SimulationLoseWin();
  //SimulationLoseLose();
  cout << endl;
  cin.get();
  return 0;
}
