#include "Team.h"
#include"Match.h"
#include "Player.h"
#include <fstream>
#include <queue>
Team::Team()
{
	this->Goals = 0;
	this->OwnGoals = 0;
	this->Points = 0;
}
void Team::Load_Teams()
{
	queue <string> Teams_Info;
	string word;
	ifstream TeamFile("Teams.txt");
	if (TeamFile.is_open())
	{
		Player p;
		p.Load_Players();
		
		while (!TeamFile.eof() && TeamFile.peek() != std::ifstream::traits_type::eof())
		{
			TeamFile >> word;
			Teams_Info.push(word);
		}
		TeamFile.close();
		while (!Teams_Info.empty())
		{
			Team T;
			T.Name = Teams_Info.front();
			Teams_Info.pop();
			T.ID_Team = stoi(Teams_Info.front());
			Teams_Info.pop();
			T.OwnGoals = stoi(Teams_Info.front());
			Teams_Info.pop();
			T.Goals = stoi(Teams_Info.front());
			Teams_Info.pop();
			T.Captain = Teams_Info.front();
			Teams_Info.pop();
			T.Points = stoi(Teams_Info.front());
			Teams_Info.pop();
			vector <  Player >::iterator it;
			for ( it = p.Players.begin(); it != p.Players.end(); it++)
			{
				if (it->TeamName == T.Name)
				{
					Player test;
					test.Age = it->Age;
					test.Name = it->Name;
					test.Rank = it->Rank;
					test.TeamName = it->TeamName;
					
					test.Player_Number = it->Player_Number;
           T.Team_Members.insert(make_pair(test.Player_Number, test));
				}
					
			}
			Teams.insert(make_pair(T.ID_Team, T));
			if (Teams_Info.size() == 1)
				break;
		}
	}
	
}
void Team::Display_Team_Info()
{
	Load_Teams();
	for (auto i = Teams.begin(); i != Teams.end(); i++)
	{
		Player p;
		
		cout << "Team Name : " << i->second.Name << endl;
		cout << "Team ID : " << i->second.ID_Team << endl;
		cout << "Team Score :" << i->second.OwnGoals << endl;
		cout << "Team Captain :" << i->second.Captain << endl;
		if (i->second.Team_Members.size() != 0)
		{
			cout << "Team Members :" << endl;
			p.Display_Team_member(i->second.Name, 0);
		}
		else
			cout << "The Team has no Members" << endl;
		cout << "........................................................................... " << endl;
	}
}
void Team::Display_team_player()
{
	Load_Teams();
	string Name;
	cout << "Enter Team Name" << endl;
	cin >> Name;
	for (auto i = Teams.begin(); i != Teams.end(); i++)
	{
		if (i->second.Name == Name)
		{
			cout << "Team Players : " << endl;
			map<int, Team> ::iterator it;// to see map of Teams
			i->second.Team_Members;
			map<int, Player> ::iterator it1; //iterator in list of players to see player in each team
			it1 = i->second.Team_Members.begin();
			it1->second.Display_Team_member(it1->second.TeamName , 0);
			it1++;
			break;
		}
	}
}
void Team::Add_Team()
{
	Load_Teams();
	ofstream Teams_File;
	Teams_File.open("Teams.txt", ios::out | ios::app);
	Team t;
	cout << "Enter Team Name : " << endl;
	cin >> t.Name;
	Teams_File << t.Name << "\t";
	
	string s;
	cout << "Enter Team ID :" << endl;
	cin >> s;
	while (true)
	{
		
		if (checkNom(s))
			t.ID_Team = stoi(s);
		else
		{
			cout << "Error Enter Int Data" << endl;
			cin >> s;
		}
		t.ID_Team = stoi(s);
		auto it = Teams.find(t.ID_Team);
		if (it != Teams.end())
		{
			cout << "This Team ID Already Exist" << endl;
			cin >> s;
		}
		else
			break;
	}
	t.ID_Team = stoi(s);
		Teams_File << t.ID_Team << "\t";
		Teams_File << t.OwnGoals << "\t";
		t.Goals = 0;
		Teams_File << t.Goals << "\t";
		cout << "Enter Team Captain \n";
		cin >> t.Captain;
		Teams_File << t.Captain << "\t";//"\t"; 
		Teams_File << t.Points << endl;
		
		char ch;
		while (true)
		{
			cout << "Press (y) To Add Team Player :  (n) To Skip \n";
			cin >> ch;
			if (ch == 'n' || ch == 'N')
				break;
			Player p;
			p.Enter_data();
			t.Team_Members.insert(make_pair(p.Player_Number, p));
			p.Players.push_back(p);
		}
		Teams.insert(make_pair(t.ID_Team, t));

	
}
void Team::Search_for_team()
{
	Load_Teams();
	bool found = 0;
	int id_search;
	string name_search;
	cout << "Enter ID & Name For team You want to search " << endl;
	string s, s1;
	cin >> s >> name_search;
	while (checkNom(s))
	{
		cout << "Error On Type Enter Only Num !!" << endl;
		cin >> s >> name_search;
	}
	id_search = stoi(s);

	map<int, Team> ::iterator it;
	for (it = Teams.begin(); it != Teams.end(); it++)
	{
		if (it->first == id_search && it->second.Name == name_search)
		{
			cout << "Name OF team You want is : " << Teams[id_search].Name << endl;
			cout << "ID OF team You want is : " << Teams[id_search].ID_Team << endl;
			cout << "Capitan OF team You want is : " << Teams[id_search].Captain << endl;
			cout << "Players OF team You want is : " << endl;
			map<int, Player> ::iterator it1; //iterator in list of players to see player in each team 
			it1 = it->second.Team_Members.begin();
			it1->second.Display_Team_member(it1->second.TeamName, 0);
			it1++;
			found = true;
			break;
		}
	}
	if (!found)
		cout << "Not Found !!" << endl;
}
void Team::Update_team_information()
{
	Load_Teams();
	Display_Team_Info();
	int id_search;
	string name_search;
	int ch;
	string s;

	cout << "Enter Team Name & ID Of team : " << endl;
	cin >> name_search >> s;
	while (checkNom(s) == false)
	{
		cout << "Error On Type Enter Only Num !!" << endl;
		cin >> s >> name_search;
	}
	id_search = stoi(s);
	cout << "What you want Update : " << endl;
	cout << " update Name press 1" << endl;
	cout << " update ID OF team  press 2" << endl;
	cout << " update Capitan OF team  press 3" << endl;
	cout << " update Players OF team  press 4" << endl;
	cin >> ch;
	switch (ch)
	{
	case 1:
	{
		string new_s;
		cout << "Enter New Name" << endl;
		cin >> new_s;
		for (auto i = Teams.begin(); i != Teams.end(); i++)
			if (i->second.Name == name_search   && i->second.ID_Team == id_search)
				i->second.Name = new_s;
		break;
	}
	case 2:
	{
		int  new_s;
		cout << "Enter New ID" << endl;
		cin >> new_s;
		for (auto i = Teams.begin(); i != Teams.end(); i++)
			if (i->second.Name == name_search   && i->second.ID_Team == id_search)
				i->second.ID_Team = new_s;
		break;
	}
	case 3:
	{

		string  new_s;
		cout << "Enter New Captain" << endl;
		cin >> new_s;
		for (auto i = Teams.begin(); i != Teams.end(); i++)
			if (i->second.Name == name_search   && i->second.ID_Team == id_search)
				i->second.Captain = new_s;
		break;
	}
	case 4:
	{
		Player p;
		p.Update_Player();
		break;
	}
	}
	Put_Data_in_file();
}
void Team::Display_team_Order(string n)
{
	Load_Teams();
	for (auto i = Teams.begin(); i != Teams.end(); i++)
	{
		if (i->second.Name == n) // Check Team Name From Function Display_3_Frist_Teams
		{	
			cout << "Team Name : ";
			cout << i->second.Name << endl;
			cout << "Team Num  : ";
			cout << i->second.ID_Team << endl;
		}
	}
} // Display Spacific Team From Function Display_3_Frist_Teams
void Team::Display_Matches()
{
	string s;
	Match m;
	m.Load_Matches();
	Load_Teams();
	cout << "Enter Name Team You Want To Display : ";
	cin >> s;
	for (auto it = m.matches.begin(); it != m.matches.end(); it++)
		if (it->second.team1 == s || it->second.team2 == s)
		{
			cout << "ID :" << it->second.ID_Match << endl;
			cout << "Date :" << it->second.Date << endl;
			cout << "Footbool referee :" << it->second.Footbool_referee << endl;
			cout << "Stadium Name :" << it->second.Stadium_Name << endl;
			cout << it->second.team1 << "(" << it->second.Score_Team_One << ")" << " - " << it->second.team2 << "(" << it->second.Score_Team_two << ")" << endl;
			cout << "_________________________________________________________" << endl;
		}

}

