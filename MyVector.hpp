#ifndef MYVECTOR_HPP
#define MYVECTOR_HPP

/**
 * TODO: Complete this class!
 */

/// Your welcome
#include <assert.h>
#include <iostream>
#include <string>

//
template <typename T>
class MyVector
{
	public:
		
		/*******************
		 * Static constants
		 ******************/
		
		/// Default capacity
		static constexpr size_t DEFAULT_CAPACITY = 64;
		
		/// Minimum capacity
		static constexpr size_t MINIMUM_CAPACITY = 8;
		
		/*****************************
		 * Constructors / Destructors
		 ****************************/
		
		/// Normal constructor
		MyVector(size_t capacity = MyVector::DEFAULT_CAPACITY) {
        	if (capacity <= MINIMUM_CAPACITY)
            	this->capacity_ = MINIMUM_CAPACITY;
        	else
            	this->capacity_ = capacity;

        	elements_ = new T[capacity_];
    }
		
		/// Copy constructor
		MyVector(const MyVector& other) {
			copyOther(other);
		}
		
		/**
		 * Destructor
		 * Should call clear() so each element gets its destructor called.
		 * Then, de-allocate the internal array and make it a nullptr, if its not already a nullptr.
		 */
		~MyVector() {

			clear();

			if(this->elements_ != nullptr)
				this->elements_ = nullptr;

			delete[] this->elements_;
		}
		
		/************
		 * Operators
		 ************/
		
		///	Assignment operator
		MyVector& operator=(const MyVector& rhs) {
			
			copyOther(rhs);

			return *this;
		}
		
		/// Operator overload to at()
		T& operator[](size_t index) const {
			
			if((index >= size_) || (index < 0))
				throw std::range_error("Error: index is outside the size boundary");

			return this->elements_[index];
		}

		/************
		 * Accessors
		 ************/
		
		/// Return the number of valid elements in our data
		size_t size() const {
			
			return this->size_;
		}
		
		/// Return the capacity of our internal array
		size_t capacity() const {
			
			return this->capacity_;
		}
		
		/**
		 * Check whether our vector is empty
		 * Return true if we have zero elements in our array (regardless of capacity)
		 * Otherwise, return false
		 */
		bool empty() const {
			
			return (size_ == 0);
		}
		/// Return a reference to the element at an index
		T& at(size_t index) const {

			if((index >= size_) || (index < 0))
				throw std::range_error("Error: index is outside the size boundary");

			return this->elements_[index];
		}

		/***********
		 * Mutators
		 ***********/
		
		/**
		 * Reserve capacity in advance, if our capacity isn't currently large enough.
		 * Useful if we know we're about to add a large number of elements, and we'd like to avoid the overhead of many internal changes to capacity.
		 */
		void reserve(size_t capacity) {
			
			if (size_ >= capacity)
				capacity *= 2;

			if(((capacity / 3) > size_))
				capacity /= 2;

			changeCapacity(capacity);
		}
		
		/**
		 * Set an element at an index.
		 * Throws range error if outside the size boundary.
		 * Returns a reference to the newly set element (not the original)
		 */
		T& set(size_t index, const T& element) {

			if(index >= size_ || index < 0)
				throw std::range_error("Error: index is outside the size boundary");

			elements_[index].~T();

			this->elements_[index] = element;
			
			return elements_[index];
		}

		/**
		 * Add an element onto the end of our vector, increasing the size by 1
		 * Should rely on the insert() function to avoid repeating code.
		 * Returns a reference to the newly inserted element
		 */
		T& push_back(const T& element) {
			
			insert(size_, element);

			return elements_[size_ - 1];
		}

		/**
		 * Remove the last element in our vector, decreasing the size by 1
		 * Should rely on the erase() function to avoid repeating code.
		 * Returns the new size.
		 */
		size_t pop_back() {
			
			erase(size_ - 1);

			return this->size_;
		}
		
