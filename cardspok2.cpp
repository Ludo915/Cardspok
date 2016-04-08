//cards.cpp
#include <list>
#include <iterator>
#include <string>
#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include "cardspok.h"
#include <time.h>
#include "random.h"
#include <numeric>
#include <functional>
#include <stdio.h>
#include "Console.h"
#include <cmath>

using namespace std ;
using std::list;
namespace con = JadedHoboConsole;


Card::Card (suits sv, unsigned int rv)
: rank(rv),suit(sv)
{
}

Card::Card(const Card& orig)
: rank(orig.rank), suit(orig.suit)
{
}
Card::~Card()
{
}
Card& Card:: operator = (const Card& rhs)

{
	if( this != &rhs)
{ 
	rank = rhs.rank;
	suit= rhs.suit;
}
return *this;
}

unsigned int Card:: GetRank() const
{
	return rank;
}
void Card::SetRank(unsigned int rv)
{ 
	assert ((rv>0)&&(rv<=rank_max));
	rank=rv;
}

suits Card:: GetSuit() const
{return suit;
}
void Card:: SetSuit(suits sv)
{
	suit = sv;
}


void Card::Insert (ostream& out) const
{
	switch(rank) {
	case 1:out<<"Ace"; break;
	case 11:out<<"Jack"; break;
	case 12:out<<"Queen"; break;
	case 13: out<<"King"; break;
	default: out<<rank;break;}

switch (suit)
{
	case spade:out<<" of Spades"; break;
	case heart:out<<" of Hearts"; break;
	case diamond:out<<" of Diamonds"; break;
	case club:out<<" of Clubs"; break;
}
}



ostream& operator <<(ostream& out, const Card& aCard)
{	aCard.Insert(out);
	return out;
}



Card Deck:: Draw()
{
	assert (cards.size()>0);
	randomInteger randomizer;
	int removedCard=randomizer(cards.size());
	Card drawn_card=cards[removedCard];
	cards[removedCard]=cards.back();
	cards.pop_back();
	
	
	return drawn_card;
}





Deck::Deck()
{
	for(int i=1; i<=rank_max; i++)
	{
		Card c1(diamond, i);
		Card c2(spade, i);
		Card c3(heart, i);
		Card c4(club, i);
		cards.push_back(c1);
		cards.push_back(c2);
		cards.push_back(c3);
		cards.push_back(c4);
	}
}

Deck::Deck(const Deck& orig)
{
operator=(orig);
}

Deck::~Deck()
{

}

Deck&Deck::operator=(const Deck& rhs)
{
	if (this != & rhs)
	{cards= rhs.cards;
	}
	return *this;
}

void Deck::shuffle ()
{
	randomInteger randfunc;
	random_shuffle(cards.begin(),cards.end(),randfunc);
}

ostream& operator <<(ostream& out, const Deck& aDeck)
{
	return out;
}
	
Player::Player()
{

}

Player::~Player()
{

}

Player::Player(hands hd)
:hand(hd)
{

}
Player::Player(const Player& orig)
:hand(orig.hand)
{

}

Player& Player::operator=(const Player& rhs)
{
	if(this!=&rhs)
	{
		hand=rhs.hand;
	}
	return *this;
}
hands Player::GetHand() const
{return hand;}

void Player::SetHand(hands hd)
{
	hand=hd;
}
void Player::Insert (ostream& out) const
{
	switch(hand)
	{
	case Height: out<<"Height"; break;
	case Pair:out<<"Pair"; break;
	case DoublePair:out<<"DoublePair"; break;
	case Full: out<<"Full"; break;
	case FullHouse: out<<"FullHouse"; break;
	case RoyalFlush: out<<"RoyalFlush"; break;
	case Straight: out<<"Straight"; break;
	}
}
ostream& operator <<(ostream& out, const Player& aPlayer)
{
	return out;
}

void remove_zeros(vector<int>& cont)
{    
	cont.erase(remove(cont.begin(), cont.end(),9000000), cont.end());
}

int Reste(int a, int b)
{
	int y;
	y= a - (a/b)*b;
	return y;
}