void Team::Update_Total_Score(string s, int x) //Help Function To increase Goals 
{
	Load_Teams();
	for (auto i = Teams.begin(); i != Teams.end(); i++)
		if (i->second.Name == s)
			i->second.OwnGoals += x;
	Put_Data_in_file();
}
void Team::Update_Points(string s, int x, int x1) //Help Function To increase Goals 
{
	Load_Teams();
	for (auto i = Teams.begin(); i != Teams.end(); i++)
		if (i->second.Name == s)
		{
			if (x > x1)
				i->second.Points += 3;
			else if (x == x1)
				i->second.Points += 1;
			else
				continue;
		}
	Put_Data_in_file();
}
void Team::Update_GoalKeepar_Score(string s, int x)
{
	Load_Teams();
	string n = s;
	int a = x;
	for (auto i = Teams.begin(); i != Teams.end(); i++)
		if (i->second.Name == n)
			i->second.Goals += a;
	Put_Data_in_file();
}
void Team::Put_Data_in_file() //Save Data In File After Any Operation 
{
	ofstream Teams_File;
	Teams_File.open("Teams.txt", ios::out);
	for (auto it = Teams.begin(); it != Teams.end(); it++)
	{
		Teams_File << it->second.Name << "\t";
		Teams_File << it->second.ID_Team << "\t";
		Teams_File << it->second.OwnGoals << "\t";
		Teams_File << it->second.Goals << "\t";
		Teams_File << it->second.Captain << "\t";
		Teams_File << it->second.Points << endl;
	}
	Teams_File.close();
}

