//cardspok.h

#ifndef CARDSPOK_H
#define CARDSPOK_H

#include <iostream>
#include <vector>
using namespace std;

enum hands {Height, Pair, DoublePair, Full,Straight, Flush, FullHouse,Square, RoyalFlush};
enum suits {diamond, club, heart, spade};
const unsigned int rank_max = 13;


class Card
{
public:
	Card ();
	Card(const Card& orig);
	Card(suits sv, unsigned int rv);
	~Card ();
	Card& operator=(const Card& rhs);
	unsigned int GetRank() const;
	suits GetSuit() const;
	void SetRank(unsigned int rv);
	void SetSuit(suits sv);
	void Insert(ostream&out) const;
	vector<Card> cards;
	Card Draw();
	unsigned int rank;
	suits suit;
	friend std::ostream & operator << (ostream & out, const Card& aCard);
};

 
 
 class Deck
{
public:
	Deck();
	Card Draw();
	Deck(const Deck& orig);
	~Deck();
	Deck& operator=(const Deck& rhs);
	void shuffle ();
	friend std::ostream& operator << (ostream & out, const Deck& aDeck);
	vector<Card> cards;

};



 class Player
 {
 public:
	 Player ();
	 Card Draw();
	 Player(const Player& orig);
	 Player(hands hd);
	 Player& operator=(const Player& rhs);
	 hands hand;
	 hands GetHand() const;
	 void SetHand(hands hd);
	 void Insert(ostream&out) const;
	 ~Player ();
	 vector<Card> player;
	 friend std::ostream & operator << (ostream & out, const Player& aPlayer);

 	 

 };

#endif	

	