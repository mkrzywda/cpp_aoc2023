#include "tasks.h"

int cardStrength_part_a(char card) {
    if (card >= '2' && card <= '9') return card - '0';
    if (card == 'T') return 10;
    if (card == 'J') return 11;
    if (card == 'Q') return 12;
    if (card == 'K') return 13;
    if (card == 'A') return 14;
    return -1;
}

int cardStrength_part_b(char card) {
    if (card >= '2' && card <= '9') return card - '0';
    if (card == 'T') return 10;
    if (card == 'J') return 1;
    if (card == 'Q') return 12;
    if (card == 'K') return 13;
    if (card == 'A') return 14;
    return -1;
}

HandStrength evaluateHand_part_a(const std::string& cards, int* result) {
    std::map<int, int> frequency;
    for (char card : cards) frequency[cardStrength_part_a(card)]++;

    bool isPair = false, isThreeOfAKind = false, isFourOfAKind = false, isFiveOfAKind = false;
    for (const auto& pair : frequency) {
        if (pair.second == 2) isPair = true;
        else if (pair.second == 3) isThreeOfAKind = true;
        else if (pair.second == 4) isFourOfAKind = true;
        else if (pair.second == 5) isFiveOfAKind = true;
    }

    if (isFiveOfAKind) {
        *result = static_cast<int>(HandStrength::FIVEOFAKIND);
    }
    else if (isFourOfAKind) {
        *result = static_cast<int>(HandStrength::FOUROFAKIND);
    }
    else if (isThreeOfAKind && isPair) {
        *result = static_cast<int>(HandStrength::FULLHOUSE);
    }
    else if (isThreeOfAKind) {
        *result = static_cast<int>(HandStrength::THREEOFAKIND);
    }
    else if (isPair) {
        int pairCount = 0;
        for (const auto& pair : frequency) {
            if (pair.second == 2) pairCount++;
        }
        if (pairCount == 2) {
            *result = static_cast<int>(HandStrength::TWOPAIR);
        }
        else {
            *result = static_cast<int>(HandStrength::ONEPAIR);
        }
    }
    else {
        *result = static_cast<int>(HandStrength::HIGHCARD);
    }

    return static_cast<HandStrength>(*result);
}

void part_a(std::vector<std::tuple<std::string, int, HandStrength>>* hands) {
    for (auto& hand : *hands) {
        std::string cards = std::get<0>(hand);
        std::sort(cards.begin(), cards.end(), [](char a, char b) {
            return cardStrength_part_a(a) < cardStrength_part_a(b);
        });
        int result;
        std::get<2>(hand) = evaluateHand_part_a(cards, &result);
    }

    std::sort(hands->begin(), hands->end(), [](const auto& a, const auto& b) {
        HandStrength strengthA = std::get<2>(a);
        HandStrength strengthB = std::get<2>(b);

        if (strengthA == strengthB) {
            const std::string& cardsA = std::get<0>(a);
            const std::string& cardsB = std::get<0>(b);

            for (int i = 0; i < cardsA.size(); ++i) {
                if (cardStrength_part_a(cardsA[i]) != cardStrength_part_a(cardsB[i])) {
                    return cardStrength_part_a(cardsA[i]) < cardStrength_part_a(cardsB[i]);
                }
            }
        }

        return strengthA < strengthB;
    });

    int totalWinnings = 0;
    for (int i = 0; i < hands->size(); ++i) {
        totalWinnings += std::get<1>((*hands)[i]) * (i + 1);
    }
    std::cout << "Part A Result: " << totalWinnings << std::endl;
}

HandStrength evaluateHand_part_b(const std::string& cards, int* result) {
    std::map<int, int> frequency;
    int wildCardCount = 0;

    for (char card : cards) {
        if (card == 'J') wildCardCount++;
        else frequency[cardStrength_part_b(card)]++;
    }

    while (wildCardCount > 0) {
        auto it = std::max_element(frequency.begin(), frequency.end(),
            [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
            return a.second < b.second;
        });
        if (it != frequency.end() && it->second < 5) {
            it->second++;
            wildCardCount--;
        }
        else {
            frequency[0] = wildCardCount;
            break;
        }
    }

    bool isPair = false, isThreeOfAKind = false, isFourOfAKind = false, isFiveOfAKind = false;
    for (const auto& pair : frequency) {
        if (pair.second == 2) isPair = true;
        else if (pair.second == 3) isThreeOfAKind = true;
        else if (pair.second == 4) isFourOfAKind = true;
        else if (pair.second == 5) isFiveOfAKind = true;
    }

    if (isFiveOfAKind) {
        *result = static_cast<int>(HandStrength::FIVEOFAKIND);
    }
    else if (isFourOfAKind) {
        *result = static_cast<int>(HandStrength::FOUROFAKIND);
    }
    else if (isThreeOfAKind && isPair) {
        *result = static_cast<int>(HandStrength::FULLHOUSE);
    }
    else if (isThreeOfAKind) {
        *result = static_cast<int>(HandStrength::THREEOFAKIND);
    }
    else if (isPair) {
        int pairCount = 0;
        for (const auto& pair : frequency) {
            if (pair.second == 2) pairCount++;
        }
        if (pairCount == 2) {
            *result = static_cast<int>(HandStrength::TWOPAIR);
        }
        else {
            *result = static_cast<int>(HandStrength::ONEPAIR);
        }
    }
    else {
        *result = static_cast<int>(HandStrength::HIGHCARD);
    }

    return static_cast<HandStrength>(*result);
}

void part_b(std::vector<std::tuple<std::string, int, HandStrength>>* hands) {
    for (auto& hand : *hands) {
        std::string cards = std::get<0>(hand);
        std::sort(cards.begin(), cards.end(), [](char a, char b) {
            return cardStrength_part_b(a) < cardStrength_part_b(b);
        });
        int result;
        std::get<2>(hand) = evaluateHand_part_b(cards, &result);
    }

    std::sort(hands->begin(), hands->end(), [](const auto& a, const auto& b) {
        HandStrength strengthA = std::get<2>(a);
        HandStrength strengthB = std::get<2>(b);

        if (strengthA == strengthB) {
            const std::string& cardsA = std::get<0>(a);
            const std::string& cardsB = std::get<0>(b);

            for (int i = 0; i < cardsA.size(); ++i) {
                if (cardStrength_part_b(cardsA[i]) != cardStrength_part_b(cardsB[i])) {
                    return cardStrength_part_b(cardsA[i]) < cardStrength_part_b(cardsB[i]);
                }
            }
        }

        return strengthA < strengthB;
    });

    int totalWinnings = 0;
    for (int i = 0; i < hands->size(); ++i) {
        totalWinnings += std::get<1>((*hands)[i]) * (i + 1);
    }
    std::cout << "Part B Result: " << totalWinnings << std::endl;
}
