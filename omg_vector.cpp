#include <iostream>
#include <vector>
#include <optional>

namespace omg {
	template<class T>
	struct params {
		std::optional<size_t> reserve;
		std::optional<size_t> size;
		std::optional<T> val;
	};
	
	template<class T, class A = std::allocator<T>>
	void apply_params (const params<T>& p, std::vector<T,A>& out) {
		if (p.reserve) {
			out.reserve(*p.reserve);
		}
		if (p.size) {
			if (p.val) out.resize(*p.size, *p.val);
			else out.resize(*p.size);			
		}
	}
	
	template <class T, class A = std::allocator<T>>
	std::vector<T, A> vector (
		std::initializer_list<T>&& values,
		const params<T>& p = params<T>{}
	) {
		std::vector<T,A> out {
			std::move(values)
		};
		apply_params(p, out);
		return out;
	}
	
	template <class T, class A = std::allocator<T>>
	std::vector<T, A> vector (
		const params<T>& p = params<T>{}
	) {
		std::vector<T,A> out;
		apply_params(p, out);
		return out;
	}
}

int main(int argc, char *argv[]) {
	{
		auto vec = omg::vector<int>(
			{0, 1, 4}, // This is an initializer list
			{.reserve = 10}
		);
		std::cerr << vec.size();	 // 3
	}
	{
		auto vec = omg::vector<int>(
			omg::params<int>{
				.size = 4,
				.val = 2
			}
		);
		std::cerr << vec.size();	// 4
	}
	{
		auto vec = omg::vector<int>(
			{ // This is of type params<int>
				.size = 4,
				.val = 2
			}
		);
		std::cerr << vec.size();	 // also 4
	}

	{
		auto vec = omg::vector<int>(
			{ // This is also an initializer list
				4,
				2
			}
		);
		std::cerr << vec.size();		
	}
}
