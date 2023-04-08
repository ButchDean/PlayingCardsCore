#ifndef _CARDS_MECHANIC_
#define _CARDS_MECHANIC_

#include <iostream>

#include <deque>
#include <unordered_map>
#include <array>
#include <string>
#include <stdexcept>

#include <common.h>

static int bad_card() {
	throw std::runtime_error("ERROR: Bad card - CardRefs::INVALID_CARD");
}

static int bad_card_value() {
	throw std::runtime_error("ERROR: Bad card value (-1)");
}

namespace cards
{
	enum class CardRefs { SPADES_A = 0, SPADES2, SPADES3, SPADES4, SPADES5, SPADES6, SPADES7, SPADES8, SPADES9, SPADES10, SPADES_J, SPADES_Q, SPADES_K,
			CLUBS_A, CLUBS2, CLUBS3, CLUBS4, CLUBS5, CLUBS6, CLUBS7, CLUBS8, CLUBS9, CLUBS10, CLUBS_J, CLUBS_Q, CLUBS_K,
			HEARTS_A, HEARTS2, HEARTS3, HEARTS4, HEARTS5, HEARTS6, HEARTS7, HEARTS8, HEARTS9, HEARTS10, HEARTS_J, HEARTS_Q, HEARTS_K,
			DIAMONDS_A, DIAMONDS2, DIAMONDS3, DIAMONDS4, DIAMONDS5, DIAMONDS6, DIAMONDS7, DIAMONDS8, DIAMONDS9, DIAMONDS10, DIAMONDS_J, DIAMONDS_Q, DIAMONDS_K,
			EMPTY_DECK, INVALID_CARD };
			
	struct CardDetail {
	    std::string cardStr;
	    int cardVal;
	};	

	struct cardSpecs {
		CardRefs card;
		CardDetail cd;
	};
	
	class CCardDeck
	{
		public:
			CCardDeck(){
				// Set card values
				std::array<std::string, 4> suit{"SPADES", "CLUBS", "HEARTS", "DIAMONDS"};
				std::array<std::string, 13> face{"_A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "_J", "_Q", "_K"};

				unsigned int itr = 0;
				for(const auto& s : suit) {
					for(const auto& f : face) {
						CardRefs cr;
						try{
							cr = _CardRefFilter(itr);

							if(cr == CardRefs::INVALID_CARD) {
								bad_card();
							}
						}
						catch(...) {
							std::cout << "Invalid card deck due to invalid card.\n";
						}

						int crv;
						try {
							crv = _CardRefFilterValue(cr);

							if(crv == -1){
								bad_card_value();
							}
						}
						catch(...) {
							std::cout << "Invalid card value with -1 returned.\n";
						}

						cardspecs[itr] = {cr, {s + f, crv}};
						itr++;
					}
				}

			}
			~CCardDeck() = default;

			CCardDeck(const CCardDeck &) = delete;
			CCardDeck(CCardDeck &&) = delete;
			CCardDeck &operator=(const CCardDeck &) = delete;
			CCardDeck &operator=(CCardDeck &&) = delete;
			
			void Init();
			void Shuffle();
			CardRefs Draw();
			std::string CardToStr(const CardRefs card) const;
			
			int CardValue(const CardRefs card) const;

			int DeckSize() {
				return deck.size();
			}
			
		private:
			std::deque<CardRefs> deck;
			std::unordered_map<CardRefs, CardDetail> cardDetail;
			std::array<cardSpecs, CARDDECKSIZE> cardspecs;
			
			CardRefs _CardRefFilter(unsigned int cvVal) const;
			int _CardRefFilterValue(const CardRefs crVal);
			int _GetRandomCardPos();	
	};
}

#endif