int main()
{



std::vector<string> PlayerType;
string HumanComputer;
string action;
int bet;
int numberofplayers;	
int walletsize;										//initial wallet size
int Pot;
cout <<"\n";
cout <<con::fg_gray<<"How many Players in Game?";
cin >> numberofplayers;
cout <<"\n";
for (int o=0;o<numberofplayers;o++)
{
cout <<con::fg_magenta<<"Player"<<o<<con::fg_gray<<" Type: Human or Computer?";
cin>>HumanComputer;
cout<<"\n";
PlayerType.push_back(HumanComputer);
};

cout<<"How much are you willing to play?";
cin>>walletsize;

float ProbERROR;
float PairProbError;
float DoublePairProbError;
float FullProbError;
float FullHouseProbError;
float StraightProbError;
float FourOfAKindProbError;
int PAIRCOUNT;
int FLUSHCOUNT;
int DOUBLEPAIRCOUNT;
int FULLCOUNT;
int FULLHOUSECOUNT;
int STRAIGHTCOUNT;
int FOUROFAKINDCOUNT;
int HandReorganizer;
int breaker;
int BetIncrement;
int loopcount;
int loopcount2;
int winnerfound;
int PrimaryPot;
int PIGnotAllIn;
int IndexesAllInsorted;
std::vector<Card> PlayerCards;						
std::vector<Card> TableCards;
std::vector<Card> hands;	
std::vector<Card> cardsCOPY;
std::vector<vector<Card>> player(numberofplayers);	//contains all player hands
std::vector<int> PIGstatusTEMP;
std::vector<int> MIGTEMP;
std::vector<int> flush(numberofplayers);
std::vector<int> WALLETSIZE;
std::vector<int> PossibleWinner;
std::vector<int> Wallet;
std::vector<int> MIG;								//Player Money In Game vector
std::vector<int> PIGstatus;							//Player status vector
std::vector<int> PIGsorted;
std::vector<int> sumspades(numberofplayers); 
std::vector<int> sumhearts(numberofplayers);
std::vector<int> sumdiamonds(numberofplayers);
std::vector<int> sumclubs(numberofplayers);
std::vector<int> AllIn(numberofplayers);
std::vector<int> AllInsorted(numberofplayers);
std::vector<int>::iterator MIGMAX;
std::vector<int>::iterator::difference_type OutOfGame;
std::vector<int>::iterator::difference_type HaveFolded;
std::vector<int>::iterator::difference_type HaveFoldedBefore;
std::vector<int>::iterator::difference_type StillInGame;
std::vector<vector<int>>::iterator PossibleWinnerPointsMAX;
std::vector<vector<int>> Ranks(numberofplayers);	//contains the Rank of all theCards in a Players hand
std::vector<vector<int>> spades(numberofplayers);	//boolean matrice that checks for cards of suit spade in a player's hand
std::vector<vector<int>> hearts(numberofplayers);
std::vector<vector<int>> diamonds(numberofplayers);
std::vector<vector<int>> clubs(numberofplayers);
std::vector<vector<int>> DoublePairRank(numberofplayers);
std::vector<vector<int>> FullRank(numberofplayers);
std::vector<vector<int>> flushsort(numberofplayers);
std::vector<vector<int>> FlushRank(numberofplayers);
std::vector<vector<int>> PlayerPoints(numberofplayers);
std::vector<vector<int>> temppoints(numberofplayers);


Pot=0;
FLUSHCOUNT=0;
PAIRCOUNT=0;
DOUBLEPAIRCOUNT=0;
FULLCOUNT=0;
FULLHOUSECOUNT=0;
STRAIGHTCOUNT=0;
FOUROFAKINDCOUNT=0;
AllIn.erase(AllIn.begin(),AllIn.end());
//cout << "All in erased" << endl;
//int stop;
//cin >> stop;
if (AllIn.size() == 0)
{
	for (int o = 0; o < numberofplayers; o++)
	{
		AllIn.push_back(0);
	};
}
for(int o=0;o<numberofplayers;o++)
{
	WALLETSIZE.push_back(walletsize);
}

int increment;

increment=0;


OutOfGame=count(WALLETSIZE.begin(),WALLETSIZE.end(),0);
Deck theDeck;

std::copy(theDeck.cards.begin(), theDeck.cards.end(), back_inserter(cardsCOPY));
srand( (unsigned)time( NULL ) );

while(OutOfGame!=numberofplayers-1)
{
	for (int o=0;o<numberofplayers;o++)
	{
		AllIn[o]=0;
	};
	cout<<"\n";
	cout<<con::fg_white<<"GAME NUMBER "<<increment<<endl<<con::fg_gray;
	cout<<"\n";
	increment=increment+1;
	BetIncrement=0;
	HandReorganizer=0;


	if (increment>1)
	{
		
		theDeck.cards.erase(theDeck.cards.begin(),theDeck.cards.end());
		std::copy(cardsCOPY.begin(),cardsCOPY.end(),back_inserter(theDeck.cards));
		PlayerCards.erase(PlayerCards.begin(),PlayerCards.end());
		TableCards.erase(TableCards.begin(),TableCards.end());
		hands.erase(hands.begin(),hands.end());	
		sumspades.erase(sumspades.begin(),sumspades.end());
		sumhearts.erase(sumhearts.begin(),sumhearts.end());
		sumdiamonds.erase(sumdiamonds.begin(),sumdiamonds.end());
		sumclubs.erase(sumclubs.begin(),sumclubs.end());
		for (int o=0;o<numberofplayers;o++)
		{
			sumspades.push_back(0);
			sumhearts.push_back(0);
			sumdiamonds.push_back(0);
			sumclubs.push_back(0);
		}
		
	}
	
	theDeck.shuffle();
	bet=0;
	winnerfound=0;
	OutOfGame = count(Wallet.begin(), Wallet.end(), 0);
	HaveFolded = count(PIGstatus.begin(), PIGstatus.end(), 0);

	for(int i=0;i<2*(numberofplayers-OutOfGame);i++) PlayerCards.push_back(theDeck.Draw());
	for(int j=0; j<5; j++) TableCards.push_back(theDeck.Draw());
	std::copy (PlayerCards.begin(), PlayerCards.end(), back_inserter(hands));
	std::copy (TableCards.begin(), TableCards.end(), back_inserter(hands));

	
	HandReorganizer=0;
	for(int o=0;o<numberofplayers;o++)
	{
		
		if (player[o].size()>0)
		{	
			PlayerPoints[o].erase(PlayerPoints[o].begin(),PlayerPoints[o].end());
			player[o].erase(player[o].begin(),player[o].end());
	
		}
	
		else 
		{
			if (Wallet.size()<=o)
			{
				Wallet.push_back(walletsize);
			}
			
		}

		if (DoublePairRank[o].size()!=0)
		{
			DoublePairRank[o].erase(DoublePairRank[o].begin(),DoublePairRank[o].end());
		}
		if (temppoints[o].size()!=0)
		{
			temppoints[o].erase(temppoints[o].begin(),temppoints[o].end());
		}
		if (flushsort[o].size()!=0)
		{
			flushsort[o].erase(flushsort[o].begin(),flushsort[o].end());
		}

		if (FlushRank[o].size()!=0)
		{
			FlushRank[o].erase(FlushRank[o].begin(),FlushRank[o].end());
		}


		if(FullRank[o].size()!=0)
		{
			FullRank[o].erase(FullRank[o].begin(),FullRank[o].end());
		}

		if(Ranks[o].size()!=0)
		{
			Ranks[o].erase(Ranks[o].begin(),Ranks[o].end());
		}

		if(spades[o].size()!=0)
		{
			spades[o].erase(spades[o].begin(),spades[o].end());
		}
		if(hearts[o].size()!=0)
		{
			hearts[o].erase(hearts[o].begin(),hearts[o].end());
		}
		if(diamonds[o].size()!=0)
		{
			diamonds[o].erase(diamonds[o].begin(),diamonds[o].end());
		}
		if(clubs[o].size()!=0)
		{
			clubs[o].erase(clubs[o].begin(),clubs[o].end());
		}
	if (increment==1)
		{
			HaveFoldedBefore=0;
		}
		
		else if (increment>1) HaveFoldedBefore=count(Wallet.begin(),Wallet.begin()+o,0);
		for(int k=2*(o)-2*HaveFoldedBefore;k<2*(o)-2*HaveFoldedBefore+2;k++)
		{
			if (Wallet[o]>0&&HaveFoldedBefore==0)
			{
				Card& i=hands[k];
				player[o].push_back(i);		
			}

			else if(Wallet[o]>0&&HaveFoldedBefore>=1)
			{
				
				Card& i=hands[k];
				player[o].push_back(i);		
			}

		


			else if (Wallet[o]<=0)
			{
				player.reserve(0);
				HandReorganizer=HandReorganizer+1;
				
				
				if (PIGstatus.size()<=o)
				{
					PIGstatus.push_back(0);
				}
				else if (PIGstatus.size()>o)
				{
					PIGstatus[o]=0;
				}
		
				if (MIG.size()>o)
				{
					MIG[o]=0;
				}
				else if (MIG.size()<=o)
				{
					MIG.push_back(0);
				}
				if (MIGTEMP.size()<=o)
				{
					MIGTEMP.push_back(MIG[o]);
				}
									
				else if (MIGTEMP.size()>o)
				{
					MIGTEMP[o]=MIG[o];
				}
				

				
			}
		};
		
	

		if (player[o].size()!=0)
		{
			std::copy (TableCards.begin(), TableCards.end(), back_inserter(player[o]));
			cout<<con::fg_blue;
			std::copy(player[o].begin(),player[o].end(),std::ostream_iterator<Card> (cout,"\n"));	
			cout<<con::fg_gray;
			for (int j=0;j<7;j++) Ranks[o].push_back(player[o][j].GetRank());
			std::sort (Ranks[o].begin(),Ranks[o].end());
			for (int i=0;i<7;i++)
			{
				if(player[o][i].GetSuit()==spade)
				{
					spades[o].push_back(1);
				}
				else
				{
					spades[o].push_back(0);
				}	
				if(player[o][i].GetSuit()==heart)
				{
					hearts[o].push_back(1);
				}
				else
				{
					hearts[o].push_back(0);	
				}
				if(player[o][i].GetSuit()==diamond)
				{
					diamonds[o].push_back(1);	
				}
				else
				{
					diamonds[o].push_back(0);
				}
				if(player[o][i].GetSuit()==club)
				{
					clubs[o].push_back(1);
				}
				else
				{	
					clubs[o].push_back(0);
				}
			};	
			sumspades[o]= accumulate(spades[o].begin(), spades[o].end(), 0);
			sumhearts[o]= accumulate(hearts[o].begin(), hearts[o].end(), 0);
			sumdiamonds[o]= accumulate(diamonds[o].begin(), diamonds[o].end(), 0);
			sumclubs[o]= accumulate(clubs[o].begin(), clubs[o].end(), 0);
			if (sumspades[o]>=5) 
			{
				flush[o]=0;
			}
			if (sumhearts[o]>=5) 
			{
				flush[o]=1;
			}
			if (sumdiamonds[o]>=5) 
			{
				flush[o]=2;
			}
			if(sumclubs[o]>=5) 
			{
				flush[o]=3;
			}
			
			for (int j=0;j<7;j++)
			{
				if (flush[o]==0&&spades[o][j]==1) 
				{
					flushsort[o].push_back(player[o][j].GetRank());
					std::sort(flushsort[o].begin(),flushsort[o].end());
				}
				if (flush[o]==1&&hearts[o][j]==1) 
				{
					flushsort[o].push_back(player[o][j].GetRank());
					std::sort(flushsort[o].begin(),flushsort[o].end());
				}
	
				if (flush[o]==2&&diamonds[o][j]==1) 
				{
					flushsort[o].push_back(player[o][j].GetRank());
					std::sort(flushsort[o].begin(),flushsort[o].end());
				}	
	
				if (flush[o]==3&&clubs[o][j]==1) 
				{
					flushsort[o].push_back(player[o][j].GetRank());
					std::sort(flushsort[o].begin(),flushsort[o].end());
				}
			};
	
			int sumbooleansuitequality=(player[o][0].GetSuit()==player[o][1].GetSuit())+(player[o][0].GetSuit()==player[o][2].GetSuit())+(player[o][0].GetSuit()==player[o][3].GetSuit())+
			(player[o][0].GetSuit()==player[o][4].GetSuit())+(player[o][0].GetSuit()==player[o][5].GetSuit())+(player[o][0].GetSuit()==player[o][6].GetSuit())+
			(player[o][1].GetSuit()==player[o][2].GetSuit())+(player[o][1].GetSuit()==player[o][3].GetSuit())+(player[o][1].GetSuit()==player[o][4].GetSuit())+
			(player[o][1].GetSuit()==player[o][5].GetSuit())+(player[o][1].GetSuit()==player[o][6].GetSuit())+(player[o][2].GetSuit()==player[o][3].GetSuit())+
			(player[o][2].GetSuit()==player[o][4].GetSuit())+(player[o][2].GetSuit()==player[o][5].GetSuit())+(player[o][2].GetSuit()==player[o][6].GetSuit())+
			(player[o][3].GetSuit()==player[o][4].GetSuit())+(player[o][3].GetSuit()==player[o][5].GetSuit())+(player[o][3].GetSuit()==player[o][6].GetSuit())+
			(player[o][4].GetSuit()==player[o][5].GetSuit())+(player[o][4].GetSuit()==player[o][6].GetSuit())+(player[o][5].GetSuit()==player[o][6].GetSuit());	

			int sumbooleansuitinequality=(player[o][0].GetSuit()!=player[o][1].GetSuit())+(player[o][0].GetSuit()!=player[o][2].GetSuit())+(player[o][0].GetSuit()!=player[o][3].GetSuit())+
			(player[o][0].GetSuit()!=player[o][4].GetSuit())+(player[o][0].GetSuit()!=player[o][5].GetSuit())+(player[o][0].GetSuit()!=player[o][6].GetSuit())+
			(player[o][1].GetSuit()!=player[o][2].GetSuit())+(player[o][1].GetSuit()!=player[o][3].GetSuit())+(player[o][1].GetSuit()!=player[o][4].GetSuit())+
			(player[o][1].GetSuit()!=player[o][5].GetSuit())+(player[o][1].GetSuit()!=player[o][6].GetSuit())+(player[o][2].GetSuit()!=player[o][3].GetSuit())+
			(player[o][2].GetSuit()!=player[o][4].GetSuit())+(player[o][2].GetSuit()!=player[o][5].GetSuit())+(player[o][2].GetSuit()!=player[o][6].GetSuit())+
			(player[o][3].GetSuit()!=player[o][4].GetSuit())+(player[o][3].GetSuit()!=player[o][5].GetSuit())+(player[o][3].GetSuit()!=player[o][6].GetSuit())+
			(player[o][4].GetSuit()!=player[o][5].GetSuit())+(player[o][4].GetSuit()!=player[o][6].GetSuit())+(player[o][5].GetSuit()!=player[o][6].GetSuit());

			int sumbooleanheightequality=(player[o][0].GetRank()==player[o][1].GetRank())+(player[o][0].GetRank()==player[o][2].GetRank())+(player[o][0].GetRank()==player[o][3].GetRank())+
			(player[o][0].GetRank()==player[o][4].GetRank())+(player[o][0].GetRank()==player[o][5].GetRank())+(player[o][0].GetRank()==player[o][6].GetRank())+
			(player[o][1].GetRank()==player[o][2].GetRank())+(player[o][1].GetRank()==player[o][3].GetRank())+(player[o][1].GetRank()==player[o][4].GetRank())+
			(player[o][1].GetRank()==player[o][5].GetRank())+(player[o][1].GetRank()==player[o][6].GetRank())+(player[o][2].GetRank()==player[o][3].GetRank())+
			(player[o][2].GetRank()==player[o][4].GetRank())+(player[o][2].GetRank()==player[o][5].GetRank())+(player[o][2].GetRank()==player[o][6].GetRank())+
			(player[o][3].GetRank()==player[o][4].GetRank())+(player[o][3].GetRank()==player[o][5].GetRank())+(player[o][3].GetRank()==player[o][6].GetRank())+
			(player[o][4].GetRank()==player[o][5].GetRank())+(player[o][4].GetRank()==player[o][6].GetRank())+(player[o][5].GetRank()==player[o][6].GetRank());

			int sumbooleanheightinequality=(player[o][0].GetRank()!=player[o][1].GetRank())+(player[o][0].GetRank()!=player[o][2].GetRank())+(player[o][0].GetRank()!=player[o][3].GetRank())+
			(player[o][0].GetRank()!=player[o][4].GetRank())+(player[o][0].GetRank()!=player[o][5].GetRank())+(player[o][0].GetRank()!=player[o][6].GetRank())+
			(player[o][1].GetRank()!=player[o][2].GetRank())+(player[o][1].GetRank()!=player[o][3].GetRank())+(player[o][1].GetRank()!=player[o][4].GetRank())+
			(player[o][1].GetRank()!=player[o][5].GetRank())+(player[o][1].GetRank()!=player[o][6].GetRank())+(player[o][2].GetRank()!=player[o][3].GetRank())+
			(player[o][2].GetRank()!=player[o][4].GetRank())+(player[o][2].GetRank()!=player[o][5].GetRank())+(player[o][2].GetRank()!=player[o][6].GetRank())+
			(player[o][3].GetRank()!=player[o][4].GetRank())+(player[o][3].GetRank()!=player[o][5].GetRank())+(player[o][3].GetRank()!=player[o][6].GetRank())+
			(player[o][4].GetRank()!=player[o][5].GetRank())+(player[o][4].GetRank()!=player[o][6].GetRank())+(player[o][5].GetRank()!=player[o][6].GetRank());

			cout<<con::fg_magenta<<"						Player"<<o<<"\n";
			int FOOK;
			FOOK=0;
			if(sumbooleanheightequality>=6&&sumbooleanheightinequality!=13&&sumbooleanheightinequality<=15) 
			{
				int FOOK;
				FOOK=1;
			}
			if (FOOK!=1)
			{
			if ((Ranks[o][0]==Ranks[o][1]-1)+(Ranks[o][0]==Ranks[o][2]-2)+(Ranks[o][0]==Ranks[o][3]-3)+(Ranks[o][0]==Ranks[o][4]-4)!=4&&(Ranks[o][1]==Ranks[o][2]-1)+(Ranks[o][1]==Ranks[o][3]-2)+(Ranks[o][1]==Ranks[o][4]-3)+(Ranks[o][1]==Ranks[o][5]-4)!=4&&(Ranks[o][2]==Ranks[o][3]-1)+(Ranks[o][2]==Ranks[o][4]-2)+(Ranks[o][2]==Ranks[o][5]-3)+(Ranks[o][2]==Ranks[o][6]-4)!=4) 
			{
				if (sumbooleanheightequality==0&&sumbooleansuitinequality>=9&&sumbooleansuitinequality!=10&&sumbooleansuitinequality!=11)
				{
					std::cout<<"						Height ";
					PlayerPoints[o].push_back(0);
					if (Ranks[o][0]==1) 
					{
						cout<< "Ace "<< "\n";
						PlayerPoints[o].push_back(14);
						PlayerPoints[o].push_back(Ranks[o][6]);
						PlayerPoints[o].push_back(Ranks[o][5]);
						PlayerPoints[o].push_back(Ranks[o][4]);
						PlayerPoints[o].push_back(Ranks[o][3]);
						
					}
					else if (Ranks[o][6]==11) 
					{
						cout<<"Jack \n";
						PlayerPoints[o].push_back(11);
						PlayerPoints[o].push_back(Ranks[o][5]);
						PlayerPoints[o].push_back(Ranks[o][4]);
						PlayerPoints[o].push_back(Ranks[o][3]);
						PlayerPoints[o].push_back(Ranks[o][2]);
					}
					else if (Ranks[o][6]==12) 
					{
						cout<<"Queen \n";
						PlayerPoints[o].push_back(12);
						PlayerPoints[o].push_back(Ranks[o][5]);
						PlayerPoints[o].push_back(Ranks[o][4]);
						PlayerPoints[o].push_back(Ranks[o][3]);
						PlayerPoints[o].push_back(Ranks[o][2]);
					} 
					else if (Ranks[o][6]==13)
					{
						cout<<"King \n";
						PlayerPoints[o].push_back(13);
						PlayerPoints[o].push_back(Ranks[o][5]);
						PlayerPoints[o].push_back(Ranks[o][4]);
						PlayerPoints[o].push_back(Ranks[o][3]);
						PlayerPoints[o].push_back(Ranks[o][2]);
					
					} 
					else 
					{
						cout<< Ranks[o][6]<< "s \n";
						PlayerPoints[o].push_back(Ranks[o][6]);
						PlayerPoints[o].push_back(Ranks[o][5]);
						PlayerPoints[o].push_back(Ranks[o][4]);
						PlayerPoints[o].push_back(Ranks[o][3]);
						PlayerPoints[o].push_back(Ranks[o][2]);
					}
					
				}
				if (sumbooleanheightequality==1&&sumbooleansuitinequality>=9&&sumbooleansuitinequality!=10&&sumbooleansuitinequality!=11)
				{
					std::cout <<"						Pair"; 
					PAIRCOUNT=PAIRCOUNT+1;
					PlayerPoints[o].push_back(1);
					for (int k=1;k<=6;k++)
					{
						for (int i=k; i<7;i++)
						{
							if (player[o][k-1].GetRank()==player[o][i].GetRank())
							{
								if (player[o][k-1].GetRank()==1) 
								{
									cout<<" of Aces \n";
									PlayerPoints[o].push_back(14);
										
								}
								else if (player[o][k-1].GetRank()==11) 
								{
									cout<<" of Jacks \n";
									PlayerPoints[o].push_back(11);
								}
								else if (player[o][k-1].GetRank()==12) 
								{
									cout<<" of Queens \n";
									PlayerPoints[o].push_back(12);
								} 
								else if (player[o][k-1].GetRank()==13)
								{
									cout<<" of Kings \n";
									PlayerPoints[o].push_back(13);
								} 
								else
								{
									cout<<" of "<< player[o][k-1].GetRank()<< "s\n";
									PlayerPoints[o].push_back(player[o][k-1].GetRank());
								}

								if (Ranks[o][6]!=player[o][k-1].GetRank()&&Ranks[o][0]!=1) 
								{
									cout<<"						Kicker: ";
									if (Ranks[o][6]==11) 
									{
										cout<<"Jack \n";
										PlayerPoints[o].push_back(11);
									}
									else if (Ranks[o][6]==12) 
									{
										cout<<"Queen \n";
										PlayerPoints[o].push_back(12);
									} 
									else if (Ranks[o][6]==13)
									{
										cout<<"King \n";
										PlayerPoints[o].push_back(13);
									} 
									else 
									{
										cout<< Ranks[o][6]<< "s \n";
										PlayerPoints[o].push_back(Ranks[o][6]);
									}
								}

								if (Ranks[o][6]!=player[o][k-1].GetRank()&&Ranks[o][0]==1&&player[o][k-1].GetRank()!=1) 
								{
									cout<<"						Kicker:  Ace \n";
									PlayerPoints[o].push_back(14);
								}

								if (Ranks[o][6]==player[o][k-1].GetRank()&&Ranks[o][0]!=1) 
								{
									cout<<"						Kicker: ";
									if (Ranks[o][4]==11) 
									{
										cout<<"Jack \n";
										PlayerPoints[o].push_back(11);
									}
									else if (Ranks[o][4]==12) 
									{
										cout<<"Queen \n";
										PlayerPoints[o].push_back(12);
									} 
									else if (Ranks[o][4]==13)
									{
										cout<<"King \n";
										PlayerPoints[o].push_back(13);
									} 
									else 
									{
										cout<< Ranks[o][4]<< "s \n";
										PlayerPoints[o].push_back(Ranks[o][4]);
									}
								}
								if (Ranks[o][6]==player[o][k-1].GetRank()&&Ranks[o][0]==1) 
								{
									cout<<"						Kicker:  Ace \n";
									PlayerPoints[o].push_back(14);
								}
									
								if (Ranks[o][0]==player[o][k-1].GetRank()&&Ranks[o][0]==1) 
								{
									cout<<"						Kicker: ";
									if (Ranks[o][6]==11) 
									{
										cout<<"Jack \n";
										PlayerPoints[o].push_back(11);
									}
									else if (Ranks[o][6]==12) 
									{
										cout<<"Queen \n";
										PlayerPoints[o].push_back(12);
									} 
									else if (Ranks[o][6]==13)
									{
										cout<<"King \n";
										PlayerPoints[o].push_back(13);
									} 
									else 
									{
										cout<< Ranks[o][6]<< "s \n";
										PlayerPoints[o].push_back(Ranks[o][6]);
									}
								}


							}
						};
					};
			
					
				}


				if (sumbooleanheightequality==2&&sumbooleansuitinequality>=9&&sumbooleansuitinequality!=10&&sumbooleansuitinequality!=11)
				{	
					std::cout<<"						DoublePair "; 
					DOUBLEPAIRCOUNT=DOUBLEPAIRCOUNT+1;
					PlayerPoints[o].push_back(2);
					for (int k=1;k<=6;k++)
					{
						for (int i=k; i<7;i++)
						{
							if (player[o][k-1].GetRank()==player[o][i].GetRank())
							{
								if (player[o][k-1].GetRank()==1) 
								{
									cout<<" Aces ";
									DoublePairRank[o].push_back(14);		
								} 
								else if (player[o][k-1].GetRank()==11) 
								{
									cout<<" Jacks ";
									DoublePairRank[o].push_back(11);	
								} 
								else if (player[o][k-1].GetRank()==12)
								{
									cout<<" Queens ";
									DoublePairRank[o].push_back(12);	
								} 
								else if (player[o][k-1].GetRank()==13) 
								{
									cout<<" Kings ";
									DoublePairRank[o].push_back(13);
								} 
								else 
								{
									cout<< player[o][k-1].GetRank()<< "s";
									DoublePairRank[o].push_back(player[o][k-1].GetRank());
								}
									
							}
								
						};
					};
					
					std::sort(DoublePairRank[o].begin(),DoublePairRank[o].end());	
					for (int z=0;z<2;z++) PlayerPoints[o].push_back(DoublePairRank[o][z]);
					if (DoublePairRank[o][1]!=Ranks[o][6]&&Ranks[o][0]!=1|DoublePairRank[o][1]==14&&DoublePairRank[o][0]!=Ranks[o][6])
					{
						cout<<"								Kicker: ";
						if (Ranks[o][6]==11) 
						{
							cout<<"Jack \n";
							PlayerPoints[o].push_back(11);
						}
						else if (Ranks[o][6]==12) 
						{
							cout<<"Queen \n";
							PlayerPoints[o].push_back(12);
						} 
						else if (Ranks[o][6]==13)
						{
							cout<<"King \n";
							PlayerPoints[o].push_back(13);
						} 
						else 
						{
							cout<< Ranks[o][6]<< "s \n";
							PlayerPoints[o].push_back(Ranks[o][6]);
						}
					}

					if (DoublePairRank[o][1]==14&&DoublePairRank[o][0]==Ranks[o][6]|DoublePairRank[o][0]==Ranks[o][0]&&DoublePairRank[o][1]==Ranks[o][6]|DoublePairRank[o][1]==14)
					{
						cout<<"								Kicker: ";
						if (Ranks[o][5]==11) 
						{
							cout<<"Jack \n";
							PlayerPoints[o].push_back(11);
						}
						else if (Ranks[o][5]==12) 
						{
							cout<<"Queen \n";
							PlayerPoints[o].push_back(12);
						} 
						else if (Ranks[o][5]==13)
						{
							cout<<"King \n";
							PlayerPoints[o].push_back(13);
						} 
						else 
						{
							cout<< Ranks[o][5]<< "s \n";
							PlayerPoints[o].push_back(Ranks[o][5]);
						}
					}

					if (DoublePairRank[o][1]==Ranks[o][6]&&DoublePairRank[o][0]!=Ranks[o][4]&&Ranks[o][0]!=1)		
					{
						cout<<"								Kicker: ";
						if (Ranks[o][4]==11) 
						{
							cout<<"Jack \n";
							PlayerPoints[o].push_back(11);
						}
						else if (Ranks[o][4]==12) 
						{
							cout<<"Queen \n";
							PlayerPoints[o].push_back(12);
						} 
						else if (Ranks[o][4]==13)
						{
							cout<<"King \n";
							PlayerPoints[o].push_back(13);
						} 
						else 
						{
							cout<< Ranks[o][4]<< "s \n";
							PlayerPoints[o].push_back(Ranks[o][4]);
						}
					}
					
					if (Ranks[o][6]==DoublePairRank[o][1]&&Ranks[o][4]==DoublePairRank[o][0]&&Ranks[o][0]!=1)
					{
						cout<<"								Kicker: ";
						if (Ranks[o][2]==11) 
						{
							cout<<"Jack \n";
							PlayerPoints[o].push_back(11);
						}
						else if (Ranks[o][2]==12) 
						{
							cout<<"Queen \n";
							PlayerPoints[o].push_back(12);
						} 
						else if (Ranks[o][2]==13)
						{
							cout<<"King \n";
							PlayerPoints[o].push_back(13);
						} 
						else 
						{
							cout<< Ranks[o][2]<< "s \n";
							PlayerPoints[o].push_back(Ranks[o][2]);
						}
					}
					
					if (DoublePairRank[o][1]!=14&&Ranks[o][0]==1)
					{
						cout<<"								Kicker:  Ace \n";
						PlayerPoints[o].push_back(14);
					}

				}
				if ((Ranks[o][0]==Ranks[o][1])+(Ranks[o][2]==Ranks[o][3])+(Ranks[o][4]==Ranks[o][5])+(Ranks[o][5]!=Ranks[o][6])==4|(Ranks[o][0]==Ranks[o][1])+(Ranks[o][2]==Ranks[o][3])+(Ranks[o][4]!=Ranks[o][5])+(Ranks[o][5]==Ranks[o][6])==4|(Ranks[o][0]==Ranks[o][1])+(Ranks[o][2]!=Ranks[o][3])+(Ranks[o][3]==Ranks[o][4])+(Ranks[o][5]==Ranks[o][6])==4|(Ranks[o][0]!=Ranks[o][1])+(Ranks[o][1]==Ranks[o][2])+(Ranks[o][3]==Ranks[o][4])+(Ranks[o][5]==Ranks[o][6])==4)
				{
					cout<<"						Double Pair "<< "\n";
					PlayerPoints[o].push_back(2);
					DOUBLEPAIRCOUNT=DOUBLEPAIRCOUNT+1;
				}
				
				for (int k=0;k<5;k++)
				{
					for (int i=k+1;i<6;i++)
					{
						for(int j=i+1;j<7;j++)
						{				
							if (sumbooleanheightinequality==18&&(player[o][k].GetRank()==player[o][j].GetRank())+(player[o][k].GetRank()==player[o][i].GetRank())+(player[o][i].GetRank()==player[o][j].GetRank())==3)
							{
								std::cout<<"						Full";
								FULLCOUNT=FULLCOUNT+1;
								PlayerPoints[o].push_back(3);
								if (player[o][k].GetRank()==1) 
								{ 
									cout<<" of Aces ";
									FullRank[o].push_back(14);
								} 
								else if (player[o][k].GetRank()==11) 
								{
									cout<<" of Jacks ";
									FullRank[o].push_back(11);
								} 
								else if (player[o][k].GetRank()==12) 
								{
									cout<<" of Queens ";
									FullRank[o].push_back(12);
								}
								else if (player[o][k].GetRank()==13) 
								{
									cout<<" of Kings ";
									FullRank[o].push_back(13);
								} 
								else 
								{
									cout<< " of " <<player[o][k].GetRank()<< "s ";
									FullRank[o].push_back(player[o][k].GetRank());
								}
								cout << "\n";
								std::copy (FullRank[o].begin(), FullRank[o].end(), back_inserter(PlayerPoints[o]));
								for (int i=0;i<4;i++)
								{
									if (FullRank[o][0]==Ranks[o][i]&&FullRank[o][0]==Ranks[o][i+1]&&FullRank[o][0]==Ranks[o][i+2]&&Ranks[o][0]!=1)
									{
										cout<<"						Kicker: ";
										if (Ranks[o][6]==11) 
										{
											cout<<"Jack \n";
											PlayerPoints[o].push_back(11);
						
										}
										else if (Ranks[o][6]==12) 
										{
											cout<<"Queen \n";
											PlayerPoints[o].push_back(12);
										} 
										else if (Ranks[o][6]==13)
										{
											cout<<"King \n";
											PlayerPoints[o].push_back(13);
										} 
										else 
										{
											cout<< Ranks[o][6]<< "s \n";
											PlayerPoints[o].push_back(Ranks[o][6]);
										}
										if (i==0|i==1|i==2)
										{
											PlayerPoints[o].push_back(Ranks[o][5]);
										}

										if (i==3)
										{
											PlayerPoints[o].push_back(Ranks[o][2]);
										}
									}
								};

								if (FullRank[o][0]==14)
								{
									cout<<"						Kicker: ";
									if (Ranks[o][6]==11) 
									{
										cout<<"Jack \n";
										PlayerPoints[o].push_back(11);
									}
									else if (Ranks[o][6]==12) 
									{
										cout<<"Queen \n";
										PlayerPoints[o].push_back(12);
									} 
									else if (Ranks[o][6]==13)
									{
										cout<<"King \n";
										PlayerPoints[o].push_back(13);
									} 
									else 
									{
										cout<< Ranks[o][6]<< "s \n";
										PlayerPoints[o].push_back(Ranks[o][6]);
									}
								}
								if (FullRank[o][0]==Ranks[o][6]&&Ranks[o][0]!=1)
								{
									cout<<"						Kicker: ";
									if (Ranks[o][3]==11) 
									{
										cout<<"Jack"<<" \n";
										PlayerPoints[o].push_back(11);
									}
									else if (Ranks[o][3]==12) 
									{
										cout<<"Queen"<<" \n";
										PlayerPoints[o].push_back(12);
									} 
									else if (Ranks[o][3]==13)
									{
										cout<<"King"<<" \n";
										PlayerPoints[o].push_back(13);
									} 
									else 
									{
										cout<< Ranks[o][3]<< "s "<<"\n";
										PlayerPoints[o].push_back(Ranks[o][3]);
									}
								}
								if (FullRank[o][0]!=14&&Ranks[o][0]==1)
								{
									cout<<"						Kicker: Ace "<<"\n";
									PlayerPoints[o].push_back(14);
								}
							}
						};
					};
				};

			}

			if(Ranks[o][0]==1&&Ranks[o][3]==10&&Ranks[o][4]==11&&Ranks[o][5]==12&&Ranks[o][6]==13)
			{
				cout<<"						Straight"<<'\n';
				STRAIGHTCOUNT=STRAIGHTCOUNT+1;
				PlayerPoints[o].push_back(4);
				cout<<"						High Card: Ace"<<"\n"; 
				PlayerPoints[o].push_back(14);
			}

			if ((Ranks[o][0]==Ranks[o][1]-1) +(Ranks[o][0]==Ranks[o][2]-2)+(Ranks[o][0]==Ranks[o][3]-3)+(Ranks[o][0]==Ranks[o][4]-4)==4|(Ranks[o][1]==Ranks[o][2]-1)+(Ranks[o][1]==Ranks[o][3]-2)+(Ranks[o][1]==Ranks[o][4]-3)+(Ranks[o][1]==Ranks[o][5]-4)==4|(Ranks[o][2]==Ranks[o][3]-1)+(Ranks[o][2]==Ranks[o][4]-2)+(Ranks[o][2]==Ranks[o][5]-3)+(Ranks[o][2]==Ranks[o][6]-4)==4) 		
			{
				cout<<"						Straight"<<'\n';
				STRAIGHTCOUNT=STRAIGHTCOUNT+1;
				PlayerPoints[o].push_back(4);
				if(Ranks[o][6]==Ranks[o][5]+1&&Ranks[o][6]==Ranks[o][4]+2)
				{
					cout<<"						High Card: "; 
					if (Ranks[o][6]==11) 
					{
						cout<<"Jack"<<" \n";
						PlayerPoints[o].push_back(11);
					}
					else if (Ranks[o][6]==12) 
					{
						cout<<"Queen"<<" \n";
						PlayerPoints[o].push_back(12);
					} 
					else if (Ranks[o][6]==13)
					{
						cout<<"King"<<" \n";
						PlayerPoints[o].push_back(13);
					} 
					else 
					{
						cout<< Ranks[o][6]<< "s "<<"\n";
						PlayerPoints[o].push_back(Ranks[o][6]);
					}
					
				}
				
				if(Ranks[o][6]!=Ranks[o][5]+1&&Ranks[o][5]==Ranks[o][4]+1)
				{
					cout<<"						High Card: "; 
					if (Ranks[o][5]==11) 
					{
						cout<<"Jack"<<" \n";
						PlayerPoints[o].push_back(11);
					}
					else if (Ranks[o][5]==12) 
					{
						cout<<"Queen"<<" \n";
						PlayerPoints[o].push_back(12);
					} 
					else if (Ranks[o][5]==13)
					{
						cout<<"King"<<" \n";
						PlayerPoints[o].push_back(13);
					} 
					else 
					{
						cout<< Ranks[o][5]<<"\n";
						PlayerPoints[o].push_back(Ranks[o][5]);
					}
					
				}
				if (Ranks[o][4]!=Ranks[o][5]-1)
				{
					cout<<"						High Card: "; 
					if (Ranks[o][4]==11) 
					{
						cout<<"Jack"<<" \n";
						PlayerPoints[o].push_back(11);
					}
					else if (Ranks[o][4]==12) 
					{
						cout<<"Queen"<<" \n";
						PlayerPoints[o].push_back(12);
					}	 
					else if (Ranks[o][4]==13)
					{
						cout<<"King"<<" \n";
						PlayerPoints[o].push_back(13);
					} 
					else 
					{
						cout<< Ranks[o][4]<<"\n";
						PlayerPoints[o].push_back(Ranks[o][4]);
					}
				}
				PlayerPoints[o].push_back(0);
				PlayerPoints[o].push_back(0);
				PlayerPoints[o].push_back(0);
				PlayerPoints[o].push_back(0);	
			}	
			
			if (sumbooleansuitequality>=5&&sumbooleansuitinequality!=9&&sumbooleansuitinequality<=11)
			{
				std::cout << "						Flush"<< "\n";
				
					FLUSHCOUNT=FLUSHCOUNT+1;
	

				PlayerPoints[o].push_back(5);
				if(flushsort[o][0]!=1)
				{
					cout<<"						High Card: "; 
					if (flushsort[o][flushsort[o].size()-1]==11) 
					{
						cout<<"Jack"<<" \n";
						std::copy(flushsort[o].begin(),flushsort[o].end(),back_inserter(PlayerPoints[o]));
					}
					else if (flushsort[o][flushsort[o].size()-1]==12) 
					{
						cout<<"Queen"<<" \n";
						std::copy(flushsort[o].begin(),flushsort[o].end(),back_inserter(PlayerPoints[o]));
					} 
					else if (flushsort[o][flushsort[o].size()-1]==13)
					{
						cout<<"King"<<" \n";
						std::copy(flushsort[o].begin(),flushsort[o].end(),back_inserter(PlayerPoints[o]));
					} 
					else 
					{
						cout<< flushsort[o][flushsort[o].size()-1]<<"\n";
						std::copy(flushsort[o].begin(),flushsort[o].end(),back_inserter(PlayerPoints[o]));
					}

				}

				if (flushsort[o][0]==1)
				{
					cout<<"						High Card: Ace \n ";
					PlayerPoints[o].push_back(14);
					for(int i=0;i<flushsort[o].size();i++)
					{	
						std::copy(flushsort[o].begin()+1,flushsort[o].end(),back_inserter(PlayerPoints[o]));	
					};
				}				
			}
			}
			if (sumbooleanheightequality>=12&&sumbooleanheightinequality!=13&&sumbooleanheightinequality<=15)
			{
				std::cout << "						Four of a Kind:";
				FOUROFAKINDCOUNT=FOUROFAKINDCOUNT+1;
				PlayerPoints[o].push_back(8);
				
				for (int k=0;k<4;k++)
				{
					if ((Ranks[o][k]==Ranks[o][k+1])+(Ranks[o][k]==Ranks[o][k+2])+(Ranks[o][k]==Ranks[o][k+3])==3)
					{
						if (Ranks[o][k]==1) 
						{
							cout<<" Aces \n ";
							PlayerPoints[o].push_back(14);
						}
						else if (Ranks[o][k]==11)  
						{
							cout<<" Jacks  \n ";
							PlayerPoints[o].push_back(11);
						}
						else if (Ranks[o][k]==12)
						{
							cout<<" Queens  \n ";
							PlayerPoints[o].push_back(12);
						}
						else if (Ranks[o][k]==13) 
						{
							cout<<" Kings  \n ";
							PlayerPoints[o].push_back(13);
						}
						else 
						{
							cout<< " " << Ranks[o][k] << "s ";
							PlayerPoints[o].push_back(Ranks[o][k]);
						}
					}
				};
				PlayerPoints[o].push_back(0);
				PlayerPoints[o].push_back(0);
				PlayerPoints[o].push_back(0);
				PlayerPoints[o].push_back(0);	
			}
			if (sumbooleanheightequality==6&&sumbooleanheightinequality==18&&FOOK!=1)
			{
				std::cout << "						Full House";
				FULLHOUSECOUNT=FULLHOUSECOUNT+1;
				PlayerPoints[o].push_back(6);	
				for (int k=0;k<1;k++)
				{
					if (Ranks[o][k]==Ranks[o][k+1]&&Ranks[o][k]!=Ranks[o][k+2])
					{	
						if (Ranks[o][k]==1) 
						{
							cout<<" Aces ";
							temppoints[o].push_back(14);
						}
						else if (Ranks[o][k]==11)  
						{
							cout<<" Jacks ";
							temppoints[o].push_back(11);
						}
						else if (Ranks[o][k]==12)
						{
							cout<<" Queens ";
							temppoints[o].push_back(12);
						}
						else if (Ranks[o][k]==13) 
						{
							cout<<" Kings ";
							temppoints[o].push_back(13);
						}
						else 
						{
							cout<< " " << Ranks[o][k] << "s ";
							temppoints[o].push_back(Ranks[o][k]);
						}
					}			
				};
				for (int k=1;k<5;k++)
				{
					if (Ranks[o][k]==Ranks[o][k+1]&&Ranks[o][k]!=Ranks[o][k+2]&&Ranks[o][k]!=Ranks[o][k-1])
					{		
						if (Ranks[o][k]==1) 
						{
							cout<<" Aces ";
							temppoints[o].push_back(14);
						}
						else if (Ranks[o][k]==11)  
						{
							cout<<" Jacks ";
							temppoints[o].push_back(11);
						}
						else if (Ranks[o][k]==12)
						{
							cout<<" Queens ";
							temppoints[o].push_back(12);
						}
						else if (Ranks[o][k]==13) 
						{
							cout<<" Kings ";
							temppoints[o].push_back(13);
						}
						else 
						{
							cout<< " " << Ranks[o][k] << "s ";
							temppoints[o].push_back(Ranks[o][k]);
						}
					}			
				};
				
				for (int k=5;k<6;k++)
				{
					if (Ranks[o][k]==Ranks[o][k+1]!=Ranks[o][k-1])
					{	
						if (Ranks[o][k]==1) 
						{
							cout<<" Aces ";
							temppoints[o].push_back(14);
						}
						else if (Ranks[o][k]==11)  
						{
							cout<<" Jacks ";
							temppoints[o].push_back(11);
						}
						else if (Ranks[o][k]==12)
						{
							cout<<" Queens ";
							temppoints[o].push_back(12);
						}
						else if (Ranks[o][k]==13) 
						{
							cout<<" Kings ";
							temppoints[o].push_back(13);
						}
						else 
						{
							cout<< " " << Ranks[o][k] << "s ";
							temppoints[o].push_back(Ranks[o][k]);
						}
					}				
				};
				for (int l=0;l<5;l++)
				{
					for (int m=l+1;m<6;m++)
					{
						for(int n=m+1;n<7;n++)
						{
							if ((player[o][l].GetRank()==player[o][n].GetRank())+(player[o][l].GetRank()==player[o][m].GetRank())+(player[o][m].GetRank()==player[o][n].GetRank())==3)
							{
								if (player[o][l].GetRank()==1) 
								{
									cout<<" in Aces "<<"\n";
									PlayerPoints[o].push_back(14);
								}
								else if (player[o][l].GetRank()==11) 
								{
									cout<<" in Jacks "<<"\n";
									PlayerPoints[o].push_back(11);
								}
								else if (player[o][l].GetRank()==12)
								{
									cout<<" in Queens "<<"\n";
									PlayerPoints[o].push_back(12);
								}
								else if (player[o][l].GetRank()==13) 
								{
									cout<<" in Kings "<<"\n";
									PlayerPoints[o].push_back(13);
								}
								else 
								{
									cout<< " in " <<player[o][l].GetRank()<< "s "<<"\n";
									PlayerPoints[o].push_back(player[o][l].GetRank());
								}
							}
						};
					};
				};
			}
			if (sumbooleanheightequality==5&&sumbooleanheightinequality==16)
			{
				std::cout<<"						FullHouse: exception case";
				FULLHOUSECOUNT=FULLHOUSECOUNT+1;
				PlayerPoints[o].push_back(6);
			}

			if (sumbooleanheightequality==4&&sumbooleanheightinequality>12)
			{
				std::cout << "						FullHouse";
				FULLHOUSECOUNT=FULLHOUSECOUNT+1;
				PlayerPoints[o].push_back(6);
				for (int k=0;k<1;k++)
				{
					if (Ranks[o][k]==Ranks[o][k+1]&&Ranks[o][k]!=Ranks[o][k+2]&&Ranks[o][k])
					{
						if (Ranks[o][k]==1) 
						{
							cout<<" Aces ";
							temppoints[o].push_back(14);
						}
						else if (Ranks[o][k]==11)  
						{
							cout<<" Jacks ";
							temppoints[o].push_back(11);
						}
						else if (Ranks[o][k]==12)
						{
							cout<<" Queens ";
							temppoints[o].push_back(12);
						}
						else if (Ranks[o][k]==13) 
						{
							cout<<" Kings ";
							temppoints[o].push_back(13);
						}
						else 
						{
							cout<< " " << Ranks[o][k] << "s ";
							temppoints[o].push_back(Ranks[o][k]);
						}				
					}			
				};
				
				for (int k=1;k<5;k++)
				{	
					if (Ranks[o][k]==Ranks[o][k+1]&&Ranks[o][k]!=Ranks[o][k+2]&&Ranks[o][k]!=Ranks[o][k-1])
					{					
						if (Ranks[o][k]==1) 
						{
							cout<<" Aces ";
							temppoints[o].push_back(14);
						}
						else if (Ranks[o][k]==11)  
						{
							cout<<" Jacks ";
							temppoints[o].push_back(11);
						}
						else if (Ranks[o][k]==12)
						{
							cout<<" Queens ";
							temppoints[o].push_back(12);
						}
						else if (Ranks[o][k]==13) 
						{
							cout<<" Kings ";
							temppoints[o].push_back(13);
						}
						else 
						{
							cout<< " " << Ranks[o][k] << "s ";
							temppoints[o].push_back(Ranks[o][k]);
						}
					}			
				};
			
				for (int k=5;k<6;k++)
				{
					if (Ranks[o][k]==Ranks[o][k+1]&&Ranks[o][k]!=Ranks[o][k-1])
					{
						if (Ranks[o][k]==1) 
						{
							cout<<" Aces ";
							temppoints[o].push_back(14);
						}
						else if (Ranks[o][k]==11)  
						{
							cout<<" Jacks ";
							temppoints[o].push_back(11);
						}
						else if (Ranks[o][k]==12)
						{
							cout<<" Queens ";
							temppoints[o].push_back(12);
						}
						else if (Ranks[o][k]==13) 
						{
							cout<<" Kings ";
							temppoints[o].push_back(13);
						}
						else 
						{
							cout<< " " << Ranks[o][k] << "s ";
							temppoints[o].push_back(Ranks[o][k]);
						}
					}			
				};

				for (int l=0;l<5;l++)
				{
					for (int m=l+1;m<6;m++)
					{
						for(int n=m+1;n<7;n++)
						{	
							if ((player[o][l].GetRank()==player[o][n].GetRank())+(player[o][l].GetRank()==player[o][m].GetRank())+(player[o][m].GetRank()==player[o][n].GetRank())==3)
							{
								if (player[o][l].GetRank()==1) 
								{
									cout<<" in Aces "<<"\n";
									PlayerPoints[o].push_back(14);
								}
								else if (player[o][l].GetRank()==11) 
								{
									cout<<" in Jacks "<<"\n";
									PlayerPoints[o].push_back(11);
								}
								else if (player[o][l].GetRank()==12)
								{
									cout<<" in Queens "<<"\n";
									PlayerPoints[o].push_back(12);
								}
								else if (player[o][l].GetRank()==13) 
								{
									cout<<" in Kings "<<"\n";
									PlayerPoints[o].push_back(13);
								}
								else 
								{
									cout<< " in " <<player[o][l].GetRank()<< "s "<<"\n";
									PlayerPoints[o].push_back(player[o][l].GetRank());
								}
							}
						};
					};
				};
				std::copy(temppoints[o].begin(),temppoints[o].end(),back_inserter(PlayerPoints[o]));
				
			}
		}
		else if (Wallet[o]==0)
		{
			PlayerPoints.erase(PlayerPoints.begin(),PlayerPoints.end());
			PlayerPoints[o].push_back(0);
			PIGstatus[o]=0;

		}

	};

	vector<vector<int>>::iterator winner_it = max_element ( PlayerPoints.begin(), PlayerPoints.end()) ; 
	cout<<"\n";
	cout<<"\n"<<con::fg_gray;
	for(int o=0;o<numberofplayers;o++)
	 {
		std::copy(PlayerPoints[o].begin(),PlayerPoints[o].end(),std::ostream_iterator<int> (cout,":"));
			cout<<"\n";
	};
	cout<< "			AnD tHe WinNeR(s) are/is:";
	for(int o=0;o<numberofplayers;o++)
	 {
		if (PlayerPoints[o]==*winner_it)
			{
				cout<<con::fg_magenta<<".... PLAYER "<<o<<con::fg_gray;
			    
			}
	};

	cout<<"\n";
	cout<<"\n";




	//PIGstatus contains the player statuses: if a player Checks status is: 1;
	//Raises: amount of bet+PIGsortedMAX;
	//if the player folds: 0, and if he calls: PIGsortedMAX;
	//PIGsortedMAX is the max_element of PIGsorted and 
	//PIGsorted filters the players who still haven't folded yet
	//it also sorts their in game money amounts...






		PIGstatus.erase(PIGstatus.begin(),PIGstatus.end());
		PIGstatusTEMP.erase(PIGstatusTEMP.begin(),PIGstatusTEMP.end());
		MIGTEMP.erase(MIGTEMP.begin(),MIGTEMP.end());
		
		
		for (int o=0;o<numberofplayers;o++) 
		{
			if (Wallet[o]>0)
			{
				PIGstatus.push_back(9000000);
				PIGstatusTEMP.push_back(9000000);
			}
			else if(Wallet[o]<=0)
			{
				PIGstatusTEMP.push_back(0);
				PIGstatus.push_back(0);
			
			}

			MIGTEMP.push_back(0);
			
		};
		OutOfGame = count(WALLETSIZE.begin(), WALLETSIZE.end(), 0);
		HaveFolded = count(PIGstatus.begin(), PIGstatus.end(), 0);
		breaker=0;
		loopcount=0;
		loopcount2=0;
		BetIncrement=0;
		HaveFolded=0;

	while (HaveFolded!=numberofplayers-1)
	{
		
		vector<int>::iterator::difference_type OutOfGame;
		for (int o=0;o<numberofplayers;o++)
		{
			if(Wallet[o]<=0)
			{
				Wallet[o]=0;
				WALLETSIZE[o]=0;
				PIGstatus[o]=0;
				PIGstatusTEMP[o]=0;
				
			}

			else if(Wallet[o]>0)
			{
				WALLETSIZE[o]=Wallet[o];
				if (PIGstatusTEMP[o]==9000000)
				{
					PIGstatusTEMP[o]=1;
				}
			}
		};
		
		OutOfGame=count(PIGstatus.begin(), PIGstatus.end(), 0);
		BetIncrement=BetIncrement+1;
		if (BetIncrement==5)
		{
			break;
		}
		vector<int>::iterator PIGsortedMAX = max_element ( PIGsorted.begin(),  PIGsorted.end()) ;
		
		int Pot=0;
		
		PIGsorted.erase(PIGsorted.begin(),PIGsorted.end());
		PIGsorted.push_back(0);
		//MIGTEMP[o] = 0;
		if (breaker==numberofplayers-1)
		{
			break;
		}

		if(BetIncrement==1)
			{
				MIG.erase(MIG.begin(), MIG.end());
				MIGTEMP.erase(MIGTEMP.begin(), MIGTEMP.end());
				vector<int> MIG(numberofplayers);
				vector<int> MIGTEMP(numberofplayers);
				cout<<con::fg_white<< "FLOP BETS"<<con::fg_gray;
				if(increment==1)
				{

					for(int o=0;o<numberofplayers;o++)
					{
						cout << "MIGRESET" << endl;
						
						MIG[o]=0;
						MIGTEMP[o]=0;
					};
				}
			}
			else if(BetIncrement==2)
			{
				cout<<con::fg_white<< "TURN BETS"<<con::fg_gray;
				Pot=Pot+accumulate(MIG.begin(),MIG.end(),0);
				
			}
			else if(BetIncrement==3)
			{
				cout<<con::fg_white<< "RIVER BETS"<<con::fg_gray;
				Pot=Pot+accumulate(MIG.begin(),MIG.end(),0);
				
			}
			else if(BetIncrement==4)
			{
				cout<< con::fg_white<<"FINAL BETS"<<con::fg_gray;
				Pot=Pot+accumulate(MIG.begin(),MIG.end(),0);
				
				
			}
			cout<< "\n";
			cout<< "\n";
			
		
		if (PIGstatusTEMP[0]!=0)
		{
			
			if(PIGstatus[0]==9000000)
			{
				remove_zeros(PIGstatus);
			}
			
			if (PIGstatusTEMP[0]==9000000)
			{
				PIGstatusTEMP[0]==1;
			}
			
			if(Wallet[0]<=0)
			{
				Wallet[0]=0;
				PIGstatus[0]=0;
				PIGstatusTEMP[0]=0;
				WALLETSIZE[0]=0;
				goto ici;
				
			}
			
			else if(Wallet[0]>0)
			{
				cout<<con::fg_magenta<<"PLAYER 0: "<<con::fg_gray<<endl<<"Your cards: "<<con::fg_blue;
				std::copy(player[0].begin(),player[0].end()-5,std::ostream_iterator<Card> (cout," : "));
				cout<<"\n"<<con::fg_gray;
				cout<<"Your wallet: "<<con::fg_yellow<<Wallet[0]<<con::fg_gray;
				cout<<"\n";
				cout<<"Action: Check, Raise, or Fold?";
				if (PlayerType[0]=="Human")
				{
					cin>>action;
				}
				else if(PlayerType[0]=="Computer")
				{
					if(max(player[0][0].GetRank(),player[0][1].GetRank())>9|min(player[0][0].GetRank(),player[0][1].GetRank())==1)
					{
						action="Raise";cout<<con::fg_cyan<<"Raise"<<con::fg_gray;
					}
					else
					{
						action="Check";cout<<con::fg_cyan<<"Check"<<con::fg_gray;
					}
				
				}
				if (action=="Check") 
				{
					if(PIGstatus.size()==0)
					{
						PIGstatus.push_back(1);
						if(PIGstatusTEMP.size()==0)
						{
							PIGstatusTEMP.push_back(1);
						}
						else if (PIGstatusTEMP.size()>0)
						{
							PIGstatusTEMP[0]=1;
						}

						if (MIG.size()==0)
						{
							MIG.push_back(0);
						}
					
						if (MIGTEMP.size()==0)
						{
							MIGTEMP.push_back(MIG[0]);
						}
						
					
					}	
					else if(PIGstatus.size()!=0)
					{
						PIGstatus[0]=1;
						if(PIGstatusTEMP.size()==0)
						{
							PIGstatusTEMP.push_back(1);
						}
						else if (PIGstatusTEMP.size()>0)
						{
							PIGstatusTEMP[0]=1;
						}

						if (MIG.size()==0)
						{
							MIG.push_back(0);
						}
					
						if (MIGTEMP.size()==0)
						{
							MIGTEMP.push_back(MIG[0]);
						}
					
					}
					
				}

				if (action=="Raise") 
				{
					PIGsorted.push_back(0);
				
					vector<int>::iterator PIGsortedMAX = max_element ( PIGstatus.begin(),  PIGstatus.end()) ;
				
					cout<<"Raise by?";
					if(PlayerType[0]=="Human")
					{
						cin>>bet;

					}
					else if(PlayerType[0]=="Computer")
					{
					bet=10;cout<<con::fg_cyan<<10<<endl<<con::fg_gray;
					}
					if (Wallet[0]-bet<=0)
					{
						AllIn[0]=Wallet[0]+ MIG[0];
						bet=Wallet[0];

					}

					PIGsorted.push_back(0);
					

					
					if(PIGstatus.size()==0)
					{
						if (MIG.size()==0)
						{
							MIG.push_back(bet);
						}
						else if (MIG.size()!=0)
						{
							MIG[0]=bet;
						}

						PIGstatus.push_back(bet);
					
						if (PIGstatusTEMP.size()!=0)
						{
							PIGstatusTEMP[0]=bet;
						}
						else if(PIGstatusTEMP.size()==0)
						{
							PIGstatusTEMP.push_back(bet);
						}
							vector<int>::iterator MIGMAX = max_element ( MIG.begin(),  MIG.end()) ;
						if (*MIGMAX!=MIG[0]) 
						{
							cout << "CASE MIGMAX DIFFERENT FROM MIG[0]" << endl;
							cout << "Wallet[0]" << Wallet[0] << endl;
							cout << "*MIGMAX" << *MIGMAX << endl;
							cout << "MIGTEMP[0]" << MIGTEMP[0] << endl;
							cout << "Bet" << bet << endl;
							if (Wallet[0]-(*MIGMAX-MIGTEMP[0]+bet)>0)
							{
								Wallet[0]=Wallet[0]-(*MIGMAX-MIGTEMP[0]+bet);
							}
							else if (Wallet[0]-(*MIGMAX-MIGTEMP[0]+bet)<=0)
							{
								Wallet[0]=0;
							}
						}
						else if(*MIGMAX==MIG[0]) 
						{
							if (Wallet[0]-bet>0)
							{
								Wallet[0]=Wallet[0]-bet;
							}
							else if (Wallet[0]-bet<=0)
							{
								Wallet[0]=0;
								AllIn[0]=bet;
								MIG[0]=bet;
								MIGTEMP[0]=bet;
							}
						}
						if (MIGTEMP.size()!=0)
						{
							MIGTEMP[0]=MIG[0];
						}
						else if (MIGTEMP.size()==0)
						{
							MIGTEMP.push_back(MIG[0]);
						}
						
					}

					else if (PIGstatus.size()!=0)
					{
						PIGstatus[0]=*PIGsortedMAX+bet;
						if (PIGstatusTEMP.size()!=0)
						{
							if (PIGstatusTEMP[0]==9000000)
							{
								PIGstatusTEMP[0]=1;
							}
							PIGstatusTEMP[0]=PIGstatusTEMP[0]+bet;
						}

						else if(PIGstatusTEMP.size()==0)
						{
							PIGstatusTEMP.push_back(PIGstatusTEMP[0]+bet);
						}
						if (MIG.size()!=0)
						{
							cout << "MIG=" << endl;
							for (int i = 0; i < MIG.size(); i++)
							{
								cout << MIG[i] << ";";
							};
							cout << endl;
							cout << "MIGTEMP=" << endl;
							for (int i = 0; i < MIGTEMP.size(); i++)
							{
								cout << MIGTEMP[i] << ";";
							};
							cout << endl;
							vector<int>::iterator MIGMAX = max_element(MIG.begin(), MIG.end());
							cout << "*MIGMAX=" << *MIGMAX << endl;
							cout << "MIGTEMP[0]" << MIGTEMP[0] << endl;
							if (Wallet[0]-(*MIGMAX-MIGTEMP[0]+bet)>0)
							{
								MIG[0]=MIG[0]+bet;
							}
							else if (Wallet[0]-(*MIGMAX-MIGTEMP[0]+bet)<=0)
							{
								Wallet[0]=0;
								MIG[0]=Wallet[0]+MIGTEMP[0];
								AllIn[0]=Wallet[0]+MIGTEMP[0];
							}
						}
						else if(MIG.size()==0)
						{
							MIG.push_back(bet);
						}
						vector<int>::iterator MIGMAX = max_element(MIG.begin(), MIG.end());
						if (*MIGMAX!=MIG[0]) 
						{
							if (Wallet[0]-(*MIGMAX-MIGTEMP[0]+bet)>0)
							{
								Wallet[0]=Wallet[0]-(*MIGMAX-MIGTEMP[0]+bet);
							}
							else if (Wallet[0]-(*MIGMAX-MIGTEMP[0]+bet)<=0)
							{
								Wallet[0]=0;
								AllIn[0]=Wallet[0]+MIGTEMP[0];
							}
						}
						else if(*MIGMAX==MIG[0]) 
						{
							if (Wallet[0]-bet>0)
							{
								Wallet[0]=Wallet[0]-bet;
							}
							else if (Wallet[0]-bet<=0)
							{
								AllIn[0]=Wallet[0]+MIGTEMP[0];
								Wallet[0]=0;
							}
						}

						if (MIGTEMP.size()!=0)
						{
							MIGTEMP[0]=MIG[0];
						}
						else if(MIGTEMP.size()<0)
						{
							MIGTEMP.push_back(MIG[0]);
						}		
					}	
					
				}	

				if(action=="Fold")
				{
					if(PIGstatus.size()==0)
					{
						PIGstatus.push_back(0);
						if(PIGstatusTEMP.size()==0)
						{
							PIGstatusTEMP.push_back(0);
						}
						else if (PIGstatusTEMP.size()>0)
						{
							PIGstatusTEMP[0]=0;
						}

						if (MIG.size()==0)
						{
							MIG.push_back(0);
						}
						
						if (MIGTEMP.size()==0)
						{
							MIGTEMP.push_back(MIG[0]);
						}
						
						//Wallet[0]=Wallet[0]-MIG[0];
					}
					else
					{
						PIGstatus[0]=0;
						if(PIGstatusTEMP.size()==0)
						{
							PIGstatusTEMP.push_back(0);
						}
						else if (PIGstatusTEMP.size()>0)
						{
							PIGstatusTEMP[0]=0;
						}

						if (MIG.size()==0)
						{
							MIG.push_back(0);
						}
						
						if (MIGTEMP.size()==0)
						{
							MIGTEMP.push_back(MIG[0]);
						}
					
						//Wallet[0]=Wallet[0]-MIG[0];
					}
					HaveFolded = count(PIGstatus.begin(), PIGstatus.end(), 0);
					breaker=HaveFolded;
					
				} 

				

				if (PIGstatus[0]!=9000000)
				{
					PIGsorted.push_back(PIGstatus[0]);
				}
				Pot= accumulate(MIG.begin(), MIG.end(), 0);
				cout<<"The Pot: "<<Pot;
				cout<<"\n";
				cout<<"Your wallet: "<<con::fg_yellow<<Wallet[0]<<con::fg_gray;
				cout<<"\n";
				cout<<"\n";
				
				HaveFolded = count(PIGstatus.begin(), PIGstatus.end(), 0);
		
			}
			
			
			
		}
	
ici:
		int loop3;
		loop3=0;
		loop3=loop3+1;
		vector<int>::iterator::difference_type HaveFolded;

		HaveFolded = count(PIGstatus.begin(), PIGstatus.end(), 0);
		breaker=HaveFolded;
	
			
			for (int o=1;o<numberofplayers;o++)
			{
				PIGsorted.push_back(0);
				if (Wallet[o]<=0)
				{
					
					if (PIGstatus.size()<=o)
					{
						PIGstatus.push_back(0);
					}
					else if (PIGstatus.size()>o)
					{
						vector<int>::iterator PIGsortedMAX = max_element ( PIGsorted.begin(),  PIGsorted.end()) ;
						if (AllIn[o]==0)
						{
							PIGstatus[o]=0;
						}
						else if (AllIn[o]!=0)
						{
							PIGstatus[o]=*PIGsortedMAX;
						}
					}
					if (PIGstatusTEMP.size()<=o)
					{
						PIGstatusTEMP.push_back(0);
					}
					else if(PIGstatusTEMP.size()>o)
					{
						PIGstatusTEMP[o]=0;
					}
					if (MIGTEMP.size()<=o)
					{
						MIGTEMP.push_back(0);
					}
					
					else if (MIG.size()<=o)
					{
						MIG.push_back(0);
					}


					Wallet[o]=0;
					HaveFolded = count(PIGstatus.begin(), PIGstatus.end(), 0);
					
					continue;
					
					
					
				}
				else if (Wallet[o]>0)
				{
					
					vector<int>::iterator::difference_type HaveFolded;
					HaveFolded = count(PIGstatus.begin(), PIGstatus.end(), 0);
				
									
					if(HaveFolded == numberofplayers-1)
					{
						break;
					}
					if(PIGsorted.size()==0)
					{
						PIGsorted.push_back(0);
					}	
					std::sort(PIGsorted.begin(),PIGsorted.end());
					vector<int>::iterator PIGsortedMAX = max_element ( PIGsorted.begin(),  PIGsorted.end()) ;
				
				

					if(PIGstatus[o]!=0)
					{
						cout << "PIGstatusTEMP[o]" << PIGstatusTEMP[o] << endl;
						if (*PIGsortedMAX<2)
						{
							cout<<con::fg_magenta<<"PLAYER"<<o<<":"<<con::fg_gray<<endl<<"Cards: "<<con::fg_blue;
							std::copy(player[o].begin(),player[o].end()-5,std::ostream_iterator<Card> (cout," : "));
							cout<<"\n"<<con::fg_gray;
							cout<<"Your wallet:" <<con::fg_yellow<<Wallet[o]<<con::fg_gray;
							cout<<"\n";
							cout<<"Action: Check, Raise, or Fold?";
						
							if(PlayerType[o]=="Human")
							{
								cin>>action;
							}
							else if(PlayerType[o]=="Computer")
							{
								if(loop3<5&&max(player[o][0].GetRank(),player[o][1].GetRank())>9|min(player[o][0].GetRank(),player[o][1].GetRank())==1)
								{
									cout<<con::fg_cyan<<"Raise"<<con::fg_gray<<endl;action="Raise";
								}
								else if(max(player[o][0].GetRank(),player[o][1].GetRank())<=9&&min(player[o][0].GetRank(),player[o][1].GetRank())!=1)
								{
									cout<<con::fg_cyan<<"Check"<<con::fg_gray<<endl;action="Check";
								}

								else 
								{
									cout<<con::fg_cyan<<"Fold"<<con::fg_gray<<endl;action="Fold";
								}

							}

							if (action=="Check") 
							{
								if (PIGstatus.size()<=o)
								{
									PIGstatus.push_back(1);
									if(PIGstatusTEMP.size()<=o)
									{
										PIGstatusTEMP.push_back(PIGstatus[o]);
									}
									
									if (MIG.size()<=o)
									{
										MIG.push_back(0);
									}
								
									
									else if(MIGTEMP.size()<=o)
									{
										MIGTEMP.push_back(MIG[o]);
									}
									


								}
								else if (PIGstatus.size()>o)
								{
									PIGstatus[o]=1;
								}
								if (PIGstatusTEMP.size()<=o)
								{
									PIGstatusTEMP.push_back(1);
								}
							
								if(MIG.size()<=o)
								{
									MIG.push_back(0);
								}
								
								if(MIGTEMP.size()<=o)
								{
									MIGTEMP.push_back(MIG[o]);
								}
							
								

							}

							if (action=="Raise") 
							{	
								vector<int>::iterator MIGMAX = max_element ( MIG.begin(),  MIG.end()) ;
								cout<<"Raise by?";
								if(PlayerType[o]=="Human")
								{
									cin>>bet;
								}
								else if(PlayerType[o]=="Computer")
								{
									bet=10;cout<<con::fg_cyan<<10<<endl<<con::fg_gray;
								}
								if (Wallet[o]-bet<=0)
								{
									bet=Wallet[o];
									AllIn[o]=Wallet[o]+MIGTEMP[o];
								}

								if (PIGstatus.size()<=o)
								{
					
									PIGstatus.push_back(bet);	

									if (PIGstatusTEMP.size()<=o)
									{
										PIGstatusTEMP.push_back(PIGstatus[o]);
									}
									else if (PIGstatusTEMP.size()>o)
									{
										PIGstatusTEMP[o]=PIGstatus[o];
										
									}
									if(MIG.size()<=o)
									{
										MIG.push_back(bet);
									}
									//Modif apportée ici MIG[o]=bet
									else if(MIG.size()>o)
									{
										MIG[o]=MIG[o]+bet;
									}
									
								
									cout << "IS THE ERROR HERE?" << endl;
									Wallet[o]=Wallet[o]-MIG[o];
						
									if (MIGTEMP.size()<=o)
									{
										MIGTEMP.push_back(MIG[o]);
									}
									else if(MIGTEMP.size()>o)
									{
										MIGTEMP[o]=MIG[o];
									}			
								}
								else if (PIGstatus.size()>o)
								{
									if (*PIGsortedMAX!=1)
									{
										PIGstatus[o]=(bet+ *PIGsortedMAX);
									}
									else if (*PIGsortedMAX==1)
									{
										PIGstatus[o]=(bet);
									}

									if (PIGstatusTEMP.size()<=o)
									{
										PIGstatusTEMP.push_back(PIGstatus[o]);
									}
									else if (PIGstatusTEMP.size()>o)
									{
										PIGstatusTEMP[o]=PIGstatus[o];
										
									}
									
									if (MIG.size()<=o)
									{
										
										if (Wallet[o]-(*MIGMAX+bet-MIGTEMP[o])>0)
										{
											MIG.push_back(*MIGMAX+bet);
										}
										else if (Wallet[o]-(*MIGMAX+bet-MIGTEMP[o])<=0)
										{
											MIG.push_back(Wallet[o]+MIGTEMP[o]);
											AllIn[o]=Wallet[o]+MIGTEMP[o];
										}
									}
									else if (MIG.size()>o)
									{
										if (Wallet[o]-(*MIGMAX+bet-MIGTEMP[o])>0)
										{
											MIG[o]=*MIGMAX+bet;
										}
										else if (Wallet[o]-(*MIGMAX+bet-MIGTEMP[o])<=0)
										{
											MIG[o]=Wallet[o]+MIGTEMP[o];
											AllIn[o]=MIG[o];
										}

									}
									cout << "In loop once" << endl;
									Wallet[o]=Wallet[o]-(MIG[o]-MIGTEMP[o]);
									if (MIGTEMP.size()<=o)
									{
										MIGTEMP.push_back(MIG[o]);
									}
									else if(MIGTEMP.size()>o)
									{
										MIGTEMP[o]=MIG[o];
									}		
								}
							}
			
							if(action=="Fold")
							{
								if (PIGstatus.size()<=o)
								{
									PIGstatus.push_back(0);
									if (MIG.size()<=o)
									{
										MIG.push_back(0);
									}
								
								
									if (MIGTEMP.size()<=o)
									{
										MIGTEMP.push_back(MIG[o]);
									}
									else
									{
										MIGTEMP[o] = MIG[o];
									}
								
									if (PIGstatusTEMP.size()<=o)
									{
										PIGstatusTEMP.push_back(0);
									}
									else if(PIGstatusTEMP.size()>o)
									{
										PIGstatusTEMP[o]=0;
									}
									

								}
								else if (PIGstatus.size()>o)
								{
									PIGstatus[o]=0;
									if (MIG.size()<=o)
									{
										MIG.push_back(0);
									}
								
									if (MIGTEMP.size()<=o)
									{
										MIGTEMP.push_back(MIG[o]);
									}
								
									if (PIGstatusTEMP.size()<=o)
									{
										PIGstatusTEMP.push_back(0);
									}
									else if(PIGstatusTEMP.size()>o)
									{
										PIGstatusTEMP[o]=0;
									}
									
								}
								HaveFolded = count(PIGstatus.begin(), PIGstatus.end(), 0);
								breaker=HaveFolded;
								
							} 
							if (HaveFolded==numberofplayers-1)
							{
								break;
							}
					
						
							Pot= accumulate(MIG.begin(), MIG.end(), 0);
							cout<<"The Pot: "<<Pot;
							cout<<"\n";
							cout<<"Your new wallet size: "<<con::fg_yellow<<Wallet[o]<<con::fg_gray;
							cout << "Here3";
							cout<<"\n";
							cout<<"\n";
				
						}
						
						
		//this is the case where at least one player has Raised

						else if (*PIGsortedMAX>=2)
						{		
							cout<<con::fg_magenta<<"PLAYER"<<o<<":"<<con::fg_gray<<endl<<"Cards: "<<con::fg_blue;
							std::copy(player[o].begin(),player[o].end()-5,std::ostream_iterator<Card> (cout," : "));
							cout<<"\n"<<con::fg_gray;
							cout<<"Your wallet: "<<con::fg_yellow<<Wallet[o];
							cout<<"\n"<<con::fg_gray;
							cout<<"Action: Call, Raise, or Fold?";
							if (PlayerType[o]=="Human")
							{
								cin>>action;
							}
							else if(PlayerType[o]=="Computer")
							{
								if(max(player[o][0].GetRank(),player[o][1].GetRank())>9|min(player[o][0].GetRank(),player[o][1].GetRank())==1)
								{
									cout<<con::fg_cyan<<"Call"<<con::fg_gray<<endl;action="Call";
								}
								else if(PlayerPoints[o][0]>=2)
								{
									cout<<con::fg_cyan<<"Raise"<<con::fg_gray<<endl;action="Raise";
								}

								else
								{
									cout<<con::fg_cyan<<"Fold"<<con::fg_gray<<endl;action="Fold";
								}
								 
							}

				
							if (action=="Call") 
							{
								vector<int>::iterator MIGMAX = max_element ( MIG.begin(),  MIG.end()) ;
								vector<int>::iterator PIGsortedMAX = max_element(PIGsorted.begin(), PIGsorted.end());

							
								if (PIGstatus.size()<=o)
								{

									PIGstatus.push_back(*PIGsortedMAX);	
									
									if (MIG.size()<=o)
									{
										cout << "MIGTEMP[o]" << MIGTEMP[o] << endl;
										
										if (Wallet[o]-(*MIGMAX-MIGTEMP[o])>0)
										{
											MIG.push_back(*PIGsortedMAX);
											AllIn[o]=0;
										}
										else if(Wallet[o]-(*MIGMAX-MIGTEMP[o])<=0)
										{
											MIG.push_back(Wallet[o]+MIGTEMP[o]);
											AllIn[o]=Wallet[o]+MIGTEMP[o];
										}
									}
									else if(MIG.size()>o)
									{
										if (Wallet[o]-(*MIGMAX-MIGTEMP[o])>0)
										{
											MIG[o]=*PIGsortedMAX;
											AllIn[o]=0;
										}
										else if (Wallet[o]-(*MIGMAX-MIGTEMP[o])<=0)
										{
											MIG[o]=Wallet[o]+MIGTEMP[o];
											AllIn[o]=Wallet[o]+MIGTEMP[o];
										}
									}

									cout << "CALL ERROR DEBUG" << endl;
									cout << "*MIGMAX" << *MIGMAX << endl;
									cout << "MIGTEMP[o]" << MIGTEMP[o] << endl;
									cout << "MIGTEMP" << endl;
									for (int l = 0; l < numberofplayers; l++)
									{
										cout << MIGTEMP[l] << ":";
									};
									cout << endl;
									cout << "MIG" << endl;
									for (int l = 0; l < numberofplayers; l++)
									{
										cout << MIG[l] << ":";
									};
									cout << endl;

									Wallet[o]=Wallet[o]-(*MIGMAX-MIGTEMP[o]);
									
									if (MIGTEMP.size()<=o)
									{
										if(Wallet[o]-(*MIGMAX-MIGTEMP[o])>0)
										{
											MIGTEMP.push_back(*MIGMAX);
										}
										else if (Wallet[o]-(*MIGMAX-MIGTEMP[o])<=0)
										{
											MIGTEMP.push_back(Wallet[o]+MIGTEMP[o]);
										}
									}
									else if(MIGTEMP.size()>o)
									{
										vector<int>::iterator MIGMAX = max_element ( MIG.begin(),  MIG.end()) ;
										PIGsortedMAX = max_element(PIGsorted.begin(), PIGsorted.end());
										if (Wallet[o]-*MIGMAX+MIGTEMP[o]>0)
										{
											MIGTEMP[o]=*MIGMAX;
										}
										else if (Wallet[o]-*MIGMAX+MIGTEMP[o]<=0)
										{
											MIGTEMP[o]=Wallet[o]+MIGTEMP[o];
										}
									}
									if (PIGstatusTEMP.size()<=o)
									{
									PIGstatusTEMP.push_back(*PIGsortedMAX);
									}
									else PIGstatusTEMP[o]=*PIGsortedMAX;
									Pot= accumulate(MIG.begin(), MIG.end(), 0);
									
								}
								else if (PIGstatus.size()>o)
								{ 
									vector<int>::iterator MIGMAX;
									MIGMAX = max_element(MIG.begin(), MIG.end());
									PIGsortedMAX = max_element(PIGsorted.begin(), PIGsorted.end());
									PIGstatus[o]=*PIGsortedMAX;

									if (PIGstatusTEMP.size()<=o)
									{
										PIGstatusTEMP.push_back(*PIGsortedMAX);
									}
									else {PIGstatusTEMP[o]=*PIGsortedMAX;}

									Pot= accumulate(MIG.begin(), MIG.end(), 0);
									if (MIG.size()>o)
									{
										if (Wallet[o]-(*MIGMAX-MIGTEMP[o])>0)
										{
											MIG[o]=*MIGMAX;
										}
										else if (Wallet[o]-(*MIGMAX-MIGTEMP[o])<=0)
										{
											MIG[o]=Wallet[o]+MIGTEMP[o];
											AllIn[o]=MIG[o];
										}
									}
									else if (MIG.size()<=o)
									{
										if (Wallet[o]-(*MIGMAX-MIGTEMP[o])>0)
										{
											MIG.push_back(*MIGMAX);
										}
										else if (Wallet[o]-(*MIGMAX-MIGTEMP[o])<=0)
										{
											MIG.push_back(max(Wallet[o]+MIGTEMP[o],AllIn[o]));
										}
									}
								    cout << "CALL ERROR DEBUG" << endl;
									cout << "*MIGMAX" << *MIGMAX << endl;
									cout << "MIGTEMP[o]" << MIGTEMP[o] << endl;
									cout << "MIGTEMP" << endl;
									for (int l = 0; l < numberofplayers; l++)
									{
										cout << MIGTEMP[o] << ":";
									}
									cout << endl;
									cout << "MIG" << endl;
									for (int l = 0; l < numberofplayers; l++)
									{
										cout << MIG[o] << ":";
									}
									cout << endl;


			    					Wallet[o]=Wallet[o]-(*MIGMAX-MIGTEMP[o]);

									if (MIGTEMP.size()>o)
									{
										MIGTEMP[o]=MIG[o];
									}
									else if (MIGTEMP.size()<=o)
									{
										MIGTEMP.push_back(MIG[o]);
									}
									
									
								
									Pot= accumulate(MIG.begin(), MIG.end(), 0);

									
									
								}
								

								
							}
							if (action=="Raise") 
							{
								cout<<"Raise by?";
								if (PlayerType[o]=="Human")
								{
									cin>>bet;
								}
								if (PlayerType[o]=="Computer")
								{
								bet=10;cout<<con::fg_cyan<<10<<endl<<con::fg_gray;
								}

								if (PIGstatus.size() <= o)
								{
									MIGMAX = max_element(MIG.begin(), MIG.end());
									PIGsortedMAX = max_element(PIGsorted.begin(), PIGsorted.end());
									PIGstatus.push_back(bet + *PIGsortedMAX);
									if (MIG.size() <= o)
									{
										cout << "MIG size" << MIG.size() << endl;
										if (Wallet[o] - (bet + *MIGMAX - MIGTEMP[o]) > 0)
										{
											cout << "MIGTEMP[o]" << MIGTEMP[o] << endl;
											cout << "MIGMAX*" << *MIGMAX << endl;
											cout << " BET" << bet << endl;
											MIG.push_back(bet + *MIGMAX);
										}
										else if (Wallet[o] - (bet + *MIGMAX - MIGTEMP[o]) <= 0)
										{
											MIG.push_back(Wallet[o] + MIGTEMP[o]);
										}
									}
									else if (MIG.size() > o)
									{
										if (Wallet[o] - (bet + *MIGMAX - MIGTEMP[o]) > 0)
										{
											MIG[o] = bet + *MIGMAX;
										}
										else if (Wallet[o] - (bet + *MIGMAX - MIGTEMP[o]) >= 0)
										{
											MIG[o] = Wallet[o] + MIGTEMP[o];
										}
									}

									if (PIGstatusTEMP.size() > o)
									{
										PIGstatusTEMP[o] = bet + *PIGsortedMAX;
									}

									else if (PIGstatusTEMP.size() <= o)
									{
										PIGstatusTEMP.push_back(bet + *PIGsortedMAX);
									}
									//cout << "WALLET DEFINED BY" << endl;
									//Wallet[o] = Wallet[o] - (MIG[o] - MIGTEMP[o]);

									Wallet[o] = Wallet[o] - (bet + *MIGMAX - MIGTEMP[o]);

									if (MIGTEMP.size() <= o)
									{
										if (Wallet[o] - (bet + *PIGsortedMAX - MIGTEMP[o]) > 0)
										{
											MIGTEMP.push_back(bet + *PIGsortedMAX);
										}
										else if (Wallet[o] - (bet + *PIGsortedMAX - MIGTEMP[o]) <= 0)
										{
											MIGTEMP.push_back(Wallet[o] + MIGTEMP[o]);
											AllIn[o] = Wallet[o] + MIGTEMP[o];
										}

									}
									else if (MIGTEMP.size() > o)
									{
										if (Wallet[o] - (bet + *PIGsortedMAX - MIGTEMP[o]) > 0)
										{
											MIGTEMP[o] = bet + *PIGsortedMAX;
										}
										else if (Wallet[o] - (bet + *PIGsortedMAX - MIGTEMP[o]) <= 0)
										{
											MIGTEMP[o] = Wallet[o] + MIGTEMP[o];
											AllIn[o] = Wallet[o] + MIGTEMP[o];
										}
									}
									//cout << "WALLET DEFINED BY 2:" << endl;
									//Wallet[o] = Wallet[o] - (MIG[o]-MIGTEMP[o]);
									cout << "MIGTEMP" << endl;
									for (int l = 0; l < numberofplayers; l++)
									{
										cout << MIGTEMP[l]<<":";
									}
									cout << endl;
									cout << "MIG" << endl;
									for (int l = 0; l < numberofplayers; l++)
									{
										cout << MIG[l] << ":";
									}
									cout << endl;

								}
								else if (PIGstatus.size()>o)
								{
									if (PIGstatusTEMP.size()>o)
									{
										PIGstatusTEMP[o]=bet+ *PIGsortedMAX;
									}
									else if (PIGstatusTEMP.size()<=o)
									{
										PIGstatusTEMP.push_back(bet+ *PIGsortedMAX);
									}
									PIGstatus[o]=(bet+ *PIGsortedMAX);
									
									if (MIG.size()>o)
									{
										if (Wallet[o]-*MIGMAX+MIGTEMP[o]-bet>0)
										{
											MIG[o]=*MIGMAX+bet;
										}
										else if (Wallet[o]-*MIGMAX+MIGTEMP[o]-bet<=0)
										{
											MIG[o]=Wallet[o]+MIGTEMP[o];
											AllIn[o]=MIG[o];
										}
									}
									else if(MIG.size()<=o)
									{
										if (Wallet[o]-*MIGMAX+MIGTEMP[o]-bet>0)
										{
											MIG.push_back(*MIGMAX+bet);
										}
										else if (Wallet[o]-*MIGMAX+MIGTEMP[o]-bet<=0)
										{
											MIG.push_back(Wallet[o]+MIGTEMP[o]);
											AllIn[o]=MIG[o];
										}

									}
									cout << "WALLET DEFINED BY 3" << endl;
									Wallet[o]=Wallet[o] -(MIG[o]-MIGTEMP[o]);

									if (MIGTEMP.size()>o)
									{
										MIGTEMP[o]=MIG[o];
									}
									else if (MIGTEMP.size()<=o)
									{
										MIGTEMP.push_back(MIG[o]);
									}
									

									
								}
								

								Pot= accumulate(MIG.begin(), MIG.end(), 0);
							}

							if(action=="Fold")
							{
								if (PIGstatus.size()<=o)
								{
									PIGstatus.push_back(0);
									if(PIGstatusTEMP.size()<=o)
									{
										PIGstatus.push_back(PIGstatus[o]);
									}
									else if(PIGstatusTEMP.size()>o)
									{
										PIGstatus[o]=PIGstatus[o];
									}
									if(MIG.size()<=o)
									{
										MIG.push_back(0);
									}
									if (MIGTEMP.size() < o)
									{
										MIGTEMP.push_back(0);
									}
								}
								else if (PIGstatus.size()>o)
								{
									cout << "IN HERE MIG" << endl;
									for (int l = 0; l < numberofplayers; l++)
									{
										cout << MIG[l]<<":";
									}
									PIGstatus[o]=0;
									if(PIGstatusTEMP.size()<=o)
									{
										PIGstatus.push_back(PIGstatus[o]);
									}
									else if(PIGstatusTEMP.size()>o)
									{
										PIGstatusTEMP[o]=PIGstatus[o];
									}
									if(MIG.size()<=o)
									{
										MIG.push_back(0);
									}
									if(MIGTEMP.size()<=o)
									{
										MIGTEMP.push_back(MIG[o]);
									}
								}
								HaveFolded = count(PIGstatus.begin(), PIGstatus.end(), 0);
								breaker=HaveFolded;
								
							}
						}
						
						HaveFolded = count(PIGstatus.begin(), PIGstatus.end(), 0);
						Pot=accumulate(MIG.begin(),MIG.end(),0);
						cout<<"The Pot: "<<Pot;
						cout<<"\n";
						cout<<"Your new wallet size: "<<con::fg_yellow<<Wallet[o]<<con::fg_gray;
						cout << "Here1";
						cout<<"\n";
						cout<<"\n";
					
				
						if (HaveFolded==numberofplayers-1)
						{
							break;
						}
				
					}
				}
		
				
				if (HaveFolded==numberofplayers-1)
				{
					break;
				}
	
				if(PIGsorted.size()!=0)
				{
					PIGsorted.erase(PIGsorted.begin(),PIGsorted.end());	
					for (int i=0;i<o+1;i++)
					{
						if (PIGstatus[i]!=0)
						{
							PIGsorted.push_back(PIGstatus[i]);
						}
					};
					std::sort(PIGsorted.begin(),PIGsorted.end());	
				}
				
				if (HaveFolded==numberofplayers-1)
				{
					break;
				}
			};
			
			int temp;
			if (PIGsorted.size() > 0)
			{
				vector<int>::iterator PIGsortedMAX = max_element(PIGsorted.begin(), PIGsorted.end());
				temp = *PIGsortedMAX;
				PIGsorted.erase(PIGsorted.begin(), PIGsorted.end());
			}
			for (int o=0;o<numberofplayers; o++)
			{
				if (PIGstatus[o]!=0)
				{
					PIGsorted.push_back(PIGstatus[o]);
				}
			};
			if (PIGsorted.size()!=0)
			{
				std::sort(PIGsorted.begin(),PIGsorted.end());
				cout<<"\n";
				cout<<"PIGstatus: ";
				std::copy(PIGstatus.begin(),PIGstatus.end(),std::ostream_iterator<int> (cout,":"));
				cout<<"\n";
				cout<<"PIGsorted: ";
				std::copy(PIGsorted.begin(),PIGsorted.end(),std::ostream_iterator<int> (cout,":"));	
				cout<<"\n";
				cout<<"MIGTEMP: ";
				std::copy(MIGTEMP.begin(),MIGTEMP.end(),std::ostream_iterator<int> (cout,":"));
				cout<<"\n";
				cout<<"MIG: ";
				std::copy(MIG.begin(),MIG.end(),std::ostream_iterator<int> (cout,":"));

			}
			cout<<"\n";
				

				while(PIGsorted[0]!= PIGsorted[PIGsorted.size()-1])
				{	
					
					loopcount=loopcount+1;
					vector<int>::iterator MIGMAX = max_element ( MIG.begin(),  MIG.end()) ;
					
					vector<int>::iterator::difference_type HaveFolded;
					HaveFolded = count(PIGstatus.begin(), PIGstatus.end(), 0);
					breaker=HaveFolded;
					if(HaveFolded==numberofplayers-1)
					{
						break;
					}

					for (int o=0;o<numberofplayers;o++)
					{
						WALLETSIZE[o]=Wallet[o];
						if(Wallet[o]<=0)
						{
							Wallet[o]=0;
							if (AllIn[o]==0)
							{
								PIGstatus[o]=0;
							}
							else if (AllIn[o]!=0)
							{
								PIGstatus[o]=*PIGsortedMAX;
							}

							PIGstatusTEMP[o]=0;
							WALLETSIZE[o]=0;
							HaveFolded = count(PIGstatus.begin(), PIGstatus.end(), 0);
							continue;
						}
						vector<int>::iterator::difference_type HaveFolded;
						HaveFolded = count(PIGstatus.begin(), PIGstatus.end(), 0);
						
						if(PIGsorted.size()==0)
						{
							PIGsorted.push_back(temp);
							vector<int>::iterator PIGsortedMAX = max_element ( PIGsorted.begin(),  PIGsorted.end()) ;
							int temp= *PIGsortedMAX;
							
						}	

						if (PIGstatus[o]==0&&AllIn[o]!=0)
						{
							cout<<con::fg_magenta<<"PLAYER"<<o<<":"<<con::fg_cyan<<" is allin ";
						}
						if (PIGstatus[o]!=0)
						{
							vector<int>::iterator PIGsortedMAX = max_element ( PIGsorted.begin(),  PIGsorted.end()) ;
							temp= *PIGsortedMAX;
							
							if (PIGstatus[o]<*PIGsortedMAX)
							{
								PIGsortedMAX = max_element ( PIGsorted.begin(),  PIGsorted.end()) ;				
								MIGMAX=max_element( PIGsorted.begin(),PIGsorted.end());
								cout<<con::fg_magenta<<"PLAYER"<<o<<":"<<con::fg_gray<<endl<<"Cards: "<<con::fg_blue;
								std::copy(player[o].begin(),player[o].end()-5,std::ostream_iterator<Card> (cout," : "));
								cout<<"\n"<<con::fg_gray;
								cout<<"Your wallet: "<<con::fg_yellow<<Wallet[o]<<con::fg_gray;
								cout<<"\n";
								cout<<"Action: Call, Raise, or Fold?";
								if (PlayerType[o]=="Human")
								{
									cin>>action;
								}
								else if(PlayerType[o]=="Computer")
								{
									if(PlayerPoints[o][0]<2)
									{
										cout<<con::fg_cyan<<"Fold"<<con::fg_gray<<endl;action="Fold";

									}
									
									else if(PlayerPoints[o][0]>2&&loopcount<=3)
									{
										cout<<con::fg_cyan<<"Raise"<<endl<<con::fg_gray;action="Raise";
									}
									else 
									{
										cout<<con::fg_cyan<<"Call"<<con::fg_gray<<endl;action="Call";
									}
								}


								if (action=="Call")
								{
									MIGMAX=max_element(MIG.begin(),MIG.end());

									if (PIGstatus.size()>o)
									{
										PIGstatus[o]= *PIGsortedMAX;
									}
									else if(PIGstatus.size()<=o)
									{
										PIGstatus.push_back(*PIGsortedMAX);
									}

									if (MIG.size()>o)
									{
										if (Wallet[o]-*MIGMAX+MIGTEMP[o]>0)
										{
											MIG[o]=*MIGMAX;
										}
										else if (Wallet[o]-*MIGMAX+MIGTEMP[o]<=0)
										{
											MIG[o]=Wallet[o]+MIGTEMP[o];
											AllIn[o]=Wallet[o]+MIGTEMP[o];
										}
									}
									else if (MIG.size()<=o)
									{
										if (Wallet[o]-*MIGMAX+MIGTEMP[o]>0)
										{
											MIG.push_back(*MIGMAX);
										}
										else if (Wallet[o]-*MIGMAX+MIGTEMP[o]<=0)
										{
											MIG.push_back(Wallet[o]+MIGTEMP[o]);
											AllIn[o]=Wallet[o]+MIGTEMP[o];
										}
									}
									cout << "CALL WALLET" << endl;
									Wallet[o] = Wallet[o] - (*MIGMAX - MIGTEMP[o]);
									cout << "CALL ERROR DEBUG" << endl;
									cout << "*MIGMAX" << *MIGMAX << endl;
									cout << "MIGTEMP[o]" << MIGTEMP[o] << endl;
									cout << "MIGTEMP" << endl;
									for (int l = 0; l < numberofplayers; l++)
									{
										cout << MIGTEMP[l] << ":";
									}
									cout << endl;
									cout << "MIG" << endl;
									for (int l = 0; l < numberofplayers; l++)
									{
										cout << MIG[l] << ":";
									}
									cout << endl;
									
									if (MIGTEMP.size()<=o)
									{
										MIGTEMP.push_back(MIG[o]);
									}
									
									else if (MIGTEMP.size()>o)
									{
										MIGTEMP[o]=MIG[o];
									}
									
								}

								if (action=="Raise")
								{
									MIGMAX=max_element(MIG.begin(),MIG.end());
									cout<<"Raise by?";
									if (PlayerType[o]=="Human")
									{
										cin>> bet;
									}
									if (PlayerType[o]=="Computer")
									{
										bet=10;cout<<con::fg_cyan<<10<<endl<<con::fg_gray;
									}
									
									if (PIGstatus.size()>o)
									
									{
										PIGstatus[o]= *PIGsortedMAX + bet;	
									}
									else if(PIGstatus.size()<=o)
									{
										PIGstatus.push_back(*PIGsortedMAX + bet);
									}
									if (MIG.size()>o)
									{
										if (Wallet[o]-(*MIGMAX+bet-MIGTEMP[o])>0)
										{
											MIG[o]=*MIGMAX+bet;
											cout << "MIG[o]=" << MIG[o] << endl;
										}
										else if (Wallet[o]-(*MIGMAX+bet-MIGTEMP[o])<=0)
										{
											MIG[o]=MIGTEMP[o]+Wallet[o];
											AllIn[o]=MIG[o];
										}					
									}
									else if (MIG.size()<=o)
									{
										if (Wallet[o]-(*MIGMAX+bet-MIGTEMP[o])>0)
										{
											MIG.push_back(*MIGMAX+bet);
										}
										else if ( Wallet[o]-(*MIGMAX+bet-MIGTEMP[o])<=0)
										{
											MIG.push_back(Wallet[o]+MIGTEMP[o]);
										}

									}
									Wallet[o]=Wallet[o]-(bet+*MIGMAX-MIGTEMP[o]);
									cout << "*MIGMAX" << *MIGMAX << endl;
									cout << "MIGTEMP[o]" << MIGTEMP[o] << endl;
									if (MIGTEMP.size()>o)
									{
										MIGTEMP[o]=MIG[o];
									}
									else if(MIGTEMP.size()<=o)
									{
										MIGTEMP.push_back(MIG[o]);
									}
								}

								if (action=="Fold")
								{
									if (MIGTEMP.size() < o)
									{
										MIGTEMP.push_back(0);
									}
									else
									{
										MIGTEMP[o] = 0;
									}
									
									PIGstatus[o]=0;
									PIGstatusTEMP[o]=0;
									HaveFolded = count(PIGstatus.begin(), PIGstatus.end(), 0);
									breaker=HaveFolded;
									if(HaveFolded==numberofplayers-1)
									{
										break;
									}
								}
								PIGstatusTEMP[o]=PIGstatus[o];
								if (PIGsorted.size()!=0)
								{
									PIGsorted.erase(PIGsorted.begin(),PIGsorted.end());
									for (int i=0;i<o+1;i++)
									{
										if (PIGstatus[i]!=0)
										{
											PIGsorted.push_back(PIGstatus[i]);
										}
									};
								}
								HaveFolded = count(PIGstatus.begin(), PIGstatus.end(), 0);
								breaker=HaveFolded;
								Pot= accumulate(MIG.begin(), MIG.end(), 0);
								cout<<"The Pot: "<<Pot;
								cout<<"\n";
								cout<<"Your new wallet size: "<<con::fg_yellow<<Wallet[o]<<con::fg_gray;
								cout << "Here2";
								cout<<"\n";
								cout<<"\n";

							}	
							
						}
						vector<int>::iterator MIGMAX = max_element ( MIG.begin(),  MIG.end()) ;
						
						if(HaveFolded==numberofplayers-1)
						{
							break;
						}	
					};
				};	
				for (int o=0;o<numberofplayers;o++)
				{
					if(PIGstatus[o]!=0|AllIn[o]>0)
					{
						cout<<con::fg_magenta<<"Player"<<o<<con::fg_gray<<" still in game!";
						cout<<"\n";
					}
				};
			HaveFolded = count(PIGstatus.begin(), PIGstatus.end(), 0);
			if (HaveFolded==numberofplayers-1) goto here;
			
			cout<<"\n";
			cout<<"\n";
			
			if(BetIncrement==1)
			{
				Pot=Pot+ accumulate(MIG.begin(), MIG.end(), 0);
				cout<<con::fg_white<< "				FLOP: ";
				cout<<"\n";
				cout<<"\n";
				cout<<"						"<<con::fg_blue;
				std::copy(TableCards.begin(),TableCards.end()-2,std::ostream_iterator<Card> (cout,"\n						"));
				cout<<"\n"<<con::fg_gray;
				cout<<"\n";

			}
			else if(BetIncrement==2)
			{
				cout<<con::fg_white<< "				TURN: ";
				Pot=Pot+ accumulate(MIG.begin(), MIG.end(), 0);
				cout<<"\n";
				cout<<"\n";
				cout<<"						"<<con::fg_blue;
				cout<<TableCards[3];
				std::copy(TableCards.end()-1,TableCards.end()-1,std::ostream_iterator<Card> (cout,"\n						"));
				cout<<"\n"<<con::fg_gray;
				cout<<"\n";
			}
			else if(BetIncrement==3)
			{
				cout<<con::fg_white<< "				RIVER ";
				Pot=Pot+ accumulate(MIG.begin(), MIG.end(), 0);
				cout<<"\n";
				cout<<"\n";
				cout<<"						"<<con::fg_blue;
				std::copy(TableCards.end(),TableCards.end(),std::ostream_iterator<Card> (cout,"\n						"));
				cout<<TableCards[4]<<con::fg_gray;
				cout<<"\n";
				cout<<"\n";
			}
		
			
			
			//Display Vectors 
			cout<<"PIGsorted: ";
			std::copy(PIGsorted.begin(),PIGsorted.end(),std::ostream_iterator<int> (cout,":"));
			cout<<"\n";
			PIGsorted.erase(PIGsorted.begin(),PIGsorted.end());
			cout<<"PIGstatus: ";
			std::copy(PIGstatus.begin(),PIGstatus.end(),std::ostream_iterator<int> (cout,":"));
			cout<<"\n";
			cout<<"PIGstatusTEMP: ";
			std::copy(PIGstatusTEMP.begin(),PIGstatusTEMP.end(),std::ostream_iterator<int> (cout,":"));
			cout<<"\n";
			cout<<"MIG: ";
			std::copy(MIG.begin(),MIG.end(),std::ostream_iterator<int> (cout,":"));
			cout<<"\n";
			cout<<"MIGTEMP: ";
			std::copy(MIGTEMP.begin(),MIGTEMP.end(),std::ostream_iterator<int> (cout,":"));
			cout<<"\n";
			cout<<"AllIn: ";
			std::copy(AllIn.begin(),AllIn.end(),std::ostream_iterator<int> (cout,":"));
			cout<<"\n";
			cout<<"Wallet: ";
			std::copy(Wallet.begin(),Wallet.end(),std::ostream_iterator<int> (cout,":"));
			cout<<"\n";
			HaveFolded = count(PIGstatus.begin(), PIGstatus.end(), 0);
			cout<<"Have folded: ";
			cout<<HaveFolded;
			cout<<"\n";
			if (accumulate(Wallet.begin(),Wallet.end(),accumulate(MIG.begin(),MIG.end(),0))!=numberofplayers*walletsize)
			{
				int anint2;
				cout<<con::fg_red<<"ERROR !!!!!!!!!!!!"<<endl;
				cin>>anint2;
			}
			
			
			cout<<"\n";
			cout<<"\n";
			//end Display Vectors
		
			OutOfGame = count(Wallet.begin(), Wallet.end(), 0);

	};

here:

		std::vector<int> zeros;
		std::vector<vector<int>> PossibleWinnerPoints;
		vector<int>::iterator::difference_type OutOfGame;
		OutOfGame = count(Wallet.begin(), Wallet.end(), 0);
		Pot=accumulate(MIG.begin(),MIG.end(),0);
		int AllInCount;
		AllInCount=0;
		for (int o=0;o<numberofplayers;o++)
		{
			if(AllIn[o]!=0)
			{
				AllInCount=AllInCount+1;
			}
		};
       
		
		cout<<"accumulate(AllIn.begin(),AllIn.end()) "<<accumulate(AllIn.begin(),AllIn.end(),0)<<endl;

		if (HaveFolded==numberofplayers-1&&OutOfGame!=numberofplayers-1&&AllInCount==0)
		{
			cout<<"Only one player remains"<<endl;
		
			for(int o=0;o<numberofplayers;o++)
			{	
					if(Wallet[o]<=0)
					{
						Wallet[o]=0;
						WALLETSIZE[o]=0;
						PIGstatus[o]=0;
						PIGstatusTEMP[o]=0;
					
					}
				
				if (PIGstatus[o]!=0)
				{
				
					cout <<con::fg_magenta<<"PLAYER"<<o<<" WINS: "<<con::fg_yellow<<Pot<<con::fg_gray<<endl;
					Wallet[o]=Wallet[o]+Pot;
					if(Wallet[o]<=0)
					{
						PIGstatus[o]=0;
						PIGstatusTEMP[o]=0;
						Wallet[o]=0;
						WALLETSIZE[o]=0;
						continue;
					}
					cout<<"New wallet size: "<<Wallet[o]<<endl;
				}
				else if(PIGstatus[o]==0)
				{
				
					cout<<con::fg_magenta<<"PLAYER"<<o<<" Looses: "<<con::fg_gray<<MIG[o]<<endl;
					WALLETSIZE[o]=Wallet[o];
					
					cout<<"New wallet size: "<<Wallet[o]<<endl;
				}
					if(Wallet[o]<=0)
					{
						Wallet[o]=0;
						WALLETSIZE[o]=0;
						PIGstatus[o]=0;
						PIGstatusTEMP[o]=0;
						continue;
					}
			};
			
				vector<int>::iterator::difference_type OutOfGame;
				OutOfGame = count(Wallet.begin(), Wallet.end(), 0);
		}
		else if(HaveFolded!=numberofplayers-1&&OutOfGame!=numberofplayers-1|accumulate(AllIn.begin(),AllIn.end(),0)!=0)
		{
			cout<<"allInCase1";	
			std::vector<int> NotAllIn;
			std::vector<int> AllInsorted;
			std::vector<int> IndexesAllInsorted;
			int indexeswinner;
			int AllInCase;
			int numberallinwinners;
			int numbernotallinwinners;
			int primarypot;
			std::vector<int> WinnerNotAllIn;
			std::vector<int> WinnerAllIn;
			int indexes(PossibleWinner.size());
			int winnerfound;
			randomInteger a;
			unsigned int lucky;
			
			numberallinwinners=0;
			numbernotallinwinners=0;
			
			zeros.erase(zeros.begin(),zeros.end());
			for(int i=0;i<PlayerPoints.size()/(numberofplayers);i++)
			{
				zeros.push_back(0);
			};

			PossibleWinnerPoints.resize(PlayerPoints.size()*(numberofplayers-HaveFolded));
			
			
			for(int o=0;o<numberofplayers;o++)
			{	
			
				if (PIGstatus[o]!=0|AllIn[o]!=0)		
				{	
					PossibleWinnerPoints[o]=PlayerPoints[o];
					PossibleWinner.push_back(o);	
				}
				else if (PIGstatus[o]==0&&AllIn[o]==0)  
				{
					PossibleWinnerPoints[o]=zeros;
				}
			};
			
			


			//POTENTIAL START OF WINNER LOOP
			
			if (AllInsorted.size()!=0) 
			{
				AllInsorted.erase(AllInsorted.begin(),AllInsorted.end());
			}

			for(int o=0;o<numberofplayers;o++)
			{
				if (AllIn[o]!=0)
				{
					AllInsorted.push_back(AllIn[o]);
				}
			}

			if(AllInsorted.size()!=0)
			{
				for(int o=0;o<numberofplayers;o++)
				{
					if (AllIn[o]==0&&PIGstatus[o]!=0)
					{
						NotAllIn.push_back(MIG[o]);
					}
				};
				std::sort(AllInsorted.begin(),AllInsorted.end());
				std::copy(NotAllIn.begin(),NotAllIn.end(),back_inserter(AllInsorted));
			}
			if(AllInsorted.size()==0)
			{
				AllInsorted.push_back(0);
			}
			
			while (AllInsorted.size()!=0)
			{
			
				std::sort(AllInsorted.begin(),AllInsorted.end());
				PossibleWinnerPointsMAX= max_element(PossibleWinnerPoints.begin(),PossibleWinnerPoints.end());
				winnerfound=0;
				numberallinwinners=0;
				numbernotallinwinners=0;
				WinnerNotAllIn.erase(WinnerNotAllIn.begin(),WinnerNotAllIn.end());
				
				winnerfound=0;
				numbernotallinwinners=0;
				numberallinwinners=0;

				for(int o=0;o<numberofplayers;o++)
				{
					if (PlayerPoints[o]==*PossibleWinnerPointsMAX&&AllIn[o]==0)
					{	
						numbernotallinwinners=numbernotallinwinners+1;
						winnerfound=winnerfound+1;
						WinnerNotAllIn.push_back(o);
					}
				};
	
				
				for (int o=0;o<numberofplayers;o++)
				{
					if (PlayerPoints[o]==*PossibleWinnerPointsMAX&&AllIn[o]!=0)
					{
						numberallinwinners=numberallinwinners+1;
						winnerfound=winnerfound+1;
						WinnerAllIn.push_back(o);
					}
				}
				cout<<"Number of allinwinners: "<<numberallinwinners<<endl;
				cout<<"Numer of Notallinwinners: "<<numbernotallinwinners<<endl;
				if (numberallinwinners==0&&winnerfound>=1)
				{
					AllInCase=0;
				}
				
				if (numberallinwinners==1&&winnerfound==1)
				{
					AllInCase=1;
				}
	
				for (int o=0;o<numberofplayers;o++)
				{
					if(MIG[o]==0)
					{
						MIG[o]=AllIn[o];
					}
				}

				Pot=accumulate(MIG.begin(),MIG.end(),0);
		
				if(AllInCase==0)
				{
					for(int o=0;o<numberofplayers;o++)
					{
						if (PlayerPoints[o]==*PossibleWinnerPointsMAX&&AllIn[o]==0)
						{
							lucky=a(winnerfound);
							if (WinnerNotAllIn[lucky]==o)
							{
								Wallet[o]=Wallet[o]+Reste(Pot,winnerfound);
							}
						
							cout <<con::fg_magenta<<"PLAYER"<<o<<" WINS: "<<con::fg_yellow<<Pot/winnerfound<<con::fg_gray<<endl;
							Wallet[o]=Wallet[o]+ (Pot/winnerfound);
							cout<<"New wallet size: "<<Wallet[o]<<endl;
							cout<<"\n";
							
						}
				
					};
			
			
					for (int o=0;o<numberofplayers;o++)
					{
						if(PlayerPoints[o]!=*PossibleWinnerPointsMAX&&AllInCase==0)
						{	
							cout<<con::fg_magenta<<"PLAYER"<<o<<" Looses: "<<con::fg_gray<<MIG[o]<<endl;
							
							if(Wallet[o]<=0)
							{
								cout<<con::fg_magenta<<"PLAYER"<<o<<con::fg_cyan<<" leaves the table!"<<endl<<con::fg_gray;
								Wallet[o]=0;
								WALLETSIZE[o]=0;
								PIGstatus[o]=0;
								PIGstatusTEMP[o]=0;
							}
							cout<<"New wallet size: "<<Wallet[o]<<endl;
							cout<<"\n";
						}
					};
					AllInsorted.resize(0);
				}
			
				//Start of AllIn Case 1
				
				if (AllInCase==1)
				{
					cout<<"AllInCase=1";
					std::copy(AllInsorted.begin(),AllInsorted.end(),std::ostream_iterator<int> (cout, ":"));
					cout<<"\n";
					
					for (int h=0;h<AllInsorted.size();h++)
					{
						for (int o=0;o<numberofplayers;o++)
						{
							if( AllInsorted[h]==MIG[o])
							{
								IndexesAllInsorted.push_back(o);
							}
						};
					};
					if (IndexesAllInsorted.size()!=0)
					{
						std::copy(IndexesAllInsorted.begin(),IndexesAllInsorted.end(),std::ostream_iterator<int> (cout,":"));
					}

					for(int o=0;o<numberofplayers;o++)
					{
						if (PlayerPoints[o]==*PossibleWinnerPointsMAX&&AllIn[o]!=0&&AllInCase==1)
						{
							for(int k=0;k<AllInsorted.size();k++)
							{
								if(AllInsorted[k]==AllIn[o]+MIG[o])
								{
									indexeswinner=k;
									cout<<"\n";
									cout<< "indexeswinner : "<<indexeswinner<<endl;

								}
							};
						}
					};
	
					for (int o=0;o<numberofplayers;o++)
					{
						if (PlayerPoints[o]==*PossibleWinnerPointsMAX&&AllIn[o]!=0&&AllInCase==1)
						{
							primarypot=std::accumulate(AllInsorted.begin(),AllInsorted.begin()+indexeswinner,(AllIn[indexeswinner])*(AllInsorted.size()-(indexeswinner+1)));
							cout <<con::fg_magenta<<"PLAYER"<<o<<" WINS: "<<con::fg_yellow<<primarypot<<con::fg_gray<<endl;
							cout<<"\n";
							Wallet[o]=Wallet[o]+ primarypot;
							cout<<"New wallet size: "<<Wallet[o]<<endl;
							cout<<"\n";
							AllIn[o]=0;
							MIG[o]=0;
							MIGTEMP[o]=0;
							Pot=Pot-primarypot;
						}
						else continue;
					};
					for (int o=0;o<numberofplayers;o++)
					{

						if (PlayerPoints[o]!=*PossibleWinnerPointsMAX&&AllInCase==1)
						{
							
							for(int k=0;k<IndexesAllInsorted.size();k++)
							{	
								if(IndexesAllInsorted[k]=o)
								{
									if (k<=indexeswinner)
									{
										cout<<con::fg_magenta<<"PLAYER"<<o<<" Looses: "<<con::fg_gray<<MIG[o]<<endl;	
										if(Wallet[o]<=0)
										{
											Wallet[o]=0;
											WALLETSIZE[o]=0;
											PIGstatus[o]=0;
											PIGstatusTEMP[o]=0;
										}
										std::vector<int> HasLeftTable;
										cout<<"New wallet size: "<<Wallet[o]<<endl;
										if(Wallet[o]<=0&&count(HasLeftTable.begin(),HasLeftTable.end(),o)==0)
										{
											cout<<con::fg_cyan<<"Player "<<o<<"leaves the table."<<con::fg_gray<<endl;
											AllIn[o]=0;
											PlayerPoints[o]=zeros;
											PossibleWinnerPoints[o]=zeros;
											AllInsorted[k]=0;
											HasLeftTable.push_back(o);
										}
										cout<<"\n";
										
									
										
									}
									else if (k>indexeswinner)
									{	
										AllInsorted[k]=AllInsorted[k]-AllInsorted[indexeswinner];
										cout<<con::fg_magenta<<"PLAYER"<<o<<" Looses: "<<con::fg_gray<<AllInsorted[k]<<endl;	
								
									}
								}
								HaveFolded=count(PIGstatus.begin(),PIGstatus.end(),0);
							};
							AllInsorted.erase(remove(AllInsorted.begin(), AllInsorted.end(),0), AllInsorted.end());
						}
					};
				}
			};
			
		}
		
	OutOfGame = count(WALLETSIZE.begin(), WALLETSIZE.end(), 0);
	MIG.erase(MIG.begin(),MIG.end());
	PairProbError=abs(0.43822546-(static_cast<double>(PAIRCOUNT)/(increment * (numberofplayers-OutOfGame))));
	DoublePairProbError=abs(0.23495536-(static_cast<double>(DOUBLEPAIRCOUNT)/(increment * (numberofplayers-OutOfGame))));
	FullProbError=abs(0.0482987-(static_cast<double>(FULLCOUNT)/(increment * (numberofplayers-OutOfGame))));
	FullHouseProbError=abs(0.02596102-(static_cast<double>(FULLHOUSECOUNT)/(increment *(numberofplayers-OutOfGame))));
	StraightProbError=abs(0.04650465-(static_cast<double>(STRAIGHTCOUNT)/(increment * (numberofplayers-OutOfGame))));
	ProbERROR=abs(0.03025494-(static_cast<double>(FLUSHCOUNT)/(increment * (numberofplayers-OutOfGame))));
	FourOfAKindProbError=abs(0.00168067-(static_cast<double>(FOUROFAKINDCOUNT)/(increment * (numberofplayers-OutOfGame))));
	
	
	if (ProbERROR<=0.001) 
	{
		cout<<con::fg_white<<"Flush Probability error: "<<endl		<<con::fg_green <<"\n						"<<ProbERROR;
		cout<<"\n"<<con::fg_gray;
	}
	else if(ProbERROR>0.001)
	{
		cout<<con::fg_white<<"Flush Probability error: "<<endl		<<con::fg_red<<"\n						"	<<ProbERROR;
		cout<<"\n"<<con::fg_gray;
	}

	if (PairProbError<=0.02)
	{
		cout<<con::fg_white<<"Pair Probability error: "<<endl <<con::fg_green<<"\n						"	<<PairProbError;
		cout<<"\n"<<con::fg_gray;	
	}
	else if (PairProbError>0.02)
	{
		cout<<con::fg_white<<"Pair Probability error: "<<endl <<con::fg_red<<"\n						"	<<PairProbError;
		cout<<"\n"<<con::fg_gray;	
	}
	if (DoublePairProbError<=0.01)
	{
		cout<<con::fg_white<<"Double Pair Probability error: "<<endl <<con::fg_green<<"\n						"	<<DoublePairProbError;
		cout<<"\n"<<con::fg_gray;	
	}
	else if (DoublePairProbError>0.01)
	{
		cout<<con::fg_white<<"Double Pair Probability error: "<<endl <<con::fg_red<<"\n						"	<<DoublePairProbError;
		cout<<"\n"<<con::fg_gray;	
	}
	if(FullProbError<=0.01)
	{
		cout<<con::fg_white<<"Full Probability error: "<<endl<<con::fg_green<<"\n						"<<FullProbError;
		cout<<"\n"<<con::fg_gray;	
	}
	else if (FullProbError>0.001)
	{
		cout<<con::fg_white<<"Full Probability error: "<<endl<<con::fg_red<<"\n						"<<FullProbError;
		cout<<"\n"<<con::fg_gray;	
	}

	if(FullHouseProbError<=0.001)
	{
		cout<<con::fg_white<<"Full House Probability error: "<<endl<<"\n						"<<con::fg_green<<FullHouseProbError;
		cout<<"\n"<<con::fg_gray;	
	}
	else if(FullHouseProbError>0.001)
	{
		cout<<con::fg_white<<"Full House Probability error: "<<endl<<"\n						"<<con::fg_red<<FullHouseProbError;
		cout<<"\n"<<con::fg_gray;	
	}
	if(StraightProbError<=0.01)
	{
		cout<<con::fg_white<<"Straight Probability error: "<<endl<<"\n						"<<con::fg_green<<StraightProbError;
		cout<<"\n"<<con::fg_gray;	
	}
	else if(StraightProbError>0.01)
	{
		cout<<con::fg_white<<"Straight Probability error: "<<endl<<"\n						"<<con::fg_red<<StraightProbError;
		cout<<"\n"<<con::fg_gray;	
	}

	if(FourOfAKindProbError<=0.001)
	{
		cout<<con::fg_white<<"Four of a Kind Probability error: "<<endl<<"\n						"<<con::fg_green<<FourOfAKindProbError;
		cout<<"\n"<<con::fg_gray;	
	}
	else if(FourOfAKindProbError>0.001)
	{
		cout<<con::fg_white<<"Four of a Kind Probability error: "<<endl<<"\n						"<<con::fg_red<<FourOfAKindProbError;
		cout<<"\n"<<con::fg_gray;	
	}


	
	//cout<<"increment "<<increment;	
	//cout<<loopcount;
	//cout<<"\n";
	//cout<<breaker;
	//cout<<"\n";
	//cout<<BetIncrement;
	//cout<<"\n";
	//cout<<loopcount;
	//cout<<"\n";
	//cout<<loopcount2;
	//cout<<"\n";
	//cout<<winnerfound;
	//cout<<"\n";
	
};

cout<<"\n";
cout<<"\n";
cout<<"\n";
for (int o=0;o<numberofplayers;o++)
{
	if (Wallet[o]!=0)
	{
cout<<"\n";
cout<<"\n";
cout<<"\n";		
cout<<con::fg_green<< "	PLAYER "<<o<< " WINS "<<con::fg_yellow<<Wallet[o]<<" $ "<<con::fg_green<<" !!!!!!!!!!!! CoNgRaTuLaTioNs!!!!";
cout<<"\n";
cout<<"\n";
cout<<"\n";
cout<<con::fg_green<< "	PLAYER "<<o<< " WINS "<<con::fg_yellow<<Wallet[o]<<" $ "<<con::fg_green<<" !!!!!!!!!!!! CoNgRaTuLaTioNs!!!!";
cout<<"\n";
cout<<"\n";
cout<<"\n";
cout<<con::fg_green<< "	PLAYER "<<o<< " WINS "<<con::fg_yellow<<Wallet[o]<<" $ "<<con::fg_green<<" !!!!!!!!!!!! CoNgRaTuLaTioNs!!!!";
cout<<"\n";
cout<<"\n";
cout<<"\n";
cout<<con::fg_green<< "	PLAYER "<<o<< " WINS "<<con::fg_yellow<<Wallet[o]<<" $ "<<con::fg_green<<" !!!!!!!!!!!! CoNgRaTuLaTioNs!!!!";
cout<<"\n";
cout<<"\n";
cout<<"\n";
int end;
cin>>end;

	}
};


}