void Team::Display_team_detailed_scores()
{
	Match m;
	Load_Teams();
	m.Load_Matches();
	string s;
	cout << "Enter The Team Name You Want the details of : " << endl;
	cin >> s;
	for (auto it = Teams.begin(); it != Teams.end(); it++)
	{
		if (it->second.Name == s)
		{
			cout << "The Total Score of The " << s << " Team is : " << it->second.OwnGoals << endl;
			cout << "Divided to : " << endl;
			for (auto i = m.matches.begin(); i != m.matches.end(); i++)
			{
				if (s == i->second.team1 || s == i->second.team2)
				{
					if (s == i->second.team1)
					{
						cout << i->second.Score_Team_One << " Score on The Match with " << i->second.team2 << endl;
						cout << "The final score of match was" << i->second.Score_Team_One << " : " << i->second.Score_Team_two << endl;
						if (i->second.Score_Team_One > i->second.Score_Team_two)
						{
							cout << "The Winner was : " << i->second.team1 << endl;
							cout << "The Loser was : " << i->second.team2 << endl;
						}
						else
						{
							cout << "The Winner was : " << i->second.team2 << endl;
							cout << "The Loser was : " << i->second.team1 << endl;
						}
						cout << "on Date : " << i->second.Date << endl;;
						cout << "on Stadium Match : " << i->second.Stadium_Name << endl;
						cout << "Football Referee was :" << i->second.Footbool_referee << endl;
						cout << "________________________________________________________" << endl;
					}
					else if (s == i->second.team2)
					{
						cout << i->second.Score_Team_two << " Score on The Match with " << i->second.team1 << endl;
						cout << "The final score of match was" << i->second.Score_Team_two << " : " << i->second.Score_Team_One << endl;
						if (i->second.Score_Team_two > i->second.Score_Team_One)
						{
							cout << "The Winner was : " << i->second.team2 << endl;
							cout << "The Loser was : " << i->second.team1 << endl;
						}
						else
						{
							cout << "The Winner was : " << i->second.team1 << endl;
							cout << "The Loser was : " << i->second.team2 << endl;
						}
						cout << "on Date : " << i->second.Date << endl;;
						cout << "on Stadium Match : " << i->second.Stadium_Name << endl;
						cout << "Football Referee was :" << i->second.Footbool_referee << endl;
						cout << "________________________________________________________" << endl;
					}
				}
			}
		}
	}
}
/* General Functions */
bool sortbyPoints(const pair<int, Team> &a, const pair<int, Team> &b)
{
	return (a.second.Points > b.second.Points);
}// To Compare To Sort Teams by points
bool sortbyOwnGoals(const pair<int, Team> &a, const pair<int, Team> &b)
{
	return (a.second.OwnGoals > b.second.OwnGoals);
}// To Compare To Sort Teams by Goals
bool sortGoalkeepers(const pair<int, Team> &a, const pair<int, Team> &b)
{
	return a.second.Goals < b.second.Goals;
}
void Display_3_Frist_Teams_By_Points()
{
	Team s;
	s.Load_Teams();
	vector < pair <int, Team> > Sor;
	map<int, Team>::iterator it2;
	for (it2 = s.Teams.begin(); it2 != s.Teams.end(); it2++)
	{
		Sor.push_back(make_pair(it2->first, it2->second)); // Push Map in Vector To Sort 
	}
	sort(Sor.begin(), Sor.end(), sortbyPoints); // Sort Here 
	for (int j = 0; j < Sor.size(); j++)
	{
		cout << j + 1 << " - "; // To Write The Order Of Team 
		s.Display_team_Order(Sor[j].second.Name);
	}
}// To Display First Three Team in League
 /*Sort Teams By Goals*/
