#include <iostream>
#include <vector>
#include <map>
#include <cstdint>
#include <tuple>
#include <algorithm>
#include <random>

template<class K ,class V,class Sel,class Comp = std::less<K>>
std::vector<V> StableBakectSort(const std::vector<V>& D,Sel F) {
	std::map < K, std::vector<V>, Comp > B;

	for (auto& o : D) {
		B[F(o)].push_back(o);
	}
	std::vector<V> R;
	for (auto o : B) {
		R.insert(R.end(),o.second.begin(), o.second.end());
	}

	return R;
}

typedef std::uintmax_t Elem;
typedef std::tuple < Elem, Elem, Elem> Data;
typedef std::vector<Data> DType;
//template<class T> using MType = std::map<T, DType>;

DType MakeVector(std::size_t N, unsigned int S = 0) {
	std::minstd_rand mr(S);
	std::uniform_int_distribution<> ui(0, 16);

	DType R;

	for (std::size_t i = 0; i < N; i++) {
		R.push_back({ui(mr),ui(mr),ui(mr)});
	}

	return R;
}

bool Show(DType& In) {
	for (auto& o : In) {
		std::cout << std::get<0>(o) << ',' << std::get<1>(o) << ',' << std::get<2>(o) << '|';
	}
	std::cout << std::endl<< std::endl;
	return true;
}

int main() {
	auto D = MakeVector(32);
	Show(D);

	auto R = StableBakectSort<Elem>(D, [](auto& A) {return std::get<1>(A); });
	Show(R);

	return true;
}