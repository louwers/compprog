// ask price: lowest price somebody is willing to sell
// bid price: highest price somebody is willing to buy
// stock price: price at which a deal was established

#include <functional>
#include <iostream>
#include <queue>
#include <string>
#include <tuple>

using namespace std;

using Order = tuple<size_t, size_t>;
using SellOrders =
    priority_queue<Order, std::vector<Order>, std::greater<Order>>;
using BuyOrders = priority_queue<Order>;

int main() {

  size_t cases;
  cin >> cases;

  while (cases--) {
    SellOrders sellOrders;
    BuyOrders buyOrders;

    size_t n;
    cin >> n;

    size_t askPrice = 0;
    size_t bidPrice = 0;
    size_t stockPrice = 0;

    while (n--) {

      string order_type;
      size_t amount;
      string shares;
      string at;
      size_t price;
      cin >> order_type >> amount >> shares >> at >> price;

      if (order_type == "buy") {
        // try to buy
        while (true) {
          if (sellOrders.empty())
            break;
          auto [sellPrice, sellAmount] = sellOrders.top();
          if (sellPrice <= price) {
            // buy
            sellOrders.pop();
            stockPrice = sellPrice;
            if (sellAmount > amount) {
              sellOrders.emplace(sellPrice, sellAmount - amount);
              amount = 0;
            } else {
              amount = amount - sellAmount;
            }
            if (amount == 0)
              break;
          } else {
            break;
          }
        }
        if (amount > 0) {
          buyOrders.emplace(price, amount);
        }
      } else if (order_type == "sell") {
        // try to sell
        while (true) {
          if (buyOrders.empty())
            break;
          auto [buyPrice, buyAmount] = buyOrders.top();
          if (buyPrice >= price) {
            // make sale
            buyOrders.pop();
            stockPrice = price;
            if (buyAmount > amount) {
              buyOrders.emplace(buyPrice, buyAmount - amount);
              amount = 0;
            } else {
              amount = amount - buyAmount;
            }
            if (amount == 0)
              break;
          } else {
            break;
          }
        }
        if (amount > 0) {
          sellOrders.emplace(price, amount);
        }
      } else {
        throw runtime_error("unexpected order_type: " + order_type);
      }

      if (sellOrders.empty()) {
        askPrice = 0;
      } else
        askPrice = get<0>(sellOrders.top());
      if (buyOrders.empty())
        bidPrice = 0;
      else
        bidPrice = get<0>(buyOrders.top());

      cout << (askPrice != 0 ? to_string(askPrice) : "-") << " "
           << (bidPrice != 0 ? to_string(bidPrice) : "-") << " "
           << (stockPrice != 0 ? to_string(stockPrice) : "-") << '\n';
    }
  }
}
