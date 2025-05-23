#include <iostream>
#include <deque>

using namespace std;

int main(void) {

	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int N;
	cin >> N;
	deque<int> arr;
	deque<int> p_arr;

	for (int i = 0; i < N; i++) {
		int input;
		cin >> input;
		arr.push_back(input);
	}

	while (!arr.empty()) {
		int element=arr.front();
		arr.pop_front();

		if (p_arr.size() == 0) {
			p_arr.push_back(element);
		}
		else if (p_arr.size() == 1) {
			if (p_arr[0] < element)
				p_arr.push_back(element);
			else
				p_arr[0] = element;
		}
		else if (p_arr.size() > 1) {

			//이진 탐색

			int start = 0;
			int end = p_arr.size() - 1;

			if (element <= p_arr[start])
				p_arr[start] = element;
			else if (element > p_arr[end])
				p_arr.push_back(element);
			else {

				int mid;

				do {
					mid = (start + end) / 2;
					if (p_arr[mid] < element)
						start = mid;
					else
						end = mid;
				} while (end - mid != 1);
				
				p_arr[end] = element;

			}
		}
	}

	cout << p_arr.size() << "\n";

	return 0;
}