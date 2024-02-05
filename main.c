#include <stdio.h>
#include "card.h"
#include "handtest.h"
#include "cardtest.h"
#include "decktest.h"

int main()
{
    CardTest_RunAll();
    DeckTest_RunAll();
    HandTest_RunAll();
}