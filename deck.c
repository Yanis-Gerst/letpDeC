// File : deck.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "card.h"
#include "deck.h"

void Deck_InitEmpty(Deck *self)
{
  self->length = 0;
}

void Deck_AddCardAtEnd(Deck *self, Card card)
{
  assert(self->length <= DECK_CAPACITY);
  self->cards[self->length] = card;
  self->length += 1;
}

Card Deck_RemoveCardAtEnd(Deck *self)
{
  assert(self->length > 0);

  Card card = self->cards[self->length - 1];
  self->length -= 1;
  return card;
}

void Deck_InitFullSorted(Deck *self)
{
  Deck_InitEmpty(self);
  for (int suit = CLUB; suit <= SPADE; suit++)
  {
    for (int rank = 0; rank < NB_RANKS; rank++)
    {

      Card card = Card_Make(suit, rank);
      Deck_AddCardAtEnd(self, card);
    }
  }
}

void Deck_Shuffle(Deck *self)
{

  for (int i = 0; i < self->length; i++)
  {
    int randomIndex = rand() % self->length;
    Card temporaryCard = self->cards[i];
    self->cards[i] = self->cards[randomIndex];
    self->cards[randomIndex] = temporaryCard;
  }
}
