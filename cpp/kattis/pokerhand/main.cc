#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

int main() {
	size_t noHands = 5;
	string hand;
	unordered_map<char, size_t> hands;
	size_t maxCardSeen = 0;

	while (noHands--) {
		cin >> hand;
		hands.try_emplace(hand.at(0), 0);

		// amount of times this card has been seen
		size_t cardSeen = ++hands[hand.at(0)];
		if (cardSeen > maxCardSeen) {
			maxCardSeen = cardSeen;
		}
	}
	cout << maxCardSeen << endl;
}
