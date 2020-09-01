#include <iostream>
#include <vector>

using namespace std;

namespace cardsProperties {
enum Suits {
    Hearts,
    Spades,
    Clubs,
    Diamonds,
};

enum Ranks {
    two,
    three,
    four,
    five,
    six,
    seven,
    eight,
    nine,
    ten,
    jack,
    queen,
    king,
    ace
};
}  // namespace cardsProperties

struct card {
    cardsProperties::Ranks rank;
    cardsProperties::Suits suit;

    card(cardsProperties::Ranks r, cardsProperties::Suits s)
        : rank(r), suit(s) {}
};

struct deckOfCards {
    int nCards;
    vector<card> deck;

    deckOfCards() : nCards(52) {
        for (int i = 0; i < 13; ++i) {
            for (int j = 0; j < 4; ++j) {
                deck.push_back(card(static_cast<cardsProperties::Ranks>(i),
                                    static_cast<cardsProperties::Suits>(j)));
            }
        }
    }
};

int main() {
    return 0;
}