// File : hand.c
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "card.h"
#include "hand.h"
#include "deck.h"

char *handname[] = {"Straight Flush", "Four of a kind", "Full house", "Flush", "Straight", "Three of a kind", "Two pairs", "One pair", "High card"};

void Hand_InitEmpty(Hand *self)
{
  self->length = 0;
}

void Hand_AddCard(Hand *self, Card card)
{
  assert(self->length < NB_CARDS);
  self->cards[self->length] = card;
  self->length++;
}

bool Hand_ContainsCard(Hand self, Card card)
{
  for (int i = 0; i < self.length; i++)
  {
    Card currentCard = self.cards[i];
    if (Card_isEqual(currentCard, card))
      return true;
  }
  return false;
}

int Hand_GetCardIndex(Hand self, Card card)
{
  for (int i = 0; i < self.length; i++)
  {
    Card currentCard = self.cards[i];
    if (Card_isEqual(currentCard, card))
      return i;
  }
  return -1;
}

void Hand_RemoveCard(Hand *self, Card card)
{
  assert(Hand_ContainsCard(*self, card));
  int index = Hand_GetCardIndex(*self, card);

  for (int i = index; i < self->length; i++)
  {
    self->cards[i] = self->cards[i + 1];
  }
  self->length = self->length - 1;
}

void Hand_DrawFromDeck(Hand *self, Deck *deck)
{
  Card lastCard = deck->cards[deck->length - 1];
  Hand_AddCard(self, lastCard);
  Deck_RemoveCardAtEnd(deck);
}

void Hand_GetFullHand(Hand *self, Deck *deck)
{
  Hand_InitEmpty(self);
  for (int i = 0; i < 5; i++)
  {
    Hand_DrawFromDeck(self, deck);
  }
}

void Hand_Sort(Hand *self)
{

  for (int i = 0; i < self->length; i++)
  {
    Card swapcard;
    Card lowestCard = self->cards[i];
    int indexToSwap = 0;
    for (int j = i + 1; j < self->length; j++)
    {
      Card currentCard = self->cards[j];
      indexToSwap = i;
      if (currentCard.suit < lowestCard.suit)
      {
        lowestCard = currentCard;
        indexToSwap = j;
      }
      if (currentCard.suit == lowestCard.suit && currentCard.rank < lowestCard.rank)
      {
        lowestCard = currentCard;
        indexToSwap = j;
      }
    }
    swapcard = self->cards[i];
    self->cards[i] = lowestCard;
    self->cards[indexToSwap] = swapcard;
  }
}

int Hand_CountNumberOf(Hand self, int rank)
{
  int count = 0;

  for (int i = 0; i < self.length; i++)
  {
    if (self.cards[i].rank == rank)
      count += 1;
  }
  return count;
}

bool Hand_IsStraightFlush(Hand self)
{
  Hand_Sort(&self);
  int i;
  for (i = 0; i < self.length - 1; i++)
  {
    if (self.cards[i].rank != self.cards[i + 1].rank - 1 || self.cards[i].suit != self.cards[i + 1].suit)
    {
      return false;
    }
  }
  return true;
}

bool Hand_IsFourOfAKind(Hand self)
{
  Hand_Sort(&self);
  return (self.cards[0].rank == self.cards[1].rank && self.cards[1].rank == self.cards[2].rank && self.cards[2].rank == self.cards[3].rank) ||
         (self.cards[1].rank == self.cards[2].rank && self.cards[2].rank == self.cards[3].rank && self.cards[3].rank == self.cards[4].rank);
}

bool Hand_IsFullHouse(Hand self)
{
  Hand_Sort(&self);
  return (self.cards[0].rank == self.cards[1].rank && self.cards[1].rank == self.cards[2].rank && self.cards[3].rank == self.cards[4].rank) ||
         (self.cards[0].rank == self.cards[1].rank && self.cards[2].rank == self.cards[3].rank && self.cards[3].rank == self.cards[4].rank);
}

bool Hand_IsFlush(Hand self)
{
  for (int i = 0; i < self.length - 1; i++)
  {
    if (self.cards[i].suit != self.cards[i + 1].suit)
    {
      return false;
    }
  }
  return true;
}

bool Hand_IsStraight(Hand self)
{
  Hand_Sort(&self);

  for (int i = 0; i < self.length - 1; i++)
  {
    if (self.cards[i].rank != self.cards[i + 1].rank - 1)
    {
      return false;
    }
  }
  return true;
}

bool Hand_IsThreeOfAKind(Hand self)
{
  Hand_Sort(&self);
  return (self.cards[0].rank == self.cards[1].rank && self.cards[1].rank == self.cards[2].rank) ||
         (self.cards[1].rank == self.cards[2].rank && self.cards[2].rank == self.cards[3].rank) ||
         (self.cards[2].rank == self.cards[3].rank && self.cards[3].rank == self.cards[4].rank);
}

bool Hand_IsTwoPairs(Hand self)
{
  Hand_Sort(&self);
  return (self.cards[0].rank == self.cards[1].rank && self.cards[2].rank == self.cards[3].rank) ||
         (self.cards[0].rank == self.cards[1].rank && self.cards[3].rank == self.cards[4].rank) ||
         (self.cards[1].rank == self.cards[2].rank && self.cards[3].rank == self.cards[4].rank);
}

bool Hand_IsOnePair(Hand self)
{
  Hand_Sort(&self);
  return (self.cards[0].rank == self.cards[1].rank) ||
         (self.cards[1].rank == self.cards[2].rank) ||
         (self.cards[2].rank == self.cards[3].rank) ||
         (self.cards[3].rank == self.cards[4].rank);
}
Card Hand_GetHighCard(Hand self)
{
  // TO DO
}

HandType Hand_Is(Hand self)
{
  if (Hand_IsStraightFlush(self))
  {
    return STRAIGHT_FLUSH;
  }
  else if (Hand_IsFourOfAKind(self))
  {
    return FOUR_OF_A_KIND;
  }
  else if (Hand_IsFullHouse(self))
  {
    return FULL_HOUSE;
  }
  else if (Hand_IsFlush(self))
  {
    return FLUSH;
  }
  else if (Hand_IsStraight(self))
  {
    return STRAIGHT;
  }
  else if (Hand_IsThreeOfAKind(self))
  {
    return THREE_OF_A_KIND;
  }
  else if (Hand_IsTwoPairs(self))
  {
    return TWO_PAIRS;
  }
  else if (Hand_IsOnePair(self))
  {
    return ONE_PAIR;
  }
  else
  {
    return HIGH_CARD;
  }
}

char const *Hand_ToString(Hand self)
{
  return handname[Hand_Is(self)];
}

void Hand_Print(Hand self)
{
  for (int i = 0; i < self.length; i++)
  {
    Card_Print(self.cards[i]);
    printf(" - ");
  }
  printf("\n");
}
