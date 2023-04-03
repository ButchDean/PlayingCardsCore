#include <cstdio>
#include <chrono>
#include <random>
#include <cmath>
#include <cards.h>
#include <progbar.h>

namespace cards
{
	void CCardDeck::Init() {
		std::puts("Initializing default sorted deck...");

		deck.clear();

		for(const auto& c : cardspecs) {
			deck.push_back(std::move(c.card));
		}

		std::printf("Deck size: %lu\n", deck.size());

		// Populate card values and other details key-value pairs.
		cardDetail.clear();
		for(auto c : cardspecs) {
			cardDetail.insert({c.card, c.cd});
		}
	}

	CardRefs CCardDeck::_CardRefFilter(unsigned int cvVal) const {
		switch(cvVal) {
			case 0:
				return CardRefs::SPADES_A;
			case 1:
				return CardRefs::SPADES2;
			case 2:
				return CardRefs::SPADES3;
			case 3:
				return CardRefs::SPADES4;
			case 4:
				return CardRefs::SPADES5;
			case 5:
				return CardRefs::SPADES6;
			case 6:
				return CardRefs::SPADES7;
			case 7:
				return CardRefs::SPADES8;
			case 8:
				return CardRefs::SPADES9;
			case 9:
				return CardRefs::SPADES10;
			case 10:
				return CardRefs::SPADES_J;
			case 11:
				return CardRefs::SPADES_Q;
			case 12:
				return CardRefs::SPADES_K;
			case 13:
				return CardRefs::CLUBS_A;
			case 14:
				return CardRefs::CLUBS2;
			case 15:
				return CardRefs::CLUBS3;
			case 16:
				return CardRefs::CLUBS4;
			case 17:
				return CardRefs::CLUBS5;
			case 18:
				return CardRefs::CLUBS6;
			case 19:
				return CardRefs::CLUBS7;
			case 20:
				return CardRefs::CLUBS8;
			case 21:
				return CardRefs::CLUBS9;
			case 22:
				return CardRefs::CLUBS10;
			case 23:
				return CardRefs::CLUBS_J;
			case 24:
				return CardRefs::CLUBS_Q;
			case 25:
				return CardRefs::CLUBS_K;
			case 26:
				return CardRefs::HEARTS_A;
			case 27:
				return CardRefs::HEARTS2;
			case 28:
				return CardRefs::HEARTS3;
			case 29:
				return CardRefs::HEARTS4;
			case 30:
				return CardRefs::HEARTS5;
			case 31:
				return CardRefs::HEARTS6;
			case 32:
				return CardRefs::HEARTS7;
			case 33:
				return CardRefs::HEARTS8;
			case 34:
				return CardRefs::HEARTS9;
			case 35:
				return CardRefs::HEARTS10;
			case 36:
				return CardRefs::HEARTS_J;
			case 37:
				return CardRefs::HEARTS_Q;
			case 38:
				return CardRefs::HEARTS_K;
			case 39:
				return CardRefs::DIAMONDS_A;
			case 40:
				return CardRefs::DIAMONDS2;
			case 41:
				return CardRefs::DIAMONDS3;
			case 42:
				return CardRefs::DIAMONDS4;
			case 43:
				return CardRefs::DIAMONDS5;
			case 44:
				return CardRefs::DIAMONDS6;
			case 45:
				return CardRefs::DIAMONDS7;
			case 46:
				return CardRefs::DIAMONDS8;
			case 47:
				return CardRefs::DIAMONDS9;
			case 48:
				return CardRefs::DIAMONDS10;
			case 49:
				return CardRefs::DIAMONDS_J;
			case 50:
				return CardRefs::DIAMONDS_Q;
			case 51:
				return CardRefs::DIAMONDS_K;
			default:
				break;
		}

		// Should never get here!
		return CardRefs::INVALID_CARD;
	}

	int CCardDeck::_GetRandomCardPos() {
		std::chrono::system_clock::time_point tp = std::chrono::system_clock::now();
		std::chrono::system_clock::duration periods = tp.time_since_epoch();

		// Seed 64-bit Mersenne Twister
		std::mt19937_64::result_type seed = periods.count();

		// Generate rand.
		auto deckPos = std::bind(std::uniform_int_distribution<int>(0, deck.size() - 1), std::mt19937_64(seed));

		return deckPos();
	}

	void CCardDeck::Shuffle() {
		// Do we need to shuffle?
		auto deckSize = deck.size();

		if(deckSize == 0)
		{
			std::puts("Deck size is empty, so there isn't anything to shuffle.");
			return;
		}
		else
		if(deckSize == 1)
		{
			std::puts("Deck only contains one card, so no need to shuffle.");
			return;
		}

		// We continue with shuffling.

		CardRefs cardValA, cardValB;

		auto randIterations = std::pow(deckSize, 3);

		for(int j = 0; j < randIterations; j++)
		{
			int posA = std::move(_GetRandomCardPos());
			cardValA = deck[posA];

			int posB = std::move(_GetRandomCardPos());
			cardValB = deck[posB];

			// Swap values
			deck[posA] = cardValB;
			deck[posB] = cardValA;

			// Update the progress bar
			const int PROG_DONE = j / randIterations * 100;
			UpdateProgress(PROG_DONE, deckSize);
		}
	}

	CardRefs CCardDeck::Draw() {
		if(deck.empty())
		{
			std::puts("Attempted to deal but deck is empty.");
			return CardRefs::EMPTY_DECK;
		}

		std::puts("\nDealing card...");
		CardRefs currentCard = deck[0];

		// Remove top card from deck.
		deck.pop_front();

		return currentCard;
	}

	std::string CCardDeck::CardToStr(const CardRefs card) const {
		auto cardSearch = std::move(cardDetail.find(card));

		if(cardSearch == cardDetail.end())
			return "Card string not found!";

		return cardSearch->second.cardStr;
	}

	int CCardDeck::CardValue(const CardRefs card) const {
		auto cardSearch = std::move(cardDetail.find(card));

		if(cardSearch == cardDetail.end())
		{
			std::puts("Card value not found!");
			return -1;
		}

		return cardSearch->second.cardVal;
	}
}