void Display_3_First_Teams_By_Total_Score()
{
	Team s;
	s.Load_Teams();
	vector <pair <int, Team> > Sor;
	map<int, Team>::iterator it2;
	for (it2 = s.Teams.begin(); it2 != s.Teams.end(); it2++)
	{
		Sor.push_back(make_pair(it2->first, it2->second)); // Push Map in Vector To Sort 
	}
	sort(Sor.begin(), Sor.end(), sortbyOwnGoals); // Sort Here 
	for (int j = 0; j < Sor.size(); j++)
	{
		cout << j + 1 << " - "; // To Write The Order Of Team 
		s.Display_team_Order(Sor[j].second.Name);
	}
}// To Display First Three Team in League
void Display_3_First_GoalKeepers()
{
	Team s;
	s.Load_Teams();
	vector <pair <int, Team> > Sor;
	map<int, Team>::iterator it2;
	for (it2 = s.Teams.begin(); it2 != s.Teams.end(); it2++)
	{
		Sor.push_back(make_pair(it2->first, it2->second)); // Push Map in Vector To Sort 
	}
	sort(Sor.begin(), Sor.end(), sortGoalkeepers); // Sort Here 
	Player p;
	for (int j = 0; j < 3; j++)
	{
		cout << j + 1 << " - " << Sor[j].second.Name << endl; // To Write The Order Of Team 
		p.Display_Team_member(Sor[j].second.Name , 1);
	}
}
void Team::DisPlay_Team_Match_With_Date()
{
	Load_Teams();
	Match M;
	M.Load_Matches();
	string s, s1;
	vector <Match> Played, notPlayed;
	cout << "Enter Team Name & Date " << endl;
	cin >> s >> s1;
	while (!validDate(s1))
	{
		cout << "InValid Date Enter Valid Date" << endl;
		cin >> s1;
	}
	string ch;
	int y = 0, m = 0, d = 0;
	for (int i = 0; i < s1.size(); i++)
	{
		ch += s1[i];
		if (i == 1)
		{
			d = stoi(ch);
			ch.clear();
			i++;
		}
		if (i == 4)
		{
			m = stoi(ch);
			ch.clear();
			i++;
		}
		if (i == 9)
		{
			y = stoi(ch);
			ch.clear();
			break;
		}
	}
	ch.clear();
	for (auto it1 = M.matches.begin(); it1 != M.matches.end(); it1++)
	{
		if (s == it1->second.team1 || s == it1->second.team2)
		{
			int Y = 0, Mo = 0, D = 0;
			for (int i = 0; i < it1->second.Date.size(); i++)
			{
				ch += it1->second.Date[i];
				if (i == 1)
				{
					D = stoi(ch);
					ch.clear();
					i++;
				}
				if (i == 4)
				{
					Mo = stoi(ch);
					ch.clear();
					i++;
				}
				if (i == 9)
				{
					Y = stoi(ch);
					ch.clear();
					break;
				}
			}
			if (Y < y)
				Played.push_back(it1->second);
			else if (Mo < m)
				Played.push_back(it1->second);
			else if (D < d)
				Played.push_back(it1->second);
			else if (Y == y && Mo == m && D == d)
				Played.push_back(it1->second);
			else
				notPlayed.push_back(it1->second);
		}
	}
	cout << "Held Matches : " << endl;
	for (int i = 0; i < Played.size(); i++)
	{
		cout << Played[i].ID_Match << "\t" << Played[i].team1 << "\t";
		cout << Played[i].Score_Team_One << "\t" << Played[i].team2 << "\t";
		cout << Played[i].Score_Team_two << "\t" << Played[i].Date << endl;
		cout << "_______________________________________" << endl;
	}
	cout << "TO Be Held Matches : " << endl;
	for (int i = 0; i < notPlayed.size(); i++)
	{
		cout << notPlayed[i].ID_Match << "\t" << notPlayed[i].team1 << "\t";
		cout << notPlayed[i].Score_Team_One << "\t" << notPlayed[i].team2 << "\t";
		cout << notPlayed[i].Score_Team_two << "\t" << notPlayed[i].Date << endl;
		cout << "_______________________________________" << endl;
	}

}

Team::~Team()
{
}