		/**
		 * Insert an element at some index in our vector, increasing the size by 1
		 * 
		 * Scoot all elements at index and beyond, one to the right. This
		 * makes a "hole" available at the index, where you can then place
		 * the new element.
		 * 
		 * Returns a reference to the newly added element (not the original).
		 */
		T& insert(size_t index, const T& element) {

			if((index > size_) || (index < 0))
				throw std::range_error("Error: index is outside the size boundary");

			if (size_ >= capacity_) {
            	reserve(capacity_ * 2);
        	}

        	size_++;
        	
			for (size_t i = size_ - 1; i > index; i--) {
            	elements_[i] = elements_[i - 1];
        	}

        	elements_[index] = element;

        	return elements_[index];
		}
		
		/**
		 * Erase one element in our vector at the specified index, decreasing the size by 1.
		 * 
		 * This means you'd then have to scoot elements to the left to fill the "hole"
		 * 	left by the erased element.
		 * 
		 * Throws std::range_error if the index is out of bounds.
		 * 
		 * Calls the erased element's destructor.
		 * 
		 * Returns the new size.
		 */
		size_t erase(size_t index) {

			if(index >= size_ || index < 0)
				throw std::range_error("Error: index is of bounds");

			elements_[index].~T();

			size_--;

			if(((capacity_ / 3) > size_))
				reserve(capacity_ / 2);

			if((size_ - 1) > 0)
			{
				for (size_t i = index; i < size_; i++) {
            		elements_[i] = elements_[i + 1];
				}
        	}

        	return this->size_;
    }
		
		/**
		 * Calls each element's destructor, then clears our internal
		 * data by setting size to zero and resetting the capacity.
		*/
		void clear() {
			
			elements_ = nullptr;
			delete[] elements_;

			this->size_ = 0;
			this->capacity_ = 0;
		}
	
	/**
	 * Begin private members and methods.
	 * Private methods can often contain useful helper functions,
	 * or functions to reduce repeated code.
	*/
	private:
		
		/// Number of valid elements currently in our vector
		size_t size_ = 0;
		
		/// Capacity of our vector; The actual size of our internal array
		size_t capacity_ = 0;
		
		/**
		 * Our internal array of elements of type T.
		 * Starts off as a null pointer.
		 */
		T* elements_ = nullptr;
		
		/**
		 * Helper function that is called whenever we need to change the capacity of our vector
		 * Should throw std::range_error when asked to change to a capacity that cannot hold our existing elements.
		 * It's probably a good idea to make an additional helper function that decides
		 * 	whether to change capacity at all (and to what new capacity), that your public functions can rely upon.
		 */
	    void changeCapacity(size_t c) {

			if(c < size_)
				throw std::range_error("Error: capacity cannot hold existing elements");

        	T* newElements = new T[c];

        	for (size_t i = 0; i < size_; i++) {
            	newElements[i] = elements_[i];
        	}

        	delete[] elements_;
        	elements_ = newElements;
        	capacity_ = c;
    	}

		/**
		 * Copy another vector's elements into our own, by value.
		 * Does not simply copy the other vector's array's pointer
		 * Does not care about matching the capacity exactly.
		 * This is a helper function relied upon by the copy constructor and the assignment operator,
		 * 	to avoid repeated code.
		 * 
		 * You will probably want to make additional helper functions to make this one easier.
		 * Here is a suggested strategy for copying the internal array:
		 * 1. Deallocate the current array for 'this' (if it is already allocated)
		 * 2. Allocate a new array for 'this' of the appropriate size
		 * 3. Use a loop to copy elements one-by-one (by value)
		 * 4. Copy other relevant properties from the 'other' to 'this'
		 */
		void copyOther(const MyVector& other) {
        
			capacity_ = other.capacity_;
        	size_ = other.size_;
        	elements_ = new T[capacity_];

        	for (size_t i = 0; i < size_; i++) {
            	elements_[i] = other.elements_[i];
        	}
    	}
};

#endif