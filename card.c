// File : card.c
#include <stdio.h>
#include <assert.h>
#include "card.h"

char *suitname[] = {"club", "diamon", "heart", "spade"};

char const *Suit_ToString(Suit suit)
{
  assert(suit < NB_SUITS);
  return suitname[suit];
}

Card Card_Make(Suit _suit, int _rank)
{
  Card card;
  card.rank = _rank;
  card.suit = _suit;
  return card;
}

void Card_Print(Card card)
{
  printf("%d %s \n", card.rank, Suit_ToString(card.suit));
}

bool Card_isEqual(Card card1, Card card2)
{
  return card1.rank == card2.rank && card1.suit == card2.suit;
}
