#include <gtest/gtest.h>
#include <progbar.h>
#include <cards.h>
#include <functional.h>

#include <vector>

#include <common.h>

namespace {

TEST(PlayingCardsTest, InitDeckSize) {
    cards::CCardDeck cardDeck;

    cardDeck.Init();

    EXPECT_EQ(cardDeck.DeckSize(), CARDDECKSIZE);
}

TEST(PlayingCardsTest, DrawSingleCardDeckSize) {
    cards::CCardDeck cardDeck;

    cardDeck.Init();

    cardDeck.Draw();
    
    EXPECT_EQ(cardDeck.DeckSize(), CARDDECKSIZE - 1);
}

TEST(PlayingCardsTest, DrawToEmptyDeckWithZeroCardsRemaining) {
    cards::CCardDeck cardDeck;

    cardDeck.Init();

    cards::CardRefs cr = cardDeck.Draw();

    while(cr != cards::CardRefs::EMPTY_DECK) {
        cr = cardDeck.Draw();
    }

    EXPECT_EQ(cardDeck.DeckSize(), 0);
}

TEST(PlayingCardsTest, CheckEachCardUniqueUnshuffled) {
    cards::CCardDeck cardDeck;

    cardDeck.Init();

    cards::CardRefs cr = cards::CardRefs::SPADES_A;
    std::vector<cards::CardRefs> cardVec;
    int same = 0;

    while(cr != cards::CardRefs::EMPTY_DECK) {
        cr = cardDeck.Draw();
        cardVec.push_back(cr);
    }

    for(int i = 0; i < cardVec.size() - 1; i++) {
        for(int j = 0; j < cardVec.size() - 1; j++) {
            if(cardVec[i] == cardVec[j]) {
                same++;
            }
        }
    }

    EXPECT_EQ(same, CARDDECKSIZE);
}

TEST(PlayingCardsTest, CheckEachCardUniqueShuffled) {
    cards::CCardDeck cardDeck;

    cardDeck.Init();

    cards::CardRefs cr = cards::CardRefs::SPADES_A;
    std::vector<cards::CardRefs> cardVec;
    int same = 0;

    cardDeck.Shuffle();

    while(cr != cards::CardRefs::EMPTY_DECK) {
        cr = cardDeck.Draw();
        cardVec.push_back(cr);
    }

    for(int i = 0; i < cardVec.size() - 1; i++) {
        for(int j = 0; j < cardVec.size() - 1; j++) {
            if(cardVec[i] == cardVec[j]) {
                same++;
            }
        }
    }

    EXPECT_EQ(same, CARDDECKSIZE);
}

TEST(PlayingCardsTest, CanReinitializeEmptyDeck) {
    cards::CCardDeck cardDeck;

    cardDeck.Init();

    cards::CardRefs cr = cardDeck.Draw();

    while(cr != cards::CardRefs::EMPTY_DECK) {
        cr = cardDeck.Draw();
    }

    cardDeck.Init();

    EXPECT_EQ(cardDeck.DeckSize(), CARDDECKSIZE);    
}

TEST(PlayingCardsTest, CanDoubleInitializeDeckToRemainSameSize) {
    cards::CCardDeck cardDeck;

    cardDeck.Init();
    cardDeck.Init();

    EXPECT_EQ(cardDeck.DeckSize(), CARDDECKSIZE);   
}

TEST(PlayingCardsTest, CanDoubleInitializeDeckToRemainSameSizeEachCardUnique) {
    cards::CCardDeck cardDeck;

    cardDeck.Init();
    cardDeck.Init();

    cards::CardRefs cr = cards::CardRefs::SPADES_A;
    std::vector<cards::CardRefs> cardVec;
    int same = 0;

    while(cr != cards::CardRefs::EMPTY_DECK) {
        cr = cardDeck.Draw();
        cardVec.push_back(cr);
    }

    for(int i = 0; i < cardVec.size() - 1; i++) {
        for(int j = 0; j < cardVec.size() - 1; j++) {
            if(cardVec[i] == cardVec[j]) {
                same++;
            }
        }
    }

    EXPECT_EQ(same, CARDDECKSIZE);    
}

}