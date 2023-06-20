# omg_vector
Initialize C++ std::vector declaratively and explicitly! This is a toy project that is a proof-of-concept.

In many cases, construction can accept both () and {}. They often result in the same result, but {} has a distinct advantage that it will never be interpreted as a funcion declaration.
```
  My_class c (1, 2); // This is a class instanciation
  My_class c (); // But this is a function declaration...

  My_class c {1, 2}; // People thus prefer {} over ().
  My_class c {};     // Because, this is still a class instanciation.
```

The problem with std::vector is that it allows an aggregate initialization...
```
   std::vector<int> vec {4, 2}; // This is a vector with items 4 and 2.
   std::vector<int> vec (4, 2); // This is a vector of size 4, filled with 2.
```

I was tired of this problem. Can we be more explicit with what we do at the time of initialization?

Yes, and this toy code shows how to do the following:
```
		std::vector<int> vec = omg::vector<int>(
			{
				.size = 4,
				.val = 2
			}
		);
    // A vector with 4 items of value 2.
```

We can also reserve container space in a declarative manner.
```
		std::vector<int> vec = omg::vector<int>(
			{0, 1, 4},      // This is an initializer list
			{.reserve = 10} // This reserves some value.
		);
```
