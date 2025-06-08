#include <iostream>
#include <vector>
#include "SegmentTree.h"

int main() {
	// Вывод был на русском, но выводились кракозябры, поэтому вывод на английском

	std::vector<int> arr = { 1, 3, 5, 7, 9, 11 };
	std::cout << "Initial array: ";
	for (int x : arr) std::cout << x << " ";
	std::cout << "\n\n";

	SegmentTree st(arr);

	std::cout << "=== Sum Queries ===\n";
	std::cout << "Sum [1, 3]: " << st.sumQuery(1, 3) << "\n";
	std::cout << "Sum [0, 5]: " << st.sumQuery(0, 5) << "\n";

	st.update(1, 10);
	std::cout << "After update(1, 10):\n";
	std::cout << "Sum [1, 3]: " << st.sumQuery(1, 3) << "\n";

	std::cout << "\n=== Min and Max Queries ===\n";
	std::cout << "Min [0, 5]: " << st.minQuery(0, 5) << "\n";
	std::cout << "Max [0, 5]: " << st.maxQuery(0, 5) << "\n";

	std::cout << "\n=== Range Update ===\n";
	st.updateRange(2, 4, 2);
	std::cout << "After updateRange(2, 4, 2):\n";
	std::cout << "Sum [2, 4]: " << st.sumQuery(2, 4) << "\n";

	std::cout << "\n=== Invalid Queries ===\n";
	st.sumQuery(-1, 10);

	st.print();

	return 0;
}
