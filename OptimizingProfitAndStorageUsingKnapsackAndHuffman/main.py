import heapq
import collections


# Define a gadget class to represent each gadget
class Gadget:
    def __init__(self, ID, weight, price):
        self.ID = ID
        self.weight = weight
        self.price = price

    def __repr__(self):
        return f"Gadget({self.ID}, {self.weight}, {self.price})"


# Define the Knapsack algorithm
def knapsack(gadgets, weight_capacity):
    n = len(gadgets)
    table = [[0 for _ in range(weight_capacity+1)] for _ in range(n+1)]

    for i in range(1, n+1):
        gadget = gadgets[i-1]

        for j in range(1, weight_capacity+1):
            if gadget.weight > j:
                table[i][j] = table[i-1][j]
            else:
                table[i][j] = max(table[i-1][j], gadget.price + table[i-1][j-gadget.weight])
    max_profit = table[n][weight_capacity]

    # Trace back the selected items
    selected_items = []
    i, j = n, weight_capacity
    
    while i > 0 and j > 0:
        if table[i][j] != table[i-1][j]:
            selected_items.append(gadgets[i-1])
            j -= gadgets[i-1].weight
        i -= 1

    selected_items.reverse()

    return selected_items, max_profit


# Define the Huffman coding technique
def huffman_coding(prices):
    freq_dict = collections.Counter(prices)
    heap = [[freq, [price, ""]] for price, freq in freq_dict.items()]
    heapq.heapify(heap)
    while len(heap) > 1:
        lo = heapq.heappop(heap)
        hi = heapq.heappop(heap)

        for pair in lo[1:]:
            pair[1] = '0' + pair[1]

        for pair in hi[1:]:
            pair[1] = '1' + pair[1]

        heapq.heappush(heap, [lo[0] + hi[0]] + lo[1:] + hi[1:])

    huffman_dict = dict(heapq.heappop(heap)[1:])
    compressed_prices = [huffman_dict[price] for price in prices]

    return compressed_prices, huffman_dict


def main():
    # Define the list of gadgets
    gadget_test_list = [
        (5, 20), (3, 14), (8, 35), (2, 10),
        (10, 1), (20, 2), (30, 3), (40, 4),
        (50, 5), (60, 6), (3, 5), (2, 3),
        (1, 2), (5, 9), (4, 7), (6, 12)
    ]
    gadgets = []
    for i, test_data in enumerate(gadget_test_list):
        gadgets.append(
            Gadget(i, test_data[0], test_data[1])
        )

    # Define the weight capacity of the shelf
    weight_capacity = 10

    # Use the Knapsack algorithm to select the most profitable items
    selected_items, max_profit = knapsack(gadgets, weight_capacity)

    # Use the Huffman coding technique to compress the prices of the selected items
    prices = [gadget.price for gadget in selected_items]
    compressed_prices, huffman_dict = huffman_coding(prices)

    # Print the selected items and their compressed prices
    print("Selected Items:")
    for item in selected_items:
        print(item)

    print("Max Profit:", max_profit)
    print("Compressed Prices:")

    for price, compressed_price in zip(prices, compressed_prices):
        print(f"{price}: {compressed_price}")

    print("Huffman Dictionary:", huffman_dict)

    # Print the time complexity of the algorithms
    print("\nTime Complexity Analysis:")
    print("Knapsack Algorithm - O(nW)")
    print("Huffman Coding Technique - O(nlogn)")


if __name__ == '__main__':
    main()
